"""
Dualocke: jefes con estrategia y con la fuerza de los salvajes al principio
(randomizer_config.json, "lideres"; pedido por Miguel y Jorge el 31/10/2026: "que los líderes
sean difíciles, que tengan una estrategia", pero sin sacar Pokémon mucho más fuertes que los
que encuentras).

- Estilos (Miguel, 15/11/2026: "que cada jefe se sienta diferente sin perder la sensación del
  randomlocke; no todos tienen que llevar trampas"). Cada jefe juega con uno de ESTILOS:
  trampas, espacio raro, chetarse, clima, estados, pantallas, aguante o velocidad.
  - Se reparten al azar con la semilla, sin repetir dentro de cada grupo: los 8 líderes llevan
    los 8 estilos, y el Alto Mando con Plubio y los jefes de mitad de tramo (rival, BLASCO,
    MAGNO, AQUILES y los admins), estilos distintos entre sí.
  - Un personaje lleva el mismo estilo en todos sus combates (MAGNO en el Monte Cenizo, en su
    guarida y en el Centro Espacial).
- Papeles dentro del equipo (Jorge, #128; mejorados por Miguel el 26/11/2026, papeles()): uno pone
  la estrategia (el que mejor encaja; va el primero del equipo), uno o dos la aprovechan y pegan
  fuerte, uno hace de tanque y el resto va libre, sin estrategia, como en un randomlocke. Cada
  movimiento de estrategia sale una vez por equipo (LIMITE_EQUIPO) y los ataques no se repiten.
- Movimientos de cada Pokémon: hasta 2 de estrategia de su estilo y su papel, y el resto "al azar":
  los mejores ataques de los que aprende por nivel (las tablas al azar de aprendizajes.py) y uno al
  azar entre todos. Ninguno pasa del tope de potencia (lideres.potencia_maxima), contando los golpes.
  - Hasta el gimnasio 3 (los que tienen tope de fuerza), 1 de estrategia, los 2 mejores ataques
    de su nivel y 1 al azar.
  - Nunca coge ataques que le perjudican (NO_CONVIENEN): los que lo debilitan o le quitan media
    vida (Autodestrucción, Explosión, Explosión Bruma, Sacrificio...) ni los que obligan a
    recargar (Hiperrayo, Giga Impacto...). Lo vio Jorge al probar el #54.
  - Siempre lleva al menos un ataque.
- Fuerza de los salvajes (los marcados en "limite_salvajes", hasta el gimnasio 3): sus Pokémon no
  pueden tener más estadísticas base (suma) que el percentil "percentil_salvajes" de los salvajes
  de hierba de los tramos hasta ese gimnasio, con la semilla de la partida, y nunca más que el
  "techo_por_tramo". El techo hace falta porque en los primeros tramos hay pocas rutas, y un solo
  salvaje fuerte que no evoluciona (Dondozo, Iron Treads) subía el percentil a 570 (Jorge, #54).
  Si los salvajes aún no han evolucionado, el líder tampoco.
"""

import fnmatch
import random
import re

from . import movimientos as mov

ESTILOS = ["trampas", "espacio_raro", "chetarse", "clima", "estados", "pantallas", "aguante", "velocidad"]
NOMBRE_ESTILO = {
    "trampas": "Trampas y arrastre", "espacio_raro": "Espacio Raro", "chetarse": "Chetarse",
    "clima": "Clima", "estados": "Estados", "pantallas": "Pantallas", "aguante": "Aguante",
    "velocidad": "Velocidad",
}
# Grupos de jefes: dentro de cada uno no se repite estilo
GRUPOS = [
    ["ROXANNE", "BRAWLY", "WATTSON", "FLANNERY", "NORMAN", "WINONA", "TATE_AND_LIZA", "JUAN"],
    ["SIDNEY", "PHOEBE", "GLACIA", "DRAKE", "WALLACE"],
    ["RIVAL", "MAXIE", "TABITHA", "SHELLY", "MATT", "ARCHIE", "WALLY"],
]

