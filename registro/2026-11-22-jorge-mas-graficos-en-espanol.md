# 22/11/2026 — Jorge (con Claude): más gráficos en español y descripciones que se saltaban

Rama `jorge/mas-graficos-en-espanol`, sacada de `jorge/textos-en-ingles` (#120) porque usa su herramienta: hay que fusionar antes el #120.

## Gráficos (con `tools/dualocke/textos_graficos.py`)

- **Pantalla de datos:** PERFIL, HABILIDAD, NOTAS ENTRENADOR, ESTADO (huevo), OBJETO, CARACT., MOVIMIENTOS, EFECTO, DESCRIPCIÓN. EXP. y AMISTAD ya estaban.
  - Con los IV/EV activados, el juego usa `iv_ev_tiles.png` y no `tiles.png`. Son iguales salvo los tiles 218-223, y la herramienta copia los cambios a los dos.
  - La etiqueta de CARACT. la vuelve a poner el código (`WriteToStatsTilemapBuffer`, tiles 169-172) al pasar entre estadísticas, IV y EV, y borra lo que hay detrás. Por eso va con la letra más estrecha, para que quepa en esos 4 tiles. NOTAS ENTRENADOR también, para no pasar del sitio de "TRAINER MEMO".
  - **Cuidado con los tiles "libres":** el código pinta tiles que no salen en ningún tilemap (rellenos de un color, los corazones de los concursos, la etiqueta de IV/EV). Al principio se tomaron como libres los tiles 1, 9 y 10, y salía una fila de "R" debajo del Pokémon. Ahora, en esta pantalla, solo se toman tiles vacíos del final (234-239), y solo hacen falta dos, para el acento de DESCRIPCIÓN.
- **Iconos de tipo** (32 píxeles, caben unos 30): BICHO, SINIE., DRAGÓN, ELÉCT., HADA, LUCHA, FUEGO, VOLAD., FANT., PLANTA, TIERRA, HIELO, VENENO, PSÍQ., ROCA, ACERO, ASTRAL y AGUA. NORMAL y ??? se quedan como estaban. Las categorías de concurso (BELLEZA, CARISMA, DULZURA, INGENIO, DUREZA) van con la fuente pequeña más estrecha del juego.
- **Combate:** el botón de la descripción del movimiento pone INFO / MOV. (antes MOVE / INFO).
- **Pantalla de nombres (motes):** BORRAR (antes BACK), B BOTÓN, y las pestañas del teclado ABC / abc / otros. MAYÚS no cabe con el acento en 8 píxeles de alto.
- Herramienta: fuentes `small_narrow` y `small_narrower`; si un texto no cabe con la normal o la pequeña, prueba la estrecha. `acento_pegado` baja los acentos una fila en las barras con poco alto. Nuevas letras hechas a mano: M, V, F y el punto (de MOVE INFO) y las de "BUTTON".

## Descripciones que seguían en inglés

En combate, la descripción de Surf salía en inglés. Había **70 movimientos, 28 objetos y 10 habilidades** sin traducir: su texto tiene un `#if` dentro (cambia según la generación) o una macro (`BINDING_TURNS`), y `aplicar_descripciones.py` se los saltaba sin avisar. Entre ellos hay muchos que salen todo el rato:
- movimientos: Surf, Cascada, Rayo Hielo, Ventisca, Hiperrayo, Triturar, Desarme…;
- objetos: Superpoción, Hiperpoción, todos los objetos X, la Buceo Ball, las MT de Rayo Hielo y Ventisca, y las MO de Surf y Cascada.

- Se han traducido los que faltaban (50 movimientos, 28 objetos y 10 habilidades, `propia` en los CSV), según la configuración activa: generación más reciente, ataques que atrapan "4 o 5 turnos", y granizo y nieve los dos.
- `aplicar_descripciones.py` ya los reconoce. Como un `#if` no puede ir dentro de `ES()`, quedan así: `#if TESTING <la original> #else <la española> #endif`, con un comentario de marca para no volver a tocarlos. Se puede volver a lanzar y no cambia nada (comprobado).
- Hay tres que tienen dos `.description` enteras dentro de un `#if` (Tri Ataque, Carga y Roca Helada); llevan la misma traducción en las dos.

## Comprobado

- En el emulador, con la ROM de pruebas:
  - un combate (INFO MOV., y la descripción de Surf en español);
  - una captura (la pantalla de mote, con las tres pestañas);
  - la pantalla de datos (las tres páginas, cambiando a IV y EV y volviendo);
  - los iconos de tipo.
- `make`, `make check` entero y las comprobaciones de Python del CI. Las paletas y el formato de los PNG no cambian.

## Queda en inglés

- PRESS START en la pantalla de título: es una letra metalizada propia y habría que dibujar a mano la U y la L. Sale una vez al encender.
