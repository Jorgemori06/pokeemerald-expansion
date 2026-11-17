#!/usr/bin/env python3
"""
Dualocke: las islas de las rutas del sur (ZONAS.md, propuestas 2, 3 y 4; Miguel, 17/11/2026).

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_islas_sur.py

Cada isla es un mapa pegado al borde de una ruta de mar: se surfea hacia fuera de la ruta y se entra sin
pantalla de carga. Usan los mismos gráficos que su ruta (si no, la conexión se vería rota). Todas son del
**tramo 8**. El sitio de cada una se eligió mirando las corrientes: las RUTAS 132-134 tienen los bordes
cerrados por rocas y corrientes que solo empujan al oeste, y el borde este de la RUTA 127 es una pared de
roca, así que dos islas cambian de sitio respecto a ZONAS.md (ver abajo).

- **ISLA DE RUINAS**, al norte de la RUTA 131 (junto al PILAR CELESTE): el islote del PILAR CELESTE
  (SkyPillar_Outside) con su torre, con niebla (Campo de Niebla en combate). La puerta de la torre (abierta)
  lleva a la **TORRE**: la planta 1 del PILAR CELESTE, sin la escalera, con el guardián delante.
- **ISLA VOLCÁNICA**, al sur de la RUTA 134 (donde el mar no tiene corriente): un bajío de la RUTA 134 con
  el montículo de la cueva del PILAR CELESTE en medio. La cueva baja al **CRÁTER**: la cima del MONTE
  CENIZO (lava y terrazas) con ceniza que tiene salvajes, una salida nueva y el guardián. Sol.
- **ISLA ARENOSA**, al este de la RUTA 129 (en ZONAS.md iba al este de la RUTA 127, que está cerrado):
  dos islotes de arena y uno de árboles de la RUTA 127, con hierba alta entre los árboles. Tormenta de arena.

Los islotes se copian con `isla()`: solo las casillas que no son mar y están unidas al islote (así no se
cuelan rocas ni trozos de otras islas). Zonas de captura propias: MAPSEC_ISLA_DE_RUINAS,
MAPSEC_ISLA_VOLCANICA y MAPSEC_ISLA_ARENOSA (cada isla con su interior cuenta como una).
Los entrenadores, los salvajes y los objetos los ponen zonas_nuevas.py y colocar_objetos.py.
"""

import json
import re
import os
import struct
import sys
from collections import deque

sys.path.insert(0, "tools/dualocke")
import colocar_objetos as co  # noqa: E402

RUINAS, TORRE = "IslaDeRuinas", "IslaDeRuinas_Torre"
VOLCAN, CRATER = "IslaVolcanica", "IslaVolcanica_Crater"
ARENOSA = "IslaArenosa"
MAPAS = {RUINAS: "MAP_ISLA_DE_RUINAS", TORRE: "MAP_ISLA_DE_RUINAS_TORRE", VOLCAN: "MAP_ISLA_VOLCANICA",
         CRATER: "MAP_ISLA_VOLCANICA_CRATER", ARENOSA: "MAP_ISLA_ARENOSA"}
MAPSEC = {RUINAS: "MAPSEC_ISLA_DE_RUINAS", TORRE: "MAPSEC_ISLA_DE_RUINAS", VOLCAN: "MAPSEC_ISLA_VOLCANICA",
          CRATER: "MAPSEC_ISLA_VOLCANICA", ARENOSA: "MAPSEC_ISLA_ARENOSA"}
COLISION = 1 << 10

