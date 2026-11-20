#!/usr/bin/env python3
"""
Dualocke: la PLAYA VOLCÁNICA, al oeste del MONTE PÍRICO (ZONAS.md, propuesta 10). Rehecha el 17/11/2026 para
que pareciera diseñada como el juego original, y otra vez el 20/11/2026 con ceniza (Miguel: "más que la
piedra rojiza que forma la playa, un paisaje donde se mezcle la playa con una zona de ceniza, como la ruta
de arriba del volcán").

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_playa_volcanica.py

**Cómo se dibuja.** El mapa es un dibujo de letras (PLANO). La arena, el bajío y el mar los pinta autotile.py
con las piezas generales que ha aprendido de los mapas originales. La ceniza usa las piezas de la RUTA 113
(gráficos de PARDA, `gTileset_Fallarbor`), puestas como allí:
- **Suelo de ceniza** (0x218) y **hierba con ceniza** (0x20A): sin bordes, como en la RUTA 113. La hierba
  tiene salvajes y, al pisarla, se le cae la ceniza (como en la RUTA 113: `STEP_CB_ASH`; con el Saco Hollín
  se recoge).
- **Árboles con ceniza:** cada árbol ocupa dos columnas (la de la izquierda, impar). Las filas del bosque
  alternan "arriba" (0x275/0x276) y "abajo" (0x26D/0x26E); encima del bosque va la copa sobre la ceniza
  (0x204/0x205, se pasa por debajo) y debajo, el pie (0x20C/0x20D). A los lados, igual: junto a una fila de
  "abajo" va una copa y junto a una de "arriba", un pie. `bosque()` lo hace solo.
- **Saltos** (0x21B-0x21D): separan la meseta de ceniza de la playa de abajo. Se bajan, no se suben.
- **Rocas** (0x219).
La ceniza toca la arena directamente: es la mezcla de playa y ceniza que pidió Miguel. Nunca toca el agua.

**El diseño:** la meseta de ceniza al noroeste, con hierba con ceniza y rocas; la playa al este, a lo largo
del mar, y, bajando los saltos, una playa ancha al sur con manchas de ceniza. Bosque con ceniza en los bordes
de tierra y rocas de mar en los del mar. **Sol** (sol normal, sin sol en combate; Miguel, 20/11/2026). Guardián
en la playa y un vecino junto al mar. **Tramo 7.**

**La unión con la RUTA 122** (gráficos General + Algaria). Una conexión entre mapas de gráficos distintos solo
se ve bien si lo que se ve del otro mapa son gráficos generales:
- Se cruza por arriba (filas 2-7), donde el borde de la RUTA 122 solo tiene mar y rocas generales. En la
  RUTA 122 se quita una roca del anillo (x 5-6, filas 4-5) para poder salir por ahí.
- Las 8 columnas del este de la playa son solo mar y rocas generales, y desde la fila 8 un arrecife no deja
  acercarse al borde (desde ahí se vería la orilla del monte, que es de Algaria). El script lo comprueba.
"""

import json
import os
import re
import struct
import sys

sys.path.insert(0, "tools/dualocke")
import autotile as at  # noqa: E402
import colocar_objetos as co  # noqa: E402

