# 25/10/2026 · Jorge · Caja de prohibidos

Sesión de Jorge con Claude. Rama `jorge/caja-prohibidos`, encima de `jorge/captura-zona` (#17), porque usa su regla de repetidos. El PR se abre cuando el #17 esté en `master`.

## Decisiones de Jorge

- **Huevos:** se aplica la regla de los eventos. Si al eclosionar es repetido o legendario, queda bloqueado. Criar no se prohíbe; se controla por honor.
- **Intercambios con NPCs:** cuentan como regalo.

## Cómo funciona

- **La caja 13 ("VETADOS") es la de prohibidos**; la 14 sigue siendo la de muertos. El nombre se pone al empezar partida nueva, y la de muertos pasa a llamarse "MUERTOS" en español.
- **Qué va ahí:** los Pokémon que no pasan por la regla de la zona y son **repetidos** (la misma regla de ramas del #17) o **legendarios**:
  - regalos, eventos y fósiles (`GiveScriptedMonToPlayer`);
  - estáticos capturados: Kecleon, Electrode, Regis… (`GiveCapturedMonToPlayer`);
  - huevos, al eclosionar (`EggHatchSetMonNickname`, después del mote);
  - intercambios con NPCs (`TradeMons`). Si el Pokémon que das sale del PC, el que recibes va directo a la caja de prohibidos. Si sale del equipo, se comprueba al salir de la escena, después de guardar su nombre para los textos del NPC.
- **Excepciones:**
  - Los **variocolor** nunca van a la caja de prohibidos.
  - Antes de recibir las Poké Balls (`FLAG_ADVENTURE_STARTED`) no se prohíbe nada, así que el inicial y los tests de la expansion no se ven afectados.
  - Nunca se deja el equipo vacío: si el huevo o el intercambio es el único Pokémon que tienes, se queda en el equipo.
- **En el PC:**
  - Un Pokémon de la caja de prohibidos que sigue siendo repetido o legendario solo deja ver el resumen.
  - Un **repetido se desbloquea solo** cuando deja de serlo, es decir, cuando muere el de su línea que tenías. Entonces sale el menú normal y se puede sacar o mover.
  - En la caja no se puede dejar nada, ni de uno en uno ni varios a la vez, y `CopyMonToPC` nunca manda nada ahí.
- **Los de la caja de prohibidos no cuentan como "línea que ya tienes"**, ni para los salvajes ni para la evolución bloqueada ni entre ellos.
- **Mensaje:** al recibirlo sale el de siempre, "se ha enviado a la caja VETADOS".

## Archivos

- `src/dualocke.c`, `include/dualocke.h`: la regla (`Dualocke_ShouldBanMon`, `Dualocke_IsBoxMonLocked`, `Dualocke_SendMonToBannedBox`, `Dualocke_TryBanPartyMon`) y los nombres de las cajas.
- `src/pokemon.c`: regalos, capturas y `CopyMonToPC`.
- `src/egg_hatch.c`: huevos.
- `src/trade.c`: intercambios con NPCs.
- `src/pokemon_storage_system.c`: bloqueo en el PC (`Dualocke_IsLockedBox` en vez de `Dualocke_IsDeadBox`).
- `test/dualocke.c`: 8 tests nuevos.

## Decisiones de Claude por el camino (revisables)

- **Caja 13** como caja de prohibidos, al lado de la de muertos.
- Los nombres de caja "VETADOS" y "MUERTOS", porque el nombre de caja tiene un máximo de 8 letras.
- **No hay mensaje propio** explicando por qué va a la caja de prohibidos: sale el de siempre con el nombre de la caja.
- **Huevo o intercambio que te dejaría sin equipo:** se queda en el equipo. Es un caso casi imposible, porque no se puede tener un equipo solo de huevos.

## Pruebas

- Compila (`make`).
- Tests del locke: ver abajo.
- **No probado jugando.** Se puede probar con el menú de depuración (R + START):
  1. Darse un Beldum.
  2. Ir a la casa de Máximo en Ciudad Algaria a por el otro Beldum, o darse un regalo con el menú.
  3. Mirar la caja 13 del PC.
