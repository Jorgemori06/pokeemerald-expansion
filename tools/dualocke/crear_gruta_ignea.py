#!/usr/bin/env python3
"""
Dualocke: la GRUTA ÍGNEA, debajo del SENDERO ÍGNEO (ZONAS.md, propuesta 7; Miguel, 16/11/2026).

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_gruta_ignea.py

Qué hace:
- **La gruta** (59 × 28): la planta 4 de la GUARIDA MAGMA (mismos gráficos que el SENDERO ÍGNEO, con
  el lago de lava) sin las máquinas del Equipo Magma: cada casilla de máquina pasa a ser el suelo de
  cueva de al lado. La puerta del noreste es la entrada.
- **La CÁMARA DEL MAGMA** (33 × 24): la salida del sur de la gruta baja a una sala en terrazas con
  dos pozas de lava (la sala 3 de la planta 3 de la guarida, sin su máquina y con la puerta de
  arriba tapiada). Arriba del todo está el guardián: un Pokémon fuerte que se puede capturar, como
  en las islas del ferry (data/scripts/dualocke_islas.inc).
- **La entrada:** una boca de cueva en la sala del suroeste del SENDERO ÍGNEO, la de detrás de las
  rocas de FUERZA (así se llega con la 4.ª medalla: tramo 5).
- **Zona del mapa de la región:** MAPSEC_GRUTA_IGNEA, al final de la lista (zona de captura propia,
  sin mover los bits de las demás). Las dos salas cuentan como una zona.
- Los mapas van al final de layouts.json y de gMapGroup_Dungeons, para no mover los números de los
  mapas de las partidas guardadas. Hay que apuntar sus scripts.inc en data/event_scripts.s.
Los entrenadores, los salvajes y los objetos los ponen zonas_nuevas.py y colocar_objetos.py.
"""

import json
import os
import struct
import sys

sys.path.insert(0, "tools/dualocke")
import colocar_objetos as co  # noqa: E402

GRUTA, CAMARA = "GrutaIgnea", "GrutaIgnea_Camara"
MAPAS = {GRUTA: "MAP_GRUTA_IGNEA", CAMARA: "MAP_GRUTA_IGNEA_CAMARA"}
MAPSEC = "MAPSEC_GRUTA_IGNEA"
MAQUINAS = set(range(0x35C, 0x39E)) | {0x3A8, 0x3A9}   # depósitos, ordenadores, taladros y el pedestal
PARED = 0x274                    # pared de roca lisa
PUERTA = (46, 7)                 # gruta: entrada desde el SENDERO ÍGNEO
BAJADA = (20, 21)                # gruta: flecha hacia la CÁMARA DEL MAGMA
SUBIDA = (16, 21)                # cámara: flecha de vuelta a la gruta
PUERTA_TAPIADA = [(16, 0), (16, 1)]   # cámara: la puerta de arriba (iba a la planta 2 de la guarida)
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
    return co.cargar_layouts()[json.loads(leer(f"data/maps/{carpeta}/map.json"))["layout"]]


def sin_maquinas(base_mapa):
    """El layout de una sala de la GUARIDA MAGMA con suelo de cueva donde había máquinas."""
    base = layout_de(base_mapa)
    w, h = base["width"], base["height"]
    celdas = list(struct.unpack(f"<{w * h}H", open(base["blockdata_filepath"], "rb").read()))
    mb = {v: k for k, v in co.comportamientos().items()}
    atributos = co.atributos_tilesets()
    prim, sec = atributos[base["primary_tileset"]], atributos[base["secondary_tileset"]]

    def es_maquina(v):
        return (v & 0x3FF) in MAQUINAS

    # Solo se rellena con suelo de cueva (no con tablas del puente ni bordes de lava)
    def es_suelo(v):
        mt = v & 0x3FF
        a = prim[mt] if mt < 512 else sec[mt - 512]
        return (v >> 10) & 3 == 0 and mb.get(a & 0xFF) == "MB_CAVE" and not es_maquina(v)

    # Varias pasadas, porque las máquinas ocupan 2 × 3 casillas
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
    return base, celdas


