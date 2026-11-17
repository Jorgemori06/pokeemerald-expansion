# 16/11/2026 — Miguel: opciones del motor (interfaz)

## Qué se pidió

Miguel, después del estudio del #75 ("interfaces más chulas, actualizadas"): empezar por las opciones del motor que estaban apagadas (idea 10 del estudio).

## Qué se ha hecho

- **Pokédex estilo HeartGold/SoulSilver** (`POKEDEX_PLUS_HGSS`):
  - Traducidos los 97 textos de `src/pokedex_plus_hgss.c` con `ES()`. Los de la página de estadísticas se han medido con la tabla de anchos de la fuente pequeña (`gFontSmallLatinGlyphWidths`) frente al hueco que tienen en el código: por eso "LEYENDA" y "MUY DURA" en vez de "LEGENDARIO" y "MUY DIFÍCIL", y "HUMANO" en el grupo huevo.
  - Los métodos de evolución se montan por trozos. Los que en español van delante del tipo o de la naturaleza ("tipo Siniestro en el equipo", "naturaleza Firme") llevan un trozo nuevo delante, que en los tests es vacío.
  - **MT y tutores de la semilla:** la Pokédex sacaba la lista original de cada especie, que con el randomizer no vale. Ahora usa `Dualocke_MovimientosEnsenables` (`src/dualocke_aleatorio.c`): las MT y MO con su movimiento de la semilla, los tutores nuevos y el resto de su lista, y solo los que `CanLearnTeachableMove` deja aprender. La lista se guarda en `struct PokedexView` (memoria dinámica, 400 huecos).
  - Los movimientos por nivel y la habilidad ya salían de la semilla (`GetSpeciesLevelUpLearnset` y `GetAbilityBySpecies`).
- **Combate:** tipos del rival junto a la barra (`B_SHOW_TYPES`), textos a la mitad de pausa (`B_WAIT_TIME_MULTIPLIER` 8), sin entrada deslizante.
- **No se puede huir de los entrenadores** (`B_RUN_TRAINER_BATTLE` = `FALSE`): huir contaba como perder el combate, o sea, el locke. El mensaje "¡No se puede huir…!" ya estaba traducido.
- **Objetos:** imagen y descripción al recogerlos, siempre (`OW_ITEM_DESCRIPTIONS_ALWAYS`). El modo "la primera vez" añade datos a `SaveBlock3` y rompería las partidas en curso.
- **Carteles de zona estilo Blanco/Negro** con la hora en 24 h. La ventana ocupa todo el ancho (30 tiles), así que caben los nombres en español.
- Documentado en `DUALOCKE.md` (sección 6, "Interfaz"), `GUIA.html` (Novedades) y `PRUEBAS.md`.

## Cómo se comprobó

- **No se ha compilado:** en el PC de Miguel no hay WSL ni compilador. Lo tiene que compilar Jorge (`make` y `make check`).
- Anchos de los textos de la Pokédex medidos con un script con la tabla de la fuente.
- Revisado a mano que todas las opciones existen en el código y qué hacen (`src/map_name_popup.c`, `src/overworld.c`, `src/menu.c`, `src/battle_main.c`).
- Falta verlo en el emulador: la lista está en `PRUEBAS.md`, "Interfaz".

## Ojo

- La partida guardada sigue valiendo: ninguna opción cambia `SaveBlock`. `struct PokedexView` solo vive mientras la Pokédex está abierta.
- Si algún test de la expansion depende de poder huir de entrenadores, saldría en `make check`.
