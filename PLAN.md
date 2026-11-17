# Plan: hacer la ROM ya y seguir con los biomas (Miguel → Jorge, 17/11/2026)

**Para Jorge y para su Claude.** Este es el punto de partida para seguir con el trabajo de las zonas sin tener que leer toda la conversación de Miguel. Está escrito para que Claude lo siga paso a paso.

Antes de empezar, Claude tiene que leer:
- `DUALOCKE.md`: sobre todo "Al añadir una zona nueva" y "Dibujar mapas como los del juego: `autotile.py`";
- `ZONAS.md`;
- `PRUEBAS.md`;
- el registro de cada zona en `registro/`.

---

## 1. Dónde estamos

### Lo que ya está hecho (todo compila en GitHub)

- **Zonas nuevas, cada una con su zona de captura, su guardián y sus objetos:**
  - ISLAS DEL FERRY (una por medalla);
  - GRUTA ÍGNEA;
  - ISLA NEVADA;
  - DESIERTO PROFUNDO y RUINAS ARENOSAS;
  - MARISMA AZULIZA;
  - BOSQUE FRONDOSO y MANSIÓN OLVIDADA;
  - las tres islas del sur (ISLA DE RUINAS, ISLA VOLCÁNICA e ISLA ARENOSA);
  - PLAYA VOLCÁNICA;
  - CUMBRE METEORO.
