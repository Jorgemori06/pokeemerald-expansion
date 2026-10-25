"""
Dualocke: habilidades aleatorias (randomizer_config.json, "pokemon" -> "habilidades_aleatorias";
decidido por Miguel en el PR #27, 25/10/2026).

- Por especie: todos los Zigzagoon tienen la misma habilidad, también los del jugador. Cada forma
  (megas, regionales...) es una especie aparte.
- Ninguna prohibida, tampoco en los jefes (Superguarda incluida: "permitir_superguarda").
- Solo se quitan las que dependen de una especie concreta y el juego no deja cambiar (Cambio
  Táctico, Multitipo, Banco, Disfraz...: las que tienen cantBeOverwritten).

El juego cambia la habilidad al vuelo (GetSpeciesAbility, src/pokemon.c) con la tabla que se
genera aquí.
"""

import random
import re

from . import especies as esp


def leer_habilidades(cpp="arm-none-eabi-cpp", cppflags=None):
    """{ABILITY_X: nombre} de las habilidades que pueden salir al azar."""
    if cppflags is None:
        cppflags = ["-iquote", "include", "-Wno-trigraphs", "-DMODERN=1", "-DTESTING=0",
                    "-DEMERALD", "-std=gnu17"]
    texto = esp._preprocesar(cpp, cppflags)
    texto = texto[re.search(r"gAbilitiesInfo\[\w*\]\s*=", texto).start():]
    habilidades = {}
    for m in re.finditer(r"\[(ABILITY_\w+)\]\s*=\s*\{", texto):
        cuerpo = esp._cuerpo_entre_llaves(texto, m.end() - 1)
        if m.group(1) == "ABILITY_NONE" or re.search(r"\.cantBeOverwritten\s*=\s*(TRUE|1)", cuerpo):
            continue
        nombre = re.findall(r'_\("([^"]*)"\)', cuerpo.split(".description")[0])
        habilidades[m.group(1)] = nombre[-1] if nombre else m.group(1)
    if len(habilidades) < 200:
        raise RuntimeError(f"Dualocke: solo se han leído {len(habilidades)} habilidades")
    return habilidades


def randomizar(pokedex, habilidades, semilla, config):
    """{SPECIES_X: ABILITY_Y} para todas las especies que tienen habilidad."""
    if not config.get("pokemon", {}).get("habilidades_aleatorias"):
        return {}
    lista = sorted(habilidades)
    if not config["pokemon"].get("permitir_superguarda", True):
        lista.remove("ABILITY_WONDER_GUARD")
    rng = random.Random(f"{semilla}|habilidades")
    return {nombre: rng.choice(lista) for nombre, e in sorted(pokedex.especies.items()) if e.habilidades}
