#!/usr/bin/env python3
"""
Dualocke: equipos de los jefes y entrenadores importantes.

Uso (desde la raíz del repo, después de reescalar_niveles.py):
    python3 tools/dualocke/reescalar_niveles.py
    python3 tools/dualocke/equipos_jefes.py

Cada equipo se construye desde el original de la expansion (commit BASE) y la tabla de
abajo, con los niveles que calcula reescalar_niveles.py, así que se puede volver a lanzar.

Reglas (decididas por Miguel, ver DUALOCKE.md, sección 6):
- +2 Pokémon a los líderes, al Alto Mando y a Plubio; +1 al rival, Blasco, Magno, Aquiles
  y los admins. Máximo 6.
- Huecos nuevos: Pokémon del tipo del jefe. El randomizer los cambiará igualmente.
- Desde el aro (Alana en adelante) el as (el último del equipo) lleva su megapiedra.
- Sin más objetos: el resto los pondrá el randomizer.

Formato de cada equipo, en orden (el último es el as):
    "Geodude"            Pokémon original que se conserva (con sus movimientos)
    "Swablu>Altaria"     Pokémon original que evoluciona (conserva sus movimientos)
    "+SPECIES_ONIX"      Pokémon nuevo (movimientos por defecto de su nivel)
    "...@ITEM_X"         objeto equipado (sustituye al original)
"""

import re
import sys

sys.path.insert(0, __file__.rsplit("/", 1)[0].rsplit("\\", 1)[0])
import reescalar_niveles as rn  # noqa: E402

EQUIPOS = {
    # Líderes (+2)
    "TRAINER_ROXANNE_1": ["Geodude", "+SPECIES_LARVITAR", "+SPECIES_ONIX", "+SPECIES_ARON", "Nosepass"],
    "TRAINER_BRAWLY_1": ["Machop", "Meditite", "+SPECIES_MANKEY", "+SPECIES_TIMBURR", "Makuhita"],
    "TRAINER_WATTSON_1": ["Voltorb>Electrode", "Magneton", "+SPECIES_LUXRAY", "+SPECIES_AMPHAROS",
                          "+SPECIES_RAICHU", "Manectric"],
    "TRAINER_FLANNERY_1": ["+SPECIES_NINETALES", "Slugma>Magcargo", "+SPECIES_HOUNDOOM", "+SPECIES_ARCANINE",
                           "Camerupt", "Torkoal"],
    "TRAINER_NORMAN_1": ["Spinda", "Vigoroth", "Linoone", "+SPECIES_URSARING", "+SPECIES_KANGASKHAN",
                         "Slaking"],
    "TRAINER_WINONA_1": ["+SPECIES_SWELLOW", "Tropius", "Pelipper", "Skarmory", "+SPECIES_STARAPTOR",
                         "Altaria@ITEM_ALTARIANITE"],
    "TRAINER_TATE_AND_LIZA_1": ["Claydol", "Xatu", "Lunatone", "Solrock", "+SPECIES_BRONZONG",
                                "+SPECIES_METAGROSS@ITEM_METAGROSSITE"],
    "TRAINER_JUAN_1": ["Whiscash", "Sealeo>Walrein", "Crawdaunt", "+SPECIES_LANTURN", "Kingdra",
                       "+SPECIES_STARMIE@ITEM_STARMINITE"],
    # Alto Mando y Plubio (+2, máximo 6)
    "TRAINER_SIDNEY": ["Mightyena", "Shiftry", "Cacturne", "Crawdaunt", "+SPECIES_HONCHKROW",
                       "Absol@ITEM_ABSOLITE"],
    "TRAINER_PHOEBE": ["Dusclops>Dusknoir", "Sableye", "+SPECIES_MISMAGIUS", "+SPECIES_CHANDELURE",
                       "+SPECIES_GENGAR", "Banette@ITEM_BANETTITE"],
    "TRAINER_GLACIA": ["Walrein", "+SPECIES_FROSLASS", "+SPECIES_WEAVILE", "+SPECIES_MAMOSWINE",
                       "+SPECIES_ABOMASNOW", "Glalie@ITEM_GLALITITE"],
    "TRAINER_DRAKE": ["Altaria", "Kingdra", "Flygon", "+SPECIES_GARCHOMP", "+SPECIES_DRAGONITE",
                      "Salamence@ITEM_SALAMENCITE"],
    "TRAINER_WALLACE": ["Wailord", "Tentacruel", "Ludicolo", "Whiscash", "Milotic",
                        "Gyarados@ITEM_GYARADOSITE"],
    # Blasco (+1)
    "TRAINER_WALLY_MAUVILLE": ["+SPECIES_SWABLU", "Ralts>Kirlia"],
    "TRAINER_WALLY_VR_1": ["Altaria", "Delcatty", "Roselia>Roserade", "Magneton>Magnezone",
                           "+SPECIES_GALLADE", "Gardevoir@ITEM_GARDEVOIRITE"],
    # Magno y Aquiles (+1)
    "TRAINER_MAXIE_MT_CHIMNEY": ["Mightyena", "Zubat>Golbat", "+SPECIES_HOUNDOOM", "Camerupt"],
    "TRAINER_MAXIE_MAGMA_HIDEOUT": ["Mightyena", "Crobat", "+SPECIES_HOUNDOOM", "Camerupt@ITEM_CAMERUPTITE"],
    "TRAINER_MAXIE_MOSSDEEP": ["Mightyena", "Crobat", "+SPECIES_HOUNDOOM", "Camerupt@ITEM_CAMERUPTITE"],
    "TRAINER_ARCHIE": ["Mightyena", "Crobat", "+SPECIES_MUK", "Sharpedo@ITEM_SHARPEDONITE"],
    # Admins (+1)
    "TRAINER_TABITHA_MT_CHIMNEY": ["Numel", "Poochyena>Mightyena", "Numel>Camerupt", "Zubat>Golbat",
                                   "+SPECIES_HOUNDOOM"],
    "TRAINER_TABITHA_MAGMA_HIDEOUT": ["Numel>Torkoal", "Mightyena", "Zubat>Crobat", "Camerupt",
                                      "+SPECIES_HOUNDOOM"],
    "TRAINER_TABITHA_MOSSDEEP": ["Camerupt", "Mightyena", "Golbat>Crobat", "+SPECIES_HOUNDOOM"],
    "TRAINER_SHELLY_WEATHER_INSTITUTE": ["Carvanha>Sharpedo", "Mightyena", "+SPECIES_CRAWDAUNT"],
    "TRAINER_SHELLY_SEAFLOOR_CAVERN": ["Sharpedo", "Mightyena", "+SPECIES_CRAWDAUNT"],
    "TRAINER_MATT": ["Mightyena", "Golbat>Crobat", "+SPECIES_SHARPEDO"],
}

