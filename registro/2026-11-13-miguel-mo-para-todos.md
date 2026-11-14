# 13/11/2026 — Miguel: MO olvidables siempre y para todas las especies

## Qué se pidió

Que las MO se puedan olvidar siempre y que las aprendan todos los Pokémon.

## Qué se ha hecho

- **Olvidar MO: ya estaba.** `P_CAN_FORGET_HIDDEN_MOVE` vale `TRUE` (`include/config/pokemon.h`), así que `CannotForgetMove` nunca bloquea. Se comprobaron los sitios donde se olvida un movimiento, y en ninguno hay otro bloqueo:
  - en combate, al aprender uno nuevo;
  - al evolucionar;
  - en la pantalla de datos;
  - con el OLVIDAMOVIMIENTOS de Calagua (`IsLastMonThatKnowsSurf` también usa la opción).
- **Aprender MO: nuevo.** `CanLearnTeachableMove` (`src/pokemon.c`) dice que sí a cualquier MO (`IsMoveHM`) para todas las especies, menos los huevos.
  - Va antes de la compatibilidad al azar de las MT, así que no toca el randomizer: con la misma semilla, la partida sigue igual y las ROMs se pueden rehacer sin empezar de nuevo.
- **Tests nuevos** en `test/dualocke.c`:
  - Magikarp, Caterpie y Ditto aprenden Vuelo, Surf, Fuerza y Cascada, y un huevo no;
  - Surf y Buceo se pueden olvidar.
- **Documentación:** `DUALOCKE.md` (secciones 7 y 10) y la guía (Novedades).

## Cómo se comprobó

- Revisado a mano: `IsMoveHM` está declarado en `pokemon.h`, y los otros usos de `CanLearnTeachableMove` (guardería, IA, Pirámide, aprendiz) solo ganan las MO.
- **Sin compilar:** en el PC de Miguel no hay WSL.

## Pendiente

- Jorge: `make check` (los dos tests nuevos) y probar en el juego a enseñar una MO a un Pokémon que antes no podía.
