#!/usr/bin/env python3
"""
Dualocke: la CUMBRE METEORO, la montaña de la CATARATA METEORO (ZONAS.md, propuesta 11; Miguel, 17/11/2026).

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_cumbre_meteoro.py

- **Entrada:** una cueva nueva en la pared de roca de la RUTA 115, junto a la entrada de la CATARATA METEORO
  (x 31, fila 39; se entra desde abajo). Es el mismo dibujo de boca de cueva que el de la catarata. **Tramo 4.**
  El borde norte de la RUTA 115 está cerrado (bosque y acantilados), así que se entra por una cueva y no
  por el borde.
- **LADERA** (40 × 20): las terrazas de roca del sur de la RUTA 114 (escaleras, rocas, bordillos de un solo
  sentido), con hierba alta de montaña. Se llega por su boca de cueva (la de la catarata en la RUTA 114) y,
  arriba del todo, otra cueva sube a la cumbre.
- **CUMBRE** (24 × 31): las cimas de la RUTA 115 (las de arriba, a las que en el juego no se llega), con
  nieve (nieve en combate) y hierba escarchada. Arriba espera el guardián.
- Las bases secretas de los trozos copiados se tapan con roca, y dos de ellas pasan a ser las cuevas
  (mismo sitio en la pared). No se quita ninguna base secreta de las rutas.
- **Zona de captura propia:** MAPSEC_CUMBRE_METEORO (las dos partes cuentan como una).
Los salvajes y los objetos los ponen zonas_nuevas.py y colocar_objetos.py.
"""

import json
import os
import re
import struct
import sys

sys.path.insert(0, "tools/dualocke")
import colocar_objetos as co  # noqa: E402

LADERA, CUMBRE = "CumbreMeteoro_Ladera", "CumbreMeteoro"
MAPAS = {LADERA: "MAP_CUMBRE_METEORO_LADERA", CUMBRE: "MAP_CUMBRE_METEORO"}
MAPSEC = "MAPSEC_CUMBRE_METEORO"
CUEVA = 0x261                                 # boca de cueva de la CATARATA METEORO (gráficos de Fallarbor)
PARED = 0x265                                 # pared de roca en la que va la boca
SUELO = 0x241
BASE_SECRETA = 0x208
ENTRADA_RUTA115 = (31, 39)                    # pared lisa junto a la base secreta (32, 39)
LADERA_TROZO = ("Route114", (0, 56, 40, 76))
LADERA_LLEGADA = (8, 63)                      # la boca de la catarata en la RUTA 114
LADERA_SUBIDA = (32, 57)                      # una base secreta de arriba: pasa a ser la cueva a la cumbre
LADERA_HIERBA, HIERBA_LADERA = [(14, 58, 27, 61), (13, 64, 25, 67), (7, 69, 15, 73)], 0x212
CUMBRE_TROZO = ("Route115", (18, 0, 40, 31))   # sin la franja del bosque de la izquierda
CUMBRE_LLEGADA = (25, 24)                     # una base secreta: pasa a ser la cueva de llegada
CUMBRE_HIERBA, HIERBA_CUMBRE = [(18, 9, 29, 12), (21, 13, 29, 17), (32, 11, 37, 16)], 0x20A
GUARDIAN = (21, 7, "SPECIES_SALAMENCE", 34, "ITEM_DRAGON_FANG", "FLAG_DUALOCKE_GUARDIAN_CUMBRE")


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


def valor_de(carpeta, x, y):
    l, c = celdas_de(carpeta)
    return c[y * l["width"] + x]


def recortar(origen, caja, cuevas, hierba, valor_hierba):
    """Copia el trozo; tapa sus bases secretas con la roca de su izquierda, pone las cuevas (coordenadas de
    origen) y la hierba (en el suelo liso, sin colisión)."""
    l, c = celdas_de(origen)
    w = l["width"]
    x0, y0, x1, y1 = caja
    cueva = valor_de("Route115", 27, 37)
    assert cueva & 0x3FF == CUEVA
    nuevas = []
    for y in range(y0, y1):
        for x in range(x0, x1):
            v = c[y * w + x]
            if (x, y) in cuevas:
                assert v & 0x3FF in (BASE_SECRETA, CUEVA), ("ahí no hay base secreta", origen, x, y)
                v = cueva
            elif v & 0x3FF == BASE_SECRETA:
                v = c[y * w + x - 1]
            elif v & 0x3FF == SUELO and not (v >> 10) & 3 and any(a <= x < b and e <= y < f for a, e, b, f in hierba):
                v = (v & ~0x3FF) | valor_hierba
            nuevas.append(v)
    return l, nuevas, x1 - x0, y1 - y0


