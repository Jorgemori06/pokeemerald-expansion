# 31/10/2026 — Jorge: captura con el equipo lleno (MO) y evoluciones raras en la guía

## Qué se pidió

Jorge, jugando su locke (Ciudad Férrica, Ruta 116), capturó un Tandemaus con el equipo lleno:

- El juego no le dejó mandar a la caja a uno del equipo porque sabía un movimiento de MO, aunque otro del equipo también lo sabía.
- En la Pokédex de la guía, Tandemaus salía con "Método especial" en vez de cómo evoluciona.

## Qué se ha hecho

- **Captura con el equipo lleno:**
  - La expansion (`B_CATCH_SWAP_CHECK_HMS`) bloqueaba a cualquier Pokémon que supiera una MO.
  - Ahora solo se bloquea si es el único del equipo que sabe alguna de sus MO. Los huevos no cuentan como otro que la sabe.
  - Está en `Dualocke_KnowsUniqueHM` (`src/dualocke.c`), que llama `DoesSelectedMonKnowHM` (`src/party_menu.c`).
  - El mensaje ahora dice "es el único que sabe un mov. de MO".
- **Guía (`tools/dualocke/guia_pokedex.py` y `GUIA.html`):** ya no queda ningún "Método especial".
  - Tandemaus: "Nivel 25, subiendo de nivel en un combate". Con Caramelo Raro fuera de combate no evoluciona (`EVO_LEVEL_BATTLE_ONLY`).
  - Shedinja: "Aparece al evolucionar, si hay hueco en el equipo y con Poké Ball en la mochila".
  - Sirfetch'd: "Al acabar un combate en el que haya dado 3 golpes críticos".
  - Runerigus y Urshifu: "No puede evolucionar en este juego" (necesitan sitios de Galar).
  - Dos líneas nuevas en Novedades.
- `DUALOCKE.md`: sección 4 (captura con el equipo lleno) y sección 9 (guía).

## Cómo se comprobó

- `make` compila sin errores ni avisos.
- `make check TESTS="Dualocke"`: 3 tests nuevos (otro sabe la MO, es el único y huevos), todos en verde.
- La guía se ha regenerado con `python3 tools/dualocke/guia_pokedex.py`.

## Disco Eléctrico (sigue abierto)

- Jorge tiene 10 Discos Eléctricos en la mochila: les salía a todo el equipo o al Pokémon recién capturado.
- Con su partida en el arnés de mGBA, la causa no se ha encontrado. Se han probado más de 30 combates:
  - con y sin objeto en el salvaje;
  - atacando antes;
  - primera captura de la zona;
  - especie nueva en la Pokédex;
  - Tauros e Iron Hands;
  - con el equipo lleno y sin llenar.
- El disco no puede venir de los objetos al azar de los salvajes: tiene 1 posibilidad entre 10.000.
- Sí puede venir de la devolución de objetos al acabar el combate (`TryRestoreHeldItems`, `RestoreCaughtWildMonHeldItem`), si `gBattleStruct->itemLost` se machaca con 0x0111.
- Jorge no usa trucos ni estados, y lo vio un rato después de capturar.
- Si le vuelve a pasar, pasará el `.sav` antes de quitar los discos, y un `.ss1` de antes de la captura si puede.

## Pendiente

- Probar en el emulador el cambio de la MO.
- ROMs versión 5 con las mismas semillas: la partida guardada sigue valiendo, porque no cambia lo que se guarda ni el randomizer.
