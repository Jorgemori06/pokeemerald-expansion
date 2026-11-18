#!/usr/bin/env python3
"""
Dualocke: la MARISMA AZULIZA, al oeste de PUEBLO AZULIZA (ZONAS.md, propuesta 6; rehecha el 17/11/2026
para que parezca diseñada como el juego original).

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_marisma_azuliza.py

**Cómo se dibuja.** El mapa se escribe abajo como un dibujo de letras (PLANO) y lo pinta autotile.py, que ha
aprendido de los mapas originales qué pieza va en cada sitio (orillas de estanque, bordes de arena…). Los
árboles grandes siguen las reglas de los del BOSQUE PETALIA y los pequeños, las de los árboles de AZULIZA. Al
final se comprueba que no haya parejas de piezas vecinas que el juego original no use nunca.

**El diseño** (inspirado en la RUTA 120, la de la lluvia y la hierba muy alta):
- **Este:** la franja de árboles y arena del borde oeste de AZULIZA, copiada tal cual (la unión se ve
  igual que el pueblo). Un camino de arena entra y se va convirtiendo en pradera.
- **Centro:** franjas de hierba muy alta y manchas de hierba alta, charcas, flores, rocas de GOLPE ROCA,
  grupos de árboles grandes y árboles pequeños sueltos. Dos entrenadores.
- **Oeste:** un lago grande para pescar y surfear. Al otro lado, cerrada por árboles, una cala a la que solo
  se llega con SURF: allí están **Dondozo y Tatsugiri** (se desbloquean más tarde: nivel del tramo 6).
- Siempre llueve. Conexión con AZULIZA: la fila 0 del pueblo es la fila 7 de la marisma.
"""

import json
import os
import re
import struct
import sys

sys.path.insert(0, "tools/dualocke")
import autotile as at  # noqa: E402
import colocar_objetos as co  # noqa: E402

CARPETA, MAPA, MAPSEC = "MarismaAzuliza", "MAP_MARISMA_AZULIZA", "MAPSEC_MARISMA_AZULIZA"
# Fila de la marisma que queda junto a la fila 0 de AZULIZA. Era 7, y la marisma sobresalía 7 filas por encima del
# pueblo, justo donde está la RUTA 106: desde AZULIZA se veía un muro de árboles sobre la playa (lo vio Miguel
# jugando, 18/11/2026). Con 0 no sobresale; la entrada sigue cayendo en la arena (filas 6-13 de AZULIZA).
DESPLAZAMIENTO_AZULIZA = 0
# D árbol pequeño (de AZULIZA, 1 de ancho)   T árbol grande (2 de ancho; columnas pares)
# E franja copiada del borde oeste de AZULIZA   . hierba   , hierba alta   ; hierba muy alta
# ~ agua   m agua de mar (charca de marea)
# (Sin hierba muy alta desde el 18/11/2026: con los gráficos de AZULIZA no tiene borde de abajo y quedaba cortada.)   s arena   * flores   c cartel   R risco (como el de la playa de la RUTA 104)   1 2 su escalera
PLANO = """
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTDDDDDDDDDDEEEE
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTDDDDDDDDDDEEEE
TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTDDDDDDDDDDEEEE
TTTTTTTT.........................RsssDDDDDDDEEEE
TTTTTTTT..,,,,,,...,,,,,,,,,.*...RssDsssssssEEEE
TTTTTTTT..,,,,,,...,,,,,,,,,..*..RssDsssssssEEEE
TTTTTTTT...........,,,,,,,,,.*...RssDsssssssEEEE
TTTTTTTT..~~~~~~...,,,,,,,,,.....RssssDDssssEEEE
TTTTTTTT~~~~~~~~~~............TT.RssssDDssssEEEE
TTTTTTTT~~~~~~~~~~~...........TT.RssssDDssssEEEE
TT....~~~~~~~~~~~~~~..,,,,,...TT.RsDDsssssssEEEE
TT....~~~~~~~~~~~~~~..,,,,,......RsDDsssssssEEEE
TT,,..~~~~~~~~~~~~~~~.,,,,,......RsDDscsssssEEEE
TT,,..~~~~~~~~~~~~~~~.,,,,,RR12RRRssssssssssEEEE
TT,,..~~~~~~~~~~~~~~..,,,,,RssssssssssssssssEEEE
TT,,..~~~~~~~~~~~~~...,,,,,RsssssssssmmmmsssEEEE
TT,,..~~~~~~~~~~~~~........RsssssssssmmmmsssEEEE
TT....~~~~~~~~~~~~~~.......RssDDsssssmmmmsssEEEE
TT....~~~~~~~~~~~~~~..TTTT.RssDDssssssssssssEEEE
TT*...~~~~~~~~~~~~~~~.TTTT.RssDDssssssssssssEEEE
TT*...~~~~~~~~~~~~~~~.TTTT.RssssssssssssssssEEEE
TT.*..~~~~~~~~~~~~~~.*TTTT.RsssssssssssssDDsEEEE
TT....~~~~~~~~~~~~~...TTTT.RsssssssDsssssDDsEEEE
TT.....~~~~~~~~~~~~.*......RsssssssDsssssDDsEEEE
TT......~~~~~~~~~~..,,,,,,.RsssssssDssssssssEEEE
TTTTTTTTTT~~~~~~~...,,,,,,.RsssssssssDssssssEEEE
TTTTTTTTTT.~~~~.....,,,,,,.RssssDDsssDssssssEEEE
TTTTTTTTTT....TT....,,,,,,.RssssDDsssDssssssEEEE
TTTTTTTTTT..*.TT....,,,,,,.RssssDDssssssssssEEEE
TTTTTTTTTT...*TT....,,,,,,.RssssssssssssssssEEEE
TT.........................RssssssssssDDDDDDEEEE
TTTTTTTTTTTTTTTTTTTTTTTTTTTTDDDDDDDDDDDDDDDDEEEE
TTTTTTTTTTTTTTTTTTTTTTTTTTTTDDDDDDDDDDDDDDDDEEEE
TTTTTTTTTTTTTTTTTTTTTTTTTTTTDDDDDDDDDDDDDDDDEEEE
"""
TERRENO = {".": "suelo", "*": "suelo", "c": "suelo", ",": "hierba_alta", ";": "hierba_larga", "~": "estanque",
           "s": "arena", "m": "mar", "R": "risco", "1": "risco", "2": "risco"}
