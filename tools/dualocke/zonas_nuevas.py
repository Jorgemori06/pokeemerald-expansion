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
SALVAJES = {
    "MAP_SOUTHERN_ISLAND_EXTERIOR": {
        "fishing_mons": PESCA_TROPICAL,
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
}
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


def main():
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
    print(f"Dualocke: salvajes de {len(SALVAJES)} mapas de zonas nuevas")


if __name__ == "__main__":
    main()
