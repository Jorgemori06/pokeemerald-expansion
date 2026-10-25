"""
Dualocke: intercambios con NPCs aleatorios ("objetos" -> "intercambios_internos": totalmente
aleatorios; decidido por Miguel en el PR #27, 25/10/2026).

- El Pokémon que te piden: al azar entre los que salen en la hierba, el agua, la pesca o Golpe
  Roca de esa partida (si no, sería imposible hacer el intercambio), sin legendarios.
- El que te dan: forma base al azar, sin legendarios. Sale al nivel del que entregas, como en el
  original. Cuenta como regalo: si es repetido va a la caja de prohibidos.
- El objeto que lleva (del grupo del suelo) y los IVs, al azar. El mote pasa a ser el nombre de
  la especie y el entrenador original se queda.

No se toca src/data/trade.h: src/trade.c pide los cambios a src/dualocke_aleatorio.c.
"""

import glob
import random
import re


def buscar():
    """Intercambios que se usan en los scripts de Hoenn (INGAME_TRADE_X), en orden."""
    usados = []
    for ruta in sorted(glob.glob("data/maps/*/scripts.inc")):
        if "_Frlg" in ruta:
            continue
        with open(ruta, encoding="utf-8") as f:
            for nombre in re.findall(r"^\s*ingame_trade\s+(INGAME_TRADE_\w+)", f.read(), re.M):
                if nombre not in usados:
                    usados.append(nombre)
    return usados


def especies_salvajes(datos):
    """Especies que salen en los salvajes de Hoenn (wild_encounters.json ya randomizado)."""
    especies = set()
    for grupo in datos["wild_encounter_groups"]:
        if grupo.get("label") != "gWildMonHeaders":
            continue  # la Pirámide y el Pike no cuentan
        for mapa in grupo.get("encounters", []):
            if "_Frlg" in mapa.get("base_label", "") or "_FRLG" in mapa.get("map", ""):
                continue
            for clave, valor in mapa.items():
                if isinstance(valor, dict) and "mons" in valor:
                    especies |= {m["species"] for m in valor["mons"]}
    return especies


def randomizar(pokedex, semilla, datos_salvajes, grupo_objetos):
    """Devuelve {INGAME_TRADE_X: {"especie", "pide", "objeto", "ivs"}}."""
    rng = random.Random(f"{semilla}|intercambios")
    salvajes = sorted(e for e in especies_salvajes(datos_salvajes)
                      if e in pokedex.especies and not pokedex.especies[pokedex.forma_base(e)].es_legendaria)
    raices = pokedex.raices_validas()
    resultado = {}
    for intercambio in buscar():
        resultado[intercambio] = {
            "especie": rng.choice(raices),
            "pide": rng.choice(salvajes),
            "objeto": rng.choice(grupo_objetos) if grupo_objetos else "ITEM_NONE",
            "ivs": [rng.randint(0, 31) for _ in range(6)],
        }
    return resultado
