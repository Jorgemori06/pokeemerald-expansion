# Ideas para personalizar el juego

Ideas de Jorge y Miguel para darle un toque propio al Dualocke. **No se implementan todavía**: se guardan aquí y se hacen cuando el juego esté terminado y todo funcione.

> **Para Claude:** no implementes nada de este archivo salvo que te lo pidan expresamente. Cuando una idea se haga, márcala como hecha y enlaza el PR.

## Cómo apuntar una idea

Una sección por idea, con:

- **Qué:** la idea en una o dos frases.
- **Propuesta de:** quién la tuvo y cuándo.
- **Notas:** lo que haga falta saber para hacerla (qué hay que tocar, dudas…).
- **Estado:** Pendiente / En curso / Hecha (PR #…).

## Ideas

### 1. Gonzalo Plaza como Campeón

- **Qué:** sustituir al Campeón por **Gonzalo Plaza**, con un aspecto de señor mayor (profesor).
- **Propuesta de:** Miguel, 23/10/2026.
- **Notas:**
  - Hay que cambiar el nombre y la clase del entrenador (`TRAINER_WALLACE` en `src/data/trainers.party`) y los textos de la sala del Campeón (`data/maps/EverGrandeCity_ChampionsRoom/`).
  - Para el aspecto, sirven los gráficos de un personaje mayor que ya existe en el juego (por ejemplo, el del profesor Abedul o un "Gentleman"), o unos nuevos: el sprite de combate y el del mapa.
  - El equipo y los niveles del Campeón (sección 6 de `DUALOCKE.md`) se pueden mantener o adaptar a él.
- **Estado:** Pendiente.