FLORES, CARTEL = 0x004, 0x003
# Árbol pequeño de AZULIZA: copa (se pasa por detrás), cuerpo y base
D_COPA, D_CUERPO, D_BASE = 0x239, 0x243, 0x23A
# Los árboles grandes (T) los pone autotile.arboles_grandes(), con las reglas del BOSQUE PETALIA

# Personajes y cosas (x, y)
TOMAS = (21, 3, "DOWN", 4)
MARGARITA = (32, 5, "LEFT", 3)
ROCAS = [(27, 12), (36, 20), (16, 30), (31, 23)]
DONDOZO = (4, 11, "SPECIES_DONDOZO", "ITEM_ROCKY_HELMET", "FLAG_DUALOCKE_MARISMA_DONDOZO", "VAR_0")
TATSUGIRI = (4, 19, "SPECIES_TATSUGIRI", "ITEM_MYSTIC_WATER", "FLAG_DUALOCKE_MARISMA_TATSUGIRI", "VAR_1")
NIVEL_INICIAL = 59


def leer(ruta):
    with open(ruta, encoding="utf-8", newline="") as f:
        return f.read()


def escribir(ruta, texto):
    with open(ruta, "w", encoding="utf-8", newline="") as f:
        f.write(texto)


LAYOUTS = co.cargar_layouts()


def celdas_de(carpeta):
    l = LAYOUTS[json.loads(leer(f"data/maps/{carpeta}/map.json"))["layout"]]
    return l, list(struct.unpack(f"<{l['width'] * l['height']}H", open(l["blockdata_filepath"], "rb").read()))


def valor_de_mapa(carpeta, metatile, colision):
    """El valor más común de un metatile en un mapa, con o sin colisión."""
    _, c = celdas_de(carpeta)
    vs = [v for v in c if v & 0x3FF == metatile and bool((v >> 10) & 3) == colision]
    return max(set(vs), key=vs.count)


