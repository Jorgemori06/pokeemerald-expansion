# 27/10/2026 — Jorge: guía actualizada con lo fusionado

## Qué se pidió

Jorge quería pasarle a Miguel la guía (`GUIA.html`, PR #43 de Miguel) con lo que ya está en las ROMs nuevas del locke (versión 2, commit `a661c0eb`).

## Qué se ha hecho

- Rama `jorge/guia-actualizada` desde `miguel/guia-html`, con `master` fusionado. El conflicto en `DUALOCKE.md` se resolvió dejando las líneas de los dos lados (la guía y el recuerdamovimientos).
- `python3 tools/dualocke/guia.py` en `master`: 81 megapiedras, 55 competitivos y 45 tickets, sin cambios en las pistas.
- `GUIA.html`:
  - fuera las etiquetas "próximamente" y el aviso de que los tickets aún no estaban en la ROM;
  - explicados los movimientos por nivel al azar (los tuyos, los salvajes y los de los entrenadores).

## Cómo se comprobó

- Abierta con Chromium (Playwright): 0 errores en la consola. La sección de novedades se ve bien.

## Pendiente

- Nada. Este PR sustituye al #43 (lleva sus commits).
