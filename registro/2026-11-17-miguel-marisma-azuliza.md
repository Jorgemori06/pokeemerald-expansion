# 17/11/2026 — Miguel: MARISMA AZULIZA

## Qué se pidió

Miguel: "Dewford marsh". Es una de las zonas planteadas en el estudio de zonas: una marisma al oeste de PUEBLO AZULIZA.

## Qué se ha hecho

- **El mapa:** `tools/dualocke/crear_marisma_azuliza.py` (se puede volver a lanzar).
  - Mide 36 × 20 y usa los gráficos de AZULIZA.
  - Se une al pueblo por el borde oeste, sin pantalla de carga.
  - Tiene hierba alta, flores, dos charcas (de la RUTA 123 y la RUTA 102), lluvia y un cartel.
- **Zona de captura propia:** `MAPSEC_MARISMA_AZULIZA`, con sus carteles (los dos temas).
  - Hacía falta otra variable de zonas: `VAR_UNUSED_0x40FE` pasa a ser `VAR_DUALOCKE_ZONES_7`. Ahora caben 128 zonas y se usan 109.
  - Actualizados `src/dualocke.c` y `test/dualocke.c`.
- **Tramo 2** (cap 23): en `reescalar_niveles.py` y en `guia.py`.
- **Entrenadores nuevos:**
  - TOMÁS, pescador (861): Barboach y Lotad, a nivel 19-20.
  - MARGARITA, dama aroma (862): Shroomish y Paras, a nivel 19-20.
  - `TRAINERS_COUNT_EMERALD` pasa a 863.
- **Salvajes** (`zonas_nuevas.py`): POKéMON de pantano en hierba, surf y pesca.
- **Objetos:**
  - Semilla Milagro y un Ticket-Recuerdo (flags 0x88F y 0x8E3).
  - Se movieron a mano a la hierba alta: el script los ponía delante de TOMÁS.
- **Documentación:** `DUALOCKE.md`, `PRUEBAS.md` y `GUIA.html`.

## Cómo se comprobó

- **`comprobar_zonas.py`:** 0 fallos en 945 mapas (zonas 109 de 128, entrenadores 863 de 864).
- **Mapa:** dibujado con `ver_mapa.py` junto a AZULIZA, para ver que el borde casa. El cálculo de alcance llega a 396 casillas desde la entrada, objetos incluidos.
- **Cadena de niveles:**
  - En `trainers.party` solo se añaden los 2 entrenadores nuevos.
  - En `wild_encounters.json` solo se añade la tabla nueva, al final.
- **No se ha compilado** (sin WSL).

## Pendiente

- Probarla en el juego (`PRUEBAS.md`), sobre todo la unión con el pueblo y la variable nueva con una partida guardada de antes.
- Queda 1 hueco de entrenador (863). Para las próximas zonas habrá que subir `MAX_TRAINERS_COUNT_EMERALD` o reutilizar entrenadores.