def guardar_layout(carpeta, ancho, alto, celdas, base):
    os.makedirs(f"data/layouts/{carpeta}", exist_ok=True)
    with open(f"data/layouts/{carpeta}/map.bin", "wb") as f:
        f.write(struct.pack(f"<{ancho * alto}H", *celdas))
    # El borde (lo que se ve fuera del mapa) es el de la RUTA 114, montaña con los mismos gráficos. Antes era el
    # de la RUTA 115, que es mar: el mapa se veía cortado por agua (lo vio Miguel jugando, 18/11/2026).
    borde = LAYOUTS[json.loads(leer("data/maps/Route114/map.json"))["layout"]]["border_filepath"]
    with open(borde, "rb") as f, open(f"data/layouts/{carpeta}/border.bin", "wb") as g:
        g.write(f.read())
    ident = "LAYOUT_" + MAPAS[carpeta][4:]
    texto = leer("data/layouts/layouts.json")
    if f'"{ident}"' not in texto:
        texto = co.insertar_en_lista(texto, "layouts", {
            "id": ident, "name": f"{carpeta}_Layout", "width": ancho, "height": alto,
            "primary_tileset": base["primary_tileset"], "secondary_tileset": base["secondary_tileset"],
            "border_filepath": f"data/layouts/{carpeta}/border.bin",
            "blockdata_filepath": f"data/layouts/{carpeta}/map.bin"})
        json.loads(texto)
        escribir("data/layouts/layouts.json", texto)
    return ident


def en_trozo(caja, x, y):
    return x - caja[0], y - caja[1]


def entrada_ruta115():
    """Abre la cueva en la pared de la RUTA 115 y le pone su puerta. Devuelve el número de esa puerta."""
    l, c = celdas_de("Route115")
    w = l["width"]
    x, y = ENTRADA_RUTA115
    assert c[y * w + x] & 0x3FF in (PARED, CUEVA) and not (c[(y + 1) * w + x] >> 10) & 3, "la pared no es la esperada"
    c[y * w + x] = valor_de("Route115", 27, 37)
    with open(l["blockdata_filepath"], "wb") as f:
        f.write(struct.pack(f"<{w * l['height']}H", *c))
    ruta = "data/maps/Route115/map.json"
    texto = leer(ruta)
    if MAPAS[LADERA] not in texto:
        texto = co.insertar_en_lista(texto, "warp_events", {"x": x, "y": y, "elevation": 0,
                                                            "dest_map": MAPAS[LADERA], "dest_warp_id": "0"})
        json.loads(texto)
        escribir(ruta, texto)
    # Las puertas van a altura 0, que vale para cualquier altura (como la de la CATARATA METEORO)
    mapa = json.loads(leer(ruta))
    for wp in mapa["warp_events"]:
        if wp["dest_map"] == MAPAS[LADERA]:
            wp["elevation"] = 0
    escribir(ruta, json.dumps(mapa, indent=2, ensure_ascii=False) + "\n")
    warps = json.loads(leer(ruta))["warp_events"]
    return next(i for i, wp in enumerate(warps) if wp["dest_map"] == MAPAS[LADERA])


def con_nivel_actual(ruta, texto):
    """Conserva el nivel del guardián que haya puesto reescalar_niveles.py si el script ya existe."""
    if os.path.exists(ruta):
        anterior = re.search(r"setwildbattle (SPECIES_\w+), (\d+)", leer(ruta))
        if anterior:
            texto = re.sub(rf"setwildbattle {anterior.group(1)}, \d+",
                           f"setwildbattle {anterior.group(1)}, {anterior.group(2)}", texto)
    return texto


def mapa_json(carpeta, datos, objetos):
    ruta = f"data/maps/{carpeta}/map.json"
    os.makedirs(f"data/maps/{carpeta}", exist_ok=True)
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    datos["object_events"] = objetos + [o for o in anteriores.get("object_events", [])
                                        if str(o.get("flag", "")).startswith("FLAG_ITEM_")]
    datos["bg_events"] = [b for b in anteriores.get("bg_events", []) if b.get("type") == "hidden_item"]
    datos["coord_events"] = []
    escribir(ruta, json.dumps(datos, indent=2, ensure_ascii=False) + "\n")


