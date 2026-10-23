#!/usr/bin/env python3
"""
Dualocke: reescala los niveles de entrenadores y salvajes de Hoenn según la curva de caps.

Uso (desde la raíz del repo):
    python3 tools/dualocke/reescalar_niveles.py            # aplica los cambios
    python3 tools/dualocke/reescalar_niveles.py --resumen  # solo enseña el resumen por tramo

Los niveles originales se leen siempre del commit BASE (la expansion sin tocar), así que
el script se puede volver a lanzar tras cambiar la tabla y da siempre el mismo resultado.
Solo reescribe niveles: no toca especies, movimientos ni nada más, y deja intactos los
entrenadores y zonas que no estén asignados a un tramo (revanchas, postgame, Kanto…).

Reglas (decididas por Miguel, ver DUALOCKE.md, sección 5):
- Cada mapa pertenece a un tramo: el que hay entre una medalla y la siguiente.
- Entrenadores normales: del cap anterior - 3 al cap del tramo - 3, según lo fuerte
  que eran en el original dentro de su tramo.
- Líderes de gimnasio: el equipo entero al cap del tramo.
- Alto Mando, Plubio y Blasco en Calle Victoria: niveles fijos (JEFES_FIJOS).
- Jefes a mitad de tramo (rival, Magno, Aquiles, Blasco en Malvalona): el equipo entero
  3 niveles por encima de los entrenadores de ese punto, sin pasar del cap.
- Salvajes: 3 niveles por debajo de los entrenadores de su zona, con un margen de +-2.
"""

import fnmatch
import json
import os
import re
import subprocess
import sys

BASE = "30988a58b"  # rh-hideout/pokeemerald-expansion en el momento del fork

TRAINERS = "src/data/trainers.party"
WILD = "src/data/wild_encounters.json"

# Cap que se sube al ganar la medalla de cada tramo (src/caps.c)
CAPS = {1: 16, 2: 23, 3: 32, 4: 43, 5: 50, 6: 62, 7: 73, 8: 84, 9: 100}
INICIO_TRAMO_1 = 3   # nivel de los primeros entrenadores del juego
MARGEN_NORMALES = 3  # los entrenadores normales llegan hasta cap - 3
MARGEN_SALVAJES = 3  # salvajes = entrenadores de la zona - 3
SUBIDA_JEFES_MEDIO = 3  # jefes a mitad de tramo: +3 sobre los entrenadores de ese punto

# Mapas de cada tramo, en orden de historia (patrones sobre el id MAP_...)
TRAMOS = {
    1: ["ROUTE101", "ROUTE102", "ROUTE103", "ROUTE104", "PETALBURG_WOODS",
        "RUSTBORO_CITY", "RUSTBORO_CITY_GYM"],
    2: ["ROUTE116", "RUSTURF_TUNNEL", "DEWFORD_TOWN", "GRANITE_CAVE_*", "ROUTE106",
        "DEWFORD_TOWN_GYM"],
    3: ["ROUTE109", "ROUTE109_SEASHORE_HOUSE", "SLATEPORT_CITY",
        "SLATEPORT_CITY_OCEANIC_MUSEUM_*", "ROUTE110", "MAUVILLE_CITY", "ROUTE117",
        "MAUVILLE_CITY_GYM"],
    4: ["ROUTE111", "ROUTE112", "FIERY_PATH", "ROUTE113", "ROUTE114", "METEOR_FALLS_1F_1R",
        "ROUTE115", "MT_CHIMNEY", "JAGGED_PASS", "LAVARIDGE_TOWN_GYM_*"],
    5: ["PETALBURG_CITY_GYM"],
    6: ["PETALBURG_CITY", "ROUTE105", "ROUTE107", "ROUTE108", "ABANDONED_SHIP_*",
        "NEW_MAUVILLE_*", "MIRAGE_TOWER_*", "ROUTE118", "ROUTE123", "ROUTE119",
        "ROUTE119_WEATHER_INSTITUTE_*", "ROUTE120", "FORTREE_CITY_GYM"],
    7: ["ROUTE121", "SAFARI_ZONE_*", "LILYCOVE_CITY", "MT_PYRE_*", "ROUTE122",
        "MAGMA_HIDEOUT_*", "AQUA_HIDEOUT_*", "ROUTE124", "ROUTE125", "SHOAL_CAVE_*",
        "ROUTE126", "ROUTE127", "MOSSDEEP_CITY", "MOSSDEEP_CITY_GYM"],
    8: ["MOSSDEEP_CITY_SPACE_CENTER_*", "UNDERWATER_*", "ROUTE128", "SEAFLOOR_CAVERN_*",
        "SOOTOPOLIS_CITY", "CAVE_OF_ORIGIN_*", "SKY_PILLAR_*", "ROUTE129", "ROUTE130",
        "ROUTE131", "PACIFIDLOG_TOWN", "ROUTE132", "ROUTE133", "ROUTE134",
        "SOOTOPOLIS_CITY_GYM_*"],
    9: ["EVER_GRANDE_CITY", "VICTORY_ROAD_*", "METEOR_FALLS_1F_2R", "METEOR_FALLS_B1F_*",
        "EVER_GRANDE_CITY_*S_ROOM"],
}

