"""
Dualocke: MT aleatorias (randomizer_config.json, "movimientos_y_mt"; decidido por Miguel en el PR
#27, 25/10/2026).

- Cada MT enseña un movimiento al azar (la MT26 deja de ser Terremoto). No se repiten.
- Las de movimientos de campo se quedan como están (Excavar, Daño Secreto...), y las MO también.
- Tutores: también enseñan un movimiento al azar (sin repetir los de las MT).
- Compatibilidad: cada especie puede aprender cada MT nueva (y cada movimiento nuevo de tutor) con
  un 50 % de probabilidad, sin excepción para las de su tipo. Las que se quedan (las de campo y las MO) mantienen la
  compatibilidad original, para no quedarse sin poder avanzar.

No se toca include/constants/tms_hms.h: el juego pregunta qué enseña cada MT y quién la puede
aprender a src/dualocke_aleatorio.c, con la tabla que se genera aquí.
"""

import random
import re

from . import movimientos as mov


def leer_mts():
    """[(ITEM_TM_X, MOVE_X)] de FOREACH_TM, en orden."""
    with open("include/constants/tms_hms.h", encoding="utf-8") as f:
        texto = f.read()
    bloque = texto[texto.index("#define FOREACH_TM(F)"):texto.index("#define FOREACH_HM(F)")]
    return [(f"ITEM_TM_{n}", f"MOVE_{n}") for n in re.findall(r"F\((\w+)\)", bloque)]


def movimientos_de_campo():
    with open("include/constants/field_move.h", encoding="utf-8") as f:
        return {"MOVE_" + n for n in re.findall(r"FIELD_MOVE_(\w+)\s*,", f.read())}


def randomizar(movimientos, semilla, config):
    """{ITEM_TM_X: MOVE_NUEVO} de las MT que cambian, y el % de compatibilidad."""
    cfg = config.get("movimientos_y_mt", {})
    if not cfg.get("mt_aleatorias"):
        return {}, 0
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
    usados = set(mapa_mts.values()) | {m for _, m in leer_mts()} | campo
    opciones = [m for m in mov.validos(movimientos) if m not in usados]
    nuevos = {}
    for original in originales:
        if original in campo:
            continue
        nuevo = rng.choice(opciones)
        opciones.remove(nuevo)
        nuevos[original] = nuevo
    return nuevos
