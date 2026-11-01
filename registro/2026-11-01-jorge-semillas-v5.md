# 01/11/2026 — Jorge: ROMs de la versión 5 con semillas nuevas

## Qué se pidió

Jorge pidió ROMs nuevas para los dos, con una semilla nueva para cada uno, después de fusionar el #53, el #54 y el #55. Miguel no puede compilarlas sin WSL.

## Qué se ha hecho

- ROMs con `make release` (sin menús de depuración) sobre el commit `27c61472d` de `master`:
  - **Miguel:** semilla `2918696854`, `Esmeralda Dualocke - Mikemine.gba` (md5 `37d7812237190d8217ac9c893c99b6cc`).
  - **Jorge:** semilla `2780853751`, `Esmeralda Dualocke - Jorgemori.gba` (md5 `1c901b81ee5fc3440b5d677d0c66ae22`).
- Las semillas son nuevas y el juego cambia, así que los dos empiezan partida nueva.
- `DUALOCKE.md`, sección 9: versión 5 y semillas actuales.
- `GUIA.html`, Novedades: los movimientos ya no tienen tope y los líderes llevan estrategia.

## Cómo se comprobó

- Las dos compilan sin errores y el randomizer no da avisos.
- Los tests completos ya se pasaron con el #54 (5455 en verde) y, después, con los dos arreglos de Miguel solo se ha comprobado que compila.
