# 17/11/2026 — Miguel: rediseño de la ISLA NEVADA

## Qué se pidió

Después de las islas del sur (`registro/2026-11-17-miguel-rediseno-islas-sur.md`), Miguel pidió seguir con la ISLA NEVADA.

## Qué fallaba

La isla era el islote de la CUEVA CARDUMEN de la RUTA 125 pegado arriba del mapa:

- En la RUTA 125 ese islote sigue por fuera del mapa. Aquí acababa cortado en recto contra el borde de arriba.
- Al lado había un banco de arena suelto y mucho mar vacío.

## Qué se ha hecho

Se dibuja como las islas del sur: con letras (`PLANO`), que pinta `autotile.py`. Se usan `dibujar()` y `sello()` de `crear_islas_sur.py`.

- **La isla** (80 × 40, mismo tamaño): una isla grande de arena con su anillo de bajío y una cala al sur. Tiene tres peñas de la RUTA 127, y rocas sueltas y remolinos en el mar.
- **La cresta:** arriba va la cresta de roca del islote grande de la RUTA 127, que tiene cima. Se copian solo sus casillas de roca, sin las rocas del mar de al lado.
  - Sus dos huecos de base secreta se tapan.
  - En su pie se abre la entrada de la cueva, con las piezas de la cueva del PILAR CELESTE (0x064 encima y 0x0A9 a los lados).
  - La entrada lleva a la CUEVA HELADA, que no cambia.
- **Entrenadores y objetos** (`SITIOS`):
  - DUDLEY y KAYLEE nadan en el mar del sur, por donde se llega desde la RUTA 124.
  - La Bola de Nieve oculta está en la punta oeste.
- **Documentación:** `DUALOCKE.md`, `PRUEBAS.md` y `GUIA.html`.

## Cómo se comprobó

- **Parejas de piezas que el juego no usa:** 2, el pie de las dos peñas pequeñas (por tapar la base secreta, como en las islas del sur). No queda ninguna base secreta.
- **Alcance**, surfeando desde abajo (la RUTA 124): se llega a la cueva, a los dos nadadores y a la Bola de Nieve. En la cueva, a la escalera, a NIEVES, a los objetos y al guardián.
- **`comprobar_zonas.py`:** 0 fallos.
- **No se ha compilado** (sin WSL).

## Pendiente

- Probarlo en el juego (`PRUEBAS.md`, ISLA NEVADA).
