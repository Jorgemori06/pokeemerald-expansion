#!/usr/bin/env python3
"""
Dualocke: IA de los entrenadores normales.

Uso (desde la raíz del repo, el último de los cuatro):
    python3 tools/dualocke/reescalar_niveles.py
    python3 tools/dualocke/equipos_jefes.py
    python3 tools/dualocke/evolucionar_entrenadores.py
    python3 tools/dualocke/ia_entrenadores.py

En el original, casi todos los entrenadores de rutas y gimnasios llevan "Check Bad Move": solo
evitan los movimientos que fallan y eligen al azar entre los demás. Decidido por Miguel el
15/11/2026: hasta el gimnasio 4 (CANDELA) se quedan así, y desde entonces llevan "Basic Trainer"
(eligen un buen movimiento y rematan si pueden), como ya llevaban el rival y los jefes.

- Solo se toca a los que en la expansion original (commit BASE) llevaban "Check Bad Move", así
  que se puede volver a lanzar y cambiar TRAMO_BASICA sin miedo.
- El tramo de cada entrenador es el de su mapa (la tabla TRAMOS de reescalar_niveles.py).
- Las revanchas (_2 a _5) empiezan con 5 medallas: siempre básica.
- Los que no salen en ningún mapa (sin usar) se quedan como están.
- Los jefes con estrategia (líderes, Alto Mando, rival desde la Ruta 119...) llevan su IA aparte:
  la pone el randomizer ("lideres" en randomizer_config.json).
"""

import collections
import re
import sys

sys.path.insert(0, __file__.rsplit("/", 1)[0].rsplit("\\", 1)[0])
import reescalar_niveles as rn  # noqa: E402

IA_FLOJA = "Check Bad Move"
IA_BASICA = "Basic Trainer"
TRAMO_BASICA = 5  # desde este tramo (después del gimnasio 4), IA básica
TRAMO_REVANCHAS = 6  # las revanchas se activan con 5 medallas


def ia_por_entrenador(texto):
    partes = re.split(r"^=== (TRAINER_\w+) ===[ \t]*$", texto, flags=re.M)
    resultado = {}
    for i in range(1, len(partes), 2):
        m = re.search(r"^AI:[ \t]*(.*?)[ \t]*$", partes[i + 1], re.M)
        resultado[partes[i]] = m.group(1) if m else None
    return resultado


def tramo_de(nombre, mapas):
    if nombre in mapas:
        if rn.de_otro_tramo(nombre, mapas):
            return rn.TRAMO_ENTRENADORES_DE_MAPA[mapas[nombre]]
        return rn.tramo_de_mapa(mapas[nombre])
    if re.search(r"_[2-5]$", nombre):
        return TRAMO_REVANCHAS
    return None


def main():
    originales = ia_por_entrenador(rn.git_show(rn.TRAINERS))
    mapas = rn.mapas_de_entrenadores()
    with open(rn.TRAINERS, encoding="utf-8", newline="") as f:
        texto = f.read()
    partes = re.split(r"(^=== TRAINER_\w+ ===[ \t]*$)", texto, flags=re.M)
    cuenta = collections.Counter()
    cambiados = 0
    for i in range(1, len(partes), 2):
        nombre = re.match(r"=== (TRAINER_\w+) ===", partes[i]).group(1)
        if originales.get(nombre) != IA_FLOJA:
            continue
        tramo = tramo_de(nombre, mapas)
        if tramo is None:
            cuenta["sin mapa (no se tocan)"] += 1
            continue
        ia = IA_BASICA if tramo >= TRAMO_BASICA else IA_FLOJA
        cuenta[f"tramo {tramo:2d}: {ia}"] += 1
        nuevo = re.sub(r"^(AI:[ \t]*).*?([ \t]*)$", lambda m: m.group(1) + ia + m.group(2), partes[i + 1],
                       count=1, flags=re.M)
        if nuevo != partes[i + 1]:
            partes[i + 1] = nuevo
            cambiados += 1
    with open(rn.TRAINERS, "w", encoding="utf-8", newline="") as f:
        f.write("".join(partes))
    for clave in sorted(cuenta):
        print(f"{cuenta[clave]:4d}  {clave}")
    print(f"\n{cambiados} entrenadores cambiados.")


if __name__ == "__main__":
    main()
