#!/usr/bin/env python3
"""
Dualocke: dibujar zonas nuevas con las piezas del juego original, aprendiendo de los mapas de Hoenn.

Se usa desde los scripts que crean zonas (crear_*.py):

    import autotile as at
    piezas = at.Aprendiz()                      # mira todos los mapas exteriores originales
    celdas = piezas.pintar(rejilla_de_terrenos)  # terrenos -> metatiles generales, con sus bordes
    at.revisar(celdas, ancho, alto, layout)      # parejas de vecinos que el juego original nunca usa

**Cómo funciona.** Cada casilla de los mapas originales tiene un *terreno* (por su comportamiento: mar,
bajío, arena, estanque, hierba alta, hierba muy alta, suelo o pared). Para cada terreno, la pieza que se usa
depende de los terrenos de sus 8 vecinas: el borde de un estanque se dibuja en el agua y la orilla de abajo
en la hierba (0x002); la orilla de la arena se dibuja en el agua (0x125, 0x123…). El aprendiz guarda, para
cada terreno y cada combinación de vecinas, la pieza más usada en el juego. Al pintar busca la combinación
exacta; si no la hay, la de las 4 vecinas de los lados; si tampoco, la pieza normal del terreno.

Solo aprende piezas **generales** (las del tileset General, 0x000-0x1FF), que valen en cualquier mapa.
Las piezas propias de cada sitio (árboles de AZULIZA, termas de LAVACALDA…) las pone cada script.
"""

import json
import os
import struct
import sys
from collections import Counter, defaultdict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import colocar_objetos as co  # noqa: E402

# Terrenos que se pintan solos y su pieza normal (la de en medio de una zona grande)
TERRENOS = {
    "mar": 0x170, "bajio": 0x19E, "arena": 0x124, "estanque": 0x0A1,
    "hierba_alta": 0x00D, "hierba_larga": 0x015, "suelo": 0x001,
    "risco": 0x088, "camino": 0x121,
}
# El risco: la franja de roca de una casilla que separa la arena de una playa de la hierba (RUTA 104).
# Sus piezas son de pared (con colisión); la escalera para subirlo es 0x0AF + 0x0CF (la pone cada script).
RISCO = {0x06F, 0x072, 0x074, 0x075, 0x079, 0x07C, 0x080, 0x082, 0x086, 0x087, 0x088, 0x089, 0x090, 0x092}
ESCALERA_RISCO = (0x0AF, 0x0CF)
# El camino de tierra de las praderas (RUTA 117, RUTA 112…): pieza del medio y sus bordes con la hierba
CAMINO = {0x118, 0x119, 0x11A, 0x120, 0x121, 0x122, 0x128, 0x129, 0x12A}
POR_COMPORTAMIENTO = {
    "MB_OCEAN_WATER": "mar", "MB_SHALLOW_WATER": "bajio", "MB_SAND": "arena", "MB_POND_WATER": "estanque",
    "MB_TALL_GRASS": "hierba_alta", "MB_LONG_GRASS": "hierba_larga", "MB_NORMAL": "suelo",
}
# Piezas que se pueden aprender para cada terreno (las demás de su comportamiento son otras cosas: casas,
# caminos, carteles…). Salen de mirar el juego: hierba con orilla de estanque, arena con borde, etc.
PERMITIDAS = {
    "suelo": {0x001, 0x002},
    "hierba_alta": {0x00D},
    "hierba_larga": {0x015},
    "risco": RISCO,
    "camino": CAMINO,
}
# Grupos para cuando no hay una combinación exacta en el juego
GRUPO = {"suelo": "tierra", "hierba_alta": "tierra", "hierba_larga": "tierra"}
VECINAS = [(-1, -1), (0, -1), (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1), (1, 1)]
LADOS = [1, 3, 4, 6]   # posiciones de VECINAS que son arriba, izquierda, derecha y abajo
NUEVOS = ("Marisma", "Playa", "Bosque", "Isla", "Cumbre", "Desierto", "Ruinas", "Gruta", "Mansion", "Cienaga", "Cantera", "Prado")


