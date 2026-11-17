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
  - **Zona junto a PUEBLO AZULIZA (Miguel, 15/11/2026):** una marisma con plantas y agua al oeste del pueblo, debajo de la RUTA 106, donde ahora no hay nada, con objetos, megapiedras y entrenadores que den cosas.
    - **Hay sitio:** un hueco de unas 36 × 20 casillas entre el acantilado de la CUEVA GRANITO y el pueblo, que no pertenece a ningún mapa.
    - **Entrada sin tocar AZULIZA:** el borde oeste del pueblo ya es arena transitable en las filas 6 a 14. Basta una conexión a la izquierda.
    - **Mismos gráficos:** la RUTA 106 y AZULIZA usan `gTileset_General` y `gTileset_Dewford`, que ya tienen hierba, hierba alta, charcas, flores, árboles, arena y acantilados. No hace falta dibujar nada.
    - **Ya se pueden ver los mapas sin Porymap:** `tools/dualocke/ver_mapa.py` dibuja cualquier mapa en un PNG con sus tilesets. Así se puede diseñar el mapa por código y comprobarlo a ojo, y mirar las colisiones como se hizo con los objetos.
    - **Qué lleva:** mapa y layout nuevos, las conexiones, salvajes (hierba, agua y pesca), entrenadores nuevos en `trainers.party`, objetos, su tramo en `reescalar_niveles.py` (el 2) y su nombre en el mapa de la región.
    - **Ojo con la zona de captura:** si es una zona nueva del mapa de la región, da una captura más y cambia cómo se guardan las zonas gastadas. Si cuenta como RUTA 106, no cambia nada.
    - **Dificultad:** media-alta, pero ya no depende de dibujar a mano.
  - **Edificios nuevos con NPC:** más fácil que una ruta. Se copia una casa que ya exista en el mismo pueblo a un hueco libre, se le pone una puerta y el interior reutiliza el de otra casa. Dentro, personajes con combates o regalos.
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

### 5. Dos versiones: una personalizada para nosotros y otra general

- **Qué:** sacar dos ROMs del mismo código. La **personalizada**, con lo nuestro: jugar como Jorge o Miguel (idea 3), amigos como NPC (idea 4), Gonzalo Plaza de Campeón (idea 1)… Y la **general**, sin nada de eso, para pasársela a cualquiera.
- **Propuesta de:** Miguel, 26/10/2026.
- **Notas (viabilidad, sin planificar):**
  - **Es fácil si se prepara desde el principio.** Se hace igual que el randomizer: una opción al compilar, por ejemplo `make PERSONALIZADA=1`, que define una constante (`DUALOCKE_PERSONALIZADA`).
  - **Código:** lo personal va dentro de `#if DUALOCKE_PERSONALIZADA`.
  - **Gráficos y textos personales:** van en archivos aparte que el Makefile solo usa en esa versión.
  - **Mapas** (cambiar un NPC por otro sprite): mejor por código al cargar el mapa que tocando el `map.json`, para no tener dos copias de cada mapa.
  - Todo lo demás (reglas del locke, randomizer, traducción) es igual en las dos.
  - Las dos se compilan con la misma semilla o con otra, como se quiera.
  - **Instalador:** se le añade una opción para elegir cuál compilar.
- **Estado:** Pendiente.

### 6. Que el primer Pokémon del equipo te siga por el mapa

- **Qué:** como en HeartGold y SoulSilver, el primer Pokémon del equipo va andando detrás del jugador por el mapa, y se puede hablar con él.
- **Propuesta de:** Miguel, 26/10/2026.
- **Notas (viabilidad, sin planificar):**
  - **La expansion ya lo trae hecho.**
    - Se activa con `OW_FOLLOWERS_ENABLED` en `include/config/overworld.h`, que ahora vale `FALSE`.
    - Los sprites de mapa de todos los Pokémon ya están: `OW_POKEMON_OBJECT_EVENTS` vale `TRUE`.
    - En el mismo archivo hay opciones para afinarlo:
      - que salga de su propia Ball;
      - que se balancee al andar;
      - un flag para esconderlo durante un rato (`B_FLAG_FOLLOWERS_DISABLED`).
  - **Lo que habría que revisar:**
    - **Escenas de la historia:** la expansion avisa de que algunos scripts pueden necesitar retoques para que el Pokémon no estorbe, por ejemplo cuando un NPC camina hacia ti. Habría que pasar la historia viendo que no se queda nada atascado.
    - **Textos:** al hablar con él dice frases según su humor y el sitio. Son unos 138 textos en inglés, en `src/data/text/follower_messages.h`, y habría que traducirlos.
    - **Con el locke:** si el primero del equipo se debilita y se va a la caja de muertos, el que te sigue pasa a ser el siguiente. Hay que comprobar que ese cambio no se lía.
    - **Memoria de vídeo:** con muchos Pokémon en pantalla a la vez puede faltar memoria de vídeo. Con uno solo no debería haber problema.
  - **Dificultad:** baja para activarlo y probarlo. La traducción y la revisión de las escenas llevan más tiempo.
