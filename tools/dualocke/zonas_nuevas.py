#!/usr/bin/env python3
"""
Dualocke: salvajes de las zonas nuevas y de las que antes no tenían (ZONAS.md).

Uso (desde la raíz del repo), siempre después de reescalar_niveles.py, que vuelve a escribir
src/data/wild_encounters.json desde la base y se las llevaría por delante:
    python3 tools/dualocke/reescalar_niveles.py
    python3 tools/dualocke/zonas_nuevas.py
    python3 tools/dualocke/equipos_jefes.py
    ...

- Las tablas van **al final** de gWildMonHeaders. El randomizer saca los salvajes de una baraja en
  el orden del archivo (aleatorio/salvajes.py): así no cambian los de las semillas en curso.
- Las especies son las de una partida sin semilla; con semilla las cambia el randomizer.
- Nivel: el de los entrenadores del tramo menos 3 (como reescalar_niveles.py), ±2. Las tres cañas,
  el mismo.
- Se puede volver a lanzar: si la tabla del mapa ya está, la sustituye en su sitio.
"""

import json
import re
import sys

sys.path.insert(0, "tools/dualocke")
import reescalar_niveles as rn  # noqa: E402

WILD = "src/data/wild_encounters.json"

# Islas del ferry (Miguel, 16/11/2026). Tierra: 12 huecos; agua: 5; pesca: 10 (2 caña vieja,
# 3 buena, 5 súper).
PESCA_TROPICAL = ["MAGIKARP", "LUVDISC", "LUVDISC", "CORSOLA", "FINNEON",
                  "CORSOLA", "LUMINEON", "WISHIWASHI", "BRUXISH", "DHELMISE"]
PESCA_LEJOS = ["MAGIKARP", "REMORAID", "REMORAID", "CHINCHOU", "SKRELP",
               "LANTURN", "OCTILLERY", "CLAUNCHER", "DRAGALGE", "LAPRAS"]
CUEVA_OMBLIGO = ["GOLBAT", "SABLEYE", "NOIBAT", "GOLBAT", "MAWILE", "CARBINK",
                 "NOIBAT", "LAIRON", "DRUDDIGON", "HONEDGE", "CROBAT", "DEINO"]
CUEVA_GRUTA = ["SLUGMA", "NUMEL", "SALANDIT", "SIZZLIPEDE", "ROLYCOLY", "LITWICK",
               "HEATMOR", "MAGBY", "CHARCADET", "TURTONATOR", "TORKOAL", "LARVESTA"]
RUINAS = ["BALTOY", "YAMASK", "GOLETT", "BRONZOR", "SIGILYPH", "RUNERIGUS",
          "ELGYEM", "CLAYDOL", "BRONZONG", "COFAGRIGUS", "SPIRITOMB", "ARCHEN"]
# Islas de las rutas del sur (crear_islas_sur.py): mar del sur, ruinas, volcán y arena
AGUA_SUR = ["TENTACOOL", "WINGULL", "PELIPPER", "TENTACRUEL", "MANTINE"]
MANSION = ["GASTLY", "SHUPPET", "DUSKULL", "MISDREAVUS", "LITWICK", "PHANTUMP",
           "PUMPKABOO", "SINISTEA", "GREAVARD", "DRIFLOON", "ROTOM", "DREEPY"]
