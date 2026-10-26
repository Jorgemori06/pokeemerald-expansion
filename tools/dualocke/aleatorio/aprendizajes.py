"""
Dualocke: movimientos que aprende cada especie al subir de nivel, al azar (randomizer_config.json,
"movimientos_y_mt" -> "aprendizaje_aleatorio"; pedido por Miguel el 26/10/2026, al ver en la
partida que todo aprendía los movimientos de siempre).

- Cada tabla de movimientos por nivel conserva sus niveles (se aprende lo mismo de veces y a los
  mismos niveles), pero cada movimiento cambia por uno al azar entre los válidos
  (movimientos.validos: sin Movimientos Z, Dinamax ni los que Metrónomo no puede usar).
- Tope de potencia según el nivel al que se aprende, como el cuarto movimiento de los
  entrenadores (40 + 1,5 por nivel: a nivel 5, hasta 47; a nivel 40, hasta 100). Los que se
  aprenden al evolucionar (nivel 0) cuentan como nivel 30.
- Cada movimiento es de daño con un 60 % de probabilidad (PROBABILIDAD_DANO) y de estado si no:
  al azar puro salían demasiados de estado (Treecko con Hora del Té, Canto y Encanto).
- Entre los de daño, los de uno de sus tipos son más probables (PREFERENCIA_SU_TIPO).
- Sin repetir movimiento en la misma tabla.
- Entre los que aprende hasta nivel 5 hay al menos uno de daño, para poder combatir desde el
  principio.
- Se randomiza por tabla: las formas que compartían tabla siguen compartiéndola.

Lo usan los salvajes, los Pokémon del jugador, el que recuerda movimientos y los entrenadores
(sus 3 movimientos "de nivel" salen de estas tablas nuevas).
"""

import random

from . import movimientos as mov

# Probabilidad de que cada movimiento de la tabla sea de daño
PROBABILIDAD_DANO = 0.6
# Movimientos que no se aprenden por nivel: Plegaria Vital revive en pleno combate a un Pokémon
# debilitado, y en el locke eso se salta la muerte
PROHIBIDOS = {"MOVE_REVIVAL_BLESSING"}
# Entre los de daño, cuánto más probable es uno de sus tipos que uno de otro tipo
PREFERENCIA_SU_TIPO = 3.0
NIVEL_AL_EVOLUCIONAR = 30
NIVEL_PRIMER_DANO = 5


def _tope(nivel, tope):
    if not tope:
        return 999
    return tope[0] + tope[1] * (nivel or NIVEL_AL_EVOLUCIONAR)


def _tabla_nueva(original, tipos, movimientos, todos, rng, tope):
    nuevos = []
    for nivel, _ in original:
        maxima = _tope(nivel, tope)
        opciones = [m for m in todos if m not in nuevos
                    and (not movimientos[m].de_dano or mov.potencia(movimientos[m]) <= maxima)]
        dano = rng.random() < PROBABILIDAD_DANO
        opciones = [m for m in opciones if movimientos[m].de_dano == dano] or opciones
        pesos = [PREFERENCIA_SU_TIPO if movimientos[m].de_dano and movimientos[m].tipo in tipos else 1.0
                 for m in opciones]
        nuevos.append(rng.choices(opciones, weights=pesos)[0])
    # Al menos uno de daño entre los primeros, para no empezar solo con Gruñido y Látigo
    primeros = [i for i, (nivel, _) in enumerate(original) if nivel <= NIVEL_PRIMER_DANO]
    if primeros and not any(movimientos[nuevos[i]].de_dano for i in primeros):
        i = primeros[0]
        maxima = _tope(original[i][0], tope)
        opciones = [m for m in todos if m not in nuevos and movimientos[m].de_dano
                    and mov.potencia(movimientos[m]) <= maxima]
        suyas = [m for m in opciones if movimientos[m].tipo in tipos]
        nuevos[i] = rng.choice(suyas or opciones)
    return [(nivel, m) for (nivel, _), m in zip(original, nuevos)]


def randomizar(pokedex, movimientos, semilla, config):
    """Devuelve {SPECIES_X: [(nivel, MOVE_Y)]} con las tablas nuevas, o {} si está desactivado."""
    cfg = config.get("movimientos_y_mt", {})
    if not cfg.get("aprendizaje_aleatorio"):
        return {}
    tope = config.get("entrenadores", {}).get("movimientos", {}).get(
        "potencia_maxima_del_cuarto", {"base": 40, "por_nivel": 1.5})
    tope = (tope["base"], tope["por_nivel"]) if tope else None
    todos = [m for m in mov.validos(movimientos) if m not in PROHIBIDOS]
    por_tabla = {}
    resultado = {}
    for nombre in sorted(pokedex.especies):
        e = pokedex.especies[nombre]
        if not e.por_nivel or not e.tabla_aprendizaje:
            continue
        if e.tabla_aprendizaje not in por_tabla:
            rng = random.Random(f"{semilla}|aprendizajes|{e.tabla_aprendizaje}")
            por_tabla[e.tabla_aprendizaje] = _tabla_nueva(e.por_nivel, set(e.tipos), movimientos, todos, rng, tope)
        resultado[nombre] = por_tabla[e.tabla_aprendizaje]
    return resultado


def comprobar(pokedex, movimientos, resultado, config):
    """Mismos niveles que el original, sin repetidos, sin movimientos prohibidos y dentro del tope."""
    errores = []
    validos = set(mov.validos(movimientos)) - PROHIBIDOS
    tope = config.get("entrenadores", {}).get("movimientos", {}).get(
        "potencia_maxima_del_cuarto", {"base": 40, "por_nivel": 1.5})
    tope = (tope["base"], tope["por_nivel"]) if tope else None
    for especie, tabla in resultado.items():
        original = pokedex.especies[especie].por_nivel
        if [n for n, _ in tabla] != [n for n, _ in original]:
            errores.append(f"{especie}: cambian los niveles")
        nuevos = [m for _, m in tabla]
        if len(set(nuevos)) != len(nuevos):
            errores.append(f"{especie}: movimiento repetido")
        for nivel, m in tabla:
            if m not in validos:
                errores.append(f"{especie}: {m} no puede salir")
            elif movimientos[m].de_dano and mov.potencia(movimientos[m]) > _tope(nivel, tope):
                errores.append(f"{especie}: {m} pasa del tope a nivel {nivel}")
    return errores