- **Rediseños** (`autotile.py`, mirando cómo están hechos los mapas originales): la marisma, la playa, el bosque, las islas del sur y la ISLA NEVADA. Los guardianes ya no se repiten.
- **Biomas por tipo:** el BOSQUE SINIESTRO (Siniestro, tramo 6) y la CIÉNAGA TÓXICA (Veneno, tramo 3).
- **Arreglos de compilación** (las PR fallaban en GitHub desde la #78):
  - la línea en blanco que faltaba en `trainers.party`;
  - un texto de la Pokédex partido en dos líneas;
  - dos descripciones de megapiedra demasiado largas;
  - la prueba del tamaño de la partida guardada;
  - los objetos ocultos con un flag de menos de 0x1F4.
- **Accesos a las islas:** la #100 (sobre la #99) abre paso en las rocas para llegar surfeando a la ISLA ARENOSA, la ISLA DE RUINAS, la ISLA VOLCÁNICA y la ISLA NEVADA. Ver la sección 2.

### Las PR

| PR | Qué es | Estado |
| --- | --- | --- |
| **#99** (Jorge) | Junta todo lo de Miguel hasta la #98 (sustituye a la #85), con los arreglos para las partidas en curso | Compila y pasa las pruebas |
| **#100** (Miguel, base #99) | Paso abierto a las islas y este plan | Ver su CI |
| #78-#98 (Miguel) | Las PR sueltas; la #99 ya las lleva todas | Compilan y pasan las pruebas |
| #76, #77, #97 (Jorge) | Tus PR (IA, versión 7, entrenadores alcanzables + `alcance.py`) | Las decides tú |

---

## 2. Hacer la ROM para jugar (lo primero)

1. **Fusionar la #99 en `master`.** Lleva todo lo de Miguel hasta la #98. Después se pueden cerrar sin fusionar la #78-#98 y la #85, porque ya van dentro.
2. **Fusionar la #100**, que va encima de la #99. Sin ella, a cuatro islas no se llega, o solo buceando.
   - Si la #99 ya está fusionada, GitHub cambia la base de la #100 a `master` solo.
   - Si no, se cambia a mano.
3. **Tus PR #76, #77 y #97**, como las tengas pensadas. La #97 trae `tools/dualocke/alcance.py`, que hace falta para el paso 5 de la receta de la sección 4.
4. **Compilar:** `powershell -ExecutionPolicy Bypass -File tools\dualocke\instalar_windows.ps1`, como siempre (`DUALOCKE.md`, sección 3).
   - El CI de GitHub (`.github/workflows/build.yml`) compila la ROM con `make release`, pero **no la sube**. Así tiene que ser: el repo es público y no se suben ROMs.
5. **Jugar con `PRUEBAS.md`.** Tiene una sección por zona nueva con lo que hay que mirar:
   - uniones con las rutas;
   - riscos de un solo sentido;
   - guardianes y su premio;
   - carteles y zonas de captura;
   - salvajes.

   Lo que se encuentre, en un PR de arreglos.

**Partidas en curso:** según la #99, con las dos semillas de la versión 7 no cambia nada de lo ya visto. Las zonas nuevas van al final de todas las listas.

---

## 3. Lo siguiente: los biomas que faltan

### Por qué

Análisis de los salvajes sin semilla:
- **Familias:** se pueden capturar 200 de 614 (sin legendarios ni megas).
- **Tipos sin zona propia:** Lucha, Acero, Dragón, Planta, Hada, Eléctrico, Psíquico… (cuento las zonas donde el tipo es al menos el 20 % de lo que sale).
- **Ya hechos:** Siniestro (BOSQUE SINIESTRO) y Veneno (CIÉNAGA TÓXICA).

### Las propuestas que quedan

Salen del mapa de propuestas (letras A-I). Antes de empezar cualquiera, hay que comprobar el acceso con `alcance.py` (paso 5 de la receta): los bordes "libres" de las rutas de mar suelen estar fuera de la barrera de rocas.

| | Bioma | Tipo | Dónde | Tramo | Cómo se entra / ojo con |
| --- | --- | --- | --- | --- | --- |
| A | Isla Dojo | Lucha (y Roca) | Al sur de PUEBLO AZULIZA | 2 | El borde sur de AZULIZA tiene 12 casillas de arena pisables (x 3-19). Gráficos de AZULIZA: arena, rocas y árboles de playa. Tema: el gimnasio de Lucha de MARCIAL. |
| B | Mina abandonada | Acero (y Tierra) | Al oeste de CIUDAD FÉRRICA (Devon) | 1-2 o 6 | El borde oeste de FÉRRICA es agua (haría falta SURF, tramo 6). Para que sea temprana: una **cueva** en una pared, como la CUMBRE METEORO (RUTA 116 o la de FÉRRICA). Interior de cueva o de la GUARIDA MAGMA. |
| C | Prado de las Hadas | Hada (y Planta, Bicho) | Al norte de la RUTA 117 | 3 | Borde norte de la 117, pisable en x 38-59. Flores y hierba, gráficos de Malvalona. Va junto a la CIÉNAGA (que está al sur de la misma ruta). |
| E | Central de la tormenta | Eléctrico (y Acero) | Al sur de la RUTA 118 | 6 | Borde sur, agua en x 0-12: con SURF, que en el tramo 6 ya se tiene. Clima de tormenta (`WEATHER_RAIN_THUNDERSTORM`). Por dentro, una central abandonada: interior de NUEVA MALVALONA. |
| G | Selva de ARBORADA | Planta (y Bicho) | Al sur de CIUDAD ARBORADA | 6 | Borde sur de ARBORADA, 7 casillas pisables (x 9-36). Gráficos de ARBORADA: tienen la hierba muy alta con su borde, que en Malvalona no existe. |
| H | Santuario astral | Psíquico (y Hada) | Al este de la RUTA 125, junto a ARRECÍPOLIS | 7 | Borde este, agua. **Mirarlo con `alcance.py`** antes: puede estar fuera de las rocas. Isla con ruinas y niebla. |
| I | Abismo del dragón | Dragón | Al sur de la RUTA 129 | 8 | **Mirarlo con `alcance.py`**: el borde sur de la 129 parece abierto, pero hay que comprobarlo. |

Recomendación de Miguel: seguir por **E (Eléctrico)** o **A (Lucha)**, que son los tipos con menos zonas.

### Límites que hay que tener en cuenta

- **Zonas de captura:** 118 de 128 → caben **10 más**. Cada bioma usa una.
- **Entrenadores:** **864 de 864, no queda ninguno libre.** Las zonas nuevas se están haciendo sin entrenadores (con un personaje que habla).
  - Para tener entrenadores hay que **agrandar la lista** (`TRAINERS_COUNT`). Eso mueve los flags del sistema y **rompe las partidas guardadas**.
  - La otra opción es reutilizar revanchas (`_2` a `_5`).
  - Es una decisión para cuando se empiece una partida nueva (versión 8).
- **Flags:** ya no quedan bloques seguidos; cada zona coge flags sueltos.
  - Libres que no son de Jorge: 0x068, 0x0E9, 0x1DA, 0x1E0, 0x2D9 y 0x4FF.
  - Del sistema: 0x8F4, 0x8F5, 0x8FD-0x8FF, 0x905-0x907, 0x913 y 0x91B. No usar 0x91F: lo usa `DAILY_FLAGS_START`.
  - **Los objetos ocultos necesitan un flag de 0x1F4 en adelante** (`FLAG_HIDDEN_ITEMS_START`); si no, no compila. `comprobar_zonas.py` ya lo avisa.
  - Los de 0x043-0x04F, 0x2B6-0x2BB y 0x4CA-0x4E4 se dejaron para Jorge.

---

## 4. Receta para hacer un bioma nuevo

Así se hicieron el BOSQUE SINIESTRO (`tools/dualocke/crear_bosque_siniestro.py`) y la CIÉNAGA TÓXICA (`crear_cienaga_toxica.py`). Lo más fácil es copiar uno de los dos.

1. **Elegir el borde** de una ruta por el que se entra. Ese borde tiene que:
   - ser pisable o surfeable;
   - estar **dentro** de lo que se alcanza (`alcance.py`);
   - estar lejos de las conexiones con otros mapas.

   El mapa nuevo usa **los mismos gráficos que esa ruta**: si no, la unión se ve rota.
2. **Dibujar el plano con letras** (`PLANO`) y pintarlo con `autotile.py`. Reglas aprendidas:
   - **Árboles normales de Hoenn:** `at.arbol_normal()` y `at.copa_normal()`. La copa del árbol de debajo se pinta en la casilla de encima.
   - **La fila 0 del mapa nuevo sigue a la última de la ruta:** donde la ruta tiene copas de árbol (0x00E, 0x00F, 0x025), debajo tiene que haber árbol. Las casillas de la entrada se cambian a hierba en la ruta. El script lo comprueba con `assert`.
   - **Charcas:** rectas, sin escalones abajo; con escalones quedan esquinas sin orilla. Con un margen de hierba normal hasta la hierba alta y los árboles.
   - **La arena no toca la hierba:** tiene que haber agua o un risco entre las dos.
   - **La hierba muy alta** (0x015) solo tiene borde con los gráficos de ARBORADA.
   - **El prefijo de la carpeta del mapa nuevo va en `NUEVOS`** de `autotile.py`. Si no, el autotile aprende del propio mapa y la revisión de piezas da 0 sin serlo.
   - `Aprendiz.revisar()` cuenta las parejas de piezas que el juego no usa. Hay que mirarlas en la foto (`ver_mapa.py`): unas pocas son normales.
3. **Lo que hace el script** (copiar de los dos de arriba):
   - el mapa y el layout;
   - la conexión en los dos mapas;
   - el grupo de mapas (al final);
   - la zona de captura al final de `region_map_sections.json` y `HOENN_EXTRA_MAPSEC_LAST`;
   - el cartel en los dos temas de `map_name_popup.c`;
   - el flag del guardián;
   - el `.include` en `data/event_scripts.s`;
   - los scripts del guardián y del personaje;
   - `SITIO_OBJETOS` para poner los objetos en su sitio.
4. **Apuntar la zona en las herramientas:**
   - **`reescalar_niveles.py`:** el tramo en `TRAMOS` y el guardián, regla `"tope"`.
   - **`zonas_nuevas.py`:** los salvajes, ya evolucionados para el nivel del tramo. Tierra, 12; agua, 5; pesca, 10.
   - **`colocar_objetos.py`:** sus grupos, con flags sueltos. El oculto, de 0x1F4 en adelante.
   - **`aleatorio/estaticos.py`:** `MAPAS_ISLAS`, para que con semilla salga otro guardián.
   - **`aleatorio/zonas.py`:** `PREFIJOS` y `FLAGS_OBJETOS` (ver "Al añadir una zona nueva" en `DUALOCKE.md`). Si no, cambian los objetos de las partidas en curso.
   - **`guia.py`:** su tramo.
5. **La cadena**, en este orden:
   1. `reescalar_niveles.py`
   2. `zonas_nuevas.py`
   3. `equipos_jefes.py`
   4. `evolucionar_entrenadores.py`
   5. `ia_entrenadores.py`
   6. `colocar_objetos.py`
   7. el `crear_*.py` de la zona otra vez (para `SITIO_OBJETOS`)

   **`trainers.party` no se toca a mano nunca.**
6. **Comprobar:**
   - `comprobar_zonas.py` con 0 fallos;
   - `alcance.py`: que se llega a la zona en su tramo, y que desde el guardián se vuelve a la entrada si hay riscos;
   - fotos con `ver_mapa.py`.
7. **Documentar:**
   - en `DUALOCKE.md`, una sección con la zona y otra línea en "Guardianes únicos";
   - una sección en `PRUEBAS.md`;
   - la línea "Opcional" y la tarjeta en `GUIA.html`;
   - el registro en `registro/AAAA-MM-DD-nombre-tema.md`.
8. **Rama y PR:** una rama por zona y commits pequeños en español. **El CI tiene que pasar** (`build-emerald`, `release` y `test`); si falla, el log está en la pestaña Actions.

Los textos van en español, con lenguaje neutro (sin dar por hecho el género de quien juega), y no se copian textos de Heart & Soul.

---

## 5. Otras mejoras para más adelante

- **Probar en el emulador todo `PRUEBAS.md`.** Es lo que más falta: nada de lo de las zonas se ha jugado todavía.
- **Pulir las uniones que quedan raras**, cuando se vean jugando:
  - 16 parejas de piezas en las curvas del camino de barro de la CIÉNAGA;
  - la unión de la playa de la ISLA DE RUINAS;
  - el pie de las peñas pequeñas.
- **Entrenadores en las zonas nuevas:** decidir si en la versión 8 se agranda la lista (partida nueva) o se reutilizan revanchas.
- **Más familias capturables sin semilla:** cada bioma nuevo suma 10-15 especies. Con los 7 que quedan se pasaría de 200 a unas 280 familias.
- **`alcance.py` y las islas, ahora que se llega a ellas.** Con la #100, la herramienta marca "por encima" a DARÍO (ISLA ARENOSA) y a DUDLEY, KAYLEE y NIEVES (ISLA NEVADA): dice que se alcanzan en el tramo 6.
  - Es lo mismo que pasa con los entrenadores de la RUTA 124, que no se marcan porque `MAP_ROUTE12[4-9]` y `MAP_ROUTE13[0-4]` están en `POR_HISTORIA` (la historia no deja ir antes).
  - Las islas cuelgan de esas rutas, pero no están en la lista. Hay que añadirlas a `POR_HISTORIA`: `MAP_ISLA_NEVADA*`, `MAP_ISLA_ARENOSA`, `MAP_ISLA_DE_RUINAS*` y `MAP_ISLA_VOLCANICA*`.
  - Los de la RUTA 111 y la RUTA 118 que también salen ya los trata la #97.
