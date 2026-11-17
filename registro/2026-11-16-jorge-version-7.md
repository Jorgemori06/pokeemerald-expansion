# 16/11/2026 — Jorge: ROMs de la versión 7

## Qué se pidió

Miguel, a través de Jorge, pidió que se revisara y se le diera salida a lo suyo. Con sus cuatro PR fusionados (#69, #73, #74 y #75) y los de Jorge que fusionó Miguel el 14/11 (#66, #67, #68, #70, #71 y #72), tocaba ROM nueva: la última era la versión 6, del 12/11.

## Qué se ha hecho

- ROMs con `make release` sobre el commit `8103388b2`, con las mismas semillas:
  - **Miguel:** `2918696854`, md5 `c9ffa49009ed959540fd252e6dc7f76f`.
  - **Jorge:** `2780853751`, md5 `68a30f9824083b16e0976825c2e5bb86`.
- `DUALOCKE.md`, sección 9: versión 7.

## Cómo se comprobó

- `make check` completo sobre ese mismo árbol: 5469 tests, 0 fallos.
- **Las partidas siguen valiendo:**
  - Lo que se guarda no ha cambiado desde la versión 6: de `include/` solo cambia el nombre de un flag que no se usaba (`FLAG_DUALOCKE_CAJAS_REVISADAS`).
  - Con las dos semillas, contra la versión 6: salvajes, iniciales, MT y tutores idénticos, y ningún entrenador cambia de especie.
- El solucionario de cada ROM es el mismo que se comparó en la revisión.
- No se ha cargado una partida de verdad en la ROM nueva: aquí no hay ninguna de este locke.
