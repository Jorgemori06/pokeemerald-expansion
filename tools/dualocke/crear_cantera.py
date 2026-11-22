#!/usr/bin/env python3
"""
Dualocke: la CANTERA, el bioma del tipo Acero (PLAN.md, propuesta B; idea de Miguel, 18/11/2026: "una Cantera
de tipo Acero en la RUTA 116, por la salida del Túnel Fervergal").

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_cantera.py

- **Entrada:** una boca de cueva nueva en la RUTA 116, en la misma pared que la salida este del TÚNEL
  FERVERGAL (la del túnel está en (65, 10); la de la cantera, en (67, 10)). Es el mismo dibujo de boca de cueva.
  A esa parte de la RUTA 116 se llega cruzando el túnel, con GOLPE ROCA: **tramo 3** (`alcance.py`), como la
  CIÉNAGA TÓXICA. No se quita ninguna base secreta.
- **La cantera** (40 × 30, gráficos de la RUTA 116): se llega por una boca de cueva en la pared de roca de
  arriba y se baja en tres terrazas separadas por riscos, cada uno con su escalera. Suelo de tierra con rocas de
  GOLPE ROCA, manchas de hierba alta (los salvajes) y árboles a los lados y abajo. En el fondo, el guardián.
- **Guardián:** Aggron (Acero/Roca), el de Hoenn (Miguel, 21/11/2026). Premio, Tabla Acero.
- **Una persona que trabaja en la cantera,** junto a la entrada. No hay entrenadores: no queda ninguno libre.
- **Zona de captura propia:** MAPSEC_CANTERA.
Los salvajes y los objetos los ponen zonas_nuevas.py y colocar_objetos.py; este script pone los objetos en su
sitio (SITIO_OBJETOS).

**Cómo se dibuja.** La pared de arriba (relleno de montaña, cara de dos filas y la boca) se pinta con las piezas
de la RUTA 116, copiando sus valores. El resto lo pinta autotile.py: tierra (el camino de las praderas), hierba,
hierba alta, riscos con su escalera y árboles normales de Hoenn.
"""

import json
import os
import re
import struct
import sys

sys.path.insert(0, "tools/dualocke")
import autotile as at  # noqa: E402
import colocar_objetos as co  # noqa: E402

