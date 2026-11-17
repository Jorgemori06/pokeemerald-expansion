#!/usr/bin/env python3
"""
Dualocke: la PLAYA VOLCÁNICA, al oeste del MONTE PÍRICO (ZONAS.md, propuesta 10; Miguel, 17/11/2026).

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_playa_volcanica.py

- **Dónde:** pegada al borde oeste de la RUTA 122 (la del MONTE PÍRICO). Se llega surfeando, sin pantalla de
  carga. **Tramo 7.** La RUTA 122 está rodeada por un anillo de rocas: se quita una roca arriba a la izquierda
  (x 5-6, filas 4-5) para poder salir por el noroeste.
- **Gráficos:** General + LAVACALDA (ceniza, aguas termales, árboles de ceniza), distintos de los de la RUTA 122
  (General + Algaria). Una conexión entre mapas de gráficos distintos solo se ve bien si lo que se ve del otro
  mapa son gráficos generales. Por eso:
  - Se cruza por arriba (filas 0-7), donde el borde de la RUTA 122 solo tiene mar y rocas generales.
  - Las 8 columnas del este de la playa son solo mar y rocas generales, y desde la fila 8 una fila de rocas
    no deja acercarse al borde (desde ahí se vería la orilla del monte, que es de Algaria).
- **La playa** (40 × 40): mar al este, una franja de arena con su orilla (gráficos generales, como en AZULIZA)
  y, al oeste, suelo de ceniza del MONTE CENIZO con manchas de ceniza con salvajes, árboles de ceniza y dos
  pozas de aguas termales de LAVACALDA. Sol (sol en combate).
- **Guardián** en la arena, y un bañista en las termas que cuenta cosas.
- **Zona de captura propia:** MAPSEC_PLAYA_VOLCANICA.
Los salvajes y los objetos los ponen zonas_nuevas.py y colocar_objetos.py.
"""

import json
import re
import os
import struct
import sys

sys.path.insert(0, "tools/dualocke")
import colocar_objetos as co  # noqa: E402

PLAYA, MAPA, MAPSEC = "PlayaVolcanica", "MAP_PLAYA_VOLCANICA", "MAPSEC_PLAYA_VOLCANICA"
ANCHO, ALTO = 40, 40
COLISION = 1 << 10
ROCA_RUTA122 = (5, 4)                     # la roca (2 × 2) que se quita del anillo de la RUTA 122
FILAS_CRUCE = 8                           # filas 0-7: por aquí se pasa de un mapa a otro
BANDA_GENERAL = 8                         # las últimas 8 columnas, solo gráficos generales
ROCA = (0x175, 0x176, 0x17D, 0x17E)      # roca de mar (general): arriba izq., arriba der., abajo izq., abajo der.
ARENA, ORILLA = 0x124, 0x125              # arena y agua con orilla de arena a su izquierda (generales)
ARENA_X = (25, 31)                        # columnas de arena (x0, x1)
SUELO, CENIZA = 0x271, 0x207              # suelo y ceniza con salvajes del MONTE CENIZO / CAMINO ESCABROSO
ARBOL = (0x2C5, 0x2CC)                    # árbol de ceniza del MONTE CENIZO (arriba, abajo)
CENIZA_ZONAS = [(1, 8, 10, 13), (13, 14, 22, 21), (4, 15, 10, 22), (3, 26, 11, 34), (15, 31, 22, 37)]
ARBOLES = [(1, 12), (11, 4), (12, 10), (23, 3), (24, 12), (1, 22), (12, 24), (22, 25), (8, 36), (23, 34),
           (5, 18)]