SALVAJES = {
    "MAP_SOUTHERN_ISLAND_EXTERIOR": {
        "fishing_mons": PESCA_TROPICAL,
    },
    # ISLA SUR: hierba alta en el claro del bosque (puesta a mano en su map.bin el 17/11/2026)
    "MAP_SOUTHERN_ISLAND_INTERIOR": {
        "land_mons": ["BOUNSWEET", "PIKIPEK", "EXEGGCUTE", "FOMANTIS", "TROPIUS", "COMFEY",
                      "ORANGURU", "PASSIMIAN", "DARTRIX", "TSAREENA", "LURANTIS", "JANGMO_O"],
    },
    "MAP_FARAWAY_ISLAND_ENTRANCE": {
        "fishing_mons": PESCA_LEJOS,
    },
    "MAP_FARAWAY_ISLAND_INTERIOR": {
        "land_mons": ["AIPOM", "TROPIUS", "PIKIPEK", "EXEGGCUTE", "PASSIMIAN", "ORANGURU",
                      "COMFEY", "TRUMBEAK", "HERACROSS", "PINSIR", "SNORLAX", "KANGASKHAN"],
    },
    "MAP_BIRTH_ISLAND_EXTERIOR": {
        "fishing_mons": ["MAGIKARP", "STARYU", "STARYU", "CLAMPERL", "MAREANIE",
                         "STARMIE", "PYUKUMUKU", "TOXAPEX", "DHELMISE", "LAPRAS"],
    },
    "MAP_NAVEL_ROCK_EXTERIOR": {
        "fishing_mons": PESCA_LEJOS,
    },
    "MAP_NAVEL_ROCK_ENTRANCE": {"land_mons": CUEVA_OMBLIGO},
    "MAP_NAVEL_ROCK_B1F": {"land_mons": CUEVA_OMBLIGO},
    "MAP_NAVEL_ROCK_FORK": {"land_mons": CUEVA_OMBLIGO},
    "MAP_NAVEL_ROCK_TOP": {"land_mons": CUEVA_OMBLIGO},
    "MAP_NAVEL_ROCK_BOTTOM": {"land_mons": CUEVA_OMBLIGO},
    # GRUTA ÍGNEA (crear_gruta_ignea.py): Pokémon de fuego y roca de todas las generaciones
    "MAP_GRUTA_IGNEA": {"land_mons": CUEVA_GRUTA},
    "MAP_GRUTA_IGNEA_CAMARA": {"land_mons": CUEVA_GRUTA},
    # ISLA NEVADA y CUEVA HELADA (crear_isla_nevada.py): Pokémon de hielo
    "MAP_ISLA_NEVADA": {
        "water_mons": ["SPHEAL", "SEEL", "SPHEAL", "DELIBIRD", "LAPRAS"],
        "fishing_mons": ["MAGIKARP", "SEEL", "SEEL", "SPHEAL", "ARCTOVISH",
                         "SEALEO", "DEWGONG", "CLOYSTER", "ARCTOVISH", "LAPRAS"],
    },
    # DESIERTO PROFUNDO y RUINAS ARENOSAS (crear_desierto_profundo.py)
    "MAP_DESIERTO_PROFUNDO": {
        "land_mons": ["TRAPINCH", "SANDSHREW", "CACNEA", "HIPPOPOTAS", "SANDILE", "SILICOBRA",
                      "HELIOPTILE", "SKORUPI", "MARACTUS", "BALTOY", "LARVITAR", "GIBLE"],
    },
    "MAP_RUINAS_ARENOSAS": {"land_mons": RUINAS},
    "MAP_RUINAS_ARENOSAS_2F": {"land_mons": RUINAS},
    "MAP_RUINAS_ARENOSAS_3F": {"land_mons": RUINAS},
    # MARISMA AZULIZA (crear_marisma_azuliza.py): Pokémon de pantano. Se pesca en las charcas con la
    # CAÑA VIEJA de AZULIZA; el agua de surf, para cuando se vuelva con SURF
    "MAP_MARISMA_AZULIZA": {
        "land_mons": ["WOOPER", "LOTAD", "SURSKIT", "YANMA", "TYMPOLE", "SHROOMISH",
                      "CROAGUNK", "PARAS", "SHELLOS", "STUNFISK", "DEWPIDER", "GOOMY"],
        "water_mons": ["SURSKIT", "LOTAD", "WOOPER", "POLIWAG", "CHEWTLE"],
        "rock_smash_mons": ["GEODUDE", "GEODUDE", "NOSEPASS", "ROGGENROLA", "BINACLE"],
        "fishing_mons": ["MAGIKARP", "BARBOACH", "BARBOACH", "POLIWAG", "GOLDEEN",
                         "WISHIWASHI", "BARBOACH", "TYMPOLE", "CHEWTLE", "BASCULIN"],
    },
    # BOSQUE FRONDOSO (crear_bosque_frondoso.py): bichos y plantas de todas las generaciones. Se pesca en
    # la charca; el agua de surf, para cuando se vuelva con SURF
    "MAP_BOSQUE_FRONDOSO": {
        "land_mons": ["SEWADDLE", "NINCADA", "SEEDOT", "SKWOVET", "PIKIPEK", "PINECO",
                      "FOMANTIS", "CUTIEFLY", "MORELULL", "PETILIL", "SCYTHER", "HERACROSS"],
        "water_mons": ["LOTAD", "SURSKIT", "PSYDUCK", "LOTAD", "WOOPER"],
        "fishing_mons": ["MAGIKARP", "GOLDEEN", "POLIWAG", "GOLDEEN", "PSYDUCK", "POLIWAG",
                         "GOLDEEN", "LOTAD", "MARILL", "DRATINI"],
    },
    # MANSIÓN OLVIDADA: fantasmas en el suelo de madera (los del barco tienen salvajes)
    "MAP_MANSION_OLVIDADA": {"land_mons": MANSION},
    "MAP_MANSION_OLVIDADA_DESVAN": {"land_mons": MANSION},
    "MAP_ISLA_DE_RUINAS": {"water_mons": AGUA_SUR, "fishing_mons": ["MAGIKARP", "TENTACOOL", "WAILMER", "CHINCHOU", "RELICANTH", "LANTURN",
                                       "WAILORD", "SHARPEDO", "DHELMISE", "GYARADOS"]},
    "MAP_ISLA_DE_RUINAS_TORRE": {"land_mons": ["BRONZONG", "GOLURK", "SIGILYPH", "BEHEEYEM", "CLAYDOL", "CHIMECHO",
                                  "SOLROCK", "LUNATONE", "RUNERIGUS", "COFAGRIGUS", "METANG", "ZWEILOUS"]},
    "MAP_ISLA_VOLCANICA": {"water_mons": AGUA_SUR, "fishing_mons": ["MAGIKARP", "TENTACOOL", "WAILMER", "CORSOLA", "CLAUNCHER", "CLAWITZER",
                                       "SHARPEDO", "CRAWDAUNT", "TOXAPEX", "GYARADOS"]},
    # El CRÁTER: salvajes en la ceniza
    "MAP_ISLA_VOLCANICA_CRATER": {"land_mons": ["MAGCARGO", "CAMERUPT", "TORKOAL", "MAGMORTAR", "HEATMOR", "SALAZZLE",
                                   "CENTISKORCH", "COALOSSAL", "ARMAROUGE", "TURTONATOR", "VOLCARONA", "LARVESTA"]},
    # ISLA ARENOSA: hierba alta entre los árboles del islote de abajo a la izquierda
    "MAP_ISLA_ARENOSA": {
        "land_mons": ["SANDSLASH", "DUGTRIO", "KROOKODILE", "HIPPOWDON", "CACTURNE", "SANDACONDA",
                      "PALOSSAND", "FLYGON", "DRAPION", "STEELIX", "GABITE", "PUPITAR"],
        "water_mons": AGUA_SUR,
        "fishing_mons": PESCA_TROPICAL,
    },
    # PLAYA VOLCÁNICA (crear_playa_volcanica.py): salvajes en la ceniza; playa y mar
    "MAP_PLAYA_VOLCANICA": {
        "land_mons": ["NUMEL", "SLUGMA", "TORKOAL", "CAMERUPT", "MAGCARGO", "SALANDIT",
                      "KRABBY", "CRABRAWLER", "DWEBBLE", "SANDYGAST", "TURTONATOR", "LARVESTA"],
        "water_mons": AGUA_SUR,
        "fishing_mons": ["MAGIKARP", "TENTACOOL", "KRABBY", "CORPHISH", "CLAUNCHER", "KINGLER",
                         "CRAWDAUNT", "CLAWITZER", "WAILORD", "GYARADOS"],
    },
    # CUMBRE METEORO (crear_cumbre_meteoro.py): roca y lucha en la ladera; hielo, aire y dragón arriba
    "MAP_CUMBRE_METEORO_LADERA": {"land_mons": ["MACHOP", "GEODUDE", "ARON", "MAKUHITA", "NOSEPASS", "SWABLU",
                                   "ROGGENROLA", "ROCKRUFF", "TIMBURR", "MIENFOO", "DRUDDIGON", "BAGON"]},
    "MAP_CUMBRE_METEORO": {"land_mons": ["SWABLU", "SNORUNT", "SKARMORY", "NOIBAT", "BERGMITE", "CUBCHOO",
                                   "AMAURA", "ROOKIDEE", "ALTARIA", "CRYOGONAL", "FRIGIBAX", "BAGON"]},
    "MAP_ISLA_NEVADA_CUEVA": {
        "land_mons": ["SNORUNT", "SWINUB", "SNOVER", "CUBCHOO", "VANILLITE", "SNOM",
                      "BERGMITE", "SNEASEL", "CETODDLE", "CRYOGONAL", "EISCUE", "FRIGIBAX"],
    },
}

