#!/usr/bin/env python3
"""
Dualocke: reparte por el mapa de Hoenn las megapiedras, los objetos competitivos modernos y los
Ticket-Recuerdo (uno por ruta como mínimo, para el que recuerda movimientos de los Centros Pokémon).

Uso (desde la raíz del repo):
    python3 tools/dualocke/colocar_objetos.py            # coloca los que falten
    python3 tools/dualocke/colocar_objetos.py --resumen  # solo enseña dónde irían

Cada megapiedra va en un mapa de la tabla, como bola de objeto ("bola") o como objeto oculto
("oculta"). La casilla se busca automáticamente cerca de algo que seguro se puede alcanzar
(un objeto o un entrenador que ya están en ese mapa): solo casillas transitables, a la misma
altura, sin otros objetos, puertas ni eventos. Cada objeto usa su propio flag
(FLAG_ITEM_MEGA_..., FLAG_ITEM_COMP_... o FLAG_ITEM_TICKET_..., en include/constants/flags.h)
para no volver a aparecer.

Si una megapiedra ya está colocada (su flag aparece en el map.json), no se toca, así que se
puede volver a lanzar sin duplicar nada. Para moverla, se borra a mano de ese map.json.
"""

import json
import os
import re
import struct
import sys
from collections import deque

# (megapiedra, carpeta del mapa, "bola" u "oculta", pista opcional para elegir el ancla)
MEGAPIEDRAS = [
    ("BEEDRILLITE", "PetalburgWoods", "bola", None),
    ("SCOLIPITE", "PetalburgWoods", "bola", None),
    ("VENUSAURITE", "PetalburgWoods", "oculta", None),
    ("AGGRONITE", "GraniteCave_B2F", "bola", None),
    ("SABLENITE", "GraniteCave_B1F", "bola", None),
    ("STEELIXITE", "GraniteCave_1F", "bola", None),
    ("MAWILITE", "GraniteCave_B2F", "oculta", None),
    ("EXCADRITE", "RusturfTunnel", "bola", None),
    ("FLOETTITE", "Route104", "bola", None),
    ("ALAKAZITE", "Route116", "oculta", None),
    ("MEGANIUMITE", "Route117", "bola", None),
    ("LOPUNNITE", "Route117", "oculta", None),
    ("AUDINITE", "Route117", "oculta", None),
    ("MEOWSTICITE", "Route110_TrickHouseEnd", "bola", None),
    ("CHARIZARDITE_X", "FieryPath", "bola", None),
    ("HOUNDOOMINITE", "FieryPath", "bola", None),
    ("EMBOARITE", "FieryPath", "oculta", None),
    ("CAMERUPTITE", "JaggedPass", "bola", None),
    ("CHARIZARDITE_Y", "MtChimney", "bola", None),
    ("PYROARITE", "MtChimney", "oculta", None),
    ("GARCHOMPITE", "Route111", "bola", "DESERT|SANDSTORM|STARDUST"),
    ("TYRANITARITE", "Route111", "bola", "DESERT|SANDSTORM|STARDUST"),
    ("SCOVILLAINITE", "Route111", "oculta", "DESERT|SANDSTORM|STARDUST"),
    ("AERODACTYLITE", "MirageTower_4F", "bola", None),
    ("CLEFABLITE", "MeteorFalls_1F_1R", "bola", None),
    ("GLIMMORANITE", "MeteorFalls_1F_1R", "oculta", None),
    ("SKARMORITE", "Route113", "bola", None),
    ("SCRAFTINITE", "Route114", "oculta", None),
    ("MANECTITE", "NewMauville_Inside", "bola", None),
    ("AMPHAROSITE", "NewMauville_Inside", "bola", None),
    ("RAICHUNITE_X", "NewMauville_Inside", "bola", None),
    ("RAICHUNITE_Y", "NewMauville_Inside", "oculta", None),
    ("EELEKTROSSITE", "NewMauville_Inside", "bola", None),
    ("GOLISOPITE", "AbandonedShip_Rooms_B1F", "bola", None),
    ("GRENINJITE", "AbandonedShip_HiddenFloorCorridors", "oculta", None),
    ("HAWLUCHANITE", "Route118", "bola", None),
    ("HERACRONITE", "Route119", "bola", None),
    ("SCIZORITE", "Route119", "bola", None),
    ("VICTREEBELITE", "Route119", "bola", None),
    ("CHESNAUGHTITE", "Route119", "oculta", None),
    ("SCEPTILITE", "Route119", "bola", None),
    ("ABSOLITE", "Route120", "bola", None),
    ("ABSOLITE_Z", "Route120", "oculta", None),
    ("LUCARIONITE", "Route120", "bola", None),
    ("PIDGEOTITE", "Route123", "bola", None),
    ("STARAPTITE", "Route123", "bola", None),
    ("KANGASKHANITE", "SafariZone_Southwest", "bola", None),
    ("PINSIRITE", "SafariZone_Northwest", "bola", None),
    ("BANETTITE", "MtPyre_3F", "bola", None),
    ("CHANDELURITE", "MtPyre_4F", "bola", None),
    ("GOLURKITE", "MtPyre_5F", "bola", None),
    ("DELPHOXITE", "MtPyre_2F", "bola", None),
    ("CHIMECHITE", "MtPyre_Summit", "bola", None),
    ("GENGARITE", "MtPyre_6F", "oculta", None),
    ("BLAZIKENITE", "MagmaHideout_3F_3R", "bola", None),
    ("SWAMPERTITE", "AquaHideout_B1F", "bola", None),
    ("MALAMARITE", "LilycoveCity", "oculta", None),
    ("GLALITITE", "ShoalCave_LowTideIceRoom", "bola", None),
    ("ABOMASITE", "ShoalCave_LowTideIceRoom", "bola", None),
    ("FROSLASSITE", "ShoalCave_LowTideLowerRoom", "bola", None),
    ("CRABOMINITE", "ShoalCave_LowTideInnerRoom", "bola", None),
    ("BAXCALIBRITE", "ShoalCave_LowTideStairsRoom", "bola", None),
    ("SHARPEDONITE", "Underwater_Route124", "oculta", None),
    ("TATSUGIRINITE", "Underwater_Route126", "oculta", None),
    ("DRAGALGITE", "Route124", "bola", None),
    ("SLOWBRONITE", "Route126", "bola", None),
    ("FERALIGITE", "Route125", "bola", None),
    ("BLASTOISINITE", "Route127", "bola", None),
    ("GYARADOSITE", "Route127", "oculta", None),
    ("METAGROSSITE", "MossdeepCity", "oculta", None),
    ("STARMINITE", "Route130", "bola", None),
    ("ALTARIANITE", "SkyPillar_3F", "bola", None),
    ("DRAGONINITE", "SkyPillar_5F", "bola", None),
    ("DRAMPANITE", "SkyPillar_1F", "bola", None),
    ("GALLADITE", "VictoryRoad_1F", "bola", None),
    ("GARDEVOIRITE", "VictoryRoad_1F", "bola", None),
    ("GARCHOMPITE_Z", "VictoryRoad_B1F", "bola", None),
    ("LUCARIONITE_Z", "VictoryRoad_B2F", "bola", None),
    ("FALINKSITE", "VictoryRoad_B1F", "oculta", None),
    ("MEDICHAMITE", "VictoryRoad_B2F", "bola", None),
    ("SALAMENCITE", "MeteorFalls_B1F_2R", "bola", None),
]

