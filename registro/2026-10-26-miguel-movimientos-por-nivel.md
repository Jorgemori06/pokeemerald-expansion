# 26/10/2026 — Miguel: movimientos por nivel al azar

## Qué se pidió

Miguel jugó el locke hasta el BOSQUE PETALIA y vio que los movimientos no eran aleatorios: los Pokémon aprendían lo normal. El randomizer solo cambiaba los de los entrenadores (3 de nivel y el cuarto al azar, #27). Miguel eligió que **cada especie aprenda movimientos al azar al subir de nivel**, para todos: los suyos, los salvajes y los entrenadores.

En la misma prueba dijo que no encontraba objetos en el suelo ni el que recuerda movimientos (ver "Lo demás").

## Qué se ha hecho

- **`tools/dualocke/aleatorio/aprendizajes.py` (nuevo).** Para cada tabla de movimientos por nivel:
  - **Mismos niveles** que el original, con cada movimiento cambiado por uno al azar.
  - **Tope de potencia por nivel**, el mismo que el cuarto de los entrenadores (40 + 1,5 por nivel). Los de "al evolucionar" cuentan como nivel 30.
  - **Más ataques y de su tipo.** El 60 % son de daño y, entre ellos, los de su tipo son 3 veces más probables. Al azar puro salían demasiados de estado: Treecko con Hora del Té, Canto y Encanto.
  - **Siempre algún ataque al principio:** hay uno de daño entre los que aprende hasta nivel 5.
  - **Sin repetidos.** Las formas que compartían tabla la siguen compartiendo.
  - **Sin Plegaria Vital**, que revive en pleno combate y se saltaría las muertes del locke.
  - Tiene su `comprobar()`, que el randomizer lanza como los demás.
- **`randomizer.py`:** genera las tablas antes que los entrenadores, que sacan sus 3 movimientos "de nivel" de ellas. Las tablas también van al solucionario.
- **`cabecera.py`:** las escribe en `src/data/dualocke_aleatorio.h`: una tabla por cada tabla distinta y `sDualockeAprendizajes[NUM_SPECIES]`. Sin semilla, todo `NULL`.
- **`src/pokemon.c`:** `GetSpeciesLevelUpLearnset` usa la tabla nueva si la hay (`Dualocke_AprendizajeAleatorio`, en `src/dualocke_aleatorio.c`). Ahí miran los movimientos iniciales de los salvajes, lo que se aprende al subir de nivel y al evolucionar, y el que recuerda movimientos.
- **Configuración:** `"aprendizaje_aleatorio": true` en `randomizer_config.json`, dentro de `movimientos_y_mt`.
- **Documentación:** `DUALOCKE.md` (sección 7) y `PRUEBAS.md`.

## Cómo se comprobó

- **Sin preprocesador:** en el PC de Miguel no hay preprocesador ni compilador. Se probó `aprendizajes.py` leyendo a mano los `.h` de movimientos, tablas y especies, con la semilla de Miguel (7044754226). Resultados:
  - 1329 especies con tabla nueva (1089 tablas distintas);
  - 0 errores en `comprobar()`;
  - la misma semilla da siempre lo mismo;
  - todas tienen un ataque hasta nivel 5.
  - Ejemplo: Treecko aprende Corte Sombra, Voz Cautivadora, Megaagotar y Gigadrenado antes de nivel 18.
- **Cabecera:** se generó la de prueba, con unas 17 500 entradas (unos 70 KB de ROM). La de "Sin randomizar" queda con la tabla vacía.
- **Sin compilar:** falta que Jorge pase `make check` y `make release`.

## Lo demás de la prueba

- **Objetos del suelo.** Están, y se pueden alcanzar; se comprobó casilla a casilla en las rutas 102-104 y el BOSQUE PETALIA. Con el randomizer, lo que hay dentro de cada bola es otro objeto al azar.
  - Las megapiedras del bosque (Beedrillita y Scolipita) están en la esquina de arriba a la derecha, junto a la Superball. La Venusaurita está oculta al lado.
  - La primera megapiedra de la RUTA 104 está en la parte de arriba, pasado el bosque.
  - Los objetos competitivos empiezan en AZULIZA y la RUTA 106.
- **El que recuerda movimientos y los tickets** están en el PR #40, todavía sin fusionar. La ROM del locke es del commit `46ba7600` (#41), anterior.

## Pendiente

- Jorge: compilar, fusionar #40 y esto, y regenerar la ROM de Miguel con su semilla (`make release SEED=7044754226`). La partida guardada sigue valiendo. Los Pokémon que ya tiene conservan sus movimientos y aprenden de la tabla nueva desde ahora.
- Decidir si se quita Plegaria Vital también de las MT y los tutores al azar. Cambiaría lo que enseñan las MT de la semilla actual.
