#!/usr/bin/env python3
"""Dualocke: pone en el juego los nombres oficiales en español de traduccion/nombres/.

Cada nombre pasa de  _("Pound")  a  ES(_("Pound"), _("Destructor"))  (o lo mismo con
COMPOUND_STRING / ITEM_NAME): en los tests de la expansion sigue el inglés y en el juego sale
el español (ver include/dualocke_es.h).

- Los nombres salen de los .csv que genera tools/dualocke/nombres_oficiales.py.
- traduccion/nombres/decididos.csv manda sobre ellos: abreviaturas y nombres que no tienen
  versión oficial.
- Se puede volver a ejecutar: lo que ya está traducido no se toca.

Uso (desde la raíz del repo):
    python3 tools/dualocke/aplicar_nombres.py            # solo comprueba
    python3 tools/dualocke/aplicar_nombres.py --aplicar  # escribe los archivos
"""
import csv
import glob
import re
import sys

APLICAR = '--aplicar' in sys.argv
DIR = 'traduccion/nombres/'

# tabla -> (csv, límite de letras, archivos, patrón del nombre en el código)
TABLAS = {
    'especies': ('especies.csv', 12, sorted(glob.glob('src/data/pokemon/species_info/*.h')),
                 r'(\.speciesName\s*=\s*)_\("((?:[^"\\]|\\.)*)"\)', '_'),
    'movimientos': ('movimientos.csv', 16, ['src/data/moves_info.h'],
                    r'(\.name\s*=\s*)COMPOUND_STRING\("((?:[^"\\]|\\.)*)"\)', 'COMPOUND_STRING'),
    'objetos': ('objetos.csv', 20, ['src/data/items.h'],
                r'(\.name\s*=\s*)ITEM_NAME\("((?:[^"\\]|\\.)*)"\)', 'ITEM_NAME'),
    'habilidades': ('habilidades.csv', 16, ['src/data/abilities.h'],
                    r'(\.name\s*=\s*)_\("((?:[^"\\]|\\.)*)"\)', '_'),
    'tipos': ('tipos.csv', 9, ['src/data/types_info.h'],
              r'(\.name\s*=\s*)_\("((?:[^"\\]|\\.)*)"\)', '_'),
    'naturalezas': ('naturalezas.csv', 12, ['src/pokemon.c'],
                    r'(\.name\s*=\s*)COMPOUND_STRING\("((?:[^"\\]|\\.)*)"\)', 'COMPOUND_STRING'),
}


def leer_csv(nombre):
    with open(DIR + nombre, encoding='utf-8', newline='') as f:
        return list(csv.DictReader(f))


def main():
    charmap = open('charmap.txt', encoding='utf-8').read()
    letras = {m.group(1) for m in re.finditer(r"^'(.)'\s*=", charmap, re.M)}
    decididos = {f['constante']: f['espanol'] for f in leer_csv('decididos.csv')}
    usados = set()
    errores = 0

    for tabla, (archivo_csv, limite, rutas, patron, envoltura) in TABLAS.items():
        nombres = {}  # inglés -> español
        for fila in leer_csv(archivo_csv):
            es = decididos.get(fila['constante'], fila['espanol'])
            if fila['constante'] in decididos:
                usados.add(fila['constante'])
            if not es:
                continue  # sin nombre: se queda en inglés
            if len(es) > limite:
                print(f'[{tabla}] NO CABE ({len(es)} > {limite}): {fila["constante"]} {es}')
                errores += 1
            raras = {c for c in es if c not in letras and c != ' '}
            if raras:
                print(f'[{tabla}] LETRAS QUE NO EXISTEN EN EL JUEGO: {fila["constante"]} {es} {raras}')
                errores += 1
            anterior = nombres.get(fila['ingles'])
            if anterior and anterior != es:
                print(f'[{tabla}] AVISO: "{fila["ingles"]}" tiene dos traducciones: {anterior} / {es}')
            nombres.setdefault(fila['ingles'], es)

        cambiados = sin_traduccion = 0
        faltan = set()
        for ruta in rutas:
            datos = open(ruta, encoding='utf-8', newline='').read()

            def cambiar(m):
                nonlocal cambiados, sin_traduccion
                en = m.group(2)
                es = nombres.get(en)
                if es is None:
                    faltan.add(en)
                    sin_traduccion += 1
                    return m.group(0)
                if es == en:
                    return m.group(0)
                cambiados += 1
                return (f'{m.group(1)}ES({envoltura}("{en}"), {envoltura}("{es}"))')

            if tabla == 'naturalezas':
                # solo dentro de gNaturesInfo
                ini = datos.index('gNaturesInfo[')
                fin = datos.index('};', ini)
                nuevo = datos[:ini] + re.sub(patron, cambiar, datos[ini:fin]) + datos[fin:]
            else:
                nuevo = re.sub(patron, cambiar, datos)
            if APLICAR and nuevo != datos:
                if '#include "dualocke_es.h"' not in nuevo and ruta.endswith('.c'):
                    nuevo = nuevo.replace('#include "global.h"', '#include "global.h"\n#include "dualocke_es.h"', 1)
                open(ruta, 'w', encoding='utf-8', newline='').write(nuevo)
        print(f'[{tabla}] traducidos: {cambiados}; sin traducción en la tabla: {sin_traduccion}')
        if faltan:
            print(f'    sin traducción: {", ".join(sorted(faltan)[:25])}{" …" if len(faltan) > 25 else ""}')

    sobran = set(decididos) - usados
    if sobran:
        print('decididos.csv tiene constantes que no están en las tablas:', ', '.join(sorted(sobran)))
        errores += 1
    print('errores:', errores)
    return 1 if errores else 0


if __name__ == '__main__':
    sys.exit(main())
