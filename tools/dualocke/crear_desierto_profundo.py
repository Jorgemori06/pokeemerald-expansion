#!/usr/bin/env python3
"""
Dualocke: el DESIERTO PROFUNDO y las RUINAS ARENOSAS (ZONAS.md, propuesta 5 y ruinas; Miguel, 16/11/2026).

Uso (desde la raíz del repo; se puede volver a lanzar):
    python3 tools/dualocke/crear_desierto_profundo.py

- **Entrada:** un montículo con puerta en la parte este del desierto de la RUTA 111, copia del de las
  RUINAS DESIERTO. Se llega con las GAFAS AISLANTES (tramo 5).
- **DESIERTO PROFUNDO** (24 × 68): el desierto de la RUTA 111 (x 16-39, y 30-97), sin la TORRE
  ESPEJISMO ni los huecos de base secreta. Tormenta de arena (tormenta en combate). La puerta del
  montículo de abajo (el de las RUINAS DESIERTO en la RUTA 111) es la salida; en el norte hay otro
  montículo que lleva a las ruinas.
- **Dunas y arenas movedizas (Miguel, 21/11/2026).** Antes era igual que el desierto de la RUTA 111 y se
  andaba hasta las ruinas. Ahora:
  - todo es arena clara, con dunas, y una fila de peñas (BARRERA_FILAS) corta el paso al norte, donde
    están las ruinas;
  - las **arenas movedizas** son los únicos hoyos de arena honda (HOYOS): al pisar el centro te traga y
    caes a la **CUEVA** de abajo, cada una a una sala distinta;
  - la **CUEVA** (DesiertoProfundo_Cueva) es un trozo del PASO DESIERTO, la cueva de arena del juego,
    partida en tres salas con rocas. Cada sala tiene una escalera: dos te devuelven a la entrada del
    desierto y solo una (la de la arena movediza buena) sale al norte, junto a las ruinas.
- **RUINAS ARENOSAS:** las cuatro plantas de la TORRE ESPEJISMO: la entrada, dos plantas con suelo
  agrietado (si se rompe, caes a la de abajo; en la tercera hay rocas de GOLPE ROCA) y la CÁMARA,
  la sala del fósil, donde está el guardián: un Pokémon fuerte que se puede capturar (como en las
  islas del ferry, data/scripts/dualocke_islas.inc).
- **Zonas de captura propias:** MAPSEC_DESIERTO_PROFUNDO y MAPSEC_RUINAS_ARENOSAS, al final de la lista.
- Los mapas van al final de su grupo y de layouts.json.
Los entrenadores, los salvajes y los objetos los ponen zonas_nuevas.py y colocar_objetos.py.
"""

import json
import os
import struct
import sys

sys.path.insert(0, "tools/dualocke")
import colocar_objetos as co  # noqa: E402
import variantes  # noqa: E402

DESIERTO, RUINAS, CAMARA = "DesiertoProfundo", "RuinasArenosas", "RuinasArenosas_Camara"
PLANTA2, PLANTA3 = "RuinasArenosas_2F", "RuinasArenosas_3F"
CUEVA = "DesiertoProfundo_Cueva"
MAPAS = {DESIERTO: "MAP_DESIERTO_PROFUNDO", RUINAS: "MAP_RUINAS_ARENOSAS", CAMARA: "MAP_RUINAS_ARENOSAS_CAMARA",
         PLANTA2: "MAP_RUINAS_ARENOSAS_2F", PLANTA3: "MAP_RUINAS_ARENOSAS_3F", CUEVA: "MAP_DESIERTO_PROFUNDO_CUEVA"}
