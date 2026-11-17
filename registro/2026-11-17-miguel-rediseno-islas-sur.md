# 17/11/2026 — Miguel: rediseño de las islas de las rutas del sur

## Qué se pidió

Después del BOSQUE FRONDOSO (`registro/2026-11-17-miguel-rediseno-bosque.md`), Miguel eligió la siguiente zona que mejorar con lo aprendido: "Las islas del sur" (ISLA DE RUINAS, ISLA VOLCÁNICA e ISLA ARENOSA).

## Qué fallaba

Eran trozos de islotes del juego copiados tal cual (`isla()` de `crear_islas_sur.py`):

- **ISLA DE RUINAS:** la franja de arena de abajo del PILAR CELESTE sigue fuera de su mapa. Al copiarla, acababa cortada en recto contra el mar, con media roca cortada al lado.
- **ISLA VOLCÁNICA:** un montículo del PILAR CELESTE pegado sobre un bajío de la RUTA 134, de forma cuadrada.
- **ISLA ARENOSA:** dos islotes de arena y uno de árboles de la RUTA 127, iguales que los de la ruta. La hierba alta estaba puesta sobre el bajío.

## Qué se ha hecho

- **Mirando las islas de las RUTAS 127-134 y ARRECÍPOLIS:**
  - la arena va rodeada de un anillo de bajío de 2 o 3 casillas;
  - sobre la arena hay peñas, y en el mar rocas sueltas y remolinos, separados del bajío;
  - la arena nunca toca la hierba: en ARRECÍPOLIS la hierba está en lo alto, con acantilados, y en la ISLA ARENOSA va en un islote aparte, con orilla de mar.
- **ISLA VOLCÁNICA** (40 × 30): ahora es una isla de arena con su bajío. Tiene tres peñas de la RUTA 127 y rocas en el mar. En medio está el montículo con la cueva que baja al CRÁTER. La cima del montículo se cambió por la de una peña, porque la suya tenía la sombra de la torre.
- **ISLA ARENOSA** (56 × 40):
  - Es una isla grande de arena con cinco peñas y una cala al sur.
  - Al oeste hay un islote de hierba con árboles, flores y la hierba alta de los salvajes.
  - DARÍO espera en la orilla oeste, mirando a donde se llega surfeando.
  - El guardián (Sandy Shocks) está en la punta del sur. Su texto se cambió: "Al sur de esta isla vive un POKéMON enorme".
- **ISLA DE RUINAS:** el islote del PILAR CELESTE no cambia. Abajo, la franja de arena acaba en una playa, sin bajío, como el islote. Se copia entera la roca con remolino de la orilla, y hay rocas en el mar.
- **Bases secretas:** las peñas de la RUTA 127 tienen un hueco de base secreta, y se tapa. La otra pieza que va en ese sitio (0x1A0) también es de base secreta, así que no se usa. Ninguna de las tres islas deja hacer bases secretas.
- **Objetos:** `crear_islas_sur.py` los mueve al sitio que les toca (`SITIO_OBJETOS`):
  - la Perla Grande oculta de la VOLCÁNICA;
  - las Gafa Protectora, la Sarta de Perlas oculta y el Ticket-Recuerdo de la ARENOSA (este último, en el islote de hierba).
- **`autotile.py`:** `pintar()` acepta casillas marcadas como `"pared"`, que pone el script y sus vecinas ven como acantilado (el mar de debajo del islote copiado). Antes, una etiqueta que no fuera un terreno daba error. La MARISMA AZULIZA, la PLAYA VOLCÁNICA y el BOSQUE FRONDOSO salen igual (comprobado volviendo a lanzar sus scripts).
- **Documentación:** `DUALOCKE.md` (las reglas de las islas de mar y la sección de las islas), `PRUEBAS.md` y `GUIA.html`.

## Cómo se comprobó

- **Parejas de piezas que el juego no usa:**
  - **ISLA VOLCÁNICA:** 2, el pie de dos peñas pequeñas (0x0AB junto a 0x079, por tapar la base secreta).
  - **ISLA ARENOSA:** 3, por lo mismo.
  - **ISLA DE RUINAS:** 12. Hay 7 en la puerta abierta de la torre (ya estaban) y 5 en la unión de la playa con la franja de arena. Mirada de cerca, la unión se ve bien.
- **Alcance**, surfeando desde la ruta de cada isla:
  - se llega a la cueva del CRÁTER, a la playa y al túnel de RUINAS (y por él, a la torre y a sus dos objetos);
  - en la ARENOSA se llega a DARÍO, al guardián y a los tres objetos.
- **`comprobar_zonas.py`:** 0 fallos (956 mapas, 116 de 128 zonas, 864 de 864 entrenadores).
- **No se ha compilado** (sin WSL).

## Pendiente

- Probarlo en el juego (`PRUEBAS.md`, islas de las rutas del sur).
- Seguir con otras zonas si Miguel quiere (queda la ISLA NEVADA).
