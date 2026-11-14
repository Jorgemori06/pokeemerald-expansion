# 13/11/2026 — Jorge: la amistad en la pantalla de datos

## Qué se pidió

Jorge: "me gustaría q se viera el nivel de amistad q tienen los pokemon de tu equipo en info, igual q puedes ver ivs, evs y eso".

## Qué se ha hecho

- En la página de características, arriba a la derecha, donde salía el número de cintas, ahora sale la amistad: "123/255". Las cintas no sirven en el locke y así no hay que mover nada de sitio.
- La etiqueta de encima ("RIBBON") pasa a "AMISTAD". Se ha dibujado copiando las letras de las otras etiquetas (A y S de STATS, M e I de ITEM, D de DESCRIPTION) en los dos tilesets de la pantalla: `graphics/summary_screen/tiles.png` y `iv_ev_tiles.png`. Las demás etiquetas siguen en inglés (está apuntado lo de las imágenes).
- Código: `PrintRibbonCount` en `src/pokemon_summary_screen.c`. La amistad ya se leía del Pokémon (`summary.friendship`).
- Nota en `DUALOCKE.md`, sección 6 (pantalla de datos).

## Cómo se comprobó

- `make` compila.
- La etiqueta se ha revisado píxel a píxel: cabe en los 7 tiles que ocupaba "RIBBON" (los únicos que usan esos tiles en el tilemap).
- Falta verla en el emulador: no hay emulador con pantalla aquí.
