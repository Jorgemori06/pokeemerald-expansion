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

## Respuestas de Miguel (27/10/2026)

**El combate**
1. **Equipo lleno (6).**
2. **El primero era el Charmander "Mikemine".**
3. **Fuera tenía al Charmander todo el combate.** El Wiglett puso **Campo de Niebla** y usó **Canto Mortal**.
4. **No cambió de Pokémon.**
5. **No se le debilitó ninguno.** No cambió ni usó objetos, y no salió ningún aviso de muerte.
6. **Una sola Ball**, que lo capturó a la primera.
7. **El Charmander ganó experiencia al capturar, pero no subió de nivel.** No le salió aprender ningún movimiento.
8. Por responder: si salió el aviso de primera captura. Seguramente sí, porque lo pudo capturar.
9. **La pantalla de mote salió una vez.** Escribió un mote distinto de WIGLETT y aceptó. **El mote no se aplicó: el Wiglett se quedó sin nombre, en blanco.**
10. **Le preguntó si lo quería en el equipo y contestó NO**, así que fue directo al PC.
11. No llegó a ver el menú "Elige un POKéMON" de la captura. **Vio el equipo clonado al salir del combate**, en el menú de pausa.
12. **El Wiglett está en el PC**, sin mote y con la habilidad "-------". **Sus otros 5 Pokémon se han perdido**: no están en ninguna caja.
13. Por responder: de qué pantalla es la foto. Por lo anterior, será del PC o del menú de pausa.

**Al lanzar la Ball**
- **Seguían activos el Campo de Niebla y el contador del Canto Mortal.**

**La partida**
14. **No guardó encima.** Tiene la partida de antes del combate (no un estado guardado justo antes).
15. **La versión 2 de Jorge.**
16. **mGBA.** **Es posible que usara el turbo (aceleración) en mitad del combate**; suele usarlo. No cargó estados en mitad del combate.
17. **Antes había capturado un Growlithe con el equipo lleno, contestó SÍ y lo cambió por uno del equipo, y fue todo bien.**

## Lo que dicen las respuestas (Claude de Miguel)

- **No es el menú de "¿lo metes en el equipo?"**: Miguel dijo NO, y con SÍ (el Growlithe) funcionó.
- **Se rompe entre el mote y el PC, antes de ir al PC.**
  - `Cmd_trygivecaughtmonnick` (`src/battle_script_commands.c`) copia el nombre a `gBattleStruct->caughtMonNick` en el estado 2, abre el mote y, al volver (estado 3), lo escribe en el Pokémon.
  - Como el mote salió en blanco, **`caughtMonNick` ya estaba borrado al volver de la pantalla de mote**.
  - Con el equipo lleno, la vuelta pasa por `ReshowBlankBattleScreenAfterMenu`, que es la vía rara.
- **Los dos fallos son la misma escritura.** En `struct BattleStruct` (`include/battle.h`) estos campos van seguidos:
  ```
  battlerPartyIndexes[4], monToSwitchIntoId[4], battlerPartyOrders[4][3], runTries, caughtMonNick[13]
  ```
  - Si algo pone a cero ese trozo, el mote se queda en blanco.
  - `battlerPartyOrders` queda en ceros, y al acabar el combate `UpdatePartyToBattleOrder` copia el primer Pokémon (Charmander) en los 6 huecos, que es lo que vio Miguel.
  - Lo que sobrescribe no es necesariamente de esa zona: puede ser un campo de antes que se sale de su tamaño, o memoria liberada y reutilizada durante el mote o la vuelta al combate.
- **Diferencias con la captura del Growlithe, que fue bien:**
  - Campo de Niebla activo (con `B_TERRAIN_BG_CHANGE`, el fondo del combate se vuelve a dibujar con el del campo).
  - Contador del Canto Mortal activo.
  - Habilidad de relleno (`ABILITY_314`/`317`/Guardia Aura).
  - Respuesta NO en vez de SÍ.
  - Turbo. No debería cambiar la lógica, pero se apunta.
- No se ha podido probar en el PC de Miguel: no hay compilador ni emulador para depurar.

## Siguiente paso

**Cómo reproducirlo:**
1. Partida con el equipo lleno, un salvaje que ponga Campo de Niebla y use Canto Mortal (o forzarlo con el menú de depuración), capturarlo con los dos activos, poner mote y contestar NO.
2. Si se clona, repetir quitando cosas de una en una para ver cuál lo provoca: sin campo, sin Canto Mortal, con SÍ, con un Pokémon con habilidad normal.

**La forma más rápida de encontrar al culpable: un punto de vigilancia en mGBA** (Herramientas → Depurador, con el `.elf` de la compilación).
- Poner un *watchpoint* de escritura en `gBattleStruct->caughtMonNick`, o en `battlerPartyOrders`, justo antes de lanzar la Ball. El depurador se para en la instrucción que lo borra.
- La dirección sale de `gBattleStruct` (un puntero, en el `.map`) más el desplazamiento del campo.

**Mientras tanto:** con el equipo lleno, NO a meterlo en el equipo sigue sin ser seguro (justo así pasó). Hasta arreglarlo, **mejor no capturar con el equipo lleno**: deja antes un Pokémon en el PC. Y si vuelve a pasar, no guardar.

### Siguiente paso (de Jorge, antes de las respuestas)



Con las respuestas, intentar reproducirlo en el emulador con un estado guardado. Si se confirma lo del equipo lleno, un arreglo sencillo y seguro es desactivar ese menú (`B_CATCH_SWAP_INTO_PARTY` a `GEN_6` en `include/config/battle.h`): con el equipo lleno, lo capturado iría directo al PC, como en el Esmeralda original.

*Lo apunta el Claude de Jorge, a petición de Jorge (27/10/2026). Cuando el bug esté resuelto, quitar el aviso del principio de `DUALOCKE.md`.*

## Estado (27/10/2026, tarde, Claude de Jorge)

**Reproducción automática, sin éxito todavía.**
- Se montó un mGBA que juega solo el combate: una versión de la ROM con un arnés que pulsa los botones y vigila cada fotograma `battlerPartyIndexes`…`caughtMonNick` de `gBattleStruct`. No se ha subido al repo.
- Escenario: equipo de 6 con Charmander delante, Wiglett salvaje con solo Campo de Niebla y Canto Mortal, Ball con los dos activos, mote y NO.
- Resultado: **no se clonó**. El mote se guardó bien, y el único cambio en esa zona fue el de la pantalla de mote al escribir el nombre.
- Esa prueba se hizo con otra semilla, así que el Wiglett tenía una habilidad normal. Falta repetirla con la semilla de Miguel (`7044754226`), con `ABILITY_317`. Como el #47 ya quita esa habilidad, si era la causa, ya no pasa.

**Parche de protección: PR #49 de Miguel, fusionado.**
- El mote va en un búfer propio, fuera de `gBattleStruct`.
- El orden del equipo se guarda antes de la pantalla de mote y se repone al volver.
- `UpdatePartyToBattleOrder` y `UpdatePartyToFieldOrder` comprueban que el orden sea una permutación de 0-5; si no lo es, lo rehacen. Así no se clona el equipo aunque algo borre esa memoria.
- El Claude de Jorge había preparado lo mismo (#50); se quedó el de Miguel porque añade la última comprobación.
- La causa de fondo sigue sin encontrarse. Si vuelve a pasar algo raro al capturar (mote en blanco, equipo cambiado), avisad con capturas.
