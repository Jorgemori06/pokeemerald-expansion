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

También mira que **ninguna persona ni entrenador tape el paso**: entre las salidas del mapa (puertas,
bordes y los sitios a los que te lleva un script, como el barco) se tiene que poder ir igual con ellos
que sin ellos. Cuentan las personas que no se mueven y no desaparecen nunca (flag "0"); los objetos y
las rocas, árboles y peñas de MO no.

Y que **ninguna Poké Ball del suelo tape el paso**: ni entre dos salidas, ni delante de una puerta (la
única casilla para entrar), ni a una persona, un entrenador o un cartel. Detrás de una Ball sí puede
haber otra (coges la primera y pasas). Esto se mira en todos los mapas, pero solo con las Balls que pone
colocar_objetos.py (FLAG_ITEM_MEGA_, FLAG_ITEM_COMP_ y FLAG_ITEM_TICKET_) y las de las zonas nuevas: las
de Esmeralda que tapan algo lo hacen a propósito (detrás de un árbol de CORTE, por ejemplo).

Por qué: en la ISLA SUR, TERRY estaba en la única casilla del sendero y no dejaba llegar a la cueva
(Miguel, 19/11/2026). Y en la CUMBRE METEORO se bajaba al guardián por una cuesta de barro y solo se podía volver con la
bici de carreras. Miguel se quedó encerrado jugando (18/11/2026). Con la cumbre de antes, esto da 92
casillas sin vuelta.
La Ball de las GAFAS ESPECIALES tapaba la escalera del MUSEO OCEÁNICO 2F, y la del TICKET-RECUERDO, la
puerta del MONTE PÍRICO, la de la casa de la RUTA 124 y las escaleras del PILAR CELESTE (las vio el bot,
22/11/2026).
"""

import argparse
import glob
import os
import re
import sys
from collections import deque

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import alcance as a  # noqa: E402
from aleatorio import zonas  # noqa: E402

DIRS = {"up": (0, -1), "down": (0, 1), "left": (-1, 0), "right": (1, 0)}
SALTOS = {"MB_JUMP_NORTH": "up", "MB_JUMP_SOUTH": "down", "MB_JUMP_EAST": "right", "MB_JUMP_WEST": "left"}


def pasos(mundo, mid, puertas, x, y, tapadas=frozenset()):
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
        if mb in mundo.surf or (nx, ny) in tapadas:
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


def llegadas_por_script():
    """{MAP_X: {(x, y)}}: sitios a los que te llevan los scripts (warp MAP_X, x, y), como el barco."""
    llegadas = {}
    for ruta in glob.glob("data/**/*.inc", recursive=True):
        texto = open(ruta, encoding="utf-8", errors="replace").read()
        for mapa, x, y in re.findall(r"^\s*warp\w*\s+(MAP_\w+)\s*,\s*(\d+)\s*,\s*(\d+)", texto, re.M):
            llegadas.setdefault(mapa, set()).add((int(x), int(y)))
    return llegadas


def personas_fijas(m):
    """Casillas con una persona o entrenador que no se mueve ni desaparece."""
    fijas = set()
    for o in m.get("object_events", []):
        if str(o.get("flag", "0")) != "0" or o["graphics_id"] in a.GFX_MO or "ITEM_BALL" in o["graphics_id"]:
            continue
        if any(t in o["movement_type"] for t in ("WANDER", "WALK")):
            continue
        fijas.add((o["x"], o["y"]))
    return fijas


def tapados(mundo, mid, llegadas):
    """[(salida, salida a la que ya no se llega por las personas)]."""
    m = mundo.mapas[mid]
    w, h, c = mundo.rejilla(mid)
    puertas = {(p["x"], p["y"]) for p in m.get("warp_events", [])}
    salidas = set(puertas) | {p for p in llegadas if 0 <= p[0] < w and 0 <= p[1] < h}
    for con in m.get("connections") or []:
        borde = {"up": [(x, 0) for x in range(w)], "down": [(x, h - 1) for x in range(w)],
                 "left": [(0, y) for y in range(h)], "right": [(w - 1, y) for y in range(h)]}.get(con["direction"], [])
        salidas |= {p for p in borde if not c[p[1] * w + p[0]][0]}
    fijas = personas_fijas(m)
    salidas -= fijas

    def alcanzables(ini, tapadas):
        vistos, cola = {ini}, deque([ini])
        while cola:
            for n in pasos(mundo, mid, puertas, *cola.popleft(), tapadas=tapadas):
                if n not in vistos:
                    vistos.add(n)
                    cola.append(n)
        return vistos

    malos = []
    for s in sorted(salidas):
        sin, con = alcanzables(s, frozenset()), alcanzables(s, frozenset(fijas))
        malos += [(s, t) for t in sorted(salidas & (sin - con))]
    return malos


BOLAS_NUESTRAS = re.compile(r"FLAG_ITEM_(MEGA|COMP|TICKET)_")


def salidas(mundo, mid, llegadas):
    """(puertas, salidas): las puertas del mapa, y además los bordes con conexión y las llegadas por script."""
    m = mundo.mapas[mid]
    w, h, c = mundo.rejilla(mid)
    puertas = {(p["x"], p["y"]) for p in m.get("warp_events", [])}
    todas = set(puertas) | {p for p in llegadas if 0 <= p[0] < w and 0 <= p[1] < h}
    for con in m.get("connections") or []:
        borde = {"up": [(x, 0) for x in range(w)], "down": [(x, h - 1) for x in range(w)],
                 "left": [(0, y) for y in range(h)], "right": [(w - 1, y) for y in range(h)]}.get(con["direction"], [])
        todas |= {p for p in borde if not c[p[1] * w + p[0]][0]}
    return puertas, todas


def bolas_que_tapan(mundo, mid, llegadas, casillas=None):
    """[(casilla de la Ball, [lo que tapa])] de las Balls de este mapa que tapan algo.
    casillas: las Balls que se miran (por defecto, las nuestras); sirve también para probar una casilla en la
    que todavía no hay Ball (colocar_objetos.py)."""
    m = mundo.mapas[mid]
    puertas, sal = salidas(mundo, mid, llegadas)
    fijas = personas_fijas(m)
    sal -= fijas
    objetos = m.get("object_events", []) + m.get("bg_events", [])
    if casillas is None:
        nueva = zonas.es_nueva(os.path.basename(m["carpeta"]))
        casillas = [(o["x"], o["y"]) for o in m.get("object_events", []) if "ITEM_BALL" in o["graphics_id"]
                    and (nueva or BOLAS_NUESTRAS.match(str(o.get("flag", ""))))]
    # Lo que no se puede quedar detrás de una Ball: personas, entrenadores y carteles (se habla desde al lado)
    importan = {(o["x"], o["y"]) for o in objetos
                if "ITEM_BALL" not in o.get("graphics_id", "") and o.get("type") != "hidden_item"}

    def alcanzables(ini, tapadas):
        vistos, cola = {ini}, deque([ini])
        while cola:
            for n in pasos(mundo, mid, puertas, *cola.popleft(), tapadas=tapadas):
                if n not in vistos:
                    vistos.add(n)
                    cola.append(n)
        return vistos

    def al_lado(p):
        return {(p[0] + 1, p[1]), (p[0] - 1, p[1]), (p[0], p[1] + 1), (p[0], p[1] - 1)}

    malos = []
    for b in casillas:
        sin_bola, con_bola = frozenset(fijas), frozenset(fijas | {b})
        tapa = set()
        for s in sorted(sal - {b}):
            sin, con = alcanzables(s, sin_bola), alcanzables(s, con_bola)
            if s in puertas and con == {s} and len(sin) > 1:
                tapa.add(f"la puerta {s}")
            tapa |= {f"la salida {t}" for t in sal if t in sin and t not in con and t != b}
            tapa |= {f"el objeto {p}" for p in importan if p != b and al_lado(p) & sin and not (al_lado(p) - {b}) & con}
        if tapa:
            malos.append((b, sorted(tapa)))
    return malos


def main():
    p = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    p.add_argument("--comprobar", action="store_true")
    args = p.parse_args()
    mundo = a.Mundo()
    malos = 0
    llegadas = llegadas_por_script()
    for mid, m in sorted(mundo.mapas.items()):
        carpeta = os.path.basename(m["carpeta"])
        if not zonas.es_nueva(carpeta) or carpeta.endswith("_Frlg"):  # los de Rojo Fuego no están en el juego
            continue
        casillas = sin_vuelta(mundo, mid)
        if casillas:
            malos += 1
            print(f"{mid}: {len(casillas)} casillas sin vuelta, por ejemplo {casillas[:6]}")
        cortes = tapados(mundo, mid, llegadas.get(mid, set()))
        if cortes:
            malos += 1
            print(f"{mid}: una persona tapa el paso entre {len(cortes)} parejas de salidas, por ejemplo {cortes[:3]}")
    for mid, m in sorted(mundo.mapas.items()):
        if os.path.basename(m["carpeta"]).endswith("_Frlg"):
            continue
        for b, tapa in bolas_que_tapan(mundo, mid, llegadas.get(mid, set())):
            malos += 1
            print(f"{mid}: la Ball de {b} tapa {', '.join(tapa[:3])}")
    print(f"{malos} problemas (sitios sin vuelta en las zonas nuevas, o paso tapado por una persona o una Ball).")
    if args.comprobar and malos:
        sys.exit(1)


if __name__ == "__main__":
    main()
