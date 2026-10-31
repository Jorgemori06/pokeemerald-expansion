"""
Dualocke: líderes con estrategia y con la fuerza de los salvajes al principio
(randomizer_config.json, "lideres"; pedido por Miguel y Jorge el 31/10/2026: "que los líderes
sean difíciles, que tengan una estrategia", pero sin sacar Pokémon mucho más fuertes que los
que encuentras).

- Movimientos con plan (líderes, Alto Mando y Plubio):
  - El primero del equipo pone trampas (y solo él): Trampa Rocas, Púas, Púas Tóxicas o Red Viscosa, según su
    tipo (Trampa Rocas si no tiene una de su tipo).
  - Los demás llevan movimientos de estrategia de su tipo o de su papel: envenenar o quemar,
    paralizar, chetarse (Danza Espada, Maquinación, Paz Mental, Danza Dragón...), clima,
    pantallas, recuperarse.
  - Hasta el gimnasio 3, un movimiento de estrategia por Pokémon; después, dos.
  - El resto son ataques **de los que aprende por nivel** (las tablas al azar de aprendizajes.py),
    los mejores para él (de su tipo y potentes). Así no pegan más fuerte que lo que podría tener
    el jugador. Si no aprende suficientes ataques hasta su nivel, se completa al azar.
- Fuerza de los salvajes (los marcados en "limite_salvajes", hasta el gimnasio 3): sus Pokémon no
  pueden tener más estadísticas base (suma) que el percentil "percentil_salvajes" de los salvajes
  de hierba de los tramos hasta ese gimnasio, con la semilla de la partida. Si los salvajes aún
  no han evolucionado, el líder tampoco.
"""

import fnmatch
import random

from . import movimientos as mov

TRAMPAS = ["MOVE_STEALTH_ROCK", "MOVE_SPIKES", "MOVE_TOXIC_SPIKES", "MOVE_STICKY_WEB"]
TRAMPA_POR_TIPO = {
    "TYPE_ROCK": "MOVE_STEALTH_ROCK", "TYPE_GROUND": "MOVE_SPIKES", "TYPE_STEEL": "MOVE_STEALTH_ROCK",
    "TYPE_POISON": "MOVE_TOXIC_SPIKES", "TYPE_BUG": "MOVE_STICKY_WEB",
}
ESTRATEGIA_POR_TIPO = {
    "TYPE_POISON": ["MOVE_TOXIC", "MOVE_TOXIC_SPIKES"],
    "TYPE_ROCK": ["MOVE_STEALTH_ROCK", "MOVE_SANDSTORM"],
    "TYPE_GROUND": ["MOVE_STEALTH_ROCK", "MOVE_SPIKES"],
    "TYPE_STEEL": ["MOVE_IRON_DEFENSE", "MOVE_STEALTH_ROCK"],
    "TYPE_FIRE": ["MOVE_WILL_O_WISP", "MOVE_SUNNY_DAY"],
    "TYPE_WATER": ["MOVE_RAIN_DANCE", "MOVE_AQUA_RING"],
    "TYPE_ELECTRIC": ["MOVE_THUNDER_WAVE"],
    "TYPE_GRASS": ["MOVE_LEECH_SEED", "MOVE_STUN_SPORE"],
    "TYPE_ICE": ["MOVE_SNOWSCAPE", "MOVE_HAZE"],
    "TYPE_FIGHTING": ["MOVE_BULK_UP"],
    "TYPE_PSYCHIC": ["MOVE_CALM_MIND", "MOVE_REFLECT", "MOVE_LIGHT_SCREEN"],
    "TYPE_GHOST": ["MOVE_WILL_O_WISP", "MOVE_CONFUSE_RAY"],
    "TYPE_DARK": ["MOVE_NASTY_PLOT", "MOVE_TAUNT"],
    "TYPE_DRAGON": ["MOVE_DRAGON_DANCE"],
    "TYPE_FLYING": ["MOVE_ROOST", "MOVE_TAILWIND"],
    "TYPE_BUG": ["MOVE_QUIVER_DANCE", "MOVE_STICKY_WEB"],
    "TYPE_NORMAL": ["MOVE_SWORDS_DANCE", "MOVE_GLARE"],
    "TYPE_FAIRY": ["MOVE_CALM_MIND", "MOVE_MOONLIGHT"],
}
# Según sus estadísticas: el que pega físico se cheta el ataque, el especial el ataque especial
# y el que aguanta envenena y se cura
FISICO = ["MOVE_SWORDS_DANCE", "MOVE_BULK_UP", "MOVE_DRAGON_DANCE"]
ESPECIAL = ["MOVE_NASTY_PLOT", "MOVE_CALM_MIND"]
AGUANTE = ["MOVE_TOXIC", "MOVE_RECOVER"]
# Cuánto más vale un ataque de su tipo al elegir los mejores de su tabla
VALOR_SU_TIPO = 1.5


