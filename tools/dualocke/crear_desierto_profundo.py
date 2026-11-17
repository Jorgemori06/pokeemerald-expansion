#!/usr/bin/env python3
"""
Dualocke: el DESIERTO PROFUNDO y las RUINAS ARENOSAS (ZONAS.md, propuesta 5 y ruinas; Miguel, 16/11/2026).

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_desierto_profundo.py

- **Entrada:** un montículo con puerta en la parte este del desierto de la RUTA 111, copia del de las
  RUINAS DESIERTO. Se llega con las GAFAS AISLANTES (tramo 5).
- **DESIERTO PROFUNDO** (24 × 68): el desierto de la RUTA 111 (x 16-39, y 30-97), sin la TORRE
  ESPEJISMO ni los huecos de base secreta. Tormenta de arena (tormenta en combate). La puerta del
  montículo de abajo (el de las RUINAS DESIERTO en la RUTA 111) es la salida; en el norte hay otro
  montículo que lleva a las ruinas.
- **RUINAS ARENOSAS:** las cuatro plantas de la TORRE ESPEJISMO: la entrada, dos plantas con suelo
  agrietado (si se rompe, caes a la de abajo; en la tercera hay rocas de GOLPE ROCA) y la CÁMARA,
  la sala del fósil, donde está el guardián: un Pokémon fuerte que se puede capturar (como en las
  islas del ferry, data/scripts/dualocke_islas.inc).
- **Zonas de captura propias:** MAPSEC_DESIERTO_PROFUNDO y MAPSEC_RUINAS_ARENOSAS, al final de la lista.
- Los mapas van al final de su grupo y de layouts.json.
Los entrenadores, los salvajes y los objetos los ponen zonas_nuevas.py y colocar_objetos.py.
"""

import json
import os
import struct
import sys

sys.path.insert(0, "tools/dualocke")
import colocar_objetos as co  # noqa: E402

DESIERTO, RUINAS, CAMARA = "DesiertoProfundo", "RuinasArenosas", "RuinasArenosas_Camara"
PLANTA2, PLANTA3 = "RuinasArenosas_2F", "RuinasArenosas_3F"
MAPAS = {DESIERTO: "MAP_DESIERTO_PROFUNDO", RUINAS: "MAP_RUINAS_ARENOSAS", CAMARA: "MAP_RUINAS_ARENOSAS_CAMARA",
         PLANTA2: "MAP_RUINAS_ARENOSAS_2F", PLANTA3: "MAP_RUINAS_ARENOSAS_3F"}
# Plantas con suelo agrietado: como en la TORRE ESPEJISMO, al romperse caes a la planta de abajo
AGUJEROS = """{carpeta}_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_TRANSITION, CaveHole_FixCrackedGround
	map_script MAP_SCRIPT_ON_RESUME, {carpeta}_SetHoleWarp
	.byte 0

@ Dualocke: RUINAS ARENOSAS (tools/dualocke/crear_desierto_profundo.py). Si el suelo se rompe, caes abajo
{carpeta}_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp {abajo}
	end
"""
CAJA = (16, 30, 40, 98)                  # trozo de la RUTA 111 (x0, y0, x1, y1)
TORRE = range(0x3D8, 0x3F3)              # metatiles de la TORRE ESPEJISMO
ARENA = 0x251                            # arena lisa del desierto
BASE_SECRETA = 0x1A8                     # hueco de base secreta en la roca
MONTICULO = (27, 84, 32, 88)             # montículo con puerta de las RUINAS DESIERTO en la RUTA 111
PUERTA_MONTICULO = (2, 3)                # la puerta dentro del montículo
SITIO_RUTA111 = (31, 76)                 # dónde va el montículo nuevo en la RUTA 111
SITIO_RUINAS = (10, 8)                   # dónde va el montículo de las ruinas en el DESIERTO PROFUNDO


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


def monticulo(c111, w111):
    x0, y0, x1, y1 = MONTICULO
    return [[c111[y * w111 + x] for x in range(x0, x1)] for y in range(y0, y1)]


def estampar(celdas, ancho, bloque, x0, y0):
    for dy, fila in enumerate(bloque):
        for dx, v in enumerate(fila):
            celdas[(y0 + dy) * ancho + x0 + dx] = v


