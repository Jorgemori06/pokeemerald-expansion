# Ideas para personalizar el juego

Ideas de Jorge y Miguel para darle un toque propio al Dualocke. **No se implementan todavía**: se guardan aquí y se hacen cuando el juego esté terminado y todo funcione.

> **Para Claude:** no implementes nada de este archivo salvo que te lo pidan expresamente. Cuando una idea se haga, márcala como hecha y enlaza el PR.

## Cómo apuntar una idea

Una sección por idea, con:

- **Qué:** la idea en una o dos frases.
- **Propuesta de:** quién la tuvo y cuándo.
- **Notas:** lo que haga falta saber para hacerla (qué hay que tocar, dudas…).
- **Estado:** Pendiente / En curso / Hecha (PR #…).

## Ideas

### 1. Gonzalo Plaza como Campeón

- **Qué:** sustituir al Campeón por **Gonzalo Plaza**, con un aspecto de señor mayor (profesor).
- **Propuesta de:** Miguel, 23/10/2026.
- **Notas:**
  - Hay que cambiar el nombre y la clase del entrenador (`TRAINER_WALLACE` en `src/data/trainers.party`) y los textos de la sala del Campeón (`data/maps/EverGrandeCity_ChampionsRoom/`).
  - Para el aspecto, sirven los gráficos de un personaje mayor que ya existe en el juego (por ejemplo, el del profesor Abedul o un "Gentleman"), o unos nuevos: el sprite de combate y el del mapa.
  - El equipo y los niveles del Campeón (sección 6 de `DUALOCKE.md`) se pueden mantener o adaptar a él.
- **Estado:** Pendiente.

### 2. Zonas nuevas y mapas con más personalidad

- **Qué:** modificar el mapa de Hoenn y añadir zonas. Por ejemplo:
  - una cueva de ruinas en el desierto,
  - una pradera de flores junto a Pueblo Azuliza,
  - un bosque en otra parte del juego,
  - retocar alguna ruta para darle más personalidad.
- **Propuesta de:** Miguel, 23/10/2026.
- **Notas (viabilidad, sin planificar):**
  - **Es posible.** La expansion trae todo lo necesario y hay un editor visual, **Porymap**, pensado justo para esto.
  - **Retocar una ruta que ya existe** (mover árboles, añadir hierba, agua o flores): **fácil**. Se hace en Porymap con los tilesets que ya tiene el juego, y solo hay que revisar los objetos y entrenadores que haya encima.
  - **Ampliar un mapa** (por ejemplo, la pradera junto a Azuliza): **medio**. Hay que cambiar el tamaño del mapa y sus conexiones con los vecinos, y añadir encuentros salvajes. Si la isla no tiene sitio, se hace como mapa aparte con su entrada.
  - **Zona nueva completa** (la cueva de ruinas, un bosque): **medio-alto**. Hace falta:
    - un mapa y un layout nuevos,
    - la entrada (warp) desde el desierto,
    - encuentros salvajes,
    - nombre en el mapa de la región,
    - objetos y entrenadores, si se quieren.
    Con los tilesets que ya existen (cuevas, ruinas como las de las Cámaras Selladas, bosque como el de Petalia) es asumible.
  - **Gráficos nuevos** (un estilo de ruinas que no exista en el juego): **lo más difícil**. Habría que dibujar tiles y paletas a mano.
  - **Reparto del trabajo:** el diseño visual se hace mejor a mano en Porymap. Claude puede encargarse de lo demás: crear el mapa en los datos, conexiones y warps, scripts, encuentros, objetos y entrenadores. También puede generar un mapa sencillo por código, pero sin ver el resultado, así que el diseño fino es mejor en Porymap.
  - **Cosas que habría que tocar después:** los tramos de `reescalar_niveles.py` (para los niveles de la zona nueva), la tabla de `colocar_objetos.py` y la lista de zonas para las reglas de captura y el randomizer.
- **Estado:** Pendiente.
