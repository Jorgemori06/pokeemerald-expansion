# Bot que se pasa el juego (`tools/dualocke/bot/`)

Juega el Dualocke en el emulador sin pantalla (`tools/dualocke/emulador/`) **con la ROM normal de `make release`**, no con la de pruebas: sin atajos ni menús de depuración. Lee la memoria del juego para saber dónde está el jugador, si hay textos o un combate, y pulsa los botones como lo haría una persona. Así se puede comprobar de un tirón que la historia se puede terminar después de cada cambio, sin jugarla a mano.

Lo hizo Claude entre el 20 y el 22/11/2026 pasándose el juego entero (semilla 777000111): 8 medallas, Liga, Salón de la Fama, créditos y continuar la partida después. Lo que encontró está en `registro/2026-11-22-jorge-bot-partida-completa.md`.

## Preparar

```bash
sudo apt install libmgba-dev          # para el emulador
make release SEED=777000111           # o la semilla que quieras
python3 tools/dualocke/bot/preparar.py
```

`preparar.py` crea la carpeta de la partida (`partida_bot/` en la raíz del repo, o la que digas en `DUALOCKE_PARTIDA`; está en `.gitignore`), copia la ROM y su `.elf`, y genera desde el código:

- `datos.json`: los movimientos (potencia, tipo, precisión, efecto, golpes…) para calcular el daño;
- `offsets.json`: los desplazamientos de los structs (`BattlePokemon`, `Pokemon`, `PartyMenu`…).

Si cambian los movimientos o los structs, basta con volver a lanzarlo.

## Usar

Todo se hace a trozos, con estados guardados (`.ss`) dentro de la carpeta de la partida:

```bash
cd tools/dualocke/bot
# partida nueva: intro, nombre y hasta el camión
python3 -c "import piloto as P; e = P.Piloto(); P.empezar_partida(e, 'Claude'); e.guardar_estado(P.AQUI + '/est/e00.ss')"
# un tramo: carga e00, ejecuta el código y guarda e01 (si falla, guarda e01_fallo.ss para seguir desde ahí)
python3 paso.py est/e00.ss est/e01.ss 'ir(e, "MAP_LITTLEROOT_TOWN"); print(estado(e))'
# lo mismo en segundo plano (hasta 50 min), con la salida en ultimo.log
./correr.sh est/e01.ss est/e02.ss 'hablar_con(e, "MAP_RUSTBORO_CITY_GYM", 5, 2)'
```

El bot apunta todo en `diario.txt`: cada combate turno a turno, capturas, curas, recargas y ayudas.

## Qué sabe hacer

- **Moverse:** `ir(e, mapa, x, y)` planea el camino por todo Hoenn (puertas, conexiones, saltos, alturas, surf, buceo, corrientes, cascada, teleférico) y lo anda; por el camino lucha, cura en el Centro más cercano, rompe rocas, corta árboles, coge Balls que tapan y empuja rocas de FUERZA. `hablar_con(e, mapa, x, y)`, `hablar_y_elegir(...)` (menús de opciones), `volar(e, mapsec)`, `curar`, `comprar`, `usar_objeto`, `usar_clave`, `cuerda_huida`, `foto_equipo`.
- **Combatir:** `seguir(e)` pasa textos y juega los combates. Elige el movimiento que más daño hace (con tipos, STAB, golpes múltiples, inmunidades que ha visto), cambia si le van a tumbar, juega dobles y el combate múltiple con Steven, captura el primer Pokémon de cada zona sin dejar que se le muera nadie (si nadie aguanta, huye) y aprende/olvida movimientos protegiendo las MO.
- **Puzles:** gimnasios de Malvalona, Arborada (puertas giratorias), Petalia, Algaria (estatuas que giran; simula el puzle entero), Arrecípolis (hielo: recorrido que pisa cada casilla una vez), rocas de FUERZA con rocas rompibles en medio (búsqueda en anchura), y el suelo agrietado del Pilar Celeste con la BICI CARRERA (prueba de verdad en el emulador qué pasa con cada tecla y busca con A*).
- **Reintentos:** `intentar(e, accion)` recarga si se pierde una vida o el locke; `con_ayuda(e, accion, nombre)` lo intenta limpio y, si no sale, lo repite con la **ayuda declarada** (rellena la vida de los suyos en combate y deja la del rival a 1), apuntándolo en el diario. Sirve para seguir probando la historia, **no** para medir la dificultad: el bot combate peor que una persona y no usa objetos curativos.

## Herramientas

- `eventos.py MAP_X [--dibujo]`: eventos de un mapa y, con `--dibujo`, la rejilla tal como la ve el planificador.

## Limitaciones

- No hay un guion de la historia de principio a fin: se va tramo a tramo con `paso.py` (así se ve dónde falla y se arregla). En el registro está el orden que se siguió en la segunda mitad.
- Solo pisa las zonas del camino de la historia y captura lo que le sale al pasar: no visita las zonas nuevas ni busca encuentros en cada ruta.
- No usa objetos en combate.
