# 21/11/2026 — Miguel: arreglos de la quinta prueba (ISLA VOLCÁNICA, ISLA DE RUINAS, DESIERTO PROFUNDO y RUINAS ARENOSAS)

## Qué se pidió

De la quinta prueba de Miguel (`registro/2026-11-21-miguel-prueba-5-y-plan.md`):
- **ISLA VOLCÁNICA:** solo se puede entrar por PORTUAL. Ahora también se entra desde la RUTA 134, y la parte de PORTUAL se buguea.
- **ISLA DE RUINAS:** no se puede entrar. Hay que rehacerla, con una entrada más clara y una zona mejor.
- **DESIERTO PROFUNDO y RUINAS ARENOSAS:** funcionan, pero son el mismo dibujo que el desierto y la TORRE ESPEJISMO. Hay que cambiar el escenario y la manera de avanzar.

Miguel contestó antes de empezar:
- **ISLA VOLCÁNICA:** barco desde PORTUAL.
- **ISLA DE RUINAS:** templo en ruinas.
- **DESIERTO:** dunas y arenas movedizas.
- **RUINAS:** interruptores.

## Qué se ha hecho (rama `miguel/arreglos-prueba-5`, sobre la #113)

### ISLA VOLCÁNICA: en barca desde PORTUAL (`crear_islas_sur.py`)
- **Ya no está pegada a la RUTA 134.**
- **Ida:** un marinero en la punta del muelle de PORTUAL (38, 34) lleva a la isla desde la 7.ª medalla. Antes dice que el mar está bravo.
- **Vuelta:** en la playa de abajo de la isla hay una barca, y el marinero trae de vuelta al muelle.
- **La roca de la RUTA 134** que se había quitado para llegar (9, 21) vuelve a su sitio (`ROCAS_DEVUELTAS`).
- **`alcance.py`:** el viaje está en `VIAJES`. Se llega en el tramo 8 y no antes.

### ISLA DE RUINAS: templo en ruinas al sur de la RUTA 129 (`crear_islas_sur.py`)
- **Por qué no se llegaba:** estaba encima de la RUTA 131, junto a las corrientes del PILAR CELESTE.
- **Sitios que se miraron con `alcance.py`:**
  - **Encima de la RUTA 130:** no. Ahí aparece la ISLA ESPEJISMO, con otros gráficos, y desde la isla se vería rota.
  - **A la izquierda de la RUTA 128:** no. En el juego no se llega. Solo se llegaba a través de la isla vieja, que hacía de puente sin querer: al quitarla, la parte norte de las RUTAS 128-131 dejaba de alcanzarse.
  - **Debajo de la RUTA 129:** sí. Todo su borde de abajo es mar abierto y se alcanza.
- **Cómo es ahora:**
  - 40 × 38, con 8 filas de mar arriba para rodear la isla.
  - De la playa grande del sur sube una escalinata de piedra (`0x29D`/`0x29E`) en lugar de la cueva escondida.
  - Arriba hay un patio enlosado (`0x234`) con columnas de piedra en lugar del montículo, con la sombra de la torre a la derecha.
  - Al fondo, la torre. Se quita el túnel de las dos cuevas.
- **El hueco de la RUTA 131 (7, 12) se queda:** también lleva a la parte norte de las RUTAS 128-131.
- **Los dos objetos del rellano** se mueven 8 filas (`SITIO_OBJETOS`). La zona de captura pasa debajo de la RUTA 129 en el mapa de la región.
- `guardar_layout()` actualiza el tamaño en `layouts.json` si el mapa cambia.

### DESIERTO PROFUNDO: dunas y arenas movedizas (`crear_desierto_profundo.py`)
- **Arriba:**
  - Todo es arena clara, sin la arena honda, las peñas ni las piedras sueltas del desierto de la RUTA 111.
  - Una fila de peñas (filas 22-23) corta el paso al norte.
- **Arenas movedizas:** son 4 hoyos de arena honda de 3 × 3 (`HOYOS`). Al pisar el centro se lanza un `coord_event` con mensaje y sonido, y caes a la CUEVA.
- **CUEVA** (`DesiertoProfundo_Cueva`, 40 × 23):
  - Es el trozo x 99-138 del PASO DESIERTO, partido en tres salas con rocas (`CUEVA_ROCAS`).
  - Cada sala tiene una escalera (`0x23E`). La de la sala buena sale junto a las ruinas; las otras dos, a la entrada.
  - El script comprueba que las salas no se tocan.
- **SOLEDAD** da la pista después del combate.
- **`alcance.py`** conoce la caída. El desierto, la cueva y las ruinas se alcanzan en el tramo 5.

### RUINAS ARENOSAS: interruptores (`crear_desierto_profundo.py`, `interruptores()`)
- **Fuera:** el suelo agrietado (pasa a suelo normal) y las rocas de GOLPE ROCA de la planta 3.
- **Plantas 2 y 3:**
  - Dos puertas de piedra (`0x213`) cierran la escalera siguiente por los dos lados del pasillo.
  - El interruptor (losa morada, `0x237`) está en la otra punta.
  - Al pisarlo, las puertas vuelven a ser el suelo que había y la losa queda pulsada.
- **Se quedan abiertas:** un flag por planta (0x913 y 0x91B) y `MAP_SCRIPT_ON_LOAD`. Así, al bajar de la planta 3 no te quedas encerrado.
- **`colocar_objetos.py`:** los bloques de las islas del sur y de la playa acaban ahora en 0x912 y 0x91A.

## Cómo se comprobó

- **Las herramientas de comprobación:**
  - `comprobar_zonas.py`: 0 fallos.
  - `sin_salida.py --comprobar`: 0.
  - `alcance.py --comprobar`: 0.
  - `variantes.py --comprobar`: 0.
  - `graficos.py --comprobar`: nada de estos cambios. En Windows marca los mapas `_Frlg` porque la ruta va con `\`; en el CI (Linux) no pasa.
- **`alcance.py`, por tramos:**
  - ISLA VOLCÁNICA: tramo 8.
  - ISLA DE RUINAS: se alcanza.
  - DESIERTO, CUEVA, RUINAS y CÁMARA: tramo 5.
- **Comprobaciones de los scripts:**
  - lo que se ve desde la RUTA 129 son piezas generales;
  - las salas de la cueva están separadas;
  - cada puerta y cada interruptor están sobre suelo.
- **Fotos de cada arreglo:** `fotos_zonas/16` a `19`, enviadas a Miguel.
- **`guia.py`:** relanzado.
- **Compilación:** la hará el CI de la PR. **Sin probar en el emulador.**

## Pendiente

- **Probar jugando** (`PRUEBAS.md`).
- **Jorge:** las fotos de la guía (`fotos_guia.py`), porque los objetos de la ISLA DE RUINAS cambian de sitio.
- **Lo siguiente del plan:** los biomas (CANTERA, Prado de las Hadas e isla del dragón).
