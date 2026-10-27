# Bug abierto: Wiglett sin habilidad y equipo clonado al capturar (27/10/2026)

**Para el Claude de Miguel:** antes de tocar código, **hazle a Miguel todas las preguntas de abajo** (de una en una o en pocas tandas) y apunta las respuestas en este archivo (y en el registro de su sesión). Ir a ciegas con este fallo es muy difícil, así que primero hay que saber exactamente qué pasó. Si puede, que pase capturas o, mejor, el `.sav` y un estado guardado del emulador justo antes.

## Qué pasó (lo que sabemos por Jorge)

Jugando su ROM del locke (semilla `7044754226`, versión 2, commit `a661c0eb`), Miguel estaba en el TÚNEL FERVERGAL. Un Wiglett salvaje (nivel 12) usó **Canto Mortal** y Miguel lo capturó. Después:

1. **El Wiglett salió "Sin habilidad especial".**
2. **Todo el equipo se convirtió en copias de su Charmander "Mikemine"** (nivel 18, 34/34 PS en los 6 huecos), en un menú de combate que dice "Elige un POKéMON." con el botón SALIR.

## Lo que ya ha encontrado el Claude de Jorge

- **Habilidad: causa encontrada y arreglada** (rama `jorge/arreglo-habilidades`, este mismo PR). El randomizer de habilidades podía elegir 3 de relleno del motor que no hacen nada: `ABILITY_314` y `ABILITY_317` ("-------") y `ABILITY_AURA_GUARD` (sin implementar).
  - En la semilla de Miguel afectaba a 18 especies: Wiglett, Onix, Gardevoir, Floatzel, Crabrawler, Gigalith y algunas formas y megas.
  - Con el arreglo **solo cambian esas 18**: el resto de su randomización sale igual.
- **Equipo clonado: no está confirmado.**
  - El mecanismo cuadra con el menú de equipo del combate. `UpdatePartyToBattleOrder` (`src/party_menu.c`) reordena el equipo con `gBattlePartyCurrentOrder`. Si ese orden llega a ceros, copia el primer Pokémon en los 6 huecos, que es justo lo que se ve en la foto.
  - Pasa con el orden de un combatiente que no existe (en combate individual, el 2 o el 3) o si se corrompe `gBattleStruct`.
  - **Sospechoso principal:** capturar con el **equipo lleno** y contestar **SÍ** a "¿Quieres meterlo en el equipo?" (`B_CATCH_SWAP_INTO_PARTY`, función `Cmd_givecaughtmon`). Antes pasa por la pantalla de mote obligatorio (`Cmd_trygivecaughtmonnick`), que con el equipo lleno vuelve al combate por `ReshowBlankBattleScreenAfterMenu`, un camino que casi nadie usa.
  - También podría venir de un **cambio de Pokémon** durante el Canto Mortal.
  - No se ha podido reproducir en los tests: los combates de los tests se saltan el mote y se quedan esperando en el "¿lo metes en el equipo?".
- **Mientras tanto:** al capturar con el equipo lleno, contestar **NO** (va directo al PC), y no guardar encima de una partida buena si vuelve a pasar.

## Preguntas para Miguel

**El combate**
1. ¿Cuántos Pokémon llevaba en el equipo justo antes de capturar? ¿Estaba lleno (6)?
2. ¿Cuál era el primero del equipo? ¿El Charmander "Mikemine"?
3. ¿Qué Pokémon tenía fuera cuando Wiglett usó Canto Mortal? ¿Cuántos turnos pasaron hasta capturarlo?
4. ¿Cambió de Pokémon durante el combate (por el Canto Mortal o por otra cosa)? ¿Cuántas veces y a cuáles?
5. ¿Se le debilitó o murió algún Pokémon en ese combate (contador del Canto Mortal o ataques)? ¿Salió el aviso de "ha muerto"?
6. ¿Usó algún objeto antes de la Ball (poción, etc.)? ¿Qué Ball usó y cuántas tiró?
7. ¿Su Pokémon subió de nivel al capturar (experiencia por captura)? ¿Le salió aprender algún movimiento?
8. ¿Era el primer Pokémon de la zona (salió el aviso de primera captura al empezar)? ¿Wiglett era repetido de algo que ya tenía?

**Después de capturar**
9. ¿Le salió la pantalla de mote? ¿Qué nombre le puso? ¿Tuvo que ponerlo dos veces (si dejas el de la especie te lo vuelve a pedir)?
10. ¿Le preguntó "¿Quieres meterlo en el equipo?" o similar? ¿Qué contestó?
11. Si dijo que sí: ¿qué Pokémon eligió mandar al PC en el menú "Elige un POKéMON"? ¿Ya salían todos como Charmander al abrir ese menú, o pasó después de elegir?
12. ¿Dónde está ahora el Wiglett: en el equipo o en el PC? ¿Y sus otros 5 Pokémon de antes: siguen en alguna caja?
13. ¿La foto del resumen de Wiglett ("Sin habilidad especial", con el botón MOTE) de qué pantalla es: del combate, del PC o del menú de pausa?

**La partida**
14. ¿Guardó después de que pasara? ¿Tiene una partida o un estado guardado de antes?
15. ¿Qué ROM usaba exactamente: la versión 2 que le pasó Jorge, o compilada él mismo? ¿Venía de una partida de la versión 1?
16. ¿Qué emulador y versión? ¿Usó aceleración, trucos o estados guardados en medio del combate?
17. ¿Le ha pasado algo raro más en la partida (otros combates, el recuerdamovimientos, la mochila)?

## Siguiente paso

Con las respuestas, intentar reproducirlo en el emulador con un estado guardado. Si se confirma lo del equipo lleno, un arreglo sencillo y seguro es desactivar ese menú (`B_CATCH_SWAP_INTO_PARTY` a `GEN_6` en `include/config/battle.h`): con el equipo lleno, lo capturado iría directo al PC, como en el Esmeralda original.

*Lo apunta el Claude de Jorge, a petición de Jorge (27/10/2026). Cuando el bug esté resuelto, quitar el aviso del principio de `DUALOCKE.md`.*
