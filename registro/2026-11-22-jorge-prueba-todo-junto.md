# 22/11/2026 (tarde) — Jorge (con Claude): todo junto antes de las ROMs

Miguel arregló los fallos de las zonas que vio el bot (#116 y #117) y metió la regla de la Liga en el juego (#122), y preguntó si se podían hacer ya las ROMs para jugar. Antes de fusionar, Claude lo probó todo junto, sin tocar `master`.

## Todo fusionado en local

Rama `prueba/integracion-todo`, que no se ha subido: `master` + #117 (que lleva el #112, el #113 y el #116) + #115 + #118 + #122 + #119 + #120 + #121.
- Solo hay dos choques:
  - `GUIA.html`: las dos líneas generadas; se vuelven a generar con `guia.py` y `fotos_guia.py`;
  - `DUALOCKE.md`: el mapa del código, con una línea de cada lado.
- `alcance.py`, `sin_salida.py`, `graficos.py`, `variantes.py` y `comprobar_zonas.py` dan 0, y `make` compila.
- Volver a lanzar `aplicar_descripciones.py` y `textos_graficos.py` no cambia nada.

## Zonas arregladas, con el bot

Con la ROM release (semilla 777000111, sin el #115 porque cambia la partida guardada) y la partida de después de la Liga:
- **ISLA VOLCÁNICA:** el barquero nuevo, (37, 40) en PORTUAL, lleva y trae; guardián vencido.
- **TORRE de la ISLA DE RUINAS:** ya se entra; guardián vencido.
- **PRADO DE HADAS:** se entra desde la RUTA 119; guardián vencido.
- **DESIERTO PROFUNDO:** desde el norte (12, 12) se vuelve andando a la RUTA 111, sin VUELO.
- **RUTA 130 → ISLA DEL DRAGÓN:** por la x 70 se baja; por la 76 ya no se cruza, como quería Miguel.
- No se pierde ninguna vida.
- En el bot se ha cambiado el sitio del barquero (`VIAJES` de `piloto.py`, en el #118).

## Regla de la Liga, en el emulador

- **La tienda:** el dependiente explica la regla, y dos compras seguidas de RESTAURAR TODO (3 y 2) se cobran enteras, 3000 ₽ cada uno.
- **La cura al entrar en la sala de SIXTO:** con los PS bajados a mano (50/345 y 20/236), sale el mensaje y el equipo queda entero.
- **Si el rival no ha curado,** no deja usar RESTAURAR TODO y el objeto no se gasta. **Fallo:** salía "No tendrá ningún efecto" y no el mensaje de la regla. Los curativos se usan eligiendo un Pokémon, y `party_menu.c` enseñaba siempre ese texto. **Arreglado** en `jorge/mensaje-regla-liga`, encima del #122: enseña el motivo que deja `CannotUseItemsInBattle` en `gStringVar4`. Comprobado: ahora sale "Regla de la Liga: no puedes curar más veces que el rival.".
- **Si el rival ha curado una vez** (contador puesto a 1 en memoria), deja curar una vez (de 100 a 345 PS) y a la siguiente vuelve a bloquear.
- **Los del rival se cuentan:** en un combate entero, SIXTO usó 2 RESTAURAR TODO y su contador quedó en 2.

## Visto de paso

- Al curar con RESTAURAR TODO en combate sale "Mandibuzz ha recuperado PS." con el nombre de la especie, no el mote (Gus). No es de la regla.
