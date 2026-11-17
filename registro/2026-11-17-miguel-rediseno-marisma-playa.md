# 17/11/2026 — Miguel: rediseño de la MARISMA AZULIZA y la PLAYA VOLCÁNICA, y guardianes únicos

## Qué se pidió

Miguel, después de ver las fotos de todas las zonas nuevas:

- La MARISMA AZULIZA y la PLAYA VOLCÁNICA "quedan raras". Hay que mirar cómo están diseñadas las rutas, playas y pantanos del juego (qué piezas van en cada sitio) y hacerlas igual. Que tengan "un sentido de atravesar": manchas de hierba distintas, zonas sin hierba, agua, rocas y árboles grandes y pequeños. Si se puede, mejorar también las demás zonas con lo aprendido.
- **Que cada guardián sea único.** Se quedan Houndoom, Baxcalibur, Garchomp, Gengar, el Charizard de la ISLA VOLCÁNICA, el Salamence de la CUMBRE METEORO y el Metagross de la ISLA DE RUINAS.
  - Dondozo o Tatsugiri en una parte de la marisma que se abra más tarde.
  - En las islas del ferry, Pokémon que recuerden a Ho-Oh y Lugia: Kingdra, Dragonite y Volcarona.
  - En otras islas, Pokémon Paradoja (Slither Wing, Flutter Mane, Roaring Moon…).
- "Primero vamos a arreglar esto y luego veremos qué más podemos ampliar."

## Qué se ha hecho

- **`tools/dualocke/autotile.py` (nuevo):** aprende de los mapas originales de exterior qué pieza va en cada sitio según sus vecinas, pinta un mapa dibujado con letras y cuenta las parejas de piezas que el juego no usa. Pinta también árboles grandes. Ver `DUALOCKE.md`, "Dibujar mapas como los del juego".
- **Reglas sacadas mirando el juego** (la RUTA 104, AZULIZA, ARBORADA…):
  - La arena de playa nunca toca la hierba: siempre hay un risco o agua entre las dos.
  - El risco tiene la hierba arriba o a la izquierda y se baja por una escalera.
  - La orilla de abajo de una charca se dibuja sobre la hierba.
  - Los árboles de AZULIZA solo van sobre arena.
- **MARISMA AZULIZA rehecha** (48 × 34, antes 36 × 20):
  - Al este, la playa de AZULIZA; un risco con escalera la separa de la pradera.
  - En la pradera hay manchas de hierba alta y de hierba muy alta, sitios sin hierba, árboles y flores.
  - Al oeste, un lago y una cala a la que solo se llega con SURF.
  - Cuatro rocas para GOLPE ROCA con su tabla de salvajes.
- **Dondozo y Tatsugiri** en la cala, a nivel 59. Usan flags normales libres (0x1E2 y 0x1E3) y la regla nueva `("tope", 6)` de `reescalar_niveles.py`: la marisma está en el tramo 2, pero sin SURF no se llega.
- **PLAYA VOLCÁNICA rehecha** (40 × 40):
  - Una playa con orilla, bajío, charca de marea, rocas y arrecife.
  - Un risco con escalera la separa de una meseta con hierba alta, árboles, un camino de tierra, una peña volcánica (RUTA 112) y el rincón de las termas de LAVACALDA.
  - La unión con la RUTA 122 sigue siendo solo de gráficos generales (el script lo comprueba).
- **Guardianes únicos**, sin semilla:

  | Sitio | Antes | Ahora |
  | --- | --- | --- |
  | ISLA SUR | Salamence | Dragonite |
  | ISLA LEJANA | Tyranitar | Flutter Mane |
  | ISLA ORIGEN | Metagross | Roaring Moon |
  | ROCA OMBLIGO, cima | Charizard | Volcarona |
  | ROCA OMBLIGO, fondo | Gyarados | Kingdra |
  | ISLA ARENOSA | Tyranitar | Sandy Shocks |
  | PLAYA VOLCÁNICA | Gyarados | Slither Wing (premio: Energía Potenciadora) |
  | MARISMA AZULIZA, cala | — | Dondozo y Tatsugiri |

  - Los premios de las islas no cambian.
  - Los Pokémon Paradoja no cuentan como legendarios en el locke: la regla solo mira los restringidos, los singulares y los míticos.
- **Documentación:** `DUALOCKE.md`, `PRUEBAS.md` y `GUIA.html`.

## Problemas encontrados y arreglados al hacerlo

- **Parejas raras:** la marisma vieja tenía 118 parejas de piezas vecinas que el juego no usa, y la playa 240. Ahora tienen 63 y 61. Las que quedan son uniones con trozos copiados (las termas, la peña, la franja del pueblo).
- **Hierba larga y árboles de AZULIZA:** la hierba larga (0x015) casi no tiene bordes en el juego, y los árboles de AZULIZA solo existen sobre arena. Si una vecina no sale en ningún mapa, el aprendiz busca por grupo (hierba, hierba alta y hierba larga cuentan como "tierra"), y los árboles del pueblo solo se ponen en la arena.
- **Árboles grandes cortados:** los grupos de árboles de 2 × 2 tienen que tener un número de columnas que cuadre. `arboles_grandes()` lo comprueba, también en los bordes del mapa. Las copas sobre hierba normal usan 0x1CE/0x1CF (la 0x1C6 parecía una mata de hierba).
- **Pico de agua en las charcas de marea:** en la esquina de abajo a la derecha el aprendiz elegía 0x11B. Ahora pone el borde recto (0x123), como en el lado izquierdo.
- **Objetos de la playa:** al cambiar el mapa, tres objetos quedaron en el risco, en el mar y en el bajío. Se movieron a mano a la arena y a la hierba (anotado en `colocar_objetos.py`).

## Cómo se comprobó

- **`comprobar_zonas.py`:** 0 fallos en 956 mapas (zonas 116 de 128, entrenadores 864 de 864).
- **Alcance**, con los saltos de risco de un solo sentido:
  - En la marisma, a pie se llega a todo menos a la cala; con SURF, también a la cala.
  - En la playa se llega a todo a pie.
  - Todos los objetos se pueden coger.
- **Cadena de niveles completa:**
  - Dondozo y Tatsugiri 59, Slither Wing 70, Sandy Shocks 81, Dragonite 70, Flutter Mane 81, Roaring Moon, Volcarona y Kingdra 97.
  - En `trainers.party` no cambia nada; en `wild_encounters.json` solo se añade la tabla de GOLPE ROCA de la marisma.
- **Mapas:** dibujados y revisados en las fotos.
- **No se ha compilado** (sin WSL).

## Pendiente

- Probarlo en el juego (`PRUEBAS.md`).
- Mejorar las otras zonas nuevas con lo aprendido, cuando Miguel diga cuáles.
