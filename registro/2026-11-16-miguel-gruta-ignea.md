# 16/11/2026 — Miguel: la GRUTA ÍGNEA

## Qué se pidió

Miguel eligió seguir con el "SENDERO ÍGNEO profundo" (`ZONAS.md`, propuesta 7) después de las islas del ferry (#81). Al principio lo había llamado "gruta ígnea", y ese es el nombre de la zona.

## Qué se ha hecho

- **`tools/dualocke/crear_gruta_ignea.py`** crea el mapa:
  - **Base:** la planta 4 de la GUARIDA MAGMA (mismo tileset que el SENDERO ÍGNEO, con el lago de lava), sin las máquinas.
  - **Máquinas:** cada casilla pasa a ser el suelo de cueva de al lado. Solo suelo de cueva, para que no salgan tablas de puente donde no tocan, como pasó en la primera prueba.
  - **Salida:** se tapa la de la guarida, y la puerta del noreste es la entrada.
- **Entrada:** una boca de cueva en la sala del suroeste del SENDERO ÍGNEO, la de detrás de las rocas de FUERZA, copiada de la salida del sur (flecha y boca).
- **Zona de captura propia:**
  - `MAPSEC_GRUTA_IGNEA` va al final de `region_map_sections.json`, y `HOENN_EXTRA_MAPSEC_LAST` pasa a ser esa.
  - En `map_name_popup.c` se le ha puesto la entrada que le tocaba: la tabla del estilo Blanco/Negro no tiene tamaño fijo y sin ella se habría leído fuera.
- **Mapa y layout al final** de su grupo y de `layouts.json`: no cambia el número de ningún mapa de las partidas guardadas.
- **Entrenadores:**
  - `TRAINER_IGOR` y `TRAINER_ROQUE` son nuevos (856 y 857 de 864).
  - `TRAINER_GRUNT_UNUSED` existía sin usar.
  - `zonas_nuevas.py` escribe los nuevos (con las especies ya evolucionadas: `evolucionar_entrenadores.py` solo mira los de la base) y cambia los gráficos de la soldado.
- **Salvajes, objetos y tramo 5:** en `zonas_nuevas.py`, `colocar_objetos.py` y `reescalar_niveles.py`.
  - `colocar_objetos.py` ya acepta mapas en los que todo el suelo tiene altura 0, como este.
- **Documentado** en `DUALOCKE.md` (sección 6), `GUIA.html` y `PRUEBAS.md`.

## Cómo se comprobó

- **No se ha compilado** (sin WSL).
- Mapa dibujado con `ver_mapa.py`: sin restos de máquinas, y la boca del SENDERO ÍGNEO igual que la salida del sur.
- `alcance.py` (en la carpeta temporal de la sesión): 389 casillas conectadas desde la entrada, alrededor del lago.
- Cadena de niveles entera: solo cambian los 3 entrenadores de la gruta y se añade la tabla de salvajes al final.
- Textos medidos: caben.

## Dudas para probar

- **Clima:** `WEATHER_DROUGHT` dentro de una cueva. Si se ve mal, se cambia a `WEATHER_NONE` y se pierde el sol en combate.
