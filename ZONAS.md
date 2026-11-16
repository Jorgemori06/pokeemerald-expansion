# Zonas nuevas y zonas que mejorar: análisis

Miguel, 16/11/2026: "islas (como las del Ultravuelo en Rubí Omega/Zafiro Alfa) en rutas de agua, mejorar el Sendero Ígneo, añadir zonas con climas más diversos (hielo, mejorar el desierto, ruinas…). Vamos a hacer un análisis de las rutas y luego empezamos a hacerlas."

Este documento es ese análisis: qué hay, dónde queda sitio, qué se puede hacer con lo que trae el juego y qué límites hay. Las zonas se irán haciendo una a una, cada una en su PR.

## 1. Cómo está Hoenn ahora

- **Mapa del mundo:** `python3 tools/dualocke/ver_mundo.py mundo.png 3` une los 49 mapas exteriores por sus conexiones (800 × 383 casillas) y escribe la posición de cada uno en `mundo.json`. Cada mapa suelto se ve con `tools/dualocke/ver_mapa.py`.
- **Las rutas de mar del este (124-134) son enormes y tienen poco:**

  | Ruta | Tamaño | Entrenadores | Objetos | Borde libre |
  | --- | --- | --- | --- | --- |
  | 124 | 80 × 80 | 9 | 5 | norte |
  | 125 | 80 × 40 | 9 | 3 | norte y este |
  | 126 | 80 × 80 | 8 | 3 | sur y oeste |
  | 127 | 80 × 80 | 8 | 6 | este |
  | 128 | 120 × 40 | 7 | 5 | — |
  | 129 | 80 × 40 | 5 | 1 | sur y este |
  | 130 | 80 × 40 | 3 | 2 | norte y sur |
  | 131 | 60 × 40 | 8 | 1 | norte y sur |
  | 132 | 80 × 40 | 8 | 3 | norte y sur |
  | 133 | 80 × 40 | 7 | 4 | norte y sur |
  | 134 | 80 × 40 | 9 | 3 | norte y sur |

  Las de tierra (110, 111, 119, 120, 123) tienen 12-23 objetos cada una.
- **Ya hay islas hechas que casi no se ven:** ISLA SUR (Latios/Latias), ISLA LEJANA (Mew), ISLA ORIGEN (Deoxys) y ROCA OMBLIGO (Ho-Oh/Lugia). Tienen mapa, zona propia en el mapa de la región y viaje en el ferry de CALAGUA, pero solo con un ticket de evento y después de la Liga. También la ISLA ESPEJISMO de la RUTA 130, que sale casi nunca.
- **Cuevas y ruinas ya hechas:** PASO DESÉRTICO (139 × 23, postgame), RUINAS DESIERTO, CUEVA ISLA y TUMBA ANTIGUA (las de los Regi), CÁMARA SELLADA, CUEVA CAMBIANTE, CUEVA ARTESANA, LOSA CALCINADA (RUTA 120), CUEVA TERRESTRE y CUEVA MARINA.
- **SENDERO ÍGNEO:** un solo mapa de 35 × 38, de tierra y roca, sin lava.

## 2. Qué se puede hacer con los gráficos del juego

| Clima / paisaje | Gráficos que ya hay | Clima del mapa y efecto en combate |
| --- | --- | --- |
| Hielo | Suelo de hielo, bloques y agua helada de la CUEVA CARDUMEN (tileset `Cave`) | `WEATHER_SNOW`: nieve en combate (`B_OVERWORLD_SNOW`, la de la 9.ª generación) |
| Volcán | Lava, roca y vapor de la GUARIDA MAGMA y LAVACALDA (tileset `Lavaridge`, el mismo del SENDERO ÍGNEO) | `WEATHER_DROUGHT`: sol en combate |
| Desierto | Arena, dunas y rocas de la RUTA 111 (tileset `Mauville`) | `WEATHER_SANDSTORM`: tormenta de arena en combate |
| Ruinas | Pilares y suelo del PILAR CELESTE (tileset `Pacifidlog`) y salas de las ruinas de los Regi (`Cave`) | Niebla (`WEATHER_FOG_*`): Campo de Niebla en combate |
| Bosque / isla verde | Isla Sur e Isla Lejana (tilesets `Rustboro` y `Fortree`) | Sol o lluvia |
| Marisma | Hierba alta, charcas y flores de AZULIZA y la RUTA 106 (`Dewford`) | Lluvia |