# Objetos competitivos de generaciones nuevas (misma estructura). Los más fuertes (Pañuelo
# Elegido, Chaleco Asalto, Gafas Elegidas, Vidasfera) van a partir del tramo 6.
COMPETITIVOS = [
    ("EVIOLITE", "Route116", "bola", None),
    ("FOCUS_SASH", "DewfordTown", "oculta", None),
    ("PUNCHING_GLOVE", "DewfordTown", "bola", None),
    ("MUSCLE_BAND", "Route106", "bola", None),
    ("BLUNDER_POLICY", "Route109", "oculta", None),
    ("RED_CARD", "SlateportCity", "oculta", None),
    ("WISE_GLASSES", "SlateportCity_OceanicMuseum_2F", "bola", None),
    ("WEAKNESS_POLICY", "Route110", "bola", None),
    ("EJECT_BUTTON", "Route110", "bola", None),
    ("TOXIC_ORB", "Route117", "bola", None),
    ("JOLLY_MINT", "Route117", "bola", None),
    ("TIMID_MINT", "Route117", "oculta", None),
    ("EJECT_PACK", "Route117", "oculta", None),
    ("THROAT_SPRAY", "VerdanturfTown", "oculta", None),
    ("LOADED_DICE", "MauvilleCity_GameCorner", "oculta", None),
    ("FLAME_ORB", "FieryPath", "bola", None),
    ("HEAT_ROCK", "MtChimney", "bola", None),
    ("SMOOTH_ROCK", "Route111", "bola", "DESERT|SANDSTORM|STARDUST"),
    ("SAFETY_GOGGLES", "Route111", "bola", "DESERT|SANDSTORM|STARDUST"),
    ("ROCKY_HELMET", "Route111", "bola", None),
    ("LIGHT_CLAY", "Route112", "bola", None),
    ("PROTECTIVE_PADS", "Route112", "oculta", None),
    ("WIDE_LENS", "Route113", "oculta", None),
    ("HEAVY_DUTY_BOOTS", "Route114", "bola", None),
    ("EXPERT_BELT", "Route115", "bola", None),
    ("BLACK_SLUDGE", "AbandonedShip_Corridors_B1F", "oculta", None),
    ("ELECTRIC_SEED", "NewMauville_Inside", "bola", None),
    ("BOOSTER_ENERGY", "NewMauville_Inside", "bola", None),
    ("AIR_BALLOON", "Route119_WeatherInstitute_2F", "bola", None),
    ("UTILITY_UMBRELLA", "Route119_WeatherInstitute_1F", "oculta", None),
    ("CHOICE_SCARF", "Route118", "bola", None),
    ("BIG_ROOT", "Route119", "bola", None),
    ("IMPISH_MINT", "Route119", "bola", None),
    ("CAREFUL_MINT", "Route119", "oculta", None),
    ("DAMP_ROCK", "Route120", "bola", None),
    ("ASSAULT_VEST", "Route120", "bola", None),
    ("GRASSY_SEED", "Route123", "bola", None),
    ("MIRROR_HERB", "Route123", "bola", None),
    ("BOLD_MINT", "Route123", "bola", None),
    ("CALM_MINT", "Route123", "oculta", None),
    ("CHOICE_SPECS", "Route121", "bola", None),
    ("ADAMANT_MINT", "SafariZone_South", "bola", None),
    ("MODEST_MINT", "SafariZone_Southeast", "oculta", None),
    ("LIFE_ORB", "MtPyre_Exterior", "bola", None),
    ("MISTY_SEED", "MtPyre_Summit", "oculta", None),
    ("ROOM_SERVICE", "LilycoveCity", "oculta", None),
    ("COVERT_CLOAK", "AquaHideout_B2F", "bola", None),
    ("ICY_ROCK", "ShoalCave_LowTideIceRoom", "bola", None),
    ("PSYCHIC_SEED", "MossdeepCity", "oculta", None),
    ("ZOOM_LENS", "MossdeepCity_SpaceCenter_1F", "bola", None),
    ("ABILITY_CAPSULE", "SootopolisCity", "oculta", None),
    ("CLEAR_AMULET", "MeteorFalls_B1F_1R", "bola", None),
    ("TERRAIN_EXTENDER", "SkyPillar_4F", "bola", None),
    ("ABILITY_SHIELD", "VictoryRoad_B1F", "bola", None),
    ("ABILITY_PATCH", "VictoryRoad_B2F", "oculta", None),
]

