"""
Dualocke: MT aleatorias (randomizer_config.json, "movimientos_y_mt"; decidido por Miguel en el PR
#27, 25/10/2026).

- Cada MT enseña un movimiento al azar (la MT26 deja de ser Terremoto). No se repiten.
- Las de movimientos de campo se quedan como están (Excavar, Daño Secreto...), y las MO también.
- Tutores: también enseñan un movimiento al azar (sin repetir los de las MT).
- Compatibilidad: cada especie puede aprender cada MT nueva (y cada movimiento nuevo de tutor) con
  un 50 % de probabilidad, sin excepción para las de su tipo. Las que se quedan (las de campo y las MO) mantienen la
  compatibilidad original, para no quedarse sin poder avanzar.

Ni las MT ni los tutores enseñan los de PROHIBIDOS (Plegaria Vital revive a un debilitado en pleno
combate y se saltaría las muertes del locke). Para no cambiar las partidas en curso, se sortea
igual que antes y solo se vuelve a sortear, aparte, la MT o el tutor que haya caído en uno.

No se toca include/constants/tms_hms.h: el juego pregunta qué enseña cada MT y quién la puede
aprender a src/dualocke_aleatorio.c, con la tabla que se genera aquí.
"""

import random
import re

from . import movimientos as mov


# Movimientos que no pueden enseñar las MT ni los tutores (los mismos que aprendizajes.PROHIBIDOS)
PROHIBIDOS = {"MOVE_REVIVAL_BLESSING"}


def _sin_prohibidos(nuevos, opciones, semilla, que, evitar=()):
    """Cambia los de PROHIBIDOS (y los de `evitar`) que hayan salido por otro de `opciones` (los
    que quedaban libres)."""
    libres = [m for m in opciones if m not in PROHIBIDOS and m not in evitar]
    for clave, movimiento in list(nuevos.items()):
        if movimiento in PROHIBIDOS or movimiento in evitar:
            otro = random.Random(f"{semilla}|{que}|{clave}").choice(libres)
            libres.remove(otro)
            nuevos[clave] = otro
    return nuevos


def comprobar(mapa_mts, tutores):
    """Ninguna MT ni tutor enseña un movimiento prohibido."""
    return [f"{clave}: enseña {m}" for clave, m in list(mapa_mts.items()) + list(tutores.items())
            if m in PROHIBIDOS]


def leer_mts():
    """[(ITEM_TM_X, MOVE_X)] de FOREACH_TM, en orden."""
    with open("include/constants/tms_hms.h", encoding="utf-8") as f:
        texto = f.read()
    bloque = texto[texto.index("#define FOREACH_TM(F)"):texto.index("#define FOREACH_HM(F)")]
    return [(f"ITEM_TM_{n}", f"MOVE_{n}") for n in re.findall(r"F\((\w+)\)", bloque)]


def movimientos_de_campo():
    with open("include/constants/field_move.h", encoding="utf-8") as f:
        return {"MOVE_" + n for n in re.findall(r"FIELD_MOVE_(\w+)\s*,", f.read())}


def _sorteo_mts(movimientos, semilla, config):
    """El sorteo de las MT tal cual, sin quitar los prohibidos: ({ITEM_TM_X: MOVE_NUEVO}, los
    movimientos que han quedado libres)."""
    cfg = config.get("movimientos_y_mt", {})
    if not cfg.get("mt_aleatorias"):
        return {}, []
    rng = random.Random(f"{semilla}|mt")
    campo = movimientos_de_campo() if cfg.get("conservar_movimientos_de_campo", True) else set()
    mts = leer_mts()
    with open("include/constants/tms_hms.h", encoding="utf-8") as f:
        texto = f.read()
    mos = {f"MOVE_{n}" for n in re.findall(r"F\((\w+)\)", texto[texto.index("#define FOREACH_HM(F)"):])}
    usados = {m for _, m in mts if m in campo} | mos
    opciones = [m for m in mov.validos(movimientos) if m not in usados]
    nuevas = {}
    for objeto, original in mts:
        if original in campo:
            continue
        nuevo = rng.choice(opciones)
        opciones.remove(nuevo)
        nuevas[objeto] = nuevo
    return nuevas, opciones


def randomizar(movimientos, semilla, config):
    """{ITEM_TM_X: MOVE_NUEVO} de las MT que cambian, y el % de compatibilidad."""
    cfg = config.get("movimientos_y_mt", {})
    if not cfg.get("mt_aleatorias"):
        return {}, 0
    nuevas, opciones = _sorteo_mts(movimientos, semilla, config)
    _sin_prohibidos(nuevas, opciones, semilla, "mt")
    # Las MT nuevas no están en las listas de compatibilidad originales: siempre va por porcentaje
    return nuevas, int(cfg.get("compatibilidad_porcentaje", 50))


def randomizar_tutores(movimientos, semilla, config, mapa_mts):
    """{MOVE_ORIGINAL: MOVE_NUEVO} de los tutores de Hoenn (data/scripts/move_tutors.inc).
    Movimientos al azar, sin repetir los de las MT; los de campo se quedan. Se aprenden con la
    misma probabilidad que las MT."""
    cfg = config.get("movimientos_y_mt", {})
    if not cfg.get("tutores_aleatorios"):
        return {}
    with open("data/scripts/move_tutors.inc", encoding="utf-8") as f:
        originales = list(dict.fromkeys(re.findall(r"^\s*move_tutor\s+(MOVE_\w+)", f.read(), re.M)))
    rng = random.Random(f"{semilla}|tutores")
    campo = movimientos_de_campo() if cfg.get("conservar_movimientos_de_campo", True) else set()
    # Se parte del sorteo de las MT sin sustituciones, para que los tutores salgan igual que antes
    crudas, _ = _sorteo_mts(movimientos, semilla, config)
    usados = set(crudas.values()) | {m for _, m in leer_mts()} | campo
    opciones = [m for m in mov.validos(movimientos) if m not in usados]
    nuevos = {}
    for original in originales:
        if original in campo:
            continue
        nuevo = rng.choice(opciones)
        opciones.remove(nuevo)
        nuevos[original] = nuevo
    # Tampoco repiten el movimiento que haya sustituido a un prohibido en una MT
    return _sin_prohibidos(nuevos, opciones, semilla, "tutores", set(mapa_mts.values()))
