# 11/11/2026 — Jorge: diálogos sueltos que quedaban en inglés

## Qué se pidió

Jugando la versión 5, Jorge encontró textos en inglés en PUEBLO AZULIZA: en el SALÓN AZULIZA (la casa de la palabra de moda, mandó una captura) y fuera.

## Qué se ha hecho

- Se han buscado todos los textos de los mapas de Hoenn que siguen en inglés. Se detectan por palabras en inglés y por no llevar tildes, ¿ ni ¡; quedan fuera el postgame y Kanto.
- Se han traducido los 125 que se ven durante la historia, en `traduccion/dialogos/56_sueltos.tsv`, y se han aplicado con `dialogos.py aplicar` (0 errores):
  - SALÓN AZULIZA: los vecinos que hablan de la palabra de moda y el que regala BOMBA LODO;
  - CLUB DE FANS de CALAGUA;
  - casa de LOTAD y SEEDOT de ARRECÍPOLIS;
  - TORRE ESPEJISMO (los fósiles);
  - KECLEON de la RUTA 120 (DETECTOR DEVON);
  - cartel del MONTE ENTRENADOR en la RUTA 111;
  - CUEVA CARDUMEN (CASCABEL CONCHA);
  - POKéMON que te sigue;
  - DEXNAV;
  - revanchas de AMY y LIV y de MIGUEL en la RUTA 103;
  - mensajes del BUSCAPELEA;
  - casas de los combates de visita de ALGARIA y ARRECÍPOLIS;
  - tíos y padres de BLASCO.
- Fila nueva en `traduccion/dialogos/LEEME.md` y nota en `DUALOCKE.md`, sección 8.

## Lo que sigue en inglés

- **Palabras del chat fácil** (`src/data/easy_chat/`, unas 1000). Es lo de "fuera" que vio Jorge en AZULIZA: la palabra de moda sale en inglés ("EXPENSIVE MESSAGE"), y también en los perfiles, el cuestionario y el correo. Traducirlas también obliga a rehacer el orden alfabético del modo ABC (`easy_chat_words_by_letter.h`).
- **La tele** (`data/text/tv.inc`, ~350) y **el hombre de MALVALONA** (`mauville_man`, ~80). En el reparto eran de Miguel.
- El postgame: revanchas de los líderes, FRENTE BATALLA, POKéDEX NACIONAL.

## Cómo se comprobó

- `python3 tools/dualocke/dialogos.py comprobar`: 0 errores (ancho de línea y códigos).
- `make` compila sin avisos.
- No se ha visto en el emulador.
