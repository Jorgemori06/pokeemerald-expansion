# Traducción de los diálogos

Son unas 187.000 palabras (los `.string` de `data/maps/*/scripts.inc`, `data/text/` y `data/scripts/`). Se traducen por tramos, en el orden de la historia, y **sin el postgame** (Frente Batalla, Pokédex Nacional, lo que pasa después de la Liga).

## Cómo funciona

- Cada tramo es un `.tsv` de esta carpeta, con una línea por texto: `etiqueta<TAB>texto`. Las líneas que empiezan por `#` son comentarios.
- El texto va en una sola línea, con los mismos códigos que el original: `\n` (salto de línea), `\l` (la línea sube), `\p` (página nueva), `{PLAYER}`, `{RIVAL}`, `{STR_VAR_1}`… y `$` al final si el original lo lleva.
- `tools/dualocke/dialogos.py`:
  - `exportar <archivos .inc>`: saca el inglés en el mismo formato, para traducirlo.
  - `comprobar`: mide cada línea en píxeles con la fuente del juego (máximo 208 px; `{PLAYER}` y parecidos cuentan como 7 letras), y comprueba los códigos, el `$` final y que existan las etiquetas.
  - `aplicar`: escribe el español en los `.inc`. Se puede volver a ejecutar.
- Los diálogos no los comprueba ningún test de la expansion, así que se cambian directamente (sin `ES()`).

## Nombres de Hoenn (oficiales)

VILLA RAÍZ, PUEBLO ESCASO, CIUDAD PETALIA, CIUDAD FÉRRICA, PUEBLO AZULIZA, PUEBLO VERDEGAL, CIUDAD PORTUAL, CIUDAD CALAGUA; NORMAN, PETRA (Roxanne), SR. PEÑA (Mr. Stone), MÁXIMO (Steven), SCOTT, MARCIAL (Brawly), CAPITÁN BABOR (Capt. Stern), EQUIPO AQUA; PROF. ABEDUL, AURA (May), BRUNO (Brendan), BLASCO (Wally), SR. ARENQUE (Mr. Briney), AREDIA (Lanette). Las DEPORTIVAS (Running Shoes).

## Hecho

| Tramo | Archivo |
|---|---|
| Presentación del PROF. ABEDUL y VILLA RAÍZ | `01_inicio_villa_raiz.tsv` |
| Casa del jugador y casa del rival | `02_casas_villa_raiz.tsv` |
| LABORATORIO y RUTA 101 | `03_laboratorio_ruta101.tsv` |
| PUEBLO ESCASO, enfermera del CENTRO POKéMON y RUTA 103 | `04_pueblo_escaso_ruta103.tsv` |
| RUTA 102 (y sus entrenadores) y CIUDAD PETALIA | `05_ruta102_petalia.tsv` |
| GIMNASIO PETALIA (sin la revancha del postgame) | `06_gimnasio_petalia.tsv` |
| RUTA 104, casa del SR. ARENQUE y BOSQUE PETALIA | `07_ruta104_bosque_petalia.tsv` |
| CIUDAD FÉRRICA (calles) y su GIMNASIO | `08_ciudad_ferrica.tsv` |
| CIUDAD FÉRRICA: DEVON, ESCUELA, casas, tienda, CENTRO POKéMON | `09_ferrica_edificios.tsv` |
| RUTA 116 y TÚNEL FERVERGAL | `10_ruta116_tunel_fervergal.tsv` |

Siguiente: PUEBLO AZULIZA (con su GIMNASIO), CUEVA GRANITO y RUTAS 105-109 (el mar hasta PORTUAL).

## Género del jugador

El jugador puede ser chico o chica y el texto no cambia. Hay que evitar las frases con género ("¿estás listo?" → "¿todo a punto?", "el hijo del LÍDER" → "de la familia del LÍDER"). Donde el juego ya tiene un texto para cada uno (AURA habla a un chico, BRUNO a una chica), se adapta.
