# 27/10/2026 — Miguel: arreglo defensivo del equipo clonado

## Qué se pidió

Miguel ha perdido la partida guardada y empieza de nuevo. Quiere una ROM sin los fallos del Wiglett: la habilidad "-------" y el equipo clonado al capturar con el equipo lleno (`BUG-EQUIPO-CLONADO.md`, #47 y #48).

## Qué se ha hecho

- **Habilidad:** la arregla el #47 de Jorge, revisado. Falta fusionarlo; se pidió permiso a Miguel.
- **Equipo clonado:** la causa exacta no se ha encontrado (no se puede reproducir sin emulador). Por eso se ha hecho un arreglo **defensivo**, que tapa los dos síntomas sea cual sea la escritura que los provoca:
  1. **Mote fuera de `gBattleStruct`** (`Cmd_trygivecaughtmonnick`, `src/battle_script_commands.c`):
     - el mote se escribe en un búfer propio (`sDualockeMote`);
     - `battlerPartyOrders`, `battlerPartyIndexes` y `monToSwitchIntoId` se guardan antes de la pantalla de mote y se reponen al volver;
     - si el mote vuelve vacío, se vuelve a pedir, igual que cuando se deja el nombre de la especie.
  2. **Orden del equipo comprobado** (`Dualocke_ArreglarOrdenEquipo`, `src/party_menu.c`):
     - antes de reordenar el equipo en combate (`UpdatePartyToBattleOrder` y `UpdatePartyToFieldOrder`) se comprueba que el orden sea una permutación de 0-5;
     - si no lo es (por ejemplo, a ceros), se rehace con `BufferBattlePartyCurrentOrder` en vez de copiar el primer Pokémon en los 6 huecos;
     - en los combates múltiples no se toca.

## Cómo se comprobó

- **Sin compilar:** en el PC de Miguel no hay compilador. Se ha revisado el código a mano: tipos, cabeceras (`IsMultiBattle` y `BufferBattlePartyCurrentOrder` están en `party_menu.h`) y que `EWRAM_DATA` estático se usa así en otros archivos.
- **Tests:** en `make check` no se pasa por la pantalla de mote, así que no cambia nada en los tests.

## Pendiente

- **Jorge:**
  - `make check` y `make release`;
  - si puede, reproducir la captura con el equipo lleno (Campo de Niebla y Canto Mortal) para ver que el mote se queda y el equipo no se clona;
  - buscar la causa de fondo con el *watchpoint*.
- **ROM nueva para Miguel:** con el #47 y este PR fusionados, y una semilla nueva (`make nueva-partida` o el instalador con `-NuevaPartida`).
