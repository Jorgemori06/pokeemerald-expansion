# 26/10/2026 — Miguel: PRs de Jorge aceptados y lista de pruebas

## Qué se pidió

Ponerse al día, aceptar los PRs pendientes y hacer lo necesario para que Jorge pueda compilar, probar y que podamos jugar.

## Qué se ha hecho

- **PRs de Jorge revisados, aprobados y fusionados:**
  - #33, textos comunes en español (AGENDA, concursos, lotería, club cable…). `comprobar` da 4715 textos y 0 errores, `aplicar` no cambia nada, y sin nombres en inglés ni las variantes que se corrigieron en el repaso. Jorge lo había compilado y pasado `make check` (5450 en verde).
  - #34, ideas nuevas en `IDEAS.md`. Solo documentación.
  - El #32 (historia de CALAGUA a la LIGA) ya lo había fusionado Jorge.
- **`traduccion/dialogos/LEEME.md`:** faltaban las filas 29-41 de la tabla "Hecho". Se intentaron añadir en la rama `miguel/dialogos-3`, pero se buscaba una fila que no existía allí y el cambio no se hizo. Añadidas ahora, y cambiado el "Siguiente".
- **`DUALOCKE.md`:**
  - sección 8, la traducción de la historia como hecha;
  - sección 9, randomizer y traducción en "Hecho", y el siguiente paso (jugar).
- **`PRUEBAS.md` (nuevo):** lista de qué mirar en la primera partida de prueba: textos, reglas del locke, randomizer y equilibrio, y cómo apuntar fallos.
  - Aviso: el menú de depuración (R + START) y el de combate (SELECT) están activos en el `make` normal. Para la partida de verdad habría que usar `make release`; queda pendiente comprobar que compila y adaptar el instalador.

## Cómo se comprobó

- `dialogos.py comprobar` en `master` tras fusionar: 4715 textos, 0 errores.
- Solo cambia documentación. Sin compilar (en el PC de Miguel no hay compilador).

## Pendiente

- Jugar la primera partida de prueba siguiendo `PRUEBAS.md`.
- `make release` para la partida de verdad (sin menús de depuración).
