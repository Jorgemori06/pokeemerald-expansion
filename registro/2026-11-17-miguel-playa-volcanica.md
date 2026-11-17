# 17/11/2026 — Miguel: PLAYA VOLCÁNICA

## Qué se pidió

Miguel: "Mt Pyre beach". Es la propuesta 10 de ZONAS.md: una playa volcánica pegada a la RUTA 122, con arena, aguas termales, rocas volcánicas y sol.

## Qué se ha hecho

- **`tools/dualocke/crear_playa_volcanica.py`** (se puede volver a lanzar) hace la playa, la abre en la RUTA 122 y la conecta. Tramo 7.
- **Paso:** la RUTA 122 está rodeada por un anillo de rocas sin huecos. Se quitó una roca de arriba a la izquierda para salir por el noroeste.
- **Gráficos de LAVACALDA** (ceniza, termas, árboles de ceniza), aunque la RUTA 122 usa otros. Para que la unión se vea bien:
  - se cruza por la parte de la ruta donde solo hay gráficos generales;
  - el borde de la playa es solo de mar y rocas generales;
  - una fila de rocas no deja acercarse al borde donde se verían gráficos de la otra ruta.
  - El script comprueba las dos cosas.
- **La playa:** mar, arena con orilla, ceniza con salvajes, árboles de ceniza y dos pozas termales (de adorno).
- **Guardián en la arena:** Gyarados a nivel 70 sin semilla. Hay también un bañista que cuenta cosas.
- **Zona de captura propia** (115 de 128), salvajes, 3 objetos y un Ticket-Recuerdo.
- **Documentación:** `DUALOCKE.md`, `PRUEBAS.md` y `GUIA.html`.

## Problemas encontrados y arreglados al hacerlo

- **Suelo con colisión:** el suelo de ceniza (0x271) se cogía de la primera vez que sale en el MONTE CENIZO, que es la cima de una roca, con colisión. Habría dejado toda la playa sin poder pisarse. Ahora se coge el más común con la colisión que toca, y el script lo comprueba.
- **Termas:** las pozas de LAVACALDA tienen el borde de arriba dibujado sobre el acantilado y el de los lados sobre arena. Se pusieron pegadas al borde de arriba y con arena alrededor.
- **Bañista:** solo se entra en las termas por una escalera de arriba, así que el bañista va en la arena.
- **Objetos:** el script los ponía todos junto al guardián. Se movieron a mano.
- **Salvajes:** al probar se volvió a lanzar `reescalar_niveles.py` después de `zonas_nuevas.py`, y se borraron las tablas de las zonas nuevas. Se repitió la cadena en orden: hay que lanzarla siempre entera y en orden.

- **Guardianes de las islas del sur (#89):**
  - Los scripts de las zonas escriben el nivel del guardián fijo, y `reescalar_niveles.py` lo cambia luego al tope del tramo.
  - Al volver a lanzar `crear_islas_sur.py` después de la cadena, Metagross, Charizard y Tyranitar se quedaron a 70 en vez de 81, y así se subió el #89.
  - Arreglado en el #89 (commit aparte). Este PR añade la misma protección a `crear_playa_volcanica.py` y `crear_bosque_frondoso.py`: si el script ya existe, conservan el nivel que tenga. Sus guardianes ya estaban bien (Gyarados 70 y Gengar 20 coinciden con su tope).

## Cómo se comprobó

- **`comprobar_zonas.py`:** 0 fallos en 954 mapas (zonas 115 de 128).
- **Alcance:**
  - Desde dentro de la RUTA 122 se llega al borde oeste por las filas 0-13.
  - En la playa se llega a todo menos al agua de las pozas, también al guardián y al bañista.
- **Mapa:** dibujado junto a la RUTA 122.
- **Cadena de niveles:**
  - En `trainers.party` no cambia nada.
  - En `wild_encounters.json` solo se añade la tabla nueva al final.
- **No se ha compilado** (sin WSL).

## Pendiente

- Probarlo en el juego (`PRUEBAS.md`). Lo más delicado es la unión con la RUTA 122, porque los dos mapas tienen gráficos distintos.
