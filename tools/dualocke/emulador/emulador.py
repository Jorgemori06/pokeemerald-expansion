#!/usr/bin/env python3
"""Dualocke: probar la ROM en un emulador sin pantalla, sin jugar.

Usa la ROM de pruebas (`make DUALOCKE_PRUEBA=1 [SEED=...]` -> pokeemerald-prueba.gba) y `gbarun`, un
programa pequeño en C sobre libmgba (`gbarun.c`, se compila solo la primera vez; hace falta
`apt install libmgba-dev`). La partida empieza directamente en el mapa y la casilla que se pida, con
las 8 medallas, las gafas, las bicis, la supercaña y un Lapras con MO (`src/dualocke_prueba.c`).

    from emulador import Emulador
    with Emulador() as emu:
        emu.empezar("MAP_ROUTE111", 33, 81)
        emu.andar("arriba", 2)
        print(emu.mapa(), emu.posicion())
        emu.foto("/tmp/foto.png")
"""
import json
import os
import re
import subprocess

RAIZ = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
AQUI = os.path.dirname(os.path.abspath(__file__))
TECLAS = {"a": 1, "b": 2, "select": 4, "start": 8, "derecha": 16, "izquierda": 32, "arriba": 64,
          "abajo": 128, "r": 256, "l": 512}
MAGIA = 0x50525545


def gbarun():
    binario = os.path.join(AQUI, "gbarun")
    fuente = os.path.join(AQUI, "gbarun.c")
    if not os.path.exists(binario) or os.path.getmtime(binario) < os.path.getmtime(fuente):
        subprocess.run(["gcc", "-O2", "-o", binario, fuente, "-lmgba"], check=True)
    return binario


def simbolos(mapa):
    """{nombre: dirección} de las variables globales del .map del enlazador."""
    texto = open(mapa, encoding="utf-8", errors="replace").read()
    return {m.group(2): int(m.group(1), 16) for m in re.finditer(r"^\s+0x([0-9a-f]{8})\s+(\w+)\s*$", texto, re.M)}


def codigo_de(mapa, objeto):
    """(inicio, fin) del código de src/<objeto>.c en el .map."""
    texto = open(mapa, encoding="utf-8", errors="replace").read()
    m = re.search(r"^ \.text\s+0x([0-9a-f]+)\s+0x([0-9a-f]+) (?:\S*/)?src/" + objeto + r"\.o$", texto, re.M)
    return int(m.group(1), 16), int(m.group(1), 16) + int(m.group(2), 16)


def mapas():
    """{MAP_X: (grupo, número)} según map_groups.json."""
    grupos = json.load(open(os.path.join(RAIZ, "data/maps/map_groups.json")))
    ids = {}
    for g, nombre in enumerate(grupos["group_order"]):
        for n, carpeta in enumerate(grupos[nombre]):
            ids[json.load(open(os.path.join(RAIZ, "data/maps", carpeta, "map.json")))["id"]] = (g, n)
    return ids


