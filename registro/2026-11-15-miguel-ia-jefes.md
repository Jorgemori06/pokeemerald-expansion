# 15/11/2026 — Miguel: IA de los jefes, estilos y entrenadores normales

## Qué se pidió

Del repaso general del 14/11/2026 quedó por decidir la IA de los combates. Miguel eligió empezar por ahí y decidió:

1. **Jefes de mitad de tramo** (rival, BLASCO, MAGNO, AQUILES, los admins y MÁXIMO en la Ruta 120): la IA lista de los líderes, **desde el gimnasio 3**. Antes de ERICO se quedan con la básica.
2. **Movimientos:** "que sean un poco random pero que tengan algo de estrategia; no todos los entrenadores tienen que llevar entry hazards. Uno que lleve Trampa Rocas, otro Trick Room, otro que juegue a chetarse… que cada jefe se sienta diferente sin perder la sensación del randomlocke. 2 movimientos de estrategia y 2 randoms".
3. **Entrenadores normales:** IA básica desde el gimnasio 4.
4. **Que la IA no haga trampa:** que no conozca tus movimientos, tu objeto ni tu habilidad sin haberlos visto.

## Qué se ha hecho

- **`tools/dualocke/aleatorio/estrategia.py`, reescrito con estilos:**
  - 8 estilos: trampas y arrastre, Espacio Raro, chetarse, clima, estados, pantallas, aguante y velocidad.
  - `estilo_de`: reparto al azar con la semilla, sin repetir dentro de cada grupo (los 8 líderes; el Alto Mando y Plubio; los jefes de mitad de tramo). Un personaje lleva el mismo estilo en todos sus combates (`personaje`).
  - `plan_de`: el estilo, cuántos movimientos de estrategia lleva cada Pokémon y el clima del jefe (el de su tipo, o uno al azar).
  - `elegir`: 2 de estrategia de su estilo, el mejor ataque de los que aprende por nivel y 1 al azar entre todos. Hasta el gimnasio 3: 1 de estrategia, 2 de nivel y 1 al azar. Siempre lleva un ataque, y nunca los de `NO_CONVIENEN`.
  - **Esto cambia lo de los líderes del 31/10/2026**: ya no pone trampas el primero de todos, y sus ataques ya no son todos de su nivel.
- **`tools/dualocke/aleatorio/entrenadores.py`:**
  - `con_estrategia` admite comodines (`_es_estratega`).
  - El rival lleva estilo e IA desde la Ruta 119 (`_rival`).
  - Los de equipo fijo (MÁXIMO en la Ruta 120) solo reciben la IA.
  - Los estilos de la partida van al solucionario (`estilos_de_los_jefes`).
- **`randomizer_config.json`:**
  - `con_estrategia` con los jefes nuevos: `TRAINER_MAXIE_*`, `TRAINER_ARCHIE`, `TRAINER_TABITHA_*`, `TRAINER_SHELLY_*`, `TRAINER_MATT`, el rival en la Ruta 119 y en Calagua, `TRAINER_WALLY_VR_1` y `TRAINER_STEVEN_ROUTE_120`.
  - `ia`: `Basic Trainer / Smart Switching / Smart Mon Choices / PP Stall Prevention / Randomize Switchin / Know Opponent Party / Hp Aware / Ace Pokemon`. Es `Smart Trainer` sin `Omniscient` (y sin `Smart Tera`, que no se usa).
- **`tools/dualocke/ia_entrenadores.py` (nuevo) y `src/data/trainers.party`:**
  - Los entrenadores que en el original llevaban `Check Bad Move` pasan a `Basic Trainer` desde el tramo 5 (después de CANDELA), con las revanchas: 462 entrenadores.
  - Los de los tramos 1 a 4 (169) se quedan igual.
  - Es el cuarto script, después de los tres de niveles y equipos. Se puede volver a lanzar.
- **Documentación:** `DUALOCKE.md` (secciones 5 y 7), la guía (Novedades) y `PRUEBAS.md`.

## Las partidas en curso

- **Especies:** no cambian. El reparto de especies de cada entrenador no depende de los movimientos.
- **Jefes con estrategia:** cambian sus movimientos y, con ellos, el objeto que les sale (depende de sus movimientos). Son los líderes, el Alto Mando, Plubio y los jefes de mitad de tramo desde el gimnasio 3.
- **El resto:** salvajes, entrenadores normales (salvo la IA), objetos, MT… salen igual.
- **Partida guardada:** sigue valiendo.

## Cómo se comprobó

- **Sin compilar:** no hay WSL en el PC de Miguel. Se probó el generador con una Pokédex de mentira (72 especies) y los movimientos de verdad de `moves_info.h`, con 60 semillas:
  - `comprobar()` de los entrenadores no da errores;
  - los estilos no se repiten dentro de cada grupo, y MAGNO lleva el mismo en todos sus combates;
  - todos los Pokémon de los jefes llevan 4 movimientos distintos, con al menos un ataque y ninguno de `NO_CONVIENEN`;
  - la IA es la nueva en los jefes con estrategia (con `Double Ace Pokemon` en VITO y LETI) y la de siempre en el rival de la Ruta 103, BLASCO en Malvalona y un entrenador normal;
  - MÁXIMO conserva su equipo y solo cambia la IA;
  - en 60 semillas, los 8 estilos salen por igual (entre 145 y 156 veces cada uno).
- **`ia_entrenadores.py`:** lanzado dos veces. La segunda no cambia nada. El diff de `trainers.party` son 462 líneas `AI:` y nada más.
- **Movimientos de los estilos:** todos existen en `include/constants/moves.h`.

## Pendiente

- **Claude de Jorge:**
  - `make check` y `make release SEED=...`. Lo que puede fallar al compilar son los nombres de la IA en `trainers.party` generado (`PP Stall Prevention`, `Randomize Switchin`, `Know Opponent Party`).
  - Comparar el solucionario con el de la versión 6: deberían cambiar solo los movimientos y objetos de los jefes con estrategia.
- **Probarlo jugando:** si los jefes usan bien su estilo (Espacio Raro, clima, pantallas) y si los entrenadores normales se notan demasiado después de CANDELA.
- **Del repaso general queda por decidir:** contenido nuevo en el mapa y qué ideas de `IDEAS.md` se hacen.