TRAMPAS = ["MOVE_STEALTH_ROCK", "MOVE_SPIKES", "MOVE_TOXIC_SPIKES", "MOVE_STICKY_WEB"]
TRAMPA_POR_TIPO = {
    "TYPE_ROCK": "MOVE_STEALTH_ROCK", "TYPE_GROUND": "MOVE_SPIKES", "TYPE_STEEL": "MOVE_STEALTH_ROCK",
    "TYPE_POISON": "MOVE_TOXIC_SPIKES", "TYPE_BUG": "MOVE_STICKY_WEB",
}
ARRASTRE = ["MOVE_ROAR", "MOVE_WHIRLWIND"]
CLIMAS = ["MOVE_RAIN_DANCE", "MOVE_SUNNY_DAY", "MOVE_SANDSTORM", "MOVE_SNOWSCAPE"]
CLIMA_POR_TIPO = {
    "TYPE_WATER": "MOVE_RAIN_DANCE", "TYPE_ELECTRIC": "MOVE_RAIN_DANCE",
    "TYPE_FIRE": "MOVE_SUNNY_DAY", "TYPE_GRASS": "MOVE_SUNNY_DAY",
    "TYPE_ROCK": "MOVE_SANDSTORM", "TYPE_GROUND": "MOVE_SANDSTORM", "TYPE_STEEL": "MOVE_SANDSTORM",
    "TYPE_ICE": "MOVE_SNOWSCAPE",
}
ESTADOS = ["MOVE_TOXIC", "MOVE_WILL_O_WISP", "MOVE_THUNDER_WAVE", "MOVE_CONFUSE_RAY", "MOVE_LEECH_SEED",
           "MOVE_YAWN", "MOVE_GLARE"]
DESGASTE = ["MOVE_TOXIC", "MOVE_LEECH_SEED", "MOVE_WILL_O_WISP"]
CURAS = ["MOVE_RECOVER", "MOVE_ROOST", "MOVE_PROTECT"]
FRENOS = ["MOVE_THUNDER_WAVE", "MOVE_ICY_WIND", "MOVE_ELECTROWEB", "MOVE_SCARY_FACE"]
# Para chetarse: el que pega físico se sube el ataque y el especial, el ataque especial
FISICO = ["MOVE_SWORDS_DANCE", "MOVE_BULK_UP", "MOVE_DRAGON_DANCE"]
ESPECIAL = ["MOVE_NASTY_PLOT", "MOVE_CALM_MIND", "MOVE_QUIVER_DANCE"]
VELOCIDAD_LENTO = 60  # con esta velocidad base o menos, le conviene el Espacio Raro
# Ataques que no le convienen a un jefe: lo debilitan, le quitan media vida o obligan a recargar
NO_CONVIENEN = {
    "MOVE_SELF_DESTRUCT", "MOVE_EXPLOSION", "MOVE_MISTY_EXPLOSION", "MOVE_FINAL_GAMBIT",
    "MOVE_MIND_BLOWN", "MOVE_STEEL_BEAM", "MOVE_CHLOROBLAST",
    "MOVE_HYPER_BEAM", "MOVE_GIGA_IMPACT", "MOVE_BLAST_BURN", "MOVE_HYDRO_CANNON", "MOVE_FRENZY_PLANT",
    "MOVE_ROCK_WRECKER", "MOVE_ROAR_OF_TIME", "MOVE_PRISMATIC_LASER", "MOVE_METEOR_ASSAULT",
    "MOVE_ETERNABEAM",
}
# Cuánto más vale un ataque de su tipo al elegir los mejores de su tabla
VALOR_SU_TIPO = 1.5


def bst(especie):
    return sum(especie.stats.values())


def personaje(trainer):
    """El personaje de un entrenador: el mismo en todos sus combates y revanchas."""
    if re.match(r"TRAINER_(MAY|BRENDAN)_", trainer):
        return "RIVAL"
    nombre = re.sub(r"_\d+$", "", trainer[len("TRAINER_"):])
    for clave in ("MAXIE", "TABITHA", "SHELLY", "WALLY"):
        if nombre.startswith(clave + "_"):
            return clave
    return nombre


def estilo_de(semilla, trainer):
    """El estilo del jefe: repartido al azar con la semilla, sin repetir dentro de su grupo."""
    quien = personaje(trainer)
    for n, grupo in enumerate(GRUPOS):
        if quien in grupo:
            estilos = ESTILOS[:]
            random.Random(f"{semilla}|estilos|{n}").shuffle(estilos)
            return estilos[grupo.index(quien) % len(estilos)]
    return random.Random(f"{semilla}|estilo|{quien}").choice(ESTILOS)


