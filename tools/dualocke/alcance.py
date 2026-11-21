#!/usr/bin/env python3
"""
Dualocke: desde qué tramo se puede llegar a cada entrenador, y si su nivel cuadra con ese tramo.

Uso (desde la raíz del repo):
    python3 tools/dualocke/alcance.py              # tabla de los entrenadores que van por encima
    python3 tools/dualocke/alcance.py --todos      # todos los entrenadores, con su tramo de alcance
    python3 tools/dualocke/alcance.py --comprobar  # sale con error si alguno va por encima (para el CI)

Por qué: reescalar_niveles.py pone el nivel según el tramo de cada MAPA, pero hay mapas que se
pisan en parte antes de su tramo (la Ruta 103 este, la orilla oeste de la Ruta 118 al salir de
MALVALONA…). Esto recorre el mundo casilla a casilla, como el jugador, con lo que se puede hacer
en cada tramo, y mira a qué entrenadores se llega (o quién te ve) antes de lo que les toca.

Cómo anda el jugador (simplificado, del motor):
- Colisión y elevación de cada casilla del mapa (map.bin). Las elevaciones 0 y 15 pasan a todas.
- Saltos (MB_JUMP_*): solo en su dirección, y se cae dos casillas más allá.
- Agua (TILE_FLAG_SURFABLE): con SURF. Cascadas, con CASCADA. Bucear, con BUCEO.
- Árboles de CORTE, rocas de GOLPE ROCA y rocas de FUERZA (objetos del mapa): con su MO.
- La tormenta de arena del desierto (SCRIPTS_QUE_BLOQUEAN): con las GAFAS AISLANTES.
- Barro y raíles de las bicis: con la bici (MALVALONA, tramo 3).
- Conexiones entre mapas, warps y los viajes con script de la tabla VIAJES (barco del SR. BRINEY,
  teleférico…).
No sabe nada de los PNJ que cortan el paso hasta un evento ni de los scripts que te echan para
atrás: puede dar alguno de más, que hay que mirar a mano (y apuntarlo en IGNORAR).

Un entrenador se alcanza cuando se puede pisar alguna casilla desde la que te ve (en línea recta,
hasta su distancia de visión, en las direcciones a las que mira) o una pegada a él (para hablarle).
"""

import argparse
import fnmatch
import glob
import json
import os
import re
import struct
import sys
from collections import deque

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import reescalar_niveles as rn  # noqa: E402
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import variantes  # noqa: E402

# Lo que se puede usar en cada tramo (tramo N = entre la medalla N-1 y la N)
MO = {
    "CORTE": 2,       # MT de CORTE en FÉRRICA y medalla PIEDRA
    "BICI": 3,        # tienda de bicis de MALVALONA
    "GOLPE_ROCA": 4,  # medalla DINAMO
    "FUERZA": 5,      # medalla CALOR
    "SURF": 6,        # medalla EQUILIBRIO
    "BUCEO": 8,       # medalla MENTE
    "CASCADA": 9,     # medalla LLUVIA
}

# Viajes con script (no son warps): (desde, hasta, tramo). Se llega a la casilla del primer warp del
# mapa de destino (la puerta del Centro POKéMON o similar).
VIAJES = [
    # Barco del SR. BRINEY: a AZULIZA tras FÉRRICA, y a PORTUAL tras AZULIZA. Se puede ir a PORTUAL
    # en cuanto se entrega la carta a MÁXIMO, sin la medalla de MARCIAL, pero lo normal es hacer
    # el gimnasio, que está en el pueblo donde te deja.
    ("MAP_ROUTE104", "MAP_DEWFORD_TOWN", 2),
    ("MAP_DEWFORD_TOWN", "MAP_ROUTE104", 2),
    ("MAP_DEWFORD_TOWN", "MAP_SLATEPORT_CITY", 3),
    ("MAP_SLATEPORT_CITY", "MAP_DEWFORD_TOWN", 3),
    # Teleférico de la RUTA 112 a la cima del MONTE CENIZO
    ("MAP_ROUTE112_CABLE_CAR_STATION", "MAP_MT_CHIMNEY_CABLE_CAR_STATION", 4),
    ("MAP_MT_CHIMNEY_CABLE_CAR_STATION", "MAP_ROUTE112_CABLE_CAR_STATION", 4),
    # Barca del muelle de PORTUAL a la ISLA VOLCÁNICA, desde la 7.ª medalla (crear_islas_sur.py; Miguel,
    # 21/11/2026). La isla ya no está pegada a la RUTA 134.
    ("MAP_SLATEPORT_CITY", "MAP_ISLA_VOLCANICA", 8),
    ("MAP_ISLA_VOLCANICA", "MAP_SLATEPORT_CITY", 8),
]

