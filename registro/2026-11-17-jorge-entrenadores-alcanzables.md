# 17/11/2026 — Jorge: entrenadores que se alcanzan antes de su tramo

## Qué se pidió

Jorge, con 2 medallas (cap 32) y su equipo a 28-29, salió de MALVALONA y se metió en un combate doble contra ROSA y DEANDRE a nivel 47. "Me aseguraste que no iba a volver a pasar." Ya había pasado con los entrenadores de la RUTA 103 este (#55) y con la pesca a pie (#61), y se arregló caso a caso, cuando salían jugando.

## Por qué pasaba

`reescalar_niveles.py` pone el nivel según el tramo de cada **mapa**. La RUTA 118 es del tramo 6, porque casi toda se hace con SURF, pero su orilla oeste se pisa nada más salir de MALVALONA (tramo 3), y ahí hay 4 entrenadores que te ven al pasar. En el #61 se arregló la pesca de esa orilla, pero no sus entrenadores.

## Qué se ha hecho

- **`tools/dualocke/alcance.py` (nuevo):** recorre el mundo casilla a casilla, como el jugador, con lo que se puede hacer en cada tramo.
  - Tiene en cuenta: colisión y elevación de cada casilla, saltos, agua (SURF), cascadas, buceo, corrientes, árboles de CORTE, rocas de GOLPE ROCA y de FUERZA, bici, puertas y warps, conexiones entre mapas, el barco del SR. BRINEY y el teleférico.
  - Para cada entrenador dice desde qué tramo te ve (en línea recta, hasta su distancia de visión) o le puedes hablar, y avisa si su nivel pasa del de ese tramo (cap − 3 los normales y el cap los jefes).
  - No sabe nada de los PNJ ni de los scripts que cortan el paso. Las elevaciones entre tierra y tierra no las sigue (`ESTRICTO = False`), así que puede dar casos de más, que se miran a mano, pero no de menos. Con `ESTRICTO = True` salen los mismos casos de los tramos 1 a 5.
  - Lo que no es un fallo va apuntado con su motivo:
    - `IGNORAR`: las guaridas Magma y Aqua, la cima del MONTE PÍRICO y el gimnasio de PETALIA, que se abren por la historia.
    - `POR_HISTORIA`: LIRIA, el MONTE PÍRICO, ALGARIA y todo el mar del sur. Con SURF (tramo 6) se puede ir por las RUTAS 118 y 123 sin pasar por ARBORADA, pero la historia no va por ahí. Para eso está la red del juego (abajo).
  - `--comprobar` sale con error si hay alguno. **Va en el CI** (`build.yml`, antes de compilar; tarda 2 segundos).
- **Lo que ha encontrado: 8 entrenadores**, que pasan al rango del tramo 3 según su nivel original:

  | Dónde | Entrenadores | Antes | Ahora |
  | --- | --- | --- | --- |
  | RUTA 118, orilla oeste (al salir de MALVALONA) | ROSA, DEANDRE, WADE, DALTON | 47 | 21-23 |
  | RUTA 111 sur (entre MALVALONA y las rocas de GOLPE ROCA) | TYRON, CELINA, BIANCA, HAYDEN | 30-31 | 24 |

  - `TRAMO_DE_ENTRENADOR` en `reescalar_niveles.py`. Se aplica al final, así que no cambian las bandas de los tramos, los salvajes, los estáticos ni los niveles de las revanchas.
  - `ia_entrenadores.py` también lo lee: los 4 de la RUTA 118 vuelven a la IA de antes de CANDELA, como el resto del tramo 3.
  - Relanzados los cuatro scripts en orden. Sobre master, sin el cambio, no cambiaban nada.
- **Red de seguridad en el juego:** `Dualocke_CapTrainerMon` (`src/dualocke.c`), llamado desde `CreateNPCTrainerPartyFromTrainer` (`src/battle_setup.c`).
  - Ningún POKéMON de un entrenador rival sale por encima del level cap. Si pasa, sale al cap justo y con la etapa que le toca para ese nivel (la misma regla que los salvajes).
  - Sin `Random()`, para que el mismo entrenador salga siempre igual.
  - No toca al compañero de los dobles ni al Frente Batalla, que tiene su propio sistema.
  - Con la curva de la sección 5 no debería saltar nunca: los jefes van como mucho al cap y las revanchas encajan con las medallas que las abren. Solo salta si algo se alcanza antes de tiempo.
- 2 tests en `test/dualocke.c`.
- `DUALOCKE.md`, secciones 5 y 10.

## Las partidas en curso

- **Lo que se guarda:** no cambia (ni flags, ni vars, ni SaveBlocks).
- **Semillas:** comparado el solucionario de la versión 7 con el nuevo, con las dos semillas.
  - Solo cambian los 8 entrenadores de arriba y las revanchas (\_2 a \_5) de ROSA y DALTON.
  - Salvajes, iniciales, objetos del suelo, Recogida, intercambios, MT, tutores, estáticos, habilidades y el resto de entrenadores salen igual.
- **ROMs** (`make release`, rama `jorge/entrenadores-alcanzables`, que es master + esto):
  - Jorge `2780853751`, md5 `ce6f5f87dbf7a9c41365192d64b92370`;
  - Miguel `2918696854`, md5 `0e947dfa75c619b2ef0d2d0a45033946`.

## Encontrado por el camino

- **Las revanchas no siempre mantienen las líneas del primer combate.** El randomizer las empareja por la especie escrita en `trainers.party` (`lineas_familia`, clave `(familia, especie)`). Si el primer combate va sin evolucionar y la revancha evolucionada, no coinciden y la revancha sale con otras líneas. Pasa en casi todos los de los primeros tramos con revancha (JERRY, KAREN, MIGUEL, LYDIA…), y ahora también con ROSA y DALTON. Solo afecta a revanchas, que se abren con 5 medallas. Arreglarlo (emparejar por línea evolutiva) cambiaría muchas revanchas que aún no se han visto: pendiente de decidir.
- **Zonas nuevas de Miguel** (pasando la herramienta por `miguel/rediseno-isla-nevada`, el #95):
  - El BOSQUE FRONDOSO y la MANSIÓN OLVIDADA se alcanzan desde el BOSQUE PETALIA sin ninguna MO, o sea en el tramo 1, con los entrenadores a 20 (cap 16).
  - El DESIERTO PROFUNDO y las RUINAS ARENOSAS salen en el tramo 4 con nivel 47 (cap 43). Seguramente es un falso positivo, porque se entra por el desierto y hacen falta las GAFAS AISLANTES, que la herramienta no conoce.
  - Hay que mirarlo al rehacer la revisión de su cadena.

## Cómo se comprobó

- `make` compila sin avisos nuevos.
- `make check TESTS="Dualocke"`: 50/50.
- `make check` completo: ver el PR.
- `alcance.py --comprobar`: 0 casos.
- No se ha probado en el emulador.

## Pendiente

- Probarlo jugando: salir de MALVALONA hacia el este y que ROSA y DEANDRE salgan a 21.
- Decidir lo de las líneas de las revanchas.
- Revisar las zonas de Miguel con `alcance.py`.