def crear_desierto():
    l111, c111 = celdas_de("Route111")
    w111 = l111["width"]
    x0, y0, x1, y1 = CAJA
    ancho, alto = x1 - x0, y1 - y0
    celdas = [c111[y * w111 + x] for y in range(y0, y1) for x in range(x0, x1)]
    # Si ya se lanzó, la RUTA 111 tiene el montículo nuevo dentro de la caja: en el desierto, arena
    sx, sy = SITIO_RUTA111[0] - x0, SITIO_RUTA111[1] - y0
    mx0, my0, mx1, my1 = MONTICULO
    bloque = monticulo(c111, w111)
    if all(c111[(SITIO_RUTA111[1] + dy) * w111 + SITIO_RUTA111[0] + dx] == bloque[dy][dx]
           for dy in range(my1 - my0) for dx in range(mx1 - mx0)):
        for dy in range(my1 - my0):
            for dx in range(mx1 - mx0):
                celdas[(sy + dy) * ancho + sx + dx] = ARENA | (3 << 12)
    for i, v in enumerate(celdas):
        if (v & 0x3FF) in TORRE:
            celdas[i] = ARENA | (3 << 12)
        elif (v & 0x3FF) == BASE_SECRETA:
            celdas[i] = celdas[i - 1]
    estampar(celdas, ancho, monticulo(c111, w111), *SITIO_RUINAS)
    return guardar_layout(DESIERTO, ancho, alto, celdas, l111), (ancho, alto)


def copiar_layout(carpeta, base_mapa):
    base, celdas = celdas_de(base_mapa)
    return guardar_layout(carpeta, base["width"], base["height"], celdas, base)


def mapa_json(carpeta, datos):
    ruta = f"data/maps/{carpeta}/map.json"
    os.makedirs(f"data/maps/{carpeta}", exist_ok=True)
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    datos["object_events"] = anteriores.get("object_events", [])
    datos["bg_events"] = anteriores.get("bg_events", [])
    escribir(ruta, json.dumps(datos, indent=2, ensure_ascii=False) + "\n")
    if not os.path.exists(f"data/maps/{carpeta}/scripts.inc"):
        escribir(f"data/maps/{carpeta}/scripts.inc", f"{carpeta}_MapScripts::\n\t.byte 0\n")


def puerta_en(x, y):
    return x + PUERTA_MONTICULO[0], y + PUERTA_MONTICULO[1]


def crear_mapas(layout_desierto, layout_ruinas, layout_camara, layout_2f, layout_3f):
    salida = (MONTICULO[0] + PUERTA_MONTICULO[0] - CAJA[0], MONTICULO[1] + PUERTA_MONTICULO[1] - CAJA[1])
    a_ruinas = puerta_en(*SITIO_RUINAS)
    comun = {"region": "REGION_HOENN", "requires_flash": False, "allow_cycling": True, "allow_escaping": True,
             "allow_running": True, "show_map_name": True, "battle_scene": "MAP_BATTLE_SCENE_NORMAL",
             "connections": None, "coord_events": []}
    mapa_json(DESIERTO, {
        "id": MAPAS[DESIERTO], "name": DESIERTO, "layout": layout_desierto, "music": "MUS_ROUTE110",
        "region_map_section": "MAPSEC_DESIERTO_PROFUNDO", "weather": "WEATHER_SANDSTORM",
        "map_type": "MAP_TYPE_ROUTE", **comun,
        "warp_events": [
            {"x": salida[0], "y": salida[1], "elevation": 0, "dest_map": "MAP_ROUTE111", "dest_warp_id": "5"},
            {"x": a_ruinas[0], "y": a_ruinas[1], "elevation": 0, "dest_map": MAPAS[RUINAS], "dest_warp_id": "0"}]})
    mapa_json(RUINAS, {
        "id": MAPAS[RUINAS], "name": RUINAS, "layout": layout_ruinas, "music": "MUS_MT_CHIMNEY",
        "region_map_section": "MAPSEC_RUINAS_ARENOSAS", "weather": "WEATHER_NONE",
        "map_type": "MAP_TYPE_UNDERGROUND", **comun,
        "warp_events": [
            {"x": 10, "y": 14, "elevation": 3, "dest_map": MAPAS[DESIERTO], "dest_warp_id": "1"},
            {"x": 15, "y": 2, "elevation": 3, "dest_map": MAPAS[PLANTA2], "dest_warp_id": "1"}]})
    # Las dos plantas de en medio: mismas escaleras que en la TORRE ESPEJISMO
    for carpeta, layout, abajo, warps in (
            (PLANTA2, layout_2f, MAPAS[RUINAS],
             [{"x": 18, "y": 12, "elevation": 3, "dest_map": MAPAS[PLANTA3], "dest_warp_id": "0"},
              {"x": 15, "y": 2, "elevation": 3, "dest_map": MAPAS[RUINAS], "dest_warp_id": "1"}]),
            (PLANTA3, layout_3f, MAPAS[PLANTA2],
             [{"x": 18, "y": 12, "elevation": 3, "dest_map": MAPAS[PLANTA2], "dest_warp_id": "0"},
              {"x": 2, "y": 4, "elevation": 3, "dest_map": MAPAS[CAMARA], "dest_warp_id": "0"}])):
        if not os.path.exists(f"data/maps/{carpeta}/scripts.inc"):
            os.makedirs(f"data/maps/{carpeta}", exist_ok=True)
            escribir(f"data/maps/{carpeta}/scripts.inc", AGUJEROS.format(carpeta=carpeta, abajo=abajo))
        mapa_json(carpeta, {
            "id": MAPAS[carpeta], "name": carpeta, "layout": layout, "music": "MUS_MT_CHIMNEY",
            "region_map_section": "MAPSEC_RUINAS_ARENOSAS", "weather": "WEATHER_NONE",
            "map_type": "MAP_TYPE_UNDERGROUND", **comun, "warp_events": warps})
    # Las rocas de GOLPE ROCA de la planta 3, como en la torre
    ruta = f"data/maps/{PLANTA3}/map.json"
    if "OBJ_EVENT_GFX_BREAKABLE_ROCK" not in leer(ruta):
        texto = leer(ruta)
        for o in json.loads(leer("data/maps/MirageTower_3F/map.json"))["object_events"]:
            texto = co.insertar_en_lista(texto, "object_events", o)
        json.loads(texto)
        escribir(ruta, texto)
    mapa_json(CAMARA, {
        "id": MAPAS[CAMARA], "name": CAMARA, "layout": layout_camara, "music": "MUS_MT_CHIMNEY",
        "region_map_section": "MAPSEC_RUINAS_ARENOSAS", "weather": "WEATHER_NONE",
        "map_type": "MAP_TYPE_UNDERGROUND", **comun,
        "warp_events": [{"x": 1, "y": 4, "elevation": 3, "dest_map": MAPAS[PLANTA3], "dest_warp_id": "1"}]})

    grupos = leer("data/maps/map_groups.json")
    salto = "\r\n" if "\r\n" in grupos else "\n"
    for carpeta in (DESIERTO, RUINAS, CAMARA, PLANTA2, PLANTA3):
        if f'"{carpeta}"' in grupos:
            continue
        d = json.loads(grupos)
        ultimo = d["gMapGroup_Dungeons"][-1]
        a = f'"{ultimo}"{salto}'
        i = grupos.index(a, grupos.index('"gMapGroup_Dungeons": ['))
        grupos = grupos[:i] + f'"{ultimo}",{salto}    "{carpeta}"{salto}' + grupos[i + len(a):]
    json.loads(grupos)
    escribir("data/maps/map_groups.json", grupos)