# Entrenadores que da por alcanzables antes de tiempo, pero que no lo son por la historia
# (un PNJ que corta el paso, un script…). TRAINER_X: por qué.
IGNORAR = {
    # La entrada de la GUARIDA MAGMA (SENDERO ESCARPADO) no se abre hasta el EMBLEMA MAGMA (tramo 7)
    **{f"TRAINER_GRUNT_MAGMA_HIDEOUT_{n}": "guarida Magma" for n in range(1, 17)},
    "TRAINER_TABITHA_MAGMA_HIDEOUT": "guarida Magma",
    # La GUARIDA AQUA la guardan dos soldados hasta lo del MONTE PÍRICO (tramo 7)
    **{f"TRAINER_GRUNT_AQUA_HIDEOUT_{n}": "guarida Aqua" for n in range(1, 9)},
    # Los soldados de la cima del MONTE PÍRICO solo están durante ese evento (tramo 7)
    "TRAINER_GRUNT_MT_PYRE_1": "evento del MONTE PÍRICO",
    # Las puertas de las salas del gimnasio de PETALIA están cerradas hasta tener 4 medallas
    **{t: "gimnasio de PETALIA" for t in ("TRAINER_RANDALL", "TRAINER_PARKER", "TRAINER_GEORGE",
                                         "TRAINER_BERKE", "TRAINER_MARY", "TRAINER_ALEXIA", "TRAINER_JODY")},
}

# Mapas a los que se llega antes de su tramo solo saltándose la historia. Con SURF (tramo 6) se
# puede ir por la RUTA 118 y la 123 hasta LIRIA, ALGARIA y todo el mar del sur sin pasar por
# ARBORADA (ALANA), pero la historia no va por ahí. Si alguien lo hace, la red del juego deja a
# los entrenadores como mucho al cap (Dualocke_CapTrainerMon, src/dualocke.c).
POR_HISTORIA = ["MAP_ROUTE121", "MAP_ROUTE122", "MAP_LILYCOVE_*", "MAP_MT_PYRE_*", "MAP_ROUTE12[4-9]",
                "MAP_ROUTE13[0-4]", "MAP_MOSSDEEP_*", "MAP_PACIFIDLOG_*",
                # Islas nuevas de Miguel (#83, #89; paso abierto en el #100), en esas mismas rutas de mar
                "MAP_ISLA_NEVADA*", "MAP_ISLA_ARENOSA*", "MAP_ISLA_DE_RUINAS*", "MAP_ISLA_VOLCANICA*"]

GFX_MO = {
    "OBJ_EVENT_GFX_CUTTABLE_TREE": "CORTE",
    "OBJ_EVENT_GFX_BREAKABLE_ROCK": "GOLPE_ROCA",
    "OBJ_EVENT_GFX_PUSHABLE_BOULDER": "FUERZA",
}
for _g, _mo in list(GFX_MO.items()):
    GFX_MO[_g + "_FRLG"] = _mo

