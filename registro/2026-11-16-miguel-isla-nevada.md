# 16/11/2026 — Miguel: la ISLA NEVADA

## Qué se pidió

Después de la GRUTA ÍGNEA (#82), Miguel eligió la Isla Nevada (`ZONAS.md`, propuesta 1): una isla al norte de la RUTA 124 con nieve y una cueva de hielo.

## Qué se ha hecho

- **`tools/dualocke/crear_isla_nevada.py`** crea los dos mapas.
  - **La isla** (80 × 40) es mar de la RUTA 124 con el islote de la RUTA 125 (el de la CUEVA CARDUMEN) pegado arriba.
    - Usa los mismos gráficos que la RUTA 124. En las conexiones, el trozo del otro mapa se dibuja con los gráficos del mapa en el que estás, así que si fueran otros se verían mal.
    - El trozo copiado empieza y acaba en mar abierto: la primera prueba cortaba rocas por la mitad.
  - **La CUEVA HELADA** es la sala de hielo de la CUEVA CARDUMEN.
- **Conexión:** la RUTA 124 se conecta hacia arriba con la isla y la isla hacia abajo con la RUTA 124, con el mismo ancho (80) y desplazamiento 0.
- **Zona de captura propia:** `MAPSEC_ISLA_NEVADA`, al final de la lista. `HOENN_EXTRA_MAPSEC_LAST` pasa a ser esa, con los carteles de zona en `map_name_popup.c`.
- **Entrenadores:**
  - DUDLEY y KAYLEE eran nadadores sin usar: se reescalan con `ENTRENADORES_ISLAS`.
  - `TRAINER_NIEVES` es nueva y la escribe `zonas_nuevas.py`.
- **Salvajes** (agua, pesca y cueva) en `zonas_nuevas.py`; **objetos** en `colocar_objetos.py` (`OBJETOS_NEVADA`).
  - Tres objetos se movieron después a mano, porque el script los ponía pegados a la entrenadora en un pasillo estrecho o escondidos en el agua.
- **Tramo 7**, en `reescalar_niveles.py` y `guia.py`.

## Cómo se comprobó

- **No se ha compilado** (sin WSL).
- **Isla:** dibujada con `ver_mapa.py`. Con `alcance.py`, se llega surfeando desde el borde de la RUTA 124 hasta la entrada de la cueva y el banco de arena.
- **Cueva:** dibujada. El recorrido sobre el hielo es el de la sala original, que funciona en el juego.
- **Niveles:** cadena entera; solo cambian DUDLEY, KAYLEE y NIEVES, y se añaden las tablas al final.
- **Textos:** medidos; caben.

## Para más adelante

- La cueva es una copia de la sala de la CUEVA CARDUMEN. Con Porymap se podría dibujar una propia, más grande.
