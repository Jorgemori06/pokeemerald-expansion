# 24/10/2026 · Jorge · Primera captura por zona (salvajes)

Sesión de Jorge con Claude. Rama `jorge/captura-zona`. Primera de las dos partes de la regla de captura; la segunda es la caja de prohibidos para regalos, eventos y fósiles.

## Decisiones de Jorge

- **Antes de que te den las primeras Poké Balls no cuenta ningún encuentro.** Después sí, aunque no tengas Balls porque se te olvidó comprarlas. Se usa `FLAG_ADVENTURE_STARTED`, que se activa justo cuando Aura/Bruno te dan las Balls en el laboratorio.
- **Líneas con ramas:** se puede tener un Pokémon de cada rama (Gardevoir y Gallade, Vaporeon y Sylveon…), siempre que el nuevo no evolucione a la que ya tienes. Uno que todavía no ha elegido rama (Ralts, Kirlia, Eevee) ocupa toda la línea. Las formas regionales cuentan como su especie. Si el que tenías muere, su rama se libera, también para evolucionar. El juego **bloquea** la evolución a una rama que ya tienes.
- Los **Kecleon del Detector** (y el resto de estáticos) son de evento: no gastan la zona y se pueden capturar. El randomizer los cambiará y les pondrá el nivel de la curva.

## Cómo funciona

- **Qué cuenta:** solo los encuentros aleatorios, es decir, hierba, cuevas, surf, pesca, Golpe Roca, Dulce Aroma, Safari y errantes. Se marcan en `src/battle_setup.c` con `Dualocke_SetRandomEncounter()`. Los combates con script (`setwildbattle` + `dowildbattle`), los legendarios estáticos, la Pirámide y el Pike no cuentan.
- **Al empezar el combate** (`Dualocke_OnBattleStart`, desde `BeginBattleIntro`) se decide el estado del salvaje:
  1. **Shiny:** se puede capturar y no gasta la zona.
  2. **Zona gastada:** no se puede capturar.
  3. **Legendario o singular** (`isRestrictedLegendary`, `isSubLegendary` o `isMythical` de la especie base): no cuenta, no se puede capturar y la zona sigue libre.
  4. **Línea que ya tienes viva:** igual que el legendario.
  5. **Si no es nada de lo anterior, es el primero de la zona:** se puede capturar y la zona queda gastada en ese momento, pase lo que pase en el combate.
- **Aviso al empezar:** en los casos 1, 3, 4 y 5 sale un mensaje en el combate. En el 2 no sale nada, para no repetirlo en cada combate de una zona ya gastada.
- **Bloqueo:**
  - Las Balls desde la mochila dan un mensaje y no se gastan; el botón de la última Ball usada se desactiva.
  - La Safari Ball da otro mensaje y no se pierde el turno.
- **Zonas:** las secciones del mapa regional. Son las 88 de Hoenn anteriores a Kanto más las 16 propias de Esmeralda (Guarida Aqua, Torre Espejismo, Cueva Terra…), que van después de las de Kanto. Se guardan en 7 variables libres (`VAR_DUALOCKE_ZONES_0` a `_6`, antes `VAR_UNUSED_0x40F7` a `0x40FD`), un bit por zona. **No gasta flags.**
- **Ramas:**
  - Las ramas de una especie son las evoluciones finales a las que puede llegar, con todas sus formas. Las formas regionales y las megas cuentan como su especie base.
  - Un Pokémon con una sola rama posible ocupa esa rama; uno con varias ocupa toda la línea.
  - Un salvaje es **repetido** si tienes vivo uno de su línea sin rama elegida, o si ya tienes todas sus ramas. Por ejemplo: con Gardevoir, Ralts cuenta y Gardevoir no; con Kirlia, ni Ralts ni Gallade.
  - Se miran el equipo (solo los que tienen PS) y todas las cajas menos la de muertos.
- **Evolución bloqueada** (`Dualocke_IsEvolutionBlocked`, desde `GetEvolutionTargetSpecies`):
  - Un Pokémon del equipo no evoluciona a una especie cuyas ramas ya tienes todas con otros Pokémon vivos.
  - Si sube de nivel, no evoluciona. Con una piedra, "no tendrá efecto" y no se gasta.
  - Se comprueba antes de las condiciones extra, así que nunca se gasta un objeto en una evolución bloqueada.

## Decisiones de Claude por el camino (revisables)

- **Si no cuenta (repetido o legendario), el combate es normal:** puedes huir o debilitarlo, pero no capturarlo. Jorge no tenía preferencia entre esto y que huya solo. Es más sencillo y deja elegir al jugador.
- **Aviso al empezar el combate** en vez de en el menú de pausa (Jorge no tenía preferencia).
- **Las zonas submarinas** (Buceo en las rutas 124, 126…) tienen nombre propio en el mapa, así que son zonas aparte de la ruta de encima.
- **La Zona Safari es una sola zona**, aunque tenga varias áreas.
- **Los errantes (Latios/Latias)** cuentan como encuentros aleatorios: son legendarios, así que no se pueden capturar, salvo que sean shiny.
- **Los combates salvajes del menú de depuración** cuentan como aleatorios, para poder probar la regla.

## Archivos

- `src/dualocke.c`, `include/dualocke.h`: la regla.
- `include/constants/vars.h`: las 7 variables.
- `src/battle_setup.c`: qué combates son aleatorios.
- `src/battle_main.c`, `include/battle_main.h`: estado al empezar, aviso del primer turno y bloqueo de la Safari Ball.
- `src/item_use.c`, `include/item_use.h`: bloqueo de las Balls.
- `src/battle_message.c`, `include/constants/battle_string_ids.h`, `include/battle_message.h`, `data/battle_scripts_1.s`, `include/battle_scripts.h`: mensajes.
- `src/pokemon.c`: bloqueo de la evolución.
- `test/dualocke.c`: 14 tests nuevos.

## Pruebas

- Compila (`make`).
- `make check TESTS="Dualocke"`: 20 de 20 en verde (los 6 de vidas y los 14 nuevos). Cubren:
  - el primero de la zona, la zona gastada y las zonas de Esmeralda;
  - los repetidos (ramas elegidas, sin elegir y formas regionales) y la caja de muertos;
  - la evolución bloqueada (Kirlia con Gardevoir, Eevee con Vaporeon) y que se libera al morir;
  - los legendarios (Ultraentes no) y los shiny;
  - antes de las Balls, y los combates de evento.
- **Falta verlo en el juego.** Se puede sin pasarse nada: menú de depuración (R + START) → volar a una ruta y buscar salvajes. Hay que mirar que salen los avisos, que la Ball no se gasta, la Safari Ball y que una piedra no se gasta en una evolución bloqueada.

## Pendiente

- **Caja de prohibidos:** los regalos, eventos y fósiles repetidos o legendarios van a una caja bloqueada. Los repetidos se pueden sacar cuando muere el de su línea; los legendarios se quedan.
- Los estáticos que se capturan (Kecleon, legendarios…) también son "eventos", así que irán a esa caja si son repetidos o legendarios.
