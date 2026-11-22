#!/usr/bin/env python3
"""
Dualocke: comprueba, sin compilador, lo que puede romper la compilación o el juego al añadir o
tocar mapas (ZONAS.md). Se hizo porque en el PC de Miguel no se puede compilar y los seis primeros
mapas nuevos se subieron sin apuntar sus scripts en data/event_scripts.s: no habrían compilado.

Uso (desde la raíz del repo):
    python3 tools/dualocke/comprobar_zonas.py            # todos los mapas de Hoenn
    python3 tools/dualocke/comprobar_zonas.py --resumen  # solo el número de avisos por tipo

Qué mira en cada mapa (los de Rojo Fuego, _Frlg, se saltan):
- scripts.inc apuntado en data/event_scripts.s;
- layout: existe, el map.bin mide ancho × alto y el borde existe;
- scripts de los objetos, carteles y casillas: la etiqueta existe;
- puertas (warps): el mapa de destino existe, el número de puerta de destino existe y la puerta
  está dentro del mapa (en el juego original hay muchas en casillas con colisión: es normal);
- conexiones: el otro mapa tiene la conexión de vuelta y, en las zonas nuevas, las casillas que se
  pisan a los dos lados del borde tienen la misma altura (si no, no se pasa: PRADO DE HADAS, 22/11/2026);
- puertas sin animación (MB_NON_ANIMATED_DOOR): sin colisión, porque se cruzan al pisarlas (TORRE de la
  ISLA DE RUINAS, 22/11/2026);
- objetos: en casillas que se pueden pisar, sin dos en la misma casilla, con constantes que
  existen (gráfico, flag, objeto);
- entrenadores: la constante existe, tiene equipo en trainers.party y no pasa de MAX_TRAINERS_COUNT;
- constantes de los scripts del mapa (FLAG_, VAR_, ITEM_, SPECIES_, TRAINER_, MAP_, MUS_...) y
  etiquetas a las que saltan o que leen;
- salvajes: el mapa de cada tabla existe y cada tipo tiene sus huecos;
- zonas de captura: caben en las variables y las zonas nuevas tienen cartel (map_name_popup.c).
Devuelve 1 si hay algún fallo.
"""

import glob
import json
import os
import re
import struct
import sys

sys.path.insert(0, "tools/dualocke")
import colocar_objetos as co  # noqa: E402

FALLOS = []
# Rarezas del juego original que no son fallos (comprobado con el repo sin tocar)
ORIGINALES = {
    ("puerta", "SlateportCity"), ("puerta", "SlateportCity_Harbor"),          # puertas del ferry, fuera del mapa
    ("puerta", "BattleFrontier_BattleDomeCorridor"), ("puerta", "BattleFrontier_BattleDomePreBattleRoom"),
    ("objeto", "BattleFrontier_BattlePalaceBattleRoom"),
    ("constante", "Route117"),                                                # LOCALID_DAYCARE_MON_*, de event_objects
}


def fallo(tipo, mapa, texto):
    if (tipo, mapa) not in ORIGINALES:
        FALLOS.append((tipo, mapa, texto))


def leer(ruta):
    with open(ruta, encoding="utf-8", errors="replace") as f:
        return f.read()


def constantes():
    """Nombres definidos en include/ (defines y miembros de enum) y los que se generan."""
    nombres = set()
    for ruta in glob.glob("include/**/*.h", recursive=True):
        texto = leer(ruta)
        nombres.update(re.findall(r"^\s*#define\s+(\w+)", texto, re.M))
        for cuerpo in re.findall(r"enum[^{;]*\{(.*?)\}", texto, re.S):
            nombres.update(re.findall(r"^\s*(\w+)\s*(?:=[^,\n]*)?,?\s*(?://.*)?$", cuerpo, re.M))
    # Las que se definen en los macros de ensamblador (MSGBOX_NPC = 2...)
    for ruta in glob.glob("asm/macros/*.inc") + glob.glob("constants/*.inc"):
        nombres.update(re.findall(r"^\s*(\w+)\s*=\s", leer(ruta), re.M))
        nombres.update(re.findall(r"^\s*\.(?:set|equiv)\s+(\w+)", leer(ruta), re.M))
        nombres.update(re.findall(r"^\s*enum\s+(\w+)", leer(ruta), re.M))
    return nombres