def plan_de(semilla, trainer, tipos_jefe=(), n_estrategia=2):
    """Lo que comparte todo el equipo de un jefe: su estilo, cuántos movimientos de estrategia
    lleva cada Pokémon y, si juega con el clima, cuál (el de su tipo, o uno al azar)."""
    clima = next((CLIMA_POR_TIPO[t] for t in tipos_jefe if t in CLIMA_POR_TIPO), None)
    if clima is None:
        clima = random.Random(f"{semilla}|clima|{personaje(trainer)}").choice(CLIMAS)
    return {"estilo": estilo_de(semilla, trainer), "n": n_estrategia, "clima": clima}


def _refuerzos(datos, rng):
    st = datos.stats
    lista = (FISICO if st.get("Attack", 0) >= st.get("SpAttack", 0) else ESPECIAL)[:]
    rng.shuffle(lista)
    return lista


# --- Papeles dentro del equipo ---
# Jorge, 24/11/2026 (#128): "es que le mete a la fuerza esos 2 movimientos a todos". Con el estilo Clima,
# CANDELA y MAGNO llevaban Día Soleado y Meteorobola en los seis.
# Miguel, 26/11/2026: ALANA le puso Nevada, Viento Hielo y Velo Aurora a todo el equipo, también a un
# atacante físico y rápido. Quiere varios papeles: "uno que ponga el clima, o lo que use esa estrategia,
# otro que sea el que golpea fuerte y aproveche esos cambios, otro que sea más tanky", y otros al azar
# "que le den la gracia de que sea un randomlocke". Y que no se repitan los movimientos.
#  - "pone": el que pone la estrategia. Es el que mejor encaja (aguante para las pantallas y Velo Aurora,
#    lento para Espacio Raro…), nunca el as, y entrenadores.py lo pone el primero del equipo.
#  - "aprovecha": 1 o 2, los que pegan fuerte y le sacan partido (del tipo del clima, lentos con Espacio
#    Raro, rápidos con Viento Afín…). Sus ataques van según peguen físico o especial.
#  - "tanque": 1, el más duro: cura y apoyo (y otra vez la estrategia, por si cae el que la pone).
#  - "libre": el resto, sin movimientos de estrategia: sus ataques y uno al azar, como cualquier
#    entrenador del randomlocke.
# Cada movimiento de estrategia sale como mucho una vez en el equipo (los de LIMITE_EQUIPO, dos), y los
# ataques de su tabla que ya lleva un compañero van al final de la lista.
PAPELES_POR_TAMANO = {
    1: ["pone"],
    2: ["pone", "aprovecha"],
    3: ["pone", "aprovecha", "libre"],
    4: ["pone", "aprovecha", "tanque", "libre"],
    5: ["pone", "aprovecha", "tanque", "libre", None],        # None: "aprovecha" o "libre", al azar
    6: ["pone", "aprovecha", "aprovecha", "tanque", "libre", "libre"],
}
# Cuánto cuenta el azar al elegir quién hace cada papel: la nota de cada uno se multiplica por un número
# entre 1 - AZAR_PAPELES y 1 + AZAR_PAPELES. Así no sale siempre el mismo reparto, pero tiene sentido.
AZAR_PAPELES = 0.15
VELOCIDAD_RAPIDO = 90  # con esta velocidad base o más, es rápido (Viento Afín, chetarse)

CLIMA_TIPOS = {}
for _t, _c in CLIMA_POR_TIPO.items():
    CLIMA_TIPOS.setdefault(_c, set()).add(_t)