# --- Dunas y arenas movedizas (Miguel, 21/11/2026) ---
ARENA_CLARA = 0x3121                     # la arena clara del desierto (se pisa sin hundirse)
HONDA = (0x248, 0x249, 0x24A, 0x250, 0x251, 0x252, 0x258, 0x259, 0x25A)   # la arena honda y su borde
HOYO = ((0x248, 0x249, 0x24A), (0x250, 0x251, 0x252), (0x258, 0x259, 0x25A))   # un hoyo de 3 × 3
PENA = ((0x24B, 0x24C), (0x090, 0x092))  # peña de 2 × 2 del desierto
PIEDRA = 0x0E2                           # piedrecita (rellena un hueco de una casilla en la barrera)
BARRERA_FILAS = (22, 23)                 # la fila de peñas que corta el paso al norte
# Centro de cada arena movediza -> dónde caes en la CUEVA. La buena es la primera: su sala sale al norte.
HOYOS = {(17, 44): (33, 10), (5, 27): (5, 10), (14, 33): (17, 10), (9, 40): (8, 12)}
LLEGADA_INICIO, LLEGADA_RUINAS = (13, 50), (6, 16)   # dónde sales al subir por las escaleras de la cueva
CUEVA_TROZO = ("DesertUnderpass", 99, 40)            # mapa, x de inicio y ancho (todo el alto)
ROCA_CUEVA = 0x0602                                  # rocas que separan las salas
CUEVA_ROCAS = [(12, 10), (12, 11), (12, 12), (26, 9), (26, 10), (0, 10), (0, 11), (0, 12), (0, 13)]
ESCALERA = 0x323E
# Escaleras de la cueva: la de la sala buena (warp 0) sale junto a las ruinas; las otras, a la entrada
ESCALERAS = [((34, 8), "ruinas"), ((3, 4), "inicio"), ((21, 14), "inicio")]
# Plantas con suelo agrietado: como en la TORRE ESPEJISMO, al romperse caes a la planta de abajo
AGUJEROS = """{carpeta}_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_TRANSITION, CaveHole_FixCrackedGround
	map_script MAP_SCRIPT_ON_RESUME, {carpeta}_SetHoleWarp
	.byte 0

@ Dualocke: RUINAS ARENOSAS (tools/dualocke/crear_desierto_profundo.py). Si el suelo se rompe, caes abajo
{carpeta}_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp {abajo}
	end
"""
CAJA = (16, 30, 40, 98)                  # trozo de la RUTA 111 (x0, y0, x1, y1)
TORRE = range(0x3D8, 0x3F3)              # metatiles de la TORRE ESPEJISMO
ARENA = 0x251                            # arena lisa del desierto
BASE_SECRETA = 0x1A8                     # hueco de base secreta en la roca
MONTICULO = (27, 84, 32, 88)             # montículo con puerta de las RUINAS DESIERTO en la RUTA 111
PUERTA_MONTICULO = (2, 3)                # la puerta dentro del montículo
SITIO_RUTA111 = (31, 76)                 # dónde va el montículo nuevo en la RUTA 111
SITIO_RUINAS = (10, 8)                   # dónde va el montículo de las ruinas en el DESIERTO PROFUNDO


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


def guardar_layout(carpeta, ancho, alto, celdas, base):
    os.makedirs(f"data/layouts/{carpeta}", exist_ok=True)
    with open(f"data/layouts/{carpeta}/map.bin", "wb") as f:
        f.write(struct.pack(f"<{ancho * alto}H", *celdas))
    with open(base["border_filepath"], "rb") as f, open(f"data/layouts/{carpeta}/border.bin", "wb") as g:
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


def monticulo(c111, w111):
    x0, y0, x1, y1 = MONTICULO
    return [[c111[y * w111 + x] for x in range(x0, x1)] for y in range(y0, y1)]


def estampar(celdas, ancho, bloque, x0, y0):
    for dy, fila in enumerate(bloque):
        for dx, v in enumerate(fila):
            celdas[(y0 + dy) * ancho + x0 + dx] = v


def crear_desierto():
    l111, c111 = celdas_de("Route111")
    w111 = l111["width"]
    x0, y0, x1, y1 = CAJA
    ancho, alto = x1 - x0, y1 - y0
    celdas = [c111[y * w111 + x] for y in range(y0, y1) for x in range(x0, x1)]
    # Si ya se lanzó, la RUTA 111 tiene el montículo nuevo dentro de la caja: en el desierto, arena
    sx, sy = SITIO_RUTA111[0] - x0, SITIO_RUTA111[1] - y0
    mx0, my0, mx1, my1 = MONTICULO
    bloque = monticulo(c111, w111)
    if all(c111[(SITIO_RUTA111[1] + dy) * w111 + SITIO_RUTA111[0] + dx] == bloque[dy][dx]
           for dy in range(my1 - my0) for dx in range(mx1 - mx0)):
        for dy in range(my1 - my0):
            for dx in range(mx1 - mx0):
                celdas[(sy + dy) * ancho + sx + dx] = ARENA | (3 << 12)
    for i, v in enumerate(celdas):
        if (v & 0x3FF) in TORRE:
            celdas[i] = ARENA | (3 << 12)
        elif (v & 0x3FF) == BASE_SECRETA:
            celdas[i] = celdas[i - 1]
    estampar(celdas, ancho, monticulo(c111, w111), *SITIO_RUINAS)
    dunas(celdas, ancho, alto)
    return guardar_layout(DESIERTO, ancho, alto, celdas, l111), (ancho, alto)


