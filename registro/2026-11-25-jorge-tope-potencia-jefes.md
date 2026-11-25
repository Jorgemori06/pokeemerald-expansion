# 25/11/2026 — Jorge: tope de potencia de los jefes y ROM de Luis

## Qué se pidió

1. Una ROM con otra semilla al azar para Luis, un colega de Jorge.
2. Jorge: "aplica en esta ROM los cambios que hemos dicho para que estén más balanceados los jefes". Son dos:
   - los **papeles** de los estilos (#128);
   - el **tope de potencia**, apuntado el 23/11 por el Pawmo de MARCIAL que hizo perder a todo el equipo a Miguel.

## Qué se ha hecho

- **Tope de potencia para los jefes con estrategia:** sus ataques no pasan de 40 + 1,5 × nivel.
  - Se configura en `lideres.potencia_maxima` de `randomizer_config.json`; `null` lo quita.
  - Lo aplica `estrategia.elegir()` a los ataques que aprenden por nivel, a los de estrategia y al ataque al azar.
- **Es la fórmula que tenían todos los entrenadores** (`potencia_maxima_del_cuarto`) hasta el 31/10. Ese día Jorge y Miguel la quitaron para que los movimientos fueran totalmente al azar. **Los entrenadores normales siguen así**: solo cambian los jefes.
- **Si a un jefe no le cabe nada de lo que aprende por nivel,** los ataques que faltan salen al azar entre los que caben, mejor de su tipo.

## Comprobado

- **Tres semillas:** Jorge `2635893558`, la vieja de Miguel `3483218843` y Luis `2121598288`.
  - Ningún líder ni Alto Mando pasa del tope.
  - Las especies no cambian.
- **El Pawmo de MARCIAL (semilla vieja de Miguel):**
  - antes, Fuerza Bruta, Rayo Fusión, Esquirla Helada y Onda Trueno;
  - ahora, Llave Corsé, Dracoflechas, Fortaleza y Viento Plata.
- **El Wartortle de ERICO (misma semilla):**
  - antes, Estallido (150) y Agua Lodosa;
  - con el tope solo, se quedaba con Restricción;
  - con el arreglo, lleva Tajo Acuático.

## ROM de Luis

- **Semilla:** `2121598288`.
- **Rama:** `jorge/tope-potencia-jefes`. Es la versión 9.1 más los papeles (#128) y el tope.
- **md5:** `a0e11cc3b3f7a591de5fcb7021500da2`.
- **Probada:** con el bot, partida nueva hasta el camión (nombre LUIS).
- **Antes hubo otra ROM con la misma semilla,** sacada de `master` sin estos cambios (md5 `72aeaebd9081269e30b234a4677be808`). La que vale es esta.

Jorge y Miguel siguen con sus ROMs de la versión 9.1, sin estos cambios.
