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

VILLA RAÍZ, PUEBLO ESCASO, CIUDAD PETALIA, CIUDAD FÉRRICA, PUEBLO AZULIZA, PUEBLO VERDEGAL, CIUDAD PORTUAL, CIUDAD CALAGUA, CIUDAD ALGARIA, MALVALONA; NORMAN, PETRA (Roxanne), SR. PEÑA (Mr. Stone), MÁXIMO (Steven), SCOTT, MARCIAL (Brawly), CAPITÁN BABOR (Capt. Stern), DOCK, GABI y TY, EQUIPO AQUA, AQUILES (Archie), EQUIPO MAGMA, familia VENCEDOR (Winstrate, sin confirmar), ERICO (Wattson), MAESTRO TRAMPA, MAGNO (Maxie), CANDELA (Flannery), SILVINA (Shelly), ALANA (Winona), MEDALLA PLUMA, MEGA-ARO, COMEDERO (Pokéblock Feeder), S.S. CACTUS, HERMANOS LIMPIEZA, RECORDADOR (Move Relearner), LICUADORA DE BAYAS, OLVIDAMOVIMIENTOS (Move Deleter, sin confirmar), MOTEL CALAGUA (Cove Lily Motel, sin confirmar), CONSERVADOR (Curator), PRISMA ROJO y PRISMA AZUL (Red/Blue Orb), VITO y LETI (Tate y Liza), MEDALLA MENTE, MÁXIMO PEÑA (Steven Stone), BUSCATESOROS, PARTE ROJA/AZUL/AMARILLA/VERDE (Shards), SIGNO MAGMA, AMULETO (Cleanse Tag), MAESTRO LICUADOR, MAESTRO DE BAYAS, TUBO {POKEBLOCK}, MEDALLA CALOR, HERBOLARIO, CLUB MIMÉTICO, GUARDAS POKéMON (Rangers, sin confirmar), PROF. COSMO (Cozmo, sin confirmar), SACO HOLLÍN, TUTOR DE MOVIMIENTOS, METEORITO, GALLETA LAVA, SENDERO ÍGNEO (Fiery Path, sin confirmar), CAMINO ESCABROSO (Jagged Pass, sin confirmar), ROBOMUÑECO (Mechadoll, sin confirmar), WANDA (sin confirmar), RYDEL (sin confirmar), CAMINO DE BICIS (sin confirmar); PROF. ABEDUL, AURA (May), BRUNO (Brendan), BLASCO (Wally), SR. ARENQUE (Mr. Briney), AREDIA (Lanette). Las DEPORTIVAS (Running Shoes).

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
| PUEBLO AZULIZA y su GIMNASIO, CUEVA GRANITO, RUTAS 105-109 y CASA DE LA PLAYA | `11_azuliza_cueva_granito_rutas105_109.tsv` |
| CIUDAD PORTUAL: calles, PUERTO, ASTILLERO, MUSEO OCEÁNICO, CLUB DE FANS, casas, tienda, CENTRO POKéMON | `12_ciudad_portual.tsv` |
| RUTA 110 y sus entrenadores, CIUDAD MALVALONA (calles, BLASCO, BICIS RYDEL, GIMNASIO de ERICO sin revancha, casas, tienda, CENTRO POKéMON) | `13_ruta110_malvalona.tsv` |
| CASINO de MALVALONA, NUEVA MALVALONA, RUTA 117 con la GUARDERÍA y RUTA 111 sur (familia VENCEDOR) | `14_casino_ruta117_ruta111.tsv` |
| CASA TRAMPA (pruebas 1-7; la 8 es del postgame) | `15_casa_trampa.tsv` |
| PUEBLO VERDEGAL (sin el interior de la CARPA DE COMBATE ni lo de después de la LIGA) | `16_verdegal.tsv` |
| RUTA 111 (desierto), RUTA 112, TELEFÉRICO, MONTE CENIZO (MAGNO y AQUILES) y CAMINO ESCABROSO | `17_ruta111_112_monte_cenizo.tsv` |
| RUTA 113 con el TALLER DE CRISTAL y PUEBLO PARDAL | `18_ruta113_pardal.tsv` |
| RUTA 114 (AREDIA y MANÍACO DE LOS FÓSILES), CATARATAS METEORO y RUTA 115 | `19_ruta114_cataratas_ruta115.tsv` |
| PUEBLO LAVACALDA y GIMNASIO de CANDELA (sin la revancha) | `20_lavacalda.tsv` |
| RUTAS 118 y 119 e INSTITUTO METEOROLÓGICO | `21_rutas118_119_instituto.tsv` |
| CIUDAD ARBORADA y GIMNASIO de ALANA (sin la revancha) | `22_arborada.tsv` |
| RUTA 120 (MÁXIMO y el MEGA-ARO), RUTA 121 y ZONA SAFARI de Hoenn (sin la zona ampliada del postgame) | `23_rutas120_121_safari.tsv` |
| BARCO ABANDONADO y ferry M.S. MAREA (sin la invitación al FRENTE BATALLA) | `24_barco_abandonado_ferry.tsv` |
| Textos comunes básicos: objetos, movimientos de campo, PC, guardar, SURF, REPELENTE, recordador | `25_textos_comunes_basicos.tsv` |
| BAYAS: árboles, regalos de BAYAS, FLORERÍA PÉTALO BONITO, MAESTRO DE BAYAS y LICUADORA | `26_bayas.tsv` |
| Valoración de la POKéDEX del PROF. ABEDUL y TUTORES de movimientos | `27_pokedex_tutores.tsv` |
| BASES SECRETAS | `28_bases_secretas.tsv` |

Siguiente: lo que queda está repartido entre Miguel y Jorge en `PLAN.md`.

La CARPA DE COMBATE y el FRENTE BATALLA se traducen igual cuando salen en una conversación normal, pero sus edificios se dejan para el final (son de después de la historia o secundarios).

## Género del jugador

El jugador puede ser chico o chica y el texto no cambia. Hay que evitar las frases con género ("¿estás listo?" → "¿todo a punto?", "el hijo del LÍDER" → "de la familia del LÍDER"). Donde el juego ya tiene un texto para cada uno (AURA habla a un chico, BRUNO a una chica), se adapta.