def guardar(carpeta, base, celdas):
    w, h = base["width"], base["height"]
    os.makedirs(f"data/layouts/{carpeta}", exist_ok=True)
    with open(f"data/layouts/{carpeta}/map.bin", "wb") as f:
        f.write(struct.pack(f"<{w * h}H", *celdas))
    with open(base["border_filepath"], "rb") as f, open(f"data/layouts/{carpeta}/border.bin", "wb") as g:
        g.write(f.read())
    ident = "LAYOUT_" + MAPAS[carpeta][4:]
    texto = leer("data/layouts/layouts.json")
    if f'"{ident}"' not in texto:
        texto = co.insertar_en_lista(texto, "layouts", {
            "id": ident, "name": f"{carpeta}_Layout", "width": w, "height": h,
            "primary_tileset": base["primary_tileset"], "secondary_tileset": base["secondary_tileset"],
            "border_filepath": f"data/layouts/{carpeta}/border.bin",
            "blockdata_filepath": f"data/layouts/{carpeta}/map.bin"})
        json.loads(texto)
        escribir("data/layouts/layouts.json", texto)
    return ident


def mapa_json(carpeta, layout, warps):
    os.makedirs(f"data/maps/{carpeta}", exist_ok=True)
    ruta = f"data/maps/{carpeta}/map.json"
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    escribir(ruta, json.dumps({
        "id": MAPAS[carpeta], "name": carpeta, "layout": layout, "music": "MUS_CAVE_OF_ORIGIN",
        "region": "REGION_HOENN", "region_map_section": MAPSEC, "requires_flash": False,
        "weather": "WEATHER_DROUGHT", "map_type": "MAP_TYPE_UNDERGROUND", "allow_cycling": True,
        "allow_escaping": True, "allow_running": True, "show_map_name": True,
        "battle_scene": "MAP_BATTLE_SCENE_NORMAL", "connections": None,
        # Los objetos y entrenadores que ya se hayan puesto se conservan
        "object_events": anteriores.get("object_events", []),
        "warp_events": warps, "coord_events": [], "bg_events": anteriores.get("bg_events", []),
    }, indent=2, ensure_ascii=False) + "\n")
    if not os.path.exists(f"data/maps/{carpeta}/scripts.inc"):
        escribir(f"data/maps/{carpeta}/scripts.inc", f"{carpeta}_MapScripts::\n\t.byte 0\n")
    grupos = leer("data/maps/map_groups.json")
    if f'"{carpeta}"' not in grupos:
        d = json.loads(grupos)
        ultimo = d["gMapGroup_Dungeons"][-1]
        salto = "\r\n" if "\r\n" in grupos else "\n"
        a = f'"{ultimo}"{salto}'
        i = grupos.index(a, grupos.index('"gMapGroup_Dungeons": ['))
        grupos = grupos[:i] + f'"{ultimo}",{salto}    "{carpeta}"{salto}' + grupos[i + len(a):]
        json.loads(grupos)
        escribir("data/maps/map_groups.json", grupos)


def crear_mapas():
    base, celdas = sin_maquinas("MagmaHideout_4F")
    layout_gruta = guardar(GRUTA, base, celdas)
    base, celdas = sin_maquinas("MagmaHideout_3F_3R")
    for x, y in PUERTA_TAPIADA:
        celdas[y * base["width"] + x] = PARED | (1 << 10)
    layout_camara = guardar(CAMARA, base, celdas)
    mapa_json(GRUTA, layout_gruta, [
        {"x": PUERTA[0], "y": PUERTA[1], "elevation": 0, "dest_map": "MAP_FIERY_PATH", "dest_warp_id": "2"},
        {"x": BAJADA[0], "y": BAJADA[1], "elevation": 0, "dest_map": MAPAS[CAMARA], "dest_warp_id": "0"}])
    mapa_json(CAMARA, layout_camara, [
        {"x": SUBIDA[0], "y": SUBIDA[1], "elevation": 0, "dest_map": MAPAS[GRUTA], "dest_warp_id": "1"}])


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
    if f'"dest_map": "{MAPAS[GRUTA]}"' not in texto:
        texto = co.insertar_en_lista(texto, "warp_events", {"x": x, "y": y, "elevation": 3, "dest_map": MAPAS[GRUTA],
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
    crear_mapas()
    entrada_sendero()
    zona_region()
    print("Dualocke: GRUTA ÍGNEA y CÁMARA DEL MAGMA creadas")


if __name__ == "__main__":
    main()