def dunas(celdas, ancho, alto):
    """Arena clara, la barrera de peñas y los hoyos de arena movediza."""
    mt = lambda x, y: celdas[y * ancho + x] & 0x3FF  # noqa: E731
    # Fuera la arena honda y las peñas y piedras sueltas: todo arena clara
    for y in range(alto):
        for x in range(ancho):
            m = mt(x, y)
            if m in PENA[0] and y + 1 < alto and mt(x, y + 1) in PENA[1]:
                celdas[(y + 1) * ancho + x] = ARENA_CLARA
            if m in HONDA or m in PENA[0] or m == PIEDRA:
                celdas[y * ancho + x] = ARENA_CLARA
    arena = lambda x, y: mt(x, y) == ARENA_CLARA & 0x3FF  # noqa: E731
    # La barrera: peñas de 2 × 2 en toda la arena de esas dos filas (y una piedra si sobra una casilla)
    y0 = BARRERA_FILAS[0]
    xs = [x for x in range(ancho) if arena(x, y0) and arena(x, y0 + 1)]
    assert xs == list(range(xs[0], xs[-1] + 1)), "la barrera tiene que cruzar la arena de lado a lado"
    x = xs[0]
    while x <= xs[-1]:
        if x + 1 <= xs[-1]:
            for dy in (0, 1):
                for dx in (0, 1):
                    celdas[(y0 + dy) * ancho + x + dx] = 0x0400 | PENA[dy][dx]
            x += 2
        else:
            for dy in (0, 1):
                celdas[(y0 + dy) * ancho + x] = 0x0400 | PIEDRA
            x += 1
    # Los hoyos de arena movediza
    for (cx, cy) in HOYOS:
        for dy in range(3):
            for dx in range(3):
                x, y = cx - 1 + dx, cy - 1 + dy
                assert arena(x, y), ("la arena movediza no cabe ahí", cx, cy)
                celdas[y * ancho + x] = 0x3000 | HOYO[dy][dx]
    for x, y in (LLEGADA_INICIO, LLEGADA_RUINAS):
        assert arena(x, y), ("la llegada desde la cueva no está en la arena", x, y)


def crear_cueva():
    """La CUEVA de abajo: un trozo del PASO DESIERTO partido en tres salas, con sus escaleras."""
    origen, x0, ancho = CUEVA_TROZO
    l, c = celdas_de(origen)
    w, alto = l["width"], l["height"]
    celdas = [c[y * w + x] for y in range(alto) for x in range(x0, x0 + ancho)]
    for x, y in CUEVA_ROCAS:
        celdas[y * ancho + x] = ROCA_CUEVA
    for (x, y), _ in ESCALERAS:
        assert not (celdas[y * ancho + x] >> 10) & 3, ("la escalera no está en el suelo", x, y)
        celdas[y * ancho + x] = ESCALERA
    # Cada sala por separado: desde la caída buena solo se llega a la escalera que sale a las ruinas
    libre = lambda x, y: 0 <= x < ancho and 0 <= y < alto and not (celdas[y * ancho + x] >> 10) & 3  # noqa: E731
    def sala(p):
        vistos, cola = {p}, [p]
        while cola:
            x, y = cola.pop()
            for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
                if libre(*n) and n not in vistos:
                    vistos.add(n)
                    cola.append(n)
        return vistos
    for caida in HOYOS.values():
        s = sala(caida)
        llega = {destino for (xy, destino) in ESCALERAS if xy in s}
        buena = caida == next(iter(HOYOS.values()))
        assert llega == ({"ruinas"} if buena else {"inicio"}), ("salas mal separadas", caida, llega)
    return guardar_layout(CUEVA, ancho, alto, celdas, l)