PLAYA, MAPA, MAPSEC = "PlayaVolcanica", "MAP_PLAYA_VOLCANICA", "MAPSEC_PLAYA_VOLCANICA"
SECUNDARIO = "gTileset_Fallarbor"
ROCA_RUTA122 = (5, 4)                     # la roca (2 × 2) que se quita del anillo de la RUTA 122
FILAS_CRUCE = 8                           # filas 0-7: por aquí se pasa de un mapa a otro
BANDA_GENERAL = 8                         # las últimas 8 columnas, solo gráficos generales
ROCA = (0x175, 0x176, 0x17D, 0x17E)      # roca de mar (general): arriba izq., arriba der., abajo izq., abajo der.
# F bosque con ceniza   . ceniza   , hierba con ceniza   o roca   _ salto (se baja hacia el sur)
# s arena   b bajío   m mar   X roca de mar (2 × 2)
PLANO = """
FFFFFFFFFFFFFFFFFFFFFFF.XXXXXXXXXXXXXXXX
FFFFFFFFFFFFFFFFFFFFFFF.XXXXXXXXXXXXXXXX
FFF.....................ssbbmmmmmmmmmmmm
FFF......,,,,,,,.......sssbbmmmmmmmmmmmm
FFF......,,,,,,,......ssssbbmmmmmmmmmmmm
FFF......,,,,,,,......ssssbbmmmmmmmmmmmm
FFF...o...............ssssbbmmmmmmmmmmmm
FFF..............o....ssssbbmmmmmmmmmmmm
FFF.,,,,,............sssssbbmmmmmmmmmmXX
FFF.,,,,,....,,,,....sssssbbmmmmmmmmmmXX
FFF.,,,,,....,,,,....sssssbbmmmmmmmmmmXX
FFF.,,,,,....,,,,....ssssbbmmmmmmmmmmmXX
FFF..........,,,,....ssssbbmmmmmmmmmmmXX
FFF..o...............ssssbbmmmmmmXXmmmXX
FFF..................ssssbbmmmmmmXXmmmXX
FFF.____________.....ssssbbmmmmmmmmmmmXX
FFF.ssssssssssss.,,,.ssssbbmmmmmmmmmmmXX
FFF.ssssssssssss.,,,.ssssbbmmmmmmmmmmmXX
FFF.ssssssssssss.,,,.ssssbbmmmmmmmmmmmXX
FFF.sssssssssssss...sssssbbmmmmmmmmmmmXX
FFF.sssss..ssssssssssssssbbmmmmmmmmmmmXX
FFF.ssss.,,.sssssssssssssbbmmmmmmmmmmmXX
FFF.ssss.,,,.ssssssssssssbbmmmmmmmXXmmXX
FFF.sssss...ssssssssssssssbbmmmmmmXXmmXX
FFF.ssssssssssssss...sssssbbmmmmmmmmmmXX
FFF.sssssssssssss.,,,.ssssbbmmmmmmmmmmXX
FFF..ssssssssssss.,,,.ssssbbmmmmmmmmmmXX
FFF..ssssssssssss.,,o.ssssbbmmmmmmmmmmXX
FFF..sssssssssssss...sssssbbmmmmmmmmmmXX
FFF.,,ssssssssssssssssssssbbmmmmmmmmmmXX
FFF.,,ssssssssssssssssssssbbmmmmmXXmmmXX
FFF.,,,sssssssssssssssssssbbmmmmmXXmmmXX
FFF.,,,sssssssssssssssssssbbmmmmmmmmmmXX
FFF..,,,sssssssssssssssssbbmmmmmmmmmmmXX
FFF....ssssssssssssssssssbbmmmmmmmmmmmXX
FFF.....sssssssssssssssssbbmmmmmmmmmmmXX
FFF......ssssssssssssssssbbmmmmmmmmmmmXX
FFF.....................sssbbmmmmmmmmmXX
FFFFFFFFFFFFFFFFFFFFFFF.XXXXXXXXXXXXXXXX
FFFFFFFFFFFFFFFFFFFFFFF.XXXXXXXXXXXXXXXX
"""
TERRENO = {"s": "arena", "b": "bajio", "m": "mar", "X": "mar"}
CENIZA = "F.,o_"                       # lo que es ceniza (para autotile, arena: la arena de al lado va lisa)
# Piezas de la RUTA 113 con su valor de allí (colisión y altura): (par, impar) según la columna
SUELO, HIERBA, PENA = 0x3218, 0x320A, 0x0619
SALTO = (0x061B, 0x061C, 0x061D)       # extremo izquierdo, medio, extremo derecho
COPA, PIE = (0x3204, 0x3205), (0x060C, 0x060D)
ARRIBA, ABAJO = (0x0675, 0x0676), (0x066D, 0x066E)
GUARDIAN = (14, 27, "SPECIES_SLITHER_WING", 70, "ITEM_BOOSTER_ENERGY", "FLAG_DUALOCKE_GUARDIAN_PLAYA")
VECINO = (24, 4)                       # en la arena de arriba, junto al mar
SITIO_OBJETOS = {
    "FLAG_ITEM_PLAYA_WATER_STONE": (5, 18),            # en la playa de abajo, junto al bosque
    "FLAG_ITEM_PLAYA_DAMP_ROCK": (5, 6),               # en la meseta, junto a la roca
    "FLAG_ITEM_PLAYA_PEARL": (22, 35),                 # oculta, en la arena del sur
    "FLAG_ITEM_TICKET_PLAYA_VOLCANICA": (19, 27),      # en la mancha de ceniza, junto a la roca
}