# Rival: evoluciona por nivel, +1 Pokémon de su grupo habitual y, desde el aro (Calagua),
# su inicial lleva la megapiedra.
EVOLUCION_RIVAL = [  # (de, a, nivel)
    ("Treecko", "Grovyle", 16), ("Grovyle", "Sceptile", 36),
    ("Torchic", "Combusken", 16), ("Combusken", "Blaziken", 36),
    ("Mudkip", "Marshtomp", 16), ("Marshtomp", "Swampert", 36),
    ("Wingull", "Pelipper", 25), ("Slugma", "Magcargo", 38),
    ("Lotad", "Lombre", 14), ("Lombre", "Ludicolo", 35),
]
LINEAS_RIVAL = [["Wingull", "Pelipper"], ["Slugma", "Magcargo"], ["Lotad", "Lombre", "Ludicolo"],
                ["Tropius"]]
MEGA_INICIAL = {"Sceptile": "ITEM_SCEPTILITE", "Blaziken": "ITEM_BLAZIKENITE",
                "Swampert": "ITEM_SWAMPERTITE"}
RIVAL = re.compile(r"TRAINER_(MAY|BRENDAN)_(ROUTE_103|RUSTBORO|ROUTE_110|ROUTE_119|LILYCOVE)_\w+$")


def separar(bloque):
    """Separa la cabecera del entrenador y los Pokémon (cada uno, un trozo de texto)."""
    trozos = [t for t in re.split(r"\n[ \t]*\n", bloque.strip("\n")) if t.strip()]
    return trozos[0], trozos[1:]


def especie(trozo):
    return re.sub(r"\s*\(.*?\)|\s*@.*", "", trozo.splitlines()[0]).strip()


def con_especie_y_objeto(trozo, nueva=None, objeto=None):
    lineas = trozo.splitlines()
    m = re.match(r"^(.*?)(\s*@\s*.*)?$", lineas[0])
    nombre = nueva if nueva else m.group(1).strip()
    if objeto:
        lineas[0] = f"{nombre} @ {objeto}"
    else:
        lineas[0] = nombre + (m.group(2) or "")
    return "\n".join(lineas)


