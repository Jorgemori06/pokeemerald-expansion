"""python3 preparar.py [--rom ruta.gba]

Prepara la carpeta de la partida del bot (DUALOCKE_PARTIDA, por defecto partida_bot/ en la raíz del
repo, que no se sube): copia la ROM y su .elf (por defecto pokeemerald.gba de la raíz, compilada con
`make release SEED=...`) y genera datos.json (movimientos) y offsets.json (structs) a partir del
código, para que el bot siga valiendo aunque cambien los movimientos o los structs."""
import json
import os
import re
import shutil
import subprocess
import sys

AQUI = os.path.dirname(os.path.abspath(__file__))
RAIZ = os.path.abspath(os.path.join(AQUI, "..", "..", ".."))
PARTIDA = os.environ.get("DUALOCKE_PARTIDA", os.path.join(RAIZ, "partida_bot"))
FLAGS = ["-iquote", "include", "-Wno-trigraphs", "-DMODERN=1", "-DTESTING=0", "-DEMERALD", "-DRELEASE", "-std=gnu17"]


def offsets():
    s = subprocess.run(["arm-none-eabi-gcc", "-S", "-O0", *FLAGS, "-mthumb", "-mabi=apcs-gnu", "-march=armv4t",
                        os.path.join(AQUI, "offsets.c"), "-o", "-"], cwd=RAIZ, capture_output=True, text=True, check=True).stdout
    return {m.group(1): int(m.group(2)) for m in re.finditer(r"^(\w+):\n\s*\.word\s+(\d+)", s, re.M)}


def cev(x):
    """Evalúa a lo bruto las expresiones de moves_info.h (B_UPDATED_MOVE_DATA >= GEN_6 ? 90 : 95...)."""
    if x is None:
        return 0
    x = x.strip()
    m = re.match(r"(.+?)\?(.+):(.+)$", x)
    if m:
        cond = m.group(1).replace("&&", " and ").replace("||", " or ")
        try:
            return cev(m.group(2) if eval(cond) else m.group(3))
        except Exception:
            return cev(m.group(2))
    try:
        return int(eval(x))
    except Exception:
        return 0


def elegir(x):
    """De "8 >= 1 ? TYPE_FIGHTING : TYPE_NORMAL" se queda con la rama que toca."""
    if x is None:
        return None
    m = re.match(r"(.+?)\?(.+):(.+)$", x.strip())
    if not m:
        return x.strip()
    try:
        return elegir(m.group(2) if eval(m.group(1).replace("&&", " and ").replace("||", " or ")) else m.group(3))
    except Exception:
        return elegir(m.group(2))


def datos():
    s = subprocess.run(["arm-none-eabi-gcc", "-E", *FLAGS, "-include", "global.h", "-include", "dualocke_es.h", "-x", "c", "src/data/moves_info.h"],
                       cwd=RAIZ, capture_output=True, text=True, check=True).stdout
    mv = open(os.path.join(RAIZ, "include/constants/moves.h")).read()
    cuerpo = mv[mv.find("enum __attribute__((packed)) Move"):]
    cuerpo = cuerpo[cuerpo.find("{") + 1:cuerpo.find("};")]
    ids, cur = {}, -1
    for linea in cuerpo.split("\n"):
        linea = linea.split("//")[0].strip().rstrip(",")
        m = re.match(r"(\w+)\s*=\s*(\w+)$", linea)
        if m:
            v = m.group(2)
            if v.isdigit():
                cur = int(v)
                ids[m.group(1)] = cur
            elif v in ids:
                ids[m.group(1)] = ids[v]
            continue
        if re.match(r"\w+$", linea):
            cur += 1
            ids[linea] = cur
    tp = open(os.path.join(RAIZ, "include/constants/pokemon.h")).read()
    tb = tp[re.search(r"enum\s+(?:__attribute__\(\(packed\)\)\s+)?Type\s*\{", tp).start():]
    tb = tb[tb.find("{") + 1:tb.find("};")]
    tipos, c = {}, -1
    for linea in tb.split("\n"):
        linea = linea.split("//")[0].strip().rstrip(",")
        m = re.match(r"(TYPE_\w+)\s*(?:=\s*(\d+))?$", linea)
        if m:
            c = int(m.group(2)) if m.group(2) else c + 1
            tipos[m.group(1)] = c
    moves = {}
    inicios = list(re.finditer(r"\n    \[(MOVE_\w+)\]\s*=\s*\{", s))
    for i, m in enumerate(inicios):
        b = s[m.end():inicios[i + 1].start() if i + 1 < len(inicios) else len(s)]

        def g(k):
            x = re.search(r"\." + k + r"\s*=\s*([^,\n]+),", b)
            return x.group(1).strip() if x else None
        nombre = re.search(r'\.name\s*=\s*COMPOUND_STRING\("([^"]*)"\)', b)
        if m.group(1) not in ids:
            continue
        moves[ids[m.group(1)]] = {
            "id": m.group(1), "nombre": nombre.group(1) if nombre else m.group(1), "power": cev(g("power")),
            "type": tipos.get(elegir(g("type")), 0), "tipo": elegir(g("type")), "acc": cev(g("accuracy")), "cat": g("category"),
            "effect": g("effect"), "pp": cev(g("pp")), "priority": cev(g("priority")), "target": g("target"),
            "golpes": cev(g("strikeCount")) or 1}
    return {"moves": moves, "tipos": tipos, "ids": ids}


if __name__ == "__main__":
    os.makedirs(PARTIDA, exist_ok=True)
    rom = sys.argv[sys.argv.index("--rom") + 1] if "--rom" in sys.argv else os.path.join(RAIZ, "pokeemerald.gba")
    if os.path.exists(rom):
        shutil.copy(rom, os.path.join(PARTIDA, "partida.gba"))
        shutil.copy(rom[:-4] + ".elf", os.path.join(PARTIDA, "partida.elf"))
        print("ROM:", rom, "->", PARTIDA)
    else:
        print("AVISO: no encuentro la ROM", rom, "(compílala con make release SEED=...)")
    o = offsets()
    json.dump(o, open(os.path.join(PARTIDA, "offsets.json"), "w"), indent=1)
    d = datos()
    json.dump(d, open(os.path.join(PARTIDA, "datos.json"), "w"))
    print(len(o), "desplazamientos,", len(d["moves"]), "movimientos")
