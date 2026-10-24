# 24/10/2026 · Miguel · Diálogos: primer tramo

Rama: `miguel/dialogos-1`

## Qué se ha hecho

- Decidido: los diálogos de los mapas los traducimos nosotros por tramos, en el orden de la historia, sin el postgame.
- `tools/dualocke/dialogos.py`: exporta el inglés, comprueba las traducciones (ancho en píxeles con la fuente del juego, códigos, `$`) y las aplica a los `.inc`.
- Primer tramo (149 textos): presentación del PROF. ABEDUL, VILLA RAÍZ, las dos casas, el LABORATORIO, RUTA 101, PUEBLO ESCASO (con su tienda, casas y CENTRO POKéMON), la enfermera de todos los CENTROS POKéMON y RUTA 103.
- Explicación y lista de nombres en `traduccion/dialogos/LEEME.md`.

## Cómo se comprobó

- `dialogos.py comprobar`: 0 errores. Ningún test usa estos textos.
- No se ha compilado ni visto en el emulador (en el PC de Miguel no hay compilador).

## Pendiente

- Probarlo jugando.
- Los siguientes tramos (RUTA 102, CIUDAD PETALIA…).