# Ticket-Recuerdo (es ITEM_HEART_SCALE con otro nombre). Aquí el primer campo no es el objeto
# sino el nombre del flag, porque todos son el mismo objeto. Uno por ruta en bola, y otro escondido
# en las rutas largas. Los ocultos van aparte porque su flag tiene que ser >= FLAG_HIDDEN_ITEMS_START.
TICKETS = [
    ("RUTA_101", "Route101", "bola", None),
    ("RUTA_102", "Route102", "bola", None),
    ("RUTA_103", "Route103", "bola", None),
    ("RUTA_104", "Route104", "bola", None),
    ("RUTA_105", "Route105", "bola", None),
    ("RUTA_106", "Route106", "bola", None),
    ("RUTA_107", "Route107", "bola", None),
    ("RUTA_108", "Route108", "bola", None),
    ("RUTA_109", "Route109", "bola", None),
    ("RUTA_110", "Route110", "bola", None),
    ("RUTA_111", "Route111", "bola", None),
    ("RUTA_112", "Route112", "bola", None),
    ("RUTA_113", "Route113", "bola", None),
    ("RUTA_114", "Route114", "bola", None),
    ("RUTA_115", "Route115", "bola", None),
    ("RUTA_116", "Route116", "bola", None),
    ("RUTA_117", "Route117", "bola", None),
    ("RUTA_118", "Route118", "bola", None),
    ("RUTA_119", "Route119", "bola", None),
    ("RUTA_120", "Route120", "bola", None),
    ("RUTA_121", "Route121", "bola", None),
    ("RUTA_122", "Route122", "bola", None),
    ("RUTA_123", "Route123", "bola", None),
    ("RUTA_124", "Route124", "bola", None),
    ("RUTA_125", "Route125", "bola", None),
    ("RUTA_126", "Route126", "bola", None),
    ("RUTA_127", "Route127", "bola", None),
    ("RUTA_128", "Route128", "bola", None),
    ("RUTA_129", "Route129", "bola", None),
    ("RUTA_130", "Route130", "bola", None),
    ("RUTA_131", "Route131", "bola", None),
    ("RUTA_132", "Route132", "bola", None),
    ("RUTA_133", "Route133", "bola", None),
    ("RUTA_134", "Route134", "bola", None),
]
TICKETS_OCULTOS = [
    ("RUTA_104_2", "Route104", "oculta", None),
    ("RUTA_110_2", "Route110", "oculta", None),
    ("RUTA_111_2", "Route111", "oculta", None),
    ("RUTA_113_2", "Route113", "oculta", None),
    ("RUTA_114_2", "Route114", "oculta", None),
    ("RUTA_117_2", "Route117", "oculta", None),
    ("RUTA_118_2", "Route118", "oculta", None),
    ("RUTA_119_2", "Route119", "oculta", None),
    ("RUTA_120_2", "Route120", "oculta", None),
    ("RUTA_121_2", "Route121", "oculta", None),
    ("RUTA_123_2", "Route123", "oculta", None),
]