# Ataques que pegan más con cada clima, del más fuerte al más flojo (se coge el primero que cabe en el
# tope). Por clima y por categoría. Con sol, Rayo Solar y Cuchilla Solar no cargan; con lluvia, Trueno no
# falla; con nieve, Ventisca no falla; con arena, la Roca sube su Defensa Especial.
ATAQUES_CLIMA = {
    "MOVE_SUNNY_DAY": {
        "especial": ["MOVE_FIRE_BLAST", "MOVE_SOLAR_BEAM", "MOVE_HEAT_WAVE", "MOVE_FLAMETHROWER",
                     "MOVE_MYSTICAL_FIRE", "MOVE_FLAME_BURST", "MOVE_EMBER"],
        "fisico": ["MOVE_FLARE_BLITZ", "MOVE_SOLAR_BLADE", "MOVE_FIRE_LASH", "MOVE_FIRE_PUNCH",
                   "MOVE_FIRE_FANG", "MOVE_FLAME_CHARGE"],
    },
    "MOVE_RAIN_DANCE": {
        "especial": ["MOVE_THUNDER", "MOVE_HYDRO_PUMP", "MOVE_SURF", "MOVE_SCALD", "MOVE_BUBBLE_BEAM",
                     "MOVE_WATER_PULSE", "MOVE_WATER_GUN"],
        "fisico": ["MOVE_WAVE_CRASH", "MOVE_LIQUIDATION", "MOVE_WATERFALL", "MOVE_AQUA_TAIL",
                   "MOVE_RAZOR_SHELL", "MOVE_AQUA_JET"],
    },
    "MOVE_SANDSTORM": {
        "especial": ["MOVE_EARTH_POWER", "MOVE_POWER_GEM", "MOVE_ANCIENT_POWER", "MOVE_MUD_SHOT"],
        "fisico": ["MOVE_STONE_EDGE", "MOVE_EARTHQUAKE", "MOVE_DRILL_RUN", "MOVE_ROCK_SLIDE",
                   "MOVE_ROCK_TOMB", "MOVE_BULLDOZE"],
    },
    "MOVE_SNOWSCAPE": {
        "especial": ["MOVE_BLIZZARD", "MOVE_ICE_BEAM", "MOVE_FREEZE_DRY", "MOVE_ICY_WIND"],
        "fisico": ["MOVE_ICICLE_CRASH", "MOVE_ICE_SPINNER", "MOVE_ICE_PUNCH", "MOVE_ICE_FANG",
                   "MOVE_ICE_SHARD"],
    },
}
# Curas que van mejor con cada clima
CURA_CLIMA = {"MOVE_SUNNY_DAY": ["MOVE_MORNING_SUN", "MOVE_SYNTHESIS"], "MOVE_SANDSTORM": ["MOVE_SHORE_UP"]}
DEFENSIVOS = ["MOVE_CALM_MIND", "MOVE_BULK_UP", "MOVE_IRON_DEFENSE", "MOVE_COSMIC_POWER"]
# Movimientos que pueden salir dos veces en el equipo (el que pone y el tanque, por si cae el primero)
LIMITE_EQUIPO = {"MOVE_WEATHER_BALL": 2, "MOVE_TRICK_ROOM": 2, "MOVE_TAILWIND": 2, "MOVE_PROTECT": 2,
                 **{c: 2 for c in CLIMAS}}


def _ataque(datos):
    return max(datos.stats.get("Attack", 0), datos.stats.get("SpAttack", 0))


def _fisico(datos):
    return datos.stats.get("Attack", 0) >= datos.stats.get("SpAttack", 0)


def _aguante(datos):
    st = datos.stats
    return st.get("HP", 0) + st.get("Defense", 0) + st.get("SpDefense", 0)


def _nota(papel, datos, plan):
    """Cuánto encaja un Pokémon en un papel con el estilo del plan (más es mejor)."""
    st, estilo = datos.stats, plan["estilo"]
    vel, ata, agu = st.get("Speed", 0), _ataque(datos), _aguante(datos)
    del_clima = len(set(datos.tipos) & CLIMA_TIPOS.get(plan["clima"], set())) if estilo == "clima" else 0
    if papel == "pone":
        # El que aguanta y pega menos: los que pegan fuerte quedan para aprovecharla
        if estilo == "espacio_raro":
            return agu - 2 * vel - ata // 2
        if estilo == "trampas":
            return agu + (60 if any(t in TRAMPA_POR_TIPO for t in datos.tipos) else 0) - ata // 2
        if estilo == "clima":
            return agu + 40 * del_clima - ata // 2
        if estilo == "velocidad":
            return agu + vel - ata // 2
        if estilo == "chetarse":
            return ata + vel
        return agu - ata // 2  # pantallas, estados, aguante
    if papel == "aprovecha":
        if estilo == "espacio_raro":
            return 2 * ata - 2 * vel
        if estilo == "clima":
            return 2 * ata + 120 * del_clima
        if estilo in ("velocidad", "chetarse", "pantallas"):
            return 2 * ata + vel
        if estilo == "aguante":
            return ata + agu
        return 2 * ata  # trampas y estados: el que más pega
    return agu  # tanque


