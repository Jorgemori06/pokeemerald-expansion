# 13/11/2026 — Jorge: traducción de la tele, el hombre de Malvalona y las Carpas de Combate

## Qué se pidió

Jorge seguía encontrando textos en inglés jugando. De los bloques que quedaban, eligió los tres que se ven en la historia: "Ponte con los 3". Después avisó de que "todo el tema de la carpa de combates está también en inglés".

## Qué se ha hecho

- `58_carpas_de_combate.tsv` (66): recepcionistas y reglas de las tres CARPAS DE COMBATE (`data/text/battle_tent.inc`). Los torneos se llaman "Torneo KO" y "Torneo de Intercambio".
- `59_hombre_malvalona.tsv` (166): el hombre del CENTRO POKéMON de MALVALONA, que cambia con el tiempo.
  - Las acciones del CUENTACUENTOS van en participio, porque se leen como "¿Has <acción> N veces?".
  - Los fragmentos del CHARLATÁN mantienen el espacio inicial, porque se pegan a palabras del chat fácil (que siguen en inglés).
- `60_tele_1.tsv`, `61_tele_2.tsv` y `63_tele_3.tsv` (399): todos los programas de la tele (`data/text/tv.inc`) y las entrevistas de los reporteros.
- `62_carpas_mapas.tsv` (31): la gente de los vestíbulos de las carpas y la sala de CONCURSOS de PORTUAL, cuyos textos están en el pasillo de la carpa.
- `src/strings.c`:
  - las pantallas de alquiler y cambio de la carpa de PORTUAL y los resultados de las carpas, con `ES()`;
  - los tres avisos de Pokémon que no valen en la Frontera.
- Índice en `traduccion/dialogos/LEEME.md` y nota en `DUALOCKE.md`, sección 8.

## Cómo se comprobó

- `dialogos.py comprobar`: 0 errores (anchos de 208 px y códigos).
- `dialogos.py aplicar` y `make` compilan.
