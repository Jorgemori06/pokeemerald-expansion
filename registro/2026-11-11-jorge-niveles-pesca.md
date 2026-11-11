# 11/11/2026 — Jorge: niveles de la pesca

## Qué se pidió

Jugando la versión 5, Jorge pescó en PUEBLO AZULIZA y le salió un Audino de nivel 44 (mandó una captura). Pidió revisar los niveles de las pescas.

## Causa

`reescalar_niveles.py` pone los salvajes de cada mapa según sus entrenadores. En las rutas del mar, los entrenadores son nadadores a los que llegas con SURF, así que la pesca quedaba a 42-48. Pero en algunas de esas zonas se puede pescar a pie mucho antes, con la CAÑA VIEJA (que te dan en AZULIZA):

- **RUTA 107:** la orilla este de la isla de AZULIZA pertenece a la RUTA 107. Ahí salió el Audino.
- **CIUDAD PETALIA:** el estanque de la ciudad.
- **RUTA 118:** la orilla oeste, nada más salir de MALVALONA.

## Qué se ha hecho

- Nueva tabla `PESCA_COMO` en `reescalar_niveles.py`: esos mapas pescan al nivel de la pesca de otro mapa del tramo en el que llegas andando.
  - RUTA 107 y CIUDAD PETALIA, como AZULIZA: de 44-48 y 42-46 a **15-19**.
  - RUTA 118, como la RUTA 110: de 42-46 a **17-21**.
- Se han relanzado `reescalar_niveles.py`, `equipos_jefes.py` y `evolucionar_entrenadores.py`. Solo cambian esas tres pescas; ningún entrenador cambia.
- Se han revisado las demás pescas comparándolas con la hierba del mismo mapa. Las que pasan de 5 niveles por encima o se alcanzan cuando el cap ya lo permite (RUTA 103 a 8-12, CATARATAS METEORO a 32-36), o son de Kanto.
- `DUALOCKE.md`, sección 5.

## Con la semilla de Jorge (2780853751)

- Cambian solo esas tres pescas, que ahora traen formas sin evolucionar por el nivel: Audino y Munna en la RUTA 107, Teddiursa y Geodude en la 118, Rattata en PETALIA.
- Cambia también lo que pide a cambio el intercambio de SEEDOT: Sliggoo en vez de Slowbro.
- Los entrenadores, los demás salvajes y los iniciales salen igual. La partida sigue valiendo.

## Cómo se comprobó

- `make` compila sin avisos.
- Comparación del randomizer con la semilla de Jorge, antes y después.
