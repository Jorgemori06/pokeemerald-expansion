# 12/11/2026 — Jorge: ROMs de la versión 6

## Qué se pidió

Jorge y Miguel deciden seguir con sus partidas (Jorge había perdido 4 POKéMON en el primer gimnasio, antes del #63). Jorge pidió meter también el #64.

## Qué se ha hecho

- Se ha fusionado el #64. Con la semilla de Jorge solo cambian 52 jefes, y los salvajes, las habilidades y los iniciales salen igual, así que vale con las partidas empezadas.
- ROMs con `make release` sobre el commit `24e7f72ff`, con las mismas semillas que la versión 5:
  - **Miguel:** `2918696854`, md5 `0d0a1f465678d21e20199c14ea3f5515`.
  - **Jorge:** `2780853751`, md5 `95fa56ce66e155840cc34e8aa25e075d`.
- `DUALOCKE.md`, sección 9: versión 6.

## Cómo se comprobó

- `make check` completo con el #63: 5458 en verde.
- Los tests del dualocke con el #57, el #58, el #60 y el #61 juntos: 40/40.
- Las dos ROMs compilan sin errores.
