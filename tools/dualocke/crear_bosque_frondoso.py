#!/usr/bin/env python3
"""
Dualocke: el BOSQUE FRONDOSO y la MANSIÓN OLVIDADA, al norte del BOSQUE PETALIA (ZONAS.md; idea de
Miguel: "un bosque más frondoso con una mansión abandonada").

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_bosque_frondoso.py

- **La entrada:** en el claro del noreste del BOSQUE PETALIA se abre un pasillo entre los árboles
  (x 34-35), tapado por dos árboles de CORTE. Lleva al BOSQUE FRONDOSO por el borde (conexión, sin
  pantalla de carga). Hace falta CORTE: **tramo 2**.
- **BOSQUE FRONDOSO** (36 × 40, gráficos del BOSQUE PETALIA): se dibuja sobre una rejilla de parejas de
  casillas (los árboles miden 2 de ancho) y `arboles()` pone cada pieza del árbol (copa, tronco, base y
  bordes) igual que en el bosque. Tiene hierba alta, flores, una charca para pescar y, arriba, la mansión:
  el edificio largo de CIUDAD FÉRRICA con su verja y su patio.
- **MANSIÓN OLVIDADA:** las cuatro salas del BARCO ABANDONADO (1F), que con la madera y las camas parecen
  una casa vieja. Se quitan los salvavidas, se abre un paso a la sala de arriba a la izquierda, su puerta
  queda atascada (cartel) y la de la derecha sube al DESVÁN. El suelo de este barco tiene salvajes.
- **DESVÁN:** dos salas de la planta oculta del barco, unidas. Arriba espera el guardián.
- **Zonas de captura propias:** MAPSEC_BOSQUE_FRONDOSO y MAPSEC_MANSION_OLVIDADA (las dos plantas).
- Los mapas van al final de `gMapGroup_Dungeons` y de `layouts.json`; sus scripts.inc, en
  data/event_scripts.s (lo comprueba comprobar_zonas.py).
- Este script escribe los personajes, las puertas, los carteles y los textos. Los salvajes y los
  entrenadores los pone zonas_nuevas.py; los objetos, colocar_objetos.py (este script los conserva).
"""

import json
import re
import os
import struct
import sys

sys.path.insert(0, "tools/dualocke")
import colocar_objetos as co  # noqa: E402

BOSQUE, MANSION, DESVAN = "BosqueFrondoso", "MansionOlvidada", "MansionOlvidada_Desvan"
MAPAS = {BOSQUE: "MAP_BOSQUE_FRONDOSO", MANSION: "MAP_MANSION_OLVIDADA", DESVAN: "MAP_MANSION_OLVIDADA_DESVAN"}
COLISION = 1 << 10

