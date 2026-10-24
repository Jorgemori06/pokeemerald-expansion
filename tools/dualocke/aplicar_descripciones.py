#!/usr/bin/env python3
"""Dualocke: pone en el juego las descripciones en español de movimientos, objetos y habilidades.

Las traducciones están en traduccion/descripciones/{movimientos,objetos,habilidades}.csv
(constante,espanol), escritas en una sola línea: el script corta las líneas al ancho de cada
recuadro y avisa de las que no caben. Cada descripción queda como
ES(COMPOUND_STRING("inglés"), COMPOUND_STRING("español")): en los tests sigue el inglés.

Uso (desde la raíz del repo):
    python3 tools/dualocke/aplicar_descripciones.py                 # comprueba
    python3 tools/dualocke/aplicar_descripciones.py --aplicar       # escribe los archivos
    python3 tools/dualocke/aplicar_descripciones.py --pendientes F  # lista lo que falta en F (TSV)
"""
import csv
import os
import re
import sys
import textwrap

DIR = 'traduccion/descripciones/'
# tabla -> (archivo de datos, prefijo de constante, ancho de línea, líneas)
TABLAS = {
    'movimientos': ('src/data/moves_info.h', 'MOVE_', 29, 2),
    'objetos': ('src/data/items.h', 'ITEM_', 20, 3),
    'habilidades': ('src/data/abilities.h', 'ABILITY_', 30, 1),  # la pantalla de datos estrecha la letra si hace falta
}
CAD = r'"(?:[^"\\]|\\.)*"'
DESC = re.compile(r'(\.description\s*=\s*)COMPOUND_STRING\(((?:\s*' + CAD + r')+)\s*\)')


def bloques(datos, prefijo):
    """Devuelve [(constante, inicio, fin)] de cada bloque [PREFIJO_X] = { ... }."""
    marcas = [(m.group(1), m.start()) for m in re.finditer(r'^\s*\[(' + prefijo + r'\w+)\]\s*=', datos, re.M)]
    res = []
    for i, (c, ini) in enumerate(marcas):
        fin = marcas[i + 1][1] if i + 1 < len(marcas) else len(datos)
        res.append((c, ini, fin))
    return res


def ingles(partes):
    return ''.join(re.findall(r'"((?:[^"\\]|\\.)*)"', partes))


def cortar(texto, ancho, lineas):
    trozos = textwrap.wrap(texto, ancho, break_long_words=False)
    return trozos, len(trozos) <= lineas


def main():
    aplicar = '--aplicar' in sys.argv
    pendientes = sys.argv[sys.argv.index('--pendientes') + 1] if '--pendientes' in sys.argv else None
    charmap = open('charmap.txt', encoding='utf-8').read()
    letras = {m.group(1) for m in re.finditer(r"^'(.)'\s*=", charmap, re.M)}
    errores = 0
    salida_pend = []

    for tabla, (ruta, prefijo, ancho, lineas) in TABLAS.items():
        trad = {}
        if os.path.exists(DIR + tabla + '.csv'):
            with open(DIR + tabla + '.csv', encoding='utf-8', newline='') as f:
                trad = {r['constante']: r['espanol'] for r in csv.DictReader(f)}
        datos = open(ruta, encoding='utf-8', newline='').read()
        nuevo = []
        pos = 0
        hechas = faltan = 0
        for const, ini, fin in bloques(datos, prefijo):
            bloque = datos[ini:fin]
            m = DESC.search(bloque)
            if not m:
                continue
            en = ingles(m.group(2))
            if en in ('?????', ''):
                continue
            es = trad.get(const)
            if not es:
                faltan += 1
                salida_pend.append(f'{tabla}\t{const}\t{en.replace(chr(92) + "n", " ")}')
                continue
            trozos, ok = cortar(es, ancho, lineas)
            raras = {c for c in re.sub(r'\{[^}]*\}', '', es) if c not in letras and c != ' '}
            if not ok:
                print(f'[{tabla}] NO CABE ({len(trozos)} líneas > {lineas}): {const}: {es}')
                errores += 1
            if raras:
                print(f'[{tabla}] LETRAS QUE NO EXISTEN: {const}: {raras}')
                errores += 1
            hechas += 1
            es_c = ' '.join('"' + t + ('\\n' if i < len(trozos) - 1 else '') + '"' for i, t in enumerate(trozos))
            reemplazo = f'{m.group(1)}ES(COMPOUND_STRING({m.group(2).strip()}), COMPOUND_STRING({es_c}))'
            nuevo.append(datos[pos:ini + m.start()])
            nuevo.append(reemplazo)
            pos = ini + m.end()
        nuevo.append(datos[pos:])
        print(f'[{tabla}] traducidas: {hechas}; faltan: {faltan}')
        if aplicar and errores == 0:
            open(ruta, 'w', encoding='utf-8', newline='').write(''.join(nuevo))

    if pendientes:
        with open(pendientes, 'w', encoding='utf-8') as f:
            f.write('\n'.join(salida_pend) + '\n')
    print('errores:', errores)
    return 1 if errores else 0


if __name__ == '__main__':
    sys.exit(main())