def leer(ruta):
    with open(ruta, encoding="utf-8", newline="") as f:
        return f.read()


def escribir(ruta, texto):
    with open(ruta, "w", encoding="utf-8", newline="") as f:
        f.write(texto)


def con_nivel_actual(ruta, texto):
    """Conserva el nivel del guardián que haya puesto reescalar_niveles.py (regla "tope") si el script ya
    existe: si no, al volver a lanzar este script después de la cadena de niveles se perdería."""
    if os.path.exists(ruta):
        anterior = re.search(r"setwildbattle (SPECIES_\w+), (\d+)", leer(ruta))
        if anterior:
            texto = re.sub(r"setwildbattle (SPECIES_\w+), \d+", rf"setwildbattle \1, {anterior.group(2)}", texto)
    return texto


LAYOUTS = co.cargar_layouts()


def celdas_de(carpeta):
    l = LAYOUTS[json.loads(leer(f"data/maps/{carpeta}/map.json"))["layout"]]
    return l, list(struct.unpack(f"<{l['width'] * l['height']}H", open(l["blockdata_filepath"], "rb").read()))


def bosque(filas):
    """{(x, y): valor} de los árboles con ceniza y lo que va a su alrededor (copas y pies).

    Las filas pares del bosque son "arriba" y las impares, "abajo" (así, el bosque de arriba, de las filas
    0-1, y el de abajo, de las 38-39, acaban bien). Un bosque tiene que acabar por abajo en una fila de
    "abajo" (impar), empezar por arriba en una de "arriba" (par) y, a los lados, ir de una columna impar a
    una par, salvo en el borde del mapa."""
    alto, ancho = len(filas), len(filas[0])
    es = lambda x, y: 0 <= x < ancho and 0 <= y < alto and filas[y][x] == "F"  # noqa: E731
    tipo = lambda y: ARRIBA if y % 2 == 0 else ABAJO  # noqa: E731
    piezas = {}
    for y in range(alto):
        for x in range(ancho):
            if es(x, y):
                assert es(x, y + 1) or y == alto - 1 or y % 2 == 1, ("el bosque acaba en una fila de arriba", x, y)
                assert es(x, y - 1) or y == 0 or y % 2 == 0, ("el bosque empieza en una fila de abajo", x, y)
                assert es(x - 1, y) or x == 0 or x % 2 == 1, ("el bosque empieza en una columna par", x, y)
                assert es(x + 1, y) or x == ancho - 1 or x % 2 == 0, ("el bosque acaba en una columna impar", x, y)
                piezas[(x, y)] = tipo(y)[x % 2]
                continue
            if es(x, y + 1):
                piezas[(x, y)] = COPA[x % 2]
            elif es(x, y - 1):
                piezas[(x, y)] = PIE[x % 2]
            elif es(x - 1, y) or es(x + 1, y):
                piezas[(x, y)] = (COPA if tipo(y) == ABAJO else PIE)[x % 2]
            else:
                continue
            assert filas[y][x] in CENIZA, ("al lado del bosque tiene que haber ceniza", x, y)
    return piezas