# Entrenadores de las zonas nuevas.
# - CABECERAS: entrenadores que ya existían (pero no salían en ningún mapa) a los que se les cambia
#   algo de la cabecera. Su equipo y su nivel los pone reescalar_niveles.py (ENTRENADORES_ISLAS).
# - NUEVOS: entrenadores nuevos (include/constants/opponents.h). reescalar_niveles.py no los
#   conoce (no están en la base), así que el equipo entero lo escribe este script, al nivel más
#   alto de los entrenadores normales de su tramo (el último, el as) y 1 menos el resto.
#   Las especies son las de una partida sin semilla, ya evolucionadas para su nivel
#   (evolucionar_entrenadores.py solo mira los de la base); el randomizer las cambia con semilla.
CABECERAS = {
    # El soldado sin usar tenía los gráficos y la música del Equipo Aqua
    "TRAINER_GRUNT_UNUSED": {"Pic": "Magma Grunt F", "Music": "Magma"},
}
NUEVOS = {
    "TRAINER_IGOR": {
        "mapa": "MAP_GRUTA_IGNEA",
        "cabecera": [("Name", "ÍGOR"), ("Class", "Kindler"), ("Pic", "Kindler"), ("Gender", "Male"),
                     ("Music", "Hiker"), ("Double Battle", "No"), ("AI", "Basic Trainer")],
        "equipo": ["Camerupt", "Magcargo", "Magmortar"],
    },
    "TRAINER_NIEVES": {
        "mapa": "MAP_ISLA_NEVADA_CUEVA",
        "cabecera": [("Name", "NIEVES"), ("Class", "Cooltrainer"), ("Pic", "Cooltrainer F"), ("Gender", "Female"),
                     ("Music", "Cool"), ("Double Battle", "No"), ("AI", "Basic Trainer")],
        "equipo": ["Froslass", "Abomasnow", "Walrein"],
    },
    "TRAINER_RAMIRO": {
        "mapa": "MAP_RUINAS_ARENOSAS",
        "cabecera": [("Name", "RAMIRO"), ("Class", "Ruin Maniac"), ("Pic", "Ruin Maniac"), ("Gender", "Male"),
                     ("Music", "Hiker"), ("Double Battle", "No"), ("AI", "Basic Trainer")],
        "equipo": ["Claydol", "Golurk"],
    },
    "TRAINER_SOLEDAD": {
        "mapa": "MAP_DESIERTO_PROFUNDO",
        "cabecera": [("Name", "SOLEDAD"), ("Class", "Expert"), ("Pic", "Expert F"), ("Gender", "Female"),
                     ("Music", "Intense"), ("Double Battle", "No"), ("AI", "Basic Trainer")],
        "equipo": ["Flygon", "Hippowdon", "Cacturne"],
    },
    "TRAINER_TOMAS": {
        "mapa": "MAP_MARISMA_AZULIZA",
        "cabecera": [("Name", "TOMÁS"), ("Class", "Fisherman"), ("Pic", "Fisherman"), ("Gender", "Male"),
                     ("Music", "Hiker"), ("Double Battle", "No"), ("AI", "Check Bad Move")],
        "equipo": ["Barboach", "Lotad"],
    },
    "TRAINER_MARGARITA": {
        "mapa": "MAP_MARISMA_AZULIZA",
        "cabecera": [("Name", "MARGARITA"), ("Class", "Aroma Lady"), ("Pic", "Aroma Lady"), ("Gender", "Female"),
                     ("Music", "Female"), ("Double Battle", "No"), ("AI", "Check Bad Move")],
        "equipo": ["Shroomish", "Paras"],
    },
    "TRAINER_SEBAS": {
        "mapa": "MAP_BOSQUE_FRONDOSO",
        "cabecera": [("Name", "SEBAS"), ("Class", "Bug Catcher"), ("Pic", "Bug Catcher"), ("Gender", "Male"),
                     ("Music", "Male"), ("Double Battle", "No"), ("AI", "Check Bad Move")],
        "equipo": ["Dustox", "Ninjask"],
    },
    # Estos tres existían sin usar (placeholders de Esmeralda): se reescribe su bloque entero
    "TRAINER_BRENDAN_PLACEHOLDER": {
        "mapa": "MAP_BOSQUE_FRONDOSO",
        "cabecera": [("Name", "OLIVIA"), ("Class", "Picnicker"), ("Pic", "Picnicker"), ("Gender", "Female"),
                     ("Music", "Girl"), ("Double Battle", "No"), ("AI", "Check Bad Move")],
        "equipo": ["Nuzleaf", "Skiploom"],
    },
    "TRAINER_MAY_PLACEHOLDER": {
        "mapa": "MAP_MANSION_OLVIDADA",
        "cabecera": [("Name", "ELVIRA"), ("Class", "Hex Maniac"), ("Pic", "Hex Maniac"), ("Gender", "Female"),
                     ("Music", "Suspicious"), ("Double Battle", "No"), ("AI", "Check Bad Move")],
        "equipo": ["Shuppet", "Duskull", "Misdreavus"],
    },
    "TRAINER_LEAF": {
        "mapa": "MAP_MANSION_OLVIDADA",
        "cabecera": [("Name", "ALFONSO"), ("Class", "Gentleman"), ("Pic", "Gentleman"), ("Gender", "Male"),
                     ("Music", "Rich"), ("Double Battle", "No"), ("AI", "Check Bad Move")],
        "equipo": ["Drifloon", "Litwick"],
    },
    # TRAINER_RED existía sin usar: se reescribe su bloque entero
    "TRAINER_RED": {
        "mapa": "MAP_ISLA_ARENOSA",
        "cabecera": [("Name", "DARÍO"), ("Class", "Cooltrainer"), ("Pic", "Cooltrainer M"), ("Gender", "Male"),
                     ("Music", "Cool"), ("Double Battle", "No"), ("AI", "Basic Trainer")],
        "equipo": ["Krookodile", "Hippowdon", "Flygon"],
    },
    "TRAINER_ROQUE": {
        "mapa": "MAP_GRUTA_IGNEA",
        "cabecera": [("Name", "ROQUE"), ("Class", "Hiker"), ("Pic", "Hiker"), ("Gender", "Male"),
                     ("Music", "Hiker"), ("Double Battle", "No"), ("AI", "Basic Trainer")],
        "equipo": ["Golem", "Torkoal"],
    },
}
TRAINERS = "src/data/trainers.party"
DESPUES_DE = "TRAINER_STEVEN_ROUTE_120"   # los nuevos van detrás del último de Esmeralda
TASAS = {"land_mons": 10, "water_mons": 4, "fishing_mons": 30, "rock_smash_mons": 20}


