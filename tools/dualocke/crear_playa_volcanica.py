#!/usr/bin/env python3
"""
Dualocke: la PLAYA VOLCÁNICA, al oeste del MONTE PÍRICO (ZONAS.md, propuesta 10; rehecha el 17/11/2026 para
que parezca diseñada como el juego original).

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_playa_volcanica.py

**Cómo se dibuja.** Como la MARISMA AZULIZA: el mapa es un dibujo de letras (PLANO) y lo pinta autotile.py con
las piezas que ha aprendido de los mapas originales. Copia tal cual tres cosas del juego: el rincón de las
termas de LAVACALDA (con su acantilado, su poza y su arena), la peña volcánica de la RUTA 112 y las rocas
del mar de la RUTA 122.

**El diseño** (como la playa de la RUTA 104, a los pies de un volcán):
- **Playa:** arena junto al mar, con su orilla y su bajío, una charca de marea y rocas en el mar.
- **Risco:** una franja de roca separa la playa (abajo) de la meseta (arriba), con una escalera. En el
  juego la arena de playa nunca toca la hierba: siempre hay un risco o agua entre las dos.
- **Meseta:** pradera con hierba alta, árboles, un camino de tierra hasta las termas, la peña volcánica y,
  arriba, el acantilado del volcán. Sol normal (sin sol en combate; Miguel, 20/11/2026).
- **Guardián** en la playa y un bañista en las termas. **Tramo 7.**

**La ceniza (Miguel, 20/11/2026).** Miguel quería la misma playa, pero con la hierba y el césped de ceniza,
como la RUTA 113. Las piezas de ceniza de la RUTA 113 son de otros gráficos (PARDA), y con ellos no estarían
las termas, el acantilado ni la peña, que son de LAVACALDA. Así que el mapa es el mismo y lo que cambia son
los **colores**: la playa usa una copia de los gráficos General y LAVACALDA (`gTileset_GeneralCeniza` y
`gTileset_LavaridgeCeniza`), con los mismos dibujos, piezas y animaciones, pero con los cuatro verdes del suelo
y la hierba cambiados por los de la ceniza de la RUTA 113 (`VERDES`). Los árboles y las hojas de las flores
siguen verdes, como en la RUTA 113. `paletas_ceniza()` escribe las paletas y añade los gráficos al código.

**La unión con la RUTA 122** (gráficos General + Algaria; la playa es General + LAVACALDA). Una conexión entre
mapas de gráficos distintos solo se ve bien si lo que se ve del otro mapa son gráficos generales:
- Se cruza por arriba (filas 0-7), donde el borde de la RUTA 122 solo tiene mar y rocas generales. En la
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
ROCA_RUTA122 = (5, 4)                     # la roca (2 × 2) que se quita del anillo de la RUTA 122
FILAS_CRUCE = 8                           # filas 0-7: por aquí se pasa de un mapa a otro
BANDA_GENERAL = 8                         # las últimas 8 columnas, solo gráficos generales
# Los cuatro verdes del suelo y la hierba (de claro a oscuro) y el color de la ceniza de la RUTA 113 que los cambia
VERDES = {(164, 213, 197): (205, 205, 164), (115, 197, 164): (172, 172, 139),
          (65, 180, 131): (148, 139, 115), (24, 164, 106): (115, 115, 74)}
# Gráficos originales -> (su carpeta, nombre de la copia con ceniza, carpeta de la copia)
CENIZA = {
    "gTileset_General": ("primary/general", "GeneralCeniza", "primary/general_ceniza"),
    "gTileset_Lavaridge": ("secondary/lavaridge", "LavaridgeCeniza", "secondary/lavaridge_ceniza"),
}
ROCA = (0x175, 0x176, 0x17D, 0x17E)      # roca de mar (general): arriba izq., arriba der., abajo izq., abajo der.
# L rincón de las termas   K acantilado del volcán   M peña volcánica   X roca de mar (2 × 2)
# T árbol grande   . hierba   , hierba alta   * flores   c camino de tierra   s arena   b bajío   m mar
# R risco   1 2 su escalera
PLANO = """
LLLLLLLLKKKKKKKKKKKKKKKKKKXXXXXXXXXXXXXX
LLLLLLLLKKKKKKKKKKKKKKKKKKXXXXXXXXXXXXXX
LLLLLLLL............Rssssssbbmmmmmmmmmmm
LLLLLLLL....,,,,,,,,Rssssssbbmmmmmmmmmmm
LLLLLLLL....,,,,,,,,Rssssssbbmmmmmmmmmmm
LLLLLLLL....,,,,,,,,Rssssssbbmmmmmmmmmmm
LLLLLLLL....,,,,,,,,Rssssssbbmmmmmmmmmmm
LLLLLLLL............Rssssssbbmmmmmmmmmmm
LLLLLLLLccc.....TT..RssssssbbmmmmmmmmmXX
LLLLLLLLccc.....TT..RsssssbbmmmmmmmmmmXX
LLLLLLLLccc.....TT..RsssssbbmmmmmmmmmmXX
TT......cccccccccc..RsssssbbmmmmmmmmmmXX
TT......cccccccccc..RsssssbbmmmmmmmmmmXX
TT.,,,,,.cccccccccc.RssssbbmmmmmmXXmmmXX
TT.,,,,,.......cccc.RssssbbmmmmmmXXmmmXX
TT.,,,,,.*..TT.cccc.RssssbbmmmmmmmmmmmXX
TT.,,,,,..*.TT.cccc.RssssbbmmmmmmmmmmmXX
TT.,,,,,....TT.cccc.RssssbbmmmmmmmmmmmXX
TT.,,,,,....TTRR12RRRssssbbmmmmmmmmmmmXX
TT.,,,,,....TTRssssssssssbbmmmmmmmmmmmXX
TT......*.....RssssssssssbbmmmmmmmmmmmXX
TT........,,,,RssssssssssbbmmmmmmmmmmmXX
TT...*....,,,,RssssssssssbbmmmmmmmmmmmXX
TT........,,,,RssssssssssbbmmmmmmmmmmmXX
TT........,,,,RssssssssssbbmmmmmmmXXmmXX
TT.MMMMMMMMM,,RssssssssssbbmmmmmmmXXmmXX
TT.MMMMMMMMM..RssssssssssbbmmmmmmmmmmmXX
TT.MMMMMMMMM..RsssssssmmmsbbmmmmmmmmmmXX
TT.MMMMMMMMM..RsssssssmmmsbbmmmmmmmmmmXX
TT..........*.RsssssssssssbbmmmmmmmmmmXX
TT,,,,,,.....*RssssssssssssbbmmmmmmmmmXX
TT,,,,,,..TT..RssssssssssssbbmmmXXmmmmXX
TT,,,,,,..TT..RssssssssssssbbmmmXXmmmmXX
TT,,,,,,..TT..RssssssssssssbbmmmmmmmmmXX
TT,,,,,,..TT..RssssssssssssbbmmmmmmmmmXX
TT........TT..RssssssssssssbbmmmmmmmmmXX
TT............RssssssssssssbbmmmmmmmmmXX
TTTTTTTTTTTTTTTTTTTTTTTTTTTTbmmmmmmmmmXX
TTTTTTTTTTTTTTTTTTTTTTTTTTTTXXXXXXXXXXXX
TTTTTTTTTTTTTTTTTTTTTTTTTTTTXXXXXXXXXXXX
"""
TERRENO = {".": "suelo", "*": "suelo", ",": "hierba_alta", "c": "camino", "s": "arena", "b": "bajio", "m": "mar",
           "R": "risco", "1": "risco", "2": "risco"}
FLORES = 0x004
TERMAS = ("LavaridgeTown", (0, 0, 8, 11))     # el rincón de las termas (x0, y0, x1, y1)
TERMAS_TAPAR = [(5, 1), (6, 1), (7, 1)]       # la pasarela del acantilado: aquí, acantilado
ACANTILADO = ("LavaridgeTown", 2)              # columna de la que se copia el acantilado (filas 0 y 1)
PENA = ("Route112", (23, 46, 32, 50))          # la peña volcánica, sobre hierba
GUARDIAN = (23, 14, "SPECIES_SLITHER_WING", 70, "ITEM_BOOSTER_ENERGY", "FLAG_DUALOCKE_GUARDIAN_PLAYA")
BANISTA = (3, 9)                               # en la arena de las termas


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
CR, LF = chr(13), chr(10)


def celdas_de(carpeta):
    l = LAYOUTS[json.loads(leer(f"data/maps/{carpeta}/map.json"))["layout"]]
    return l, list(struct.unpack(f"<{l['width'] * l['height']}H", open(l["blockdata_filepath"], "rb").read()))


def copiar(origen, caja):
    """{(dx, dy): valor} de un trozo de un mapa."""
    l, c = celdas_de(origen)
    x0, y0, x1, y1 = caja
    return {(x - x0, y - y0): c[y * l["width"] + x] for y in range(y0, y1) for x in range(x0, x1)}


def crear_layout():
    aprendiz = at.Aprendiz()
    filas = PLANO.strip().splitlines()
    alto, ancho = len(filas), len(filas[0])
    assert all(len(f) == ancho for f in filas), "las filas del plano no miden lo mismo"
    pintadas = aprendiz.pintar([[TERRENO.get(ch) for ch in f] for f in filas])
    valor = lambda m: aprendiz.valor.get(m, m)  # noqa: E731
    c = [0] * (ancho * alto)
    termas = copiar(TERMAS[0], TERMAS[1])
    lt, ct = celdas_de(TERMAS[0])
    cara = ct[1 * lt["width"] + ACANTILADO[1]]
    cima = ct[0 * lt["width"] + ACANTILADO[1]]
    for x, y in TERMAS_TAPAR:
        termas[(x, y)] = cara
    pena = copiar(PENA[0], PENA[1])
    _, c122 = celdas_de("Route122")
    roca = {}
    for m in ROCA:   # el valor de la roca de mar, tal como está en la RUTA 122 (con colisión)
        roca[m] = next(v for v in c122 if v & 0x3FF == m and (v >> 10) & 3)
    for y in range(alto):
        for x in range(ancho):
            ch = filas[y][x]
            if ch == "L":
                c[y * ancho + x] = termas[(x, y)]
            elif ch == "K":
                c[y * ancho + x] = cima if y == 0 else cara
            elif ch == "M":
                x0 = min(xx for xx in range(ancho) if filas[y][xx] == "M")
                y0 = min(yy for yy in range(alto) if filas[yy][x] == "M")
                c[y * ancho + x] = pena[(x - x0, y - y0)]
            elif ch == "X":
                # Cada roca es de 2 × 2: la esquina de arriba a la izquierda es la primera X de su grupo
                x0 = x
                while x0 > 0 and filas[y][x0 - 1] == "X":
                    x0 -= 1
                y0 = y
                while y0 > 0 and filas[y0 - 1][x] == "X":
                    y0 -= 1
                c[y * ancho + x] = roca[ROCA[((y - y0) % 2) * 2 + (x - x0) % 2]]
            elif ch == "T":
                continue
            else:
                v = pintadas[y][x]
                if ch == "*":
                    v = (v & ~0x3FF) | FLORES
                elif ch in "12":
                    v = valor(at.ESCALERA_RISCO[int(ch) - 1])
                c[y * ancho + x] = v
    fallos = at.arboles_grandes(filas, c, valor)
    assert not fallos, "; ".join(fallos)
    assert all(c), "casillas sin pintar"
    # La banda del este (la que se ve desde la RUTA 122) solo tiene gráficos generales
    assert all(c[y * ancho + x] & 0x3FF < 0x200 for y in range(alto) for x in range(ancho - BANDA_GENERAL, ancho))
    gx, gy = GUARDIAN[:2]
    assert not (c[gy * ancho + gx] >> 10) & 3, "el guardián no está en el suelo"

    # Borde de árboles, como la playa de la RUTA 104 (antes era la roca del MONTE CENIZO y se veía un
    # relleno rosa al acercarse a los bordes; Miguel, 19/11/2026)
    base = LAYOUTS[json.loads(leer("data/maps/Route104/map.json"))["layout"]]
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
            "primary_tileset": "gTileset_GeneralCeniza", "secondary_tileset": "gTileset_LavaridgeCeniza",
            "border_filepath": f"data/layouts/{PLAYA}/border.bin",
            "blockdata_filepath": f"data/layouts/{PLAYA}/map.bin"})
    else:
        # Los gráficos con ceniza (20/11/2026): se cambian en la entrada de la playa
        i = texto.index(f'"{ident}"')
        j = texto.index("}", i)
        trozo = re.sub(r'("primary_tileset":\s*")\w+(")', r"\g<1>gTileset_GeneralCeniza\2", texto[i:j])
        trozo = re.sub(r'("secondary_tileset":\s*")\w+(")', r"\g<1>gTileset_LavaridgeCeniza\2", trozo)
        texto = texto[:i] + trozo + texto[j:]
    json.loads(texto)
    escribir("data/layouts/layouts.json", texto)
    raras = aprendiz.revisar(c, ancho, alto, "gTileset_Lavaridge")
    print(f"Dualocke: PLAYA VOLCÁNICA: parejas de piezas que el juego no usa: {len(raras)}")
    return ident


def leer_pal(ruta):
    lineas = leer(ruta).replace(CR + LF, LF).split(LF)
    assert lineas[0] == "JASC-PAL" and lineas[2] == "16", ruta
    return [tuple(int(v) for v in linea.split()) for linea in lineas[3:19]]


def paletas_ceniza():
    """Las paletas de los gráficos con ceniza (copias de las de General y LAVACALDA con los verdes cambiados) y
    los gráficos en el código: las paletas en src/data/tilesets/graphics.h, después de las de LAVACALDA (las de
    General están en src/graphics.c), y los gráficos en headers.h, después de los originales. Usan los dibujos,
    las piezas y las animaciones de los originales."""
    graficos = leer("src/data/tilesets/graphics.h").replace(CR + LF, LF)
    cabeceras = leer("src/data/tilesets/headers.h").replace(CR + LF, LF)
    for original, (origen, nombre, destino) in CENIZA.items():
        os.makedirs(f"data/tilesets/{destino}/palettes", exist_ok=True)
        cambiados = 0
        for n in range(16):
            colores = leer_pal(f"data/tilesets/{origen}/palettes/{n:02d}.pal")
            nuevos = [VERDES.get(c, c) for c in colores]
            cambiados += sum(a != b for a, b in zip(colores, nuevos))
            escribir(f"data/tilesets/{destino}/palettes/{n:02d}.pal",
                     "JASC-PAL" + CR + LF + "0100" + CR + LF + "16" + CR + LF
                     + "".join(f"{r} {g} {b}" + CR + LF for r, g, b in nuevos))
        print(f"Dualocke: {nombre}: {cambiados} colores verdes pasan a ceniza")
        paletas = "gTilesetPalettes_" + original[len("gTileset_"):]
        if f"gTilesetPalettes_{nombre}[]" not in graficos:
            i = graficos.index("const u16 gTilesetPalettes_Lavaridge[][16] =")
            j = graficos.index("};" + LF, i) + 3
            graficos = (graficos[:j] + LF + "// Dualocke: la PLAYA VOLCÁNICA con ceniza (crear_playa_volcanica.py)" + LF
                        + f"const u16 gTilesetPalettes_{nombre}[][16] =" + LF + "{" + LF
                        + "".join(f'    INCGFX_U16("data/tilesets/{destino}/palettes/{n:02d}.pal", ".gbapal"),' + LF
                                  for n in range(16))
                        + "};" + LF + graficos[j:])
        if f"gTileset_{nombre} =" not in cabeceras:
            m = re.search(r"const struct Tileset " + original + r" =\s*\{(.*?)\};\n", cabeceras, re.S)
            cuerpo = m.group(1).replace(f"= {paletas},", f"= gTilesetPalettes_{nombre},")
            assert f"gTilesetPalettes_{nombre}" in cuerpo
            cabeceras = (cabeceras[:m.end()] + LF + f"// Dualocke: {original} con los verdes del suelo y la hierba "
                         + "de ceniza (la PLAYA VOLCÁNICA, crear_playa_volcanica.py)" + LF
                         + f"const struct Tileset gTileset_{nombre} =" + LF + "{" + cuerpo + "};" + LF
                         + cabeceras[m.end():])
    escribir("src/data/tilesets/graphics.h", graficos)
    escribir("src/data/tilesets/headers.h", cabeceras)


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
         "elevation": 3, "movement_type": "MOVEMENT_TYPE_FACE_LEFT", "movement_range_x": 0, "movement_range_y": 0,
         "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
         "script": f"{PLAYA}_EventScript_Pokemon", "flag": flag},
        {"graphics_id": "OBJ_EVENT_GFX_OLD_MAN", "x": BANISTA[0], "y": BANISTA[1], "elevation": 3,
         "movement_type": "MOVEMENT_TYPE_FACE_UP", "movement_range_x": 0, "movement_range_y": 0,
         "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
         "script": f"{PLAYA}_EventScript_Banista", "flag": "0"}]
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
	map_script MAP_SCRIPT_ON_TRANSITION, {PLAYA}_OnTransition
	.byte 0

@ Dualocke: la PLAYA VOLCÁNICA, al oeste del MONTE PÍRICO (tools/dualocke/crear_playa_volcanica.py).
@ El guardián es un Pokémon fuerte que se puede capturar, como en las islas del ferry
@ (data/scripts/dualocke_islas.inc). Con semilla sale otro de su tipo (estaticos.py, islas()).
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

{PLAYA}_EventScript_Banista::
	msgbox {PLAYA}_Text_Banista, MSGBOX_NPC
	end

{PLAYA}_Text_Banista:
	.string "Estas aguas las calienta el volcán\\n"
	.string "que hay bajo el MONTE PÍRICO.\\p"
	.string "Dicen que un POKéMON enorme sale\\n"
	.string "del mar a tomar el sol.$"
"""


def main():
    paletas_ceniza()
    crear_mapa(crear_layout())
    ruta122()
    print("Dualocke: PLAYA VOLCÁNICA creada")


if __name__ == "__main__":
    main()