- **Estado:** Pendiente.

### 7. NPC nuevos que sean colegas nuestros

- **Qué:** añadir personajes **nuevos** por el mapa que sean colegas nuestros. Pueden estar en ciudades y rutas para charlar, como entrenadores para combatir o con algún guiño entre nosotros. Es distinto de la idea 4, que cambia a los NPC que ya existen y dan regalos.
- **Propuesta de:** Miguel, 26/10/2026.
- **Notas (viabilidad, sin planificar):**
  - **NPC que solo habla: fácil.**
    - Se añade un personaje al `map.json` del mapa, con su posición, su sprite (`graphics_id`) y su script.
    - El script con su texto va en el `scripts.inc` del mapa.
    - Cada mapa tiene un límite de personajes, pero en casi todos sobra sitio.
  - **Como entrenador: medio.** Además del NPC, hace falta:
    - el entrenador en `src/data/trainers.party`, con su nombre, clase, equipo y niveles;
    - meterlo en la tabla de niveles de su tramo (`reescalar_niveles.py`);
    - tener en cuenta que el randomizer también le cambiará el equipo, como a todos.
  - **Aspecto:** igual que en la idea 4. Lo más fácil es elegir un sprite que ya exista; también se puede recolorear o dibujar uno nuevo.
  - **Versiones:** encaja con la idea 5, como parte de la versión personalizada.
  - **Qué tendrían que pasar Jorge y Miguel:**
    - la lista de colegas;
    - en qué sitio va cada uno;
    - qué dice o qué equipo lleva.
- **Estado:** Pendiente.

### 8. Nombres del jugador y motes más largos

- **Qué:** que quepan nombres más largos. Ahora el nombre del jugador tiene un máximo de 7 letras y "JORGEMORI" (9) no cabe. Para la versión general; en la personalizada (idea 5) el nombre ya vendría puesto.
- **Propuesta de:** Jorge, 27/10/2026, al empezar el locke (se ha tenido que poner "JORGE").
- **Notas (viabilidad, sin planificar):**
  - **Motes de los Pokémon: ya caben 12 letras** (`POKEMON_NAME_LENGTH` = 12 en la expansion; en el Esmeralda original eran 10). Subirlo más es difícil: el mote se guarda dentro de cada Pokémon y cambiaría el tamaño de todos los Pokémon guardados (equipo y cajas). No parece que haga falta.
  - **Nombre del jugador: dificultad media.**
    - Es `PLAYER_NAME_LENGTH` (7) en `include/constants/global.h`, y se usa en unos 170 sitios: partida guardada (`SaveBlock2`), ficha de entrenador, Salón de la Fama, programas de la tele, mezcla de récords, Frente Batalla…
    - Subirlo a 10-12 cambia la partida guardada, así que las partidas de antes dejarían de servir. Se haría para el siguiente locke, no a mitad de uno.
    - Hay que revisar que el nombre largo quepa en los textos (diálogos con `{PLAYER}`, ficha, menú de guardar) y en la pantalla de poner nombre.
    - Las estructuras de los juegos por cable y la mezcla de récords guardan el nombre con tamaño fijo. Como no jugamos por cable, se pueden dejar o recortar al copiar.
  - El nombre del rival (Aura/Bruno) y los de las cajas del PC no hace falta tocarlos.
- **Estado:** Pendiente (para el siguiente locke).

### 9. Las formas Gigamax como megaevoluciones

