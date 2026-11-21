#!/usr/bin/env python3
"""
Dualocke: la ISLA DEL DRAGÓN, el bioma del tipo Dragón (PLAN.md, propuesta I; Miguel, 21/11/2026: "alguna isla
para darle una zona propia a los Pokémon tipo dragón, con cascadas o montañas, que le dé un aire épico dirigido a
la última parte del juego").

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_isla_dragon.py

- **Entrada:** surfeando hacia el sur desde el borde de abajo de la RUTA 130 (se alcanza en el **tramo 8**,
  `alcance.py`). La isla empieza en la x 40 de la ruta.
- **ISLA DEL DRAGÓN** (40 × 34): una isla de arena con su bajío, rocas en el mar y tres peñas. En medio, el
  montículo del PILAR CELESTE con su cueva (como en la ISLA VOLCÁNICA): la cueva mira al sur, así que se rodea el
  montículo. Las 8 filas de arriba son mar, que es lo que se ve desde la ruta (gráficos distintos).
- **VALLE DEL DRAGÓN** (40 × 40): la mitad de abajo de CIUDAD COLOSALIA, la de la gran cascada, sin el Centro
  Pokémon ni los carteles. Se llega por la cueva de arriba (la de la CALLE VICTORIA). Una meseta con flores y
  hierba alta, escaleras, el lago de arriba y la gran cascada que cae al mar; para volver a subir hace falta
  CASCADA (tramo 8). El guardián espera en la meseta, frente a la cascada.
- **Guardián:** Haxorus (Miguel, 21/11/2026). Premio, Tabla Draco.
- **Zona de captura propia:** MAPSEC_ISLA_DRAGON (las dos partes cuentan como una).
Los salvajes y los objetos los ponen zonas_nuevas.py y colocar_objetos.py; este script pone los objetos en su
sitio (SITIO_OBJETOS).
"""

import json
import math
import os
import re
import struct
import sys

sys.path.insert(0, "tools/dualocke")
import colocar_objetos as co  # noqa: E402
import crear_islas_sur as islas  # noqa: E402

ISLA, VALLE = "IslaDragon", "IslaDragon_Valle"
MAPAS = {ISLA: "MAP_ISLA_DRAGON", VALLE: "MAP_ISLA_DRAGON_VALLE"}
MAPSEC, NOMBRE = "MAPSEC_ISLA_DRAGON", "ISLA DEL DRAGÓN"
RUTA, RUTA_MAPA, DESPLAZAMIENTO = "Route130", "MAP_ROUTE130", 40
TAM_ISLA = (40, 34)
CENTRO, RADIOS = (20, 19), (15, 9)          # la isla: una elipse de arena con su anillo de bajío
SITIO_MONTICULO = (17, 15)                   # la cueva queda en (20, 19), mirando al sur
PENAS = [(islas.PENA_GRANDE, 7, 16), (islas.PENA_PEQUENA, 25, 14), (islas.PENA_LARGA, 24, 24)]
ROCAS_MAR = [(3, 10), (34, 9), (2, 25), (35, 26), (10, 32), (28, 32)]   # rocas de 2 × 2 en el mar
VALLE_TROZO = ("EverGrandeCity", 40)         # mapa y fila de inicio (40 × 40)
VALLE_CUEVA = (18, 1)                        # la cueva de la CALLE VICTORIA: entrada y salida del valle
VALLE_CENTRO_POKEMON = (26, 5, 30, 9)        # (x0, y0, x1, y1): pasa a ser hierba corta
VALLE_CARTELES = [(19, 3), (18, 12)]
FLORES_COLOSALIA = range(0x288, 0x290)       # las flores de COLOSALIA: las de la izquierda pasan a hierba alta
HIERBA_CORTA, HIERBA_ALTA = 0x27C, 0x00D
GUARDIAN = (19, 7, "SPECIES_HAXORUS", 84, "ITEM_DRACO_PLATE", "FLAG_DUALOCKE_GUARDIAN_DRAGON")
FLAG_GUARDIAN = 0x8FF
SITIO_OBJETOS = {
    "FLAG_ITEM_DRAGON_DRAGON_SCALE": (21, 10),        # en la meseta
    "FLAG_ITEM_DRAGON_DRAGON_FANG": (22, 13),         # oculta, en la meseta de abajo
    "FLAG_ITEM_TICKET_ISLA_DRAGON": (13, 7),          # en la hierba alta de la izquierda
}


