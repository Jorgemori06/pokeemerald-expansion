#!/usr/bin/env python3
"""
Dualocke: prueba de los papeles de los equipos de los jefes con estrategia (aleatorio/estrategia.py),
sin compilador ni preprocesador (Miguel, 26/11/2026).

Lee a mano las especies (tipos y estadísticas) y los movimientos reales, inventa aprendizajes al azar
(como las tablas de aprendizajes.py) y reparte papeles y movimientos a los equipos de 15 jefes de
trainers.party con los 8 estilos, 60 semillas y 1 o 2 movimientos de estrategia. Mira que:
- haya uno solo que pone la estrategia, y que no sea el as; que la lleve y, con Clima, algo para que
  la IA la use (BenefitsFromSun y compañía, src/battle_ai_field_statuses.c);
- todos lleven 4 movimientos distintos y algún ataque, sin pasar del tope (contando los golpes);
- no se repitan movimientos en el equipo, nadie lleve dos mejoras y Velo Aurora solo lo lleve el que
  pone la nieve; los físicos que aprovechan el clima no lleven ataques especiales de clima.

Uso (desde la raíz del repo; tarda unos minutos):
    python3 tools/dualocke/probar_papeles.py          # devuelve 1 si hay algún fallo
    python3 tools/dualocke/probar_papeles.py --ver    # además, enseña algunos equipos
"""
import collections
import glob
import random
import re
import sys

sys.path.insert(0, "tools/dualocke")
from aleatorio import estrategia as est, movimientos as mov  # noqa: E402

VER = "--ver" in sys.argv


def sin_config(texto):
    texto = re.sub(r"\bGEN_LATEST\b", "9", texto)
    texto = re.sub(r"\bGEN_(\d)\b", r"\1", texto)
    return re.sub(r"\b[BP]_\w+\b", "9", texto)


# --- movimientos ---
t = sin_config(open("src/data/moves_info.h", encoding="utf-8").read())
movs = {}
for m in re.finditer(r"\[(MOVE_\w+)\]\s*=\s*\{(.*?)\n    \},", t, re.S):
    campos = dict(re.findall(r"^\s*\.(\w+)\s*=\s*([^\n]+?),\s*$", m.group(2), re.M))
    movs[m.group(1)] = mov.Movimiento(m.group(1), campos, m.group(1))
todos = mov.validos(movs)  # como el randomizer
assert movs["MOVE_DRAGON_DARTS"].golpes == 2 and movs["MOVE_BULLET_SEED"].golpes == 3
assert movs["MOVE_TRIPLE_AXEL"].golpes == 6 and movs["MOVE_POPULATION_BOMB"].golpes == 10
assert movs["MOVE_TACKLE"].golpes == 1

# --- especies ---


class Especie:
    pass


especies = {}
for ruta in glob.glob("src/data/pokemon/species_info/gen_*_families.h"):
    t = sin_config(open(ruta, encoding="utf-8").read())
    for m in re.finditer(r"\[(SPECIES_\w+)\]\s*=\s*\{(.*?)\n    \},", t, re.S):
        c = m.group(2)
        st = {}
        for clave, nombre in (("baseHP", "HP"), ("baseAttack", "Attack"), ("baseDefense", "Defense"),
                              ("baseSpeed", "Speed"), ("baseSpAttack", "SpAttack"), ("baseSpDefense", "SpDefense")):
            v = re.search(r"\.%s\s*=\s*([^,\n]+)" % clave, c)
            st[nombre] = mov._valor(v.group(1)) if v else 0
        tip = re.search(r"\.types\s*=\s*MON_TYPES\(([^)]*)\)", c)
        if not tip or not st["HP"]:
            continue
        e = Especie()
        e.stats, e.tipos = st, list(dict.fromkeys(x.strip() for x in tip.group(1).split(",")))
        especies[m.group(1)] = e
