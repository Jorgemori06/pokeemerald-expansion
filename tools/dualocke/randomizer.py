#!/usr/bin/env python3
"""
Dualocke: randomizer con semilla.

Lo lanza el Makefile al compilar con una semilla:

    make                        # partida randomizada con una semilla al azar, que se guarda en
                                # dualocke_semilla.txt (actualizar el juego no cambia la partida)
    make nueva-partida          # otra semilla al azar: partida nueva
    make SEED=loquesea          # una semilla concreta (misma semilla = misma partida)
    make SIN_RANDOM=1           # el juego sin randomizar (para probar); make check nunca randomiza

No toca ningún archivo del repo: lee los originales (los niveles y equipos de Miguel) y
escribe las versiones barajadas en build/dualocke/, que son las que se compilan.
Los parámetros están en tools/dualocke/randomizer_config.json (los decide Miguel).

Uso directo (normalmente no hace falta):
    python3 tools/dualocke/randomizer.py --semilla jorge123 --salida build/dualocke
"""

import argparse
import json
import os
import shlex
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from aleatorio import especies as esp  # noqa: E402
from aleatorio import salvajes  # noqa: E402

CONFIG = "tools/dualocke/randomizer_config.json"
WILD = "src/data/wild_encounters.json"


def main():
    p = argparse.ArgumentParser(description="Randomizer del dualocke")
    p.add_argument("--semilla", required=True)
    p.add_argument("--salida", default="build/dualocke")
    p.add_argument("--cpp", default="arm-none-eabi-cpp")
    p.add_argument("--cppflags", default=None, help="flags del preprocesador, como en el Makefile")
    args = p.parse_args()

    with open(CONFIG, encoding="utf-8") as f:
        config = json.load(f)
    cppflags = shlex.split(args.cppflags) if args.cppflags else None
    pokedex = esp.Pokedex(*esp.leer_especies(args.cpp, cppflags))

    os.makedirs(args.salida, exist_ok=True)
    solucionario = {"semilla": args.semilla}

    with open(WILD, encoding="utf-8") as f:
        texto = f.read()
    datos, original = json.loads(texto), json.loads(texto)
    solucionario["salvajes"] = salvajes.randomizar(datos, pokedex, args.semilla, config.get("salvajes", {}))
    errores = salvajes.comprobar(original, datos, pokedex)
    if errores:
        sys.exit("Dualocke: el randomizer de salvajes ha fallado:\n  " + "\n  ".join(errores[:20]))
    with open(os.path.join(args.salida, "wild_encounters.json"), "w", encoding="utf-8", newline="\n") as f:
        f.write(json.dumps(datos, indent=2, ensure_ascii=False) + "\n")

    # El solucionario es un destripe: está en build/ y no se sube al repo
    with open(os.path.join(args.salida, "solucionario.json"), "w", encoding="utf-8", newline="\n") as f:
        f.write(json.dumps(solucionario, indent=1, ensure_ascii=False) + "\n")
    print(f"Dualocke: partida randomizada con la semilla '{args.semilla}'.")


if __name__ == "__main__":
    main()
