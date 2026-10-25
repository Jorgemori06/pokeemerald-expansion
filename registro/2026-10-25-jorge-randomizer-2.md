# 25/10/2026 · Jorge · Randomizer (2): estáticos y regalos

Sesión de Jorge con Claude. Rama `jorge/randomizer-estaticos`, encima de `jorge/randomizer` (PR #27). PR #28, en borrador hasta que se fusione el #27.

## Decisiones de Jorge

- **Estáticos: todo al azar.** Son los combates con `setwildbattle` (Kecleon, Voltorb, Electrode, Sudowoodo, Regis, Groudon, Kyogre, Rayquaza…) y los errantes (Latios/Latias). Puede salir cualquier especie, legendarios incluidos.
- **Regalos: al azar, sin legendarios.** Son los `givemon` (Beldum, fósiles, Castform, iniciales de Johto…) y los huevos (`giveegg`: Wynaut, Pichu…).
- **El sprite del mapa da igual:** se sigue viendo el original y la especie de verdad se descubre al empezar el combate.

## Cómo funciona

- `tools/dualocke/aleatorio/estaticos.py` busca en los scripts de Hoenn (`data/maps/*/scripts.inc` y `data/scripts/*.inc`, sin FRLG ni depuración) los `setwildbattle`, `givemon` y `giveegg`, y añade los errantes de `src/roamer.c`.
- Cada especie original se cambia por **la misma especie nueva en todos sus sitios**: todos los Kecleon del Detector son, por ejemplo, el mismo Pokémon. Así la regla de Miguel de "solo el primero de cada tipo" se puede hacer agrupando por la especie original.
- La especie nueva se evoluciona según el nivel del encuentro, con las mismas reglas que los salvajes. Los huevos son siempre la forma base.
- No se repiten líneas entre estáticos y regalos.
- **No se toca ningún script.** El Makefile genera `src/data/dualocke_aleatorio.h` (vacío si no hay semilla, con `make SIN_RANDOM=1` o en `make check`), y `src/dualocke_aleatorio.c` cambia la especie al vuelo:
  - `ScrCmd_setwildbattle` y `ScrCmd_giveegg` (`src/scrcmd.c`);
  - `ScrCmd_createmon` del lado del jugador, que es lo que usa `givemon` (`src/script_pokemon_util.c`). También pone `VAR_TEMP_TRANSFERRED_SPECIES`, para que el texto del regalo diga la especie nueva;
  - `TryAddRoamer` (`src/roamer.c`).

## Comprobado

- Compila randomizado y con `make SIN_RANDOM=1`.
- `make check` completo: ver el comentario del PR #28.

## Pendiente

- **Miguel:**
  - la regla de "solo el primero de cada tipo" en los estáticos;
  - reescalar el nivel de los errantes (40 en `src/roamer.c`).
- **Jorge:** última fase del randomizer (movimientos, habilidades, objetos, MTs, intercambios), cuando Miguel decida sus parámetros.