def main():
    puerta_ruta115 = entrada_ruta115()
    _, cl, wl, hl = recortar(LADERA_TROZO[0], LADERA_TROZO[1], {LADERA_SUBIDA}, LADERA_HIERBA, HIERBA_LADERA)
    base = LAYOUTS[json.loads(leer("data/maps/Route115/map.json"))["layout"]]
    l_ladera = guardar_layout(LADERA, wl, hl, cl, base)
    _, cc, wc, hc = recortar(CUMBRE_TROZO[0], CUMBRE_TROZO[1], {CUMBRE_LLEGADA}, CUMBRE_HIERBA, HIERBA_CUMBRE)
    gx, gy = en_trozo(CUMBRE_TROZO[1], *GUARDIAN[:2])
    assert not (cc[gy * wc + gx] >> 10) & 3, "el guardián no está en el suelo"
    l_cumbre = guardar_layout(CUMBRE, wc, hc, cc, base)

    comun = {"region": "REGION_HOENN", "region_map_section": MAPSEC, "requires_flash": False,
             "map_type": "MAP_TYPE_ROUTE", "allow_cycling": True, "allow_escaping": False, "allow_running": True,
             "show_map_name": True, "battle_scene": "MAP_BATTLE_SCENE_NORMAL", "connections": None}
    llegada = en_trozo(LADERA_TROZO[1], *LADERA_LLEGADA)
    subida = en_trozo(LADERA_TROZO[1], *LADERA_SUBIDA)
    mapa_json(LADERA, {"id": MAPAS[LADERA], "name": LADERA, "layout": l_ladera, "music": "MUS_ROUTE113",
                       "weather": "WEATHER_SUNNY", **comun,
                       "warp_events": [
                           # Altura 0: el suelo de la LADERA está a 5 y con 3 no se salía (Miguel, 18/11/2026)
                           {"x": llegada[0], "y": llegada[1], "elevation": 0, "dest_map": "MAP_ROUTE115",
                            "dest_warp_id": str(puerta_ruta115)},
                           {"x": subida[0], "y": subida[1], "elevation": 0, "dest_map": MAPAS[CUMBRE],
                            "dest_warp_id": "0"}]}, [])
    c_llegada = en_trozo(CUMBRE_TROZO[1], *CUMBRE_LLEGADA)
    _, _, especie, nivel, premio, flag = GUARDIAN
    mapa_json(CUMBRE, {"id": MAPAS[CUMBRE], "name": CUMBRE, "layout": l_cumbre, "music": "MUS_ROUTE120",
                       "weather": "WEATHER_SNOW", **comun,
                       "warp_events": [{"x": c_llegada[0], "y": c_llegada[1], "elevation": 0,
                                        "dest_map": MAPAS[LADERA], "dest_warp_id": "1"}]},
              [{"local_id": "LOCALID_CUMBRE_METEORO_GUARDIAN", "graphics_id": "OBJ_EVENT_GFX_VAR_0",
                "x": gx, "y": gy, "elevation": 3, "movement_type": "MOVEMENT_TYPE_FACE_DOWN",
                "movement_range_x": 0, "movement_range_y": 0, "trainer_type": "TRAINER_TYPE_NONE",
                "trainer_sight_or_berry_tree_id": "0", "script": f"{CUMBRE}_EventScript_Pokemon", "flag": flag}])
    escribir(f"data/maps/{LADERA}/scripts.inc", f"{LADERA}_MapScripts::\n\t.byte 0\n")
    ruta = f"data/maps/{CUMBRE}/scripts.inc"
    escribir(ruta, con_nivel_actual(ruta, f"""{CUMBRE}_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, {CUMBRE}_OnTransition
	.byte 0

@ Dualocke: el guardián de la CUMBRE METEORO (tools/dualocke/crear_cumbre_meteoro.py), un Pokémon fuerte que
@ se puede capturar, como en las islas del ferry (data/scripts/dualocke_islas.inc). Con semilla sale otro.
{CUMBRE}_OnTransition:
	setvar VAR_0x8004, {especie}
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

{CUMBRE}_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, {especie}
	setvar VAR_TEMP_9, {premio}
	call Dualocke_EventScript_AvisoIsla
	setwildbattle {especie}, {nivel}
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, {CUMBRE}_EventScript_PokemonSigue
	setflag {flag}
	call Dualocke_EventScript_PremioIsla
	release
	end

{CUMBRE}_EventScript_PokemonSigue::
	release
	end
"""))

    grupos = leer("data/maps/map_groups.json")
    salto = "\r\n" if "\r\n" in grupos else "\n"
    for carpeta in (LADERA, CUMBRE):
        if f'"{carpeta}"' in grupos:
            continue
        d = json.loads(grupos)
        grupo = next(g for g in d["group_order"] if "Route115" in d[g])
        ultimo = d[grupo][-1]
        a = f'"{ultimo}"{salto}'
        i = grupos.index(a, grupos.index(f'"{grupo}": ['))
        grupos = grupos[:i] + f'"{ultimo}",{salto}    "{carpeta}"{salto}' + grupos[i + len(a):]
    json.loads(grupos)
    escribir("data/maps/map_groups.json", grupos)

    ruta = "src/data/region_map/region_map_sections.json"
    texto = leer(ruta)
    if f'"{MAPSEC}"' not in texto:
        r115 = next(s for s in json.loads(texto)["map_sections"] if s["id"] == "MAPSEC_ROUTE_115")
        texto = co.insertar_en_lista(texto, "map_sections", {"id": MAPSEC, "name": "CUMBRE METEORO",
                                                             "x": r115["x"], "y": r115["y"] - 1,
                                                             "width": 1, "height": 1})
        json.loads(texto)
        escribir(ruta, texto)
    print("Dualocke: CUMBRE METEORO creada")


if __name__ == "__main__":
    main()