# --- ISLA DE RUINAS ------------------------------------------------------------------------------
RUINAS_TAM = (40, 30)
RUINAS_ISLOTE = ("SkyPillar_Outside", (0, 0, 28, 22), (14, 10), (6, 0))  # mapa, caja, semilla, dónde
PUERTA_TORRE = (14, 5)                       # en SkyPillar_Outside; se abre con los metatiles de la torre abierta
PUERTA_ABIERTA = {(14, 4): 0x2AA, (14, 5): 0x2B2}
# El rellano de la torre está rodeado de acantilados (en el juego se llega por la cueva del montículo).
# Aquí la cueva de la orilla de abajo y la del montículo son un túnel: se entra por una y se sale por la otra.
CUEVA_PILAR, CUEVA_ORILLA = (17, 13), (15, 20)
RUINAS_RUTA, RUINAS_DESPLAZAMIENTO = "MAP_ROUTE131", 15   # la isla empieza en la x 15 de la RUTA 131
TORRE_BASE = "SkyPillar_1F"
ESCALERA_TORRE, PARED_TORRE = (10, 1), (9, 1)
ENTRADA_TORRE = ((6, 13), (7, 13))

# --- ISLA VOLCÁNICA ------------------------------------------------------------------------------
VOLCAN_TAM = (40, 30)
VOLCAN_ISLOTE = ("Route134", (16, 21, 36, 35), (25, 28), (4, 8))
MONTICULO = ("SkyPillar_Outside", (14, 9, 21, 14))   # el montículo con la cueva (17, 13)
SITIO_MONTICULO = (7, 4)                     # dentro del trozo del bajío (tapa la roca del medio)
CRATER_BASE, CRATER_FILAS = "MtChimney", 30   # la cima del MONTE CENIZO, sin la estación del teleférico
PUERTA_CRATER, METATILE_PUERTA = (22, 22), 0x25E   # la entrada de la GUARIDA MAGMA del CAMINO ESCABROSO
SUELO_CRATER, CENIZA = 0x271, 0x207
CENIZA_ZONAS = [(12, 16, 18, 21), (23, 16, 29, 21), (19, 25, 27, 29), (9, 13, 12, 16)]

# --- ISLA ARENOSA --------------------------------------------------------------------------------
ARENOSA_TAM = (56, 40)
ARENOSA_ISLOTES = [("Route127", (43, 13, 67, 27), (54, 20), (8, 2)),
                   ("Route127", (60, 34, 70, 45), (64, 38), (9, 24)),
                   ("Route127", (50, 58, 71, 76), (60, 66), (30, 21))]
BASE_SECRETA = 0x1A8
ARBOLES_ISLOTE = 1                           # el segundo islote: hierba alta entre los árboles

