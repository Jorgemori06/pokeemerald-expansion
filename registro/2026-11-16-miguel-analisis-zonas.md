# 16/11/2026 — Miguel: análisis de zonas nuevas

## Qué se pidió

Miguel: "un análisis de las zonas que podríamos mejorar/añadir, como islas (como las del Ultravuelo) en rutas de agua, mejorar el Sendero Ígneo, añadir zonas con climas más diversos (hielo, mejorar el desierto, ruinas...). Vamos a hacer un análisis de las rutas y luego empezamos a hacerlas."

## Qué se ha hecho

- `ZONAS.md`: qué hay en Hoenn, qué gráficos se pueden usar para cada clima, 8 propuestas con sitio, tramo y coste, los límites técnicos y el orden recomendado.
- `tools/dualocke/ver_mundo.py`: dibuja el mapa del mundo uniendo los mapas exteriores por sus conexiones, para ver dónde queda sitio.
- Enlace desde la idea 2 de `IDEAS.md`.

## Lo que se ha comprobado (para no tener que volver a mirarlo)

- Zonas de captura: 104 de 112 bits usados. Las zonas nuevas van al final de `region_map_sections.json`.
- Las islas del ferry (ISLA SUR, ISLA LEJANA, ISLA ORIGEN, ROCA OMBLIGO) ya cuentan como zona de captura.
- Entrenadores: 856 de 864, y 11 que no salen en ningún mapa.
- Flags libres: 162.
- El randomizer de salvajes saca de una baraja en orden: las tablas nuevas, al final de `wild_encounters.json`.
- El motor ya mezcla mapas de Rojo Fuego (`isFrlg`), pero sus tilesets solo se compilan en esa versión.

## Cómo se comprobó

- Solo se ha leído código y se han dibujado mapas: no cambia nada del juego.
