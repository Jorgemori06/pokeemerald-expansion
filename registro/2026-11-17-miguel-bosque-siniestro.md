# 17/11/2026 — Miguel: compilación arreglada, biomas por tipo y BOSQUE SINIESTRO

## Qué se pidió

1. "Vamos a chequear que todo funcione bien, que la ROM nueva compile…"
2. Saber si en el juego hay biomas para todos los tipos, y opciones de sitios libres para añadir biomas (bosque siniestro, veneno, hielo, psíquico…), enseñadas en el mapa.
3. De las opciones, Miguel eligió el **Bosque siniestro (F)**.

## 1. La compilación

El repo compila la ROM en GitHub con cada PR (`.github/workflows/build.yml`). Desde la #78, **todas las PR fallaban**. Como solo compilaba Jorge, no se había visto. Había tres fallos:

- **#82 a #95:** `trainers.party` no tenía línea vacía antes del primer entrenador nuevo (ROQUE; más arriba en la pila, NIEVES y luego SEBAS), y trainerproc se paraba ("expected empty line").
  - Se arregló en `zonas_nuevas.py`, que ahora pone la línea siempre (`separar_bloques()`).
  - El arreglo se llevó por toda la pila fusionando cada rama en la de encima, sin reescribir la historia.
  - Con la #82 la ROM ya compila en GitHub.
- **#78 (opciones del motor):** un texto de la Pokédex tenía un salto de línea real dentro de las comillas. Arreglado.
- **#79 (megas y gigamax):** la ROM compilaba, pero fallaban dos pruebas automáticas:
  - **Corviknightita:** su descripción inglesa no cabía en la mochila (103 px de 102). Ahora el generador escribe "This stone lets X Mega" con los nombres largos.
  - **Partidas guardadas:** la prueba del tamaño de la partida no sabía que el bolsillo de megapiedras pasa de 100 a 130. Las partidas de antes valen: los huecos nuevos van al final de SaveBlock3 y, al guardar, el sector se llena de ceros antes de copiar, así que salen vacíos.

## 2. Biomas por tipo

Análisis de los salvajes sin semilla:

- **Familias:** se pueden capturar 200 de 614 (sin legendarios, megas ni formas).
- **Tipos con pocas zonas propias** (zonas donde el tipo es al menos el 20 % de lo que sale):
  - **Lucha, Acero y Dragón:** 2 cada uno.
  - **Planta, Hielo y Hada:** 3 cada uno.
  - **Eléctrico y Bicho:** 4 cada uno.
  - **Siniestro:** solo Poochyena por las rutas.
  - **Veneno:** sale en muchas zonas, pero solo por Zubat y Tentacool.
- **Sitios libres:** se miraron los bordes de mapa sin conexión y desde dónde se llega a ellos. En `fotos_zonas/13_propuestas_biomas.png` hay 9 propuestas:
  - A, Isla Dojo (Lucha);
  - B, Mina abandonada (Acero);
  - C, Prado de las Hadas (Hada);
  - D, Ciénaga tóxica (Veneno);
  - E, Central de la tormenta (Eléctrico);
  - F, Bosque siniestro (Siniestro);
  - G, Selva de ARBORADA (Planta);
  - H, Santuario astral (Psíquico);
  - I, Abismo del dragón (Dragón).
- **Límites:**
  - quedan 11 zonas de captura (ya contando el bosque);
  - no queda ningún hueco de entrenador;
  - los flags libres ya no van en bloques seguidos.

## 3. BOSQUE SINIESTRO

- **Entrada:** borde sur de la RUTA 123 (x 103-106), al pie del MONTE PÍRICO. Las copas de árbol de esas cuatro casillas pasan a ser hierba. Tramo 6.
- **El mapa** (50 × 44) lo crea `tools/dualocke/crear_bosque_siniestro.py`:
  - árboles normales de Hoenn y lo demás pintado con `autotile.py`;
  - a la sombra, con la música del MONTE PÍRICO;
  - un claro con una bruja, una charca, un risco que se salta y un bosque profundo con el claro del guardián.
- **Guardián:** Hydreigon (sin semilla), premio Tabla Pavor. Flag 0x91E.
- **Salvajes:** Siniestro, Fantasma y Bicho.
- **Objetos:** 3 objetos y un Ticket-Recuerdo, en flags sueltos.
- **Zona de captura propia:** 117 de 128.
- **Otros scripts:** el bosque está apuntado en `reescalar_niveles.py`, `zonas_nuevas.py`, `colocar_objetos.py`, `aleatorio/estaticos.py` y `guia.py`.

## Cómo se comprobó

- **`comprobar_zonas.py`:** 0 fallos (957 mapas).
- **Parejas de piezas que el juego no usa:** 2 (la punta del risco junto a un árbol, y dos copas distintas juntas).
- **Alcance:** desde la entrada se llega al guardián, a la bruja y a los cuatro objetos. Desde el claro del guardián se vuelve a la entrada sin subir el risco.
- **La unión con la RUTA 123:** se miró en una foto de las dos juntas, y los árboles siguen.
- **La cadena de niveles, salvajes y objetos:** vuelta a lanzar entera. Solo cambia lo del bosque.
- **Compilación:** la de GitHub la hará el CI de la PR.

## Pendiente

- Que el CI de la PR compile y pase las pruebas.
- Probarlo en el juego (`PRUEBAS.md`, BOSQUE SINIESTRO).
- Elegir el siguiente bioma.