# Casillas con script que no dejan pasar hasta cierto tramo: (trozo del nombre del script, tramo).
# La tormenta de arena del desierto de la RUTA 111 te echa para atrás sin las GAFAS AISLANTES, que
# dan después de CANDELA (tramo 5).
SCRIPTS_QUE_BLOQUEAN = [("ViciousSandstorm", 5)]

# Las elevaciones del motor (puentes, desniveles) no se siguen del todo bien: con ESTRICTO = False
# se ignoran entre tierra y tierra, así que puede dar de más (se miran a mano) pero no de menos.
ESTRICTO = False

CORRIENTES = {"MB_EASTWARD_CURRENT": "right", "MB_WESTWARD_CURRENT": "left",
              "MB_NORTHWARD_CURRENT": "up", "MB_SOUTHWARD_CURRENT": "down"}
DIRS = {"up": (0, -1), "down": (0, 1), "left": (-1, 0), "right": (1, 0)}
MIRA = {  # direcciones a las que mira cada tipo de movimiento (las demás, todas)
    "FACE_UP": "up", "FACE_DOWN": "down", "FACE_LEFT": "left", "FACE_RIGHT": "right",
    "FACE_DOWN_AND_UP": "down up", "FACE_LEFT_AND_RIGHT": "left right",
    "FACE_UP_AND_LEFT": "up left", "FACE_UP_AND_RIGHT": "up right",
    "FACE_DOWN_AND_LEFT": "down left", "FACE_DOWN_AND_RIGHT": "down right",
    "FACE_DOWN_UP_AND_LEFT": "down up left", "FACE_DOWN_UP_AND_RIGHT": "down up right",
    "FACE_UP_LEFT_AND_RIGHT": "up left right", "FACE_DOWN_LEFT_AND_RIGHT": "down left right",
    "WALK_UP_AND_DOWN": "up down", "WALK_LEFT_AND_RIGHT": "left right",
}


def comportamientos():
    with open("include/constants/metatile_behaviors.h", encoding="utf-8") as f:
        cuerpo = f.read().split("enum {", 1)[1].split("};", 1)[0]
    nombres = re.findall(r"^\s*(MB_\w+)", cuerpo, re.M)
    with open("src/metatile_behavior.c", encoding="utf-8") as f:
        texto = f.read()
    surf = set(re.findall(r"\[(MB_\w+)\]\s*=[^,\n]*TILE_FLAG_SURFABLE", texto))
    return nombres, surf


