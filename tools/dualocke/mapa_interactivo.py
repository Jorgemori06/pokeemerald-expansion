#!/usr/bin/env python3
"""
Dualocke: genera MAPA.html, el mapa interactivo de Hoenn (estilo los mapas web de otros juegos).

Uso (desde la raíz del repo):
    python3 tools/dualocke/mapa_interactivo.py

Saca todo de los mapas del juego, así que se vuelve a lanzar cuando se toque un mapa:
- Dibuja cada mapa con sus tilesets (como Porymap) y los coloca en el mundo por sus conexiones
  (como ver_mundo.py). Los mapas de bajo el agua van en su propio nivel, encima de su ruta.
- Las cuevas, edificios y zonas sueltas se abren aparte, desde su puerta, con selector de plantas.
- Puntos: puertas, sitios (Centro POKéMON, tienda, gimnasio…), entrenadores, objetos del suelo
  (megapiedras y Ticket-Recuerdo con nombre; el resto sale al azar con la semilla), POKéMON fuertes
  (guardianes y estáticos) y las zonas nuevas, con el texto de la guía.
- Zonas de captura: las que tienen salvajes (una por nombre de zona, como en el juego).

La página es un solo archivo (con las imágenes y Leaflet dentro), como GUIA.html. La plantilla
es tools/dualocke/mapa/plantilla.html.
"""

import base64
import html
import io
import json
import os
import re
import sys
from collections import deque

import numpy as np
from PIL import Image

sys.path.insert(0, "tools/dualocke")
import ver_mapa as vm  # noqa: E402

SALIDA = "MAPA.html"
PLANTILLA = "tools/dualocke/mapa/plantilla.html"
GUIA = "GUIA.html"

# Mapas que no son de Hoenn o que no se pisan en la partida
FUERA = ("_Frlg", "SecretBase", "Prototype", "Unused", "TradeCenter", "RecordCorner", "BattleColosseum",
         "UnionRoom", "InsideOfTruck")
# Zonas nuevas del dualocke (ZONAS.md) y las islas del ferry, que ahora tienen otro contenido
NUEVAS = ("CIENAGA_TOXICA", "BOSQUE_SINIESTRO", "CUMBRE_METEORO", "PLAYA_VOLCANICA", "CANTERA", "PRADO_HADAS",
          "ISLA_DRAGON", "ISLA_DE_RUINAS", "ISLA_VOLCANICA", "ISLA_ARENOSA", "BOSQUE_FRONDOSO",
          "MANSION_OLVIDADA", "MARISMA_AZULIZA", "DESIERTO_PROFUNDO", "RUINAS_ARENOSAS", "ISLA_NEVADA",
          "GRUTA_IGNEA", "SOUTHERN_ISLAND", "FARAWAY_ISLAND", "BIRTH_ISLAND", "NAVEL_ROCK")
# Edificios de las ciudades: (patrón en el nombre del mapa, nombre, ¿sale en la capa de sitios?)
EDIFICIOS = [
    (r"PokemonCenter", "CENTRO POKéMON", "🏥"), (r"_Mart$", "TIENDA", "🛒"), (r"_Gym", "GIMNASIO", "🏅"),
    (r"DepartmentStore", "CENTRO COMERCIAL", "🏬"), (r"Harbor", "PUERTO", "⚓"), (r"Contest", "SALA DE CONCURSOS", "🎀"),
    (r"GameCorner", "CASINO", "🎰"), (r"BikeShop", "TIENDA DE BICIS", "🚲"), (r"OceanicMuseum", "MUSEO OCEÁNICO", "🏛"),
    (r"SpaceCenter", "CENTRO ESPACIAL", "🚀"), (r"WeatherInstitute", "INSTITUTO METEOROLÓGICO", "🌦"),
    (r"PokemonSchool", "ESCUELA POKéMON", "🏫"), (r"DevonCorp", "DEVON S.A.", "🏢"), (r"Shipyard", "ASTILLERO", "🛠"),
    (r"PokemonFanClub", "CLUB DE FANS", "🎤"), (r"MoveDeleter", "QUITAMOVIMIENTOS", "✂"),
    (r"NameRater", "CALIFICANOMBRES", "📝"), (r"PokemonLeague|_EliteFour|ChampionsRoom", "LIGA POKéMON", "🏆"),
    (r"TrickHouse", "CASA TRAMPA", "🎩"), (r"CyclingRoad", "CARRIL BICI", None),
    (r"Lab$", "LABORATORIO", "🔬"), (r"House|Home", "CASA", None),
]
# Islas del ferry que no salen en el mapa de la región: debajo de Hoenn, en fila (coordenadas del mapa de la región)
SIN_SITIO = {"MAPSEC_FARAWAY_ISLAND": {"x": 13, "y": 15.3}, "MAPSEC_BIRTH_ISLAND": {"x": 16, "y": 15.3},
             "MAPSEC_NAVEL_ROCK": {"x": 19, "y": 15.3}}
