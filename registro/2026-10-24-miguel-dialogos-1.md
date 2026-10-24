# 24/10/2026 · Miguel · Diálogos: primer tramo

Rama: `miguel/dialogos-1`

## Qué se ha hecho

- Decidido: los diálogos de los mapas los traducimos nosotros por tramos, en el orden de la historia, sin el postgame.
- `tools/dualocke/dialogos.py`: exporta el inglés, comprueba las traducciones (ancho en píxeles con la fuente del juego, códigos, `$`) y las aplica a los `.inc`.
- Primer tramo (149 textos): presentación del PROF. ABEDUL, VILLA RAÍZ, las dos casas, el LABORATORIO, RUTA 101, PUEBLO ESCASO (con su tienda, casas y CENTRO POKéMON), la enfermera de todos los CENTROS POKéMON y RUTA 103.
- Segundo tramo (235 textos): RUTA 102 con sus entrenadores, CIUDAD PETALIA (calles, casas, tienda, CENTRO POKéMON, casa de BLASCO), el GIMNASIO PETALIA (sin la revancha del postgame), RUTA 104 con la casa del SR. ARENQUE y sus entrenadores, y BOSQUE PETALIA.
- Tercer tramo (unos 250 textos): CIUDAD FÉRRICA (calles, GIMNASIO de PETRA, DEVON, ESCUELA DE ENTRENADORES, casas, tienda, CENTRO POKéMON), RUTA 116 con sus entrenadores y TÚNEL FERVERGAL.
- Cuarto tramo (unos 330 textos): PUEBLO AZULIZA con el GIMNASIO de MARCIAL (sin la revancha), CUEVA GRANITO con MÁXIMO, RUTAS 105 a 109 con sus entrenadores y la CASA DE LA PLAYA.
- Quinto tramo (unos 200 textos): CIUDAD PORTUAL entera: calles, mercado, la cola del EQUIPO AQUA, la entrevista de GABI y TY, el PUERTO con AQUILES y el submarino, el ASTILLERO de BABOR, el MUSEO OCEÁNICO, el CLUB DE FANS, el EVALUADOR DE NOMBRES, casas, tienda y CENTRO POKéMON.
- Repasadas las frases con género del jugador para que valgan para chico y chica.
- Explicación y lista de nombres en `traduccion/dialogos/LEEME.md`.

## Cómo se comprobó

- `dialogos.py comprobar`: 0 errores. Ningún test usa estos textos.
- No se ha compilado ni visto en el emulador (en el PC de Miguel no hay compilador).

## Pendiente

- Probarlo jugando.
- Los siguientes tramos (RUTA 110, CIUDAD MALVALONA…).
