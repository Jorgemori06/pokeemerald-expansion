# 13/11/2026 — Jorge: el muerto que se cambiaba por la captura se quedaba vivo

## Qué se pidió

Jorge, jugando: "si capturando un pokemon, te matan a uno del equipo, y a este lo cambias por el q está muerto al capturarlo, se queda vivo en la caja del pc".

## Por qué pasaba

Los muertos se entierran al acabar el combate (`Dualocke_OnBattleEnd`), mirando solo el equipo. Al capturar con el equipo lleno, la expansion deja mandar a la caja a uno del equipo (`Cmd_givecaughtmon`, `B_CATCH_SWAP_INTO_PARTY`), y eso pasa antes de acabar el combate. Si se elegía al debilitado, salía del equipo con `CopyMonToPC` y ya no se veía al enterrar. Como desde la generación 8 el PC no cura (`OW_PC_HEAL`), se quedaba en la caja con 0 PS, sin restar vida.

## Qué se ha hecho

- `Dualocke_TryBuryChosenPartyMon` (`src/dualocke.c`): si el elegido está debilitado en un combate que cuenta, va a la caja de muertos y resta una vida. El mensaje dice que se ha mandado a la caja "MUERTOS".
- `Dualocke_BuryFaintedBoxMonsOnce`: arreglo para las partidas empezadas. Al encender el PC por primera vez con esta versión, los de las cajas normales con 0 PS se entierran y restan su vida. Solo se hace una vez (`FLAG_DUALOCKE_CAJAS_REVISADAS`, el antiguo `FLAG_UNUSED_0x2B6`), porque en la Torre Entrenador sí se puede acabar con debilitados y no cuentan.
- Si el muerto ya se había curado en un Centro Pokémon no hay forma de saberlo: hay que liberarlo a mano.
- Nota en `DUALOCKE.md`, sección 9 (vidas y caja de muertos).

## Cómo se comprobó

- Tres tests nuevos en `test/dualocke.c`: el debilitado cambiado va a la caja de muertos y resta vida; uno con PS sigue yendo a una caja normal; el arreglo de las cajas entierra solo a los de 0 PS y solo una vez.
- `make` compila y `make check TESTS="Dualocke"` pasa 43/43.