class Mundo:
    def __init__(self):
        self.nombres_mb, self.surf = comportamientos()
        self.carpeta_ts = self._carpetas_tilesets()
        self.attrs = {}
        with open("data/layouts/layouts.json", encoding="utf-8") as f:
            self.layouts = {l["id"]: l for l in json.load(f)["layouts"] if "id" in l}
        self.mapas = {}
        for ruta in glob.glob("data/maps/*/map.json"):
            with open(ruta, encoding="utf-8") as f:
                m = json.load(f)
            m["carpeta"] = os.path.dirname(ruta)
            self.mapas[m["id"]] = m
        self.rejillas = {}

    @staticmethod
    def _carpetas_tilesets():
        with open("src/data/tilesets/metatiles.h", encoding="utf-8") as f:
            rutas = dict(re.findall(r'(gMetatileAttributes_\w+)\[\]\s*=\s*INCBIN_U16\("([^"]+)"\)', f.read()))
        with open("src/data/tilesets/headers.h", encoding="utf-8") as f:
            cabeceras = f.read()
        resultado = {}
        for nombre, cuerpo in re.findall(r"const struct Tileset (gTileset_\w+)\s*=\s*\{(.*?)\};", cabeceras, re.S):
            attr = re.search(r"\.metatileAttributes\s*=\s*(gMetatileAttributes_\w+)", cuerpo)
            if attr and attr.group(1) in rutas:
                resultado[nombre] = rutas[attr.group(1)]
        return resultado

    def _atributos(self, ts):
        if ts not in self.attrs:
            with open(self.carpeta_ts[ts], "rb") as f:
                datos = f.read()
            self.attrs[ts] = struct.unpack(f"<{len(datos) // 2}H", datos)
        return self.attrs[ts]

    def rejilla(self, map_id):
        """(ancho, alto, [(colisión, elevación, comportamiento)])."""
        if map_id not in self.rejillas:
            ident = self.mapas[map_id]["layout"]
            # el dibujo que se ve en el juego, si el mapa lo cambia al entrar (RUTA 131; ver variantes.py)
            l = self.layouts[variantes.EN_JUEGO.get(ident, ident)]
            with open(l["blockdata_filepath"], "rb") as f:
                datos = f.read()
            bloques = struct.unpack(f"<{len(datos) // 2}H", datos)
            prim, sec = self._atributos(l["primary_tileset"]), self._atributos(l["secondary_tileset"])
            casillas = []
            for b in bloques:
                mt = b & 0x3FF
                tabla, i = (prim, mt) if mt < 512 else (sec, mt - 512)
                mb = self.nombres_mb[tabla[i] & 0xFF] if i < len(tabla) and (tabla[i] & 0xFF) < len(self.nombres_mb) else "MB_NORMAL"
                casillas.append(((b >> 10) & 3, b >> 12, mb))
            self.rejillas[map_id] = (l["width"], l["height"], casillas)
        return self.rejillas[map_id]

    def casilla(self, map_id, x, y):
        w, h, c = self.rejilla(map_id)
        return c[y * w + x] if 0 <= x < w and 0 <= y < h else None


def entrenadores_de_mapa(m):
    """[(TRAINER_X, objeto)] de los objetos del mapa que son entrenadores."""
    ruta = os.path.join(m["carpeta"], "scripts.inc")
    etiquetas = {}
    if os.path.exists(ruta):
        with open(ruta, encoding="utf-8") as f:
            texto = f.read()
        for nombre, cuerpo in re.findall(r"^(\w+)::\n(.*?)(?=^\w+::|\Z)", texto, re.M | re.S):
            ts = re.findall(r"^\s*trainerbattle\w*\s+(TRAINER_\w+)", cuerpo, re.M)
            if ts:
                etiquetas[nombre] = ts[0]
    resultado = []
    for o in m.get("object_events", []):
        if o.get("trainer_type", "TRAINER_TYPE_NONE") != "TRAINER_TYPE_NONE" and o.get("script") in etiquetas:
            resultado.append((etiquetas[o["script"]], o))
    return resultado


