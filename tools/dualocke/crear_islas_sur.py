#!/usr/bin/env python3
"""
Dualocke: las islas de las rutas del sur (ZONAS.md, propuestas 2, 3 y 4; Miguel, 17/11/2026).

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_islas_sur.py

Cada isla es un mapa pegado al borde de una ruta de mar: se surfea hacia fuera de la ruta y se entra sin
pantalla de carga. Usan los mismos gráficos que su ruta (si no, la conexión se vería rota). Todas son del
**tramo 8**. El sitio de cada una se eligió mirando las corrientes: las RUTAS 132-134 tienen los bordes
cerrados por rocas y corrientes que solo empujan al oeste, y el borde este de la RUTA 127 es una pared de
roca, así que dos islas cambian de sitio respecto a ZONAS.md (ver abajo).

- **ISLA DE RUINAS**, al norte de la RUTA 131 (junto al PILAR CELESTE): el islote del PILAR CELESTE
  (SkyPillar_Outside) con su torre, con niebla (Campo de Niebla en combate). La franja de arena de abajo acaba
  en una playa. La puerta de la torre (abierta) lleva a la **TORRE**: la planta 1 del PILAR CELESTE, sin la
  escalera, con el guardián delante.
- **ISLA VOLCÁNICA**, al sur de la RUTA 134 (donde el mar no tiene corriente): una isla de arena con su bajío,
  peñas y, en medio, el montículo de la cueva del PILAR CELESTE. La cueva baja al **CRÁTER**: la cima del
  MONTE CENIZO (lava y terrazas) con ceniza que tiene salvajes, una salida nueva y el guardián. Sol.
- **ISLA ARENOSA**, al este de la RUTA 129 (en ZONAS.md iba al este de la RUTA 127, que está cerrado):
  una isla grande de arena con peñas y una cala, y al oeste un islote de hierba con árboles y hierba alta.
  Tormenta de arena.

**Rehechas el 17/11/2026** para que parezcan diseñadas como el juego original: antes eran trozos de islotes
copiados tal cual. Ahora la ISLA VOLCÁNICA y la ISLA ARENOSA se dibujan con letras (un PLANO) y las pinta
autotile.py, como la PLAYA VOLCÁNICA. Del juego se copian el islote del PILAR CELESTE (con `isla()`: solo las
casillas que no son mar y están unidas a él), su montículo y las peñas de la RUTA 127.

Zonas de captura propias: MAPSEC_ISLA_DE_RUINAS, MAPSEC_ISLA_VOLCANICA y MAPSEC_ISLA_ARENOSA (cada isla con
su interior cuenta como una).
Los entrenadores, los salvajes y los objetos los ponen zonas_nuevas.py y colocar_objetos.py.
"""

import json
import re
import os
import struct
import sys
from collections import deque

sys.path.insert(0, "tools/dualocke")
import autotile as at  # noqa: E402
import colocar_objetos as co  # noqa: E402

RUINAS, TORRE = "IslaDeRuinas", "IslaDeRuinas_Torre"
VOLCAN, CRATER = "IslaVolcanica", "IslaVolcanica_Crater"
ARENOSA = "IslaArenosa"
MAPAS = {RUINAS: "MAP_ISLA_DE_RUINAS", TORRE: "MAP_ISLA_DE_RUINAS_TORRE", VOLCAN: "MAP_ISLA_VOLCANICA",
         CRATER: "MAP_ISLA_VOLCANICA_CRATER", ARENOSA: "MAP_ISLA_ARENOSA"}
MAPSEC = {RUINAS: "MAPSEC_ISLA_DE_RUINAS", TORRE: "MAPSEC_ISLA_DE_RUINAS", VOLCAN: "MAPSEC_ISLA_VOLCANICA",
          CRATER: "MAPSEC_ISLA_VOLCANICA", ARENOSA: "MAPSEC_ISLA_ARENOSA"}
COLISION = 1 << 10

# --- Cómo se dibujan (rediseño del 17/11/2026) ---------------------------------------------------
# Como la PLAYA VOLCÁNICA: cada isla es un dibujo de letras (PLANO) y lo pinta autotile.py con las piezas que
# ha aprendido de los mapas originales. Mirando las islas de las RUTAS 127-134:
#   - la arena tiene siempre su orilla, y alrededor un anillo de bajío de 2 o 3 casillas antes del mar;
#   - sobre la arena hay peñas (las de los islotes de la RUTA 127) y en el mar, rocas sueltas y remolinos;
#   - la hierba no toca el mar: va en un claro dentro de la arena.
#   - como en ARRECÍPOLIS, entre la arena y la hierba hay un camino de tierra (la arena nunca toca la hierba).
# m mar   b bajío   s arena   c camino de tierra   . hierba   , hierba alta   * flores   T árbol grande
# X roca de mar (2 × 2)   W roca con remolino (2 × 2)
TERRENO = {"m": "mar", "b": "bajio", "s": "arena", "c": "camino", ".": "suelo", "*": "suelo", ",": "hierba_alta"}
FLORES = 0x004
ROCAS = {"X": (0x175, 0x176, 0x17D, 0x17E), "W": (0x150, 0x151, 0x158, 0x159)}   # piezas generales
# Peñas de los islotes de arena de la RUTA 127 (se copian solo sus casillas de roca): (mapa, caja x0, y0, x1, y1)
PENA_GRANDE = ("Route127", (55, 61, 63, 68))
PENA_PEQUENA = ("Route127", (56, 70, 62, 73))
PENA_LARGA = ("Route127", (64, 61, 70, 64))
# El hueco de base secreta se tapa con el pie de la peña (0x079). Así no se pueden hacer bases secretas aquí:
# las demás piezas que van entre las esquinas del pie (0x0AB y 0x0AC) también son bases secretas.
BASE_SECRETA, PIE_PENA = 0x1A8, 0x079

