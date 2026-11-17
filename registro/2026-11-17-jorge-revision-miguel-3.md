# 17/11/2026 (noche) — Jorge: revisión de todo lo de Miguel hasta la CIÉNAGA TÓXICA

## Qué se pidió

Jorge: "Miguel ha seguido haciendo un montón de cosas, ayúdale en todo lo que puedas y haz lo que creas conveniente". Miguel no puede compilar. La revisión anterior (#85) se quedó desfasada: solo cubría del #78 al #83 y la cadena ya va por el #98.

## Qué lleva esta rama (`jorge/revision-miguel-3`)

- **Lo de Miguel, todo junto:**
  - la cadena hasta el #98 (`miguel/cienaga-toxica`, que lleva del #81 al #96);
  - #78 (opciones del motor), #79 (megas Gigamax) y #80 (análisis de zonas).
- **Choques al juntarlos:** `PRUEBAS.md`, `src/dualocke_aleatorio.c` y `tools/dualocke/colocar_objetos.py`. Se dejan las dos partes.
- **De la revisión anterior (#85), que la cadena no tenía:**
  - `tools/dualocke/aleatorio/zonas.py`;
  - el arreglo de `zonas_nuevas.py` en Linux.
- **Arreglos nuevos:**
  - `zonas.py` con todas las zonas del #84 al #98: desierto y ruinas, marisma, bosque y mansión, islas del sur, playa, cumbre, bosque siniestro y ciénaga.
  - `HOENN_EXTRA_MAPSEC_LAST` pasa a la CIÉNAGA TÓXICA. Seguía en el BOSQUE SINIESTRO, así que la ciénaga no tenía zona de captura propia; lo avisaba `comprobar_zonas.py`.
- **Documentación:** en `DUALOCKE.md`, una sección nueva con qué mirar al añadir una zona.

## Partidas en curso

- **Semillas:** solucionario de la versión 7 contra esta rama, con `2780853751` y `2918696854`.
  - **Idénticos:** salvajes de antes, iniciales, estáticos de antes, regalos, los 302 objetos del suelo de antes, Recogida, intercambios, habilidades, MT, tutores, movimientos por nivel y estilos de los jefes.
  - **Cambian** (Jorge 42 entrenadores, Miguel 30):
    - los ases con mega de los jefes desde ALANA (#79);
    - los entrenadores reutilizados en las zonas nuevas;
    - en la semilla de Jorge, el tope de fuerza de los líderes de los tramos 4 a 8, aunque los equipos de CANDELA y NORMAN salen igual.
  - Nada de lo que cambia se ha visto ya en las partidas: o es de después de ALANA, o es de zonas nuevas.
  - **Sin `zonas.py` al día**, los objetos de las zonas nuevas habrían vuelto a mover casi todo lo del suelo.
- **Lo que se guarda:**
  - los 100 flags nuevos estaban libres en la versión 7, calculados con el preprocesador, no a ojo. Ninguno se repite y ninguno cae en los temporales (0x00-0x1F) ni en los diarios (desde 0x920);
  - la variable nueva de zonas de captura (0x40FE) también estaba libre;
  - zonas de captura: 118 de 128;
  - entrenadores: 864 de 864, **ya no queda ninguno libre**.

## Encontrado y pendiente de Miguel

- **A las tres islas del sur no se puede llegar.**
  - La ISLA ARENOSA está pegada al este de la RUTA 129, la DE RUINAS al norte de la 131 y la VOLCÁNICA al sur de la 134.
  - En los tres casos, ese borde de la ruta es mar de decorado, detrás de la barrera de rocas.
  - Comprobado con `alcance.py` y dibujando los bordes. Miguel comprobó que desde la entrada de cada isla se llega a todo, pero no que se pueda llegar a la entrada.
- **A la ISLA NEVADA (tramo 7) solo se llega buceando (tramo 8).**
  - Las filas 0-14 de la RUTA 124, las del borde de la isla, están fuera de las rocas.
  - La herramienta llega emergiendo en el agua profunda de x 67-70, y 9-12, pero hay que confirmarlo en el emulador. Si no, tampoco se llega.
- **Lo que está bien:** a todas las demás zonas nuevas se llega en su tramo, ni antes ni después.
  - El BOSQUE FRONDOSO está bien tapado con CORTE. El aviso que di esta tarde era un fallo de mi herramienta, que no veía los árboles de CORTE; ya está corregido en el #97.
  - El DESIERTO PROFUNDO, detrás de la tormenta de arena (Gafas Aislantes, tramo 5).

## Cómo se comprobó

- `make`: compila (sin avisos nuevos).
- `comprobar_zonas.py`: 0 fallos.
- `alcance.py` (del #97): solo salen los 8 de las rutas 111 y 118, que arregla el #97.
- `make check TESTS="Dualocke"` y `make check` completo: ver el PR.
- No se ha probado en el emulador.