def papeles(plan, especies, pokedex, rng):
    """El papel de cada Pokémon del equipo (en orden): "pone", "aprovecha", "tanque" o "libre".
    El último es el as: nunca pone la estrategia ni hace de tanque."""
    if not especies:
        return []
    plantilla = list(PAPELES_POR_TAMANO.get(len(especies), PAPELES_POR_TAMANO[6] + ["libre"] * len(especies)))
    plantilla = [p or rng.choice(["aprovecha", "libre"]) for p in plantilla][:len(especies)]
    papel = [None] * len(especies)
    azar = [1 + rng.uniform(-AZAR_PAPELES, AZAR_PAPELES) for _ in especies]
    datos = [pokedex.especies[e] for e in especies]
    ultimo = len(especies) - 1
    for p in ("pone", "aprovecha", "tanque"):
        for _ in range(plantilla.count(p)):
            libres = [i for i in range(len(especies)) if papel[i] is None
                      and not (p in ("pone", "tanque") and i == ultimo and len(especies) > 1)]
            if not libres:
                break
            mejor = max(libres, key=lambda i: (_nota(p, datos[i], plan) * azar[i], -i))
            papel[mejor] = p
    return [p or "libre" for p in papel]


def potencia_real(d):
    """Potencia de un ataque contando todos sus golpes (Dracoflechas, 2 × 50; Semilladora, unos 3 × 25;
    Triple Axel, 20 + 40 + 60)."""
    return mov.potencia(d) * getattr(d, "golpes", 1)


def _ataque_clima(datos, plan, movimientos, maxima, rng):
    """Los ataques que pegan más con el clima, de su categoría y que caben en el tope, del más fuerte al
    más flojo: primero los de sus tipos. elegir() coge el primero que no lleve ya el equipo."""
    lista = ATAQUES_CLIMA[plan["clima"]]["fisico" if _fisico(datos) else "especial"]
    cabe = [m for m in lista if m in movimientos and potencia_real(movimientos[m]) <= maxima]
    return [m for m in cabe if movimientos[m].tipo in datos.tipos] +         [m for m in cabe if movimientos[m].tipo not in datos.tipos]


