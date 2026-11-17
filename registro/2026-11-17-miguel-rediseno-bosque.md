# 17/11/2026 — Miguel: rediseño del BOSQUE FRONDOSO

## Qué se pidió

Después de rehacer la MARISMA AZULIZA y la PLAYA VOLCÁNICA (`registro/2026-11-17-miguel-rediseno-marisma-playa.md`), Miguel eligió la siguiente zona que mejorar con lo aprendido: "Bosque Frondoso".

## Qué se ha hecho

- **Mirando el BOSQUE PETALIA:**
  - los árboles forman franjas y grupos de distinto alto, con árboles sueltos;
  - la hierba alta va en manchas de borde irregular, con claros sin hierba entre ellas;
  - entre dos claros hay riscos cortos de un solo sentido (piezas 0x0D5, 0x087 y 0x0D6).
- **El mapa nuevo** (mismo tamaño, 36 × 40; la mansión y la entrada no se mueven):
  - Se dibuja con letras, una por casilla, y lo pinta `autotile.py`. Antes era una rejilla de parejas de casillas, con árboles en bloque y hierba alta casi por todo.
  - Tres franjas de árboles de distinto alto dividen el bosque en claros, unidos por pasos que no están en línea.
  - **El camino da la vuelta:** de la entrada se va al oeste, junto a la charca; se sube por el paso del oeste y se rodea el risco por el este hasta el paso que lleva al patio. De vuelta se puede saltar el risco.
  - Hay manchas de hierba alta, árboles sueltos, flores y una charca con un escalón.
- **Entrenadores:**
  - SEBAS, en el rodeo del risco: (25, 20), mira a la izquierda, ve 4 casillas.
  - OLIVIA, junto al paso de debajo de la charca: (9, 33), mira a la derecha, ve 4 casillas.
- **Objetos:** se quedan donde estaban (Polvo Plata, Raíz Grande oculta y el Ticket-Recuerdo): siguen en hierba alta a la que se llega.
- **Documentación:** `DUALOCKE.md`, `PRUEBAS.md` y `GUIA.html`.

## Problemas encontrados y arreglados al hacerlo

- **El cartel de la mansión no se podía leer:** se lee desde la casilla de abajo, y en el mapa viejo había un árbol. Ahora está en (22, 12), junto al paso, y el script comprueba que debajo no haya árbol.
- **La unión con el BOSQUE PETALIA:** a la derecha del pasillo (x 18-19) había hierba, y debajo, en el BOSQUE PETALIA, sigue un árbol sin copa. Ahora hay árboles que acaban en tronco, como al otro lado.
- **La charca escalonada** dejaba una esquina sin orilla. Se le dio una forma más sencilla (un solo escalón arriba).

## Cómo se comprobó

- **Parejas de piezas que el juego no usa:** 42, todas en el borde de la mansión copiada de CIUDAD FÉRRICA. En el bosque mismo no queda ninguna.
- **Alcance, con el risco de un solo sentido:**
  - De la entrada a la puerta de la mansión se llega en 53 pasos, y se vuelve igual.
  - Desde debajo del risco se sube rodeándolo.
  - Se llega a los dos entrenadores, al cartel y a los tres objetos.
- **`comprobar_zonas.py`:** 0 fallos (956 mapas).
- **No se ha compilado** (sin WSL).

## Pendiente

- Probarlo en el juego (`PRUEBAS.md`).
- Seguir con otras zonas si Miguel quiere.