# Cada grupo: (lista, prefijo del flag, primer flag, último flag del bloque libre, comentario,
# objeto fijo o None si el objeto es el primer campo de la lista)
GRUPOS = [
    (MEGAPIEDRAS, "FLAG_ITEM_MEGA_", 0x264, 0x2BB, "megapiedra en el mapa", None),
    (COMPETITIVOS, "FLAG_ITEM_COMP_", 0x493, 0x4E4, "objeto competitivo en el mapa", None),
    (TICKETS, "FLAG_ITEM_TICKET_", 0x021, 0x04F, "Ticket-Recuerdo en el mapa", "HEART_SCALE"),
    (TICKETS_OCULTOS, "FLAG_ITEM_TICKET_", 0x4E5, 0x4EF, "Ticket-Recuerdo oculto en el mapa", "HEART_SCALE"),
]
COMPORTAMIENTOS_OK = {"MB_NORMAL", "MB_TALL_GRASS", "MB_LONG_GRASS", "MB_SHORT_GRASS", "MB_DEEP_SAND",
                      "MB_SAND", "MB_CAVE", "MB_ASHGRASS", "MB_FOOTPRINTS"}


def comportamientos():
    with open("include/constants/metatile_behaviors.h", encoding="utf-8") as f:
        texto = f.read()
    cuerpo = texto[texto.index("{", texto.index("enum")) + 1:texto.index("}")]
    nombres = [n.strip().split("=")[0].strip() for n in cuerpo.split(",")]
    nombres = [re.sub(r"//.*", "", n).strip() for n in nombres]
    return {n: i for i, n in enumerate(n for n in nombres if n)}


def atributos_tilesets():
    """Devuelve {gTileset_X: lista de comportamientos por metatile}."""
    with open("src/data/tilesets/metatiles.h", encoding="utf-8") as f:
        rutas = dict(re.findall(r"(gMetatileAttributes_\w+)\[\]\s*=\s*INCBIN_U16\(\"([^\"]+)\"\)", f.read()))
    with open("src/data/tilesets/headers.h", encoding="utf-8") as f:
        cabeceras = f.read()
    resultado = {}
    for nombre, cuerpo in re.findall(r"const struct Tileset (gTileset_\w+)\s*=\s*\{(.*?)\};", cabeceras, re.S):
        attr = re.search(r"\.metatileAttributes\s*=\s*(gMetatileAttributes_\w+)", cuerpo)
        if attr and attr.group(1) in rutas and os.path.exists(rutas[attr.group(1)]):
            datos = open(rutas[attr.group(1)], "rb").read()
            resultado[nombre] = [v & 0xFF for v in struct.unpack(f"<{len(datos) // 2}H", datos)]
    return resultado