def copiar_layout(carpeta, base_mapa):
    base, celdas = celdas_de(base_mapa)
    return guardar_layout(carpeta, base["width"], base["height"], celdas, base)


def mapa_json(carpeta, datos):
    ruta = f"data/maps/{carpeta}/map.json"
    os.makedirs(f"data/maps/{carpeta}", exist_ok=True)
    anteriores = json.loads(leer(ruta)) if os.path.exists(ruta) else {}
    datos["object_events"] = anteriores.get("object_events", [])
    datos["bg_events"] = anteriores.get("bg_events", [])
    escribir(ruta, json.dumps(datos, indent=2, ensure_ascii=False) + "\n")
    if not os.path.exists(f"data/maps/{carpeta}/scripts.inc"):
        escribir(f"data/maps/{carpeta}/scripts.inc", f"{carpeta}_MapScripts::\n\t.byte 0\n")


def puerta_en(x, y):
    return x + PUERTA_MONTICULO[0], y + PUERTA_MONTICULO[1]


def crear_mapas(layout_desierto, layout_ruinas, layout_camara, layout_2f, layout_3f, layout_cueva):
    salida = (MONTICULO[0] + PUERTA_MONTICULO[0] - CAJA[0], MONTICULO[1] + PUERTA_MONTICULO[1] - CAJA[1])
    a_ruinas = puerta_en(*SITIO_RUINAS)
    comun = {"region": "REGION_HOENN", "requires_flash": False, "allow_cycling": True, "allow_escaping": True,
             "allow_running": True, "show_map_name": True, "battle_scene": "MAP_BATTLE_SCENE_NORMAL",
             "connections": None, "coord_events": []}
    mapa_json(DESIERTO, {
        "id": MAPAS[DESIERTO], "name": DESIERTO, "layout": layout_desierto, "music": "MUS_ROUTE110",
        "region_map_section": "MAPSEC_DESIERTO_PROFUNDO", "weather": "WEATHER_SANDSTORM",
        "map_type": "MAP_TYPE_ROUTE", **comun,
        "warp_events": [
            {"x": salida[0], "y": salida[1], "elevation": 0, "dest_map": "MAP_ROUTE111", "dest_warp_id": "5"},
            {"x": a_ruinas[0], "y": a_ruinas[1], "elevation": 0, "dest_map": MAPAS[RUINAS], "dest_warp_id": "0"},
            # 2 y 3: donde sales al subir por las escaleras de la cueva (en la arena: no te mandan a ningún sitio)
            {"x": LLEGADA_INICIO[0], "y": LLEGADA_INICIO[1], "elevation": 0, "dest_map": MAPAS[CUEVA],
             "dest_warp_id": "1"},
            {"x": LLEGADA_RUINAS[0], "y": LLEGADA_RUINAS[1], "elevation": 0, "dest_map": MAPAS[CUEVA],
             "dest_warp_id": "0"}]})
    # Las arenas movedizas: al pisar el centro, a la cueva
    ruta = f"data/maps/{DESIERTO}/map.json"
    m = json.loads(leer(ruta))
    m["coord_events"] = [{"type": "trigger", "x": x, "y": y, "elevation": 3, "var": "VAR_TEMP_1", "var_value": "0",
                          "script": f"{DESIERTO}_EventScript_Arena{i}"} for i, (x, y) in enumerate(HOYOS)]
    escribir(ruta, json.dumps(m, indent=2, ensure_ascii=False) + "\n")
    ruta = f"data/maps/{DESIERTO}/scripts.inc"
    texto = leer(ruta)
    marca = "@ Dualocke: arenas movedizas"
    if marca in texto:
        texto = texto[:texto.index(marca)].rstrip("\n") + "\n"
    texto += "\n" + marca + " (crear_desierto_profundo.py; Miguel, 21/11/2026)\n"
    for i, (x, y) in enumerate(HOYOS.values()):
        texto += (f"{DESIERTO}_EventScript_Arena{i}::\n\tlockall\n\tplayse SE_M_SAND_ATTACK\n"
                  f"\tmsgbox {DESIERTO}_Text_Arena, MSGBOX_DEFAULT\n\tcloseMessage\n\tplayse SE_FALL\n"
                  f"\twarp {MAPAS[CUEVA]}, {x}, {y}\n\twaitstate\n\treleaseall\n\tend\n\n").replace("closeMessage", "closemessage")
    texto += (f"{DESIERTO}_Text_Arena:\n\t.string \"¡La arena se hunde!\\n\"\n"
              "\t.string \"¡Es arena movediza!$\"\n")
    escribir(ruta, texto)
    mapa_json(CUEVA, {
        "id": MAPAS[CUEVA], "name": CUEVA, "layout": layout_cueva, "music": "MUS_MT_CHIMNEY",
        "region_map_section": "MAPSEC_DESIERTO_PROFUNDO", "weather": "WEATHER_NONE",
        "map_type": "MAP_TYPE_UNDERGROUND", **comun,
        "warp_events": [{"x": x, "y": y, "elevation": 0, "dest_map": MAPAS[DESIERTO],
                         "dest_warp_id": "3" if destino == "ruinas" else "2"} for (x, y), destino in ESCALERAS]})
    mapa_json(RUINAS, {
        "id": MAPAS[RUINAS], "name": RUINAS, "layout": layout_ruinas, "music": "MUS_MT_CHIMNEY",
        "region_map_section": "MAPSEC_RUINAS_ARENOSAS", "weather": "WEATHER_NONE",
        "map_type": "MAP_TYPE_UNDERGROUND", **comun,
        "warp_events": [
            {"x": 10, "y": 14, "elevation": 3, "dest_map": MAPAS[DESIERTO], "dest_warp_id": "1"},
            {"x": 15, "y": 2, "elevation": 3, "dest_map": MAPAS[PLANTA2], "dest_warp_id": "1"}]})
    # Las dos plantas de en medio: mismas escaleras que en la TORRE ESPEJISMO
    for carpeta, layout, abajo, warps in (
            (PLANTA2, layout_2f, MAPAS[RUINAS],
             [{"x": 18, "y": 12, "elevation": 3, "dest_map": MAPAS[PLANTA3], "dest_warp_id": "0"},
              {"x": 15, "y": 2, "elevation": 3, "dest_map": MAPAS[RUINAS], "dest_warp_id": "1"}]),
            (PLANTA3, layout_3f, MAPAS[PLANTA2],
             [{"x": 18, "y": 12, "elevation": 3, "dest_map": MAPAS[PLANTA2], "dest_warp_id": "0"},
              {"x": 2, "y": 4, "elevation": 3, "dest_map": MAPAS[CAMARA], "dest_warp_id": "0"}])):
        if not os.path.exists(f"data/maps/{carpeta}/scripts.inc"):
            os.makedirs(f"data/maps/{carpeta}", exist_ok=True)
            escribir(f"data/maps/{carpeta}/scripts.inc", AGUJEROS.format(carpeta=carpeta, abajo=abajo))
        mapa_json(carpeta, {
            "id": MAPAS[carpeta], "name": carpeta, "layout": layout, "music": "MUS_MT_CHIMNEY",
            "region_map_section": "MAPSEC_RUINAS_ARENOSAS", "weather": "WEATHER_NONE",
            "map_type": "MAP_TYPE_UNDERGROUND", **comun, "warp_events": warps})
    # Las rocas de GOLPE ROCA de la planta 3, como en la torre
    ruta = f"data/maps/{PLANTA3}/map.json"
    if "OBJ_EVENT_GFX_BREAKABLE_ROCK" not in leer(ruta):
        texto = leer(ruta)
        for o in json.loads(leer("data/maps/MirageTower_3F/map.json"))["object_events"]:
            texto = co.insertar_en_lista(texto, "object_events", o)
        json.loads(texto)
        escribir(ruta, texto)
    mapa_json(CAMARA, {
        "id": MAPAS[CAMARA], "name": CAMARA, "layout": layout_camara, "music": "MUS_MT_CHIMNEY",
        "region_map_section": "MAPSEC_RUINAS_ARENOSAS", "weather": "WEATHER_NONE",
        "map_type": "MAP_TYPE_UNDERGROUND", **comun,
        "warp_events": [{"x": 1, "y": 4, "elevation": 3, "dest_map": MAPAS[PLANTA3], "dest_warp_id": "1"}]})

    grupos = leer("data/maps/map_groups.json")
    salto = "\r\n" if "\r\n" in grupos else "\n"
    for carpeta in (DESIERTO, RUINAS, CAMARA, PLANTA2, PLANTA3, CUEVA):
        if f'"{carpeta}"' in grupos:
            continue
        d = json.loads(grupos)
        ultimo = d["gMapGroup_Dungeons"][-1]
        a = f'"{ultimo}"{salto}'
        i = grupos.index(a, grupos.index('"gMapGroup_Dungeons": ['))
        grupos = grupos[:i] + f'"{ultimo}",{salto}    "{carpeta}"{salto}' + grupos[i + len(a):]
    json.loads(grupos)
    escribir("data/maps/map_groups.json", grupos)
    # El script de la cueva en event_scripts.s
    texto = leer("data/event_scripts.s")
    linea = f'\t.include "data/maps/{CUEVA}/scripts.inc" @ Dualocke: zona nueva'
    if linea not in texto:
        salto = "\r\n" if "\r\n" in texto else "\n"
        a = '\t.include "data/maps/RuinasArenosas_3F/scripts.inc" @ Dualocke: zona nueva' + salto
        assert texto.count(a) == 1
        escribir("data/event_scripts.s", texto.replace(a, a + linea + salto))


