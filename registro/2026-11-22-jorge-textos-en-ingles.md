# 22/11/2026 — Jorge (con Claude): textos que seguían en inglés

Rama `jorge/textos-en-ingles`. Son los textos en inglés que vio el bot al pasarse el juego (PR #118, `bugs.md` n.º 1, 2, 3, 7 y 10).

## Texto

- **OPCIONES, VEL. TEXTO:** salía "LENTAMEDIARÁPIDA". El juego reparte las tres palabras entre x 104 y 198 (94 píxeles), y LENTA + MEDIA + RÁPIDA ocupan 96. Esa fila empieza ahora en x 76 (VEL. TEXTO acaba en 62); en los tests se queda en 104 (`src/option_menu.c`).
- **Menú de un POKéMON del equipo:** SUMMARY, SWITCH, ITEM… → DATOS, MOVER, OBJETO, QUITAR, CARTA, LEER, CAMBIAR, ENVIAR, ENTRAR, NO ENTRA, GUARDAR, y los del catálogo de Rotom (`src/data/party_menu.h`, con `ES()`). Caben en la ventana (80 píxeles); "Change Ability" va como "Cambiar habil.".
- **POKéNAV:** descripciones del menú, barra de ayuda (ZOOM/TODO/SALIR/VOLAR…), AGENDA (SR. PEÑA, PAPÁ, PROF. ABEDUL, MAMÁ, MÁXIMO y las descripciones de los líderes; LLAMAR/VER/SALIR; ESTRATEGIA, SUS POKéMON, PRESENTACIÓN; las fichas de MÁXIMO y del rival), búsqueda por condición y cintas. Nombres como en los diálogos ya traducidos. Comprobado el ancho de cada ventana.

## Gráficos con el texto dibujado

No son texto del juego, sino dibujos. Herramienta nueva: `tools/dualocke/textos_graficos.py`.

- Monta cada gráfico como se ve en pantalla: con su tilemap (PC, ficha, cabecera del POKéNAV) o con los trozos del sprite uno al lado del otro (botones y cabeceras del POKéNAV, dinero).
- Borra en un recuadro los colores del texto inglés (cada píxel pasa al fondo de su fila) y escribe el español con las fuentes del juego (`graphics/fonts/latin_*.png`), con sus colores: letra, sombra, contorno o degradado por filas (como el "DATOS" del PC).
- Devuelve cada píxel a su tile. Si un tile se usa en varios sitios y solo cambia en uno (un trozo de fondo liso en el que ahora entra una letra), le da un tile que no use ningún tilemap y cambia el tilemap (pasó en la ficha, con MEDALLAS).
- Se puede volver a lanzar y no cambia nada (comprobado). `--ver /tmp/x` guarda cómo queda cada pantalla.

Qué cambia:

| Dónde | Antes | Ahora |
|---|---|---|
| POKéNAV, botones | HOENN MAP, CONDITION, MATCH CALL, RIBBONS, SWITCH OFF, PARTY, SEARCH, COOL…, CANCEL | MAPA HOENN, CONDICIÓN, AGENDA, CINTAS, APAGAR, EQUIPO, BUSCAR, CARISMA, BELLEZA, DULZURA, INGENIO, DUREZA, SALIR |
| POKéNAV, cabeceras | MAIN MENU, CONDITION, MATCH CALL, RIBBONS, HOENN MAP, FULL VIEW, ZOOM VIEW… | MENÚ, CONDICIÓN, AGENDA, CINTAS, MAPA HOENN, COMPLETO, AMPLIADO… |
| POKéNAV, arriba y abajo | POKéMON NAVIGATOR | POKéNAV |
| PC | PKMN DATA, PARTY POKéMON, CANCEL, CLOSE BOX | DATOS, EQUIPO, SALIR, CERRAR CAJA |
| Ficha de entrenador | TRAINER CARD, BADGES | FICHA ENTRENADOR, MEDALLAS |
| Tiendas | MONEY | DINERO |

Detalles:

- **Cabecera del POKéNAV:** no quedaba ningún tile libre, pero cada letra grande ocupa justo una columna de tiles y las iguales comparten tiles. "POKéNAV" se monta solo con el tilemap, apuntando a las letras de "POKéMON" y "NAVIGATOR". Abajo, con la fuente pequeña.
- **MONEY y BADGES** usan letras que no hay en ninguna fuente del juego (de 5 píxeles, y gruesas de 6). Para DINERO y MEDALLAS hay unas pocas letras dibujadas a mano en la herramienta; las de MEDALLAS que ya estaban en BADGES (A, D, E, S) están copiadas de ahí.
- Los botones del POKéNAV con poco alto pierden la fila de arriba de los acentos (CONDICIÓN), para no pisar el borde.
- Las paletas y el formato de los PNG (4 bits) no cambian.

**Probado en el emulador** con la ROM de pruebas, activando a mano el POKéNAV (sin subir ese cambio): OPCIONES, menú del equipo, ficha, POKéNAV (menú, CONDICIÓN, BUSCAR, mapa completo y ampliado), PC (MOVER POKéMON) y tienda.

## Queda en inglés

- Lo que ya estaba apuntado en DUALOCKE.md (sección 8): la pantalla de nombres, las cabeceras PROFILE, ABILITY y TRAINER MEMO de los datos, el botón MOVE INFO del combate, los iconos de los tipos y PRESS START. Se pueden hacer con la misma herramienta.
