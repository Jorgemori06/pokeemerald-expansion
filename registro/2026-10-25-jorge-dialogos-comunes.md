# 25/10/2026 · Jorge · Diálogos comunes en español

Sesión de Jorge con Claude (noche). Rama `jorge/dialogos-comunes`. Son los textos comunes que le tocaban a Jorge según `traduccion/dialogos/PLAN.md`. Miguel está con los tramos de zonas de Jorge en el #32 y se le avisó allí antes de empezar, para no repetir.

## Qué se ha traducido

Unas 12.000 palabras, 580 textos, con la herramienta de Miguel (`tools/dualocke/dialogos.py`):

| Archivo | Textos | Qué es |
|---|---|---|
| `50_loteria_cuestionario_perfiles.tsv` | 35 | LOTERÍA del CENTRO COMERCIAL, el cuestionario y el hombre de los perfiles (`lottery_corner`, `questionnaire`, `profile_man`) |
| `51_noticias_pokemon.tsv` | 12 | NOTICIAS POKéMON de la tele (`pokemon_news`) |
| `52_damas_calagua.tsv` | 52 | Las tres DAMAS del CENTRO POKéMON de CALAGUA (`lilycove_lady`) |
| `53_sala_concursos.tsv` | 76 | SALA DE CONCURSOS (`contest_hall`) |
| `54_club_cable_inalambrico.tsv` | 91 | CLUB CABLE y CLUB INALÁMBRICO, SALA UNIÓN y minijuegos de ALGARIA (`cable_club`) |
| `55_agenda.tsv` | 317 | Todas las llamadas de la AGENDA del POKéNAV (`match_call`) |

## Criterios

- **Nombres de la tabla del `LEEME.md`:**
  - PETRA, MARCIAL, ERICO, CANDELA, ALANA, VITO y LETI, GALANO, PLUBIO, MÁXIMO, AURA, BRUNO, BLASCO, SR. PEÑA, SR. ARENQUE, CAPITÁN BABOR…
  - LEÑADOR y MAESTRO DE GOLPE ROCA, como ya estaban en los tramos de Miguel.
  - SIGNO MAGMA, como lo corrigió Miguel.
- **Alto Mando:** SIDNEY, FÁTIMA, NÍVEA y DRACÓN.
- **Concursos:**
  - Categorías: CARISMA, BELLEZA, DULZURA, INGENIO y DUREZA.
  - Rangos: NORMAL, SUPER, HIPER y MASTER.
  - Premios: CINTA. Personajes: PRESENTADOR y JUEZ.
- **Sin confirmar** (no estaban en la tabla):
  - BOLETO LOTO;
  - SALA UNIÓN, RINCÓN DIRECTO y RINCÓN DE DATOS;
  - MACHACABAYAS, POLVO BAYA;
  - SALTO POKéMON y RECOGEBAYAS DODRIO;
  - TEALA;
  - las tres DAMAS (DE LOS FAVORES, DE LAS PREGUNTAS, DE LOS CONCURSOS).
- **Sin género para el jugador**, como pide el `LEEME.md`: "te damos la bienvenida", "ganaste el título" en vez de "fuiste campeón", "de la familia de NORMAN"…
- **Llamadas del FRENTE BATALLA** (rachas, Domo, Pike, Pirámide): son del postgame, pero se han traducido igual porque están en el mismo archivo y son muy repetitivas.

## Comprobado

- `dialogos.py comprobar`: 3553 textos, 0 errores (ancho en píxeles y códigos).
- `dialogos.py aplicar` y `make`: compila sin errores ni avisos.
- `make check`: ver el PR. Ningún test usa estos textos.

## Pendiente

- Cuando se fusione el #32, apuntar estos archivos en `LEEME.md` ("Hecho") y en `PLAN.md`. Ahora no se tocan para no chocar con el #32.
- Probarlo jugando: sobre todo la AGENDA, que mete nombres y lugares con `{STR_VAR_1}` y `{STR_VAR_2}`.
