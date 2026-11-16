#!/usr/bin/env python3
"""
Dualocke: la ISLA NEVADA, al norte de la RUTA 124 (ZONAS.md, propuesta 1; Miguel, 16/11/2026).

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_isla_nevada.py

- **La isla** (80 × 40): mar como el de la RUTA 124, con el islote grande de la RUTA 125 (el de la
  CUEVA CARDUMEN) y sus bancos de arena pegados arriba. Usa los mismos gráficos que la RUTA 124
  (General + Mossdeep): hace falta para que la conexión se vea bien. Clima: nieve (nieve en combate).
  Se llega surfeando hacia el norte desde la RUTA 124, sin pantalla de carga.
- **La CUEVA HELADA:** la entrada del islote lleva a una cueva de hielo, la sala de hielo de la CUEVA
  CARDUMEN (suelo resbaladizo), con otro contenido.
- **Zona de captura propia:** MAPSEC_ISLA_NEVADA, al final de la lista (las dos partes cuentan como una).
- Los mapas van al final de su grupo y de layouts.json: no se mueve el número de ningún mapa de las
  partidas guardadas.
Los entrenadores, los salvajes y los objetos los ponen zonas_nuevas.py y colocar_objetos.py.
"""

import json
import os
import struct
import sys

sys.path.insert(0, "tools/dualocke")
import colocar_objetos as co  # noqa: E402

ISLA, CUEVA = "IslaNevada", "IslaNevada_Cueva"
MAPA_ISLA, MAPA_CUEVA = "MAP_ISLA_NEVADA", "MAP_ISLA_NEVADA_CUEVA"
MAPSEC = "MAPSEC_ISLA_NEVADA"
ANCHO, ALTO = 80, 40
AGUA = ("Route124", 50, 30)                # casilla de mar abierto de la que se copia el agua
TROZO = ("Route125", 4, 0, 41, 27)         # islote de la CUEVA CARDUMEN y bancos de arena (x 4-40)
DESPLAZAMIENTO = (18, 0)                   # dónde va el trozo en la isla
PUERTA_RUTA125 = (22, 19)                  # la entrada de la cueva en la RUTA 125
BASE_CUEVA = "ShoalCave_LowTideIceRoom"
ENTRADA_CUEVA = (17, 10)                   # la escalera de la sala de hielo


def leer(ruta):
    with open(ruta, encoding="utf-8", newline="") as f:
        return f.read()


def escribir(ruta, texto):
    with open(ruta, "w", encoding="utf-8", newline="") as f:
        f.write(texto)


LAYOUTS = co.cargar_layouts()


def layout_de(carpeta):
    return LAYOUTS[json.loads(leer(f"data/maps/{carpeta}/map.json"))["layout"]]


def celdas_de(carpeta):
    l = layout_de(carpeta)
    return l, list(struct.unpack(f"<{l['width'] * l['height']}H", open(l["blockdata_filepath"], "rb").read()))


def guardar_layout(carpeta, ancho, alto, celdas, base):
    os.makedirs(f"data/layouts/{carpeta}", exist_ok=True)
    with open(f"data/layouts/{carpeta}/map.bin", "wb") as f:
        f.write(struct.pack(f"<{ancho * alto}H", *celdas))
    with open(base["border_filepath"], "rb") as f, open(f"data/layouts/{carpeta}/border.bin", "wb") as g:
        g.write(f.read())
    texto = leer("data/layouts/layouts.json")
    ident = "LAYOUT_" + MAPA_ISLA[4:] if carpeta == ISLA else "LAYOUT_" + MAPA_CUEVA[4:]
    if f'"{ident}"' not in texto:
        texto = co.insertar_en_lista(texto, "layouts", {
            "id": ident, "name": f"{carpeta}_Layout", "width": ancho, "height": alto,
            "primary_tileset": base["primary_tileset"], "secondary_tileset": base["secondary_tileset"],
            "border_filepath": f"data/layouts/{carpeta}/border.bin",
            "blockdata_filepath": f"data/layouts/{carpeta}/map.bin"})
        json.loads(texto)
        escribir("data/layouts/layouts.json", texto)
    return ident


def crear_isla():
    l124, c124 = celdas_de(AGUA[0])
    agua = c124[AGUA[2] * l124["width"] + AGUA[1]]
    celdas = [agua] * (ANCHO * ALTO)
    l125, c125 = celdas_de(TROZO[0])
    _, x0, y0, x1, y1 = TROZO
    dx, dy = DESPLAZAMIENTO
    for y in range(y0, y1):
        for x in range(x0, x1):
            celdas[(y + dy) * ANCHO + (x + dx)] = c125[y * l125["width"] + x]
    return guardar_layout(ISLA, ANCHO, ALTO, celdas, l124)