GUARDIANES = {   # mapa: (x, y, especie, nivel sin reescalar, premio, flag)
    TORRE: (10, 2, "SPECIES_METAGROSS", 70, "ITEM_EXPERT_BELT", "FLAG_DUALOCKE_GUARDIAN_ISLA_RUINAS"),
    CRATER: (20, 16, "SPECIES_CHARIZARD", 70, "ITEM_HEAT_ROCK", "FLAG_DUALOCKE_GUARDIAN_VOLCAN"),
    ARENOSA: (41, 26, "SPECIES_SANDY_SHOCKS", 70, "ITEM_SMOOTH_ROCK", "FLAG_DUALOCKE_GUARDIAN_ARENOSA"),
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


COMPORTAMIENTOS = {v: k for k, v in co.comportamientos().items()}
ATRIBUTOS = co.atributos_tilesets()


def comportamiento(layout, metatile):
    if metatile < 512:
        return COMPORTAMIENTOS.get(ATRIBUTOS[layout["primary_tileset"]][metatile])
    return COMPORTAMIENTOS.get(ATRIBUTOS[layout["secondary_tileset"]][metatile - 512])


def mar_de(mapa):
    """El metatile de mar abierto (sin corriente) más común del mapa."""
    l, c = celdas_de(mapa)
    cuenta = {}
    for v in c:
        if comportamiento(l, v & 0x3FF) == "MB_OCEAN_WATER":
            cuenta[v] = cuenta.get(v, 0) + 1
    return max(cuenta, key=cuenta.get)


def isla(celdas, ancho, alto, origen, caja, semilla, sitio, mar):
    """Copia en `celdas` el islote de `origen` que contiene la casilla `semilla`: solo las casillas que no
    son mar y están unidas a ella (sin diagonales). Devuelve {(x, y) en el mapa nuevo: valor}.
    Es mar el mar abierto (`mar`) y las corrientes: las corrientes nunca se copian."""
    l, c = celdas_de(origen)
    w = l["width"]
    mar_origen = mar & 0x3FF
    es_mar = lambda v: (v & 0x3FF) == mar_origen or "CURRENT" in str(comportamiento(l, v & 0x3FF))  # noqa: E731
    x0, y0, x1, y1 = caja
    dentro = lambda x, y: x0 <= x < x1 and y0 <= y < y1 and not es_mar(c[y * w + x])  # noqa: E731
    assert dentro(*semilla), ("la semilla es mar", origen, semilla)
    vistos, cola = {semilla}, deque([semilla])
    while cola:
        x, y = cola.popleft()
        for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if n not in vistos and dentro(*n):
                vistos.add(n)
                cola.append(n)
    copiadas = {}
    for x, y in vistos:
        nx, ny = sitio[0] + x - x0, sitio[1] + y - y0
        assert 0 <= nx < ancho and 0 <= ny < alto, ("el islote no cabe", origen, caja)
        celdas[ny * ancho + nx] = copiadas[(nx, ny)] = c[y * w + x]
    return copiadas


def crear_ruinas():
    ancho, alto = RUINAS_TAM
    mar = mar_de("Route131")
    c = [mar] * (ancho * alto)
    origen, caja, semilla, sitio = RUINAS_ISLOTE
    isla(c, ancho, alto, origen, caja, semilla, sitio, mar)
    _, cp = celdas_de(origen)
    wp = LAYOUTS[json.loads(leer(f"data/maps/{origen}/map.json"))["layout"]]["width"]
    for (x, y), m in PUERTA_ABIERTA.items():
        c[(sitio[1] + y) * ancho + sitio[0] + x] = (cp[y * wp + x] & ~0x3FF) | m
    base = LAYOUTS[json.loads(leer("data/maps/Route131/map.json"))["layout"]]
    return guardar_layout(RUINAS, ancho, alto, c, base)


def crear_torre():
    base, c = celdas_de(TORRE_BASE)
    w = base["width"]
    ex, ey = ESCALERA_TORRE
    px, py = PARED_TORRE
    c[ey * w + ex] = c[py * w + px]
    gx, gy = GUARDIANES[TORRE][:2]
    assert (c[gy * w + gx] >> 10) & 3 == 0, "el guardián de la torre no está en el suelo"
    return guardar_layout(TORRE, w, base["height"], c, base)


def crear_volcan():
    ancho, alto = VOLCAN_TAM
    mar = mar_de("Route134")
    c = [mar] * (ancho * alto)
    origen, caja, semilla, sitio = VOLCAN_ISLOTE
    copiadas = isla(c, ancho, alto, origen, caja, semilla, sitio, mar)
    # El bajío está rodeado de corriente en la RUTA 134: sus bordes (y el mar que se copia) llevan dibujadas
    # las rayas de la corriente. Aquí el mar está en calma: mar liso y bajío liso, como su borde de abajo.
    l134 = LAYOUTS[json.loads(leer(f"data/maps/{origen}/map.json"))["layout"]]
    bajios = [v for v in copiadas.values() if comportamiento(l134, v & 0x3FF) == "MB_SHALLOW_WATER"]
    bajio = max(set(bajios), key=bajios.count)
    for (x, y), v in copiadas.items():
        if comportamiento(l134, v & 0x3FF) == "MB_OCEAN_WATER":
            c[y * ancho + x] = mar
        elif comportamiento(l134, v & 0x3FF) == "MB_SHALLOW_WATER":
            c[y * ancho + x] = bajio
    lm, cm = celdas_de(MONTICULO[0])
    x0, y0, x1, y1 = MONTICULO[1]
    for y in range(y0, y1):
        for x in range(x0, x1):
            nx, ny = sitio[0] + SITIO_MONTICULO[0] + x - x0, sitio[1] + SITIO_MONTICULO[1] + y - y0
            c[ny * ancho + nx] = cm[y * lm["width"] + x]
    base = LAYOUTS[json.loads(leer("data/maps/Route134/map.json"))["layout"]]
    return guardar_layout(VOLCAN, ancho, alto, c, base)


def cueva_volcan():
    """La cueva del montículo en la ISLA VOLCÁNICA (era la (17, 13) del PILAR CELESTE)."""
    sx, sy = VOLCAN_ISLOTE[3]
    mx, my = SITIO_MONTICULO
    return sx + mx + 17 - MONTICULO[1][0], sy + my + 13 - MONTICULO[1][1]


def crear_crater():
    base, c = celdas_de(CRATER_BASE)
    w = base["width"]
    c = c[:w * CRATER_FILAS]
    _, cj = celdas_de("JaggedPass")
    wj = LAYOUTS[json.loads(leer("data/maps/JaggedPass/map.json"))["layout"]]["width"]
    puerta = cj[18 * wj + 16]
    assert puerta & 0x3FF == METATILE_PUERTA
    px, py = PUERTA_CRATER
    assert c[py * w + px] & 0x3FF == 0x274 and c[(py + 1) * w + px] & 0x3FF == SUELO_CRATER, "la puerta no va en la pared"
    c[py * w + px] = (c[py * w + px] & ~0x3FF & ~(3 << 10)) | METATILE_PUERTA
    for x0, y0, x1, y1 in CENIZA_ZONAS:
        for y in range(y0, y1):
            for x in range(x0, x1):
                v = c[y * w + x]
                if v & 0x3FF == SUELO_CRATER and not (v >> 10) & 3:
                    c[y * w + x] = (v & ~0x3FF) | CENIZA
    gx, gy = GUARDIANES[CRATER][:2]
    assert (c[gy * w + gx] >> 10) & 3 == 0, "el guardián del cráter no está en el suelo"
    return guardar_layout(CRATER, w, CRATER_FILAS, c, base)


def crear_arenosa():
    ancho, alto = ARENOSA_TAM
    mar = mar_de("Route129")
    c = [mar] * (ancho * alto)
    for i, (origen, caja, semilla, sitio) in enumerate(ARENOSA_ISLOTES):
        copiadas = isla(c, ancho, alto, origen, caja, semilla, sitio, mar)
        # Las bases secretas: roca lisa (la de su izquierda)
        for (x, y), v in copiadas.items():
            if v & 0x3FF == BASE_SECRETA:
                c[y * ancho + x] = c[y * ancho + x - 1]
        if i == ARBOLES_ISLOTE:
            # Hierba alta en el bajío de dentro del islote (las casillas de bajío rodeadas de islote)
            bajio = max(set(v for v in copiadas.values()), key=list(copiadas.values()).count)
            hierba = 0x00D | (bajio & ~0x3FF & ~(3 << 10))
            for (x, y), v in copiadas.items():
                if v == bajio and all((x + dx, y + dy) in copiadas for dx in (-1, 0, 1) for dy in (-1, 0, 1)):
                    c[y * ancho + x] = hierba
    gx, gy = GUARDIANES[ARENOSA][:2]
    assert (c[gy * ancho + gx] >> 10) & 3 == 0 and c[gy * ancho + gx] != mar, "el guardián de la isla no está en tierra"
    base = LAYOUTS[json.loads(leer("data/maps/Route129/map.json"))["layout"]]
    return guardar_layout(ARENOSA, ancho, alto, c, base)


def mapa_json(carpeta, datos, objetos):
    """map.json con los personajes de este script; conserva los objetos de colocar_objetos.py."""
    ruta = f"data/maps/{carpeta}/map.json"
    os.makedirs(f"data/maps/{carpeta}", exist_ok=True)
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    datos["object_events"] = objetos + [o for o in anteriores.get("object_events", [])
                                        if str(o.get("flag", "")).startswith("FLAG_ITEM_")]
    datos["bg_events"] = [b for b in anteriores.get("bg_events", []) if b.get("type") == "hidden_item"]
    datos["coord_events"] = []
    escribir(ruta, json.dumps(datos, indent=2, ensure_ascii=False) + "\n")


def guardian(carpeta):
    x, y, _, _, _, flag = GUARDIANES[carpeta]
    return {"local_id": f"LOCALID_{MAPAS[carpeta][4:]}_GUARDIAN", "graphics_id": "OBJ_EVENT_GFX_VAR_0",
            "x": x, "y": y, "elevation": 3, "movement_type": "MOVEMENT_TYPE_FACE_DOWN",
            "movement_range_x": 0, "movement_range_y": 0, "trainer_type": "TRAINER_TYPE_NONE",
            "trainer_sight_or_berry_tree_id": "0", "script": f"{carpeta}_EventScript_Pokemon", "flag": flag}


def script_guardian(carpeta, donde):
    _, _, especie, nivel, premio, flag = GUARDIANES[carpeta]
    # El nivel lo pone reescalar_niveles.py (regla "tope"): si el script ya existe, se conserva el suyo.
    # Si no, al volver a lanzar este script después de la cadena de niveles se perdería.
    ruta = f"data/maps/{carpeta}/scripts.inc"
    if os.path.exists(ruta):
        anterior = re.search(rf"setwildbattle {especie}, (\d+)", leer(ruta))
        if anterior:
            nivel = int(anterior.group(1))
    return f"""
@ Dualocke: el guardián de {donde}, un Pokémon fuerte que se puede capturar, como en las islas del
@ ferry (data/scripts/dualocke_islas.inc). Con semilla sale otro de su tipo (estaticos.py, islas()).
{carpeta}_OnTransition:
	setvar VAR_0x8004, {especie}
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

{carpeta}_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, {especie}
	setvar VAR_TEMP_9, {premio}
	call Dualocke_EventScript_AvisoIsla
	setwildbattle {especie}, {nivel}
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, {carpeta}_EventScript_PokemonSigue
	setflag {flag}
	call Dualocke_EventScript_PremioIsla
	release
	end

{carpeta}_EventScript_PokemonSigue::
	release
	end
"""


def cabecera_guardian(carpeta):
    return f"{carpeta}_MapScripts::\n\tmap_script MAP_SCRIPT_ON_TRANSITION, {carpeta}_OnTransition\n\t.byte 0\n"


def crear_mapas(l_ruinas, l_torre, l_volcan, l_crater, l_arenosa):
    comun = {"region": "REGION_HOENN", "requires_flash": False, "allow_running": True, "show_map_name": True,
             "battle_scene": "MAP_BATTLE_SCENE_NORMAL"}
    mar = {"music": "MUS_ROUTE119", "map_type": "MAP_TYPE_OCEAN_ROUTE", "allow_cycling": True,
           "allow_escaping": False}
    dentro = {"music": "MUS_MT_CHIMNEY", "map_type": "MAP_TYPE_UNDERGROUND", "allow_cycling": True,
              "allow_escaping": True}
    sx, sy = RUINAS_ISLOTE[3]
    puerta = (sx + PUERTA_TORRE[0], sy + PUERTA_TORRE[1])
    mapa_json(RUINAS, {"id": MAPAS[RUINAS], "name": RUINAS, "layout": l_ruinas, **mar, **comun,
                       "region_map_section": MAPSEC[RUINAS], "weather": "WEATHER_FOG_HORIZONTAL",
                       "connections": [{"map": RUINAS_RUTA, "offset": -RUINAS_DESPLAZAMIENTO, "direction": "down"}],
                       # 0: la torre; 1 y 2: el túnel entre la cueva de la orilla y la del montículo
                       "warp_events": [{"x": puerta[0], "y": puerta[1], "elevation": 3, "dest_map": MAPAS[TORRE],
                                        "dest_warp_id": "0"},
                                       {"x": sx + CUEVA_ORILLA[0], "y": sy + CUEVA_ORILLA[1], "elevation": 3,
                                        "dest_map": MAPAS[RUINAS], "dest_warp_id": "2"},
                                       {"x": sx + CUEVA_PILAR[0], "y": sy + CUEVA_PILAR[1], "elevation": 3,
                                        "dest_map": MAPAS[RUINAS], "dest_warp_id": "1"}]}, [])
    mapa_json(TORRE, {"id": MAPAS[TORRE], "name": TORRE, "layout": l_torre, **dentro, **comun,
                      "region_map_section": MAPSEC[TORRE], "weather": "WEATHER_NONE", "connections": None,
                      "warp_events": [{"x": x, "y": y, "elevation": 3, "dest_map": MAPAS[RUINAS], "dest_warp_id": "0"}
                                      for x, y in ENTRADA_TORRE]}, [guardian(TORRE)])
    cueva = cueva_volcan()
    mapa_json(VOLCAN, {"id": MAPAS[VOLCAN], "name": VOLCAN, "layout": l_volcan, **mar, **comun,
                       "region_map_section": MAPSEC[VOLCAN], "weather": "WEATHER_DROUGHT",
                       "connections": [{"map": "MAP_ROUTE134", "offset": 0, "direction": "up"}],
                       "warp_events": [{"x": cueva[0], "y": cueva[1], "elevation": 3, "dest_map": MAPAS[CRATER],
                                        "dest_warp_id": "0"}]}, [])
    mapa_json(CRATER, {"id": MAPAS[CRATER], "name": CRATER, "layout": l_crater, **comun,
                       "music": "MUS_MT_CHIMNEY", "map_type": "MAP_TYPE_ROUTE", "allow_cycling": True,
                       "allow_escaping": True,
                       "region_map_section": MAPSEC[CRATER], "weather": "WEATHER_DROUGHT", "connections": None,
                       "warp_events": [{"x": PUERTA_CRATER[0], "y": PUERTA_CRATER[1], "elevation": 3,
                                        "dest_map": MAPAS[VOLCAN], "dest_warp_id": "0"}]}, [guardian(CRATER)])
    mapa_json(ARENOSA, {"id": MAPAS[ARENOSA], "name": ARENOSA, "layout": l_arenosa, **mar, **comun,
                        "region_map_section": MAPSEC[ARENOSA], "weather": "WEATHER_SANDSTORM",
                        "connections": [{"map": "MAP_ROUTE129", "offset": 0, "direction": "left"}],
                        "warp_events": []},
                       [guardian(ARENOSA),
                        {"graphics_id": "OBJ_EVENT_GFX_COOLTRAINER_M", "x": 16, "y": 12, "elevation": 3,
                         "movement_type": "MOVEMENT_TYPE_FACE_RIGHT", "movement_range_x": 0, "movement_range_y": 0,
                         "trainer_type": "TRAINER_TYPE_NORMAL", "trainer_sight_or_berry_tree_id": "4",
                         "script": "IslaArenosa_EventScript_Dario", "flag": "0"}])
    escribir(f"data/maps/{RUINAS}/scripts.inc", f"{RUINAS}_MapScripts::\n\t.byte 0\n")
    escribir(f"data/maps/{VOLCAN}/scripts.inc", f"{VOLCAN}_MapScripts::\n\t.byte 0\n")
    escribir(f"data/maps/{TORRE}/scripts.inc", cabecera_guardian(TORRE) + script_guardian(TORRE, "la ISLA DE RUINAS"))
    escribir(f"data/maps/{CRATER}/scripts.inc", cabecera_guardian(CRATER) + script_guardian(CRATER, "la ISLA VOLCÁNICA"))
    escribir(f"data/maps/{ARENOSA}/scripts.inc", cabecera_guardian(ARENOSA) + script_guardian(ARENOSA, "la ISLA ARENOSA")
             + DARIO)

    # Grupos: las islas con las rutas, los interiores con las mazmorras
    grupos = leer("data/maps/map_groups.json")
    salto = "\r\n" if "\r\n" in grupos else "\n"
    for grupo, carpetas in (("gMapGroup_TownsAndRoutes", (RUINAS, VOLCAN, ARENOSA)), ("gMapGroup_Dungeons", (TORRE, CRATER))):
        for carpeta in carpetas:
            if f'"{carpeta}"' in grupos:
                continue
            d = json.loads(grupos)
            ultimo = d[grupo][-1]
            a = f'"{ultimo}"{salto}'
            i = grupos.index(a, grupos.index(f'"{grupo}": ['))
            grupos = grupos[:i] + f'"{ultimo}",{salto}    "{carpeta}"{salto}' + grupos[i + len(a):]
    json.loads(grupos)
    escribir("data/maps/map_groups.json", grupos)

    # Las rutas se conectan con su isla
    for ruta_mapa, isla_mapa, direccion, desplazamiento in (("Route131", RUINAS, "up", RUINAS_DESPLAZAMIENTO),
                                                           ("Route134", VOLCAN, "down", 0),
                                                           ("Route129", ARENOSA, "right", 0)):
        ruta = f"data/maps/{ruta_mapa}/map.json"
        texto = leer(ruta)
        if MAPAS[isla_mapa] not in texto:
            texto = co.insertar_en_lista(texto, "connections", {"map": MAPAS[isla_mapa], "offset": desplazamiento,
                                                                "direction": direccion})
            json.loads(texto)
            escribir(ruta, texto)


DARIO = """
@ DARÍO es TRAINER_RED, que existía sin usar (zonas_nuevas.py le pone nombre y equipo)
IslaArenosa_EventScript_Dario::
	trainerbattle_single TRAINER_RED, IslaArenosa_Text_DarioIntro, IslaArenosa_Text_DarioDefeat
	msgbox IslaArenosa_Text_DarioPostBattle, MSGBOX_AUTOCLOSE
	end

IslaArenosa_Text_DarioIntro:
	.string "Con esta arena no se ve nada…\\n"
	.string "¡Pero a ti sí te veo!$"

IslaArenosa_Text_DarioDefeat:
	.string "Se me ha metido arena en los ojos.$"

IslaArenosa_Text_DarioPostBattle:
	.string "En el islote de abajo vive un\\n"
	.string "POKéMON enorme. Ten cuidado.$"
"""


def zonas_region():
    ruta = "src/data/region_map/region_map_sections.json"
    texto = leer(ruta)
    secciones = {s["id"]: s for s in json.loads(texto)["map_sections"]}
    r131, r134, r129 = (secciones[f"MAPSEC_ROUTE_{n}"] for n in (131, 134, 129))
    for mapsec, nombre, x, y in (
            ("MAPSEC_ISLA_DE_RUINAS", "ISLA DE RUINAS", r131["x"] + 1, r131["y"] - 1),
            ("MAPSEC_ISLA_VOLCANICA", "ISLA VOLCÁNICA", r134["x"], r134["y"] + 1),
            ("MAPSEC_ISLA_ARENOSA", "ISLA ARENOSA", r129["x"] + r129["width"], r129["y"])):
        assert len(nombre) <= 16, nombre
        if f'"{mapsec}"' not in texto:
            texto = co.insertar_en_lista(texto, "map_sections", {"id": mapsec, "name": nombre, "x": x, "y": y,
                                                                 "width": 1, "height": 1})
    json.loads(texto)
    escribir(ruta, texto)


def main():
    crear_mapas(crear_ruinas(), crear_torre(), crear_volcan(), crear_crater(), crear_arenosa())
    zonas_region()
    print("Dualocke: ISLA DE RUINAS, ISLA VOLCÁNICA e ISLA ARENOSA creadas")


if __name__ == "__main__":
    main()
