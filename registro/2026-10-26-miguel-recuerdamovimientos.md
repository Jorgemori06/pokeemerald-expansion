# 26/10/2026 — Miguel: recuerdamovimientos en los Centros Pokémon y Ticket-Recuerdo

## Qué se pidió

Un recuerdamovimientos en los Centros Pokémon, para recordar los movimientos que un Pokémon ha podido aprender durante la aventura. Que cobre con "Ticket-Recuerdo", repartidos por el mapa como objetos para recoger: bastantes, al menos uno por ruta.

## Qué se ha hecho

- **Ticket-Recuerdo:** es la Escama Corazón (`ITEM_HEART_SCALE`) con otro nombre, otra descripción y el icono del Ticket del Barco.
  - El tutor de PUEBLO PARDAL ya cobraba con la escama, así que también pide el ticket. Sus textos están cambiados en `18_ruta113_pardal.tsv`.
  - También están cambiadas las tablas de `traduccion/nombres` y `traduccion/descripciones`.
- **Recuerdamovimientos:** un PNJ en los 16 Centros Pokémon de Hoenn, en la casilla (13, 2), a la derecha del PC. Es una casilla libre en todos y no tapa el PC ni el mapa de la región.
  - Enseña los movimientos de nivel que el Pokémon ya podría saber, del equipo o de las cajas.
  - Gasta un ticket solo si el Pokémon aprende el movimiento.
  - Script nuevo: `data/scripts/dualocke_recuerda_movimientos.inc`. Los textos se midieron con la fuente del juego y caben.
- **Recordador gratis quitado:** el de la pantalla de datos (`P_SUMMARY_SCREEN_MOVE_RELEARNER` a `FALSE`). Si no, los tickets no servirían.
- **45 tickets por el mapa**, con `colocar_objetos.py`:
  - uno en bola en cada ruta, de la 101 a la 134;
  - otro oculto en 11 rutas largas.
- **Cambios en `colocar_objetos.py`:**
  - grupos con un objeto fijo, porque todos los tickets son el mismo objeto y el flag se nombra por la ruta;
  - busca primero suelo firme y solo después casillas como la del ancla (agua, puentes). Así, en las rutas de mar los tickets van a las playas si las hay.
    - Antes salían 16 en el agua, uno de ellos en un puente de la RUTA 110. Ahora solo 7, en rutas de mar abierto sin playa cerca. Se cogen haciendo Surf.
  - No cambia las megapiedras ni los objetos competitivos que ya estaban puestos: el script no toca lo que ya está en el mapa.
- **Flags:**
  - **De bola:** 0x021-0x042.
  - **Ocultos:** 0x4E5-0x4EF. Los ocultos tienen que ir por encima de `FLAG_HIDDEN_ITEMS_START` (0x1F4); si no, el macro `bg_hidden_item_event` da error al compilar.
  - El tope de los objetos competitivos baja a 0x4E4, que les sigue dejando hueco.
- **Randomizer:** los tickets (`FLAG_ITEM_TICKET_*`) son fijos, como las megapiedras (`FIJOS` en `aleatorio/objetos.py`).
- **Documentación:** `DUALOCKE.md` (sección 6, "Hecho", mapa del código y flags libres) y `PRUEBAS.md`.

## Cómo se comprobó

- **Repetir el script:** `colocar_objetos.py` se volvió a lanzar y no duplica nada (todo "ya está").
- **Casillas:** se miró, para cada ticket, el comportamiento y la altura de su casilla. Todas son suelo firme (hierba, arena, normal), salvo las 7 de mar.
- **Randomizer:** `buscar_suelo()` del randomizer ve los 45 tickets, cada uno con su flag, y todos como `ITEM_HEART_SCALE`.
- **Diálogos:** `dialogos.py comprobar` da 4715 textos y 0 errores.
- **Sin compilar:** en el PC de Miguel no hay compilador. Falta que Jorge pase `make check` y `make release`.

## Pendiente

- Que Jorge lo compile y lo pruebe: un Centro Pokémon, recoger tickets en una ruta de tierra, en una de mar y uno oculto. La lista está en `PRUEBAS.md`.