# --- ISLA DE RUINAS ------------------------------------------------------------------------------
RUINAS_TAM = (40, 30)
RUINAS_ISLOTE = ("SkyPillar_Outside", (0, 0, 28, 22), (14, 10), (6, 0))  # mapa, caja, semilla, dónde
PUERTA_TORRE = (14, 5)                       # en SkyPillar_Outside; se abre con los metatiles de la torre abierta
PUERTA_ABIERTA = {(14, 4): 0x2AA, (14, 5): 0x2B2}
# El rellano de la torre está rodeado de acantilados (en el juego se llega por la cueva del montículo).
# Aquí la cueva de la orilla de abajo y la del montículo son un túnel: se entra por una y se sale por la otra.
CUEVA_PILAR, CUEVA_ORILLA = (17, 13), (15, 20)
RUINAS_RUTA, RUINAS_DESPLAZAMIENTO = "MAP_ROUTE131", 15   # la isla empieza en la x 15 de la RUTA 131
# En el PILAR CELESTE la franja de arena de abajo sigue fuera del mapa: aquí acaba en una playa (filas 22-29).
RUINAS_FILA_PLAYA = 22
# La roca con remolino de la orilla (x 20-21 del PILAR CELESTE) tiene su mitad de abajo en la fila 22: se copia
RUINAS_ROCA_ORILLA = [(20, 22), (21, 22)]
RUINAS_PLAYA = """
mmmmmmmmmmmmmmmmmmmsssssmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmsssssssmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmsssssssssmmmmmmXXmmmmmm
mmmmmmmmmmmmmmmmmsssssssssmmmmmmXXmmmmmm
mmmmmmmmXXmmmmmmmmsssssssmmmmmmmmmmmmmmm
mmmWWmmmXXmmmmmmmmmmsssmmmmmmmmmmmmmmmmm
mmmWWmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmXXmm
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmXXmm
"""
TORRE_BASE = "SkyPillar_1F"
ESCALERA_TORRE, PARED_TORRE = (10, 1), (9, 1)
ENTRADA_TORRE = ((6, 13), (7, 13))

# --- ISLA VOLCÁNICA ------------------------------------------------------------------------------
# Una isla de arena con su bajío. En medio, el montículo del PILAR CELESTE con la cueva
# que baja al CRÁTER; alrededor, peñas y rocas en el mar. Se llega desde arriba (la RUTA 134).
VOLCAN_PLANO = """
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmWWmmmmmmmm
mmmmmmmWWmmmmmmmmmmmmmmmmmmmmmWWmmXXmmmm
mmmXXmmWWmmmmmmmmmmmmmmmmmmmmmmmmmXXmmmm
mmmXXmmmmmmmmmbbbbbbbbbbbbmmmmmmmmmmmmmm
mmmmmmmmmmmbbbbbbbbbbbbbbbbbbmmmmmmmmmmm
mmmmmmmmmbbbbbbbssssssssbbbbbbbmmmmmmmmm
mmmmmmmmbbbbbssssssssssssssbbbbbmmmmmmmm
mmmmmmmbbbbssssssssssssssssssbbbbmmmXXmm
mmmmmmbbbbssssssssssssssssssssbbbbmmXXmm
mmmmmmbbbssssssssssssssssssssssbbbmmmmmm
mmmmmbbbssssssssssssssssssssssssbbmmmmmm
mmmmmbbbssssssssssssssssssssssssbbbmmmmm
mXXmmbbsssssssssssssssssssssssssbbbmmmmm
mXXmmbbssssssssssssssssssssssssssbbbmmmm
mmmmmbbssssssssssssssssssssssssssbbbbmmm
mmmmmbbbssssssssssssssssssssssssssbbbmmm
mmmmmbbbsssssssssssssssssssssssssssbbmmm
mWWmmmbbbssssssssssssssssssssssssssbbmmm
mWWmmmbbbsssssssssssssssssssssssssbbbmmm
mmmmmmmbbbsssssssssssssssssssssssbbbbmmm
mmmmmmmbbbbsssssssssssssssssssssbbbbmmmm
mmmXXmmmbbbbbsssssssssssssssssbbbbbmmmmm
mmmXXmmmmbbbbbbssssssssssssbbbbbbbmmmmXX
mmmmmmmmmmmbbbbbbsssssssbbbbbbbbmmmmmmXX
mmmmmmmmmmmmmbbbbbbbbbbbbbbbbmmmmmmmmmmm
mmmmmmmmmmmmmmmbbbbbbbbbbbmmmmmmmmmmmmmm
mmmmmmmmmWWmmmmmmmmmmmmmmmmmmmmmmXXmmmmm
mmmmmmmmmWWmmmmmmmmmmmmmmmmmXXmmmXXmmmmm
mmmmmmmmmmmmmmmmmmmmmmmmmmmmXXmmmmmmmmmm
"""
MONTICULO = ("SkyPillar_Outside", (14, 9, 21, 14), (17, 13))   # el montículo (caja) y su cueva
PIEDRA_MONTICULO = (20, 9)                  # una piedrecita pegada al montículo: no se copia
# La cima del montículo lleva la sombra de la torre (arena oscura): aquí va la cima de una peña de la RUTA 127
CIMA_MONTICULO = {(16, 9): 0x080, (17, 9): 0x081, (18, 9): 0x081, (19, 9): 0x082, (19, 10): 0x0BF,
                  (20, 10): 0x082, (19, 11): 0x06D}
