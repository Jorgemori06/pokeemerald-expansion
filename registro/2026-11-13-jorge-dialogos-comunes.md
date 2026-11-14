# 13/11/2026 — Jorge: textos comunes que quedaban en inglés

## Qué se pidió

Jorge vio en el mercado de PORTUAL "Do you know the TM SECRET POWER?" en inglés (mandó una captura), y se quejó de que no para de encontrar textos sin traducir.

## Causa

Ese texto está en `data/event_scripts.s`, un archivo que `tools/dualocke/dialogos.py` no miraba, así que ni se exportaba ni salía en las búsquedas.

## Qué se ha hecho

- `dialogos.py` ahora también lee `data/event_scripts.s`.
- Se han buscado los textos en inglés en todos los archivos de `data/` que no son mapas, y se han traducido los comunes que se ven en Hoenn (`57_sueltos_comunes.tsv`, 47 textos):
  - `event_scripts.s`: MT DAÑO SECRETO, curación en el centro POKéMON, MAMÁ, POKÉRUS, tormenta de arena, SELECT, haber perdido el conocimiento…;
  - los carteles genéricos de las casas (`flavor_text.inc`);
  - el hombre del perfil de los centros POKéMON (`mystery_event_club.inc`);
  - lo que faltaba de la CUEVA CARDUMEN.
- Se han dejado fuera los textos de Kanto (OAK, guardería, intercambios FRLG), el postgame y los regalos misteriosos.
- `LEEME.md` y `DUALOCKE.md`, sección 8, con lo que queda.

## Lo que sigue en inglés y se ve durante la historia

- La tele (`data/text/tv.inc`, ~350 textos).
- El hombre de MALVALONA (`data/scripts/mauville_man.inc` y `data/text/mauville_man.inc`, ~80).
- Las TIENDAS BATALLA de PARDAL, VERDEGAL y PORTUAL (`data/text/battle_tent.inc`, ~56).

## Cómo se comprobó

- `dialogos.py comprobar`: 0 errores.
- `make` compila sin avisos.
