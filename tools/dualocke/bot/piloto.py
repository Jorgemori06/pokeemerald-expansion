#!/usr/bin/env python3
"""Piloto para jugar el Dualocke en el emulador sin pantalla, con la ROM normal (make release).

Lee la memoria del juego para saber dónde está el jugador, si hay textos, si está en combate, y
pulsa los botones como lo haría una persona. No escribe nada en la memoria del juego salvo los
cursores de los menús de combate y de la mochila (equivale a mover el cursor con las flechas).
"""
import bisect
import json
import os
import subprocess
import sys
from collections import deque

RAIZ_REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", ".."))
sys.path.insert(0, os.path.join(RAIZ_REPO, "tools/dualocke/emulador"))
sys.path.insert(0, os.path.join(RAIZ_REPO, "tools/dualocke"))
os.chdir(RAIZ_REPO)
from emulador import Emulador  # noqa: E402
import alcance as a  # noqa: E402
import sin_salida as ss  # noqa: E402

# carpeta de la partida: ROM, .elf, estados, diario y fotos (no se sube; ver README.md)
AQUI = os.environ.get("DUALOCKE_PARTIDA", os.path.join(RAIZ_REPO, "partida_bot"))
OFF = json.load(open(os.path.join(AQUI, "offsets.json")))
DATOS = json.load(open(os.path.join(AQUI, "datos.json")))
class _Movs(dict):
    def __missing__(self, k):
        return {"id": str(k), "nombre": f"mov{k}", "power": 0, "type": 1, "tipo": "TYPE_NORMAL", "acc": 100,
                "cat": "DAMAGE_CATEGORY_STATUS", "effect": "EFFECT_HIT", "pp": 10, "priority": 0, "golpes": 1}


MOVES = _Movs({int(k): v for k, v in DATOS["moves"].items()})
DIRS = {"arriba": (0, -1), "abajo": (0, 1), "izquierda": (-1, 0), "derecha": (1, 0)}
MUNDO = None


def mundo():
    global MUNDO
    if MUNDO is None:
        MUNDO = a.Mundo()
    return MUNDO


