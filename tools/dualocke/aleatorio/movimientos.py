"""
Dualocke: movimientos de los entrenadores (randomizer_config.json, "entrenadores" ->
"movimientos"; decidido por Miguel en el PR #27, 25/10/2026).

- 3 de los que aprende por nivel (hasta su nivel) y el cuarto al azar entre todos.
- Ligera preferencia por los potentes, igual para todos (los jefes no llevan mejores
  movimientos que el resto).
- Diversidad de tipos: se evita repetir el tipo de un movimiento de daño.
- Al menos uno de daño, si puede.
- El cuarto, al azar pero con un tope de potencia según el nivel (40 + 1,5 por nivel: a nivel 7,
  hasta 50; a nivel 40, hasta 100; desde nivel 74, sin tope). Si no, un entrenador de nivel 5
  podría llevar Hidrobomba. Se cambia con "potencia_maxima_del_cuarto" en el config.
"""

import random
import re

from . import especies as esp

# Cuánto más probable es un movimiento de 100 de potencia que uno de estado (1 + 0.5 = 1.5 veces)
PREFERENCIA_POTENTES = 0.5
# Si ya lleva un movimiento de daño de ese tipo, el siguiente de ese tipo es así de probable
REPETIR_TIPO = 0.35


class Movimiento:
    def __init__(self, constante, campos, nombre):
        self.constante = constante
        self.nombre = nombre
        self.tipo = _texto(campos.get("type", "TYPE_NORMAL"))
        self.categoria = _texto(campos.get("category", "DAMAGE_CATEGORY_STATUS"))
        self.potencia = _valor(campos.get("power", "0"))
        self.vetado = _valor(campos.get("metronomeBanned", "0")) != 0

    @property
    def de_dano(self):
        return self.categoria != "DAMAGE_CATEGORY_STATUS" and self.potencia > 0


def _valor(expr):
    """Valor de una expresión numérica ya preprocesada: 90, 8 >= 6 ? 60 : 40..."""
    expr = expr.strip()
    if re.fullmatch(r"\d+", expr):
        return int(expr)
    m = re.fullmatch(r"(.+?)\?(.+?):(.+)", expr)
    if m:
        return _valor(m.group(2)) if _valor(m.group(1)) else _valor(m.group(3))
    if re.fullmatch(r"[\d\s<>=!&|()+\-*/]+", expr):
        try:
            return int(eval(expr.replace("&&", " and ").replace("||", " or ")))  # noqa: S307
        except (SyntaxError, ValueError, ZeroDivisionError):
            return 0
    return 0


def _texto(expr):
    """Igual que _valor, para constantes: 8 >= 1 ? TYPE_MYSTERY : TYPE_NORMAL."""
    m = re.fullmatch(r"(.+?)\?(.+?):(.+)", expr.strip())
    if m:
        return _texto(m.group(2)) if _valor(m.group(1)) else _texto(m.group(3))
    return expr.strip()


def _normales():
    """Movimientos normales (con número, antes de MOVES_COUNT): sin Movimientos Z ni Dinamax."""
    with open("include/constants/moves.h", encoding="utf-8") as f:
        texto = f.read()
    texto = texto[:texto.index("MOVES_COUNT_GEN9")]
    return set(re.findall(r"^\s*(MOVE_\w+)\s*=\s*\d+\s*,", texto, re.M))


def leer_movimientos(cpp="arm-none-eabi-cpp", cppflags=None):
    """Lee gMovesInfo de src/move.c. Devuelve {MOVE_X: Movimiento}."""
    if cppflags is None:
        cppflags = ["-iquote", "include", "-Wno-trigraphs", "-DMODERN=1", "-DTESTING=0",
                    "-DEMERALD", "-std=gnu17"]
    texto = esp._preprocesar(cpp, cppflags, "src/move.c")
    texto = texto[re.search(r"gMovesInfo\[\w*\]\s*=", texto).start():]
    movimientos = {}
    for m in re.finditer(r"\[(MOVE_\w+)\]\s*=\s*\{", texto):
        cuerpo = esp._cuerpo_entre_llaves(texto, m.end() - 1)
        campos = dict(re.findall(r"^\s*\.(\w+)\s*=\s*([^,\n]+),\s*$", cuerpo, re.M))
        nombre = re.search(r'COMPOUND_STRING\("([^"]*)"\)', campos.get("name", ""))
        movimientos[m.group(1)] = Movimiento(m.group(1), campos, nombre.group(1) if nombre else "?")
    if len(movimientos) < 500:
        raise RuntimeError(f"Dualocke: solo se han leído {len(movimientos)} movimientos de src/move.c")
    return movimientos


def validos(movimientos):
    """Movimientos que pueden salir al azar: los que Metrónomo puede usar (sin Movimientos Z,
    Dinamax, Forcejeo, exclusivos raros...)."""
    normales = _normales()
    return sorted(c for c, m in movimientos.items() if c != "MOVE_NONE" and not m.vetado and c in normales)


def _peso(mov, elegidos, movimientos):
    if not mov.de_dano:
        return 1.0
    peso = 1.0 + PREFERENCIA_POTENTES * min(potencia(mov), 150) / 100
    if any(movimientos[e].de_dano and movimientos[e].tipo == mov.tipo for e in elegidos):
        peso *= REPETIR_TIPO
    return peso


def _sacar(opciones, elegidos, movimientos, rng):
    opciones = [o for o in opciones if o not in elegidos]
    if not opciones:
        return None
    pesos = [_peso(movimientos[o], elegidos, movimientos) for o in opciones]
    return rng.choices(opciones, weights=pesos)[0]


def potencia(mov):
    return 60 if mov.potencia == 1 else mov.potencia


def elegir(especie, nivel, pokedex, movimientos, todos, rng, garantizados=3, tope=(40, 1.5)):
    """Los 4 movimientos de un Pokémon de entrenador. `tope`: (base, por nivel) de la potencia
    máxima del movimiento al azar."""
    por_nivel = sorted({mv for nv, mv in pokedex.especies[especie].por_nivel
                        if nv <= nivel and mv in movimientos and mv != "MOVE_NONE"})
    elegidos = []
    while len(elegidos) < garantizados:
        mv = _sacar(por_nivel, elegidos, movimientos, rng)
        if mv is None:
            break
        elegidos.append(mv)
    # El resto (el cuarto, o más si no aprende suficientes por nivel), al azar entre todos; si
    # no lleva ninguno de daño, el último es de daño
    maxima = tope[0] + tope[1] * nivel if tope else 999
    todos = [t for t in todos if not movimientos[t].de_dano or potencia(movimientos[t]) <= maxima]
    while len(elegidos) < 4:
        falta_dano = not any(movimientos[e].de_dano for e in elegidos)
        opciones = todos
        if falta_dano and len(elegidos) == 3:
            opciones = [t for t in todos if movimientos[t].de_dano]
        mv = _sacar(opciones, elegidos, movimientos, rng)
        if mv is None:
            break
        elegidos.append(mv)
    return elegidos