def bst(especie):
    return sum(especie.stats.values())


def _papel(especie):
    st = especie.stats
    if st.get("HP", 0) + st.get("Defense", 0) + st.get("SpDefense", 0) >= 270:
        return AGUANTE
    return ESPECIAL if st.get("SpAttack", 0) > st.get("Attack", 0) else FISICO


def elegir(especie, nivel, pokedex, movimientos, todos, rng, n_estrategia=2, primero=False):
    """Los 4 movimientos de un Pokémon de un líder: estrategia (trampas si va primero) y ataques
    de los que aprende por nivel."""
    datos = pokedex.especies[especie]
    tipos = list(datos.tipos)
    estrategia = []
    if primero:
        trampa = next((TRAMPA_POR_TIPO[t] for t in tipos if t in TRAMPA_POR_TIPO), "MOVE_STEALTH_ROCK")
        estrategia.append(trampa)
    opciones = []
    for t in tipos:
        opciones += [m for m in ESTRATEGIA_POR_TIPO.get(t, []) if m not in opciones]
    rng.shuffle(opciones)
    papel = [m for m in _papel(datos) if m not in opciones]
    rng.shuffle(papel)
    for m in opciones + papel:
        if len(estrategia) >= n_estrategia:
            break
        # Las trampas solo las pone el primero (con una por equipo basta)
        if m in movimientos and m not in estrategia and m not in TRAMPAS:
            estrategia.append(m)
    estrategia = [m for m in estrategia if m in movimientos][:max(n_estrategia, 1)]

    # Ataques: los mejores de los que aprende hasta su nivel, sin repetir tipo si se puede
    def valor(m):
        d = movimientos[m]
        return mov.potencia(d) * (VALOR_SU_TIPO if d.tipo in tipos else 1.0)

    aprendidos = sorted({m for nv, m in datos.por_nivel if nv <= nivel and m in movimientos
                         and movimientos[m].de_dano and m not in estrategia}, key=lambda m: (-valor(m), m))
    ataques = []
    tipos_usados = set()
    for m in aprendidos:
        if len(ataques) + len(estrategia) >= 4:
            break
        if movimientos[m].tipo in tipos_usados:
            continue
        ataques.append(m)
        tipos_usados.add(movimientos[m].tipo)
    for m in aprendidos:  # si faltan, aunque repita tipo
        if len(ataques) + len(estrategia) >= 4:
            break
        if m not in ataques:
            ataques.append(m)
    # Si no aprende suficientes ataques hasta su nivel, se completa al azar (mejor de su tipo)
    while len(ataques) + len(estrategia) < 4:
        danos = [t for t in todos if movimientos[t].de_dano and t not in ataques and t not in estrategia]
        if not danos:
            break
        suyos = [t for t in danos if movimientos[t].tipo in tipos]
        ataques.append(rng.choice(suyos if suyos and rng.random() < 0.6 else danos))
    return ataques[:2] + estrategia + ataques[2:]


def fuerza_salvajes(datos, pokedex, tramo_de_mapa, percentil):
    """{tramo: tope de estadísticas base} con los salvajes de hierba de los tramos hasta ese."""
    por_tramo = {}
    for grupo in datos["wild_encounter_groups"]:
        if grupo.get("label") != "gWildMonHeaders":
            continue
        for encuentro in grupo["encounters"]:
            tramo = tramo_de_mapa(encuentro["map"])
            if not tramo:
                continue
            for mon in encuentro.get("land_mons", {}).get("mons", []):
                if mon["species"] in pokedex.especies:
                    por_tramo.setdefault(tramo, []).append(bst(pokedex.especies[mon["species"]]))
    topes = {}
    acumulado = []
    for tramo in range(1, 11):
        acumulado += por_tramo.get(tramo, [])
        if acumulado:
            valores = sorted(acumulado)
            topes[tramo] = valores[min(len(valores) - 1, int(percentil * (len(valores) - 1) + 0.5))]
    return topes


def tramo_limitado(trainer, limites):
    """El tramo de "limite_salvajes" que le toca a este entrenador (admite comodines), o None."""
    for patron, tramo in limites.items():
        if fnmatch.fnmatchcase(trainer, patron):
            return tramo
    return None


def generar_rng(semilla, trainer, i):
    return random.Random(f"{semilla}|estrategia|{trainer}|{i}")