class Piloto(Emulador):
    def __init__(self, rom=os.path.join(AQUI, "partida.gba"), log=None):
        from emulador import gbarun, mapas
        self.rom = rom
        nm = subprocess.run(["arm-none-eabi-nm", "-n", rom[:-4] + ".elf"], capture_output=True, text=True).stdout
        funcs, todos = [], {}
        for l in nm.splitlines():
            p = l.split()
            if len(p) != 3:
                continue
            v = int(p[0], 16)
            nombre = p[2].split(".lto_priv")[0].split(".part")[0].split(".constprop")[0].split(".isra")[0]
            todos.setdefault(nombre, v)
            if p[1] in "tT":
                funcs.append((v, nombre))
        self.funcs = sorted(funcs)
        self.faddr = [f[0] for f in self.funcs]
        self.s = todos
        self.sim = todos
        self.porfunc = {}
        for v, n in self.funcs:
            self.porfunc.setdefault(n, set()).add(v | 1)
        self.elegir_accion = self.porfunc.get("HandleInputChooseAction", set())
        self.elegir_movimiento = self.porfunc.get("HandleInputChooseMove", set())
        self.elegir_objetivo = self.porfunc.get("HandleInputChooseTarget", set())
        self.ids = mapas()
        self.nombres = {v: k for k, v in self.ids.items()}
        self.proc = subprocess.Popen([gbarun(), rom], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
        self.log = log or os.path.join(AQUI, "diario.txt")
        self.bloqueos = set()
        self._efect = None
        self._especies = {}
        self.motes_usados = []

    # --- utilidades ---
    def apunta(self, texto):
        with open(self.log, "a", encoding="utf-8") as f:
            f.write(texto + "\n")
        print(texto, flush=True)

    def funcion(self, v):
        i = bisect.bisect_right(self.faddr, v & ~1) - 1
        return self.funcs[i][1] if i >= 0 else hex(v)

    def cb2(self):
        return self.funcion(self.leer(self.sim["gMain"] + 4, 32))

    def en_combate(self):
        return bool(self.leer(self.s["gMain"] + 0x439) & 2) or self.cb2() in (
            "BattleMainCB2", "CB2_InitBattle", "CB2_InitBattleInternal", "CB2_HandleStartBattle")

    def en_mapa(self):
        return (self.leer(self.s["gMain"] + 4, 32) | 1) == (self.s["CB2_Overworld"] | 1)

    def en_motes(self):
        return self.cb2() in ("CB2_NamingScreen", "CB2_LoadNamingScreen")

    def bloqueado(self):
        return self.leer(self.s["sLockFieldControls"]) != 0

    def mensaje(self):
        return self.leer(self.s["sFieldMessageBoxMode"]) != 0

    def controlable(self):
        return self.en_mapa() and not self.bloqueado() and not self.mensaje()

    def jugador(self):
        oid = self.leer(self.s["gPlayerAvatar"] + OFF["pa_objId"])
        b = self.s["gObjectEvents"] + oid * 0x24
        x = self.leer(b + 0x10, 16) - 7
        y = self.leer(b + 0x12, 16) - 7
        z = self.leer(b + 0x0B) & 0xF
        return x, y, z

    def pos(self):
        x, y, _ = self.jugador()
        return x, y

    def objetos(self):
        """[(x, y, localId, gfx)] de los personajes activos del mapa (sin el jugador)."""
        res = []
        oid = self.leer(self.s["gPlayerAvatar"] + OFF["pa_objId"])
        for i in range(16):
            b = self.s["gObjectEvents"] + i * 0x24
            if not (self.leer(b) & 1) or i == oid:
                continue
            res.append((self.leer(b + 0x10, 16) - 7, self.leer(b + 0x12, 16) - 7, self.leer(b + 8), self.leer(b + 4, 16)))
        return res

    def surfeando(self):
        return bool(self.leer(self.s["gPlayerAvatar"] + 0) & 0x08)

    # --- textos ---
    def pasar_textos(self, maximo=200, boton="a"):
        """Pulsa A hasta que se pueda mover (o empiece un combate)."""
        for _ in range(maximo):
            if self.en_combate():
                return "combate"
            if self.en_motes():
                self.poner_mote()
                continue
            if self.controlable():
                self.avanzar(4)
                if self.controlable():
                    return "libre"
            self.pulsar(boton, fotogramas=4, despues=12)
        return "atascado"

    def poner_mote(self):
        self.avanzar(40)
        for _ in range(3):
            self.pulsar("a", despues=12)
        self.pulsar("start", despues=20)
        self.pulsar("a", despues=80)

    # --- moverse ---
    def paso(self, d, correr=True):
        """Un paso; devuelve True si se movió (o cambió de mapa)."""
        antes = (self.mapa(), self.pos())
        teclas = [d] + (["b"] if correr else [])
        self.orden("keys %d" % sum({"a": 1, "b": 2, "select": 4, "start": 8, "derecha": 16, "izquierda": 32,
                                    "arriba": 64, "abajo": 128}[t] for t in teclas))
        for _ in range(40):
            self.avanzar(2)
            if (self.mapa(), self.pos()) != antes or not self.controlable():
                break
        self.orden("keys 0")
        for _ in range(30):
            self.avanzar(2)
            if self.controlable() or self.en_combate():
                break
        return (self.mapa(), self.pos()) != antes

    def mirando(self):
        oid = self.leer(self.s["gPlayerAvatar"] + OFF["pa_objId"])
        return {1: "abajo", 2: "arriba", 3: "izquierda", 4: "derecha"}.get(
            self.leer(self.s["gObjectEvents"] + oid * 0x24 + 0x18) & 0xF)

    def mirar(self, d):
        for f in (3, 3, 4, 5, 6):
            if self.mirando() == d:
                return True
            self.avanzar(6)
            self.pulsar(d, fotogramas=f, despues=10)
        return self.mirando() == d

# --- planificar caminos por el mundo ---
SALTOS = {"MB_JUMP_NORTH": "arriba", "MB_JUMP_SOUTH": "abajo", "MB_JUMP_EAST": "derecha", "MB_JUMP_WEST": "izquierda"}
FLECHAS = {"MB_SOUTH_ARROW_WARP": "abajo", "MB_NORTH_ARROW_WARP": "arriba", "MB_EAST_ARROW_WARP": "derecha",
           "MB_WEST_ARROW_WARP": "izquierda", "MB_WATER_SOUTH_ARROW_WARP": "abajo"}
CON = {"up": "arriba", "down": "abajo", "left": "izquierda", "right": "derecha"}


def info_mapa(mid):
    m = mundo().mapas[mid]
    w, h, c = mundo().rejilla(mid)
    warps = {}
    for i, wp in enumerate(m.get("warp_events", [])):
        warps.setdefault((wp["x"], wp["y"]), []).append((i, wp))
    cons = {}
    for c_ in (m.get("connections") or []):
        if c_["direction"] in CON:
            cons.setdefault(CON[c_["direction"]], []).append(c_)
    return w, h, c, warps, cons


def destino_warp(wp):
    dm = wp["dest_map"]
    if dm not in mundo().mapas:
        return None
    lista = mundo().mapas[dm].get("warp_events", [])
    try:
        d = lista[int(wp["dest_warp_id"])]
    except (ValueError, IndexError):
        return None
    return dm, d["x"], d["y"]


PUEDE_SURF = [False]


def puede_entrar(c, w, h, x, y, z, surf, desde_agua=False):
    """(entra, nueva_z) al pisar (x, y) con altura z."""
    if not (0 <= x < w and 0 <= y < h):
        return False, z
    col, e, mb = c[y * w + x]
    if col:
        return False, z
    agua = mb in mundo().surf
    if agua:
        if not (PUEDE_SURF[0] or desde_agua or surf):
            return False, z
        if not desde_agua:
            return True, e if e != 15 else z    # subirse a surfear
    elif desde_agua:
        return (e in (0, 3, 15)), (e if e != 15 else z)   # bajarse del agua
    if z not in (0, 15) and e not in (0, 15) and e != z:
        return False, z
    # como ObjectEventUpdateElevation: se coge la altura de la casilla salvo si es 15
    return True, (e if e != 15 else z)


CORRIENTES = {"MB_EASTWARD_CURRENT": "derecha", "MB_WESTWARD_CURRENT": "izquierda",
              "MB_NORTHWARD_CURRENT": "arriba", "MB_SOUTHWARD_CURRENT": "abajo"}


def vecinos(mid, x, y, z, surf, tapadas, bloqueos):
    w, h, c, warps, cons = info_mapa(mid)
    en_agua = c[y * w + x][2] in mundo().surf
    forzada = CORRIENTES.get(c[y * w + x][2])     # en una corriente solo se va hacia donde empuja
    for d, (dx, dy) in DIRS.items():
        if (mid, x, y, d) in bloqueos or (forzada and d != forzada):
            continue
        nx, ny = x + dx, y + dy
        if not (0 <= nx < w and 0 <= ny < h):
            for con in cons.get(d, []):
                if con["map"] not in mundo().mapas:
                    continue
                dm = con["map"]
                w2, h2, c2 = mundo().rejilla(dm)
                o = con["offset"]
                tx, ty = {"arriba": (x - o, h2 - 1), "abajo": (x - o, 0),
                          "izquierda": (w2 - 1, y - o), "derecha": (0, y - o)}[d]
                if not (0 <= tx < w2 and 0 <= ty < h2):
                    continue
                ok, z2 = puede_entrar(c2, w2, h2, tx, ty, z, surf, en_agua)
                if ok:
                    yield d, (dm, tx, ty, z2)
            continue
        col, e, mb = c[ny * w + nx]
        if mb in SALTOS:
            if SALTOS[mb] == d:
                jx, jy = nx + dx, ny + dy
                # el salto no mira la altura de donde caes (CheckForObjectEventCollision devuelve LEDGE_JUMP antes)
                ok, z2 = puede_entrar(c, w, h, jx, jy, 0, surf, en_agua)
                if ok and (jx, jy) not in tapadas:
                    yield d, (mid, jx, jy, z2)
            continue
        if (nx, ny) in tapadas:
            continue
        if (nx, ny) in warps and not en_agua:
            # puerta o escalera: se entra pisándola (aunque tenga colisión, como las puertas)
            yield d, (mid, nx, ny, z if e in (0, 15) else e)
            continue
        if (nx, ny) in tapadas:
            continue
        if mb == "MB_MUDDY_SLOPE" and d != "abajo":
            continue
        if mb == "MB_WATERFALL" and d == "arriba" and not PUEDE_CASCADA[0]:
            continue
        if mb == "MB_BUMPY_SLOPE":      # hace falta la Bici Acrobática
            continue
        ok, z2 = puede_entrar(c, w, h, nx, ny, z, surf, en_agua)
        if ok and mb == "MB_ICE":
            # hielo resbaladizo: se sigue deslizando hasta chocar o salir del hielo
            cx, cy = nx, ny
            while c[cy * w + cx][2] == "MB_ICE":
                tx, ty = cx + dx, cy + dy
                if not (0 <= tx < w and 0 <= ty < h) or (tx, ty) in tapadas or (tx, ty) in warps:
                    break
                ok2, z3 = puede_entrar(c, w, h, tx, ty, z2, surf, False)
                if not ok2:
                    break
                cx, cy, z2 = tx, ty, z3
            yield d, (mid, cx, cy, z2)
        elif ok:
            yield d, (mid, nx, ny, z2)


PUEDE_BUCEAR = [False]
SIN_VIAJES = [False]
PUEDE_CASCADA = [False]
BUCEABLE = ("MB_INTERIOR_DEEP_WATER", "MB_DEEP_WATER", "MB_SOOTOPOLIS_DEEP_WATER")
NO_EMERGER = ("MB_NO_SURFACING", "MB_SEAWEED_NO_SURFACING")
# setdivewarp de los scripts: se usan cuando el mapa no tiene conexión de buceo/emerger
BUCEO_FIJO = {
    "MAP_UNDERWATER_SEAFLOOR_CAVERN": ("MAP_SEAFLOOR_CAVERN_ENTRANCE", 10, 17),
    "MAP_UNDERWATER_SOOTOPOLIS_CITY": ("MAP_SOOTOPOLIS_CITY", 29, 53),
    "MAP_UNDERWATER_ROUTE134": ("MAP_ROUTE134", 60, 31),
    "MAP_SEAFLOOR_CAVERN_ENTRANCE": ("MAP_UNDERWATER_SEAFLOOR_CAVERN", 6, 5),
    "MAP_SOOTOPOLIS_CITY": ("MAP_UNDERWATER_SOOTOPOLIS_CITY", 9, 6),
    "MAP_ROUTE134": ("MAP_UNDERWATER_ROUTE134", 8, 6),
}


def buceos(mid, x, y):
    """[(\"bucear\"|\"emerger\", mapa, x, y)] desde (x, y) con BUCEO."""
    if not PUEDE_BUCEAR[0]:
        return []
    m = mundo().mapas[mid]
    w, h, c = mundo().rejilla(mid)
    mb = c[y * w + x][2]
    bajo = m.get("map_type") == "MAP_TYPE_UNDERWATER"
    if not bajo and mb not in BUCEABLE:
        return []
    if bajo and mb in NO_EMERGER:
        return []
    tipo = "emerger" if bajo else "bucear"
    for con in (m.get("connections") or []):
        if con["direction"] == ("emerge" if bajo else "dive") and con["map"] in mundo().mapas:
            return [(tipo, con["map"], x, y)]
    if mid in BUCEO_FIJO:
        return [(tipo,) + BUCEO_FIJO[mid]]
    return []


def _saltos_por_script():
    """Casillas de las zonas nuevas con un script que te lleva a otro sitio al pisarlas (arenas movedizas
    del DESIERTO PROFUNDO...): {mapa: {(x, y): (destino, x, y)}}."""
    import glob
    import re as _r
    nuevos = ("Marisma", "Playa", "Bosque", "Isla", "Cumbre", "Desierto", "Ruinas", "Gruta", "Mansion", "Cienaga",
              "Cantera", "Prado")
    res = {}
    for carpeta in glob.glob(os.path.join(RAIZ_REPO, "data/maps/*/")):
        nombre = os.path.basename(carpeta.rstrip("/"))
        if not nombre.startswith(nuevos) or not os.path.exists(carpeta + "scripts.inc"):
            continue
        m = json.load(open(carpeta + "map.json"))
        txt = open(carpeta + "scripts.inc").read()
        for c in m.get("coord_events") or []:
            sc = c.get("script")
            i = txt.find(sc + "::")
            if not sc or i < 0:
                continue
            bloque = txt[i:txt.find("\n\n", i)]
            w = _r.search(r"warp\w*\s+(MAP_\w+),\s*(\d+),\s*(\d+)", bloque)
            if w:
                res.setdefault(m["id"], {})[(c["x"], c["y"])] = (w.group(1), int(w.group(2)), int(w.group(3)))
    return res


SALTOS_SCRIPT = _saltos_por_script()


VIAJES = {   # mapa -> [(destino, x, y, (x, y) de con quién hablar)]
    "MAP_ROUTE112_CABLE_CAR_STATION": [("MAP_MT_CHIMNEY_CABLE_CAR_STATION", 6, 7, (6, 6))],
    "MAP_MT_CHIMNEY_CABLE_CAR_STATION": [("MAP_ROUTE112_CABLE_CAR_STATION", 6, 7, (6, 6))],
    # barca de la ISLA VOLCÁNICA (desde la 7.ª medalla)
    "MAP_SLATEPORT_CITY": [("MAP_ISLA_VOLCANICA", 20, 24, (37, 40))],  # barquero nuevo (Miguel, #116)
    "MAP_ISLA_VOLCANICA": [("MAP_SLATEPORT_CITY", 36, 40, (21, 24))],
}


def planear(origen, objetivo, surf=False, tapadas_mapa=None, bloqueos=frozenset(), max_estados=400000, solo_mapa=None):
    """Camino de pasos [(dir, estado)] de origen (mid, x, y, z) a objetivo: función estado -> bool, o (mid, x, y)."""
    if isinstance(objetivo, tuple):
        om, ox, oy = objetivo
        es_obj = lambda s: s[0] == om and s[1] == ox and s[2] == oy  # noqa: E731
    else:
        es_obj = objetivo
    tapadas_mapa = tapadas_mapa or {}
    prev = {origen: None}
    cola = deque([origen])
    while cola and len(prev) < max_estados:
        s = cola.popleft()
        if es_obj(s) and s != origen:
            camino = []
            while prev[s] is not None:
                d, p = prev[s]
                camino.append((d, s))
                s = p
            return camino[::-1]
        mid, x, y, z = s
        # casilla con script que te lleva a otro sitio (arenas movedizas...)
        if (x, y) in SALTOS_SCRIPT.get(mid, {}) and prev[s] is not None:
            dm, dx_, dy_ = SALTOS_SCRIPT[mid][(x, y)]
            if not (solo_mapa and dm != solo_mapa):
                n = (dm, dx_, dy_, 0)
                if n not in prev:
                    prev[n] = ("warp", s)
                    cola.append(n)
            continue
        # un warp lleva a otro mapa (si no es el de origen recién pisado)
        w_, h_, c_, warps, _ = info_mapa(mid)
        if (x, y) in warps and prev[s] is not None and prev[s][0] != "warp" and (c_[y * w_ + x][2] != "MB_NORMAL" or c_[y * w_ + x][0]):
            for i, wp in warps[(x, y)]:
                if wp["elevation"] not in (0, z) and z not in (0, 15):
                    continue
                dst = destino_warp(wp)
                if dst:
                    dm, dx_, dy_ = dst
                    w2, h2, c2 = mundo().rejilla(dm)
                    e2 = c2[dy_ * w2 + dx_][1]
                    n = (dm, dx_, dy_, e2 if e2 != 15 else 0)
                    if solo_mapa and dm != solo_mapa:
                        continue
                    if n not in prev:
                        prev[n] = ("warp", s)
                        cola.append(n)
            continue
        if prev[s] is None or prev[s][0] not in ("bucear", "emerger"):
            for tipo, dm, dx_, dy_ in buceos(mid, x, y):
                w2, h2, c2 = mundo().rejilla(dm)
                if not (0 <= dx_ < w2 and 0 <= dy_ < h2):
                    continue
                e2 = c2[dy_ * w2 + dx_][1]
                n = (dm, dx_, dy_, e2 if e2 != 15 else 0)
                if n not in prev:
                    prev[n] = (tipo, s)
                    cola.append(n)
        if (prev[s] is None or prev[s][0] != "viaje") and not SIN_VIAJES[0]:
            for dm, dx_, dy_, quien in VIAJES.get(mid, []):
                n = (dm, dx_, dy_, 3)
                if n not in prev:
                    prev[n] = ("viaje", s)
                    cola.append(n)
        for d, n in vecinos(mid, x, y, z, surf, tapadas_mapa.get(mid, set()), bloqueos):
            if solo_mapa and n[0] != solo_mapa:
                continue
            if n not in prev:
                prev[n] = (d, s)
                cola.append(n)
    return None


# --- nombre en el teclado ---
TECLADO = ["ABCDEF .", "GHIJKL ,", "MNOPQRS ", "TUVWXYZ "]


def teclear(e, texto, inicio=(0, 0)):
    """Escribe texto (las minúsculas en la misma casilla que su mayúscula: el teclado pasa solo a
    minúsculas tras la primera letra) y pulsa OK."""
    x, y = inicio
    for ch in texto.upper():
        ty = next(i for i, f in enumerate(TECLADO) if ch in f)
        tx = TECLADO[ty].index(ch)
        while y < ty:
            e.pulsar("abajo", despues=6); y += 1
        while y > ty:
            e.pulsar("arriba", despues=6); y -= 1
        while x < tx:
            e.pulsar("derecha", despues=6); x += 1
        while x > tx:
            e.pulsar("izquierda", despues=6); x -= 1
        e.pulsar("a", despues=40)
    e.pulsar("start", despues=20)
    e.pulsar("a", despues=60)


def refrescar_mapa(e, maximo=8000):
    """Rehace la rejilla del mapa actual con lo que hay en memoria (barreras que se abren, rocas...)."""
    mid = e.mapa()
    M = mundo()
    w, h, c = M.rejilla(mid)
    if w * h > maximo:
        return
    b = e.s["gBackupMapLayout"]
    W = e.leer(b, 32)
    H = e.leer(b + 4, 32)
    ptr = e.leer(b + 8, 32)
    if W != w + 15 or H != h + 14:
        return
    l = M.layouts[M.mapas[mid]["layout"]]
    prim, sec = M._atributos(l["primary_tileset"]), M._atributos(l["secondary_tileset"])
    nuevo = []
    for y in range(h):
        dir_ = ptr + 2 * ((y + 7) * W + 7)
        fila = leer_bloque(e, dir_ & ~3, 2 * w + 8)[dir_ & 3:]
        for x in range(w):
            v = int.from_bytes(fila[2 * x:2 * x + 2], "little")
            mt = v & 0x3FF
            tabla, i = (prim, mt) if mt < 512 else (sec, mt - 512)
            mb = M.nombres_mb[tabla[i] & 0xFF] if i < len(tabla) and (tabla[i] & 0xFF) < len(M.nombres_mb) else "MB_NORMAL"
            nuevo.append(((v >> 10) & 3, v >> 12, mb))
    M.rejillas[mid] = (w, h, nuevo)


# --- ir a un sitio ---
def evitar_base(e):
    """Casillas que echan para atrás por la historia (tormenta de arena sin GAFAS AISLANTES...)."""
    res = {}
    if not flag(e, "FLAG_RECEIVED_GO_GOGGLES"):
        m = _mapa_json("MAP_ROUTE111")
        res["MAP_ROUTE111"] = {(c_["x"], c_["y"]) for c_ in m.get("coord_events", []) if "Vicious" in (c_.get("script") or "")}
    return res


def hacia(x, y, tx, ty):
    dx, dy = tx - x, ty - y
    if abs(dx) >= abs(dy):
        return "derecha" if dx > 0 else "izquierda"
    return "abajo" if dy > 0 else "arriba"


def sabe_mo(e, mov):
    n = DATOS["ids"].get(mov)
    return any(n in m["movs"] for m in equipo(e) if m["hp"] and not m["huevo"])


def ir_a(e, objetivo, surf=None, max_intentos=60, correr=True, al_lado=False):
    """Anda hasta objetivo ((mapa, x, y) o función estado->bool). Si al_lado, hasta una casilla
    junto a (x, y) y mira hacia ella. Devuelve 'ok', 'combate', 'texto', o 'sin camino'."""
    if al_lado and isinstance(objetivo, tuple):
        om, ox, oy = objetivo
        w_, h_, c_, _, _ = info_mapa(om)

        def obj(s):
            if s[0] != om:
                return False
            dx, dy = ox - s[1], oy - s[2]
            if abs(dx) + abs(dy) == 1:
                return True
            if (dx == 0 and abs(dy) == 2) or (dy == 0 and abs(dx) == 2):
                mx, my = s[1] + dx // 2, s[2] + dy // 2
                return 0 <= my * w_ + mx < len(c_) and c_[my * w_ + mx][2] == "MB_COUNTER"
            return False
    else:
        obj = objetivo
    for intento in range(max_intentos):
        r = e.pasar_textos() if not e.controlable() else "libre"
        if r == "combate":
            return "combate"
        mid = e.mapa()
        PUEDE_SURF[0] = sabe_mo(e, "MOVE_SURF") and flag(e, "FLAG_BADGE05_GET")
        PUEDE_BUCEAR[0] = sabe_mo(e, "MOVE_DIVE") and flag(e, "FLAG_BADGE07_GET")
        PUEDE_CASCADA[0] = sabe_mo(e, "MOVE_WATERFALL") and flag(e, "FLAG_BADGE08_GET")
        refrescar_mapa(e)
        x, y, z = e.jugador()
        s_ = surf if surf is not None else e.surfeando()
        estado = (mid, x, y, z)
        if (obj(estado) if callable(obj) else (mid, x, y) == obj):
            break
        evitar = {k: set(v) for k, v in getattr(e, "evitar", {}).items()}
        for k, v in evitar_base(e).items():
            evitar.setdefault(k, set()).update(v)
        tap = {k: set(v) for k, v in evitar.items()}
        tap.setdefault(mid, set()).update((ox_, oy_) for ox_, oy_, _, _ in e.objetos())
        mismo = objetivo[0] if isinstance(objetivo, tuple) and objetivo[0] == mid else None
        camino = None
        if mismo:     # objetivo en este mismo mapa: primero sin salir de él (mucho más rápido)
            camino = planear(estado, obj, surf=s_, tapadas_mapa=tap, bloqueos=e.bloqueos, solo_mapa=mismo)
        if camino is None:
            camino = planear(estado, obj, surf=s_, tapadas_mapa=tap, bloqueos=e.bloqueos,
                             max_estados=60000 if mismo else 400000)
        if camino is None:
            # sin contar personajes, pero sin atravesar rocas de FUERZA (empujarlas mal puede cerrar el camino)
            nb_ = _GFX_N["OBJ_EVENT_GFX_PUSHABLE_BOULDER"]
            tapb = {k: set(v) for k, v in evitar.items()}
            tapb.setdefault(mid, set()).update((ox_, oy_) for ox_, oy_, _, g_ in e.objetos() if g_ == nb_)
            camino = planear(estado, obj, surf=s_, tapadas_mapa=tapb, bloqueos=e.bloqueos,
                             max_estados=60000 if mismo else 400000)
        if camino is None:
            camino = planear(estado, obj, surf=s_, tapadas_mapa={k: set(v) for k, v in evitar.items()}, bloqueos=e.bloqueos,
                             max_estados=60000 if mismo else 400000)
            if camino is None:
                # encima de una puerta que no me ha llevado (llegué empujando rocas...): salir y volver a pisarla
                if (x, y) in info_mapa(mid)[3] and not getattr(e, "_repisando", False):
                    OPU = {"arriba": "abajo", "abajo": "arriba", "izquierda": "derecha", "derecha": "izquierda"}
                    e._repisando = True
                    try:
                        for d_ in ("abajo", "izquierda", "derecha", "arriba"):
                            if e.paso(d_, correr=False):
                                e.paso(OPU[d_], correr=False)
                                e.avanzar(40)
                                if e.mapa() == mid:
                                    e.paso(OPU[d_], correr=False)
                                    e.avanzar(40)
                                break
                    finally:
                        e._repisando = False
                    continue
                return "sin camino"
        if getattr(e, "depurar", False):
            e.apunta(f"    [ir_a] {mid} {(x, y, z)} -> {objetivo if isinstance(objetivo, tuple) else 'f'}: {[ (d_, s__[1:3]) for d_, s__ in camino[:4]]}")
        for d, sig in camino:
            if d in ("bucear", "emerger"):
                mm = e.mapa()
                e.pulsar("a" if d == "bucear" else "b", despues=40)
                for _ in range(80):
                    if e.mapa() != mm and e.controlable():
                        break
                    e.pulsar("a", despues=20)
                e.avanzar(30)          # sin seguir(): pulsar B bajo el agua es emerger
                if e.mapa() != sig[0]:
                    break
                continue
            if d == "viaje":
                quien = next(q for dm, _, _, q in VIAJES[e.mapa()] if dm == sig[0])
                mm = e.mapa()
                SIN_VIAJES[0] = True          # para llegar hasta quien te lleva no vale otro viaje
                try:
                    ir_a(e, (mm,) + tuple(quien), al_lado=True, max_intentos=6)
                finally:
                    SIN_VIAJES[0] = False
                e.mirar(hacia(e.pos()[0], e.pos()[1], quien[0], quien[1]))
                pulsar_a(e, intentos=2)
                for _ in range(80):
                    if e.mapa() != mm and e.controlable():
                        break
                    e.pulsar("a", despues=20)
                seguir(e)
                if e.mapa() != sig[0]:
                    break
                continue
            if d == "warp":
                # el warp de una puerta ya se cruzó al pisarla; si es de flecha o escalera, empujar
                for _ in range(15):          # géiseres y agujeros tardan en llevarte
                    e.avanzar(10)
                    if e.mapa() == sig[0] or e.controlable():
                        break
                if e.mapa() != sig[0]:
                    w_, h_, c_, _, _ = info_mapa(e.mapa())
                    px, py = e.pos()
                    mb = c_[py * w_ + px][2] if 0 <= px < w_ and 0 <= py < h_ else ""
                    ult = FLECHAS.get(mb, ultimo_dir)
                    e.paso(ult, correr=False)
                    e.avanzar(30)
                if e.mapa() != sig[0]:
                    break
                continue
            ultimo_dir = d
            antes = (e.mapa(), e.pos())
            w_, h_, c_, _, _ = info_mapa(e.mapa())
            px, py = e.pos()
            dx, dy = DIRS[d]
            if (sig[0] == e.mapa() and not e.surfeando() and 0 <= px + dx < w_ and 0 <= py + dy < h_
                    and c_[(py + dy) * w_ + px + dx][2] in mundo().surf):
                e.mirar(d)
                if pulsar_a(e, intentos=2):          # "¿Quieres usar SURF?" -> SÍ
                    for _ in range(40):
                        if e.surfeando() and e.controlable():
                            break
                        e.pulsar("a", despues=15)
                if e.surfeando():
                    continue
            if (d == "arriba" and e.surfeando() and 0 <= py - 1 < h_ and c_[(py - 1) * w_ + px][2] == "MB_WATERFALL"):
                # subir la cascada: mirar, A y SÍ; sube sola hasta arriba
                e.mirar("arriba")
                if pulsar_a(e, intentos=2):
                    for _ in range(80):
                        if e.controlable():
                            break
                        e.pulsar("a", despues=15)
                break
            bajo_agua = mundo().mapas[e.mapa()].get("map_type") == "MAP_TYPE_UNDERWATER"
            movido = e.paso(d, correr=correr and not bajo_agua)   # B bajo el agua = emerger
            if e.en_combate():
                return "combate"
            if not e.controlable():
                r = e.pasar_textos()
                if r == "combate":
                    return "combate"
                break
            if not movido:
                if (e.mapa(), e.pos()) == antes:
                    # puerta con cartel (gimnasio de PETALIA): mirar, A y SÍ
                    w_, h_, c_, warps_, _ = info_mapa(e.mapa())
                    px, py = e.pos()
                    dx, dy = DIRS[d]
                    if (px + dx, py + dy) in warps_ and c_[(py + dy) * w_ + px + dx][0]:
                        e.mirar(d)
                        if pulsar_a(e, intentos=1):
                            for _ in range(60):
                                if e.controlable() and (e.mapa(), e.pos()) != antes:
                                    break
                                e.pulsar("a", despues=15)
                    break
            if (e.mapa(), e.pos()) != (sig[0], (sig[1], sig[2])):
                break
    else:
        return "atascado"
    if al_lado and isinstance(objetivo, tuple):
        x, y = e.pos()
        e.mirar(hacia(x, y, objetivo[1], objetivo[2]))
    return "ok"


# --- datos del juego leídos de la ROM ---
def leer_bloque(e, dir_, n):
    """n bytes desde dir_ (de 4 en 4)."""
    out = bytearray()
    for i in range(0, n, 4):
        v = e.leer(dir_ + i, 32)
        out += v.to_bytes(4, "little")
    return bytes(out[:n])


def efectividad(e, atk, dfn):
    if e._efect is None:
        b = leer_bloque(e, e.s["gTypeEffectivenessTable"], 21 * 21 * 4)
        e._efect = [[int.from_bytes(b[(i * 21 + j) * 4:(i * 21 + j) * 4 + 4], "little") / 4096 for j in range(21)] for i in range(21)]
    if atk >= 21 or dfn >= 21:
        return 1.0
    return e._efect[atk][dfn]


def especie(e, sp):
    """(baseStats[6], tipos(2), habilidades) de una especie."""
    if sp not in e._especies:
        b = leer_bloque(e, e.s["gSpeciesInfo"] + sp * 264, 32)
        e._especies[sp] = (list(b[0:6]), (b[6], b[7]))
    return e._especies[sp]


SUB = [[0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3],
       [1, 1, 2, 3, 2, 3, 0, 0, 0, 0, 0, 0, 2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2],
       [2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2, 0, 0, 0, 0, 0, 0, 3, 2, 3, 2, 1, 1],
       [3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0]]


def equipo(e, cual=0):
    """Lista de dicts del equipo (0 jugador, 1 rival): especie, nivel, hp, maxhp, estado, movs, pp, objeto, mote."""
    base = e.s["gParties"] + cual * 6 * 100
    n = e.leer(e.s["gPartiesCount"] + cual)
    res = []
    for i in range(min(n, 6)):
        b = leer_bloque(e, base + i * 100, 100)
        pers = int.from_bytes(b[0:4], "little")
        otid = int.from_bytes(b[4:8], "little")
        clave = pers ^ otid
        raw = bytearray(b[32:80])
        for k in range(0, 48, 4):
            v = int.from_bytes(raw[k:k + 4], "little") ^ clave
            raw[k:k + 4] = v.to_bytes(4, "little")
        orden = pers % 24
        s0 = raw[SUB[0][orden] * 12:SUB[0][orden] * 12 + 12]
        s1 = raw[SUB[1][orden] * 12:SUB[1][orden] * 12 + 12]
        w0 = int.from_bytes(s0[0:2], "little")
        w1 = int.from_bytes(s0[2:4], "little")
        sp = w0 & 0x7FF
        item = w1 & 0x3FF
        movs = [int.from_bytes(s1[k * 2:k * 2 + 2], "little") & 0x7FF for k in range(4)]
        pp = [s1[8 + k] & 0x7F for k in range(4)]
        es_huevo = bool(b[19] & 0x04)
        res.append({"i": i, "especie": sp, "nivel": b[84], "hp": int.from_bytes(b[86:88], "little"),
                    "maxhp": int.from_bytes(b[88:90], "little"), "estado": int.from_bytes(b[80:84], "little"),
                    "movs": movs, "pp": pp, "objeto": item, "huevo": es_huevo,
                    "stats": [int.from_bytes(b[88 + 2 * k:90 + 2 * k], "little") for k in range(6)]})
    return res


def mon_combate(e, bat):
    b = leer_bloque(e, e.s["gBattleMons"] + bat * OFF["sz_bm"], OFF["sz_bm"])
    w = lambda o: int.from_bytes(b[o:o + 2], "little")  # noqa: E731
    return {"especie": w(0), "atk": w(2), "def": w(4), "spe": w(6), "spa": w(8), "spd": w(10),
            "movs": [w(12 + 2 * k) for k in range(4)], "pp": list(b[OFF["bm_pp"]:OFF["bm_pp"] + 4]),
            "tipos": (b[OFF["bm_types"]], b[OFF["bm_types"] + 1], b[OFF["bm_types"] + 2]),
            "hp": w(OFF["bm_hp"]), "maxhp": w(OFF["bm_maxHP"]), "nivel": b[OFF["bm_level"]],
            "estado": int.from_bytes(b[OFF["bm_status1"]:OFF["bm_status1"] + 4], "little"),
            "etapas": [x - 256 if x > 127 else x for x in b[24:32]]}


ESTADO_EFECTOS = {"EFFECT_SLEEP", "EFFECT_PARALYZE", "EFFECT_TOXIC", "EFFECT_POISON", "EFFECT_WILL_O_WISP",
                  "EFFECT_YAWN"}


def danio(e, mov, atacante, defensor, nivel=None, tipos_atk=None):
    """Estimación del daño medio de mov (% de la vida máxima del defensor)."""
    m = MOVES.get(mov)
    if not m or m["power"] <= 1 or "STATUS" in m["cat"]:
        return 0.0
    t = m["type"]
    ef = 1.0
    for td in set(x for x in defensor["tipos"] if x not in (0, 10)):
        ef *= efectividad(e, t, td)
    stab = 1.5 if t in (tipos_atk or atacante["tipos"]) else 1.0
    fis = "PHYSICAL" in m["cat"] or ("SPECIAL" not in m["cat"])
    a = atacante["atk"] if fis else atacante["spa"]
    d = defensor["def"] if fis else defensor["spd"]
    lv = nivel or atacante["nivel"]
    pw = m["power"] * m.get("golpes", 1)
    if m["effect"] in ("EFFECT_SEMI_INVULNERABLE", "EFFECT_SOLAR_BEAM", "EFFECT_TWO_TURNS_ATTACK"):
        pw *= 0.5
    if m["effect"] in ("EFFECT_MULTI_HIT",):
        pw *= 3
    base = ((2 * lv / 5 + 2) * pw * a / max(d, 1)) / 50 + 2
    dmg = base * stab * ef * 0.925 * (m["acc"] or 100) / 100
    return 100 * dmg / max(defensor["maxhp"], 1)


# --- combate ---
MOTES = ["Kai", "Lia", "Dex", "Fio", "Max", "Bea", "Gus", "Ada", "Leo", "Ivy", "Rex", "Zoe", "Teo", "Nia",
         "Hugo", "Luz", "Pax", "Sol", "Uma", "Vic", "Yuk", "Eli", "Oto", "Ras", "Mia", "Nox", "Kip", "Bo"]


def tarea_activa(e, nombre):
    dirs = e.porfunc.get(nombre, set())
    for i in range(16):
        b = e.s["gTasks"] + i * 40
        if e.leer(b + 4) and (e.leer(b, 32) | 1) in dirs:
            return i
    return None


def opcode(e):
    p = e.leer(e.s["gBattlescriptCurrInstr"], 32)
    return e.leer(p) if 0x08000000 <= p < 0x0A000000 else None


def valor_mov(e, mov, tipos):
    m = MOVES.get(mov)
    if not m:
        return 0
    if "STATUS" in m["cat"] or m["power"] <= 1:
        return 15 if m["effect"] in ESTADO_EFECTOS or m["effect"] in ("EFFECT_DRAGON_DANCE", "EFFECT_SWORDS_DANCE") else 2
    v = m["power"] * (m["acc"] or 100) / 100 * (1.5 if m["type"] in tipos else 1)
    if m["effect"] in ("EFFECT_RECHARGE", "EFFECT_SOLAR_BEAM", "EFFECT_TWO_TURNS_ATTACK", "EFFECT_SEMI_INVULNERABLE", "EFFECT_POLTERGEIST"):
        v *= 0.5
    if m["effect"] == "EFFECT_MULTI_HIT":
        v *= 3
    return v


def elegir_olvido(e, mon_idx, nuevo):
    """Índice (0-3) del movimiento a olvidar, o 4 para no aprender."""
    m = equipo(e)[mon_idx]
    tipos = especie(e, m["especie"])[1]
    MO = {DATOS["ids"].get(x) for x in ("MOVE_CUT", "MOVE_FLY", "MOVE_SURF", "MOVE_STRENGTH", "MOVE_FLASH",
                                        "MOVE_ROCK_SMASH", "MOVE_WATERFALL", "MOVE_DIVE")}
    vals = [999 if mv in MO else valor_mov(e, mv, tipos) for mv in m["movs"]]
    # no quedarse sin variedad: penaliza tener dos del mismo tipo
    peor = min(range(4), key=lambda k: vals[k])
    vn = valor_mov(e, nuevo, tipos)
    tipos_mios = [MOVES.get(mv, {}).get("type") if mv not in MO else None for mv in m["movs"]]
    if MOVES.get(nuevo, {}).get("type") in tipos_mios and MOVES.get(nuevo, {}).get("power", 0) > 0:
        k = tipos_mios.index(MOVES[nuevo]["type"])
        if vn > vals[k]:
            return k
    if vn > vals[peor]:
        return peor
    return 4


class Combate:
    def __init__(self, e, capturar=None, huir=True, nombre_mote=None):
        self.e = e
        self.capturar = capturar
        self.huir = huir
        self.balls = 0
        self.mote = nombre_mote
        self.turnos = 0
        self.eventos = []

    def func_bat(self, b):
        return self.e.leer(self.e.s["gBattlerControllerFuncs"] + 4 * b, 32) | 1

    def tipo(self):
        return self.e.leer(self.e.s["gBattleTypeFlags"], 32)

    def jugar(self, maximo=6000):
        e = self.e
        sin_cambio = 0
        for it in range(maximo):
            cb = e.cb2()
            if cb == "CB2_Overworld" and not e.en_combate():
                e.avanzar(30)
                return e.leer(e.s["gBattleOutcome"])
            if e.en_motes():
                self.poner_mote()
                continue
            t = tarea_activa(e, "Task_HandleReplaceMoveInput")
            if t is not None:
                self.olvidar()
                continue
            if cb in ("CB2_UpdatePartyMenu",):
                self.menu_equipo()
                continue
            if cb.startswith("CB2_EvolutionScene") or cb.startswith("CB2_TradeEvolution"):
                e.pulsar("a", despues=20)
                continue
            if cb == "BattleMainCB2":
                op = opcode(e)
                if op == 92:          # ¿cambiar de POKéMON? -> no
                    e.pulsar("b", despues=20)
                    continue
                if op == 188 and e.leer(e.s["gBattleCommunication"]) == 2:
                    # equipo lleno tras capturar: "¿Lo metes en el equipo?" -> NO, a la caja (no tocar mi equipo)
                    e.pulsar("abajo", despues=10)
                    e.pulsar("a", despues=20)
                    e.apunta("  equipo lleno: la captura va a la caja")
                    continue
                hecho = False
                for b in (0, 2):
                    f = self.func_bat(b)
                    if f in e.elegir_accion:
                        self.decidir(b)
                        hecho = True
                        break
                    if f in e.elegir_movimiento:
                        e.pulsar("b", despues=20)
                        hecho = True
                        break
                    if f in e.elegir_objetivo:
                        e.pulsar("a", despues=20)
                        hecho = True
                        break
                if hecho:
                    continue
            e.pulsar("a", fotogramas=4, despues=12)
        raise RuntimeError("combate demasiado largo")

    # --- decisiones ---
    def decidir(self, b):
        e = self.e
        self.turnos += 1
        if self.turnos > 120 and self.turnos % 10 == 0:
            e.apunta(f"    AVISO: combate de {self.turnos} turnos")
        if getattr(e, "modo_dios", False):
            # AYUDA DECLARADA: rellena la vida de mis Pokémon en combate (solo para seguir probando la historia)
            for bb in ((0, 2) if self.tipo() & 1 else (0,)):
                base = e.s["gBattleMons"] + bb * OFF["sz_bm"]
                mx = e.leer(base + OFF["bm_maxHP"], 16)
                if e.leer(base + OFF["bm_hp"], 16):
                    e.escribir(base + OFF["bm_hp"], mx, 16)
            for bb in ((1, 3) if self.tipo() & 1 else (1,)):
                base = e.s["gBattleMons"] + bb * OFF["sz_bm"]
                if e.leer(base + OFF["bm_hp"], 16) > 1:
                    e.escribir(base + OFF["bm_hp"], 1, 16)
        self.veces_menu = 0
        if b == 0:
            self.reservados = set()
        yo = mon_combate(e, b)
        # ¿el movimiento del turno anterior no le hizo nada? (Superguarda, inmunidad, Poltergeist sin objeto...)
        if not hasattr(self, "ultimo") or not isinstance(self.ultimo, dict):
            self.ultimo = {}
        ult = self.ultimo.pop(b, None)
        if ult:
            rb, esp, hp_antes, mov, mio = ult
            r1 = mon_combate(e, rb)
            dos_turnos = MOVES[mov]["effect"] in ("EFFECT_SEMI_INVULNERABLE", "EFFECT_SOLAR_BEAM", "EFFECT_TWO_TURNS_ATTACK",
                                                   "EFFECT_SKULL_BASH", "EFFECT_SKY_DROP", "EFFECT_METEOR_BEAM")
            if r1["especie"] == esp and r1["hp"] >= hp_antes and r1["hp"] > 0 and yo["especie"] == mio and not dos_turnos \
                    and yo["etapas"][6] >= 6 and r1["etapas"][7] <= 6:
                self.fallos = getattr(self, "fallos", {})
                self.fallos[(esp, mov)] = self.fallos.get((esp, mov), 0) + 1
                if self.fallos[(esp, mov)] >= 2 or MOVES[mov]["acc"] == 0:
                    self.inutiles = getattr(self, "inutiles", set()) | {(esp, mov)}
                    e.apunta(f"    ({MOVES[mov]['nombre']} no le hace nada a {nombre(esp)})")
        dobles = bool(self.tipo() & 1)
        rivales = []
        for rb in ((1, 3) if dobles else (1,)):
            r = mon_combate(e, rb)
            r["bat"] = rb
            if r["hp"] > 0:
                rivales.append(r)
        if not rivales:
            r = mon_combate(e, 1)
            r["bat"] = 1
            rivales = [r]
        # en dobles, el que más amenaza es el que importa para cambiar
        rivales.sort(key=lambda r: -max([danio(e, mv, r, yo) for mv in r["movs"] if mv] + [0]))
        rival = rivales[0]
        salvaje = not (self.tipo() & 8)
        # agarrado por Caída Libre: no se puede usar la mochila; pasar turno con un movimiento
        if (e.leer(e.s["gBattleMons"] + b * OFF["sz_bm"] + 92) >> 3) & 15 == 6:
            self.usar_mov(b, 0)
            return
        if salvaje and self.turnos == 1:
            enc = e.leer(e.s["sCurrentEncounter"])
            self.encuentro = enc
            e.apunta(f"  salvaje {nombre(rival['especie'])} L{rival['nivel']} en {e.mapa()}: {ENCUENTRO[enc] if enc < 6 else enc}")
            if self.capturar is None:
                self.capturar = enc in (1, 2)
        if salvaje and self.capturar and yo["hp"] / max(yo["maxhp"], 1) < 0.35 and len([m for m in equipo(e) if m["hp"]]) == 1:
            e.apunta(f"    me quedo sin vida intentando capturar a {nombre(rival['especie'])}: huyo")
            self.capturar = False
        if salvaje and self.capturar:
            # que no se me muera nadie capturando: si el siguiente golpe me tumba, saco a otro que lo aguante
            mi_vida = 100 * yo["hp"] / max(yo["maxhp"], 1)
            golpe = max([danio(e, mv, rival, yo) for mv in rival["movs"] if mv] + [0])
            if golpe * 1.15 >= mi_vida and getattr(self, "cambios_captura", 0) < 4:
                otro = self.mejor_del_equipo(rival, excluir=[yo.get("i", -1)] + self.activos())
                if otro is not None:
                    m_ = next(m for m in equipo(e) if m["i"] == otro[1])
                    recibe = self.puntuar(m_, rival)[2]      # lo que le quitaría al que entra
                    if 100 * m_["hp"] / max(m_["maxhp"], 1) > recibe * 2.2:
                        self.cambios_captura = getattr(self, "cambios_captura", 0) + 1
                        self.cambio_a = otro[1]
                        e.apunta(f"    captura: {nombre(yo['especie'])} ({mi_vida:.0f}%) no aguanta otro golpe (~{golpe:.0f}%): cambio a {nombre(m_['especie'])} (recibiría ~{recibe:.0f}%)")
                        self.accion(b, 2)
                        return
            if golpe * 1.15 >= mi_vida:
                # nadie puede aguantar con seguridad: mejor huir que perder a alguien por una captura
                e.apunta(f"    captura: {nombre(yo['especie'])} ({mi_vida:.0f}%) no aguanta y no hay cambio seguro: huyo de {nombre(rival['especie'])}")
                self.capturar = False
                self.accion(b, 3)
                return
            pct = rival["hp"] / max(rival["maxhp"], 1)
            if pct <= 0.5 or self.turnos > 6 or rival["estado"] & 7:
                if self.lanzar_ball(b):
                    e.apunta(f"    captura T{self.turnos}: lanzo Ball ({100*rival['hp']//max(rival['maxhp'],1)}%), yo {100*yo['hp']//max(yo['maxhp'],1)}%")
                    return
            # debilitar sin matar: el movimiento que haga más daño sin pasar de la vida que le queda
            opciones = []
            for k, mv in enumerate(yo["movs"]):
                if mv and yo["pp"][k] > 0:
                    d = danio(e, mv, yo, rival)
                    opciones.append((d, k, mv))
            vida = 100 * rival["hp"] / max(rival["maxhp"], 1)
            seguras = [o for o in opciones if 0 < o[0] * 1.8 < vida and o[0] < 45]
            if seguras:
                _, k, _ = max(seguras)
            else:
                # dormir/paralizar si se puede; si no, lanzar ya
                estado = [o for o in opciones if MOVES.get(o[2], {}).get("effect") in ("EFFECT_SLEEP", "EFFECT_PARALYZE")]
                if estado and not rival["estado"]:
                    k = estado[0][1]
                elif self.lanzar_ball(b):
                    return
                else:
                    k = min(opciones)[1] if opciones else 0
            e.apunta(f"    captura T{self.turnos}: {nombre(yo['especie'])} {100*yo['hp']//max(yo['maxhp'],1)}% vs "
                     f"{nombre(rival['especie'])} {100*rival['hp']//max(rival['maxhp'],1)}%: {MOVES[yo['movs'][k]]['nombre']} "
                     f"[{', '.join(MOVES[m]['nombre'] for m in rival['movs'] if m)}]")
            self.usar_mov(b, k)
            return
        if salvaje and self.huir and not getattr(e, "no_huir", False):   # no_huir: guardianes y estáticos
            self.accion(b, 3)
            return
        # ¿cambiar? si me tumban este turno sin que yo le tumbe, y hay otro que aguanta el golpe
        if getattr(self, "cambios", 0) < 4:
            act = e.leer(e.s["gBattlerPartyIndexes"] + 2 * b, 16)
            otros_activos = set(self.activos())
            eq = equipo(e)
            vida = 100 * yo["hp"] / max(yo["maxhp"], 1)
            vida_r = 100 * rival["hp"] / max(rival["maxhp"], 1)
            mi_mejor = max([0 if (rival["especie"], mv) in getattr(self, "inutiles", set()) else danio(e, mv, yo, rival)
                            for k, mv in enumerate(yo["movs"]) if mv and yo["pp"][k]] + [0])
            amenaza = max([danio(e, mv, rival, yo) for mv in rival["movs"] if mv] + [0])
            prioridad = any(MOVES.get(mv, {}).get("priority", 0) > 0 and danio(e, mv, yo, rival) >= vida_r
                            for k, mv in enumerate(yo["movs"]) if mv and yo["pp"][k])
            espacio_raro = bool(e.leer(e.s["gFieldStatuses"], 32) & 2)
            yo_primero = (yo["spe"] > rival["spe"]) != espacio_raro or prioridad
            le_tumbo = mi_mejor >= vida_r * 1.1 and yo_primero
            me_tumba = amenaza >= vida * 0.9
            # turnos que necesito / que aguanto
            necesito = max(1, -(-vida_r // max(mi_mejor, 1)))
            aguanto = max(1, -(-vida // max(amenaza, 1)))
            pierdo = necesito > aguanto or (necesito == aguanto and not yo_primero)
            if (pierdo and not le_tumbo) or (vida <= 30 and not le_tumbo) or mi_mejor < 5:
                mejor_sw = None
                for m in eq:
                    if m["hp"] == 0 or m["huevo"] or m["i"] in otros_activos or m["i"] in getattr(self, "reservados", set()):
                        continue
                    p, at, df = self.puntuar(m, rival)
                    v = 100 * m["hp"] / max(m["maxhp"], 1)
                    # entra recibiendo un golpe: tiene que aguantarlo con margen y luego ganar
                    if df * 1.0 >= v * (0.9 if (yo["etapas"][6] <= 4 or mi_mejor < 5) else 0.6):
                        continue
                    nec = max(1, -(-vida_r // max(at, 1)))
                    agu = max(1, -(-(v - df) // max(df, 1)))
                    gana = nec <= agu
                    clave = (gana, -df, at)
                    if mejor_sw is None or clave > mejor_sw[0]:
                        mejor_sw = (clave, m["i"])
                atascado = yo["etapas"][6] <= 4 or rival["etapas"][7] >= 8 or mi_mejor < 5
                if mejor_sw and (mejor_sw[0][0] or atascado):
                    self.cambio_a = mejor_sw[1]
                    self.reservados = getattr(self, "reservados", set()) | {mejor_sw[1]}
                    self.cambios = getattr(self, "cambios", 0) + 1
                    e.apunta(f"  cambio: {nombre(eq[act]['especie'])} ({vida:.0f}%, recibe ~{amenaza:.0f}%) -> "
                             f"{nombre(eq[mejor_sw[1]]['especie'])} contra {nombre(rival['especie'])}")
                    self.accion(b, 2)
                    return
        self.cambiado_hace_poco = False
        # contra Superguarda y compañía: si nada le hace daño, quemar/envenenar/drenar
        DOT = ("EFFECT_WILL_O_WISP", "EFFECT_TOXIC", "EFFECT_POISON", "EFFECT_LEECH_SEED")
        utiles = [k for k, mv in enumerate(yo["movs"]) if mv and yo["pp"][k] and MOVES[mv]["power"] > 1
                  and (rival["especie"], mv) not in getattr(self, "inutiles", set()) and danio(e, mv, yo, rival) > 0]
        if not utiles:
            dot = [k for k, mv in enumerate(yo["movs"]) if mv and yo["pp"][k] and MOVES[mv]["effect"] in DOT]
            if dot and not rival["estado"]:
                e.apunta(f"    nada le hace daño a {nombre(rival['especie'])}: uso {MOVES[yo['movs'][dot[0]]]['nombre']}")
                self.usar_mov(b, dot[0], rival["bat"])
                return
            if not rival["estado"]:
                act = e.leer(e.s["gBattlerPartyIndexes"] + 2 * b, 16)
                for m in equipo(e):
                    if m["i"] != act and m["hp"] and m["i"] not in self.activos() and any(MOVES[mv]["effect"] in DOT for mv in m["movs"] if mv):
                        if getattr(self, "cambio_dot", 0) < 2:
                            self.cambio_dot = getattr(self, "cambio_dot", 0) + 1
                            self.cambio_a = m["i"]
                            e.apunta(f"  cambio a {nombre(m['especie'])} para quemar/envenenar a {nombre(rival['especie'])}")
                            self.accion(b, 2)
                            return
        # el mejor movimiento contra el rival más fácil de tumbar
        mejor = None
        for k, mv in enumerate(yo["movs"]):
            if not mv or yo["pp"][k] == 0:
                continue
            for ri, r in enumerate(rivales):
                d = danio(e, mv, yo, r)
                if (r["especie"], mv) in getattr(self, "inutiles", set()):
                    d = 0
                if MOVES[mv]["effect"] in ("EFFECT_SEMI_INVULNERABLE", "EFFECT_SOLAR_BEAM", "EFFECT_TWO_TURNS_ATTACK",
                                           "EFFECT_SKY_DROP", "EFFECT_RECHARGE") and getattr(e, "modo_dios", False):
                    d = 0
                vida = 100 * r["hp"] / max(r["maxhp"], 1)
                puntos = min(d, vida) + (50 if d >= vida else 0) + MOVES[mv]["priority"] * (20 if d >= vida else 0)
                if mejor is None or puntos > mejor[0]:
                    mejor = (puntos, k, ri)
        if mejor is None:
            self.usar_mov(b, 0)
            return
        r = rivales[mejor[2]]
        self.ultimo[b] = (r["bat"], r["especie"], r["hp"], yo["movs"][mejor[1]], yo["especie"])
        amenaza = max([danio(e, mv, r, yo) for mv in r["movs"] if mv] + [0])
        e.apunta(f"    T{self.turnos} {nombre(yo['especie'])} {100*yo['hp']//max(yo['maxhp'],1)}% vs "
                 f"{nombre(r['especie'])} L{r['nivel']} {100*r['hp']//max(r['maxhp'],1)}%: "
                 f"{MOVES[yo['movs'][mejor[1]]]['nombre']} (~{danio(e, yo['movs'][mejor[1]], yo, r):.0f}%), "
                 f"me quita ~{amenaza:.0f}% [{', '.join(MOVES[m]['nombre'] for m in r['movs'] if m)}]")
        self.usar_mov(b, mejor[1], r["bat"])

    def accion(self, b, cual):
        e = self.e
        e.escribir(e.s["gActionSelectionCursor"] + b, cual)
        e.pulsar("a", despues=30)

    def usar_mov(self, b, k, objetivo=None):
        e = self.e
        self.accion(b, 0)
        for _ in range(60):
            if self.func_bat(b) in e.elegir_movimiento:
                break
            e.avanzar(5)
        e.escribir(e.s["gMoveSelectionCursor"] + b, k)
        e.avanzar(4)
        e.pulsar("a", despues=30)
        if objetivo is not None and self.tipo() & 1:
            for _ in range(10):
                if self.func_bat(b) in e.elegir_objetivo:
                    e.escribir(e.s["gMultiUsePlayerCursor"], objetivo)
                    e.avanzar(4)
                    e.pulsar("a", despues=30)
                    break
                e.avanzar(3)

    def lanzar_ball(self, b):
        """MOCHILA -> bolsillo de Balls -> la primera. False si no hay."""
        e = self.e
        self.accion(b, 1)
        for _ in range(60):
            if e.cb2() in ("CB2_BagMenuRun", "CB2_Bag"):
                break
            e.avanzar(5)
        else:
            e.apunta("  AVISO: no se abre la mochila en el combate")
            return False
        e.avanzar(30)
        bp = e.s["gBagPosition"]
        for _ in range(8):
            if e.leer(bp + 5) == 2:
                break
            e.pulsar("derecha" if e.leer(bp + 5) < 2 else "izquierda", despues=25)
        lista = [n for n, q in mochila(e, "balls")]
        if not lista:
            e.pulsar("b", despues=60)
            if self.capturar:
                e.apunta("  AVISO: no me quedan Balls; dejo de intentar capturar")
                self.capturar = False
            return False
        orden = ["ULTRA_BALL", "QUICK_BALL", "DUSK_BALL", "GREAT_BALL", "NET_BALL", "DIVE_BALL", "POKE_BALL", "PREMIER_BALL"]
        mejor = min(range(len(lista)), key=lambda i: orden.index(lista[i]) if lista[i] in orden else 50)
        for _ in range(40):
            c = e.leer(bp + 8 + 2 * 2, 16) + e.leer(bp + 22 + 2 * 2, 16)
            if c == mejor:
                break
            e.pulsar("abajo" if c < mejor else "arriba", despues=10)
        e.pulsar("a", despues=30)
        e.pulsar("a", despues=60)
        self.balls += 1
        return True

    def poner_mote(self):
        e = self.e
        e.avanzar(60)
        ruta = os.path.join(AQUI, "motes.txt")
        usados = open(ruta).read().split() if os.path.exists(ruta) else []
        # motes sin repetir; si se acaba la lista, dos juntos (Kailia, Kaidex...): el teclado no tiene números
        libres = [m for m in MOTES if m not in usados] or \
                 [a + b.lower() for a in MOTES for b in MOTES if a != b and a + b.lower() not in usados]
        nombre = self.mote or libres[0]
        open(ruta, "w").write(" ".join(usados + [nombre]))
        e.motes_usados.append(nombre)
        teclear(e, nombre)
        e.avanzar(60)

    def olvidar(self):
        e = self.e
        nuevo = e.leer(e.s["gMoveToLearn"], 16)
        # qué POKéMON aprende: el que sube de nivel (expGetterMonId) o el de la evolución; se busca el que no lo tiene
        eq = equipo(e)
        idx = getattr(e, "aprende_idx", None)
        if idx is None:
            idx = 0
        k = elegir_olvido(e, idx, nuevo)
        if getattr(e, "olvido_forzado", None) is not None:
            k = e.olvido_forzado
        e.apunta(f"  aprender {MOVES.get(nuevo, {}).get('nombre')}: olvida "
                 f"{MOVES.get(eq[idx]['movs'][k], {}).get('nombre') if k < 4 else 'nada'}")
        e.avanzar(40)
        for _ in range(k):
            e.pulsar("abajo", despues=12)
        e.pulsar("a" if k < 4 else "b", despues=60)

    def puntuar(self, m, rival):
        """Lo bien que le va a m (del equipo) contra rival: % que le quita por turno menos % que recibe."""
        e = self.e
        bs, tipos = especie(e, m["especie"])
        yo = {"atk": m["stats"][1], "def": m["stats"][2], "spa": m["stats"][4], "spd": m["stats"][5],
              "spe": m["stats"][3], "tipos": tipos, "nivel": m["nivel"], "maxhp": m["maxhp"]}
        ataque = max([danio(e, mv, yo, rival) for k, mv in enumerate(m["movs"]) if mv and m["pp"][k]] + [0])
        defensa = max([danio(e, mv, rival, yo) for mv in rival["movs"] if mv] + [0])
        # turnos que aguanta y turnos que necesita
        vida = 100 * m["hp"] / max(m["maxhp"], 1)
        aguanta = vida / max(defensa, 1)
        necesita = (100 * rival["hp"] / max(rival["maxhp"], 1)) / max(ataque, 1)
        rapido = yo["spe"] > rival["spe"]
        return aguanta - necesita + (0.5 if rapido else 0), ataque, defensa

    def mejor_del_equipo(self, rival, excluir=()):
        e = self.e
        mejor = None
        for m in equipo(e):
            if m["hp"] == 0 or m["huevo"] or m["i"] in excluir:
                continue
            p = self.puntuar(m, rival)[0]
            if mejor is None or p > mejor[0]:
                mejor = (p, m["i"])
        return mejor

    def activos(self):
        e = self.e
        return [e.leer(e.s["gBattlerPartyIndexes"] + 2 * b, 16) for b in ((0, 2) if self.tipo() & 1 else (0,))]

    def menu_equipo(self):
        """Elige a quién sacar (cambio obligado, o el elegido en decidir) por tipos contra el rival."""
        e = self.e
        e.avanzar(30)
        rival = mon_combate(e, 1) if mon_combate(e, 1)["hp"] else mon_combate(e, 3)
        slot = getattr(self, "cambio_a", None)
        self.cambio_a = None
        # en el menú del combate el equipo está en orden de combate (los que luchan primero)
        o = e.s["gBattlePartyCurrentOrder"]
        orden = []
        for k in range(6):
            v = e.leer(o + k // 2)
            orden.append((v & 0xF) if k & 1 else (v >> 4))
        if slot is not None and slot in orden:
            slot = orden.index(slot)
        self.veces_menu = getattr(self, "veces_menu", 0) + 1
        if self.veces_menu > 6:
            # algo no va: probar con cualquiera que esté vivo y no activo, en orden
            vivos = [m["i"] for m in equipo(e) if m["hp"] and not m["huevo"] and m["i"] not in ([0, 1] if self.tipo() & 1 else [0])]
            slot = vivos[self.veces_menu % len(vivos)] if vivos else None
            if slot is None or self.veces_menu > 20:
                e.pulsar("b", despues=30)
                return
        if slot is None:
            mejor = self.mejor_del_equipo(rival, excluir=[0, 1] if self.tipo() & 1 else [0])
            if mejor is None:
                e.pulsar("b", despues=30)
                return
            slot = mejor[1]
        eq_ = equipo(e)
        nom_ = nombre(eq_[slot]["especie"]) if slot < len(eq_) else f"hueco {slot}"
        e.apunta(f"  saca a {nom_} contra {nombre(rival['especie'])}")
        pm = e.s["gPartyMenu"]
        for _ in range(8):
            cur = e.leer(pm + OFF["pm_slot"])
            if cur == slot:
                break
            e.pulsar("abajo" if cur < slot or cur > 6 else "arriba", despues=10)
        e.pulsar("a", despues=30)
        e.pulsar("a", despues=60)


# --- alto nivel ---
def seguir(e, maximo=600, **kw):
    """Pasa textos y combates hasta poder mover al jugador. Devuelve la lista de resultados de combate."""
    res = []
    for _ in range(maximo):
        if e.en_combate():
            c = Combate(e, **kw)
            r = c.jugar()
            res.append(r)
            e.apunta(f"  combate: resultado {r} en {e.mapa()}")
            continue
        if e.en_motes():
            Combate(e).poner_mote()
            continue
        t = tarea_activa(e, "Task_HandleReplaceMoveInput")
        if t is not None:
            Combate(e).olvidar()
            continue
        if e.cb2().startswith("CB2_EvolutionScene"):
            e.pulsar("a", despues=20)
            continue
        if e.controlable():
            e.avanzar(10)
            if e.controlable():
                return res
        e.pulsar("a", fotogramas=4, despues=12)
    raise RuntimeError("seguir: no se libera el control en " + str(e.mapa()) + " " + e.cb2())


def pulsar_a(e, intentos=3):
    """Pulsa A hasta que empiece algo (texto, script o combate)."""
    for _ in range(intentos):
        e.avanzar(8)
        e.pulsar("a", fotogramas=6, despues=4)
        for _ in range(12):
            if not e.controlable() or e.en_combate():
                return True
            e.avanzar(4)
    return False


def hablar_con(e, mapa, x, y, **kw):
    """Va junto a (x, y), mira y pulsa A; sigue textos/combates."""
    if e.mapa() != mapa:
        ir(e, mapa, **kw)
    for _ in range(12):
        r = ir_a(e, (mapa, x, y), al_lado=True)
        if r in ("combate", "atascado"):
            seguir(e, **kw)
            continue
        break
    if r != "ok":
        raise RuntimeError(f"hablar_con: {r} hacia {mapa} {x},{y} desde {e.mapa()} {e.pos()}")
    for intento in range(3):
        e.mirar(hacia(e.pos()[0], e.pos()[1], x, y))
        if pulsar_a(e):
            return seguir(e, **kw)
    e.apunta(f"  AVISO: hablar_con {mapa} {x},{y}: no pasa nada al pulsar A")
    return []


def centro_cercano(e):
    """El Centro POKéMON al que se llega antes andando desde aquí."""
    centros = {m for m in mundo().mapas if m.endswith("_POKEMON_CENTER_1F")}
    x, y, z = e.jugador()
    c = planear((e.mapa(), x, y, z), lambda s: s[0] in centros, tapadas_mapa=evitar_base(e))
    return c[-1][1][0] if c else None


def hace_falta_curar(e):
    if getattr(e, "no_curar", False):
        return False
    eq = [m for m in equipo(e) if not m["huevo"]]
    if not eq:
        return False
    total = sum(m["hp"] for m in eq) / max(sum(m["maxhp"] for m in eq), 1)
    return total < 0.55 or any(m["hp"] / m["maxhp"] < 0.3 for m in eq)


def ir(e, mapa, x=None, y=None, **kw):
    """Va a (mapa, x, y) o a cualquier casilla de mapa, resolviendo lo que salga por el camino."""
    obj = (mapa, x, y) if x is not None else (lambda s: s[0] == mapa)
    for intento in range(30):
        r = ir_a(e, obj, max_intentos=12)
        if r == "ok":
            return
        if r in ("combate", "texto", "atascado"):
            seguir(e, **kw)
            if r == "combate" and hace_falta_curar(e):
                centro = centro_cercano(e)
                if centro and getattr(e, "sin_curar_hasta", None) != (e.mapa(),):
                    e.apunta(f"  vuelvo a curar a {centro}: {resumen(e)}")
                    base_ = (e.mapa(), e.pos())
                    try:
                        curar(e, centro)
                    except RuntimeError as err:
                        # no se puede volver (rocas, cascadas...): sigo sin curar, como haría cualquiera
                        e.apunta(f"  no puedo volver a curar ({err}); sigo así")
                        e.sin_curar_hasta = (e.mapa(),)
            if r == "atascado" or intento % 3 == 2:
                if not despejar(e, obj):
                    empujar_rocas(e, obj)
            continue
        raise RuntimeError(f"ir: {r} hacia {mapa} {x},{y} desde {e.mapa()} {e.pos()}")
    raise RuntimeError("ir: no llega")


ROMPIBLES = ("OBJ_EVENT_GFX_BREAKABLE_ROCK", "OBJ_EVENT_GFX_CUTTABLE_TREE", "OBJ_EVENT_GFX_ITEM_BALL")


def despejar(e, obj):
    """Si el camino (sin contar personajes) pasa por una roca o un árbol, lo rompe/corta."""
    mid = e.mapa()
    x, y, z = e.jugador()
    rompibles = {(o[0], o[1]) for o in e.objetos() if o[3] in {_GFX_N[g] for g in ROMPIBLES}}
    # los que están lejos no están cargados: se cogen del mapa (las rocas vuelven al salir del mapa)
    vivos = {(o[0], o[1]) for o in e.objetos()}
    for o in _mapa_json(mid).get("object_events", []):
        if o.get("graphics_id") in ROMPIBLES and isinstance(o.get("x"), int):
            if abs(o["x"] - x) > 8 or abs(o["y"] - y) > 6 or (o["x"], o["y"]) in vivos:
                rompibles.add((o["x"], o["y"]))
    tap = {k: set(v) for k, v in getattr(e, "evitar", {}).items()}
    for k, v in evitar_base(e).items():
        tap.setdefault(k, set()).update(v)
    tap.setdefault(mid, set()).update((o[0], o[1]) for o in e.objetos() if (o[0], o[1]) not in rompibles)
    camino = planear((mid, x, y, z), obj, tapadas_mapa=tap)
    if not camino:
        return False
    en_camino = [(s_[1], s_[2]) for d, s_ in camino if s_[0] == mid and (s_[1], s_[2]) in rompibles]
    if not en_camino:
        return False
    # el del camino primero; si no se llega a su lado, los demás de cerca
    px, py = e.pos()
    r0 = en_camino[0]
    cerca = [r for r in rompibles - {r0} if abs(r[0] - r0[0]) + abs(r[1] - r0[1]) <= 3]
    candidatos = [r0] + sorted(cerca, key=lambda r: abs(r[0] - px) + abs(r[1] - py))[:3]
    for rx, ry in candidatos:
        # solo si se llega a su lado sin salir de este mapa (si no, el camino da vueltas por otros mapas)
        x, y, z = e.jugador()
        tap_ = {mid: {(o[0], o[1]) for o in e.objetos()}}
        if planear((mid, x, y, z), lambda s, rx=rx, ry=ry: s[0] == mid and abs(s[1] - rx) + abs(s[2] - ry) == 1,
                   tapadas_mapa=tap_, solo_mapa=mid) is None:
            continue
        e.apunta(f"  rompo/corto lo de {mid} {rx},{ry}")
        try:
            hablar_con(e, mid, rx, ry)
            if (rx, ry) not in {(o[0], o[1]) for o in e.objetos()}:
                return True
        except RuntimeError as err:
            e.apunta(f"  AVISO: {err}")
    return False


def estado(e):
    eq = equipo(e)
    return f"{e.mapa()} {e.pos()} | " + resumen(e)


def _constantes(ruta):
    import re
    d = {}
    for l in open(os.path.join(RAIZ_REPO, ruta)):
        m = re.match(r"#define\s+(\w+)\s+(.+?)\s*(//.*)?$", l)
        if m:
            d[m.group(1)] = m.group(2)
    def valor(n, prof=0):
        v = d[n]
        try:
            return int(eval(re.sub(r"\b([A-Z_][A-Z0-9_]*)\b", lambda mm: str(valor(mm.group(1), prof + 1)), v)))
        except Exception:
            return None
    return d, valor


_VARS = _constantes("include/constants/vars.h")
_FLAGS = _constantes("include/constants/flags.h")
_FLAGS[0]["TRAINER_FLAGS_END"] = "0x85F"


def var(e, nombre):
    n = _VARS[1](nombre)
    return e.leer(e._sb1() + 5020 + 2 * (n - 0x4000), 16)


def flag(e, nombre):
    n = _FLAGS[1](nombre) if isinstance(nombre, str) else nombre
    return bool(e.leer(e._sb1() + 4720 + n // 8) >> (n % 8) & 1)


import re as _re
NOMBRE_ESPECIE = {}
for _m in _re.finditer(r"\b(SPECIES_\w+)\s*=\s*(\d+)\s*,", open(os.path.join(RAIZ_REPO, "include/constants/species.h")).read()):
    NOMBRE_ESPECIE.setdefault(int(_m.group(2)), _m.group(1)[8:].capitalize())


def nombre(sp):
    return NOMBRE_ESPECIE.get(sp, str(sp))


def resumen(e):
    return ", ".join(f"{nombre(m['especie'])} {m['nivel']} ({m['hp']}/{m['maxhp']})" for m in equipo(e))


def hierba(mapa):
    w, h, c, _, _ = info_mapa(mapa)
    return [(x, y) for y in range(h) for x in range(w) if c[y * w + x][2] in ("MB_TALL_GRASS", "MB_LONG_GRASS", "MB_ASHGRASS")]


def entrenar(e, mapa, nivel, min_vida=0.35, max_combates=60, centro=None, **kw):
    """Anda por la hierba de mapa luchando con salvajes hasta que el primero llegue a nivel. Si la vida
    baja, vuelve a curar con centro() (una función)."""
    casillas = hierba(mapa)
    import random
    rnd = random.Random(1)
    combates = 0
    while combates < max_combates:
        eq = equipo(e)
        if eq[0]["nivel"] >= nivel:
            return combates
        if any(m["hp"] / m["maxhp"] < min_vida for m in eq[:1]) and centro:
            centro(e)
            continue
        if e.mapa() != mapa:
            ir(e, mapa)
        x, y = e.pos()
        cerca = [c for c in casillas if abs(c[0] - x) + abs(c[1] - y) <= 8] or casillas
        dest = rnd.choice(cerca)
        r = ir_a(e, (mapa,) + dest, max_intentos=3)
        if e.en_combate() or r == "combate":
            seguir(e, **kw)
            combates += 1
    return combates


def _mapa_json(mid):
    return mundo().mapas[mid]


def curar(e, centro):
    """Va al Centro POKéMON `centro` (mapa del 1F) y habla con la enfermera."""
    ir(e, centro)
    m = _mapa_json(centro)
    n = next(o for o in m["object_events"] if o["graphics_id"] == "OBJ_EVENT_GFX_NURSE")
    ir(e, centro, n["x"], n["y"] + 2)
    e.mirar("arriba")
    pulsar_a(e)
    seguir(e)
    e.apunta(f"  curado en {centro}: {resumen(e)}")
    e.ultimo_centro = centro
    try:
        open(os.path.join(AQUI, "ultimo_centro.txt"), "w").write(centro)
    except OSError:
        pass


def curador(centro):
    return lambda e: curar(e, centro)


_ITEMS = {}
for _m in _re.finditer(r"#define\s+(ITEM_\w+)\s+(\d+)\b", open(os.path.join(RAIZ_REPO, "include/constants/items.h")).read()):
    _ITEMS.setdefault(int(_m.group(2)), _m.group(1)[5:])
for _m in _re.finditer(r"\b(ITEM_\w+)\s*=\s*(\d+)\s*,", open(os.path.join(RAIZ_REPO, "include/constants/items.h")).read()):
    _ITEMS.setdefault(int(_m.group(2)), _m.group(1)[5:])


BOLSILLOS = {"objetos": (0x560, 30), "clave": (None, 0), "balls": (1616, 16)}


def bolsillo(e, off, n):
    sb1 = e._sb1()
    sb2 = e.leer(e.s["gSaveBlock2Ptr"], 32)
    clave = e.leer(sb2 + 172, 32) & 0xFFFF
    res = []
    for i in range(n):
        it = e.leer(sb1 + off + 4 * i, 16)
        q = e.leer(sb1 + off + 4 * i + 2, 16) ^ clave
        if it:
            res.append((_ITEMS.get(it, it), q))
    return res


def dinero(e):
    sb2 = e.leer(e.s["gSaveBlock2Ptr"], 32)
    return e.leer(e._sb1() + 1168, 32) ^ e.leer(sb2 + 172, 32)


def comprar(e, tienda, compras, dependiente=None):
    """compras: [(indice_en_la_lista, cantidad)]. Habla con el dependiente de `tienda`."""
    m = _mapa_json(tienda)
    if dependiente is None:
        d = next(o for o in m["object_events"] if o["graphics_id"] == "OBJ_EVENT_GFX_MART_EMPLOYEE"
                 and "Dualocke" not in (o.get("script") or ""))
    else:
        d = dependiente
    ir(e, tienda)
    r = ir_a(e, (tienda, d["x"], d["y"]), al_lado=True)
    pulsar_a(e)
    for _ in range(40):           # textos hasta el menú COMPRAR/VENDER
        if e.cb2() == "CB2_BuyMenu" or tarea_activa(e, "Task_ShopMenu") is not None:
            break
        e.pulsar("a", despues=15)
    e.avanzar(30)
    if tarea_activa(e, "Task_ShopMenu") is not None:
        e.pulsar("a", despues=60)        # COMPRAR
    for _ in range(40):
        if e.cb2() == "CB2_BuyMenu":
            break
        e.avanzar(10)
    e.avanzar(60)
    e.foto("/tmp/tienda.png")
    pos = 0
    antes = dinero(e)
    for idx, cant in compras:
        while pos < idx:
            e.pulsar("abajo", despues=8); pos += 1
        while pos > idx:
            e.pulsar("arriba", despues=8); pos -= 1
        e.pulsar("a", despues=10)
        for _ in range(60):
            if tarea_activa(e, "Task_BuyHowManyDialogueHandleInput") is not None:
                break
            e.avanzar(10)
        else:
            e.apunta(f"  AVISO: no sale la cantidad del objeto {idx}")
            continue
        e.avanzar(10)
        for _ in range((cant - 1) // 10):
            e.pulsar("derecha", despues=15)
        for _ in range((cant - 1) % 10):
            e.pulsar("arriba", despues=15)
        e.pulsar("a", despues=20)     # cantidad
        for _ in range(60):           # ¿de acuerdo? -> SÍ; gracias -> A; hasta volver a la lista
            if tarea_activa(e, "Task_BuyMenu") is not None:
                break
            e.pulsar("a", despues=20)
        e.avanzar(20)
    e.pulsar("b", despues=60)
    for _ in range(60):
        if e.controlable():
            break
        e.pulsar("b", despues=15)
    seguir(e)
    e.apunta(f"  compra en {tienda}: {antes} -> {dinero(e)} ₽")


POCKET = {"objetos": 0, "medicinas": 1, "balls": 2, "mt": 3, "bayas": 4, "megas": 5, "clave": 6}


def mochila(e, cual):
    """[(nombre, cantidad)] de un bolsillo, leyendo gBagPockets."""
    b = e.s["gBagPockets"] + POCKET[cual] * 8
    ptr = e.leer(b, 32)
    cap = e.leer(b + 4, 16) & 0x3FF
    sb2 = e.leer(e.s["gSaveBlock2Ptr"], 32)
    clave = e.leer(sb2 + 172, 32) & 0xFFFF
    res = []
    for i in range(min(cap, 120)):
        it = e.leer(ptr + 4 * i, 16)
        if it:
            res.append((_ITEMS.get(it, it), e.leer(ptr + 4 * i + 2, 16) ^ clave))
    return res


MENU_PAUSA = {"pokedex": 0, "pokemon": 1, "mochila": 2, "pokenav": 3, "jugador": 4, "guardar": 5, "opciones": 6, "salir": 7}


def menu_pausa(e, cual):
    """Abre el menú START y elige `cual`."""
    for _ in range(5):
        e.pulsar("start", despues=30)
        if tarea_activa(e, "Task_ShowStartMenu") is not None or e.leer(e.s["sNumStartMenuActions"]) and not e.controlable():
            break
    e.avanzar(10)
    n = e.leer(e.s["sNumStartMenuActions"])
    acciones = [e.leer(e.s["sCurrentStartMenuActions"] + i) for i in range(n)]
    obj = acciones.index(MENU_PAUSA[cual])
    for _ in range(12):
        c = e.leer(e.s["sStartMenuCursorPos"])
        if c == obj:
            break
        e.pulsar("abajo" if c < obj else "arriba", despues=8)
    e.pulsar("a", despues=60)


def cerrar_menus(e):
    for _ in range(40):
        if e.controlable():
            return
        e.pulsar("b", despues=20)


def usar_objeto(e, bolsillo_, item, slot, veces=1):
    """Desde el mapa: MOCHILA -> bolsillo -> item -> USAR -> POKéMON del hueco `slot`, `veces` veces."""
    menu_pausa(e, "mochila")
    for _ in range(60):
        if e.cb2() == "CB2_BagMenuRun":
            break
        e.avanzar(5)
    e.avanzar(30)
    bp = e.s["gBagPosition"]
    p = POCKET[bolsillo_]
    for _ in range(10):
        if e.leer(bp + 5) == p:
            break
        e.pulsar("derecha" if e.leer(bp + 5) < p else "izquierda", despues=25)
    lista = [n for n, q in mochila(e, bolsillo_)]
    if item not in lista:
        e.apunta(f"  AVISO: no tengo {item}")
        cerrar_menus(e)
        return False
    idx = lista.index(item)
    for _ in range(40):
        c = e.leer(bp + 8 + 2 * p, 16) + e.leer(bp + 22 + 2 * p, 16)
        if c == idx:
            break
        e.pulsar("abajo" if c < idx else "arriba", despues=10)
    usados = 0
    while usados < veces:
        CTX = ("Task_ItemContext_MultipleRows", "Task_ItemContext_SingleRow", "Task_ItemContext_Normal")
        for _ in range(10):            # menú del objeto
            if tarea_activa(e, "Task_BagMenu_HandleInput") is not None:
                break
            e.avanzar(10)
        for _ in range(5):
            e.pulsar("a", despues=20)
            if any(tarea_activa(e, t) is not None for t in CTX):
                break
        e.pulsar("a", despues=40)      # USAR (la primera opción)
        for i_ in range(60):
            if e.cb2() == "CB2_UpdatePartyMenu":
                break
            e.avanzar(5)
            if i_ % 4 == 3 and bolsillo_ == "mt":
                e.pulsar("a", despues=10)      # "Has encendido la MO... ¿Enseñarle...?" -> SÍ
        else:
            e.apunta("  AVISO: usar_objeto no llega al menú del equipo")
            break
        e.avanzar(20)
        pm = e.s["gPartyMenu"]
        for _ in range(8):
            cur = e.leer(pm + OFF["pm_slot"])
            if cur == slot:
                break
            e.pulsar("abajo" if cur < slot or cur > 6 else "arriba", despues=10)
        e.pulsar("a", despues=30)
        # textos de subir de nivel, aprender movimientos, evolución...
        for _ in range(200):
            if e.cb2() == "CB2_BagMenuRun" and tarea_activa(e, "Task_BagMenu_HandleInput") is not None:
                break
            if tarea_activa(e, "Task_HandleReplaceMoveInput") is not None:
                e.aprende_idx = slot
                Combate(e).olvidar()
                continue
            if e.cb2() == "CB2_UpdatePartyMenu" and tarea_activa(e, "Task_HandleChooseMonInput") is not None:
                e.pulsar("b", despues=30)
                break
            e.pulsar("a", despues=15)
        usados += 1
        if getattr(e, "depurar", False):
            print("   uso", usados, resumen(e), mochila(e, bolsillo_))
        if item not in [n for n, q in mochila(e, bolsillo_)]:
            break
    cerrar_menus(e)
    return usados


_SECS = [s_["id"] for s_ in json.load(open(os.path.join(RAIZ_REPO, "src/data/region_map/region_map_sections.json")))["map_sections"]]
_KANTO = _SECS.index("MAPSEC_PALLET_TOWN")
_EXTRA = _SECS.index("MAPSEC_AQUA_HIDEOUT")


def zona_de(mid):
    return _mapa_json(mid).get("region_map_section")


def zona_usada(e, mapsec):
    ms = _SECS.index(mapsec)
    z = ms if ms < _KANTO else (_KANTO + ms - _EXTRA if ms >= _EXTRA else -1)
    if z < 0:
        return None
    v = e.leer(e.s["sZoneVars"] + 2 * (z // 16), 16)
    return bool(e.leer(e._sb1() + 5020 + 2 * (v - 0x4000), 16) >> (z % 16) & 1)


ENCUENTRO = ["sin regla", "primero", "shiny", "repetido", "legendario", "zona gastada"]


def buscar_captura(e, mapa, max_combates=15, casillas=None):
    """Anda por la hierba de mapa hasta que se gasta la zona (capturando al primero válido)."""
    zona = zona_de(mapa)
    casillas = casillas or hierba(mapa)
    import random
    rnd = random.Random(len(e.motes_usados) + 1000 * getattr(e, "semilla", 0))
    antes = len(equipo(e))
    for _ in range(80):
        if zona_usada(e, zona):
            break
        if e.mapa() != mapa:
            ir(e, mapa)
        x, y = e.pos()
        cerca = [c for c in casillas if abs(c[0] - x) + abs(c[1] - y) <= 6] or casillas
        r = ir_a(e, (mapa,) + rnd.choice(cerca), max_intentos=2)
        if e.en_combate() or r == "combate":
            seguir(e)
    e.apunta(f"  {zona}: gastada={zona_usada(e, zona)} equipo: {resumen(e)}")


_GFX_N = {}
_k = 0
for _l in open(os.path.join(RAIZ_REPO, "include/constants/event_objects.h")):
    _m = _re.match(r"\s+(OBJ_EVENT_GFX_\w+)\s*(?:=\s*(\d+))?\s*,", _l)
    if _m:
        if _m.group(2):
            _k = int(_m.group(2))
        _GFX_N.setdefault(_m.group(1), _k)
        _k += 1


def hablar_obj(e, gfx, **kw):
    """Habla con el personaje (vivo) con gráfico OBJ_EVENT_GFX_<gfx> más cercano."""
    n = _GFX_N["OBJ_EVENT_GFX_" + gfx]
    x, y = e.pos()
    objs = [o for o in e.objetos() if o[3] == n]
    if not objs:
        raise RuntimeError(f"no veo a {gfx} en {e.mapa()}: {e.objetos()}")
    for intento in range(8):
        x, y = e.pos()
        objs = [o for o in e.objetos() if o[3] == n]
        o = min(objs, key=lambda o: abs(o[0] - x) + abs(o[1] - y))
        r = ir_a(e, (e.mapa(), o[0], o[1]), al_lado=True, max_intentos=4)
        if r in ("combate",):
            seguir(e, **kw)
            continue
        # si anda de un lado a otro, esperar quieto a que pase al lado
        for _ in range(150):
            objs = [o2 for o2 in e.objetos() if o2[3] == n]
            o = min(objs, key=lambda o: abs(o[0] - e.pos()[0]) + abs(o[1] - e.pos()[1]))
            px, py = e.pos()
            d = abs(o[0] - px) + abs(o[1] - py)
            if d == 1 or (d == 2 and (o[0] == px or o[1] == py) and getattr(e, "mostrador", False)):
                e.mirar(hacia(px, py, o[0], o[1]))
                e.pulsar("a", fotogramas=4, despues=10)
                if not e.controlable() or e.en_combate():
                    return seguir(e, **kw)
            if d > 3 and _ % 25 == 24:
                break
            e.avanzar(4)
    e.apunta(f"  AVISO: no consigo hablar con {gfx}")
    return []


def suelo(mapa):
    """Casillas pisables (para buscar encuentros en cuevas)."""
    w, h, c, warps, _ = info_mapa(mapa)
    return [(x, y) for y in range(h) for x in range(w)
            if not c[y * w + x][0] and (x, y) not in warps and c[y * w + x][2] in ("MB_NORMAL", "MB_CAVE", "MB_TALL_GRASS", "MB_SAND", "MB_ASHGRASS", "MB_LONG_GRASS")]


def recoger(e, mapa, x, y):
    """Coge el objeto del suelo en (x, y)."""
    try:
        hablar_con(e, mapa, x, y)
    except RuntimeError as err:
        e.apunta(f"  AVISO: no cojo el objeto de {mapa} {x},{y}: {err}")


def foto_equipo(e, ruta):
    """Abre START -> POKéMON, hace la foto del equipo y cierra."""
    menu_pausa(e, "pokemon")
    for _ in range(60):
        if e.cb2() == "CB2_UpdatePartyMenu":
            break
        e.avanzar(5)
    e.avanzar(60)
    e.foto(os.path.join(AQUI, ruta))
    cerrar_menus(e)


def ficha(e):
    """Texto con el equipo: especie, nivel, vida y movimientos."""
    lineas = []
    for m in equipo(e):
        movs = ", ".join(MOVES[x]["nombre"] for x in m["movs"] if x)
        lineas.append(f"{nombre(m['especie'])} {m['nivel']} ({m['hp']}/{m['maxhp']}): {movs}")
    return "\n".join(lineas)


def elegir(e, idx, max_a=40):
    """Pasa textos con A hasta que sale un menú de opciones (o SÍ/NO) y elige la opción idx."""
    hay = lambda: tarea_activa(e, "Task_HandleMultichoiceInput") is not None or tarea_activa(e, "Task_HandleYesNoInput") is not None  # noqa: E731
    for _ in range(max_a):
        if hay():
            break
        e.pulsar("a", fotogramas=3, despues=0)
        for _ in range(6):            # mirar a menudo: si el menú sale y pulso A, elijo la primera opción
            e.avanzar(3)
            if hay():
                break
    else:
        raise RuntimeError("elegir: no sale ningún menú")
    e.avanzar(10)
    for _ in range(12):
        c = e.leer(e.s["sMenu"] + 2)
        c = c - 256 if c > 127 else c
        if c == idx:
            break
        e.pulsar("abajo" if c < idx else "arriba", despues=10)
    e.pulsar("a", despues=20)


def hablar_y_elegir(e, mapa, x, y, opciones, **kw):
    """Habla con (x, y) y va eligiendo las opciones de los menús que salgan, en orden."""
    ir_a(e, (mapa, x, y), al_lado=True)
    e.mirar(hacia(e.pos()[0], e.pos()[1], x, y))
    pulsar_a(e)
    for o in opciones:
        elegir(e, o)
    return seguir(e, **kw)


def resolver_interruptores(e, mapa, objetivo, interruptores, profundidad=4):
    """Pisa interruptores (casillas con evento) hasta que haya camino a objetivo (función o (mapa,x,y)).
    Busca en anchura probando combinaciones con estados guardados."""
    import tempfile
    e.evitar = {mapa: set(interruptores)}
    def hay_camino():
        refrescar_mapa(e)
        x, y, z = e.jugador()
        tap = {mapa: {(o[0], o[1]) for o in e.objetos()} | set(interruptores)}
        return planear((mapa, x, y, z), objetivo, tapadas_mapa=tap) is not None
    if hay_camino():
        return True
    base = tempfile.mktemp(suffix=".ss", dir=AQUI)
    e.guardar_estado(base)
    cola = [()]
    vistos = set()
    while cola:
        sec = cola.pop(0)
        if len(sec) >= profundidad:
            continue
        for sw in interruptores:
            if sec and sec[-1] == sw:
                continue
            nueva = sec + (sw,)
            e.cargar_estado(base)
            e.avanzar(2)
            ok = True
            for paso_ in nueva:
                e.evitar = {mapa: set(interruptores) - {paso_}}
                r = ir_a(e, (mapa,) + paso_, max_intentos=3)
                seguir(e)
                if e.pos() != paso_:
                    ok = False
                    break
                # salir de la casilla para poder volver a pisarla
                for d in DIRS:
                    if e.paso(d):
                        break
                seguir(e)
            if not ok:
                continue
            refrescar_mapa(e)
            firma = tuple(c[0] for c in mundo().rejillas[mapa][2])
            if firma in vistos:
                continue
            vistos.add(firma)
            e.evitar = {mapa: set(interruptores)}
            if hay_camino():
                e.apunta(f"  interruptores: {nueva}")
                os.remove(base)
                return True
            cola.append(nueva)
    e.cargar_estado(base)
    os.remove(base)
    return False


def gimnasio_malvalona(e):
    """Va hasta ERICO pisando interruptores: si no hay camino, pisa el interruptor alcanzable más cercano
    que no sea el último pisado (cada uno cambia las barreras)."""
    G = "MAP_MAUVILLE_CITY_GYM"
    SW = [(0, 15), (4, 12), (3, 9), (8, 9)]   # estados 1..4
    obj = lambda s: s[0] == G and abs(s[1] - 5) + abs(s[2] - 2) == 1  # noqa: E731
    for _ in range(8):
        e.evitar = {G: set(SW)}
        refrescar_mapa(e)
        x, y, z = e.jugador()
        tap = {G: {(o[0], o[1]) for o in e.objetos()} | set(SW)}
        if planear((G, x, y, z), obj, tapadas_mapa=tap):
            hablar_con(e, G, 5, 2)
            e.evitar = {}
            return True
        ultimo = var(e, "VAR_MAUVILLE_GYM_STATE")
        opciones = []
        for i, t in enumerate(SW):
            if i + 1 == ultimo:
                continue
            tap2 = {G: {(o[0], o[1]) for o in e.objetos()} | (set(SW) - {t})}
            c = planear((G, x, y, z), (G,) + t, tapadas_mapa=tap2)
            if c is not None:
                opciones.append((len(c), t))
        if not opciones:
            break
        t = min(opciones)[1]
        e.evitar = {G: set(SW) - {t}}
        for _ in range(5):
            ir_a(e, (G,) + t)
            seguir(e)
            if e.pos() == t:
                break
        e.apunta(f"  interruptor {t}: estado {var(e, 'VAR_MAUVILLE_GYM_STATE')}")
    e.evitar = {}
    return False


def intentar(e, accion, n=6, nombre_=""):
    """Hace accion(e); si se pierde un combate o muere alguien, recarga y lo intenta de otra forma
    (como quien recarga la partida). Devuelve el número de intento que salió bien."""
    import tempfile
    base = tempfile.mktemp(suffix=".ss", dir=AQUI)
    e.guardar_estado(base)
    vidas = var(e, "VAR_DUALOCKE_LIVES")
    e.fallos_intentar = []
    for i in range(n):
        if i:
            e.cargar_estado(base)
            e.avanzar(2)
            e.apunta(f"  ... recargo y repito {nombre_} (intento {i + 1})")
        e.semilla = i
        perdio = lambda: var(e, "VAR_DUALOCKE_LIVES") != vidas or flag(e, "FLAG_DUALOCKE_LOCKE_LOST")  # noqa: E731
        try:
            accion(e)
        except RuntimeError as err:
            e.apunta(f"  AVISO en {nombre_}: {err}")
            e.fallos_intentar.append("combate" if perdio() else "nav: " + str(err))
            continue
        e.fallos_intentar.append("combate")
        if not perdio():
            os.remove(base)
            return i + 1
    e.apunta(f"  AVISO: {nombre_} sale mal {n} veces; me quedo con el último intento")
    os.remove(base)
    return 0


def con_ayuda(e, accion, nombre_, intentos_limpios=3):
    """Intenta `accion` sin ayuda; si sale mal, con el modo dios declarado (rellenar vida en combate)."""
    import tempfile
    base = tempfile.mktemp(suffix=".ss", dir=AQUI)
    e.guardar_estado(base)
    n = intentar(e, accion, n=intentos_limpios, nombre_=nombre_)
    if n:
        os.remove(base)
        return f"sin ayuda (intento {n})"
    e.cargar_estado(base)
    e.avanzar(2)
    os.remove(base)
    if e.fallos_intentar and all(f.startswith("nav") for f in e.fallos_intentar):
        # no es culpa de los combates: la ayuda no vale aquí, es un problema del camino
        raise RuntimeError(f"{nombre_}: falla el camino, no los combates: {e.fallos_intentar[-1]}")
    e.apunta(f"  *** {nombre_}: no lo saco limpio; repito con AYUDA (vida rellena en combate)")
    e.modo_dios = True
    try:
        accion(e)
    finally:
        e.modo_dios = False
    return "con ayuda"


def gimnasio_petalia(e):
    """Sube por las salas del gimnasio de NORMAN abriendo puertas (carteles con SÍ/NO) hasta él."""
    G = "MAP_PETALBURG_CITY_GYM"
    puertas = [(b["x"], b["y"]) for b in _mapa_json(G)["bg_events"] if "Door" in (b.get("script") or "")]
    for _ in range(10):
        x, y = e.pos()
        if y <= 8:
            break
        # puertas de la sala actual: las de más abajo que estén por encima de mí
        arriba = [p for p in puertas if p[1] < y and y - p[1] <= 12]
        if not arriba:
            break
        fila = max(p[1] for p in arriba)
        # el entrenador de la sala: hay que ganarle para que se abran las puertas
        for o in _mapa_json(G)["object_events"]:
            if o.get("trainer_type") == "TRAINER_TYPE_NORMAL" and fila < o["y"] <= y + 1:
                tr = (o["script"] or "")
                try:
                    hablar_con(e, G, o["x"], o["y"])
                except RuntimeError as err:
                    e.apunta(f"  AVISO: {err}")
        hecho = False
        for p in sorted([p for p in arriba if p[1] == fila], key=lambda p: abs(p[0] - x)):
            r = ir_a(e, (G, p[0], p[1] + 1), max_intentos=6)
            seguir(e)
            if e.pos() != (p[0], p[1] + 1):
                continue
            e.mirar("arriba")
            if pulsar_a(e, intentos=2):
                for _ in range(60):
                    if e.controlable() and e.pos()[1] < p[1]:
                        break
                    e.pulsar("a", despues=15)
                seguir(e)
                if e.pos()[1] < p[1]:
                    hecho = True
                    e.apunta(f"  puerta {p} -> {e.pos()}")
                    break
        if not hecho:
            e.apunta("  AVISO: no paso de sala en el gimnasio de PETALIA")
            break
    hablar_con(e, G, 4, 2)


def eclosionar(e, mapa, maximo=20000):
    """Anda de un lado a otro en `mapa` hasta que eclosionen los huevos del equipo."""
    x0, y0 = e.pos()
    pasos = 0
    w, h, c, _, _ = info_mapa(mapa)
    # dos casillas libres en línea para ir y venir
    d1, d2 = ("derecha", "izquierda")
    while pasos < maximo and any(m["huevo"] for m in equipo(e)):
        for d in (d1,) * 6 + (d2,) * 6:
            if not e.paso(d):
                d1, d2 = d2, d1
            pasos += 1
            if not e.controlable() or e.en_combate():
                seguir(e)
        if pasos % 600 == 0:
            e.apunta(f"  ... {pasos} pasos")
    return pasos


# --- puertas giratorias (gimnasio de ARBORADA): simulación de src/rotating_gate.c ---
_ARM_LAYOUT = {"L1": [1, 0, 1, 0, 0, 0, 0, 0], "L2": [1, 1, 1, 0, 0, 0, 0, 0], "L3": [1, 0, 1, 1, 0, 0, 0, 0],
               "L4": [1, 1, 1, 1, 0, 0, 0, 0], "T1": [1, 0, 1, 0, 1, 0, 0, 0], "T2": [1, 1, 1, 0, 1, 0, 0, 0],
               "T3": [1, 0, 1, 1, 1, 0, 0, 0], "T4": [1, 0, 1, 0, 1, 1, 0, 0]}
_N, _E, _S, _W = 0, 1, 2, 3
_ACW, _CW = 1, 2


def _rot(d, arm, larga):
    return (d << 4) | (arm << 1) | larga


_NONE = 255
_ROT = {
    "arriba": [_NONE] * 4 + [_rot(_CW, _W, 1), _rot(_CW, _W, 0), _rot(_ACW, _E, 0), _rot(_ACW, _E, 1)] + [_NONE] * 8,
    "abajo": [_NONE] * 8 + [_rot(_ACW, _W, 1), _rot(_ACW, _W, 0), _rot(_CW, _E, 0), _rot(_CW, _E, 1)] + [_NONE] * 4,
    "izquierda": [_NONE, _rot(_ACW, _N, 1), _NONE, _NONE, _NONE, _rot(_ACW, _N, 0), _NONE, _NONE,
                  _NONE, _rot(_CW, _S, 0), _NONE, _NONE, _NONE, _rot(_CW, _S, 1), _NONE, _NONE],
    "derecha": [_NONE, _NONE, _rot(_CW, _N, 1), _NONE, _NONE, _NONE, _rot(_CW, _N, 0), _NONE,
                _NONE, _NONE, _rot(_ACW, _S, 0), _NONE, _NONE, _NONE, _rot(_ACW, _S, 1), _NONE],
}
_POS_CW = [(0, -1), (1, -2), (0, 0), (1, 0), (-1, 0), (-1, 1), (-1, -1), (-2, -1)]
_POS_ACW = [(-1, -1), (-1, -2), (0, -1), (1, -1), (0, 0), (0, 1), (-1, 0), (-2, 0)]
PUERTAS_ARBORADA = [(6, 7, "T2"), (9, 15, "T2"), (3, 19, "T2"), (2, 6, "T1"), (9, 12, "T1"), (6, 23, "T1"), (12, 22, "T1"), (6, 3, "L4")]


def _puerta_bloquea(c, w, h, puertas, orients, d, nx, ny):
    """None si no hay puerta; (bloquea, nuevas_orients)."""
    for i, (gx, gy, forma) in enumerate(puertas):
        if gx - 2 <= nx <= gx + 1 and gy - 2 <= ny <= gy + 1:
            info = _ROT[d][(ny - gy + 2) * 4 + (nx - gx + 2)]
            if info == _NONE:
                continue
            sentido, arm_info = info >> 4, info & 0xF
            arm, larga = arm_info // 2, arm_info % 2
            o = orients[i]
            if not _ARM_LAYOUT[forma][((arm - o + 4) % 4) * 2 + larga]:
                continue
            pos = _POS_ACW if sentido == _ACW else _POS_CW
            for a in range(4):
                for j in range(2):
                    if _ARM_LAYOUT[forma][2 * a + j]:
                        k = 2 * ((o + a) % 4) + j
                        px, py = gx + pos[k][0], gy + pos[k][1]
                        if not (0 <= px < w and 0 <= py < h) or c[py * w + px][0]:
                            return True, orients
            nuevo = list(orients)
            nuevo[i] = (o - 1) % 4 if sentido == _ACW else (o + 1) % 4
            return False, tuple(nuevo)
    return None


def plan_puertas(e, mapa, puertas, objetivo):
    """BFS sobre (x, y, orientaciones) hasta objetivo(x, y). Devuelve la lista de direcciones."""
    w, h, c, _, _ = info_mapa(mapa)
    orients = tuple(e.leer(e._sb1() + 5020 + 2 * (_VARS[1]("VAR_TEMP_0") - 0x4000) + i) for i in range(len(puertas)))
    tap = {(o[0], o[1]) for o in e.objetos()}
    x, y = e.pos()
    ini = (x, y, orients)
    prev = {ini: None}
    cola = deque([ini])
    while cola:
        s = cola.popleft()
        if objetivo(s[0], s[1]):
            camino = []
            while prev[s]:
                d, p = prev[s]
                camino.append(d)
                s = p
            return camino[::-1]
        for d, (dx, dy) in DIRS.items():
            nx, ny = s[0] + dx, s[1] + dy
            if not (0 <= nx < w and 0 <= ny < h) or c[ny * w + nx][0] or (nx, ny) in tap:
                continue
            r = _puerta_bloquea(c, w, h, puertas, s[2], d, nx, ny)
            no = s[2]
            if r is not None:
                if r[0]:
                    continue
                no = r[1]
            n = (nx, ny, no)
            if n not in prev:
                prev[n] = (d, s)
                cola.append(n)
    return None


def gimnasio_arborada(e):
    G = "MAP_FORTREE_CITY_GYM"
    ir(e, G)
    for _ in range(6):
        camino = plan_puertas(e, G, PUERTAS_ARBORADA, lambda x, y: abs(x - 15) + abs(y - 2) == 1)
        if camino is None:
            raise RuntimeError("arborada: no hay camino con las puertas")
        for d in camino:
            if not e.paso(d, correr=False):
                break
            if not e.controlable() or e.en_combate():
                seguir(e)
                break
        else:
            break
    hablar_con(e, G, 15, 2)


_SECCIONES = {s_["id"]: s_ for s_ in json.load(open(os.path.join(RAIZ_REPO, "src/data/region_map/region_map_sections.json")))["map_sections"]}


def volar(e, mapsec):
    tipo = _mapa_json(e.mapa()).get("map_type")
    if tipo == "MAP_TYPE_UNDERGROUND":
        cuerda_huida(e)
    elif tipo == "MAP_TYPE_INDOOR":
        fuera = ("MAP_TYPE_TOWN", "MAP_TYPE_CITY", "MAP_TYPE_ROUTE", "MAP_TYPE_OCEAN_ROUTE")
        for _ in range(4):
            if ir_a(e, lambda s_: _mapa_json(s_[0]).get("map_type") in fuera) == "ok":
                break
            seguir(e)
    for intento in range(3):
        if _volar(e, mapsec):
            return True
        cerrar_menus(e)
    return False


def _volar(e, mapsec):
    """START -> POKéMON -> el que sabe VUELO -> VUELO -> elegir mapsec en el mapa."""
    vuelo = DATOS["ids"]["MOVE_FLY"]
    slot = next(m["i"] for m in equipo(e) if vuelo in m["movs"])
    menu_pausa(e, "pokemon")
    for _ in range(60):
        if e.cb2() == "CB2_UpdatePartyMenu":
            break
        e.avanzar(5)
    e.avanzar(30)
    pm = e.s["gPartyMenu"]
    for _ in range(8):
        cur = e.leer(pm + OFF["pm_slot"])
        if cur == slot:
            break
        e.pulsar("abajo" if cur < slot or cur > 6 else "arriba", despues=10)
    e.pulsar("a", despues=30)
    e.pulsar("abajo", despues=15)      # el primero es DATOS; VUELO va justo después
    e.pulsar("a", despues=60)
    for _ in range(80):
        if e.leer(e.s["sFlyMap"], 32):
            break
        e.avanzar(5)
    else:
        e.apunta("  AVISO: no se abre el mapa de VUELO")
        cerrar_menus(e)
        return False
    e.avanzar(60)
    fm = e.leer(e.s["sFlyMap"], 32)
    sec = _SECCIONES[mapsec]
    tx, ty = sec["x"] + 1, sec["y"] + 2      # MAPCURSOR_X_MIN, MAPCURSOR_Y_MIN
    for _ in range(60):
        cx = e.leer(fm + 8 + 0x54, 16)
        cy = e.leer(fm + 8 + 0x56, 16)
        if (cx, cy) == (tx, ty) or (tx <= cx < tx + sec.get("width", 1) and ty <= cy < ty + sec.get("height", 1)):
            break
        if cx < tx:
            e.pulsar("derecha", fotogramas=2, despues=14)
        elif cx > tx:
            e.pulsar("izquierda", fotogramas=2, despues=14)
        elif cy < ty:
            e.pulsar("abajo", fotogramas=2, despues=14)
        else:
            e.pulsar("arriba", fotogramas=2, despues=14)
    # afinar: mirar qué sección hay bajo el cursor y probar las casillas de al lado
    objetivo = _SECS.index(mapsec)
    for d in ["", "derecha", "arriba", "izquierda", "izquierda", "abajo", "abajo", "derecha", "derecha"]:
        if d:
            e.pulsar(d, fotogramas=2, despues=14)
        if e.leer(fm + 8, 16) == objetivo:
            break
    else:
        e.apunta(f"  AVISO: no encuentro {mapsec} en el mapa de VUELO")
    e.pulsar("a", despues=30)
    for _ in range(100):
        if e.controlable():
            break
        e.avanzar(10)
    seguir(e)
    e.apunta(f"  vuelo a {mapsec}: {e.mapa()}")
    return True


def plan_rocas(e, objetivo, max_estados=200000):
    """BFS en el mapa actual empujando rocas de FUERZA. objetivo(x, y). Devuelve direcciones."""
    mid = e.mapa()
    refrescar_mapa(e)
    w, h, c, warps, _ = info_mapa(mid)
    nroca = _GFX_N["OBJ_EVENT_GFX_PUSHABLE_BOULDER"]
    nromp = _GFX_N["OBJ_EVENT_GFX_BREAKABLE_ROCK"]
    rocas = frozenset((o[0], o[1]) for o in e.objetos() if o[3] == nroca)
    romp0 = frozenset((o[0], o[1]) for o in e.objetos() if o[3] == nromp) if sabe_mo(e, "MOVE_ROCK_SMASH") else frozenset()
    otros = {(o[0], o[1]) for o in e.objetos() if o[3] != nroca and (o[0], o[1]) not in romp0}
    x, y, z = e.jugador()

    def libre(px, py):
        return 0 <= px < w and 0 <= py < h and not c[py * w + px][0] and (px, py) not in otros

    # estado: (x, y, rocas de FUERZA, rocas rompibles que quedan); "R"+dir = romper la de esa dirección
    ini = (x, y, rocas, romp0)
    prev = {ini: None}
    cola = deque([ini])
    while cola and len(prev) < max_estados:
        s = cola.popleft()
        if objetivo(s[0], s[1]):
            camino = []
            while prev[s]:
                d, p = prev[s]
                camino.append(d)
                s = p
            return camino[::-1]
        for d, (dx, dy) in DIRS.items():
            nx, ny = s[0] + dx, s[1] + dy
            accion = d
            if (nx, ny) in s[3]:
                n = (s[0], s[1], s[2], s[3] - {(nx, ny)})
                accion = "R" + d
            elif (nx, ny) in s[2]:
                bx, by = nx + dx, ny + dy
                if not libre(bx, by) or (bx, by) in s[2] or (bx, by) in warps or (bx, by) in s[3]:
                    continue
                n = (nx, ny, s[2] - {(nx, ny)} | {(bx, by)}, s[3])
            elif libre(nx, ny) or (nx, ny) in warps:
                n = (nx, ny, s[2], s[3])
            else:
                continue
            if n not in prev:
                prev[n] = (accion, s)
                cola.append(n)
    return None


def con_fuerza(e, objetivo, replanes=6):
    """Va empujando rocas (y rompiendo las rompibles) hasta objetivo(x, y) del mapa actual.
    Si un combate o algo descuadra el camino, vuelve a planear desde donde esté."""
    nroca = _GFX_N["OBJ_EVENT_GFX_PUSHABLE_BOULDER"]
    mid = e.mapa()
    for _ in range(replanes):
        if e.mapa() != mid:
            return False
        if objetivo(*e.pos()):
            return True
        camino = plan_rocas(e, objetivo)
        if camino is None:
            return False
        activa = False
        descuadre = False
        for d in camino:
            px, py = e.pos()
            if d.startswith("R"):
                e.mirar(d[1:])
                pulsar_a(e)
                seguir(e)
                continue
            dx, dy = DIRS[d]
            if (px + dx, py + dy) in {(o[0], o[1]) for o in e.objetos() if o[3] == nroca} and not activa:
                e.mirar(d)
                pulsar_a(e)
                for _ in range(20):
                    if e.controlable():
                        break
                    e.pulsar("a", despues=15)
                activa = True
            for _ in range(3):
                if e.paso(d, correr=False):
                    break
                e.avanzar(20)
            seguir(e)
            if e.mapa() != mid:
                return False
            if e.pos() != (px + dx, py + dy):
                descuadre = True
                break
        if not descuadre:
            return objetivo(*e.pos())
    return False


def reiniciar_sala(e):
    """Sale por la puerta más cercana y vuelve a entrar: las rocas de FUERZA vuelven a su sitio."""
    mid = e.mapa()
    x, y, z = e.jugador()
    warps = set(info_mapa(mid)[3])
    tap = {mid: {(o[0], o[1]) for o in e.objetos()}}
    c = planear((mid, x, y, z), lambda s: s[0] == mid and (s[1], s[2]) in warps, tapadas_mapa=tap)
    if not c:
        return False
    e.apunta(f"  las rocas de {mid} se han quedado mal: salgo y vuelvo a entrar")
    ir_a(e, lambda s: s[0] != mid)
    seguir(e)
    if e.mapa() == mid:
        return False
    ir_a(e, lambda s: s[0] == mid)
    seguir(e)
    return e.mapa() == mid


def empujar_rocas(e, obj):
    """Si el camino (sin contar rocas de FUERZA) pasa por una roca, las empuja hasta pasarla."""
    mid = e.mapa()
    nroca = _GFX_N["OBJ_EVENT_GFX_PUSHABLE_BOULDER"]
    rocas = {(o[0], o[1]) for o in e.objetos() if o[3] == nroca}
    if not rocas or not sabe_mo(e, "MOVE_STRENGTH"):
        return False
    x, y, z = e.jugador()
    nromp_ = _GFX_N["OBJ_EVENT_GFX_BREAKABLE_ROCK"]
    tap = {mid: {(o[0], o[1]) for o in e.objetos() if o[3] not in (nroca, nromp_)}}
    camino = planear((mid, x, y, z), obj, tapadas_mapa=tap)
    if not camino:
        return False
    pasos = [(s_[1], s_[2]) for d, s_ in camino if s_[0] == mid]
    if any(p in rocas for p in pasos) and pasos:
        # primero, intentar llegar empujando hasta la salida de este mapa (no a la casilla de después de la roca)
        fin = pasos[-1]
        if fin not in rocas and plan_rocas(e, lambda a, b: (a, b) == fin, max_estados=60000) is None:
            # a lo mejor hay que romper antes una roca para poder empujar desde otro lado
            nr = _GFX_N["OBJ_EVENT_GFX_BREAKABLE_ROCK"]
            for o in list(e.objetos()):
                if o[3] == nr and sabe_mo(e, "MOVE_ROCK_SMASH"):
                    x, y, z = e.jugador()
                    tap2 = {mid: {(p[0], p[1]) for p in e.objetos()}}
                    if planear((mid, x, y, z), lambda s, o=o: s[0] == mid and abs(s[1] - o[0]) + abs(s[2] - o[1]) == 1,
                               tapadas_mapa=tap2) is None:
                        continue
                    e.apunta(f"  rompo la roca de {mid} {o[0]},{o[1]} para poder empujar")
                    try:
                        hablar_con(e, mid, o[0], o[1])
                    except RuntimeError as err:
                        e.apunta(f"  AVISO: {err}")
        if fin not in rocas and plan_rocas(e, lambda a, b: (a, b) == fin, max_estados=60000) is not None:
            e.apunta(f"  empujo rocas de FUERZA en {mid} hasta {fin}")
            return con_fuerza(e, lambda a, b: (a, b) == fin)
        # ¿rocas atascadas? las de la sala sin mover darían camino: reiniciar la sala
        orig = {(o["x"], o["y"]) for o in _mapa_json(mid).get("object_events", [])
                if o.get("graphics_id") == "OBJ_EVENT_GFX_PUSHABLE_BOULDER"}
        if orig and not rocas <= orig and getattr(e, "reinicios_sala", 0) < 3:
            e.reinicios_sala = getattr(e, "reinicios_sala", 0) + 1
            if reiniciar_sala(e):
                return True
    for i, p in enumerate(pasos):
        if p in rocas:
            # la casilla más lejana del camino (hasta 20 pasos después de la roca) a la que se pueda llegar
            # empujando: así no se empuja la roca hacia donde luego tapa el paso
            despues = [q for q in pasos[i + 1:i + 21] if q not in rocas]
            for meta in reversed(despues):
                if plan_rocas(e, lambda a, b, meta=meta: (a, b) == meta, max_estados=30000) is not None:
                    e.apunta(f"  empujo rocas de FUERZA en {mid} hacia {meta}")
                    return con_fuerza(e, lambda a, b, meta=meta: (a, b) == meta)
            return False
    return False


def usar_clave(e, item):
    """Usa un objeto clave desde la MOCHILA (BICI, CUERDA HUIDA...)."""
    menu_pausa(e, "mochila")
    for _ in range(60):
        if e.cb2() == "CB2_BagMenuRun":
            break
        e.avanzar(5)
    e.avanzar(30)
    bp = e.s["gBagPosition"]
    p = POCKET["clave"]
    for _ in range(10):
        if e.leer(bp + 5) == p:
            break
        e.pulsar("derecha" if e.leer(bp + 5) < p else "izquierda", despues=25)
    lista = [n for n, q in mochila(e, "clave")]
    idx = lista.index(item)
    for _ in range(40):
        c = e.leer(bp + 8 + 2 * p, 16) + e.leer(bp + 22 + 2 * p, 16)
        if c == idx:
            break
        e.pulsar("abajo" if c < idx else "arriba", despues=10)
    e.pulsar("a", despues=30)
    e.pulsar("a", despues=60)
    for _ in range(60):
        if e.controlable():
            break
        e.avanzar(10)


def en_bici(e):
    return bool(e.leer(e.s["gPlayerAvatar"]) & 0x06)


def cuerda_huida(e):
    """Usa la CUERDA HUIDA (objeto clave) para salir de una cueva o guarida."""
    menu_pausa(e, "mochila")
    for _ in range(60):
        if e.cb2() == "CB2_BagMenuRun":
            break
        e.avanzar(5)
    e.avanzar(30)
    bp = e.s["gBagPosition"]
    p = POCKET["clave"]
    for _ in range(10):
        if e.leer(bp + 5) == p:
            break
        e.pulsar("derecha" if e.leer(bp + 5) < p else "izquierda", despues=25)
    lista = [n for n, q in mochila(e, "clave")]
    idx = lista.index("ESCAPE_ROPE")
    for _ in range(40):
        c = e.leer(bp + 8 + 2 * p, 16) + e.leer(bp + 22 + 2 * p, 16)
        if c == idx:
            break
        e.pulsar("abajo" if c < idx else "arriba", despues=10)
    antes = e.mapa()
    e.pulsar("a", despues=30)
    e.pulsar("a", despues=60)
    for _ in range(120):
        if e.mapa() != antes and e.controlable():
            break
        e.pulsar("a", despues=10) if not e.cb2() == "CB2_Overworld" else e.avanzar(10)
    seguir(e)
    e.apunta(f"  CUERDA HUIDA: {antes} -> {e.mapa()}")
    return e.mapa() != antes



def plantillas(e):
    """[(i, localId, x, y)] de gSaveBlock1Ptr->objectEventTemplates (posiciones guardadas de los objetos)."""
    p = e.leer(e.s["gSaveBlock1Ptr"], 32) + 0xC70
    res = []
    for i in range(64):
        a = p + 0x18 * i
        lid = e.leer(a)
        if lid:
            x, y = e.leer(a + 4, 16), e.leer(a + 6, 16)
            res.append((i, lid, x - 0x10000 if x >= 0x8000 else x, y - 0x10000 if y >= 0x8000 else y))
    return res


_MAPBIN = {}


def metatiles(mid):
    """Ids de metatile del .bin del layout (sin colisión ni altura)."""
    if mid not in _MAPBIN:
        M = mundo()
        l = M.layouts[M.mapas[mid]["layout"]]
        raw = open(os.path.join(RAIZ_REPO, l["blockdata_filepath"]), "rb").read()
        _MAPBIN[mid] = [int.from_bytes(raw[k:k + 2], "little") & 0x3FF for k in range(0, len(raw), 2)]
    return _MAPBIN[mid]


def gimnasio_algaria(e):
    """Gimnasio de ALGARIA: estatuas sobre flechas de colores que se mueven un paso (en la dirección de
    su flecha) cada vez que pisas un interruptor de su color. Simula el puzle entero (posiciones guardadas
    de todas las estatuas, teletransportes e interruptores) con una búsqueda en anchura y ejecuta el camino;
    si un entrenador te para, vuelve a calcular desde donde estés."""
    from collections import deque
    G = "MAP_MOSSDEEP_CITY_GYM"
    if e.mapa() != G:
        ir(e, G)
    j = _mapa_json(G)
    COLOR = {"Yellow": 0, "Blue": 1, "Green": 2, "Purple": 3, "Red": 4}
    sw, trampa = {}, set()
    for c in j["coord_events"]:
        sc = c.get("script") or ""
        for k, v in COLOR.items():
            if k + "FloorSwitch" in sc:
                sw[(c["x"], c["y"])] = v
        if "WarpToEntrance" in sc:
            trampa.add((c["x"], c["y"]))
    estatuas_idx = {i for i, o in enumerate(j["object_events"]) if "STATUE" in o["graphics_id"]}
    w, h, c, warps, cons = info_mapa(G)
    mts = metatiles(G)
    ARR = 0x250
    lista_warps = [(wp["x"], wp["y"]) for wp in j["warp_events"]]
    META = {(23, 8), (24, 8)}

    def girar(est, color):
        nuevo = []
        for (x, y) in est:
            mt = mts[y * w + x] if 0 <= x < w and 0 <= y < h else 0
            if mt >= ARR and (mt - ARR) // 8 == color and (mt - ARR) % 8 < 4:
                dx, dy = [(1, 0), (0, 1), (-1, 0), (0, -1)][(mt - ARR) % 8]
                x, y = x + dx, y + dy
            nuevo.append((x, y))
        return tuple(nuevo)

    def resolver():
        # OJO: los entrenadores que están sobre flechas también se mueven con los interruptores
        pl = plantillas(e)
        vivos = {o[2]: (o[0], o[1]) for o in e.objetos()}
        est = tuple(sorted(vivos.get(lid, (x, y)) for i, lid, x, y in pl))
        otros = set()
        x0, y0, z0 = e.jugador()
        ini = (x0, y0, z0, est)
        prev = {ini: None}
        q = deque([ini])
        while q:
            s = q.popleft()
            x, y, z, est_ = s
            if (x, y) in META:
                camino = []
                while prev[s]:
                    s, d = prev[s]
                    camino.append(d)
                return camino[::-1]
            tap = set(est_) | otros | trampa
            for d, n in vecinos(G, x, y, z, False, tap, frozenset()):
                if n[0] != G:
                    continue
                nx, ny, nz = n[1], n[2], n[3]
                nest = est_
                if (nx, ny) in warps and (nx, ny) in lista_warps:
                    dest = warps[(nx, ny)][0][1]
                    if dest["dest_map"] != G:
                        continue
                    tx, ty = lista_warps[int(dest["dest_warp_id"])]
                    nx, ny, nz = tx, ty, nz
                elif (nx, ny) in sw:
                    nest = tuple(sorted(girar(est_, sw[(nx, ny)])))
                    if (nx, ny) in nest:      # una estatua no puede caer encima de mí
                        continue
                k = (nx, ny, nz, nest)
                if k not in prev:
                    prev[k] = (s, d)
                    q.append(k)
            if len(prev) > 300000:
                break
        return None

    vidas0 = var(e, "VAR_DUALOCKE_LIVES")
    for vuelta in range(250):
        if var(e, "VAR_DUALOCKE_LIVES") != vidas0 or flag(e, "FLAG_DUALOCKE_LOCKE_LOST"):
            raise RuntimeError("gimnasio de Algaria: he perdido un combate")
        if e.mapa() != G:
            ir(e, G)
        if e.pos() in META:
            break
        camino = resolver()
        e.apunta(f"    algaria: desde {e.pos()} -> {None if camino is None else len(camino)} pasos; objetos {sorted((o[0], o[1]) for o in e.objetos())}")
        if camino is None:
            raise RuntimeError("gimnasio de Algaria: el puzle no tiene solución desde aquí")
        if vuelta == 0:
            e.apunta(f"  puzle de Algaria: {len(camino)} pasos")
        for d in camino:
            antes = (e.mapa(), e.pos())
            e.paso(d)
            if e.en_combate() or not e.controlable():
                seguir(e)
            if (e.mapa(), e.pos()) == antes or e.mapa() != G:
                break          # me han parado (entrenador, texto...): recalculo
        else:
            continue
    hablar_con(e, G, 23, 7)
    seguir(e)


def bici_cruzar(e, destino, max_nodos=3000, meta=None, cerca=None):
    """Cruza un piso con SUELO AGRIETADO (Pilar Celeste) con la BICI CARRERA: búsqueda A* probando de
    verdad en el emulador qué pasa con cada tecla en cada casilla (acelerar, frenar, girar...).
    destino: mapa al que hay que llegar (por la escalera). Si te caes, esa rama se descarta."""
    import heapq
    import tempfile
    mid = e.mapa()
    if not en_bici(e):
        usar_clave(e, "MACH_BIKE")
    pa = e.s["gPlayerAvatar"]
    TECLA = {"arriba": 64, "abajo": 128, "izquierda": 32, "derecha": 16}
    w, h, c, warps, _ = info_mapa(mid)
    metas = cerca or [(x, y) for (x, y), l in warps.items() if l[0][1]["dest_map"] == destino]
    if meta is None:
        meta = lambda m, p: m == destino  # noqa: E731

    # distancia real andando (sin paredes) hasta las casillas objetivo, para guiar la búsqueda
    from collections import deque as _dq
    dist = {m: 0 for m in metas}
    q_ = _dq(metas)
    while q_:
        px, py = q_.popleft()
        for dx, dy in DIRS.values():
            nx, ny = px + dx, py + dy
            if 0 <= nx < w and 0 <= ny < h and not c[ny * w + nx][0] and (nx, ny) not in dist:
                dist[(nx, ny)] = dist[(px, py)] + 1
                q_.append((nx, ny))

    def h_(p):
        return dist.get(p, 99)

    def agujeros():
        refrescar_mapa(e)
        _, _, cc = mundo().rejilla(mid)
        return frozenset(i for i, t in enumerate(cc) if t[2] == "MB_CRACKED_FLOOR_HOLE")

    def clave():
        return (e.pos(), e.leer(pa + 0x0A), e.leer(pa + 0x0B), e.leer(e.s["gObjectEvents"] + e.leer(pa + 5) * 0x24 + 0x18) & 0xF,
                agujeros())

    def accion(d):
        """Mantiene d (o nada) hasta el siguiente punto de decisión. Devuelve False si me caigo o no pasa nada."""
        antes = e.pos()
        e.orden("keys %d" % (TECLA[d] if d else 0))
        for _ in range(40):
            e.avanzar(1)
            if e.mapa() != mid or e.pos() != antes:
                break
        else:
            # no me he movido: chocar contra la pared también vale (para la bici del todo)
            e.orden("keys 0")
            e.avanzar(10)
            return True
        for _ in range(30):            # hasta el centro de la casilla (donde el juego vuelve a leer las teclas)
            if e.mapa() != mid or e.leer(pa + 3) != 1:
                break
            e.avanzar(1)
        if e.mapa() != mid:
            e.orden("keys 0")
            return True
        return True

    base = tempfile.mktemp(suffix=".ss", dir=AQUI)
    e.guardar_estado(base)
    ficheros = [base]
    cola = [(h_(e.pos()), 0, 0, base, [])]
    vistos = {clave()}
    n = 0
    hallado = None
    try:
        while cola and n < max_nodos and hallado is None:
            _, g, _, fich, hist = heapq.heappop(cola)
            for d in ("arriba", "abajo", "izquierda", "derecha", None):
                e.cargar_estado(fich)
                if not accion(d):
                    continue
                n += 1
                if e.mapa() == mid and var(e, "VAR_ICE_STEP_COUNT") == 0:
                    e.orden("keys 0")
                    for _ in range(60):       # dejar que caiga del todo
                        e.avanzar(5)
                        if e.mapa() != mid and e.controlable():
                            break
                if meta(e.mapa(), e.pos()):
                    hallado = hist + [d]
                    break
                if e.mapa() != mid or var(e, "VAR_ICE_STEP_COUNT") == 0:
                    continue          # me he caído donde no era
                k = clave()
                if k in vistos:
                    continue
                vistos.add(k)
                e._bici_pos = getattr(e, "_bici_pos", set()) | {e.pos()}
                nf = tempfile.mktemp(suffix=".ss", dir=AQUI)
                e.guardar_estado(nf)
                ficheros.append(nf)
                heapq.heappush(cola, (g + 1 + h_(e.pos()), g + 1, n, nf, hist + [d]))
        if hallado is None:
            e.cargar_estado(base)
            raise RuntimeError(f"bici_cruzar: no encuentro cómo cruzar {mid} ({n} pruebas)")
        # repetir el camino de verdad desde el principio
        e.cargar_estado(base)
        for d in hallado:
            accion(d)
        e.orden("keys 0")
        for _ in range(60):
            e.avanzar(5)
            if e.controlable():
                break
        if e.mapa() == mid and var(e, "VAR_ICE_STEP_COUNT") == 0:
            for _ in range(60):
                e.avanzar(5)
                if e.mapa() != mid and e.controlable():
                    break
        e.apunta(f"  BICI CARRERA por {mid}: {len(hallado)} casillas ({n} pruebas) -> {e.mapa()} {e.pos()}")
        return meta(e.mapa(), e.pos())
    finally:
        e.orden("keys 0")
        for f in ficheros:
            if os.path.exists(f):
                os.remove(f)


def gimnasio_arrecipolis(e):
    """Gimnasio de ARRECÍPOLIS: en cada sala hay que pisar TODO el hielo fino una sola vez (si pisas uno
    ya agrietado te caes al sótano) para que se abra la escalera. Busca en profundidad un recorrido que
    pise cada casilla de hielo una vez y acabe junto a la escalera, y lo anda."""
    G = "MAP_SOOTOPOLIS_CITY_GYM_1F"
    if e.mapa() != G:
        ir(e, G)
    # (casilla de escalera que se abre, primera casilla de la sala siguiente)
    SALAS = [((8, 16), (8, 15)), ((8, 11), (8, 10)), ((8, 5), (8, 4))]
    import sys as _s
    _s.setrecursionlimit(10000)
    for escalera, siguiente in SALAS:
        refrescar_mapa(e)
        w, h, c = mundo().rejilla(G)
        x0, y0 = e.pos()
        cerradas = {p for p, _ in SALAS} | {q for _, q in SALAS}
        # sala: lo alcanzable sin cruzar escaleras
        sala, pila = {(x0, y0)}, [(x0, y0)]
        while pila:
            px, py = pila.pop()
            for dx, dy in DIRS.values():
                n = (px + dx, py + dy)
                if 0 <= n[0] < w and 0 <= n[1] < h and n not in sala and n not in cerradas and not c[n[1] * w + n[0]][0] \
                        and c[n[1] * w + n[0]][2] in ("MB_NORMAL", "MB_THIN_ICE"):
                    sala.add(n)
                    pila.append(n)
        hielo = {p for p in sala if c[p[1] * w + p[0]][2] == "MB_THIN_ICE"}
        if not hielo:
            continue
        ex, ey = escalera

        def vecinas(p, pisado):
            for d, (dx, dy) in DIRS.items():
                n = (p[0] + dx, p[1] + dy)
                if n in sala and n not in pisado:
                    yield d, n

        def llega_a_escalera(p, pisado):
            # por suelo normal o hielo sin pisar no hace falta: al final solo queda suelo normal y hielo pisado
            vis, pila_ = {p}, [p]
            while pila_:
                q = pila_.pop()
                if abs(q[0] - ex) + abs(q[1] - ey) == 1:
                    return True
                for _, n in vecinas(q, pisado):
                    if n not in vis and n not in hielo:
                        vis.add(n)
                        pila_.append(n)
            return False

        camino = []
        mejor = [None]
        visit_norm = {}

        def dfs(p, pisado, resto):
            if mejor[0]:
                return
            if not resto:
                if llega_a_escalera(p, pisado):
                    mejor[0] = list(camino)
                return
            # poda: todo el hielo que queda tiene que seguir siendo alcanzable
            vis, pila_ = {p}, [p]
            while pila_:
                q = pila_.pop()
                for _, n in vecinas(q, pisado):
                    if n not in vis:
                        vis.add(n)
                        pila_.append(n)
            if not resto <= vis:
                return
            k = (p, frozenset(resto))
            if visit_norm.get(k):
                return
            visit_norm[k] = True
            opciones = list(vecinas(p, pisado))
            # primero el hielo con menos salidas (Warnsdorff)
            opciones.sort(key=lambda dn: (dn[1] not in hielo, sum(1 for _ in vecinas(dn[1], pisado))))
            for d, n in opciones:
                camino.append(d)
                if n in hielo:
                    dfs(n, pisado | {n}, resto - {n})
                else:
                    dfs(n, pisado, resto)
                camino.pop()
                if mejor[0]:
                    return

        dfs((x0, y0), frozenset(), frozenset(hielo))
        if not mejor[0]:
            raise RuntimeError(f"gimnasio de Arrecípolis: no encuentro recorrido para la sala de {escalera}")
        e.apunta(f"  hielo de Arrecípolis: {len(hielo)} casillas en {len(mejor[0])} pasos")
        for d in mejor[0]:
            antes = e.pos()
            e.paso(d, correr=False)
            if e.en_combate() or not e.controlable():
                seguir(e)
            if e.mapa() != G:
                raise RuntimeError("gimnasio de Arrecípolis: me he caído al sótano")
        for _ in range(40):          # la escalera se abre con una pausa
            e.avanzar(10)
            if e.controlable():
                break
        seguir(e)
        refrescar_mapa(e)
        w, h, c = mundo().rejilla(G)
        e.apunta(f"    escalera {escalera}: {c[ey * w + ex]} / {c[siguiente[1] * w + siguiente[0]]}")
        r = ir_a(e, (G,) + siguiente)
        if e.mapa() != G or e.pos() != siguiente:
            raise RuntimeError(f"gimnasio de Arrecípolis: no subo por la escalera {escalera} ({r})")
        seguir(e)
    hablar_con(e, G, 8, 2)
    seguir(e)


def empezar_partida(e, nombre="Claude"):
    """Desde la ROM recién encendida (sin partida guardada): intro, NUEVA PARTIDA, chico, nombre y
    hasta tener el control dentro del camión."""
    for _ in range(600):
        if "Naming" in e.cb2():
            break
        e.pulsar("a", despues=20)
    else:
        raise RuntimeError("empezar_partida: no sale la pantalla del nombre")
    e.avanzar(120)
    teclear(e, nombre)
    for _ in range(600):
        if e.cb2() == "CB2_Overworld" and e.controlable():
            return
        e.pulsar("a", despues=20)
    raise RuntimeError("empezar_partida: no llego a tener el control")