CANTERA, MAPA, MAPSEC = "Cantera", "MAP_CANTERA", "MAPSEC_CANTERA"
NOMBRE = "CANTERA"
RUTA, RUTA_MAPA = "Route116", "MAP_ROUTE116"
ENTRADA_RUTA = (67, 10)             # la boca nueva; (67, 9) es la parte de arriba. La del túnel está en (65, 10)
BOCA_TUNEL = (65, 10)               # de aquí se copian las piezas de la boca
# Piezas de la pared de arriba, copiadas de la RUTA 116 (con su colisión y altura): letra -> (x, y) de la ruta
PARED = {
    "M": (62, 4),     # relleno de montaña (no se pisa)
    "K": (46, 7),     # cara, fila de arriba
    "k": (44, 8),     # cara, fila de abajo
    "q": (66, 9),     # cara junto a la boca, fila de arriba
    "w": (46, 8),     # cara junto a la boca, fila de abajo
    "Q": (65, 9),     # encima de la boca
    "C": (65, 10),    # la boca
}
# M montaña   K k cara de la pared   q w cara junto a la boca   Q C boca de la cueva
# T árbol   . hierba   , hierba alta   c tierra   R risco   1 2 su escalera
PLANO = """
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
KKKKKKKKKKKKKKKKKKKqQqKKKKKKKKKKKKKKKKKK
kkkkkkkkkkkkkkkkkkkwCwkkkkkkkkkkkkkkkkkk
........................................
TT..,,,,,,.......cccc........,,,,,,...TT
TT.,,,,,,,,......cccc.......,,,,,,,,..TT
TT.,,,,,,,,......cccc........,,,,,,...TT
TT..,,,,,,.......cccccccc.............TT
TT...............cccccccc.............TT
TTRRRRRRRRRRRRRRRRRRRRR12RRRRRRRRRRRRRTT
TT....ccccccccccccccccccccccccc.......TT
TT..,,ccccccccccccccccccccccccc,,,....TT
TT.,,,ccccccccccccccccccccccccc,,,,...TT
TT.,,,ccccccccccccccccccccccccc,,,,...TT
TT..,,ccccccccccccccccccccccccc,,,....TT
TT....ccccccccccccccccccccccccc.......TT
TT.....cccccccccccccccccccccc.........TT
TT..........cccc......................TT
TTRRRRRRRRRRR12RRRRRRRRRRRRRRRRRRRRRRRTT
TT..........cccc......................TT
TT..,,,,..cccccccccccccccc....,,,,,,..TT
TT.,,,,,,.cccccccccccccccccc..,,,,,,..TT
TT.,,,,,,.cccccccccccccccccc...,,,,...TT
TT..,,,,..cccccccccccccccccc..........TT
TT........cccccccccccccccccc..........TT
TT....................................TT
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
"""
TERRENO = {".": "suelo", ",": "hierba_alta", "c": "camino", "R": "risco", "1": "risco", "2": "risco"}
GUARDIAN = (19, 23, "SPECIES_AGGRON", 29, "ITEM_IRON_PLATE", "FLAG_DUALOCKE_GUARDIAN_CANTERA")
FLAG_GUARDIAN = 0x4FF
OBRERA = (16, 5)                    # junto a la entrada, en la hierba
ROCAS = [(12, 13), (24, 12), (27, 15), (9, 16), (14, 23), (25, 24)]   # rocas de GOLPE ROCA (vuelven al salir)
# Dónde va cada objeto (los pone colocar_objetos.py; aquí se ponen en su sitio)
SITIO_OBJETOS = {
    "FLAG_ITEM_CANTERA_HARD_STONE": (32, 7),          # en la hierba alta de arriba a la derecha
    "FLAG_ITEM_CANTERA_METAL_COAT": (5, 23),          # en la hierba alta de abajo a la izquierda
    "FLAG_ITEM_CANTERA_IRON_BALL": (26, 22),          # oculta, en la tierra del fondo
    "FLAG_ITEM_TICKET_CANTERA": (33, 22),             # en la hierba alta de abajo a la derecha
}
LLEGADA = (20, 3)                   # la boca de la cantera (el warp): se sale hacia abajo


def leer(ruta):
    with open(ruta, encoding="utf-8", newline="") as f:
        return f.read()


def escribir(ruta, texto):
    with open(ruta, "w", encoding="utf-8", newline="") as f:
        f.write(texto)


LAYOUTS = co.cargar_layouts()


def celdas_de(carpeta):
    l = LAYOUTS[json.loads(leer(f"data/maps/{carpeta}/map.json"))["layout"]]
    return l, list(struct.unpack(f"<{l['width'] * l['height']}H", open(l["blockdata_filepath"], "rb").read()))


def ruta116():
    """La boca nueva en la pared de la RUTA 116 y su warp. Devuelve el número del warp."""
    l, c = celdas_de(RUTA)
    w = l["width"]
    ex, ey = ENTRADA_RUTA
    bx, by = BOCA_TUNEL
    for dy in (-1, 0):
        actual = c[(ey + dy) * w + ex] & 0x3FF
        boca = c[(by + dy) * w + bx]
        assert actual in (0x0A9, boca & 0x3FF), ("ahí no está la pared de dos filas", ex, ey + dy, hex(actual))
        c[(ey + dy) * w + ex] = boca
    assert not (c[(ey + 1) * w + ex] >> 10) & 3, "debajo de la boca no se puede pisar"
    with open(l["blockdata_filepath"], "wb") as f:
        f.write(struct.pack(f"<{w * l['height']}H", *c))
    ruta = f"data/maps/{RUTA}/map.json"
    texto = leer(ruta)
    if MAPA not in texto:
        # Altura 0, como las de las cuevas del juego: así funciona desde cualquier altura
        texto = co.insertar_en_lista(texto, "warp_events", {"x": ex, "y": ey, "elevation": 0,
                                                            "dest_map": MAPA, "dest_warp_id": "0"})
        json.loads(texto)
        escribir(ruta, texto)
    warps = json.loads(leer(ruta))["warp_events"]
    return next(i for i, wp in enumerate(warps) if wp["dest_map"] == MAPA)


