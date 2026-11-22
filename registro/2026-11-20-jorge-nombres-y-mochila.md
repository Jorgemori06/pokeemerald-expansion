# 20/11/2026 — Jorge: nombre del jugador largo y mochila más grande

**Qué se pidió:** las dos cosas que, según Miguel (#112), faltan para empezar el locke de verdad y son de Jorge: nombres del jugador más largos (para que quepa "JORGEMORI") y más casillas en la mochila.

**Qué se hizo:**
- **Nombre:** hasta 10 letras, guardado aparte al final de `SaveBlock2` (`playerNameLong`). Se enseña entero en diálogos, combates, menú de pausa (más ancho), ficha, menús de guardar y continuar, Salón de la Fama, Pokédex y el EO de tus Pokémon. El EO dentro de cada Pokémon y el resto de cosas guardadas siguen con 7 letras: agrandarlo cambiaría el tamaño de todos los Pokémon guardados, y en las cajas no cabe.
- **Mochila:** OBJETOS 150, OBJ. CLAVE 50, POKé BALLS 30, BAYAS 70 y MEDICINAS 70. OBJETOS pasa a `SaveBlock3`.

**Comprobado:** `make`, `make DUALOCKE_PRUEBA=1`, `make check TESTS="Dualocke"` (64/64) y los tests de la mochila. En el emulador: "JORGEMORI" en el menú, la ficha y el EO. Solucionario igual con las dos semillas.

**Ojo:** la mochila rompe las partidas guardadas. Va para la partida nueva (el locke de verdad), con semillas nuevas.

**Pendiente:** los entrenadores nuevos (Miguel elige zonas y equipos), lo último que falta para el locke de verdad.
