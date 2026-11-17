#!/usr/bin/env python3
"""
Dualocke: el BOSQUE SINIESTRO, al sur de la RUTA 123 (Miguel, 17/11/2026). Primer bioma "por tipo": el tipo
Siniestro no tenía zona propia (solo Poochyena por las rutas). Con Fantasma y Bicho.

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_bosque_siniestro.py

- **Dónde:** se entra andando desde el borde sur de la RUTA 123 (x 103-106), al pie del MONTE PÍRICO, sin
  pantalla de carga. Ahí la RUTA 123 tenía las copas de los árboles del borde: pasan a ser hierba.
  **Tramo 6** (cap 62), el de la RUTA 123.
- **El mapa** (50 × 44), con los gráficos de la RUTA 123 (General + Lilycove) para que la unión se vea bien.
  Bosque cerrado de los árboles normales de Hoenn, a la sombra (`WEATHER_SHADE`) y con la música del MONTE PÍRICO:
  - un sendero baja hasta un primer claro con hierba alta, donde vive una bruja;
  - al este, una charca oscura; al oeste, un callejón;
  - en el centro, un claro grande con un risco que se salta hacia abajo (también se rodea por el este);
  - abajo, el bosque profundo: senderos estrechos, claros de hierba alta y, al fondo, el claro del guardián.
- **Cómo se dibuja:** con letras (PLANO), como las demás zonas; autotile.py pinta la hierba, la hierba alta y la
  charca. Los árboles son los de la RUTA 123, que miden una casilla de ancho:
  - interior del bosque: 0x0C6 y 0x0C7 (se alternan como en la ruta);
  - pie de una franja de árboles (debajo hay suelo): 0x016;
  - la copa del árbol de debajo se pinta en la casilla de hierba de encima, que se puede pisar: 0x00E sobre hierba,
    0x025 sobre hierba alta.
- **Guardián:** sin semilla, Hydreigon (Siniestro/Dragón); premio, Tabla Pavor. `FLAG_DUALOCKE_GUARDIAN_SINIESTRO`.
- **Zona de captura propia:** `MAPSEC_BOSQUE_SINIESTRO`, al final de la lista (117 de 128).
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

BOSQUE, MAPA, MAPSEC = "BosqueSiniestro", "MAP_BOSQUE_SINIESTRO", "MAPSEC_BOSQUE_SINIESTRO"
NOMBRE = "BOSQUE SINIESTRO"
RUTA, RUTA_MAPA = "Route123", "MAP_ROUTE123"
DESPLAZAMIENTO = 82                         # el bosque empieza en la x 82 de la RUTA 123
ENTRADA_RUTA = range(103, 107)              # en la RUTA 123, fila de abajo: copas de árbol que pasan a ser hierba
HIERBA = 0x001
# Los árboles de la RUTA 123 (los normales de Hoenn: autotile.arbol_normal() y copa_normal())
COPA, INTERIOR = at.ARBOL_COPA, at.ARBOL_INTERIOR
RISCO = (0x0D5, 0x087, 0x0D6)               # el risco del BOSQUE PETALIA: punta izquierda, medio, punta derecha
FLORES = 0x004
# T árbol   . hierba   , hierba alta   ~ charca   J risco (se salta hacia abajo)   * flores
PLANO = """
TTTTTTTTTTTTTTTTTTTTT....TTTTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTT....TTTTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTT....TTTTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTT....TTTTTTTTTTTTTTTTTTTTTTTTT
TTT...*TTTTTTTTTTTTTT....TTTTTTTTTTTTT........TTTT
TT.,,,..TTTT..................*TTTTTT..........TTT
TT.,,,,.TT.,,,,,,................TTTT...~~~~~~..TT
TT......T.,,,,,,,,......................~~~~~~..TT
TTT.......,,,,,,,,,.....................~~~~~~..TT
TTTTTTTTTT.,,,,,,................TTTT...~~~~~~..TT
TTTTTTTTTTTT.,,,...............TTTTTTT.........TTT
TTTTTTTTTTTTTTT............TTTTTTTTTTTT......*TTTT
TTTTTTTTTTTTTTTTTTT...TTTTTTTTTTTTTTTTTTT....TTTTT
TTTTTTTTTTTTTTTTTTT...TTTTTTTTTTTTTTTTTTTT..TTTTTT
TTTTTTTTTTTTTTTTTTT...TTTTTTTTTTTTTTTTTTTT..TTTTTT
TTTTTTTTTTTTTTTTTTT...TTTTTTTTTTTTTTTTTTTT..TTTTTT
TTTTTTTTTTTTTTTTTTT...TTTTTTTTTTTTTTTTTTTT..TTTTTT
TTTTTTTT.,,,,,,,...................TTTTTTT..TTTTTT
TTTTTT.,,,,,,,,,,,........,,,,,,,,...TTT.....TTTTT
TTTTTT.,,,,,,,,,,,,......,,,,,,,,,,..........TTTTT
TTTTTT..,,,,,,,,,,........,,,,,,,,,,.........TTTTT
TTTTTTT..,,,,,,............,,,,,,,.....TTT...TTTTT
TTTTTTTT.........................*...TTTTT...TTTTT
TTTTTTTTTT.....................TTTTTTTTTTT...TTTTT
TTTTTTTTTJJJJJJJJJJJJJJJJJJJJJJJTTTTTTTTTT...TTTTT
TTTTTTTTT...,,,,,,,.............TTTTTTTTTT...TTTTT
TTTTTTTT...,,,,,,,,,,..............TTTTTTT...TTTTT
TTTTTTTT.....,,,,,,,...............TTTTTTT...TTTTT
TTTTTTTTTT...TTTTTTTTTTT...TTTTTT............TTTTT
TTTTTTTTTT...TTTTTTTTTTT...TTTTTTT...........TTTTT
TTTTTTTTTT...TTTTTTTTTTT...TTTTTTT..*........TTTTT
TTTTTTTTTT...TTTTTTTTTTT...TTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTT...TTTTTTTTTTT...TTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTT...TTTTTTT.......,,,,,.TTTTTTTTTTTTTTTTT
TTTTTTTTTT...TTTTTT.......,,,,,,,.TTTTTTTTTTTTTTTT
TTTT.,,,,,.......TT........,,,,,,,.TTTTTTTTTTTTTTT
TTT.,,,,,,,.......TT...........*..TTTTTTTTTTTTTTTT
TTT.,,,,,,.......TTTTTTTT..TTTTTTTTTTTTTTTTTTTTTTT
TTTT..........TTTTTTTTTTT..TTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTT..........TTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTT............TTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTT..........TTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
"""
TERRENO = {".": "suelo", "*": "suelo", ",": "hierba_alta", "~": "estanque"}
GUARDIAN = (25, 40, "SPECIES_HYDREIGON", 59, "ITEM_DREAD_PLATE", "FLAG_DUALOCKE_GUARDIAN_SINIESTRO")
FLAG_GUARDIAN = 0x91E
BRUJA = (27, 6)
# Dónde va cada objeto (los pone colocar_objetos.py; aquí se ponen en su sitio, en callejones y claros)
SITIO_OBJETOS = {
    "FLAG_ITEM_SINIESTRO_BLACK_GLASSES": (45, 5),     # junto a la charca
    "FLAG_ITEM_SINIESTRO_MOON_STONE": (4, 36),        # el claro del oeste, en el bosque profundo
    "FLAG_ITEM_SINIESTRO_SPELL_TAG": (32, 35),        # oculto, en el claro del centro
    "FLAG_ITEM_TICKET_BOSQUE_SINIESTRO": (3, 7),      # al fondo del callejón del oeste
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


def ruta123():
    """Abre la entrada en el borde sur de la RUTA 123: las copas (0x00E) pasan a ser hierba. Comprueba que lo
    que hay encima de cada árbol de la fila 0 del bosque es bosque (interior o copa)."""
    l, c = celdas_de(RUTA)
    w, h = l["width"], l["height"]
    y = h - 1
    hierba = next(v for v in c if v & 0x3FF == HIERBA and not (v >> 10) & 3)
    for x in ENTRADA_RUTA:
        v = c[y * w + x]
        assert v & 0x3FF in (COPA, HIERBA), ("la entrada no va donde se pensaba", x, hex(v & 0x3FF))
        c[y * w + x] = hierba
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
    # La fila 0 del bosque sigue a la fila de abajo de la RUTA 123
    for x in range(ancho):
        arriba = borde_ruta[DESPLAZAMIENTO + x]
        if filas[0][x] == "T":
            assert arriba in INTERIOR + (COPA,), ("encima de un árbol del borde hay otra cosa", x, hex(arriba))
        else:
            assert arriba == HIERBA, ("la entrada no coincide con la de la ruta", x, hex(arriba))
    c = [0] * (ancho * alto)
    for y in range(alto):
        for x in range(ancho):
            ch = filas[y][x]
            if ch == "T":
                c[y * ancho + x] = valor(at.arbol_normal(filas, x, y))
                continue
            if ch == "J":
                punta = 0 if filas[y][x - 1] != "J" else 2 if filas[y][x + 1] != "J" else 1
                c[y * ancho + x] = valor(RISCO[punta])
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
    for donde in list(SITIO_OBJETOS.values()) + [BRUJA]:
        x, y = donde
        assert filas[y][x] in ".,*", ("objeto o persona fuera del suelo", donde)

    base = LAYOUTS[json.loads(leer(f"data/maps/{RUTA}/map.json"))["layout"]]
    os.makedirs(f"data/layouts/{BOSQUE}", exist_ok=True)
    with open(f"data/layouts/{BOSQUE}/map.bin", "wb") as f:
        f.write(struct.pack(f"<{ancho * alto}H", *c))
    with open(base["border_filepath"], "rb") as f, open(f"data/layouts/{BOSQUE}/border.bin", "wb") as g:
        g.write(f.read())
    ident = "LAYOUT_" + MAPA[4:]
    texto = leer("data/layouts/layouts.json")
    if f'"{ident}"' not in texto:
        texto = co.insertar_en_lista(texto, "layouts", {
            "id": ident, "name": f"{BOSQUE}_Layout", "width": ancho, "height": alto,
            "primary_tileset": base["primary_tileset"], "secondary_tileset": base["secondary_tileset"],
            "border_filepath": f"data/layouts/{BOSQUE}/border.bin",
            "blockdata_filepath": f"data/layouts/{BOSQUE}/map.bin"})
        json.loads(texto)
        escribir("data/layouts/layouts.json", texto)
    raras = aprendiz.revisar(c, ancho, alto, base["secondary_tileset"])
    print(f"Dualocke: BOSQUE SINIESTRO: parejas de piezas que el juego no usa: {len(raras)}")
    return ident


def con_nivel_actual(ruta, texto):
    """Conserva el nivel del guardián que haya puesto reescalar_niveles.py (regla "tope")."""
    if os.path.exists(ruta):
        anterior = re.search(r"setwildbattle (SPECIES_\w+), (\d+)", leer(ruta))
        if anterior:
            texto = re.sub(r"setwildbattle (SPECIES_\w+), \d+", rf"setwildbattle \1, {anterior.group(2)}", texto)
    return texto


def crear_mapa(layout):
    ruta = f"data/maps/{BOSQUE}/map.json"
    os.makedirs(f"data/maps/{BOSQUE}", exist_ok=True)
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    gx, gy, _, _, _, flag = GUARDIAN
    objetos = [
        {"local_id": "LOCALID_BOSQUE_SINIESTRO_GUARDIAN", "graphics_id": "OBJ_EVENT_GFX_VAR_0", "x": gx, "y": gy,
         "elevation": 3, "movement_type": "MOVEMENT_TYPE_FACE_UP", "movement_range_x": 0, "movement_range_y": 0,
         "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
         "script": f"{BOSQUE}_EventScript_Pokemon", "flag": flag},
        {"graphics_id": "OBJ_EVENT_GFX_HEX_MANIAC", "x": BRUJA[0], "y": BRUJA[1], "elevation": 3,
         "movement_type": "MOVEMENT_TYPE_FACE_DOWN", "movement_range_x": 0, "movement_range_y": 0,
         "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
         "script": f"{BOSQUE}_EventScript_Bruja", "flag": "0"}]
    datos = {
        "id": MAPA, "name": BOSQUE, "layout": layout, "music": "MUS_MT_PYRE_EXTERIOR", "region": "REGION_HOENN",
        "region_map_section": MAPSEC, "requires_flash": False, "weather": "WEATHER_SHADE",
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
    escribir(f"data/maps/{BOSQUE}/scripts.inc", con_nivel_actual(f"data/maps/{BOSQUE}/scripts.inc", SCRIPTS))

    # La RUTA 123 se conecta hacia abajo con el bosque
    ruta = f"data/maps/{RUTA}/map.json"
    texto = leer(ruta)
    if MAPA not in texto:
        texto = co.insertar_en_lista(texto, "connections", {"map": MAPA, "offset": DESPLAZAMIENTO,
                                                            "direction": "down"})
        json.loads(texto)
        escribir(ruta, texto)

    # Grupo: el de la RUTA 123, al final (no cambia el número de ningún mapa)
    grupos = leer("data/maps/map_groups.json")
    if f'"{BOSQUE}"' not in grupos:
        salto = "\r\n" if "\r\n" in grupos else "\n"
        d = json.loads(grupos)
        grupo = next(g for g in d["group_order"] if RUTA in d[g])
        ultimo = d[grupo][-1]
        a = f'"{ultimo}"{salto}'
        i = grupos.index(a, grupos.index(f'"{grupo}": ['))
        grupos = grupos[:i] + f'"{ultimo}",{salto}    "{BOSQUE}"{salto}' + grupos[i + len(a):]
        json.loads(grupos)
        escribir("data/maps/map_groups.json", grupos)


def zona_y_cartel():
    """La zona de captura (al final de la lista), el cartel, HOENN_EXTRA_MAPSEC_LAST, el flag del guardián y el
    script en event_scripts.s."""
    ruta = "src/data/region_map/region_map_sections.json"
    texto = leer(ruta)
    if f'"{MAPSEC}"' not in texto:
        secciones = json.loads(texto)["map_sections"]
        r123 = next(s for s in secciones if s["id"] == "MAPSEC_ROUTE_123")
        texto = co.insertar_en_lista(texto, "map_sections", {"id": MAPSEC, "name": NOMBRE,
                                                             "x": r123["x"] + 2, "y": r123["y"] + 1,
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
        for tema in ("MAPPOPUP_THEME_STONE", "MAPPOPUP_THEME_BW_DEFAULT"):
            a = f"    [MAPSEC_CUMBRE_METEORO - KANTO_MAPSEC_COUNT] = {tema}, // Dualocke: zona nueva{salto}"
            assert texto.count(a) == 1, tema
            nuevo = "MAPPOPUP_THEME_WOOD" if tema == "MAPPOPUP_THEME_STONE" else tema
            texto = texto.replace(a, a + f"    [{MAPSEC} - KANTO_MAPSEC_COUNT] = {nuevo}, // Dualocke: zona nueva{salto}")
        escribir(ruta, texto)

    ruta = "include/constants/flags.h"
    texto = leer(ruta)
    nombre = GUARDIAN[5]
    if nombre not in texto:
        antigua = re.search(rf"^#define FLAG_UNUSED_0x{FLAG_GUARDIAN:03X}\s+\(SYSTEM_FLAGS \+ (0x[0-9A-F]+)\).*$",
                            texto, re.M)
        assert antigua, f"el flag 0x{FLAG_GUARDIAN:03X} ya no está libre"
        texto = texto.replace(antigua.group(0), f"#define {nombre:<44} (SYSTEM_FLAGS + {antigua.group(1)}) "
                                                f"// Dualocke: guardián del {NOMBRE} vencido o capturado")
        escribir(ruta, texto)

    ruta = "data/event_scripts.s"
    texto = leer(ruta)
    linea = f'\t.include "data/maps/{BOSQUE}/scripts.inc" @ Dualocke: zona nueva'
    if linea not in texto:
        salto = "\r\n" if "\r\n" in texto else "\n"
        a = '\t.include "data/maps/CumbreMeteoro/scripts.inc" @ Dualocke: zona nueva' + salto
        assert texto.count(a) == 1
        texto = texto.replace(a, a + linea + salto)
        escribir(ruta, texto)


_, _, ESPECIE, NIVEL, PREMIO, FLAG = GUARDIAN
SCRIPTS = f"""{BOSQUE}_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, {BOSQUE}_OnTransition
	.byte 0