def nivel_de(trozo):
    return int(re.search(r"^Level:\s*(\d+)", trozo, re.M).group(1))


def con_nivel(trozo, nivel):
    return re.sub(r"^(Level:\s*)\d+", lambda m: f"{m.group(1)}{nivel}", trozo, flags=re.M)


def construir(nombre, cabecera, mons, spec):
    nivel_max = max(nivel_de(m) for m in mons)
    ivs = re.search(r"^IVs:.*$", mons[-1], re.M)
    usados = set()
    salida = []
    for entrada in spec:
        entrada, _, objeto = entrada.partition("@")
        if entrada.startswith("+"):
            trozo = f"{entrada[1:]}\nLevel: {nivel_max}" + (f"\n{ivs.group(0)}" if ivs else "")
            salida.append(con_especie_y_objeto(trozo, objeto=objeto or None))
            continue
        original, _, nueva = entrada.partition(">")
        idx = next(i for i, m in enumerate(mons) if i not in usados and especie(m) == original)
        usados.add(idx)
        salida.append(con_especie_y_objeto(mons[idx], nueva or None, objeto or None))
    assert len(salida) <= 6, nombre
    return cabecera, salida


def construir_rival(nombre, cabecera, mons):
    nivel = max(nivel_de(m) for m in mons)
    actuales = []
    for m in mons:
        sp = especie(m)
        for de, a, lv in EVOLUCION_RIVAL:
            if sp == de and nivel >= lv:
                sp = a
        actuales.append([m, sp])
    presentes = {sp for _, sp in actuales}
    for linea in LINEAS_RIVAL:
        if not presentes & set(linea):
            sp = linea[0]
            for de, a, lv in EVOLUCION_RIVAL:
                if sp == de and nivel >= lv:
                    sp = a
            ivs = re.search(r"^IVs:.*$", mons[-1], re.M)
            actuales.insert(len(actuales) - 1, [f"{sp}\nLevel: {nivel}" + (f"\n{ivs.group(0)}" if ivs else ""), sp])
            break
    salida = []
    for trozo, sp in actuales:
        objeto = MEGA_INICIAL.get(sp) if "LILYCOVE" in nombre else None
        cambia = sp != especie(trozo)
        salida.append(con_especie_y_objeto(trozo, sp if cambia else None, objeto))
    return cabecera, salida


def main():
    base_txt = rn.git_show(rn.TRAINERS)
    base = rn.leer_entrenadores(base_txt)
    nuevos, _, _ = rn.calcular_entrenadores(base, rn.mapas_de_entrenadores())

    partes_base = re.split(r"^=== (TRAINER_\w+) ===[ \t]*$", base_txt, flags=re.M)
    bloques_base = {partes_base[i]: partes_base[i + 1] for i in range(1, len(partes_base), 2)}

    with open(rn.TRAINERS, encoding="utf-8", newline="") as f:
        texto = f.read()
    partes = re.split(r"(^=== (?:TRAINER_\w+) ===[ \t]*$)", texto, flags=re.M)
    hechos = []
    for i in range(1, len(partes), 2):
        nombre = re.match(r"=== (TRAINER_\w+) ===", partes[i]).group(1)
        if nombre not in EQUIPOS and not RIVAL.match(nombre):
            continue
        cabecera, mons = separar(bloques_base[nombre])
        if nombre in nuevos:
            mons = [con_nivel(m, n) for m, n in zip(mons, nuevos[nombre])]
        if nombre in EQUIPOS:
            cabecera, mons = construir(nombre, cabecera, mons, EQUIPOS[nombre])
        else:
            cabecera, mons = construir_rival(nombre, cabecera, mons)
        partes[i + 1] = "\n" + "\n\n".join([cabecera] + mons) + "\n\n"
        hechos.append((nombre, [especie(m) + (" @ " + m.splitlines()[0].split("@")[1].strip() if "@" in m.splitlines()[0] else "") for m in mons]))

    texto = "".join(partes)
    with open(rn.TRAINERS, "w", encoding="utf-8", newline="") as f:
        f.write(texto)
    for nombre, mons in hechos:
        print(f"{nombre[8:]:34s} {', '.join(mons)}")
    print(f"\n{len(hechos)} equipos actualizados.")


if __name__ == "__main__":
    main()
