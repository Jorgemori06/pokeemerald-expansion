# 16/11/2026 — Jorge: revisión de los PR #78 a #83 de Miguel

## Qué se pidió

Miguel abrió seis PR entre la madrugada y el mediodía del 16/11, sin poder compilarlos (no tiene WSL): #78 (opciones del motor), #79 (Gigamax como megas), #80 (análisis de zonas), #81 (islas del ferry), #82 (GRUTA ÍGNEA) y #83 (ISLA NEVADA). Jorge pidió revisarlos como los anteriores: compilar, tests, comparar con las semillas en curso y ver que no se rompen las partidas, y contarle qué está bien antes de fusionar.

## Qué se ha hecho

Los seis juntos sobre `master` en la rama `jorge/revision-miguel-2`. El #81, el #82 y el #83 van apilados, así que se juntó el #83, que lleva los tres.

### Choques al juntarlos

En `PRUEBAS.md`, `src/dualocke_aleatorio.c` y `tools/dualocke/colocar_objetos.py`. En los tres se dejan las dos partes, como decía Miguel.

### Lo que no compilaba

- **#78:** en la Pokédex HGSS, un texto con un salto de línea de verdad dentro de las comillas (`sText_EVO_CRITICAL_HITS`). Rompía todo el archivo.
- **#82 y #83, `trainers.party`:** TRAINER_STEVEN_ROUTE_120 es el último del archivo y no tiene línea en blanco detrás. `zonas_nuevas.py` pegaba ahí los entrenadores nuevos y `trainerproc` fallaba. Arreglado el archivo y el script, que ahora la pone.
- **#82 y #83, scripts de los mapas:** faltaba incluirlos en `data/event_scripts.s` y no enlazaba. Miguel lo arregló a la vez (14:21) y se queda su versión.
- **`zonas_nuevas.py` en Linux:** se paraba con `data/maps/.gitignore` (no es una carpeta). En Windows da otro error y por eso a Miguel no le pasaba.

### Lo que fallaba en los tests

- **"SaveBlock3 is backwards compatible":** el tamaño esperado era 644 bytes y ahora son 764, porque el bolsillo de megapiedras crece (#79). Es seguro, ver "Partidas guardadas" abajo. Actualizado en `test/save.c`.
- **"Item descriptions fit on Bag and Shop Screen":** las descripciones en inglés de la Corviknightita y la Centiskorchita ("This stone enables X to Mega…") no cabían por 1 píxel. Solo se ven en los tests (en el juego sale la española), pero se han cambiado las 26 a "This stone lets X Mega…", también en `megas_gigamax.py`.

### Semillas en curso

Con el #81, los objetos nuevos de las islas, la GRUTA y la ISLA NEVADA cambiaban casi todo lo que se sortea después:

- unos 285 de los 302 objetos del suelo;
- los 30 de la Recogida;
- lo que piden 3 o 4 intercambios.

El randomizer recorre los mapas por orden alfabético, y los nuevos se metían en medio. Arreglado con `tools/dualocke/aleatorio/zonas.py`: los objetos (por su flag) y los salvajes (por su mapa) de las zonas nuevas se sortean aparte. Los objetos van por flag porque ROCA OMBLIGO ya tenía uno (la Ceniza Sagrada oculta) y ese tiene que seguir donde estaba en la cuenta.

Con las semillas `2780853751` y `2918696854`, contra la versión 7:

- **Idénticos:** objetos del suelo, Recogida, intercambios, salvajes de antes, iniciales, MT y tutores.
- **Cambian, a propósito:**
  - los ases con mega de los jefes desde Alana: salen también las megas nuevas (#79);
  - el tope de fuerza de los líderes en los tramos con zona nueva, porque cuenta lo que se puede capturar. Con la de Jorge, tramo 6 de 505 a 510 y tramo 7 de 540 a 535; con la de Miguel, nada;
  - los entrenadores que no salían en ningún mapa y ahora salen en las islas;
  - los 5 Pokémon fuertes de las islas.

### Partidas guardadas

- **Flags nuevos:** todos estaban libres en la versión 7 (0x4CA-0x4E3, 0x881-0x885, 0x8E5-0x8FC).
- **Entrenadores:** 859 de 864, así que los flags de entrenador no se mueven.
- **Zonas de captura:** las nuevas van al final y las demás no cambian de número.
- **Bolsillo de megapiedras (100 a 130):** va al final del SaveBlock3, y el juego pone a cero el sector antes de guardar. En una partida de antes, las casillas nuevas se leen vacías.

### Cadena de scripts

`reescalar_niveles.py`, `equipos_jefes.py`, `evolucionar_entrenadores.py`, `ia_entrenadores.py` y `zonas_nuevas.py`, lanzados en ese orden, dejan el repo igual.

## Cómo se comprobó

- `make` compila (con los arreglos).
- `make check` completo: solo fallaban esos dos, que ya pasan. El resto, 5466 en verde (con los 48 del dualocke).
- El randomizer con las dos semillas antes y después, comparando el solucionario y los archivos que genera.

## Pendiente

- Probar en el emulador: `PRUEBAS.md`, "Interfaz", "Megas de las formas Gigamax", "Islas del ferry", "GRUTA ÍGNEA" e "ISLA NEVADA". Aquí no se puede.
- Lo deciden Jorge y Miguel: fusionar y hacer la versión 8.