SITIO_MONTICULO = (16, 9)
VOLCAN_PENAS = [(PENA_GRANDE, 8, 12), (PENA_PEQUENA, 24, 9), (PENA_LARGA, 16, 19)]
CRATER_BASE, CRATER_FILAS = "MtChimney", 30   # la cima del MONTE CENIZO, sin la estación del teleférico
PUERTA_CRATER, METATILE_PUERTA = (22, 22), 0x25E   # la entrada de la GUARIDA MAGMA del CAMINO ESCABROSO
SUELO_CRATER, CENIZA = 0x271, 0x207
CENIZA_ZONAS = [(12, 16, 18, 21), (23, 16, 29, 21), (19, 25, 27, 29), (9, 13, 12, 16)]

# --- ISLA ARENOSA --------------------------------------------------------------------------------
# Una isla grande de arena con peñas y una cala al sur. Al oeste, un islote de hierba con
# árboles y hierba alta, con orilla de mar (la arena y la hierba no se tocan). Se llega desde la izquierda
# (la RUTA 129): primero el islote, luego la isla, donde espera DARÍO.
ARENOSA_PLANO = """
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmXXmmmmmmm
mmmmmmmmmmmmmmmmmmmmmmbbbbbbbbbbbbbbbbbmmmmmmmmXXmmmmmmm
mmmmmmmmmmmmmmmmmmmmbbbbbbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmbbbbsssssssssssssbbbbbbbmmmmmmmmmmmm
mmmXXmmmmmmmmXXmmmmbbbssssssssssssssssssbbbbbbmmmmmmmmmm
mmmXXmmmmmmmmXXmmmbbbsssssssssssssssssssssbbbbbbmmmmmmmm
mmmmmmmmmmmmmmmmmbbbssssssssssssssssssssssssbbbbmmmmmmmm
mmmmmmmmmmmmmmmmmbbsssssssssssssssssssssssssssbbmmmmmmmm
mmWWmmmmmmmmmmmmmbbsssssssssssssssssssssssssssbbbmmmXXmm
mmWWmmmmmmmmmmmmmbbsssssssssssssssssssssssssssbbbbmmXXmm
mmmmmmmmmmmmmmmmmbbssssssssssssssssssssssssssssbbbmmmmmm
mmmmmm.....mmmmmmbbsssssssssssssssssssssssssssssbbmmmmmm
mmmm....*....mmmmbbsssssssssssssssssssssssssssssbbmmmmmm
mmm..........mmmmbbsssssssssssssssssssssssssssssbbmmmmmm
mmm.TTTT.,,,.mmmmbbsssssssssssssssssssssssssssssbbmmmmmm
mmm.TTTT.,,,.mmmmbbsssssssssssssssssssssssssssssbbmmmmmm
mmm.TTTT..,,.mmmmbbsssssssssssssssssssssssssssssbbmmmmmm
mmm.TTTT.,,,.mmmmbbsssssssssssssssssssssssssssssbbmmmmmm
mmm.TTTT.,,..mmmmbbsssssssssssssssssssssssssssssbbmmmmmm
mmm.TTTT.....mmmmbbsssssssssssssssssssssssssssssbbmmXXmm
mmm.TTTT...*.mmmmbbsssssssssssssssssssssssssssssbbmmXXmm
mmm..........mmmmbbbssssssssssssssssssssssssssssbbmmmmmm
mmm..,,,,.TT.mmmmbbbssssssssssssssssssssssssssssbbmmmmmm
mmm.,,,,,,TT.mmmmmbbssssssssssssssssssssssssssssbbmmmmmm
mmm.,,,,,,TT.mmmmmbbssssssssssssssssssssssssssssbbmmmmmm
mmm..,,,,,,..mmmmmbbssssssssssssssssssssssssssssbbmmWWmm
mmm...,,,,.*.mmmmmbbssssssssssssbbbbssssssssssssbbmmWWmm
mmm.*..,,....mmmmmbbbsssssssssssbbbbssssssssssssbbmmmmmm
mmmm........mmmmmmmbbbssssssssssbbbbsssssssssssbbbmmmmmm
mmmmm......mmmmmmmmmbbbsssssssssbbbbbssssssssssbbbmmmmmm
mmmmmm....mmmmmmmmmmbbbbssssssssbbbbbsssssssssbbbmmmmmmm
mmmmmmmmmmmmmmmmmmmmmbbbbssssssbbbbbbbsssssssbbbbmmmmmmm
mmmmmmmmmmmmmmmmmmmmmmbbbbbssssbbbbbbbssssssbbbbmmmXXmmm
mXXmmmmmmmmmWWmmmmmmmmmbbbbbbssbbbbbbbbsssbbbbbmmmmXXmmm
mXXmmmmmmmmmWWmmmmmmmmmmmbbbbbbbbbbbbbbbbbbbbbmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmmmmmmmmbbbbbbbbbbbbbbbbbmmmmmmmmmmmm
mmmmmmmmXXmmmmmmmmmmmmmmmmmmmbbbbbbbbbbbbmmmmmmmmmmmmmmm
mmmmmmmmXXmmmmmmmmmmXXmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmXXmmmmmmmmmmmmmmmmmmmmmmXXmmmmmmmmmm
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmXXmmmmmmmmmm
"""
ARENOSA_PENAS = [(PENA_GRANDE, 22, 4), (PENA_PEQUENA, 34, 5), (PENA_LARGA, 40, 18), (PENA_GRANDE, 23, 21),
                 (PENA_PEQUENA, 40, 24)]
