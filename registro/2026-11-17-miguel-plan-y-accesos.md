# 17/11/2026 — Miguel: todo listo para la ROM, paso a las islas y plan para Jorge

## Qué se pidió

Miguel: "detallar todo esto en un plan para que Jorge se lo pueda pasar a su Claude y él siga adelante… déjalo todo preparado para que se pueda hacer la ROM ya y haz un plan para seguir mejorando las cosas en el futuro y se lo mandas a Jorge".

## Qué se encontró

- **#99 (Jorge):** ya junta todo lo de Miguel hasta la #98, con los arreglos para las partidas en curso. **Compila y pasa todas las pruebas** de GitHub, incluida `release`, que es la que compila la ROM. Así que la ROM sale de ahí.
- **El fallo que encontró Jorge en la #99 (con `alcance.py`):**
  - a la ISLA ARENOSA, la ISLA DE RUINAS y la ISLA VOLCÁNICA no se podía entrar, porque se conectan por un borde de su ruta que está fuera de la barrera de rocas;
  - a la ISLA NEVADA solo se llegaba buceando.
  - Era un fallo de las comprobaciones de Miguel: se miraba el alcance desde el borde de la isla, no desde la ruta.

## Qué se ha hecho (rama `miguel/accesos-islas`, base #99)

- **Paso abierto en la barrera de rocas:**
  - **Cómo se eligió:** con `alcance.py` de Jorge se vio qué casillas de cada ruta se alcanzan. Una búsqueda de menor coste buscó las rocas sueltas de 2 × 2 que hay que quitar para llegar al borde de la isla sin pasar por corrientes y lejos de las conexiones de los lados.
  - **Qué se quita:**
    - **RUTA 129:** una roca en (46, 24);
    - **RUTA 131:** una en (7, 12) (la primera opción era un trozo de una peña de 3 × 3, y se descartó);
    - **RUTA 134:** un remolino en (9, 21);
    - **RUTA 124:** dos remolinos, en (11, 0) y (18, 16).
  - **Dónde está:** `quitar_rocas()` y `PASOS` en `crear_islas_sur.py`, y `PASOS_RUTA124` en `crear_isla_nevada.py`. Se puede volver a lanzar.
  - **Resultado con `alcance.py`:** las cuatro islas se alcanzan surfeando, en el tramo 7 (antes, 0 casillas; la NEVADA, solo en el tramo 8).
- **`PLAN.md`:** el plan para Jorge y su Claude:
  - cómo hacer la ROM ya (orden de fusión: #99, luego #100);
  - los biomas que quedan (A, B, C, E, G, H e I), con dónde, tramo y qué mirar;
  - la receta paso a paso para hacer un bioma;
  - los límites (zonas, entrenadores, flags);
  - mejoras para más adelante.
- **Documentación:** `DUALOCKE.md` y `PRUEBAS.md`, con el paso abierto.

## Cómo se comprobó

- **`comprobar_zonas.py`:** 0 fallos.
- **`alcance.py`:** las cuatro islas se alcanzan.
  - Ahora marca "por encima" a DARÍO y a los entrenadores de la ISLA NEVADA (los da como del tramo 6). Es el mismo caso que los de la RUTA 124, que no se marcan porque están en `POR_HISTORIA`. Apuntado en `PLAN.md` para que se añadan las islas a esa lista (es de la #97).
- **Fotos de los cinco huecos:** se ven como un paso normal entre rocas.
- **Compilación:** la hará el CI de la PR.

## Pendiente

- Fusionar la #99 y la #100, compilar y jugar con `PRUEBAS.md`.
- Seguir el plan (`PLAN.md`).