def _mapas_originales():
    for carpeta in sorted(os.listdir("data/maps")):
        if "Frlg" in carpeta or carpeta.startswith("_") or carpeta.startswith(NUEVOS):
            continue
        ruta = f"data/maps/{carpeta}/map.json"
        if not os.path.exists(ruta):
            continue
        m = json.load(open(ruta, encoding="utf-8"))
        if m.get("map_type") in ("MAP_TYPE_ROUTE", "MAP_TYPE_TOWN", "MAP_TYPE_CITY", "MAP_TYPE_OCEAN_ROUTE"):
            yield carpeta, m


class Aprendiz:
    def __init__(self):
        comp = {v: k for k, v in co.comportamientos().items()}
        attrs = co.atributos_tilesets()
        layouts = co.cargar_layouts()
        self.completas = defaultdict(Counter)   # (terreno, 8 vecinas) -> piezas
        self.lados = defaultdict(Counter)       # (terreno, 4 lados) -> piezas
        self.gruesas = defaultdict(Counter)     # lo mismo, con las vecinas agrupadas (tierra, agua, pared)
        self.gruesas_lados = defaultdict(Counter)
        self.parejas = defaultdict(set)         # secundario -> parejas (izq, der) y (arriba, abajo) vistas
        self.valor = {}                         # metatile -> valor más común (colisión y altura)
        cuenta_valor = defaultdict(Counter)
        for carpeta, m in _mapas_originales():
            l = layouts[m["layout"]]
            w, h = l["width"], l["height"]
            c = struct.unpack(f"<{w * h}H", open(l["blockdata_filepath"], "rb").read())
            prim, sec = attrs[l["primary_tileset"]], attrs[l["secondary_tileset"]]

            def terreno(x, y):
                if not (0 <= x < w and 0 <= y < h):
                    return None
                v = c[y * w + x]
                mt = v & 0x3FF
                b = comp.get(prim[mt] if mt < 512 else sec[mt - 512] if mt - 512 < len(sec) else None)
                t = POR_COMPORTAMIENTO.get(b)
                if mt in RISCO and (v >> 10) & 3:
                    return "risco"
                if mt in CAMINO:
                    return "camino"
                if t in ("suelo", "arena") and (v >> 10) & 3:
                    return "pared"
                return t or "pared"

            parejas = self.parejas[l["secondary_tileset"]]
            for y in range(h):
                for x in range(w):
                    v = c[y * w + x]
                    mt = v & 0x3FF
                    if x + 1 < w:
                        parejas.add(("h", mt, c[y * w + x + 1] & 0x3FF))
                    if y + 1 < h:
                        parejas.add(("v", mt, c[(y + 1) * w + x] & 0x3FF))
                    if mt >= 0x200:
                        continue
                    cuenta_valor[mt][v] += 1
                    t = terreno(x, y)
                    if t not in TERRENOS or (t in PERMITIDAS and mt not in PERMITIDAS[t]):
                        continue
                    vec = tuple(terreno(x + dx, y + dy) or t for dx, dy in VECINAS)
                    self.completas[(t, vec)][mt] += 1
                    self.lados[(t, tuple(vec[i] for i in LADOS))][mt] += 1
                    gruesas = tuple(GRUPO.get(v, v) for v in vec)
                    self.gruesas[(t, gruesas)][mt] += 1
                    self.gruesas_lados[(t, tuple(gruesas[i] for i in LADOS))][mt] += 1
        self.valor = {mt: vs.most_common(1)[0][0] for mt, vs in cuenta_valor.items()}

    def pieza(self, terreno, vecinas):
        """La pieza general para un terreno con esas 8 vecinas (terrenos o None fuera del mapa). Busca la
        combinación exacta; si no la hay en el juego, agrupa las vecinas en tierra / agua / pared (para el
        borde de un estanque da igual que al lado haya hierba o hierba alta)."""
        vec = tuple(v or terreno for v in vecinas)
        gruesas = tuple(GRUPO.get(v, v) for v in vec)
        for tabla, clave in ((self.completas, (terreno, vec)), (self.gruesas, (terreno, gruesas)),
                             (self.lados, (terreno, tuple(vec[i] for i in LADOS))),
                             (self.gruesas_lados, (terreno, tuple(gruesas[i] for i in LADOS)))):
            if tabla.get(clave):
                return tabla[clave].most_common(1)[0][0]
        return TERRENOS[terreno]

    def pintar(self, rejilla):
        """rejilla: lista de filas de terrenos (o None donde el script pone otra cosa). Devuelve una lista de
        filas de valores completos (metatile con su colisión y altura) o None."""
        alto, ancho = len(rejilla), len(rejilla[0])
        salida = []
        for y in range(alto):
            fila = []
            for x in range(ancho):
                t = rejilla[y][x]
                if t not in TERRENOS:
                    # None (lo pone el script y cuenta como el terreno de al lado) u otra cosa, como "pared"
                    # (lo pone el script y sus vecinas lo ven como pared: un acantilado copiado)
                    fila.append(None)
                    continue
                vec = []
                for dx, dy in VECINAS:
                    nx, ny = x + dx, y + dy
                    vec.append(rejilla[ny][nx] if 0 <= nx < ancho and 0 <= ny < alto else None)
                # Lo que no es un terreno que se pinta solo (árboles, rocas…) cuenta como pared
                vec = [v if v in TERRENOS or v is None else "pared" for v in vec]
                mt = self.pieza(t, vec)
                # Esquina de abajo a la derecha de una charca en la arena: el aprendiz elige 0x11B (la orilla
                # que sigue hacia abajo), que deja un pico de agua. Como en el lado izquierdo (0x125), va el
                # borde derecho recto (0x123); la orilla de abajo ya está en la fila de arena.
                if mt == 0x11B and vec[4] == "arena" and vec[6] == "arena":
                    mt = 0x123
                fila.append(self.valor.get(mt, mt))
            salida.append(fila)
        return salida

    def revisar(self, celdas, ancho, alto, secundario):
        """Parejas de vecinos que no salen en ningún mapa original con ese secundario ni con ningún otro
        (para las piezas generales). Devuelve [(x, y, 'h' o 'v', pieza, vecina)]."""
        vistas = self.parejas.get(secundario, set())
        todas = set().union(*self.parejas.values())
        raras = []
        for y in range(alto):
            for x in range(ancho):
                a = celdas[y * ancho + x] & 0x3FF
                for d, nx, ny in (("h", x + 1, y), ("v", x, y + 1)):
                    if nx >= ancho or ny >= alto:
                        continue
                    b = celdas[ny * ancho + nx] & 0x3FF
                    pareja = (d, a, b)
                    general = a < 0x200 and b < 0x200
                    if pareja not in vistas and not (general and pareja in todas):
                        raras.append((x, y, d, a, b))
        return raras