def valores_flags():
    """Valor de cada FLAG_ de include/constants/flags.h (las formas sencillas: 0x123, (OTRO + 0x12))."""
    valores = {}
    for nombre, expr in re.findall(r"^#define\s+(FLAG_\w+|SYSTEM_FLAGS|TRAINER_FLAGS_\w+)\s+([^/\n]+)",
                                   leer("include/constants/flags.h"), re.M):
        expr = expr.strip()
        m = re.fullmatch(r"\(?\s*(\w+)\s*\+\s*(0x[0-9A-Fa-f]+|\d+)\s*\)?", expr)
        if re.fullmatch(r"0x[0-9A-Fa-f]+|\d+", expr):
            valores[nombre] = int(expr, 0)
        elif m and m.group(1) in valores:
            valores[nombre] = valores[m.group(1)] + int(m.group(2), 0)
        elif expr in valores:
            valores[nombre] = valores[expr]
    return valores


# Prefijos de las carpetas de las zonas nuevas (los mismos que NUEVOS de autotile.py)
NUEVOS = ("Marisma", "Playa", "Bosque", "Isla", "Cumbre", "Desierto", "Ruinas", "Gruta", "Mansion", "Cienaga", "Cantera", "Prado")


def alturas_alrededor(info, x, y, w, h, con_la_suya=False):
    """Alturas (sin 0 ni 15) de las casillas que se pisan junto a (x, y) (y la suya, si se pide)."""
    sitios = [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)] + ([(x, y)] if con_la_suya else [])
    alturas = set()
    for nx, ny in sitios:
        if 0 <= nx < w and 0 <= ny < h:
            colision, alt, _ = info(nx, ny)
            if not colision and alt not in (0, 15):
                alturas.add(alt)
    return alturas


def rejilla_de(l, atributos, mb):
    """(ancho, alto, info) de un layout; info(x, y) = (colisión, altura, comportamiento)."""
    w, h = l["width"], l["height"]
    celdas = struct.unpack(f"<{w * h}H", open(l["blockdata_filepath"], "rb").read())
    prim, sec = atributos.get(l["primary_tileset"], []), atributos.get(l["secondary_tileset"], [])

    def info(x, y):
        v = celdas[y * w + x]
        mt = v & 0x3FF
        tabla, i = (prim, mt) if mt < 512 else (sec, mt - 512)
        return (v >> 10) & 3, v >> 12, mb.get(tabla[i] & 0xFF, "?") if i < len(tabla) else "?"
    return w, h, info


def alturas_en_el_borde(info, w, h, otra, con):
    """Casillas del borde (de este mapa) que se pisan, con la de enfrente también pisable y otra altura.
    El juego no deja pasar de una altura a otra (salvo 0 y 15). Fuera queda el agua (altura 1), porque se
    sale del agua a la orilla (altura 3) al dejar de surfear."""
    ow, oh, oinfo = otra
    d, off = con["direction"], con["offset"]
    if d in ("up", "down"):
        pares = [((x, 0 if d == "up" else h - 1), (x - off, oh - 1 if d == "up" else 0)) for x in range(w)]
    else:
        pares = [((0 if d == "left" else w - 1, y), (ow - 1 if d == "left" else 0, y - off)) for y in range(h)]
    malas = []
    for (x, y), (ox, oy) in pares:
        if not (0 <= ox < ow and 0 <= oy < oh):
            continue
        (c1, a1, _), (c2, a2, _) = info(x, y), oinfo(ox, oy)
        if not c1 and not c2 and a1 != a2 and not {a1, a2} & {0, 1, 15}:
            malas.append((x, y))
    return malas


def etiquetas():
    """Etiquetas de script y de texto de data/ y símbolos de C que usan los scripts."""
    nombres = set()
    for ruta in glob.glob("data/**/*.inc", recursive=True) + glob.glob("data/**/*.s", recursive=True):
        nombres.update(re.findall(r"^(\w+)::?", leer(ruta), re.M))
    return nombres


def macros_y_ordenes():
    nombres = set()
    for ruta in glob.glob("asm/macros/*.inc"):
        nombres.update(re.findall(r"^\s*\.macro\s+(\w+)", leer(ruta), re.M))
    return nombres