def cargar_layouts():
    with open("data/layouts/layouts.json", encoding="utf-8") as f:
        return {l["id"]: l for l in json.load(f)["layouts"] if "id" in l}


def buscar_casilla(mapa, layout, tilesets, mb, tipo, pista, ocupadas):
    ancho, alto = layout["width"], layout["height"]
    datos = open(layout["blockdata_filepath"], "rb").read()
    celdas = struct.unpack(f"<{ancho * alto}H", datos)
    prim = tilesets.get(layout["primary_tileset"], [])
    sec = tilesets.get(layout["secondary_tileset"], [])

    def info(x, y):
        v = celdas[y * ancho + x]
        mt = v & 0x3FF
        comp = (prim[mt] if mt < 512 and mt < len(prim) else
                sec[mt - 512] if mt >= 512 and mt - 512 < len(sec) else -1)
        return (v >> 10) & 3, v >> 12, comp

    ok = {mb[n] for n in COMPORTAMIENTOS_OK if n in mb}
    anclas = [(o["x"], o["y"], o.get("flag", "") + o.get("trainer_sight_or_berry_tree_id", ""))
              for o in mapa.get("object_events", [])
              if o.get("graphics_id") == "OBJ_EVENT_GFX_ITEM_BALL" or o.get("trainer_type", "TRAINER_TYPE_NONE") != "TRAINER_TYPE_NONE"]
    anclas += [(b["x"], b["y"], b.get("flag", "")) for b in mapa.get("bg_events", []) if b.get("type") == "hidden_item"]
    # Si no hay objetos ni entrenadores, las puertas, escaleras y PNJ también se alcanzan
    anclas += [(w["x"], w["y"], "") for w in mapa.get("warp_events", [])]
    anclas += [(o["x"], o["y"], "") for o in mapa.get("object_events", [])]
    if pista:
        preferidas = [a for a in anclas if re.search(pista, a[2])]
        anclas = preferidas + [a for a in anclas if a not in preferidas]
    distancia = (1, 4) if tipo == "bola" else (3, 8)
    # Primero solo suelo firme (hierba, arena, cueva…); si no hay, también casillas como la del
    # ancla (agua, puentes), para que en las rutas de mar no salgan flotando si hay una playa
    for solo_suelo in (True, False):
        sitio = _buscar_desde_anclas(anclas, info, ancho, alto, ok, distancia, ocupadas, solo_suelo)
        if sitio:
            return sitio
    return None


def _buscar_desde_anclas(anclas, info, ancho, alto, ok, distancia, ocupadas, solo_suelo):
    for ax, ay, _ in anclas:
        if not (0 <= ax < ancho and 0 <= ay < alto):
            continue
        _, elev, comp_ancla = info(ax, ay)
        if elev in (0, 15):
            # Puertas y escaleras tienen altura "de transición": se usa la del suelo de al lado
            vecinas = [info(ax + dx, ay + dy)[1] for dx, dy in ((0, 1), (0, -1), (1, 0), (-1, 0))
                       if 0 <= ax + dx < ancho and 0 <= ay + dy < alto and info(ax + dx, ay + dy)[0] == 0
                       and info(ax + dx, ay + dy)[1] not in (0, 15)]
            if not vecinas:
                continue
            elev = vecinas[0]
        vistos = {(ax, ay)}
        cola = deque([(ax, ay, 0)])
        while cola:
            x, y, d = cola.popleft()
            if distancia[0] <= d <= distancia[1] and (x, y) not in ocupadas:
                col, e, comp = info(x, y)
                if col == 0 and e == elev and (comp in ok or (not solo_suelo and comp == comp_ancla)):
                    return x, y, elev
            if d >= distancia[1]:
                continue
            for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                nx, ny = x + dx, y + dy
                if 0 <= nx < ancho and 0 <= ny < alto and (nx, ny) not in vistos:
                    col, e, _ = info(nx, ny)
                    if col == 0 and e == elev:
                        vistos.add((nx, ny))
                        cola.append((nx, ny, d + 1))
    return None