PLANTAS = [
    (r"_B(\d)F_(\d)R$", lambda m: f"Sótano {m.group(1)}, sala {m.group(2)}", lambda m: -int(m.group(1))),
    (r"_(\d)F_(\d)R$", lambda m: f"Planta {m.group(1)}, sala {m.group(2)}", lambda m: int(m.group(1))),
    (r"_B(\d)F$", lambda m: f"Sótano {m.group(1)}", lambda m: -int(m.group(1))),
    (r"_(\d)F$", lambda m: f"Planta {m.group(1)}", lambda m: int(m.group(1))),
    (r"_Roof$|_Top$|_Summit$|Cima$", lambda m: "Cima", lambda m: 9),
    (r"_Exterior$|_Outside\w*$", lambda m: "Exterior", lambda m: 0.5),
    (r"_Entrance$", lambda m: "Entrada", lambda m: 0.4),
    (r"_(Camara|Cueva|Valle|Torre|Desvan|Crater|Ladera|Interior)$",
     lambda m: {"Camara": "Cámara", "Desvan": "Desván", "Crater": "Cráter"}.get(m.group(1), m.group(1)), lambda m: 0),
]


def leer_json(ruta):
    with open(ruta, encoding="utf-8") as f:
        return json.load(f)


# ---------------------------------------------------------------- dibujar los mapas