def crear_layout():
    filas = PLANO.strip().splitlines()
    alto, ancho = len(filas), len(filas[0])
    assert all(len(f) == ancho for f in filas), "las filas del plano no miden lo mismo"
    aprendiz = at.Aprendiz()
    valor = lambda m: aprendiz.valor.get(m, m)  # noqa: E731
    # La pared de arriba cuenta como "pared" para el autotile (no está en TERRENO)
    pintadas = aprendiz.pintar([[TERRENO.get(ch, "pared" if ch in PARED else None) for ch in f] for f in filas])
    _, c116 = celdas_de(RUTA)
    w116 = LAYOUTS[json.loads(leer(f"data/maps/{RUTA}/map.json"))["layout"]]["width"]
    pared = {ch: c116[y * w116 + x] for ch, (x, y) in PARED.items()}
    c = [0] * (ancho * alto)
    for y in range(alto):
        for x in range(ancho):
            ch = filas[y][x]
            if ch in PARED:
                v = pared[ch]
            elif ch == "T":
                v = valor(at.arbol_normal(filas, x, y))
            else:
                v = pintadas[y][x]
                copa = at.copa_normal(filas, x, y, v & 0x3FF)   # la copa del árbol de debajo
                if copa:
                    v = valor(copa)
                elif ch in "12":
                    v = valor(at.ESCALERA_RISCO[int(ch) - 1])
            c[y * ancho + x] = v
    assert all(c), "casillas sin pintar"
    lx, ly = LLEGADA
    assert filas[ly][lx] == "C" and filas[ly + 1][lx] == ".", "debajo de la boca tiene que haber hierba"
    for donde in [GUARDIAN[:2], OBRERA] + ROCAS + list(SITIO_OBJETOS.values()):
        x, y = donde
        assert filas[y][x] in ".,c" and not (c[y * ancho + x] >> 10) & 3, ("objeto o persona fuera del suelo", donde)
    assert len(set([GUARDIAN[:2], OBRERA] + ROCAS + list(SITIO_OBJETOS.values()))) == 4 + len(ROCAS) + 2

    base = LAYOUTS[json.loads(leer(f"data/maps/{RUTA}/map.json"))["layout"]]
    os.makedirs(f"data/layouts/{CANTERA}", exist_ok=True)
    with open(f"data/layouts/{CANTERA}/map.bin", "wb") as f:
        f.write(struct.pack(f"<{ancho * alto}H", *c))
    with open(base["border_filepath"], "rb") as f, open(f"data/layouts/{CANTERA}/border.bin", "wb") as g:
        g.write(f.read())
    ident = "LAYOUT_" + MAPA[4:]
    texto = leer("data/layouts/layouts.json")
    if f'"{ident}"' not in texto:
        texto = co.insertar_en_lista(texto, "layouts", {
            "id": ident, "name": f"{CANTERA}_Layout", "width": ancho, "height": alto,
            "primary_tileset": base["primary_tileset"], "secondary_tileset": base["secondary_tileset"],
            "border_filepath": f"data/layouts/{CANTERA}/border.bin",
            "blockdata_filepath": f"data/layouts/{CANTERA}/map.bin"})
        json.loads(texto)
        escribir("data/layouts/layouts.json", texto)
    raras = aprendiz.revisar(c, ancho, alto, base["secondary_tileset"])
    print(f"Dualocke: CANTERA: parejas de piezas que el juego no usa: {len(raras)}")
    return ident


def con_nivel_actual(ruta, texto):
    """Conserva el nivel del guardián que haya puesto reescalar_niveles.py (regla "tope")."""
    if os.path.exists(ruta):
        anterior = re.search(r"setwildbattle (SPECIES_\w+), (\d+)", leer(ruta))
        if anterior:
            texto = re.sub(r"setwildbattle (SPECIES_\w+), \d+", rf"setwildbattle \1, {anterior.group(2)}", texto)
    return texto