# Árboles normales de Hoenn (los de las rutas: RUTA 117, RUTA 123…), de una casilla de ancho. Dentro del bosque se
# alternan 0x0C6 y 0x0C7; la última fila de una franja (debajo hay suelo) es el pie, 0x016. La copa del árbol de
# debajo se pinta en la casilla de encima, que se puede pisar: 0x00E sobre hierba y 0x025 sobre hierba alta.
ARBOL_INTERIOR, ARBOL_PIE = (0x0C6, 0x0C7), 0x016
ARBOL_COPA, ARBOL_COPA_HIERBA_ALTA = 0x00E, 0x025


def arbol_normal(filas, x, y, letra="T"):
    """La pieza del árbol normal de la casilla (x, y) del plano (fuera del plano, abajo, cuenta como árbol)."""
    alto, ancho = len(filas), len(filas[0])
    debajo = y + 1 >= alto or not 0 <= x < ancho or filas[y + 1][x] == letra
    # Con un patrón fijo que no parece una rejilla, como en las rutas
    return ARBOL_INTERIOR[(x * 7 + y * 3 + (x * y) % 5) % 2] if debajo else ARBOL_PIE


def copa_normal(filas, x, y, pieza, letra="T", hierba_alta=","):
    """Si debajo de (x, y) empieza un árbol normal, la casilla lleva su copa: devuelve la pieza con copa, o None."""
    if y + 1 >= len(filas) or filas[y + 1][x] != letra:
        return None
    if filas[y][x] == hierba_alta:
        return ARBOL_COPA_HIERBA_ALTA
    if pieza == 0x001 or filas[y][x] == "*":
        return ARBOL_COPA
    return None


