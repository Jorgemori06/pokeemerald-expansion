# 22/11/2026 · Jorge (con Claude) · Bot que se pasa el juego y partida completa de prueba

## Qué se pidió

Jorge: que Claude se creara una ROM aleatoria normal (no la de pruebas) y se pasara el juego entero como uno de nosotros, comprobando a su paso que todo funciona, con una foto del equipo después de cada medalla y de la Liga. Después, subir el bot al repo para que se pueda repetir, y apuntar en el PR lo descubierto, lo que ha tardado y las recomendaciones para Miguel.

## Qué se hizo

- Partida con `make release SEED=777000111`, jugador "Claude". Se terminó: **8 medallas, Liga, Salón de la Fama, créditos y continuar la partida después** (aparece la estrella en la ficha).
- Acabó con **8 vidas de 20** y el locke sin perder en la partida que quedó. Caja 14 (MUERTOS) con 12 Pokémon; equipo final a nivel 100: Mandibuzz, Medicham, Feraligatr, Sandslash de Alola, Kingler y Ampharos.
- El bot se sube en `tools/dualocke/bot/` (ver su `README.md`). La partida, la ROM y los estados guardados **no** se suben (`partida_bot/` está en `.gitignore`).

## Tiempo y coste

- Unas **32 horas de reloj** desde el nombre hasta la Liga, contando los parones por falta de tokens; **unas 11 h y media de trabajo real**.
- La mayor parte se fue en **construir y arreglar el bot**: planificador de caminos, combates, capturas, puzles, buceo, bici, rocas… El juego emulado va rápido: tramos enteros de historia salen en uno o dos minutos.
- Con el bot ya hecho, repetirlo con otra semilla debería costar unas pocas horas y una fracción de los tokens, aunque cada semilla trae algo nuevo (equipos, capturas).

## Cómo de "legal" fue la partida (importante para leer los resultados)

- **Recargas: 51.** Unas 32 por errores del propio bot (atascos en puzles, menús, caminos), unas 13 por combates perdidos (habría perdido el locke) y unas 6 por muertes en combates ganados. Jugando de verdad, sin recargas, no habría pasado del Monte Cenizo.
- **Ayuda declarada** (vida rellena en combate y el rival a 1) en 17 tramos, casi todos jefes: Norman, el Instituto Meteorológico, Máximo en la Ruta 120, Alana, Candela, el Monte Cenizo, la Guarida Magma, la Cima del Monte Pírico, la Guarida Aqua, Vito y Leti, Aquiles, Galano, la Calle Victoria, Fátima, Nívea, Dracón y Plubio. Sin ayuda salieron los tres primeros líderes, Magno y Tatiano en el Centro Espacial (con Steven) y Sixto.
- El bot **combate peor que una persona y no usa objetos curativos**, así que esto prueba que el juego funciona, **no** su dificultad.
- **Capturas:** solo gastó 35 zonas, las del camino de la historia y lo que le salió al pasar. **No pisó ninguna zona nueva** (Bosque Frondoso, Ciénaga Tóxica, Marisma Azuliza, Cumbre Meteoro, Desierto Profundo, Ruinas Arenosas, islas del ferry…): siguen sin probar.

## Fallos encontrados en el juego

1. **[Arreglar] Toxtricity Grave se convierte en Aguda al acabar cualquier combate.** En `src/data/pokemon/species_info/gen_8_families.h`, `SPECIES_TOXTRICITY_LOW_KEY` y `SPECIES_TOXTRICITY_LOW_KEY_GMAX` usan `sToxtricityAmpedFormChangeTable` en vez de la de Grave (viene de la expansion).
2. **[Mapa] Balls que tapan el paso** (se pueden coger, pero quedan raras):
   - Museo Oceánico 2F: las GAFAS ESPECIALES en (6,2), la única casilla delante de la escalera.
   - Ruta 122: el TICKET-RECUERDO (22,30) y la INTELEONITA (23,30) delante de la puerta del MONTE PÍRICO.
   - Calle Victoria: la GALLADITA (32,22) y la GARDEVOIRITA (33,23) junto a Edgar en 1F; el ESCUDO HABILIDAD (36,12) y la GARCHOMPITA Z (38,12) a los lados de Samuel en B1F. No cortan el paso.
   - Merece la pena una comprobación en el CI que avise de Balls delante de una puerta o en un paso de una casilla.
