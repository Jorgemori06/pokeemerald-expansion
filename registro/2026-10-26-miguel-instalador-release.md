# 26/10/2026 — Miguel: bolsillos y arreglos de Jorge, e instalador con make release

## Qué se pidió

Revisar, aprobar y fusionar los PRs #36 y #37 de Jorge (el reparto de Medicinas vale), y cambiar el instalador para que la partida de verdad use `make release`.

## Qué se ha hecho

- **#36 (arreglos de la primera prueba), aprobado y fusionado:**
  - las reglas empiezan también al tener Balls;
  - el mapa de la región en español;
  - TIPO/, los textos de "scurried", la ventana de vidas y "¿Adónde VOLAR?".
  - Jorge: `make check` con 5451 en verde, y `make release` compila.
- **#37 (bolsillos MEDICINAS y MEGAPIEDRAS), aprobado y fusionado:**
  - los bolsillos nuevos van en SaveBlock3 (60 y 100 huecos);
  - los bucles van por `POCKETS_COUNT`, así que no se queda ninguno atrás.
  - Las partidas guardadas viejas dejan de valer, pero todavía no había ninguna de verdad.
  - Jorge: `make check` con 5454 en verde.
- **`tools/dualocke/instalar_windows.ps1`:**
  - **Sin opciones:** `make release`, que copia `pokeemerald-release.gba` como `Dualocke.gba`. Sin menús de depuración.
  - **`-NuevaPartida`:** borra `dualocke_semilla.txt` y hace `make release`. Es lo mismo que `make nueva-partida`, que por dentro llama a `make` sin release.
  - **`-SinRandom`:** igual que antes, `make SIN_RANDOM=1` con los menús de depuración, y lo copia como `Dualocke-sin-random.gba`.
- **`DUALOCKE.md` (sección 3) y `PRUEBAS.md`:** explican lo de la versión release.

## Cómo se comprobó

- **Script:** pasa el analizador de PowerShell sin errores.
- **Comandos:** se comprobó a mano cómo quedan los comandos y la ruta de la ROM.
- **Makefile:** `make release` deja la ROM como `pokeemerald-release.gba`. La semilla se lee de `dualocke_semilla.txt` igual con release que sin él.
- **Sin compilar:** en el PC de Miguel no hay compilador. Jorge ya confirmó que `make release` compila con el randomizer.

## Pendiente

- Que Jorge pruebe el instalador sin opciones y compruebe que en la ROM no salen los menús de depuración (R + START, SELECT en combate).
