# 22/11/2026 — Jorge: repartir los objetos amontonados

## Qué se pidió

Jorge, mirando el mapa interactivo (#125), vio que en la RUTA 123 y en la RUTA 119 los objetos estaban todos juntos. Miguel: "no rompe nada y me parece medio bien, pero si se puede cambiar pues mejor".

## Qué pasaba

`colocar_objetos.py` busca la casilla libre más cercana a un "ancla" (un objeto, un entrenador, una puerta o una persona del mapa), y coge siempre **la primera ancla que tenga sitio**. Así, todos los objetos de una ruta acababan alrededor del mismo:

| Mapa | Antes (objetos en un 7×7) |
|---|---|
| RUTA 119 | 11 |
| RUTA 123 | 10 (alrededor de WENDY) |
| RUTA 117 | 9 |
| NUEVA MALVALONA | 8 |
| RUTA 111 | 7 |
| RUTA 120 | 7 |
| RUTA 121 | 6 |
| RUTA 110 | 5 |
| RUTA 113 | 5 |
| SENDERO ÍGNEO | 5 |

## Qué se ha hecho

- **`colocar_objetos.py --repartir`.** En los mapas con 5 o más objetos en un 7×7, vuelve a colocar los nuestros: megapiedras, competitivos y Ticket-Recuerdo.
  - Las casillas candidatas siguen las mismas reglas de siempre:
    - transitable y a la altura del ancla;
    - de 1 a 4 pasos de un ancla (las ocultas, de 3 a 8);
    - sin tapar el paso (`sin_salida.py`).
  - **Mismo tramo:** solo vale una casilla a la que se llega en el mismo tramo que a la de antes (`alcance.py`). Ningún objeto se adelanta ni se retrasa.
  - **La más lejana:** de esas, la que queda más lejos de todos los demás objetos del mapa, uno detrás de otro.
  - **Qué cambia en el `map.json`:** solo la x, la y y la altura. El orden de la lista no cambia, así que los números de los objetos que usan los scripts siguen igual.
- **Se movieron 70 objetos de 10 mapas.**
  - El montón más grande baja a 3 objetos, en NUEVA MALVALONA. En el resto se queda en 1 o 2.
  - En NUEVA MALVALONA, `alcance.py` no sabe de las barreras eléctricas, así que el tramo no se pudo comprobar. Los objetos siguen dentro del mismo edificio.
- **Guía:** pistas y fotos regeneradas (`guia.py` y `emulador/fotos_guia.py`, 164 de 164). Se miraron a ojo las 47 fotos de las megapiedras y tickets movidos: todos están en sitios normales y se pueden coger.

## Comprobado

- `make` y `make DUALOCKE_PRUEBA=1` compilan.
- `alcance.py --comprobar`: 0.
- `sin_salida.py --comprobar`: 0.
- `comprobar_zonas.py`: 0 fallos.
- `graficos.py --comprobar`: 0.
- `variantes.py --comprobar`: 0.

## Partidas en curso

No se rompen: cada objeto tiene su propio flag. Lo que ya cogiste no vuelve a salir, y lo que no, aparece en el sitio nuevo. Hacen falta ROMs nuevas con las mismas semillas (Jorge `2635893558`, Miguel `3483218843`).

## Al fusionar

- `GUIA.html` choca con el #124, que también regenera las pistas y las fotos. Se arregla volviendo a lanzar `guia.py` y `fotos_guia.py` sobre `master`.
- Cuando estén el #125 y este, hay que volver a lanzar `mapa_interactivo.py`.
