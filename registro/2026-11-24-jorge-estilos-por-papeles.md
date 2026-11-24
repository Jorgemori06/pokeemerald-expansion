# 24/11/2026 — Jorge: estilos de los jefes repartidos por papeles

## Qué se pidió

Jorge, después de la 4.ª medalla: "casi todos los Pokémon de MAGNO y la líder del gimnasio tenían Día Soleado y Meteorobola". En su semilla, a los dos les tocó el estilo Clima. Los dos son de Fuego, así que llevan sol. Ese estilo metía los dos movimientos en **todos** los Pokémon del equipo.

Miguel: la idea de los estilos está bien, "porque si no es solo pegar, pegar y pegar". Jorge: "yo lo modificaría para que tenga más sentido; no todos lo mismo".

**Para la versión siguiente.** El locke en curso no se toca: las ROMs de ahora no cambian.

## Qué se ha hecho

Lo propuso Claude y Jorge lo aceptó. Cada Pokémon del jefe tiene un papel (`papeles()` en `tools/dualocke/aleatorio/estrategia.py`):

- **El que la pone:** el primero del equipo, con lo mismo que antes (el clima y Meteorobola, las trampas, las pantallas…).
- **Los que la aprovechan:** 1 en equipos de hasta 4 y 2 en equipos de 5 o 6. Se eligen los que mejor le sacan partido al estilo:
  - en Clima, los de su tipo y, después, los de más Ataque Especial;
  - en Espacio Raro, los lentos;
  - en Aguante, los más duros.
  - Lo que llevan está en la tabla de `DUALOCKE.md`. Por ejemplo, en Clima: Meteorobola y Rayo Solar con sol, o Trueno con lluvia.
- **El resto:** sin movimientos de estrategia, solo sus mejores ataques y uno al azar.

`entrenadores.py` elige primero todo el equipo y luego los movimientos, para saber el papel de cada uno. Los movimientos tienen su propio generador al azar por Pokémon, así que este cambio de orden no toca nada más.

## Comprobado

- **Con la semilla de Jorge** (`2635893558`):
  - solo cambian los movimientos de los 36 entrenadores con estrategia (líderes, Alto Mando, PLUBIO, rival, MAGNO, AQUILES y admins);
  - no cambia ninguna especie, y los salvajes, los iniciales y `dualocke_aleatorio.h` salen igual.
- **CANDELA:**
  - antes, los seis con Día Soleado y Meteorobola;
  - ahora, Rabsca pone el sol con Meteorobola, Farigiraf y Tauros de Paldea (Fuego) llevan Meteorobola y Rayo Solar, y Sableye, Medicham y Crawdaunt van con sus ataques.
- **MAGNO en el Monte Cenizo:** Rapidash pone el sol, Thievul lo aprovecha, y Crustle y Golem van con sus ataques.
- `make release SEED=2635893558` compila.

## Pendiente

- El tope de potencia de los movimientos de los jefes sigue pendiente (lo apuntó Jorge el 23/11; es de equilibrio, para Miguel). Con este cambio, los que no tienen papel llevan un ataque más de su tabla en vez de los dos de estrategia, así que pegan algo más.
