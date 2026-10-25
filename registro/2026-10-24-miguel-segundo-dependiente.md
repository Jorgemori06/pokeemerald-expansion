# 24/10/2026 · Miguel · Segundo dependiente de las tiendas

Tarea de Jorge que adelanta Miguel (reservada en el PR #18), junto con su contenido, que era de Miguel. Rama `miguel/segundo-dependiente`.

## Decisiones de Miguel

| Pregunta | Decisión |
| --- | --- |
| ¿Qué vende? | **Equipables y evolutivos** (las megapiedras ya están por el mapa) |
| ¿Cuántos y cuándo cambian? | **3-4 fijos por partida** |
| ¿Dónde? | **Tiendas de ciudad** (11): no en Calagua, la Liga, el Frente ni la Cima |

## Cómo se hizo

- **Dónde está:** las 11 tiendas usan el mismo interior (`LAYOUT_MART`). El segundo dependiente va en **(1, 2)**, detrás del mostrador y encima del principal. Se le habla desde (3, 2), a través del mostrador (casilla `MB_COUNTER`).
  - En Verdegal había una chica en (3, 2): se ha movido a (9, 6), una esquina libre lejos de la puerta.
- **Script común:** `Dualocke_EventScript_SegundoDependiente`, en `data/scripts/dualocke_segundo_dependiente.inc`, incluido en `data/event_scripts.s`. Todas las tiendas usan el mismo.
- **Special `Dualocke_AbrirSegundoDependiente`** (`src/dualocke_segundo_dependiente.c`, registrado en `data/specials.inc` con `waitstate=1`):
  - genera la lista y abre la tienda normal con `CreatePokemartMenu`;
  - al cerrarla, el script sigue, igual que con `pokemart`.
- **Lista:** 1 evolutivo (de 27) y 3 equipables distintos (de 26).
  - Semilla: ID de entrenador ^ número de tienda. Es la misma en toda la partida y distinta entre partidas, porque no depende del randomizer.
  - Pasa por el filtro de medallas de `src/shop_criteria.c`, así que un evolutivo no aparece hasta su medalla y en las primeras ciudades puede verse solo con 3 objetos.
- **Fuera de los equipables:** la Cinta Elegida (cuesta 100.000 ₽ y es de las fuertes) y la Raíz Grande (ya está en el mapa).

## Queda

- **Una compra por objeto** también en este dependiente: se hará cuando entre el PR #19, con un bit por (tienda, hueco). Hacen falta 44 bits, es decir, 3 variables libres más.
- **Probar jugando:** que el dependiente sale, se le puede hablar y abre su tienda en las 11 ciudades.
