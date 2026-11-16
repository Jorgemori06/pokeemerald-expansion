#!/usr/bin/env python3
"""
Dualocke: las formas Gigamax son megaevoluciones, cada una con su megapiedra (idea 9 de IDEAS.md;
pedido por Miguel el 15/11/2026: "como el Dinamax no se usa, que las formas Gigamax sean megas").

Uso (desde la raíz del repo; se puede volver a lanzar después de cambiar DISENO):
    python3 tools/dualocke/megas_gigamax.py

Qué hace:
- Formas (src/data/pokemon/species_info/gen_*_families.h): cada forma Gigamax de DISENO pasa a ser
  una mega (isMegaEvolution) con las estadísticas, el tipo, la habilidad y el peso de DISENO.
  Va dentro de "#if TESTING ... #else ... #endif": en los tests de la expansion se queda la forma
  Gigamax de siempre, porque los tests del Dinamax la usan. En el juego sale la mega.
- Tabla de cambios de forma (src/data/pokemon/form_change_tables.h): en el juego, la forma
  Gigamax se consigue megaevolucionando con su megapiedra, no con el Dinamax.
- Megapiedras (include/constants/items.h y src/data/items.h): objetos nuevos al final de la
  lista, para no mover los números de los que ya hay en las partidas guardadas.
- Iconos: el dibujo de la Gengarita con una paleta nueva para cada una (la bola del color
  principal del Pokémon y la espiral de sus otros dos colores), en graphics/items/icon_palettes/.
- Bolsillo de megapiedras (BAG_MEGASTONES_COUNT): de 100 a 130. Es lo último de SaveBlock3 y las
  casillas nuevas se leen vacías de las partidas de antes.

Dónde está cada megapiedra en el mapa: MEGAPIEDRAS_GIGAMAX en colocar_objetos.py.
"""

import colorsys
import os
import re