3. **[Traducción] Textos en inglés:**
   - OPCIONES: en VEL. TEXTO las tres palabras salen pegadas ("LENTAMEDIARÁPIDA").
   - Ficha de entrenador: "TRAINER CARD" y "BADGES"; en la tienda, "MONEY".
   - El POKéNAV entero (menús, mapa, AGENDA).
   - Menú de un Pokémon del equipo: "SUMMARY", "SWITCH" e "ITEM".
   - PC, MOVER POKéMON: "PKMN DATA", "PARTY POKéMON" y "CLOSE BOX".

## Comprobado y sin fallos

Historia entera (Equipo Aqua y Magma, Monte Pírico, Puerto de Portual, Guarida Aqua, Centro Espacial y combate múltiple con Steven eligiendo 3, Cueva Abisal, Arrecípolis, Pilar Celeste con Rayquaza), los 8 gimnasios con sus puzles (Algaria con las estatuas que giran y Arrecípolis con el hielo incluidos), Buceo y emerger, corrientes, Cascada, Bici Carrera y suelo agrietado (incluida la caída a propósito del 4F al 3F del Pilar Celeste), rocas de FUERZA y rompibles de la Calle Victoria, guardias de la Liga, Alto Mando, Campeón, Salón de la Fama y créditos. Las vidas, la caja de muertos, las zonas gastadas, los topes de nivel, los Caramelos Raros a 1 ₽ y la captura con el equipo lleno funcionan como dice `DUALOCKE.md`.

## Recomendaciones (sobre todo para Miguel)

1. **Movimientos del randomizer:** a los Pokémon del jugador les tocaban movimientos sin sentido (Medicham: Rizo Defensa, Acupresión, Dragoaliento y Fragor Escamas; Sandslash de Alola: Castigo, Disparo Lodo, Reflejo y Conversión), casi nunca un ataque fuerte de su tipo, mientras los jefes llevan equipos muy fuertes (Giratina con Dracón, Spectrier, Baxcalibur…). Propuesta: que el random de movimientos por nivel asegure al menos un ataque de daño de su tipo cada pocos niveles.
2. **Alto Mando sin curas:** las tiendas no venden curas y en la Liga no hay Centro entre salas. Jorge ha contado la regla que usáis (abajo); ahora mismo **no está en el juego**.
3. **Salvajes de la Calle Victoria a nivel 87** (Sandy Shocks…): capturarlos con el cap a 100 sigue siendo arriesgado, y huir pierde la zona. Valorar si es lo que queréis.
4. **Balls nuevas:** revisar las que están delante de puertas o en pasos estrechos (n.º 2) y añadir esa comprobación al CI.
5. **Jefes de mitad de juego** (Norman, Candela, el Monte Cenizo, Aquiles): fueron los que más recargas costaron; si alguien juega como el bot (sin curas), son muros. Con objetos curativos encontrados y una persona jugando debería ser otra cosa, pero conviene mirarlo.
6. **Zonas nuevas:** el bot no las pisó; queda probarlas (con el bot se puede: `ir(e, "MAP_...")` hasta cada una y capturar).

## Regla de la Liga (contada por Jorge el 22/11/2026)

Al llegar a la Liga se pueden comprar todos los RESTAURAR TODO que se quiera. En combate solo se pueden usar **si el rival ya ha usado uno**, y como mucho **tantos como haya usado él** (si usa 2, puedes usar 2). **Entre combates se cura el equipo entero.** Está apuntada en `DUALOCKE.md` (sección 4); falta decidir si se hace en el juego (tienda en la Liga, contador en combate y cura automática al pasar de sala).

## Orden que siguió el bot en la segunda mitad

Puerto de Portual (Stern) → Guarida Aqua → Ruta 124 → Algaria (gimnasio 7) → Centro Espacial → casa de Steven (Buceo) → Ruta 128 y Cueva Abisal → Arrecípolis (Steven, Cueva Ancestral) → Malvalona (Bici Carrera) → Pilar Celeste → Arrecípolis (Magno, Aquiles, Plubio: Cascada) → gimnasio 8 → Calle Victoria → Liga.


## Prueba de las zonas nuevas con los PR de Miguel (#112, #113, #116 y #117), 22/11/2026 de madrugada

Jorge se fue a dormir y Claude probó las zonas nuevas sin fusionar nada: rama local con `master` + #117 (que lleva debajo la #112, la #113 y la #116) + este PR, `make release SEED=777000111`, y la partida de después de la Liga pasada a la ROM nueva (`sacar_sav`/`meter_sav`). **La partida guardada de la ROM vieja carga bien en la nueva.** Con `probar_zonas.py`, en cada zona: llegar volando a la ciudad más cercana y andando, el primer Pokémon, el guardián y volver andando a un Centro. Unos 20 s por zona.