def pintar(plano, aprendiz):
    filas = plano.strip().splitlines()
    alto, ancho = len(filas), len(filas[0])
    assert all(len(f) == ancho for f in filas), "las filas del plano no miden lo mismo"
    rejilla = [[TERRENO.get(ch) for ch in f] for f in filas]
    pintadas = aprendiz.pintar(rejilla)
    valor = lambda m: aprendiz.valor.get(m, m)  # noqa: E731
    c = [0] * (ancho * alto)
    es = lambda x, y, ch: 0 <= x < ancho and 0 <= y < alto and filas[y][x] == ch  # noqa: E731
    # Franja de AZULIZA: su columna 0, fila a fila; arriba y abajo, árbol
    _, cd = celdas_de("DewfordTown")
    wd = LAYOUTS[json.loads(leer("data/maps/DewfordTown/map.json"))["layout"]]["width"]
    cuerpo_d = valor_de_mapa("DewfordTown", D_CUERPO, True)
    copa_d = valor_de_mapa("DewfordTown", D_COPA, False)
    base_d = valor_de_mapa("DewfordTown", D_BASE, True)
    fallos = []
    for y in range(alto):
        for x in range(ancho):
            ch = filas[y][x]
            if ch == "E":
                fd = y - DESPLAZAMIENTO_AZULIZA
                c[y * ancho + x] = cd[fd * wd] if 0 <= fd < 20 else cuerpo_d
            elif ch == "D":
                arriba, abajo = es(x, y - 1, "D") or y == 0, es(x, y + 1, "D") or y == alto - 1
                if not arriba and not abajo:
                    fallos.append(f"árbol pequeño de una sola casilla en {(x, y)}")
                c[y * ancho + x] = copa_d if not arriba else base_d if not abajo else cuerpo_d
            elif ch == "T":
                continue
            else:
                v = pintadas[y][x]
                if ch == "*":
                    v = (v & ~0x3FF) | FLORES
                elif ch == "c":
                    v = valor(CARTEL)
                elif ch in "12":
                    v = valor(at.ESCALERA_RISCO[int(ch) - 1])
                c[y * ancho + x] = v
    # Árboles grandes: por parejas de columnas, con las reglas del BOSQUE PETALIA (autotile.py)
    fallos += at.arboles_grandes(filas, c, valor)
    assert not fallos, "; ".join(fallos)
    assert all(c), "casillas sin pintar"
    return c, ancho, alto


def guardar_layout(c, ancho, alto, base):
    os.makedirs(f"data/layouts/{CARPETA}", exist_ok=True)
    with open(f"data/layouts/{CARPETA}/map.bin", "wb") as f:
        f.write(struct.pack(f"<{ancho * alto}H", *c))
    with open(base["border_filepath"], "rb") as f, open(f"data/layouts/{CARPETA}/border.bin", "wb") as g:
        g.write(f.read())
    ident = "LAYOUT_" + MAPA[4:]
    texto = leer("data/layouts/layouts.json")
    if f'"{ident}"' not in texto:
        texto = co.insertar_en_lista(texto, "layouts", {
            "id": ident, "name": f"{CARPETA}_Layout", "width": ancho, "height": alto,
            "primary_tileset": base["primary_tileset"], "secondary_tileset": base["secondary_tileset"],
            "border_filepath": f"data/layouts/{CARPETA}/border.bin",
            "blockdata_filepath": f"data/layouts/{CARPETA}/map.bin"})
    else:   # el tamaño puede haber cambiado
        i = texto.index(f'"id": "{ident}"')
        j = texto.index("}", i)
        trozo = re.sub(r'"width": \d+', f'"width": {ancho}', texto[i:j])
        trozo = re.sub(r'"height": \d+', f'"height": {alto}', trozo)
        texto = texto[:i] + trozo + texto[j:]
    json.loads(texto)
    escribir("data/layouts/layouts.json", texto)
    return ident


def persona(gfx, x, y, mira, script, vista=0, tipo="TRAINER_TYPE_NONE", flag="0", local=None):
    o = {"graphics_id": gfx, "x": x, "y": y, "elevation": 3, "movement_type": f"MOVEMENT_TYPE_FACE_{mira}",
         "movement_range_x": 0, "movement_range_y": 0, "trainer_type": tipo,
         "trainer_sight_or_berry_tree_id": str(vista), "script": script, "flag": flag}
    if local:
        o = {"local_id": local, **o}
    return o


