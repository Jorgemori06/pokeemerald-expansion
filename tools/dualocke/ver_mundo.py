#!/usr/bin/env python3
"""
Dualocke: une los mapas exteriores de Hoenn por sus conexiones y dibuja el mapa del mundo
(cada casilla con el color medio de su metatile). Sirve para ver dónde queda sitio libre para
zonas nuevas (ZONAS.md).

Uso (desde la raíz del repo):
    python3 tools/dualocke/ver_mundo.py mundo.png [píxeles_por_casilla]

Escribe también mundo.json, con la posición (en casillas), el tamaño, el tileset secundario y la
zona de cada mapa.
"""
import json
import struct
import sys
from collections import deque

sys.path.insert(0, 'tools/dualocke')
import ver_mapa as vm
from PIL import Image, ImageDraw

salida = sys.argv[1]
px = int(sys.argv[2]) if len(sys.argv) > 2 else 4

layouts = {l['id']: l for l in json.load(open('data/layouts/layouts.json', encoding='utf-8'))['layouts'] if 'id' in l}
grupos = json.load(open('data/maps/map_groups.json', encoding='utf-8'))
carpeta_de = {}
for g in grupos['group_order']:
    for carpeta in grupos[g]:
        m = json.load(open(f'data/maps/{carpeta}/map.json', encoding='utf-8'))
        carpeta_de[m['id']] = carpeta


def mapa(c):
    return json.load(open(f'data/maps/{c}/map.json', encoding='utf-8'))


pos = {'LittlerootTown': (0, 0)}
cola = deque(['LittlerootTown'])
while cola:
    c = cola.popleft()
    m = mapa(c)
    l = layouts[m['layout']]
    x, y = pos[c]
    for con in m.get('connections') or []:
        if con['direction'] not in ('up', 'down', 'left', 'right'):
            continue
        d = carpeta_de.get(con['map'])
        if not d or d in pos:
            continue
        ld = layouts[mapa(d)['layout']]
        off = con['offset']
        if con['direction'] == 'up':
            p = (x + off, y - ld['height'])
        elif con['direction'] == 'down':
            p = (x + off, y + l['height'])
        elif con['direction'] == 'left':
            p = (x - ld['width'], y + off)
        else:
            p = (x + l['width'], y + off)
        pos[d] = p
        cola.append(d)

minx = min(p[0] for p in pos.values()); miny = min(p[1] for p in pos.values())
maxx = max(p[0] + layouts[mapa(c)['layout']]['width'] for c, p in pos.items())
maxy = max(p[1] + layouts[mapa(c)['layout']]['height'] for c, p in pos.items())
W, H = maxx - minx, maxy - miny
print('mapas', len(pos), 'tamaño en casillas', W, H)

carpetas = vm.carpetas_tilesets()
paletas = vm.carpetas_paletas()
cache_ts = {}


def ts(n):
    if n not in cache_ts:
        cache_ts[n] = vm.Tileset(carpetas[n], paletas.get(n))
    return cache_ts[n]


img = Image.new('RGB', (W * px, H * px), (0, 0, 40))
info = {}
for c, (x, y) in pos.items():
    m = mapa(c)
    l = layouts[m['layout']]
    w, h = l['width'], l['height']
    celdas = struct.unpack(f'<{w * h}H', open(l['blockdata_filepath'], 'rb').read())
    prim, sec = ts(l['primary_tileset']), ts(l['secondary_tileset'])
    # Color medio de cada metatile (rápido)
    medios = {}
    trozo = Image.new('RGB', (w * px, h * px))
    tp = trozo.load()
    for my in range(h):
        for mx in range(w):
            mt = celdas[my * w + mx] & 0x3FF
            if mt not in medios:
                medios[mt] = color_medio = None
                t, base = (prim, mt) if mt < 512 else (sec, mt - 512)
                cols = []
                for k in range(8):
                    i = base * 8 + k
                    if i >= len(t.metatiles):
                        continue
                    v = t.metatiles[i]
                    tile, pal = v & 0x3FF, v >> 12
                    datos = prim.tile(tile) if tile < 512 else sec.tile(tile - 512)
                    pals = (prim if pal < 6 else sec).paletas.get(pal) or prim.paletas.get(pal) or [(255, 0, 255)] * 16
                    cols += [pals[d] for d in datos if d]
                medios[mt] = tuple(sum(cc[j] for cc in cols) // len(cols) for j in range(3)) if cols else (0, 0, 0)
            col = medios[mt]
            for yy in range(px):
                for xx in range(px):
                    tp[mx * px + xx, my * px + yy] = col
    img.paste(trozo, ((x - minx) * px, (y - miny) * px))
    info[c] = {'x': x - minx, 'y': y - miny, 'w': w, 'h': h, 'sec': l['secondary_tileset'],
               'mapsec': m.get('region_map_section'), 'tipo': m.get('map_type')}

d = ImageDraw.Draw(img)
for c, i in info.items():
    d.rectangle([i['x'] * px, i['y'] * px, (i['x'] + i['w']) * px - 1, (i['y'] + i['h']) * px - 1], outline=(255, 255, 255))
    d.text((i['x'] * px + 3, i['y'] * px + 3), c.replace('Route', 'R'), fill=(255, 255, 0))
img.save(salida)
json.dump(info, open(salida.rsplit('.', 1)[0] + '.json', 'w', encoding='utf-8'), indent=1)
print('ok', img.size)
