# 27/10/2026 — Miguel: respuestas sobre el bug del equipo clonado

## Qué se pidió

Ponerse al día con el repo y, siguiendo `BUG-EQUIPO-CLONADO.md` (PR #47 de Jorge), hacerle a Miguel las preguntas sobre la captura del Wiglett antes de tocar código.

## Qué se ha hecho

- **Puesta al día:** fusionados en `master` los #38, #39, #40 y #42. Abiertos:
  - #44 (guía actualizada por Jorge, sustituye al #43);
  - #45 (idea 8);
  - #46 (Pokédex en la guía);
  - #47 (arreglo de habilidades y documento del bug).
- **Respuestas de Miguel** apuntadas en `BUG-EQUIPO-CLONADO.md`:
  - equipo lleno, con el Charmander delante todo el combate;
  - Campo de Niebla y Canto Mortal activos al capturar, con una sola Ball;
  - ganó experiencia sin subir de nivel;
  - mote escrito una vez y **NO** a meterlo en el equipo;
  - el equipo clonado lo vio al salir del combate, y los otros 5 se han perdido;
  - versión 2 en mGBA, posiblemente con turbo;
  - antes capturó un Growlithe con el equipo lleno diciendo SÍ, y fue bien;
  - tiene la partida guardada de antes.
- **Análisis:**
  - No es el menú de "¿lo metes en el equipo?".
  - `caughtMonNick` y `battlerPartyOrders` van juntos en `struct BattleStruct`, y algo los borra entre la pantalla de mote y la vuelta al combate. Con el equipo lleno, esa vuelta pasa por `ReshowBlankBattleScreenAfterMenu`.
  - Eso explica a la vez el mote en blanco y los clones (`UpdatePartyToBattleOrder` con el orden a cero).
  - Diferencias con la captura que fue bien: el campo, el Canto Mortal, la habilidad de relleno y el NO.
- **Cómo reproducirlo:** se apunta el plan para hacerlo en el emulador, con un *watchpoint* de mGBA en esos campos.
- **Aviso en `DUALOCKE.md`:** cambiado para decir que las preguntas ya están respondidas.

## Cómo se comprobó

- Se ha leído el código de `Cmd_trygivecaughtmonnick`, `Cmd_givecaughtmon`, `ReshowBlankBattleScreenAfterMenu` y `struct BattleStruct`.
- No se ha reproducido: en el PC de Miguel no hay compilador ni depurador.

## Pendiente

- Jorge: reproducirlo con el plan del documento y encontrar la escritura con el *watchpoint*.
- Miguel, mientras tanto: no capturar con el equipo lleno, y no guardar si vuelve a pasar.