def entrada_ruta111():
    l111, c111 = celdas_de("Route111")
    w = l111["width"]
    x, y = SITIO_RUTA111
    estampar(c111, w, monticulo(c111, w), x, y)
    with open(l111["blockdata_filepath"], "wb") as f:
        f.write(struct.pack(f"<{w * l111['height']}H", *c111))
    ruta = "data/maps/Route111/map.json"
    texto = leer(ruta)
    if MAPAS[DESIERTO] not in texto:
        px, py = puerta_en(x, y)
        texto = co.insertar_en_lista(texto, "warp_events", {"x": px, "y": py, "elevation": 0,
                                                            "dest_map": MAPAS[DESIERTO], "dest_warp_id": "0"})
        json.loads(texto)
        escribir(ruta, texto)
    # La salida del DESIERTO PROFUNDO vuelve a este montículo: comprobar que es el warp 5
    warps = json.loads(leer(ruta))["warp_events"]
    assert warps[5]["dest_map"] == MAPAS[DESIERTO], "el warp de la RUTA 111 no es el 5"


def zonas_region():
    ruta = "src/data/region_map/region_map_sections.json"
    texto = leer(ruta)
    for mapsec, nombre, y in (("MAPSEC_DESIERTO_PROFUNDO", "DESIERTO PROFUNDO", 3),
                              ("MAPSEC_RUINAS_ARENOSAS", "RUINAS ARENOSAS", 2)):
        if f'"{mapsec}"' not in texto:
            texto = co.insertar_en_lista(texto, "map_sections", {"id": mapsec, "name": nombre,
                                                                 "x": 9, "y": y, "width": 1, "height": 1})
    json.loads(texto)
    escribir(ruta, texto)


def main():
    layout_desierto, _ = crear_desierto()
    crear_mapas(layout_desierto, copiar_layout(RUINAS, "MirageTower_1F"), copiar_layout(CAMARA, "MirageTower_4F"),
                copiar_layout(PLANTA2, "MirageTower_2F"), copiar_layout(PLANTA3, "MirageTower_3F"))
    entrada_ruta111()
    zonas_region()
    print("Dualocke: DESIERTO PROFUNDO y RUINAS ARENOSAS creados")


if __name__ == "__main__":
    main()
