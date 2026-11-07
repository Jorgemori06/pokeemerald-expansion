# 07/11/2026 — Jorge: objetos de los Pokémon muertos

## Qué se pidió

Jugando la versión 5, a Jorge se le murió un Tyrogue que llevaba una Baya Aranja, y no podía quitársela en la caja de muertos (mandó una captura).

## Causa

La caja de muertos está bloqueada a propósito: solo deja ver el resumen. Así que el objeto se quedaba atrapado para siempre.

## Qué se ha hecho

- `Dualocke_RecoverDeadMonsItems` (`src/dualocke.c`):
  - recorre la caja de muertos y pasa los objetos a la mochila, o al PC de objetos si ese bolsillo está lleno;
  - las cartas no, porque llevan texto del jugador;
  - si no caben en ningún sitio, el objeto se queda en el muerto hasta la próxima vez.
- Se llama:
  - al acabar cada combate del locke, después de enterrar a los muertos (`Dualocke_OnBattleEnd`);
  - al encender el PC (`ShowPokemonStorageSystemPC`).

  Así también vuelven los objetos de los que ya estaban muertos, como la Baya Aranja del Tyrogue.
- 2 tests en `test/dualocke.c`: el que muere en combate y el que ya estaba en la caja.
- `DUALOCKE.md` (vidas y caja de muertos) y `GUIA.html` (Novedades).

## Cómo se comprobó

- `make` compila sin avisos.
- `make check TESTS="Dualocke"`: 39/39.
- No se ha probado en el emulador.

## Pendiente

- Va en la próxima ROM. No cambia el randomizer ni lo que se guarda, así que vale con la misma semilla y la misma partida. Con esta ROM, la Baya Aranja del Tyrogue vuelve a la mochila al encender el PC.