dano = [c for c in todos if movs[c].de_dano]
for nombre, e in especies.items():  # aprendizajes al azar, como las tablas de aprendizajes.py
    r = random.Random(nombre)
    e.por_nivel = sorted((r.randint(1, 70), mv) for mv in r.sample(dano, 14) + r.sample(todos, 6))


class Pokedex:
    pass


pk = Pokedex()
pk.especies = especies

# --- equipos de los jefes ---
JEFES = ["ROXANNE_1", "BRAWLY_1", "WATTSON_1", "FLANNERY_1", "NORMAN_1", "WINONA_1", "TATE_AND_LIZA_1",
         "JUAN_1", "SIDNEY", "PHOEBE", "GLACIA", "DRAKE", "WALLACE", "MAXIE_MT_CHIMNEY", "ARCHIE"]
party = open("src/data/trainers.party", encoding="utf-8").read()
equipos = {}
for j in JEFES:
    bloque = re.search(r"^=== TRAINER_%s ===\n(.*?)(?=^=== )" % j, party, re.M | re.S).group(1)
    mons = []
    for trozo in re.split(r"\n\s*\n", bloque)[1:]:
        lineas = trozo.strip().split("\n")
        if not lineas[0].strip():
            continue
        nombre = re.match(r"^\s*([^@(]+?)\s*(?:\(|@|$)", lineas[0]).group(1)
        const = "SPECIES_" + re.sub(r"[^A-Z0-9]+", "_", nombre.upper()).strip("_")
        nivel = int(re.search(r"Level:\s*(\d+)", trozo).group(1))
        if const in especies:
            mons.append((const, nivel))
    equipos[j] = mons

ESPECIALES_CLIMA = {"MOVE_WEATHER_BALL", "MOVE_SOLAR_BEAM", "MOVE_THUNDER", "MOVE_BLIZZARD", "MOVE_FIRE_BLAST",
                    "MOVE_HYDRO_PUMP", "MOVE_ICE_BEAM", "MOVE_EARTH_POWER", "MOVE_HEAT_WAVE", "MOVE_FLAMETHROWER"}


def equipar(semilla, j, mons, plan, tope=(40, 1.5)):
    """Como entrenadores.py: papeles, movimientos por orden de papel y el que pone, el primero."""
    papel = est.papeles(plan, [m[0] for m in mons], pk, random.Random(f"{semilla}|papeles|{j}"))
    salida = {}
    orden = sorted(range(len(mons)), key=lambda k: ({"pone": 0, "aprovecha": 1, "tanque": 2}.get(papel[k], 3), k))
    for k in orden:
        e, nivel = mons[k]
        salida[k] = est.elegir(e, nivel, pk, movs, todos, est.generar_rng(semilla, j, k), plan, papel[k], tope=tope)
    return papel, [salida[k] for k in range(len(mons))]


