# 17/11/2026 — Miguel: BOSQUE FRONDOSO y MANSIÓN OLVIDADA

## Qué se pidió

Miguel: "Petalia forest + mansion". Es la zona planteada en el estudio de zonas: ampliar el BOSQUE PETALIA con un bosque más frondoso y una mansión abandonada.

## Qué se ha hecho

- **`tools/dualocke/crear_bosque_frondoso.py`** (se puede volver a lanzar) hace los tres mapas y la entrada.
- **Entrada:**
  - Un pasillo nuevo en el claro del noreste del BOSQUE PETALIA, tapado por dos árboles de CORTE.
  - Lleva al bosque por el borde, sin pantalla de carga.
  - Tramo 2 (cap 23).
- **BOSQUE FRONDOSO** (36 × 40):
  - Se dibuja con una rejilla de letras. Una función pone las piezas de los árboles como en el bosque y avisa si alguna fila queda mal.
  - Tiene hierba alta, flores y una charca.
  - Arriba está la mansión: el edificio largo de CIUDAD FÉRRICA con su verja.
- **MANSIÓN OLVIDADA:**
  - Las salas del BARCO ABANDONADO, sin salvavidas y con un paso nuevo.
  - Una puerta atascada y otra que sube al DESVÁN.
  - El suelo de madera de ese barco ya tenía salvajes en el juego (sin usar): aquí salen fantasmas.
- **Guardián en el DESVÁN:** Gengar a nivel 20 sin semilla, con el mismo sistema que las islas del ferry. Premio: Hechizo y su megapiedra.
- **Dos zonas de captura nuevas** (111 de 128).
- **Cuatro entrenadores:**
  - SEBAS ocupa el último hueco (863).
  - OLIVIA, ELVIRA y ALFONSO reutilizan tres entrenadores de Esmeralda sin usar (los placeholders de BRENDAN y MAY, y HOJA).
  - Ya no quedan huecos.
- **Salvajes** de bosque, charca y fantasmas; **objetos:** 5 y un Ticket-Recuerdo.
  - Se movieron a mano: el script los ponía en la línea de visión de dos entrenadores y en la entrada del desván.
- **Documentación:** `DUALOCKE.md`, `PRUEBAS.md` y `GUIA.html`.

## Cómo se comprobó

- **`comprobar_zonas.py`:** 0 fallos en 948 mapas (zonas 111 de 128, entrenadores 864 de 864).
- **Mapas:** dibujados con `ver_mapa.py`, el bosque junto al BOSQUE PETALIA para ver la unión.
- **Alcance:** desde la entrada se llega a todas las casillas libres de los tres mapas, también a la de delante del guardián.
- **Cadena de niveles:**
  - En `trainers.party` solo cambian los tres bloques reutilizados y se añade SEBAS.
  - En `wild_encounters.json` solo se añaden las tablas nuevas, al final.
- **El script se puede volver a lanzar:** se lanzó dos veces y deja los mapas igual.
- **No se ha compilado** (sin WSL).

## Pendiente

- Probarlo en el juego (`PRUEBAS.md`), sobre todo:
  - la unión de los dos bosques;
  - que los tres entrenadores reutilizados salgan con su nombre y su foto.
- Para más entrenadores nuevos habrá que reutilizar otros (queda `TRAINER_RED`).