SITIO_DARIO = (21, 14)                           # mira a la izquierda, a donde se llega surfeando

# Dónde va cada objeto (los pone colocar_objetos.py; aquí se mueven al sitio que les toca en el dibujo nuevo)
SITIO_OBJETOS = {
    "FLAG_ITEM_SUR_BIG_PEARL": (30, 19),
    "FLAG_ITEM_SUR_SAFETY_GOGGLES": (44, 9),
    "FLAG_ITEM_TICKET_ISLA_ARENOSA": (6, 28),
    "FLAG_ITEM_SUR_PEARL_STRING": (45, 24),
}

GUARDIANES = {   # mapa: (x, y, especie, nivel sin reescalar, premio, flag)
    TORRE: (10, 2, "SPECIES_METAGROSS", 70, "ITEM_EXPERT_BELT", "FLAG_DUALOCKE_GUARDIAN_ISLA_RUINAS"),
    CRATER: (20, 16, "SPECIES_CHARIZARD", 70, "ITEM_HEAT_ROCK", "FLAG_DUALOCKE_GUARDIAN_VOLCAN"),
    ARENOSA: (41, 30, "SPECIES_SANDY_SHOCKS", 70, "ITEM_SMOOTH_ROCK", "FLAG_DUALOCKE_GUARDIAN_ARENOSA"),
}


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


COMPORTAMIENTOS = {v: k for k, v in co.comportamientos().items()}
ATRIBUTOS = co.atributos_tilesets()


def comportamiento(layout, metatile):
    if metatile < 512:
        return COMPORTAMIENTOS.get(ATRIBUTOS[layout["primary_tileset"]][metatile])
    return COMPORTAMIENTOS.get(ATRIBUTOS[layout["secondary_tileset"]][metatile - 512])


def mar_de(mapa):
    """El metatile de mar abierto (sin corriente) más común del mapa."""
    l, c = celdas_de(mapa)
    cuenta = {}
    for v in c:
        if comportamiento(l, v & 0x3FF) == "MB_OCEAN_WATER":
            cuenta[v] = cuenta.get(v, 0) + 1
    return max(cuenta, key=cuenta.get)


def isla(celdas, ancho, alto, origen, caja, semilla, sitio, mar):
    """Copia en `celdas` el islote de `origen` que contiene la casilla `semilla`: solo las casillas que no
    son mar y están unidas a ella (sin diagonales). Devuelve {(x, y) en el mapa nuevo: valor}.
    Es mar el mar abierto (`mar`) y las corrientes: las corrientes nunca se copian."""
    l, c = celdas_de(origen)
    w = l["width"]
    mar_origen = mar & 0x3FF
    es_mar = lambda v: (v & 0x3FF) == mar_origen or "CURRENT" in str(comportamiento(l, v & 0x3FF))  # noqa: E731
    x0, y0, x1, y1 = caja
    dentro = lambda x, y: x0 <= x < x1 and y0 <= y < y1 and not es_mar(c[y * w + x])  # noqa: E731
    assert dentro(*semilla), ("la semilla es mar", origen, semilla)
    vistos, cola = {semilla}, deque([semilla])
    while cola:
        x, y = cola.popleft()
        for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if n not in vistos and dentro(*n):
                vistos.add(n)
                cola.append(n)
    copiadas = {}
    for x, y in vistos:
        nx, ny = sitio[0] + x - x0, sitio[1] + y - y0
        assert 0 <= nx < ancho and 0 <= ny < alto, ("el islote no cabe", origen, caja)
        celdas[ny * ancho + nx] = copiadas[(nx, ny)] = c[y * w + x]
    return copiadas


_APRENDIZ = []


def aprendiz():
    if not _APRENDIZ:
        _APRENDIZ.append(at.Aprendiz())
    return _APRENDIZ[0]


def sello(origen, caja):
    """{(dx, dy): valor} con las casillas de roca (con colisión) de un trozo de mapa. El hueco de base secreta
    de las peñas se tapa con su pie."""
    l, c = celdas_de(origen)
    x0, y0, x1, y1 = caja
    trozo = {}
    for y in range(y0, y1):
        for x in range(x0, x1):
            v = c[y * l["width"] + x]
            if (v >> 10) & 3:
                if v & 0x3FF == BASE_SECRETA:
                    v = (v & ~0x3FF) | PIE_PENA
                trozo[(x - x0, y - y0)] = v
    return trozo


def poner_sellos(filas, sellos):
    """{(x, y): valor} de las peñas de una isla; comprueba que cada una va sobre arena."""
    fijas = {}
    for (origen, caja), sx, sy in sellos:
        for (dx, dy), v in sello(origen, caja).items():
            assert filas[sy + dy][sx + dx] == "s", ("la peña no va sobre arena", origen, caja, sx + dx, sy + dy)
            fijas[(sx + dx, sy + dy)] = v
    return fijas