def _de_estrategia(datos, plan, papel, rng, movimientos=None, maxima=999):
    """Los movimientos de estrategia que le tocan a este Pokémon según su papel: una lista de huecos, cada
    uno con un fin distinto (poner el clima, un ataque que lo aproveche, una mejora…) y sus alternativas por
    orden de preferencia. elegir() coge, de los primeros plan["n"] huecos, la primera alternativa que cabe en
    el tope y que no lleva ya el equipo. Así no salen dos mejoras ni dos curas en el mismo Pokémon."""
    if papel in ("libre", "normal"):
        return []
    movimientos = movimientos or {}
    estilo = plan["estilo"]
    tipos = list(datos.tipos)
    fisico = _fisico(datos)
    lento = datos.stats.get("Speed", 0) <= VELOCIDAD_LENTO
    rapido = datos.stats.get("Speed", 0) >= VELOCIDAD_RAPIDO
    refuerzos = _refuerzos(datos, rng)
    curas = CURAS[:]
    rng.shuffle(curas)
    frenos = FRENOS[:]
    rng.shuffle(frenos)
    if papel == "lanzador":
        papel = "pone"  # el nombre de antes (#128)
    if estilo == "trampas":
        trampa = next((TRAMPA_POR_TIPO[t] for t in tipos if t in TRAMPA_POR_TIPO), rng.choice(TRAMPAS))
        otras = [t for t in TRAMPAS if t != trampa]
        rng.shuffle(otras)
        if papel == "pone":
            return [[trampa] + otras, ARRASTRE[:]]
        if papel == "aprovecha":
            return [refuerzos, ["MOVE_PROTECT", "MOVE_SUBSTITUTE"]]
        return [otras + [trampa], ARRASTRE + curas]  # tanque: otra trampa, y arrastre o cura
    if estilo == "espacio_raro":
        if papel == "pone":
            return [["MOVE_TRICK_ROOM"], curas]
        if papel == "aprovecha":
            return [(["MOVE_CURSE"] if lento and fisico else []) + refuerzos, ["MOVE_PROTECT"]]
        return [curas, ["MOVE_TRICK_ROOM"]]
    if estilo == "chetarse":
        if papel == "pone":
            return [refuerzos, ["MOVE_SUBSTITUTE", "MOVE_PROTECT"]]
        if papel == "aprovecha":
            return [refuerzos, ["MOVE_AGILITY"] if not rapido else ["MOVE_SUBSTITUTE", "MOVE_PROTECT"]]
        defensivos = DEFENSIVOS[:]
        rng.shuffle(defensivos)
        return [defensivos, curas]
    if estilo == "clima":
        clima = plan["clima"]
        ataque = _ataque_clima(datos, plan, movimientos, maxima, rng)
        if papel == "pone":
            # La IA solo pone el clima si le sirve al que está en el campo (BenefitsFromSun y compañía,
            # src/battle_ai_field_statuses.c): con Meteorobola, Velo Aurora o un ataque del tipo del clima
            if clima == "MOVE_SNOWSCAPE":
                return [[clima], ["MOVE_AURORA_VEIL", "MOVE_BLIZZARD", "MOVE_WEATHER_BALL"]]
            if fisico and clima != "MOVE_SANDSTORM":
                return [[clima], ataque + ["MOVE_WEATHER_BALL"]]
            return [[clima], ["MOVE_WEATHER_BALL"] + ataque]
        if papel == "aprovecha":
            # Un ataque del clima y, el especial, Meteorobola; el físico, una mejora. Si no hay ataque del
            # clima que quepa, ese hueco se queda para sus ataques (nunca dos mejoras)
            if fisico:
                return [ataque, refuerzos]
            return [ataque, ["MOVE_WEATHER_BALL"], refuerzos]
        cura = CURA_CLIMA.get(clima, []) + curas
        apoyo = [clima] + (["MOVE_ICY_WIND"] if clima == "MOVE_SNOWSCAPE" else []) + frenos
        return [cura, apoyo]
    if estilo == "estados":
        estados = ESTADOS[:]
        rng.shuffle(estados)
        if papel == "pone":
            return [estados, estados]
        if papel == "aprovecha":
            if fisico:
                return [refuerzos, estados]
            return [["MOVE_HEX"] + refuerzos, estados]
        return [["MOVE_LEECH_SEED", "MOVE_TOXIC"] + estados, curas]
    if estilo == "pantallas":
        if papel == "pone":
            return [["MOVE_REFLECT"], ["MOVE_LIGHT_SCREEN"]]
        if papel == "aprovecha":
            return [refuerzos, ["MOVE_SUBSTITUTE", "MOVE_PROTECT"]]
        return [curas, frenos]
    if estilo == "aguante":
        desgaste = DESGASTE[:]
        rng.shuffle(desgaste)
        if papel == "pone":
            return [desgaste, curas]
        if papel == "aprovecha":
            return [refuerzos, curas]
        return [curas, desgaste]
    if estilo == "velocidad":
        if papel == "pone":
            return [["MOVE_TAILWIND"], frenos]
        if papel == "aprovecha":
            return [refuerzos, ["MOVE_AGILITY"] if not rapido else ["MOVE_PROTECT"]]
        return [frenos, curas]
    raise ValueError(f"Dualocke: estilo desconocido '{estilo}'")


# Movimientos que no salen al azar en los jefes con estrategia (además de NO_CONVIENEN y las trampas):
# Velo Aurora sin nieve falla (Miguel, 26/11/2026: atacantes físicos con Velo Aurora)
NO_AL_AZAR = {"MOVE_AURORA_VEIL"}
# Mejoras: si ya lleva una, el movimiento al azar no le da otra
MEJORAS = set(FISICO + ESPECIAL + DEFENSIVOS + ["MOVE_CURSE"])