def crear_cueva():
    base, celdas = celdas_de(BASE_CUEVA)
    return guardar_layout(CUEVA, base["width"], base["height"], celdas, base)


def mapa_json(carpeta, datos):
    ruta = f"data/maps/{carpeta}/map.json"
    os.makedirs(f"data/maps/{carpeta}", exist_ok=True)
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    datos["object_events"] = anteriores.get("object_events", [])
    datos["bg_events"] = anteriores.get("bg_events", [])
    escribir(ruta, json.dumps(datos, indent=2, ensure_ascii=False) + "\n")
    if not os.path.exists(f"data/maps/{carpeta}/scripts.inc"):
        escribir(f"data/maps/{carpeta}/scripts.inc", f"{carpeta}_MapScripts::\n\t.byte 0\n")


def crear_mapas(layout_isla, layout_cueva):
    puerta = (PUERTA_RUTA125[0] + DESPLAZAMIENTO[0], PUERTA_RUTA125[1] + DESPLAZAMIENTO[1])
    comun = {"region": "REGION_HOENN", "region_map_section": MAPSEC, "requires_flash": False,
             "allow_cycling": True, "allow_escaping": False, "allow_running": True, "show_map_name": True}
    mapa_json(ISLA, {
        "id": MAPA_ISLA, "name": ISLA, "layout": layout_isla, "music": "MUS_ROUTE120", **comun,
        "weather": "WEATHER_SNOW", "map_type": "MAP_TYPE_ROUTE", "battle_scene": "MAP_BATTLE_SCENE_NORMAL",
        "connections": [{"map": "MAP_ROUTE124", "offset": 0, "direction": "down"}],
        "warp_events": [{"x": puerta[0], "y": puerta[1], "elevation": 0, "dest_map": MAPA_CUEVA,
                         "dest_warp_id": "0"}],
        "coord_events": []})
    mapa_json(CUEVA, {
        "id": MAPA_CUEVA, "name": CUEVA, "layout": layout_cueva, "music": "MUS_MT_PYRE", **comun,
        "allow_escaping": True,
        "weather": "WEATHER_NONE", "map_type": "MAP_TYPE_UNDERGROUND", "battle_scene": "MAP_BATTLE_SCENE_NORMAL",
        "connections": None,
        "warp_events": [{"x": ENTRADA_CUEVA[0], "y": ENTRADA_CUEVA[1], "elevation": 3, "dest_map": MAPA_ISLA,
                         "dest_warp_id": "0"}],
        "coord_events": []})

    # Grupo: la isla con las rutas (Route124 está en gMapGroup_Routes) y la cueva con las mazmorras
    grupos = leer("data/maps/map_groups.json")
    d = json.loads(grupos)
    salto = "\r\n" if "\r\n" in grupos else "\n"
    for grupo, carpeta in (("gMapGroup_Dungeons", CUEVA), (next(g for g in d["group_order"] if "Route124" in d[g]), ISLA)):
        if f'"{carpeta}"' in grupos:
            continue
        ultimo = d[grupo][-1]
        a = f'"{ultimo}"{salto}'
        i = grupos.index(a, grupos.index(f'"{grupo}": ['))
        grupos = grupos[:i] + f'"{ultimo}",{salto}    "{carpeta}"{salto}' + grupos[i + len(a):]
        d = json.loads(grupos)
    escribir("data/maps/map_groups.json", grupos)

    # La RUTA 124 se conecta hacia arriba con la isla
    ruta = "data/maps/Route124/map.json"
    texto = leer(ruta)
    if MAPA_ISLA not in texto:
        texto = co.insertar_en_lista(texto, "connections", {"map": MAPA_ISLA, "offset": 0, "direction": "up"})
        json.loads(texto)
        escribir(ruta, texto)


def zona_region():
    ruta = "src/data/region_map/region_map_sections.json"
    texto = leer(ruta)
    if f'"{MAPSEC}"' not in texto:
        texto = co.insertar_en_lista(texto, "map_sections", {"id": MAPSEC, "name": "ISLA NEVADA",
                                                             "x": 21, "y": 2, "width": 1, "height": 1})
        json.loads(texto)
        escribir(ruta, texto)


def main():
    crear_mapas(crear_isla(), crear_cueva())
    zona_region()
    print("Dualocke: ISLA NEVADA y CUEVA HELADA creadas")


if __name__ == "__main__":
    main()
