# 27/10/2026 — Jorge: Pokédex en la guía

## Qué se pidió

Una Pokédex interactiva dentro de `GUIA.html`, como la de Pokémon Showdown pero más visual: tocas un Pokémon (Machop, por ejemplo) y salen sus estadísticas base y sus evoluciones.

## Qué se ha hecho

- **Sección 8 "Pokédex"** en `GUIA.html` (Novedades pasa a ser la 9):
  - **Rejilla de cartas:** sprite, número, total de estadísticas y tipos, con el color de sus tipos.
  - **Filtros:** búsqueda por nombre o número, filtro por tipo (hasta dos), orden por número, nombre, total o cada estadística, y casilla para ver megas y primigenios. Se pintan de 120 en 120 al bajar.
  - **Ficha al tocar un Pokémon:**
    - sprite grande;
    - barras de estadísticas por colores (en las megas, con lo que suben respecto a la normal);
    - débil a, resiste e inmune a, con la tabla de tipos moderna (con Hada), marcando ×4 y ×¼;
    - línea evolutiva completa, con el método de cada paso y las ramas (Eevee, Wurmple…); se puede tocar para ir a cada uno;
    - megaevoluciones con su megapiedra.
  - En el móvil la ficha ocupa toda la pantalla. El botón de atrás del móvil la cierra.
  - Habilidades y movimientos no salen: el randomizer los cambia en cada partida. Lo dice la ficha.
- **`tools/dualocke/guia_pokedex.py` (nuevo):** genera los datos desde el código, con el mismo preprocesador que el randomizer, y los mete en `<script id="datos-pokedex">`.
  - 1176 entradas: las 1025 especies, las formas regionales y las megas y primigenios. Las formas que solo cambian de aspecto se juntan con la normal.
  - Las evoluciones son las nuestras (las de intercambio ya salen por nivel o con objeto), en español.
  - Los sprites (PNG de 4 bits en base64) van dentro del HTML, que sigue siendo un solo archivo sin nada de fuera. Ocupa unos 1,6 MB.
- `DUALOCKE.md`: línea de la guía y mapa del código.

## Decisiones y cosas encontradas

- Las estadísticas que dependen de la generación (`P_UPDATED_STATS >= GEN_X ? a : b`) se evalúan bien en este script.
- **Fallo en el randomizer, sin tocar:** `tools/dualocke/aleatorio/especies.py` lee esas mismas estadísticas cogiendo el primer número de la expresión. Machoke sale con 8 de Def. Esp., y a Charizard le falta At. Esp.
  - Solo se usan para elegir el objeto de algunos jefes (`objeto_coherente`), así que el efecto es pequeño.
  - No se ha arreglado porque cambiaría los objetos de los jefes de las semillas del locke en curso. Queda para el siguiente.

## Cómo se comprobó

- Abierta con Chromium (Playwright) en escritorio (1280 px, tema claro) y móvil (375 px, tema oscuro):
  - 0 errores en la consola y sin barra horizontal;
  - ficha de Machop, Eevee y Mega-Charizard X;
  - filtro Dragón + Volador ordenado por total.
- `guia.py` y `guia_pokedex.py` se pueden relanzar: dejan el archivo igual.

## Pendiente

- Arreglar la lectura de estadísticas de `especies.py` para el siguiente locke.