# --- BOSQUE FRONDOSO ---------------------------------------------------------------------------
# Una letra = dos casillas. T árbol, . hierba, , hierba alta, * flores, W charca, M mansión.
# Las filas de árboles entre dos claros tienen que ser impares (copa, cuerpo, [tronco, cuerpo]…, base);
# las que tocan abajo, también (acaban en tronco, como la fila de arriba del BOSQUE PETALIA).
REJILLA = """
TTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTT
TTT,,,,.....,,,TTT
TT,,,MMMMMMM,,,,TT
TT,,.MMMMMMM.,,,TT
TT,,.MMMMMMM..,,TT
TT,..MMMMMMM...,TT
TT,..MMMMMMM...,TT
TT,,.MMMMMMM..,,TT
TT,,.MMMMMMM.,,,TT
TT,,.MMMMMMM.,,,TT
TT,,,MMMMMMM,,,,TT
TT,,,,,,..,,,,,,TT
TTTTTTTT..TTTTTTTT
TTTTTTTT..TTTTTTTT
TTTTTTTT..TTTTTTTT
TT,,,,,,..,,,,*,TT
TT,,,,,,..,,,,,,TT
TT,,TTTT..TTTT..TT
TT,,TTTT..TTTT..TT
TT,,TTTT..TTTT..TT
TT..........,,..TT
TT......*...,,..TT
TTTTTT..TTTT,,TTTT
TTTTTT..TTTT,,TTTT
TTTTTT..TTTT,,TTTT
TT,WWW,.TT,,,,,,TT
TT,WWW,.TT,,TT,,TT
TT,WWW,.TT,,TT,,TT
TT,WWW,.TT,,TT,,TT
TT,WWW,.TT,,..,,TT
TT,,,,..TT,,..,,TT
TT,,,,........,,TT
TT*,,,........,,TT
TT,,,,........,,TT
TTTTTT........,,TT
TTTTTT........,,TT
TTTTTTTT..TTTTTTTT
TTTTTTTT..TTTTTTTT
TTTTTTTT..TTTTTTTT
"""
ANCHO_B, ALTO_B = 36, 40
# Piezas de árbol (gráficos generales, las mismas del BOSQUE PETALIA): (izquierda, derecha)
COPA, CUERPO, TRONCO, BASE = (0x1C6, 0x1C7), (0x1D4, 0x1D5), (0x1DC, 0x1DD), (0x1E4, 0x1E5)
CUERPO_BORDE, BASE_BORDE = (0x1D6, 0x1D7), (0x1E6, 0x1E7)
HIERBA, HIERBA_ALTA, FLORES = 0x001, 0x00D, 0x004
# Charca (gráficos generales, como las de la RUTA 102): borde de arriba, lados, agua y orilla de abajo
CHARCA_ARRIBA, CHARCA_IZQ, AGUA, CHARCA_DER, ORILLA = (0x0B0, 0x0B1, 0x0B2), 0x0B8, 0x0A1, 0x0BA, 0x002
# La mansión: el edificio largo de CIUDAD FÉRRICA con la verja, el patio y dos farolas (x0, y0, x1, y1)
MANSION_FERRICA = (6, 23, 20, 32)
SITIO_MANSION = (10, 3)                     # dónde va en el bosque (casilla de arriba a la izquierda)
PUERTA_MANSION = (13 - 6 + 10, 30 - 23 + 3)  # la puerta del edificio en FÉRRICA era (13, 30)
CARTEL_MANSION = (20, 12)                    # cartel delante del patio
# Conexión con el BOSQUE PETALIA: el pasillo del bosque (x 16-17) cae sobre el del BOSQUE PETALIA (x 34-35)
PASILLO_BOSQUE, PASILLO_PETALIA = 16, 34
DESPLAZAMIENTO = PASILLO_PETALIA - PASILLO_BOSQUE

# --- MANSIÓN (las salas de AbandonedShip_Rooms_1F) ---------------------------------------------
# Cambios: (x, y, metatile). Los salvavidas se tapan con la cabecera de cama sin salvavidas (como la de
# la sala de arriba a la derecha y la del S.S. TIDAL) y pared lisa.
PARED_ARRIBA, PARED_ABAJO, SUELO, SUELO_SOMBRA, SUELO_ESQUINA = 0x227, 0x22F, 0x238, 0x23D, 0x23C
CAMBIOS_MANSION = [
    (2, 9, 0x26B), (3, 9, PARED_ARRIBA), (2, 10, 0x273), (3, 10, PARED_ABAJO),          # salvavidas 1
    (14, 9, PARED_ARRIBA), (15, 9, 0x26D), (16, 9, 0x245),                                # salvavidas 2
    (14, 10, PARED_ABAJO), (15, 10, 0x275), (16, 10, 0x24D),
    (13, 16, SUELO), (14, 16, SUELO),                                                      # una sola salida
    (5, 7, SUELO), (5, 8, SUELO_SOMBRA), (5, 9, SUELO_SOMBRA), (5, 10, SUELO_SOMBRA),       # paso nuevo
    (5, 11, SUELO_ESQUINA),
]
PUERTA_ATASCADA, PUERTA_DESVAN, ENTRADA_MANSION = (4, 1), (13, 1), (4, 16)
# --- DESVÁN (dos salas de AbandonedShip_HiddenFloorRooms, unidas por un paso) -------------------
DESVAN_RECORTE = (14, 0, 44, 8)
PUERTA_DESVAN_ARRIBA = (36 - 14, 1)
GUARDIAN = (7, 2)                         # delante de la puerta rota
FLAG_GUARDIAN, LOCALID_GUARDIAN = "FLAG_DUALOCKE_GUARDIAN_MANSION", "LOCALID_MANSION_OLVIDADA_GUARDIAN"
ESPECIE_GUARDIAN, NIVEL_GUARDIAN, PREMIO_GUARDIAN = "SPECIES_GENGAR", 20, "ITEM_SPELL_TAG"


