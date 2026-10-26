# 26/10/2026 — Jorge: bolsillos Medicinas y Megapiedras en la mochila

## Qué se pidió

Al probar la ROM, Jorge vio que las megapiedras y las pociones se guardaban en Objetos. Pidió dos bolsillos nuevos, **Medicinas** y **Megapiedras**, sin dibujar mochila nueva (reutilizando los dibujos) y repartiendo los objetos. Es una funcionalidad nueva, no un arreglo. Las partidas guardadas de antes dan igual (eran de prueba).

## Qué se ha hecho

- **Bolsillos nuevos** `POCKET_MEDICINE` y `POCKET_MEGA_STONES` en `enum Pocket` (`include/constants/item.h`). Orden en la mochila: Objetos, Medicinas, Poké Balls, MT y MO, Bayas, Megapiedras, Obj. clave.
- **Espacio:** 60 huecos de medicinas y 100 de megapiedras (hay 92) en `SaveBlock3` (`include/global.h`), que solo usaba 1 byte de 1624. `SaveBlock1` no se toca (le quedan 376 bytes). `SetBagItemsPointers` y `ClearBag` (`src/item.c`) los enlazan y los vacían.
- **Reparto (`.pocket` en `src/data/items.h`):**
  - Medicinas: 69 objetos con `sortType` de curar PS, estados o PP, vitaminas, plumas, mochis y caramelos (Caramelo Raro, Caramelos Exp.). La Miel tenía el tipo de los caramelos, pero se queda en Objetos.
  - Megapiedras: los 92 objetos con `HOLD_EFFECT_MEGA_STONE`.
- **Menú de la mochila (`src/item_menu.c`):**
  - menú de usar/dar/tirar para los bolsillos nuevos (el mismo que Objetos);
  - 7 cuadraditos centrados (columnas 4-10; el fondo traía 5);
  - nombre con la fuente estrecha si no cabe (MEGAPIEDRAS);
  - el tutorial de Blasco guarda y devuelve el bolsillo de medicinas, y abre en Medicinas para que al pasar a la derecha salgan las Poké Balls, como antes.
- **Dibujos:** Medicinas usa el de Objetos y Megapiedras el de Obj. clave (`src/item_menu_icons.c`).
- **Nombres traducidos:** los de los bolsillos (`src/strings.c`) y los del mensaje "guardado en el BOLSILLO …" (`src/data/script_menu.h`, nuevos `STDSTRING_MEDICINE` y `STDSTRING_MEGA_STONES`). Antes salía "BOLSILLO ITEMS".
- **Scripts:** `data/scripts/obtain_item.inc` con los dos bolsillos nuevos (sin esto, el script se cortaba al recoger una medicina). Las bebidas de la máquina de la azotea de Calagua dicen MEDICINAS.
- **Depuración (`src/debug.c`):** "Fill Pocket Items" también llena Medicinas y da una de cada megapiedra.
- **Tests (`test/dualocke.c` y el tamaño de `SaveBlock3` en `test/save.c`):** a qué bolsillo va cada tipo de objeto, guardar/quitar/vaciar, que caben todas las megapiedras y que todos los bolsillos tienen nombre.
- `DUALOCKE.md`: sección 6 (apartado nuevo), sección 9 y mapa del código.

## Cómo se comprobó

- `make` compila sin errores ni avisos (`SaveBlock3` cabe).
- `make check TESTS="Dualocke"`: los 4 tests nuevos en verde.
- `make check` completo: 5454 en verde. El único fallo era `SaveBlock3 is backwards compatible`, que comprueba el tamaño de `SaveBlock3`: crece a propósito (de 4 a 644 bytes), así que se ha actualizado el número en `test/save.c`.
- No hay emulador aquí: lo visual (cuadraditos, nombre MEGAPIEDRAS, cambio de dibujo) hay que mirarlo jugando.

## Pendiente

- Probarlo en el emulador: abrir la mochila, pasar por los 7 bolsillos, recoger una poción y una megapiedra, usar una poción en combate y darle una megapiedra a un Pokémon.
- Si se quiere, dibujar más adelante una mochila con 7 bolsillos.