def leer(ruta):
    with open(ruta, encoding="utf-8", newline="") as f:
        return f.read()


def escribir(ruta, texto):
    with open(ruta, "w", encoding="utf-8", newline="") as f:
        f.write(texto)


LAYOUTS = co.cargar_layouts()


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


def plano_isla():
    ancho, alto = TAM_ISLA
    (cx, cy), (rx, ry) = CENTRO, RADIOS
    filas = []
    for y in range(alto):
        f = ""
        for x in range(ancho):
            d = math.hypot((x - cx) / rx, (y - cy) / ry)
            f += "s" if d <= 1 else "b" if d <= 1 + 2.2 / ry else "m"
        filas.append(f)
    filas = [list(f) for f in filas]
    # Sin granos sueltos: la arena con menos de dos vecinas de arena pasa a bajío (las puntas de la elipse)
    for y in range(1, alto - 1):
        for x in range(1, ancho - 1):
            if filas[y][x] == "s" and sum(filas[y + dy][x + dx] == "s" for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))) < 2:
                filas[y][x] = "b"
    for x, y in ROCAS_MAR:
        for dy in (0, 1):
            for dx in (0, 1):
                assert filas[y + dy][x + dx] == "m", ("la roca no va en el mar", x, y)
                filas[y + dy][x + dx] = "X"
    return "\n".join("".join(f) for f in filas)


def crear_isla():
    plano = plano_isla()
    filas = plano.splitlines()
    fijas = islas.poner_sellos(filas, PENAS)
    origen, caja, cueva = islas.MONTICULO
    l, cm = islas.celdas_de(origen)
    mx, my = SITIO_MONTICULO
    for (dx, dy), v in islas.sello(origen, caja).items():
        donde = (caja[0] + dx, caja[1] + dy)
        if donde in islas.CIMA_MONTICULO:
            v = (v & ~0x3FF) | islas.CIMA_MONTICULO[donde]
        if donde != islas.PIEDRA_MONTICULO:
            assert (mx + dx, my + dy) not in fijas, "el montículo se pisa con una peña"
            fijas[(mx + dx, my + dy)] = v
    cx, cy = mx + cueva[0] - caja[0], my + cueva[1] - caja[1]
    fijas[(cx, cy)] = cm[cueva[1] * l["width"] + cueva[0]]
    assert all(filas[y][x] == "s" for x, y in fijas), "el montículo o una peña no va sobre arena"
    assert filas[cy + 1][cx] == "s" and (cx, cy + 1) not in fijas, "no se llega a la cueva"
    _, ancho, alto, c = islas.dibujar(plano, fijas)
    # Lo que se ve desde la RUTA 130 (las 8 filas de arriba) son piezas generales
    assert all(c[y * ancho + x] & 0x3FF < 0x200 for y in range(8) for x in range(ancho))
    base = LAYOUTS[json.loads(leer("data/maps/Route134/map.json"))["layout"]]
    return guardar_layout(ISLA, ancho, alto, c, base), (cx, cy)


