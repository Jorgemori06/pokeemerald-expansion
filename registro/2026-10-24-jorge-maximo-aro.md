# 24/10/2026 · Jorge · Fusión de los PR de Miguel y evento de Máximo

Sesión de Jorge con Claude (entorno en la nube de Claude, con compilador de ARM). Rama `jorge/maximo-aro`.

## Qué se pidió

1. Ponerse al día y revisar y fusionar, en orden, los PR #10 a #15 de Miguel.
2. Compilar `master` con todo dentro y borrar las ramas `miguel/*` fusionadas.
3. Montar el evento de Máximo en la Ruta 120: combate con `TRAINER_STEVEN_ROUTE_120` y Aro Mega al ganar.

## PR de Miguel

| PR | Qué | Resultado |
| --- | --- | --- |
| #10 | Parámetros del randomizer y arreglo de `caps.h` | Aprobado y fusionado |
| #11 | Contenido de las tiendas (tabla de medallas en `src/shop_criteria.c`) | Aprobado y fusionado |
| #12 | 81 megapiedras y 55 objetos competitivos por el mapa, `IDEAS.md` | Aprobado y fusionado |
| #13 | Equipo de Máximo (`TRAINER_STEVEN_ROUTE_120`) | Conflicto en la tabla del reparto de `DUALOCKE.md` (por el #10): se fusionó `master` en la rama conservando las dos filas. Aprobado y fusionado |
| #14 | Script de instalación para Windows | Aprobado y fusionado |
| #15 | Revanchas, postgame y Casa Trampa | Aprobado y fusionado. Comprobado que Máximo sigue en `trainers.party` tras la fusión |

- Todos con CI en verde (`build-emerald` y `test`) y con `base=master`.
- Comprobado en la revisión del #12: los flags nuevos no se repiten, los offsets de los objetos ocultos caben en su campo de 13 bits y los IDs de objeto en el de 11.
- `master` compila (`make`) y sale `pokeemerald.gba`.
- **Ramas `miguel/*` sin borrar:** el proxy de GitHub del entorno de Claude no deja borrar ramas. Están todas fusionadas (la de `miguel/evoluciones-entrenadores` solo tiene encima el merge del antiguo #8, cuyo contenido ya está en `master`). Hay que borrarlas desde GitHub.

## Evento de Máximo

Antes: Máximo te preguntaba si estabas listo, usaba el Detector Devon, combatías contra el Kecleon invisible y te daba el Detector.

Ahora (`data/maps/Route120/scripts.inc`):

1. Máximo te habla de la megaevolución y te pregunta si estás listo (el "no" funciona igual que antes).
2. Combate con `trainerbattle_single TRAINER_STEVEN_ROUTE_120`.
3. Si ganas: te da el **Aro Mega** y te dice que las megapiedras están escondidas por Hoenn.
4. Sigue el evento original: Detector Devon, Kecleon y entrega del Detector.

- **Si pierdes contra Máximo:** *whiteout* normal (y el locke se pierde, como cualquier combate perdido). Máximo sigue en el puente.
- **Si ya le habías ganado** y Máximo sigue ahí (perdiste contra el Kecleon, por ejemplo): no vuelve a combatir; te da el aro si no lo tienes y sigue con el Kecleon.
- El combate es obligatorio antes de Alana, porque sin el Detector no se quita el Kecleon de la puerta del gimnasio de Arborada.
- No hace falta un flag nuevo: el flag de entrenador de `TRAINER_STEVEN_ROUTE_120` dice si le has ganado, y para saber si tienes el aro basta con mirar la mochila (`ITEM_MEGA_RING`), que es lo que ya comprueba el combate.
- Textos en inglés, como el resto del juego. Se han medido en píxeles con la fuente del juego: la línea más larga ocupa 196 px (el máximo del original es 208).

## Decisiones de Claude por el camino (revisables)

- **Orden del evento:** primero el combate y el aro, después el Kecleon. Así se reaprovecha el evento original y el Detector sigue llegando en el mismo sitio.
- **Textos:** Máximo presenta la megaevolución antes del combate y explica las megapiedras después. El texto "Your battle style is intriguing… since DEWFORD" pasa a la entrega del aro.

## Pruebas

- Compila (`make`).
- **No probado jugando.** Hay que comprobar en mGBA: que el combate salta al decir "sí", que al ganar aparece "Obtained MEGA RING!", que después se puede megaevolucionar, y el caso de perder.
- Sin test automático: el evento son movimientos, combates y mensajes en el mapa, y el framework de tests de la expansion no cubre eso.

## Para Miguel (equilibrio, no tocado)

- El **Kecleon del puente** sigue a **nivel 30** (`setwildbattle SPECIES_KECLEON, 30`), igual que los otros Kecleon que se ven con el Detector. En el tramo 6 los salvajes van de 44 a 53, así que quizá quieras subirlos.
- Cuando esté la regla de captura por zona, ese Kecleon es un salvaje de la Ruta 120: habrá que decidir si cuenta como su primer encuentro.

## Pendiente

- Probarlo jugando.
- Mis siguientes tareas: segundo dependiente de las tiendas, primera captura por zona, una compra por objeto, aviso al morir y randomizer.
