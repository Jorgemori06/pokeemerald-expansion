# 24/10/2026 · Miguel · Aviso al morir

Tarea de Jorge que adelanta Miguel (reservada en el PR #18). Rama `miguel/aviso-muerte`.

## Qué hace

Cuando se debilita un Pokémon del jugador en un combate en el que cuentan las vidas:
- en vez de "X fainted!" sale **"X has died! Lives left: N."**, con las vidas que quedarán al acabar el combate;
- si ya no quedan vidas, o se han debilitado todos (perder el combate), sale **"X has died! The locke is lost!"**.

## Cómo

- **Cuándo:** se avisa al debilitarse y no al acabar el combate. Así sale justo cuando pasa, en el combate, y no choca con el texto de los entrenadores después del combate. Las vidas se siguen restando al acabar el combate (`Dualocke_OnBattleEnd`, de Jorge); el aviso calcula cuántas quedarán contando los que hay debilitados.
- **`src/dualocke_aviso.c`** (nuevo) devuelve el texto. En `src/battle_message.c` (`BufferStringBattle`) se usa para `STRINGID_BATTLERFAINTED` solo si cuentan las vidas. Si no, sale el texto original.
- **Combates en los que cuenta:** los mismos que las vidas (`IsDualockeBattle` en `src/dualocke.c`, que ha dejado de ser `static`). Los Pokémon del compañero en los combates con compañero no cuentan.
- **Tests:** con `TESTING` se deja el texto original, porque cientos de tests de la expansion comprueban "X fainted!". Es el mismo criterio que con el level cap y Revivir.
- **Sin choques con el PR #17:** no toco `dualocke.h` ni el final de `dualocke.c`.

## Caso raro

- Si en el mismo combate se revive a un Pokémon con Revival Blessing (Jorge lo dejó permitido), el aviso habrá contado una muerte de más.

## Queda

- **Probar jugando:** que se debilite un Pokémon y salga el aviso con las vidas bien.
