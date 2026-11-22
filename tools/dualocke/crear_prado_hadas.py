#!/usr/bin/env python3
"""
Dualocke: el PRADO DE HADAS, el bioma del tipo Hada (PLAN.md, propuesta C; Miguel, 21/11/2026: "en la ruta de
antes del Instituto Meteorológico, al lado hay una zona como de vallas, de jardín… una entrada a un bosque o
prado de flores").

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_prado_hadas.py

- **Entrada:** por el oeste del INSTITUTO METEOROLÓGICO, en la RUTA 119. Se cortan los árboles del borde
  izquierdo de la ruta en las filas 33-34 (junto al jardín del instituto) y por ahí se pasa al prado, sin
  pantalla de carga. A esa parte de la ruta se llega en el **tramo 6** (`alcance.py`). (El jardín con vallas
  junto al lago del norte de la ruta no se alcanza hasta más tarde.)
- **El prado** (40 × 36, gráficos de la RUTA 119): un camino de tierra lleva de la entrada al centro. Alrededor,
  flores, charcas, hierba alta y hierba muy alta (con su borde: los gráficos de ARBORADA lo tienen). Al norte,
  junto a la charca grande, un claro con un anillo de flores donde espera el guardián.
- **Guardián:** Gardevoir (Psíquico/Hada; Miguel, 21/11/2026). Premio, Tabla Duende.
- **Una florista** junto a la entrada. No hay entrenadores: no queda ninguno libre.
- **Zona de captura propia:** MAPSEC_PRADO_HADAS.
Los salvajes y los objetos los ponen zonas_nuevas.py y colocar_objetos.py; este script pone los objetos en su
sitio (SITIO_OBJETOS).
"""

import json
import os
import re
import struct
import sys

sys.path.insert(0, "tools/dualocke")
import autotile as at  # noqa: E402
import colocar_objetos as co  # noqa: E402