# La poza de LAVACALDA con su borde de piedras. Su borde de arriba está dibujado sobre el acantilado y el
# de los lados sobre arena: por eso van pegadas al borde de arriba del mapa y con arena alrededor.
TERMAS = ("LavaridgeTown", (2, 2, 8, 7))
SITIOS_TERMAS = [(4, 0), (14, 0)]
ARENA_TERMAS = 0x2A8
GUARDIAN = (28, 22, "SPECIES_GYARADOS", 70, "ITEM_MYSTIC_WATER", "FLAG_DUALOCKE_GUARDIAN_PLAYA")
BANISTA = (16, 5)                         # en la arena, debajo de la segunda poza (no se puede entrar)


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


SOLIDOS = set(ROCA) | set(ARBOL)


def valores(*carpetas):
    """{metatile: valor completo (colisión y altura)}: el más común en esos mapas con la colisión que toca.
    Ojo: el mismo metatile sale con y sin colisión (el 0x271 es suelo, pero también la cima de las rocas
    del MONTE CENIZO): las rocas y los árboles con colisión y el resto sin ella."""
    cuenta = {}
    for carpeta in carpetas:
        for c in celdas_de(carpeta)[1]:
            m = c & 0x3FF
            if bool((c >> 10) & 3) == (m in SOLIDOS):
                cuenta.setdefault(m, {})
                cuenta[m][c] = cuenta[m].get(c, 0) + 1
    return {m: max(vs, key=vs.get) for m, vs in cuenta.items()}


def crear_layout():
    v = valores("Route122", "DewfordTown", "MtChimney", "JaggedPass")
    assert all(not (v[m] >> 10) & 3 for m in (SUELO, CENIZA, ARENA, ORILLA, 0x170)), "suelo con colisión"
    mar = v[0x170]
    c = [v[SUELO]] * (ANCHO * ALTO)
    pon = lambda x, y, m: c.__setitem__(y * ANCHO + x, m)  # noqa: E731
    # Ceniza con salvajes
    for x0, y0, x1, y1 in CENIZA_ZONAS:
        for y in range(y0, y1):
            for x in range(x0, x1):
                pon(x, y, (v[SUELO] & ~0x3FF) | CENIZA)
    # Arena, orilla y mar
    for y in range(ALTO):
        for x in range(ARENA_X[0], ARENA_X[1] + 1):
            pon(x, y, v[ARENA])
        pon(ARENA_X[1] + 1, y, v[ORILLA])
        for x in range(ARENA_X[1] + 2, ANCHO):
            pon(x, y, mar)
    # Rocas que no dejan acercarse al borde este desde la fila 8
    for y in range(FILAS_CRUCE, ALTO, 2):
        for dx, dy, m in ((0, 0, ROCA[0]), (1, 0, ROCA[1]), (0, 1, ROCA[2]), (1, 1, ROCA[3])):
            if y + dy < ALTO:
                pon(ANCHO - 2 + dx, y + dy, v[m])
    # Unas rocas sueltas en el mar
    for rx, ry in ((34, 12), (35, 24), (34, 33)):
        for dx, dy, m in ((0, 0, ROCA[0]), (1, 0, ROCA[1]), (0, 1, ROCA[2]), (1, 1, ROCA[3])):
            pon(rx + dx, ry + dy, v[m])
    # Árboles de ceniza
    for x, y in ARBOLES:
        pon(x, y, v[ARBOL[0]])
        pon(x, y + 1, v[ARBOL[1]])
    # Aguas termales de LAVACALDA
    lt, ct = celdas_de(TERMAS[0])
    x0, y0, x1, y1 = TERMAS[1]
    arena = next(v for v in ct if v & 0x3FF == ARENA_TERMAS)
    for sx, sy in SITIOS_TERMAS:
        for y in range(sy, sy + y1 - y0 + 1):
            for x in range(sx - 1, sx + x1 - x0 + 1):
                pon(x, y, arena)
        for y in range(y0, y1):
            for x in range(x0, x1):
                pon(sx + x - x0, sy + y - y0, ct[y * lt["width"] + x])
    # Comprobaciones: la banda del este solo tiene gráficos generales
    assert all(c[y * ANCHO + x] & 0x3FF < 0x200 for y in range(ALTO) for x in range(ANCHO - BANDA_GENERAL, ANCHO))
    gx, gy = GUARDIAN[:2]
    assert (c[gy * ANCHO + gx] >> 10) & 3 == 0 and c[gy * ANCHO + gx] & 0x3FF == ARENA, "el guardián no está en la arena"

    base = LAYOUTS[json.loads(leer("data/maps/MtChimney/map.json"))["layout"]]
    os.makedirs(f"data/layouts/{PLAYA}", exist_ok=True)
    with open(f"data/layouts/{PLAYA}/map.bin", "wb") as f:
        f.write(struct.pack(f"<{ANCHO * ALTO}H", *c))
    with open(base["border_filepath"], "rb") as f, open(f"data/layouts/{PLAYA}/border.bin", "wb") as g:
        g.write(f.read())
    ident = "LAYOUT_" + MAPA[4:]
    texto = leer("data/layouts/layouts.json")
    if f'"{ident}"' not in texto:
        texto = co.insertar_en_lista(texto, "layouts", {
            "id": ident, "name": f"{PLAYA}_Layout", "width": ANCHO, "height": ALTO,
            "primary_tileset": "gTileset_General", "secondary_tileset": "gTileset_Lavaridge",
            "border_filepath": f"data/layouts/{PLAYA}/border.bin",
            "blockdata_filepath": f"data/layouts/{PLAYA}/map.bin"})
        json.loads(texto)
        escribir("data/layouts/layouts.json", texto)
    return ident