def dibujar(plano, fijas, paredes=()):
    """Pinta un PLANO con autotile.py. `fijas`: {(x, y): valor} que pone el script (peñas, el montículo…); para
    las piezas de al lado cuentan como el terreno de alrededor. `paredes`: casillas fijas que las de al lado ven
    como pared (un acantilado copiado). Devuelve (filas, ancho, alto, celdas)."""
    filas = plano.strip().splitlines()
    alto, ancho = len(filas), len(filas[0])
    assert all(len(f) == ancho for f in filas), "las filas del plano no miden lo mismo"
    a = aprendiz()
    valor = lambda m: a.valor.get(m, m)  # noqa: E731
    rejilla = [[None if (x, y) in fijas or ch in "XWT" else TERRENO[ch] for x, ch in enumerate(f)]
               for y, f in enumerate(filas)]
    for x, y in paredes:
        rejilla[y][x] = "pared"
    pintadas = a.pintar(rejilla)
    c = [0] * (ancho * alto)
    for y in range(alto):
        for x in range(ancho):
            ch = filas[y][x]
            if (x, y) in fijas:
                c[y * ancho + x] = fijas[(x, y)]
            elif ch in ROCAS:
                # Cada roca es de 2 × 2: la esquina de arriba a la izquierda es la primera de su grupo
                x0 = x
                while x0 > 0 and filas[y][x0 - 1] == ch:
                    x0 -= 1
                y0 = y
                while y0 > 0 and filas[y0 - 1][x] == ch:
                    y0 -= 1
                c[y * ancho + x] = valor(ROCAS[ch][((y - y0) % 2) * 2 + (x - x0) % 2])
            elif ch != "T" and pintadas[y][x] is not None:
                v = pintadas[y][x]
                c[y * ancho + x] = (v & ~0x3FF) | FLORES if ch == "*" else v
    fallos = at.arboles_grandes(filas, c, valor)
    assert not fallos, "; ".join(fallos)
    return filas, ancho, alto, c


def crear_ruinas():
    ancho, alto = RUINAS_TAM
    mar = mar_de("Route131")
    c = [mar] * (ancho * alto)
    origen, caja, semilla, sitio = RUINAS_ISLOTE
    copiadas = isla(c, ancho, alto, origen, caja, semilla, sitio, mar)
    _, cp = celdas_de(origen)
    wp = LAYOUTS[json.loads(leer(f"data/maps/{origen}/map.json"))["layout"]]["width"]
    for (x, y), m in PUERTA_ABIERTA.items():
        c[(sitio[1] + y) * ancho + sitio[0] + x] = (cp[y * wp + x] & ~0x3FF) | m
    # La playa de abajo: se pinta el plano entero y se ponen solo sus filas. Arriba, las rocas del islote copiado
    # cuentan como pared; su arena y su mar, como el terreno de al lado.
    playa = RUINAS_PLAYA.strip().splitlines()
    assert len(playa) == alto - RUINAS_FILA_PLAYA
    arriba = ["".join("s" if (x, y) in copiadas else "m" for x in range(ancho)) for y in range(RUINAS_FILA_PLAYA)]
    fijas = {(x, y): c[y * ancho + x] for y in range(RUINAS_FILA_PLAYA) for x in range(ancho)}
    paredes = [(x, y) for (x, y), v in copiadas.items() if y < RUINAS_FILA_PLAYA and (v >> 10) & 3]
    _, _, _, pintadas = dibujar("\n".join(arriba + playa), fijas, paredes)
    for i in range(RUINAS_FILA_PLAYA * ancho, ancho * alto):
        c[i] = pintadas[i]
    for x, y in RUINAS_ROCA_ORILLA:
        nx, ny = sitio[0] + x, sitio[1] + y
        assert playa[ny - RUINAS_FILA_PLAYA][nx] == "m", "la roca de la orilla no va en el mar"
        c[ny * ancho + nx] = cp[y * wp + x]
    base = LAYOUTS[json.loads(leer("data/maps/Route131/map.json"))["layout"]]
    return guardar_layout(RUINAS, ancho, alto, c, base)


def crear_torre():
    base, c = celdas_de(TORRE_BASE)
    w = base["width"]
    ex, ey = ESCALERA_TORRE
    px, py = PARED_TORRE
    c[ey * w + ex] = c[py * w + px]
    gx, gy = GUARDIANES[TORRE][:2]
    assert (c[gy * w + gx] >> 10) & 3 == 0, "el guardián de la torre no está en el suelo"
    return guardar_layout(TORRE, w, base["height"], c, base)


def crear_volcan():
    filas = VOLCAN_PLANO.strip().splitlines()
    fijas = poner_sellos(filas, VOLCAN_PENAS)
    # El montículo: sus casillas de roca y la cueva
    origen, caja, cueva = MONTICULO
    l, cm = celdas_de(origen)
    mx, my = SITIO_MONTICULO
    for (dx, dy), v in sello(origen, caja).items():
        donde = (caja[0] + dx, caja[1] + dy)
        if donde in CIMA_MONTICULO:
            v = (v & ~0x3FF) | CIMA_MONTICULO[donde]
        if donde != PIEDRA_MONTICULO:
            fijas[(mx + dx, my + dy)] = v
    cx, cy = cueva_volcan()
    fijas[(cx, cy)] = cm[cueva[1] * l["width"] + cueva[0]]
    assert all(filas[y][x] == "s" for x, y in fijas), "el montículo o una peña no va sobre arena"
    assert filas[cy + 1][cx] == "s" and (cx, cy + 1) not in fijas, "no se llega a la cueva"
    _, ancho, alto, c = dibujar(VOLCAN_PLANO, fijas)
    base = LAYOUTS[json.loads(leer("data/maps/Route134/map.json"))["layout"]]
    return guardar_layout(VOLCAN, ancho, alto, c, base)


def cueva_volcan():
    """La cueva del montículo en la ISLA VOLCÁNICA (era la (17, 13) del PILAR CELESTE)."""
    (x0, y0, _, _), (cx, cy) = MONTICULO[1], MONTICULO[2]
    return SITIO_MONTICULO[0] + cx - x0, SITIO_MONTICULO[1] + cy - y0


