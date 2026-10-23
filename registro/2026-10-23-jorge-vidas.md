# 23/10/2026 · Jorge · Vidas y caja de muertos

## Qué se pidió

Implementar la regla de las vidas del locke: 20 vidas más la "vida 0", y los Pokémon muertos guardados en una caja del PC que no se puede usar.

## Cómo funciona

- Al empezar partida nueva: 20 vidas (`VAR_DUALOCKE_LIVES`, antes `VAR_UNUSED_0x404E`) y la caja 14 se llama "DEAD".
- Al terminar un combate, cada Pokémon del equipo con 0 PS (que no sea huevo) se mueve a la caja de muertos, se borra del equipo y se resta una vida. El equipo se compacta.
- Con 0 vidas se sigue jugando. La siguiente muerte activa `FLAG_DUALOCKE_LOCKE_LOST` (antes `FLAG_UNUSED_0x020`).
- Perder un combate (todo el equipo debilitado) también activa `FLAG_DUALOCKE_LOCKE_LOST`. En ese caso no se mueve a nadie, porque el equipo no puede quedarse vacío; el juego hace el *whiteout* normal.
- El juego no se bloquea al perder el locke: solo se marca. El menú de pausa muestra "Lives: N" o "LOCKE LOST".
- Caja de muertos: solo se puede ver el resumen. No se puede retirar, mover (ni uno ni varios), soltar ni depositar nada, y `CopyMonToPC` nunca manda Pokémon nuevos ahí.
- Los objetos de revivir no se pueden usar en combate (mismo bloqueo que los Objetos X).
- No cuentan como combates del locke: cable/link y grabados, Frontera, Pirámide, Pike, Cima Entrenador, Safari, el primer combate (el de la mochila del Prof. Abedul), e-Reader y bases secretas.

## Archivos

- Nuevos: `src/dualocke.c`, `include/dualocke.h`, `test/dualocke.c`.
- `src/battle_setup.c`: llamada a `Dualocke_OnBattleEnd` al final de los combates salvajes, salvajes con script, de entrenador y de revancha (después de restaurar el equipo en combates con compañero).
- `src/pokemon_storage_system.c`: bloqueo de la caja de muertos.
- `src/pokemon.c`: `CopyMonToPC` se salta la caja de muertos.
- `src/start_menu.c`: ventana de vidas.
- `src/item_use.c`: revivir bloqueado en combate.
- `src/new_game.c`: inicialización.
- `include/constants/vars.h`, `include/constants/flags.h`: nombres de la variable y la flag.

## Pruebas

- Compila (`make`).
- Tests automáticos en `test/dualocke.c`: una muerte, varias muertes, vida 0, perder un combate, combates de la Frontera y que los Pokémon nuevos no van a la caja de muertos.
- **Falta probarlo jugando en mGBA**: que la ventana del menú se ve bien y que la caja de muertos se comporta como debe.

## Pendiente

- Aviso al morir ("X ha muerto. Te quedan N vidas."). Ahora solo se nota porque desaparece del equipo y por el menú.
- Revival Blessing (el movimiento) sí puede revivir en combate; es muy raro y se deja por honor.
- Los textos nuevos están en inglés como el resto del juego; se traducen con todo lo demás.

## Arreglo posterior (PR aparte)

El CI de la PR #4 falló en `test`: el test de la expansion "Revive can only be used if the selected Pokémon has fainted" (`test/battle/item_effect/revive.c`) espera que Revivir se pueda usar en combate, justo lo que bloquea la regla. Se arregla como el level cap: el bloqueo de revivir no se aplica al compilar los tests (`!TESTING` en `src/item_use.c`). En el juego no cambia nada.
