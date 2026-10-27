# 26/10/2026 — Jorge: ROMs para empezar el locke

## Qué se pidió

Empezar ya el locke, sin implementar las ideas: una ROM randomizada para Miguel y otra nueva para Jorge, sin el modo depuración y con nombres que acaben en Mikemine y Jorgemori.

## Qué se ha hecho

- Dos ROMs con `make release` (sin el menú de R + START ni el de SELECT en combate) desde `master` en `46ba7600`, cada una con una semilla nueva al azar:
  - `Esmeralda Dualocke - Mikemine.gba`: semilla `7044754226`.
  - `Esmeralda Dualocke - Jorgemori.gba`: semilla `6629063067`.
- `DUALOCKE.md`, sección 9: apartado "Locke en curso" con las semillas, el commit y cómo regenerarlas sin romper la partida.
- Las ROMs no se suben al repo; se pasaron por el chat.

## Cómo se comprobó

- Las dos compilan sin errores y el randomizer se ejecuta con su semilla (sale en el log). Las ROMs son distintas entre sí.
- En `make release`, `DEBUG_OVERWORLD_MENU` y `DEBUG_BATTLE_MENU` valen `FALSE`.

## Versión 2 (27/10/2026)

- Miguel jugó hasta el BOSQUE PETALIA y vio que los movimientos por nivel no eran al azar, y que no encontraba objetos ni el recuerdamovimientos. Lo arregló él en #42 y #40.
- Claude probó #38, #39, #40, #41 y #42 juntos: `make check` (5455 en verde) y `make release` con la semilla de Miguel. Comparó su randomización antigua con la nueva: todo igual salvo los movimientos por nivel y los de los entrenadores. Después aprobó y fusionó #38, #39, #40 y #42.
- ROMs nuevas para los dos desde `a661c0eb`, con las mismas semillas. Las partidas guardadas siguen valiendo.

## Pendiente

- Jugar. Apuntar los fallos que salgan (`PRUEBAS.md`).