def crear_layout():
    aprendiz = at.Aprendiz()
    filas = PLANO.strip().splitlines()
    alto, ancho = len(filas), len(filas[0])
    assert all(len(f) == ancho for f in filas), "las filas del plano no miden lo mismo"
    pintadas = aprendiz.pintar([[TERRENO.get(ch, "arena") for ch in f] for f in filas])
    arboles = bosque(filas)
    c = [0] * (ancho * alto)
    _, c122 = celdas_de("Route122")
    roca = {}
    for m in ROCA:   # el valor de la roca de mar, tal como está en la RUTA 122 (con colisión)
        roca[m] = next(v for v in c122 if v & 0x3FF == m and (v >> 10) & 3)
    for y in range(alto):
        for x in range(ancho):
            ch = filas[y][x]
            if (x, y) in arboles:
                v = arboles[(x, y)]
            elif ch == "X":
                # Cada roca es de 2 × 2: la esquina de arriba a la izquierda es la primera X de su grupo
                x0 = x
                while x0 > 0 and filas[y][x0 - 1] == "X":
                    x0 -= 1
                y0 = y
                while y0 > 0 and filas[y0 - 1][x] == "X":
                    y0 -= 1
                v = roca[ROCA[((y - y0) % 2) * 2 + (x - x0) % 2]]
            elif ch == ".":
                v = SUELO
            elif ch == ",":
                v = HIERBA
            elif ch == "o":
                v = PENA
            elif ch == "_":
                izq, der = filas[y][x - 1] == "_", filas[y][x + 1] == "_"
                assert filas[y - 1][x] in ".,o" and filas[y][x - 1] in "._" and filas[y][x + 1] in "._", \
                    ("el salto tiene que tener ceniza arriba y a los lados", x, y)
                v = SALTO[1] if izq and der else SALTO[0] if der else SALTO[2]
            else:
                v = pintadas[y][x]
            # La ceniza nunca toca el agua (no hay piezas de orilla para ella)
            if ch in CENIZA:
                assert all(filas[yy][xx] not in "bm" for yy in range(max(0, y - 1), min(alto, y + 2))
                           for xx in range(max(0, x - 1), min(ancho, x + 2))), ("ceniza junto al agua", x, y)
            c[y * ancho + x] = v
    assert all(c), "casillas sin pintar"
    # La banda del este (la que se ve desde la RUTA 122) solo tiene gráficos generales
    assert all(c[y * ancho + x] & 0x3FF < 0x200 for y in range(alto) for x in range(ancho - BANDA_GENERAL, ancho))
    for donde in [GUARDIAN[:2], VECINO] + list(SITIO_OBJETOS.values()):
        x, y = donde
        assert not (c[y * ancho + x] >> 10) & 3 and (x, y) not in arboles, ("objeto o persona fuera del suelo", donde)

    # Borde de árboles con ceniza, el de la RUTA 113
    base = LAYOUTS[json.loads(leer("data/maps/Route113/map.json"))["layout"]]
    os.makedirs(f"data/layouts/{PLAYA}", exist_ok=True)
    with open(f"data/layouts/{PLAYA}/map.bin", "wb") as f:
        f.write(struct.pack(f"<{ancho * alto}H", *c))
    with open(base["border_filepath"], "rb") as f, open(f"data/layouts/{PLAYA}/border.bin", "wb") as g:
        g.write(f.read())
    ident = "LAYOUT_" + MAPA[4:]
    texto = leer("data/layouts/layouts.json")
    if f'"{ident}"' not in texto:
        texto = co.insertar_en_lista(texto, "layouts", {
            "id": ident, "name": f"{PLAYA}_Layout", "width": ancho, "height": alto,
            "primary_tileset": "gTileset_General", "secondary_tileset": SECUNDARIO,
            "border_filepath": f"data/layouts/{PLAYA}/border.bin",
            "blockdata_filepath": f"data/layouts/{PLAYA}/map.bin"})
    else:
        # Antes era de LAVACALDA (las termas): se cambia solo el secundario de esta entrada
        i = texto.index(f'"{ident}"')
        j = texto.index("}", i)
        texto = texto[:i] + re.sub(r'("secondary_tileset":\s*")\w+(")', rf"\g<1>{SECUNDARIO}\2", texto[i:j]) + texto[j:]
    json.loads(texto)
    escribir("data/layouts/layouts.json", texto)
    raras = aprendiz.revisar(c, ancho, alto, SECUNDARIO)
    print(f"Dualocke: PLAYA VOLCÁNICA: parejas de piezas que el juego no usa: {len(raras)}")
    return ident


