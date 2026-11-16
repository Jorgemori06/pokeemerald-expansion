#!/usr/bin/env python3
"""
Dualocke: la GRUTA ÍGNEA, debajo del SENDERO ÍGNEO (ZONAS.md, propuesta 7; Miguel, 16/11/2026).

Uso (desde la raíz del repo; solo hace falta una vez, y se puede volver a lanzar):
    python3 tools/dualocke/crear_gruta_ignea.py

Qué hace:
- **El mapa:** parte de la planta 4 de la GUARIDA MAGMA (mismos gráficos que el SENDERO ÍGNEO,
  59 × 28, con el lago de lava) y quita las máquinas del Equipo Magma: cada casilla de máquina pasa
  a ser el suelo de al lado. La puerta del noreste es la entrada; la otra salida se tapa.
  Escribe data/layouts/GrutaIgnea/ y lo añade al final de layouts.json y del grupo de mapas
  gMapGroup_Dungeons (al final, para no mover los números de los mapas de las partidas guardadas).
- **La entrada:** una boca de cueva en la sala del suroeste del SENDERO ÍGNEO, la de detrás de las
  rocas de FUERZA (así se llega con la 4.ª medalla: tramo 5).
- **Zona del mapa de la región:** MAPSEC_GRUTA_IGNEA, al final de la lista (zona de captura propia,
  sin mover los bits de las demás).
Los entrenadores, los salvajes y los objetos los ponen zonas_nuevas.py y colocar_objetos.py.
"""

import json
import os
import struct
import sys

sys.path.insert(0, "tools/dualocke")
import colocar_objetos as co  # noqa: E402

CARPETA = "GrutaIgnea"
MAPA = "MAP_GRUTA_IGNEA"
LAYOUT = "LAYOUT_GRUTA_IGNEA"
MAPSEC = "MAPSEC_GRUTA_IGNEA"
BASE = "MagmaHideout_4F"
MAQUINAS = set(range(0x35C, 0x39E)) | {0x3A8, 0x3A9}   # depósitos, ordenadores, taladros y el pedestal
SUELO = 0x3A2                    # suelo de cueva de la guarida
PARED_ABAJO = 0x30C              # borde de abajo de una pared
# La salida hacia la planta 3 de la guarida: la flecha pasa a ser suelo y la boca, pared
SALIDA_TAPADA = [((20, 21), SUELO, 0), ((19, 22), PARED_ABAJO, 1), ((20, 22), PARED_ABAJO, 1),
                 ((21, 22), PARED_ABAJO, 1)]
PUERTA = (46, 7)                 # entrada desde el SENDERO ÍGNEO
# Boca de cueva en el SENDERO ÍGNEO: la flecha y las tres casillas de la boca (como la salida del sur)
BOCA_FLECHA = (7, 34)
BOCA = [((6, 35), 0x20D), ((7, 35), 0x20E), ((8, 35), 0x20F)]
FLECHA = 0x309


def leer(ruta):
    with open(ruta, encoding="utf-8", newline="") as f:
        return f.read()


def escribir(ruta, texto):
    with open(ruta, "w", encoding="utf-8", newline="") as f:
        f.write(texto)


def layout_de(carpeta):
    layouts = co.cargar_layouts()
    m = json.loads(leer(f"data/maps/{carpeta}/map.json"))
    return layouts[m["layout"]]


def crear_layout():
    base = layout_de(BASE)
    w, h = base["width"], base["height"]
    celdas = list(struct.unpack(f"<{w * h}H", open(base["blockdata_filepath"], "rb").read()))

    def es_maquina(v):
        return (v & 0x3FF) in MAQUINAS

    # Solo se rellena con suelo de cueva (no con tablas del puente ni bordes de lava)
    mb = {v: k for k, v in co.comportamientos().items()}
    atributos = co.atributos_tilesets()
    prim, sec = atributos[base["primary_tileset"]], atributos[base["secondary_tileset"]]

    def es_suelo(v):
        mt = v & 0x3FF
        a = prim[mt] if mt < 512 else sec[mt - 512]
        return (v >> 10) & 3 == 0 and mb.get(a & 0xFF) == "MB_CAVE" and not es_maquina(v)

    # Cada máquina pasa a ser el suelo transitable más repetido a su alrededor (varias pasadas,
    # porque las máquinas ocupan 2 × 3 casillas)
    for _ in range(6):
        cambios = {}
        for i, v in enumerate(celdas):
            if not es_maquina(v):
                continue
            x, y = i % w, i // w
            vecinos = [celdas[ny * w + nx] for nx, ny in ((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1),
                                                          (x - 1, y - 1), (x + 1, y + 1), (x - 1, y + 1), (x + 1, y - 1))
                       if 0 <= nx < w and 0 <= ny < h]
            suelo = [n for n in vecinos if es_suelo(n)]
            if suelo:
                cambios[i] = max(set(suelo), key=suelo.count)
        celdas = [cambios.get(i, v) for i, v in enumerate(celdas)]
    assert not any(es_maquina(v) for v in celdas), "quedan máquinas"
    for (x, y), mt, colision in SALIDA_TAPADA:
        celdas[y * w + x] = mt | (colision << 10)

    os.makedirs(f"data/layouts/{CARPETA}", exist_ok=True)
    with open(f"data/layouts/{CARPETA}/map.bin", "wb") as f:
        f.write(struct.pack(f"<{w * h}H", *celdas))
    with open(base["border_filepath"], "rb") as f, open(f"data/layouts/{CARPETA}/border.bin", "wb") as g:
        g.write(f.read())

    texto = leer("data/layouts/layouts.json")
    if f'"{LAYOUT}"' not in texto:
        nuevo = {"id": LAYOUT, "name": f"{CARPETA}_Layout", "width": w, "height": h,
                 "primary_tileset": base["primary_tileset"], "secondary_tileset": base["secondary_tileset"],
                 "border_filepath": f"data/layouts/{CARPETA}/border.bin",
                 "blockdata_filepath": f"data/layouts/{CARPETA}/map.bin"}
        texto = co.insertar_en_lista(texto, "layouts", nuevo)
        json.loads(texto)
        escribir("data/layouts/layouts.json", texto)


