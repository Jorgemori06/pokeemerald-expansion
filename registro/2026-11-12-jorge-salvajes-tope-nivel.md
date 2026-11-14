# 12/11/2026 — Jorge: ningún salvaje por encima del level cap

## Qué se pidió

"Se supone que no puedes conseguir POKéMON por encima del level cap. No puede volver a pasar que, si capturas en una ruta donde hay entrenadores con POKéMON de nivel alto, salgan por encima del level cap." Pasó con el Audino de nivel 44 de la pesca junto a AZULIZA, arreglado en las tablas en el #61.

## Qué se ha hecho

- `Dualocke_CapWildMon` (`src/dualocke.c`) es una red de seguridad en el juego, para que no dependa solo de que las tablas estén bien.
  - Si un salvaje sale por encima de `GetCurrentLevelCap()`, su nivel queda entre el cap y 2 niveles menos, al azar.
  - Vuelve a la etapa que le toca para ese nivel (`Dualocke_SpeciesForWildLevel`), con las mismas reglas que el randomizer: por nivel si evoluciona por nivel; si es por piedra o sin nivel, 30 la primera evolución y 40 la segunda. Por ejemplo, un Pidgeot de nivel 44 con cap 23 sale como Pidgeotto de nivel 21-23.
- Se llama desde `CreateWildMon` (hierba, agua, pesca, golpe roca, DEXNAV y brotes masivos) y desde `CreateScriptedWildMon` y su versión doble (los estáticos de los scripts).
- No afecta a los regalos ni a los intercambios.
- 3 tests en `test/dualocke.c`: la etapa según el nivel, el recorte al cap y que no cambia si está por debajo. Usan `Dualocke_CapWildMonTo` con un cap fijo, porque en los tests no hay cap.
- `DUALOCKE.md`, sección 5.

## Cómo se comprobó

- `make` compila sin avisos.
- `make check TESTS="Dualocke"`: 43/43.
- No se ha probado en el emulador.

## Con las partidas empezadas

No cambia el randomizer ni lo que se guarda, así que vale con la misma semilla.