fallos = collections.Counter()
ejemplos = {}
casos = 0
for semilla in range(60):
    for j, mons in equipos.items():
        for estilo in est.ESTILOS:
            for n in (1, 2):
                tipos_as = especies[mons[-1][0]].tipos
                plan = est.plan_de(semilla, "TRAINER_" + j, tipos_as, n)
                plan["estilo"] = estilo
                papel, movsq = equipar(semilla, j, mons, plan)
                casos += 1
                cuenta = collections.Counter(m for ms in movsq for m in ms)
                if len(mons) > 1 and papel[-1] in ("pone", "tanque"):
                    fallos["el as pone o es tanque"] += 1
                if papel.count("pone") != 1:
                    fallos["no hay uno solo que pone"] += 1
                for k, ((e, nivel), ms, p) in enumerate(zip(mons, movsq, papel)):
                    d = especies[e]
                    maxima = 40 + 1.5 * nivel
                    if len(ms) != 4 or len(set(ms)) != 4:
                        fallos["no lleva 4 distintos"] += 1
                    mejoras = set(ms) & set(est.FISICO + est.ESPECIAL)
                    if len(mejoras) > 1 and p != "libre":
                        fallos["dos mejoras en el mismo"] += 1
                        ejemplos.setdefault("dos mejoras", []).append((j, estilo, p, e, ms))
                    if not any(movs[m].de_dano for m in ms):
                        fallos["sin ataque"] += 1
                    if any(movs[m].de_dano and est.potencia_real(movs[m]) > maxima for m in ms):
                        fallos["pasa del tope"] += 1
                    kit = {x for h in est._de_estrategia(d, plan, p, random.Random(0), movs, maxima) for x in h}
                    if p == "aprovecha" and est._fisico(d) and kit & {"MOVE_WEATHER_BALL", "MOVE_BLIZZARD",
                                                                     "MOVE_SOLAR_BEAM", "MOVE_THUNDER"} \
                            and estilo == "clima":
                        fallos["físico que aprovecha con ataque especial de clima"] += 1
                    if "MOVE_AURORA_VEIL" in ms and p != "pone":
                        fallos["Velo Aurora fuera del que pone"] += 1
                    if p == "libre" and set(ms) & {plan["clima"] if estilo == "clima" else "", "MOVE_TRICK_ROOM",
                                                   "MOVE_TAILWIND", "MOVE_REFLECT", "MOVE_LIGHT_SCREEN"} - {""}:
                        pass  # un libre puede sacarlo al azar (el cuarto), pero no le toca
                    if p == "pone":
                        nucleo = {"clima": plan["clima"], "espacio_raro": "MOVE_TRICK_ROOM", "velocidad": "MOVE_TAILWIND",
                                  "pantallas": "MOVE_REFLECT"}.get(estilo)
                        if nucleo and nucleo not in ms:
                            fallos[f"el que pone no lleva {nucleo}"] += 1
                        if estilo == "clima" and n == 2:
                            sirve = (set(ms) & {"MOVE_WEATHER_BALL", "MOVE_AURORA_VEIL", "MOVE_BLIZZARD", "MOVE_THUNDER",
                                                "MOVE_SOLAR_BEAM", "MOVE_SOLAR_BLADE", "MOVE_MORNING_SUN", "MOVE_SYNTHESIS"}
                                     or set(d.tipos) & est.CLIMA_TIPOS[plan["clima"]] and plan["clima"] in ("MOVE_SANDSTORM", "MOVE_SNOWSCAPE")
                                     or any(movs[m].de_dano and movs[m].tipo == {"MOVE_SUNNY_DAY": "TYPE_FIRE", "MOVE_RAIN_DANCE": "TYPE_WATER"}.get(plan["clima"]) for m in ms))
                            if not sirve:
                                fallos["la IA no pondría el clima (no le sirve)"] += 1
                                ejemplos.setdefault("no sirve", []).append((semilla, j, plan["clima"], e, nivel, ms))
                limites = dict(est.LIMITE_EQUIPO)
                for m, c in cuenta.items():
                    if c > limites.get(m, 1):
                        fallos["movimiento repetido en el equipo"] += 1
                        ejemplos.setdefault("repetido", []).append((semilla, j, estilo, n, m, c))
                if semilla < 1 and n == 2 and VER and j in ("WINONA_1", "FLANNERY_1", "GLACIA") and estilo in ("clima", "espacio_raro", "pantallas"):
                    print(f"\n{j} {estilo} {plan['clima'] if estilo == 'clima' else ''}")
                    for (e, nivel), ms, p in zip(mons, movsq, papel):
                        d = especies[e]
                        print(f"  {p:9} {e[8:]:12} nv{nivel} {'/'.join(x[5:] for x in d.tipos):15} "
                              f"{'fís' if est._fisico(d) else 'esp'} vel{d.stats['Speed']:3} agu{est._aguante(d):3}: "
                              + ", ".join(x[5:] for x in ms))
print(f"\n{casos} equipos ({len(especies)} especies, {len(movs)} movimientos)")
print("fallos:", dict(fallos) or "ninguno")
if fallos:
    print(ejemplos)
    sys.exit(1)