def crear_mapa(layout, warp_ruta):
    ruta = f"data/maps/{CANTERA}/map.json"
    os.makedirs(f"data/maps/{CANTERA}", exist_ok=True)
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    gx, gy, _, _, _, flag = GUARDIAN
    objetos = [
        {"local_id": "LOCALID_CANTERA_GUARDIAN", "graphics_id": "OBJ_EVENT_GFX_VAR_0", "x": gx, "y": gy,
         "elevation": 3, "movement_type": "MOVEMENT_TYPE_FACE_DOWN", "movement_range_x": 0, "movement_range_y": 0,
         "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
         "script": f"{CANTERA}_EventScript_Pokemon", "flag": flag},
        {"graphics_id": "OBJ_EVENT_GFX_HIKER", "x": OBRERA[0], "y": OBRERA[1], "elevation": 3,
         "movement_type": "MOVEMENT_TYPE_FACE_DOWN", "movement_range_x": 0, "movement_range_y": 0,
         "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
         "script": f"{CANTERA}_EventScript_Obrera", "flag": "0"}]
    for i, (x, y) in enumerate(ROCAS):
        objetos.append({"graphics_id": "OBJ_EVENT_GFX_BREAKABLE_ROCK", "x": x, "y": y, "elevation": 3,
                        "movement_type": "MOVEMENT_TYPE_LOOK_AROUND", "movement_range_x": 0, "movement_range_y": 0,
                        "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
                        "script": "EventScript_RockSmash", "flag": f"FLAG_TEMP_{0x11 + i:X}"})
    datos = {
        "id": MAPA, "name": CANTERA, "layout": layout, "music": "MUS_ROUTE110", "region": "REGION_HOENN",
        "region_map_section": MAPSEC, "requires_flash": False, "weather": "WEATHER_SUNNY",
        "map_type": "MAP_TYPE_ROUTE", "allow_cycling": True, "allow_escaping": False, "allow_running": True,
        "show_map_name": True, "battle_scene": "MAP_BATTLE_SCENE_NORMAL",
        "connections": None,
        "object_events": objetos + [o for o in anteriores.get("object_events", [])
                                    if str(o.get("flag", "")).startswith("FLAG_ITEM_")],
        "warp_events": [{"x": LLEGADA[0], "y": LLEGADA[1], "elevation": 0, "dest_map": RUTA_MAPA,
                         "dest_warp_id": str(warp_ruta)}],
        "coord_events": [],
        "bg_events": [b for b in anteriores.get("bg_events", []) if b.get("type") == "hidden_item"],
    }
    for o in datos["object_events"] + datos["bg_events"]:
        if o.get("flag") in SITIO_OBJETOS:
            o["x"], o["y"] = SITIO_OBJETOS[o["flag"]]
            o["elevation"] = 3
    escribir(ruta, json.dumps(datos, indent=2, ensure_ascii=False) + "\n")
    escribir(f"data/maps/{CANTERA}/scripts.inc", con_nivel_actual(f"data/maps/{CANTERA}/scripts.inc", SCRIPTS))

    # Grupo: el de la RUTA 116, al final (no cambia el número de ningún mapa)
    grupos = leer("data/maps/map_groups.json")
    if f'"{CANTERA}"' not in grupos:
        salto = "\r\n" if "\r\n" in grupos else "\n"
        d = json.loads(grupos)
        grupo = next(g for g in d["group_order"] if RUTA in d[g])
        ultimo = d[grupo][-1]
        a = f'"{ultimo}"{salto}'
        i = grupos.index(a, grupos.index(f'"{grupo}": ['))
        grupos = grupos[:i] + f'"{ultimo}",{salto}    "{CANTERA}"{salto}' + grupos[i + len(a):]
        json.loads(grupos)
        escribir("data/maps/map_groups.json", grupos)


