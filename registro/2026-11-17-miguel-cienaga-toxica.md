# 17/11/2026 — Miguel: CIÉNAGA TÓXICA

## Qué se pidió

Después del BOSQUE SINIESTRO (`registro/2026-11-17-miguel-bosque-siniestro.md`), Miguel eligió el siguiente bioma del mapa de propuestas: la **Ciénaga tóxica (D)**, para el tipo Veneno.

## Qué se ha hecho

- **Otro sitio que el de la propuesta:** la D iba al este de la RUTA 110, pero ese borde es todo agua y haría falta SURF (tramo 6). Va al **sur de la RUTA 117**:
  - se entra andando (x 32-36, junto a la hierba alta);
  - es del **tramo 3**;
  - usa los mismos gráficos (Mauville).
  - Las copas de árbol del borde de la RUTA 117 en esas casillas pasan a ser hierba alta y hierba.
- **`tools/dualocke/crear_cienaga_toxica.py`** (60 × 40):
  - siempre llueve;
  - charcas, hierba alta y un camino de barro;
  - el guardián, en un islote de la charca grande al que se llega por una lengua de tierra.
- **Guardián:** Dragalge sin semilla, nivel 29. Premio, Lodo Negro y su megapiedra. Flag 0x472.
- **Salvajes:**
  - **Hierba alta:** Grimer, Croagunk, Koffing, Gloom, Weepinbell, Wooper de Paldea, Arbok, Trubbish, Foongus y Grafaiai; raros, Salandit y Toxel.
  - **Pesca:** Barboach, Skrelp, Qwilfish, Mareanie y Whiscash.
  - **Surf:** más tarde.
- **Objetos:** Flecha Venenosa, Bulbo, Tabla Tóxica oculta y un Ticket-Recuerdo, en flags sueltos (0x054, 0x055, 0x479 y 0x1AA).
- **Una científica** que estudia el agua. No hay entrenadores, porque no queda ningún hueco libre.
- **Zona de captura propia:** 118 de 128.
- **`autotile.py`:**
  - los árboles normales de Hoenn pasan a `arbol_normal()` y `copa_normal()`, compartidas con el BOSQUE SINIESTRO (que sale igual);
  - "Cienaga" se añade a `NUEVOS`. Sin eso, el autotile aprendía de la propia ciénaga como si fuera un mapa original, y la revisión de piezas daba 0 sin serlo.
- **Lo que no quedó bien y se cambió:**
  - **La hierba muy alta** (la de la RUTA 120): su borde de abajo solo existe en los gráficos de ARBORADA. Se cambió por hierba alta.
  - **Las charcas con escalones** dejaban esquinas sin orilla. Ahora son rectas, como las de la RUTA 117.
- **Documentación:** `DUALOCKE.md`, `PRUEBAS.md` y `GUIA.html`.

## Cómo se comprobó

- **`comprobar_zonas.py`:** 0 fallos (958 mapas, 118 de 128 zonas). El objeto oculto lleva un flag de 0x1F4 en adelante.
- **Parejas de piezas que el juego no usa:** 16, casi todas en las curvas del camino de barro y en la entrada.
- **Alcance:**
  - desde la entrada se llega al guardián, a la científica y a los cuatro objetos;
  - desde el islote se vuelve a la entrada.
- **La cadena de niveles, salvajes y objetos:** vuelta a lanzar entera.
- **Compilación:** la hará el CI de la PR.

## Pendiente

- Que compile en GitHub y probarlo en el juego (`PRUEBAS.md`, CIÉNAGA TÓXICA).
- Siguiente bioma, si Miguel quiere.