def crear_crater():
    base, c = celdas_de(CRATER_BASE)
    w = base["width"]
    c = c[:w * CRATER_FILAS]
    _, cj = celdas_de("JaggedPass")
    wj = LAYOUTS[json.loads(leer("data/maps/JaggedPass/map.json"))["layout"]]["width"]
    puerta = cj[18 * wj + 16]
    assert puerta & 0x3FF == METATILE_PUERTA
    px, py = PUERTA_CRATER
    assert c[py * w + px] & 0x3FF == 0x274 and c[(py + 1) * w + px] & 0x3FF == SUELO_CRATER, "la puerta no va en la pared"
    c[py * w + px] = (c[py * w + px] & ~0x3FF & ~(3 << 10)) | METATILE_PUERTA
    for x0, y0, x1, y1 in CENIZA_ZONAS:
        for y in range(y0, y1):
            for x in range(x0, x1):
                v = c[y * w + x]
                if v & 0x3FF == SUELO_CRATER and not (v >> 10) & 3:
                    c[y * w + x] = (v & ~0x3FF) | CENIZA
    gx, gy = GUARDIANES[CRATER][:2]
    assert (c[gy * w + gx] >> 10) & 3 == 0, "el guardián del cráter no está en el suelo"
    return guardar_layout(CRATER, w, CRATER_FILAS, c, base)


def crear_arenosa():
    filas = ARENOSA_PLANO.strip().splitlines()
    _, ancho, alto, c = dibujar(ARENOSA_PLANO, poner_sellos(filas, ARENOSA_PENAS))
    for x, y in (GUARDIANES[ARENOSA][:2], SITIO_DARIO):
        assert filas[y][x] == "s" and not (c[y * ancho + x] >> 10) & 3, \
            ("el guardián o DARÍO no está en la arena", x, y)
    base = LAYOUTS[json.loads(leer("data/maps/Route129/map.json"))["layout"]]
    return guardar_layout(ARENOSA, ancho, alto, c, base)


# Rocas sueltas de mar (2 × 2): (arriba izq., arriba der., abajo izq., abajo der.)
ROCAS_SUELTAS = [(0x175, 0x176, 0x17D, 0x17E), (0x150, 0x151, 0x158, 0x159), (0x15A, 0x15B, 0x158, 0x159),
                 (0x33B, 0x33D, 0x17D, 0x17E)]


def quitar_rocas(carpeta, esquinas):
    """Quita rocas sueltas de mar (2 × 2, esquina de arriba a la izquierda) de una ruta y pone el mar de al lado.
    Se usa para abrir paso en la barrera de rocas hasta el borde por el que se entra a una isla. Se puede volver
    a lanzar: si la roca ya no está, no hace nada."""
    l, c = celdas_de(carpeta)
    w = l["width"]
    for x0, y0 in esquinas:
        cuatro = tuple(c[(y0 + j) * w + x0 + i] & 0x3FF for j in (0, 1) for i in (0, 1))
        alrededor = [c[y * w + x] for y in range(y0 - 1, y0 + 3) for x in range(x0 - 1, x0 + 3)
                     if 0 <= x < w and 0 <= y < l["height"] and not (x0 <= x <= x0 + 1 and y0 <= y <= y0 + 1)]
        mar = [v for v in alrededor if not (v >> 10) & 3 and comportamiento(l, v & 0x3FF) == "MB_OCEAN_WATER"]
        if all(comportamiento(l, m) == "MB_OCEAN_WATER" for m in cuatro):
            continue
        assert cuatro in ROCAS_SUELTAS, (carpeta, x0, y0, [hex(m) for m in cuatro])
        assert mar, (carpeta, x0, y0, "sin mar alrededor")
        valor = max(set(mar), key=mar.count)
        for j in (0, 1):
            for i in (0, 1):
                c[(y0 + j) * w + x0 + i] = valor
    with open(l["blockdata_filepath"], "wb") as f:
        f.write(struct.pack(f"<{w * l['height']}H", *c))


def mapa_json(carpeta, datos, objetos):
    """map.json con los personajes de este script; conserva los objetos de colocar_objetos.py."""
    ruta = f"data/maps/{carpeta}/map.json"
    os.makedirs(f"data/maps/{carpeta}", exist_ok=True)
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    datos["object_events"] = objetos + [o for o in anteriores.get("object_events", [])
                                        if str(o.get("flag", "")).startswith("FLAG_ITEM_")]
    datos["bg_events"] = [b for b in anteriores.get("bg_events", []) if b.get("type") == "hidden_item"]
    for o in datos["object_events"] + datos["bg_events"]:
        if o.get("flag") in SITIO_OBJETOS:
            o["x"], o["y"] = SITIO_OBJETOS[o["flag"]]
    datos["coord_events"] = []
    escribir(ruta, json.dumps(datos, indent=2, ensure_ascii=False) + "\n")


def guardian(carpeta):
    x, y, _, _, _, flag = GUARDIANES[carpeta]
    return {"local_id": f"LOCALID_{MAPAS[carpeta][4:]}_GUARDIAN", "graphics_id": "OBJ_EVENT_GFX_VAR_0",
            "x": x, "y": y, "elevation": 3, "movement_type": "MOVEMENT_TYPE_FACE_DOWN",
            "movement_range_x": 0, "movement_range_y": 0, "trainer_type": "TRAINER_TYPE_NONE",
            "trainer_sight_or_berry_tree_id": "0", "script": f"{carpeta}_EventScript_Pokemon", "flag": flag}


