"""Dibuja un mapa del juego en un PNG, con sus tilesets, como lo haría Porymap.

Uso (desde la raíz del repo):
    python3 tools/dualocke/ver_mapa.py DewfordTown azuliza.png 2 --rejilla --eventos

El tercer argumento es la escala. --rejilla pinta las coordenadas cada 5 casillas y --eventos marca
los objetos (rojo), los entrenadores (naranja), los demás personajes (azul) y las puertas (rosa).
Hace falta Pillow (pip install pillow). No toca nada del juego: sirve para ver un mapa sin Porymap
y para comprobar a ojo los cambios que se hagan por código.
"""
import json
import os
import re
import struct
import sys

from PIL import Image, ImageDraw

TILES_PRIMARIO = 512
METATILES_PRIMARIO = 512
PALETAS_PRIMARIO = 6


def carpetas_tilesets():
    """{gTileset_X: carpeta} a partir de los atributos de los metatiles."""
    with open('src/data/tilesets/metatiles.h', encoding='utf-8') as f:
        rutas = dict(re.findall(r'(gMetatileAttributes_\w+)\[\]\s*=\s*INCBIN_U16\("([^"]+)"\)', f.read()))
    with open('src/data/tilesets/headers.h', encoding='utf-8') as f:
        cabeceras = f.read()
    resultado = {}
    for nombre, cuerpo in re.findall(r'const struct Tileset (gTileset_\w+)\s*=\s*\{(.*?)\};', cabeceras, re.S):
        attr = re.search(r'\.metatileAttributes\s*=\s*(gMetatileAttributes_\w+)', cuerpo)
        if attr and attr.group(1) in rutas:
            resultado[nombre] = os.path.dirname(rutas[attr.group(1)])
    return resultado


class Tileset:
    def __init__(self, carpeta):
        self.carpeta = carpeta
        img = Image.open(os.path.join(carpeta, 'tiles.png'))
        assert img.mode == 'P', (carpeta, img.mode)
        self.ancho = img.width // 8
        self.pix = img.load()
        self.n_tiles = (img.width // 8) * (img.height // 8)
        with open(os.path.join(carpeta, 'metatiles.bin'), 'rb') as f:
            datos = f.read()
        self.metatiles = struct.unpack(f'<{len(datos) // 2}H', datos)
        self.paletas = {}
        for n in range(16):
            ruta = os.path.join(carpeta, 'palettes', f'{n:02d}.pal')
            if os.path.exists(ruta):
                lineas = open(ruta).read().split('\n')
                self.paletas[n] = [tuple(int(v) for v in l.split()) for l in lineas[3:19] if l.strip()]

    def tile(self, indice):
        """Los 64 índices de color (0-15) de un tile."""
        if indice >= self.n_tiles:
            return [0] * 64
        x0, y0 = (indice % self.ancho) * 8, (indice // self.ancho) * 8
        return [self.pix[x0 + x, y0 + y] & 15 for y in range(8) for x in range(8)]


def dibujar(carpeta_mapa, salida, escala=1, rejilla=False, eventos=False):
    mapa = json.load(open(f'data/maps/{carpeta_mapa}/map.json', encoding='utf-8'))
    layouts = {l['id']: l for l in json.load(open('data/layouts/layouts.json', encoding='utf-8'))['layouts'] if 'id' in l}
    l = layouts[mapa['layout']]
    w, h = l['width'], l['height']
    celdas = struct.unpack(f'<{w * h}H', open(l['blockdata_filepath'], 'rb').read())
    carpetas = carpetas_tilesets()
    prim, sec = Tileset(carpetas[l['primary_tileset']]), Tileset(carpetas[l['secondary_tileset']])

    def paleta(n):
        ts = prim if n < PALETAS_PRIMARIO else sec
        return ts.paletas.get(n) or prim.paletas.get(n) or [(255, 0, 255)] * 16

    img = Image.new('RGB', (w * 16, h * 16), (0, 0, 0))
    px = img.load()
    cache = {}
    for my in range(h):
        for mx in range(w):
            mt = celdas[my * w + mx] & 0x3FF
            if mt not in cache:
                ts, base = (prim, mt) if mt < METATILES_PRIMARIO else (sec, mt - METATILES_PRIMARIO)
                bloque = [[None] * 16 for _ in range(16)]
                for capa in range(2):
                    for k in range(4):
                        i = base * 8 + capa * 4 + k
                        if i >= len(ts.metatiles):
                            continue
                        v = ts.metatiles[i]
                        t, hf, vf, p = v & 0x3FF, (v >> 10) & 1, (v >> 11) & 1, v >> 12
                        datos = (prim.tile(t) if t < TILES_PRIMARIO else sec.tile(t - TILES_PRIMARIO))
                        colores = paleta(p)
                        ox, oy = (k % 2) * 8, (k // 2) * 8
                        for y in range(8):
                            for x in range(8):
                                c = datos[(7 - y if vf else y) * 8 + (7 - x if hf else x)]
                                if c == 0 and capa == 1:
                                    continue
                                if c == 0 and bloque[oy + y][ox + x] is not None:
                                    continue
                                bloque[oy + y][ox + x] = colores[c] if c < len(colores) else (255, 0, 255)
                cache[mt] = bloque
            bloque = cache[mt]
            for y in range(16):
                for x in range(16):
                    if bloque[y][x] is not None:
                        px[mx * 16 + x, my * 16 + y] = bloque[y][x]
    if escala != 1:
        img = img.resize((w * 16 * escala, h * 16 * escala), Image.NEAREST)
    d = ImageDraw.Draw(img)
    e = 16 * escala
    if rejilla:
        for x in range(0, w, 5):
            d.line([(x * e, 0), (x * e, h * e)], fill=(255, 255, 255))
            d.text((x * e + 2, 1), str(x), fill=(255, 255, 0))
        for y in range(0, h, 5):
            d.line([(0, y * e), (w * e, y * e)], fill=(255, 255, 255))
            d.text((1, y * e + 2), str(y), fill=(255, 255, 0))
    if eventos:
        for o in mapa.get('object_events', []):
            bola = o['graphics_id'] == 'OBJ_EVENT_GFX_ITEM_BALL'
            entrenador = o.get('trainer_type', 'TRAINER_TYPE_NONE') != 'TRAINER_TYPE_NONE'
            color = (255, 60, 60) if bola else (255, 160, 0) if entrenador else (60, 160, 255)
            d.ellipse([o['x'] * e + 3, o['y'] * e + 3, o['x'] * e + e - 3, o['y'] * e + e - 3], outline=color, width=2)
        for wp in mapa.get('warp_events', []):
            d.rectangle([wp['x'] * e + 2, wp['y'] * e + 2, wp['x'] * e + e - 2, wp['y'] * e + e - 2], outline=(255, 0, 255), width=2)
    img.save(salida)
    print(carpeta_mapa, f'{w}x{h}', l['primary_tileset'], l['secondary_tileset'], '->', salida, img.size)
    print('conexiones:', [(c['direction'], c['map'], c['offset']) for c in (mapa.get('connections') or [])])


if __name__ == '__main__':
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    dibujar(args[0], args[1], int(args[2]) if len(args) > 2 else 1, '--rejilla' in sys.argv, '--eventos' in sys.argv)
