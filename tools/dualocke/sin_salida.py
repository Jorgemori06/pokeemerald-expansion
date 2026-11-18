#!/usr/bin/env python3
"""
Dualocke: que en las zonas nuevas nadie se quede encerrado.

Uso (desde la raíz del repo):
    python3 tools/dualocke/sin_salida.py              # lista los sitios sin vuelta
    python3 tools/dualocke/sin_salida.py --comprobar  # sale con error si hay alguno (va en el CI)

Para cada mapa de las zonas nuevas (los de PREFIJOS en tools/dualocke/aleatorio/zonas.py), mira a qué
casillas se llega andando desde sus puertas y bordes, y si desde todas ellas se puede volver a alguna
salida. Anda como el jugador sin bici ni MO:
- el barro (MB_MUDDY_SLOPE) solo se baja; para subirlo hace falta la bici de carreras;
- los saltos solo en su dirección;
- el agua no se pisa;
- a las puertas sí se entra, aunque tengan colisión.
No mira las alturas (como alcance.py con ESTRICTO = False) ni los objetos del mapa (árboles de CORTE,
rocas…).

Por qué: en la CUMBRE METEORO se bajaba al guardián por una cuesta de barro y solo se podía volver con la
bici de carreras. Miguel se quedó encerrado jugando (18/11/2026). Con la cumbre de antes, esto da 92
casillas sin vuelta.
"""

import argparse
import os
import sys
from collections import deque

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import alcance as a  # noqa: E402
from aleatorio import zonas  # noqa: E402

DIRS = {"up": (0, -1), "down": (0, 1), "left": (-1, 0), "right": (1, 0)}
SALTOS = {"MB_JUMP_NORTH": "up", "MB_JUMP_SOUTH": "down", "MB_JUMP_EAST": "right", "MB_JUMP_WEST": "left"}


def pasos(mundo, mid, puertas, x, y):
    """Casillas a las que se pasa desde (x, y) en un paso (o en un salto)."""
    w, h, c = mundo.rejilla(mid)
    for d, (dx, dy) in DIRS.items():
        nx, ny = x + dx, y + dy
        if not (0 <= nx < w and 0 <= ny < h):
            continue
        col, _, mb = c[ny * w + nx]
        if mb in SALTOS:
            if SALTOS[mb] == d and 0 <= nx + dx < w and 0 <= ny + dy < h:
                yield nx + dx, ny + dy
            continue
        if col and (nx, ny) not in puertas:
            continue
        if mb == "MB_MUDDY_SLOPE" and d != "down":
            continue
        if mb in mundo.surf:
            continue
        yield nx, ny


def sin_vuelta(mundo, mid):
    """Casillas a las que se llega desde las salidas del mapa pero desde las que no se vuelve a ninguna."""
    m = mundo.mapas[mid]
    w, h, c = mundo.rejilla(mid)
    puertas = {(p["x"], p["y"]) for p in m.get("warp_events", [])}
    salidas = set(puertas)
    for con in m.get("connections") or []:
        borde = {"up": [(x, 0) for x in range(w)], "down": [(x, h - 1) for x in range(w)],
                 "left": [(0, y) for y in range(h)], "right": [(w - 1, y) for y in range(h)]}.get(con["direction"], [])
        salidas |= {p for p in borde if not c[p[1] * w + p[0]][0]}
    # Hacia delante, desde las salidas; y hacia atrás (el grafo al revés), también desde las salidas
    delante, atras = set(salidas), set(salidas)
    inversa = {}
    cola = deque(salidas)
    vistos = set(salidas)
    while cola:
        p = cola.popleft()
        for n in pasos(mundo, mid, puertas, *p):
            inversa.setdefault(n, []).append(p)
            if n not in vistos:
                vistos.add(n)
                cola.append(n)
    delante = vistos
    # Para el grafo al revés hace falta conocer los pasos de todas las casillas a las que se llega
    cola = deque(salidas)
    while cola:
        p = cola.popleft()
        for n in inversa.get(p, ()):
            if n not in atras:
                atras.add(n)
                cola.append(n)
    return sorted(delante - atras)


def main():
    p = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    p.add_argument("--comprobar", action="store_true")
    args = p.parse_args()
    mundo = a.Mundo()
    malos = 0
    for mid, m in sorted(mundo.mapas.items()):
        carpeta = os.path.basename(m["carpeta"])
        if not zonas.es_nueva(carpeta) or carpeta.endswith("_Frlg"):  # los de Rojo Fuego no están en el juego
            continue
        casillas = sin_vuelta(mundo, mid)
        if casillas:
            malos += 1
            print(f"{mid}: {len(casillas)} casillas sin vuelta, por ejemplo {casillas[:6]}")
    print(f"{malos} mapas de zonas nuevas con sitios sin vuelta.")
    if args.comprobar and malos:
        sys.exit(1)


if __name__ == "__main__":
    main()
