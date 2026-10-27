"""
Dualocke: habilidades aleatorias (randomizer_config.json, "pokemon" -> "habilidades_aleatorias";
decidido por Miguel en el PR #27, 25/10/2026).

- Por especie: todos los Zigzagoon tienen la misma habilidad, también los del jugador. Cada forma
  (megas, regionales...) es una especie aparte.
- Ninguna prohibida, tampoco en los jefes (Superguarda incluida: "permitir_superguarda").
- Solo se quitan las que dependen de una especie concreta y el juego no deja cambiar (Cambio
  Táctico, Multitipo, Banco, Disfraz...: las que tienen cantBeOverwritten).
- Tampoco salen las de relleno del motor (ABILITY_314 y ABILITY_317, que se llaman "-------", y
  las que dicen "Unimplemented" o "Sin implementar", como Guardia Aura): no hacen nada. Salían al principio y dejaban a 18 especies de la
  semilla de Miguel "sin habilidad" (Wiglett, Onix, Gardevoir...). Para no cambiar las habilidades
  de las partidas en curso, se sortea igual que antes y solo se cambia la que haya caído en una de
  relleno, con un sorteo aparte para esa especie.

El juego cambia la habilidad al vuelo (GetSpeciesAbility, src/pokemon.c) con la tabla que se
genera aquí.
"""

import random
import re

from . import especies as esp


# Habilidades de relleno del motor, que no hacen nada (las rellena leer_habilidades)
RELLENO = set()


def leer_habilidades(cpp="arm-none-eabi-cpp", cppflags=None):
    """{ABILITY_X: nombre} de las habilidades que pueden salir al azar."""
    if cppflags is None:
        cppflags = ["-iquote", "include", "-Wno-trigraphs", "-DMODERN=1", "-DTESTING=0",
                    "-DEMERALD", "-std=gnu17"]
    texto = esp._preprocesar(cpp, cppflags)
    texto = texto[re.search(r"gAbilitiesInfo\[\w*\]\s*=", texto).start():]
    habilidades = {}
    RELLENO.clear()
    for m in re.finditer(r"\[(ABILITY_\w+)\]\s*=\s*\{", texto):
        cuerpo = esp._cuerpo_entre_llaves(texto, m.end() - 1)
        if m.group(1) == "ABILITY_NONE" or re.search(r"\.cantBeOverwritten\s*=\s*(TRUE|1)", cuerpo):
            continue
        nombre = re.findall(r'_\("([^"]*)"\)', cuerpo.split(".description")[0])
        habilidades[m.group(1)] = nombre[-1] if nombre else m.group(1)
        if re.fullmatch(r"ABILITY_\d+", m.group(1)) or "-------" in habilidades[m.group(1)] \
                or "Unimplemented" in cuerpo or "Sin implementar" in cuerpo:
            RELLENO.add(m.group(1))
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
    validas = [h for h in lista if h not in RELLENO]
    rng = random.Random(f"{semilla}|habilidades")
    resultado = {}
    for nombre, e in sorted(pokedex.especies.items()):
        if not e.habilidades:
            continue
        habilidad = rng.choice(lista)
        if habilidad in RELLENO:
            habilidad = random.Random(f"{semilla}|habilidades|{nombre}").choice(validas)
        resultado[nombre] = habilidad
    return resultado


def comprobar(resultado):
    """Ninguna especie con una habilidad de relleno."""
    return [f"{especie}: {h} no hace nada" for especie, h in resultado.items() if h in RELLENO]
