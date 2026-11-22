#!/usr/bin/env python3
"""
Dualocke: pone en español los textos que están dibujados en los gráficos (no son texto del juego).

Uso (desde la raíz del repo):
    python3 tools/dualocke/textos_graficos.py              # cambia los PNG
    python3 tools/dualocke/textos_graficos.py --ver /tmp/x  # además guarda cómo queda cada uno en pantalla

Cada gráfico se monta como se ve en el juego (con su tilemap, o poniendo uno al lado del otro los trozos
de un sprite), se borra el texto inglés de un recuadro y se escribe el español con una de las fuentes
del juego (graphics/fonts/latin_*.png), con los colores del original. Luego se devuelve cada píxel a su
tile. Se puede volver a lanzar: borra lo que haya en el recuadro y vuelve a escribir.

Por qué: el bot que se pasa el juego vio en inglés el PC ("PKMN DATA", "PARTY POKéMON", "CLOSE BOX"),
la ficha de entrenador ("TRAINER CARD", "BADGES"), el dinero de las tiendas ("MONEY") y el POKéNAV
(Jorge, 22/11/2026).
"""

import os
import re
import struct
import sys
from collections import Counter

from PIL import Image

RAIZ = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

# ---------------------------------------------------------------- fuentes del juego

FUENTES = {  # nombre: (tabla de anchos en src/fonts.c, primera fila de las mayúsculas en el glifo)
    "normal": ("gFontNormalLatinGlyphWidths", 3),
    "small": ("gFontSmallLatinGlyphWidths", 4),
    "narrow": ("gFontNarrowLatinGlyphWidths", 3),
    "short": ("gFontShortLatinGlyphWidths", 3),
}
_cache = {}


def _charmap():
    if "cm" not in _cache:
        cm = {" ": 0}
        texto = open(os.path.join(RAIZ, "charmap.txt"), encoding="utf-8").read()
        for m in re.finditer(r"^'(.)'\s*=\s*([0-9A-F]{2})\s*$", texto, re.M):
            cm.setdefault(m.group(1), int(m.group(2), 16))
        _cache["cm"] = cm
    return _cache["cm"]


def _anchos(fuente):
    if ("anchos", fuente) not in _cache:
        s = open(os.path.join(RAIZ, "src/fonts.c"), encoding="utf-8").read()
        t = s[s.index(FUENTES[fuente][0] + "[]"):]
        _cache[("anchos", fuente)] = [int(x) for x in re.findall(r"\d+", t[t.index("{"):t.index("}")])]
    return _cache[("anchos", fuente)]


