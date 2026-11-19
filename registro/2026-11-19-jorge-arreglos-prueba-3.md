# 19/11/2026 — Jorge: arreglos de la tercera prueba de Miguel, emulador y fotos de la guía

**Qué se pidió (mensajes de Miguel jugando):**
- La puerta del DESIERTO PROFUNDO no es accesible desde la RUTA 111, aun con las gafas.
- El camino de la ISLA SUR está bloqueado por una de sus entrenadoras.
- PLAYA VOLCÁNICA: "las capturas en el agua rompen el personaje, gráficos raros, baldosas y límites del mapa fatal puestos, mejorar el estilo de la zona por completo".
- Mejorar las pistas de las megapiedras en la guía (con fotos).
- Repetidos de antes: Parche Habilidad y fósiles (arreglados en la 8.2, #109) y la mochila más grande (para la próxima partida nueva).

**Qué se hizo:**
- **Emulador sin pantalla** (`tools/dualocke/emulador/`) y ROM de pruebas (`make DUALOCKE_PRUEBA=1`): empieza la partida en el mapa que se quiera y deja andar, surfear, combatir, capturar y hacer fotos desde Python. Ganchos con `#ifdef DUALOCKE_PRUEBA`: la ROM normal y la de `make release` no cambian (comprobado en el `.elf`: no hay nada de las pruebas).
- **DESIERTO PROFUNDO:** no se reproduce. En el emulador se va andando desde la puerta de las RUINAS DESIERTO hasta el montículo nuevo (unas 8 casillas más arriba y a la derecha) y se entra. Falta que Miguel diga dónde lo intentó.
- **ISLA SUR:** TERRY estaba en la única casilla del sendero. Se mueve a un lado (25, 10), mirando a la izquierda.
- **ISLA LEJANA:** MIKE tapaba igual un pasillo (lo encontró la comprobación nueva). Se mueve a (11, 26).
- **`sin_salida.py`** comprueba ahora también que ninguna persona tape el paso entre las salidas (va en el CI).
- **PLAYA VOLCÁNICA:** borde de árboles (era la roca rosa del MONTE CENIZO), y el mapa cerrado arriba (acantilado y rocas) y abajo (árboles y rocas). El cruce con la RUTA 122 sigue funcionando (probado surfeando en el emulador).
  - El personaje roto no se reproduce: se surfeó, se combatió, se huyó y se capturó en el agua. Falta una foto o el `.sav`.
  - La sequía aclara mucho los colores: puede ser lo de los "gráficos raros". Propuesta para Miguel: `WEATHER_SUNNY` (sin sol en combate).
- **Guía:** cada megapiedra y cada Ticket-Recuerdo tiene una foto del juego con el sitio marcado (`fotos_guia.py`; 161 fotos, unos 2,7 MB dentro de `GUIA.html`). Probada en el navegador.

**Comprobado:**
- `make`, `make DUALOCKE_PRUEBA=1`, `make check TESTS="Dualocke"` (62/62).
- `sin_salida.py --comprobar` (0 problemas) y `alcance.py --comprobar` (0).
- Solucionario con las dos semillas: idéntico al de la 8.3. No cambia nada de lo que se guarda: las partidas siguen valiendo.

**Pendiente:**
- Que Miguel diga dónde no pudo entrar al DESIERTO PROFUNDO y cuándo se le rompió el personaje en la playa (fotos o `.sav`).
- Que decida el tiempo de la PLAYA VOLCÁNICA y, si quiere rehacerla más, qué cambiaría.
- Mochila más grande: con la próxima partida nueva (rompe las partidas guardadas).