- **El clima del mapa cambia los combates.** Cada zona nueva con su clima juega distinto, no solo se ve distinto.
- **Nieve en el exterior:** Esmeralda no tiene suelo nevado para fuera. Una isla nevada puede ser una isla de roca con nieve cayendo y una cueva de hielo dentro, que sí tiene gráficos.
- **Rojo Fuego/Verde Hoja (opción para más adelante):** la expansion trae sus mapas y tilesets (Cueva Helada, Ruinas Tanobi, Monte Ascuas, Islas Espuma). El motor ya sabe mezclar mapas de los dos juegos (`isFrlg` en cada layout, `src/fieldmap.c`), pero esos tilesets solo se compilan en la versión Rojo Fuego (`#if IS_FRLG` en `src/data/tilesets/`) y `mapjson` se salta sus layouts. Habría que cambiar las dos cosas. Daría gráficos de hielo y ruinas que Esmeralda no tiene.

## 3. Propuestas

Los números son los del mapa (`mundo_propuestas.png`, en el PR). Los tramos son los de `reescalar_niveles.py`.

| # | Zona | Dónde | Tramo | Qué lleva | Coste |
| --- | --- | --- | --- | --- | --- |
| 8 | **Islas del ferry** (ISLA SUR, ISLA LEJANA, ISLA ORIGEN, ROCA OMBLIGO) | Ferry de CALAGUA | 7-8 | Ya existen. Quitar el ticket y el postgame, cambiar los legendarios por salvajes, entrenadores y objetos | **Bajo** |
| 7 | **SENDERO ÍGNEO profundo** | Bajando desde el SENDERO ÍGNEO | 4 | Mapa nuevo con ríos de lava, rocas de Fuerza, montañeros y "fogoneros", objetos de fuego (Roca Calor, Piedra Fuego, Carbón) | Medio |
| 1 | **Isla Nevada** | Al norte de la RUTA 124 | 7 | Isla de roca con nieve y una cueva de hielo con suelo resbaladizo | Medio-alto |
| 5 | **Desierto profundo** | Al este del desierto de la RUTA 111 | 5 | Más desierto con tormenta, entrada al PASO DESÉRTICO y a las RUINAS DESIERTO | Medio |
| 2 | **Isla de las Ruinas** | Al sur de la RUTA 132 | 8 | Ruinas con niebla y salas como las de los Regi | Medio-alto |
| 3 | **Isla Volcánica** | Al sur de la RUTA 134 | 8 | Lava y sol | Medio-alto |
| 4 | **Isla Arenosa** | Al este de la RUTA 127 | 8 | Playa y dunas con tormenta de arena | Medio |
| 6 | **Marisma** | Al oeste de AZULIZA | 2 | La del estudio del #75 | Medio |
| 9 | **BOSQUE PETALIA frondoso y mansión abandonada** | Un camino nuevo desde el BOSQUE PETALIA | 1-2 (bosque) y más tarde (mansión) | Bosque más cerrado y oscuro, con hierba alta y entrenadores, y al fondo una mansión abandonada con fantasmas | Medio-alto |
| 10 | **Playa volcánica del MONTE PÍRICO** | Pegada a la RUTA 122, al oeste o al este | 7 | Arena oscura, aguas termales y rocas volcánicas, con sol | Medio |
| 11 | **Cumbre de la CASCADA METEORO** | Al norte de la RUTA 115 (borde libre) o por una salida nueva de la CASCADA METEORO | 4-6 | Montaña escarpada con pisos a distintas alturas y la cima nevada | Medio-alto |

- **Islas "como las del Ultravuelo":** aquí no se vuela, así que se llega surfeando. Cada isla nueva es un mapa propio pegado al borde de una ruta de mar: se surfea hacia fuera de la ruta y se entra en la isla sin pantalla de carga, como entre dos rutas. Así cada isla tiene su zona de captura y sus salvajes.
- **Propuestas de Miguel del 16/11/2026 (9, 10 y 11):**
  - **BOSQUE PETALIA (9):** el bosque es un mapa de 48 × 44 sin conexiones, con salidas solo a la RUTA 104. La zona nueva sería otro mapa al que se entra por un camino entre los árboles, con el clima a la sombra (`WEATHER_SHADE`) y más hierba alta. La mansión:
    - **Fuera:** casas y vallas de los tilesets `Rustboro` y `Petalburg`.
    - **Dentro:** los interiores de casa (`GenericBuilding`) o del BARCO ABANDONADO, que ya tiene aire de sitio abandonado. Con los tilesets de Rojo Fuego estaría la Mansión Pokémon, que es justo eso.
    - Como está al principio del juego, la mansión podría abrirse más tarde (con Corte o con una llave), para meter fantasmas de nivel más alto y premios mejores.
  - **MONTE PÍRICO (10):** la RUTA 122 es un mapa de agua de 40 × 40 con la isla del monte, sin entrenadores, y tiene libres los dos lados. La playa sería un mapa pegado a uno de ellos, con el tileset de LAVACALDA (arena, roca volcánica, aguas termales) y sol en combate.
  - **CASCADA METEORO (11):** es todo cueva. La montaña sería un mapa exterior nuevo:
    - Acantilados en escalones, como la RUTA 115, con caminos que suben con la Bici Acrobática o la Bici Carrera, y rocas de Golpe Roca y de Fuerza.
    - Abajo, clima normal; arriba, un mapa de cima con nieve cayendo (nieve en combate).