def crear_mapa():
    os.makedirs(f"data/maps/{CARPETA}", exist_ok=True)
    ruta = f"data/maps/{CARPETA}/map.json"
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    mapa = {
        "id": MAPA,
        "name": CARPETA,
        "layout": LAYOUT,
        "music": "MUS_CAVE_OF_ORIGIN",
        "region": "REGION_HOENN",
        "region_map_section": MAPSEC,
        "requires_flash": False,
        "weather": "WEATHER_DROUGHT",
        "map_type": "MAP_TYPE_UNDERGROUND",
        "allow_cycling": True,
        "allow_escaping": True,
        "allow_running": True,
        "show_map_name": True,
        "battle_scene": "MAP_BATTLE_SCENE_NORMAL",
        "connections": None,
        # Los objetos y entrenadores que ya se hayan puesto se conservan
        "object_events": anteriores.get("object_events", []),
        "warp_events": [{"x": PUERTA[0], "y": PUERTA[1], "elevation": 0, "dest_map": "MAP_FIERY_PATH",
                         "dest_warp_id": "2"}],
        "coord_events": [],
        "bg_events": anteriores.get("bg_events", []),
    }
    escribir(ruta, json.dumps(mapa, indent=2, ensure_ascii=False) + "\n")
    if not os.path.exists(f"data/maps/{CARPETA}/scripts.inc"):
        escribir(f"data/maps/{CARPETA}/scripts.inc", f"{CARPETA}_MapScripts::\n\t.byte 0\n")

    grupos = leer("data/maps/map_groups.json")
    if f'"{CARPETA}"' not in grupos:
        d = json.loads(grupos)
        assert "FieryPath" in d["gMapGroup_Dungeons"]
        ultimo = d["gMapGroup_Dungeons"][-1]
        salto = "\r\n" if "\r\n" in grupos else "\n"
        a = f'"{ultimo}"{salto}'
        i = grupos.index(a, grupos.index('"gMapGroup_Dungeons": ['))
        grupos = grupos[:i] + f'"{ultimo}",{salto}    "{CARPETA}"{salto}' + grupos[i + len(a):]
        json.loads(grupos)
        escribir("data/maps/map_groups.json", grupos)


def entrada_sendero():
    l = layout_de("FieryPath")
    w, h = l["width"], l["height"]
    celdas = list(struct.unpack(f"<{w * h}H", open(l["blockdata_filepath"], "rb").read()))
    x, y = BOCA_FLECHA
    celdas[y * w + x] = (celdas[y * w + x] & ~0x3FF) | FLECHA
    for (bx, by), mt in BOCA:
        celdas[by * w + bx] = mt | (1 << 10)  # pared (con colisión), altura 0
    with open(l["blockdata_filepath"], "wb") as f:
        f.write(struct.pack(f"<{w * h}H", *celdas))

    ruta = "data/maps/FieryPath/map.json"
    texto = leer(ruta)
    if f'"dest_map": "{MAPA}"' not in texto:
        texto = co.insertar_en_lista(texto, "warp_events", {"x": x, "y": y, "elevation": 3, "dest_map": MAPA,
                                                            "dest_warp_id": "0"})
        json.loads(texto)
        escribir(ruta, texto)


def zona_region():
    ruta = "src/data/region_map/region_map_sections.json"
    texto = leer(ruta)
    if f'"{MAPSEC}"' not in texto:
        texto = co.insertar_en_lista(texto, "map_sections", {"id": MAPSEC, "name": "GRUTA ÍGNEA",
                                                             "x": 6, "y": 3, "width": 1, "height": 1})
        json.loads(texto)
        escribir(ruta, texto)


def main():
    crear_layout()
    crear_mapa()
    entrada_sendero()
    zona_region()
    print("Dualocke: GRUTA ÍGNEA creada")


if __name__ == "__main__":
    main()