# Especie Gigamax (sin SPECIES_ ni _GMAX): megapiedra (constante, inglés, español),
# estadísticas (PS, Ata, Def, AtE, DfE, Vel), tipos, habilidad, peso (en hg) y colores del icono
# (bola, espiral 1, espiral 2). Las estadísticas suman 100 más que la forma normal, como las megas.
# Diseño aprobado por Miguel el 16/11/2026.
DISENO = [
    ("BUTTERFREE", "BUTTERFRITE", "Butterfrite", "Butterfrita",
     (60, 45, 70, 130, 100, 90), ("BUG", "PSYCHIC"), "TINTED_LENS", 380,
     ((200, 176, 232), (112, 72, 176), (88, 168, 216))),
    ("PIKACHU", "PIKACHUNITE", "Pikachunite", "Pikachunita",
     (35, 75, 50, 90, 60, 110), ("ELECTRIC",), "TRANSISTOR", 75,
     ((248, 224, 96), (224, 64, 48), (160, 104, 40))),
    ("MEOWTH", "MEOWTHITE", "Meowthite", "Meowthita",
     (55, 75, 55, 40, 50, 115), ("NORMAL", "STEEL"), "TECHNICIAN", 62,
     ((240, 224, 176), (232, 176, 40), (152, 104, 64))),
    ("MACHAMP", "MACHAMPITE", "Machampite", "Machampita",
     (90, 160, 100, 65, 100, 90), ("FIGHTING",), "NO_GUARD", 1500,
     ((160, 176, 200), (88, 104, 152), (232, 192, 64))),
    ("KINGLER", "KINGLERITE", "Kinglerite", "Kinglerita",
     (55, 160, 135, 60, 70, 95), ("WATER", "STEEL"), "TOUGH_CLAWS", 720,
     ((232, 120, 88), (176, 40, 32), (240, 216, 176))),
    ("LAPRAS", "LAPRASITE", "Laprasite", "Laprasita",
     (130, 95, 110, 115, 125, 60), ("WATER", "ICE"), "SNOW_WARNING", 2600,
     ((112, 168, 224), (48, 88, 168), (232, 216, 184))),
    ("EEVEE", "EEVINITE", "Eevinite", "Eevinita",
     (65, 80, 70, 70, 75, 65), ("NORMAL",), "ADAPTABILITY", 90,
     ((208, 152, 96), (136, 80, 40), (248, 232, 192))),
    ("SNORLAX", "SNORLAXITE", "Snorlaxite", "Snorlaxita",
     (160, 140, 95, 65, 140, 40), ("NORMAL", "GRASS"), "THICK_FAT", 4600,
     ((72, 136, 152), (32, 80, 96), (240, 224, 184))),
    ("GARBODOR", "GARBODORITE", "Garbodorite", "Garbodorita",
     (100, 125, 112, 60, 102, 75), ("POISON",), "TOXIC_DEBRIS", 1300,
     ((120, 168, 96), (64, 104, 56), (216, 104, 168))),
    ("RILLABOOM", "RILLABOOMITE", "Rillaboomite", "Rillaboomita",
     (100, 155, 110, 60, 90, 115), ("GRASS", "FIGHTING"), "GRASSY_SURGE", 1000,
     ((96, 168, 72), (48, 104, 48), (152, 96, 56))),
    ("CINDERACE", "CINDERACITE", "Cinderacite", "Cinderacita",
     (80, 146, 90, 70, 90, 154), ("FIRE",), "LIBERO", 330,
     ((240, 240, 232), (224, 64, 40), (248, 200, 56))),
    ("INTELEON", "INTELEONITE", "Inteleonite", "Inteleonita",
     (70, 85, 75, 165, 85, 150), ("WATER",), "SNIPER", 452,
     ((80, 136, 208), (32, 64, 136), (248, 216, 72))),
    ("CORVIKNIGHT", "CORVIKNIGHTITE", "Corviknightite", "Corviknightita",
     (98, 127, 125, 53, 105, 87), ("FLYING", "STEEL"), "MIRROR_ARMOR", 750,
     ((72, 80, 128), (32, 32, 64), (216, 48, 48))),
    ("ORBEETLE", "ORBEETLITE", "Orbeetlite", "Orbeetlita",
     (70, 45, 120, 130, 140, 100), ("BUG", "PSYCHIC"), "PSYCHIC_SURGE", 408,
     ((208, 64, 56), (120, 32, 32), (88, 168, 232))),
    ("DREDNAW", "DREDNAWITE", "Drednawite", "Drednawita",
     (90, 145, 115, 48, 88, 99), ("WATER", "ROCK"), "STRONG_JAW", 1300,
     ((80, 168, 168), (40, 104, 112), (168, 120, 80))),
    ("COALOSSAL", "COALOSSALITE", "Coalossalite", "Coalossalita",
     (110, 80, 150, 120, 120, 30), ("ROCK", "FIRE"), "DROUGHT", 3300,
     ((96, 88, 88), (232, 112, 32), (248, 208, 64))),
    ("FLAPPLE", "FLAPPLITE", "Flapplite", "Flapplita",
     (70, 140, 90, 95, 70, 120), ("GRASS", "DRAGON"), "TOUGH_CLAWS", 20,
     ((224, 72, 64), (136, 32, 32), (120, 184, 72))),
    ("APPLETUN", "APPLETUNITE", "Appletunite", "Appletunita",
     (120, 85, 110, 130, 110, 30), ("GRASS", "DRAGON"), "THICK_FAT", 200,
     ((128, 184, 80), (64, 120, 48), (224, 72, 64))),
    ("SANDACONDA", "SANDACONDITE", "Sandacondite", "Sandacondita",
     (72, 137, 155, 65, 90, 91), ("GROUND",), "SAND_STREAM", 900,
     ((216, 184, 120), (152, 104, 56), (88, 64, 48))),
    ("TOXTRICITY_AMPED", "TOXTRICITITE", "Toxtricitite", "Toxtricitita",
     (75, 98, 80, 154, 90, 105), ("ELECTRIC", "POISON"), "PUNK_ROCK", 500,
     ((152, 104, 200), (80, 48, 128), (248, 224, 80))),
    ("TOXTRICITY_LOW_KEY", "TOXTRICITITE", "Toxtricitite", "Toxtricitita",
     (75, 98, 80, 154, 90, 105), ("ELECTRIC", "POISON"), "PUNK_ROCK", 500,
     ((152, 104, 200), (80, 48, 128), (248, 224, 80))),
    ("CENTISKORCH", "CENTISKORCHITE", "Centiskorchite", "Centiskorchita",
     (100, 145, 85, 90, 110, 95), ("FIRE", "BUG"), "STRONG_JAW", 1400,
     ((216, 80, 48), (136, 40, 32), (248, 168, 48))),
    ("HATTERENE", "HATTERENITE", "Hatterenite", "Hatterenita",
     (67, 90, 115, 176, 133, 29), ("PSYCHIC", "FAIRY"), "MAGIC_BOUNCE", 60,
     ((240, 168, 200), (200, 80, 136), (96, 152, 216))),
    ("GRIMMSNARL", "GRIMMSNARLITE", "Grimmsnarlite", "Grimmsnarlita",
     (95, 150, 85, 95, 105, 80), ("DARK", "FAIRY"), "PRANKSTER", 700,
     ((216, 96, 168), (64, 48, 88), (136, 192, 88))),
    ("ALCREMIE", "ALCREMITE", "Alcremite", "Alcremita",
     (75, 60, 95, 140, 141, 84), ("FAIRY",), "MISTY_SURGE", 10,
     ((248, 232, 216), (232, 120, 152), (120, 192, 136))),
    ("COPPERAJAH", "COPPERAJAHITE", "Copperajahite", "Copperajahita",
     (122, 160, 99, 80, 99, 40), ("STEEL",), "SHEER_FORCE", 7000,
     ((208, 120, 72), (136, 72, 40), (88, 184, 168))),
    ("DURALUDON", "DURALUDONITE", "Duraludonite", "Duraludonita",
     (70, 95, 135, 150, 70, 115), ("STEEL", "DRAGON"), "FILTER", 500,
     ((200, 208, 224), (64, 96, 160), (224, 64, 64))),
]