def ruta122():
    """Quita la roca del anillo de la RUTA 122 y la conecta con la playa."""
    l, c = celdas_de("Route122")
    w = l["width"]
    mar = c[0]
    assert mar & 0x3FF == 0x170
    rx, ry = ROCA_RUTA122
    for dy in range(2):
        for dx in range(2):
            assert c[(ry + dy) * w + rx + dx] & 0x3FF in ROCA + (0x170,), "ahí no está la roca"
            c[(ry + dy) * w + rx + dx] = mar
    # La parte de la RUTA 122 que se ve desde el cruce (filas 0-12, x 0-7) solo tiene gráficos generales
    assert all(c[y * w + x] & 0x3FF < 0x200 for y in range(FILAS_CRUCE + 5) for x in range(BANDA_GENERAL))
    with open(l["blockdata_filepath"], "wb") as f:
        f.write(struct.pack(f"<{w * l['height']}H", *c))
    ruta = "data/maps/Route122/map.json"
    texto = leer(ruta)
    if MAPA not in texto:
        texto = co.insertar_en_lista(texto, "connections", {"map": MAPA, "offset": 0, "direction": "left"})
        json.loads(texto)
        escribir(ruta, texto)


def crear_mapa(layout):
    ruta = f"data/maps/{PLAYA}/map.json"
    os.makedirs(f"data/maps/{PLAYA}", exist_ok=True)
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    gx, gy, _, _, _, flag = GUARDIAN
    objetos = [
        {"local_id": "LOCALID_PLAYA_VOLCANICA_GUARDIAN", "graphics_id": "OBJ_EVENT_GFX_VAR_0", "x": gx, "y": gy,
         "elevation": 3, "movement_type": "MOVEMENT_TYPE_FACE_DOWN", "movement_range_x": 0, "movement_range_y": 0,
         "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
         "script": f"{PLAYA}_EventScript_Pokemon", "flag": flag},
        {"graphics_id": "OBJ_EVENT_GFX_OLD_MAN_1", "x": VECINO[0], "y": VECINO[1], "elevation": 3,
         "movement_type": "MOVEMENT_TYPE_FACE_RIGHT", "movement_range_x": 0, "movement_range_y": 0,
         "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
         "script": f"{PLAYA}_EventScript_Vecino", "flag": "0"}]
    datos = {
        "id": MAPA, "name": PLAYA, "layout": layout, "music": "MUS_ROUTE119", "region": "REGION_HOENN",
        "region_map_section": MAPSEC, "requires_flash": False, "weather": "WEATHER_SUNNY",
        "map_type": "MAP_TYPE_ROUTE", "allow_cycling": True, "allow_escaping": False, "allow_running": True,
        "show_map_name": True, "battle_scene": "MAP_BATTLE_SCENE_NORMAL",
        "connections": [{"map": "MAP_ROUTE122", "offset": 0, "direction": "right"}],
        "object_events": objetos + [o for o in anteriores.get("object_events", [])
                                    if str(o.get("flag", "")).startswith("FLAG_ITEM_")],
        "warp_events": [], "coord_events": [],
        "bg_events": [b for b in anteriores.get("bg_events", []) if b.get("type") == "hidden_item"],
    }
    for o in datos["object_events"] + datos["bg_events"]:
        if o.get("flag") in SITIO_OBJETOS:
            o["x"], o["y"] = SITIO_OBJETOS[o["flag"]]
            o["elevation"] = 3
    escribir(ruta, json.dumps(datos, indent=2, ensure_ascii=False) + "\n")
    escribir(f"data/maps/{PLAYA}/scripts.inc", con_nivel_actual(f"data/maps/{PLAYA}/scripts.inc", SCRIPTS))

    grupos = leer("data/maps/map_groups.json")
    if f'"{PLAYA}"' not in grupos:
        salto = "\r\n" if "\r\n" in grupos else "\n"
        d = json.loads(grupos)
        grupo = next(g for g in d["group_order"] if "Route122" in d[g])
        ultimo = d[grupo][-1]
        a = f'"{ultimo}"{salto}'
        i = grupos.index(a, grupos.index(f'"{grupo}": ['))
        grupos = grupos[:i] + f'"{ultimo}",{salto}    "{PLAYA}"{salto}' + grupos[i + len(a):]
        json.loads(grupos)
        escribir("data/maps/map_groups.json", grupos)

    ruta = "src/data/region_map/region_map_sections.json"
    texto = leer(ruta)
    if f'"{MAPSEC}"' not in texto:
        r122 = next(s for s in json.loads(texto)["map_sections"] if s["id"] == "MAPSEC_ROUTE_122")
        texto = co.insertar_en_lista(texto, "map_sections", {"id": MAPSEC, "name": "PLAYA VOLCÁNICA",
                                                             "x": r122["x"] - 1, "y": r122["y"], "width": 1, "height": 1})
        json.loads(texto)
        escribir(ruta, texto)


