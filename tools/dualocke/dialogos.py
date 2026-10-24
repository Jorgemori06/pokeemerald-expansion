#!/usr/bin/env python3
"""Dualocke: traducción de los diálogos de los mapas (.string de los .inc).

Las traducciones están en traduccion/dialogos/*.tsv, una línea por texto:
    etiqueta<TAB>texto
El texto va en una sola línea con los mismos códigos que el original: \\n (salto), \\l (sube la
línea), \\p (página nueva), {PLAYER}, {STR_VAR_1}… y $ al final si el original lo lleva.

Comprueba que cada línea quepa en el recuadro midiendo en píxeles con la fuente del juego
(gFontNormalLatinGlyphWidths), que estén los mismos códigos {…} y que no falten etiquetas.
Los diálogos no los comprueban los tests de la expansion, así que se cambian directamente.

Uso (desde la raíz del repo):
    python3 tools/dualocke/dialogos.py exportar data/maps/LittlerootTown/scripts.inc ...  > ingles.tsv
    python3 tools/dualocke/dialogos.py comprobar
    python3 tools/dualocke/dialogos.py aplicar
"""
import glob
import re
import sys

ANCHO_MAX = 208          # píxeles por línea del recuadro de diálogo (lo más ancho del inglés)
ANCHO_VARIABLE = 42      # lo que se reserva para {PLAYER}, {STR_VAR_1}…: 7 letras
DIR = 'traduccion/dialogos/'
ETIQ = re.compile(r'^(\w+)::?\s*\n((?:[ \t]*\.string "(?:[^"\\]|\\.)*"[ \t]*\n)+)', re.M)


def anchos():
    """Ancho en píxeles de cada carácter según charmap.txt y la tabla de la fuente normal."""
    fuente = open('src/fonts.c', encoding='utf-8').read()
    tabla = fuente[fuente.index('gFontNormalLatinGlyphWidths[]'):]
    tabla = [int(x) for x in re.findall(r'\d+', tabla[tabla.index('{'):tabla.index('}')])]
    res = {}
    for m in re.finditer(r"^'(.)'\s*=\s*([0-9A-F]{2})\s*$", open('charmap.txt', encoding='utf-8').read(), re.M):
        cod = int(m.group(2), 16)
        if cod < len(tabla):
            res[m.group(1)] = tabla[cod]
    return res


ANCHOS = None


def ancho_linea(linea):
    total = 0
    for trozo in re.split(r'(\{[^}]*\})', linea):
        if trozo.startswith('{'):
            if re.match(r'\{(PLAYER|RIVAL|STR_VAR_\d|KUN|B_\w+)\}', trozo):
                total += ANCHO_VARIABLE
            continue
        total += sum(ANCHOS.get(c, 6) for c in trozo if c != '$')
    return total


def lineas(texto):
    return re.split(r'\\[nlp]', texto)


def leer_inc(ruta):
    datos = open(ruta, encoding='utf-8', newline='').read()
    return datos, {m.group(1): m for m in ETIQ.finditer(datos)}


def texto_de(bloque):
    return ''.join(re.findall(r'\.string "((?:[^"\\]|\\.)*)"', bloque))


def a_strings(texto):
    """Parte el texto en líneas .string como el original: un trozo por cada \\n, \\l o \\p."""
    trozos = re.findall(r'.*?(?:\\[nlp]|$)', texto)
    trozos = [t for t in trozos if t]
    return ''.join(f'\t.string "{t}"\n' for t in trozos)


def leer_traducciones():
    trad = {}
    for ruta in sorted(glob.glob(DIR + '*.tsv')):
        for n, linea in enumerate(open(ruta, encoding='utf-8'), 1):
            linea = linea.rstrip('\n')
            if not linea.strip() or linea.startswith('#'):
                continue
            etiqueta, texto = linea.split('\t', 1)
            trad[etiqueta] = (texto, f'{ruta}:{n}')
    return trad


def archivos():
    return sorted(glob.glob('data/maps/*/scripts.inc') + glob.glob('data/text/*.inc') + glob.glob('data/scripts/*.inc'))


def main():
    global ANCHOS
    ANCHOS = anchos()
    orden = sys.argv[1] if len(sys.argv) > 1 else 'comprobar'
    if orden == 'exportar':
        for ruta in sys.argv[2:]:
            _, etiquetas = leer_inc(ruta)
            for e, m in etiquetas.items():
                print(f'{e}\t{texto_de(m.group(2))}')
        return 0

    trad = leer_traducciones()
    usadas = set()
    errores = 0
    for ruta in archivos():
        datos, etiquetas = leer_inc(ruta)
        cambios = []
        for e, m in etiquetas.items():
            if e not in trad:
                continue
            usadas.add(e)
            es, origen = trad[e]
            en = texto_de(m.group(2))
            # mismos códigos {…}, aunque se usen más o menos veces ({PLAYER} se puede quitar al reordenar)
            if set(re.findall(r'\{[^}]*\}', en)) != set(re.findall(r'\{[^}]*\}', es)):
                print(f'CÓDIGOS DISTINTOS {origen} {e}'); errores += 1
            if en.endswith('$') != es.endswith('$'):
                print(f'FALTA O SOBRA $ {origen} {e}'); errores += 1
            for l in lineas(es):
                if ancho_linea(l) > ANCHO_MAX:
                    print(f'NO CABE ({ancho_linea(l)} px) {origen} {e}: {l}'); errores += 1
            raras = {c for c in re.sub(r'\{[^}]*\}|\\.', '', es) if c not in ANCHOS and c not in ' $'}
            if raras:
                print(f'LETRAS QUE NO EXISTEN {origen} {e}: {raras}'); errores += 1
            cambios.append((m.start(2), m.end(2), a_strings(es)))
        if orden == 'aplicar' and cambios and errores == 0:
            for ini, fin, nuevo in sorted(cambios, reverse=True):
                datos = datos[:ini] + nuevo + datos[fin:]
            open(ruta, 'w', encoding='utf-8', newline='').write(datos)
    for e in sorted(set(trad) - usadas):
        print(f'ETIQUETA QUE NO EXISTE: {e} ({trad[e][1]})'); errores += 1
    print(f'traducciones: {len(trad)}; errores: {errores}')
    return 1 if errores else 0


if __name__ == '__main__':
    sys.exit(main())
