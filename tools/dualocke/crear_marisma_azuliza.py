#!/usr/bin/env python3
"""
Dualocke: la MARISMA AZULIZA, al oeste de PUEBLO AZULIZA (ZONAS.md, propuesta 6; estudio del #75).

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_marisma_azuliza.py

- **El mapa** (36 × 20) se monta por piezas, con los gráficos de AZULIZA (General + Dewford), que
  hacen falta para que la conexión con el pueblo se vea bien:
  - fondo de hierba, con manchas de hierba alta y flores (gráficos generales);
  - un borde de árboles como el de AZULIZA (arriba, abajo y a la izquierda);
  - a la derecha, la arena del pueblo, que sigue la del borde oeste de AZULIZA (filas 6 a 13);
  - dos charcas copiadas enteras de la RUTA 123 y la RUTA 102 (solo gráficos generales).
- **Conexión:** AZULIZA (izquierda) <-> MARISMA (derecha), sin pantalla de carga. Tramo 2.
- **Zona de captura propia:** MAPSEC_MARISMA_AZULIZA, al final de la lista.
- El mapa va al final de su grupo y de layouts.json. Hay que apuntar su scripts.inc en
  data/event_scripts.s (lo comprueba comprobar_zonas.py).
Los entrenadores, los salvajes y los objetos los ponen zonas_nuevas.py y colocar_objetos.py.
"""

import json
import os
import struct
import sys

sys.path.insert(0, "tools/dualocke")
import colocar_objetos as co  # noqa: E402

CARPETA, MAPA, MAPSEC = "MarismaAzuliza", "MAP_MARISMA_AZULIZA", "MAPSEC_MARISMA_AZULIZA"
ANCHO, ALTO = 36, 20
ALTURA = 3 << 12
COLISION = 1 << 10
HIERBA, HIERBA_ALTA, FLORES = 0x001, 0x00D, 0x004   # gráficos generales
ARENA = 0x124                                       # arena de AZULIZA
ARBOL, ARBOL_ABAJO, ARBOL_ARRIBA = 0x243, 0x23A, 0x239   # árboles de AZULIZA (copa, base y punta)
# Charcas: (mapa, x0, y0, ancho, alto) con un borde de hierba alrededor, y dónde van
CHARCAS = [(("Route123", 33, 3, 10, 7), (4, 3)), (("Route102", 39, 1, 8, 7), (17, 10))]
HIERBA_ALTA_ZONAS = [(3, 11, 15, 17), (16, 3, 26, 9), (26, 11, 30, 17), (14, 10, 17, 17)]
ARENA_ZONA = (27, 5, 36, 15)    # la arena del pueblo (x0, y0, x1, y1)
CARTEL = (29, 6)                # el cartel de la marisma (gráfico de cartel general, como en AZULIZA)
GRAFICO_CARTEL = 0x003


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


def crear_layout():
    c = [HIERBA | ALTURA] * (ANCHO * ALTO)

    def pon(x, y, v):
        if 0 <= x < ANCHO and 0 <= y < ALTO:
            c[y * ANCHO + x] = v

    for x0, y0, x1, y1 in HIERBA_ALTA_ZONAS:
        for y in range(y0, y1):
            for x in range(x0, x1):
                pon(x, y, HIERBA_ALTA | ALTURA)
    # Flores sueltas, siempre en los mismos sitios
    for i in range(ANCHO * ALTO):
        if (i * 37) % 23 == 0 and c[i] == HIERBA | ALTURA:
            c[i] = FLORES | ALTURA
    x0, y0, x1, y1 = ARENA_ZONA
    for y in range(y0, y1):
        for x in range(x0, x1):
            pon(x, y, ARENA | ALTURA)
    for (mapa, mx, my, w, h), (dx, dy) in CHARCAS:
        l, celdas = celdas_de(mapa)
        for y in range(h):
            for x in range(w):
                pon(dx + x, dy + y, celdas[(my + y) * l["width"] + mx + x])
    # Borde de árboles: arriba (copas y base), abajo (puntas y copas) y a la izquierda
    for x in range(ANCHO):
        pon(x, 0, ARBOL | COLISION)
        pon(x, 1, ARBOL | COLISION)
        pon(x, 2, ARBOL_ABAJO | COLISION)
        pon(x, ALTO - 3, ARBOL_ARRIBA | ALTURA)
        pon(x, ALTO - 2, ARBOL | COLISION)
        pon(x, ALTO - 1, ARBOL | COLISION)
    for y in range(ALTO):
        pon(0, y, ARBOL | COLISION)
        pon(1, y, ARBOL | COLISION)
    # A la derecha, igual que el borde oeste de AZULIZA: árboles arriba y abajo, arena en medio
    for y in range(3, 5):
        for x in range(30, ANCHO):
            pon(x, y, (ARBOL if y == 3 else ARBOL_ABAJO) | COLISION)
    for y in range(15, 17):
        for x in range(30, ANCHO):
            pon(x, y, ARBOL_ARRIBA | ALTURA if y == 15 else ARBOL | COLISION)
    pon(*CARTEL, GRAFICO_CARTEL | COLISION)

    base, _ = celdas_de("DewfordTown")
    os.makedirs(f"data/layouts/{CARPETA}", exist_ok=True)
    with open(f"data/layouts/{CARPETA}/map.bin", "wb") as f:
        f.write(struct.pack(f"<{ANCHO * ALTO}H", *c))
    with open(base["border_filepath"], "rb") as f, open(f"data/layouts/{CARPETA}/border.bin", "wb") as g:
        g.write(f.read())
    ident = "LAYOUT_" + MAPA[4:]
    texto = leer("data/layouts/layouts.json")
    if f'"{ident}"' not in texto:
        texto = co.insertar_en_lista(texto, "layouts", {
            "id": ident, "name": f"{CARPETA}_Layout", "width": ANCHO, "height": ALTO,
            "primary_tileset": base["primary_tileset"], "secondary_tileset": base["secondary_tileset"],
            "border_filepath": f"data/layouts/{CARPETA}/border.bin",
            "blockdata_filepath": f"data/layouts/{CARPETA}/map.bin"})
        json.loads(texto)
        escribir("data/layouts/layouts.json", texto)
    return ident