def ruta122():
    """Quita la roca del anillo de la RUTA 122 y la conecta con la playa."""
    l, c = celdas_de("Route122")
    w = l["width"]
    mar = c[0]
    assert mar & 0x3FF == 0x170
    rx, ry = ROCA_RUTA122
    for dy in range(2):
        for dx in range(2):
            assert c[(ry + dy) * w + rx + dx] & 0x3FF in ROCA + (0x170,), "ahí no está la roca"
            c[(ry + dy) * w + rx + dx] = mar
    # La parte de la RUTA 122 que se ve desde el cruce (filas 0-12, x 0-7) solo tiene gráficos generales
    assert all(c[y * w + x] & 0x3FF < 0x200 for y in range(FILAS_CRUCE + 5) for x in range(BANDA_GENERAL))
    with open(l["blockdata_filepath"], "wb") as f:
        f.write(struct.pack(f"<{w * l['height']}H", *c))
    ruta = "data/maps/Route122/map.json"
    texto = leer(ruta)
    if MAPA not in texto:
        texto = co.insertar_en_lista(texto, "connections", {"map": MAPA, "offset": 0, "direction": "left"})
        json.loads(texto)
        escribir(ruta, texto)


def crear_mapa(layout):
    ruta = f"data/maps/{PLAYA}/map.json"
    os.makedirs(f"data/maps/{PLAYA}", exist_ok=True)
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    gx, gy, _, _, _, flag = GUARDIAN
    objetos = [
        {"local_id": "LOCALID_PLAYA_VOLCANICA_GUARDIAN", "graphics_id": "OBJ_EVENT_GFX_VAR_0", "x": gx, "y": gy,
         "elevation": 3, "movement_type": "MOVEMENT_TYPE_FACE_LEFT", "movement_range_x": 0, "movement_range_y": 0,
         "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
         "script": f"{PLAYA}_EventScript_Pokemon", "flag": flag},
        {"graphics_id": "OBJ_EVENT_GFX_OLD_MAN_1", "x": BANISTA[0], "y": BANISTA[1], "elevation": 3,
         "movement_type": "MOVEMENT_TYPE_FACE_UP", "movement_range_x": 0, "movement_range_y": 0,
         "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
         "script": f"{PLAYA}_EventScript_Banista", "flag": "0"}]
    datos = {
        "id": MAPA, "name": PLAYA, "layout": layout, "music": "MUS_ROUTE119", "region": "REGION_HOENN",
        "region_map_section": MAPSEC, "requires_flash": False, "weather": "WEATHER_DROUGHT",
        "map_type": "MAP_TYPE_ROUTE", "allow_cycling": True, "allow_escaping": False, "allow_running": True,
        "show_map_name": True, "battle_scene": "MAP_BATTLE_SCENE_NORMAL",
        "connections": [{"map": "MAP_ROUTE122", "offset": 0, "direction": "right"}],
        "object_events": objetos + [o for o in anteriores.get("object_events", [])
                                    if str(o.get("flag", "")).startswith("FLAG_ITEM_")],
        "warp_events": [], "coord_events": [],
        "bg_events": [b for b in anteriores.get("bg_events", []) if b.get("type") == "hidden_item"],
    }
    escribir(ruta, json.dumps(datos, indent=2, ensure_ascii=False) + "\n")
    escribir(f"data/maps/{PLAYA}/scripts.inc", con_nivel_actual(f"data/maps/{PLAYA}/scripts.inc", SCRIPTS))

    grupos = leer("data/maps/map_groups.json")
    if f'"{PLAYA}"' not in grupos:
        salto = "\r\n" if "\r\n" in grupos else "\n"
        d = json.loads(grupos)
        grupo = next(g for g in d["group_order"] if "Route122" in d[g])
        ultimo = d[grupo][-1]
        a = f'"{ultimo}"{salto}'
        i = grupos.index(a, grupos.index(f'"{grupo}": ['))
        grupos = grupos[:i] + f'"{ultimo}",{salto}    "{PLAYA}"{salto}' + grupos[i + len(a):]
        json.loads(grupos)
        escribir("data/maps/map_groups.json", grupos)

    ruta = "src/data/region_map/region_map_sections.json"
    texto = leer(ruta)
    if f'"{MAPSEC}"' not in texto:
        r122 = next(s for s in json.loads(texto)["map_sections"] if s["id"] == "MAPSEC_ROUTE_122")
        texto = co.insertar_en_lista(texto, "map_sections", {"id": MAPSEC, "name": "PLAYA VOLCÁNICA",
                                                             "x": r122["x"] - 1, "y": r122["y"], "width": 1, "height": 1})
        json.loads(texto)
        escribir(ruta, texto)


