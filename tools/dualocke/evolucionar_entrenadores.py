#!/usr/bin/env python3
"""
Dualocke: evoluciona según su nivel a los Pokémon de los entrenadores normales de Hoenn.

Uso (desde la raíz del repo, en este orden):
    python3 tools/dualocke/reescalar_niveles.py
    python3 tools/dualocke/equipos_jefes.py
    python3 tools/dualocke/evolucionar_entrenadores.py

Parte siempre de las especies originales de la expansion (commit BASE) y del nivel que
tenga cada Pokémon ahora, así que se puede volver a lanzar. No toca a los jefes (eso lo
hace equipos_jefes.py) ni a los entrenadores sin tramo (revanchas, postgame…).

Reglas (decididas por Miguel):
- Las evoluciones por nivel se aplican a su nivel normal (Swablu -> Altaria a 35).
- Las que no son por nivel (piedra, amistad, lugar…): la primera evolución a partir del
  nivel 30 y la segunda a partir del 40.
- Si hay varias opciones (Eevee, Wurmple…), se elige una fija por entrenador y Pokémon,
  para que haya variedad pero el resultado sea siempre el mismo.
"""

import glob
import hashlib
import re
import sys

sys.path.insert(0, __file__.rsplit("/", 1)[0].rsplit("\\", 1)[0])
import equipos_jefes as ej  # noqa: E402
import reescalar_niveles as rn  # noqa: E402

NIVEL_SIN_NIVEL_PRIMERA = 30
NIVEL_SIN_NIVEL_SEGUNDA = 40


def leer_especies():
    """Devuelve ({SPECIES_X: nombre}, {nombre: SPECIES_X}, {SPECIES_X: [(nivel o None, SPECIES_Y)]})."""
    nombres, por_nombre, evos = {}, {}, {}
    for archivo in sorted(glob.glob("src/data/pokemon/species_info/gen_*_families.h")):
        with open(archivo, encoding="utf-8") as f:
            texto = "\n".join(l for l in f.read().splitlines() if not l.lstrip().startswith("#"))
        for m in re.finditer(r"^\s*\[(SPECIES_\w+)\]\s*=\s*\{", texto, re.M):
            especie = m.group(1)
            fin = texto.find("\n    [SPECIES_", m.end())
            cuerpo = texto[m.end():fin if fin != -1 else len(texto)]
            nombre = re.search(r'\.speciesName\s*=\s*_\("([^"]*)"\)', cuerpo)
            if nombre:
                nombres[especie] = nombre.group(1)
                por_nombre.setdefault(nombre.group(1).lower(), especie)
            e = re.search(r"\.evolutions\s*=\s*EVOLUTION\((.*?)\),\s*\n", cuerpo, re.S)
            if not e:
                continue
            lista = []
            for metodo, param, destino in re.findall(r"\{(EVO_\w+),\s*([^,]+),\s*(SPECIES_\w+)", e.group(1)):
                if metodo == "EVO_LEVEL" and param.strip().isdigit() and int(param) > 0:
                    lista.append((int(param), destino))
                elif metodo in ("EVO_LEVEL", "EVO_ITEM"):
                    lista.append((None, destino))
            if lista:
                evos[especie] = lista
    return nombres, por_nombre, evos


def evolucionar(especie, nivel, evos, tiene_preevo, semilla):
    while especie in evos:
        opciones = []
        for lv, destino in evos[especie]:
            minimo = lv if lv is not None else (
                NIVEL_SIN_NIVEL_SEGUNDA if especie in tiene_preevo else NIVEL_SIN_NIVEL_PRIMERA)
            if nivel >= minimo and destino not in opciones:
                opciones.append(destino)
        if not opciones:
            break
        elegido = int(hashlib.md5(f"{semilla}{especie}".encode()).hexdigest(), 16) % len(opciones)
        especie = opciones[elegido]
    return especie


def main():
    nombres, por_nombre, evos = leer_especies()
    tiene_preevo = {d for lista in evos.values() for _, d in lista}

    base_txt = rn.git_show(rn.TRAINERS)
    partes_base = re.split(r"^=== (TRAINER_\w+) ===[ \t]*$", base_txt, flags=re.M)
    bloques_base = {partes_base[i]: partes_base[i + 1] for i in range(1, len(partes_base), 2)}
    base = rn.leer_entrenadores(base_txt)
    # Entrenadores normales, revanchas (también las de los líderes) y postgame
    nuevos, _, _ = rn.calcular_entrenadores(base, rn.mapas_de_entrenadores())
    normales = {t for t in nuevos if t not in rn.LIDERES and t not in rn.JEFES_FIJOS
                and t not in ej.EQUIPOS and not ej.RIVAL.match(t)}

    with open(rn.TRAINERS, encoding="utf-8", newline="") as f:
        texto = f.read()
    partes = re.split(r"(^=== (?:TRAINER_\w+) ===[ \t]*$)", texto, flags=re.M)
    cambios, desconocidas = 0, set()
    for i in range(1, len(partes), 2):
        nombre = re.match(r"=== (TRAINER_\w+) ===", partes[i]).group(1)
        if nombre not in normales:
            continue
        cabecera, mons = ej.separar(partes[i + 1])
        _, mons_base = ej.separar(bloques_base[nombre])
        if len(mons) != len(mons_base):
            continue
        nuevos = []
        for n, (mon, mon_base) in enumerate(zip(mons, mons_base)):
            original = ej.especie(mon_base)
            constante = original if original.startswith("SPECIES_") else por_nombre.get(original.lower())
            if not constante:
                desconocidas.add(original)
                nuevos.append(mon)
                continue
            final = evolucionar(constante, ej.nivel_de(mon), evos, tiene_preevo, f"{nombre}{n}")
            nueva = original if final == constante else nombres.get(final, final)
            cambios += final != constante
            # Solo se cambia el nombre de la especie: se conservan el género, el mote y el objeto
            primera, _, resto = mon.partition("\n")
            actual = ej.especie(mon)
            nuevos.append(primera.replace(actual, nueva, 1) + ("\n" + resto if resto else ""))
        partes[i + 1] = "\n" + "\n\n".join([cabecera] + nuevos) + "\n\n"

    with open(rn.TRAINERS, "w", encoding="utf-8", newline="") as f:
        f.write("".join(partes))
    print(f"{cambios} Pokémon evolucionados en {len(normales)} entrenadores normales.")
    if desconocidas:
        print("Especies que no se han reconocido (se quedan igual):", ", ".join(sorted(desconocidas)))


if __name__ == "__main__":
    main()
