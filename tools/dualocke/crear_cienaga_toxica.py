#!/usr/bin/env python3
"""
Dualocke: la CIÉNAGA TÓXICA, al sur de la RUTA 117 (Miguel, 17/11/2026). Segundo bioma "por tipo": el tipo
Veneno no tenía zona propia (salía en muchas, pero solo por Zubat y Tentacool).

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_cienaga_toxica.py

- **Dónde:** se entra andando por el borde sur de la RUTA 117 (x 32-36), junto a su hierba alta, sin pantalla de
  carga. **Tramo 3** (cap 32), el de la RUTA 117: es la primera zona nueva a la que se llega sin SURF ni CORTE
  después del BOSQUE FRONDOSO. (Iba a ir al este de la RUTA 110, pero ese borde es todo agua y haría falta SURF.)
  En esa parte de la RUTA 117, la fila de abajo tenía las copas de los árboles del borde; pasan a ser hierba
  alta (x 32-34) y hierba (x 35-36).
- **El mapa** (60 × 40), con los gráficos de la RUTA 117 (General + Mauville). Siempre llueve.
  - Charcas por todas partes, manchas de hierba alta y un camino de barro
    que baja desde la entrada y cruza la ciénaga.
  - Al fondo, la gran charca del sureste, con un islote en medio al que se llega por una lengua de tierra: ahí
    está el guardián.
  - Los árboles son los normales de Hoenn (autotile.arbol_normal() y copa_normal()); lo demás lo pinta autotile.py.
- **Guardián:** sin semilla, Dragalge (Veneno/Dragón); premio, Lodo Negro (y su megapiedra).
  `FLAG_DUALOCKE_GUARDIAN_CIENAGA`.
- **Zona de captura propia:** `MAPSEC_CIENAGA_TOXICA`, al final de la lista (118 de 128).
Los salvajes los pone zonas_nuevas.py y los objetos, colocar_objetos.py.
"""

import json
import os
import re
import struct
import sys

sys.path.insert(0, "tools/dualocke")
import autotile as at  # noqa: E402
import colocar_objetos as co  # noqa: E402

