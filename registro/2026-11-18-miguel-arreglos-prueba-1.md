# 18/11/2026 — Miguel: arreglos de la primera prueba jugando (versión 8)

## Qué se pidió

Las notas de Miguel después de jugar:

- **Bien:** hasta la 1.ª medalla, el BOSQUE FRONDOSO y la MANSIÓN, CIUDAD PORTUAL y hasta el 3.er gimnasio.
- **Idea:** una CANTERA con POKéMON de tipo Acero en la RUTA 116, por la salida del TÚNEL FERVERGAL.
- **Fallos:**
  - baldosas mal puestas en la MARISMA y árboles raros en AZULIZA;
  - en la CUMBRE METEORO no funcionan ni la salida para volver ni la de seguir, y el mapa queda cortado por agua. "Me he quedado encerrado en la Cumbre Meteoro sin poder salir."

## Por qué pasaba

- **CUMBRE METEORO, encerrado:**
  - **Las dos cuevas de la LADERA:** estaban a altura 3, pero el suelo de alrededor está a 5 (sale de las terrazas de la RUTA 114). El juego solo usa una puerta si su altura es la del jugador, o 0, así que no salía por ninguna.
  - **Por qué no se vio antes:** la comprobación de alcance de Miguel y `alcance.py` miran por dónde se anda, no la altura de las puertas.
- **CUMBRE METEORO, agua:** el borde de los dos mapas (lo que se ve fuera) era el de la RUTA 115, que es mar. Dentro no hay agua.
- **CUMBRE METEORO, objetos:** sus dos objetos estaban a altura 3 sobre suelo a 4-7, y no se podían coger. La LADERA se rehízo cuando ya estaban puestos.
- **MARISMA, baldosas:** la hierba muy alta (0x015) no tiene borde de abajo con los gráficos de AZULIZA, y quedaba cortada. Había también una charquita de 2 × 2 suelta.
- **AZULIZA, árboles:** la marisma se pegaba al pueblo 7 filas más arriba, justo donde está la RUTA 106. Desde el pueblo se veía su muro de árboles encima de la playa. La #103 de Jorge lo tapaba cambiando el orden de las conexiones.

## Qué se ha hecho (rama `miguel/arreglos-prueba-1`)

- **`crear_cumbre_meteoro.py`:**
  - las tres cuevas (y la de la RUTA 115) van a altura 0, como la de la CATARATA METEORO;
  - el borde de los dos mapas es el de la RUTA 114, que es montaña.
- **`crear_marisma_azuliza.py`:**
  - `DESPLAZAMIENTO_AZULIZA` pasa a 0: la marisma ya no sobresale por encima del pueblo, y la entrada sigue cayendo en la arena (filas 6-13 de AZULIZA);
  - la hierba muy alta pasa a hierba alta;
  - se quita la charquita.
- **`colocar_objetos.py`:** `ajustar_alturas()` pone a cada objeto colocado por el script la altura del suelo en el que está. Corrigió los dos de la LADERA (a 4 y a 5).
- **`comprobar_zonas.py`:** avisa de puertas y objetos de las zonas nuevas a una altura que no es la del suelo. Con la LADERA de antes da justo los 4 fallos; ahora, 0.
- **`PLAN.md`:**
  - la CANTERA de la RUTA 116 sustituye a la "mina al oeste de FÉRRICA", que necesitaba SURF;
  - apartado "Arreglos del 18/11/2026" con lo aprendido.
- **`PRUEBAS.md`:** la partida 3 (esta) y qué mirar de los arreglos.

## Cómo se comprobó

- **`comprobar_zonas.py`:** 0 fallos, con las comprobaciones nuevas.
- **Todas las zonas nuevas:** solo la LADERA tenía puertas u objetos a una altura mal. Las 36 puertas "raras" de los mapas originales son las escaleras de los Centros POKéMON, que van así a propósito.
- **Fotos:**
  - la RUTA 106, la marisma y AZULIZA juntas: la marisma ya no se pisa con la ruta;
  - la CUMBRE: dentro no hay agua.
- **La cadena de niveles, salvajes y objetos:** vuelta a lanzar entera. Solo cambian las alturas de esos dos objetos.
- **Compilación:** la hará el CI de la PR.

## Pendiente

- Volver a jugar la CUMBRE y la MARISMA con estos arreglos.
- La CANTERA (`PLAN.md`, B).
