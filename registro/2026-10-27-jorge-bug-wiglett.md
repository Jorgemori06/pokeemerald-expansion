# 27/10/2026 — Jorge: bug del Wiglett (habilidad y equipo clonado)

## Qué se pidió

Jugando el locke, a Miguel le pasaron dos cosas al capturar un Wiglett en el TÚNEL FERVERGAL: el Wiglett se quedó "Sin habilidad especial" y su equipo se convirtió en 6 copias de su Charmander. Jorge pidió averiguar por qué. Después pidió dejar un aviso para que el Claude de Miguel le pregunte todo lo necesario, porque sin saber exactamente qué pasó es ir a ciegas.

## Qué se ha hecho

- **Habilidades (arreglado):** `tools/dualocke/aleatorio/habilidades.py` ya no da habilidades de relleno.
  - Eran tres: `ABILITY_314` y `ABILITY_317` ("-------") y `ABILITY_AURA_GUARD` (sin implementar).
  - Para no cambiar las partidas en curso, se sortea igual que antes y solo se vuelve a sortear la especie que haya caído en una de relleno, con su propio sorteo.
  - Nueva `comprobar()`, que el randomizer lanza: si alguna especie se queda con una de relleno, para.
  - Con la semilla de Miguel cambian exactamente las 18 afectadas. El resto de su randomización (salvajes, entrenadores, objetos, MT, movimientos…) sale igual: comparado con el solucionario.
- **Equipo clonado (sin resolver):**
  - Análisis y preguntas para Miguel en `BUG-EQUIPO-CLONADO.md`.
  - Aviso al principio de `DUALOCKE.md` para que lo vea su Claude.
  - No se pudo reproducir en los tests: los combates de los tests se saltan el mote y se quedan esperando en el "¿lo metes en el equipo?". Issues de GitHub está desactivado en el repo, por eso va en un archivo.

## Cómo se comprobó

- `randomizer.py --semilla 7044754226` antes y después: solo cambian 18 habilidades.
- `make release SEED=7044754226`: compila, y el `.h` generado ya no tiene ninguna habilidad de relleno.

## Pendiente

- Respuestas de Miguel y reproducir lo del equipo clonado.
- ROM nueva para los dos con el arreglo de habilidades, cuando se fusione.