CIENAGA, MAPA, MAPSEC = "CienagaToxica", "MAP_CIENAGA_TOXICA", "MAPSEC_CIENAGA_TOXICA"
NOMBRE = "CIÉNAGA TÓXICA"
RUTA, RUTA_MAPA = "Route117", "MAP_ROUTE117"
DESPLAZAMIENTO = 0                          # la ciénaga empieza en la x 0 de la RUTA 117
# En la RUTA 117, fila de abajo: copas de árbol (0x025 sobre hierba alta, 0x00F sobre hierba) que pasan a ser
# hierba alta y hierba
ENTRADA_RUTA = {32: 0x00D, 33: 0x00D, 34: 0x00D, 35: 0x001, 36: 0x001}
COPAS_RUTA = (0x025, 0x00F)
BORDE_BOSQUE = at.ARBOL_INTERIOR + (at.ARBOL_COPA, 0x00F, 0x025, 0x01D)   # lo que puede haber encima de un árbol
FLORES = 0x004
# T árbol   . hierba   , hierba alta   ~ charca   c camino de barro   * flores
# (Sin hierba muy alta: su borde de abajo solo existe en los gráficos de ARBORADA.)
PLANO = """
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT,,,..TTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT,,,..TTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT,,...TTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT...ccTTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT...ccTTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTT...........................cc................TTTTTTT
TTTTT.................,,,,,,,,.....cc..................TTTTT
TTTT.....~~~~~~~~~~~~..,,,,,,,,....cc.......*...........TTTT
TTTTTTT..~~~~~~~~~~~~..,,,,,,,,....cc...........TTTTTTTTTTTT
TTTTTTT..~~~~~~~~~~~~...,,,,,,.....cc...........TTTTTTTTTTTT
TTTTTTT..~~~~~~~~~~~~...ccccccccccccc...........TTTTTTTTTTTT
TTTTTTT..~~~~~~~~~~~~...ccccccccc,,,,,,,.................TTT
TTTTTTT................cc.......,,,,,,,......*...........TTT
TTT....................cc..................TTTTT.........TTT
TTT...............*....cc.........~~~~~~...TTTTT.........TTT
TTT....................cc.TTTTTT..~~~~~~.................TTT
TTT....................cc.TTTTTT..~~~~~~.......,,,,,,,,..TTT
TTT...*................cc.TTTTTT..~~~~~~......,,,,,,,,,,.TTT
TTT....................cc.....................,,,,,,,,,,.TTT
TTT....~~~~~~~~~~......cc..........................,,,,..TTT
TTT....~~~~~~~~~~......cc.......~~~~~~~~~~~~~~~~~~~.,,,..TTT
TTT....~~~~~~~~~~......cc.......~~~~~~~~~~~~~~~~~~~......TTT
TTTTTT.~~~~~~~~~~......ccccccc..~~~~~~~~~~~~~~~~~~~......TTT
TTTTTT.................ccccccc..~~~~~~.......~~~~~~......TTT
TTTTTT..,,,,,,,,................~~~~~~.......~~~~~~......TTT
TTTTTT.,,,,,,,,,,...............~~~~~~.......~~~~~~......TTT
TTTTTT..,,,,,,,,...TTTTTT.......~~~~~~.......~~~~~~......TTT
TTTTTT...,,,,,,....TTTTTT.......~~~~~~~~~.~~~~~~~~~......TTT
TTT.............................~~~~~~~~~.~~~~~~~~~......TTT
TTT..,,,,,,,,...................~~~~~~~~~.~~~~~~~~~......TTT
TTT.,,,,,,,,,,,.....................................TTTTTTTT
TTT.,,,,,,,,,,,,,...........*.......................TTTTTTTT
TTTT.,,,,,,,,,,,........................................TTTT
TTTTT..,,,,,,,....................................*....TTTTT
TTTTTTT..............................................TTTTTTT
TTTTTTTTTT.......................................TTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
"""
TERRENO = {".": "suelo", "*": "suelo", ",": "hierba_alta", ";": "hierba_larga", "~": "estanque", "c": "camino"}
GUARDIAN = (41, 24, "SPECIES_DRAGALGE", 29, "ITEM_BLACK_SLUDGE", "FLAG_DUALOCKE_GUARDIAN_CIENAGA")
FLAG_GUARDIAN = 0x472
CIENTIFICA = (38, 6)
# Dónde va cada objeto (los pone colocar_objetos.py; aquí se ponen en su sitio)
SITIO_OBJETOS = {
    "FLAG_ITEM_CIENAGA_POISON_BARB": (4, 7),          # al oeste de la charca del noroeste
    "FLAG_ITEM_CIENAGA_ABSORB_BULB": (55, 18),        # al fondo de la hierba alta del este
    "FLAG_ITEM_CIENAGA_TOXIC_PLATE": (40, 25),        # oculta, en el islote del guardián
    "FLAG_ITEM_TICKET_CIENAGA_TOXICA": (8, 33),       # en la hierba alta del suroeste
}


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


def ruta117():
    """Abre la entrada en el borde sur de la RUTA 117: las copas pasan a ser hierba alta y hierba."""
    l, c = celdas_de(RUTA)
    w, h = l["width"], l["height"]
    y = h - 1
    for x, m in ENTRADA_RUTA.items():
        v = c[y * w + x]
        assert v & 0x3FF in COPAS_RUTA + (m,), ("la entrada no va donde se pensaba", x, hex(v & 0x3FF))
        c[y * w + x] = next(u for u in c if u & 0x3FF == m and not (u >> 10) & 3)
    with open(l["blockdata_filepath"], "wb") as f:
        f.write(struct.pack(f"<{w * h}H", *c))
    return [c[y * w + x] & 0x3FF for x in range(w)]