_, _, ESPECIE, NIVEL, PREMIO, FLAG = GUARDIAN
SCRIPTS = f"""{PLAYA}_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, {PLAYA}_OnTransition
	.byte 0

@ Dualocke: la PLAYA VOLCÁNICA, al oeste del MONTE PÍRICO (tools/dualocke/crear_playa_volcanica.py).
@ El guardián es un Pokémon fuerte que se puede capturar, como en las islas del ferry
@ (data/scripts/dualocke_islas.inc). Con semilla sale otro de su tipo (estaticos.py, islas()).
{PLAYA}_OnTransition:
	setvar VAR_0x8004, {ESPECIE}
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

{PLAYA}_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, {ESPECIE}
	setvar VAR_TEMP_9, {PREMIO}
	call Dualocke_EventScript_AvisoIsla
	setwildbattle {ESPECIE}, {NIVEL}
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, {PLAYA}_EventScript_PokemonSigue
	setflag {FLAG}
	call Dualocke_EventScript_PremioIsla
	release
	end

{PLAYA}_EventScript_PokemonSigue::
	release
	end

{PLAYA}_EventScript_Banista::
	msgbox {PLAYA}_Text_Banista, MSGBOX_NPC
	end

{PLAYA}_Text_Banista:
	.string "Estas aguas las calienta el volcán\\n"
	.string "que hay bajo el MONTE PÍRICO.\\p"
	.string "Dicen que un POKéMON enorme sale\\n"
	.string "del mar a tomar el sol.$"
"""


def main():
    crear_mapa(crear_layout())
    ruta122()
    print("Dualocke: PLAYA VOLCÁNICA creada")


if __name__ == "__main__":
    main()