# Índices de la paleta de la Gengarita (graphics/items/icon_palettes/gengarite.pal)
ICONO_BASE = "gengarite"
BOLA = (5, 6, 10, 11)
ESPIRAL_1 = (2, 9)
ESPIRAL_2 = (3, 4, 7)

BAG_MEGAPIEDRAS = 130
INICIO_TEST = "#if TESTING // Dualocke: en los tests, la forma Gigamax de siempre"
INICIO_MEGA = "#else // Dualocke: megaevolución (tools/dualocke/megas_gigamax.py)"
FIN = "#endif // Dualocke: megaevolución"


def leer(ruta):
    with open(ruta, encoding="utf-8", newline="") as f:
        t = f.read()
    return t, ("\r\n" if "\r\n" in t else "\n")


def escribir(ruta, t):
    with open(ruta, "w", encoding="utf-8", newline="") as f:
        f.write(t)


def stats(d):
    hp, at, de, sa, sd, ve = d
    return [f".baseHP        = {hp},", f".baseAttack    = {at},", f".baseDefense   = {de},",
            f".baseSpeed     = {ve},", f".baseSpAttack  = {sa},", f".baseSpDefense = {sd},"]


def tipos(t):
    return f".types = MON_TYPES({', '.join('TYPE_' + x for x in t)}),"


def bloque(sangria, original, nuevo, salto):
    lineas = [INICIO_TEST] + original + [INICIO_MEGA] + [sangria + x for x in nuevo] + [FIN]
    return salto.join(lineas)


def formas():
    rutas = sorted(f"src/data/pokemon/species_info/{f}" for f in os.listdir("src/data/pokemon/species_info")
                   if re.match(r"gen_\d+_families\.h$", f))
    textos = {r: leer(r) for r in rutas}
    for (especie, _, _, _, st, ti, hab, peso, _) in DISENO:
        clave = f"[SPECIES_{especie}_GMAX] ="
        ruta = next(r for r, (t, _) in textos.items() if clave in t)
        t, salto = textos[ruta]
        i = t.index(clave)
        j = t.index(salto + "    }," + salto, i)
        cuerpo = t[i:j]
        lineas = cuerpo.split(salto)
        # Si ya se había aplicado, se vuelve a la forma original y se aplica otra vez
        k = 0
        limpias = []
        while k < len(lineas):
            if lineas[k] == INICIO_TEST:
                fin = lineas.index(INICIO_MEGA, k)
                limpias += lineas[k + 1:fin]
                k = lineas.index(FIN, fin) + 1
            else:
                limpias.append(lineas[k])
                k += 1
        lineas = limpias
        sangria = "        "
        nuevas = []
        k = 0
        while k < len(lineas):
            l = lineas[k].strip()
            if l.startswith("ALCREMIE_MISC_INFO("):
                color = re.search(r"\((\w+)\)", l).group(1)
                nuevo = stats(st) + [tipos(ti), ".catchRate = 100,", ".expYield = 173,",
                                     ".evYield_SpDefense = 2,", ".genderRatio = MON_FEMALE,",
                                     ".eggCycles = 20,", ".friendship = STANDARD_FRIENDSHIP,",
                                     ".growthRate = GROWTH_MEDIUM_FAST,",
                                     ".eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY, EGG_GROUP_AMORPHOUS),",
                                     f".abilities = {{ ABILITY_{hab}, ABILITY_{hab}, ABILITY_{hab} }},",
                                     f".bodyColor = {color},"]
                nuevas.append(bloque(sangria, [lineas[k]], nuevo, salto))
                k += 1
            elif l.startswith(".baseHP"):
                fin = k
                while not lineas[fin].strip().startswith(".types"):
                    assert lineas[fin].strip().startswith(".base"), (especie, lineas[fin])
                    fin += 1
                nuevas.append(bloque(sangria, lineas[k:fin + 1], stats(st) + [tipos(ti)], salto))
                k = fin + 1
            elif l.startswith(".abilities"):
                nuevas.append(bloque(sangria, [lineas[k]],
                                     [f".abilities = {{ ABILITY_{hab}, ABILITY_{hab}, ABILITY_{hab} }},"], salto))
                k += 1
            elif l.startswith(".weight"):
                nuevas.append(bloque(sangria, [lineas[k]], [f".weight = {peso},"], salto))
                k += 1
            elif l == ".isGigantamax = TRUE,":
                nuevas.append(bloque(sangria, [lineas[k]], [".isMegaEvolution = TRUE,"], salto))
                k += 1
            else:
                nuevas.append(lineas[k])
                k += 1
        nuevo = salto.join(nuevas)
        for marca in (".isMegaEvolution", ".weight = ", "ABILITY_" + hab):
            assert marca in nuevo, (especie, marca)
        textos[ruta] = (t[:i] + nuevo + t[j:], salto)
    for ruta, (t, _) in textos.items():
        escribir(ruta, t)