def crear_mapa(layout):
    ruta = f"data/maps/{CARPETA}/map.json"
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    objetos = [
        persona("OBJ_EVENT_GFX_FISHERMAN", TOMAS[0], TOMAS[1], TOMAS[2], f"{CARPETA}_EventScript_Tomas", TOMAS[3],
                "TRAINER_TYPE_NORMAL"),
        persona("OBJ_EVENT_GFX_WOMAN_2", MARGARITA[0], MARGARITA[1], MARGARITA[2], f"{CARPETA}_EventScript_Margarita",
                MARGARITA[3], "TRAINER_TYPE_NORMAL"),
    ]
    for i, (x, y) in enumerate(ROCAS):
        o = persona("OBJ_EVENT_GFX_BREAKABLE_ROCK", x, y, "DOWN", "EventScript_RockSmash", flag=f"FLAG_TEMP_{11 + i}")
        o["movement_type"] = "MOVEMENT_TYPE_LOOK_AROUND"
        objetos.append(o)
    for x, y, especie, _, flag, var in (DONDOZO, TATSUGIRI):
        nombre = especie[8:].capitalize()
        objetos.append(persona(f"OBJ_EVENT_GFX_{var}", x, y, "RIGHT", f"{CARPETA}_EventScript_{nombre}", flag=flag,
                               local=f"LOCALID_MARISMA_AZULIZA_{especie[8:]}"))
    cartel = next((x, y) for y, f in enumerate(PLANO.strip().splitlines()) for x, ch in enumerate(f) if ch == "c")
    escribir(ruta, json.dumps({
        "id": MAPA, "name": CARPETA, "layout": layout, "music": "MUS_ROUTE119", "region": "REGION_HOENN",
        "region_map_section": MAPSEC, "requires_flash": False, "weather": "WEATHER_RAIN",
        "map_type": "MAP_TYPE_ROUTE", "allow_cycling": True, "allow_escaping": False, "allow_running": True,
        "show_map_name": True, "battle_scene": "MAP_BATTLE_SCENE_NORMAL",
        "connections": [{"map": "MAP_DEWFORD_TOWN", "offset": DESPLAZAMIENTO_AZULIZA, "direction": "right"}],
        "object_events": objetos + [o for o in anteriores.get("object_events", [])
                                    if str(o.get("flag", "")).startswith("FLAG_ITEM_")],
        "warp_events": [], "coord_events": [],
        "bg_events": [{"type": "sign", "x": cartel[0], "y": cartel[1], "elevation": 0,
                       "player_facing_dir": "BG_EVENT_PLAYER_FACING_NORTH",
                       "script": f"{CARPETA}_EventScript_Cartel"}]
                     + [b for b in anteriores.get("bg_events", []) if b.get("type") == "hidden_item"],
    }, indent=2, ensure_ascii=False) + "\n")

    ruta = f"data/maps/{CARPETA}/scripts.inc"
    nivel = NIVEL_INICIAL
    if os.path.exists(ruta):
        m = re.search(r"setwildbattle SPECIES_DONDOZO, (\d+)", leer(ruta))
        nivel = int(m.group(1)) if m else nivel
    escribir(ruta, scripts(nivel))

    grupos = leer("data/maps/map_groups.json")
    d = json.loads(grupos)
    grupo = next(g for g in d["group_order"] if "DewfordTown" in d[g])
    if f'"{CARPETA}"' not in grupos:
        salto = "\r\n" if "\r\n" in grupos else "\n"
        ultimo = d[grupo][-1]
        a = f'"{ultimo}"{salto}'
        i = grupos.index(a, grupos.index(f'"{grupo}": ['))
        grupos = grupos[:i] + f'"{ultimo}",{salto}    "{CARPETA}"{salto}' + grupos[i + len(a):]
        json.loads(grupos)
        escribir("data/maps/map_groups.json", grupos)

    # AZULIZA: la conexión con la marisma, con el desplazamiento nuevo
    ruta = "data/maps/DewfordTown/map.json"
    texto = leer(ruta)
    if MAPA not in texto:
        texto = co.insertar_en_lista(texto, "connections", {"map": MAPA, "offset": -DESPLAZAMIENTO_AZULIZA,
                                                            "direction": "left"})
    else:
        texto = re.sub(r'("map": "MAP_MARISMA_AZULIZA",\s*"offset": )-?\d+', rf"\g<1>{-DESPLAZAMIENTO_AZULIZA}", texto)
    json.loads(texto)
    escribir(ruta, texto)

    ruta = "src/data/region_map/region_map_sections.json"
    texto = leer(ruta)
    if f'"{MAPSEC}"' not in texto:
        dewford = next(s for s in json.loads(texto)["map_sections"] if s["id"] == "MAPSEC_DEWFORD_TOWN")
        texto = co.insertar_en_lista(texto, "map_sections", {"id": MAPSEC, "name": "MARISMA AZULIZA",
                                                             "x": dewford["x"] - 1, "y": dewford["y"],
                                                             "width": 1, "height": 1})
        json.loads(texto)
        escribir(ruta, texto)


