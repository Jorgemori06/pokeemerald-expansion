# 20/11/2026 — Miguel: la PLAYA VOLCÁNICA con ceniza

## Qué se pidió

Al contestar a las dudas de Jorge (`registro/2026-11-20-miguel-respuestas-jorge.md`), Miguel pidió:

- **Rehacer la PLAYA VOLCÁNICA:** "más que la 'piedra rojiza' que forma la playa, quizás quedaría mejor un paisaje donde se mezcle la playa con una zona de ceniza (como la ruta de arriba del volcán)".
- **Tiempo:** sol normal.

### Primer intento: descartado

- **Qué se hizo:** un mapa nuevo con las piezas de ceniza de la RUTA 113 (gráficos de PARDA):
  - una meseta de ceniza;
  - saltos hacia la playa;
  - manchas de ceniza en la arena;
  - un bosque con ceniza alrededor;
  - sin termas.
- **Qué dijo Miguel:** "No me gusta la nueva playa, creo que la estructura de la anterior está mejor, solo cambiaría la hierba y césped verde por el de ceniza".
- Se deshizo con un commit en la misma rama.

## Qué se ha hecho (rama `miguel/playa-ceniza`, sobre `miguel/respuestas-jorge`)

El mapa es **el mismo de antes**, con el arreglo de bordes de Jorge (#111). Lo que cambia son los **colores**.

### Por qué por colores

- **Las termas, el acantilado y la peña** son de LAVACALDA. Las piezas de ceniza de la RUTA 113 son de PARDA, y no se pueden mezclar.
- **La ceniza de LAVACALDA** (la del CAMINO ESCARPADO) es rosa, no como la de la RUTA 113.
- **Muchas piezas mezclan hierba con otra cosa:** bordes del camino, del risco, de las termas, de la peña, de las charcas y el suelo bajo los árboles. Cambiar las piezas una a una dejaría bordes verdes.

### Qué se ha cambiado

- **Dos tilesets nuevos, `gTileset_GeneralCeniza` y `gTileset_LavaridgeCeniza`:**
  - Son copias de General y de LAVACALDA, con los mismos dibujos, piezas, comportamientos y animaciones.
  - Sus paletas son otras: los cuatro verdes del suelo y la hierba pasan a los cuatro colores de la ceniza de la RUTA 113 (12 colores en General y 16 en LAVACALDA).
  - Los verdes de las hojas no cambian: árboles y flores siguen verdes, como en la RUTA 113.
- **`crear_playa_volcanica.py`:**
  - `paletas_ceniza()` escribe las paletas (`data/tilesets/primary/general_ceniza/palettes/`, `data/tilesets/secondary/lavaridge_ceniza/palettes/`);
  - añade las dos copias a `src/data/tilesets/graphics.h` y `headers.h`, justo después de las originales y solo si no están;
  - la playa usa los dos tilesets nuevos;
  - `WEATHER_SUNNY`.
- **`ver_mapa.py` y `ver_mundo.py`:** usan las paletas de cada tileset (`carpetas_paletas()`), para que las fotos salgan con la ceniza.

### La unión con la RUTA 122

Desde la playa, la parte de la RUTA 122 que se ve se pinta con las paletas de la playa. Ahí solo hay mar y rocas, que no usan ninguno de los colores cambiados (comprobado pieza a pieza). Se ve igual que antes.

## Cómo se comprobó

- **Fotos del mapa** (`ver_mapa.py`): sin ningún verde suelto en el suelo; los árboles y las flores, verdes.
- **`comprobar_zonas.py`:** 0 fallos.
- **`sin_salida.py --comprobar`:** 0 problemas.
- **`alcance.py --comprobar`:** 0.
- **`colocar_objetos.py`, el script y `guia.py`, otra vez:**
  - nada se mueve;
  - el script no repite los tilesets en el código;
  - las pistas de la guía no cambian.
- **Compilación:** la hará el CI de la PR (en local no se puede).
- **Sin probar en el emulador.**

## Pendiente

- Probar jugando (`PRUEBAS.md`, PLAYA VOLCÁNICA).
- **Las hojitas al pasar por la hierba alta** siguen verdes: son un efecto aparte con sus propios colores. Si quedan raras, se puede mirar.
- **Porymap** quizá no abra bien este mapa, porque las carpetas de los tilesets nuevos solo tienen paletas. Las zonas nuevas se hacen con sus scripts, así que no debería hacer falta.