**Bien (se llega, se captura, se gana al guardián y se vuelve):** PLAYA VOLCÁNICA (con la ceniza de la #113), CIÉNAGA TÓXICA, BOSQUE SINIESTRO, BOSQUE FRONDOSO y MANSIÓN OLVIDADA (hace falta CORTE), MARISMA AZULIZA, CUMBRE METEORO, CANTERA, ISLA ARENOSA, ISLA NEVADA (con el hielo), GRUTA ÍGNEA (con las rocas del CAMINO ÍGNEO), ISLA DEL DRAGÓN y su VALLE, y RUINAS ARENOSAS (los interruptores del 2F y el 3F abren las puertas).

**Fallos (para Miguel):**

1. **ISLA VOLCÁNICA: no se puede llegar.** El barquero de PORTUAL está en (38, 34), en la punta de un trozo de muelle (filas 33-34, x 32-38) que no está unido a la ciudad: ni andando ni surfeando desde PORTUAL (esa agua solo da a la RUTA 134). `alcance.py` no lo ve porque da el viaje por hecho desde cualquier casilla del mapa. Hay que ponerlo en un sitio al que se llegue andando (por ejemplo, el muelle de abajo, junto al otro marinero de (37, 41)).
2. **PRADO DE HADAS: no se puede entrar desde la RUTA 119.** Las casillas del borde de la ruta (filas 33-34) tienen altura 4 y las del prado, altura 3: el juego no deja pasar (probado en el emulador: andando hacia la izquierda desde (0, 34) no te mueves). Hay que poner la misma altura a los dos lados o una casilla de altura 0 o 15 en medio.
3. **ISLA DE RUINAS: no se puede entrar en la TORRE.** La puerta (20, 13) es `MB_NON_ANIMATED_DOOR` con colisión: en el juego, al subir desde (20, 14) no pasa nada (probado). Así no se llega al guardián. Las puertas sin animación tienen que ir sin colisión (como la de la CUEVA ANCESTRAL en ARRECÍPOLIS, que se cruza al pisarla) o ser una puerta animada.
4. **DESIERTO PROFUNDO: el norte es una trampa sin VUELO.** Desde la parte de arriba (donde se sale de la cueva buena, junto a las ruinas) no se puede volver: la fila de peñas (filas 22-23) lo cierra, las escaleras de la cueva que salen ahí son de llegada (no se puede volver a bajar) y la CUERDA HUIDA en las ruinas te devuelve a (12, 12), en el mismo norte. En el tramo 5 todavía no hay VUELO. `sin_salida.py` no lo ve porque cuenta la puerta de las ruinas como salida. Arreglo posible: una escalera de vuelta a la cueva en el norte, o que la cuerda en las ruinas te deje en la entrada del desierto (`setescapewarp`).
5. **RUTA 130 → ISLA DEL DRAGÓN: en la esquina de la derecha no se baja.** Desde la fila 39 de la RUTA 130 se pasa a la isla con x entre 40 y 72, pero con x de 73 a 79 no te mueves (probado dos veces). Las casillas de la isla son agua; en memoria, debajo de esas siete columnas no está copiada la isla. Por el medio se llega sin problema; puede bastar con que la isla no llegue hasta la esquina.

**No es del juego (el bot):** el DESIERTO PROFUNDO y las islas no se capturaron porque el bot solo busca por la hierba alta; la ISLA VOLCÁNICA y la ISLA DE RUINAS (torre) no se probaron por dentro por los fallos 1 y 3.

## Cambios

- `tools/dualocke/bot/`: `piloto.py` (el bot), `paso.py` y `correr.sh` (jugar a tramos), `preparar.py` y `offsets.c` (carpeta de la partida, movimientos y structs), `eventos.py` (ver un mapa), `probar_zonas.py` (recorrer zonas), `README.md`.
- `tools/dualocke/emulador/gbarun.c`: órdenes `sacar_sav` y `meter_sav` (pasar la partida guardada de una ROM a otra).
- `.gitignore`: `partida_bot/`.
- `DUALOCKE.md`: sección 3 (el bot), sección 4 (regla de la Liga), sección 9 (pendientes) y sección 10 (mapa del código).

## Pendiente

- Arreglar los fallos de arriba (Toxtricity con test, Balls, traducciones), cada uno en su rama.
- Decidir si la regla de la Liga se hace en el juego.
- Probar las zonas nuevas con el bot.
