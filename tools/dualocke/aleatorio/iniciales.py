"""
Dualocke: iniciales aleatorios (randomizer_config.json, "iniciales"; decidido por Miguel).

- Forma base de una línea de 3 fases, sin legendarios.
- Los tres forman un triángulo de tipos por su tipo principal: A gana a B, B gana a C y C gana
  a A, como Fuego > Planta > Agua > Fuego.
- Para que el jugador pueda evolucionarlo, las dos evoluciones tienen que ser por nivel o con
  objeto (las que se pueden hacer en el juego sin intercambios).

Se devuelven en el orden de sStarterMon (src/starter_choose.c), que en el original es
[Planta, Fuego, Agua]: el segundo gana al primero, el tercero al segundo y el primero al
tercero. Así el rival, que lleva "el que gana al del jugador", sigue la misma lógica que en
Esmeralda.
"""

import random

# Tabla de tipos (generación 6 en adelante): atacante -> tipos a los que hace x2
SUPEREFICAZ = {
    "TYPE_NORMAL": set(),
    "TYPE_FIRE": {"TYPE_GRASS", "TYPE_ICE", "TYPE_BUG", "TYPE_STEEL"},
    "TYPE_WATER": {"TYPE_FIRE", "TYPE_GROUND", "TYPE_ROCK"},
    "TYPE_ELECTRIC": {"TYPE_WATER", "TYPE_FLYING"},
    "TYPE_GRASS": {"TYPE_WATER", "TYPE_GROUND", "TYPE_ROCK"},
    "TYPE_ICE": {"TYPE_GRASS", "TYPE_GROUND", "TYPE_FLYING", "TYPE_DRAGON"},
    "TYPE_FIGHTING": {"TYPE_NORMAL", "TYPE_ICE", "TYPE_ROCK", "TYPE_DARK", "TYPE_STEEL"},
    "TYPE_POISON": {"TYPE_GRASS", "TYPE_FAIRY"},
    "TYPE_GROUND": {"TYPE_FIRE", "TYPE_ELECTRIC", "TYPE_POISON", "TYPE_ROCK", "TYPE_STEEL"},
    "TYPE_FLYING": {"TYPE_GRASS", "TYPE_FIGHTING", "TYPE_BUG"},
    "TYPE_PSYCHIC": {"TYPE_FIGHTING", "TYPE_POISON"},
    "TYPE_BUG": {"TYPE_GRASS", "TYPE_PSYCHIC", "TYPE_DARK"},
    "TYPE_ROCK": {"TYPE_FIRE", "TYPE_ICE", "TYPE_FLYING", "TYPE_BUG"},
    "TYPE_GHOST": {"TYPE_PSYCHIC", "TYPE_GHOST"},
    "TYPE_DRAGON": {"TYPE_DRAGON"},
    "TYPE_DARK": {"TYPE_PSYCHIC", "TYPE_GHOST"},
    "TYPE_STEEL": {"TYPE_ICE", "TYPE_ROCK", "TYPE_FAIRY"},
    "TYPE_FAIRY": {"TYPE_FIGHTING", "TYPE_DRAGON", "TYPE_DARK"},
}


def gana(a, b):
    return b in SUPEREFICAZ.get(a, set())


def _tres_fases(pokedex, raiz):
    """True si la línea tiene 3 fases y se puede evolucionar en el juego (nivel u objeto)."""
    e = pokedex.especies[raiz]
    for _, medio in e.evoluciones:
        if medio in pokedex.especies and pokedex.especies[medio].evoluciones:
            return True
    return False


def candidatos(pokedex):
    resultado = []
    for raiz in pokedex.raices_validas():
        if pokedex.forma_base(raiz) != raiz:
            continue
        if not pokedex.especies[raiz].tipos or not _tres_fases(pokedex, raiz):
            continue
        resultado.append(raiz)
    return resultado


def elegir(pokedex, semilla):
    """Devuelve [inicial_0, inicial_1, inicial_2]: el 1 gana al 0, el 2 al 1 y el 0 al 2."""
    rng = random.Random(f"{semilla}|iniciales")
    lista = candidatos(pokedex)
    por_tipo = {}
    for raiz in lista:
        por_tipo.setdefault(pokedex.especies[raiz].tipos[0], []).append(raiz)
    triangulos = []
    tipos = sorted(por_tipo)
    for a in tipos:
        for b in tipos:
            for c in tipos:
                if len({a, b, c}) == 3 and gana(b, a) and gana(c, b) and gana(a, c):
                    triangulos.append((a, b, c))
    a, b, c = rng.choice(triangulos)
    return [rng.choice(sorted(por_tipo[a])), rng.choice(sorted(por_tipo[b])), rng.choice(sorted(por_tipo[c]))]


def cabecera(iniciales, comentario):
    nombres = ("GRASS", "FIRE", "WATER")
    lineas = ["// Generado por el Makefile (Dualocke, tools/dualocke/randomizer.py): no editar.",
              f"// {comentario}"]
    for nombre, especie in zip(nombres, iniciales):
        lineas.append(f"#define DUALOCKE_STARTER_{nombre} {especie}")
    return "\n".join(lineas) + "\n"