def crear_mapa(layout):
    ruta = f"data/maps/{CARPETA}/map.json"
    os.makedirs(f"data/maps/{CARPETA}", exist_ok=True)
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    escribir(ruta, json.dumps({
        "id": MAPA, "name": CARPETA, "layout": layout, "music": "MUS_ROUTE104", "region": "REGION_HOENN",
        "region_map_section": MAPSEC, "requires_flash": False, "weather": "WEATHER_RAIN",
        "map_type": "MAP_TYPE_ROUTE", "allow_cycling": True, "allow_escaping": False, "allow_running": True,
        "show_map_name": True, "battle_scene": "MAP_BATTLE_SCENE_NORMAL",
        "connections": [{"map": "MAP_DEWFORD_TOWN", "offset": 0, "direction": "right"}],
        "object_events": anteriores.get("object_events", []), "warp_events": [], "coord_events": [],
        "bg_events": anteriores.get("bg_events", []),
    }, indent=2, ensure_ascii=False) + "\n")
    if not os.path.exists(f"data/maps/{CARPETA}/scripts.inc"):
        escribir(f"data/maps/{CARPETA}/scripts.inc", f"{CARPETA}_MapScripts::\n\t.byte 0\n")

    grupos = leer("data/maps/map_groups.json")
    d = json.loads(grupos)
    grupo = next(g for g in d["group_order"] if "DewfordTown" in d[g])
    if f'"{CARPETA}"' not in grupos:
        salto = "\r\n" if "\r\n" in grupos else "\n"
        ultimo = d[grupo][-1]
        a = f'"{ultimo}"{salto}'
        i = grupos.index(a, grupos.index(f'"{grupo}": ['))
        grupos = grupos[:i] + f'"{ultimo}",{salto}    "{CARPETA}"{salto}' + grupos[i + len(a):]
        json.loads(grupos)
        escribir("data/maps/map_groups.json", grupos)

    ruta = "data/maps/DewfordTown/map.json"
    texto = leer(ruta)
    if MAPA not in texto:
        texto = co.insertar_en_lista(texto, "connections", {"map": MAPA, "offset": 0, "direction": "left"})
        json.loads(texto)
        escribir(ruta, texto)

    ruta = "src/data/region_map/region_map_sections.json"
    texto = leer(ruta)
    if f'"{MAPSEC}"' not in texto:
        dewford = next(s for s in json.loads(texto)["map_sections"] if s["id"] == "MAPSEC_DEWFORD_TOWN")
        texto = co.insertar_en_lista(texto, "map_sections", {"id": MAPSEC, "name": "MARISMA AZULIZA",
                                                             "x": dewford["x"] - 1, "y": dewford["y"],
                                                             "width": 1, "height": 1})
        json.loads(texto)
        escribir(ruta, texto)


def main():
    crear_mapa(crear_layout())
    print("Dualocke: MARISMA AZULIZA creada")


if __name__ == "__main__":
    main()