LIDERES = {"TRAINER_ROXANNE_1", "TRAINER_BRAWLY_1", "TRAINER_WATTSON_1", "TRAINER_FLANNERY_1",
           "TRAINER_NORMAN_1", "TRAINER_WINONA_1", "TRAINER_TATE_AND_LIZA_1", "TRAINER_JUAN_1"}

# Liga: el as del Alto Mando entre 92 y 97 y Plubio a 100 (todo el equipo al mismo nivel)
JEFES_FIJOS = {"TRAINER_SIDNEY": 92, "TRAINER_PHOEBE": 94, "TRAINER_GLACIA": 95,
               "TRAINER_DRAKE": 97, "TRAINER_WALLACE": 100, "TRAINER_WALLY_VR_1": 90}

JEFES_MEDIO_TRAMO = ["TRAINER_MAY_*", "TRAINER_BRENDAN_*", "TRAINER_MAXIE_*", "TRAINER_ARCHIE",
                     "TRAINER_WALLY_MAUVILLE"]


def git_show(path):
    return subprocess.run(["git", "show", f"{BASE}:{path}"], capture_output=True, check=True,
                          encoding="utf-8").stdout


def tramo_de_mapa(map_id):
    nombre = map_id[len("MAP_"):]
    for tramo, patrones in TRAMOS.items():
        if any(fnmatch.fnmatchcase(nombre, p) for p in patrones):
            return tramo
    return None


def rango_tramo(tramo):
    inicio = INICIO_TRAMO_1 if tramo == 1 else CAPS[tramo - 1] - MARGEN_NORMALES
    return inicio, CAPS[tramo] - MARGEN_NORMALES


def percentil(valores, p):
    valores = sorted(valores)
    return valores[min(len(valores) - 1, int(p * (len(valores) - 1) + 0.5))]


def es_jefe_medio(nombre):
    return any(fnmatch.fnmatchcase(nombre, p) for p in JEFES_MEDIO_TRAMO) and not nombre.endswith("PLACEHOLDER")


def leer_entrenadores(texto):
    """Devuelve {TRAINER_X: [niveles]} en el orden de su equipo."""
    partes = re.split(r"^=== (TRAINER_\w+) ===[ \t]*$", texto, flags=re.M)
    return {partes[i]: [int(n) for n in re.findall(r"^Level:\s*(\d+)", partes[i + 1], re.M)]
            for i in range(1, len(partes), 2)}


def mapas_de_entrenadores():
    """Devuelve {TRAINER_X: MAP_...} según los scripts de cada mapa."""
    resultado = {}
    for carpeta in sorted(os.listdir("data/maps")):
        script = os.path.join("data/maps", carpeta, "scripts.inc")
        if not os.path.exists(script):
            continue
        with open(os.path.join("data/maps", carpeta, "map.json"), encoding="utf-8") as f:
            map_id = json.load(f)["id"]
        with open(script, encoding="utf-8") as f:
            # trainerbattle_* y multi_2_vs_2 (Magno y Tatiano en el Centro Espacial)
            for linea in re.findall(r"^\s*(?:trainerbattle|multi_)\w*\s+.*$", f.read(), re.M):
                for t in re.findall(r"\bTRAINER_\w+", linea):
                    resultado.setdefault(t, map_id)
    return resultado


def interpolar(v, vmin, vmax, nmin, nmax):
    if vmax <= vmin:
        return nmax
    v = min(max(v, vmin), vmax)
    return round(nmin + (v - vmin) * (nmax - nmin) / (vmax - vmin))


def calcular_entrenadores(base, mapas):
    tramo_de = {t: tramo_de_mapa(m) for t, m in mapas.items()}
    tramo_de = {t: s for t, s in tramo_de.items() if s and t in base and base[t]
                and not re.search(r"_[2-5]$", t)}

    # Banda original de cada tramo: nivel del Pokémon más fuerte de cada entrenador normal
    bandas = {}
    for s in TRAMOS:
        maximos = [max(base[t]) for t, ts in tramo_de.items() if ts == s
                   and t not in LIDERES and t not in JEFES_FIJOS and not es_jefe_medio(t)]
        if maximos:
            bandas[s] = (percentil(maximos, 0.10), percentil(maximos, 0.95))

    nuevos = {}
    for t, s in tramo_de.items():
        lv = base[t]
        nmin, nmax = rango_tramo(s)
        vmin, vmax = bandas.get(s, (min(lv), max(lv)))
        if t in JEFES_FIJOS:
            nuevos[t] = [JEFES_FIJOS[t]] * len(lv)
        elif t in LIDERES:
            nuevos[t] = [CAPS[s]] * len(lv)
        elif es_jefe_medio(t):
            nivel = min(CAPS[s], interpolar(max(lv), vmin, vmax, nmin, nmax) + SUBIDA_JEFES_MEDIO)
            nuevos[t] = [nivel] * len(lv)
        else:
            nuevos[t] = [max(2, interpolar(v, vmin, vmax, nmin, nmax)) for v in lv]
    return nuevos, tramo_de, bandas