- **Dentro de cada zona:** salvajes propios (hierba, agua, pesca), 2-4 entrenadores con recompensa, objetos (megapiedras, competitivos, Ticket-Recuerdo) y algún NPC con un regalo o un combate especial.

## 4. Límites técnicos

| Qué | Cuánto queda | Qué pasa si se pasa |
| --- | --- | --- |
| **Zonas de captura** | Hay 104 de 112 bits usados: caben **8 zonas nuevas**. Con la variable libre 0x40FE, 16 más | Las zonas nuevas se añaden **al final** de la lista de zonas del mapa de la región, después de la Cima Entrenador. Así no se mueve ningún bit y las partidas guardadas siguen valiendo |
| **Entrenadores** | 8 huecos libres y 11 entrenadores que no salen en ningún mapa (Dudley, Kaylee, Terry…): **unos 19** | Más allá, hay que reutilizar revanchas (`_2` a `_5`) o agrandar la lista, y eso mueve los flags del sistema y rompe las partidas guardadas |
| **Flags** (objetos, eventos) | 162 libres (122 en la zona del sistema, 0x863-0x95F) | Suficientes |
| **Salvajes y semillas** | El randomizer saca los salvajes de una baraja en el orden de `wild_encounters.json` | Las tablas nuevas tienen que ir **al final**; si no, cambian los salvajes de las semillas en curso |
| **Niveles** | Cada mapa nuevo necesita su tramo en `reescalar_niveles.py` | — |
| **Ferry** | Hoy pide la Liga (`FLAG_SYS_GAME_CLEAR`) y un ticket por isla | Se cambia en el script del puerto de CALAGUA |

- **Dibujar los mapas:** sin Porymap (el editor de mapas) se puede hacer por código, copiando trozos de mapas que ya existen (una charca de AZULIZA, un río de lava de la GUARIDA MAGMA) y comprobándolo con `ver_mapa.py`. Así ya se hicieron los Ticket-Recuerdo y las megapiedras.
  - **Porymap funciona en Windows sin compilador.** Con él, Miguel podría dibujar los mapas a mano, y luego se añaden los scripts y los salvajes. No está instalado: si se quiere, se descarga de su GitHub (`huderlem/porymap`).
- **Partidas en curso:** las zonas nuevas no rompen la partida guardada (zonas al final, flags libres, tablas de salvajes al final). Lo que se añada antes de donde vais lo veréis al volver a pasar.

## 5. Orden recomendado

1. **Islas del ferry** (8): es lo más barato, porque los mapas ya existen, y es la primera prueba del sistema de islas.
2. **SENDERO ÍGNEO profundo** (7): primer mapa nuevo, en un tramo temprano (4), con un tileset que ya tiene todo.
3. **Isla Nevada** (1): primera isla nueva pegada a una ruta, con cueva de hielo.
4. **Desierto profundo** (5).
5. **Islas de las rutas del sur** (2, 3 y 4).
6. **Marisma de AZULIZA** (6).
7. **Opcional:** traer los tilesets de Rojo Fuego para más hielo y ruinas.

- **Después:** BOSQUE PETALIA frondoso (9), playa volcánica del MONTE PÍRICO (10) y cumbre de la CASCADA METEORO (11).

**Zonas de captura:** cada zona nueva usa una. Con las 10 nuevas (todas menos el ferry, cuyas islas ya tienen zona) se pasa de las 8 libres, así que hará falta la variable 0x40FE (16 más). Es un cambio pequeño en `src/dualocke.c` que no rompe nada: los bits de esa variable empiezan a 0 en las partidas de ahora.
