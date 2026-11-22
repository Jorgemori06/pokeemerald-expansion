# 22/11/2026 — Miguel: los fallos de las zonas nuevas que encontró el bot de Jorge

## Qué se pidió

Jorge probó las zonas nuevas con su bot (#118), sin fusionar nada, y dejó cinco fallos:
- tres en el #116 (comentario del 22/11/2026);
- dos en el #117.

Miguel: "Jorge nos ha dejado cosas para hacer, vamos a ello".

## Qué se ha hecho

### En el #116 (rama `miguel/arreglos-prueba-5`)

1. **ISLA VOLCÁNICA: no se llegaba al barquero.**
   - **El fallo:** estaba en (38, 34), en la punta de un trozo de muelle de PORTUAL que no está unido a la ciudad.
   - **El arreglo:** el barquero pasa al final del muelle de abajo, en (37, 40), encima del otro marinero. Al volver te deja en (36, 40).
   - **`alcance.py`:** no lo veía porque daba el viaje por hecho desde cualquier casilla del mapa. Ahora cada viaje de `VIAJES` puede llevar la casilla desde la que se habla al barquero, y solo cuenta si se llega a ella. Con esto, (38, 33) sale inalcanzable y la isla se sigue alcanzando en el tramo 8.
2. **ISLA DE RUINAS: no se entraba en la TORRE.**
   - **El fallo:** la puerta (20, 13) es una puerta sin animación (`MB_NON_ANIMATED_DOOR`), que se cruza al pisarla, y tenía colisión.
   - **El arreglo:** ahora va sin colisión, como hace el juego en el PILAR CELESTE (`setmetatile ..., FALSE`).
   - **`comprobar_zonas.py`:** avisa de estas puertas en todos los mapas. En el juego original no hay ninguna.
3. **DESIERTO PROFUNDO: el norte era una trampa sin VUELO.**
   - **El fallo:** la escalera buena de la cueva te dejaba en la arena del norte, y de ahí no se podía volver al sur.
   - **El arreglo:** ahora sales por la puerta de un montículo del norte (`MONTICULO_NORTE`, puerta en (6, 16)), que es de ida y vuelta con la escalera buena. Además, la sala buena tiene una segunda escalera, en (33, 14), que vuelve a la entrada.
   - **La CUERDA HUIDA:** sigue dejándote en el norte, pero ya no es una trampa.

### En el #117 (rama `miguel/biomas`)

4. **PRADO DE HADAS: no se entraba desde la RUTA 119.**
   - **El fallo:** la hierba de la ruta está a altura 4 y la del prado a 3, y el juego no deja pasar de una altura a otra.
   - **El arreglo:** las dos casillas del borde del prado que dan a la entrada van a altura 0, la de paso, desde la que se puede ir a las dos.
   - **`comprobar_zonas.py`:** mira la altura a los dos lados de las conexiones de las zonas nuevas.
5. **ISLA DEL DRAGÓN: en la esquina de la derecha no se bajaba.**
   - **El fallo:** al pasar de la RUTA 129 a la 130, el juego copia lo que se veía en la 129 (`MoveMapViewToBackup`, `src/fieldmap.c`, 7 columnas hacia dentro). Debajo de la 129, en esas columnas, no hay nada, así que la isla quedaba tapada en las x 73-79.
   - **El arreglo:** la isla va ahora de la x 33 a la 72.
   - **`comprobar_zonas.py`:** avisa si una zona nueva de arriba o de abajo se puede cruzar a menos de 7 columnas de un lado con otro mapa al lado. Lo mira solo donde se cruza, así que la CIÉNAGA TÓXICA y la ISLA NEVADA no salen (en esas columnas hay árboles o rocas).

## Cómo se comprobó

- **Las comprobaciones nuevas** encuentran los fallos 2, 4 y 5 antes del arreglo (el 5, justo en las x 73-79) y dan 0 después.
- **`comprobar_zonas.py`, `alcance.py`, `sin_salida.py` y `variantes.py`:** 0 en las dos ramas.
- **Tramos (`alcance.py`):**
  - ISLA VOLCÁNICA: 8;
  - entrada del DESIERTO PROFUNDO y escalera nueva: 5;
  - PRADO: 6;
  - ISLA DEL DRAGÓN: 6, saltándose la historia, como las otras islas del sur (no cambia).
- **Fotos enviadas a Miguel:** `fotos_zonas/23` a `27`.
- **Choques con los PR de Jorge:** solo `GUIA.html` con el #119, en las dos líneas que se generan (`datos-pistas` y `datos-fotos`). Al fusionar, quedarse con una y relanzar `guia.py` y `emulador/fotos_guia.py`.
- **Compilación:** la hará el CI. **Sin probar en el emulador:** Jorge lo puede volver a pasar con `probar_zonas.py`.

## Pendiente

- Que Jorge vuelva a pasar el bot por la ISLA VOLCÁNICA, la TORRE, el DESIERTO PROFUNDO, el PRADO y la ISLA DEL DRAGÓN.
- `comprobar_zonas.py` no está en el CI: proponer a Jorge meterlo (da 0 en todas las ramas).