# Árboles grandes (gráficos generales, los del BOSQUE PETALIA y la ZONA SAFARI): 2 de ancho, por parejas de
# columnas pares. Piezas (izquierda, derecha). La copa sobre hierba normal es 0x1CE; sobre hierba alta, 0x1C6.
COPA, COPA_HIERBA_ALTA = (0x1CE, 0x1CF), (0x1C6, 0x1C7)
CUERPO, TRONCO, BASE = (0x1D4, 0x1D5), (0x1DC, 0x1DD), (0x1E4, 0x1E5)
CUERPO_BORDE, BASE_BORDE = (0x1D6, 0x1D7), (0x1E6, 0x1E7)


def arboles_grandes(filas, c, valor, letra="T", hierba_alta=","):
    """Pone en c (lista de valores, fila a fila) los árboles grandes de las casillas `letra` del plano.
    Columna de árboles entre dos claros: copa, cuerpo, [tronco, cuerpo]…, base (largo impar). Si toca el
    borde de arriba no lleva copa; si toca el de abajo, no lleva base y acaba en tronco (largo impar).
    Devuelve la lista de fallos (filas de largo imposible, árboles sin pareja)."""
    alto, ancho = len(filas), len(filas[0])
    es = lambda x, y, ch: 0 <= x < ancho and 0 <= y < alto and filas[y][x] == ch  # noqa: E731
    fallos = []
    for x in range(0, ancho, 2):
        y = 0
        while y < alto:
            if not es(x, y, letra):
                y += 1
                continue
            if not es(x + 1, y, letra):
                fallos.append(f"árbol grande sin pareja en {(x, y)}")
            y0 = y
            while y < alto and es(x, y, letra):
                y += 1
            y1 = y - 1
            largo, arriba, abajo = y1 - y0 + 1, y0 > 0, y1 < alto - 1
            if arriba and abajo and (largo < 3 or largo % 2 == 0) or arriba and not abajo and largo % 2 == 0 \
                    or not arriba and abajo and largo < 2:
                fallos.append(f"árbol grande de largo {largo} en x {x}, filas {y0}-{y1}")
            for yy in range(y0, y1 + 1):
                if arriba and yy == y0:
                    tipo = "copa"
                elif abajo and yy == y1:
                    tipo = "base"
                elif arriba:
                    tipo = "cuerpo" if (yy - y0) % 2 else "tronco"
                elif abajo:
                    tipo = "cuerpo" if (y1 - yy) % 2 else "tronco"
                else:
                    tipo = "cuerpo" if yy % 2 == 0 else "tronco"
                izq, der = {"copa": COPA, "cuerpo": CUERPO, "tronco": TRONCO, "base": BASE}[tipo]
                if tipo == "copa" and (es(x, yy - 1, hierba_alta) or es(x + 1, yy - 1, hierba_alta)):
                    izq, der = COPA_HIERBA_ALTA
                if tipo == "cuerpo":
                    izq = CUERPO_BORDE[0] if x > 0 and not es(x - 1, yy, letra) else izq
                    der = CUERPO_BORDE[1] if x + 2 < ancho and not es(x + 2, yy, letra) else der
                if tipo == "base":
                    izq = BASE_BORDE[0] if x > 0 and not es(x - 1, yy, letra) else izq
                    der = BASE_BORDE[1] if x + 2 < ancho and not es(x + 2, yy, letra) else der
                c[yy * ancho + x] = valor(izq)
                if x + 1 < ancho:
                    c[yy * ancho + x + 1] = valor(der)
    return fallos