PRADO, MAPA, MAPSEC = "PradoHadas", "MAP_PRADO_HADAS", "MAPSEC_PRADO_HADAS"
NOMBRE = "PRADO DE HADAS"
RUTA, RUTA_MAPA = "Route119", "MAP_ROUTE119"
# El prado va a la izquierda de la RUTA 119; su fila 0 es la fila -1 de la ruta (así su fila 34 es la 33 de la ruta)
DESPLAZAMIENTO = -1
# En la RUTA 119 (columna 0-2): la fila 32 pasa a ser pie de árbol y las 33-34, hierba (la entrada)
ENTRADA_RUTA = {"pie": 32, "hierba": (33, 34), "columnas": (0, 1, 2), "columnas_pie": (0, 1)}   # (2, 32) es el instituto
FLORES = 0x004
# T árbol   . hierba   , hierba alta   ; hierba muy alta   ~ charca   c camino de tierra   * flores
PLANO = """
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTT.............*...TTTTTTTTTTTTT
TTTTTTTT...*...........*.....TTTTTTTTTTT
TTTTTTT..*.....~~~~~~~.....*..TTTTTTTTTT
TTTTTT..*......~~~~~~~......*..TTTTTTTTT
TTTTTT.........~~~~~~~..........TTTTTTTT
TTTTT...*..................*....TTTTTTTT
TTTTT.......*.*.*.*.*.*.........TTTTTTTT
TTTTT..*....*...........*....*..TTTTTTTT
TTTTT,,,,...*.*.*...*.*.*...,,,,TTTTTTTT
TTTT,,,,,,.......c.......,,,,,,,TTTTTTTT
TTT;;;;,,,.......c.......,,;;;;;,TTTTTTT
TTT;;;;;,,...*...c...*...,;;;;;;,TTTTTTT
TTT;;;;;,,.......c.......,;;;;;;,TTTTTTT
TTT,;;;,,....*...c...*....,;;;;,,TTTTTTT
TTT,,,,,.........c.........,,,,..TTTTTTT
TTT......~~~~....c....~~~~......TTTTTTTT
TTT..*...~~~~....c....~~~~...*..TTTTTTTT
TTT......~~~~....c....~~~~......TTTTTTTT
TTT...*..........c..........*...TTTTTTTT
TTTT.......*.....c.....*.......TTTTTTTTT
TTTT,,,,,........c........,,,,,TTTTTTTTT
TTTT,,,,,,.......c.......,,,,,,TTTTTTTTT
TTTT,,,,,,..*....c....*..,,,,,,TTTTTTTTT
TTTT,,,,,........c........,,,,,TTTTTTTTT
TTTTT............c...............TTTTTTT
TTTTTT...*.......ccccccccc...*....TTTTTT
TTTTTTT..................ccc.......TTTTT
TTTTTTTT...,,,,,...........cc.......TTTT
TTTTTTTTT..,,,,,............cc......TTTT
TTTTTTTTTT.,,,,,.....*.......cc.....TTTT
TTTTTTTTTTT.........TTTTT.....cc....TTTT
TTTTTTTTTTTTTTTTTTTTTTTTTTTT...ccc..TTTT
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTT..cccccc..
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT........
"""
TERRENO = {".": "suelo", "*": "suelo", ",": "hierba_alta", ";": "hierba_larga", "~": "estanque", "c": "camino"}
GUARDIAN = (17, 9, "SPECIES_GARDEVOIR", 59, "ITEM_PIXIE_PLATE", "FLAG_DUALOCKE_GUARDIAN_PRADO")
FLAG_GUARDIAN = 0x4E4
FLORISTA = (34, 33)                 # junto a la entrada
SITIO_OBJETOS = {
    "FLAG_ITEM_PRADO_SHINY_STONE": (6, 9),             # al oeste del claro del guardián
    "FLAG_ITEM_PRADO_SACHET": (29, 21),                # junto a la charca del este
    "FLAG_ITEM_PRADO_FAIRY_FEATHER": (27, 3),          # oculta, en el claro de la charca grande
    "FLAG_ITEM_TICKET_PRADO_HADAS": (13, 31),          # en la hierba alta del sur
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


def ruta119():
    """Abre la entrada en el borde izquierdo de la RUTA 119: pie de árbol en la fila 32 y hierba en las 33-34."""
    l, c = celdas_de(RUTA)
    w = l["width"]
    pie = next(v for v in c if v & 0x3FF == at.ARBOL_PIE + 1 and (v >> 10) & 3)    # 0x017, como el de la fila 34
    hierba = c[33 * w + 3]
    assert hierba & 0x3FF == 0x001, "junto a la entrada no hay hierba"
    for x in ENTRADA_RUTA["columnas_pie"]:
        assert c[ENTRADA_RUTA["pie"] * w + x] & 0x3FF in at.ARBOL_INTERIOR + (pie & 0x3FF,)
        c[ENTRADA_RUTA["pie"] * w + x] = pie
    for x in ENTRADA_RUTA["columnas"]:
        for y in ENTRADA_RUTA["hierba"]:
            assert c[y * w + x] & 0x3FF in at.ARBOL_INTERIOR + (0x017, 0x001), ("la entrada no va donde se pensaba", x, y)
            c[y * w + x] = hierba
    with open(l["blockdata_filepath"], "wb") as f:
        f.write(struct.pack(f"<{w * l['height']}H", *c))
    return [c[y * w] if 0 <= y < l["height"] else None for y in range(DESPLAZAMIENTO, DESPLAZAMIENTO + 36)]


def crear_layout(borde_ruta):
    filas = PLANO.strip().splitlines()
    alto, ancho = len(filas), len(filas[0])
    assert all(len(f) == ancho for f in filas), "las filas del plano no miden lo mismo"
    aprendiz = at.Aprendiz()
    valor = lambda m: aprendiz.valor.get(m, m)  # noqa: E731
    pintadas = aprendiz.pintar([[TERRENO.get(ch) for ch in f] for f in filas])
    # La columna de la derecha del prado sigue a la columna 0 de la ruta: árboles donde la ruta no se pisa
    # (árboles, y en las filas 23-26 de la ruta, el acantilado de encima del instituto); hierba en la entrada
    for y in range(alto):
        de_la_ruta = borde_ruta[y]
        if de_la_ruta is None:
            continue
        if filas[y][-1] == "T":
            assert (de_la_ruta >> 10) & 3, ("junto a un árbol del prado, la ruta se pisa", y)
        else:
            assert de_la_ruta & 0x3FF == 0x001, ("la entrada del prado no coincide con la de la ruta", y, hex(de_la_ruta))
    c = [0] * (ancho * alto)
    for y in range(alto):
        for x in range(ancho):
            ch = filas[y][x]
            if ch == "T":
                c[y * ancho + x] = valor(at.arbol_normal(filas, x, y))
                continue
            v = pintadas[y][x]
            copa = at.copa_normal(filas, x, y, v & 0x3FF)
            if copa:
                v = valor(copa)
            elif ch == "*":
                assert all(filas[yy][xx] != "~" for yy in range(y - 1, y + 2) for xx in range(x - 1, x + 2)), \
                    ("flores junto a la charca: se perdería su orilla", x, y)
                v = (v & ~0x3FF) | FLORES
            c[y * ancho + x] = v
    assert all(c), "casillas sin pintar"
    # La entrada: la hierba de la ruta está a altura 4 y la del prado a 3, y el juego no deja pasar de una a
    # otra. Las casillas del borde del prado que dan a la entrada van a altura 0, la de paso (como en las
    # escaleras): desde ella se puede ir a las dos alturas. Antes no se entraba (lo vio el bot de Jorge, #117,
    # 22/11/2026); comprobar_zonas.py lo mira ahora en todas las conexiones de las zonas nuevas.
    for y in range(alto):
        if borde_ruta[y] is not None and filas[y][-1] != "T" and borde_ruta[y] >> 12 != c[y * ancho + ancho - 1] >> 12:
            c[y * ancho + ancho - 1] &= 0x0FFF
    for donde in [GUARDIAN[:2], FLORISTA] + list(SITIO_OBJETOS.values()):
        x, y = donde
        assert filas[y][x] in ".,;*c" and not (c[y * ancho + x] >> 10) & 3, ("objeto o persona fuera del suelo", donde)

    base = LAYOUTS[json.loads(leer(f"data/maps/{RUTA}/map.json"))["layout"]]
    os.makedirs(f"data/layouts/{PRADO}", exist_ok=True)
    with open(f"data/layouts/{PRADO}/map.bin", "wb") as f:
        f.write(struct.pack(f"<{ancho * alto}H", *c))
    with open(base["border_filepath"], "rb") as f, open(f"data/layouts/{PRADO}/border.bin", "wb") as g:
        g.write(f.read())
    ident = "LAYOUT_" + MAPA[4:]
    texto = leer("data/layouts/layouts.json")
    if f'"{ident}"' not in texto:
        texto = co.insertar_en_lista(texto, "layouts", {
            "id": ident, "name": f"{PRADO}_Layout", "width": ancho, "height": alto,
            "primary_tileset": base["primary_tileset"], "secondary_tileset": base["secondary_tileset"],
            "border_filepath": f"data/layouts/{PRADO}/border.bin",
            "blockdata_filepath": f"data/layouts/{PRADO}/map.bin"})
        json.loads(texto)
        escribir("data/layouts/layouts.json", texto)
    raras = aprendiz.revisar(c, ancho, alto, base["secondary_tileset"])
    print(f"Dualocke: PRADO DE HADAS: parejas de piezas que el juego no usa: {len(raras)}")
    return ident


def con_nivel_actual(ruta, texto):
    """Conserva el nivel del guardián que haya puesto reescalar_niveles.py (regla "tope")."""
    if os.path.exists(ruta):
        anterior = re.search(r"setwildbattle (SPECIES_\w+), (\d+)", leer(ruta))
        if anterior:
            texto = re.sub(r"setwildbattle (SPECIES_\w+), \d+", rf"setwildbattle \1, {anterior.group(2)}", texto)
    return texto


def crear_mapa(layout):
    ruta = f"data/maps/{PRADO}/map.json"
    os.makedirs(f"data/maps/{PRADO}", exist_ok=True)
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    gx, gy, _, _, _, flag = GUARDIAN
    objetos = [
        {"local_id": "LOCALID_PRADO_HADAS_GUARDIAN", "graphics_id": "OBJ_EVENT_GFX_VAR_0", "x": gx, "y": gy,
         "elevation": 3, "movement_type": "MOVEMENT_TYPE_FACE_DOWN", "movement_range_x": 0, "movement_range_y": 0,
         "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
         "script": f"{PRADO}_EventScript_Pokemon", "flag": flag},
        {"graphics_id": "OBJ_EVENT_GFX_WOMAN_2", "x": FLORISTA[0], "y": FLORISTA[1], "elevation": 3,
         "movement_type": "MOVEMENT_TYPE_FACE_DOWN", "movement_range_x": 0, "movement_range_y": 0,
         "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
         "script": f"{PRADO}_EventScript_Florista", "flag": "0"}]
    datos = {
        "id": MAPA, "name": PRADO, "layout": layout, "music": "MUS_ROUTE119", "region": "REGION_HOENN",
        "region_map_section": MAPSEC, "requires_flash": False, "weather": "WEATHER_SUNNY",
        "map_type": "MAP_TYPE_ROUTE", "allow_cycling": True, "allow_escaping": False, "allow_running": True,
        "show_map_name": True, "battle_scene": "MAP_BATTLE_SCENE_NORMAL",
        "connections": [{"map": RUTA_MAPA, "offset": -DESPLAZAMIENTO, "direction": "right"}],
        "object_events": objetos + [o for o in anteriores.get("object_events", [])
                                    if str(o.get("flag", "")).startswith("FLAG_ITEM_")],
        "warp_events": [], "coord_events": [],
        "bg_events": [b for b in anteriores.get("bg_events", []) if b.get("type") == "hidden_item"],
    }
    for o in datos["object_events"] + datos["bg_events"]:
        if o.get("flag") in SITIO_OBJETOS:
            o["x"], o["y"] = SITIO_OBJETOS[o["flag"]]
            o["elevation"] = 3
    escribir(ruta, json.dumps(datos, indent=2, ensure_ascii=False) + "\n")
    escribir(f"data/maps/{PRADO}/scripts.inc", con_nivel_actual(f"data/maps/{PRADO}/scripts.inc", SCRIPTS))

    # La RUTA 119 se conecta por la izquierda con el prado
    ruta = f"data/maps/{RUTA}/map.json"
    texto = leer(ruta)
    if MAPA not in texto:
        texto = co.insertar_en_lista(texto, "connections", {"map": MAPA, "offset": DESPLAZAMIENTO,
                                                            "direction": "left"})
        json.loads(texto)
        escribir(ruta, texto)

    grupos = leer("data/maps/map_groups.json")
    if f'"{PRADO}"' not in grupos:
        salto = "\r\n" if "\r\n" in grupos else "\n"
        d = json.loads(grupos)
        grupo = next(g for g in d["group_order"] if RUTA in d[g])
        ultimo = d[grupo][-1]
        a = f'"{ultimo}"{salto}'
        i = grupos.index(a, grupos.index(f'"{grupo}": ['))
        grupos = grupos[:i] + f'"{ultimo}",{salto}    "{PRADO}"{salto}' + grupos[i + len(a):]
        json.loads(grupos)
        escribir("data/maps/map_groups.json", grupos)


def zona_y_cartel():
    """La zona de captura (al final de la lista), el cartel, HOENN_EXTRA_MAPSEC_LAST, el flag del guardián y el
    script en event_scripts.s."""
    ruta = "src/data/region_map/region_map_sections.json"
    texto = leer(ruta)
    if f'"{MAPSEC}"' not in texto:
        secciones = json.loads(texto)["map_sections"]
        r119 = next(s for s in secciones if s["id"] == "MAPSEC_ROUTE_119")
        texto = co.insertar_en_lista(texto, "map_sections", {"id": MAPSEC, "name": NOMBRE,
                                                             "x": r119["x"] - 1, "y": r119["y"],
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
            a = f"    [MAPSEC_CANTERA - KANTO_MAPSEC_COUNT] = {tema}, // Dualocke: zona nueva{salto}"
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
                                                f"// Dualocke: guardián del {NOMBRE} vencido o capturado")
        escribir(ruta, texto)

    ruta = "data/event_scripts.s"
    texto = leer(ruta)
    linea = f'\t.include "data/maps/{PRADO}/scripts.inc" @ Dualocke: zona nueva'
    if linea not in texto:
        salto = "\r\n" if "\r\n" in texto else "\n"
        a = '\t.include "data/maps/Cantera/scripts.inc" @ Dualocke: zona nueva' + salto
        assert texto.count(a) == 1
        texto = texto.replace(a, a + linea + salto)
        escribir(ruta, texto)


_, _, ESPECIE, NIVEL, PREMIO, FLAG = GUARDIAN
SCRIPTS = f"""{PRADO}_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, {PRADO}_OnTransition
	.byte 0

@ Dualocke: el PRADO DE HADAS, al oeste del INSTITUTO METEOROLÓGICO (tools/dualocke/crear_prado_hadas.py).
@ El guardián es un Pokémon fuerte que se puede capturar, como en las islas del ferry
@ (data/scripts/dualocke_islas.inc). Con semilla sale otro fuerte (estaticos.py, islas()).
{PRADO}_OnTransition:
	setvar VAR_0x8004, {ESPECIE}
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

{PRADO}_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, {ESPECIE}
	setvar VAR_TEMP_9, {PREMIO}
	call Dualocke_EventScript_AvisoIsla
	setwildbattle {ESPECIE}, {NIVEL}
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, {PRADO}_EventScript_PokemonSigue
	setflag {FLAG}
	call Dualocke_EventScript_PremioIsla
	release
	end

{PRADO}_EventScript_PokemonSigue::
	release
	end

{PRADO}_EventScript_Florista::
	msgbox {PRADO}_Text_Florista, MSGBOX_NPC
	end

{PRADO}_Text_Florista:
	.string "Vengo a por flores para la tienda,\\n"
	.string "pero aquí hay que andar con cuidado.\\p"
	.string "Los POKéMON hada juegan a esconderte\\n"
	.string "el camino entre la hierba.\\p"
	.string "Junto a la charca grande del norte\\n"
	.string "vive una que protege el prado.$"
"""


def main():
    borde = ruta119()
    crear_mapa(crear_layout(borde))
    zona_y_cartel()
    print("Dualocke: PRADO DE HADAS creado")


if __name__ == "__main__":
    main()