def crear_valle():
    origen, fila0 = VALLE_TROZO
    l, c = islas.celdas_de(origen)
    w = l["width"]
    alto = l["height"] - fila0
    celdas = list(c[fila0 * w:])
    v = lambda x, y: celdas[y * w + x]  # noqa: E731
    assert v(*VALLE_CUEVA) & 0x3FF == 0x0A7, "la cueva no está donde se pensaba"
    x0, y0, x1, y1 = VALLE_CENTRO_POKEMON
    corta = next(u for u in celdas if u & 0x3FF == HIERBA_CORTA and not (u >> 10) & 3)
    for y in range(y0, y1):
        for x in range(x0, x1):
            celdas[y * w + x] = corta
    for x, y in VALLE_CARTELES:
        assert v(x, y) & 0x3FF == 0x003, ("ahí no hay cartel", x, y)
        celdas[y * w + x] = v(x - 1, y)
    for y in range(alto):
        for x in range(w // 2 - 3):
            u = v(x, y)
            if u & 0x3FF in FLORES_COLOSALIA:
                celdas[y * w + x] = (u & ~0x3FF) | HIERBA_ALTA
    for donde in [GUARDIAN[:2]] + list(SITIO_OBJETOS.values()):
        x, y = donde
        assert not (v(x, y) >> 10) & 3, ("objeto o guardián fuera del suelo", donde)
    return guardar_layout(VALLE, w, alto, celdas, l)


def con_nivel_actual(ruta, texto):
    if os.path.exists(ruta):
        anterior = re.search(r"setwildbattle (SPECIES_\w+), (\d+)", leer(ruta))
        if anterior:
            texto = re.sub(r"setwildbattle (SPECIES_\w+), \d+", rf"setwildbattle \1, {anterior.group(2)}", texto)
    return texto


def mapa_json(carpeta, datos, objetos):
    ruta = f"data/maps/{carpeta}/map.json"
    os.makedirs(f"data/maps/{carpeta}", exist_ok=True)
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    datos["object_events"] = objetos + [o for o in anteriores.get("object_events", [])
                                        if str(o.get("flag", "")).startswith("FLAG_ITEM_")]
    datos["bg_events"] = [b for b in anteriores.get("bg_events", []) if b.get("type") == "hidden_item"]
    datos["coord_events"] = []
    for o in datos["object_events"] + datos["bg_events"]:
        if o.get("flag") in SITIO_OBJETOS:
            o["x"], o["y"] = SITIO_OBJETOS[o["flag"]]
    # Cada cosa a la altura del suelo en el que está (el valle tiene varias alturas)
    l = LAYOUTS[datos["layout"]] if datos["layout"] in LAYOUTS else co.cargar_layouts()[datos["layout"]]
    c = struct.unpack(f"<{l['width'] * l['height']}H", open(l["blockdata_filepath"], "rb").read())
    for o in datos["object_events"] + datos["bg_events"]:
        if isinstance(o.get("x"), int) and "elevation" in o:
            o["elevation"] = c[o["y"] * l["width"] + o["x"]] >> 12
    escribir(ruta, json.dumps(datos, indent=2, ensure_ascii=False) + "\n")


def crear_mapas(l_isla, cueva, l_valle):
    comun = {"region": "REGION_HOENN", "requires_flash": False, "allow_running": True, "show_map_name": True,
             "battle_scene": "MAP_BATTLE_SCENE_NORMAL", "region_map_section": MAPSEC}
    mapa_json(ISLA, {"id": MAPAS[ISLA], "name": ISLA, "layout": l_isla, **comun, "music": "MUS_ROUTE119",
                     "weather": "WEATHER_SUNNY", "map_type": "MAP_TYPE_OCEAN_ROUTE", "allow_cycling": True,
                     "allow_escaping": False,
                     "connections": [{"map": RUTA_MAPA, "offset": -DESPLAZAMIENTO, "direction": "up"}],
                     "warp_events": [{"x": cueva[0], "y": cueva[1], "elevation": 0, "dest_map": MAPAS[VALLE],
                                      "dest_warp_id": "0"}]}, [])
    gx, gy, _, _, _, flag = GUARDIAN
    mapa_json(VALLE, {"id": MAPAS[VALLE], "name": VALLE, "layout": l_valle, **comun, "music": "MUS_EVER_GRANDE",
                      "weather": "WEATHER_NONE", "map_type": "MAP_TYPE_ROUTE", "allow_cycling": True,
                      "allow_escaping": True, "connections": None,
                      "warp_events": [{"x": VALLE_CUEVA[0], "y": VALLE_CUEVA[1], "elevation": 0, "dest_map": MAPAS[ISLA],
                                       "dest_warp_id": "0"}]},
              [{"local_id": "LOCALID_ISLA_DRAGON_GUARDIAN", "graphics_id": "OBJ_EVENT_GFX_VAR_0", "x": gx, "y": gy,
                "elevation": 3, "movement_type": "MOVEMENT_TYPE_FACE_DOWN", "movement_range_x": 0,
                "movement_range_y": 0, "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
                "script": f"{VALLE}_EventScript_Pokemon", "flag": flag}])
    escribir(f"data/maps/{ISLA}/scripts.inc", f"{ISLA}_MapScripts::\n\t.byte 0\n")
    escribir(f"data/maps/{VALLE}/scripts.inc", con_nivel_actual(f"data/maps/{VALLE}/scripts.inc", SCRIPTS))

    ruta = f"data/maps/{RUTA}/map.json"
    texto = leer(ruta)
    if MAPAS[ISLA] not in texto:
        texto = co.insertar_en_lista(texto, "connections", {"map": MAPAS[ISLA], "offset": DESPLAZAMIENTO,
                                                            "direction": "down"})
        json.loads(texto)
        escribir(ruta, texto)

    grupos = leer("data/maps/map_groups.json")
    salto = "\r\n" if "\r\n" in grupos else "\n"
    for carpeta in (ISLA, VALLE):
        if f'"{carpeta}"' in grupos:
            continue
        d = json.loads(grupos)
        grupo = next(g for g in d["group_order"] if RUTA in d[g])
        ultimo = d[grupo][-1]
        a = f'"{ultimo}"{salto}'
        i = grupos.index(a, grupos.index(f'"{grupo}": ['))
        grupos = grupos[:i] + f'"{ultimo}",{salto}    "{carpeta}"{salto}' + grupos[i + len(a):]
    json.loads(grupos)
    escribir("data/maps/map_groups.json", grupos)


def zona_y_cartel():
    ruta = "src/data/region_map/region_map_sections.json"
    texto = leer(ruta)
    if f'"{MAPSEC}"' not in texto:
        secciones = json.loads(texto)["map_sections"]
        r130 = next(s for s in secciones if s["id"] == "MAPSEC_ROUTE_130")
        texto = co.insertar_en_lista(texto, "map_sections", {"id": MAPSEC, "name": NOMBRE,
                                                             "x": r130["x"], "y": r130["y"] + 1,
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
            a = f"    [MAPSEC_PRADO_HADAS - KANTO_MAPSEC_COUNT] = {tema}, // Dualocke: zona nueva{salto}"
            assert texto.count(a) == 1, tema
            texto = texto.replace(a, a + f"    [{MAPSEC} - KANTO_MAPSEC_COUNT] = {tema}, // Dualocke: zona nueva{salto}")
        escribir(ruta, texto)

    ruta = "include/constants/flags.h"
    texto = leer(ruta)
    nombre = GUARDIAN[5]
    if nombre not in texto:
        antigua = re.search(rf"^#define FLAG_UNUSED_0x{FLAG_GUARDIAN:03X}\s+(0x{FLAG_GUARDIAN:X}\b|\(SYSTEM_FLAGS \+ 0x[0-9A-F]+\)).*$",
                            texto, re.M)
        assert antigua, f"el flag 0x{FLAG_GUARDIAN:03X} ya no está libre"
        texto = texto.replace(antigua.group(0), f"#define {nombre:<34} 0x{FLAG_GUARDIAN:03X} "
                                                f"// Dualocke: guardián de la {NOMBRE} vencido o capturado")
        escribir(ruta, texto)

    ruta = "data/event_scripts.s"
    texto = leer(ruta)
    salto = "\r\n" if "\r\n" in texto else "\n"
    anterior = '\t.include "data/maps/PradoHadas/scripts.inc" @ Dualocke: zona nueva'
    for carpeta in (ISLA, VALLE):
        linea = f'\t.include "data/maps/{carpeta}/scripts.inc" @ Dualocke: zona nueva'
        if linea not in texto:
            assert texto.count(anterior + salto) == 1
            texto = texto.replace(anterior + salto, anterior + salto + linea + salto)
        anterior = linea
    escribir(ruta, texto)


_, _, ESPECIE, NIVEL, PREMIO, FLAG = GUARDIAN
SCRIPTS = f"""{VALLE}_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, {VALLE}_OnTransition
	.byte 0

@ Dualocke: el VALLE DEL DRAGÓN, en la ISLA DEL DRAGÓN (tools/dualocke/crear_isla_dragon.py).
@ El guardián es un Pokémon fuerte que se puede capturar, como en las islas del ferry
@ (data/scripts/dualocke_islas.inc). Con semilla sale otro fuerte (estaticos.py, islas()).
{VALLE}_OnTransition:
	setvar VAR_0x8004, {ESPECIE}
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

{VALLE}_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, {ESPECIE}
	setvar VAR_TEMP_9, {PREMIO}
	call Dualocke_EventScript_AvisoIsla
	setwildbattle {ESPECIE}, {NIVEL}
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, {VALLE}_EventScript_PokemonSigue
	setflag {FLAG}
	call Dualocke_EventScript_PremioIsla
	release
	end

{VALLE}_EventScript_PokemonSigue::
	release
	end
"""


def main():
    l_isla, cueva = crear_isla()
    crear_mapas(l_isla, cueva, crear_valle())
    zona_y_cartel()
    print("Dualocke: ISLA DEL DRAGÓN y VALLE DEL DRAGÓN creados")


if __name__ == "__main__":
    main()