def main():
    solo_resumen = "--resumen" in sys.argv
    global FLAGS
    FLAGS = valores_flags()
    consts = constantes()
    labels = etiquetas()
    grupos = json.loads(leer("data/maps/map_groups.json"))
    carpetas = [c for g in grupos["group_order"] for c in grupos[g]]
    layouts = co.cargar_layouts()
    mb = {v: k for k, v in co.comportamientos().items()}
    atributos = co.atributos_tilesets()
    event_scripts = leer("data/event_scripts.s")
    mapas = {}
    for c in carpetas:
        ruta = f"data/maps/{c}/map.json"
        if not os.path.exists(ruta):
            fallo("mapa", c, "está en map_groups.json pero no tiene map.json")
            continue
        mapas[c] = json.loads(leer(ruta))
    por_id = {m["id"]: c for c, m in mapas.items()}
    consts.update(por_id)
    consts.update(layouts)
    consts.update(s["id"] for s in json.loads(leer("src/data/region_map/region_map_sections.json"))["map_sections"])
    consts.update({"MAPSEC_NONE", "MAPSEC_COUNT"})
    for m in mapas.values():
        consts.update(o["local_id"] for o in m.get("object_events", []) if isinstance(o.get("local_id"), str))
    specials = set(re.findall(r"def_special\s+(\w+)", leer("data/specials.inc")))
    simbolos_c = set()
    for ruta in glob.glob("src/**/*.c", recursive=True):
        simbolos_c.update(re.findall(r"^(?:\w[\w \*]*?)\b(\w+)\s*\(", leer(ruta), re.M))
    party = set(re.findall(r"^=== (TRAINER_\w+) ===", leer("src/data/trainers.party"), re.M))
    opp = leer("include/constants/opponents.h")
    ids = {n: int(v) for n, v in re.findall(r"^#define (TRAINER_\w+)\s+(\d+)\b", opp, re.M)}
    maximo = int(re.search(r"#define MAX_TRAINERS_COUNT_EMERALD\s+(\d+)", opp).group(1))
    cuenta = int(re.search(r"#define TRAINERS_COUNT_EMERALD\s+(\d+)", opp).group(1))
    emerald = {n: v for n, v in ids.items() if v < 1000 and not n.endswith("_FRLG")}
    PREFIJOS = ("FLAG_", "VAR_", "ITEM_", "SPECIES_", "TRAINER_", "MAP_", "MUS_", "SE_", "WEATHER_", "OBJ_EVENT_GFX_",
                "MOVEMENT_TYPE_", "B_OUTCOME_", "LOCALID_", "MSGBOX_", "FADE_", "MOVE_", "TRAINER_TYPE_")

    for c, m in mapas.items():
        if c.endswith("_Frlg") or m.get("region") not in (None, "REGION_HOENN"):
            continue
        # scripts.inc apuntado
        if os.path.exists(f"data/maps/{c}/scripts.inc") and f'"data/maps/{c}/scripts.inc"' not in event_scripts:
            fallo("scripts sin apuntar", c, "su scripts.inc no está en data/event_scripts.s")
        l = layouts.get(m.get("layout"))
        if not l:
            fallo("layout", c, f"no existe el layout {m.get('layout')}")
            continue
        w, h = l["width"], l["height"]
        if not os.path.exists(l["blockdata_filepath"]) or os.path.getsize(l["blockdata_filepath"]) != w * h * 2:
            fallo("layout", c, f"{l['blockdata_filepath']} no mide {w}x{h}")
            continue
        if not os.path.exists(l["border_filepath"]):
            fallo("layout", c, f"falta {l['border_filepath']}")
        celdas = struct.unpack(f"<{w * h}H", open(l["blockdata_filepath"], "rb").read())
        prim, sec = atributos.get(l["primary_tileset"], []), atributos.get(l["secondary_tileset"], [])

        def info(x, y):
            v = celdas[y * w + x]
            mt = v & 0x3FF
            tabla, i = (prim, mt) if mt < 512 else (sec, mt - 512)
            return (v >> 10) & 3, v >> 12, mb.get(tabla[i] & 0xFF, "?") if i < len(tabla) else "?"

        for clave in ("region_map_section", "music", "weather"):
            if m.get(clave) and m[clave] not in consts:
                fallo("constante", c, f"{clave}: {m[clave]} no existe")
        # puertas
        for n, wp in enumerate(m.get("warp_events", [])):
            destino = wp["dest_map"]
            if destino in ("MAP_DYNAMIC", "MAP_UNDEFINED"):
                continue
            if destino not in por_id:
                fallo("puerta", c, f"la puerta {n} va a {destino}, que no existe")
            else:
                otras = mapas[por_id[destino]].get("warp_events", [])
                if not str(wp["dest_warp_id"]).isdigit() or int(wp["dest_warp_id"]) >= len(otras):
                    if not str(wp["dest_warp_id"]).startswith("WARP_ID"):
                        fallo("puerta", c, f"la puerta {n} va a la puerta {wp['dest_warp_id']} de {destino}, que solo tiene {len(otras)}")
            if not (0 <= wp["x"] < w and 0 <= wp["y"] < h):
                fallo("puerta", c, f"la puerta {n} está fuera del mapa ({wp['x']}, {wp['y']})")
            elif c.startswith(NUEVOS) and wp.get("elevation") not in (0, 15):
                # Una puerta solo se usa si su altura es la del jugador (o 0). Pasó en la LADERA de la CUMBRE
                # METEORO: puertas a 3 sobre suelo a 5, y no se podía salir (Miguel, 18/11/2026).
                alturas = alturas_alrededor(info, wp["x"], wp["y"], w, h)
                if alturas and wp["elevation"] not in alturas:
                    fallo("altura", c, f"la puerta {n} está a altura {wp['elevation']} y el suelo de al lado a "
                                       f"{sorted(alturas)}: no se puede usar (pon 0)")
            if 0 <= wp["x"] < w and 0 <= wp["y"] < h and info(wp["x"], wp["y"])[2] == "MB_NON_ANIMATED_DOOR"                     and info(wp["x"], wp["y"])[0]:
                # Se cruzan al pisarlas (TryStartWarpEventScript): con colisión no se entra. Pasó en la TORRE
                # de la ISLA DE RUINAS (lo vio el bot de Jorge, #116, 22/11/2026).
                fallo("puerta", c, f"la puerta {n} ({wp['x']}, {wp['y']}) es una puerta sin animación con "
                                   "colisión: no se puede entrar (quítale la colisión)")
        # objetos con una altura que no es la del suelo: no se pueden coger ni hablarles
        if c.startswith(NUEVOS):
            for o in m.get("object_events", []) + m.get("bg_events", []):
                if not (isinstance(o.get("x"), int) and 0 <= o["x"] < w and 0 <= o["y"] < h):
                    continue
                if o.get("elevation") in (0, 15, None):
                    continue
                alturas = alturas_alrededor(info, o["x"], o["y"], w, h, con_la_suya=True)
                if alturas and o["elevation"] not in alturas:
                    fallo("altura", c, f"({o['x']}, {o['y']}) {o.get('flag') or o.get('script')}: altura "
                                       f"{o['elevation']} sobre suelo a {sorted(alturas)}")
        # conexiones
        for con in m.get("connections") or []:
            if con["map"] not in por_id:
                fallo("conexión", c, f"conecta con {con['map']}, que no existe")
                continue
            vuelta = {"up": "down", "down": "up", "left": "right", "right": "left", "dive": "emerge", "emerge": "dive"}
            otras = mapas[por_id[con["map"]]].get("connections") or []
            if not any(o["map"] == m["id"] and o["direction"] == vuelta.get(con["direction"]) for o in otras):
                fallo("conexión", c, f"{con['direction']} con {con['map']}, pero ese mapa no conecta de vuelta")
            otro = por_id[con["map"]]
            if con["direction"] in ("up", "down", "left", "right") and (c.startswith(NUEVOS) or otro.startswith(NUEVOS)):
                lo = layouts.get(mapas[otro].get("layout"))
                if lo:
                    malas = alturas_en_el_borde(info, w, h, rejilla_de(lo, atributos, mb), con)
                    if malas:
                        fallo("altura", c, f"{con['direction']} con {con['map']}: en {malas[:4]} las casillas de los "
                                           "dos lados tienen distinta altura y no se pasa")
        # objetos
        vistos = {}
        for o in m.get("object_events", []):
            if isinstance(o.get("x"), int) and 0 <= o["x"] < w and 0 <= o["y"] < h:
                if (o["x"], o["y"]) in vistos and "FLAG" not in str(o.get("flag")) + str(vistos[(o["x"], o["y"])]):
                    fallo("objeto", c, f"dos objetos sin flag en ({o['x']}, {o['y']})")
                vistos[(o["x"], o["y"])] = o.get("flag")
            for clave in ("graphics_id", "flag", "movement_type", "trainer_type"):
                v = o.get(clave)
                if isinstance(v, str) and v.startswith(PREFIJOS) and v not in consts:
                    fallo("constante", c, f"objeto en ({o.get('x')}, {o.get('y')}): {v} no existe")
            sc = o.get("script")
            if sc and sc not in ("0x0", "NULL", "0") and sc not in labels:
                fallo("script", c, f"objeto en ({o.get('x')}, {o.get('y')}): no existe el script {sc}")
            if o.get("graphics_id") == "OBJ_EVENT_GFX_ITEM_BALL":
                item = o.get("trainer_sight_or_berry_tree_id")
                if isinstance(item, str) and item.startswith("ITEM_") and item not in consts                         and not item.startswith(("ITEM_TM_", "ITEM_HM_")):
                    fallo("constante", c, f"bola en ({o['x']}, {o['y']}): {item} no existe")
        for b in m.get("bg_events", []):
            # Los objetos ocultos necesitan un flag >= FLAG_HIDDEN_ITEMS_START: si no, no compila
            if b.get("type") == "hidden_item":
                valor = FLAGS.get(b.get("flag"))
                if valor is not None and valor < FLAGS["FLAG_HIDDEN_ITEMS_START"]:
                    fallo("oculto", c, f"objeto oculto en ({b['x']}, {b['y']}): {b['flag']} vale 0x{valor:03X}, "
                                       f"menos que FLAG_HIDDEN_ITEMS_START (0x{FLAGS['FLAG_HIDDEN_ITEMS_START']:03X})")
            for clave in ("script", ):
                sc = b.get(clave)
                if sc and sc not in ("0x0", "NULL") and sc not in labels:
                    fallo("script", c, f"cartel en ({b['x']}, {b['y']}): no existe el script {sc}")
            for clave in ("item", "flag"):
                v = b.get(clave)
                if isinstance(v, str) and v.startswith(PREFIJOS) and v not in consts                         and not v.startswith(("ITEM_TM_", "ITEM_HM_")):
                    fallo("constante", c, f"objeto oculto en ({b['x']}, {b['y']}): {v} no existe")
        for q in m.get("coord_events", []):
            sc = q.get("script")
            if sc and sc not in ("0x0", "NULL") and sc not in labels:
                fallo("script", c, f"casilla ({q['x']}, {q['y']}): no existe el script {sc}")
        # scripts del mapa
        ruta = f"data/maps/{c}/scripts.inc"
        if os.path.exists(ruta):
            texto = re.sub(r"@.*$", "", leer(ruta), flags=re.M)
            texto = re.sub(r'\.string\s+"(?:[^"\\]|\\.)*"', "", texto)
            for token in set(re.findall(r"\b[A-Z][A-Z0-9_]{3,}\b", texto)):
                # Las MT y MO se llaman ITEM_TM_<movimiento>: salen de una macro (constants/tms_hms.h)
                if token.startswith(("ITEM_TM_", "ITEM_HM_")):
                    continue
                if token.startswith(PREFIJOS) and token not in consts:
                    fallo("constante", c, f"scripts.inc usa {token}, que no existe")
            for t in set(re.findall(r"\bTRAINER_\w+", texto)):
                if t in emerald or t in ids:
                    if t not in party and not t.startswith(("TRAINER_TYPE", "TRAINER_BATTLE", "TRAINER_PARTNER")):
                        fallo("entrenador", c, f"{t} no tiene equipo en trainers.party")
            for etiqueta in set(re.findall(r"\b(?:%s|Dualocke|Common|EventScript|Std|Route\d+|gText)_\w+" % re.escape(c), texto)):
                if etiqueta not in labels and etiqueta not in simbolos_c and etiqueta not in consts:
                    fallo("etiqueta", c, f"scripts.inc usa {etiqueta}, que no existe")
            for sp in re.findall(r"^\s*special(?:var\s+\w+,)?\s+(\w+)", texto, re.M):
                if sp not in specials:
                    fallo("special", c, f"{sp} no está en data/specials.inc")
                elif sp not in simbolos_c:
                    fallo("special", c, f"{sp} no está definido en src/")

    # entrenadores
    for t, v in emerald.items():
        if v >= maximo and not t.startswith("TRAINER_PARTNER"):
            fallo("entrenador", "-", f"{t} = {v} pasa de MAX_TRAINERS_COUNT_EMERALD ({maximo})")
    usados = [v for t, v in emerald.items() if v < maximo]
    if usados and max(usados) + 1 != cuenta:
        fallo("entrenador", "-", f"TRAINERS_COUNT_EMERALD es {cuenta} y el último entrenador es el {max(usados)}")
    for t in [t for t, v in emerald.items() if 0 < v < maximo and t not in party]:
        fallo("entrenador", "-", f"{t} no tiene equipo en trainers.party")

    # entrenadores nuevos (zonas_nuevas.py): la clase, la foto y la música las usa algún otro
    # entrenador, el nombre cabe y las especies existen
    import zonas_nuevas as zn
    texto_party = leer("src/data/trainers.party")
    bloques = dict(zip(re.findall(r"^=== (TRAINER_\w+) ===", texto_party, re.M),
                       re.split(r"^=== TRAINER_\w+ ===[ 	]*$", texto_party, flags=re.M)[1:]))
    for t, datos in zn.NUEVOS.items():
        if t not in ids:
            fallo("entrenador", "-", f"{t} no está en include/constants/opponents.h")
        if t not in bloques:
            fallo("entrenador", "-", f"{t} no está en trainers.party (¿falta lanzar zonas_nuevas.py?)")
            continue
        otros = "".join(b for n, b in bloques.items() if n not in zn.NUEVOS)
        for campo, valor in datos["cabecera"]:
            if campo == "Name" and len(valor) > 10:
                fallo("entrenador", "-", f"{t}: el nombre {valor} pasa de 10 letras")
            if campo in ("Class", "Pic", "Music") and not re.search("^" + campo + ": " + re.escape(valor) + r"\s*$", otros, re.M):
                fallo("entrenador", "-", f"{t}: ningún otro entrenador usa {campo}: {valor}")
        for especie in datos["equipo"]:
            if "SPECIES_" + re.sub(r"[^A-Z0-9]+", "_", especie.upper()).strip("_") not in consts:
                fallo("entrenador", "-", f"{t}: no existe la especie {especie}")
        if datos["mapa"] not in por_id:
            fallo("entrenador", "-", f"{t}: no existe el mapa {datos['mapa']}")

    # salvajes
    salvajes = json.loads(leer("src/data/wild_encounters.json"))
    for g in salvajes["wild_encounter_groups"]:
        if g.get("label") != "gWildMonHeaders":
            continue
        huecos = {f["type"]: len(f["encounter_rates"]) for f in g["fields"]}
        vistos = set()
        for e in g["encounters"]:
            if e["map"] not in por_id:
                fallo("salvajes", e["map"], "la tabla es de un mapa que no existe")
            if (e["map"], e.get("base_label")) in vistos:
                fallo("salvajes", e["map"], "tabla repetida")
            vistos.add((e["map"], e.get("base_label")))
            for tipo, n in huecos.items():
                if tipo in e:
                    if len(e[tipo]["mons"]) != n:
                        fallo("salvajes", e["map"], f"{tipo} tiene {len(e[tipo]['mons'])} huecos y hacen falta {n}")
                    for mon in e[tipo]["mons"]:
                        if mon["species"] not in consts:
                            fallo("salvajes", e["map"], f"{mon['species']} no existe")

    # zonas de captura y carteles
    secciones = [s["id"] for s in json.loads(leer("src/data/region_map/region_map_sections.json"))["map_sections"]]
    dualocke = leer("src/dualocke.c")
    ultima = re.search(r"#define HOENN_EXTRA_MAPSEC_LAST\s+(\w+)", dualocke).group(1)
    primera = re.search(r"#define HOENN_EXTRA_MAPSEC_FIRST\s+(\w+)", dualocke).group(1)
    n_vars = len(re.findall(r"^\s*VAR_DUALOCKE_ZONES_\d+,", dualocke, re.M))
    if secciones[-1] != ultima:
        fallo("zonas", "-", f"la última zona es {secciones[-1]} y HOENN_EXTRA_MAPSEC_LAST es {ultima}")
    total = secciones.index("MAPSEC_PALLET_TOWN") + secciones.index(ultima) - secciones.index(primera) + 1
    if total > n_vars * 16:
        fallo("zonas", "-", f"hay {total} zonas de captura y solo caben {n_vars * 16}")
    popup = leer("src/map_name_popup.c")
    for s in secciones[secciones.index("MAPSEC_TRAINER_HILL") + 1:]:
        if len(re.findall(rf"\[{s} - KANTO_MAPSEC_COUNT\]", popup)) < 2:
            fallo("zonas", "-", f"{s} no tiene sus dos carteles en src/map_name_popup.c")

    tipos = {}
    for tipo, mapa, texto in FALLOS:
        tipos[tipo] = tipos.get(tipo, 0) + 1
        if not solo_resumen:
            print(f"[{tipo}] {mapa}: {texto}")
    print(f"Dualocke: {len(mapas)} mapas; zonas de captura {total} de {n_vars * 16}; "
          f"entrenadores {cuenta} de {maximo}; fallos: {len(FALLOS)} {tipos if tipos else ''}")
    return 1 if FALLOS else 0


if __name__ == "__main__":
    sys.exit(main())
