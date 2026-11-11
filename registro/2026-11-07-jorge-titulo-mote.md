# 07/11/2026 — Jorge: título de la pantalla del mote

## Qué se pidió

Jugando la versión 5, Jorge vio que la pantalla del mote decía "Torchic¿Mote de ?" (mandó una captura).

## Causa

`DrawMonTextEntryBox` (`src/naming_screen.c`) escribía el nombre de la especie y le pegaba detrás el título. En inglés el título es "{STR_VAR_1}'s nickname?", y ese `{STR_VAR_1}` sale vacío al imprimir: quedaba "Torchic's nickname?" y no se notaba. La traducción "¿Mote de {STR_VAR_1}?" lleva el hueco en medio, y salía "Torchic¿Mote de ?".

## Qué se ha hecho

- `Dualocke_BuildMonNamingTitle` (`src/naming_screen.c`, declarada en `include/naming_screen.h`):
  - mete la especie en el hueco `{STR_VAR_1}` del título, con la fuente estrecha si no cabe, como antes;
  - si el título no lleva hueco, pone la especie delante, como antes.
- No toca `gStringVar1`, así que no afecta a los scripts que llaman a la pantalla.
- Test nuevo en `test/dualocke.c`: castellano, inglés y título sin hueco.
- `DUALOCKE.md`, sección de la traducción: el arreglo y los botones de la pantalla de nombres, que siguen en inglés (son imágenes).

## Cómo se comprobó

- `make` compila sin avisos.
- `make check TESTS="Dualocke"`: 38/38.
- No se ha visto en el emulador.

## Pendiente

- Los botones de la pantalla de nombres (lower, BACK, B BUTTON, OK, START, SELECT) son imágenes en inglés, en `graphics/naming_screen/`.
- Va en la próxima ROM. No cambia el randomizer ni lo que se guarda, así que se puede usar con la misma semilla y la misma partida.