@ Dualocke: el BOSQUE SINIESTRO, al sur de la RUTA 123 (tools/dualocke/crear_bosque_siniestro.py).
@ El guardián es un Pokémon fuerte que se puede capturar, como en las islas del ferry
@ (data/scripts/dualocke_islas.inc). Con semilla sale otro fuerte (estaticos.py, islas()).
{BOSQUE}_OnTransition:
	setvar VAR_0x8004, {ESPECIE}
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

{BOSQUE}_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, {ESPECIE}
	setvar VAR_TEMP_9, {PREMIO}
	call Dualocke_EventScript_AvisoIsla
	setwildbattle {ESPECIE}, {NIVEL}
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, {BOSQUE}_EventScript_PokemonSigue
	setflag {FLAG}
	call Dualocke_EventScript_PremioIsla
	release
	end

{BOSQUE}_EventScript_PokemonSigue::
	release
	end

{BOSQUE}_EventScript_Bruja::
	msgbox {BOSQUE}_Text_Bruja, MSGBOX_NPC
	end

{BOSQUE}_Text_Bruja:
	.string "Aquí abajo nunca llega el sol:\\n"
	.string "es el bosque de la noche.\\p"
	.string "Al fondo hay un claro, y algo\\n"
	.string "muy grande duerme allí…\\p"
	.string "No lo despiertes si no vas\\n"
	.string "preparado. Je, je, je…$"
"""


def main():
    borde = ruta123()
    crear_mapa(crear_layout(borde))
    zona_y_cartel()
    print("Dualocke: BOSQUE SINIESTRO creado")


if __name__ == "__main__":
    main()