def script_guardian(carpeta, donde):
    _, _, especie, nivel, premio, flag = GUARDIANES[carpeta]
    # El nivel lo pone reescalar_niveles.py (regla "tope"): si el script ya existe, se conserva el suyo.
    # Si no, al volver a lanzar este script después de la cadena de niveles se perdería.
    ruta = f"data/maps/{carpeta}/scripts.inc"
    if os.path.exists(ruta):
        anterior = re.search(rf"setwildbattle {especie}, (\d+)", leer(ruta))
        if anterior:
            nivel = int(anterior.group(1))
    return f"""
@ Dualocke: el guardián de {donde}, un Pokémon fuerte que se puede capturar, como en las islas del
@ ferry (data/scripts/dualocke_islas.inc). Con semilla sale otro de su tipo (estaticos.py, islas()).
{carpeta}_OnTransition:
	setvar VAR_0x8004, {especie}
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

{carpeta}_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, {especie}
	setvar VAR_TEMP_9, {premio}
	call Dualocke_EventScript_AvisoIsla
	setwildbattle {especie}, {nivel}
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, {carpeta}_EventScript_PokemonSigue
	setflag {flag}
	call Dualocke_EventScript_PremioIsla
	release
	end

{carpeta}_EventScript_PokemonSigue::
	release
	end
"""


def cabecera_guardian(carpeta):
    return f"{carpeta}_MapScripts::\n\tmap_script MAP_SCRIPT_ON_TRANSITION, {carpeta}_OnTransition\n\t.byte 0\n"


def crear_mapas(l_ruinas, l_torre, l_volcan, l_crater, l_arenosa):
    comun = {"region": "REGION_HOENN", "requires_flash": False, "allow_running": True, "show_map_name": True,
             "battle_scene": "MAP_BATTLE_SCENE_NORMAL"}
    mar = {"music": "MUS_ROUTE119", "map_type": "MAP_TYPE_OCEAN_ROUTE", "allow_cycling": True,
           "allow_escaping": False}
    dentro = {"music": "MUS_MT_CHIMNEY", "map_type": "MAP_TYPE_UNDERGROUND", "allow_cycling": True,
              "allow_escaping": True}
    sx, sy = RUINAS_ISLOTE[3]
    puerta = (sx + PUERTA_TORRE[0], sy + PUERTA_TORRE[1])
    mapa_json(RUINAS, {"id": MAPAS[RUINAS], "name": RUINAS, "layout": l_ruinas, **mar, **comun,
                       "region_map_section": MAPSEC[RUINAS], "weather": "WEATHER_FOG_HORIZONTAL",
                       "connections": [{"map": RUINAS_RUTA, "offset": -RUINAS_DESPLAZAMIENTO, "direction": "down"}],
                       # 0: la torre; 1 y 2: el túnel entre la cueva de la orilla y la del montículo
                       "warp_events": [{"x": puerta[0], "y": puerta[1], "elevation": 3, "dest_map": MAPAS[TORRE],
                                        "dest_warp_id": "0"},
                                       {"x": sx + CUEVA_ORILLA[0], "y": sy + CUEVA_ORILLA[1], "elevation": 3,
                                        "dest_map": MAPAS[RUINAS], "dest_warp_id": "2"},
                                       {"x": sx + CUEVA_PILAR[0], "y": sy + CUEVA_PILAR[1], "elevation": 3,
                                        "dest_map": MAPAS[RUINAS], "dest_warp_id": "1"}]}, [])
    mapa_json(TORRE, {"id": MAPAS[TORRE], "name": TORRE, "layout": l_torre, **dentro, **comun,
                      "region_map_section": MAPSEC[TORRE], "weather": "WEATHER_NONE", "connections": None,
                      "warp_events": [{"x": x, "y": y, "elevation": 3, "dest_map": MAPAS[RUINAS], "dest_warp_id": "0"}
                                      for x, y in ENTRADA_TORRE]}, [guardian(TORRE)])
    cueva = cueva_volcan()
    mapa_json(VOLCAN, {"id": MAPAS[VOLCAN], "name": VOLCAN, "layout": l_volcan, **mar, **comun,
                       "region_map_section": MAPSEC[VOLCAN], "weather": "WEATHER_DROUGHT",
                       "connections": [{"map": "MAP_ROUTE134", "offset": 0, "direction": "up"}],
                       "warp_events": [{"x": cueva[0], "y": cueva[1], "elevation": 3, "dest_map": MAPAS[CRATER],
                                        "dest_warp_id": "0"}]}, [])
    mapa_json(CRATER, {"id": MAPAS[CRATER], "name": CRATER, "layout": l_crater, **comun,
                       "music": "MUS_MT_CHIMNEY", "map_type": "MAP_TYPE_ROUTE", "allow_cycling": True,
                       "allow_escaping": True,
                       "region_map_section": MAPSEC[CRATER], "weather": "WEATHER_DROUGHT", "connections": None,
                       "warp_events": [{"x": PUERTA_CRATER[0], "y": PUERTA_CRATER[1], "elevation": 3,
                                        "dest_map": MAPAS[VOLCAN], "dest_warp_id": "0"}]}, [guardian(CRATER)])
    mapa_json(ARENOSA, {"id": MAPAS[ARENOSA], "name": ARENOSA, "layout": l_arenosa, **mar, **comun,
                        "region_map_section": MAPSEC[ARENOSA], "weather": "WEATHER_SANDSTORM",
                        "connections": [{"map": "MAP_ROUTE129", "offset": 0, "direction": "left"}],
                        "warp_events": []},
                       [guardian(ARENOSA),
                        {"graphics_id": "OBJ_EVENT_GFX_COOLTRAINER_M", "x": SITIO_DARIO[0], "y": SITIO_DARIO[1], "elevation": 3,
                         "movement_type": "MOVEMENT_TYPE_FACE_LEFT", "movement_range_x": 0, "movement_range_y": 0,
                         "trainer_type": "TRAINER_TYPE_NORMAL", "trainer_sight_or_berry_tree_id": "4",
                         "script": "IslaArenosa_EventScript_Dario", "flag": "0"}])
    escribir(f"data/maps/{RUINAS}/scripts.inc", f"{RUINAS}_MapScripts::\n\t.byte 0\n")
    escribir(f"data/maps/{VOLCAN}/scripts.inc", f"{VOLCAN}_MapScripts::\n\t.byte 0\n")
    escribir(f"data/maps/{TORRE}/scripts.inc", cabecera_guardian(TORRE) + script_guardian(TORRE, "la ISLA DE RUINAS"))
    escribir(f"data/maps/{CRATER}/scripts.inc", cabecera_guardian(CRATER) + script_guardian(CRATER, "la ISLA VOLCÁNICA"))
    escribir(f"data/maps/{ARENOSA}/scripts.inc", cabecera_guardian(ARENOSA) + script_guardian(ARENOSA, "la ISLA ARENOSA")
             + DARIO)

    # Grupos: las islas con las rutas, los interiores con las mazmorras
    grupos = leer("data/maps/map_groups.json")
    salto = "\r\n" if "\r\n" in grupos else "\n"
    for grupo, carpetas in (("gMapGroup_TownsAndRoutes", (RUINAS, VOLCAN, ARENOSA)), ("gMapGroup_Dungeons", (TORRE, CRATER))):
        for carpeta in carpetas:
            if f'"{carpeta}"' in grupos:
                continue
            d = json.loads(grupos)
            ultimo = d[grupo][-1]
            a = f'"{ultimo}"{salto}'
            i = grupos.index(a, grupos.index(f'"{grupo}": ['))
            grupos = grupos[:i] + f'"{ultimo}",{salto}    "{carpeta}"{salto}' + grupos[i + len(a):]
    json.loads(grupos)
    escribir("data/maps/map_groups.json", grupos)

    # Las rutas se conectan con su isla
    for ruta_mapa, isla_mapa, direccion, desplazamiento in (("Route131", RUINAS, "up", RUINAS_DESPLAZAMIENTO),
                                                           ("Route134", VOLCAN, "down", 0),
                                                           ("Route129", ARENOSA, "right", 0)):
        ruta = f"data/maps/{ruta_mapa}/map.json"
        texto = leer(ruta)
        if MAPAS[isla_mapa] not in texto:
            texto = co.insertar_en_lista(texto, "connections", {"map": MAPAS[isla_mapa], "offset": desplazamiento,
                                                                "direction": direccion})
            json.loads(texto)
            escribir(ruta, texto)