def _glifo(fuente, codigo):
    if ("png", fuente) not in _cache:
        _cache[("png", fuente)] = Image.open(os.path.join(RAIZ, f"graphics/fonts/latin_{fuente}.png")).load()
    px = _cache[("png", fuente)]
    gx, gy = (codigo % 16) * 16, (codigo // 16) * 16
    return [[px[gx + x, gy + y] for x in range(16)] for y in range(16)]


def dibujo(texto, fuente, negrita=False, letra_extra=0):
    """{(x, y): 1 letra / 2 sombra}. y = 0 es la fila de arriba de las mayúsculas (los acentos, y < 0)."""
    cm, anchos, arriba = _charmap(), _anchos(fuente), FUENTES[fuente][1]
    pix, x = {}, 0
    for ch in texto:
        c = cm[ch]
        g = _glifo(fuente, c)
        ancho = anchos[c]
        for gy in range(16):
            for gx in range(ancho):
                v = g[gy][gx]
                if v == 1:
                    pix[(x + gx, gy - arriba)] = 1
                    if negrita:
                        pix[(x + gx + 1, gy - arriba)] = 1
                elif v == 2 and (x + gx, gy - arriba) not in pix:
                    pix[(x + gx, gy - arriba)] = 2
        x += ancho + (1 if negrita else 0) + letra_extra
    if negrita:  # la sombra no puede quedar encima de la letra engordada
        pix = {p: v for p, v in pix.items() if v == 1 or (p[0] - 1, p[1]) not in pix or pix[(p[0] - 1, p[1])] != 1}
    return pix


# Letras de 5 píxeles de alto, como las de "MONEY" del dinero de las tiendas (no hay ninguna fuente así)
MINI = {
    "D": ["1110", "1001", "1001", "1001", "1110"],
    "I": ["1", "1", "1", "1", "1"],
    "N": ["1001", "1101", "1011", "1001", "1001"],
    "E": ["1111", "1000", "1110", "1000", "1111"],
    "R": ["1110", "1001", "1110", "1010", "1001"],
    "O": ["0110", "1001", "1001", "1001", "0110"],
}


# Letras gruesas de 6 píxeles de alto, como las de "BADGES" de la ficha de entrenador: A, D, E y S copiadas de
# ahí; M y L dibujadas igual
MEDALLAS = {
    "M": ["1100011", "1110111", "1111111", "1101011", "1100011", "1100011"],
    "E": ["11111", "11000", "11110", "11000", "11000", "11111"],
    "D": ["111110", "110011", "110011", "110011", "110011", "111110"],
    "A": ["001100", "011110", "110011", "111111", "110011", "110011"],
    "L": ["11000", "11000", "11000", "11000", "11000", "11111"],
    "S": ["0111110", "1100000", "0111110", "0000011", "0000011", "1111110"],
}


def dibujo_mini(texto, letras=MINI):
    """Con letras dibujadas a mano: '1' es la letra; '0' o '.', nada; otro número, ese color de la paleta."""
    pix, x = {}, 0
    for ch in texto:
        filas = letras[ch]
        for y, fila in enumerate(filas):
            for dx, v in enumerate(fila):
                if v == "1":
                    pix[(x + dx, y)] = 1
                elif v not in "0.":
                    pix[(x + dx, y)] = ("color", int(v, 16))
        x += len(filas[0]) + 1
    return pix


# ---------------------------------------------------------------- montar y desmontar los gráficos

class Tiles:
    """Un PNG de tiles que se ve en pantalla a través de uno o varios tilemaps."""

    def __init__(self, png, tilemaps, base=0):
        self.png = os.path.join(RAIZ, png)
        self.im = Image.open(self.png)
        w, h = self.im.size
        px = self.im.load()
        self.ancho_tiles = w // 8
        self.tiles = [[[px[tx * 8 + x, ty * 8 + y] for x in range(8)] for y in range(8)]
                      for ty in range(h // 8) for tx in range(w // 8)]
        self.base = base
        self.mapas, self.rutas, self.mapas_cambiados = {}, {}, set()
        for nombre, (ruta, ancho, alto) in tilemaps.items():
            datos = open(os.path.join(RAIZ, ruta), "rb").read()
            self.mapas[nombre] = (list(struct.unpack(f"<{len(datos) // 2}H", datos)), ancho, alto)
            self.rutas[nombre] = os.path.join(RAIZ, ruta)

    def pantalla(self, nombre):
        mapa, ancho, alto = self.mapas[nombre]
        g = [[0] * (ancho * 8) for _ in range(alto * 8)]
        for i in range(ancho * alto):
            t, hf, vf = self._tile(mapa[i])
            if t is None:
                continue
            cx, cy = i % ancho * 8, i // ancho * 8
            for y in range(8):
                for x in range(8):
                    g[cy + y][cx + x] = self.tiles[t][7 - y if vf else y][7 - x if hf else x]
        return g

    def _tile(self, e):
        t = (e & 0x3FF) - self.base
        return (t if 0 <= t < len(self.tiles) else None), e >> 10 & 1, e >> 11 & 1

    def usados(self):
        return {self._tile(e)[0] for m, an, al in self.mapas.values() for e in m[:an * al]} - {None}

    def guardar_pantalla(self, nombre, g):
        """Devuelve a los tiles lo cambiado en la pantalla. Si un tile se usa en varios sitios y solo cambia en
        alguno (por ejemplo, un trozo de fondo liso en el que ahora entra una letra), ahí se pone un tile nuevo,
        de los que no usa ningún tilemap, y se cambia el tilemap."""
        mapa, ancho, alto = self.mapas[nombre]
        por_tile = {}
        for i in range(ancho * alto):
            t, hf, vf = self._tile(mapa[i])
            if t is None:
                continue
            cx, cy = i % ancho * 8, i // ancho * 8
            # el dibujo del tile tal como está guardado (deshaciendo el volteo)
            tile = [[g[cy + (7 - y if vf else y)][cx + (7 - x if hf else x)] for x in range(8)] for y in range(8)]
            por_tile.setdefault(t, []).append((i, tile))
        libres = sorted(set(range(len(self.tiles))) - self.usados())
        for t, sitios in por_tile.items():
            distintos = []
            for _, tile in sitios:
                if tile not in distintos:
                    distintos.append(tile)
            if distintos == [self.tiles[t]]:
                continue
            if len(distintos) == 1:  # cambia igual en todos sus sitios (si sale en otro tilemap, mirarlo con --ver)
                self.tiles[t] = distintos[0]
                continue
            for i, tile in sitios:
                if tile == self.tiles[t]:
                    continue
                igual = next((n for n in range(len(self.tiles)) if self.tiles[n] == tile), None)
                if igual is None:
                    if not libres:
                        raise SystemExit(f"{self.png}: no quedan tiles libres para el texto nuevo")
                    igual = libres.pop(0)
                    self.tiles[igual] = tile
                # mismo tile nuevo, sin volteo y con la misma paleta
                mapa[i] = (mapa[i] & 0xF000) | (igual + self.base)
            self.mapas_cambiados.add(nombre)

    def escribir(self):
        px = self.im.load()
        for i, tile in enumerate(self.tiles):
            tx, ty = i % self.ancho_tiles, i // self.ancho_tiles
            for y in range(8):
                for x in range(8):
                    px[tx * 8 + x, ty * 8 + y] = tile[y][x]
        self.im.save(self.png)
        for nombre in self.mapas_cambiados:
            m = self.mapas[nombre][0]
            open(self.rutas[nombre], "wb").write(struct.pack(f"<{len(m)}H", *m))


class Tira:
    """Un sprite hecho de trozos: el PNG los tiene uno debajo de otro (de `alto` filas) y en pantalla van seguidos."""

    def __init__(self, png, alto):
        self.png = os.path.join(RAIZ, png)
        self.im = Image.open(self.png)
        self.alto = alto

    def pantalla(self, _=None):
        w, h = self.im.size
        px = self.im.load()
        n = h // self.alto
        return [[px[x % w, (x // w) * self.alto + y] for x in range(w * n)] for y in range(self.alto)]

    def guardar_pantalla(self, _, g):
        w, _h = self.im.size
        px = self.im.load()
        for y in range(self.alto):
            for x in range(len(g[0])):
                px[x % w, (x // w) * self.alto + y] = g[y][x]

    def escribir(self):
        self.im.save(self.png)


# ---------------------------------------------------------------- borrar y escribir

def cambiar_texto(g, caja, texto, fuente="normal", letra=1, sombra=2, borrar=None, contorno=None,
                  negrita=False, alinear="centro", arriba=0, letra_extra=0):
    """Borra en `caja` (x0, y0, x1, y1, incluidos) los píxeles de los colores `borrar` y escribe `texto`.
    letra: índice de la paleta de la letra (o {fila: índice}, para los degradados); sombra: el de la sombra
    (None, sin sombra); contorno: un borde de un píxel alrededor de la letra. arriba: fila de la pantalla en
    la que empiezan las mayúsculas. alinear: "izq", "centro", "der" (en el sitio del texto que había) o un x."""
    x0, y0, x1, y1 = caja
    borrar = set(borrar if borrar is not None else [letra] if isinstance(letra, int) else letra.values())
    borrar |= {c for c in (sombra, contorno) if c is not None}
    viejo = [(x, y) for y in range(y0, y1 + 1) for x in range(x0, x1 + 1) if g[y][x] in borrar]
    if not viejo:
        raise SystemExit(f"no hay texto que borrar en {caja}")
    vx0, vx1 = min(x for x, _ in viejo), max(x for x, _ in viejo)
    for y in range(y0, y1 + 1):
        fondo = Counter(g[y][x] for x in range(x0, x1 + 1) if g[y][x] not in borrar).most_common(1)
        for x in range(x0, x1 + 1):
            if g[y][x] in borrar and fondo:
                g[y][x] = fondo[0][0]
    if fuente in ("mini", "medallas"):
        pix = dibujo_mini(texto, MINI if fuente == "mini" else MEDALLAS)
    else:
        pix = dibujo(texto, fuente, negrita, letra_extra)
    if fuente == "normal" and max(x for x, _ in pix) + 3 > x1 - x0:  # no cabe: la fuente estrecha del juego
        pix = dibujo(texto, "narrow", negrita, letra_extra)
    if sombra is None:
        pix = {p: v for p, v in pix.items() if v == 1}
    if contorno is not None:
        letras = [p for p, v in pix.items() if v == 1]
        for (x, y) in letras:
            for dx in (-1, 0, 1):
                for dy in (-1, 0, 1):
                    pix.setdefault((x + dx, y + dy), 3)
    # Se centra igual el texto viejo que el nuevo (con su sombra y su contorno), así se puede volver a lanzar
    nx0, nx1 = min(x for x, _ in pix), max(x for x, _ in pix)
    if alinear == "izq":
        ox = vx0 - nx0
    elif alinear == "der":
        ox = vx1 - nx1
    elif alinear == "centro":
        ox = (vx0 + vx1 - nx0 - nx1 + 1) // 2
    else:
        ox = alinear
    oy = arriba
    for (x, y), v in pix.items():
        sx, sy = ox + x, oy + y
        if not (x0 <= sx <= x1 and y0 <= sy <= y1):
            if v == 1 and sy >= y0:  # un acento que se sale por arriba se pierde; una letra, no
                raise SystemExit(f"'{texto}' no cabe en {caja} (sale en {sx}, {sy})")
            continue
        if v == 1:
            g[sy][sx] = letra[y] if isinstance(letra, dict) else letra
        elif isinstance(v, tuple):
            g[sy][sx] = v[1]
        elif v == 2:
            g[sy][sx] = sombra
        else:
            g[sy][sx] = contorno


# ---------------------------------------------------------------- los cambios

def _opcion(png, texto, icono):
    """Botones del menú del POKéNAV: 4 trozos de 32x16; letra 1, sombra 2, fondo 8. El texto va a la izquierda
    (después del cuadradito de color, si lo hay)."""
    return (Tira(png, 16), {None: [dict(caja=(16 if icono else 7, 2, 126, 15), texto=texto, alinear="izq", arriba=4)]})


def cabecera_pokenav(t):
    """Arriba, cada letra grande ocupa justo una columna de tiles (dos de alto), y las iguales comparten tiles; no
    queda ningún tile libre. Así que "POKéNAV" se monta solo con el tilemap: en las columnas de "POKéMON" (3 a 9)
    se ponen las letras P, O, K, é (las mismas), N (la de la columna 9), A (13) y V (14), y "NAVIGATOR" (12 a 20)
    se deja en blanco (el tile de la columna 10)."""
    m, ancho, _ = t.mapas["cabecera"]
    if m[12] == m[10]:  # ya está hecho
        return
    def col(c):
        return m[c], m[ancho + c]
    letras = [col(3), col(4), col(5), col(6), col(9), col(13), col(14)]
    blanco = col(10)
    for c in range(3, 10):
        m[c], m[ancho + c] = letras[c - 3]
    for c in range(12, 21):
        m[c], m[ancho + c] = blanco
    t.mapas_cambiados.add("cabecera")


def cambios():
    nav = "graphics/pokenav/options/"
    cab = "graphics/pokenav/left_headers/"
    c = [
        _opcion(nav + "hoenn_map.png", "MAPA HOENN", True),
        _opcion(nav + "condition.png", "CONDICIÓN", True),
        _opcion(nav + "match_call.png", "AGENDA", True),
        _opcion(nav + "ribbons.png", "CINTAS", True),
        _opcion(nav + "switch_off.png", "APAGAR", True),
        _opcion(nav + "party.png", "EQUIPO", True),
        _opcion(nav + "search.png", "BUSCAR", True),
        _opcion(nav + "cancel.png", "SALIR", True),
        _opcion(nav + "cool.png", "CARISMA", False),
        _opcion(nav + "beauty.png", "BELLEZA", False),
        _opcion(nav + "cute.png", "DULZURA", False),
        _opcion(nav + "smart.png", "INGENIO", False),
        _opcion(nav + "tough.png", "DUREZA", False),
    ]
    # Cabeceras de la izquierda del POKéNAV: las grandes, 2 trozos de 64x32; las pequeñas, 2 de 32x16
    for png, texto in [("main_menu.png", "MENÚ"), ("condition.png", "CONDICIÓN"), ("match_call.png", "AGENDA"),
                       ("ribbons.png", "CINTAS")]:
        c.append((Tira(cab + png, 32), {None: [dict(caja=(0, 2, 85, 21), texto=texto, arriba=7)]}))
    c.append((Tira(cab + "hoenn_map.png", 32), {None: [
        dict(caja=(2, 2, 55, 21), texto="MAPA HOENN", arriba=7),
        dict(caja=(64, 2, 119, 21), texto="COMPLETO", arriba=7),
        dict(caja=(128, 2, 183, 21), texto="AMPLIADO", arriba=7),
    ]}))
    for png, texto in [("party.png", "EQUIPO"), ("search.png", "BUSCAR"), ("cool.png", "CARISMA"),
                       ("beauty.png", "BELLEZA"), ("cute.png", "DULZURA"), ("smart.png", "INGENIO"),
                       ("tough.png", "DUREZA")]:
        c.append((Tira(cab + png, 16), {None: [dict(caja=(0, 2, 61, 15), texto=texto, arriba=4)]}))

    # Cabecera del POKéNAV: "POKéMON NAVIGATOR" arriba (letra grande) y abajo a la derecha (la pequeña del juego)
    cabecera = Tiles("graphics/pokenav/header.png", {"cabecera": ("graphics/pokenav/header.bin", 32, 32)})
    cabecera_pokenav(cabecera)
    c.append((cabecera, {
        "cabecera": [dict(caja=(140, 178, 236, 189), texto="POKéNAV", fuente="small", letra=0x1, sombra=0x5,
                          alinear="der", arriba=181)],
    }))
    # PC: el botón de los datos (letra en degradado con contorno), CERRAR CAJA (normal y apretado) y el equipo
    pc = "graphics/pokemon_storage/"
    c.append((Tiles(pc + "menu.png", {
        "datos": (pc + "pkmn_data.bin", 8, 4), "cerrar": (pc + "close_box_button.bin", 9, 4),
        "equipo": (pc + "party_menu.bin", 12, 22), "pantalla": (pc + "display_menu.bin", 32, 20)}, base=256), {
        # dos veces: el botón normal y el apagado (los mismos tiles, con otra paleta)
        "datos": [dict(caja=(5, 4 + y, 58, 13 + y), texto="DATOS", fuente="small", negrita=True, sombra=None,
                       contorno=0x3, letra={0: 0xE, 1: 0xE, 2: 0xE, 3: 0xE, 4: 0xA, 5: 0xA, 6: 0x5},
                       borrar={0xE, 0xA, 0x5, 0x3}, arriba=6 + y) for y in (0, 16)],
        "cerrar": [dict(caja=(4, 4, 66, 12), texto="CERRAR CAJA", fuente="small", letra=0xE, sombra=0x9, arriba=5),
                   dict(caja=(4, 20, 66, 28), texto="CERRAR CAJA", fuente="small", letra=0x9, sombra=None, arriba=21)],
        "equipo": [dict(caja=(56, 139, 87, 148), texto="SALIR", fuente="small", letra=0x18, sombra=0x17, arriba=140),
                   dict(caja=(4, 163, 68, 172), texto="EQUIPO", fuente="small", letra=0x18, sombra=0x17, arriba=164)],
    }))
    # Ficha de entrenador
    tc = "graphics/trainer_card/"
    c.append((Tiles(tc + "tiles.png", {
        "delante": (tc + "front.bin", 30, 20), "detras": (tc + "back.bin", 30, 20),
        "delante_cable": (tc + "front_link.bin", 30, 20), "fondo": (tc + "bg.bin", 30, 20)}), {
        "delante": [dict(caja=(20, 19, 115, 28), texto="FICHA ENTRENADOR", fuente="small", letra=0xF, sombra=None,
                         borrar={0xF, 0x8}, arriba=20),
                    dict(caja=(20, 112, 125, 119), texto="MEDALLAS", fuente="medallas", letra=0x1,
                         sombra=None, alinear="izq", arriba=113)],
    }))
    # El dinero de las tiendas
    c.append((Tira("graphics/shop/money.png", 16), {None: [
        dict(caja=(4, 4, 30, 8), texto="DINERO", fuente="mini", letra={0: 0xE, 1: 0xE, 2: 0xC, 3: 0xC, 4: 0xD},
             sombra=None, borrar={0xE, 0xC, 0xD, 0x2}, alinear="izq", arriba=4)]}))
    return c


def main():
    ver = sys.argv[sys.argv.index("--ver") + 1] if "--ver" in sys.argv else None
    if ver:
        os.makedirs(ver, exist_ok=True)
    for grafico, por_pantalla in cambios():
        for pantalla, ediciones in por_pantalla.items():
            g = grafico.pantalla(pantalla)
            for e in ediciones:
                cambiar_texto(g, **e)
            grafico.guardar_pantalla(pantalla, g)
        grafico.escribir()
        if ver:  # todas las pantallas que usan el gráfico, también las que comparten tiles con lo cambiado
            for pantalla in (grafico.mapas if isinstance(grafico, Tiles) else [None]):
                g = grafico.pantalla(pantalla)
                im = Image.new("P", (len(g[0]), len(g)))
                im.putpalette(grafico.im.getpalette())
                im.putdata([v for fila in g for v in fila])
                nombre = os.path.basename(grafico.png)[:-4] + (f"_{pantalla}" if pantalla else "")
                carpeta = os.path.basename(os.path.dirname(grafico.png))
                im.resize((im.size[0] * 3, im.size[1] * 3), Image.NEAREST).save(os.path.join(ver, f"{carpeta}_{nombre}.png"))
        print("hecho:", os.path.relpath(grafico.png, RAIZ))


if __name__ == "__main__":
    main()
