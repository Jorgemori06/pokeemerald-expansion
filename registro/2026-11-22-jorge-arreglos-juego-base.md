# 22/11/2026 — Jorge (con Claude): arreglos de lo que encontró el bot en el juego base

Rama `jorge/arreglos-juego-base`. Son los fallos del juego base que encontró el bot al pasarse el juego entero (PR #118, `registro/2026-11-22-jorge-bot-partida-completa.md`). Los de las zonas nuevas de Miguel están comentados en sus PR (#116 y #117). Los textos en inglés van en otro PR.

## Toxtricity Grave pasaba a Aguda

- **Qué pasaba:** al acabar cualquier combate (o al debilitarse), Toxtricity Grave se convertía en Toxtricity Aguda. Lo vio el bot en el MUSEO OCEÁNICO con su Toxtricity de naturaleza Tranquila.
- **Por qué:** en `src/data/pokemon/species_info/gen_8_families.h`, `SPECIES_TOXTRICITY_LOW_KEY` y `SPECIES_TOXTRICITY_LOW_KEY_GMAX` usaban `sToxtricityAmpedFormChangeTable`, que con `FORM_CHANGE_END_BATTLE` y `FORM_CHANGE_FAINT` te devuelve a la Aguda. Viene de la expansion (#4281), no de nuestros cambios.
- **Arreglo:** usan `sToxtricityLowKeyFormChangeTable`. Se miraron las 339 especies con tabla de cambios de forma: ninguna otra usa la de otra especie (las que salen, Deoxys, Zygarde y Cramorant, cambian siempre a otra forma a propósito).
- **Test:** `test/battle/form_change/end_battle.c`, "Dualocke: Toxtricity Low Key stays Low Key upon battle end" (y lo mismo con la Aguda). Sin el arreglo falla.
- Con las partidas en curso: el que ya haya pasado a Aguda se queda Aguda.

## Poké Balls que tapaban el paso

- **Qué pasaba:** `colocar_objetos.py` no ponía Balls encima de puertas, pero sí delante. El bot encontró la de las GAFAS ESPECIALES delante de la escalera del MUSEO OCEÁNICO 2F y la del TICKET-RECUERDO delante de la puerta del MONTE PÍRICO (RUTA 122). Se pueden coger, así que no te encierran, pero hasta que no la coges no pasas.
- **Comprobación nueva en `sin_salida.py` (va en el CI):** `bolas_que_tapan` mira, para cada Ball, si con ella en medio deja de poder irse entre dos salidas del mapa, si es la única casilla para entrar por una puerta, o si deja sin poder llegar a una persona, un entrenador o un cartel. Detrás de una Ball sí puede haber otra. Solo mira las Balls de `colocar_objetos.py` y las de las zonas nuevas: con todas, salen también cuatro de Esmeralda (MALVALONA, RUTAS 116, 117 y 123) que tapan a propósito (detrás de un árbol de CORTE, etc.).
- **Encontró 12:**

  | Mapa | Ball | Tapaba | De → a |
  |---|---|---|---|
  | MUSEO OCEÁNICO 2F | Gafas Especiales | la escalera | (6, 2) → (7, 2) |
  | RUTA 122 | Ticket-Recuerdo | la puerta del MONTE PÍRICO | (22, 30) → (21, 30) |
  | RUTA 124 | Ticket-Recuerdo | la puerta de la casa del cazador | (70, 49) → (71, 49) |
  | PILAR CELESTE 3F | Altarianita | la escalera | (3, 2) → (2, 2) |
  | PILAR CELESTE 4F | Cubresuelos | la escalera | (11, 2) → (12, 2) |
  | PILAR CELESTE 5F | Dragonitita | la escalera | (3, 2) → (4, 2) |
  | ISLA LEJANA (entrada) | Maxipepita | el camino entre el muelle y el resto de la isla | (17, 21) → (18, 20), a mano |
  | RUTA 106 | Ticket-Recuerdo | al pescador Elliot | (52, 14) → (52, 15) |
  | RUTA 115 | Cinta Experto, Ticket-Recuerdo, Copperajahita | a Timothy (tres Balls seguidas en su pasillo) | (6, 15) → (9, 15), (7, 15) → (8, 16), (8, 15) → (9, 16) |
  | CAMINO ESCABROSO | Cameruptita | al montañero Eric | (11, 8) → (14, 7) |

- **`colocar_objetos.py`:** al colocar, ya no elige casillas en las que la Ball tape algo. Y con `--mover` mueve a la casilla buena más cercana (a 1-4 pasos) las que ya estén puestas y tapen. **Solo les cambia la x y la y**, sin quitarlas de la lista, para no cambiar el número de los demás objetos del mapa (los scripts los usan). La de la ISLA LEJANA no tenía sitio a 4 pasos y se movió a mano a la esquina de la sala de las gemelas.
- Las de la CALLE VICTORIA que apuntó el bot (junto a Edgar y Samuel) no tapan nada: se pasa por abajo. Se quedan.
- Con las partidas en curso no pasa nada: el flag de cada Ball es el mismo, así que si ya la has cogido no vuelve a salir. Si has guardado dentro de uno de esos mapas, la Ball sigue en el sitio viejo hasta que sales y vuelves a entrar.
- Se han regenerado las pistas y las fotos de la guía (`guia.py` y `fotos_guia.py`) de esas Balls.

## Comprobado

- `make`, `make check` entero, y `alcance.py`, `sin_salida.py`, `graficos.py` y `variantes.py` con `--comprobar`.
