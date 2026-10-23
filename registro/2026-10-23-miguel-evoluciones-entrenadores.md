# 23/10/2026 · Miguel · Evoluciones de los entrenadores normales

Cuarta tarea de equilibrio de la sesión de Miguel. Rama `miguel/evoluciones-entrenadores`, encima de `miguel/equipos-jefes` (PR #5).

## Por qué

Tras el reescalado, muchos entrenadores llevaban Pokémon sin evolucionar a niveles altos (un Swablu a 50, un Poochyena a 40…). En el diseño eso lo hace el randomizer, pero hasta que exista el juego se veía raro.

## Decisión de Miguel

- **Evoluciones por nivel:** a su nivel normal (Swablu → Altaria a 35).
- **Evoluciones que no son por nivel** (piedra, amistad, lugar…): la **primera a partir de nivel 30** y la **segunda a partir de 40**.

## Cómo se hizo

- `tools/dualocke/evolucionar_entrenadores.py` lee las evoluciones de `src/data/pokemon/species_info/` y las aplica a cada Pokémon de los entrenadores normales de Hoenn según su nivel.
- Parte siempre de las especies originales de la expansion, así que se puede volver a lanzar. Orden: `reescalar_niveles.py` → `equipos_jefes.py` → `evolucionar_entrenadores.py`.
- **Qué no toca:** jefes (ya lo hace `equipos_jefes.py`), revanchas, postgame ni entrenadores sin tramo.
- Solo cambia el nombre de la especie: se conservan los movimientos, el objeto, el género y el mote.
- **Evoluciones con varias opciones** (Eevee, Wurmple…): se elige una fija por entrenador y Pokémon, con un hash de su nombre. Así hay variedad, pero el resultado sale siempre igual.

## Resultado

- **342 Pokémon evolucionados** en 422 entrenadores normales. Todas las especies se reconocieron.
- Ejemplos: Poochyena → Mightyena, Zubat → Crobat (a partir de 40), Lotad → Ludicolo (a partir de 40), Seedot → Shiftry, Makuhita → Hariyama. Un Gloom a nivel 31 se queda como Gloom.

## Queda

- **Probar jugando.**
- Los movimientos originales se conservan al evolucionar. Alguno puede quedar flojo para el nivel, pero eso lo cambiará el randomizer ("movimientos aleatorios con preferencia por los potentes").
