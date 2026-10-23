# 23/10/2026 · Miguel · Megapiedras por el mapa

Tarea de equilibrio de la sesión de Miguel. Rama `miguel/megapiedras`.

## Decisiones de Miguel

- Las megapiedras **no se venden: se encuentran explorando el mapa**, en sitios que encajen con ellas. Por ejemplo, la Cameruptita cerca del Monte Cenizo y la Garchompita en el desierto.
- **Todas** las de Pokémon no legendarios, por temática.
- Unas en **bolas de objeto nuevas** en rincones que hay que explorar y otras **ocultas**. No se quita ningún objeto que ya hubiera.
- Miguel aprobó la tabla antes de colocarlas.

## Cómo se hizo

- `tools/dualocke/colocar_megapiedras.py` tiene la tabla (megapiedra, mapa, bola u oculta) y elige la casilla él solo:
  - Parte de algo que seguro se alcanza en ese mapa: un objeto, un objeto oculto, un entrenador o, si no hay nada de eso, una puerta o escalera.
  - Desde ahí recorre solo casillas **transitables a la misma altura** (`map.bin` del layout).
  - Descarta casillas ocupadas, puertas y eventos, y comportamientos raros (agua, salientes…), salvo que sean iguales a los del punto de partida, como bajo el agua.
  - Las bolas van a 1-4 casillas del punto de partida y las ocultas, a 3-8.
- **Flags:** cada megapiedra tiene el suyo (`FLAG_ITEM_MEGA_...`). Se han usado los flags libres 0x264-0x283 de `include/constants/flags.h`, del bloque 0x264-0x2BB, que es válido también para objetos ocultos.
- **Solo se añade texto** en cada `map.json`: no se reescribe el archivo, porque el formato no es uniforme y el diff quedaría lleno de cambios falsos.
- **Se puede volver a lanzar:** las que ya están colocadas no se tocan.

## Resultado

- **81 megapiedras en 54 mapas.**
- **Cambio sobre la tabla aprobada:** la **Malamarita** iba en la Ruta 122, pero es toda agua y no tenía dónde ponerla. Va **oculta en la playa de Ciudad Calagua**.

## Decisiones de Claude por el camino (revisables)

- Las casillas exactas las ha elegido el script. **Hay que comprobar jugando** que todas se ven bien y se pueden coger, sobre todo en Sky Pillar, Mirage Tower y la parte oculta del barco, donde se ha partido de las escaleras.

## Para Jorge

- **Randomizer:** estas ubicaciones son fijas. Al barajar los objetos del suelo, sáltate los que tienen flag `FLAG_ITEM_MEGA_...`. Está anotado en la sección 6.
- **Flags:** si necesitas flags nuevos (por ejemplo, para las capturas por zona), quedan libres los del 0x284 al 0x2BB y los demás `FLAG_UNUSED_...`.