- **Qué:** como el Dinamax no se usa, que las formas Gigamax sean megas con su megapiedra. Kingler no tiene mega: se le da una "Kinglerita" y megaevoluciona a su forma Gigamax. Lo hace el Pokémon Añil.
- **Propuesta de:** Miguel, 15/11/2026.
- **Notas (viabilidad, mirado en el código el 15/11/2026):**
  - **Se puede, y el motor lo pone fácil.**
    - Cada forma Gigamax ya es una especie (`SPECIES_KINGLER_GMAX`…), con sus sprites de frente, de espaldas e icono.
    - Una mega es una línea en la tabla de cambios de forma de la especie (`src/data/pokemon/form_change_tables.h`): `{FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM, SPECIES_KINGLER_GMAX, ITEM_KINGLERITE}`.
  - **Cuáles:** hay 32 formas Gigamax.
    - **Ya tienen mega (4):** Venusaur, Charizard, Blastoise y Gengar.
    - **Legendarios o singulares (2):** Urshifu y Melmetal.
    - **Megas nuevas (26):** Butterfree, Pikachu, Meowth, Machamp, Kingler, Lapras, Eevee, Snorlax, Garbodor, Rillaboom, Cinderace, Inteleon, Corviknight, Orbeetle, Drednaw, Coalossal, Flapple, Appletun, Sandaconda, Toxtricity, Centiskorch, Hatterene, Grimmsnarl, Alcremie, Copperajah y Duraludon.
  - **Qué hay que hacer:**
    1. **Estadísticas, tipo y habilidad de cada mega.** Las formas Gigamax tienen las mismas que la forma normal. Hay que decidirlas (lo normal en una mega: +100 de estadísticas base y una habilidad que pegue con su movimiento Gigamax). Es la parte de diseño, y es de Miguel.
    2. **26 megapiedras nuevas:** constante, nombre, descripción e icono (se puede reutilizar el de otra megapiedra cambiando los colores).
    3. **Marcar las formas como megas** (`isMegaEvolution`) y quitarles `isGigantamax`, y la línea de la tabla de cambios de forma.
    4. **Colocarlas en el mapa** con `colocar_objetos.py`. Quedan flags libres para 26: 0x043-0x04F, 0x2B7-0x2BB y 0x4CA-0x4E4.
    5. **Bolsillo de megapiedras:** caben 100 y habría 107 que se pueden conseguir. Hay que subirlo a 130. `bagMegaStones` es lo último de `SaveBlock3` y sobra sitio (usa 644 de 1624 bytes), así que en principio las partidas guardadas siguen valiendo; hay que comprobarlo.
    6. **Randomizer y guía:** el randomizer saca las megas de la tabla de cambios de forma, así que los jefes podrían llevar las nuevas sin tocar nada. La Pokédex de la guía también las saca del código.
  - **Dificultad:** media. Lo que más lleva es decidir las 26 megas.
  - **Partidas en curso:** con megas nuevas, el as con mega de algunos jefes puede cambiar (hay más donde elegir). Mejor para un locke nuevo, o comprobar con las semillas qué cambia.
- **Estado:** Pendiente.

### 10. Interfaces y opciones del motor que tenemos apagadas

- **Qué:** la expansion trae cosas hechas que no usamos. Activarlas es barato y cambia bastante cómo se ve el juego.
- **Propuesta de:** Miguel, 15/11/2026 ("interfaces más chulas, actualizadas").
- **Notas (repaso de `include/config/` del 15/11/2026):**
  - **Pokédex estilo HeartGold/SoulSilver** (`POKEDEX_PLUS_HGSS`): dentro del juego, para cada Pokémon, estadísticas base, movimientos por nivel y por MT, evoluciones y formas.
    - Con el randomizer enseñaría los movimientos al azar de cada especie. Es muy útil, o un destripe, según se mire.
    - Tiene 97 textos en inglés que habría que traducir.
  - **Tipos del rival en combate** (`B_SHOW_TYPES`): iconos de tipo junto a la barra de vida al elegir el movimiento. Con Pokémon de 9 generaciones ayuda mucho. La eficacia del movimiento ya sale (`B_SHOW_EFFECTIVENESS`), pero solo con especies que ya has visto.
  - **Descripción del objeto al recogerlo** (`OW_SHOW_ITEM_DESCRIPTIONS`): sale la imagen y qué hace. Con los objetos del suelo al azar, viene muy bien. El modo "siempre" no toca la partida guardada; el de "solo la primera vez" sí.
  - **Carteles de zona estilo Blanco/Negro** (`OW_POPUP_GENERATION`): el nombre de la ruta en una banda arriba, en negro o en blanco, con la hora si se quiere.
  - **Combates más rápidos** (`B_WAIT_TIME_MULTIPLIER`, `B_FAST_INTRO_NO_SLIDE`): menos pausa en los textos y sin la entrada deslizante.
  - **Huir de los entrenadores** (`B_RUN_TRAINER_BATTLE`): está **activado**, y huir cuenta como perder el combate, o sea, perder el locke. Mejor quitarlo para que no pase por error.
  - **Ya están:** ventana de información del movimiento (botón L), última Ball con R, icono de categoría, día y noche, IVs y EVs en la pantalla de datos.
  - **Más grande:** el Pokémon que te sigue (idea 6) y el DexNav. Y lo que no trae el motor (pantalla de datos estilo Blanco/Negro, menú de pausa a pantalla completa) son ramas de otra gente que habría que integrar: más difícil y con más riesgo.
- **Estado:** Hecho en el #78 (Miguel, 16/11/2026), menos el Pokémon que te sigue y el DexNav. Falta compilarlo y probarlo.