def crear_layout(borde_ruta):
    filas = PLANO.strip().splitlines()
    alto, ancho = len(filas), len(filas[0])
    assert all(len(f) == ancho for f in filas), "las filas del plano no miden lo mismo"
    aprendiz = at.Aprendiz()
    valor = lambda m: aprendiz.valor.get(m, m)  # noqa: E731
    pintadas = aprendiz.pintar([[TERRENO.get(ch) for ch in f] for f in filas])
    # La fila 0 de la ciénaga sigue a la fila de abajo de la RUTA 117
    for x in range(ancho):
        arriba = borde_ruta[DESPLAZAMIENTO + x]
        if filas[0][x] == "T":
            assert arriba in BORDE_BOSQUE, ("encima de un árbol del borde hay otra cosa", x, hex(arriba))
        else:
            assert x in ENTRADA_RUTA and arriba == ENTRADA_RUTA[x], ("la entrada no coincide con la de la ruta", x)
    c = [0] * (ancho * alto)
    for y in range(alto):
        for x in range(ancho):
            ch = filas[y][x]
            if ch == "T":
                c[y * ancho + x] = valor(at.arbol_normal(filas, x, y))
                continue
            v = pintadas[y][x]
            copa = at.copa_normal(filas, x, y, v & 0x3FF)   # la copa del árbol de debajo
            if copa:
                v = valor(copa)
            elif ch == "*":
                v = (v & ~0x3FF) | FLORES
            c[y * ancho + x] = v
    assert all(c), "casillas sin pintar"
    gx, gy = GUARDIAN[:2]
    assert not (c[gy * ancho + gx] >> 10) & 3, "el guardián no está en el suelo"
    for donde in list(SITIO_OBJETOS.values()) + [CIENTIFICA]:
        x, y = donde
        assert filas[y][x] in ".,;*c", ("objeto o persona fuera del suelo", donde)

    base = LAYOUTS[json.loads(leer(f"data/maps/{RUTA}/map.json"))["layout"]]
    os.makedirs(f"data/layouts/{CIENAGA}", exist_ok=True)
    with open(f"data/layouts/{CIENAGA}/map.bin", "wb") as f:
        f.write(struct.pack(f"<{ancho * alto}H", *c))
    with open(base["border_filepath"], "rb") as f, open(f"data/layouts/{CIENAGA}/border.bin", "wb") as g:
        g.write(f.read())
    ident = "LAYOUT_" + MAPA[4:]
    texto = leer("data/layouts/layouts.json")
    if f'"{ident}"' not in texto:
        texto = co.insertar_en_lista(texto, "layouts", {
            "id": ident, "name": f"{CIENAGA}_Layout", "width": ancho, "height": alto,
            "primary_tileset": base["primary_tileset"], "secondary_tileset": base["secondary_tileset"],
            "border_filepath": f"data/layouts/{CIENAGA}/border.bin",
            "blockdata_filepath": f"data/layouts/{CIENAGA}/map.bin"})
        json.loads(texto)
        escribir("data/layouts/layouts.json", texto)
    raras = aprendiz.revisar(c, ancho, alto, base["secondary_tileset"])
    print(f"Dualocke: CIÉNAGA TÓXICA: parejas de piezas que el juego no usa: {len(raras)}")
    return ident


def con_nivel_actual(ruta, texto):
    """Conserva el nivel del guardián que haya puesto reescalar_niveles.py (regla "tope")."""
    if os.path.exists(ruta):
        anterior = re.search(r"setwildbattle (SPECIES_\w+), (\d+)", leer(ruta))
        if anterior:
            texto = re.sub(r"setwildbattle (SPECIES_\w+), \d+", rf"setwildbattle \1, {anterior.group(2)}", texto)
    return texto


def crear_mapa(layout):
    ruta = f"data/maps/{CIENAGA}/map.json"
    os.makedirs(f"data/maps/{CIENAGA}", exist_ok=True)
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    gx, gy, _, _, _, flag = GUARDIAN
    objetos = [
        {"local_id": "LOCALID_CIENAGA_TOXICA_GUARDIAN", "graphics_id": "OBJ_EVENT_GFX_VAR_0", "x": gx, "y": gy,
         "elevation": 3, "movement_type": "MOVEMENT_TYPE_FACE_DOWN", "movement_range_x": 0, "movement_range_y": 0,
         "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
         "script": f"{CIENAGA}_EventScript_Pokemon", "flag": flag},
        {"graphics_id": "OBJ_EVENT_GFX_SCIENTIST_1", "x": CIENTIFICA[0], "y": CIENTIFICA[1], "elevation": 3,
         "movement_type": "MOVEMENT_TYPE_FACE_LEFT", "movement_range_x": 0, "movement_range_y": 0,
         "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
         "script": f"{CIENAGA}_EventScript_Cientifica", "flag": "0"}]
    datos = {
        "id": MAPA, "name": CIENAGA, "layout": layout, "music": "MUS_ROUTE119", "region": "REGION_HOENN",
        "region_map_section": MAPSEC, "requires_flash": False, "weather": "WEATHER_RAIN",
        "map_type": "MAP_TYPE_ROUTE", "allow_cycling": True, "allow_escaping": False, "allow_running": True,
        "show_map_name": True, "battle_scene": "MAP_BATTLE_SCENE_NORMAL",
        "connections": [{"map": RUTA_MAPA, "offset": -DESPLAZAMIENTO, "direction": "up"}],
        "object_events": objetos + [o for o in anteriores.get("object_events", [])
                                    if str(o.get("flag", "")).startswith("FLAG_ITEM_")],
        "warp_events": [], "coord_events": [],
        "bg_events": [b for b in anteriores.get("bg_events", []) if b.get("type") == "hidden_item"],
    }
    for o in datos["object_events"] + datos["bg_events"]:
        if o.get("flag") in SITIO_OBJETOS:
            o["x"], o["y"] = SITIO_OBJETOS[o["flag"]]
    escribir(ruta, json.dumps(datos, indent=2, ensure_ascii=False) + "\n")
    escribir(f"data/maps/{CIENAGA}/scripts.inc", con_nivel_actual(f"data/maps/{CIENAGA}/scripts.inc", SCRIPTS))

    # La RUTA 117 se conecta hacia abajo con la ciénaga
    ruta = f"data/maps/{RUTA}/map.json"
    texto = leer(ruta)
    if MAPA not in texto:
        texto = co.insertar_en_lista(texto, "connections", {"map": MAPA, "offset": DESPLAZAMIENTO,
                                                            "direction": "down"})
        json.loads(texto)
        escribir(ruta, texto)

    # Grupo: el de la RUTA 117, al final (no cambia el número de ningún mapa)
    grupos = leer("data/maps/map_groups.json")
    if f'"{CIENAGA}"' not in grupos:
        salto = "\r\n" if "\r\n" in grupos else "\n"
        d = json.loads(grupos)
        grupo = next(g for g in d["group_order"] if RUTA in d[g])
        ultimo = d[grupo][-1]
        a = f'"{ultimo}"{salto}'
        i = grupos.index(a, grupos.index(f'"{grupo}": ['))
        grupos = grupos[:i] + f'"{ultimo}",{salto}    "{CIENAGA}"{salto}' + grupos[i + len(a):]
        json.loads(grupos)
        escribir("data/maps/map_groups.json", grupos)


