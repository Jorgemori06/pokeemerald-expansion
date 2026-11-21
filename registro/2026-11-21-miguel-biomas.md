# 21/11/2026 — Miguel: tres biomas nuevos (CANTERA, PRADO DE HADAS e ISLA DEL DRAGÓN)

## Qué se pidió

Después de los arreglos de la quinta prueba (`registro/2026-11-21-miguel-arreglos-prueba-5.md`), los biomas de `PLAN.md`, sección 0. Miguel contestó antes de empezar:

| Bioma | Guardián | Acceso |
| --- | --- | --- |
| CANTERA (Acero, su idea del 18/11) | **Aggron** (en vez de Copperajah) | — |
| PRADO DE HADAS | **Gardevoir** | — |
| ISLA DEL DRAGÓN | **Haxorus** | **Surfeando desde una ruta del sur** |

## Qué se ha hecho (rama `miguel/biomas`, sobre `miguel/arreglos-prueba-5`)

Cada uno con su `crear_*.py`, apuntado en las herramientas (receta de `PLAN.md`, sección 4) y con la cadena entera lanzada. `trainers.party` no cambia.

### CANTERA (`crear_cantera.py`), tramo 3
- **Entrada:** boca de cueva nueva en la RUTA 116, en (67, 10), en la misma pared que la salida este del TÚNEL FERVERGAL (65, 10).
- **El mapa:** pared de arriba con las piezas de la RUTA 116, tres terrazas con riscos y escaleras, tierra, hierba alta, seis rocas de GOLPE ROCA y árboles.
- **Guardián:** Aggron (0x4FF).
- **Objetos:** 0x068, 0x0E9, 0x2D9 (oculto) y 0x1DA (Ticket-Recuerdo).

### PRADO DE HADAS (`crear_prado_hadas.py`), tramo 6
- **Dónde:** el jardín con vallas del lago, al norte del INSTITUTO METEOROLÓGICO, no se alcanza en el tramo 6 (`alcance.py`). Por eso la entrada va junto al instituto, por el oeste.
- **La entrada en la RUTA 119:** se cortan los árboles del borde izquierdo en las filas 33-34. La fila 32 pasa a ser pie de árbol, en las columnas 0-1; en (2, 32) está el instituto.
- **El prado:**
  - 40 × 36, a la izquierda de la ruta (fila 0 = fila -1 de la ruta);
  - un camino de tierra, flores, charcas, hierba alta y muy alta;
  - un claro con un anillo de flores para Gardevoir.
- **Flags:** 0x4E4 (guardián), 0x8F4-0x8F5, 0x8FD (oculto) y 0x8FE.

### ISLA DEL DRAGÓN (`crear_isla_dragon.py`), tramo 8
- **La isla:**
  - al sur de la RUTA 130, desde su x 40;
  - de arena, generada como una elipse, con su bajío, rocas y tres peñas;
  - el montículo con cueva del PILAR CELESTE, como la ISLA VOLCÁNICA (reutiliza funciones de `crear_islas_sur.py`);
  - las 8 filas de arriba son mar (la RUTA 130 tiene otros gráficos).
- **El VALLE DEL DRAGÓN:**
  - la mitad de abajo de CIUDAD COLOSALIA (filas 40-79), con la gran cascada;
  - el Centro Pokémon pasa a ser hierba corta, los carteles pasan a hierba y las flores de la izquierda, a hierba alta;
  - la cueva de la CALLE VICTORIA es la entrada;
  - objetos y guardián, a la altura de su suelo (el valle tiene varias).
- **Flags:** 0x8FF (guardián), 0x905, 0x906 (oculto) y 0x907.

### Además
- **Flags:** en `colocar_objetos.py`, los bloques de las megapiedras Gigamax, el DESIERTO, la ISLA NEVADA y el BOSQUE acaban donde acaban de verdad, porque sus últimos flags son ahora de estos biomas.
- **Sitios descartados para la ISLA DEL DRAGÓN:**
  - **Debajo de la RUTA 129:** ahí está ya la ISLA DE RUINAS.
  - **Encima de la RUTA 130 o la 125:** la isla se vería mal (la ISLA ESPEJISMO) o se llegaría en el tramo 7.
- **Zonas de captura:** 121 de 128.
- **Flags libres:** casi ninguno. Solo quedan 0x1E0 y los de Jorge.

## Cómo se comprobó

- **Las herramientas de comprobación:**
  - `comprobar_zonas.py`: 0 fallos. Primero dio el nombre de una música que no existe y las alturas del valle; arreglado.
  - `sin_salida.py --comprobar`, `alcance.py --comprobar` y `variantes.py --comprobar`: 0.
  - `graficos.py`: nada de estos mapas.
- **`alcance.py`, por tramos:**
  - CANTERA: tramo 3 (no en el 2).
  - PRADO: tramo 6 (no en el 5).
  - ISLA y VALLE DEL DRAGÓN: se alcanzan (desde el tramo 7, como las otras islas del sur).
- **Fotos de cada uno:** `fotos_zonas/20` a `22`, enviadas a Miguel.
- **Compilación:** la hará el CI. **Sin probar en el emulador.**

## Pendiente

- **Probar jugando** (`PRUEBAS.md`).
- **Jorge:** las fotos de la guía (`fotos_guia.py`), por los Ticket-Recuerdo nuevos.
- **Lo siguiente del plan:**
  - comprobar jugando las habilidades, el Parche Habilidad y la mochila;
  - los amigos de los Centros Pokémon (falta la lista);
  - los entrenadores de las zonas nuevas.
