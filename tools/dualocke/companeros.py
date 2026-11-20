#!/usr/bin/env python3
"""Dualocke: el equipo de MÁXIMO PEÑAS cuando lucha a tu lado (src/data/battle_partners.party).

En el CENTRO ESPACIAL de ARRECÍPOLIS se lucha en equipo con él contra MAXI y TATIANA (combate múltiple:
tú llevas 3 POKéMON y él otros 3). Los rivales los reescala `reescalar_niveles.py` (tramo 8, cap 84),
pero el equipo de Máximo Peñas no lo tocaba ningún script y se quedó con los niveles del juego
original (42-44): era un 2 contra 1 imposible. Miguel perdió el locke ahí (20/11/2026).

Ahora va al nivel del tramo, como MAXI: Metagross (Metang ya evolucionado), Skarmory y Aggron, con
ataques que en un combate doble no te dan a ti (sin Terremoto). El randomizer no lo cambia: es el mismo
con cualquier semilla. Se puede relanzar: siempre deja lo mismo.

    python3 tools/dualocke/companeros.py
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import reescalar_niveles as rn  # noqa: E402

ARCHIVO = "src/data/battle_partners.party"
NIVEL = rn.CAPS[8]  # el del tramo del CENTRO ESPACIAL, como MAXI

STEVEN = f"""=== PARTNER_STEVEN ===
Name: STEVEN
Class: Rival
Pic: Steven
Gender: Male
Music: Male
AI: Basic Trainer

Metagross @ Sitrus Berry
Adamant Nature
Level: {NIVEL}
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 6 SpD
- Meteor Mash
- Zen Headbutt
- Ice Punch
- Bullet Punch

Skarmory @ Sitrus Berry
Impish Nature
Level: {NIVEL}
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 6 Atk / 252 Def
- Brave Bird
- Iron Head
- Tailwind
- Roost

Aggron @ Sitrus Berry
Adamant Nature
Level: {NIVEL}
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 6 SpD
- Heavy Slam
- Stone Edge
- Superpower
- Protect
"""


def main():
    texto = open(ARCHIVO, encoding="utf-8").read()
    patron = re.compile(r"=== PARTNER_STEVEN ===\n.*?(?=\n=== |\Z)", re.S)
    if not patron.search(texto):
        sys.exit("Dualocke: no está PARTNER_STEVEN en " + ARCHIVO)
    nuevo = patron.sub(STEVEN.rstrip("\n"), texto, count=1)
    with open(ARCHIVO, "w", encoding="utf-8", newline="") as f:
        f.write(nuevo)
    print(f"MÁXIMO PEÑAS (compañero): Metagross, Skarmory y Aggron a nivel {NIVEL}.")


if __name__ == "__main__":
    main()
