# 17/11/2026 — Miguel: islas de las rutas del sur

## Qué se pidió

Miguel: "Southern islands". Son las propuestas 2, 3 y 4 de ZONAS.md: una isla de ruinas, una volcánica y una de arena en las rutas de mar del sur.

## Qué se ha hecho

- **`tools/dualocke/crear_islas_sur.py`** (se puede volver a lanzar) hace las tres islas, sus dos interiores y las conexiones con las rutas. Todas son del tramo 8.
- **Antes de colocarlas se miraron las corrientes:**
  - Las RUTAS 132-134 tienen los bordes cerrados por rocas, y sus corrientes solo empujan al oeste, así que no se llega a los huecos.
  - El borde este de la RUTA 127 es una pared de roca.
  - Por eso dos islas cambian de sitio respecto a ZONAS.md.
- **ISLA DE RUINAS** (al norte de la RUTA 131):
  - El islote del PILAR CELESTE con su torre, con niebla.
  - Un túnel entre dos cuevas lleva al rellano de la torre.
  - La torre (la planta 1 del PILAR CELESTE) tiene el guardián: Metagross.
- **ISLA VOLCÁNICA** (al sur de la RUTA 134, sin corriente):
  - Un bajío con el montículo del PILAR CELESTE.
  - Su cueva baja al CRÁTER: la cima del MONTE CENIZO con ceniza que tiene salvajes, una salida nueva y el guardián, Charizard.
- **ISLA ARENOSA** (al este de la RUTA 129):
  - Tres islotes de la RUTA 127, sin bases secretas, con hierba alta entre los árboles.
  - Tormenta de arena; guardián, Tyranitar.
- **Tres zonas de captura nuevas** (114 de 128).
- **Entrenadores:** uno, DARÍO, que reutiliza `TRAINER_RED`, el último entrenador de Esmeralda sin usar. **Ya no quedan entrenadores libres.**
- **Salvajes, objetos y documentación:** salvajes de ruinas, de fuego, de arena y de mar; 7 objetos y un Ticket-Recuerdo por isla. Actualizados `DUALOCKE.md`, `PRUEBAS.md` y `GUIA.html`.

## Problemas encontrados y arreglados al hacerlo

- **El rellano de la torre no tenía entrada desde el mar** (en el juego se llega por una cueva desde otro mapa). Se unieron las dos cuevas del islote como un túnel.
- **El mar más común de la RUTA 134 es corriente:** la isla volcánica habría salido llena de corriente. Ahora se usa el mar en calma, y las corrientes nunca se copian.
- **Los bordes del bajío de la RUTA 134 llevan dibujada la corriente:** se cambiaron por bajío liso.
- **Al copiar el islote de árboles se colaban trozos de rocas vecinas:** se ajustó el recorte.
- **Objetos:**
  - El script ponía uno delante de DARÍO y otros juntos: se movieron a mano.
  - Se añadió el bajío (`MB_SHALLOW_WATER`) a las casillas válidas para objetos, porque la arena de esos islotes es bajío.

## Cómo se comprobó

- **`comprobar_zonas.py`:** 0 fallos en 953 mapas (zonas 114 de 128, entrenadores 864 de 864).
- **Alcance:** desde la entrada de cada mapa se llega a todas las puertas, al guardián y al entrenador. Ninguna isla tiene casillas de corriente.
- **Mapas:** dibujados con `ver_mapa.py` y revisados de cerca en los bordes.
- **Cadena de niveles:**
  - En `trainers.party` solo cambia el bloque de `TRAINER_RED`.
  - En `wild_encounters.json` solo se añaden las tablas nuevas al final.
  - Los guardianes salen a nivel 81.
- **No se ha compilado** (sin WSL).

## Pendiente

- Probarlo en el juego (`PRUEBAS.md`), sobre todo cómo se ven las uniones con las rutas y el túnel de la ISLA DE RUINAS.
- **Entrenadores:** para poner más en zonas nuevas hay que decidir entre reutilizar entrenadores existentes o agrandar la lista. Agrandarla rompe las partidas guardadas.
