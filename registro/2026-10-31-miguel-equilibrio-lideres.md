# 31/10/2026 — Miguel: movimientos sin tope y líderes con estrategia

## Qué se pidió

Miguel y Jorge vieron jugando que el juego estaba desequilibrado: los líderes sacaban Pokémon y movimientos mucho más fuertes que los suyos, que tenían casi todo de 40 de potencia. Pidieron tres cosas:

1. Movimientos **totalmente aleatorios**, sin tope. Si en la Ruta 101 sale un Charmander con Lanzallamas, sale; y un Garchomp puede salir con Arañazo.
2. **Hasta el gimnasio 3**, que los líderes usen Pokémon de fuerza parecida a los salvajes que se han encontrado. Si no salen evoluciones, los líderes tampoco las llevan.
3. **Líderes con estrategia:** que envenenen si pueden, que pongan piedras, que se cheten, que jueguen bien.

## Qué se ha hecho

- **Sin tope de potencia:**
  - `potencia_maxima_del_cuarto` a `null` en `randomizer_config.json`.
  - Vale para el cuarto movimiento de los entrenadores y para los movimientos por nivel (`aprendizajes.py`), que leen el mismo campo.
  - Se mantienen el 60 % de ataques, la preferencia por los de su tipo y el ataque antes de nivel 5. Si se quieren quitar, se cambia aparte.
- **`tools/dualocke/aleatorio/estrategia.py` (nuevo):**
  - `elegir`: movimientos con plan. El primero del equipo pone trampas, y solo él. Los demás llevan movimientos de estrategia de su tipo o de su papel. Los ataques son los mejores de los que aprende por nivel (las tablas al azar).
  - Cuántos de estrategia: hasta el gimnasio 3, uno por Pokémon; después, dos.
  - `fuerza_salvajes`: tope de estadísticas base por tramo, con el percentil 90 de los salvajes de hierba de los tramos hasta ese, según la semilla.
- **`entrenadores.py`:**
  - Los de `lideres.con_estrategia` (líderes, Alto Mando y Plubio) llevan movimientos con plan e IA `Smart Trainer / Hp Aware / Ace Pokemon` (en dobles, `Double Ace Pokemon`).
  - Los de `lideres.limite_salvajes` no pasan del tope: PETRA, MARCIAL, ERICO, el rival hasta la Ruta 110 y BLASCO en Malvalona.
  - Cuando el as tiene que ser de su tipo y ninguno cabe en el tope, se elige el más flojo de su tipo. El inicial del rival se queda.
- **`randomizer.py`:** calcula los topes con los salvajes ya randomizados y los pasa al generador. Salen en el solucionario (`tope_lideres_por_tramo`).
- **Documentación:** `DUALOCKE.md` (sección 7) y `PRUEBAS.md`.

## Cómo se comprobó

- No hay compilador ni preprocesador en el PC de Miguel. Se probó con una Pokédex pequeña de mentira y los movimientos de verdad de `moves_info.h`:
  - PETRA (nivel 16, tope 300 con esos salvajes) sale con Larvitar, Geodude, Zigzagoon y Aron; sin Tyranitar ni Garchomp.
  - El primero lleva Trampa Rocas y los demás su estrategia (Tormenta Arena, Mirada Serpiente, Defensa Férrea…), sin repetir trampas.
  - Hay ataques en los cuatro y la IA queda cambiada.
  - `comprobar()` de los entrenadores, sin errores.
- Movimientos por nivel con la semilla de Miguel: 0 errores. Ahora 1 de cada 5 movimientos entre los niveles 1 y 10 tiene 90 o más de potencia (antes no podía).

## Pendiente

- Jorge: `make check` y `make release SEED=...` con el randomizer de verdad, y mirar en el solucionario cómo salen PETRA, MARCIAL y ERICO frente a los salvajes.
- Probarlo jugando. Ojo: con la misma semilla cambian los movimientos de todos y los equipos de los líderes del principio, así que conviene empezar partida nueva.

## Arreglos tras la revisión de Jorge (01/11/2026)

Jorge lo compiló y lo probó con la semilla `5966102869`: `make release` sin avisos y `make check` con 5455 en verde. Vio dos cosas, y están arregladas:

1. **Ataques que no convienen.** Los líderes cogían ataques que los perjudican: el Minccino de PETRA llevaba Explosión Bruma, y el Ninjask de ERICO, Giga Impacto. Ahora `estrategia.NO_CONVIENEN` los quita de la lista:
   - los que debilitan al que los usa o le quitan media vida: Autodestrucción, Explosión, Explosión Bruma, Sacrificio, Cabeza Sorpresa, Metalaser y Clorofiláser;
   - los que obligan a recargar: Hiperrayo, Giga Impacto, Anillo Ígneo, Hidrocañón, Planta Feroz, Romperrocas, Distorsión, Láser Prisma, Asalto Estelar y Rayo Infinito.
2. **Tope del tramo 1 demasiado alto.** Con esa semilla salía 570, por un Iron Treads en la Ruta 101 y un Dondozo en la 102. Ahora hay `techo_por_tramo` (360, 400 y 450 hasta PETRA, MARCIAL y ERICO): el tope nunca pasa de ahí aunque el percentil salga más alto.

Se comprobó con la prueba de siempre:
- con Explosión, Giga Impacto e Hiperrayo en la tabla, el líder no los coge;
- con un Garchomp y un Tyranitar en la Ruta 101, el tope del tramo 1 se queda en 360.
