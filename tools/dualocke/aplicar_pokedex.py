#!/usr/bin/env python3
"""Dualocke: pone en el juego la Pokédex en español (entradas y categorías).

- traduccion/pokedex/entradas.csv (constante,espanol,origen): el texto de cada especie o forma
  en una sola línea. El script lo corta en 4 líneas de 40 letras, como el inglés.
- traduccion/pokedex/categorias.csv (ingles,espanol): "Seed" -> "Semilla".
Todo queda como ES(inglés, español): en los tests sigue el inglés.

Uso (desde la raíz del repo):
    python3 tools/dualocke/aplicar_pokedex.py                 # comprueba
    python3 tools/dualocke/aplicar_pokedex.py --aplicar       # escribe los archivos
    python3 tools/dualocke/aplicar_pokedex.py --pendientes F  # lista lo que falta en F (TSV)
"""
import csv
import glob
import os
import re
import sys
import textwrap

DIR = 'traduccion/pokedex/'
ANCHO, LINEAS = 40, 4
LIMITE_CATEGORIA = 12  # categoryName es u8[13] (include/pokemon.h)
CAD = r'"(?:[^"\\]|\\.)*"'
DESC = re.compile(r'(\.description\s*=\s*)COMPOUND_STRING\(((?:\s*' + CAD + r')+)\s*\)')
CATEG = re.compile(r'(\.categoryName\s*=\s*)_\("((?:[^"\\]|\\.)*)"\)')


def leer(nombre, clave):
    if not os.path.exists(DIR + nombre):
        return {}
    with open(DIR + nombre, encoding='utf-8', newline='') as f:
        return {r[clave]: r['espanol'] for r in csv.DictReader(f)}


def bloques(datos):
    marcas = [(m.group(1), m.start()) for m in re.finditer(r'^\s*\[(SPECIES_\w+)\]\s*=', datos, re.M)]
    return [(c, ini, marcas[i + 1][1] if i + 1 < len(marcas) else len(datos)) for i, (c, ini) in enumerate(marcas)]


def main():
    aplicar = '--aplicar' in sys.argv
    pend = sys.argv[sys.argv.index('--pendientes') + 1] if '--pendientes' in sys.argv else None
    charmap = open('charmap.txt', encoding='utf-8').read()
    letras = {m.group(1) for m in re.finditer(r"^'(.)'\s*=", charmap, re.M)}
    entradas = leer('entradas.csv', 'constante')
    categorias = leer('categorias.csv', 'ingles')
    errores = hechas = 0
    pendientes = []

    for ruta in sorted(glob.glob('src/data/pokemon/species_info/*.h')):
        datos = open(ruta, encoding='utf-8', newline='').read()
        trozos, pos = [], 0
        for const, ini, fin in bloques(datos):
            bloque = datos[ini:fin]
            nuevo_bloque = bloque
            m = DESC.search(bloque)
            if m:
                en = ''.join(re.findall(r'"((?:[^"\\]|\\.)*)"', m.group(2)))
                es = entradas.get(const)
                if not es:
                    pendientes.append(f'{const}\t{en.replace(chr(92) + "n", " ")}')
                else:
                    lineas = textwrap.wrap(es, ANCHO, break_long_words=False)
                    if len(lineas) > LINEAS:
                        print(f'NO CABE ({len(lineas)} líneas): {const}: {es}')
                        errores += 1
                    raras = {c for c in re.sub(r'\{[^}]*\}', '', es) if c not in letras and c != ' '}
                    if raras:
                        print(f'LETRAS QUE NO EXISTEN: {const}: {raras}')
                        errores += 1
                    es_c = ' '.join('"' + t + ('\\n' if i < len(lineas) - 1 else '') + '"' for i, t in enumerate(lineas))
                    nuevo_bloque = (nuevo_bloque[:m.start()] + f'{m.group(1)}ES(COMPOUND_STRING({m.group(2).strip()}), COMPOUND_STRING({es_c}))'
                                    + nuevo_bloque[m.end():])
                    hechas += 1
            mc = CATEG.search(nuevo_bloque)
            if mc and categorias.get(mc.group(2)) and categorias[mc.group(2)] != mc.group(2):
                es = categorias[mc.group(2)]
                if len(es) > LIMITE_CATEGORIA:
                    print(f'CATEGORÍA LARGA: {mc.group(2)} -> {es}')
                    errores += 1
                nuevo_bloque = (nuevo_bloque[:mc.start()] + f'{mc.group(1)}ES(_("{mc.group(2)}"), _("{es}"))'
                                + nuevo_bloque[mc.end():])
            trozos.append(datos[pos:ini])
            trozos.append(nuevo_bloque)
            pos = fin
        trozos.append(datos[pos:])
        if aplicar and errores == 0:
            open(ruta, 'w', encoding='utf-8', newline='').write(''.join(trozos))

    print(f'entradas traducidas: {hechas}; faltan: {len(pendientes)}; errores: {errores}')
    if pend:
        open(pend, 'w', encoding='utf-8').write('\n'.join(pendientes) + '\n')
    return 1 if errores else 0


if __name__ == '__main__':
    sys.exit(main())
