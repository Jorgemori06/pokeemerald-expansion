"""
Dualocke: estáticos y regalos aleatorios.

Decidido por Jorge (25/10/2026):
- Estáticos (los combates con setwildbattle: Kecleon, Voltorb, Electrode, Regis, Groudon,
  Kyogre, Rayquaza, Sudowoodo; y los errantes Latios/Latias): **todo al azar**, cualquier
  especie, legendarios incluidos. Cada especie original cambia por la misma en todos sus
  sitios: todos los Kecleon del Detector son la misma especie nueva.
- Regalos (Beldum, fósiles, Castform, iniciales de Johto, huevos de Wynaut y Pichu): al azar,
  sin legendarios, ajustados a su nivel. Los huevos, siempre la forma base.
- El sprite del mapa sigue siendo el del original (da igual: se descubre al empezar el combate).

No se tocan los scripts: el juego cambia la especie al vuelo con la tabla que se genera aquí
(src/data/dualocke_aleatorio.h, la escribe cabecera.py y la usa src/dualocke_aleatorio.c).
"""

import glob
import random
import re

ERRANTES = {"SPECIES_LATIAS": 40, "SPECIES_LATIOS": 40}  # src/roamer.c (InitRoamer)


def _scripts_de_hoenn():
    archivos = sorted(glob.glob("data/maps/*/scripts.inc")) + sorted(glob.glob("data/scripts/*.inc"))
    return [a for a in archivos if "_Frlg" not in a and not a.endswith("debug.inc")]


def buscar(alias):
    """Devuelve ({especie estática: nivel máximo}, {especie regalo: nivel}, {especie huevo})."""
    estaticos, regalos, huevos = dict(ERRANTES), {}, set()
    for archivo in _scripts_de_hoenn():
        with open(archivo, encoding="utf-8") as f:
            texto = f.read()
        for especie, nivel in re.findall(r"^\s*setwildbattle\s+(SPECIES_\w+)\s*,\s*(\d+)", texto, re.M):
            especie = alias.get(especie, especie)
            estaticos[especie] = max(estaticos.get(especie, 0), int(nivel))
        for especie, nivel in re.findall(r"^\s*givemon\s+(SPECIES_\w+)\s*,\s*(\d+)", texto, re.M):
            especie = alias.get(especie, especie)
            regalos[especie] = max(regalos.get(especie, 0), int(nivel))
        for especie in re.findall(r"^\s*giveegg\s+(SPECIES_\w+)", texto, re.M):
            huevos.add(alias.get(especie, especie))
    return estaticos, regalos, huevos


def randomizar(pokedex, semilla):
    """Devuelve ({original: nueva} de estáticos, {original: nueva} de regalos y huevos)."""
    estaticos, regalos, huevos = buscar(pokedex.alias)
    rng = random.Random(f"{semilla}|estaticos")
    todas = pokedex.raices_validas(con_legendarios=True)
    sin_legendarios = pokedex.raices_validas()

    mapa_estaticos, usadas = {}, set()
    for original in sorted(estaticos):
        raiz = rng.choice([r for r in todas if r not in usadas] or todas)
        usadas.add(raiz)
        mapa_estaticos[original] = pokedex.evolucionar(raiz, estaticos[original], rng)

    mapa_regalos = {}
    for original in sorted(regalos):
        raiz = rng.choice([r for r in sin_legendarios if r not in usadas] or sin_legendarios)
        usadas.add(raiz)
        mapa_regalos[original] = pokedex.evolucionar(raiz, regalos[original], rng)
    for original in sorted(huevos):
        raiz = rng.choice([r for r in sin_legendarios if r not in usadas] or sin_legendarios)
        usadas.add(raiz)
        mapa_regalos[original] = raiz
    return mapa_estaticos, mapa_regalos

