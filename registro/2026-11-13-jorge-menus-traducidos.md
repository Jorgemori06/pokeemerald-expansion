# 13/11/2026 — Jorge: menús de opciones traducidos

## Qué se pidió

Jugando, Jorge vio el menú del barco del SR. BRINEY en inglés: "PETALBURG / SLATEPORT / SALIR" (mandó una captura).

## Qué se ha hecho

- Los menús de opciones de los scripts están en `src/data/script_menu.h` y casi ninguno estaba traducido.
- Se han traducido con `ES()` las 183 entradas que había en inglés. Solo quedan sin tocar los nombres de POKéMON, los números y los precios sueltos. Entre ellas:
  - los destinos del barco (PETALIA, PORTUAL, AZULIZA);
  - la ayuda de las bicis;
  - el casino (FICHAS y premios);
  - las máquinas de bebidas;
  - los concursos (CARISMA, BELLEZA, DULZURA, INGENIO, DUREZA y las categorías);
  - las flautas, los fósiles, las setas y las escamas;
  - las encuestas;
  - los estados (ENV, PAR, DOR, QUE, CON);
  - el ascensor (P1-P5);
  - el FRENTE BATALLA y el cable.
- Los nombres de los objetos son los de `traduccion/nombres/objetos.csv`. En los menús de premios con `{CLEAR_TO}`, se ha comprobado que el nombre cabe antes del precio, y se han acortado FLAUTA AMARILLA y SEMILLA MILAGRO.
- `DUALOCKE.md`, sección 8.

## Cómo se comprobó

- `make` compila sin avisos.
- No se ha visto en el emulador. Los menús calculan su ancho según el texto más largo.