def etiqueta(mapa):
    """MAP_NAVEL_ROCK_B1F -> gNavelRock_B1F (la carpeta del mapa)."""
    for carpeta in sorted(__import__("os").listdir("data/maps")):
        try:
            with open(f"data/maps/{carpeta}/map.json", encoding="utf-8") as f:
                if json.load(f)["id"] == mapa:
                    return "g" + carpeta
        except (FileNotFoundError, KeyError):
            continue
    raise SystemExit(f"Dualocke: no encuentro el mapa {mapa}")


def tabla(mapa, tipos):
    tramo = rn.tramo_de_mapa(mapa)
    assert tramo, f"{mapa} no tiene tramo en reescalar_niveles.py (TRAMOS)"
    nivel = rn.rango_tramo(tramo)[1] - rn.MARGEN_SALVAJES
    nivel = min(nivel, rn.CAPS[tramo])
    entrada = {"map": mapa, "base_label": etiqueta(mapa)}
    for tipo, especies in tipos.items():
        mons = []
        for i, especie in enumerate(especies):
            # Los huecos raros (los últimos) un poco más altos
            sube = 2 if i >= len(especies) - 2 else (1 if i >= len(especies) // 2 else 0)
            mons.append({"min_level": nivel - 2 + sube, "max_level": nivel + sube, "species": f"SPECIES_{especie}"})
        entrada[tipo] = {"encounter_rate": TASAS[tipo], "mons": mons}
    return entrada


def bloques(texto):
    """[(TRAINER_X, inicio, fin)] de cada entrenador en trainers.party."""
    marcas = [(m.group(1), m.start()) for m in re.finditer(r"^=== (TRAINER_\w+) ===[ \t]*$", texto, re.M)]
    return [(t, ini, marcas[i + 1][1] if i + 1 < len(marcas) else len(texto)) for i, (t, ini) in enumerate(marcas)]


def entrenadores():
    with open(TRAINERS, encoding="utf-8", newline="") as f:
        texto = f.read()
    salto = "\r\n" if "\r\n" in texto else "\n"
    for t, campos in CABECERAS.items():
        _, ini, fin = next(b for b in bloques(texto) if b[0] == t)
        bloque = texto[ini:fin]
        for campo, valor in campos.items():
            bloque, n = re.subn(rf"^{campo}: .*$", f"{campo}: {valor}", bloque, count=1, flags=re.M)
            assert n == 1, (t, campo)
        texto = texto[:ini] + bloque + texto[fin:]
    for t, datos in NUEVOS.items():
        tramo = rn.tramo_de_mapa(datos["mapa"])
        tope = rn.rango_tramo(tramo)[1]
        lineas = [f"=== {t} ==="] + [f"{c}: {v}" for c, v in datos["cabecera"]] + [""]
        for i, especie in enumerate(datos["equipo"]):
            nivel = tope if i == len(datos["equipo"]) - 1 else tope - 1
            lineas += [especie, f"Level: {nivel}", "IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe", ""]
        nuevo = salto.join(lineas) + salto
        actual = next((b for b in bloques(texto) if b[0] == t), None)
        if actual:
            texto = texto[:actual[1]] + nuevo + texto[actual[2]:]
        else:
            _, _, fin = next(b for b in bloques(texto) if b[0] == DESPUES_DE)
            texto = texto[:fin] + nuevo + texto[fin:]
    with open(TRAINERS, "w", encoding="utf-8", newline="") as f:
        f.write(texto)


def main():
    entrenadores()
    with open(WILD, encoding="utf-8") as f:
        datos = json.load(f)
    grupo = next(g for g in datos["wild_encounter_groups"] if g.get("label") == "gWildMonHeaders")
    huecos = {c["type"]: len(c["encounter_rates"]) for c in grupo["fields"]}
    for mapa, tipos in SALVAJES.items():
        for tipo, especies in tipos.items():
            assert len(especies) == huecos[tipo], (mapa, tipo, len(especies), huecos[tipo])
        nueva = tabla(mapa, tipos)
        actual = next((i for i, e in enumerate(grupo["encounters"]) if e["map"] == mapa), None)
        if actual is None:
            grupo["encounters"].append(nueva)
        else:
            grupo["encounters"][actual] = nueva
    with open(WILD, "w", encoding="utf-8", newline="") as f:
        f.write(json.dumps(datos, indent=2, ensure_ascii=False) + "\n")
    print(f"Dualocke: salvajes de {len(SALVAJES)} mapas de zonas nuevas y {len(NUEVOS)} entrenadores nuevos")


if __name__ == "__main__":
    main()