def alcanzables(mundo, tramo):
    """Conjunto de (mapa, x, y) que se pisan con lo que se puede hacer en `tramo`."""
    puede = {mo for mo, t in MO.items() if tramo >= t}
    bloqueos = {}  # (mapa, x, y) que bloquea un objeto que necesita una MO que aún no se tiene
    for mid, m in mundo.mapas.items():
        for o in m.get("object_events", []):
            mo = GFX_MO.get(o.get("graphics_id"))
            if mo and mo not in puede and isinstance(o.get("x"), int):
                bloqueos[(mid, o["x"], o["y"])] = True
        for e in m.get("coord_events", []):
            for trozo, t in SCRIPTS_QUE_BLOQUEAN:
                if trozo in e.get("script", "") and tramo < t:
                    bloqueos[(mid, e["x"], e["y"])] = True
    viajes = {}
    for desde, hasta, t in VIAJES:
        if tramo >= t:
            viajes.setdefault(desde, []).append(hasta)

    def warp_destino(mid, idx):
        m = mundo.mapas.get(mid)
        if not m:
            return None
        try:
            w = m.get("warp_events", [])[int(idx)]
        except (ValueError, IndexError):
            return None
        return (mid, w["x"], w["y"])

    warps = {mid: {(w["x"], w["y"]) for w in m.get("warp_events", [])} for mid, m in mundo.mapas.items()}
    inicio = warp_destino("MAP_LITTLEROOT_TOWN", 0)
    visto = set()
    cola = deque()

    def llegar(mid, x, y, elev, agua):
        c = mundo.casilla(mid, x, y)
        if c is None:
            return
        if c[1] not in (0, 15):
            elev = c[1]
        estado = (mid, x, y, elev, agua)
        if estado not in visto:
            visto.add(estado)
            cola.append(estado)

    llegar(*inicio, 0, False)
    pisadas = set()
    while cola:
        mid, x, y, elev, agua = cola.popleft()
        pisadas.add((mid, x, y))
        m = mundo.mapas[mid]
        # Warps: al pisar uno, al otro lado (no en la casilla de llegada de otro warp)
        for w in m.get("warp_events", []):
            if (w["x"], w["y"]) == (x, y) and w["dest_map"] in mundo.mapas:
                d = warp_destino(w["dest_map"], w["dest_warp_id"])
                if d:
                    llegar(*d, 0, False)
        for hasta in viajes.pop(mid, []):  # una vez por mapa basta
            d = warp_destino(hasta, 0)
            if d:
                llegar(*d, 0, False)
        # Bucear y salir a la superficie
        if agua and "BUCEO" in puede:
            mb = mundo.casilla(mid, x, y)[2]
            for con in m.get("connections") or []:
                if con["direction"] == "dive" and mb in ("MB_DEEP_WATER", "MB_INTERIOR_DEEP_WATER", "MB_SOOTOPOLIS_DEEP_WATER"):
                    llegar(con["map"], x, y, 0, True)
                if con["direction"] == "emerge" and mb != "MB_NO_SURFACING":
                    llegar(con["map"], x, y, 0, True)
        w, h, _ = mundo.rejilla(mid)
        # En una corriente solo se va hacia donde tira el agua
        actual = mundo.casilla(mid, x, y)[2]
        corriente = CORRIENTES.get(actual)
        for d, (dx, dy) in DIRS.items():
            if corriente and d != corriente:
                continue
            nx, ny, nmid = x + dx, y + dy, mid
            if not (0 <= nx < w and 0 <= ny < h):
                # Conexión con el mapa de al lado
                for con in m.get("connections") or []:
                    if con["direction"] != d or con["map"] not in mundo.mapas:
                        continue
                    cw, ch, _ = mundo.rejilla(con["map"])
                    if d in ("up", "down"):
                        tx, ty = nx - con["offset"], (ch - 1 if d == "up" else 0)
                    else:
                        tx, ty = (cw - 1 if d == "left" else 0), ny - con["offset"]
                    if 0 <= tx < cw and 0 <= ty < ch:
                        nmid, nx, ny = con["map"], tx, ty
                        break
                else:
                    continue
            c = mundo.casilla(nmid, nx, ny)
            col, el, mb = c
            if (nmid, nx, ny) in bloqueos:
                continue
            if (nx, ny) in warps.get(nmid, ()) and not agua:  # puertas (tienen colisión) y escaleras
                llegar(nmid, nx, ny, elev, agua)
                continue
            if mb.startswith("MB_JUMP_"):
                if mb == f"MB_JUMP_{ {'up': 'NORTH', 'down': 'SOUTH', 'left': 'WEST', 'right': 'EAST'}[d] }" and nmid == mid:
                    llegar(mid, nx + dx, ny + dy, elev, agua)
                continue
            if col:
                continue
            if mb == "MB_WATERFALL" and "CASCADA" not in puede:
                continue
            if (mb == "MB_MUDDY_SLOPE" or "RAIL" in mb) and "BICI" not in puede:
                continue
            es_agua = mb in mundo.surf
            if es_agua and not agua:
                if "SURF" in puede:  # empezar a hacer surf
                    llegar(nmid, nx, ny, el, True)
                continue
            if agua and not es_agua:  # bajarse del agua: solo a tierra de elevación 3
                if el == 3 or el in (0, 15):
                    llegar(nmid, nx, ny, el, False)
                continue
            if ESTRICTO and elev not in (0, 15) and el not in (0, 15) and el != elev:
                continue
            llegar(nmid, nx, ny, elev, agua)
    return pisadas


