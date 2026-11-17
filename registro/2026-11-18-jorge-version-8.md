# 18/11/2026 — Jorge: versión 8 (semillas nuevas)

## Qué se pidió

Jorge: fusionar todo y sacar las dos ROM nuevas para empezar a jugar. Si lo suyo pendiente tardaba más de 40 minutos, solo fusionar y las ROM. Tardaba más (los nombres largos y los tests completos), así que se ha hecho solo eso. Se empieza el locke de cero con semillas nuevas.

## Qué se ha hecho

- **Fusionados en `master`:** #99 (todo lo de Miguel hasta el #98), #100 (paso a las islas y `PLAN.md`), #101 (idea 11), #97, #76 y #77.
- **Cerrados sin fusionar,** porque ya iban dentro del #99: del #82 al #98 y el #85. Del #78 al #81 GitHub los marcó como fusionados solos.
- **Comprobado en `master` (`9c897c01d`):**
  - `make` compila;
  - `make check TESTS="Dualocke"`: 60/60;
  - `alcance.py --comprobar`: 0;
  - `comprobar_zonas.py`: 0 fallos;
  - relanzar los cinco scripts de niveles y zonas en orden no cambia nada.
- **ROMs** (`make release`):
  - Jorge `2425682645`, md5 `e7d16beabbbce082914a6a535e5d1cae`;
  - Miguel `3632113266`, md5 `7340ed4779e8fb1776b4f83b7587be15`.
- `DUALOCKE.md`, sección 9: versión 8 y semillas.
- `IDEAS.md`: idea 12, el regalo de los amigos en los Centros Pokémon, con lo que decidió Jorge (nivel 1 y totalmente al azar).

## Pendiente

- **Probar en el emulador:** `PRUEBAS.md`. Nada de las zonas nuevas se ha jugado todavía.
- **Lo de Jorge que no ha entrado:**
  - nombres del jugador más largos (idea 8);
  - ampliar la lista de entrenadores para las zonas nuevas (los pone Miguel);
  - las revanchas con las mismas líneas que el primer combate;
  - el regalo de los amigos (idea 12).
  - Como el locke ya ha empezado con la versión 8, los nombres largos y la lista de entrenadores (cambian lo que se guarda) se quedan para la siguiente partida nueva, o hay que empezar otra vez.
- Los 7 biomas que quedan (`PLAN.md`, Miguel).
