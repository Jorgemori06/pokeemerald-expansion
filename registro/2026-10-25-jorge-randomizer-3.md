# 25/10/2026 · Jorge · Randomizer (3): objetos, intercambios, movimientos, habilidades, MT y tutores

Sesión de Jorge con Claude (tarde). Rama `jorge/randomizer-objetos`, desde master con el #17, #26, #27 y #28 ya fusionados. Antes, el #29 de Miguel (diálogos 11-28): compila y pasa `make check` (5449 en verde), así que se ha aprobado y fusionado. Última fase del randomizer, con las respuestas de Miguel a las preguntas del #27.

## Decisiones

**De Miguel (#27):**

- **Objetos del suelo:**
  - Las megapiedras se quedan donde están y ningún otro objeto del suelo puede ser una megapiedra.
  - Los competitivos son totalmente aleatorios.
  - Las MT se barajan entre ellas.
  - Fuera objetos clave, MO y cartas; las bayas sí pueden salir.
- **Recogida:** solo objetos de consumo.
- **Salvajes:** cualquiera puede llevar un objeto, con poca probabilidad.
- **Objetos de los jefes:** un objeto que le sirva a cada Pokémon, en todo el equipo. La megapiedra del as se queda.
- **Movimientos de los entrenadores:**
  - 3 de los que aprende por nivel y el cuarto al azar.
  - La preferencia por los potentes es igual para todos.
- **Habilidades:** por especie, y ninguna prohibida.
- **Estadísticas:** los totales **no** se barajan.
- **MT:**
  - Cada MT enseña un movimiento al azar, menos las de campo.
  - Compatibilidad del 50 % para todas.
- **Intercambios:** al azar el que te piden (sin legendarios) y el que te dan.
- **Tutores:** aleatorios. Se aprenden con la misma probabilidad que las MT.

**De Jorge (con Claude), pendientes de que Miguel las vea, porque son de equilibrio:**

- **Probabilidad de que un salvaje lleve objeto: 5 %** (el doble con Ojo Compuesto). Está en `salvajes.probabilidad_objeto`.
- **Tope de potencia del cuarto movimiento:** 40 + 1,5 por nivel. Si no, un entrenador de nivel 5 podría llevar Hidrobomba. Está en `potencia_maxima_del_cuarto` (`null` = sin tope).
- **Intercambios:** el Pokémon que te piden sale de entre los salvajes de la partida. Si fuera de cualquier especie, casi nunca se podría hacer el intercambio.
- **MT de campo y MO:** mantienen la compatibilidad original, para no quedarse sin poder avanzar.

## Cómo funciona

- **Módulos nuevos en `tools/dualocke/aleatorio/`:**
  - `objetos.py`: lee `gItemsInfo` de `src/item.c` con el preprocesador; los nombres salen en español para el solucionario.
  - `intercambios.py`
  - `movimientos.py`: lee `gMovesInfo` de `src/move.c`.
  - `habilidades.py`
  - `mts.py`
  - `cabecera.py`: escribe `src/data/dualocke_aleatorio.h` con todas las tablas.
  - `especies.py` lee además las estadísticas base, las habilidades y los movimientos por nivel.
- **Lo que no se puede barajar sin tocar mapas, scripts o datos se cambia al vuelo** en `src/dualocke_aleatorio.c`, con las tablas de la semilla (vacías sin semilla):
  - Objetos del suelo: por el flag de cada Poké Ball (`item_ball.c`) y de cada objeto oculto (`field_control_avatar.c`).
  - Recogida: `battle_script_commands.c`.
  - Objetos de los salvajes: `SetWildMonHeldItem` en `pokemon.c`.
  - Intercambios: `trade.c` usa una copia del intercambio con la especie, la que piden, el objeto y los IVs cambiados; el mote pasa a ser el nombre de la especie.
  - Habilidades: `GetSpeciesAbility` en `pokemon.c`, con la misma en todos los huecos.
  - MT:
    - qué enseña cada una: `include/item.h`, en `GetItemTMHMMoveId`, `GetTMHMMoveId` y `GetTMHMItemIdFromMoveId`;
    - quién la aprende: `CanLearnTeachableMove`, con un cálculo fijo a partir de la especie, el movimiento y la semilla;
    - `party_menu.c` usa `CanLearnTeachableMove` al cambiar de forma.
- **Tutores:**
  - La macro `move_tutor` llama a `Dualocke_TutorAleatorio`, que cambia el movimiento y pone su nombre en `{STR_VAR_1}`.
  - Los textos de los 10 tutores dicen el movimiento con `{STR_VAR_1}`. Están en `data/text/move_tutors.inc` y en el `.tsv` de Miguel, que pasa `dialogos.py comprobar` con 0 errores.
  - Los textos que describían el movimiento original se han dejado más generales (que si CORTE FURIA es "de tipo BICHO", que si SUSTITUTO "hace una copia"…).
- **Movimientos de los entrenadores:** van escritos en el `trainers.party` barajado (`- MOVE_X`).
- **Objetos coherentes de los jefes:** según estadísticas y movimientos:
  - Mineral Evolutivo si puede evolucionar;
  - Vidasfera, Cinta Experto, objetos Elección si todos sus movimientos son de daño;
  - potenciador del tipo de su mejor ataque;
  - Restos o Lodo Negro, Baya Zidra, Casco Dentado, Chaleco Asalto, Banda Aguante…
- **Comprobaciones** antes de escribir: objetos excluidos, megapiedras sin tocar y MT solo por MT. Si algo falla, para la compilación.
- `randomizer_config.json` recoge las respuestas de Miguel y los parámetros nuevos.

## Comprobado

- Compila randomizado y con `make SIN_RANDOM=1`.
- `make check` completo: ver el comentario del PR.
- Prueba temporal con semilla (no se sube): las habilidades cambian, las MT cambian, la compatibilidad ronda el 50 %, las MO no cambian y los intercambios y objetos de los salvajes están activos.

## Pendiente

- **Miguel:** echar un ojo a los textos de los tutores, que eran suyos.
- **Miguel:** revisar los valores provisionales (5 % de objeto en salvajes y tope del cuarto movimiento).
- **Los dos:** probarlo jugando.
