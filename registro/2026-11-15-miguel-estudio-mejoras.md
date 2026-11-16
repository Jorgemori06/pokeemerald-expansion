# 15/11/2026 — Miguel: estudio de mejoras (Gigamax como megas, interfaces y zonas nuevas)

## Qué se pidió

Revisar qué nos hemos podido dejar y mirar si se pueden hacer tres cosas:

1. Las formas Gigamax como megaevoluciones, con su megapiedra (como en el Pokémon Añil).
2. Interfaces más chulas y actualizadas.
3. Zonas nuevas, empezando por una marisma junto a PUEBLO AZULIZA, y edificios con NPC.

Es un estudio: no se ha cambiado nada del juego.

## Qué se ha hecho

- **`tools/dualocke/ver_mapa.py` (nuevo):** dibuja cualquier mapa en un PNG con sus tilesets (metatiles, tiles y paletas), como Porymap. Puede marcar la rejilla, los objetos, los entrenadores y las puertas. Necesita Pillow.
  - Probado con PUEBLO AZULIZA, las RUTAS 106 y 107 y el BOSQUE PETALIA: se ven como en el juego.
  - Con esto ya se puede diseñar un mapa por código y comprobarlo a ojo.
- **`IDEAS.md`:**
  - **Idea 9 (nueva):** las formas Gigamax como megas. Qué especies, qué hay que tocar y qué cuesta.
  - **Idea 10 (nueva):** opciones del motor que tenemos apagadas.
  - **Idea 2:** añadida la zona junto a AZULIZA, con lo que se ha medido, y los edificios nuevos.

## Lo que se ha encontrado

- **Gigamax como megas: se puede.**
  - Las 32 formas ya son especies con sus sprites, y una mega es una línea en la tabla de cambios de forma.
  - Quitando las 4 que ya tienen mega y los 2 legendarios, salen 26 megas nuevas.
  - Lo que más lleva es decidir sus estadísticas, tipo y habilidad.
  - El bolsillo de megapiedras habría que subirlo de 100 a 130. Es lo último de `SaveBlock3` y sobra sitio.
- **Interfaces:** el motor trae apagados la Pokédex estilo HGSS, los tipos del rival en combate, la descripción de los objetos al recogerlos y los carteles estilo Blanco/Negro.
- **Huir de un entrenador:** `B_RUN_TRAINER_BATTLE` está activado, y huir cuenta como perder (`B_OUTCOME_FORFEITED`), o sea, perder el locke. No es un fallo, pero se puede pulsar por error.
- **Zona junto a AZULIZA: hay sitio.**
  - Al oeste del pueblo y debajo de la RUTA 106 hay un hueco de unas 36 × 20 casillas que no es de ningún mapa.
  - El borde oeste de AZULIZA es arena transitable en las filas 6 a 14, así que basta una conexión, sin tocar el pueblo.
  - La RUTA 106 y AZULIZA usan los mismos tilesets, que ya tienen todo lo necesario para una marisma.

## Cómo se comprobó

- **Gigamax:** leídos `species.h`, `form_change_tables.h`, `gen_1_families.h` (Kingler Gigamax) y `global.h` (`SaveBlock3`).
- **Opciones:** leídos los archivos de `include/config/`.
- **Mapas:** dibujados con la herramienta y miradas las colisiones de los bordes de AZULIZA y de la RUTA 106.
- No se ha compilado nada: solo hay una herramienta nueva y documentación.

## Pendiente

Lo decide Miguel: qué se hace y en qué orden. Lo recomendado:

1. Las opciones del motor (idea 10), que es lo más barato.
2. Las megas Gigamax (idea 9).
3. La zona de AZULIZA (idea 2), que es lo más grande.
