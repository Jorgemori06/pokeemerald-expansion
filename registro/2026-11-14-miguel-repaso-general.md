# 14/11/2026 — Miguel: repaso general

## Qué se pidió

Revisar todo lo hecho, aceptar los PRs que quedaran, buscar fallos y mejoras (traducción, IA de los combates…) y plantear ampliar el mapa con rutas, casas y NPC con eventos o combates con recompensa. Preguntar las dudas antes de hacer lo grande.

## PRs

- **Aprobados y fusionados (todos de Jorge):**
  - #66: ningún salvaje por encima del cap;
  - #67: menús de opciones;
  - #68: textos comunes;
  - #70: el muerto que se cambia por la captura;
  - #71: la tele, el hombre de Malvalona y las carpas;
  - #72: la amistad en la pantalla de datos.
- **Conflictos resueltos** dejando los dos lados:
  - #68: `DUALOCKE.md` y `LEEME.md`;
  - #70: `include/dualocke.h`.
- **#69 (MO para todas las especies, de Miguel):** actualizado con `master` (conflicto en `test/dualocke.c`). Falta que lo apruebe Jorge.
- **Corrección de la nota del #66:** las evoluciones por amistad son `EVO_LEVEL` con parámetro 0, así que `EvolutionLevelFor` ya las trata como el randomizer. No hay nada que cambiar.

## Lo que se ha revisado

- **Reglas del locke (`src/dualocke.c`):** vidas, entierro, captura por zona, ramas evolutivas, caja de prohibidos y tope de los salvajes. Sin fallos a la vista.
  - Los combates del Frente y de las carpas no pasan por `Dualocke_OnBattleEnd`, y las bases secretas se excluyen por el entrenador.
- **IA (`trainers.party`, `include/config/ai.h`, `randomizer_config.json`):**
  - 640 entrenadores normales con `Check Bad Move`: solo evitan los movimientos que fallan y eligen al azar entre el resto.
  - 174 con `Basic Trainer`: el rival, BLASCO, MAGNO, AQUILES, los admins y MÁXIMO.
  - 13 con `Smart Trainer / Hp Aware / Ace Pokemon`, puesta por el randomizer: líderes, Alto Mando y PLUBIO.
- **Traducción:** medido qué queda (está en `DUALOCKE.md`, sección 8).

## Qué se ha cambiado (este PR)

- **Clases de entrenador en español:** las 59 de Hoenn, con `ES()` en `src/battle_main.c`. Salían en inglés en todos los combates.
- **Ventana de información del movimiento en combate:** "POT:" y "PRE:" (`src/battle_controller_player.c`).
- **Tres frases con género** del #68, en `57_sueltos_comunes.tsv` y aplicadas:
  - "Bienvenido a casa";
  - "Bienvenido a los GRANDES ALMACENES";
  - "un ENTRENADOR listo".
- **Plegaria Vital fuera de las MT y los tutores (`mts.py`):** revive a un debilitado en combate y se saltaría las muertes.
  - Se sortea igual que antes y solo se cambia la MT o el tutor que caiga en ella.
  - Los tutores parten del sorteo de las MT sin sustituir, para salir igual.
  - `comprobar()` nuevo, que lanza `randomizer.py`.
- **`DUALOCKE.md`:** sección 8 (qué queda en inglés, clases) y sección 7 (Plegaria Vital).

## Cómo se comprobó

- **Diálogos:** `dialogos.py comprobar` da 5551 textos y 0 errores.
- **MT y tutores:** 400 semillas con los movimientos de `moves_info.h`. En 29 salía Plegaria Vital, y en todas solo cambia esa MT o ese tutor (o un tutor que coincidía con el sustituto).
- **Clases:** todas caben en 12 caracteres, y las letras con tilde están en `charmap.txt`.
- **Sin compilar:** en el PC de Miguel no hay WSL.

## Pendiente

**Lo decide Miguel:**
- IA de los jefes de mitad de tramo y de los entrenadores normales.
- Contenido nuevo en el mapa (NPC con combates y recompensas, casas, rutas).
- Qué ideas de `IDEAS.md` se hacen.

**Apuntado, sin hacer:**
- La regla de una compra por objeto no se aplica al segundo dependiente.
- De los estáticos solo se debería poder capturar el primero de cada tipo.
- Los nombres de las bayas de `src/berry.c` siguen en inglés.
- Con la semilla de cada uno no se sabe si alguna MT enseñaba Plegaria Vital: lo dirá el solucionario al regenerar la ROM.