def zona_y_cartel():
    """La zona de captura (al final de la lista), el cartel, HOENN_EXTRA_MAPSEC_LAST, el flag del guardián y el
    script en event_scripts.s."""
    ruta = "src/data/region_map/region_map_sections.json"
    texto = leer(ruta)
    if f'"{MAPSEC}"' not in texto:
        secciones = json.loads(texto)["map_sections"]
        r117 = next(s for s in secciones if s["id"] == "MAPSEC_ROUTE_117")
        texto = co.insertar_en_lista(texto, "map_sections", {"id": MAPSEC, "name": NOMBRE,
                                                             "x": r117["x"] + 1, "y": r117["y"] + 1,
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
            a = f"    [MAPSEC_BOSQUE_SINIESTRO - KANTO_MAPSEC_COUNT] = {tema}, // Dualocke: zona nueva{salto}"
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
    linea = f'\t.include "data/maps/{CIENAGA}/scripts.inc" @ Dualocke: zona nueva'
    if linea not in texto:
        salto = "\r\n" if "\r\n" in texto else "\n"
        a = '\t.include "data/maps/BosqueSiniestro/scripts.inc" @ Dualocke: zona nueva' + salto
        assert texto.count(a) == 1
        texto = texto.replace(a, a + linea + salto)
        escribir(ruta, texto)


_, _, ESPECIE, NIVEL, PREMIO, FLAG = GUARDIAN
SCRIPTS = f"""{CIENAGA}_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, {CIENAGA}_OnTransition
	.byte 0

@ Dualocke: la CIÉNAGA TÓXICA, al sur de la RUTA 117 (tools/dualocke/crear_cienaga_toxica.py).
@ El guardián es un Pokémon fuerte que se puede capturar, como en las islas del ferry
@ (data/scripts/dualocke_islas.inc). Con semilla sale otro fuerte (estaticos.py, islas()).
{CIENAGA}_OnTransition:
	setvar VAR_0x8004, {ESPECIE}
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

{CIENAGA}_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, {ESPECIE}
	setvar VAR_TEMP_9, {PREMIO}
	call Dualocke_EventScript_AvisoIsla
	setwildbattle {ESPECIE}, {NIVEL}
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, {CIENAGA}_EventScript_PokemonSigue
	setflag {FLAG}
	call Dualocke_EventScript_PremioIsla
	release
	end

{CIENAGA}_EventScript_PokemonSigue::
	release
	end

{CIENAGA}_EventScript_Cientifica::
	msgbox {CIENAGA}_Text_Cientifica, MSGBOX_NPC
	end

{CIENAGA}_Text_Cientifica:
	.string "Estudio el agua de esta ciénaga.\\n"
	.string "Está llena de veneno… ¡y de vida!\\p"
	.string "En el islote de la charca grande\\n"
	.string "vive un POKéMON enorme.\\p"
	.string "Lleva antídotos si vas a verlo.$"
"""


def main():
    borde = ruta117()
    crear_mapa(crear_layout(borde))
    zona_y_cartel()
    print("Dualocke: CIÉNAGA TÓXICA creada")


if __name__ == "__main__":
    main()
