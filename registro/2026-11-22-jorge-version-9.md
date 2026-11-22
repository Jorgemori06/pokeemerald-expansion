# 22/11/2026 — Jorge: versión 9, la partida que cuenta (semillas nuevas)

## Qué se pidió

Miguel: "creo que de Pkmn está todo hecho; ¿haces las ROMs y lo jugamos?". Jorge: empezar el locke de cero y sacar las ROMs.

## Qué se ha hecho

- **Antes de fusionar, se probó todo junto** con el bot y la ROM release: las zonas arregladas por Miguel, la regla de la Liga (se encontró y arregló que no salía su mensaje, #123) y los tests completos (`registro/2026-11-22-jorge-prueba-todo-junto.md`).
- **Fusionados en `master`**, en este orden (Jorge aprobó los de Miguel):
  - de Miguel: #112, #113, #116 y #117;
  - el #115;
  - el #118, con el #123 dentro de la rama de Miguel y después el #122;
  - el #119, el #120 y el #121.
  - **Choques:** solo `GUIA.html` (las dos líneas generadas) y una tabla de `DUALOCKE.md`.
  - El #115 tenía el CI en rojo: no se habían actualizado los tamaños de la partida guardada en `test/save.c`. Se arregló antes de fusionar.
- **Comprobado en `master` (`e38ad8986f`):**
  - `make`;
  - `alcance.py`, `sin_salida.py`, `graficos.py`, `variantes.py` y `comprobar_zonas.py` dan 0;
  - `make check` entero (ver abajo).
- **Guía regenerada:** `guia.py` (164 pistas) y `emulador/fotos_guia.py` (164 fotos). Las Balls movidas del #119 y las zonas nuevas salen en su sitio.
- **ROMs** (`make release`, sin menús de depuración):
  - Jorge `2635893558`, md5 `989fda3e196b243041ccbc1b04e39665`;
  - Miguel `3483218843`, md5 `09358fb9f18594cc8575d60e6cdc6654`.
  - La de Jorge sale igual al compilarla otra vez (mismo md5).
  - Las dos se han probado en el emulador con una partida nueva:
    - intro y pantalla del nombre (ya en español: BORRAR, B BOTÓN, otros);
    - nombre de 9 letras (JORGEMORI) y de 8 (MIKEMINE);
    - camión con el control;
    - menú con el nombre entero y 20 vidas.
- `DUALOCKE.md`, sección 9: versión 9, commit y semillas.

## Ojo con el bot y las ROMs con semilla

`preparar.py` copia `pokeemerald.gba` y su `.elf`. Si se le pone a mano otra ROM (por ejemplo, la de una semilla), hay que copiar también **su** `.elf`: con otra semilla cambian las direcciones y el bot lee mal la memoria (no encuentra la pantalla del nombre). Las ROMs release salen como `pokeemerald-release.gba` y `pokeemerald-release.elf`.

## Pendiente

- Jugar. Apuntar los fallos que salgan (`PRUEBAS.md`).
- Lo que dejó Miguel por decidir en la regla de la Liga: precio normal, cuentan todos los curativos del rival y la cura es al entrar en cada sala. Se cambia fácil si se prefiere otra cosa.
- PRESS START del título, en inglés.
- La propuesta de Miguel: meter `comprobar_zonas.py` en el CI.