def cambios_de_forma():
    ruta = "src/data/pokemon/form_change_tables.h"
    t, salto = leer(ruta)
    for (especie, piedra, *_rest) in DISENO:
        destino = f"SPECIES_{especie}_GMAX"
        if f"FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM, {destino}," in t:
            continue
        patron = re.compile(r"#if P_GIGANTAMAX_FORMS" + re.escape(salto) +
                            r"(\s*\{FORM_CHANGE_BATTLE_GIGANTAMAX,\s*" + destino + r"\},)" + re.escape(salto) +
                            r"#endif")
        m = patron.search(t)
        assert m, destino
        sangria = re.match(r"\s*", m.group(1)).group(0)
        nuevo = salto.join([
            "#if P_GIGANTAMAX_FORMS && TESTING",
            m.group(1),
            "#elif P_GIGANTAMAX_FORMS // Dualocke: la forma Gigamax es su megaevolución (megas_gigamax.py)",
            f"{sangria}{{FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM, {destino}, ITEM_{piedra}}},",
            "#endif",
        ])
        t = t[:m.start()] + nuevo + t[m.end():]
    escribir(ruta, t)


def piedras():
    """Una vez por megapiedra (Toxtricity tiene dos formas y una piedra)."""
    vistas = {}
    for (especie, piedra, en, es, _, _, _, _, colores) in DISENO:
        if piedra not in vistas:
            vistas[piedra] = (especie, en, es, colores)
    return vistas


def nombre_pokemon(especie):
    return {"TOXTRICITY_AMPED": "Toxtricity", "TOXTRICITY_LOW_KEY": "Toxtricity"}.get(
        especie, especie.capitalize())