class Emulador:
    def __init__(self, rom=None):
        rom = rom or os.path.join(RAIZ, "pokeemerald-prueba.gba")
        self.sim = simbolos(rom[:-4] + ".map")
        self.menu = codigo_de(rom[:-4] + ".map", "main_menu")
        self.combate = codigo_de(rom[:-4] + ".map", "battle_main")
        self.motes = codigo_de(rom[:-4] + ".map", "naming_screen")
        nm = subprocess.run(["arm-none-eabi-nm", rom[:-4] + ".elf"], capture_output=True, text=True).stdout
        self.elegir_accion = {int(l.split()[0], 16) | 1 for l in nm.splitlines() if l.endswith(" HandleInputChooseAction")}
        self.ids = mapas()
        self.nombres = {v: k for k, v in self.ids.items()}
        self.proc = subprocess.Popen([gbarun(), rom], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)

    def __enter__(self):
        return self

    def __exit__(self, *a):
        self.proc.stdin.close()
        self.proc.wait()

    def orden(self, texto):
        self.proc.stdin.write(texto + "\n")
        self.proc.stdin.flush()
        return self.proc.stdout.readline().strip()

    def avanzar(self, fotogramas):
        self.orden(f"run {fotogramas}")

    def pulsar(self, *teclas, fotogramas=8, despues=8):
        self.orden(f"keys {sum(TECLAS[t] for t in teclas)}")
        self.avanzar(fotogramas)
        self.orden("keys 0")
        self.avanzar(despues)

    def leer(self, direccion, tam=8):
        return int(self.orden(f"r{tam} {direccion}"))

    def escribir(self, direccion, valor, tam=8):
        self.orden(f"w{tam} {direccion} {valor}")

    def foto(self, ruta, escala=2):
        from PIL import Image
        self.orden(f"shot {ruta}.ppm")
        Image.open(ruta + ".ppm").resize((240 * escala, 160 * escala), Image.NEAREST).save(ruta)
        os.remove(ruta + ".ppm")

    def guardar_estado(self, ruta):
        self.orden(f"save {ruta}")

    def cargar_estado(self, ruta):
        self.orden(f"load {ruta}")

    def empezar(self, mapa, x, y, especie=0, nivel=0, sin_equipo=False, foto=False):
        """Nueva partida directamente en (x, y) de MAP_X."""
        g, n = self.ids[mapa]
        for _ in range(100):          # intro -> título -> menú principal
            if self.menu[0] <= self.leer(self.sim["gMain"] + 4, 32) < self.menu[1]:
                break
            self.pulsar("start", despues=30)
        else:
            raise RuntimeError("no llega al menú principal")
        self.avanzar(60)
        p = self.sim["gDualockePrueba"]
        self.escribir(p, MAGIA, 32)
        self.escribir(p + 4, (g << 8) | n, 16)
        self.escribir(p + 6, x & 0xFFFF, 16)
        self.escribir(p + 8, y & 0xFFFF, 16)
        self.escribir(p + 10, especie, 16)
        self.escribir(p + 12, nivel)
        self.escribir(p + 13, int(sin_equipo))
        self.escribir(p + 14, int(foto))
        self.pulsar("a", despues=240)  # NUEVA PARTIDA
        if self.mapa() != mapa:
            raise RuntimeError(f"no ha empezado en {mapa}: está en {self.mapa()}")

    def en_combate(self):
        return self.combate[0] <= self.leer(self.sim["gMain"] + 4, 32) < self.combate[1]

    def en_mapa(self):
        return (self.leer(self.sim["gMain"] + 4, 32) | 1) == (self.sim["CB2_Overworld"] | 1)

    def esperar_accion(self, maximo=60):
        """En combate, pasa los textos (B) hasta que toca elegir LUCHA/MOCHILA/POKéMON/HUIR."""
        for _ in range(maximo):
            if (self.leer(self.sim["gBattlerControllerFuncs"], 32) | 1) in self.elegir_accion:
                return True
            if not self.en_combate():
                return False
            self.pulsar("b", despues=20)
        return False

    def accion(self, cual):
        """Elige en combate 0 LUCHA, 1 MOCHILA, 2 POKéMON o 3 HUIR."""
        self.esperar_accion()
        self.escribir(self.sim["gActionSelectionCursor"], cual)
        self.pulsar("a", despues=60)

    def en_motes(self):
        return self.motes[0] <= self.leer(self.sim["gMain"] + 4, 32) < self.motes[1]

    def capturar(self):
        """En un combate salvaje: lanza una Master Ball (MOCHILA, tercer bolsillo), pone el mote
        obligatorio y espera a volver al mapa."""
        self.accion(1)
        self.avanzar(40)
        self.pulsar("derecha", despues=30)
        self.pulsar("derecha", despues=30)
        self.pulsar("a", despues=40)
        self.pulsar("a", despues=300)
        for _ in range(80):
            if self.en_mapa():
                self.avanzar(60)
                return True
            if self.en_motes():
                self.avanzar(60)
                for _ in range(3):
                    self.pulsar("a", despues=15)
                self.pulsar("start", despues=20)
                self.pulsar("a", despues=120)
            else:
                self.pulsar("a", despues=40)
        return False

    def hablar(self, direccion, maximo=15):
        """Mira hacia `direccion` y pulsa A hasta que empieza un combate (True) o se acaban los intentos."""
        self.pulsar(direccion, fotogramas=3, despues=10)
        for _ in range(maximo):
            self.pulsar("a", despues=40)
            if self.en_combate():
                self.avanzar(300)
                return True
        return False

    def huir(self):
        """En un combate salvaje: HUIR (el cursor se pone en HUIR escribiendo en la memoria) y esperar a
        volver al mapa."""
        for _ in range(60):
            if self.en_mapa():
                self.avanzar(60)
                return True
            if self.en_combate():
                self.accion(3)
            else:
                self.pulsar("b", despues=40)
        return False

    def _sb1(self):
        return self.leer(self.sim["gSaveBlock1Ptr"], 32)

    def mapa(self):
        sb1 = self._sb1()
        return self.nombres.get((self.leer(sb1 + 4), self.leer(sb1 + 5)))

    def posicion(self):
        sb1 = self._sb1()
        return self.leer(sb1, 16), self.leer(sb1 + 2, 16)

    def andar(self, direccion, pasos=1):
        for _ in range(pasos):
            self.pulsar(direccion, fotogramas=16, despues=4)
        self.avanzar(30)
