# 18/11/2026 (tarde) — Jorge: arreglos de la segunda prueba de Miguel

## Qué se pidió

Miguel, jugando la versión 8.1 (hasta el 3.er gimnasio), mandó a Jorge:

- **Fallos:**
  - En la CUMBRE METEORO, de la zona del guardián solo se sale con la bici de carreras.
  - No se puede entrar al DESIERTO PROFUNDO.
  - El Parche Habilidad no funciona bien.
  - Solo se reviven los fósiles de Esmeralda (por ejemplo, el Fósil Pluma no).
- **Mejora que pide:** más espacio para objetos en la mochila.
- **Zona nueva que propone:** la CANTERA, de tipo Acero, en la RUTA 116 (ya está en `PLAN.md`).

Miguel no había subido nada desde el #105, así que lo ha hecho Jorge.

## Qué se ha hecho

- **CUMBRE METEORO:**
  - **Causa:** a la zona del guardián se bajaba por dos casillas de barro, (10,8) y (10,9). Venían de la RUTA 115 original, de la que se recorta la cumbre. El barro solo se sube con la bici de carreras, y era la única vuelta.
  - **Arreglo:** pasan a ser suelo, a la misma altura. Se hace en `crear_cumbre_meteoro.py` (`BARRO`), así que si se relanza no vuelve. Relanzado: solo cambian esas dos casillas.
- **DESIERTO PROFUNDO: no es un fallo.**
  - La puerta está bien: altura 0, número de puerta correcto y arena delante.
  - Está dentro del desierto de la RUTA 111, y sin las GAFAS AISLANTES la tormenta de arena te echa para atrás. Las dan después del 4.º gimnasio, y Miguel va por el 3.º.
  - Con `alcance.py`, se entra en el tramo 5.
- **Parche Habilidad:**
  - **Causa:** con la semilla, cada especie tiene una sola habilidad en sus tres huecos (#27, Miguel). El parche cambiaba a la oculta, que era la misma, y se gastaba igual.
  - **Arreglo:** si la habilidad no cambiaría, dice "No tendría efecto" y no se gasta (`Task_AbilityPatch`, `src/party_menu.c`). La Cápsula Habilidad ya lo comprobaba.
  - **Pendiente de decidir:** que el parche sirva para algo, por ejemplo con una habilidad oculta propia al azar. Es diseño (#27), así que hay que hablarlo con Miguel.
- **Fósiles:**
  - **Causa:** el randomizer de objetos del suelo reparte los 15 fósiles del motor, pero el INVESTIGADOR de DEVON solo conocía el Raíz y el Garra.
  - **Arreglo:** si no llevas ninguno de esos dos, busca en la mochila los demás. La tabla de fósiles y su POKéMON está en `src/data/dualocke_fosiles.h`, y el script en `data/scripts/dualocke_fosiles.inc`. Usa las funciones especiales `Dualocke_BuscarFosil` y `Dualocke_EspecieFosil`.
  - Se guarda el objeto del fósil en `VAR_WHICH_FOSSIL_REVIVED`, que en el original solo valía 1 o 2. Las partidas guardadas siguen valiendo.
  - **Pokémon que sale:** con semilla, otro al azar a nivel 20. Se sortea aparte con su propio generador (`fosiles()` en `aleatorio/estaticos.py`), así que los regalos de antes no cambian. Pasa por `givemon`, así que si es repetido o legendario va a VETADOS, como los demás regalos.
  - Los de Galar reviven uno cada uno.
- **`tools/dualocke/sin_salida.py` (nuevo, en el CI):** mira que en las zonas nuevas, desde todo sitio al que se llega andando, se pueda volver a una salida.
  - Anda sin bici: el barro solo se baja y los saltos son de un sentido.
  - Con la cumbre de antes da 92 casillas sin vuelta, y ahora 0 en todas las zonas.
  - Mirados aparte, por si encerraban, el barro del DESIERTO PROFUNDO y el suelo que se hunde de las RUINAS ARENOSAS: no encierran.
- **Tests:** 2 nuevos en `test/dualocke.c`, para los fósiles.

## Lo que no se ha hecho

- **Más espacio en la mochila:** el tamaño de cada bolsillo se guarda en la partida, así que agrandarlo rompe las partidas guardadas. Cabe (quedan unos 300 bytes en ese bloque del guardado, unos 75 huecos más), pero para la próxima partida nueva, junto con los nombres largos y los entrenadores.

## Partidas en curso

- **Semillas:** solucionario de la versión 8 contra esto, con las dos (`2425682645`, `3632113266`). Todo igual; solo se añaden a los regalos los 13 fósiles nuevos.
- **Lo que se guarda:** no cambia. No hay flags ni variables nuevas; `VAR_WHICH_FOSSIL_REVIVED` ya existía.

## Cómo se comprobó

- `make` compila sin avisos nuevos.
- `make check TESTS="Dualocke"`: 62/62.
- `make check` completo: ver el PR.
- `comprobar_zonas.py` 0 fallos, `alcance.py --comprobar` 0 y `sin_salida.py --comprobar` 0.
- No se ha probado en el emulador.