def objetos():
    vistas = piedras()
    # Constantes, al final (después de la última)
    ruta = "include/constants/items.h"
    t, salto = leer(ruta)
    ultima = max(int(n) for n in re.findall(r"^\s*ITEM_\w+ = (\d+),", t, re.M))
    nuevas = [p for p in vistas if not re.search(rf"^\s*ITEM_{p} = ", t, re.M)]
    if nuevas:
        lineas = [salto + "    // Dualocke: megapiedras de las formas Gigamax (tools/dualocke/megas_gigamax.py)"]
        for n, p in enumerate(nuevas, ultima + 1):
            lineas.append(f"    ITEM_{p} = {n},")
        a = salto + salto + "    ITEMS_COUNT,"
        assert t.count(a) == 1
        t = t.replace(a, salto.join(lineas) + a)
        escribir(ruta, t)

    # Datos del objeto, después de la última megapiedra de la expansion
    ruta = "src/data/items.h"
    t, salto = leer(ruta)
    entradas = []
    for p, (especie, en, es, _) in vistas.items():
        if f"[ITEM_{p}] =" in t:
            continue
        poke = nombre_pokemon(especie)
        camel = "".join(x.capitalize() for x in p.split("_"))
        entradas.append(salto.join([
            f"    [ITEM_{p}] =",
            "    {",
            f'        .name = ES(ITEM_NAME("{en}"), ITEM_NAME("{es}")),',
            "        .price = 0,",
            "        .holdEffect = HOLD_EFFECT_MEGA_STONE,",
            f'        .description = ES(COMPOUND_STRING("This stone enables\\n"',
            f'            "{poke} to Mega\\n"',
            f'            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\\n" "a {poke}.")),',
            "        .pocket = POCKET_MEGA_STONES,",
            "        .sortType = ITEM_TYPE_MEGA_STONE,",
            "        .type = ITEM_USE_BAG_MENU,",
            "        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,",
            "        .flingPower = 80,",
            f"        .iconPic = gItemIcon_{ICONO_BASE.capitalize()},",
            f"        .iconPalette = gItemIconPalette_{camel},",
            "    },",
        ]))
    if entradas:
        i = t.index("    [ITEM_GLIMMORANITE] =")
        j = t.index(salto + "    }," + salto, i) + len(salto + "    },")
        bloque_nuevo = salto + salto + "    // Dualocke: megapiedras de las formas Gigamax (tools/dualocke/megas_gigamax.py)" + \
            salto + (salto + salto).join(entradas)
        t = t[:j] + bloque_nuevo + t[j:]
        escribir(ruta, t)

    # Paletas: declaración y archivo
    for ruta, plantilla in (
            ("src/data/graphics/items.h",
             'const u16 gItemIconPalette_{c}[] = INCGFX_U16("graphics/items/icon_palettes/{f}.pal", ".gbapal");'),
            ("include/graphics.h", "extern const u16 gItemIconPalette_{c}[];")):
        t, salto = leer(ruta)
        nuevas = []
        for p in vistas:
            c = "".join(x.capitalize() for x in p.split("_"))
            linea = plantilla.format(c=c, f=p.lower())
            if linea not in t:
                nuevas.append(linea)
        if nuevas:
            ancla = next(l for l in t.split(salto) if "gItemIconPalette_Glimmoranite" in l)
            t = t.replace(ancla, ancla + salto + salto.join(
                ["// Dualocke: megapiedras de las formas Gigamax (tools/dualocke/megas_gigamax.py)"] + nuevas), 1)
            escribir(ruta, t)

    base = leer_paleta(f"graphics/items/icon_palettes/{ICONO_BASE}.pal")
    for p, (_, _, _, colores) in vistas.items():
        escribir_paleta(f"graphics/items/icon_palettes/{p.lower()}.pal", teñir(base, colores))


def leer_paleta(ruta):
    lineas = open(ruta, encoding="utf-8").read().split("\n")
    return [tuple(int(v) for v in l.split()) for l in lineas[3:19]]


def escribir_paleta(ruta, colores):
    texto = "JASC-PAL\r\n0100\r\n16\r\n" + "".join(f"{r} {g} {b}\r\n" for r, g, b in colores)
    with open(ruta, "w", encoding="utf-8", newline="") as f:
        f.write(texto)


def teñir(base, colores):
    """Cambia el tono y la saturación de cada grupo de la Gengarita por los del color que le toca,
    conservando la luz (así se mantienen los brillos y las sombras del dibujo)."""
    nueva = list(base)
    for grupo, objetivo in zip((BOLA, ESPIRAL_1, ESPIRAL_2), colores):
        h, l_obj, s = colorsys.rgb_to_hls(*(c / 255 for c in objetivo))
        luces = [colorsys.rgb_to_hls(*(c / 255 for c in base[i]))[1] for i in grupo]
        media = sum(luces) / len(luces)
        for i, luz in zip(grupo, luces):
            # La luz del color de destino, con las diferencias entre tonos del dibujo original
            l2 = min(0.95, max(0.08, l_obj + (luz - media)))
            r, g, b = colorsys.hls_to_rgb(h, l2, s)
            nueva[i] = tuple(int(round(v * 255 / 8)) * 8 for v in (r, g, b))
    return [tuple(min(248, v) for v in c) for c in nueva]


def bolsillo():
    ruta = "include/constants/global.h"
    t, _ = leer(ruta)
    t2 = re.sub(r"#define BAG_MEGASTONES_COUNT \d+\s*//[^\r\n]*",
                f"#define BAG_MEGASTONES_COUNT {BAG_MEGAPIEDRAS} // Dualocke: bolsillo MEGAPIEDRAS (caben todas, "
                "también las de las formas Gigamax)", t)
    escribir(ruta, t2)


def main():
    formas()
    cambios_de_forma()
    objetos()
    bolsillo()
    print(f"Dualocke: {len(DISENO)} formas Gigamax convertidas en megas, {len(piedras())} megapiedras")


if __name__ == "__main__":
    main()
