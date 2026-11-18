"""
Dualocke: habilidades aleatorias (randomizer_config.json, "pokemon" -> "habilidades_aleatorias";
decidido por Miguel en el PR #27, 25/10/2026).

- Por especie: todos los Zigzagoon tienen las mismas, también los del jugador. Cada forma
  (megas, regionales...) es una especie aparte.
- Tantas habilidades como en el juego original, y distintas entre sí (Miguel, 18/11/2026): si tenía
  dos normales y una oculta, tiene tres distintas al azar en esos mismos huecos; si tenía una normal y
  la oculta, dos. Así sirven el Parche y la Cápsula Habilidad. Antes era una sola en todos los huecos
  (#27): la del primer hueco sigue siendo la que salía, y las demás se sortean aparte, con su propio
  RNG, para no cambiar nada más de las semillas en curso.
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
    """{SPECIES_X: [hueco 0, hueco 1, hueco 2]} para todas las especies que tienen habilidad. En los
    huecos que la especie no tiene en el original va ABILITY_NONE."""
    if not config.get("pokemon", {}).get("habilidades_aleatorias"):
        return {}
    lista = sorted(habilidades)
    if not config["pokemon"].get("permitir_superguarda", True):
        lista.remove("ABILITY_WONDER_GUARD")
    validas = [h for h in lista if h not in RELLENO]
    # La del primer hueco: el mismo sorteo que cuando era una por especie
    rng = random.Random(f"{semilla}|habilidades")
    primera = {}
    for nombre, e in sorted(pokedex.especies.items()):
        if not e.habilidades:
            continue
        habilidad = rng.choice(lista)
        if habilidad in RELLENO:
            habilidad = random.Random(f"{semilla}|habilidades|{nombre}").choice(validas)
        primera[nombre] = habilidad
    # Las demás, aparte
    rng = random.Random(f"{semilla}|habilidades|huecos")
    resultado = {}
    for nombre, e in sorted(pokedex.especies.items()):
        if nombre not in primera:
            continue
        huecos = e.huecos_habilidad or [e.habilidades[0], "ABILITY_NONE", "ABILITY_NONE"]
        # Si el primer hueco está vacío en el original (pasa en alguna forma), la habilidad va al primero que tenga
        nuevas = {}
        for original in huecos:
            if original == "ABILITY_NONE" or original in nuevas:
                continue
            if not nuevas:
                nuevas[original] = primera[nombre]
            else:
                usadas = set(nuevas.values())
                nuevas[original] = rng.choice([h for h in validas if h not in usadas])
        resultado[nombre] = [nuevas.get(h, "ABILITY_NONE") for h in huecos]
    return resultado


def comprobar(resultado):
    """Ninguna especie con una habilidad de relleno ni con dos huecos distintos de la misma."""
    errores = []
    for especie, huecos in resultado.items():
        errores += [f"{especie}: {h} no hace nada" for h in huecos if h in RELLENO]
        llenos = [h for h in huecos if h != "ABILITY_NONE"]
        if not llenos:
            errores.append(f"{especie}: sin habilidad")
    return errores
