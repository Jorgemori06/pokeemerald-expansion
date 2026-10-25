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
escribe las versiones barajadas en build/dualocke/ (wild_encounters.json, trainers.party,
dualocke_iniciales.h, dualocke_aleatorio.h), que son las que se compilan.
Los parámetros están en tools/dualocke/randomizer_config.json (los decide Miguel).

Uso directo (normalmente no hace falta):
    python3 tools/dualocke/randomizer.py --semilla jorge123 --salida build/dualocke
"""

import argparse
import hashlib
import json
import os
import shlex
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from aleatorio import cabecera  # noqa: E402
from aleatorio import especies as esp  # noqa: E402
from aleatorio import entrenadores  # noqa: E402
from aleatorio import estaticos  # noqa: E402
from aleatorio import habilidades as hab  # noqa: E402
from aleatorio import iniciales as ini  # noqa: E402
from aleatorio import intercambios  # noqa: E402
from aleatorio import movimientos as mov  # noqa: E402
from aleatorio import mts  # noqa: E402
from aleatorio import objetos as obj  # noqa: E402
from aleatorio import salvajes  # noqa: E402

CONFIG = "tools/dualocke/randomizer_config.json"
WILD = "src/data/wild_encounters.json"
TRAINERS = "src/data/trainers.party"


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
    movs = mov.leer_movimientos(args.cpp, cppflags)

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

    iniciales = ini.elegir(pokedex, args.semilla)
    solucionario["iniciales"] = iniciales
    with open(os.path.join(args.salida, "dualocke_iniciales.h"), "w", encoding="utf-8", newline="\n") as f:
        f.write(ini.cabecera(iniciales, f"Iniciales de la semilla {args.semilla}"))

    mapa_estaticos, mapa_regalos = estaticos.randomizar(pokedex, args.semilla)
    solucionario["estaticos"], solucionario["regalos"] = mapa_estaticos, mapa_regalos
    for especie in list(mapa_estaticos.values()) + list(mapa_regalos.values()):
        if especie not in pokedex.especies:
            sys.exit(f"Dualocke: el randomizer de estáticos ha dado una especie desconocida: {especie}")

    objetos = obj.leer_objetos(args.cpp, cppflags)
    res_objetos = obj.randomizar(objetos, args.semilla, config)
    errores = obj.comprobar(objetos, config, res_objetos)
    if errores:
        sys.exit("Dualocke: el randomizer de objetos ha fallado:\n  " + "\n  ".join(errores[:20]))
    solucionario["objetos"] = obj.solucionario(objetos, res_objetos)

    res_intercambios = intercambios.randomizar(pokedex, args.semilla, datos, obj.grupo_suelo(objetos, config))
    solucionario["intercambios"] = res_intercambios

    habilidades = hab.randomizar(pokedex, hab.leer_habilidades(args.cpp, cppflags), args.semilla, config)
    solucionario["habilidades"] = habilidades
    mapa_mts, compatibilidad = mts.randomizar(movs, args.semilla, config)
    solucionario["mt"] = {o: movs[m].nombre for o, m in mapa_mts.items()}
    tutores = mts.randomizar_tutores(movs, args.semilla, config, mapa_mts)
    solucionario["tutores"] = {movs[o].nombre: movs[n].nombre for o, n in tutores.items()}
    # Para la compatibilidad de las MT (la calcula el juego a partir de este número)
    numero = int(hashlib.sha256(args.semilla.encode()).hexdigest()[:8], 16)

    with open(os.path.join(args.salida, "dualocke_aleatorio.h"), "w", encoding="utf-8", newline="\n") as f:
        f.write(cabecera.generar(f"Semilla {args.semilla}", mapa_estaticos, mapa_regalos,
                                 res_objetos["suelo"], res_objetos["recogida"], res_objetos["salvajes"],
                                 res_objetos["probabilidad_salvajes"], res_intercambios, habilidades,
                                 mapa_mts, compatibilidad, numero, tutores))

    with open(TRAINERS, encoding="utf-8") as f:
        original = f.read()
    randomizado, solucionario["entrenadores"] = entrenadores.Generador(pokedex, args.semilla, config, iniciales,
                                                                            movs).randomizar(original)
    errores = entrenadores.comprobar(original, randomizado, pokedex)
    if errores:
        sys.exit("Dualocke: el randomizer de entrenadores ha fallado:\n  " + "\n  ".join(errores[:20]))
    with open(os.path.join(args.salida, "trainers.party"), "w", encoding="utf-8", newline="\n") as f:
        f.write(randomizado)

    # El solucionario es un destripe: está en build/ y no se sube al repo
    with open(os.path.join(args.salida, "solucionario.json"), "w", encoding="utf-8", newline="\n") as f:
        f.write(json.dumps(solucionario, indent=1, ensure_ascii=False) + "\n")
    print(f"Dualocke: partida randomizada con la semilla '{args.semilla}'.")


if __name__ == "__main__":
    main()
