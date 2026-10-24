#!/usr/bin/env python3
"""
Dualocke: tablas de nombres oficiales en español (paso 1 de la traducción, sección 8).

Uso (desde la raíz del repo):
    python3 tools/dualocke/nombres_oficiales.py <carpeta con los CSV de PokéAPI>

Los CSV salen de https://github.com/PokeAPI/pokeapi (data/v2/csv). No se suben al repo:
solo el resultado, en traduccion/nombres/. Este script no cambia el juego: solo prepara las
tablas para que la traducción no invente nombres.

Para cada constante del juego (especies, movimientos, objetos, habilidades, tipos y
naturalezas) busca su nombre inglés en el código, lo empareja con el nombre inglés de
PokéAPI y saca el nombre oficial en español (idioma 7 de PokéAPI, español de España).
Cada tabla dice además si el nombre español cabe en el límite de caracteres del juego.
"""

import csv
import glob
import os
import re
import sys

ES, EN = "7", "9"
SALIDA = "traduccion/nombres"
LIMITES = {"especies": 12, "movimientos": 16, "objetos": 20, "habilidades": 16, "tipos": 8, "naturalezas": 12}


def normalizar(texto):
    texto = texto.lower().replace("é", "e").replace("♀", "f").replace("♂", "m")
    return re.sub(r"[^a-z0-9]", "", texto)


def leer_csv(carpeta, nombre):
    with open(os.path.join(carpeta, nombre + ".csv"), encoding="utf-8") as f:
        return list(csv.DictReader(f))


def nombres_pokeapi(carpeta, tabla_nombres, columna_id, tabla_ids):
    """Devuelve ({normalizado inglés: español}, {identificador: español})."""
    ingles, espanol = {}, {}
    for fila in leer_csv(carpeta, tabla_nombres):
        if fila["local_language_id"] == EN:
            ingles[fila[columna_id]] = fila["name"]
        elif fila["local_language_id"] == ES:
            espanol[fila[columna_id]] = fila["name"]
    ids = {f["id"]: f["identifier"] for f in leer_csv(carpeta, tabla_ids)}
    por_ingles = {normalizar(ingles[i]): espanol[i] for i in ingles if i in espanol}
    por_identificador = {normalizar(ids[i]): espanol[i] for i in espanol if i in ids}
    return por_ingles, por_identificador


def nombres_del_juego(archivo, prefijo, campo=".name"):
    """Devuelve [(CONSTANTE, nombre inglés)] leyendo los [PREFIJO_X] = { .name = ... }."""
    with open(archivo, encoding="utf-8") as f:
        texto = f.read()
    resultado = []
    for m in re.finditer(r"\[(" + prefijo + r"\w+)\]\s*=\s*\{", texto):
        fin = texto.find("\n    [", m.end())
        cuerpo = texto[m.end():fin if fin != -1 else len(texto)]
        nombre = re.search(re.escape(campo) + r'\s*=\s*(?:COMPOUND_STRING|ITEM_NAME|_)\("([^"]*)"\)', cuerpo)
        if nombre:
            resultado.append((m.group(1), nombre.group(1)))
    return resultado


def especies_del_juego():
    """Devuelve [(SPECIES_X, nombre inglés, nº de la Pokédex Nacional)] de las especies base."""
    resultado = []
    for archivo in sorted(glob.glob("src/data/pokemon/species_info/gen_*_families.h")):
        with open(archivo, encoding="utf-8") as f:
            texto = f.read()
        for m in re.finditer(r"^    \[(SPECIES_\w+)\]\s*=\s*\{", texto, re.M):
            fin = texto.find("\n    [SPECIES_", m.end())
            cuerpo = texto[m.end():fin if fin != -1 else len(texto)]
            nombre = re.search(r'\.speciesName\s*=\s*_\("([^"]*)"\)', cuerpo)
            dex = re.search(r"\.natDexNum\s*=\s*NATIONAL_DEX_(\w+)", cuerpo)
            if nombre and dex:
                resultado.append((m.group(1), nombre.group(1), dex.group(1)))
    return resultado


