# 23/10/2026 · Miguel · Paso 1 (reglas fáciles)

Sesión de Miguel con Claude (Claude Code, escritorio de Windows). Resumen de lo que se pidió, lo que se hizo y lo que queda.

## Lo que se pidió

1. Leer `DUALOCKE.md`.
2. Hacer el paso 1 del orden de trabajo: mote obligatorio, quitar curativos y Objetos X de las tiendas, Caramelos Raros a 1 ₽, bloquear Objetos X en combate, correr sin Deportivas, Pokédex Nacional desde el inicio, MTs reutilizables y MOs olvidables.
3. Subirlo al repo de Jorge mediante un fork y un PR, para que el CI compile y pase los tests.
4. Arreglar los tests de experiencia que rompía el level cap.
5. Escribir este registro y un plan para trabajar en paralelo (sección 13 de `DUALOCKE.md`).

## Cómo se hizo

### Entorno

- El PC de Miguel **no tiene WSL ni el compilador de ARM**, así que no se pudo compilar en local. Se clonó el repo en Windows y la compilación se dejó al CI de GitHub.
- En Windows, `git clone` falla con `Filename too long` en un archivo de tilesets. Se arregla con `git config core.longpaths true` y `git checkout -- .`. Queda anotado en la sección 3 de `DUALOCKE.md`.
- La cuenta de GitHub de Miguel (**Mike360mine**) no tiene permiso de escritura en el repo de Jorge, así que se creó el fork `Mike360mine/pokeemerald-expansion` y se abrió el PR [Jorgemori06/pokeemerald-expansion#1](https://github.com/Jorgemori06/pokeemerald-expansion/pull/1) desde la rama `dualocke/paso1`.
- **El CI nunca se había ejecutado en el repo de Jorge.** GitHub desactiva Actions en los forks hasta que el dueño lo activa en la pestaña Actions. Miguel lo activó en su fork, y el CI se ejecutó allí (al subir a `master` del fork).

### Cambios

| Commit | Qué cambia para el jugador | Archivos |
| --- | --- | --- |
| Correr, Pokédex Nacional, MTs y MOs | Se corre desde el principio, Pokédex Nacional desde el inicio, las MTs no se gastan, las MOs se pueden olvidar | `src/new_game.c`, `include/config/item.h`, `include/config/pokemon.h` |
| Mote obligatorio al capturar | Sin Sí/No; si se deja el nombre de la especie, se vuelve a pedir | `src/battle_script_commands.c`, `src/battle_message.c` |
| Tiendas | Sin curativos (PS, estados, Revivir, hierbas) ni Objetos X; Caramelos Raros a 1 ₽ en todas esas tiendas | 17 `data/maps/*/scripts.inc`, `src/data/items.h` |
| Objetos X en combate | El jugador no puede usar Objetos X, Directo, Protección X ni Maxisetas | `src/item_use.c` |
| Level cap en los tests | Nada en el juego; el cap no se aplica al compilar los tests | `src/caps.c` |
| Mote obligatorio en regalos y huevos | Sin Sí/No al recibir un regalo, al elegir inicial ni al eclosionar; se repite si se deja el nombre de la especie | `src/tv.c`, `src/egg_hatch.c`, `src/strings.c`, `data/text/pc_transfer.inc`, scripts de regalos |

### Decisiones tomadas por el camino (revisables)

- **"Curativos" incluye los de estado** (Antídoto, Cura Total…), no solo los de PS. Si no se quería así, se vuelven a poner en las tiendas.
- La **Herboristería de Lavacalda** y el mostrador de **Objetos X de Grandes Almacenes Calagua** venden ahora Caramelos Raros, para no quedarse vacíos.
- Los **Maxisetas** también cuentan como Objeto X.
- Los **rivales sí pueden** usar Objetos X; la regla es solo para el jugador.
- El **Calificanombres** también obliga a poner un nombre distinto al de la especie (comparte código con los regalos). Da igual, porque todos llevan mote.
- Mensajes nuevos en inglés, como el resto del juego: "Give X a nickname!" y "The locke rules don't allow using this item in battle!".

### CI

- Primera ejecución: compilan Esmeralda, FireRed, LeafGreen y la release. Los tests fallaban (4 tests de experiencia), **igual que en el commit de Jorge sin los cambios**: el level cap duro deja el cap en 16 en los tests, porque allí no hay medallas.
- Arreglo: `GetCurrentLevelCap()` devuelve `MAX_LEVEL` si `TESTING`. Resultado de esa ejecución: en curso al escribir esto (se apunta aquí cuando termine).
- Los tests `Tests resume after CRASH` y `fatalf counts as CRASH` salen como `CRASH` a propósito; no son fallos.

## Lo que queda

- **Probar jugando** en mGBA: pantalla de mote, tiendas, Objetos X, correr y Pokédex.
- Jorge: activar Actions en su repo, revisar y fusionar el PR #1, y decidir si añade a Miguel como colaborador (ver sección 13 de `DUALOCKE.md`).
- Visto de pasada, sin tocar: en `include/config/caps.h`, la línea de `B_EV_CAP_TYPE` tiene un `#define B_EV_CAP_VARIABLE 12` metido en el comentario. No afecta a nada, pero está feo.
