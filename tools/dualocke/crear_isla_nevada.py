#!/usr/bin/env python3
"""
Dualocke: la ISLA NEVADA, al norte de la RUTA 124 (ZONAS.md, propuesta 1; Miguel, 16/11/2026).

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_isla_nevada.py

- **La isla** (80 × 40): una isla grande de arena con su anillo de bajío y una cala al sur. Arriba, la
  cresta de roca de la RUTA 127, con la entrada de la cueva; alrededor, peñas y rocas en el mar. Usa los
  mismos gráficos que la RUTA 124 (General + Mossdeep): hace falta para que la conexión se vea bien.
  Clima: nieve (nieve en combate). Se llega surfeando hacia el norte desde la RUTA 124, sin pantalla de carga.
  **Rehecha el 17/11/2026** con autotile.py, como las islas del sur (crear_islas_sur.py): antes era el islote
  de la CUEVA CARDUMEN de la RUTA 125 pegado arriba, cortado por el borde del mapa.
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
import crear_islas_sur as cis  # noqa: E402  (dibujar(), sello() y las peñas de la RUTA 127)

ISLA, CUEVA = "IslaNevada", "IslaNevada_Cueva"
MAPA_ISLA, MAPA_CUEVA = "MAP_ISLA_NEVADA", "MAP_ISLA_NEVADA_CUEVA"
MAPSEC = "MAPSEC_ISLA_NEVADA"
ANCHO, ALTO = 80, 40
# m mar   b bajío   s arena   X roca de mar   W roca con remolino (como en crear_islas_sur.py)
PLANO = """
mmmmmmmmmmmmmmmmmmWWmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmWWmmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmWWmmmmmmmmbbbbbbbbbbbbbbbbbbbbbmmmmmmmmmWWmmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmmmmmbbbbbbbbbbbbbbbbbbbbbbbbbbbbbmmmmmmmmmmXXmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmmmbbbbbbbbsssssssssssssssssbbbbbbbbbmmmmmmmXXmmmmmmmmmmmmmmm
mmmmmmmmmmXXmmmmmmmmbbbbbbsssssssssssssssssssssssssbbbbbbbbmmmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmXXmmmmmmmbbbbbssssssssssssssssssssssssssssssbbbbbbbmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmbbbbsssssssssssssssssssssssssssssssssssbbbbbmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmbbbbssssssssssssssssssssssssssssssssssssssbbbbmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmbbbssssssssssssssssssssssssssssssssssssssssbbbbmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmbbbssssssssssssssssssssssssssssssssssssssssssbbbmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmbbbbsssssssssssssssssssssssssssssssssssssssssssbbmmmmmmXXmmmmmmmm
mmmmXXmmmmmmbbbbbbssssssssssssssssssssssssssssssssssssssssssssbbmmmmmmXXmmmmmmmm
mmmmXXmmmmbbbbbbbsssssssssssssssssssssssssssssssssssssssssssssbbmmmmmmmmmmmmmmmm
mmmmmmmmmmbbbbssssssssssssssssssssssssssssssssssssssssssssssssbbmmmmmmmmmmmmmmmm
mmmmmmmmmmbbsssssssssssssssssssssssssssssssssssssssssssssssssbbbmmmmmmmmmmmmmmmm
mmmmmmmmmmbbsssssssssssssssssssssssssssssssssssssssssssssssssbbbmmmmmmmmmWWmmmmm
mmmmmmmmmmbbbssssssssssssssssssssssssssssssssssssssssssssssssbbmmmmmmmmmmWWmmmmm
mmmmmmmmmmbbbbbssssssssssssssssssssssssssssssssssssssssssssssbbmmmmmmmmmmmmmmmmm
mmmmmmmmmmmbbbbbbbssssssssssssssssssssssssssssssssssssssssssbbbmmmmmXXmmmmmmmmmm
mmmmmmmmmmmmmbbbbbbssssssssssssssssssssssssssssssssssssssssbbbbmmmmmXXmmmmmmmmmm
mmmmmmXXmmmmmmmmbbbbssssssssssssssssssssssssssssssssssssssbbbbmmmmmmmmmmmmmmmmmm
mmmmmmXXmmmmmmmmmbbbsssssssssssssssssbbbbssssssssssssssssbbbbmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmbbbssssssssssssssssbbbbbssssssssssssssbbbbmmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmbbbbsssssssssssssssbbbbbbssssssssssssbbbbmmmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmbbbbbsssssssssssssbbbbbbssssssssssbbbbbmmmmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmbbbbbbsssssssssssbbbbbbbsssssssbbbbbbmmmmmmmmmmmmmmmmmXXmmmm
mmmmmmmmmmmmmmmmmmmmmmbbbbbbbssssssssbbbbbbbssssbbbbbbbmmmmmmmmmmmmmmmmmmmXXmmmm
mmmmmmmmmmmmmmmmmmmmmmmmbbbbbbbbsssssbbbbbbbsbbbbbbbbmmmmmmmmmmmXXmmmmmmmmmmmmmm
mmmWWmmmmmmmmXXmmmmmmmmmmmmbbbbbbbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmXXmmmmmmmmmmmmmm
mmmWWmmmmmmmmXXmmmmmmmmmmmmmmmbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmWWmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmmmmmXXmmmmmmWWmmmmmmmmmmmmmmmmmmXXmmmmmmWWmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmmmmmXXmmmmmmWWmmmmmmmmmmmmmmmmmmXXmmmmmmmmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmXXmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmXXmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
"""
# La cresta de roca del islote grande de la RUTA 127 (se copian solo sus casillas de roca; sus dos huecos de
# base secreta se tapan). En su pie se abre la cueva, con las piezas de la cueva del PILAR CELESTE.
CRESTA = ("Route127", (43, 15, 65, 26))
ROCAS_DEL_MAR = (55, 24)                   # desde aquí (abajo a la derecha) son rocas del mar: no se copian
SITIO_CRESTA = (27, 3)
CUEVA_CRESTA = {(56, 21): 0x064, (54, 22): 0x0A9, (55, 22): 0x0A9, (56, 22): 0x0A7, (57, 22): 0x0A9,
                (58, 22): 0x0A9}         # en la RUTA 127; la cueva es (56, 22)
PENAS = [(cis.PENA_GRANDE, 46, 14), (cis.PENA_PEQUENA, 24, 16), (cis.PENA_LARGA, 50, 6)]
# Dónde va cada uno (antes estaban por el mar de alrededor del islote copiado)
SITIOS = {"IslaNevada_EventScript_Dudley": (14, 31), "IslaNevada_EventScript_Kaylee": (58, 30),
          "FLAG_ITEM_NEVADA_SNOWBALL": (16, 15)}
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


def puerta_cueva():
    x0, y0 = CRESTA[1][:2]
    cx, cy = next(p for p, m in CUEVA_CRESTA.items() if m == 0x0A7)
    return SITIO_CRESTA[0] + cx - x0, SITIO_CRESTA[1] + cy - y0


def crear_isla():
    filas = PLANO.strip().splitlines()
    assert (len(filas[0]), len(filas)) == (ANCHO, ALTO)
    fijas = cis.poner_sellos(filas, PENAS)
    origen, caja = CRESTA
    _, cr = celdas_de(origen)
    w = layout_de(origen)["width"]
    sx, sy = SITIO_CRESTA
    for (dx, dy), v in cis.sello(origen, caja).items():
        if caja[0] + dx >= ROCAS_DEL_MAR[0] and caja[1] + dy >= ROCAS_DEL_MAR[1]:
            continue
        fijas[(sx + dx, sy + dy)] = v
    for (x, y), m in CUEVA_CRESTA.items():
        v = cr[y * w + x]
        if m == 0x0A7:
            v &= ~(3 << 10)            # la cueva se pisa
        fijas[(sx + x - caja[0], sy + y - caja[1])] = (v & ~0x3FF) | m
    assert all(filas[y][x] == "s" for x, y in fijas), "la cresta o una peña no va sobre arena"
    px, py = puerta_cueva()
    assert filas[py + 1][px] == "s" and (px, py + 1) not in fijas, "no se llega a la cueva"
    _, ancho, alto, c = cis.dibujar(PLANO, fijas)
    for donde in SITIOS.values():
        x, y = donde
        assert not (c[y * ancho + x] >> 10) & 3, ("sitio bloqueado", donde)
    return guardar_layout(ISLA, ancho, alto, c, layout_de("Route124"))


def crear_cueva():
    base, celdas = celdas_de(BASE_CUEVA)
    return guardar_layout(CUEVA, base["width"], base["height"], celdas, base)


def mapa_json(carpeta, datos):
    ruta = f"data/maps/{carpeta}/map.json"
    os.makedirs(f"data/maps/{carpeta}", exist_ok=True)
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    datos["object_events"] = anteriores.get("object_events", [])
    datos["bg_events"] = anteriores.get("bg_events", [])
    for o in datos["object_events"] + datos["bg_events"]:
        clave = o.get("script") if o.get("script") in SITIOS else o.get("flag")
        if clave in SITIOS:
            o["x"], o["y"] = SITIOS[clave]
    escribir(ruta, json.dumps(datos, indent=2, ensure_ascii=False) + "\n")
    if not os.path.exists(f"data/maps/{carpeta}/scripts.inc"):
        escribir(f"data/maps/{carpeta}/scripts.inc", f"{carpeta}_MapScripts::\n\t.byte 0\n")


def crear_mapas(layout_isla, layout_cueva):
    puerta = puerta_cueva()
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