def estatico(especie, premio, flag, nombre):
    return f"""
{CARPETA}_EventScript_{nombre}::
	lock
	setvar VAR_TEMP_8, {especie}
	setvar VAR_TEMP_9, {premio}
	call Dualocke_EventScript_AvisoIsla
	setwildbattle {especie}, {{nivel}}
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, {CARPETA}_EventScript_PokemonSigue
	setflag {flag}
	call Dualocke_EventScript_PremioIsla
	release
	end
"""


def scripts(nivel):
    cuerpo = f"""{CARPETA}_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, {CARPETA}_OnTransition
	.byte 0

@ Dualocke: la MARISMA AZULIZA, al oeste de PUEBLO AZULIZA (tools/dualocke/crear_marisma_azuliza.py).
@ Dondozo y Tatsugiri están en la cala del otro lado del lago: hace falta SURF. Son Pokémon fuertes que se
@ pueden capturar, como los de las islas del ferry (data/scripts/dualocke_islas.inc); con semilla salen otros.
{CARPETA}_OnTransition:
	setvar VAR_0x8004, {DONDOZO[2]}
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	setvar VAR_0x8004, {TATSUGIRI[2]}
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_1, VAR_RESULT
	end
""" + estatico(DONDOZO[2], DONDOZO[3], DONDOZO[4], "Dondozo") + estatico(
        TATSUGIRI[2], TATSUGIRI[3], TATSUGIRI[4], "Tatsugiri") + f"""
{CARPETA}_EventScript_PokemonSigue::
	release
	end

{CARPETA}_EventScript_Cartel::
	msgbox {CARPETA}_Text_Cartel, MSGBOX_SIGN
	end

{CARPETA}_EventScript_Tomas::
	trainerbattle_single TRAINER_TOMAS, {CARPETA}_Text_TomasIntro, {CARPETA}_Text_TomasDefeat
	msgbox {CARPETA}_Text_TomasPostBattle, MSGBOX_AUTOCLOSE
	end

{CARPETA}_EventScript_Margarita::
	trainerbattle_single TRAINER_MARGARITA, {CARPETA}_Text_MargaritaIntro, {CARPETA}_Text_MargaritaDefeat
	msgbox {CARPETA}_Text_MargaritaPostBattle, MSGBOX_AUTOCLOSE
	end

{CARPETA}_Text_Cartel:
	.string "MARISMA AZULIZA\\n"
	.string "Aquí siempre llueve. ¡No te mojes!$"

{CARPETA}_Text_TomasIntro:
	.string "¡Shh! Que se me espantan los peces.\\n"
	.string "Bueno, ya que estás… ¡combate!$"

{CARPETA}_Text_TomasDefeat:
	.string "Hoy no pican ni los combates…$"

{CARPETA}_Text_TomasPostBattle:
	.string "Al otro lado del lago vive un\\n"
	.string "POKéMON enorme. Sin SURF, ni lo veas.$"

{CARPETA}_Text_MargaritaIntro:
	.string "Con la lluvia, las flores huelen\\n"
	.string "mejor. ¿Lo notas?$"

{CARPETA}_Text_MargaritaDefeat:
	.string "Qué combate tan fresco.$"

{CARPETA}_Text_MargaritaPostBattle:
	.string "En la hierba muy alta se esconden\\n"
	.string "muchos POKéMON de pantano.$"
"""
    return cuerpo.replace("{nivel}", str(nivel))


def main():
    aprendiz = at.Aprendiz()
    c, ancho, alto = pintar(PLANO, aprendiz)
    base = LAYOUTS[json.loads(leer("data/maps/DewfordTown/map.json"))["layout"]]
    crear_mapa(guardar_layout(c, ancho, alto, base))
    raras = aprendiz.revisar(c, ancho, alto, base["secondary_tileset"])
    print(f"Dualocke: MARISMA AZULIZA creada ({ancho} × {alto}); parejas de piezas que el juego no usa: {len(raras)}")
    return raras


if __name__ == "__main__":
    for x, y, d, a, b in main()[:40]:
        print(f"  {(x, y)} {'→' if d == 'h' else '↓'} {a:03x} {b:03x}")