def leer(ruta):
    with open(ruta, encoding="utf-8", newline="") as f:
        return f.read()


def escribir(ruta, texto):
    with open(ruta, "w", encoding="utf-8", newline="") as f:
        f.write(texto)

def con_nivel_actual(ruta, texto):
    """Conserva el nivel del guardián que haya puesto reescalar_niveles.py (regla "tope") si el script ya
    existe: si no, al volver a lanzar este script después de la cadena de niveles se perdería."""
    if os.path.exists(ruta):
        anterior = re.search(r"setwildbattle (SPECIES_\w+), (\d+)", leer(ruta))
        if anterior:
            texto = re.sub(rf"setwildbattle {anterior.group(1)}, \d+", f"setwildbattle {anterior.group(1)}, {anterior.group(2)}", texto)
    return texto



LAYOUTS = co.cargar_layouts()


def celdas_de(carpeta):
    l = LAYOUTS[json.loads(leer(f"data/maps/{carpeta}/map.json"))["layout"]]
    return l, list(struct.unpack(f"<{l['width'] * l['height']}H", open(l["blockdata_filepath"], "rb").read()))


def valores(carpeta):
    """{metatile: valor completo (con colisión y altura)} tal como aparece en un mapa."""
    _, celdas = celdas_de(carpeta)
    v = {}
    for c in celdas:
        v.setdefault(c & 0x3FF, c)
    return v


def guardar_layout(carpeta, ancho, alto, celdas, base):
    os.makedirs(f"data/layouts/{carpeta}", exist_ok=True)
    with open(f"data/layouts/{carpeta}/map.bin", "wb") as f:
        f.write(struct.pack(f"<{ancho * alto}H", *celdas))
    with open(base["border_filepath"], "rb") as f, open(f"data/layouts/{carpeta}/border.bin", "wb") as g:
        g.write(f.read())
    ident = "LAYOUT_" + MAPAS[carpeta][4:]
    texto = leer("data/layouts/layouts.json")
    if f'"{ident}"' not in texto:
        texto = co.insertar_en_lista(texto, "layouts", {
            "id": ident, "name": f"{carpeta}_Layout", "width": ancho, "height": alto,
            "primary_tileset": base["primary_tileset"], "secondary_tileset": base["secondary_tileset"],
            "border_filepath": f"data/layouts/{carpeta}/border.bin",
            "blockdata_filepath": f"data/layouts/{carpeta}/map.bin"})
        json.loads(texto)
        escribir("data/layouts/layouts.json", texto)
    return ident


