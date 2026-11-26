# 26/11/2026 — Miguel: papeles de los equipos de los jefes, mejorados

## Qué se pidió

Miguel, jugando la versión 9.1, contra ALANA (6.ª medalla):
- Jugó con nieve: varios Pokémon que ponían la nieve, con Viento Hielo y Velo Aurora para bajar la velocidad y subir la defensa. "Eso está bien. Pero lo tenían todos los Pokémon".
- "No tiene ningún tipo de sentido que un Pokémon que sea atacante físico a tope y rápido use velo aurora".
- Quiere varios papeles: "uno que ponga el clima, o lo que use esa estrategia, otro que sea el que golpea fuerte y aproveche esos cambios, otro que sea más tanky". Que "no todos tengan meteoro bola, o no todos tengan viento hielo", y que haya otros al azar "que le den la gracia de que sea un randomlocke".
- En general, los jefes "repiten muchos movimientos o usan movimientos demasiado fuertes para el punto de la aventura".

La #128 de Jorge (fusionada el 25/11) ya daba un papel a cada uno: el primero ponía la estrategia, 1 o 2 la aprovechaban y el resto pegaba. La ROM de Miguel es de la 9.1, de antes de ese cambio.

**Lo que contestó Miguel antes de empezar:**

| Pregunta | Respuesta |
| --- | --- |
| ¿Sobre `master` o esperar a Jorge? | Sobre `master` |
| Papeles: pone / aprovecha / tanque / al azar | Sí, así |
| ¿Quién pone la estrategia? | El que mejor encaje, y que vaya el primero del equipo |
| Lo que no cabe en el tope | Alternativas más flojas que quepan |

**Para la versión siguiente:** las ROMs del locke en curso no cambian.

## Qué se ha hecho (rama `miguel/papeles-jefes`)

- **`aleatorio/estrategia.py`:**
  - `papeles()` reparte "pone", "aprovecha", "tanque" y "libre" según el tamaño del equipo. Elige a cada uno por sus estadísticas y su tipo, con un poco de azar con la semilla.
    - El que pone y el tanque nunca son el as.
    - El que pone es el que aguanta y pega menos, para que los que pegan fuerte queden para aprovechar la estrategia.
  - `_de_estrategia()` da, por papel y estilo, huecos con un fin distinto (poner el clima, un ataque que lo aproveche, una mejora…), cada uno con alternativas. La tabla está en `DUALOCKE.md`.
  - Con Clima, el que pone lleva algo que le sirva a él, porque si no la IA no pone el clima (`BenefitsFromSun` y compañía, `src/battle_ai_field_statuses.c`):
    - con nieve, Velo Aurora;
    - si es especial, Meteorobola;
    - si es físico, un ataque del tipo del clima.

    Los que aprovechan llevan ataques que pegan más con el clima, de su categoría: el físico, Envite Ígneo y no Meteorobola.
  - `elegir()`:
    - cada movimiento de estrategia sale una vez por equipo (`LIMITE_EQUIPO`: el clima, Meteorobola, Espacio Raro, Viento Afín y Protección, dos);
    - los ataques que ya lleva un compañero solo se usan si no queda otra;
    - el movimiento al azar nunca repite uno del equipo, ni es Velo Aurora, ni una segunda mejora.
  - El tope de potencia cuenta todos los golpes (`potencia_real`): Dracoflechas, 100; los de 2 a 5 golpes, 3 veces su potencia; Triple Axel, 120.
  - Lo que no cabe en el tope se cambia por otro del mismo tipo más flojo. CANDELA, a nivel 43 (tope 104), ya no se queda sin ataque de sol: lleva Onda Ígnea o Lanzallamas en vez de Rayo Solar.
- **`aleatorio/movimientos.py`:** cada movimiento sabe cuántos golpes da (`golpes`). Solo lo usa el tope de los jefes: los entrenadores normales no cambian.
- **`aleatorio/entrenadores.py`:**
  - elige los movimientos por orden de papel, empezando por el que pone, para que nadie le quite los suyos;
  - después, el que pone pasa a ser el primero del equipo, con su nivel;
  - los jefes sin estrategia salen exactamente igual que antes.
- **`tools/dualocke/probar_papeles.py` (nuevo):** la prueba de abajo, sin compilador. Devuelve 1 si algo falla.
- **`DUALOCKE.md`:** "Papeles mejorados", debajo de los de la #128.

Ejemplo, un equipo de nieve de 6 a nivel 41-44 (semilla 1 de la prueba, en el orden final):
- **pone**, Altaria: Paisaje Nevado y Velo Aurora;
- **tanque**, Skarmory: Respiro y Paisaje Nevado;
- **aprovechan**:
  - Weavile: Chuzos y Danza Dragón;
  - Abomasnow: Pirueta Helada y Corpulencia;
- **libres**, Glalie y Pelipper: sus ataques y uno al azar.

## Cómo se comprobó

- **Sin compilar:** aquí no hay preprocesador, así que no se ha lanzado el randomizer entero con una semilla.
- **`probar_papeles.py`:**
  - especies y movimientos reales, leídos a mano;
  - los equipos de 15 jefes de `trainers.party`;
  - 14.400 equipos: 8 estilos, 60 semillas, 1 y 2 movimientos de estrategia;
  - **0 fallos** en todo lo que mira (ver la lista en el propio script).
- **Durante la prueba salieron y se arreglaron:**
  - dos mejoras en el mismo Pokémon (Maquinación y Danza Aleteo);
  - Velo Aurora como movimiento al azar;
  - ataques de la tabla repetidos entre compañeros;
  - un atacante físico poniendo la nieve.
- **Las funciones nuevas de `entrenadores.py`:** probadas aparte (orden y cambio de hueco). Sin estrategia no cambian nada.
- **`comprobar_zonas.py`, `alcance.py`, `sin_salida.py` y `variantes.py`:** 0.

## Pendiente

- **Jorge:**
  - `make release` con una semilla, para ver que el randomizer entero va y que solo cambian los movimientos (y el orden) de los jefes con estrategia;
  - probar con el bot un combate con Clima y otro con Espacio Raro.
- **La ROM de Luis** se hizo con los papeles de la #128; si se rehace con esta rama, sus jefes cambian.
