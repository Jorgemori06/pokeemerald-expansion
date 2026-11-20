#!/usr/bin/env python3
"""Dualocke: los mapas que el juego cambia por otro al entrar.

Algunos mapas tienen más de un dibujo (layout) y el script del mapa elige cuál usar al entrar
(`setmaplayoutindex`). Por ejemplo:
- la RUTA 131 usa **siempre** `LAYOUT_ROUTE131_SKY_PILLAR` (con el islote del PILAR CELESTE);
- la RUTA 111 pasa a `LAYOUT_ROUTE111_NO_MIRAGE_TOWER` cuando se derrumba la TORRE ESPEJISMO.

Lo que se cambie en el dibujo de un mapa hay que cambiarlo en todos sus dibujos. Si no, en el juego no se
ve. Por qué (20/11/2026, lo vio Miguel jugando):
- el hueco en la barrera de rocas de la RUTA 131 para llegar a la ISLA DE RUINAS se abrió solo en el
  dibujo que no se usa, y en el juego la barrera seguía cerrada;
- el montículo con la puerta del DESIERTO PROFUNDO solo estaba en el dibujo de la RUTA 111 con la torre,
  y después de coger el fósil desaparecía.

Los scripts que dibujan en mapas originales (`crear_desierto_profundo.py`, `crear_islas_sur.py`) usan
`layouts_de()` para cambiarlos todos, y `alcance.py` mira el dibujo que se usa en el juego (`EN_JUEGO`).

    python3 tools/dualocke/variantes.py --comprobar   # para el CI
"""
import argparse
import glob
import json
import os
import re
import struct
import sys

# Dónde se diferencian los dibujos de cada mapa en el juego original: (x0, y0, x1, y1), sin x1 ni y1. Fuera
# de esa caja tienen que ser iguales.
PROPIAS = {
    ("LAYOUT_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB", "LAYOUT_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB_WITH_TABLE"): (8, 3, 11, 6),
    ("LAYOUT_ROUTE111", "LAYOUT_ROUTE111_NO_MIRAGE_TOWER"): (18, 53, 21, 59),
    ("LAYOUT_ROUTE130", "LAYOUT_ROUTE130_MIRAGE_ISLAND"): (16, 1, 63, 32),
    ("LAYOUT_ROUTE131", "LAYOUT_ROUTE131_SKY_PILLAR"): (23, 0, 52, 23),
    ("LAYOUT_SHOAL_CAVE_LOW_TIDE_ENTRANCE_ROOM", "LAYOUT_SHOAL_CAVE_HIGH_TIDE_ENTRANCE_ROOM"): (0, 3, 35, 35),
    ("LAYOUT_SHOAL_CAVE_LOW_TIDE_INNER_ROOM", "LAYOUT_SHOAL_CAVE_HIGH_TIDE_INNER_ROOM"): (4, 3, 43, 35),
    ("LAYOUT_SKY_PILLAR_1F", "LAYOUT_SKY_PILLAR_1F_CLEAN"): (0, 2, 14, 14),
    ("LAYOUT_SKY_PILLAR_2F", "LAYOUT_SKY_PILLAR_2F_CLEAN"): (0, 2, 14, 14),
    ("LAYOUT_SKY_PILLAR_3F", "LAYOUT_SKY_PILLAR_3F_CLEAN"): (0, 4, 14, 14),
    ("LAYOUT_SKY_PILLAR_4F", "LAYOUT_SKY_PILLAR_4F_CLEAN"): (0, 3, 14, 14),
    ("LAYOUT_SKY_PILLAR_5F", "LAYOUT_SKY_PILLAR_5F_CLEAN"): (0, 2, 14, 14),
    ("LAYOUT_SKY_PILLAR_TOP", "LAYOUT_SKY_PILLAR_TOP_CLEAN"): (0, 4, 27, 18),
    ("LAYOUT_SOOTOPOLIS_CITY", "LAYOUT_SOOTOPOLIS_CITY_LEGENDS_BATTLE"): (15, 24, 50, 57),
    ("LAYOUT_SOOTOPOLIS_CITY_MYSTERY_EVENTS_HOUSE_1F",
     "LAYOUT_SOOTOPOLIS_CITY_MYSTERY_EVENTS_HOUSE_1F_STAIRS_UNBLOCKED"): (1, 0, 7, 3),
}
# El dibujo que se ve siempre en el juego, cuando el mapa lo cambia al entrar sin condiciones
EN_JUEGO = {"LAYOUT_ROUTE131": "LAYOUT_ROUTE131_SKY_PILLAR"}


def _layouts():
    with open("data/layouts/layouts.json", encoding="utf-8") as f:
        return {l["id"]: l for l in json.load(f)["layouts"] if "id" in l}


def pares():
    """{(layout del map.json, otro layout que pone su script)} de los mapas de Esmeralda."""
    encontrados = set()
    for ruta in glob.glob("data/maps/*/scripts.inc"):
        if "_Frlg" in ruta:
            continue
        otros = set(re.findall(r"setmaplayoutindex\s+(LAYOUT_\w+)", open(ruta, encoding="utf-8").read()))
        if not otros:
            continue
        with open(os.path.join(os.path.dirname(ruta), "map.json"), encoding="utf-8") as f:
            base = json.load(f)["layout"]
        encontrados |= {(base, o) for o in otros if o != base}
    return encontrados


def layouts_de(carpeta):
    """Los dibujos de un mapa: el de su map.json y los que pone su script."""
    with open(f"data/maps/{carpeta}/map.json", encoding="utf-8") as f:
        base = json.load(f)["layout"]
    return [base] + sorted(o for b, o in pares() if b == base)


def celdas(layout):
    with open(layout["blockdata_filepath"], "rb") as f:
        datos = f.read()
    return list(struct.unpack(f"<{len(datos) // 2}H", datos))


def comprobar():
    L = _layouts()
    errores = []
    for base, otro in sorted(pares()):
        if (base, otro) not in PROPIAS:
            errores.append(f"{base} / {otro}: no está en PROPIAS (variantes.py): mira dónde se diferencian")
            continue
        x0, y0, x1, y1 = PROPIAS[(base, otro)]
        a, b = celdas(L[base]), celdas(L[otro])
        w = L[base]["width"]
        fuera = [(i % w, i // w) for i in range(len(a))
                 if a[i] != b[i] and not (x0 <= i % w < x1 and y0 <= i // w < y1)]
        if fuera:
            errores.append(f"{base} / {otro}: {len(fuera)} casillas distintas fuera de su zona, por ejemplo {fuera[:4]}")
    return errores


def main():
    p = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    p.add_argument("--comprobar", action="store_true", help="sale con error si algún dibujo no tiene un cambio")
    args = p.parse_args()
    errores = comprobar()
    for e in errores:
        print(e)
    print(f"{len(pares())} mapas con más de un dibujo; {len(errores)} con cambios que faltan en alguno.")
    if args.comprobar and errores:
        sys.exit(1)


if __name__ == "__main__":
    main()
