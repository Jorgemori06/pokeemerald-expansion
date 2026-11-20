#!/usr/bin/env python3
"""Dualocke: que ningún mapa ni script de Esmeralda use gráficos de personajes que solo existen en Rojo Fuego.

Los gráficos de Rojo Fuego/Verde Hoja (`OBJ_EVENT_GFX_COOLTRAINER_F`, `OBJ_EVENT_GFX_OLD_MAN_1`…) tienen
número, pero en Esmeralda no se compilan (`#if IS_FRLG` en object_event_graphics_info_pointers.h). Un
personaje con uno de ellos sale con un sprite de basura y, en cuanto se anima, el juego salta a una
dirección mala y **se reinicia**.

Por qué: NIEVES, en la CUEVA HELADA de la ISLA NEVADA, tenía el de la entrenadora guay de Rojo Fuego. Al
capturar o vencer al guardián de la cueva (o al verte ella), el juego se reiniciaba (Miguel, 20/11/2026).
Lo mismo DARÍO (ISLA ARENOSA) y el bañista de la PLAYA VOLCÁNICA.

    python3 tools/dualocke/graficos.py              # lista los que hay
    python3 tools/dualocke/graficos.py --comprobar  # para el CI: sale con error si hay alguno
"""
import argparse
import glob
import json
import os
import re
import sys

PUNTEROS = "src/data/object_events/object_event_graphics_info_pointers.h"


def solo_rojo_fuego():
    """Gráficos que solo están dentro del #if IS_FRLG de la tabla de punteros."""
    dentro, fuera, en_frlg = set(), set(), False
    for linea in open(PUNTEROS, encoding="utf-8"):
        if linea.startswith("#if IS_FRLG"):
            en_frlg = True
        elif linea.startswith("#endif") and en_frlg:
            en_frlg = False
        m = re.search(r"\[(OBJ_EVENT_GFX_\w+)\]", linea)
        if m:
            (dentro if en_frlg else fuera).add(m.group(1))
    return dentro - fuera


def buscar():
    malos = []
    frlg = solo_rojo_fuego()
    for ruta in sorted(glob.glob("data/maps/*/map.json")):
        if ruta.endswith("_Frlg/map.json"):  # los mapas de Rojo Fuego no están en el juego
            continue
        for o in json.load(open(ruta, encoding="utf-8")).get("object_events", []):
            if o["graphics_id"] in frlg:
                malos.append(f"{os.path.basename(os.path.dirname(ruta))} ({o['x']}, {o['y']}): {o['graphics_id']}")
    patron = re.compile(r"\b(" + "|".join(sorted(frlg)) + r")\b")
    for ruta in sorted(glob.glob("data/scripts/*.inc") + glob.glob("data/maps/*/scripts.inc")):
        if "_Frlg" in ruta or "frlg" in os.path.basename(ruta).lower():
            continue
        for n, linea in enumerate(open(ruta, encoding="utf-8", errors="replace"), 1):
            m = patron.search(linea)
            if m:
                malos.append(f"{ruta}:{n}: {m.group(1)}")
    return malos


def main():
    p = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    p.add_argument("--comprobar", action="store_true", help="sale con error si hay alguno")
    args = p.parse_args()
    malos = buscar()
    for m in malos:
        print(m)
    print(f"{len(malos)} personajes con gráficos de Rojo Fuego en Esmeralda.")
    if args.comprobar and malos:
        sys.exit(1)


if __name__ == "__main__":
    main()
