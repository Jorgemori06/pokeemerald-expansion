# 21/11/2026 — Miguel: quinta prueba (versión 8.5), lo de Jorge y el plan nuevo

## Qué dijo Miguel

- **Reinicio de la ISLA NEVADA:** arreglado. La isla "ya está muy bien".
- **ISLA DE RUINAS:** sigue sin poder entrar. Hay que rehacerla, con una entrada más clara y una zona mejor.
- **DESIERTO PROFUNDO:** se entra y funciona. Pero es el mismo dibujo que el desierto y la TORRE ESPEJISMO: hay que rehacerlo (y las RUINAS ARENOSAS), para que cambien el escenario y la manera de avanzar.
- **ISLA VOLCÁNICA:** se entra también desde la RUTA 134, y la parte de PORTUAL se buguea. Que solo se pueda entrar por PORTUAL.
- **MÁXIMO PEÑAS:** bien como lo dejó Jorge.
- **Ideas nuevas:**
  - un prado o bosque de flores para el tipo Hada, en la RUTA 119, antes del INSTITUTO METEOROLÓGICO, junto a la zona de vallas y jardín;
  - una o más islas para el tipo Dragón, con cascadas y montañas y aire épico, para el final del juego.
- **También:**
  - comprobar las habilidades, el Parche Habilidad y la mochila;
  - ir añadiendo los amigos de los Centros Pokémon con su regalo.
- **El orden:**
  1. lo de Jorge (sin choques entre las PR);
  2. lo demás, cuando Miguel diga.

## Qué se ha hecho

- **Choques entre las PR abiertas:**
  - La #112 (Miguel) y la #115 (Jorge) chocaban en `IDEAS.md`: las dos cambiaban la línea "Estado" de la idea 8.
  - En la #112, la respuesta de Miguel pasa a otra línea.
  - Ahora la #112, la #113 y la #115 se fusionan en cualquier orden (probado en local con `git merge`).
- **Revisión de la #115** (nombre de 10 letras y mochila):
  - El código está bien.
  - El CI falla solo en `test/save.c`: los tamaños de la partida guardada siguen siendo los de antes. Como la PR cambia la partida a propósito, hay que poner los nuevos, que son los que da el propio CI:
    - `T_SAVEBLOCK1_SIZE` 15680;
    - `T_SAVEBLOCK2_SIZE` 3896;
    - `T_SAVEBLOCK3_SIZE` 1404 (4 + 150×4 + 70×4 + 130×4).
- **`PLAN.md`, sección 0:** la prueba, qué hay que arreglar y el orden de lo siguiente.
  - Las propuestas C (Prado de las Hadas, ahora en la RUTA 119) e I (isla del dragón) cambian de sitio.
  - Las preguntas del 18/11 pasan a "0 bis".

## Pendiente

Todo lo de `PLAN.md`, sección 0, en ese orden. Lo primero, que Jorge arregle `test/save.c` en la #115 y fusione las PR.
