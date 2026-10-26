# Reparto de los diálogos que quedan

Hecho hasta ahora (tramos 01-14, unos 1460 textos): de VILLA RAÍZ a MALVALONA, RUTA 117 y la RUTA 111 sur.

Quedan unos 2600 textos de la historia de Hoenn. Se reparten en dos mitades independientes (mapas distintos), así cada uno trabaja sin pisar al otro. El postgame (FRENTE BATALLA, MONTE ENTRENADOR, revanchas de LÍDERES) y los mapas de Kanto no se traducen.

## Miguel: tramos 15 a 29 (unos 1300 textos)

En orden de la historia:

1. CASA TRAMPA de la RUTA 110 (~145)
2. PUEBLO VERDEGAL (~50)
3. RUTA 111 (entrenadores y desierto) y RUTA 112 (~100)
4. MONTE CENIZO (teleférico y cima) y CAMINO ESCABROSO (~90)
5. RUTA 113, PUEBLO PARDAL, RUTA 114, CATARATAS METEORO y RUTA 115 (~255)
6. PUEBLO LAVACALDA y su GIMNASIO (~70)
7. RUTA 118, RUTA 119 e INSTITUTO METEOROLÓGICO (~150)
8. CIUDAD ARBORADA y su GIMNASIO (~80)
9. RUTA 120, RUTA 121 y ZONA SAFARI (~140)
10. BARCO ABANDONADO y ferry M.S. MAREA (~105)
11. Textos comunes básicos: objetos recibidos, movimientos de campo, PC, guardar, SURF, REPELENTE, recordador de movimientos (~105)

**Hecho (tramos 15-25, 26/10/2026).**

Los textos comunes resultaron ser muchos más (~1500 de Hoenn). Los que quedan se reparten así:

- **Miguel:** `berry_tree`, `berries`, `berry_blender`, `blend_master`, `pokedex_rating`, `move_tutors`, `secret_base` y `shared_secret_base` (**hechos**, tramos 26-28); quedan `mauville_man` (el hombre de MALVALONA, ~165) y `tv` (los programas de la tele, ~400).
- **Jorge:** `contest_hall`, `lilycove_lady`, `lottery_corner`, `profile_man`, `pokemon_news`, `questionnaire`, `cable_club` y `match_call` (las llamadas de la AGENDA, ~320). Unos 580, que se suman a sus zonas.
- **No se traducen:** `apprentice`, `battle_tent`, `battle_frontier` (postgame), todo lo `_frlg` (Kanto), `debug`, los `gift_*` y `mystery_event_club` (eventos), `test_signpost`, `flavor_text` (muebles de los mapas de Kanto) y la parte de OAK de `pokedex_rating`.

## Jorge: tramos 30 a 49 (unos 1300 textos)

**Cambio (26/10/2026):** como Jorge está con el randomizer, Miguel ha empezado esta parte por CIUDAD CALAGUA (tramos 30 y 31: calles, PUERTO, MOTEL, casas, MUSEO y CENTRO COMERCIAL), y luego RUTA 123, MONTE PÍRICO y GUARIDA AQUA (tramos 32 y 33) CIUDAD ALGARIA, CENTRO ESPACIAL y GUARIDA MAGMA (tramos 34-36) y las RUTAS 124 a 134 con la CUEVA CARDUMEN, la zona submarina y la CUEVA ABISAL (tramos 37 y 38) y ARRECÍPOLIS, CUEVA ANCESTRAL, PILAR CELESTE y PACIFIDLOG (tramos 39 y 40). y COLOSALIA, la CALLE VICTORIA y la LIGA (tramo 41). **La historia principal está traducida entera.** Quedan la SALA DE CONCURSOS y el CLUB DE FANS de CALAGUA y todo lo demás de la lista. Antes de empezar un tramo, avisad en el PR para no repetirlo.

En orden de la historia:

1. CIUDAD CALAGUA: calles, CENTRO COMERCIAL, SALA DE CONCURSOS, MUSEO, casas (~270)
2. MONTE PÍRICO y GUARIDA AQUA (~110)
3. RUTA 122/123 (~70)
4. CIUDAD ALGARIA, su GIMNASIO y el CENTRO ESPACIAL (~160)
5. GUARIDA MAGMA (~55)
6. RUTAS 124 a 134 (el mar), CUEVA CARDUMEN y zona submarina (~305)
7. CUEVA ABISAL (~35)
8. ARRECÍPOLIS, su GIMNASIO, CUEVA ANCESTRAL y PILAR CELESTE (~165)
9. PUEBLO PACIFIDLOG (~35)
10. CIUDAD COLOSALIA, CALLE VICTORIA y LIGA POKéMON (~160)

## Cómo se trabaja (los dos igual)

- Rama propia: Miguel en `miguel/dialogos-1`; Jorge crea `jorge/dialogos-2` a partir de `miguel/dialogos-1` (así tiene la herramienta y los nombres).
- Cada tramo es un archivo `NN_nombre.tsv` en esta carpeta, con los números de arriba para no chocar.
- Sacar el inglés: `python tools/dualocke/dialogos.py exportar data/maps/MAPA/scripts.inc`. Los entrenadores de cada ruta están en `data/text/trainers.inc`.
- Comprobar: `python tools/dualocke/dialogos.py comprobar` (tiene que dar 0 errores: ancho de línea, códigos `{…}` y el `$` final).
- Aplicar: `python tools/dualocke/dialogos.py aplicar`, y luego commit + push al PR de cada uno.
- Nombres oficiales y regla de género: ver `LEEME.md`. Si un nombre no está en la lista, se apunta allí al usarlo por primera vez.
- Al terminar cada tramo, se añade una fila a la tabla de `LEEME.md`.

Los nombres de las zonas de este plan son los oficiales que recordamos; si alguno no lo es, se corrige en `LEEME.md`.
