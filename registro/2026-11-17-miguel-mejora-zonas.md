# 17/11/2026 — Miguel: repaso y mejora de las zonas nuevas

## Qué se pidió

Miguel: "mira lo que hemos hecho y mejóralo, mejores mapas, más editados y completos, que nada falle… Y vas implementando lo que hemos planteado".

## Qué se ha hecho

- **Que nada falle:**
  - **Fallo encontrado:** los mapas nuevos no estaban apuntados en `data/event_scripts.s` y no habrían compilado. Arreglado en las ramas de los #82, #83 y #84.
  - **`tools/dualocke/comprobar_zonas.py`** (en el #84): 0 fallos en 944 mapas.
- **GRUTA ÍGNEA, más completa:** la salida del sur baja a la **CÁMARA DEL MAGMA**, una sala en terrazas con dos pozas de lava y un guardián arriba (Houndoom sin semilla, nivel 47).
- **RUINAS ARENOSAS, de 2 a 4 plantas:** las plantas 2 y 3 de la TORRE ESPEJISMO, con suelo agrietado que se hunde (`setholewarp`) y rocas de GOLPE ROCA.
- **CUEVA HELADA:** guardián al fondo (Baxcalibur sin semilla, nivel 70).
- **ISLA SUR:** hierba alta en el claro del bosque y salvajes de hierba. Antes solo se podía pescar.
- **Guardianes:** el mismo sistema que las islas del ferry.
  - Con semilla salen otros fuertes (`islas()` de `estaticos.py`).
  - Nivel cap − 3 (regla `"tope"`).
  - Premio: objeto y megapiedra.
- **`crear_gruta_ignea.py` y `crear_desierto_profundo.py`** generan también las salas nuevas.

## Cómo se comprobó

- `comprobar_zonas.py`: 0 fallos.
- Salas dibujadas con `ver_mapa.py` y recorridas con el cálculo de alcance.
- Cadena de niveles: no cambia ningún entrenador. Solo se añaden tablas de salvajes al final.
- **No se ha compilado** (sin WSL).
