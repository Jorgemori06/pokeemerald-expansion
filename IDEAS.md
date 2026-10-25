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

### 3. Jugar como Jorge o como Miguel

- **Qué:** al empezar, en vez de elegir entre chico y chica, elegir entre **Jorge Mori** y **Mike Mine**, con su propio aspecto. Los sprites los dibujaría una IA (ChatGPT, Gemini…) y luego se adaptan al formato del juego.
- **Propuesta de:** Jorge, 25/10/2026.
- **Notas (viabilidad, sin planificar):**
  - **La parte de elegir es fácil:** son los dos huecos que ya existen (BRUNO y AURA). Se cambia el texto de la elección del PROF. ABEDUL y, si se quiere, el nombre que sale por defecto.
  - **El rival sería el otro.** El juego usa como rival al del otro hueco: si eliges a Jorge, tu rival es Miguel, y al revés. Encaja con el dualocke.
    - Como los dos son chicos, hay que revisar los textos que cambian según el sexo: los del rival (los de AURA están en femenino) y los que se dirigen al jugador. Además, `playerGender` sale en unas 30 partes del código.
  - **Gráficos que necesita cada personaje:**
    - **Combate:** imagen de frente (64×64) y de espaldas con la animación de lanzar la Ball (4 imágenes de 64×64). También salen en la ficha de entrenador y en la presentación.
    - **Mapa:** andar y correr en las cuatro direcciones (16×32 por imagen), y además bici de carreras, bici acrobática, surf, pesca, buceo, usar un movimiento, regar y decorar. Son más de 100 imágenes pequeñas.
    - **Detalles:** icono del mapa de la región, mapa del POKéNAV, transición de combate…
    - Cada imagen solo puede tener **16 colores** (uno es el transparente).
  - **¿Sirven las IA para esto?** Para la imagen de **combate**, sí. Una IA da un dibujo con buena pinta, y Claude lo puede recortar, reducir a 64×64 y dejarlo en 16 colores; puede que haya que retocar algún píxel a mano. Para el **mapa**, cuesta: las IA no suelen respetar los tamaños exactos ni mantener al personaje igual en todas las imágenes de una animación.
  - **Propuesta por fases:**
    1. Imagen de combate nueva para cada uno, hecha con IA y adaptada. Es lo que más se ve y lo más agradecido.
    2. En el mapa, recolorear los sprites de BRUNO y AURA (pelo, ropa…) para que se parezcan a cada uno. Es solo cambiar la paleta y queda bien en todas las animaciones.
    3. Si apetece, sprites de mapa propios, dibujados a mano o partiendo de bases de la comunidad.
  - **Qué tendría que pasar Jorge:** fotos o descripción de cada uno (pelo, ropa, colores) e imágenes de referencia de la IA. Claude se encarga de convertirlas, meterlas en el juego y cambiar los textos.
- **Estado:** Pendiente.

### 4. Amigos nuestros como los NPC que dan Pokémon y regalos

- **Qué:** que los personajes que te dan Pokémon u objetos sean amigos de Jorge y Miguel: con su nombre y, si se puede, algo de su aspecto.
- **Propuesta de:** Jorge, 25/10/2026.
- **Notas (viabilidad, sin planificar):**
  - **Quiénes son:**
    - **Pokémon de regalo:** cinco sitios.
      - El huevo de la señora de PUEBLO LAVACALDA.
      - El inicial de Johto del laboratorio del PROF. ABEDUL.
      - El BELDUM de casa de MÁXIMO en ALGARIA.
      - El CASTFORM del INSTITUTO METEOROLÓGICO.
      - Los fósiles que revive DEVON en FÉRRICA.
      - Con el randomizer, todos dan un Pokémon al azar.
    - **Objetos de regalo:** unos 78 mapas con alguien que te da algo (MT, el Repartir Experiencia, la Moneda Amuleto…). Se puede elegir solo a unos cuantos.
  - **Nombre: fácil.** Los NPC normales no tienen nombre en el juego: solo hablan. Se les pone delante del texto ("PABLO: ¡Toma, para ti!") o se cambia la frase para que se presenten.
    - Los textos son traducciones de Miguel (`traduccion/dialogos/`), así que se cambian en su `.tsv` y se vuelven a aplicar.
  - **Aspecto, de más fácil a más difícil:**
    1. **Cambiar el sprite por otro que ya exista en el juego.** Es una línea en el `map.json` del mapa (`graphics_id`), y hay más de 200 personajes donde elegir: chico con gorra, chica deportista, abuelo, pescador…
    2. **Recolorearlo** con los colores de cada amigo (pelo, ropa). Los NPC comparten paletas, así que hay que darle una paleta propia, pero es asumible, como en la idea 3.
    3. **Un sprite nuevo dibujado:** solo tiene 4 imágenes (andar en cuatro direcciones), mucho menos que el jugador, pero sigue siendo dibujo a mano.
  - **Qué tendrían que pasar Jorge y Miguel:** la lista de qué amigo va en qué NPC, con su nombre y, si queréis el recoloreado, una foto o los colores de cada uno.
  - **Ojo con la regla de los regalos:** con la caja de prohibidos, un regalo repetido o legendario sigue yendo a la caja, sea quien sea el que lo da.
- **Estado:** Pendiente.
