# 24/10/2026 · Miguel · Traducción: mensajes de combate (primera tanda)

Rama: `miguel/traduccion-combate`

## Qué se ha hecho

- Se miró la traducción de Heart & Soul (SergioBonet/hns_es). **No tiene licencia**, así que decidimos no copiar su texto: traducimos nosotros y le pediremos permiso al autor por si se pudiera reaprovechar con créditos.
- Sistema para traducir el combate sin romper los tests de la expansion (que comprueban los mensajes en inglés):
  - `include/dualocke_es.h`: macro `ES(inglés, español)`. En los tests elige el inglés y en el juego el español.
  - `src/data/dualocke_textos_combate_es.h`: tabla con los mensajes de `gBattleStringsTable` traducidos. Lo que no está traducido sale en inglés.
  - `src/dualocke_traduccion.c`: artículo y "salvaje"/"enemigo" para los Pokémon rivales, y las contracciones "del"/"al".
  - `src/battle_message.c`: usa la tabla en español, el artículo y las contracciones (solo fuera de los tests), y los textos sueltos con `ES()`.
- Traducido: los 180 primeros mensajes de la tabla, las subidas y bajadas de características y 105 textos sueltos (presentación del combate, sacar y retirar Pokémon, características, estados, menú de combate, evolución).
- Segunda tanda: mensajes 181–330 (clima, capturas, objetos equipados, Safari, desobediencia…). En total, 325 de 699.
- Nombres: Wally es BLASCO y Lanette es AREDIA, como en la Esmeralda española.

## Cómo se comprobó

- En el PC de Miguel no hay compilador: lo compila el CI de GitHub.
- Un script comprobó que cada traducción tiene los mismos códigos `{...}` que el inglés y que todos los caracteres existen en `charmap.txt`: 0 errores.

## Pendiente

- **Siguiente tarea pedida por Miguel:** mejorar la pantalla de datos del Pokémon (IVs, EVs, naturaleza con lo que sube y baja, habilidad y la otra posible, info de los movimientos). Apuntada en DUALOCKE §9.
- Tipo Hada: comprobado que ya está activo (tipos de Pokémon, movimientos y tabla de tipos modernos).

- Traducir el resto de la tabla (~375 mensajes) en más tandas.
- Menús de fuera del combate (`src/strings.c`).
- Probarlo jugando: frases raras, textos que no caben.
- Respuesta del autor de Heart & Soul.