def arboles(rejilla, ancho, alto):
    """Devuelve {(x, y): metatile} con las piezas de los árboles de la rejilla de parejas."""
    filas = [f for f in rejilla.strip().splitlines()]
    assert len(filas) == alto and all(len(f) * 2 == ancho for f in filas), "la rejilla no mide lo que debe"
    es_arbol = lambda p, y: 0 <= p < ancho // 2 and 0 <= y < alto and filas[y][p] == "T"  # noqa: E731
    piezas, fallos = {}, []
    for p in range(ancho // 2):
        y = 0
        while y < alto:
            if not es_arbol(p, y):
                y += 1
                continue
            y0 = y
            while y < alto and es_arbol(p, y):
                y += 1
            y1 = y - 1
            arriba, abajo = y0 > 0, y1 < alto - 1   # True si hay claro (no borde del mapa)
            largo = y1 - y0 + 1
            if arriba and abajo:
                ok = largo >= 3 and largo % 2 == 1
                fila_de = lambda yy: "copa" if yy == y0 else "base" if yy == y1 else (  # noqa: E731
                    "cuerpo" if (yy - y0) % 2 == 1 else "tronco")
            elif arriba:      # toca abajo: copa, cuerpo, tronco, cuerpo… y tronco en la última
                ok = largo >= 3 and largo % 2 == 1
                fila_de = lambda yy: "copa" if yy == y0 else ("cuerpo" if (yy - y0) % 2 == 1 else "tronco")  # noqa: E731
            elif abajo:       # toca arriba: …tronco, cuerpo y base
                ok = largo >= 2
                fila_de = lambda yy: "base" if yy == y1 else ("cuerpo" if (y1 - yy) % 2 == 1 else "tronco")  # noqa: E731
            else:
                ok = True
                fila_de = lambda yy: "cuerpo" if yy % 2 == 0 else "tronco"  # noqa: E731
            if not ok:
                fallos.append(f"columna {p} (x {2 * p}-{2 * p + 1}), filas {y0}-{y1}")
            for yy in range(y0, y1 + 1):
                tipo = fila_de(yy)
                izq, der = {"copa": COPA, "cuerpo": CUERPO, "tronco": TRONCO, "base": BASE}[tipo]
                if tipo == "cuerpo":
                    izq = CUERPO_BORDE[0] if not es_arbol(p - 1, yy) and p > 0 else izq
                    der = CUERPO_BORDE[1] if not es_arbol(p + 1, yy) and p < ancho // 2 - 1 else der
                if tipo == "base":
                    izq = BASE_BORDE[0] if not es_arbol(p - 1, yy) and p > 0 else izq
                    der = BASE_BORDE[1] if not es_arbol(p + 1, yy) and p < ancho // 2 - 1 else der
                piezas[(2 * p, yy)], piezas[(2 * p + 1, yy)] = izq, der
    assert not fallos, "filas de árboles de largo imposible: " + "; ".join(fallos)
    return piezas, filas


def crear_bosque():
    base, petalia = celdas_de("PetalburgWoods")
    v = valores("PetalburgWoods")
    v.update({k: x for k, x in valores("Route102").items() if k < 0x200 and k not in v})
    piezas, filas = arboles(REJILLA, ANCHO_B, ALTO_B)
    c = [0] * (ANCHO_B * ALTO_B)
    for y in range(ALTO_B):
        for x in range(ANCHO_B):
            letra = filas[y][x // 2]
            if letra == "T":
                c[y * ANCHO_B + x] = v[piezas[(x, y)]]
            else:
                c[y * ANCHO_B + x] = v[{",": HIERBA_ALTA, "*": FLORES}.get(letra, HIERBA)]
    # La charca: el rectángulo de las W
    ws = [(x, y) for y in range(ALTO_B) for x in range(ANCHO_B) if filas[y][x // 2] == "W"]
    x0, x1 = min(x for x, _ in ws), max(x for x, _ in ws)
    y0, y1 = min(y for _, y in ws), max(y for _, y in ws)
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            if y == y1:
                m = ORILLA
            elif y == y0:
                m = CHARCA_ARRIBA[0] if x == x0 else CHARCA_ARRIBA[2] if x == x1 else CHARCA_ARRIBA[1]
            else:
                m = CHARCA_IZQ if x == x0 else CHARCA_DER if x == x1 else AGUA
            c[y * ANCHO_B + x] = v[m]
    # La mansión, copiada de CIUDAD FÉRRICA
    lf, cf = celdas_de("RustboroCity")
    mx0, my0, mx1, my1 = MANSION_FERRICA
    for y in range(my0, my1):
        for x in range(mx0, mx1):
            c[(SITIO_MANSION[1] + y - my0) * ANCHO_B + SITIO_MANSION[0] + x - mx0] = cf[y * lf["width"] + x]
    ms = [(x, y) for y in range(ALTO_B) for x in range(ANCHO_B) if filas[y][x // 2] == "M"]
    assert (min(ms), max(ms)) == (SITIO_MANSION, (SITIO_MANSION[0] + mx1 - mx0 - 1, SITIO_MANSION[1] + my1 - my0 - 1)), \
        "las M de la rejilla no coinciden con la mansión"
    # El cartel de la mansión: el cartel de madera de FÉRRICA
    cartel = next(cf[b["y"] * lf["width"] + b["x"]] for b in json.loads(leer("data/maps/RustboroCity/map.json"))["bg_events"]
                  if b["type"] == "sign" and b["script"] == "RustboroCity_EventScript_CitySign")
    c[CARTEL_MANSION[1] * ANCHO_B + CARTEL_MANSION[0]] = cartel
    assert all(x for x in c), "casillas sin dibujar"
    return guardar_layout(BOSQUE, ANCHO_B, ALTO_B, c, base)


def crear_mansion():
    base, c = celdas_de("AbandonedShip_Rooms_1F")
    v = valores("AbandonedShip_Rooms_1F")
    v.update({k: x for k, x in valores("SSTidalRooms").items() if k not in v})
    w = base["width"]
    for x, y, m in CAMBIOS_MANSION:
        c[y * w + x] = v[m]
    return guardar_layout(MANSION, w, base["height"], c, base)


def crear_desvan():
    base, c = celdas_de("AbandonedShip_HiddenFloorRooms")
    x0, y0, x1, y1 = DESVAN_RECORTE
    nuevas = [c[y * base["width"] + x] for y in range(y0, y1) for x in range(x0, x1)]
    gx, gy = GUARDIAN
    assert (nuevas[gy * (x1 - x0) + gx] >> 10) & 3 == 0, "el guardián no está en el suelo"
    # La puerta rota de detrás del guardián era una puerta del barco: aquí no lleva a ningún sitio
    for y in range(gy):
        nuevas[y * (x1 - x0) + gx] |= COLISION
    # Delante del guardián había una papelera que no dejaba llegar a él: suelo como el de debajo
    nuevas[(gy + 1) * (x1 - x0) + gx] = nuevas[(gy + 2) * (x1 - x0) + gx]
    return guardar_layout(DESVAN, x1 - x0, y1 - y0, nuevas, base)


def mapa_json(carpeta, datos, objetos, carteles):
    """Escribe el map.json con los personajes y carteles de este script; conserva los objetos que pone
    colocar_objetos.py (los de los flags FLAG_ITEM_…)."""
    ruta = f"data/maps/{carpeta}/map.json"
    os.makedirs(f"data/maps/{carpeta}", exist_ok=True)
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    datos["object_events"] = objetos + [o for o in anteriores.get("object_events", [])
                                        if str(o.get("flag", "")).startswith("FLAG_ITEM_")]
    datos["bg_events"] = carteles + [b for b in anteriores.get("bg_events", []) if b.get("type") == "hidden_item"]
    escribir(ruta, json.dumps(datos, indent=2, ensure_ascii=False) + "\n")


def entrenador(gfx, x, y, mira, vista, script):
    return {"graphics_id": gfx, "x": x, "y": y, "elevation": 3, "movement_type": f"MOVEMENT_TYPE_FACE_{mira}",
            "movement_range_x": 0, "movement_range_y": 0, "trainer_type": "TRAINER_TYPE_NORMAL",
            "trainer_sight_or_berry_tree_id": str(vista), "script": script, "flag": "0"}


def cartel(x, y, script, elevacion=0):
    return {"type": "sign", "x": x, "y": y, "elevation": elevacion,
            "player_facing_dir": "BG_EVENT_PLAYER_FACING_NORTH", "script": script}


def crear_mapas(l_bosque, l_mansion, l_desvan):
    comun = {"region": "REGION_HOENN", "requires_flash": False, "allow_running": True, "show_map_name": True,
             "battle_scene": "MAP_BATTLE_SCENE_NORMAL", "coord_events": []}
    mapa_json(BOSQUE, {
        "id": MAPAS[BOSQUE], "name": BOSQUE, "layout": l_bosque, "music": "MUS_PETALBURG_WOODS",
        "region_map_section": "MAPSEC_BOSQUE_FRONDOSO", "weather": "WEATHER_SHADE", "map_type": "MAP_TYPE_ROUTE",
        "allow_cycling": True, "allow_escaping": False, **comun,
        "connections": [{"map": "MAP_PETALBURG_WOODS", "offset": -DESPLAZAMIENTO, "direction": "down"}],
        "warp_events": [{"x": PUERTA_MANSION[0], "y": PUERTA_MANSION[1], "elevation": 0,
                         "dest_map": MAPAS[MANSION], "dest_warp_id": "0"}]},
        [entrenador("OBJ_EVENT_GFX_BUG_CATCHER", 11, 21, "RIGHT", 4, "BosqueFrondoso_EventScript_Sebas"),
         entrenador("OBJ_EVENT_GFX_PICNICKER", 15, 30, "LEFT", 3, "BosqueFrondoso_EventScript_Olivia")],
        [cartel(*CARTEL_MANSION, "BosqueFrondoso_EventScript_CartelMansion")])
    ex, ey = ENTRADA_MANSION
    mapa_json(MANSION, {
        "id": MAPAS[MANSION], "name": MANSION, "layout": l_mansion, "music": "MUS_ABANDONED_SHIP",
        "region_map_section": "MAPSEC_MANSION_OLVIDADA", "weather": "WEATHER_NONE",
        "map_type": "MAP_TYPE_UNDERGROUND", "allow_cycling": False, "allow_escaping": True, **comun,
        "connections": None,
        "warp_events": [{"x": ex, "y": ey, "elevation": 3, "dest_map": MAPAS[BOSQUE], "dest_warp_id": "0"},
                        {"x": ex + 1, "y": ey, "elevation": 3, "dest_map": MAPAS[BOSQUE], "dest_warp_id": "0"},
                        {"x": PUERTA_DESVAN[0], "y": PUERTA_DESVAN[1], "elevation": 3,
                         "dest_map": MAPAS[DESVAN], "dest_warp_id": "0"}]},
        [entrenador("OBJ_EVENT_GFX_HEX_MANIAC", 13, 13, "LEFT", 3, "MansionOlvidada_EventScript_Elvira"),
         entrenador("OBJ_EVENT_GFX_GENTLEMAN", 2, 5, "RIGHT", 3, "MansionOlvidada_EventScript_Alfonso")],
        [cartel(*PUERTA_ATASCADA, "MansionOlvidada_EventScript_PuertaAtascada", 3)])
    gx, gy = GUARDIAN
    mapa_json(DESVAN, {
        "id": MAPAS[DESVAN], "name": DESVAN, "layout": l_desvan, "music": "MUS_ABANDONED_SHIP",
        "region_map_section": "MAPSEC_MANSION_OLVIDADA", "weather": "WEATHER_NONE",
        "map_type": "MAP_TYPE_UNDERGROUND", "allow_cycling": False, "allow_escaping": True, **comun,
        "connections": None,
        "warp_events": [{"x": PUERTA_DESVAN_ARRIBA[0], "y": PUERTA_DESVAN_ARRIBA[1], "elevation": 3,
                         "dest_map": MAPAS[MANSION], "dest_warp_id": "2"}]},
        [{"local_id": LOCALID_GUARDIAN, "graphics_id": "OBJ_EVENT_GFX_VAR_0", "x": gx, "y": gy, "elevation": 3,
          "movement_type": "MOVEMENT_TYPE_FACE_DOWN", "movement_range_x": 0, "movement_range_y": 0,
          "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
          "script": f"{DESVAN}_EventScript_Pokemon", "flag": FLAG_GUARDIAN}],
        [])
    for carpeta in (BOSQUE, MANSION, DESVAN):
        escribir(f"data/maps/{carpeta}/scripts.inc", con_nivel_actual(f"data/maps/{carpeta}/scripts.inc", SCRIPTS[carpeta]))

    grupos = leer("data/maps/map_groups.json")
    salto = "\r\n" if "\r\n" in grupos else "\n"
    for carpeta in (BOSQUE, MANSION, DESVAN):
        if f'"{carpeta}"' in grupos:
            continue
        d = json.loads(grupos)
        ultimo = d["gMapGroup_Dungeons"][-1]
        a = f'"{ultimo}"{salto}'
        i = grupos.index(a, grupos.index('"gMapGroup_Dungeons": ['))
        grupos = grupos[:i] + f'"{ultimo}",{salto}    "{carpeta}"{salto}' + grupos[i + len(a):]
    json.loads(grupos)
    escribir("data/maps/map_groups.json", grupos)


def entrada_petalia():
    """Abre el pasillo del BOSQUE PETALIA (x 34-35, filas 0-3), le pone dos árboles de CORTE y la conexión."""
    base, c = celdas_de("PetalburgWoods")
    w = base["width"]
    v = valores("PetalburgWoods")
    px = PASILLO_PETALIA
    hierba = c[4 * w + px]
    assert hierba & 0x3FF == HIERBA, "debajo del pasillo no hay hierba"
    for y in range(4):
        c[y * w + px] = c[y * w + px + 1] = hierba
    # Los árboles de los lados, con su borde (como en el resto del bosque)
    for y, (izq, der) in ((0, CUERPO_BORDE), (2, CUERPO_BORDE), (3, BASE_BORDE)):
        c[y * w + px - 1], c[y * w + px + 2] = v[der], v[izq]
    with open(base["blockdata_filepath"], "wb") as f:
        f.write(struct.pack(f"<{w * base['height']}H", *c))

    ruta = "data/maps/PetalburgWoods/map.json"
    texto = leer(ruta)
    if MAPAS[BOSQUE] not in texto:
        conexion = json.dumps([{"map": MAPAS[BOSQUE], "offset": DESPLAZAMIENTO, "direction": "up"}])
        assert texto.count('"connections": null') == 1
        texto = texto.replace('"connections": null', f'"connections": {conexion}')
        for x, flag in ((px, "FLAG_TEMP_13"), (px + 1, "FLAG_TEMP_14")):
            texto = co.insertar_en_lista(texto, "object_events", {
                "graphics_id": "OBJ_EVENT_GFX_CUTTABLE_TREE", "x": x, "y": 2, "elevation": 3,
                "movement_type": "MOVEMENT_TYPE_LOOK_AROUND", "movement_range_x": 0, "movement_range_y": 0,
                "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
                "script": "EventScript_CutTree", "flag": flag})
        json.loads(texto)
        escribir(ruta, texto)


def zonas_region():
    ruta = "src/data/region_map/region_map_sections.json"
    texto = leer(ruta)
    bosque = next(s for s in json.loads(texto)["map_sections"] if s["id"] == "MAPSEC_PETALBURG_WOODS")
    for mapsec, nombre in (("MAPSEC_BOSQUE_FRONDOSO", "BOSQUE FRONDOSO"), ("MAPSEC_MANSION_OLVIDADA", "MANSIÓN OLVIDADA")):
        assert len(nombre) <= 16, nombre
        if f'"{mapsec}"' not in texto:
            texto = co.insertar_en_lista(texto, "map_sections", {"id": mapsec, "name": nombre, "x": bosque["x"],
                                                                 "y": bosque["y"], "width": 1, "height": 1})
    json.loads(texto)
    escribir(ruta, texto)


SCRIPTS = {
    BOSQUE: """BosqueFrondoso_MapScripts::
	.byte 0

@ Dualocke: el BOSQUE FRONDOSO, al norte del BOSQUE PETALIA (tools/dualocke/crear_bosque_frondoso.py)
BosqueFrondoso_EventScript_CartelMansion::
	msgbox BosqueFrondoso_Text_CartelMansion, MSGBOX_SIGN
	end

BosqueFrondoso_EventScript_Sebas::
	trainerbattle_single TRAINER_SEBAS, BosqueFrondoso_Text_SebasIntro, BosqueFrondoso_Text_SebasDefeat
	msgbox BosqueFrondoso_Text_SebasPostBattle, MSGBOX_AUTOCLOSE
	end

@ OLIVIA es TRAINER_BRENDAN_PLACEHOLDER, que existía sin usar (zonas_nuevas.py le pone nombre y equipo)
BosqueFrondoso_EventScript_Olivia::
	trainerbattle_single TRAINER_BRENDAN_PLACEHOLDER, BosqueFrondoso_Text_OliviaIntro, BosqueFrondoso_Text_OliviaDefeat
	msgbox BosqueFrondoso_Text_OliviaPostBattle, MSGBOX_AUTOCLOSE
	end

BosqueFrondoso_Text_CartelMansion:
	.string "MANSIÓN OLVIDADA\\n"
	.string "Nadie vive aquí desde hace años.$"

BosqueFrondoso_Text_SebasIntro:
	.string "¡En este bosque hay bichos que\\n"
	.string "no salen en el BOSQUE PETALIA!$"

BosqueFrondoso_Text_SebasDefeat:
	.string "¡Mis bichos se han escondido!$"

BosqueFrondoso_Text_SebasPostBattle:
	.string "Dicen que en la mansión hay\\n"
	.string "fantasmas. Yo no entro…$"

BosqueFrondoso_Text_OliviaIntro:
	.string "¡Qué sitio tan bonito para\\n"
	.string "un combate!$"

BosqueFrondoso_Text_OliviaDefeat:
	.string "Me lo he pasado bien igual.$"

BosqueFrondoso_Text_OliviaPostBattle:
	.string "Con una caña se puede pescar\\n"
	.string "en la charca. ¡Pruébalo!$"
""",
    MANSION: """MansionOlvidada_MapScripts::
	.byte 0

@ Dualocke: la MANSIÓN OLVIDADA, en el BOSQUE FRONDOSO (tools/dualocke/crear_bosque_frondoso.py)
MansionOlvidada_EventScript_PuertaAtascada::
	msgbox MansionOlvidada_Text_PuertaAtascada, MSGBOX_SIGN
	end

@ ELVIRA es TRAINER_MAY_PLACEHOLDER y ALFONSO es TRAINER_LEAF: existían sin usar
MansionOlvidada_EventScript_Elvira::
	trainerbattle_single TRAINER_MAY_PLACEHOLDER, MansionOlvidada_Text_ElviraIntro, MansionOlvidada_Text_ElviraDefeat
	msgbox MansionOlvidada_Text_ElviraPostBattle, MSGBOX_AUTOCLOSE
	end

MansionOlvidada_EventScript_Alfonso::
	trainerbattle_single TRAINER_LEAF, MansionOlvidada_Text_AlfonsoIntro, MansionOlvidada_Text_AlfonsoDefeat
	msgbox MansionOlvidada_Text_AlfonsoPostBattle, MSGBOX_AUTOCLOSE
	end

MansionOlvidada_Text_PuertaAtascada:
	.string "La puerta está atascada.\\n"
	.string "No se abre.$"

MansionOlvidada_Text_ElviraIntro:
	.string "Los espíritus de esta casa\\n"
	.string "quieren conocerte…$"

MansionOlvidada_Text_ElviraDefeat:
	.string "Los espíritus están contentos…$"

MansionOlvidada_Text_ElviraPostBattle:
	.string "Arriba hay algo muy fuerte.\\n"
	.string "Lo noto desde aquí…$"

MansionOlvidada_Text_AlfonsoIntro:
	.string "Antes esta casa era mía.\\n"
	.string "Ahora es de los fantasmas.$"

MansionOlvidada_Text_AlfonsoDefeat:
	.string "Qué combate tan elegante.$"

MansionOlvidada_Text_AlfonsoPostBattle:
	.string "La puerta de esta sala lleva\\n"
	.string "años atascada.$"
""",
    DESVAN: f"""{DESVAN}_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, {DESVAN}_OnTransition
	.byte 0

@ Dualocke: el guardián de la MANSIÓN OLVIDADA, un Pokémon fuerte que se puede capturar, como en las
@ islas del ferry (data/scripts/dualocke_islas.inc). Con semilla sale otro de su tipo (estaticos.py, islas()).
{DESVAN}_OnTransition:
	setvar VAR_0x8004, {ESPECIE_GUARDIAN}
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

{DESVAN}_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, {ESPECIE_GUARDIAN}
	setvar VAR_TEMP_9, {PREMIO_GUARDIAN}
	call Dualocke_EventScript_AvisoIsla
	setwildbattle {ESPECIE_GUARDIAN}, {NIVEL_GUARDIAN}
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, {DESVAN}_EventScript_PokemonSigue
	setflag {FLAG_GUARDIAN}
	call Dualocke_EventScript_PremioIsla
	release
	end

{DESVAN}_EventScript_PokemonSigue::
	release
	end
""",
}


def main():
    crear_mapas(crear_bosque(), crear_mansion(), crear_desvan())
    entrada_petalia()
    zonas_region()
    print("Dualocke: BOSQUE FRONDOSO y MANSIÓN OLVIDADA creados")


if __name__ == "__main__":
    main()
