# 26/10/2026 — Miguel: nivel de Latios/Latias y opciones del instalador

## Qué se pidió

Dos tareas de Miguel que quedaron apuntadas en el prompt de Jorge del PR #27:

- El nivel de los errantes Latios/Latias, que seguía en 40 sin reescalar.
- Que `instalar_windows.ps1`, que ya compila randomizado, tenga una opción para partida nueva y otra para probar sin randomizar.

## Qué se ha hecho

- `src/roamer.c`: Latios y Latias salen a nivel **100** (`DUALOCKE_NIVEL_ERRANTE`). Aparecen después de la Liga, así que van como el resto de legendarios del postgame (sección 5). El randomizer de Jorge (`Dualocke_EstaticoAleatorio`) sigue cambiando la especie igual.
- `tools/dualocke/instalar_windows.ps1`:
  - `-NuevaPartida`: lanza `make nueva-partida` (otra semilla). Pide escribir SI antes, porque la partida guardada deja de cuadrar con la ROM nueva.
  - `-SinRandom`: lanza `make SIN_RANDOM=1` y copia la ROM al escritorio como `Dualocke-sin-random.gba`, para no pisar la de juego.
  - Las dos a la vez da error.
- `DUALOCKE.md`: secciones 3 (cómo jugar) y 5 (estáticos).

## Cómo se comprobó

- El script se ha pasado por el analizador de PowerShell: 0 errores de sintaxis.
- **Sin compilar ni probar:** en el PC de Miguel no hay compilador y el CI sigue bloqueado. Ningún test usa `InitRoamer`.

## Pendiente

- Probar las dos opciones del script en un PC con WSL.
