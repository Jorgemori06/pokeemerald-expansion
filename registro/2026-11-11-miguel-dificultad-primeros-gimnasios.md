# 11/11/2026 — Miguel: primeros gimnasios más suaves

## Qué se pidió

Jorge y Miguel ven que los primeros gimnasios son demasiado difíciles. Datos de la semilla de Jorge (`2780853751`, versión 5):
- **PETRA:** 5 Pokémon a nivel 16, todos con Mineral Evolutivo, IVs 24, IA lista y 2 Pociones. En el original eran 3 Pokémon a 12-15.
- **MARCIAL:** 5 Pokémon a 23, también con Mineral Evolutivo en todo el equipo.

Las causas:
- `objeto_coherente` daba Mineral Evolutivo a todo el que pudiera evolucionar, sin mirar si ya había otro en el equipo;
- `equipos_jefes.py` les daba 5 Pokémon;
- `reescalar_niveles.py` pone a todo el equipo de los líderes al cap.

## Qué decidió Miguel

- **PETRA, MARCIAL y ERICO:** 4, 4 y 5 Pokémon, con el as al cap y el resto 1-2 niveles por debajo.
  - PETRA: 14, 15, 15, 16 (sin Onix).
  - MARCIAL: 21, 22, 22, 23 (sin Mankey).
  - ERICO: 30, 31, 31, 31, 32 (sin Raichu).
- **Curas:** una cada uno (Poción, Superpoción y Superpoción).
- **Mineral Evolutivo:** ninguno hasta el gimnasio 3 y, después, como mucho uno por equipo.
- **Objetos hasta el gimnasio 3:** un punto medio. Al probarlo, sin el Mineral salían Vidasfera, Cinta Experto o Cinta Fuerte, así que Miguel eligió la lista:
  - sí: bayas que suben estadísticas, Baya Zidra, Cinta Fuerte, Gafas Especiales, Pañuelo Elección y potenciadores de tipo;
  - no: Vidasfera, Cinta Elección ni Gafas Elección.

## Qué se ha hecho

- **`tools/dualocke/equipos_jefes.py`:**
  - `EQUIPOS` con un Pokémon menos para los tres;
  - tablas nuevas `NIVELES_EQUIPO` (niveles por hueco) y `CURAS` (la línea `Items:`).
- **`src/data/trainers.party`:** regenerado con los tres scripts en orden (`reescalar_niveles.py`, `equipos_jefes.py` y `evolucionar_entrenadores.py`). Solo cambian `TRAINER_ROXANNE_1`, `TRAINER_BRAWLY_1` y `TRAINER_WATTSON_1`. `wild_encounters.json` y los estáticos no cambian.
- **`tools/dualocke/aleatorio/entrenadores.py`:**
  - `objeto_coherente`: como mucho un Mineral Evolutivo por equipo (afecta a todos los jefes);
  - con tope de fuerza (los de `limite_salvajes`), usa `objeto_suave` con la lista de Miguel.
- **Documentación:** `DUALOCKE.md` (secciones 5, 6 y 7) y `PRUEBAS.md`.

## La semilla de Jorge

Cada entrenador se sortea con su propia semilla (`{semilla}|entrenadores|{trainer}`, `{semilla}|movimientos|{trainer}|{i}`). Con la misma semilla:
- **Cambian por completo:** PETRA, MARCIAL y ERICO, que tienen otro tamaño y otros niveles.
- **Cambian solo los objetos:**
  - los jefes con tope (el rival hasta la Ruta 110 y BLASCO en Malvalona);
  - los jefes posteriores que tenían más de un Mineral Evolutivo. El sorteo del objeto usa el generador de ese Pokémon después de los movimientos, así que no mueve nada más.
- **No cambia nada más:** especies, movimientos y el resto de entrenadores quedan igual.

## Cómo se comprobó

- **`trainers.party`:** comparado entero con `master`. Solo son distintos los bloques de los tres líderes.
- **Sin compilar:** en el PC de Miguel no hay WSL ni compilador. Se probó el generador con una Pokédex pequeña de mentira y los movimientos de verdad:
  - PETRA (con tope) nunca lleva Mineral Evolutivo, Vidasfera, objetos Elección (salvo Pañuelo) ni Cinta Experto. En 40 semillas solo salen bayas, Cinta Fuerte y potenciadores.
  - ALANA (sin tope) lleva como mucho un Mineral Evolutivo.
  - `comprobar()` de los entrenadores no da errores.

## Pendiente

- **Claude de Jorge:**
  - compilar;
  - con la semilla `2780853751`, comprobar que solo cambian esos jefes (y los objetos citados arriba);
  - pasar `make check` y hacer las ROMs.
- **Probarlo jugando:** PETRA, MARCIAL y ERICO.
- **Ojo, PR #59:** el tope y los objetos usan la suma de estadísticas, que `especies.py` lee mal para unas 90 especies. Se arreglará al empezar partida nueva.
