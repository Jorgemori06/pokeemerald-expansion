# 23/10/2026 · Miguel · Revanchas, postgame y Casa Trampa

Tarea de equilibrio de la sesión de Miguel. Rama `miguel/revanchas-postgame`.

## Decisiones de Miguel

| Pregunta | Decisión |
| --- | --- |
| Revanchas de entrenadores normales | **Proporción del original, con límites por escalón** |
| Postgame | **Todo a 100** |
| Casa Trampa | **Al tramo de la medalla que abre cada prueba** |

## Cómo se hizo

Todo en `tools/dualocke/reescalar_niveles.py`; `evolucionar_entrenadores.py` ahora evoluciona también las revanchas y el postgame.

- **Revanchas:**
  - Se leen de `gRematchTable` (`src/battle_setup.c`).
  - Se activan con 5 medallas (`OW_REMATCH_BADGE_COUNT`), y el entrenador te reta en cuanto te ve.
  - **Primero se probó la proporción pura**, y salían revanchas de nivel 22 a 90 con cap 62: las de las primeras rutas, un paseo, y las de las últimas, más de 25 niveles por encima del cap. Miguel eligió **proporción con límites**: se calcula la proporción y se reparte dentro de \_2 47-59, \_3 59-70, \_4 70-81 y \_5 81-97, manteniendo el orden.
  - Las revanchas de **líderes y Blasco** van a 100.
- **Postgame:** un tramo 10 con los entrenadores a 100 y los salvajes a 97 (S.S. Marea, Cueva de Máximo, Túnel del Desierto, Cueva Ancestral, Cueva Alterada, cuevas Terra y Marina).
- **Casa Trampa:** la prueba 1 está disponible desde el principio (tramo 3), y la prueba N (de la 2 a la 8) pide la medalla N+1 (`Route110_TrickHouseEntrance/scripts.inc`).
  - **Fallo detectado y corregido:** al meterla en los tramos se movían las bandas, y con ellas los niveles de la historia principal (por ejemplo, los salvajes del tramo 9 pasaban de 78-85 a 78-88). Ahora la Casa Trampa no cuenta para la banda.
- **Comprobado contra `master`:** solo cambian las revanchas, la Casa Trampa, el S.S. Marea, la Cueva de Máximo y los salvajes del postgame. La historia principal queda igual. Al relanzar los tres scripts, el resultado no cambia.

## Resultado

- **744 entrenadores con nivel nuevo** (antes 477) y **713 Pokémon evolucionados**.
- Ejemplos de revancha: Rosa 47 → 59 → 70 → 81 → 97; Lola 20 → 51 → 63 → 74 → 87.

## Queda

- El Frente Batalla y la Cima Entrenador no se tocan: tienen su propio sistema de niveles.
- **Probar jugando.**