def escribir(categoria, filas):
    os.makedirs(SALIDA, exist_ok=True)
    limite = LIMITES[categoria]
    faltan = [f for f in filas if not f[2]]
    largos = [f for f in filas if f[2] and len(f[2]) > limite]
    with open(os.path.join(SALIDA, categoria + ".csv"), "w", encoding="utf-8", newline="") as f:
        w = csv.writer(f)
        w.writerow(["constante", "ingles", "espanol", "caracteres", f"cabe_en_{limite}"])
        for constante, ingles, espanol in filas:
            w.writerow([constante, ingles, espanol, len(espanol) if espanol else "",
                        "" if not espanol else ("si" if len(espanol) <= limite else "NO")])
    print(f"{categoria:12s} {len(filas):5d} | sin nombre oficial: {len(faltan):3d} | no caben: {len(largos):3d}")
    return faltan, largos


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    carpeta = sys.argv[1]
    informe = {}

    # Especies: por número de la Pokédex Nacional (las formas comparten nombre con su especie)
    especies_es = {f["pokemon_species_id"]: f["name"] for f in leer_csv(carpeta, "pokemon_species_names")
                   if f["local_language_id"] == ES}
    dex_ids = {normalizar(f["identifier"]): f["id"] for f in leer_csv(carpeta, "pokemon_species")}
    filas, vistas = [], set()
    for constante, ingles, dex in especies_del_juego():
        if dex in vistas:
            continue
        vistas.add(dex)
        filas.append((f"NATIONAL_DEX_{dex}", ingles, especies_es.get(dex_ids.get(normalizar(dex), ""), "")))
    informe["especies"] = escribir("especies", filas)

    tablas = [
        ("movimientos", "src/data/moves_info.h", "MOVE_", "move_names", "move_id", "moves"),
        ("objetos", "src/data/items.h", "ITEM_", "item_names", "item_id", "items"),
        ("habilidades", "src/data/abilities.h", "ABILITY_", "ability_names", "ability_id", "abilities"),
        ("tipos", "src/data/types_info.h", "TYPE_", "type_names", "type_id", "types"),
        ("naturalezas", "src/pokemon.c", "NATURE_", "nature_names", "nature_id", "natures"),
    ]
    for categoria, archivo, prefijo, nombres, columna, ids in tablas:
        por_ingles, por_id = nombres_pokeapi(carpeta, nombres, columna, ids)
        filas = []
        for constante, ingles in nombres_del_juego(archivo, prefijo):
            if constante.endswith("_NONE") or ingles in ("", "-", "????????"):
                continue
            espanol = por_ingles.get(normalizar(ingles)) or por_id.get(normalizar(constante[len(prefijo):]), "")
            filas.append((constante, ingles, espanol))
        informe[categoria] = escribir(categoria, filas)

    with open(os.path.join(SALIDA, "PENDIENTES.md"), "w", encoding="utf-8") as f:
        f.write("# Nombres pendientes\n\nGenerado por `tools/dualocke/nombres_oficiales.py`.\n")
        for categoria, (faltan, largos) in informe.items():
            f.write(f"\n## {categoria.capitalize()}\n\n")
            f.write(f"**Sin nombre oficial en PokéAPI ({len(faltan)}):** buscarlos en otra fuente oficial o decidirlos.\n\n")
            f.write(", ".join(f"`{c}` ({i})" for c, i, _ in faltan) or "—")
            f.write(f"\n\n**No caben en {LIMITES[categoria]} caracteres ({len(largos)}):** hará falta abreviarlos.\n\n")
            f.write(", ".join(f"{e} ({len(e)})" for _, _, e in largos) or "—")
            f.write("\n")


if __name__ == "__main__":
    main()