def aplicar_entrenadores(texto, nuevos):
    partes = re.split(r"(^=== (?:TRAINER_\w+) ===[ \t]*$)", texto, flags=re.M)
    for i in range(1, len(partes), 2):
        nombre = re.match(r"=== (TRAINER_\w+) ===", partes[i]).group(1)
        if nombre not in nuevos:
            continue
        niveles = iter(nuevos[nombre])
        partes[i + 1] = re.sub(r"^(Level:\s*)\d+", lambda m: f"{m.group(1)}{next(niveles)}",
                               partes[i + 1], flags=re.M)
    return "".join(partes)


def calcular_salvajes(datos, nuevos, tramo_de, mapas, bandas):
    # Nivel de los entrenadores normales de cada mapa (media de su Pokémon más fuerte)
    nivel_mapa = {}
    for t, s in tramo_de.items():
        if t in LIDERES or t in JEFES_FIJOS or es_jefe_medio(t):
            continue
        nivel_mapa.setdefault(mapas[t], []).append(max(nuevos[t]))
    nivel_mapa = {m: round(sum(v) / len(v)) for m, v in nivel_mapa.items()}

    resumen = {}
    for grupo in datos["wild_encounter_groups"]:
        if grupo.get("label") != "gWildMonHeaders":
            continue
        for zona in grupo["encounters"]:
            s = tramo_de_mapa(zona["map"])
            if not s:
                continue
            nmin, nmax = rango_tramo(s)
            for tipo in ("land_mons", "water_mons", "rock_smash_mons", "fishing_mons", "hidden_mons"):
                if tipo not in zona:
                    continue
                mons = zona[tipo]["mons"]
                vmedia = sum(m["min_level"] + m["max_level"] for m in mons) / (2 * len(mons))
                if zona["map"] in nivel_mapa:
                    entrenadores = nivel_mapa[zona["map"]]
                elif s in bandas:
                    entrenadores = interpolar(vmedia, *bandas[s], nmin, nmax)
                else:
                    entrenadores = (nmin + nmax) // 2
                objetivo = max(2, entrenadores - MARGEN_SALVAJES)
                desvio = max(max(abs(m["min_level"] - vmedia), abs(m["max_level"] - vmedia)) for m in mons)
                escala = min(1.0, 2 / desvio) if desvio else 0
                for m in mons:
                    m["min_level"] = max(2, round(objetivo + (m["min_level"] - vmedia) * escala))
                    m["max_level"] = max(m["min_level"], round(objetivo + (m["max_level"] - vmedia) * escala))
                resumen.setdefault(s, []).append(objetivo)
    return resumen


def main():
    solo_resumen = "--resumen" in sys.argv
    base = leer_entrenadores(git_show(TRAINERS))
    mapas = mapas_de_entrenadores()
    nuevos, tramo_de, bandas = calcular_entrenadores(base, mapas)

    with open(TRAINERS, encoding="utf-8", newline="") as f:
        texto = f.read()
    actuales = leer_entrenadores(texto)
    nuevos = {t: n for t, n in nuevos.items() if t in actuales and len(actuales[t]) == len(n)}

    salvajes = json.loads(git_show(WILD))
    resumen_salvajes = calcular_salvajes(salvajes, nuevos, tramo_de, mapas, bandas)

    print("Tramo  Cap  Normales   Jefes (equipo)                 Salvajes")
    for s in TRAMOS:
        normales = [lv for t, ts in tramo_de.items() if ts == s and t in nuevos
                    and t not in LIDERES and t not in JEFES_FIJOS and not es_jefe_medio(t)
                    for lv in nuevos[t]]
        jefes = sorted({(t, nuevos[t][0]) for t, ts in tramo_de.items() if ts == s and t in nuevos
                        and (t in LIDERES or t in JEFES_FIJOS or es_jefe_medio(t))}, key=lambda x: x[1])
        jefes_txt = ", ".join(sorted({f"{t[8:].split('_')[0].title()} {n}" for t, n in jefes}))
        sv = resumen_salvajes.get(s, [])
        print(f"{s:>5}  {CAPS[s]:>3}  {min(normales, default=0):>3}-{max(normales, default=0):<3}   "
              f"{jefes_txt[:60]:<60}  {min(sv, default=0)}-{max(sv, default=0)}")

    if solo_resumen:
        return
    with open(TRAINERS, "w", encoding="utf-8", newline="") as f:
        f.write(aplicar_entrenadores(texto, nuevos))
    with open(WILD, "w", encoding="utf-8", newline="") as f:
        f.write(json.dumps(salvajes, indent=2, ensure_ascii=False) + "\n")
    print(f"\nReescalados {len(nuevos)} entrenadores y las zonas salvajes de Hoenn.")


if __name__ == "__main__":
    main()
