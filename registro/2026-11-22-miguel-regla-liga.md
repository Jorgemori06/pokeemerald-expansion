# 22/11/2026 — Miguel: la regla de la Liga, dentro del juego

## Qué se pidió

Jorge contó en el #118 la regla de la Liga que usáis y preguntó si se metía en el juego (`DUALOCKE.md`, sección 9). Miguel contestó: **sí, entera** (tienda, contador en combate y cura al pasar de sala).

En la misma tanda de preguntas, Miguel contestó las otras recomendaciones del bot (#118):

| Recomendación | Respuesta de Miguel |
| --- | --- |
| Movimientos del randomizer (asegurar un ataque de su tipo) | **Dejarlo así**: totalmente al azar |
| Salvajes de la CALLE VICTORIA a nivel 87 | **Dejarlos a 87** |
| Jefes de mitad de juego (Norman, Candela, Monte Cenizo, Aquiles) | **Dejarlos**: se miran cuando los pruebe una persona |

## Qué se ha hecho (rama `miguel/regla-liga`, encima del #118)

Va encima del #118 porque cambia las líneas de la regla que el #118 añadió a `DUALOCKE.md`.

- **Tienda de la Liga** (`EverGrandeCity_PokemonLeague_1F`):
  - vende RESTAURAR TODO a su precio normal (3000 ₽);
  - sin límite: `compras_limitadas.py` tiene ahora `EXENTOS_TIENDA` para esa pareja;
  - la tabla de compras (`src/data/dualocke_compras.h`) no cambia, así que los bits de las partidas guardadas siguen igual;
  - antes de abrirla, el dependiente recuerda la regla.
- **En combate contra el Alto Mando y PLUBIO** (`src/dualocke_liga.c`):
  - un curativo de la mochila solo se puede usar si el rival ya ha usado uno, y como mucho tantos como él;
  - si no, sale "Regla de la Liga: no puedes curar más veces que el rival." y el objeto no se gasta (`CannotUseItemsInBattle`, `src/item_use.c`);
  - cuentan los curativos de PS, estados y PP y la Flauta;
  - se suman al usarse (`HandleAction_UseItem`, `src/battle_util.c`), y los dos contadores vuelven a 0 en cada combate (`Dualocke_OnBattleStart`).
- **Cura entre combates** (`data/scripts/dualocke_liga.inc`): al entrar en cada sala del Alto Mando (`PokemonLeague_EliteFour_EventScript_WalkInCloseDoor`) y en la del Campeón, el equipo se cura entero, con la música del Centro y un mensaje.
- **Docs:**
  - `DUALOCKE.md`: sección 4 (regla y tabla), sección 6 ("Regla de la Liga dentro del juego") y sección 9 (decidido, y las respuestas a las recomendaciones);
  - `PRUEBAS.md`: lo que hay que probar;
  - `GUIA.html`: tarjeta en las reglas y una línea en la Liga.

**Lo que Jorge dejó por decidir lo he decidido yo:**
- el precio, el normal;
- qué curativos cuentan, todos (el rival solo lleva RESTAURAR TODO);
- cuándo se cura, al entrar en cada sala.

Se cambia fácil si Miguel o Jorge prefieren otra cosa.

## Cómo se comprobó

- **`compras_limitadas.py`:** misma tabla que antes (86 compras en 15 tiendas).
- **Comprobaciones:** `comprobar_zonas.py`, `alcance.py`, `sin_salida.py` y `variantes.py` dan 0.
- **Choques:** con los PR abiertos (#115, #119, #120 y #121), ninguno en los archivos de esta rama.
- **Compilación y `make check`:** los hará el CI.
- **Sin probar en el emulador:** con el bot de Jorge se puede (una partida en la Liga).

## Pendiente

- Probarlo en el emulador: tienda, mensaje al no poder curar, que deje curar después de que el rival use un RESTAURAR TODO, y la cura al entrar en cada sala.
