# 20/11/2026 — Miguel: la PLAYA VOLCÁNICA, rehecha con ceniza

## Qué se pidió

Contestando a las dudas de Jorge (`registro/2026-11-20-miguel-respuestas-jorge.md`), Miguel pidió:

- **Rehacer la PLAYA VOLCÁNICA entera:** "más que la 'piedra rojiza' que forma la playa, quizás quedaría mejor un paisaje donde se mezcle la playa con una zona de ceniza (como la ruta de arriba del volcán)".
- **Tiempo:** sol normal.

## Qué se ha hecho (rama `miguel/playa-ceniza`, sobre `miguel/respuestas-jorge`)

- **Gráficos:** la playa pasa de los de LAVACALDA a los de PARDA (`gTileset_Fallarbor`), los de la RUTA 113. Con los de LAVACALDA la ceniza es rojiza (la del CAMINO ESCARPADO); con los de PARDA es gris, como en la RUTA 113.
- **El mapa** (`crear_playa_volcanica.py`, mismo tamaño, 40 × 40):
  - **Arriba a la izquierda, una meseta de ceniza:** suelo de ceniza, hierba con ceniza y rocas.
  - **Saltos de ceniza** bajan a la playa de abajo. Se vuelve a subir por una lengua de ceniza al este.
  - **La playa:** a lo largo del mar y, abajo, ancha, con manchas de ceniza en la arena.
  - **Bordes:**
    - bosque con ceniza en los de tierra;
    - el borde del mapa, el de la RUTA 113;
    - rocas de mar en los del mar.
  - **Sin cambios:** el cruce con la RUTA 122 (filas 2-7), el arrecife del este y la banda de gráficos generales que se ve desde la ruta.
- **Fuera:** las termas, la peña de la RUTA 112, el risco y su escalera. Eran gráficos de LAVACALDA o rojizos.
- **Ceniza que se cae al pisar la hierba,** como en la RUTA 113 (`setstepcallback STEP_CB_ASH`).
- **Tiempo:** `WEATHER_SUNNY`.
- **Personajes:**
  - el bañista de las termas pasa a ser un vecino junto al mar;
  - el guardián (Slither Wing) sigue en la arena.
- **Objetos:** `SITIO_OBJETOS` los pone en su sitio. El Ticket-Recuerdo, en la mancha de ceniza del sur (19, 27).
- **Guía:** `guia.py` relanzada. La pista del Ticket-Recuerdo dice el sitio nuevo, pero falta su foto.

## Cómo se pintan los árboles con ceniza

Están sacados de la RUTA 113 y probados con fotos:

- Cada árbol ocupa dos columnas; la de la izquierda es impar.
- Las filas pares son "arriba" (0x275/0x276) y las impares, "abajo" (0x26D/0x26E).
- **Encima del bosque:** la copa sobre la ceniza (0x204/0x205), por donde se pasa.
- **Debajo del bosque:** el pie (0x20C/0x20D).
- **A los lados:**
  - junto a una fila de "abajo", una copa;
  - junto a una de "arriba", un pie.
- `bosque()` lo hace y comprueba que cada bosque empiece y acabe en la fila y columna que toca. Si no, se ve el árbol cortado.

La ceniza no tiene orilla con el agua: el script comprueba que nunca la toque.

## Cómo se comprobó

- **Fotos del mapa** (`ver_mapa.py`). Se ajustaron las manchas de ceniza, que quedaban muy cuadradas.
- **`comprobar_zonas.py`:** 0 fallos.
- **`sin_salida.py --comprobar`:** 0 problemas.
- **`alcance.py --comprobar`:** 0.
- **`colocar_objetos.py`** y el script, otra vez: no se mueve nada más.
- **Compilación:** la hará el CI de la PR.
- **Sin probar en el emulador.**

## Pendiente

- **Jorge:** las fotos de la guía (`fotos_guia.py`), porque la del Ticket-Recuerdo de la playa es del sitio de antes.
- **Probar jugando** (`PRUEBAS.md`, PLAYA VOLCÁNICA): los árboles, los saltos, donde la ceniza toca la arena, y capturar surfeando (el personaje roto).