def zona_y_cartel():
    """La zona de captura (al final de la lista), el cartel, HOENN_EXTRA_MAPSEC_LAST, el flag del guardián y el
    script en event_scripts.s."""
    ruta = "src/data/region_map/region_map_sections.json"
    texto = leer(ruta)
    if f'"{MAPSEC}"' not in texto:
        secciones = json.loads(texto)["map_sections"]
        r116 = next(s for s in secciones if s["id"] == "MAPSEC_ROUTE_116")
        # Encima del final este de la RUTA 116
        texto = co.insertar_en_lista(texto, "map_sections", {"id": MAPSEC, "name": NOMBRE,
                                                             "x": r116["x"] + r116["width"] - 1, "y": r116["y"] - 1,
                                                             "width": 1, "height": 1})
        json.loads(texto)
        escribir(ruta, texto)
    assert len(NOMBRE) <= 16

    ruta = "src/dualocke.c"
    texto = leer(ruta)
    texto = re.sub(r"#define HOENN_EXTRA_MAPSEC_LAST  MAPSEC_\w+", f"#define HOENN_EXTRA_MAPSEC_LAST  {MAPSEC}", texto)
    escribir(ruta, texto)

    ruta = "src/map_name_popup.c"
    texto = leer(ruta)
    if MAPSEC not in texto:
        salto = "\r\n" if "\r\n" in texto else "\n"
        for tema in ("MAPPOPUP_THEME_WOOD", "MAPPOPUP_THEME_BW_DEFAULT"):
            a = f"    [MAPSEC_CIENAGA_TOXICA - KANTO_MAPSEC_COUNT] = {tema}, // Dualocke: zona nueva{salto}"
            assert texto.count(a) == 1, tema
            texto = texto.replace(a, a + f"    [{MAPSEC} - KANTO_MAPSEC_COUNT] = {tema}, // Dualocke: zona nueva{salto}")
        escribir(ruta, texto)

    ruta = "include/constants/flags.h"
    texto = leer(ruta)
    nombre = GUARDIAN[5]
    if nombre not in texto:
        antigua = re.search(rf"^#define FLAG_UNUSED_0x{FLAG_GUARDIAN:03X}\s+0x{FLAG_GUARDIAN:X}\b.*$", texto, re.M)
        assert antigua, f"el flag 0x{FLAG_GUARDIAN:03X} ya no está libre"
        texto = texto.replace(antigua.group(0), f"#define {nombre:<34} 0x{FLAG_GUARDIAN:03X} "
                                                f"// Dualocke: guardián de la {NOMBRE} vencido o capturado")
        escribir(ruta, texto)

    ruta = "data/event_scripts.s"
    texto = leer(ruta)
    linea = f'\t.include "data/maps/{CANTERA}/scripts.inc" @ Dualocke: zona nueva'
    if linea not in texto:
        salto = "\r\n" if "\r\n" in texto else "\n"
        a = '\t.include "data/maps/CienagaToxica/scripts.inc" @ Dualocke: zona nueva' + salto
        assert texto.count(a) == 1
        texto = texto.replace(a, a + linea + salto)
        escribir(ruta, texto)


_, _, ESPECIE, NIVEL, PREMIO, FLAG = GUARDIAN
SCRIPTS = f"""{CANTERA}_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, {CANTERA}_OnTransition
	.byte 0

@ Dualocke: la CANTERA, por una cueva de la RUTA 116 (tools/dualocke/crear_cantera.py).
@ El guardián es un Pokémon fuerte que se puede capturar, como en las islas del ferry
@ (data/scripts/dualocke_islas.inc). Con semilla sale otro fuerte (estaticos.py, islas()).
{CANTERA}_OnTransition:
	setvar VAR_0x8004, {ESPECIE}
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

{CANTERA}_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, {ESPECIE}
	setvar VAR_TEMP_9, {PREMIO}
	call Dualocke_EventScript_AvisoIsla
	setwildbattle {ESPECIE}, {NIVEL}
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, {CANTERA}_EventScript_PokemonSigue
	setflag {FLAG}
	call Dualocke_EventScript_PremioIsla
	release
	end

{CANTERA}_EventScript_PokemonSigue::
	release
	end

{CANTERA}_EventScript_Obrera::
	msgbox {CANTERA}_Text_Obrera, MSGBOX_NPC
	end

{CANTERA}_Text_Obrera:
	.string "De esta cantera sale el hierro\\n"
	.string "con el que DEVON hace sus inventos.\\p"
	.string "Los POKéMON de acero vienen a comer\\n"
	.string "las piedras… ¡y a veces el material!\\p"
	.string "Abajo del todo vive uno enorme.\\n"
	.string "Desde que llegó, no bajamos.$"
"""


def main():
    warp = ruta116()
    crear_mapa(crear_layout(), warp)
    zona_y_cartel()
    print("Dualocke: CANTERA creada")


if __name__ == "__main__":
    main()
