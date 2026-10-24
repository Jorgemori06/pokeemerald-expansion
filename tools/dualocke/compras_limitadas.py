#!/usr/bin/env python3
"""
Dualocke: genera la tabla de compras limitadas (una unidad de cada objeto por tienda).

Uso (desde la raíz del repo), cada vez que cambien las listas de las tiendas:
    python3 tools/dualocke/compras_limitadas.py

Lee las listas `pokemart` de los mapas de Hoenn y escribe src/data/dualocke_compras.h con
cada pareja (mapa de la tienda, objeto) que solo se puede comprar una vez. Las Balls, los
Repelentes, las Bayas, los Caramelos Raros y la Cuerda Huida se pueden comprar sin límite.
Cada pareja ocupa un bit de las variables VAR_DUALOCKE_COMPRAS_* (include/constants/vars.h).
"""

import glob
import json
import os
import re

SALIDA = "src/data/dualocke_compras.h"
EXENTOS = re.compile(r"_BALL$|REPEL$|^RARE_CANDY$|_BERRY$|^ESCAPE_ROPE$")


def main():
    parejas = []
    for script in sorted(glob.glob("data/maps/*/scripts.inc")):
        carpeta = os.path.dirname(script)
        if "Frlg" in carpeta:
            continue
        with open(script, encoding="utf-8") as f:
            texto = f.read()
        etiquetas = sorted(set(re.findall(r"pokemart\s+(\w+)", texto)))
        if not etiquetas:
            continue
        with open(os.path.join(carpeta, "map.json"), encoding="utf-8") as f:
            mapa = json.load(f)["id"]
        objetos = []
        for etiqueta in etiquetas:
            lista = re.search(re.escape(etiqueta) + r":+[ \t]*\r?\n(.*?)pokemartlistend", texto, re.S)
            for objeto in re.findall(r"ITEM_(\w+)", lista.group(1)):
                if not EXENTOS.search(objeto) and objeto not in objetos:
                    objetos.append(objeto)
        parejas += [(mapa, objeto) for objeto in objetos]

    lineas = [
        "// Generado por tools/dualocke/compras_limitadas.py: no editar a mano.",
        "// Parejas (tienda, objeto) que solo se pueden comprar una vez. El índice es el bit",
        "// que la guarda en las variables VAR_DUALOCKE_COMPRAS_*.",
        "",
        "static const struct DualockeCompraLimitada sComprasLimitadas[] =",
        "{",
    ]
    lineas += [f"    {{{mapa}, ITEM_{objeto}}}," for mapa, objeto in parejas]
    lineas += ["};", ""]
    with open(SALIDA, "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(lineas))
    print(f"{len(parejas)} compras limitadas en {len({m for m, _ in parejas})} tiendas -> {SALIDA}")


if __name__ == "__main__":
    main()
