# 01/11/2026 — Jorge: niveles de la Ruta 103

## Qué se pidió

Jugando, Jorge vio que en la Ruta 103 los salvajes salían a nivel 9-11 al principio del juego, con el inicial a 5 y la rival a 7. Pidió a Claude que lo arreglara él, aunque los niveles son de Miguel, con un PR para que lo revise.

## Causa

`tools/dualocke/reescalar_niveles.py` pone los salvajes de cada mapa 3 niveles por debajo de sus entrenadores normales. La Ruta 103 entera está en el tramo 1. Pero sus 8 entrenadores (Daisy, Amy y Liv, Andrés, Miguel, Marcos, Rhett, Pete e Isabel) están en la parte este, a la que solo se llega desde la Ruta 110 (tramo 3). En el Esmeralda original eran de 14-15, así que quedaban a 12-13 y arrastraban la hierba a 9-11.

## Qué se ha hecho

- Nueva tabla `TRAMO_ENTRENADORES_DE_MAPA = {"MAP_ROUTE103": 3}` en `reescalar_niveles.py`:
  - Los entrenadores normales de ese mapa se reescalan con el rango del tramo 3. Quedan a 20-22.
  - No cuentan para el nivel de los salvajes ni de los estáticos de su mapa.
  - Las bandas de los tramos se calculan como antes, así que no se mueve ningún otro entrenador.
- Se han relanzado en orden los tres scripts: `reescalar_niveles.py`, `equipos_jefes.py` y `evolucionar_entrenadores.py`.
- Resultado:
  - **Hierba de la Ruta 103:** de 9-11 a 2-3. Surf y pesca no cambian (8-12).
  - **Entrenadores de la Ruta 103:** de 12-13 a 20-22, y evolucionan según su nivel (por ejemplo, Magikarp pasa a Gyarados). En la partida sus especies las cambia el randomizer.
  - **Revanchas de Miguel y de Amy y Liv:** suben 2-4 niveles, porque van en proporción a su primer combate. Siguen dentro de los límites de su escalón.
- Antes del cambio, el script era idempotente: relanzarlo sobre `master` no daba ninguna diferencia.
- `DUALOCKE.md`, sección 5.

## Cómo se comprobó

- `make` compila sin avisos.
- `make release SEED=5966102869`: la Ruta 103 sale a 2-3 en el `wild_encounters.json` de la partida.

## Pendiente

- Que Miguel lo revise, porque los niveles son cosa suya.
- Va en las ROMs nuevas junto con el #54, porque en las dos hay que empezar partida nueva.