def insertar_en_lista(crudo, clave, objeto):
    """Añade un elemento al final de la lista `clave` del map.json sin tocar el resto del formato."""
    salto = "\r\n" if "\r\n" in crudo else "\n"
    inicio = crudo.index(f'"{clave}": [') + len(f'"{clave}": [')
    nivel, i = 1, inicio
    while nivel:
        nivel += {"[": 1, "]": -1}.get(crudo[i], 0)
        i += 1
    fin = i - 1  # posición del ] que cierra la lista
    elemento = salto.join("    " + l for l in json.dumps(objeto, indent=2, ensure_ascii=False).splitlines())
    if crudo[inicio:fin].strip():
        return crudo[:inicio] + crudo[inicio:fin].rstrip() + "," + salto + elemento + salto + "  " + crudo[fin:]
    return crudo[:inicio] + salto + elemento + salto + "  " + crudo[fin:]


def asegurar_flags(lista, prefijo, primero, ultimo, comentario, fijo=None):
    ruta = "include/constants/flags.h"
    with open(ruta, encoding="utf-8", newline="") as f:
        texto = f.read()
    for i, (objeto, _, _, _) in enumerate(lista):
        valor = primero + i
        assert valor <= ultimo, f"no quedan flags libres en el bloque 0x{primero:03X}-0x{ultimo:03X}"
        nombre = f"{prefijo}{objeto}"
        if nombre in texto:
            continue
        antigua = re.search(rf"^#define FLAG_UNUSED_0x{valor:03X}\s+0x{valor:X}\b.*$", texto, re.M)
        assert antigua, f"el flag 0x{valor:03X} ya no está libre"
        texto = texto.replace(antigua.group(0),
                              f"#define {nombre:<34} 0x{valor:03X} // Dualocke: {comentario}")
    with open(ruta, "w", encoding="utf-8", newline="") as f:
        f.write(texto)


def main():
    solo_resumen = "--resumen" in sys.argv
    mb = comportamientos()
    tilesets = atributos_tilesets()
    layouts = cargar_layouts()
    fallos = []
    colocadas = {}  # en --resumen no se escribe el mapa: así no se repiten casillas
    if not solo_resumen:
        for grupo in GRUPOS:
            asegurar_flags(*grupo)
    todos = [(objeto, carpeta, tipo, pista, prefijo, fijo or objeto)
             for lista, prefijo, _, _, _, fijo in GRUPOS for objeto, carpeta, tipo, pista in lista]
    for piedra, carpeta, tipo, pista, prefijo, item in todos:
        ruta = f"data/maps/{carpeta}/map.json"
        with open(ruta, encoding="utf-8", newline="") as f:
            crudo = f.read()
        mapa = json.loads(crudo)
        flag = f"{prefijo}{piedra}"
        if flag in crudo:
            print(f"{piedra:16s} ya está en {carpeta}")
            continue
        ocupadas = {(o["x"], o["y"]) for o in mapa.get("object_events", [])}
        ocupadas |= {(b["x"], b["y"]) for b in mapa.get("bg_events", [])}
        ocupadas |= {(w["x"], w["y"]) for w in mapa.get("warp_events", [])}
        ocupadas |= {(c["x"], c["y"]) for c in mapa.get("coord_events", [])}
        ocupadas |= {(x, y) for x, y in colocadas.get(carpeta, [])}
        sitio = buscar_casilla(mapa, layouts[mapa["layout"]], tilesets, mb, tipo, pista, ocupadas)
        if not sitio:
            fallos.append(f"{piedra} ({carpeta})")
            continue
        x, y, elev = sitio
        colocadas.setdefault(carpeta, []).append((x, y))
        print(f"{piedra:16s} {tipo:6s} {carpeta} ({x}, {y})")
        if solo_resumen:
            continue
        if tipo == "bola":
            nuevo = insertar_en_lista(crudo, "object_events", {
                "graphics_id": "OBJ_EVENT_GFX_ITEM_BALL", "x": x, "y": y, "elevation": elev,
                "movement_type": "MOVEMENT_TYPE_LOOK_AROUND", "movement_range_x": 0, "movement_range_y": 0,
                "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": f"ITEM_{item}",
                "script": "Common_EventScript_FindItem", "flag": flag})
        else:
            nuevo = insertar_en_lista(crudo, "bg_events", {
                "type": "hidden_item", "x": x, "y": y, "elevation": elev, "item": f"ITEM_{item}", "flag": flag})
        json.loads(nuevo)  # comprobación: sigue siendo JSON válido
        with open(ruta, "w", encoding="utf-8", newline="") as f:
            f.write(nuevo)
    if fallos:
        print("\nSin sitio (hay que colocarlas a mano):", ", ".join(fallos))


if __name__ == "__main__":
    main()