DARIO = """
@ DARÍO es TRAINER_RED, que existía sin usar (zonas_nuevas.py le pone nombre y equipo)
IslaArenosa_EventScript_Dario::
	trainerbattle_single TRAINER_RED, IslaArenosa_Text_DarioIntro, IslaArenosa_Text_DarioDefeat
	msgbox IslaArenosa_Text_DarioPostBattle, MSGBOX_AUTOCLOSE
	end

IslaArenosa_Text_DarioIntro:
	.string "Con esta arena no se ve nada…\\n"
	.string "¡Pero a ti sí te veo!$"

IslaArenosa_Text_DarioDefeat:
	.string "Se me ha metido arena en los ojos.$"

IslaArenosa_Text_DarioPostBattle:
	.string "Al sur de esta isla vive un\\n"
	.string "POKéMON enorme. Ten cuidado.$"
"""


def zonas_region():
    ruta = "src/data/region_map/region_map_sections.json"
    texto = leer(ruta)
    secciones = {s["id"]: s for s in json.loads(texto)["map_sections"]}
    r131, r134, r129 = (secciones[f"MAPSEC_ROUTE_{n}"] for n in (131, 134, 129))
    for mapsec, nombre, x, y in (
            ("MAPSEC_ISLA_DE_RUINAS", "ISLA DE RUINAS", r131["x"] + 1, r131["y"] - 1),
            ("MAPSEC_ISLA_VOLCANICA", "ISLA VOLCÁNICA", r134["x"], r134["y"] + 1),
            ("MAPSEC_ISLA_ARENOSA", "ISLA ARENOSA", r129["x"] + r129["width"], r129["y"])):
        assert len(nombre) <= 16, nombre
        if f'"{mapsec}"' not in texto:
            texto = co.insertar_en_lista(texto, "map_sections", {"id": mapsec, "name": nombre, "x": x, "y": y,
                                                                 "width": 1, "height": 1})
    json.loads(texto)
    escribir(ruta, texto)


# El borde de cada ruta por el que se entra a su isla estaba fuera de la barrera de rocas: no se llegaba (lo vio
# Jorge con alcance.py, #97/#99). Se quita una roca suelta de la barrera, por dentro (lejos de las conexiones
# de los lados): la que deja el paso más corto sin pasar por corrientes.
PASOS = {"Route129": [(46, 24)], "Route131": [(7, 12)], "Route134": [(9, 21)]}


def main():
    crear_mapas(crear_ruinas(), crear_torre(), crear_volcan(), crear_crater(), crear_arenosa())
    for ruta, rocas in PASOS.items():
        quitar_rocas(ruta, rocas)
    zonas_region()
    print("Dualocke: ISLA DE RUINAS, ISLA VOLCÁNICA e ISLA ARENOSA creadas")


if __name__ == "__main__":
    main()