def elegir(especie, nivel, pokedex, movimientos, todos, rng, plan, papel="libre", tope=None):
    """Los 4 movimientos de un Pokémon de un jefe: los de estrategia de su estilo y su papel
    (papeles()), los mejores ataques de los que aprende por nivel y uno al azar.
    `tope`: (base, por nivel) de la potencia máxima de sus ataques (lideres.potencia_maxima), contando
    todos los golpes. `plan["usados"]` lleva la cuenta de lo que ya lleva el equipo (para no repetir)."""
    datos = pokedex.especies[especie]
    tipos = list(datos.tipos)
    maxima = tope[0] + tope[1] * nivel if tope else 999
    usados = plan.setdefault("usados", {})

    def cabe(m):
        d = movimientos[m]
        return not d.de_dano or potencia_real(d) <= maxima

    estrategia = []
    for hueco in _de_estrategia(datos, plan, papel, rng, movimientos, maxima):
        if len(estrategia) >= plan["n"]:
            break
        m = next((m for m in hueco if m in movimientos and m not in estrategia and cabe(m)
                  and usados.get(m, 0) < LIMITE_EQUIPO.get(m, 1)), None)
        if m:
            estrategia.append(m)

    def valor(m):
        d = movimientos[m]
        return mov.potencia(d) * (VALOR_SU_TIPO if d.tipo in tipos else 1.0)

    # Los mejores ataques de los que aprende hasta su nivel, de tipos distintos si se puede. Los que ya
    # lleva un compañero, solo si no queda otra (Miguel, 26/11/2026: "repiten muchos movimientos")
    todos_aprendidos = sorted({m for nv, m in datos.por_nivel if nv <= nivel and m in movimientos
                               and movimientos[m].de_dano and m not in estrategia and m not in NO_CONVIENEN
                               and cabe(m)},
                              key=lambda m: (-valor(m), m))
    aprendidos = [m for m in todos_aprendidos if not usados.get(m)]
    de_nivel = 4 - len(estrategia) - 1  # el último hueco es para el movimiento al azar
    ataques = []
    for m in aprendidos:
        if len(ataques) >= de_nivel:
            break
        if not any(movimientos[a].tipo == movimientos[m].tipo for a in ataques):
            ataques.append(m)
    for m in aprendidos:  # si faltan, aunque repita tipo
        if len(ataques) >= de_nivel:
            break
        if m not in ataques:
            ataques.append(m)

    # El resto, al azar entre todos (como el cuarto de cualquier entrenador), sin lo que ya lleva el equipo
    # ni lo que no cabe. Si todavía no lleva ningún ataque, el primero al azar es de daño
    libres = [t for t in todos if t not in NO_CONVIENEN and t not in TRAMPAS and t not in NO_AL_AZAR
              and cabe(t) and not usados.get(t)]
    # Con tope, si lo que aprende por nivel no llega (todo pasaba del tope), los ataques que faltan
    # salen al azar entre los que caben, mejor de su tipo (el Wartortle de ERICO se quedaba con
    # Restricción)
    if tope:
        de_su_tipo = [t for t in libres if movimientos[t].de_dano and movimientos[t].tipo in tipos]
        de_dano = [t for t in libres if movimientos[t].de_dano]
        while len(ataques) < de_nivel:
            m = mov._sacar(de_su_tipo, ataques + estrategia, movimientos, rng) \
                or mov._sacar(de_dano, ataques + estrategia, movimientos, rng)
            if m is None:
                break
            ataques.append(m)
    for m in todos_aprendidos:  # y si aún faltan, los que ya lleva un compañero
        if len(ataques) >= de_nivel:
            break
        if m not in ataques:
            ataques.append(m)
    elegidos = ataques + estrategia
    while len(elegidos) < 4:
        sin_ataque = not any(movimientos[e].de_dano for e in elegidos)
        opciones = [t for t in libres if movimientos[t].de_dano] if sin_ataque else libres
        if any(e in MEJORAS for e in elegidos):
            opciones = [t for t in opciones if t not in MEJORAS]
        m = mov._sacar(opciones, elegidos, movimientos, rng)
        if m is None:
            break
        elegidos.append(m)
    for m in elegidos:
        usados[m] = usados.get(m, 0) + 1
    return elegidos


def fuerza_salvajes(datos, pokedex, tramo_de_mapa, percentil, techos=None):
    """{tramo: tope de estadísticas base} con los salvajes de hierba de los tramos hasta ese, sin
    pasar del techo de ese tramo ({tramo: techo})."""
    techos = techos or {}
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
            if tramo in techos:
                topes[tramo] = min(topes[tramo], techos[tramo])
    return topes


def coincide(trainer, patrones):
    """Si el entrenador está en la lista (admite comodines: TRAINER_MAXIE_*)."""
    return any(fnmatch.fnmatchcase(trainer, p) for p in patrones)


def tramo_limitado(trainer, limites):
    """El tramo de "limite_salvajes" que le toca a este entrenador (admite comodines), o None."""
    for patron, tramo in limites.items():
        if fnmatch.fnmatchcase(trainer, patron):
            return tramo
    return None


def generar_rng(semilla, trainer, i):
    return random.Random(f"{semilla}|estrategia|{trainer}|{i}")