class Dibujante:
    """Dibuja los mapas con numpy (mismo resultado que ver_mapa.dibujar, mucho más rápido)."""

    def __init__(self):
        self.carpetas = vm.carpetas_tilesets()
        self.paletas = vm.carpetas_paletas()
        self.ts = {}
        self.bloques = {}

    def tileset(self, nombre):
        if nombre not in self.ts:
            t = vm.Tileset(self.carpetas[nombre], self.paletas.get(nombre))
            a = np.array(Image.open(os.path.join(t.carpeta, "tiles.png"))) & 15
            t.np = a.reshape(a.shape[0] // 8, 8, a.shape[1] // 8, 8).transpose(0, 2, 1, 3).reshape(-1, 8, 8)
            self.ts[nombre] = t
        return self.ts[nombre]

    def metatiles(self, prim_n, sec_n):
        clave = (prim_n, sec_n)
        if clave in self.bloques:
            return self.bloques[clave]
        prim, sec = self.tileset(prim_n), self.tileset(sec_n)
        pal = np.zeros((16, 16, 3), np.uint8)
        for i in range(16):
            ts = prim if i < vm.PALETAS_PRIMARIO else sec
            colores = ts.paletas.get(i) or prim.paletas.get(i) or [(255, 0, 255)] * 16
            pal[i] = (list(colores) + [(255, 0, 255)] * 16)[:16]
        fondo = pal[0][0]
        salida = np.zeros((1024, 16, 16, 3), np.uint8)
        salida[:] = fondo
        vacio = np.zeros((8, 8), np.uint8)
        for mt in range(1024):
            ts, base = (prim, mt) if mt < vm.METATILES_PRIMARIO else (sec, mt - vm.METATILES_PRIMARIO)
            for capa in range(2):
                for k in range(4):
                    i = base * 8 + capa * 4 + k
                    if i >= len(ts.metatiles):
                        continue
                    v = ts.metatiles[i]
                    t, hf, vf, p = v & 0x3FF, (v >> 10) & 1, (v >> 11) & 1, v >> 12
                    origen, j = (prim.np, t) if t < vm.TILES_PRIMARIO else (sec.np, t - vm.TILES_PRIMARIO)
                    d = origen[j] if j < len(origen) else vacio
                    if hf:
                        d = d[:, ::-1]
                    if vf:
                        d = d[::-1, :]
                    ox, oy = (k % 2) * 8, (k // 2) * 8
                    trozo = salida[mt, oy:oy + 8, ox:ox + 8]
                    hay = d != 0
                    trozo[hay] = pal[p][d[hay]]
        self.bloques[clave] = salida
        return salida

    def dibujar(self, layout):
        w, h = layout["width"], layout["height"]
        with open(layout["blockdata_filepath"], "rb") as f:
            celdas = np.frombuffer(f.read(), dtype="<u2")[:w * h] & 0x3FF
        bloques = self.metatiles(layout["primary_tileset"], layout["secondary_tileset"])
        img = bloques[celdas].reshape(h, w, 16, 16, 3).transpose(0, 2, 1, 3, 4).reshape(h * 16, w * 16, 3)
        return Image.fromarray(img)


def png_base64(img):
    """PNG con paleta (los mapas tienen menos de 256 colores: sin pérdida)."""
    if img.getcolors(256) is None:
        print("Dualocke: un mapa tiene más de 256 colores; se reduce la paleta")
    buf = io.BytesIO()
    img.convert("P", palette=Image.ADAPTIVE, colors=256).save(buf, "PNG", optimize=True)
    return "data:image/png;base64," + base64.b64encode(buf.getvalue()).decode()


# ---------------------------------------------------------------- datos del juego

def nombres_objetos():
    with open("src/data/items.h", encoding="utf-8") as f:
        texto = f.read()
    return dict(re.findall(r'\[(ITEM_\w+)\]\s*=\s*\{\s*(?://[^\n]*\n\s*)?\.name = ES\(ITEM_NAME\("[^"]*"\), ITEM_NAME\("([^"]*)"\)\)',
                           texto))


def clases_entrenador():
    with open("src/battle_main.c", encoding="utf-8") as f:
        texto = f.read()
    return dict(re.findall(r'\[(TRAINER_CLASS_\w+)\]\s*=\s*\{\s*ES\(_\("[^"]*"\),\s*_\("([^"]*)"\)\)', texto))


def entrenadores():
    """{TRAINER_X: (clase, nombre, nivel máximo, doble)} de trainers.party."""
    clases = clases_entrenador()
    datos = {}
    with open("src/data/trainers.party", encoding="utf-8") as f:
        texto = f.read()
    for bloque in re.split(r"^=== ", texto, flags=re.M)[1:]:
        cab, _, cuerpo = bloque.partition("\n")
        clave = cab.strip(" =")
        nombre = re.search(r"^Name: *(.*)$", cuerpo, re.M)
        clase = re.search(r"^Class: *(.*)$", cuerpo, re.M)
        niveles = [int(n) for n in re.findall(r"^Level: *(\d+)", cuerpo, re.M)]
        doble = re.search(r"^Double Battle: *Yes", cuerpo, re.M) is not None
        c = "TRAINER_CLASS_" + re.sub(r"[^A-Z0-9]+", "_", (clase.group(1) if clase else "").upper()).strip("_")
        datos[clave] = (clases.get(c, clase.group(1).upper() if clase else ""), nombre.group(1).strip() if nombre else "",
                        max(niveles) if niveles else 0, doble)
    return datos


def etiquetas_de(texto):
    """{etiqueta: cuerpo} de un scripts.inc."""
    partes = re.split(r"^(\w+)::?\s*$", texto, flags=re.M)
    return {partes[i]: partes[i + 1] for i in range(1, len(partes) - 1, 2)}


def texto_guia():
    """{NOMBRE EN MAYÚSCULAS de la tarjeta: [frases]} de las tarjetas de Novedades de GUIA.html."""
    if not os.path.exists(GUIA):
        return []
    with open(GUIA, encoding="utf-8") as f:
        texto = f.read()
    i = texto.find("Novedades</h2>")
    if i < 0:
        return []
    tarjetas = []
    for titulo, cuerpo in re.findall(r'<div class="tarjeta"><h3>(.*?)</h3><ul>(.*?)</ul></div>', texto[i:], re.S):
        limpiar = (lambda s: html.unescape(re.sub(r"\s+", " ", re.sub(r"<[^>]+>", "", s))).strip())
        tarjetas.append((limpiar(titulo), [limpiar(li) for li in re.findall(r"<li>(.*?)</li>", cuerpo, re.S)]))
    return tarjetas


def parte_de(carpeta, base):
    """Nombre de la planta y orden (las de arriba primero) de un mapa de un grupo."""
    for patron, nombre, orden in PLANTAS:
        m = re.search(patron, carpeta)
        if m:
            return nombre(m), orden(m)
    if carpeta == base:
        return "Principal", 1
    resto = carpeta[len(base):].strip("_") if carpeta.startswith(base) else carpeta
    return re.sub(r"(?<=[a-z])(?=[A-Z0-9])", " ", resto).replace("_", " "), 0


def main():
    layouts = {l["id"]: l for l in leer_json("data/layouts/layouts.json")["layouts"] if "id" in l}
    grupos_json = leer_json("data/maps/map_groups.json")
    secciones = {s["id"]: s for s in leer_json("src/data/region_map/region_map_sections.json")["map_sections"]}
    mapas, por_id = {}, {}
    for g in grupos_json["group_order"]:
        for carpeta in grupos_json[g]:
            if any(f in carpeta for f in FUERA):
                continue
            m = leer_json(f"data/maps/{carpeta}/map.json")
            if m["layout"] not in layouts:
                continue
            mapas[carpeta] = m
            por_id[m["id"]] = carpeta

    def nombre_sec(sec):
        s = secciones.get(sec)
        return s["name"] if s and s.get("name") else sec.replace("MAPSEC_", "").replace("_", " ")

    # --- el mundo: mapas exteriores unidos por conexiones, desde VILLA RAÍZ
    pos = {"LittlerootTown": (0, 0)}
    cola = deque(["LittlerootTown"])
    while cola:
        c = cola.popleft()
        l = layouts[mapas[c]["layout"]]
        x, y = pos[c]
        for con in mapas[c].get("connections") or []:
            d = por_id.get(con["map"])
            if con["direction"] not in ("up", "down", "left", "right") or not d or d in pos:
                continue
            ld = layouts[mapas[d]["layout"]]
            off = con["offset"]
            pos[d] = {"up": (x + off, y - ld["height"]), "down": (x + off, y + l["height"]),
                      "left": (x - ld["width"], y + off), "right": (x + l["width"], y + off)}[con["direction"]]
            cola.append(d)
    minx = min(p[0] for p in pos.values())
    miny = min(p[1] for p in pos.values())
    mundo = {c: (x - minx, y - miny, 0) for c, (x, y) in pos.items()}
    # Bajo el agua: encima de su ruta, en el nivel -1
    for c, (x, y, _) in list(mundo.items()):
        for con in mapas[c].get("connections") or []:
            d = por_id.get(con["map"])
            if con["direction"] == "dive" and d and d not in mundo:
                mundo[d] = (x, y, -1)

    # Los de bajo el agua sin conexión de buceo (la RUTA 134 bucea por script): encima de su ruta
    for c in mapas:
        r = c.replace("Underwater_", "")
        if c.startswith("Underwater_") and c not in mundo and r in mundo and mundo[r][2] == 0:
            mundo[c] = (mundo[r][0], mundo[r][1], -1)

    # --- grupos (para el selector de plantas) y nombres
    secs_mundo = {mapas[c].get("region_map_section") for c, v in mundo.items() if v[2] == 0}
    exteriores = ("MAP_TYPE_ROUTE", "MAP_TYPE_TOWN", "MAP_TYPE_CITY", "MAP_TYPE_OCEAN_ROUTE")
    # Zonas con edificios: las del mundo, las ciudades sueltas (ARRECÍPOLIS) y el FRENTE BATALLA
    secs_ciudad = secs_mundo | {m.get("region_map_section") for m in mapas.values()
                                if m.get("map_type") in ("MAP_TYPE_TOWN", "MAP_TYPE_CITY")} | {"MAPSEC_BATTLE_FRONTIER"}
    info = {}
    for carpeta, m in mapas.items():
        sec = m.get("region_map_section") or ""
        l = layouts[m["layout"]]
        icono = None
        if carpeta in mundo:
            grupo, nombre = None, nombre_sec(sec)
        elif sec in secs_ciudad and m.get("map_type") in exteriores:
            grupo, nombre = sec, nombre_sec(sec)
        elif sec in secs_ciudad:
            # Edificio de una ciudad o ruta: se agrupan sus plantas por el nombre
            grupo = re.sub(r"_(B?\d+F)(_\d+R)?$", "", carpeta)
            tipo = next(((n, ic) for p, n, ic in EDIFICIOS if re.search(p, grupo)), ("EDIFICIO", None))
            nombre = f"{tipo[0]} · {nombre_sec(sec)}"
            icono = tipo[1]
        else:
            grupo, nombre = sec, nombre_sec(sec)
        info[carpeta] = {**({"ic": icono} if icono else {}), "e": 1 if carpeta not in mundo and sec in secs_ciudad
                                                                     and m.get("map_type") not in exteriores else 0,
                         "n": nombre, "w": l["width"], "h": l["height"], "sec": sec, "grupo": grupo,
                         "tipo": m.get("map_type", "")}
    grupos = {}
    for carpeta, i in info.items():
        if i["grupo"]:
            grupos.setdefault(i["grupo"], []).append(carpeta)
    for g, lista in grupos.items():
        base = min(lista, key=len)
        partes = {c: parte_de(c, base) for c in lista}
        lista.sort(key=lambda c: (-partes[c][1], c))
        for c in lista:
            info[c]["p"] = partes[c][0] if len(lista) > 1 else ""

    # --- puntos de cada mapa
    objetos = nombres_objetos()
    trainers = entrenadores()
    puntos = []
    especies_fuertes = 0
    for carpeta, m in mapas.items():
        ruta_scripts = f"data/maps/{carpeta}/scripts.inc"
        scripts = {}
        if os.path.exists(ruta_scripts):
            with open(ruta_scripts, encoding="utf-8") as f:
                scripts = etiquetas_de(f.read())
        # Puertas
        for i, wp in enumerate(m.get("warp_events") or []):
            destino = por_id.get(wp["dest_map"])
            punto = {"m": carpeta, "x": wp["x"], "y": wp["y"], "t": "puerta"}
            if wp["dest_map"] == "MAP_DYNAMIC":
                punto["a"] = "__volver"
            elif destino:
                dw = mapas[destino].get("warp_events") or []
                k = int(wp["dest_warp_id"]) if str(wp["dest_warp_id"]).isdigit() else 0
                d = dw[k] if k < len(dw) else {"x": 0, "y": 0}
                punto.update(a=destino, ax=d["x"], ay=d["y"])
            else:
                continue
            puntos.append(punto)
        # Personajes: entrenadores, objetos y POKéMON fuertes
        for o in m.get("object_events") or []:
            if "x" not in o:
                continue
            gfx, flag, script = o.get("graphics_id", ""), str(o.get("flag", "")), o.get("script", "")
            base = {"m": carpeta, "x": o["x"], "y": o["y"]}
            if gfx == "OBJ_EVENT_GFX_ITEM_BALL":
                item = o.get("trainer_sight_or_berry_tree_id", "")
                if flag.startswith("FLAG_ITEM_MEGA_"):
                    puntos.append({**base, "t": "mega", "n": objetos.get(item, item)})
                elif flag.startswith("FLAG_ITEM_TICKET_"):
                    puntos.append({**base, "t": "ticket", "n": "Ticket-Recuerdo"})
                else:
                    puntos.append({**base, "t": "objeto", "n": "MT al azar" if item.startswith("ITEM_TM") else "Objeto al azar"})
                continue
            cuerpo = scripts.get(script, "")
            tb = re.search(r"trainerbattle\w*\s+(TRAINER_\w+)", cuerpo)
            if tb and tb.group(1) in trainers:
                clase, nombre, nivel, doble = trainers[tb.group(1)]
                puntos.append({**base, "t": "entrenador", "n": f"{clase} {nombre}".strip(),
                               "d": f"Nv. {nivel}" + (" · combate doble" if doble else "")})
                continue
            sw = re.search(r"setwildbattle\s+(SPECIES_\w+),\s*(\d+)", cuerpo)
            if sw:
                guardian = "GUARDIAN" in flag
                isla = "Dualocke_EventScript_ResultadoIsla" in cuerpo or guardian
                puntos.append({**base, "t": "fuerte", "n": "Guardián" if isla else "POKéMON estático",
                               "d": f"Nv. {sw.group(2)}. Se puede capturar" + (" y deja premio" if isla else "")
                                    + ". La especie sale al azar con la semilla."})
                especies_fuertes += 1
        for b in m.get("bg_events") or []:
            if b.get("type") == "hidden_item":
                flag, item = b.get("flag", ""), b.get("item", "")
                base = {"m": carpeta, "x": b["x"], "y": b["y"], "o": 1}
                if flag.startswith("FLAG_ITEM_MEGA_"):
                    puntos.append({**base, "t": "mega", "n": objetos.get(item, item)})
                elif flag.startswith("FLAG_ITEM_TICKET_"):
                    puntos.append({**base, "t": "ticket", "n": "Ticket-Recuerdo"})
                else:
                    puntos.append({**base, "t": "objeto", "n": "Objeto oculto al azar"})

    # --- zonas de captura (las que tienen salvajes)
    wild = leer_json("src/data/wild_encounters.json")
    con_salvajes = set()
    for g in wild["wild_encounter_groups"]:
        for e in g.get("encounters", []):
            c = por_id.get(e.get("map"))
            if c and any(k.endswith("_mons") for k in e):
                con_salvajes.add(mapas[c].get("region_map_section"))
    con_salvajes.discard(None)

    # --- zonas nuevas, con el texto de las tarjetas de la guía
    tarjetas = texto_guia()
    nuevas = {}
    for sufijo in NUEVAS:
        sec = "MAPSEC_" + sufijo
        if sec not in secciones:
            continue
        nombre = nombre_sec(sec)
        tarjeta = next((t for t in tarjetas if nombre in t[0].upper()), None) \
            or next((t for t in tarjetas if any(nombre in f for f in t[1])), None)
        nuevas[sec] = " ".join(tarjeta[1]) if tarjeta else ""

    # --- sitios sueltos (a los que no se entra por una puerta del mundo): en su sitio del mapa de la región
    pts_x, pts_y = [], []
    for c, (x, y, nivel) in mundo.items():
        s = secciones.get(mapas[c].get("region_map_section"))
        if nivel == 0 and s and "x" in s and s.get("width", 1) == 1 and s.get("height", 1) == 1:
            pts_x.append((s["x"], x + info[c]["w"] / 2))
            pts_y.append((s["y"], y + info[c]["h"] / 2))
    ax, bx = np.polyfit([p[0] for p in pts_x], [p[1] for p in pts_x], 1)
    ay, by = np.polyfit([p[0] for p in pts_y], [p[1] for p in pts_y], 1)
    # Qué se alcanza andando desde el mundo (puertas y buceo). Lo que no, sale suelto (barco, teleférico…)
    vecinos = {c: set() for c in mapas}
    for p in puntos:
        if p["t"] == "puerta" and p.get("a") in mapas:
            vecinos[p["m"]].add(p["a"])
    for c, m in mapas.items():
        for con in m.get("connections") or []:
            if por_id.get(con["map"]):
                vecinos[c].add(por_id[con["map"]])
    alcanzables = set()

    def recorrer(desde):
        cola = deque(d for d in desde if d not in alcanzables)
        alcanzables.update(cola)
        while cola:
            c = cola.popleft()
            for d in vecinos[c]:
                if d not in alcanzables:
                    alcanzables.add(d)
                    cola.append(d)

    recorrer(mundo)
    sueltos = []
    candidatos = sorted((c for c, i in info.items() if c not in mundo and i["grupo"] == i["sec"]),
                        key=lambda c: (mapas[c].get("map_type") not in exteriores, c))
    for carpeta in candidatos:
        g = info[carpeta]["grupo"]
        s = secciones.get(g)
        if s and "x" not in s:
            s = SIN_SITIO.get(g)
        if any(c in alcanzables for c in grupos[g]) or not s:
            continue
        principal = min(grupos[g], key=lambda c: (not re.search(r"Harbor|Exterior|Entrance", c),
                                                  mapas[c].get("map_type") not in exteriores, grupos[g].index(c)))
        sueltos.append({"g": g, "a": principal, "x": round(ax * (s["x"] + 0.5) + bx, 1),
                        "y": round(ay * (s["y"] + 0.5) + by, 1)})
        recorrer(grupos[g])

    # --- imágenes
    dib = Dibujante()
    imagenes = {}
    for carpeta, m in mapas.items():
        imagenes[carpeta] = png_base64(dib.dibujar(layouts[m["layout"]]))

    datos = {
        "mapas": {c: {**i, **({"mundo": list(mundo[c])} if c in mundo else {})} for c, i in info.items()},
        "grupos": grupos,
        "puntos": puntos,
        "sueltos": sueltos,
        "nombresSec": {sec: nombre_sec(sec) for sec in sorted({i["sec"] for i in info.values()}) if sec},
        "captura": sorted(con_salvajes, key=lambda s: (nombre_sec(s), s)),
        "nuevas": nuevas,
        "tamMundo": [max(v[0] + info[c]["w"] for c, v in mundo.items()), max(v[1] + info[c]["h"] for c, v in mundo.items())],
    }
    with open(PLANTILLA, encoding="utf-8") as f:
        pagina = f.read()
    with open("tools/dualocke/mapa/leaflet.js", encoding="utf-8") as f:
        leaflet_js = f.read()
    with open("tools/dualocke/mapa/leaflet.css", encoding="utf-8") as f:
        leaflet_css = f.read()
    seguro = (lambda s: s.replace("</", "<\\/"))
    pagina = (pagina.replace("/*LEAFLET_CSS*/", leaflet_css)
              .replace("/*LEAFLET_JS*/", seguro(leaflet_js))
              .replace("/*DATOS*/", seguro(json.dumps(datos, ensure_ascii=False, separators=(",", ":"))))
              .replace("/*IMAGENES*/", json.dumps(imagenes, separators=(",", ":"))))
    with open(SALIDA, "w", encoding="utf-8", newline="\n") as f:
        f.write(pagina)
    cuenta = {}
    for p in puntos:
        cuenta[p["t"]] = cuenta.get(p["t"], 0) + 1
    print(f"{SALIDA}: {len(mapas)} mapas ({sum(1 for v in mundo.values() if v[2] == 0)} en el mundo, "
          f"{sum(1 for v in mundo.values() if v[2] < 0)} bajo el agua), {len(sueltos)} sitios sueltos, "
          f"{len(con_salvajes)} zonas de captura, {len(nuevas)} zonas nuevas, puntos {cuenta}, "
          f"{os.path.getsize(SALIDA) / 1e6:.1f} MB")


if __name__ == "__main__":
    main()
