# 27/10/2026 — Jorge: bug del equipo clonado, parche y ROMs nuevas

## Qué se pidió

Después de las respuestas de Miguel (#48), Jorge eligió hacer las dos cosas: poner un parche para poder jugar ya y seguir buscando la causa del equipo clonado. Miguel pidió fusionar y una ROM nueva.

## Qué se ha hecho

- **PRs fusionados:**
  - #47: fuera las habilidades de relleno, con las respuestas de Miguel (#48).
  - #49 de Miguel: protege el mote y el orden del equipo, y comprueba que el orden sea una permutación antes de reordenar el equipo. Compilado aquí y aprobado.
  - El Claude de Jorge tenía preparado lo mismo (#50, solo con la protección del mote). Se quedó el de Miguel, y este PR se queda solo con la documentación.
- **Reproducción automática en mGBA:** sin subir; un arnés juega el combate solo y vigila esa memoria fotograma a fotograma.
  - Con otra semilla no se reproduce: el mote y el equipo salen bien.
  - Detalles en `BUG-EQUIPO-CLONADO.md`.
- **ROMs nuevas para los dos** desde `master` con el #49 (commit `c9b5e9e38`), con las mismas semillas: Miguel `7044754226`, Jorge `6629063067`.
- `DUALOCKE.md`: el aviso del principio dice que está parcheado y sin causa confirmada.

## Cómo se comprobó

- `make release` con las dos semillas: compila.
- Arnés de mGBA, sin el parche y con otra semilla: equipo intacto y mote bien puesto.

## Pendiente

- Repetir el arnés con la semilla de Miguel.
- Más adelante, si no vuelve a pasar, quitar el aviso de `DUALOCKE.md`.
