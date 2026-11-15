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
- Movimientos de cada Pokémon: 2 de estrategia de su estilo y 2 "al azar": el mejor ataque de
  los que aprende por nivel (las tablas al azar de aprendizajes.py) y uno al azar entre todos.
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


def _de_estrategia(datos, plan, primero, rng):
    """Los movimientos de estrategia que le tocan a este Pokémon, por orden de preferencia."""
    estilo = plan["estilo"]
    tipos = list(datos.tipos)
    lento = datos.stats.get("Speed", 0) <= VELOCIDAD_LENTO
    refuerzos = _refuerzos(datos, rng)
    if estilo == "trampas":
        if primero:
            trampa = next((TRAMPA_POR_TIPO[t] for t in tipos if t in TRAMPA_POR_TIPO), rng.choice(TRAMPAS))
            return [trampa, rng.choice(ARRASTRE)]
        return [rng.choice(ARRASTRE), rng.choice(["MOVE_PROTECT", "MOVE_TOXIC", "MOVE_TAUNT"])]
    if estilo == "espacio_raro":
        if lento and datos.stats.get("Attack", 0) >= datos.stats.get("SpAttack", 0):
            refuerzos = ["MOVE_CURSE"] + refuerzos
        if primero or lento:
            return ["MOVE_TRICK_ROOM", refuerzos[0]]
        return [refuerzos[0], "MOVE_TRICK_ROOM"]
    if estilo == "chetarse":
        return [refuerzos[0], rng.choice(["MOVE_SUBSTITUTE", "MOVE_PROTECT", "MOVE_AGILITY"])]
    if estilo == "clima":
        if primero:
            return [plan["clima"], "MOVE_AURORA_VEIL" if plan["clima"] == "MOVE_SNOWSCAPE" else "MOVE_PROTECT"]
        return ["MOVE_WEATHER_BALL", plan["clima"]]
    if estilo == "estados":
        return rng.sample(ESTADOS, 2)
    if estilo == "pantallas":
        if primero:
            return ["MOVE_REFLECT", "MOVE_LIGHT_SCREEN"]
        return [refuerzos[0], rng.choice(["MOVE_REFLECT", "MOVE_LIGHT_SCREEN"])]
    if estilo == "aguante":
        return [rng.choice(DESGASTE), rng.choice(CURAS)]
    if estilo == "velocidad":
        if primero:
            return ["MOVE_TAILWIND", rng.choice(FRENOS)]
        return [rng.choice(FRENOS), rng.choice(["MOVE_AGILITY", "MOVE_TAILWIND"])]
    raise ValueError(f"Dualocke: estilo desconocido '{estilo}'")


def elegir(especie, nivel, pokedex, movimientos, todos, rng, plan, primero=False):
    """Los 4 movimientos de un Pokémon de un jefe: los de estrategia de su estilo, el mejor
    ataque (o los dos mejores) de los que aprende por nivel y uno al azar."""
    datos = pokedex.especies[especie]
    tipos = list(datos.tipos)
    estrategia = []
    for m in _de_estrategia(datos, plan, primero, rng):
        if len(estrategia) < plan["n"] and m in movimientos and m not in estrategia:
            estrategia.append(m)

    def valor(m):
        d = movimientos[m]
        return mov.potencia(d) * (VALOR_SU_TIPO if d.tipo in tipos else 1.0)

    # Los mejores ataques de los que aprende hasta su nivel, de tipos distintos si se puede
    aprendidos = sorted({m for nv, m in datos.por_nivel if nv <= nivel and m in movimientos
                         and movimientos[m].de_dano and m not in estrategia and m not in NO_CONVIENEN},
                        key=lambda m: (-valor(m), m))
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

    # El resto, al azar entre todos (como el cuarto de cualquier entrenador). Si todavía no lleva
    # ningún ataque, el primero al azar es de daño
    libres = [t for t in todos if t not in NO_CONVIENEN and t not in TRAMPAS]
    elegidos = ataques + estrategia
    while len(elegidos) < 4:
        sin_ataque = not any(movimientos[e].de_dano for e in elegidos)
        opciones = [t for t in libres if movimientos[t].de_dano] if sin_ataque else libres
        m = mov._sacar(opciones, elegidos, movimientos, rng)
        if m is None:
            break
        elegidos.append(m)
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