def entrada_ruta111():
    l111, c111 = celdas_de("Route111")
    w = l111["width"]
    x, y = SITIO_RUTA111
    bloque = monticulo(c111, w)
    # En todos los dibujos de la RUTA 111: al derrumbarse la TORRE ESPEJISMO el juego pasa a usar
    # LAYOUT_ROUTE111_NO_MIRAGE_TOWER, y sin esto la puerta desaparecía (lo vio Miguel, 20/11/2026)
    for ident in variantes.layouts_de("Route111"):
        l = LAYOUTS[ident]
        c = list(struct.unpack(f"<{l['width'] * l['height']}H", open(l["blockdata_filepath"], "rb").read()))
        estampar(c, w, bloque, x, y)
        with open(l["blockdata_filepath"], "wb") as f:
            f.write(struct.pack(f"<{w * l['height']}H", *c))
    ruta = "data/maps/Route111/map.json"
    texto = leer(ruta)
    if MAPAS[DESIERTO] not in texto:
        px, py = puerta_en(x, y)
        texto = co.insertar_en_lista(texto, "warp_events", {"x": px, "y": py, "elevation": 0,
                                                            "dest_map": MAPAS[DESIERTO], "dest_warp_id": "0"})
        json.loads(texto)
        escribir(ruta, texto)
    # La salida del DESIERTO PROFUNDO vuelve a este montículo: comprobar que es el warp 5
    warps = json.loads(leer(ruta))["warp_events"]
    assert warps[5]["dest_map"] == MAPAS[DESIERTO], "el warp de la RUTA 111 no es el 5"


def zonas_region():
    ruta = "src/data/region_map/region_map_sections.json"
    texto = leer(ruta)
    for mapsec, nombre, y in (("MAPSEC_DESIERTO_PROFUNDO", "DESIERTO PROFUNDO", 3),
                              ("MAPSEC_RUINAS_ARENOSAS", "RUINAS ARENOSAS", 2)):
        if f'"{mapsec}"' not in texto:
            texto = co.insertar_en_lista(texto, "map_sections", {"id": mapsec, "name": nombre,
                                                                 "x": 9, "y": y, "width": 1, "height": 1})
    json.loads(texto)
    escribir(ruta, texto)


def main():
    layout_desierto, _ = crear_desierto()
    crear_mapas(layout_desierto, copiar_layout(RUINAS, "MirageTower_1F"), copiar_layout(CAMARA, "MirageTower_4F"),
                copiar_layout(PLANTA2, "MirageTower_2F"), copiar_layout(PLANTA3, "MirageTower_3F"), crear_cueva())
    entrada_ruta111()
    zonas_region()
    print("Dualocke: DESIERTO PROFUNDO y RUINAS ARENOSAS creados")


if __name__ == "__main__":
    main()