_, _, ESPECIE, NIVEL, PREMIO, FLAG = GUARDIAN
SCRIPTS = f"""{PLAYA}_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, {PLAYA}_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, {PLAYA}_OnTransition
	.byte 0

@ Dualocke: la PLAYA VOLCÁNICA, al oeste del MONTE PÍRICO (tools/dualocke/crear_playa_volcanica.py).
@ El guardián es un Pokémon fuerte que se puede capturar, como en las islas del ferry
@ (data/scripts/dualocke_islas.inc). Con semilla sale otro de su tipo (estaticos.py, islas()).
@ Al pisar la hierba con ceniza se le cae la ceniza, como en la RUTA 113.
{PLAYA}_OnResume:
	setstepcallback STEP_CB_ASH
	end

{PLAYA}_OnTransition:
	setvar VAR_0x8004, {ESPECIE}
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

{PLAYA}_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, {ESPECIE}
	setvar VAR_TEMP_9, {PREMIO}
	call Dualocke_EventScript_AvisoIsla
	setwildbattle {ESPECIE}, {NIVEL}
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, {PLAYA}_EventScript_PokemonSigue
	setflag {FLAG}
	call Dualocke_EventScript_PremioIsla
	release
	end

{PLAYA}_EventScript_PokemonSigue::
	release
	end

{PLAYA}_EventScript_Vecino::
	msgbox {PLAYA}_Text_Vecino, MSGBOX_NPC
	end

{PLAYA}_Text_Vecino:
	.string "Cuando el MONTE PÍRICO echa humo,\\n"
	.string "la ceniza llega hasta esta playa.\\p"
	.string "Dicen que un POKéMON enorme sale\\n"
	.string "del mar a tomar el sol en la arena.$"
"""


def main():
    crear_mapa(crear_layout())
    ruta122()
    print("Dualocke: PLAYA VOLCÁNICA creada")


if __name__ == "__main__":
    main()