def casillas_de_vision(mundo, mid, o, sight):
    """Casillas desde las que un entrenador te ve o le puedes hablar."""
    x0, y0 = o["x"], o["y"]
    tipo = o.get("movement_type", "").replace("MOVEMENT_TYPE_", "")
    dirs = MIRA.get(tipo, "up down left right").split()
    resultado = set()
    for d, (dx, dy) in DIRS.items():
        resultado.add((mid, x0 + dx, y0 + dy))
        if d not in dirs:
            continue
        for i in range(1, sight + 1):
            c = mundo.casilla(mid, x0 + dx * i, y0 + dy * i)
            if c is None or c[0]:
                break
            resultado.add((mid, x0 + dx * i, y0 + dy * i))
    return resultado


def niveles_actuales():
    with open(rn.TRAINERS, encoding="utf-8") as f:
        return rn.leer_entrenadores(f.read())


def calcular():
    mundo = Mundo()
    por_tramo = {t: alcanzables(mundo, t) for t in range(1, 10)}
    niveles = niveles_actuales()
    filas = []
    for mid, m in sorted(mundo.mapas.items()):
        for trainer, o in entrenadores_de_mapa(m):
            if not isinstance(o.get("x"), int):
                continue
            try:
                sight = int(o.get("trainer_sight_or_berry_tree_id", 0))
            except ValueError:
                sight = 0
            vision = casillas_de_vision(mundo, mid, o, sight)
            tramo = next((t for t in range(1, 10) if vision & por_tramo[t]), None)
            lv = niveles.get(trainer)
            filas.append({"entrenador": trainer, "mapa": mid, "x": o["x"], "y": o["y"],
                          "tramo_alcance": tramo, "tramo_mapa": rn.tramo_de_mapa(mid),
                          "nivel_max": max(lv) if lv else None})
    return filas


def por_encima(fila):
    """El entrenador va por encima de lo que le toca al tramo en el que se le alcanza."""
    t, lv = fila["tramo_alcance"], fila["nivel_max"]
    if t is None or lv is None or fila["entrenador"] in IGNORAR:
        return False
    if any(fnmatch.fnmatchcase(fila["mapa"], p) for p in POR_HISTORIA) and t >= 6:
        return False
    return lv > rn.CAPS[t] - rn.MARGEN_NORMALES and not (
        fila["entrenador"] in rn.LIDERES or rn.es_jefe_medio(fila["entrenador"]) and lv <= rn.CAPS[t])


def main():
    p = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    p.add_argument("--todos", action="store_true")
    p.add_argument("--comprobar", action="store_true")
    p.add_argument("--json", help="guarda todas las filas en este archivo")
    a = p.parse_args()
    filas = calcular()
    if a.json:
        with open(a.json, "w", encoding="utf-8") as f:
            json.dump(filas, f, indent=1)
    malos = [f for f in filas if por_encima(f)]
    for f in (filas if a.todos else malos):
        marca = "  <-- POR ENCIMA" if por_encima(f) else ""
        print(f"{f['entrenador']:32} {f['mapa']:34} ({f['x']:3},{f['y']:3})  tramo mapa {f['tramo_mapa']}  "
              f"se alcanza en el {f['tramo_alcance']}  nivel {f['nivel_max']} (cap {rn.CAPS.get(f['tramo_alcance'])}){marca}")
    print(f"{len(malos)} entrenadores por encima de su tramo de alcance (de {len(filas)}).")
    if a.comprobar and malos:
        sys.exit(1)


if __name__ == "__main__":
    main()
