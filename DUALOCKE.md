# Proyecto Dualocke: contexto completo

> **⚠ Bug del equipo clonado (27/10/2026):** parcheado en el #49 (se protegen el mote y el orden del equipo), pero sin causa confirmada. Detalles y estado en `BUG-EQUIPO-CLONADO.md`.

Este archivo resume **todo lo decidido y hecho** en el proyecto, para que cualquiera de los dos (o el Claude de cualquiera de los dos) pueda retomarlo sin haber visto las conversaciones anteriores.

> **Si eres Claude y te acaban de pedir que leas este archivo:** léelo entero antes de tocar nada. Al final hay una sección con instrucciones de trabajo para ti. Cuando cambies algo importante del proyecto, actualiza también este archivo en el mismo commit.

Última actualización: 25/10/2026.

---

## 1. Qué es esto

Jorge y Miguel juegan **dualockes** de Pokémon: cada uno juega su propia partida randomizada con las mismas reglas de nuzlocke, y compiten (quién gana el locke, combates entre ellos en Showdown, etc.). Hasta ahora lo hacían con Pokémon Platino y el *Universal Pokémon Randomizer* (preset `PlatinoUltralocke.rnqs`).

El objetivo de este repo es hacer **una ROM hack propia** para esos dualockes, con:

- Pokémon de las **9 generaciones**.
- **Megaevoluciones** (incluidas las nuevas de Leyendas Z-A).
- **Ataques de todas las generaciones** con los datos de la última versión.
- Las **reglas del locke integradas en el juego** siempre que sea posible.
- Un **randomizer propio** en el que cada jugador tiene una partida completamente distinta.
- **En español** (traducción pendiente; de momento el juego está en inglés).

## 2. Por qué esta base

Se valoraron varias opciones (están razonadas en un documento aparte que tiene Jorge):

| Opción | Resultado |
| --- | --- |
| **Esmeralda con pokeemerald-expansion** | **Elegida.** Trae de serie las 9 generaciones, megas y mecánicas/datos de ataques actualizados. Es código C, compila desde cero, está muy mantenida y documentada. |
| Heart & Soul en castellano (hack de Johto sobre este mismo motor) | Descartada: ya está en español y tiene modo nuzlocke, pero de serie solo trae gens 1-3, no tiene megas y los movesets son de Gen 3/7. |
| HeartGold con la decompilación "al 100%" | Descartada: fork no oficial muy reciente, sin nuevas generaciones ni megas, pocas herramientas. |
| HeartGold con hg-engine | Descartada: en inglés, se inyecta sobre la ROM, necesita ampliar el save y tiene bugs conocidos. |
| Perla / Platino / Blanco-Negro | Descartadas: no hay ninguna base con 9 gens y megas comparable. |

Este repo es un **fork** de [rh-hideout/pokeemerald-expansion](https://github.com/rh-hideout/pokeemerald-expansion) (rama `master`), que a su vez se basa en la decompilación de Esmeralda de pret. Versión de la expansion en el momento del fork: posterior a la 1.17.1.

**Importante:** el Universal Pokémon Randomizer **no funciona** con esta ROM (solo entiende las ROMs originales). Por eso el randomizer se hace a mano (ver sección 7).

## 3. Cómo compilar y jugar

### Forma rápida (Windows): un script lo hace todo

```powershell
powershell -ExecutionPolicy Bypass -File tools\dualocke\instalar_windows.ps1
```

- **Primera vez:** si no tienes WSL, ábrelo en **PowerShell como administrador**. Instala WSL con Ubuntu y te pide reiniciar. Después abre "Ubuntu" una vez desde el menú Inicio para crear tu usuario y vuelve a lanzar el script, ya sin administrador.
- **Qué hace luego:** instala el compilador (te pide la contraseña de Ubuntu), clona el repo en `~/romhack`, compila y copia la ROM al **escritorio como `Dualocke.gba`**.
- **Para actualizar el juego** cuando se suban cambios, se vuelve a lanzar el mismo script. Si mGBA guarda la partida al lado (`Dualocke.sav`), se conserva.
- Con `-Rama nombre-de-rama` compila otra rama, por ejemplo para probar un PR antes de fusionarlo.
- El juego sale **randomizado** con tu semilla (la misma cada vez que actualizas) y compilado con **`make release`**, así que no tiene los menús de depuración (R + START en el mapa, SELECT en combate). Con **`-NuevaPartida`** genera otra semilla para empezar un locke nuevo (pide confirmación, porque la partida guardada deja de cuadrar). Con **`-SinRandom`** compila el juego sin randomizar y con los menús de depuración, para probar, y lo copia aparte como `Dualocke-sin-random.gba`.
- Si no tienes el repo en Windows, descarga solo el script desde GitHub (`tools/dualocke/instalar_windows.ps1`).

### Probar la ROM en un emulador sin jugar (Jorge, 19/11/2026)

`tools/dualocke/emulador/` lleva un emulador sin pantalla (mGBA como librería) para comprobar cosas del juego desde un script, sin jugar: entrar en un mapa, andar, surfear, combatir, capturar y hacer fotos de la pantalla.

- **ROM de pruebas:** `make DUALOCKE_PRUEBA=1 [SEED=...]` crea `pokeemerald-prueba.gba` (con su `.elf` y su `.map`), en su propia carpeta de compilación. Nunca es la que se juega: lo de las pruebas solo se compila con esa opción (`#ifdef DUALOCKE_PRUEBA`) y la ROM normal y la de `make release` salen igual que antes.
  - Al darle a "Nueva partida", si el emulador ha escrito en `gDualockePrueba` (`src/dualocke_prueba.c`), la partida empieza directamente en el mapa y la casilla que se le diga: sin la charla de Abedul ni el camión, con las 8 medallas, las gafas, las bicis, la supercaña, 20 Master Ball y un Lapras con SURF, CASCADA, BUCEO y FUERZA.
  - Modo foto: cuevas con luz, sin lluvia ni tormenta de arena, y los entrenadores no te ven.
- **Emulador:** `emulador.py` (lo usa Python; necesita `apt install libmgba-dev`, y compila solo `gbarun.c` la primera vez). Por ejemplo:
  ```python
  from emulador import Emulador
  with Emulador() as emu:
      emu.empezar("MAP_ROUTE111", 33, 81)
      emu.andar("arriba", 2)
      print(emu.mapa(), emu.posicion())
      emu.foto("/tmp/foto.png")
  ```
  También sabe si estás en combate, huir, capturar con Master Ball (con el mote obligatorio) y guardar o cargar el estado.
- Con él se comprobó (19/11/2026) que la puerta del DESIERTO PROFUNDO funciona, y que surfear, combatir y capturar en la PLAYA VOLCÁNICA no rompe al personaje.

### Bot que se pasa el juego (Jorge con Claude, 22/11/2026)

`tools/dualocke/bot/` juega el Dualocke con la **ROM normal** (`make release`), sin atajos: planea caminos por todo Hoenn, combate, captura, cura, resuelve los puzles de los gimnasios, bucea, usa la Bici Carrera… Con él Claude se pasó el juego entero (semilla 777000111) y apuntó los fallos en `registro/2026-11-22-jorge-bot-partida-completa.md`. Cómo prepararlo y usarlo: `tools/dualocke/bot/README.md`. Sirve para comprobar que la historia se puede terminar, **no** para medir la dificultad (combate peor que una persona, no usa curas y, cuando se atasca, recarga o usa una ayuda declarada que queda apuntada).

### Entorno (Windows), paso a paso

1. WSL con Ubuntu: en PowerShell como administrador, `wsl --install`, y reiniciar si lo pide.
2. Dependencias, dentro de Ubuntu:
   ```bash
   sudo apt update && sudo apt upgrade -y
   sudo apt install -y build-essential binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi git libpng-dev python3
   ```
3. El proyecto se guarda **dentro de Linux** (`~/romhack/...`), no en `C:`. Con WSL2, compilar desde `/mnt/c` es muchísimo más lento.

### Descargar y compilar

```bash
mkdir -p ~/romhack && cd ~/romhack
git clone https://github.com/Jorgemori06/pokeemerald-expansion
cd pokeemerald-expansion
make -j$(nproc)
```

Sale `pokeemerald.gba` en la carpeta del proyecto. `explorer.exe .` abre esa carpeta en Windows.

### Actualizar a la última versión del repo

```bash
cd ~/romhack/pokeemerald-expansion
git pull
make -j$(nproc)
```

### Partida randomizada (semilla)

- **`make`** compila una partida **randomizada**. La primera vez se inventa una semilla al azar y la guarda en `dualocke_semilla.txt`, en la carpeta del repo (no se sube a GitHub). Las siguientes veces la reutiliza: **actualizar el juego (`git pull` + `make`) no cambia los Pokémon de tu partida en curso**.
- **`make nueva-partida`**: otra semilla al azar, así que la partida es nueva. La ROM nueva sustituye a la anterior; si quieres conservar la vieja, renombra antes la `.gba` y la `.sav`.
- `make SEED=loquesea`: una semilla concreta, para regenerar una partida (está en `dualocke_semilla.txt`).
- `make SIN_RANDOM=1`: el juego sin randomizar, para probar cosas. `make check` (los tests) nunca randomiza.
- Lo que ha salido (el "solucionario") queda en `build/dualocke/solucionario.json`. **No lo abras** si no quieres destriparte la partida.

### Emulador

**mGBA** (mgba.io). Es preciso y permite conectar dos instancias por cable link. No usar MyBoy. melonDS, DeSmuME y Citra no sirven aquí (son de DS/3DS).

### Notas

- Si `git clone` en Windows (fuera de WSL) da `Filename too long`, ejecutar `git config core.longpaths true` y `git checkout -- .` dentro del repo.
- Para compilar **no hace falta ninguna ROM**: el código genera el juego entero.
- **Nunca** subir ROMs (`.gba`) ni saves al repo. Ya están en el `.gitignore`.
- El repo es **público** (los forks de GitHub no pueden ser privados). Solo contiene código, no la ROM.
- Si algún día se comparte con más gente, se reparte como **parche** (`.bps`/`.ups`), y hay que mantener los créditos: pokeemerald-expansion (RHH) → pokeemerald (pret).

## 4. Reglas del locke (originales)

Estas son las reglas que usaban en Platino. La idea es mantenerlas lo más parecidas posible.

- **Vidas:** 20 vidas (+ la vida "0"). Al debilitarse un Pokémon se guarda en una caja del PC exclusiva para muertos, no puede volver a usarse y se resta una vida.
- **Level cap:** no se pueden superar ciertos niveles hasta completar cada hito (ver sección 5 para los de Hoenn).
- **Capture Clause:** solo se puede capturar el primer Pokémon de cada ruta. Huir o debilitarlo significa no poder capturar más en esa ruta. Excepciones:
  - No se pueden capturar repetidos de una misma línea evolutiva.
  - No se pueden capturar singulares/legendarios.
  - Los **shiny** se pueden capturar siempre.
  - **Detalle decidido el 23/10/2026 (Jorge y Miguel) para implementarlo en el juego:**
    - Cada "ruta" es **cada zona con nombre propio** (Ruta 104, Bosque Petalia, Cueva Granito…). Pescar o hacer surf en la misma zona no da otra captura.
    - Si el primer Pokémon de una zona es de una **línea evolutiva que ya tienes** o es **legendario/singular**, **no cuenta**: se escapa y sigues buscando hasta que salga uno válido.
    - "Ya tener una línea" significa tener un Pokémon **vivo** de esa línea (equipo o PC, sin contar la caja de muertos ni la de prohibidos). Si el que tenías muere, esa línea vuelve a estar disponible.
    - Los Pokémon de **regalo, evento o fósil** (inicial, Beldum, fósiles, los que dan los NPCs…) **no gastan la captura de la zona**.
    - Si un regalo/evento/fósil es **repetido o legendario**, va a una **caja de prohibidos** del PC. Los repetidos se quedan ahí **hasta que muere el de su línea que ya tenías**, y entonces se pueden usar. Los legendarios se quedan bloqueados.
    - Los **shiny** se pueden capturar y usar siempre, aunque sean repetidos o legendarios, y **no gastan** la captura de la zona (confirmado por Jorge).
    - **Líneas con ramas** (decidido por Jorge el 24/10/2026): cada evolución final distinta es una **rama** (Gardevoir y Gallade, cada eeveelución, Beautifly y Dustox…). Se puede tener un Pokémon de cada rama: si tienes Gardevoir, un Ralts, Kirlia o Gallade sí cuentan, pero el nuevo **no puede evolucionar a la rama que ya tienes**. Un Pokémon que **todavía no ha elegido rama** (Ralts, Kirlia, Eevee…) ocupa **toda la línea** hasta que evolucione a una rama concreta. Las **formas regionales** cuentan como su especie (si tienes Pikachu, un Raichu de Alola es repetido). Si el que tenías muere, su rama se libera, también para evolucionar.
    - **Antes de que te den las primeras Poké Balls** (en el laboratorio de Abedul, al recibir la Pokédex) no cuenta ningún encuentro. Después sí, aunque no tengas Balls porque se te olvidó comprarlas (decidido por Jorge el 24/10/2026).
    - **Arreglo (26/10/2026, encontrado jugando):** como las Poké Balls se pueden comprar en PUEBLO ESCASO desde el principio, las reglas (captura por zona y caja de prohibidos) también empiezan en cuanto llevas una Poké Ball en la mochila. Se guarda en `FLAG_DUALOCKE_TIENE_BALLS` (0x2B5) para que no se desactive al gastar la última. Código: `Dualocke_ReglasEmpezadas` (`src/dualocke.c`).
  - **Cómo funciona en el juego (hecho, Jorge, 24-25/10/2026):**
    - Solo cuentan los **encuentros aleatorios**: hierba, cuevas, surf, pesca, Golpe Roca, Dulce Aroma, Safari y los errantes. Los combates de evento y los estáticos (Kecleon, Electrode, legendarios…) no gastan la zona y se pueden capturar.
    - Al **empezar** el combate con el primer salvaje válido, la zona queda gastada, pase lo que pase (lo capturas, huyes, lo debilitas o pierdes).
    - Al empezar el combate sale un aviso: "¡Es el primer Pokémon de esta zona!…", "¡Es variocolor!…", o, si no cuenta, por qué (repetido o legendario).
    - Si no se puede capturar, las Balls (y la Safari Ball) dan un mensaje y no se gastan. El combate es normal: puedes huir o debilitarlo.
    - **Ramas:** las evoluciones finales a las que puede llegar cada especie, contando las formas regionales y las megas como su especie base. Un Pokémon con una sola rama posible (Gardevoir, Silcoon, Pikachu…) ocupa esa rama; uno con varias (Ralts, Kirlia, Eevee…) ocupa toda la línea. Un salvaje es repetido si tienes vivo uno de su línea sin rama elegida, o si ya tienes todas las ramas a las que puede llegar.
    - **Evolución bloqueada:** un Pokémon del equipo no evoluciona a una especie cuyas ramas ya tienes todas con otros Pokémon vivos. Si sube de nivel, simplemente no evoluciona; con una piedra, sale "no tendrá efecto" y no se gasta. Es `Dualocke_IsEvolutionBlocked` en `src/dualocke.c`, llamado desde `GetEvolutionTargetSpecies` (`src/pokemon.c`).
    - **Capturar con el equipo lleno (arreglo, Jorge, 31/10/2026, encontrado jugando):** el juego deja meter al nuevo en el equipo mandando otro a la caja. La expansion no dejaba mandar a ninguno que supiera un movimiento de MO, aunque otro del equipo también lo supiera. Ahora solo se bloquea si es **el único del equipo** que sabe alguna de sus MO (los huevos no cuentan). Es `Dualocke_KnowsUniqueHM` en `src/dualocke.c`, llamado desde `DoesSelectedMonKnowHM` (`src/party_menu.c`).
    - Las zonas son las secciones del mapa regional: cada ruta, ciudad, cueva… La Zona Safari es una sola zona. Las zonas submarinas (Buceo) tienen nombre propio y son zonas aparte.
    - **Caja de prohibidos** (la caja 13, "VETADOS"; la 14 es la de muertos): los Pokémon que no pasan por la regla de la zona y son **repetidos o legendarios** van ahí en vez de al equipo o al PC. Son:
      - regalos, eventos y fósiles;
      - estáticos capturados (Kecleon, Electrode, legendarios…);
      - **huevos**, al eclosionar (decidido por Jorge el 25/10/2026: se aplica la regla de los eventos; criar no se prohíbe, se controla por honor);
      - **intercambios con NPCs** (decidido por Jorge el 25/10/2026: cuentan como regalo).
    - En la caja de prohibidos solo se puede ver el resumen y no se puede dejar nada. Un **repetido se desbloquea solo** cuando deja de serlo (muere el de su línea que tenías) y entonces se puede sacar o mover. Los **legendarios** se quedan bloqueados. Los **variocolor** nunca van ahí.
    - Los de la caja de prohibidos no cuentan como "línea que ya tienes".
    - Al recibirlo sale el mensaje de siempre de "se ha enviado a la caja VETADOS".
    - Nunca deja el equipo vacío: si el huevo o el intercambio es tu único Pokémon, se queda en el equipo.
- **Nick Clause:** todos los Pokémon llevan mote.
- **Items Clause:**
  - No se pueden comprar objetos curativos ni Objetos X en las tiendas.
  - Se pueden usar curativos en combate si se han encontrado durante la aventura.
  - No se pueden usar Objetos X en combate.
  - Solo se puede comprar una unidad de cada objeto por tienda, salvo Balls, Repelentes y Bayas (y los Caramelos Raros, ver sección 6).
  - No se pueden farmear objetos.
- **Liga (contada por Jorge el 22/11/2026):** al llegar a la Liga se pueden comprar todos los RESTAURAR TODO que se quiera. En combate solo se pueden usar **si el rival ya ha usado uno**, y como mucho **tantos como haya usado él** (si usa 2, tú puedes usar 2). **Entre combates se cura el equipo entero.** **Desde el 22/11/2026 está dentro del juego** (Miguel; ver "Regla de la Liga dentro del juego", en la sección 6).
- **Win Clause:**
  - Gana quien venza al Campeón sin perder todas las vidas y sin perder ningún combate (6 Pokémon debilitados).
  - Empate (los dos ganan o los dos pierden): decide el marcador de los combates entre ellos.
  - **Combates:** 3 tandas al mejor de 3 a lo largo de la aventura, en **Showdown**, con equipos legales (solo Pokémon y objetos conseguidos en la partida), idénticos a los de la partida (habilidad, movimientos, naturaleza…) pero con **EVs e IVs a 0**.
  - El ganador de cada tanda tiene **2 capturas extra** en la siguiente ruta no visitada (+ un objeto evolutivo si no es obtenible antes del postgame). El perdedor, **1 captura extra** con las mismas condiciones.

### Qué regla se hace dentro del juego y cuál no

| Regla | Implementación prevista | Esfuerzo | Estado |
| --- | --- | --- | --- |
| Level cap | Sistema del motor, por medallas | Poco | **Hecho** |
| Caramelos Raros no pasan el cap | Opción del motor | Poco | **Hecho** |
| Mote obligatorio | Forzar la pantalla de mote al capturar, al recibir regalos y al eclosionar huevos | Poco | **Hecho** |
| No comprar curativos ni Objetos X | Quitarlos de las tiendas | Poco | **Hecho** |
| No usar Objetos X en combate | Bloquearlos en combate | Poco | **Hecho** |
| Una compra por objeto (salvo Balls, Repelentes, Bayas, Caramelos) | Limitar compras en tiendas | Medio | **Hecho** (Miguel, 24/10/2026) |
| 20 vidas + caja de muertos | Contador de vidas en el menú de pausa y caja bloqueada | Medio | **Hecho** (aviso al morir incluido) |
| Primera captura por ruta + dupes + sin legendarios + shiny libre + caja de prohibidos | El juego bloquea lanzar Balls cuando no se puede capturar; los regalos repetidos/legendarios van a la caja de prohibidos | Medio | **Hecho** |
| Victoria, combates en Showdown, capturas extra | Fuera del juego, por honor | — | — |
| No farmear | Por honor | — | — |
| Regla de la Liga (RESTAURAR TODO solo si el rival cura, curar entre combates) | Tienda en la Liga, contador en combate y cura al pasar de sala | Medio | **Hecho** (Miguel, 22/11/2026) |

## 5. Curva de niveles y level caps

Decisión: **el as del campeón (Plubio) a nivel 100**, y desde ahí la curva baja de forma progresiva y lógica según cuánto juego hay entre hito e hito. No se usa el "+15%" del randomizer de Platino porque se queda muy corto: el as de Plubio en Esmeralda es nivel 58, que con +15% sería 67.

Regla general: **el as de cada jefe va exactamente al nivel del cap**, el resto de su equipo algo por debajo, y entrenadores y salvajes de cada zona escalados para ese tramo.

| Cap | Hito (se sube al conseguir la medalla) | Qué hay entre el hito anterior y este | Salto |
| --- | --- | --- | --- |
| 16 | Gym 1: Petra (Ciudad Férrica) | Rutas 101-104, Bosque Petalia | — |
| 23 | Gym 2: Marcial (Pueblo Azuliza) | Cueva Granito | +7 |
| 32 | Gym 3: Erico (Ciudad Malvalona) | Ciudad Portual, Ruta 110, rival | +9 |
| 43 | Gym 4: Candela (Pueblo Lavacalda) | Rutas 111-114, Cascada Meteoro, Monte Cenizo (Magno) | +11 |
| 50 | Gym 5: Norman (Ciudad Petalia) | Casi nada | +7 |
| 62 | Gym 6: Alana (Ciudad Arborada) | Rutas 118-120, Instituto Meteorológico, **combate con Máximo y el aro** | +12 |
| 73 | Gym 7: Vito y Leti (Ciudad Algaria) | Ciudad Calagua, Monte Pírico, guarida Magma/Aqua | +11 |
| 84 | Gym 8: Galano (Ciudad Arrecípolis) | Centro Espacial, Cueva Abisal | +11 |
| 100 | Liga | Calle Victoria (Blasco ~90), Alto Mando con ases entre 92 y 97, **Plubio 100** | +16 |

- El cap es **duro**: al llegar al cap, el Pokémon no gana experiencia.
- En los tests de la expansion (`make check`) el cap no se aplica (`TESTING` en `src/caps.c`), porque allí no hay medallas y el cap de 16 rompería los tests de experiencia.
- El último salto es grande, pero no obliga a farmear porque las tiendas venderán **Caramelos Raros a 1 ₽**, y estos **no funcionan por encima del cap**.
- **Reescalado hecho** (Miguel, 23/10/2026) con `tools/dualocke/reescalar_niveles.py`, que lee los niveles originales de la expansion y se puede volver a lanzar tras tocar la tabla. Cómo funciona:
  - Cada mapa de Hoenn está asignado a su **tramo** (entre una medalla y la siguiente, en orden de historia).
  - **Entrenadores normales:** suben del cap anterior − 3 al cap del tramo − 3, según lo fuertes que eran en el original dentro de su tramo.
  - **Líderes de gimnasio:** el equipo entero al cap. **Salvo PETRA, MARCIAL y ERICO** (Miguel, 11/11/2026; ver sección 6): el as al cap y el resto 1-2 niveles por debajo.
  - **Alto Mando:** Sidney 92, Fátima 94, Nívea 95 y Dracón 97, el equipo entero a ese nivel. **Plubio** 100 y **Blasco** en Calle Victoria 90.
  - **Jefes a mitad de tramo** (rival, Magno, Aquiles, Blasco en Malvalona): el equipo entero 3 niveles por encima de los entrenadores de ese punto, sin pasar del cap.
  - **Salvajes:** los entrenadores de su zona − 3, con un margen de ±2. Las tres cañas dan el mismo nivel.
  - **Ningún salvaje por encima del level cap (Jorge, 12/11/2026):** red de seguridad en el juego, por si alguna zona se alcanza antes de lo que dicen sus entrenadores. Si un salvaje sale por encima del cap, se queda entre el cap y 2 niveles menos, y vuelve a la etapa que le toca para ese nivel con las mismas reglas que el randomizer (por nivel; si no, 30 la primera evolución y 40 la segunda). Vale para todos los salvajes: hierba, agua, pesca, golpe roca, DEXNAV, brotes masivos y los de los scripts (estáticos). Lo hace `Dualocke_CapWildMon` (`src/dualocke.c`), llamado desde `CreateWildMon` (`src/wild_encounter.c`) y `CreateScriptedWildMon` (`src/script_pokemon_util.c`). Los regalos y los intercambios no pasan por ahí.
  - **Pesca que se alcanza a pie (arreglo, Jorge, 11/11/2026, encontrado jugando):** Jorge pescó un Audino de nivel 44 junto a AZULIZA, porque la orilla este de la isla es de la RUTA 107, cuyos entrenadores van con SURF. Ahora la pesca de la RUTA 107 y del estanque de CIUDAD PETALIA va al nivel de la de AZULIZA (15-19). La de la orilla oeste de la RUTA 118, al salir de MALVALONA, va al de la RUTA 110 (17-21). Antes estaban a 42-48. Lo hace la tabla `PESCA_COMO` de `reescalar_niveles.py`.
  - **Entrenadores que se alcanzan antes que su mapa (arreglo, Jorge, 17/11/2026, encontrado jugando):** Jorge, con el cap a 32, se metió al salir de MALVALONA en un doble contra ROSA y DEANDRE a nivel 47. La orilla oeste de la RUTA 118 se pisa en el tramo 3, pero la ruta cuenta como tramo 6 porque el resto se hace con SURF.
    - **`tools/dualocke/alcance.py`** recorre el mundo casilla a casilla, como el jugador, con lo que se puede hacer en cada tramo: MO y medallas, bici, barco del SR. BRINEY, teleférico, saltos, corrientes, puertas y conexiones. Dice desde qué tramo te ve o le puedes hablar a cada entrenador, y avisa si su nivel pasa del de ese tramo. Lo que no son fallos va apuntado con su motivo: las guaridas y el gimnasio de PETALIA se abren por la historia, y LIRIA, ALGARIA y el mar del sur solo se alcanzan antes saltándose la historia con SURF. Va en el CI (`--comprobar`).
    - Ha encontrado 8: ROSA, DEANDRE, WADE y DALTON en la RUTA 118 (estaban a 47) y TYRON, CELINA, BIANCA y HAYDEN en la parte sur de la RUTA 111, entre MALVALONA y las rocas de GOLPE ROCA (estaban a 30-31). Ahora van con el rango del tramo 3 (21-24) y con su IA (`TRAMO_DE_ENTRENADOR` en `reescalar_niveles.py`, que también lee `ia_entrenadores.py`). Se aplica al final: los salvajes, los estáticos, las bandas de los tramos y los niveles de las revanchas no cambian.
    - **Red de seguridad en el juego:** ningún POKéMON de un entrenador rival sale por encima del level cap. Si pasa, sale al cap justo y con la etapa que le toca para ese nivel, con las mismas reglas que los salvajes. Lo hace `Dualocke_CapTrainerMon` (`src/dualocke.c`), llamado desde `CreateNPCTrainerPartyFromTrainer` (`src/battle_setup.c`). No toca al compañero de los combates dobles ni al Frente Batalla. Con la curva de la sección 5 no salta nunca: los jefes van como mucho al cap, y las revanchas encajan con el cap de las medallas que las abren.
  - **Ruta 103 (arreglo, Jorge, 01/11/2026, encontrado jugando):** sus 8 entrenadores normales están en la parte este, a la que solo se llega desde la Ruta 110, pero contaban como tramo 1 y subían a los salvajes de la hierba a **9-11** al principio del juego (inicial a 5, rival a 7). Ahora esos entrenadores van con el rango del **tramo 3** (20-22) y no cuentan para los salvajes de la ruta, que quedan a **2-3** como los de las rutas 101, 102 y 104. Surf y pesca no cambian (8-12). Es la tabla `TRAMO_ENTRENADORES_DE_MAPA` de `reescalar_niveles.py`. Las bandas de cada tramo se siguen calculando como antes, así que no se mueve ningún otro entrenador; solo cambian un poco las revanchas de Miguel y de Amy y Liv, que van en proporción a su primer combate.
- **Revanchas, postgame y Casa Trampa (hecho, Miguel, 23/10/2026):**
  - **Revanchas (Match Call):** se activan con 5 medallas. Cada escalón sube respecto al primer combate en la misma proporción que en el original, pero repartido dentro de unos límites: \_2 entre 47 y 59, \_3 entre 59 y 70, \_4 entre 70 y 81 y \_5 entre 81 y 97. Así nunca te retan muy por encima del cap que puedes tener. Ejemplo: Rosa 47 → 59 → 70 → 81 → 97.
  - **Revanchas de los líderes y de Blasco** (postgame): todo a **100**.
  - **Postgame** (S.S. Marea, Cueva de Máximo en la Cascada Meteoro, Túnel del Desierto, Cueva Ancestral, Cueva Alterada, cuevas Terra y Marina): entrenadores a **100** y salvajes a **97**.
  - **Casa Trampa:** la prueba 1 al tramo 3, y cada prueba N al tramo de la medalla N+1 que la abre (la 8, a la Liga). No cuenta para la banda de su tramo, así que no mueve los niveles de la historia principal.
  - **No se tocan:** el Frente Batalla y la Cima Entrenador, que tienen su propio sistema de niveles.
- **Estáticos y regalos (hecho, Miguel, 24/10/2026):**
  - **Estáticos normales** (Kecleon de las rutas 119-120, Voltorb de Nuevo Malvalona, Electrode de la Guarida Aqua): como jefes de zona, es decir, entrenadores de su mapa + 3, sin pasar del cap. Quedan a 58, 56 y 65.
  - **Legendarios:** al cap de su tramo. Los Regis a 84 (hace falta Buceo, tramo 8); Rayquaza, Groudon y Kyogre a 100 (postgame). Sudowoodo del Frente Batalla, también a 100. Los **errantes Latios/Latias** (salen después de la Liga), también a 100 (Miguel, 26/10/2026; `DUALOCKE_NIVEL_ERRANTE` en `src/roamer.c`).
  - **Regalos** (Castform, fósiles, Beldum, iniciales de Johto, huevo de Wynaut): se quedan con su nivel original, para entrenarlos (con Caramelos Raros a 1 ₽).
  - Lo hace `reescalar_niveles.py` (tabla `ESTATICOS`).
  - **Captura de estáticos (decidido, falta implementarlo encima del PR #17):** de los estáticos normales solo se puede capturar el primero de cada tipo (un Kecleon, un Voltorb, un Electrode), sin gastar la zona.
- **Evoluciones de los entrenadores normales (hecho):** `tools/dualocke/evolucionar_entrenadores.py` evoluciona sus Pokémon según el nivel. Las evoluciones por nivel van a su nivel normal; las que no son por nivel (piedra, amistad…) van a 30 la primera y a 40 la segunda. Los scripts se lanzan en orden: `reescalar_niveles.py`, `zonas_nuevas.py` (los salvajes de las zonas nuevas, que `reescalar_niveles.py` borraría), `equipos_jefes.py` y `evolucionar_entrenadores.py`. Después va `ia_entrenadores.py` (la IA de los entrenadores normales, sección 7).
- El randomizer **no debe tocar los niveles ni el tamaño de los equipos**: solo especies, movimientos, habilidades y objetos. Al cambiar especies, debe mantener la regla de evolucionar según el nivel.

## 6. Megas, tiendas y evoluciones

### Megaevoluciones

- Las megas están activadas en el motor, incluidas las de Z-A (`P_MEGA_EVOLUTIONS`, `P_GEN_9_MEGA_EVOLUTIONS`).
- Para megaevolucionar, el jugador necesita el objeto **Mega-Aro** (`ITEM_MEGA_RING`) en la mochila (lo comprueba `src/battle_util.c`).
- **Cómo se consigue el aro (decidido el 23/10/2026):** combate con **Máximo en la Ruta 120**, justo antes del gym 6 (Alana). Al ganar, te da el aro. Encaja con la historia (en ROZA Máximo está metido en lo de las megas) y llega en un punto equilibrado: equipo ya formado, cap 62, toda la segunda mitad del juego para usarlas.
- **Equipo de Máximo (decidido por Miguel, 23/10/2026):** entrenador `TRAINER_STEVEN_ROUTE_120`, todo a **nivel 62** (el cap del tramo). Lleva Aggron, Aegislash, Excadrill, Mawile, Empoleon y, como as, **Metagross con Metagrossita**. El equipo es **fijo**: el randomizer no lo toca. Ya existe en `src/data/trainers.party`; Jorge solo tiene que montar el evento en `data/maps/Route120/` con `trainerbattle_single TRAINER_STEVEN_ROUTE_120, …` y dar el Mega-Aro al ganar.
- **Evento de Máximo (hecho, Jorge, 24/10/2026):** al hablar con Máximo en el puente de la Ruta 120 te reta con `TRAINER_STEVEN_ROUTE_120`. Si ganas, te da el **Mega-Aro** y te cuenta que las megapiedras están escondidas por Hoenn; después sigue el evento original (usa el Detector Devon, combate con el Kecleon y te da el Detector). Si pierdes, *whiteout* y te sigue esperando, pero **perder un combate es perder el locke** (como cualquier otro), y este es obligatorio: 6 Pokémon a nivel 62 con Mega Metagross. Si ya le habías ganado pero sigue ahí (por ejemplo, perdiste contra el Kecleon), no vuelve a combatir: te da el aro si no lo tienes y sigue con el Kecleon. Como el Detector hace falta para llegar al gimnasio de Arborada, el combate es obligatorio antes de Alana. Script en `data/maps/Route120/scripts.inc` (`Route120_EventScript_Steven`).
- **Desde que el jugador tiene el aro, todos los jefes llevan un Pokémon con mega** (y la usan). Lista de "jefes" (decidida el 23/10/2026): líderes de gimnasio, Alto Mando, Plubio, rival (Bruno/Aura), Blasco y los líderes Magma/Aqua (Magno, Aquiles).
- **Equipos de los jefes (hecho, Miguel, 23/10/2026)** con `tools/dualocke/equipos_jefes.py` (se lanza después de `reescalar_niveles.py`):
  - **+2 Pokémon** a líderes, Alto Mando y Plubio; **+1** al rival, Blasco, Magno, Aquiles y los admins (Tatiano, Silvina, Matías). Máximo 6.
  - **Primeros gimnasios más suaves (Miguel, 11/11/2026).** Jorge y Miguel vieron jugando que PETRA y MARCIAL eran demasiado difíciles: 5 Pokémon al cap, todos con Mineral Evolutivo, IVs 24, IA lista y 2 curas. En el original eran 3 Pokémon a nivel 12-15. Ahora:

    | Líder | Pokémon | Niveles (el último es el as) | Curas |
    | --- | --- | --- | --- |
    | PETRA | 4 (sin Onix) | 14, 15, 15, 16 | 1 Poción |
    | MARCIAL | 4 (sin Mankey) | 21, 22, 22, 23 | 1 Superpoción |
    | ERICO | 5 (sin Raichu) | 30, 31, 31, 31, 32 | 1 Superpoción |

    - Las especies son las del hueco base: el randomizer las cambia igualmente, y el as sigue siendo de su tipo.
    - En `equipos_jefes.py` son las tablas `EQUIPOS`, `NIVELES_EQUIPO` y `CURAS`.
    - Los objetos de sus Pokémon, en la sección 7 ("objetos de los jefes").
  - Los huecos nuevos son Pokémon **del tipo del jefe**; los originales **evolucionan** según su nivel. El randomizer los cambiará igualmente.
  - **Megas canónicas** desde el aro (el as, último del equipo, lleva su megapiedra): Alana Altaria, Vito y Leti Metagross, Galano Starmie, Sidney Absol, Fátima Banette, Nívea Glalie, Dracón Salamence, Plubio Gyarados, Blasco Gardevoir, Magno Camerupt, Aquiles Sharpedo y el rival su inicial (desde Ciudad Calagua).
  - **Objetos:** solo se añade la megapiedra; los que ya llevaban (Baya Zidra…) se quedan, y el resto lo pondrá el randomizer.
  - Los rivales y la IA megaevolucionan sin aro, con solo llevar la piedra.
- Las **megapiedras** (decidido por Miguel el 23/10/2026) **se encuentran explorando el mapa**: no se venden.
  - Hay **107**: las 81 de Pokémon no legendarios de la expansion y 26 de las formas Gigamax (abajo), cada una en un sitio que encaja con ella. Por ejemplo: Cameruptita en Jagged Pass, Garchompita en el desierto, Sharpedonita bajo el agua en la Ruta 124, Glalitita en Shoal Cave…
  - Unas van en **bola de objeto** y otras **ocultas** (para el Buscaobjetos).
  - Las coloca `tools/dualocke/colocar_objetos.py`, que tiene la tabla completa. Cada una tiene su flag `FLAG_ITEM_MEGA_...`, del **0x264 al 0x2B4** de `include/constants/flags.h`. El script busca solo una casilla transitable cerca de algo que ya se pueda alcanzar, y en la que la Ball no tape el paso (ver "Que ninguna Poké Ball tape el paso", sección 6). `colocar_objetos.py --mover` mueve a una casilla cercana las que ya estén puestas y tapen algo (solo les cambia la x y la y, para no cambiar el número de los demás objetos del mapa).
  - **Repartidas** (Jorge y Miguel, 22/11/2026; se vio con el mapa interactivo): el script cogía siempre la primera ancla con sitio, así que los objetos de una ruta acababan todos juntos (11 en un cuadrado de 7×7 en la RUTA 119, 10 alrededor de WENDY en la RUTA 123). `colocar_objetos.py --repartir` vuelve a colocar las megapiedras, los competitivos y los Ticket-Recuerdo de los mapas con 5 o más objetos en un 7×7, cada uno en la casilla buena más lejos de los demás objetos del mapa. Solo va a casillas a las que se llega **en el mismo tramo** que a la de antes (según `alcance.py`), así que ningún objeto se adelanta ni se retrasa. Y **siguen en su contexto** (Jorge): se respeta la pista de su tabla (las del desierto de la RUTA 111 se quedan junto a lo del desierto) y cada objeto va al **mismo tipo de suelo** que tenía (arena, hierba alta, ceniza, cueva, agua o suelo normal); se comprobó en los 70. Se movieron 70 objetos de 10 mapas: RUTAS 110, 111, 113, 117, 119, 120, 121 y 123, SENDERO ÍGNEO y NUEVA MALVALONA (el montón más grande pasa de 11 a 3). Con `--resumen` solo enseña cómo quedaría. Las partidas en curso siguen bien: solo cambian la x, la y y la altura, y lo ya cogido no vuelve a salir.
  - Las de antes del aro se pueden recoger, pero no usar hasta tenerlo.
  - **Para el randomizer:** estas ubicaciones son **fijas**. Al barajar los objetos del suelo hay que saltarse los que tienen flag `FLAG_ITEM_MEGA_...` o `FLAG_ITEM_COMP_...`.
- **Formas Gigamax como megas (Miguel, 16/11/2026; idea 9 de `IDEAS.md`).** El Dinamax no se usa, así que las formas Gigamax son megaevoluciones, cada una con su megapiedra.
  - **26 megas nuevas** (27 formas: Toxtricity tiene dos y una sola piedra). Venusaur, Charizard, Blastoise y Gengar ya tenían mega, y Urshifu y Melmetal son singulares: se quedan como estaban.
  - Usan los gráficos de la forma Gigamax. Las estadísticas suman **100 más** que la forma normal, como las megas oficiales. El diseño lo propuso Claude y **Miguel lo aprobó tal cual (16/11/2026)**:

  | Pokémon | Megapiedra | Tipo | Habilidad | PS/Ata/Def/AtE/DfE/Vel (total) | Dónde |
  | --- | --- | --- | --- | --- | --- |
  | Butterfree | Butterfrita | Bicho / Psíquico | Cromolente | 60/45/70/130/100/90 (495) | RUTA 104 (oculta) |
  | Pikachu | Pikachunita | Eléctrico | Transistor | 35/75/50/90/60/110 (420) | RUTA 110 (bola) |
  | Meowth | Meowthita | Normal / Acero | Experto | 55/75/55/40/50/115 (390) | PORTUAL (oculta) |
  | Machamp | Machampita | Lucha | Indefenso | 90/160/100/65/100/90 (605) | RUTA 112 (bola) |
  | Kingler | Kinglerita | Agua / Acero | Garra Dura | 55/160/135/60/70/95 (575) | RUTA 109 (bola) |
  | Lapras | Laprasita | Agua / Hielo | Nevada | 130/95/110/115/125/60 (635) | RUTA 128 (bola) |
  | Eevee | Eevinita | Normal | Adaptable | 65/80/70/70/75/65 (425) | RUTA 116 (bola) |
  | Snorlax | Snorlaxita | Normal / Planta | Sebo | 160/140/95/65/140/40 (640) | RUTA 121 (bola) |
  | Garbodor | Garbodorita | Veneno | Capa Tóxica | 100/125/112/60/102/75 (574) | BARCO ABANDONADO (bola) |
  | Rillaboom | Rillaboomita | Planta / Lucha | Herbogénesis | 100/155/110/60/90/115 (630) | ZONA SAFARI (bola) |
  | Cinderace | Cinderacita | Fuego | Líbero | 80/146/90/70/90/154 (630) | RUTA 113 (oculta) |
  | Inteleon | Inteleonita | Agua | Francotirador | 70/85/75/165/85/150 (630) | RUTA 122 (bola) |
  | Corviknight | Corviknightita | Volador / Acero | Coraza Reflejo | 98/127/125/53/105/87 (595) | ARBORADA (oculta) |
  | Orbeetle | Orbeetlita | Bicho / Psíquico | Psicogénesis | 70/45/120/130/140/100 (605) | RUTA 102 (bola) |
  | Drednaw | Drednawita | Agua / Roca | Mandíbula Fuerte | 90/145/115/48/88/99 (585) | RUTA 106 (bola) |
  | Coalossal | Coalossalita | Roca / Fuego | Sequía | 110/80/150/120/120/30 (610) | PASO DESNIVEL (oculta) |
  | Flapple | Flapplita | Planta / Dragón | Garra Dura | 70/140/90/95/70/120 (585) | RUTA 123 (oculta) |
  | Appletun | Appletunita | Planta / Dragón | Sebo | 120/85/110/130/110/30 (585) | RUTA 114 (bola) |
  | Sandaconda | Sandacondita | Tierra | Chorro Arena | 72/137/155/65/90/91 (610) | RUTA 111 (desierto) (oculta) |
  | Toxtricity (las dos formas) | Toxtricitita | Eléctrico / Veneno | Punk Rock | 75/98/80/154/90/105 (602) | NUEVA MALVALONA (bola) |
  | Centiskorch | Centiskorchita | Fuego / Bicho | Mandíbula Fuerte | 100/145/85/90/110/95 (625) | RUTA 112 (oculta) |
  | Hatterene | Hatterenita | Psíquico / Hada | Espejo Mágico | 67/90/115/176/133/29 (610) | MONTE PÍRICO (bola) |
  | Grimmsnarl | Grimmsnarlita | Siniestro / Hada | Bromista | 95/150/85/95/105/80 (610) | RUTA 121 (oculta) |
  | Alcremie | Alcremita | Hada | Nebulogénesis | 75/60/95/140/141/84 (595) | CALAGUA (bola) |
  | Copperajah | Copperajahita | Acero | Potencia Bruta | 122/160/99/80/99/40 (600) | RUTA 115 (bola) |
  | Duraludon | Duraludonita | Acero / Dragón | Filtro | 70/95/135/150/70/115 (635) | CALLE VICTORIA (oculta) |

  - **Con semilla, las habilidades salen al azar**, como las de todas las especies (también las megas de siempre). La de la tabla vale sin semilla.
  - **Megapiedras:** "Kinglerita", "Hace megaevolucionar a Kingler.". El icono es el dibujo de la Gengarita con otra paleta: la bola del color principal del Pokémon y la espiral de los otros dos (`graphics/items/icon_palettes/`).
  - **Dónde:** las coloca `colocar_objetos.py` (tabla `MEGAPIEDRAS_GIGAMAX`), con los flags `FLAG_ITEM_MEGA_...` del **0x4CA al 0x4E3**.
  - **Bolsillo de megapiedras:** de 100 a 130 (`BAG_MEGASTONES_COUNT`). Es lo último de `SaveBlock3` y las casillas nuevas se leen vacías de las partidas de antes.
  - **Código:** todo lo hace `tools/dualocke/megas_gigamax.py` (tabla `DISENO`). Para cambiar una mega, se cambia ahí y se vuelve a lanzar.
    - En `gSpeciesInfo` y en la tabla de cambios de forma, lo nuevo va dentro de `#if TESTING ... #else ... #endif`: en los tests de la expansion se queda la forma Gigamax de siempre, porque los tests del Dinamax la usan.
    - Las megapiedras son objetos nuevos al final de la lista (874-899): no se mueve el número de ningún objeto de las partidas guardadas.
  - **Randomizer:** los jefes que llevan as con mega desde el Mega-Aro pueden sacar una de estas, porque el randomizer lee las megas de la tabla de cambios de forma. En las semillas en curso solo cambia el as de esos jefes (de ALANA en adelante); lo demás sale igual.
- **Objetos competitivos de generaciones nuevas** (decidido por Miguel el 23/10/2026): existían en el motor, pero no se podían conseguir. Ahora hay **55 repartidos por el mapa**, como las megapiedras: Mineral Evolutivo, Banda Focus, Casco Dentado, Botas Gruesas, Pañuelo Elegido, Chaleco Asalto, Gafas Elegidas, Vidasfera, rocas de clima, semillas de terreno, Cápsula y Parche Habilidad, 8 Mentas…
  - Están ordenados por tramo: los más fuertes (Pañuelo Elegido, Chaleco Asalto, Gafas Elegidas, Vidasfera) salen a partir del tramo 6.
  - Los coloca el mismo script. Sus flags son `FLAG_ITEM_COMP_...`, del **0x493 al 0x4C9**.
  - La tabla está en el script y en `registro/2026-10-23-miguel-objetos-competitivos.md`.
  - **Flags libres que quedan para Jorge:** 0x043-0x04F, 0x2B6-0x2BB, 0x4E4 y el resto de `FLAG_UNUSED_...` (0x2B5 es `FLAG_DUALOCKE_TIENE_BALLS`; 0x021-0x042 y 0x4E5-0x4EF son de los Ticket-Recuerdo).

### Tiendas

Cada tienda tendrá **dos dependientes**:

1. **Principal:** lo de siempre (Balls, Repelentes, etc.), **sin curativos ni Objetos X**, y con **Caramelos Raros a 1 ₽**.
2. **Secundario (hecho, Miguel, 24/10/2026):** está en las 11 tiendas de ciudad (no en Calagua, la Liga, el Frente ni la Cima), detrás del mostrador, encima del principal (casilla 1, 2). Vende **4 objetos: 1 evolutivo y 3 equipables** al azar.
   - Los evolutivos son piedras y objetos de los antiguos intercambios. Los equipables son clásicos que no se venden en ningún otro sitio: Restos, Garra Rápida, Periscopio, Polvo Brillo, Campana Concha, Cinta Focus, Campana Alivio, Metrónomo, Muda Concha y los potenciadores de tipo.
   - Son **distintos en cada partida** (la semilla sale del ID de entrenador) y **fijos durante toda la partida**.
   - Pasan por el filtro de medallas de las tiendas, así que un evolutivo no sale hasta tener su medalla.
   - **Ya no vende megapiedras:** se encuentran por el mapa.
   - Código: `src/dualocke_segundo_dependiente.c` (special `Dualocke_AbrirSegundoDependiente`) y `data/scripts/dualocke_segundo_dependiente.inc`.
   - **Pendiente:** que la regla de "una compra por objeto" (PR #19) se aplique también a este dependiente.

Regla de compra: una unidad de cada objeto por tienda, salvo Balls, Repelentes, Bayas y Caramelos Raros.

**Una compra por objeto (hecho, Miguel, 24/10/2026):**

- En cada tienda, de cada objeto que no sea Ball, Repelente, Baya, Caramelo Raro o Cuerda Huida **solo se puede comprar una unidad**. La cantidad máxima es 1, y si vuelves a elegirlo sale "You've already bought one of these here.".
- **Es por tienda:** el mismo objeto se puede comprar otra vez en otra ciudad que también lo venda.
- `tools/dualocke/compras_limitadas.py` genera la tabla de parejas (tienda, objeto) en `src/data/dualocke_compras.h` a partir de las listas de las tiendas. Ahora son 86 en 15 tiendas. **Hay que relanzarlo si se cambian las listas.**
- Lo comprado se guarda en 6 variables (`VAR_DUALOCKE_COMPRAS_0`-`5`, 0x4083-0x40A1), un bit por pareja.
- Código: `src/dualocke_compras.c` y tres enganches en `src/shop.c` (al elegir, en la cantidad y al pagar).

**Regla de la Liga dentro del juego (hecho, Miguel, 22/11/2026):** la regla que contó Jorge (sección 4).

- **Tienda de la Liga** (`EverGrandeCity_PokemonLeague_1F`): vende **RESTAURAR TODO** a su precio normal (3000 ₽) y **sin límite**: es la única excepción a "una compra por objeto" (`EXENTOS_TIENDA` en `compras_limitadas.py`; la tabla de compras no cambia, así que las partidas guardadas siguen bien). Antes de abrirla, el dependiente recuerda la regla.
- **En combate contra el Alto Mando y el Campeón** (SIXTO, FÁTIMA, NÍVEA, DRACÓN y PLUBIO): un curativo de la mochila solo se puede usar si el rival ya ha usado uno, y como mucho tantos como él. Si no, sale "Regla de la Liga: no puedes curar más veces que el rival." y no se gasta.
  - Cuentan todos los curativos: PS, estados, PP y la Flauta (el rival solo lleva RESTAURAR TODO). Los Objetos X y Revivir ya estaban prohibidos.
  - Los dos contadores empiezan a 0 en cada combate. Se suma al usarse, no al elegirlo.
- **Cura entre combates:** al entrar en cada sala del Alto Mando y en la del Campeón, el equipo se cura entero, con la música del Centro Pokémon y el mensaje "Regla de la Liga: ¡tu equipo se ha recuperado por completo!".
- Código:
  - `src/dualocke_liga.c` (contadores y qué combate es de la Liga);
  - `CannotUseItemsInBattle` en `src/item_use.c` (no deja usar el curativo);
  - `HandleAction_UseItem` en `src/battle_util.c` (cuenta los curativos);
  - `ItemUseCB_BattleScript` y `TryUseItemOnMove` en `src/party_menu.c` enseñan el motivo que deja `CannotUseItemsInBattle` en `gStringVar4`. Antes ponían siempre "No tendrá ningún efecto", así que el mensaje de la regla no salía nunca: los curativos se eligen sobre un Pokémon del equipo (lo vio Jorge con el bot, 22/11/2026).
- **Probado en el emulador** (Jorge, con el bot y la ROM release, 22/11/2026): la tienda (el aviso y dos compras seguidas de RESTAURAR TODO, cobradas enteras); la cura al entrar en la sala de SIXTO (con PS bajados a mano); que no deja curar antes que el rival (con el mensaje de la regla); que deja cuando el rival ha curado una vez y vuelve a bloquear la segunda; y que se cuentan los del rival (SIXTO usó 2 en un combate entero).
  - `Dualocke_OnBattleStart` en `src/dualocke.c` (pone los contadores a 0);
  - `data/scripts/dualocke_liga.inc` (cura y textos), llamado desde `data/scripts/elite_four.inc` y la sala del Campeón.

**Contenido del dependiente principal (hecho, Miguel, 23/10/2026):**

- **Básicos en todas las tiendas:** Poké Ball, Super Ball (desde 1 medalla), Ultra Ball (5), Repelente, Superrepelente (2), Máximo Repelente (5), Cuerda Huida y Caramelo Raro.
- **Propios de cada ciudad:**

| Tienda | Balls | Objetos evolutivos |
| --- | --- | --- |
| Pueblo Escaso, Ciudad Petalia | — | — |
| Ciudad Férrica (Devon) | Turno, Acopio | Revestimiento Metálico, Mejora, Disco Extraño |
| Ciudad Portual (puerto) | Buceo, Malla | Piedra Agua, Escama Bella, Diente Marino, Escama Marina |
| Ciudad Malvalona (electricidad) | Veloz | Piedra Trueno, Electrizador |
| Pueblo Verdegal (verde) | Nido | Piedra Hoja, Saquito Fragante, Dulce de Nata |
| Pueblo Pardal (meteorito) | Ocaso | Piedra Lunar, Piedra Noche |
| Pueblo Lavacalda (volcán) | Sana | Piedra Fuego, Magmatizador |
| Herboristería de Lavacalda | — | Hierba Blanca, Hierba Mental, Hierba Única (objetos equipables) |
| Ciudad Arborada (bosque) | Nido | Piedra Solar, Garra Afilada, Colmillo Agudo |
| Grandes Almacenes Calagua (2.ª planta) | Lujo, Ocaso, Veloz | — |
| Grandes Almacenes Calagua (3.ª planta) | — | **Todos** los objetos evolutivos |
| Ciudad Algaria (espacio, Cueva Cardumen) | Malla, Buceo | Piedra Alba, Piedra Día, Piedra Hielo, Protector |
| Ciudad Arrecípolis | Buceo, Lujo | Roca del Rey, Escama Dragón, Tela Terrible |
| Liga, Cima Entrenador | — | — |
| Frente Batalla | — | Vitaminas (como en el original) |

- **Medallas necesarias** (en todas las tiendas a la vez): las piedras evolutivas desde la **2.ª**, y los objetos de las antiguas evoluciones por intercambio (y Garra/Colmillo) desde la **4.ª**. La tabla está en `src/shop_criteria.c` (`sDualockeShopBadges`); los objetos que no salen en ella se venden siempre.
- Se han quitado las Cartas de las tiendas de ciudad, salvo en Calagua.
- **Las megapiedras no se venden:** se encuentran explorando el mapa (ver más abajo). El segundo dependiente de Jorge sigue en pie para los objetos aleatorios.

### Evoluciones por intercambio (hecho)

Como no hay intercambios entre partidas, se han cambiado todas:

- **Las que solo pedían intercambio ahora son por nivel:**
  - Alakazam: 36
  - Machamp, Golem, Golem de Alola, Gengar, Gigalith, Conkeldurr: 38
  - Trevenant, Gourgeist (todos los tamaños), Escavalier, Accelgor: 32
- **Las que pedían intercambio con objeto equipado ahora evolucionan usando el objeto desde la mochila, como una piedra:** Steelix y Scizor (Revestimiento Metálico), Politoed y Slowking (Roca del Rey), Kingdra (Escama Dragón), Porygon2 (Mejora), Porygon-Z (Disco Extraño), Rhyperior (Protector), Electivire (Electrizador), Magmortar (Magmatizador), Dusknoir (Tela Terrible), Huntail (Diente Marino), Gorebyss (Escama Marina), Milotic (Escama Bella), Aromatisse (Saquito Fragante), Slurpuff (Dulce de Nata).

### Gimmicks desactivados

**Z, Dinamax y Tera no se usan.** No hace falta tocar el código: solo se activan con objetos (Pulsera Z, Maximuñequera, Orbe Teracristal) que no se pueden conseguir. El randomizer debe **excluir** del reparto esos objetos, los cristales Z, las teralitas y los Maxisetas.

### Pantalla de datos del Pokémon

Para ver todo sin herramientas externas (pedido por Miguel el 24/10/2026):

- **Página de información:**
  - Detrás de la naturaleza, lo que sube y lo que baja en letra pequeña: "Firme (+Atq -AtE)", o "(neutra)". Si se ha usado una menta, sale el efecto de la menta.
  - **START** pasa por todas las habilidades que puede tener la especie, con su descripción. A la derecha sale "Actual" (azul), "Posible" u "Oculta" (rojo) y cuántas hay ("2/3"). Al cambiar de Pokémon vuelve a la actual.
- **Página de características:** **A** pasa de características a IVs y a EVs, con el número exacto. La etiqueta de arriba cambia a IVs/EVs. Lo que sube la naturaleza sale en rojo y lo que baja en azul (ya venía activado).
  - **Amistad (Jorge, 13/11/2026):** arriba a la derecha, donde salían las cintas (que en el locke no sirven), se ve la amistad de 0 a 255 ("123/255"). La etiqueta pone "AMISTAD", dibujada con las letras de las otras etiquetas en `graphics/summary_screen/tiles.png` e `iv_ev_tiles.png`. Las evoluciones por amistad piden 160 o más.
- **Movimientos:** ya enseñaban tipo, categoría (físico/especial/estado), PP, potencia, precisión y descripción.
- Código: `include/config/summary_screen.h` (opciones `P_SUMMARY_SCREEN_IV_EV_*`) y `src/pokemon_summary_screen.c` (busca "Dualocke").
- Pendiente: hacerla más bonita con gráficos nuevos (fondos, iconos). Hace falta dibujarlos y probarlos en el emulador.

### Interfaz: opciones del motor encendidas (Miguel, 16/11/2026)

Miguel: "interfaces más chulas, actualizadas". Son cosas que la expansion ya trae y estaban apagadas. Todas en `include/config/`; ninguna cambia la partida guardada.

- **Pokédex estilo HeartGold/SoulSilver** (`POKEDEX_PLUS_HGSS`, `pokedex_plus_hgss.h`):
  - Para cada Pokémon: estadísticas base, captura, experiencia, amistad, grupos huevo, habilidades, movimientos y evoluciones (con su método).
  - **Enseña lo de la semilla:** los movimientos por nivel al azar (ya salían de `GetSpeciesLevelUpLearnset`) y la habilidad al azar (`GetAbilityBySpecies`). Las MT y los tutores se sacan con `Dualocke_MovimientosEnsenables` (`src/dualocke_aleatorio.c`): lo que enseña cada MT con la semilla y si esa especie lo puede aprender, como al usar la MT. La lista original no valía, porque las MT enseñan otros movimientos.
  - **Traducida:** los 97 textos de `src/pokedex_plus_hgss.c` con `ES()`, medidos con la fuente pequeña para que quepan en sus huecos. Las etiquetas que son dibujos (pestañas) siguen en inglés, como en la Pokédex de antes.
  - Delante de un tipo o de una naturaleza se pone "tipo" o "naturaleza", porque en español va delante ("tipo Siniestro en el equipo").
- **Tipos del rival en combate** (`B_SHOW_TYPES` = siempre): iconos de tipo junto a la barra de vida al elegir movimiento.
- **Descripción al recoger un objeto** (`OW_SHOW_ITEM_DESCRIPTIONS` = siempre): la imagen y lo que hace, arriba. El modo "solo la primera vez" no: añade datos a la partida guardada y rompería las que están en curso.
- **Carteles de zona estilo Blanco/Negro** (`OW_POPUP_GENERATION` = `GEN_5`), negros, con la hora en 24 h. Ocupan todo el ancho, así que caben todos los nombres en español.
- **Combates más rápidos:** pausas de texto a la mitad (`B_WAIT_TIME_MULTIPLIER` 16 → 8) y sin la entrada deslizante (`B_FAST_INTRO_NO_SLIDE`).
- **No se puede huir de un entrenador** (`B_RUN_TRAINER_BATTLE` = `FALSE`). Estaba activado, y huir cuenta como perder el combate (`B_OUTCOME_FORFEITED`), o sea, perder el locke. Así no pasa por error.
- **Siguen apagados:** el Pokémon que te sigue (idea 6) y el DexNav, que piden más trabajo.

### Mochila más grande (hecho, Jorge, 20/11/2026; lo pidió Miguel). **Rompe las partidas guardadas**

- **Por qué:** salen unos 370 objetos distintos del bolsillo OBJETOS y cabían 30; 37 objetos clave para 30 casillas (si se llena, no se puede recibir uno); 28 tipos de Poké Ball para 16; 68 bayas para 46.
- **Casillas:** OBJETOS 150 (antes 30), OBJ. CLAVE 50 (30), POKé BALLS 30 (16), BAYAS 70 (46), MEDICINAS 70 (60). MT Y MO (64) y MEGAPIEDRAS (130) igual. `include/constants/global.h`.
- **OBJETOS pasa a `SaveBlock3`** (`bagItems`), con MEDICINAS y MEGAPIEDRAS: con 150 casillas no cabe en `SaveBlock1`. Los demás siguen en `struct Bag` (`SaveBlock1`).
- **Espacio que queda:** `SaveBlock1` 192 bytes, `SaveBlock2` 72, `SaveBlock3` 220.
- Se mueve todo lo que va detrás en la partida guardada: **hace falta empezar partida nueva.** Va con el nombre largo y los entrenadores nuevos, para el locke de verdad (Miguel, #112).
- Tests en `test/dualocke.c` ("la mochila tiene los bolsillos más grandes").

### Nombre del jugador de hasta 10 letras (hecho, Jorge, 20/11/2026; idea 8 de `IDEAS.md`)

- **Por qué:** "JORGEMORI" (9 letras) no cabía en las 7 de siempre.
- **Cómo:** el nombre entero se guarda aparte, al final de `SaveBlock2` (`playerNameLong`, `PLAYER_NAME_LENGTH_LONG` = 10). `playerName` se queda con las 7 primeras letras para todo lo que guarda el nombre con tamaño fijo: el EO de cada Pokémon (no caben más letras sin cambiar el tamaño de todos los Pokémon guardados), bases secretas, programas de la tele, juegos por cable… Así no cambia el tamaño de nada.
- **La pantalla de nombres** escribe en `playerNameLong` (hasta 10) y al salir `Dualocke_GuardarNombreJugador` copia las 7 primeras a `playerName` (`src/naming_screen.c`).
- **Dónde se ve entero** (`Dualocke_NombreJugador`, en `src/dualocke.c`): diálogos (`{PLAYER}`), combates, menú de pausa (ahora 2 casillas más ancho), ficha de entrenador, menú de guardar, menú de continuar, Salón de la Fama, Pokédex y el EO en los datos de tus Pokémon.
- **Partidas de antes:** `playerNameLong` está a cero y se usa `playerName`. El nombre largo no rompe nada por sí solo; lo que obliga a empezar de nuevo es la mochila.
- Probado en el emulador con "JORGEMORI" (la ROM de pruebas ya empieza con ese nombre). Tests en `test/dualocke.c`.

### Mochila: bolsillos Medicinas y Megapiedras (hecho, Jorge, 26/10/2026)

Lo pidió Jorge al probar: las megapiedras y las pociones se mezclaban con todo en Objetos.

- **7 bolsillos**, en este orden: OBJETOS, **MEDICINAS**, POKé BALLS, MT Y MO, BAYAS, **MEGAPIEDRAS**, OBJ. CLAVE. Los nombres de los bolsillos y los de "guardado en el BOLSILLO …" están traducidos.
- **Medicinas** (hasta 60 objetos distintos): pociones y bebidas, revivir, curar estados, Éter/Elixir, vitaminas, Más PP, plumas, mochis y caramelos (Caramelo Raro, Caramelos Exp.). Los Objetos X, la Miel y los repelentes se quedan en Objetos.
- **Megapiedras** (hasta 100; caben las 92 que hay). El Mega-Aro sigue en Objetos clave.
- **Sin dibujos nuevos:** la mochila reutiliza el dibujo de Objetos para Medicinas y el de Objetos clave para Megapiedras. Los cuadraditos de arriba ahora son 7 (columnas 4-10 del fondo) y MEGAPIEDRAS se escribe con la fuente estrecha porque no cabe en la normal.
- **Dónde se guardan:** en `SaveBlock3` (`bagMedicine` y `bagMegaStones`), que estaba casi vacío; a `SaveBlock1` le quedaban 376 bytes y no se ha tocado. Las partidas guardadas de antes no sirven (dan igual, eran de prueba).
- El tutorial de Blasco (la Poción va a Medicinas) guarda y devuelve también ese bolsillo. Las bebidas de la azotea del Centro Comercial dicen que van a MEDICINAS.
- Depuración: "Fill Pocket Items" llena también Medicinas y da una de cada megapiedra; "Fill Pocket Key Items" da el Mega-Aro.
- Tests en `test/dualocke.c` (busca "bolsillos").

### Islas del ferry (hecho, Miguel, 16/11/2026; falta probarlo)

ISLA SUR, ISLA LEJANA, ISLA ORIGEN y ROCA OMBLIGO ya existían, pero solo con un billete de evento y después de la Liga. Ahora son las primeras zonas "nuevas" (`ZONAS.md`, propuesta 8).

- **Se abren una por medalla.** El encargado del puerto de CALAGUA da el billete de cada una y el ferry ya no espera a la Liga (`Dualocke_EventScript_BilletesIslas`, `data/scripts/dualocke_islas.inc`):

  | Isla | Medalla | Tramo | Pokémon fuerte (sin semilla) | Nivel | Premio |
  | --- | --- | --- | --- | --- | --- |
  | ISLA SUR | 6.ª | 7 | Dragonite | 70 | Cinta Elección |
  | ISLA LEJANA | 7.ª | 8 | Flutter Mane | 81 | Restos |
  | ISLA ORIGEN | 8.ª | 9 | Roaring Moon | 97 | Parche Habilidad |
  | ROCA OMBLIGO, cima | 8.ª | 9 | Volcarona | 97 | Vidasfera |
  | ROCA OMBLIGO, fondo | 8.ª | 9 | Kingdra | 97 | Chaleco Asalto |

- **Guardianes únicos (Miguel, 17/11/2026):** "que cada uno de los guardianes sea único". Antes se repetían Salamence, Tyranitar, Metagross, Charizard y Gyarados. Ahora, sin semilla, no hay dos iguales:
  - Se quedan Houndoom (GRUTA ÍGNEA), Baxcalibur (ISLA NEVADA), Garchomp (RUINAS ARENOSAS), Gengar (MANSIÓN OLVIDADA), Charizard (ISLA VOLCÁNICA), Salamence (CUMBRE METEORO) y Metagross (ISLA DE RUINAS).
  - Las islas del ferry llevan Pokémon que recuerdan a Ho-Oh y Lugia, los que había allí: Dragonite, Volcarona y Kingdra. ISLA LEJANA e ISLA ORIGEN, Pokémon Paradoja: Flutter Mane y Roaring Moon.
  - Pokémon Paradoja también en la ISLA ARENOSA (Sandy Shocks) y la PLAYA VOLCÁNICA (Slither Wing). **No son legendarios para el locke:** la regla de legendarios solo mira los restringidos, los singulares y los míticos.
  - Dondozo y Tatsugiri, en la cala de la MARISMA AZULIZA (con SURF).
  - Hydreigon, en el BOSQUE SINIESTRO, y Dragalge, en la CIÉNAGA TÓXICA.
  - Aggron, en la CANTERA; Gardevoir, en el PRADO DE HADAS, y Haxorus, en el VALLE DEL DRAGÓN (21/11/2026).
  - Con semilla salen otros, como siempre (`islas()` de `estaticos.py`): ahí se sortean por especie, así que dos guardianes de la misma especie sin semilla tendrían el mismo con semilla.

- **Sin legendarios (Miguel):** "sustituirlos por Pokémon fuertes (pseudos, Pokémon con mega o Gigamax) capturables y que den recompensa".
  - Latios/Latias, Mew, Deoxys, Ho-Oh y Lugia se quedan en el mapa, pero siempre ocultos (el código del juego los usa, como el Mew que se esconde en la hierba). Tampoco está el puzle del triángulo de la ISLA ORIGEN.
  - En su sitio hay un Pokémon que se puede capturar. Es un estático: no gasta la captura de la zona. Si es de una línea que ya tienes, va a VETADOS, como siempre.
  - **Con semilla sale otro fuerte:** de una línea que acaba en 600 o más de estadísticas base, o con mega (también las de las formas Gigamax). `islas()` en `tools/dualocke/aleatorio/estaticos.py` los sortea aparte, con su propio RNG, así que los demás estáticos y regalos de las semillas en curso no cambian. El sprite del mapa es el de la especie que sale (`Dualocke_GraficoPokemonIsla`).
  - **Nivel:** el del entrenador normal más fuerte de su tramo (cap − 3), con la regla `"tope"` de `reescalar_niveles.py`. La regla `("tope", tramo)` usa el tope de otro tramo: la cala de la MARISMA AZULIZA está en el tramo 2, pero solo se llega con SURF (tramo 6).
  - **Premio** al vencerlo o capturarlo: el objeto de la tabla y, si tiene mega, su megapiedra (`Dualocke_MegapiedraPokemonIsla`). Si huyes, se queda.
- **Entrenadores (6):** TERRY y CINDY en la ISLA SUR, MIKE y las gemelas AMY Y LIV en la ISLA LEJANA, las gemelas GINA Y MIA en la ISLA ORIGEN y LUCAS en el cruce de ROCA OMBLIGO.
  - **Movidos el 19/11/2026** porque tapaban el paso aunque los vencieras: TERRY, de la única casilla del sendero de la ISLA SUR (19, 8) a un lado del camino (25, 10), mirando a la izquierda; MIKE, del pasillo de la ISLA LEJANA (10, 22) a un hueco al lado (11, 26), mirando a la izquierda. Siguen viéndote al pasar.
  - Son entrenadores que existían pero no salían en ningún mapa, así que no se gastan flags ni se rompe la partida guardada.
  - `reescalar_niveles.py` les pone el nivel de su tramo (`ENTRENADORES_ISLAS`), pero no cuentan para la banda del tramo: así no cambia el nivel de nadie más.
- **Salvajes** (`tools/dualocke/zonas_nuevas.py`): pesca en las cuatro islas, hierba en el interior de la ISLA SUR y de la ISLA LEJANA, y cueva en ROCA OMBLIGO.
  - La ISLA SUR no tenía hierba: el 17/11/2026 se puso hierba alta en el claro del bosque, alrededor de la charca, en su `map.bin`. Las tablas van al final de `wild_encounters.json`, para no cambiar los salvajes de las semillas en curso. Cada isla es su propia zona de captura (ya lo era en el mapa de la región).
- **Objetos:** 11 objetos normales (con semilla, al azar como los demás), colocados con `colocar_objetos.py` (`OBJETOS_ISLAS`, flags `FLAG_ITEM_ISLA_...` del 0x8E5 al 0x8EF).
- **Textos:** los del ferry y los marineros eran de postgame y estaban en inglés; ahora están en `traduccion/dialogos/41_islas_ferry.tsv`.
- **Flags nuevos:** `FLAG_DUALOCKE_ISLA_SUR`, `_LEJANA`, `_ORIGEN`, `FLAG_DUALOCKE_OMBLIGO_CIMA` y `_FONDO` (0x881-0x885).

### Comprobar las zonas sin compilar

`python3 tools/dualocke/comprobar_zonas.py` revisa todos los mapas de Hoenn y devuelve los fallos (0 el 17/11/2026, en 944 mapas). Hay que lanzarlo **antes de subir cualquier mapa nuevo**: los primeros mapas nuevos se subieron sin apuntar sus `scripts.inc` en `data/event_scripts.s` y no habrían compilado.

Qué mira:

- scripts apuntados en `event_scripts.s` y layouts (existen y miden lo que dicen);
- etiquetas de los scripts y constantes (flags, objetos, especies, entrenadores, mapas, música…);
- puertas (destino y número de puerta) y conexiones (que el otro mapa conecte de vuelta);
- objetos repetidos en la misma casilla;
- entrenadores: equipo en `trainers.party`, `TRAINERS_COUNT_EMERALD` y los nuevos de `zonas_nuevas.py` (clase, foto y música que existan, nombre de 10 letras como mucho);
- salvajes: huecos y especies;
- zonas de captura: caben en las variables y las nuevas tienen sus carteles.

Las rarezas del juego original (puertas del ferry fuera del mapa…) están en `ORIGINALES`.

### Al añadir una zona nueva: que no cambie lo de las partidas en curso (Jorge, 16-17/11/2026)

- **`tools/dualocke/aleatorio/zonas.py`:** hay que poner ahí el prefijo de los mapas de la zona (`PREFIJOS`) y el de los flags de sus objetos (`FLAGS_OBJETOS`, el de su grupo en `colocar_objetos.py`). Así sus salvajes y objetos se sortean aparte, al final. Sin eso, como los mapas se recorren por orden alfabético, los objetos nuevos cambian casi todos los objetos del suelo, la Recogida y lo que piden los intercambios de las semillas en curso. Pasó con el #81 y otra vez con todas las zonas del #84 al #98.
- **Que nadie se quede encerrado:** `tools/dualocke/sin_salida.py` mira, en cada mapa de las zonas nuevas, si desde todo sitio al que se llega andando se puede volver a una salida. El barro solo se baja sin la bici de carreras, y los saltos son de un sentido. En la CUMBRE METEORO se bajaba al guardián por una cuesta de barro y Miguel se quedó encerrado (18/11/2026). Va en el CI.
- **Que ningún entrenador ni persona tape el paso** (también en `sin_salida.py`, 19/11/2026): entre las salidas del mapa (puertas, bordes y los sitios a los que te deja un script, como el barco) se tiene que poder ir igual con las personas que sin ellas. Cuentan las que no se mueven ni desaparecen nunca (flag `"0"`). En la ISLA SUR, TERRY estaba en la única casilla del sendero y no se llegaba a la cueva (lo vio Miguel); en la ISLA LEJANA, MIKE tapaba igual un pasillo de una casilla (lo vio el script).
- **Que ninguna Poké Ball del suelo tape el paso** (también en `sin_salida.py`, Jorge, 22/11/2026): ni entre dos salidas, ni delante de una puerta, ni a una persona, un entrenador o un cartel. Detrás de una Ball sí puede haber otra. Se mira en **todos los mapas**, pero solo con las Balls de `colocar_objetos.py` (`FLAG_ITEM_MEGA_`, `_COMP_` y `_TICKET_`) y las de las zonas nuevas; las de Esmeralda que tapan algo lo hacen a propósito. Lo encontró el bot que se pasa el juego (PR #118): la Ball de las GAFAS ESPECIALES tapaba la escalera del MUSEO OCEÁNICO 2F, y la del TICKET-RECUERDO, la puerta del MONTE PÍRICO. El script encontró otras 10: la casa de la RUTA 124, las escaleras del PILAR CELESTE 3F, 4F y 5F, el camino de la ISLA LEJANA, y entrenadores tapados en la RUTA 106, la RUTA 115 (tres Balls seguidas) y el CAMINO ESCABROSO. Se movieron todas a una casilla al lado (con las partidas en curso no pasa nada: solo cambia dónde está la Ball, y si ya la has cogido no vuelve a salir).
- **Que se pueda llegar desde el juego, no solo desde el borde de la zona:** `tools/dualocke/alcance.py` (#97) recorre Hoenn desde PUEBLO ESCASO y dice en qué tramo se llega a cada mapa. En las rutas de mar, el mar de fuera de la barrera de rocas es decorado: si la zona se conecta por ese borde, no se puede entrar.
- **`HOENN_EXTRA_MAPSEC_LAST`** (`src/dualocke.c`) tiene que ser la última zona nueva; si no, la zona no tiene captura propia. `comprobar_zonas.py` lo avisa.
- **Entrenadores:** están todos los de Esmeralda usados (864 de 864). Una zona nueva con entrenadores nuevos necesita subir `TRAINERS_COUNT`, y eso mueve los flags del sistema de las partidas guardadas: hay que reutilizar o pensarlo antes.

### Dibujar mapas como los del juego: `autotile.py` (Miguel, 17/11/2026)

Miguel: la marisma y la playa "quedan raras"; hay que mirar cómo están hechas las rutas, playas y pantanos del juego y diseñar igual. `tools/dualocke/autotile.py` aprende de los mapas originales de exterior (sin las zonas nuevas) qué pieza va en cada sitio según sus vecinas.

- **Cómo se usa:** el script de la zona dibuja el mapa con letras (`PLANO`): `.` hierba, `,` hierba alta, `~` agua, `s` arena, `R` risco… `Aprendiz.pintar()` elige cada pieza (las orillas, las esquinas, los bordes de la hierba) y `Aprendiz.revisar()` cuenta las parejas de piezas vecinas que no salen en ningún mapa del juego. `arboles_grandes()` pinta los árboles de 2 × 2 (con la copa de hierba alta si hay hierba alta encima) y avisa si un grupo queda cortado.
- **Reglas aprendidas del juego:**
  - La arena de playa **nunca toca la hierba**: siempre hay un risco o agua entre las dos (como la playa de la RUTA 104). El risco va con la hierba arriba o a la izquierda y la arena abajo o a la derecha, y se baja por una escalera.
  - En una charca, la orilla de arriba y los lados se dibujan sobre el agua, y la de abajo sobre la hierba (o la arena).
  - Los árboles de AZULIZA solo van sobre arena; AZULIZA no tiene hierba.
  - Los caminos de tierra tienen su propio borde (piezas 0x118-0x12A).
  - **Islas de mar** (RUTAS 127-134): la arena va rodeada de un anillo de bajío de 2 o 3 casillas; sobre la arena hay peñas, y en el mar rocas sueltas y remolinos, separados del bajío (el mar de al lado del bajío lleva orilla). La hierba de una isla va en otra parte, con orilla de mar, y no toca la arena ni el bajío. Las peñas de la RUTA 127 tienen un hueco de base secreta: al copiarlas se tapa.
- **Para copiar trozos del juego dentro de un plano:** las casillas que pone el script (peñas, un montículo) cuentan para sus vecinas como el terreno de alrededor. Si se marcan como `"pared"`, sus vecinas las ven como un acantilado (por ejemplo, el mar de debajo de un acantilado copiado).
- **Resultado:** las parejas raras bajaron de 118 a 63 en la marisma y de 240 a 61 en la playa. Las que quedan son uniones entre trozos copiados de otros mapas.

### CIÉNAGA TÓXICA (hecho, Miguel, 17/11/2026; falta probarlo)

El segundo bioma "por tipo" (sitio D del mapa de propuestas). El tipo **Veneno** salía en muchas zonas, pero solo por Zubat y Tentacool: no tenía zona propia.

- **Dónde:** se entra andando por el borde sur de la RUTA 117 (x 32-36), junto a su hierba alta, sin pantalla de carga. **Tramo 3** (cap 32), el de la RUTA 117.
  - Iba a ir al este de la RUTA 110, pero ese borde es todo agua: haría falta SURF, que llega en el tramo 6. Así es la primera zona nueva a la que se llega a pie después del BOSQUE FRONDOSO.
  - En esa parte de la RUTA 117 la fila de abajo tenía las copas de los árboles del borde; pasan a ser hierba alta (x 32-34) y hierba (x 35-36).
- **Todo lo hace `tools/dualocke/crear_cienaga_toxica.py`** (60 × 40, con los gráficos de la RUTA 117: General + Mauville). Siempre llueve.
  - Charcas por todas partes, manchas de hierba alta y un camino de barro que baja desde la entrada y cruza la ciénaga.
  - Al fondo, la charca grande, con un islote en medio al que se llega por una lengua de tierra: ahí está el guardián.
  - Los árboles son los normales de Hoenn, con las funciones `arbol_normal()` y `copa_normal()` que ahora comparten el BOSQUE SINIESTRO y la ciénaga en `autotile.py`.
  - Quedan 16 parejas de piezas que el juego no usa, casi todas en las curvas del camino de barro y en la entrada.
  - **Sin hierba muy alta:** se probó la de la RUTA 120, pero su borde de abajo solo existe en los gráficos de ARBORADA y quedaba cortada.
  - **Charcas rectas,** como las de la RUTA 117: con escalones quedaban esquinas sin orilla.
- **Guardián:** en el islote. Sin semilla es Dragalge (Veneno/Dragón) a nivel 29 (regla `"tope"`); premio, Lodo Negro y su megapiedra. `FLAG_DUALOCKE_GUARDIAN_CIENAGA` (0x472).
- **Zona de captura propia:** `MAPSEC_CIENAGA_TOXICA`, al final de la lista, y `HOENN_EXTRA_MAPSEC_LAST` pasa a ser esa: 118 de 128. Cartel de madera.
- **Salvajes** (al final de `wild_encounters.json`, nivel 27-31):
  - **Hierba alta:** Grimer, Croagunk, Koffing, Gloom, Weepinbell, Wooper de Paldea, Arbok, Trubbish, Foongus y Grafaiai; raros, Salandit y Toxel.
  - **Pesca:** Barboach, Skrelp, Qwilfish, Mareanie y Whiscash.
  - **Surf:** más tarde; salen al nivel del tramo 3.
- **Sin entrenadores** (no queda ningún hueco). Hay una científica que estudia el agua y avisa del islote.
- **Objetos** (con semilla, al azar): Flecha Venenosa, Bulbo, Tabla Tóxica oculta en el islote y un Ticket-Recuerdo. Flags sueltos: 0x054, 0x055, 0x479 (el oculto necesita uno de 0x1F4 en adelante) y 0x1AA.
- `autotile.py` ya no aprende de la ciénaga como si fuera un mapa original: "Cienaga" está en la lista de zonas nuevas (`NUEVOS`).

### CANTERA (hecho, Miguel, 21/11/2026; falta probarlo)

Idea de Miguel jugando (18/11/2026): "una Cantera de tipo Acero en la RUTA 116, por la salida del Túnel Fervergal". El bioma del tipo Acero (`PLAN.md`, propuesta B). Todo lo hace `tools/dualocke/crear_cantera.py`.

- **Entrada:** una boca de cueva nueva en la RUTA 116, en la misma pared que la salida este del TÚNEL FERVERGAL: la del túnel está en (65, 10) y la de la cantera en (67, 10), con el mismo dibujo. Puerta a altura 0. No se quita ninguna base secreta.
  - A esa parte de la ruta se llega cruzando el túnel, con GOLPE ROCA: **tramo 3**, como la CIÉNAGA TÓXICA.
- **La cantera** (40 × 30, gráficos de la RUTA 116):
  - arriba, la pared de roca con la boca de la cueva (relleno de montaña y una cara de dos filas, con los valores de la RUTA 116);
  - tres terrazas separadas por riscos, cada uno con su escalera (`autotile.py`);
  - suelo de tierra, manchas de hierba alta (los salvajes), seis rocas de GOLPE ROCA (vuelven al salir) y árboles a los lados y abajo.
- **Guardián:** Aggron (Miguel, 21/11/2026), en el fondo. Premio, Tabla Acero. `FLAG_DUALOCKE_GUARDIAN_CANTERA` (0x4FF).
- **Una persona que trabaja en la cantera,** junto a la entrada. No hay entrenadores: no queda ninguno libre.
- **Zona de captura propia:** `MAPSEC_CANTERA` (119 de 128).
- **Salvajes** (tramo 3, a medio evolucionar): Aron, Nosepass, Graveler, Carkol, Magneton, Klink, Ferroseed, Pawniard, Drilbur, Cufant y, raros, Tinkatuff y Honedge.
- **Objetos:** Piedra Dura (0x068), Revestimiento Metálico (0x0E9), Bola Férrea oculta (0x2D9) y un Ticket-Recuerdo (0x1DA). Flags sueltos: un grupo de `colocar_objetos.py` por flag.

### PRADO DE HADAS (hecho, Miguel, 21/11/2026; falta probarlo)

El bioma del tipo Hada (`PLAN.md`, propuesta C). Miguel lo quería "en la ruta de antes del Instituto Meteorológico, al lado de la zona de vallas, de jardín". Todo lo hace `tools/dualocke/crear_prado_hadas.py`.

- **Entrada:** junto al INSTITUTO METEOROLÓGICO, por el oeste. Se cortan los árboles del borde izquierdo de la RUTA 119 en las filas 33-34: la fila 32 pasa a ser pie de árbol y las 33-34, hierba (en (2, 32) está el instituto). El prado va a la izquierda de la ruta (su fila 0 es la -1 de la ruta) y se cruza sin pantalla de carga: **tramo 6**.
  - **Altura de la entrada (22/11/2026):** la hierba de la ruta está a altura 4 y la del prado a 3, y el juego no deja pasar de una a otra: no se entraba (lo vio el bot de Jorge, #117). Las dos casillas del borde del prado que dan a la entrada van a altura 0, la de paso, desde la que se puede ir a las dos. `comprobar_zonas.py` mira ahora la altura a los dos lados de las conexiones de las zonas nuevas.
  - El jardín con vallas del lago, al norte del instituto, no se alcanza en el tramo 6 (`alcance.py`): por eso la entrada va junto al instituto.
- **El prado** (40 × 36, gráficos de la RUTA 119): un camino de tierra lleva de la entrada al centro. Alrededor, flores, tres charcas, hierba alta y hierba muy alta (con su borde: los gráficos de ARBORADA lo tienen). Al norte, junto a la charca grande, un claro con un anillo de flores donde espera el guardián.
  - La columna de la derecha del prado son árboles donde la ruta no se pisa (árboles, y en las filas 23-26 de la ruta, el acantilado de encima del instituto). Las flores nunca van junto a una charca: se perdería su orilla. El script lo comprueba.
- **Guardián:** Gardevoir (Miguel, 21/11/2026). Premio, Tabla Duende. `FLAG_DUALOCKE_GUARDIAN_PRADO` (0x4E4).
- **Una florista** junto a la entrada.
- **Zona de captura propia:** `MAPSEC_PRADO_HADAS` (120 de 128).
- **Salvajes** (tramo 6): Clefable, Wigglytuff, Granbull, Azumarill, Togetic, Kirlia, Floette, Aromatisse, Slurpuff, Dedenne y, raros, Comfey y Mimikyu. En las charcas (SURF y caña): Marill, Azumarill, Luvdisc, Goldeen, Surskit y Seaking.
- **Objetos:** Piedra Día y Saquito Fragante (0x8F4-0x8F5), Pluma Feérica oculta (0x8FD) y un Ticket-Recuerdo (0x8FE).

### ISLA DEL DRAGÓN y VALLE DEL DRAGÓN (hecho, Miguel, 21/11/2026; falta probarlo)

El bioma del tipo Dragón (`PLAN.md`, propuesta I). Miguel: "una zona con cascadas o montañas, que le dé un aire épico, dirigida a la última parte del juego"; se llega surfeando desde una ruta del sur. Todo lo hace `tools/dualocke/crear_isla_dragon.py`.

- **Entrada:** surfeando hacia el sur desde el borde de abajo de la RUTA 130 (la isla va de su x 33 a la 72). Se alcanza en el tramo 7-8, como las otras islas del sur; sus niveles son los del **tramo 8**.
  - **La esquina de la derecha (22/11/2026):** antes la isla iba de la x 40 a la 79. Al pasar de la RUTA 129 a la 130, el juego copia lo que se veía en la 129 (`MoveMapViewToBackup`, `src/fieldmap.c`), y debajo de la 129 no hay nada en esas columnas: la isla quedaba tapada en las x 73-79 y desde ahí no se bajaba (lo vio el bot de Jorge, #117). Ahora acaba en la x 72. `comprobar_zonas.py` avisa si una zona nueva de arriba o de abajo se puede cruzar a menos de 7 columnas de un lado con otro mapa al lado.
- **ISLA DEL DRAGÓN** (40 × 34, gráficos de la RUTA 134):
  - una isla de arena con su bajío, tres peñas de la RUTA 127 y rocas en el mar;
  - en medio, el montículo del PILAR CELESTE con su cueva (como en la ISLA VOLCÁNICA). La cueva mira al sur: se rodea el montículo;
  - las 8 filas de arriba son mar, que es lo que se ve desde la RUTA 130 (tiene otros gráficos).
- **VALLE DEL DRAGÓN** (40 × 40): la mitad de abajo de CIUDAD COLOSALIA, la de la gran cascada.
  - Sin el Centro Pokémon (es hierba corta) ni los carteles; las flores de la izquierda son hierba alta (los salvajes).
  - Se llega por la cueva de arriba (la de la CALLE VICTORIA), a la meseta con flores. Por las escaleras se baja al lago de arriba y la gran cascada cae al mar; para volver a subir hace falta CASCADA.
  - Cada cosa va a la altura del suelo en el que está: el valle tiene varias.
- **Guardián:** Haxorus (Miguel, 21/11/2026), en la meseta, frente a la cascada. Premio, Tabla Draco. `FLAG_DUALOCKE_GUARDIAN_DRAGON` (0x8FF).
- **Zona de captura propia:** `MAPSEC_ISLA_DRAGON`, las dos partes (121 de 128).
- **Salvajes** (tramo 8): en la hierba, Flygon, Altaria, Noivern, Tyrantrum, Duraludon, Drampa, Goodra, Kommo-o, Salamence, Garchomp y, raros, Dragapult y Dragonite. En el agua, Dragonair, Seadra, Dragalge, Kingdra y Gyarados; con caña, también Horsea, Dratini y Skrelp.
- **Objetos:** Escama Dragón (0x905), Colmillo Dragón oculto (0x906) y un Ticket-Recuerdo (0x907).

### BOSQUE SINIESTRO (hecho, Miguel, 17/11/2026; falta probarlo)

El primer bioma "por tipo". Miguel pidió que cada tipo tenga su bioma; el análisis de los salvajes sin semilla dio que el tipo **Siniestro** no tenía zona propia: solo salía Poochyena por las rutas normales. Era el sitio F del mapa de propuestas (`fotos_zonas/13_propuestas_biomas.png`).

- **Dónde:** se entra andando por el borde sur de la RUTA 123, al pie del MONTE PÍRICO (x 103-106), sin pantalla de carga. **Tramo 6** (cap 62), el de la RUTA 123.
  - En esa parte de la RUTA 123, la fila de abajo tenía las copas de los árboles del borde (0x00E, que se pisa). Esas cuatro casillas pasan a ser hierba.
- **Todo lo hace `tools/dualocke/crear_bosque_siniestro.py`** (50 × 44, con los gráficos de la RUTA 123: General + Lilycove). A la sombra (`WEATHER_SHADE`) y con la música de fuera del MONTE PÍRICO.
  - **El camino:** un sendero baja hasta un primer claro con hierba alta, donde hay una bruja. Al este hay una charca oscura y al oeste, un callejón.
  - **El centro:** un claro grande con un risco que se salta hacia abajo; también se rodea por el este.
  - **El fondo:** un bosque profundo con senderos estrechos, claros de hierba alta y, al final, el claro del guardián. Desde ahí se vuelve a la entrada sin subir el risco (comprobado).
- **Los árboles normales de Hoenn** (los de la RUTA 123) miden una casilla de ancho:
  - **Interior:** 0x0C6 y 0x0C7.
  - **Pie de la franja:** 0x016.
  - **Copa:** el árbol de debajo pinta su copa en la casilla de hierba de encima, y esa casilla se puede pisar. Es 0x00E sobre hierba y 0x025 sobre hierba alta.
  - Lo demás lo pinta `autotile.py`. Quedan 2 parejas de piezas que el juego no usa: la punta del risco junto a un árbol, y dos copas distintas juntas.
- **Guardián:** en el claro del fondo. Sin semilla es Hydreigon (Siniestro/Dragón) a nivel 59 (regla `"tope"`); premio, Tabla Pavor. `FLAG_DUALOCKE_GUARDIAN_SINIESTRO` (0x91E). Con semilla sale otro fuerte (`islas()` de `estaticos.py`).
- **Zona de captura propia:** `MAPSEC_BOSQUE_SINIESTRO`, al final de la lista, y `HOENN_EXTRA_MAPSEC_LAST` pasa a ser esa: 117 de 128. Cartel de madera.
- **Salvajes** (hierba alta): Liepard, Ariados, Shiftry, Trevenant, Honchkrow, Skuntank, Gourgeist, Thievul, Spidops y Grimmsnarl; raros, Zoroark y Spiritomb.
- **Sin entrenadores:** ya no queda ningún hueco libre en la lista (864 de 864). Hay una bruja que avisa del guardián sin decir cuál es (con semilla es otro).
- **Objetos** (con semilla, al azar): Gafas de Sol, Piedra Lunar, Hechizo oculto y un Ticket-Recuerdo. Como ya no quedan bloques de flags seguidos, van en flags sueltos: 0x4F9, 0x4FA, 0x468 y 0x1AB. El oculto necesita uno de 0x1F4 en adelante (`FLAG_HIDDEN_ITEMS_START`): si no, no compila, y `comprobar_zonas.py` lo avisa. `crear_bosque_siniestro.py` los pone en su sitio (`SITIO_OBJETOS`).

### CUMBRE METEORO (hecho, Miguel, 17/11/2026; falta probarlo)

- **Arreglo del 18/11/2026** (Miguel jugando, se quedó encerrado):
  - Las cuevas van a altura 0: estaban a 3, y el suelo de la LADERA está a 5, así que no funcionaban.
  - Sus dos objetos se pasan a la altura del suelo.
  - El borde de los dos mapas es montaña (el de la RUTA 114). Antes era mar.

- **Dónde:** una cueva nueva en la pared de roca de la RUTA 115, junto a la entrada de la CATARATA METEORO (x 31, fila 39; se entra desde abajo, andando). **Tramo 4** (cap 43).
  - El borde norte de la RUTA 115 está cerrado (bosque y acantilados), así que se entra por una cueva y no por el borde.
  - La boca es el mismo dibujo que la de la catarata, puesta en una pared lisa: no se quita ninguna base secreta de la ruta.
- **Todo lo hace `tools/dualocke/crear_cumbre_meteoro.py`.** Dos mapas, con los gráficos de la RUTA 115:
  - **LADERA** (40 × 20): las terrazas de roca del sur de la RUTA 114 (escaleras, rocas y bordillos de un solo sentido), con hierba alta de montaña (la verde con fondo de roca, 0x212, que en el juego no se usaba). Arriba del todo, otra cueva sube a la cumbre.
  - **CUMBRE** (22 × 31): las cimas de la RUTA 115, a las que en el juego no se llega. Con nieve (nieve en combate) y hierba escarchada (la de ceniza de la RUTA 113, 0x20A). Arriba espera el guardián.
  - Las bases secretas de los trozos copiados se tapan con roca, y dos pasan a ser las cuevas.
  - Desde cada entrada se llega a la salida y al guardián, también con los bordillos (comprobado).
- **Guardián:** sin semilla, Salamence a nivel 40 (regla `"tope"`); premio, Colmillo Dragón y su megapiedra. `FLAG_DUALOCKE_GUARDIAN_CUMBRE` (0x91D, el último flag libre del sistema que no es diario).
- **Zona de captura propia:** `MAPSEC_CUMBRE_METEORO` (las dos partes cuentan como una): 116 de 128.
- **Salvajes:**
  - Ladera: roca y lucha (Machop, Geodude, Aron, Makuhita, Nosepass, Roggenrola, Rockruff, Timburr, Mienfoo…; raros, Druddigon y Bagon).
  - Cumbre: hielo, aire y dragón (Snorunt, Skarmory, Noibat, Bergmite, Cubchoo, Amaura, Rookidee, Altaria, Cryogonal…; raros, Frigibax y Bagon).
- **Objetos:** Piedra Dura y un Ticket-Recuerdo en la ladera; Escama Dragón y Roca Helada (oculta) en la cumbre. `OBJETOS_CUMBRE`: flags normales 0x1DE-0x1E1, porque en la zona del sistema ya no quedan libres que no sean diarios. Los de la ladera se pusieron a mano (`colocar_objetos.py` no les encontró sitio).

### PLAYA VOLCÁNICA (hecho, Miguel, 17/11/2026; con ceniza el 20/11/2026; falta probarlo)

- **Dónde:** pegada al borde oeste de la RUTA 122 (la del MONTE PÍRICO). Se llega surfeando, sin pantalla de carga: **tramo 7** (cap 73).
- **Paso:** la RUTA 122 está rodeada por un anillo de rocas sin huecos. Se quitó la roca de arriba a la izquierda (x 5-6, filas 4-5) y se sale por el noroeste (filas 0-7).
- **Gráficos de LAVACALDA (General + Lavaridge),** distintos de los de la RUTA 122 (General + Lilycove). Desde el 20/11/2026, una copia de los dos con los verdes en color ceniza (ver "Ceniza", abajo).
  - Una conexión entre mapas con gráficos distintos solo se ve bien si, desde cada lado, lo que se ve del otro mapa son gráficos generales. Lo comprueba `tools/dualocke/crear_playa_volcanica.py`, que hace todo.
  - Se cruza por arriba, donde el borde de la RUTA 122 solo tiene mar y rocas generales.
  - Las 8 columnas del este de la playa son solo mar y rocas generales, y desde la fila 8 una fila de rocas no deja acercarse al borde. Desde ahí se vería la orilla del monte, que es de Algaria.
- **La playa** (40 × 40), con sol. **Rehecha el 17/11/2026** con `autotile.py` (ver arriba), como la playa de la RUTA 104 a los pies de un volcán:
  - **Abajo y a la derecha, la playa:** arena con su orilla y su bajío, una charca de marea, rocas en el mar y un arrecife junto al borde este.
  - **Un risco** separa la playa de la meseta, con una escalera (x 16-17, fila 18).
  - **Arriba y a la izquierda, la meseta:** pradera con manchas de hierba alta, árboles, flores, un camino de tierra de la escalera a las termas y una peña volcánica de la RUTA 112.
  - **Las termas:** el rincón de las aguas termales de LAVACALDA, con su poza y su arena, bajo el acantilado del volcán.
- **Bordes (arreglo, 19/11/2026; lo vio Miguel jugando):** el borde del mapa era la roca rosa del MONTE CENIZO y se veía un relleno rosa al acercarse a los bordes, y la arena y el mar se cortaban de golpe arriba y abajo. Ahora el borde es de árboles, como la playa de la RUTA 104. Arriba, el acantilado del volcán sigue sobre la arena y el mar acaba en una fila de rocas; abajo, la playa acaba en árboles y el mar en rocas. Se sigue cruzando a la RUTA 122 por las filas 2-7.
  - Miguel dijo además que "las capturas en el agua rompen el personaje" y que hay "gráficos raros". No se ha podido reproducir: en el emulador se surfeó, se combatió, se huyó y se capturó en el agua de la playa y el personaje se ve bien. Falta que diga dónde le pasó (una foto o el `.sav`).
  - El tiempo era **sequía**, que aclara mucho los colores del mapa. Miguel eligió **sol normal** (`WEATHER_SUNNY`, sin sol en combate; 20/11/2026).
  - Más tarde (20/11/2026) Miguel concretó que le pasó **al volver de capturar** un Pokémon en el agua.
- **Ceniza (Miguel, 20/11/2026):** "solo cambiaría la hierba y el césped verde por el de ceniza", como en la RUTA 113. El mapa es el mismo; cambian los colores.
  - Antes se probó un mapa nuevo con las piezas de ceniza de la RUTA 113 (gráficos de PARDA) y a Miguel no le gustó: prefiere la estructura de antes.
  - Las piezas de ceniza de PARDA no se pueden mezclar con las termas, el acantilado ni la peña, que son de LAVACALDA. Además, muchas piezas mezclan hierba con otra cosa (bordes del camino, del risco, de las termas…), así que cambiar las piezas una a una dejaría bordes verdes.
  - **Solución:** la playa usa `gTileset_GeneralCeniza` y `gTileset_LavaridgeCeniza`. Son copias de General y LAVACALDA con los mismos dibujos, piezas, comportamientos y animaciones, pero con otras paletas (`data/tilesets/primary/general_ceniza/` y `data/tilesets/secondary/lavaridge_ceniza/`).
  - En esas paletas, los cuatro verdes del suelo y la hierba pasan a los cuatro colores de la ceniza de la RUTA 113. Los verdes de las hojas (árboles y flores) no cambian: en la RUTA 113 los árboles también son verdes.
  - Lo hace `paletas_ceniza()` en `crear_playa_volcanica.py`: escribe las paletas y añade las dos copias a `src/data/tilesets/graphics.h` y `headers.h`.
  - **La unión con la RUTA 122 no cambia:** desde la playa, la parte de la ruta que se ve se pinta con las paletas de la playa, pero allí solo hay mar y rocas, que no usan ninguno de los colores cambiados (comprobado pieza a pieza).
  - `ver_mapa.py` y `ver_mundo.py` ahora usan las paletas de cada tileset (`carpetas_paletas()`), para que las fotos salgan con la ceniza.
  - **Lo que no cambia de color:** las hojitas que salen al pasar por la hierba alta. Son un efecto aparte, con sus propios colores, y siguen verdes.
- **Guardián** en la arena: sin semilla, Slither Wing a nivel 70 (regla `"tope"`); premio, Energía Potenciadora y su megapiedra si tiene. `FLAG_DUALOCKE_GUARDIAN_PLAYA` (0x917).
- **Un bañista junto a las termas.** No hay entrenadores: ya no queda ninguno libre.
- **Zona de captura propia:** `MAPSEC_PLAYA_VOLCANICA` (115 de 128).
- **Salvajes:**
  - Ceniza: Numel, Slugma, Torkoal, Camerupt, Magcargo, Salandit, Krabby, Crabrawler, Dwebble, Sandygast y, raros, Turtonator y Larvesta.
  - Mar: el de las islas del sur. Pesca de cangrejos y Gyarados.
- **Objetos** (`OBJETOS_PLAYA`, flags 0x918-0x91A, y un Ticket-Recuerdo, 0x91C): Piedra Agua, Roca Lluvia y una Perla oculta. Se movieron a mano: el script los ponía todos junto al guardián. Al rehacer el mapa se volvieron a mover tres que habían quedado en el risco, en el mar y en el bajío.

### Islas de las rutas del sur (hecho, Miguel, 17/11/2026; falta probarlo)

Tres islas nuevas del **tramo 8** (cap 84), cada una pegada al borde de una ruta de mar. Se llega surfeando, sin pantalla de carga, y usan los gráficos de su ruta (si no, la conexión se vería rota). Todo lo hace `tools/dualocke/crear_islas_sur.py`.

- **Cambios del 21/11/2026 (Miguel, quinta prueba):** la ISLA DE RUINAS pasa al sur de la RUTA 129 (encima de la 131 no se llegaba) y la ISLA VOLCÁNICA se deja de pegar a la RUTA 134: se va en barca desde PORTUAL. Ver cada una.
- **Paso abierto en la barrera de rocas (17/11/2026):** el borde de cada ruta por el que se entra a su isla estaba fuera de la barrera de rocas del mar, y no se llegaba (lo vio Jorge con `alcance.py`, #99). Se quita una roca suelta de 2 × 2 de la barrera en cada ruta: RUTA 129 (46, 24), RUTA 131 (7, 12) y RUTA 134 (9, 21). **Desde el 21/11/2026** la de la RUTA 134 vuelve a su sitio (la isla ya no está ahí). La de la RUTA 131 se queda: por ese hueco se llega también a la parte norte de las RUTAS 128-131. Es la que deja el paso más corto sin pasar por corrientes y lejos de las conexiones de los lados (`PASOS` y `quitar_rocas()` en `crear_islas_sur.py`). Con `alcance.py`, las tres islas se alcanzan surfeando.
- **Sitios elegidos mirando las corrientes:**
  - Las RUTAS 132-134 tienen sus bordes cerrados por rocas, y sus corrientes solo empujan al oeste: no se llega a los huecos.
  - El borde este de la RUTA 127 es una pared de roca.
  - Por eso dos islas no están donde decía ZONAS.md (ver cada una).
- **Los islotes se copian con `isla()`:** solo las casillas que no son mar y están unidas al islote. Así no se cuelan rocas sueltas, corrientes ni trozos de otras islas.
- **Rehechas el 17/11/2026 con `autotile.py`** (ver "Dibujar mapas como los del juego"). Antes eran trozos de islotes copiados tal cual: la arena de la ISLA DE RUINAS acababa cortada en recto contra el mar, la ISLA VOLCÁNICA era un montículo pegado sobre un bajío cuadrado y la ISLA ARENOSA eran tres islotes de la RUTA 127.
- **ISLA DE RUINAS**, al sur de la RUTA 129, desde su x 20 (hasta el 21/11/2026 estaba al norte de la RUTA 131, junto al PILAR CELESTE, y sus corrientes no dejaban llegar; Miguel no pudo entrar):
  - **Por qué ahí:** todo el borde de abajo de la RUTA 129 es mar abierto y se alcanza en el tramo 8. Encima de la RUTA 130 aparece la ISLA ESPEJISMO (otros gráficos: desde la isla se vería rota), y a la izquierda de la RUTA 128 no se llega (solo se llegaba a través de la isla vieja, que hacía de puente sin querer).
  - **Un templo en ruinas:** el islote del PILAR CELESTE con su torre, con niebla (Campo de Niebla en combate). Se ve desde la ruta y se rodea surfeando hasta una **playa grande** en su cara sur (8 filas de mar arriba dejan sitio para rodearla).
  - De la playa sube una **escalinata de piedra** (antes, una cueva escondida que llevaba al montículo) a un **patio enlosado** con columnas de piedra, donde estaba el montículo; al fondo, la torre.
  - La puerta de la torre, abierta, lleva a la **TORRE**: la planta 1 del PILAR CELESTE, sin la escalera, con el guardián delante. La puerta va **sin colisión** (22/11/2026): es una puerta sin animación, que se cruza al pisarla, y con colisión no se entraba (lo vio el bot de Jorge, #116). `comprobar_zonas.py` lo mira ahora en todos los mapas.
- **ISLA VOLCÁNICA**, al sur de la RUTA 134. **Desde el 21/11/2026 se va en barca desde PORTUAL** (Miguel): ya no está pegada a la ruta, porque así se veía mal el borde de PORTUAL (el puerto aparecía y desaparecía) y se entraba desde toda la ruta.
  - Un marinero al final del muelle de abajo de PORTUAL (37, 40), encima del otro marinero, lleva a la isla desde la 7.ª medalla (el tramo de la isla); antes dice que el mar está muy bravo. En la playa de abajo de la isla, junto a la barca, el mismo marinero trae de vuelta. `alcance.py` conoce el viaje (`VIAJES`), y desde el 22/11/2026 solo lo da por bueno si se llega a la casilla desde la que se habla al marinero. Antes estaba en (38, 34), en la punta de un trozo de muelle que no está unido a la ciudad: no se llegaba (lo vio el bot de Jorge, #116).
  - Una isla de arena con su anillo de bajío, tres peñas de la RUTA 127, rocas en el mar y, en medio, el montículo del PILAR CELESTE (con la cima de una peña: la suya tenía la sombra de la torre). Sol.
  - Su cueva baja al **CRÁTER**: la cima del MONTE CENIZO (lago de lava y terrazas, sin la estación del teleférico). Tiene manchas de ceniza con salvajes y una salida nueva: la entrada de la GUARIDA MAGMA del CAMINO ESCABROSO, puesta en un escalón.
- **ISLA ARENOSA**, al este de la RUTA 129 (en ZONAS.md, al este de la RUTA 127):
  - Una isla grande de arena con cinco peñas y una cala al sur. Al oeste, un islote de hierba con árboles, flores y hierba alta (la de los salvajes), con orilla de mar: se llega surfeando. Tormenta de arena.
  - Se llega desde la izquierda: primero se pasa junto al islote y, al llegar a la isla, espera DARÍO (mira a la izquierda). El guardián está en la punta del sur.
  - Ninguna peña deja hacer bases secretas: el hueco se tapa.
- **Guardianes** (el sistema de las islas del ferry, regla `"tope"`: nivel 81), sin semilla:
  - Metagross en la TORRE (premio: Cinta Experto). `FLAG_DUALOCKE_GUARDIAN_ISLA_RUINAS` (0x909).
  - Charizard en el CRÁTER (Roca Calor). `FLAG_DUALOCKE_GUARDIAN_VOLCAN` (0x90A).
  - Sandy Shocks en la ISLA ARENOSA (Roca Suave). `FLAG_DUALOCKE_GUARDIAN_ARENOSA` (0x90B). Era Tyranitar: se cambió para que no se repitiera (ver "Guardianes únicos").
  - Con semilla salen otros fuertes (`islas()` de `estaticos.py`). Cada uno da también su megapiedra.
- **Zonas de captura propias (3):** `MAPSEC_ISLA_DE_RUINAS`, `MAPSEC_ISLA_VOLCANICA` y `MAPSEC_ISLA_ARENOSA` (cada isla con su interior cuenta como una). Se usan 114 de 128.
- **Entrenadores:** solo DARÍO, entrenador guay de la ISLA ARENOSA (Krookodile, Hippowdon y Flygon). Es `TRAINER_RED`, el último entrenador de Esmeralda sin usar. **Ya no queda ninguno libre:** para poner más habría que agrandar la lista (y eso mueve los flags del sistema y rompe las partidas guardadas) o reutilizar otros.
- **Salvajes:**
  - Mar: pesca y surf en las tres islas.
  - TORRE: POKéMON de ruinas (Bronzong, Golurk, Sigilyph, Beheeyem, Claydol…; raros, Metang y Zweilous).
  - CRÁTER: de fuego (Magcargo, Camerupt, Torkoal, Magmortar, Salazzle, Coalossal…; raros, Volcarona y Larvesta).
  - ISLA ARENOSA: de tierra y arena (Sandslash, Krookodile, Hippowdon, Flygon…; raros, Gabite y Pupitar).
- **Objetos** (`OBJETOS_ISLAS_SUR`, flags 0x90C-0x912, y un Ticket-Recuerdo por isla, 0x914-0x916): Gafas Especiales, Más PP, Llamasfera, Piedra Fuego, Perla Grande, Gafa Protectora y Sarta de Perlas. Se movieron a mano los que el script ponía delante de DARÍO o juntos.

### BOSQUE FRONDOSO y MANSIÓN OLVIDADA (hecho, Miguel, 17/11/2026; falta probarlo)

- **Dónde:** en el claro del noreste del BOSQUE PETALIA se abre un pasillo entre los árboles, tapado por dos árboles de CORTE (`FLAG_TEMP_13` y `_14`). Lleva al BOSQUE FRONDOSO por el borde, sin pantalla de carga. Hace falta CORTE: **tramo 2** (cap 23).
- **BOSQUE FRONDOSO** (36 × 40), con los gráficos del BOSQUE PETALIA:
  - arriba, en un patio con verja y farolas, la mansión (el edificio largo de CIUDAD FÉRRICA) y su cartel;
  - **rehecho el 17/11/2026 mirando el BOSQUE PETALIA:** franjas y grupos de árboles de distinto alto, árboles sueltos, manchas de hierba alta de borde irregular, claros sin hierba, flores y una charca para pescar;
  - **el camino da la vuelta:** de la entrada se va al oeste (pasando junto a la charca), se sube por un paso entre los árboles y se rodea por el este un **risco** del BOSQUE PETALIA (de un solo sentido). Después, por otro paso, se llega al patio de la mansión. De vuelta se puede saltar el risco.
  - El mapa se dibuja en `tools/dualocke/crear_bosque_frondoso.py` con letras, una por casilla (`PLANO`), y lo pinta `autotile.py`, como la MARISMA AZULIZA. Las únicas parejas de piezas que no salen en el juego (42) están en el borde de la mansión copiada.
  - El cartel de la mansión ahora se puede leer: antes tenía un árbol debajo. La unión con el BOSQUE PETALIA también se arregló: a la derecha del pasillo había hierba encima de un árbol del BOSQUE PETALIA.
- **MANSIÓN OLVIDADA:** las cuatro salas del BARCO ABANDONADO, que con la madera y las camas parecen una casa vieja.
  - Sin los salvavidas y con un paso nuevo a la sala de arriba a la izquierda.
  - La puerta de esa sala está atascada (cartel). La de la derecha sube al **DESVÁN**: dos salas de la planta oculta del barco.
  - El suelo de madera de ese barco tiene salvajes (`MB_INDOOR_ENCOUNTER`), aunque en el juego original no los usa: aquí salen fantasmas.
- **Guardián del DESVÁN:** delante de una puerta rota. Sin semilla es Gengar a nivel 20 (cap − 3, regla `"tope"`); premio, Hechizo y su megapiedra. `FLAG_DUALOCKE_GUARDIAN_MANSION` (0x863).
- **Zonas de captura propias (2):** `MAPSEC_BOSQUE_FRONDOSO` y `MAPSEC_MANSION_OLVIDADA` (las dos plantas). `HOENN_EXTRA_MAPSEC_LAST` pasa a ser la de la mansión: 111 de 128.
- **Entrenadores (4), a nivel 19-20:**
  - Bosque: SEBAS, cazabichos (`TRAINER_SEBAS`, 863: Dustox y Ninjask) y OLIVIA, campista (Nuzleaf y Skiploom).
  - Mansión: ELVIRA, bruja (Shuppet, Duskull y Misdreavus) y ALFONSO, caballero (Drifloon y Litwick).
  - **Ya no quedan huecos de entrenador** (864 de 864). OLIVIA, ELVIRA y ALFONSO son `TRAINER_BRENDAN_PLACEHOLDER`, `TRAINER_MAY_PLACEHOLDER` y `TRAINER_LEAF`, que existían sin usar en Esmeralda. `zonas_nuevas.py` reescribe su bloque entero y `reescalar_niveles.py` los trata como los de las islas (`ENTRENADORES_ISLAS`). Queda `TRAINER_RED` (851) sin usar; para más habrá que reutilizar otros.
- **Salvajes:**
  - Bosque: Sewaddle, Nincada, Seedot, Skwovet, Pikipek, Pineco, Fomantis, Cutiefly, Morelull, Petilil y, raros, Scyther y Heracross.
  - Charca: Magikarp, Goldeen, Poliwag, Psyduck, Lotad, Marill y, muy raro con la SUPERCAÑA, Dratini.
  - Mansión: Gastly, Shuppet, Duskull, Misdreavus, Litwick, Phantump, Pumpkaboo, Sinistea, Greavard, Drifloon y, raros, Rotom y Dreepy.
- **Objetos** (`OBJETOS_BOSQUE`, flags 0x900-0x904, y un Ticket-Recuerdo, 0x908): Polvo Plata y Raíz Grande (oculta) en el bosque, Tela Terrible y Amuleto en la mansión, Piedra Noche en el desván.

### MARISMA AZULIZA (hecho, Miguel, 17/11/2026; falta probarlo)

- **Arreglo del 18/11/2026** (Miguel jugando):
  - La marisma va a la altura de AZULIZA (`DESPLAZAMIENTO_AZULIZA` 0). Antes sobresalía 7 filas por encima, donde está la RUTA 106, y desde el pueblo se veía un muro de árboles sobre la playa.
  - Sin hierba muy alta: con los gráficos de AZULIZA no tiene borde de abajo.
  - Sin la charquita de 2 × 2 de abajo.

- **Dónde:** al oeste de PUEBLO AZULIZA, pegada al pueblo (conexión por el borde, sin pantalla de carga). Se llega andando por la arena del oeste del pueblo: **tramo 2** (cap 23).
- **El mapa** (48 × 34), con los gráficos de AZULIZA (General + Dewford). **Rehecho el 17/11/2026** con `autotile.py` (ver arriba). Siempre **llueve**.
  - **Este, la playa de AZULIZA:** arena con grupos de árboles del pueblo, una charca de marea y el cartel a la entrada.
  - **Un risco** separa la arena de la pradera, más alta, con una escalera (x 29-30, fila 13).
  - **Centro, la pradera:** manchas de hierba alta y de hierba muy alta, sitios sin hierba, flores, árboles grandes sueltos y en grupo y una charca pequeña.
  - **Oeste, el lago** (pesca y surf) y, detrás, **una cala que solo se alcanza con SURF**.
  - Rocas para GOLPE ROCA (Geodude, Nosepass, Roggenrola, Binacle).
- **La cala (con SURF, tramo 6):** Dondozo y Tatsugiri, cada uno con su flag (`FLAG_DUALOCKE_MARISMA_DONDOZO` 0x1E2 y `FLAG_DUALOCKE_MARISMA_TATSUGIRI` 0x1E3) y su premio: Casco Dentado y Agua Mística. A nivel 59 (regla `("tope", 6)`). Con semilla, otros fuertes. La Semilla Milagro también está en la cala.
- **Todo lo hace `tools/dualocke/crear_marisma_azuliza.py`.** El mapa va al final del grupo de AZULIZA y de `layouts.json`.
- **Zona de captura propia:** `MAPSEC_MARISMA_AZULIZA`, al final de la lista. `HOENN_EXTRA_MAPSEC_LAST` pasa a ser esa: 109 bits.
  - Se ha añadido una variable de zonas, `VAR_DUALOCKE_ZONES_7` (era `VAR_UNUSED_0x40FE`, sin usar): ahora caben 128 zonas.
  - En las partidas guardadas vale 0, así que no se pierde nada.
- **Entrenadores (2, nuevos), a nivel 19-20:**
  - TOMÁS, pescador (`TRAINER_TOMAS`, 861): Barboach y Lotad.
  - MARGARITA, dama aroma (`TRAINER_MARGARITA`, 862): Shroomish y Paras.
  - `TRAINERS_COUNT_EMERALD` pasa a 863: queda 1 hueco.
- **Salvajes:**
  - Hierba: Wooper, Lotad, Surskit, Yanma, Tympole, Shroomish, Croagunk, Paras, Shellos, Stunfisk, Dewpider y, raro, Goomy.
  - Pesca en las charcas con la CAÑA VIEJA (la dan en AZULIZA): Barboach, Poliwag, Goldeen, Wishiwashi, Tympole, Chewtle, Basculin…
  - Surf, para cuando se vuelva: Surskit, Lotad, Wooper, Poliwag y Chewtle.
- **Objetos:** Semilla Milagro (`FLAG_ITEM_MARISMA_MIRACLE_SEED`, 0x88F, en la cala) y un Ticket-Recuerdo (`FLAG_ITEM_TICKET_MARISMA_AZULIZA`, 0x8E3, en la hierba muy alta del norte).

### DESIERTO PROFUNDO y RUINAS ARENOSAS (hecho, Miguel, 16/11/2026; falta probarlo)

`ZONAS.md`, propuesta 5, y las ruinas que pidió Miguel ("el desierto profundo y unas ruinas").

- **Entrada:** un montículo con puerta en la parte este del desierto de la RUTA 111, como el de las RUINAS DESIERTO.
  - Se llega con las GAFAS AISLANTES: **tramo 5** (cap 50).
  - Es una puerta y no una conexión por el borde, porque todo el borde este del desierto es roca.
- **DESIERTO PROFUNDO** (24 × 68): el desierto de la RUTA 111 sin la TORRE ESPEJISMO ni los huecos de base secreta, con **tormenta de arena** (también en combate).
  - Abajo está la salida.
  - En el norte, otro montículo lleva a las ruinas.
  - **Rehecho el 21/11/2026 (Miguel: era el mismo dibujo que el desierto y se avanzaba igual): dunas y arenas movedizas.**
    - Todo es arena clara, y una fila de peñas corta el paso al norte: a las ruinas no se llega andando.
    - Hay cuatro **arenas movedizas**, los únicos hoyos de arena honda (3 × 3): al pisar el centro, "¡La arena se hunde! ¡Es arena movediza!" y caes a la **CUEVA** de abajo, cada una a una sala.
    - La **CUEVA** (`DesiertoProfundo_Cueva`, 40 × 23) es un trozo del PASO DESIERTO (la cueva de arena del juego) partido en tres salas con rocas. Las otras dos salas tienen una escalera que devuelve a la entrada del desierto. La sala buena tiene dos: una sale al norte, por la puerta de un montículo junto a las ruinas, y la otra vuelve a la entrada. El script comprueba que las salas no se tocan.
    - **Vuelta del norte (22/11/2026; lo vio el bot de Jorge, #116):** antes la escalera buena te dejaba en la arena del norte y no se podía volver a bajar. Sin VUELO (tramo 5) era una trampa. Ahora en el norte se sale por la puerta de un montículo (`MONTICULO_NORTE`, puerta en (6, 16)), que es de ida y vuelta con la escalera buena, y la sala buena tiene una segunda escalera, en (33, 14), a la entrada.
    - SOLEDAD da la pista después del combate. `alcance.py` conoce la caída (`VIAJES`).
- **RUINAS ARENOSAS:** las cuatro plantas de la TORRE ESPEJISMO (17/11/2026; antes eran dos).
  - **Entrada:** un pasillo alrededor de un bloque central.
  - **Plantas 2 y 3: interruptores** (desde el 21/11/2026, Miguel; antes, suelo agrietado como en la torre). Dos puertas de piedra cierran el paso a la escalera siguiente por los dos lados del pasillo, y el interruptor (una losa morada en el suelo) está en la otra punta: hay que dar la vuelta. Al pisarlo, "¡Clac! Algo de piedra se ha movido en esta planta", y las puertas se abren y se quedan abiertas (`FLAG_DUALOCKE_RUINAS_2F_ABIERTA` 0x913 y `FLAG_DUALOCKE_RUINAS_3F_ABIERTA` 0x91B). Ya no hay suelo agrietado ni rocas de GOLPE ROCA.
  - **CÁMARA:** arriba del todo.
  - **Guardián:** en la CÁMARA hay un Pokémon fuerte que se puede capturar, como en las islas del ferry (`dualocke_islas.inc`). Sin semilla es Garchomp a nivel 47 (cap − 3, regla `"tope"`); con semilla, otro fuerte (`islas()` en `estaticos.py`).
  - **Premio:** Cascabel Concha y su megapiedra si tiene. Flag `FLAG_DUALOCKE_GUARDIAN_RUINAS` (0x886).
- **Zonas de captura propias (2):** `MAPSEC_DESIERTO_PROFUNDO` y `MAPSEC_RUINAS_ARENOSAS`, al final de la lista. `HOENN_EXTRA_MAPSEC_LAST` pasa a ser la de las ruinas: 108 de 112 bits.
- **Todo lo hace `tools/dualocke/crear_desierto_profundo.py`.** Los tres mapas van al final de `gMapGroup_Dungeons`.
- **Entrenadores (2, nuevos):**
  - SOLEDAD, experta del desierto (`TRAINER_SOLEDAD`, 860): Flygon, Hippowdon y Cacturne.
  - RAMIRO, ruinamaníaco de las ruinas (`TRAINER_RAMIRO`, 859): Claydol y Golurk.
  - Los dos a nivel 46-47. `TRAINERS_COUNT_EMERALD` pasa a 861: quedan 3 huecos.
- **Salvajes:**
  - Desierto: Trapinch, Sandshrew, Cacnea, Hippopotas, Sandile, Silicobra, Helioptile, Skorupi, Maractus, Baltoy y, raros, Larvitar y Gible.
  - Ruinas: Baltoy, Yamask, Golett, Bronzor, Sigilyph, Runerigus, Elgyem, Claydol, Spiritomb, Archen…
- **Objetos:** Arena Fina y Trozo Estrella en el desierto, Hueso Raro y Piedra Espíritu en las ruinas (`OBJETOS_DESIERTO`, flags 0x8F0-0x8F3).

### ISLA NEVADA (hecho, Miguel, 16/11/2026; falta probarlo)

`ZONAS.md`, propuesta 1. Una isla al norte de la RUTA 124 con nieve y una cueva de hielo.

- **Cómo se llega:** surfeando hacia el norte desde la RUTA 124, sin pantalla de carga (conexión `up`). **Tramo 7** (cap 73).
  - **Paso abierto (17/11/2026):** las filas 0-14 de la RUTA 124 estaban fuera de la barrera de rocas, y a la isla solo se llegaba buceando. Se quitan dos rocas con remolino, en (11, 0) y (18, 16) (`PASOS_RUTA124` en `crear_isla_nevada.py`). Con `alcance.py`, se alcanza surfeando en el tramo 7.
- **La isla** (80 × 40). **Rehecha el 17/11/2026 con `autotile.py`**, como las islas del sur (ver "Dibujar mapas como los del juego"). Antes era el islote de la CUEVA CARDUMEN de la RUTA 125 pegado arriba, cortado por el borde del mapa, con mucho mar vacío.
  - Ahora es una isla grande de arena con su anillo de bajío y una cala al sur, peñas y rocas en el mar.
  - Arriba está la cresta de roca del islote grande de la RUTA 127, sin sus huecos de base secreta. En su pie se abre la entrada de la cueva, con las piezas de la cueva del PILAR CELESTE.
  - Lo hace `crear_isla_nevada.py` con `dibujar()` y `sello()` de `crear_islas_sur.py`.
  - Usa los mismos gráficos que la RUTA 124, para que la conexión se vea bien.
  - Clima `WEATHER_SNOW`: **nieve en combate**. Esmeralda no tiene suelo nevado para fuera, así que la nieve es la que cae.
- **Guardián de la CUEVA HELADA (17/11/2026):** al fondo de la cueva, donde estaba la Piedra Hielo (que pasa junto al Hielo Perpetuo).
  - Sin semilla es Baxcalibur a nivel 70; premio, Garra Afilada y su megapiedra.
  - `FLAG_DUALOCKE_GUARDIAN_NEVADA` (0x88E).
- **La CUEVA HELADA** (20 × 30): la entrada del islote lleva a ella. Es la sala de hielo de la CUEVA CARDUMEN (suelo resbaladizo, rocas para frenar), con otros entrenadores y objetos. Se podría rediseñar con Porymap.
- **Zona de captura propia:** `MAPSEC_ISLA_NEVADA` (la isla y la cueva cuentan como una), al final de la lista. `HOENN_EXTRA_MAPSEC_LAST` pasa a ser esa: 106 de 112 bits.
- **Todo lo hace `tools/dualocke/crear_isla_nevada.py`.** La isla va al final del grupo de las rutas y la cueva al de las mazmorras: ningún mapa cambia de número.
- **Entrenadores (3):**
  - DUDLEY y KAYLEE, nadadores que existían sin usar, en el mar al sur de la isla, por donde se llega. Los reescala `reescalar_niveles.py` (65-67).
  - NIEVES, entrenadora guay nueva en la cueva (`TRAINER_NIEVES`, 858; `TRAINERS_COUNT_EMERALD` 859). Lleva Froslass, Abomasnow y Walrein a nivel 69-70 (`zonas_nuevas.py`).
- **Salvajes:**
  - Agua y pesca: Spheal, Seel, Delibird, Arctovish, Cloyster, Lapras…
  - Cueva: Snorunt, Swinub, Snover, Cubchoo, Vanillite, Snom, Bergmite, Sneasel, Cetoddle, Cryogonal, Eiscue y, raro, Frigibax.
- **Objetos:** Hielo Perpetuo y Piedra Hielo en la cueva, y una Bola de Nieve oculta en la punta oeste de la isla (`OBJETOS_NEVADA`, flags 0x8FA-0x8FC). Después de colocarlos se movieron a mano a sitios que no tapan el pasillo. Los de fuera los pone `crear_isla_nevada.py` en su sitio (`SITIOS`).

### GRUTA ÍGNEA (hecho, Miguel, 16/11/2026; falta probarlo)

La primera zona nueva de verdad (`ZONAS.md`, propuesta 7, "SENDERO ÍGNEO profundo"). El nombre es el que usó Miguel: "mejorar la gruta ígnea".

- **CÁMARA DEL MAGMA (17/11/2026):** la salida del sur de la gruta baja a una sala en terrazas con dos pozas de lava (la sala 3 de la planta 3 de la GUARIDA MAGMA, sin su máquina y con la puerta de arriba tapiada).
  - **Guardián arriba del todo:** sin semilla, Houndoom a nivel 47; premio, Periscopio y su megapiedra.
  - Usa el mismo sistema que las islas del ferry (`FLAG_DUALOCKE_GUARDIAN_GRUTA`, 0x887).
  - Cuenta como la misma zona de captura que la gruta.
- **Dónde:** una boca de cueva en la sala del suroeste del SENDERO ÍGNEO, la de detrás de las rocas. Hace falta FUERZA, que se usa con la 4.ª medalla, así que es del **tramo 5** (cap 50), que antes no tenía casi nada.
- **El mapa** (59 × 28): es la planta 4 de la GUARIDA MAGMA sin las máquinas del Equipo Magma, que comparte gráficos con el SENDERO ÍGNEO. Es un recorrido largo alrededor de un lago de lava, que no se puede cruzar.
  - Lo hace `tools/dualocke/crear_gruta_ignea.py`: cada casilla de máquina pasa a ser el suelo de cueva de al lado y se tapa la salida hacia la guarida.
  - Clima `WEATHER_DROUGHT`: **sol en combate**. Música de la CUEVA ANCESTRAL.
- **Zona de captura propia:** `MAPSEC_GRUTA_IGNEA`, al final de `region_map_sections.json`.
  - `HOENN_EXTRA_MAPSEC_LAST` (`src/dualocke.c`) pasa a ser esa: se usan 105 de los 112 bits y los de antes no se mueven.
  - Las zonas nuevas siguientes van detrás y se cambia esa línea.
  - Cartel de zona: piedra, y negro en el estilo Blanco/Negro (`src/map_name_popup.c`).
- **El mapa nuevo va al final** de `layouts.json` y del grupo `gMapGroup_Dungeons`: no cambia el número de ningún mapa de las partidas guardadas.
- **Entrenadores (3):**
  - ÍGOR (fogonero) y ROQUE (montañero): `TRAINER_IGOR` y `TRAINER_ROQUE`, dos de los 8 huecos que quedaban (`TRAINERS_COUNT_EMERALD` pasa a 858). Sus equipos los escribe `zonas_nuevas.py` (`NUEVOS`), al nivel de los más fuertes del tramo (46-47).
  - Una soldado del Equipo Magma: `TRAINER_GRUNT_UNUSED`, que existía sin usar (con los gráficos del Equipo Aqua: `zonas_nuevas.py` se los cambia). La reescala `reescalar_niveles.py`.
- **Salvajes:** de fuego y de roca de todas las generaciones (Slugma, Salandit, Sizzlipede, Rolycoly, Litwick, Heatmor, Charcadet, Turtonator, Larvesta…), en `zonas_nuevas.py`.
- **Objetos:** Piedra Fuego, Magmatizador, Carbón y Galleta Lava (`OBJETOS_GRUTA` en `colocar_objetos.py`, flags del 0x8F6 al 0x8F9).

### Recuerdamovimientos y Ticket-Recuerdo (hecho, Miguel, 26/10/2026)

Lo pidió Miguel: poder recuperar los movimientos que un Pokémon ha podido aprender durante la aventura, pagando con tickets que se encuentran por el mapa.

- **En todos los Centros Pokémon de Hoenn** (los 16) hay una señora a la derecha del PC, en la casilla (13, 2), que hace que un Pokémon recuerde un movimiento.
  - Enseña los movimientos **de nivel** que el Pokémon ya podría saber por su nivel (los mismos que el tutor de Pueblo Pardal). Se puede elegir un Pokémon del equipo o de las cajas.
  - Cobra **un Ticket-Recuerdo por movimiento**, y solo si lo aprende: si cancelas, no se gasta.
  - Script: `data/scripts/dualocke_recuerda_movimientos.inc` (`Dualocke_EventScript_RecuerdaMovimientos`). Los PNJ están en el `map.json` de cada `*_PokemonCenter_1F`.
- **El Ticket-Recuerdo es la Escama Corazón** (`ITEM_HEART_SCALE`) con otro nombre, otra descripción y el icono del Ticket del Barco. Así el tutor de Pueblo Pardal, que ya cobraba con la escama, también lo pide (sus textos dicen TICKET-RECUERDO).
- **Dónde están:** 45 por el mapa.
  - **Uno en bola en cada ruta**, de la 101 a la 134.
  - **Otro oculto** en las rutas largas: 104, 110, 111, 113, 114, 117, 118, 119, 120, 121 y 123.
  - Además siguen las Escamas Corazón ocultas del juego original (rutas 104, 105, 106, 109, 115, 118, 128, Calagua y bajo el agua de la 124), que ahora son tickets. Con el randomizer esas sí cambian por otros objetos.
  - Los coloca `tools/dualocke/colocar_objetos.py` (tablas `TICKETS` y `TICKETS_OCULTOS`). Flags `FLAG_ITEM_TICKET_RUTA_...`: **0x021-0x042** los de bola y **0x4E5-0x4EF** los ocultos, porque los ocultos necesitan un flag por encima de `FLAG_HIDDEN_ITEMS_START`.
  - El script busca primero suelo firme. En 7 rutas de mar abierto (107, 108, 126, 128, 129, 130 y 131) no hay playa cerca y el ticket está en el agua: se coge haciendo Surf, como se habla con los nadadores.
  - **El randomizer no los toca** (`FIJOS` en `tools/dualocke/aleatorio/objetos.py`), como las megapiedras.
- **Se ha quitado el recordador gratis de la pantalla de datos** (`P_SUMMARY_SCREEN_MOVE_RELEARNER` a `FALSE` en `include/config/summary_screen.h`): si no, los tickets no servirían de nada.

## 7. Randomizer (hecho, falta probarlo jugando)

### Diseño

- **Script propio** (Python) que baraja los datos del juego **antes de compilar**, usando una **semilla**.
- **Cada jugador tiene una partida completamente distinta**: `make` se inventa una semilla al azar la primera vez y la guarda (decidido por Jorge el 25/10/2026: la semilla no se elige, es aleatoria). Cómo se usa: sección 3, "Partida randomizada".
- **Cómo está hecho (Jorge):** `tools/dualocke/randomizer.py`, con los módulos en `tools/dualocke/aleatorio/`. Lo lanza el `Makefile` (bloque "Dualocke: randomizer con semilla"). Lee los originales (`wild_encounters.json`, y más adelante `trainers.party`…) y escribe las versiones barajadas en `build/dualocke/`, que son las que se compilan. **Los archivos de Miguel no se tocan.** Los datos de las especies (evoluciones, formas, legendarios) salen de pasar `src/pokemon.c` por el preprocesador de C, así que son exactamente los de la ROM. Comprueba el resultado antes de compilar (solo cambian las especies, no hay legendarios en los salvajes…) y para si algo falla.
- **Hecho:** salvajes, entrenadores (con movimientos y objetos de los jefes), iniciales, rival, estáticos, regalos, objetos del suelo, Recogida, objetos de los salvajes, intercambios, habilidades, MT, tutores y movimientos por nivel.
- **Lo que no se puede barajar sin tocar mapas y scripts se cambia al vuelo:** el `Makefile` genera `src/data/dualocke_aleatorio.h` con las tablas de la semilla (vacías sin semilla) y `src/dualocke_aleatorio.c` las consulta: estáticos, regalos, objetos del suelo (por su flag), Recogida, objetos de los salvajes, intercambios, habilidades y MT. Enganches: `item_ball.c`, `field_control_avatar.c` (ocultos), `battle_script_commands.c` (Recogida), `pokemon.c` (`SetWildMonHeldItem`, `GetSpeciesAbility`, `CanLearnTeachableMove`, `GetSpeciesLevelUpLearnset`), `trade.c`, `include/item.h` (qué enseña cada MT), `party_menu.c` y la macro `move_tutor` (`asm/macros/event.inc`).
- `build/dualocke/solucionario.json` tiene todo lo que ha salido (no abrir si no quieres destriparte la partida).
- Para no destriparse nada: o cada uno compila la suya, o uno compila las dos sin mirar los archivos generados.
- Alternativa descartada por ahora: randomizer dentro del juego, al empezar partida (como Heart & Soul). Es más trabajo.

### Parámetros de equilibrio (decididos por Miguel, 23/10/2026)

Están en **`tools/dualocke/randomizer_config.json`**, que es el archivo que debe leer la herramienta de Jorge. Si necesita otro formato, se cambia hablándolo. Lo nuevo respecto al preset de Platino:

- **Legendarios** = legendarios y singulares (`isLegendary` / `isMythical` de la especie base). Ultraentes y paradójicos cuentan como Pokémon normales. Los legendarios solo pueden salir como estáticos y en los jefes de la Liga.
- **Iniciales:** forma base de una línea de 3 fases, sin legendarios, y los tres forman un **triángulo de tipos**: A gana a B, B gana a C y C gana a A. Por ejemplo, Fuego/Planta/Agua o Roca/Volador/Lucha. El rival lleva el que gana al del jugador.
- **Salvajes según el nivel:** la especie es libre, pero se ajusta a la fase que le toca por el nivel de la zona, con las mismas reglas que los entrenadores (por nivel a su nivel normal; piedra, amistad… a 30 y 40). Se evita repetir especies entre zonas mientras queden.
- **Jefes e importantes:** el equipo es **totalmente aleatorio**, pero **el as es de su tipo o temática** (Petra Roca, Magno Fuego/Tierra, Aquiles Agua/Siniestro, Blasco Psíquico/Hada…). Desde el aro, ese as es una **especie con mega de su tipo** y lleva su megapiedra. Hay megas de sobra para cada tipo: hasta Roca tiene 4 sin contar legendarios.
- **Rival:** su as es su inicial. Si la línea de su inicial no tiene mega, desde el aro lleva además, como as, una mega del mismo tipo.
- **Respetar lo que ya está hecho a mano:** niveles, tamaño de los equipos y la regla de evolucionar según el nivel.

### Ajustes a replicar (los del preset de Platino, adaptados)

**Pokémon**
- Iniciales aleatorios (forma base de 3 fases y en triángulo de tipos, ver arriba). **Hecho** (`tools/dualocke/aleatorio/iniciales.py`): además, las dos evoluciones tienen que ser por nivel o con objeto, para poder hacerlas en el juego. Salen en `src/data/dualocke_iniciales.h` (generado; lo usa `src/starter_choose.c`).
- Habilidades aleatorias, permitiendo Superguarda. **Hecho** (`tools/dualocke/aleatorio/habilidades.py`). Por especie: todos los Zigzagoon tienen las mismas, también los del jugador. Ninguna prohibida, tampoco en los jefes. Solo se quitan las que dependen de una especie y el juego no deja cambiar (Cambio Táctico, Multitipo, Disfraz…: `cantBeOverwritten`).
  - **Tantas como en el juego original, y distintas (Miguel, 18/11/2026; antes, desde el #27, era una sola en todos los huecos).** Si la especie tenía dos normales y una oculta, tiene tres al azar en esos huecos; si tenía una normal y la oculta, dos; si solo una, una. Así sirven la Cápsula (cambia entre las normales) y el Parche (pasa a la oculta). Lo comprueba el randomizer: con las dos semillas, las 1571 especies tienen los mismos huecos vacíos y repetidos que en el original.
  - **Las semillas en curso no cambian en nada más:** la habilidad del primer hueco es la misma que salía antes, y las otras se sortean con su propio RNG (`{semilla}|habilidades|huecos`). En la partida, los Pokémon que tenían el hueco 1 o el oculto pasan a tener su habilidad nueva; los del hueco 0 se quedan con la suya.
  - En el juego: `sDualockeHabilidades[NUM_SPECIES][3]` (generada) y `Dualocke_HabilidadAleatoria(especie, hueco)`, que usa `GetSpeciesAbility`. La pantalla de datos (START) ya enseñaba todas las de la especie.
  - **Parche Habilidad** (arreglo, Jorge, 18/11/2026; lo vio Miguel jugando): si no cambia la habilidad, dice "No tendría efecto" y no se gasta. La Cápsula Habilidad ya lo hacía.
  - **Sin habilidades de relleno** (arreglado el 27/10/2026, Jorge): `ABILITY_314`, `ABILITY_317` y Guardia Aura no hacen nada y ya no salen. Si el sorteo cae en una, solo esa especie se vuelve a sortear, así que las semillas en curso no cambian en nada más.
- Pokémon estáticos completamente aleatorios. **Hecho** (`tools/dualocke/aleatorio/estaticos.py`; decidido por Jorge el 25/10/2026):
  - **Estáticos** (`setwildbattle`: Kecleon, Voltorb, Electrode, Regis, Groudon, Kyogre, Rayquaza, Sudowoodo; y los errantes Latios/Latias): **todo al azar**, legendarios incluidos, a su nivel. Cada especie original cambia por la misma en todos sus sitios (todos los Kecleon del Detector son la misma especie nueva).
  - **Regalos** (Beldum, fósiles, Castform, iniciales de Johto) **y huevos** (Wynaut, Pichu): al azar, sin legendarios, a su nivel; los huevos, siempre la forma base.
  - **Fósiles de otras generaciones** (arreglo, Jorge, 18/11/2026; lo vio Miguel jugando): el randomizer de objetos del suelo reparte todos los fósiles (Fósil Pluma, Fósil Coraza, Ámbar Viejo, los de Galar…), pero el INVESTIGADOR de DEVON solo sabía revivir el Raíz y el Garra.
    - Ahora revive cualquiera, a nivel 20: `data/scripts/dualocke_fosiles.inc`, con la tabla de fósiles y su POKéMON en `src/data/dualocke_fosiles.h`.
    - Con semilla sale otro al azar, como los demás regalos: si es repetido o legendario, va a VETADOS. Se sortean aparte (`fosiles()` en `aleatorio/estaticos.py`, con su propio generador), así que los regalos de antes no cambian.
    - Los de Galar, que en los juegos de verdad se juntan de dos en dos, aquí reviven uno cada uno.
  - El **sprite del mapa** y los **textos** siguen siendo los del original ("Has recibido un BELDUM"): se descubre al combatir o al recibirlo (decidido por Jorge: da igual). El mensaje de "enviado al PC" sí nombra al nuevo.
  - No se tocan los scripts: `src/dualocke_aleatorio.c` cambia la especie al vuelo en `setwildbattle`, `givemon`, `giveegg` y los errantes, con la tabla generada `src/data/dualocke_aleatorio.h` (vacía sin semilla).
- Estadísticas base de Gen 9 (ya vienen así en el motor) sin aleatorizar sus valores.
- ~~Totales de estadísticas base barajados siguiendo las líneas evolutivas.~~ **No se hace** (Miguel, #27).
- Pokémon de los entrenadores aleatorios, sin duplicados dentro de un mismo equipo.
- El inicial del rival se mantiene durante toda la aventura. **Hecho:** lleva el que gana al del jugador, evolucionado según el nivel; el resto de su equipo es al azar y el mismo en todos sus combates. Desde Calagua su as lleva mega: su inicial si tiene, y si no, una especie con mega del tipo de su inicial (y el inicial pasa al hueco anterior).
- Los equipos de los entrenadores evolucionan según el nivel y pueden usar formas alternativas.
- +1 Pokémon a los entrenadores importantes y +2 a los jefes.
- Los Pokémon de entrenadores importantes y jefes pueden llevar objetos aleatorios, priorizando objetos coherentes. **Hecho** (Miguel, #27: "un objeto que le sirva", a todo el equipo): Mineral Evolutivo si puede evolucionar; si no, según sus estadísticas y movimientos (Vidasfera, Cinta Experto, Banda/Gafas/Pañuelo Elección si todos sus movimientos son de daño, potenciador del tipo de su mejor ataque, Restos/Lodo Negro, Baya Zidra, Casco Dentado, Chaleco Asalto, Banda Aguante si es rápido…), sin repetir dentro del equipo si se puede. La megapiedra del as se queda. Son jefes los de `as_por_tipo` (y sus revanchas), el Alto Mando, Plubio y el rival.
  - **Mineral Evolutivo: como mucho uno por equipo** (Miguel, 11/11/2026). Antes lo llevaba todo el equipo que pudiera evolucionar; los demás llevan ahora otro objeto según sus estadísticas.
  - **Hasta el gimnasio 3, objetos de punto medio** (`objeto_suave`; Miguel, 11/11/2026). Afecta a los de `lideres.limite_salvajes`: PETRA, MARCIAL, ERICO, el rival hasta la Ruta 110 y BLASCO en Malvalona.
    - **Sí:** Baya Zidra, bayas que suben una estadística (Lichi, Yapati, Aslac, Gonlan y Albina), Cinta Fuerte o Gafas Especiales según ataque, Pañuelo Elección si es rápido y todos sus movimientos son de daño, y el potenciador del tipo de su mejor ataque.
    - **No:** Mineral Evolutivo, Vidasfera, Cinta Elección, Gafas Elección ni Cinta Experto.
- **Nuevo:** el as de cada jefe es de su tipo y, desde el aro, una especie con mega de ese tipo con su megapiedra (ver arriba).

**Salvajes** (hecho, `tools/dualocke/aleatorio/salvajes.py`)
- Aleatorios por ubicación: cada especie de una zona se sustituye por otra aleatoria (mapeo 1 a 1 por zona). Es por mapa: la misma línea en hierba, surf, pesca y Golpe Roca, y con la misma rama en todos los huecos.
- La especie se ajusta a la fase que le toca por el **nivel mínimo** de su hueco (mismas reglas que los entrenadores; si hay varias ramas, una al azar).
- Se evita repetir líneas entre zonas hasta que se han usado todas (hay unas 470 líneas sin legendarios).
- Pueden salir formas regionales (Vulpix de Alola…) y Ultraentes y paradójicos (no cuentan como legendarios). No salen megas, Gigamax, formas de combate (Darmanitan Zen…) ni formas cosméticas.
- Solo los mapas de Hoenn: la Pirámide y el Pike del Frente Batalla se quedan como están.
- (En Platino se mantenían los encuentros por hora del día; Esmeralda no tiene encuentros por hora, así que no aplica.)
- Pueden llevar objetos aleatorios.
- Niveles según la curva de la sección 5 (sustituye al "+10%").
- Sin legendarios en salvajes.

**Entrenadores y combates**
- **Hecho** (`tools/dualocke/aleatorio/entrenadores.py`), sobre los equipos de Miguel (`trainers.party`, sin tocarlo):
  - Especies al azar, sin repetir dentro de un equipo, evolucionadas según el nivel de cada Pokémon y con formas regionales. Sin legendarios, salvo en el Alto Mando y Plubio (`permitidos_en: jefes_liga`).
  - Jefes (`as_por_tipo`): el as, el último, es de su tipo o temática. Los de `con_mega_desde_el_aro` llevan como as una especie con mega de ese tipo y su megapiedra. Las revanchas de un jefe mantienen el tipo, la mega y la misma línea del as.
  - Las revanchas de cualquier entrenador (`_2`, `_3`…) usan las mismas líneas que el primer combate, evolucionadas a su nivel.
  - Al cambiar la especie se quitan los movimientos y la habilidad que tenía escritos (la habilidad es la de su especie). Se mantienen nivel, IVs/EVs y naturaleza, y el objeto salvo en los jefes (ver arriba).
  - **Movimientos** (`movimientos.py`; Miguel, #27): **3 de los que aprende por nivel** (hasta su nivel) **y el cuarto al azar** entre todos los normales (sin Z, Dinamax ni los que Metrónomo no puede usar). Ligera preferencia por los potentes (uno de 100 de potencia sale 1,5 veces más que uno de estado), **igual para todos**. Diversidad de tipos: un segundo ataque del mismo tipo es mucho menos probable. Al menos uno de daño.
  - **Sin tope de potencia** (Miguel y Jorge, 31/10/2026). Antes el cuarto llevaba uno según el nivel (40 + 1,5 por nivel, de Jorge). Se quitó porque, con el tope, los movimientos de los Pokémon del jugador eran casi todos de 40 de potencia. Para volver a ponerlo: `"potencia_maxima_del_cuarto": {"base": 40, "por_nivel": 1.5}`.
  - **No se toca** Máximo en la Ruta 120 (equipo fijo).

#### Jefes con estrategia y con la fuerza de los salvajes (Miguel y Jorge, 31/10/2026 y 15/11/2026)

Al jugar, los líderes eran difíciles por desequilibrio, no por cómo jugaban: sacaban Pokémon y movimientos mucho más fuertes que los nuestros. Ahora la dificultad viene de que juegan bien. Está en `tools/dualocke/aleatorio/estrategia.py` y en `"lideres"` del config. **Cambia lo que se decidió en el #27** ("los jefes no llevan mejores movimientos que el resto"): los líderes ya no siguen esa regla.
- **Quién** (`con_estrategia`, admite comodines):
  - los 8 líderes, el Alto Mando y Plubio;
  - desde el gimnasio 3 (Miguel, 15/11/2026), los jefes de mitad de tramo: MAGNO, AQUILES, los admins (TATIANO, SILVINA, MATÍAS), el rival desde la Ruta 119 y BLASCO en la Calle Victoria;
  - MÁXIMO en la Ruta 120, que tiene el equipo fijo: solo se le pone la IA.
  - Antes de ERICO, el rival (rutas 103 y 110, y Férrica) y BLASCO en Malvalona se quedan con la IA básica y sus movimientos de siempre.
- **IA** (`ia`): `Basic Trainer / Smart Switching / Smart Mon Choices / PP Stall Prevention / Randomize Switchin / Know Opponent Party / Hp Aware / Ace Pokemon`.
  - Piensa qué movimiento le conviene, cambia de Pokémon con cabeza, tiene en cuenta los PS y deja el as para el final.
  - **Sin trampa (Miguel, 15/11/2026).** Antes era `Smart Trainer`, que incluye `Omniscient`: conocía tus movimientos, tu objeto y tu habilidad aunque no los hubieras enseñado. Ahora sabe qué especies llevas (`Know Opponent Party`), y lo demás solo cuando lo ve en el combate.
  - VITO y LETI, en doble, usan `Double Ace Pokemon`.
- **Estilos (Miguel, 15/11/2026):** "que cada jefe se sienta diferente sin perder la sensación del randomlocke; no todos tienen que llevar trampas". Sustituye a lo de antes, en lo que el primero de todos los líderes ponía trampas.

  | Estilo | El primero del equipo | Los demás |
  | --- | --- | --- |
  | Trampas y arrastre | Trampa Rocas, Púas, Púas Tóxicas o Red Viscosa, y Rugido o Remolino | Rugido o Remolino, y Protección, Tóxico o Mofa |
  | Espacio Raro | Espacio Raro y una mejora | Los lentos, Espacio Raro; los demás, una mejora y Espacio Raro. Los lentos físicos, Maldición |
  | Chetarse | Una mejora de su ataque y Sustituto, Protección o Agilidad | Lo mismo |
  | Clima | Su clima, y Meteorobola (Velo Aurora con nieve) | Meteorobola y su clima |
  | Estados | Dos de Tóxico, Fuego Fatuo, Onda Trueno, Rayo Confuso, Drenadoras, Bostezo y Deslumbrar | Lo mismo |
  | Pantallas | Reflejo y Pantalla de Luz | Una mejora y una pantalla |
  | Aguante | Tóxico, Drenadoras o Fuego Fatuo, y Recuperación, Respiro o Protección | Lo mismo |
  | Velocidad | Viento Afín y un freno (Onda Trueno, Viento Hielo, Electrotela o Cara Susto) | Un freno, y Agilidad o Viento Afín |

  - **Reparto:** al azar con la semilla, sin repetir dentro de cada grupo. Los 8 líderes llevan los 8 estilos; el Alto Mando y Plubio, cinco distintos; y los jefes de mitad de tramo, siete distintos.
  - **Por personaje:** MAGNO juega igual en el Monte Cenizo, en su guarida y en el Centro Espacial, y el rival, en todos sus combates.
  - **Clima:** el del tipo del jefe (Agua y Eléctrico, lluvia; Fuego y Planta, sol; Roca, Tierra y Acero, arena; Hielo, nieve) o uno al azar si no tiene.
  - **Mejoras:** los que pegan físico, Danza Espada, Corpulencia o Danza Dragón; los especiales, Maquinación, Paz Mental o Danza Aleteo.
  - Los estilos de cada partida salen en el solucionario (`estilos_de_los_jefes`).
  - **Papeles dentro del equipo (Jorge y Miguel, 24/11/2026; para la versión siguiente, el locke en curso sigue con lo de arriba).** Con la tabla de arriba, "los demás" eran todos los demás. Con el estilo Clima, CANDELA y MAGNO llevaban Día Soleado y Meteorobola en los seis ("es que le mete a la fuerza esos 2 movimientos a todos"). Ahora cada Pokémon tiene un papel (`papeles()` en `aleatorio/estrategia.py`):
    - **El que la pone:** el primero del equipo. Lleva lo de la columna "El primero del equipo", como antes.
    - **Los que la aprovechan:** 1 en equipos de hasta 4 y 2 en equipos de 5 o 6. Son los que mejor le sacan partido:
      - Clima: los del tipo de ese clima y, después, los de más Ataque Especial.
      - Espacio Raro: los más lentos.
      - Aguante: los más duros.
      - Chetarse, Pantallas y Velocidad: los que más pegan.
      - Trampas y Estados: al azar.
    - **Qué llevan los que la aprovechan:**

      | Estilo | Lo que llevan |
      | --- | --- |
      | Clima | Meteorobola y un ataque que pega más con ese clima: Rayo Solar con sol, Trueno con lluvia, Ventisca con nieve y la tormenta de arena con arena |
      | Trampas | Rugido o Remolino, y otra trampa |
      | Espacio Raro | Una mejora (Maldición, si son lentos y físicos) y Espacio Raro |
      | Chetarse | Una mejora y Sustituto, Protección o Agilidad |
      | Estados | Un estado y Infortunio |
      | Pantallas | Una mejora y Sustituto o Protección |
      | Aguante | Una cura y un desgaste |
      | Velocidad | Un freno y Agilidad |

    - **El resto:** ningún movimiento de estrategia, solo sus mejores ataques y uno al azar.
    - **Hasta el gimnasio 3:** como antes, un solo movimiento de estrategia por Pokémon.
    - **Comprobado con la semilla de Jorge:** solo cambian los movimientos de los 36 jefes con estrategia. Las especies, los salvajes, los iniciales y todo lo demás salen igual. Ejemplo de CANDELA: Rabsca pone el sol con Meteorobola; Farigiraf y Tauros de Paldea (Fuego) llevan Meteorobola y Rayo Solar; Sableye, Medicham y Crawdaunt van con sus ataques.
  - **Comprobado con tests (Jorge, 16/11/2026; `test/dualocke_ia_estilos.c`):** un test por estilo, con la IA de `ia`, mira que el jefe usa de verdad sus movimientos. Si se cambia `ia` en el config, hay que cambiar `IA_JEFES` en el test.
    - Trampas, Espacio Raro (el lento), chetarse, estados, velocidad y aguante: los usa desde el primer turno.
    - **Pantallas:** el primer turno ataca y pone la pantalla cuando ha visto un ataque tuyo. Sin `Omniscient` no sabe si pegas físico o especial. Con `Assume Stab` (supone que llevas ataques de tu tipo) la pondría de entrada; no se ha puesto.
    - **Clima:** la IA solo pone el clima si le sirve al Pokémon que está en el campo. Por eso el primero lleva Meteorobola en vez de Protección: con Protección atacaba y el clima lo ponía el segundo. Hasta el gimnasio 3 solo llevan un movimiento de estrategia (el primero, el clima; los demás, Meteorobola), así que ahí el clima solo sale si al primero le sirve por su tipo o sus ataques.
- **Movimientos de cada Pokémon:** 2 de estrategia de su estilo y 2 "al azar".
  - **Los 2 al azar:** el mejor ataque de los que aprende por nivel (las tablas al azar) y uno al azar entre todos, como el cuarto de cualquier entrenador.
  - **Hasta el gimnasio 3:** 1 de estrategia, los 2 mejores ataques de su nivel y 1 al azar.
  - **Siempre llevan al menos un ataque.**
  - **Nunca cogen ataques que les perjudican:** ni los que debilitan al que los usa o le quitan media vida (Autodestrucción, Explosión, Explosión Bruma, Sacrificio…) ni los que obligan a recargar (Hiperrayo, Giga Impacto…).
- **Entrenadores normales (Miguel, 15/11/2026; `tools/dualocke/ia_entrenadores.py`):**
  - En el original casi todos llevan `Check Bad Move`: solo evitan los movimientos que fallan y eligen al azar entre los demás.
  - **Hasta el gimnasio 4 (CANDELA) se quedan así. Desde entonces llevan `Basic Trainer`**: eligen un buen movimiento y rematan si pueden, como el rival. Las revanchas, también.
  - Son 462 entrenadores. El script solo toca a los que en el original llevaban `Check Bad Move` y se puede volver a lanzar; el umbral es `TRAMO_BASICA`.
  - No pasa por el randomizer: está escrito en `trainers.party`, así que también vale sin semilla.
- **Hasta el gimnasio 3, la fuerza de los salvajes** (`limite_salvajes`):
  - **Quién:** PETRA, MARCIAL y ERICO, el rival en la Ruta 103, Férrica y la Ruta 110, y BLASCO en Malvalona.
  - **Tope:** ninguno de sus Pokémon puede tener más estadísticas base (suma) que el percentil 90 de los salvajes de hierba de los tramos hasta ese gimnasio, con la semilla de la partida. Si hasta ahí no salen evoluciones, el líder tampoco las lleva.
  - **Techo** (`techo_por_tramo`): 360 hasta PETRA, 400 hasta MARCIAL y 450 hasta ERICO, aunque el percentil salga más alto. Con pocas rutas, un solo salvaje fuerte que no evoluciona (Dondozo, Iron Treads) subía el tope a 570 (lo vio Jorge al probar el #54).
  - **El as** sigue siendo de su tipo: el de su tipo que cabe o, si ninguno cabe, el más flojo.
  - **El inicial del rival** se queda como está (es la regla del rival).
  - Los topes de cada tramo salen en el solucionario (`tope_lideres_por_tramo`).

- Niveles según la curva de la sección 5 (sustituye al "+15%").
- Movimientos aleatorios con 3 movimientos garantizados y una ligera preferencia por movimientos dañinos potentes.
- Mejores movimientos y diversidad de tipos en jefes, importantes y normales.
- Combates individuales.

**Movimientos**
- Movimientos de Gen 9 (ya vienen así).
- **Movimientos por nivel al azar** (`aprendizajes.py`; pedido por Miguel el 26/10/2026, al ver en la primera partida que todo aprendía lo de siempre). Cada especie aprende movimientos al azar al subir de nivel: los Pokémon del jugador, los salvajes, el que recuerda movimientos y los entrenadores (sus 3 movimientos "de nivel" salen de estas tablas).
  - Mismos niveles que el original: se aprende lo mismo de veces y a los mismos niveles.
  - **Sin tope de potencia** desde el 31/10/2026 (Miguel y Jorge: "totalmente aleatorios"): si en la Ruta 101 sale un Charmander con Lanzallamas, sale, y un Garchomp puede salir con Arañazo. Lo controla el mismo `potencia_maxima_del_cuarto` (ahora `null`).
  - Un 60 % son de daño y, entre ellos, los de su tipo son 3 veces más probables. Siempre hay uno de daño entre los que aprende hasta nivel 5.
  - Sin repetidos en la misma tabla. Las formas que compartían tabla la siguen compartiendo.
  - **Nunca sale Plegaria Vital** (revive a un debilitado en pleno combate y se saltaría las muertes del locke). Las MT y los tutores tampoco la enseñan (Miguel, 14/11/2026; `PROHIBIDOS` en `mts.py`). Para no cambiar las partidas en curso, se sortea igual que antes y solo se vuelve a sortear, aparte, la MT o el tutor que caiga en ella.
  - Se activa con `"aprendizaje_aleatorio"` en `randomizer_config.json`. El juego usa la tabla nueva desde `GetSpeciesLevelUpLearnset` (`src/pokemon.c`); sin semilla, y en los tests, sale la original.
- MTs aleatorias con compatibilidad completamente aleatoria, conservando los movimientos de campo y comprobando los aprendibles por nivel. **Hecho** (`mts.py`; Miguel, #27): cada MT enseña un movimiento al azar (sin repetir) y **cada especie la aprende con un 50 %**, sin excepción para las de su tipo; es siempre la misma respuesta para la misma especie y semilla. Las de movimientos de campo (Excavar, Daño Secreto) y las MO se quedan como están, para no bloquear el avance. **Las MO las aprenden todas las especies** (Miguel, 13/11/2026): `CanLearnTeachableMove` (`src/pokemon.c`) dice que sí a cualquier MO, salvo a los huevos, para no quedarse atascado si en el locke no tienes un Pokémon compatible. No se toca `tms_hms.h`: lo cambia `include/item.h` al vuelo.
- Tutores aleatorios con compatibilidad aleatoria, conservando los movimientos de campo. **Hecho** (`mts.py`): los 10 tutores de Hoenn enseñan un movimiento al azar (sin repetir los de las MT) y se aprende con la misma probabilidad que las MT nuevas. La macro `move_tutor` llama a `Dualocke_TutorAleatorio`, que cambia el movimiento y pone su nombre en `{STR_VAR_1}`. **Textos:** los de los tutores (`data/text/move_tutors.inc` y `traduccion/dialogos/27_pokedex_tutores.tsv`) ahora dicen el movimiento con `{STR_VAR_1}`. Los que lo describían (CORTE FURIA "de tipo BICHO", SUSTITUTO "hace una copia"…) se han dejado más generales. La historia de cada tutor se queda.

**Objetos**
- Objetos del suelo aleatorios. **Hecho** (`objetos.py`; Miguel, #27):
  - Las Poké Balls del suelo y los objetos ocultos de Hoenn (unos 410).
  - **Las megapiedras se quedan donde están** y ningún otro objeto del suelo puede ser una megapiedra.
  - Los **competitivos** (`FLAG_ITEM_COMP_*`), totalmente aleatorios como el resto.
  - **Las MT se barajan entre ellas** (donde había una MT sale otra).
  - El resto, **cualquier objeto** menos los excluidos de Miguel (`objetos.excluir`), los objetos clave, las MO, las cartas, las megapiedras, los cristales Z y las teralitas. Las bayas sí.
  - Los objetos clave y las MO del suelo no se tocan.
- Objetos del segundo dependiente aleatorios, con objetos evolutivos garantizados (ver sección 6).
- Objetos de Recogida aleatorios. **Hecho:** solo objetos de consumo (curas, bayas, caramelos), con las mismas probabilidades por nivel que el original.
- **Objetos de los salvajes (hecho):** cualquier salvaje puede llevar un objeto al azar (del grupo del suelo) con un **5 %** (el doble con Ojo Compuesto). Valor provisional de Jorge: `salvajes.probabilidad_objeto`.
- Intercambios internos totalmente aleatorios (Pokémon dado y pedido, objetos, IVs, motes, entrenador original). **Hecho** (`intercambios.py`): el que te dan es una forma base al azar sin legendarios (sale al nivel del que entregas, como en el original; cuenta como regalo para la caja de prohibidos); **el que te piden sale de entre los salvajes de esa partida**, para que se pueda conseguir (Jorge). Objeto e IVs al azar; el mote pasa a ser el nombre de la especie y el entrenador original se queda.
- Precios equilibrados y Caramelos Raros a 1 ₽.

**Ajustes adicionales**
- Pokédex Nacional desde el principio.
- Nombres de Pokémon en minúsculas (normal en la expansion).
- Niveles de los estáticos según la curva.
- Correr sin Deportivas.
- Barras de PS y experiencia rápidas (ya activado por defecto: `B_FAST_HP_DRAIN`, `B_FAST_EXP_GROW`).
- MTs reutilizables (`I_REUSABLE_TMS` en `include/config/item.h`).
- MOs olvidables siempre (en combate, al evolucionar, en la pantalla de datos y con el OLVIDAMOVIMIENTOS de Calagua; `P_CAN_FORGET_HIDDEN_MOVE`) y aprendibles por todas las especies (13/11/2026).

## 8. Traducción al español (historia hecha, falta probarla jugando)

Decisión: empezar en inglés y traducir en paralelo o después. La traducción y los cambios de jugabilidad tocan cosas distintas, así que se puede pasar el español por encima cuando esté listo.

### Tamaño

Texto en la versión actual de la expansion (medido con un script):

- ~184.000 palabras en `data/` (diálogos y scripts de mapas).
- ~30.000 palabras en `src/` (menús, combate, nombres, descripciones).

En total, unas 210.000 palabras: más o menos dos novelas largas.

### Plan

1. **Nombres oficiales** de Pokémon, movimientos, habilidades, objetos, tipos y naturalezas. No inventarlos: sacarlos de listas oficiales.
   - **Tablas preparadas (Miguel, 24/10/2026):** `traduccion/nombres/*.csv` tiene cada constante del juego con su nombre inglés y su **nombre oficial en español**: 1013 especies, 934 movimientos, 873 objetos, 319 habilidades, 20 tipos y 25 naturalezas. Cada tabla dice además si el nombre cabe en el límite de caracteres del juego.
     - Fuente: PokéAPI (español de España), con los nombres **tal como salen en los juegos**, incluidas sus abreviaturas oficiales (por ejemplo, "Mineral Evol").
     - Las genera `tools/dualocke/nombres_oficiales.py`, que necesita los CSV de PokéAPI (no están en el repo).
     - **Pendientes** (`traduccion/nombres/PENDIENTES.md`):
       - Sin nombre oficial: los movimientos Gigamax (aquí no se usan), algunos objetos de Leyendas Arceus y Escarlata/Púrpura que no salen en el juego, y 3 habilidades nuevas de Z-A (Eelevate, Fire Mane, Aura Guard).
       - No caben: casi todos son movimientos Z (no se usan). Los que importan son Patada Salto Alta, Tormenta de Arena, Velocidad Extrema y Placaje Eléctrico (16 caracteres), Electricidad Estática y Absorbe Electricidad (16), y los tipos Eléctrico y Siniestro (8). Hay que abreviarlos o subir el límite.
     - **Decididos** (`traduccion/nombres/decididos.csv`, mandan sobre las tablas): abreviaturas de los que no caben (Pat. Salto Alta, Tormenta Arena, Vel. Extrema, Placaje Eléc., Elec. Estática, Absorbe Elec., los movimientos Z…), nombres de los movimientos Gigamax, y nombres **provisionales** de 3 habilidades nuevas y 15 objetos sin nombre oficial.
     - **Esos 15 objetos no salen en el juego** (decidido por Miguel el 24/10/2026): son de Leyendas Arceus, Escarlata/Púrpura y Oro/Plata (Remedios, Aux., comidas, Gen Furia, Mochi Reinicio, Teralito Astral…). No están en ningún mapa ni tienda, y están en la lista `excluir` del randomizer (`tools/dualocke/randomizer_config.json`). El nombre provisional queda solo por si acaso.
     - Tipos: se ha subido `TYPE_NAME_LENGTH` de 8 a 9 para que quepan Eléctrico y Siniestro sin abreviar.
     - **Aplicados al juego** con `tools/dualocke/aplicar_nombres.py` (`--aplicar` escribe; sin él solo comprueba). Cada nombre queda como `ES(inglés, español)`, así que los tests siguen en inglés. Se puede volver a ejecutar si cambian las tablas. Los plurales de objetos no se usan en español ("5 Poción", como en los juegos oficiales).
     - **Ojo con la documentación:** algunos nombres que se escribieron de memoria no son los oficiales. El oficial es **Mega-Aro** (no "Aro Mega") y **Repelente Máximo** (no "Máximo Repelente"); hay que consultar estas tablas.
   - **Descripciones (hecho, 24/10/2026):** 874 movimientos, 786 objetos y 306 habilidades, en `traduccion/descripciones/*.csv` (`constante,espanol,origen`). `origen` = `oficial` si es el texto oficial de los juegos (PokéAPI) y cabe; `propia` si lo hemos traducido nosotros desde el inglés del juego, porque las oficiales modernas son demasiado largas para los recuadros de Esmeralda. Se escriben en una línea; `tools/dualocke/aplicar_descripciones.py` corta las líneas (movimientos: 2 de 29 letras; objetos: 3 de 20; habilidades: 1 de 30) y avisa si no caben. `--aplicar` escribe los archivos; se puede volver a ejecutar.
   - **Pokédex (hecho, 24/10/2026):** 1284 entradas y las categorías, en `traduccion/pokedex/` (`entradas.csv`, `categorias.csv`). Unas 870 son las oficiales (PokéAPI) y el resto (megas, formas regionales, especies nuevas sin texto que quepa) son traducción propia. Las 31 formas Gigamax se quedan en inglés porque el Dinamax no se usa. La ficha pone "POKéMON Semilla" en vez de "Seed POKéMON" (`src/international_string_util.c`). La categoría tiene como mucho 12 letras (`categoryName` es `u8[13]`). Las aplica `tools/dualocke/aplicar_pokedex.py`.
2. **Mensajes de combate, menús y gráficos con texto:** reaprovechar la traducción de Heart & Soul ([SergioBonet/hns_es](https://github.com/SergioBonet/hns_es)), que tradujo este mismo motor (aunque una versión algo anterior). Incluye los arreglos de código para artículos y concordancias ("¡El Pikachu salvaje usó…!") y los gráficos con texto (iconos de tipo, barras de PS/Nv…).
3. **Diálogos de Hoenn (historia hecha, 26/10/2026):** traducidos por nosotros por tramos, en el orden de la historia y sin el postgame. **La historia principal está entera**, de VILLA RAÍZ a la LIGA (tramos 01-41, Miguel), y también los textos comunes de la AGENDA, concursos, lotería y club cable (tramos 50-55, Jorge): unos 4700 textos. Queda en inglés el postgame. **La tele, el hombre de MALVALONA y las CARPAS DE COMBATE (Jorge, 13/11/2026):** unos 640 textos (`58` a `63`), más las pantallas de alquiler y cambio de la carpa de PORTUAL y los resultados de las carpas, con `ES()` en `src/strings.c`. **Sueltos (Jorge, 11/11/2026, encontrados jugando):** el SALÓN AZULIZA, el CLUB DE FANS de CALAGUA y otras casas y textos sueltos que se ven durante la historia (`56_sueltos.tsv`). **Siguen en inglés las palabras del chat fácil** (`src/data/easy_chat/`, unas 1000): las que salen en la palabra de moda de AZULIZA, los perfiles, el cuestionario o el correo. Cómo se hace y qué falta: `traduccion/dialogos/LEEME.md` y `PLAN.md`.
4. **Pruebas jugando (siguiente paso):** recuadros donde no cabe el texto, frases sin traducir, erratas. Qué mirar: `PRUEBAS.md`.

### Dificultades técnicas

- Cada línea tiene que caber en el recuadro (ancho en píxeles de la fuente de GBA), y el español ocupa más que el inglés. Hay que recolocar saltos de línea; se puede automatizar.
- No romper los códigos dentro del texto: `{PLAYER}`, `{STR_VAR_1}`, colores, pausas, etc.
- Mensajes de combate montados por trozos que necesitan cambios de código para el género y los artículos.

**Textos del código (Jorge, 11/11/2026, encontrados jugando):** la pesca ("¡Oh! ¡Ha picado algo!"), el aviso de la tienda de que ya has comprado uno, el veneno fuera de combate, la RULETA y las tragaperras (`src/fishing.c`, `shop.c`, `strings.c`, `roulette.c`, `slot_machine.c`, con `ES()`).

**Comunes (Jorge, 13/11/2026, encontrados jugando):** quedaban textos en `data/event_scripts.s`, que `dialogos.py` no miraba (ahora sí): centro POKéMON, MAMÁ, POKÉRUS, la MT DAÑO SECRETO del mercado de PORTUAL… También los carteles genéricos de las casas, el hombre del perfil de los centros POKéMON y la CUEVA CARDUMEN (`57_sueltos_comunes.tsv`). La tele, el hombre de MALVALONA y las CARPAS DE COMBATE, que quedaban en inglés, se tradujeron después (#71).

**Clases de entrenador (Miguel, 14/11/2026):** salían en inglés en todos los combates ("HIKER", "YOUNGSTER", "TEAM AQUA"…). Las 59 de Hoenn van en español con `ES()` en `gTrainerClasses` (`src/battle_main.c`): MONTAÑERO, JOVEN, CHICA, CAZABICHOS, EQUIPO AQUA, LÍDER, ALTO MANDO, CAMPEÓN… Caben 12 caracteres (`{PKMN}` cuenta como 2), así que algunas van abreviadas: ENTREN. {PKMN}, ENTREN. GUAY, COLECCIONIS. Las del Frente Batalla y las de Kanto se quedan en inglés. También la ventana de información del movimiento en combate ("POT:" y "PRE:").

**Qué queda en inglés (repaso del 14/11/2026):** de los diálogos faltan unos 1700 textos, casi todos de después de la LIGA:
- el Frente Batalla (unos 1400);
- la Cima Entrenador;
- los eventos de regalo;
- las revanchas de los líderes;
- los entrenadores de las bases secretas.

En la historia solo quedan 38 sueltos: las revanchas de los gimnasios y la valoración de la POKéDEX. De `src/strings.c` están 561 de 1059, y de los mensajes de combate, 693 de 718.

**Menús de opciones (Jorge, 13/11/2026, encontrado jugando):** los menús de los scripts (`src/data/script_menu.h`) seguían en inglés, como el del barco del SR. BRINEY ("PETALBURG / SLATEPORT"). Se han traducido con `ES()` todos menos los nombres de POKéMON y los números: destinos, bicis, casino, tiendas, concursos, frente batalla, estados, encuestas… Los precios con `{CLEAR_TO}` se han acortado donde hacía falta (FL. AMARILLA, SEM. MILAGRO).

Hubo una traducción antigua de la expansion al castellano (fork de Xhyzi, rama `pokeemerald-expansion-es`, compilando con `LANG=ES`), pero tiene más de tres años y no sirve tal cual.

### Paso 2: mensajes de combate (hecho)

La traducción de Heart & Soul **no tiene licencia**, así que no se copia su texto: solo se mira cómo resolvió los problemas técnicos. Los textos los traducimos nosotros. Le pedimos permiso al autor por si se pudiera reaprovechar algo con créditos (pendiente de respuesta).

Cómo funciona:

- **Los tests siguen en inglés.** La expansion tiene miles de tests que comprueban los mensajes exactos. Todo lo traducido se elige al compilar: en los tests (`TESTING`) sale el inglés y en el juego el español.
- **Mensajes de la tabla** (`gBattleStringsTable`, 699): las traducciones van en `src/data/dualocke_textos_combate_es.h`, con la misma clave `STRINGID_...`. Si un mensaje no está ahí, sale en inglés, así que se puede traducir por tandas.
- **Textos sueltos** de `src/battle_message.c` (presentación del combate, "¡Adelante, X!", nombres de las características, estados, menú de combate…): se escriben con `ES(_("inglés"), _("español"))` (macro en `include/dualocke_es.h`).
- **Pokémon rival:** artículo delante y "salvaje"/"enemigo" detrás ("¡El Zigzagoon salvaje usó Placaje!"). Al final se juntan "de el" → "del" y "a el" → "al". El código está en `src/dualocke_traduccion.c`.
- **Características con artículo:** "La Defensa", "Los PS"… porque el género cambia. Por eso en las traducciones van al principio: "¡La Defensa del Zigzagoon salvaje bajó!".
- **Reglas al traducir** (están al principio del archivo de traducciones): mantener todos los códigos `{B_...}`; `{..._NAME_WITH_PREFIX}` al principio de la frase y `{..._NAME_WITH_PREFIX2}` en medio; "X's Y" se escribe "Y de X"; no hace falta poner saltos de línea, se cortan solos.

Hecho: **toda la tabla de mensajes de combate** (693 de 699; los 6 restantes son solo códigos, como el texto de derrota de cada entrenador, que viene de sus datos) y 105 textos sueltos.

**Menús (`src/strings.c`), en curso:** 524 de los 974 textos que se usan, con el mismo `ES()`. Están los de jugar normal: menú de pausa, mochila, tienda, equipo, datos del Pokémon, PC, guardado, ficha de entrenador, decoración, guardería, recordador de movimientos, Safari, huevos y Salón de la Fama. Falta lo que casi no se ve en un Dualocke: Frente Batalla, juegos por cable (Baya-Licuadora, Dodrio, Saltos), Regalo Misterioso, chat y frases de Easy Chat. 

**Menús de otros archivos (hecho):** 233 textos más en `option_menu.c` (opciones), `start_menu.c` (vidas del locke), `party_menu.c`, `item_menu.c`, `item_use.c`, `player_pc.c`, `main_menu.c` (pantalla de inicio), `naming_screen.c`, `pokemon_summary_screen.c`, `map_name_popup.c`, `pokemon_storage_system.c` (cajas del PC) y `pokedex.c`. Se sustituye cada `_("…")` o `COMPOUND_STRING("…")` por `ES(…)` con las dos versiones. No se tocan los nombres de entrenadores de ejemplo de `main_menu.c` ni el abecedario de `naming_screen.c`.

**Nombres de los lugares (hecho, Jorge, 26/10/2026):** los de Hoenn en `src/data/region_map/region_map_sections.json` (RUTA 101, VILLA RAÍZ, CIUDAD PORTUAL…). Salen en los datos del Pokémon ("lo conociste en…"), en el cartel al entrar en un mapa y en el mapa de la región. Máximo 16 letras (`MAP_NAME_LENGTH`), así que algunos van recortados: ARRECÍPOLIS y PACIFIDLOG sin "CIUDAD"/"PUEBLO", CATARATA METEORO, CAMIÓN. Los de Kanto se quedan en inglés.

**Título del mote (arreglo, Jorge, 07/11/2026, encontrado jugando):** salía "Torchic¿Mote de ?", porque la especie se escribía delante y el título detrás, con el hueco `{STR_VAR_1}` vacío. Ahora `Dualocke_BuildMonNamingTitle` (`src/naming_screen.c`) mete la especie en el hueco: "¿Mote de Torchic?".

**Textos que se veían en inglés jugando (Jorge, 22/11/2026, los vio el bot que se pasa el juego):**
- OPCIONES: en VEL. TEXTO salía "LENTAMEDIARÁPIDA" (no cabían entre x 104 y 198): esa fila empieza ahora en x 76 (`src/option_menu.c`).
- Menú de un POKéMON del equipo: DATOS, MOVER, OBJETO, QUITAR, CARTA, LEER, CAMBIAR, ENVIAR… (`src/data/party_menu.h`).
- POKéNAV: descripciones del menú, barra de ayuda, AGENDA (nombres y descripciones de los contactos, LLAMAR/VER/SALIR, la ficha de MÁXIMO y de tu rival), búsqueda por condición (CARISMA, BELLEZA, DULZURA, INGENIO, DUREZA) y cintas (`src/pokenav_*.c`).
- **Gráficos con el texto dibujado:** los botones y cabeceras del POKéNAV (MAPA HOENN, CONDICIÓN, AGENDA, CINTAS, APAGAR, MENÚ, COMPLETO/AMPLIADO…, y "POKéNAV" arriba y abajo en vez de "POKéMON NAVIGATOR"), el PC (DATOS, EQUIPO, SALIR, CERRAR CAJA), la ficha de entrenador (FICHA ENTRENADOR, MEDALLAS) y el dinero de las tiendas (DINERO). Los hace `tools/dualocke/textos_graficos.py`: monta cada gráfico como se ve en el juego (con su tilemap o con los trozos del sprite), borra el texto inglés y escribe el español con las fuentes del juego y los colores del original, y devuelve cada píxel a su tile. Si un tile se usa en varios sitios y solo cambia en uno, usa un tile libre y cambia el tilemap; en la cabecera del POKéNAV no quedaba ninguno y "POKéNAV" se monta solo con el tilemap, con las letras de "POKéMON". Para letras que no hay en las fuentes (las de 5 píxeles de "MONEY" y las gruesas de "BADGES") tiene unas pocas dibujadas a mano. Se puede volver a lanzar y no cambia nada; con `--ver /tmp/x` guarda cómo queda cada pantalla. Probado en el emulador con la ROM de pruebas.

**Más gráficos en español (Jorge, 22/11/2026, con `textos_graficos.py`):**
- Pantalla de datos: PERFIL, HABILIDAD, NOTAS ENTRENADOR, ESTADO (huevo), OBJETO, CARACT., MOVIMIENTOS, EFECTO, DESCRIPCIÓN. Con los IV/EV activados el juego usa `iv_ev_tiles.png` en vez de `tiles.png`: la herramienta copia los cambios a los dos (menos sus tiles 218-223). CARACT. va con la letra más estrecha porque el código vuelve a poner esa etiqueta (tiles 169-172) al pasar entre estadísticas, IV y EV. Ojo: el código pinta tiles que no salen en ningún tilemap; aquí los tiles nuevos solo se toman de los vacíos del final (234-239). Al principio se usaron otros "libres" y salía basura bajo el Pokémon.
- Iconos de tipo: BICHO, SINIE., DRAGÓN, ELÉCT., HADA, LUCHA, FUEGO, VOLAD., FANT., PLANTA, TIERRA, HIELO, VENENO, PSÍQ., ROCA, ACERO, ASTRAL, AGUA (caben 30 píxeles), y las categorías de concurso con la letra más estrecha.
- Combate: el botón de la descripción del movimiento pone INFO / MOV.
- Pantalla de nombres: BORRAR, B BOTÓN, y las pestañas ABC / abc / otros (MAYÚS no cabe con el acento).
- **Descripciones que seguían en inglés:** 70 movimientos (Surf, Cascada, Rayo Hielo, Hiperrayo, Triturar…), 28 objetos (Superpoción, Hiperpoción, los objetos X, Buceo Ball, las MT de Rayo Hielo y Ventisca, las MO de Surf y Cascada…) y 10 habilidades. Tenían un `#if` (o una macro como `BINDING_TURNS`) dentro del texto y `aplicar_descripciones.py` se las saltaba sin avisar: ahora quedan como `#if TESTING <la original> #else <la española> #endif`, con una marca para no tocarlas dos veces. Se vio en combate (la descripción de Surf salía en inglés).

**Pendiente (imágenes, no texto):** PRESS START en la pantalla de título (letra metalizada propia: habría que dibujar la U y la L a mano). Quedan en inglés archivos menos vistos (Pokédex HGSS y DexNav, desactivados; concursos; Baya-Licuadora; depuración).

Reglas para los menús: mantener los códigos y el mismo número de saltos `\n`, `\l` y `\p`, y que cada línea no sea mucho más larga que la inglesa (los recuadros tienen ancho fijo). Los nombres van en mayúsculas como en el original (MOCHILA, GUARDAR, CARTA…).

Falta probarlo jugando.

Para comprobar una tanda antes de subirla: que cada traducción tenga los mismos códigos `{...}` que el inglés y solo caracteres que existan en `charmap.txt`.

## 9. Estado y siguientes pasos

### Locke en curso (empezado de nuevo el 22/11/2026, con la versión 9: la partida que cuenta)

- ROMs hechas por Claude con `make release` (sin menús de depuración).
  - **Versión 1** (26/10/2026): commit `46ba7600` (con #36 y #37).
  - **Versión 2** (27/10/2026): commit `a661c0eb`. Añade el recuerdamovimientos, los Ticket-Recuerdo (#40) y los movimientos por nivel al azar (#42). Las partidas de la versión 1 siguen valiendo: con la misma semilla, salvajes, iniciales, objetos, estáticos, MT y habilidades salen idénticos. Solo cambian los movimientos por nivel y los de los entrenadores.
  - **Versión 3** (27/10/2026): commit `c9b5e9e38`. Arregla las habilidades de relleno (#47; con la misma semilla solo cambian las especies que salían "sin habilidad") y protege el mote y el orden del equipo al capturar (#49, bug del equipo clonado). Las partidas de la versión 2 siguen valiendo.
  - **Versión 4** (27/10/2026): commit `085e51aa3` (el mismo juego que la 3) con **semillas nuevas**: Jorge y Miguel empiezan el locke de cero.
  - **Versión 5** (01/11/2026): commit `27c61472d`, con **semillas nuevas** y partida nueva. Añade:
    - movimientos al azar sin tope y líderes con estrategia (#54, Miguel);
    - la hierba de la Ruta 103 a 2-3 (#55);
    - la captura con el equipo lleno, que solo bloquea al único que sabe una MO, y la guía con las evoluciones raras (#53).
  - **Versión 6** (12/11/2026): commit `24e7f72ff`, con **las mismas semillas** que la 5, así que las partidas siguen. Añade:
    - el título del mote (#57) y los objetos de los muertos, que vuelven a la mochila (#58);
    - los textos sueltos traducidos y los de la pesca, la tienda y el casino (#60, #62);
    - la pesca a pie a 15-21 (#61);
    - los tres primeros gimnasios más suaves (#63);
    - las estadísticas bien leídas en el randomizer (#64). Con la misma semilla cambian unos 50 jefes que aún no se han visto; los salvajes y el resto de entrenadores salen igual.
  - **Versión 7** (16/11/2026): commit `8103388b2`, con **las mismas semillas**, así que las partidas siguen (lo que se guarda no ha cambiado). Añade:
    - ningún salvaje por encima del level cap (#66);
    - el muerto que se cambia por la captura va a la caja de muertos, y al encender el PC se entierra al que ya se hubiera colado (#70);
    - la amistad en la pantalla de datos (#72);
    - traducción: menús, textos comunes, la tele, el hombre de MALVALONA, las CARPAS DE COMBATE y las clases de entrenador (#67, #68, #71, #73);
    - las MO las aprenden todas las especies (#69);
    - Plegaria Vital fuera de las MT y los tutores (#73; con estas dos semillas no salía, así que no cambia nada);
    - jefes con estilo propio y sin IA tramposa, y entrenadores normales con IA básica desde el gimnasio 4 (#74). Con la misma semilla, salvajes, iniciales, MT, tutores y las especies de todos los entrenadores salen igual; cambian los movimientos y los objetos de 36 jefes y la IA de 461 entrenadores.
    - El 17/11/2026 se hizo una ROM de la versión 7 con el arreglo del #97 (entrenadores de las RUTAS 111 y 118 a su nivel), desde su rama, con las mismas semillas.
  - **Versión 8** (18/11/2026, la actual): commit `9c897c01d`, con **semillas nuevas**: Jorge y Miguel empiezan el locke de cero. Añade:
    - todo lo de Miguel del 16 y el 17/11, revisado en el #99: opciones del motor (Pokédex HGSS, tipos en combate, no huir de entrenadores, carteles Blanco/Negro; #78), megas de las formas Gigamax (#79) y las zonas nuevas (las islas del ferry, la GRUTA ÍGNEA, la ISLA NEVADA, el DESIERTO PROFUNDO y las RUINAS ARENOSAS, la MARISMA AZULIZA, el BOSQUE FRONDOSO y la MANSIÓN OLVIDADA, las islas del sur, la PLAYA VOLCÁNICA, la CUMBRE METEORO, el BOSQUE SINIESTRO y la CIÉNAGA TÓXICA; del #81 al #98);
    - el paso abierto en las rocas para llegar a las islas (#100);
    - los entrenadores que se alcanzan antes de su tramo y la red de seguridad del cap para entrenadores (#97);
    - la IA de los jefes con tests y la Meteorobola en el primero del clima (#76).
    - Nada de esto se ha probado todavía en el emulador: hay que ir mirando `PRUEBAS.md` al jugar.
  - **Versión 8.1** (18/11/2026): commit `978ad496bd`, las mismas semillas, así que las partidas siguen valiendo. Lleva los arreglos de lo que vio Miguel jugando hasta la 3.ª medalla (#105):
    - las cuevas de la CUMBRE METEORO, donde se quedaba encerrado;
    - la MARISMA AZULIZA ya no tapa la RUTA 106 desde AZULIZA;
    - la hierba muy alta cortada de la marisma.
    - Solucionario comparado con la 8 en las dos semillas: idéntico.
  - **Versión 8.2** (18/11/2026): las mismas semillas, así que las partidas siguen valiendo. Arregla lo siguiente que vio Miguel jugando:
    - se sale de la zona del guardián de la CUMBRE METEORO sin la bici de carreras;
    - el Parche Habilidad ya no se gasta sin hacer nada;
    - DEVON revive los fósiles de todas las generaciones.
    - Solucionario comparado con la 8: idéntico, más los 13 fósiles nuevos en los regalos.
  - **Versión 8.3** (18/11/2026): las mismas semillas. Cada especie tiene tantas habilidades como en el original, distintas (decidido por Miguel). Las partidas siguen valiendo; los Pokémon con el hueco 1 o el oculto cambian de habilidad, el resto se queda igual.
    - Solucionario comparado con la 8.2: idéntico salvo las habilidades, y en ellas la primera de cada especie es la misma.
  - **Versión 8.4** (19/11/2026): las mismas semillas; las partidas siguen valiendo. Arregla lo que vio Miguel jugando:
    - TERRY ya no tapa el camino de la ISLA SUR, ni MIKE el de la ISLA LEJANA;
    - los bordes de la PLAYA VOLCÁNICA;
    - fotos del juego en las pistas de megapiedras y Ticket-Recuerdo de la guía.
    - Solucionario comparado con la 8.3: idéntico.
  - **Versión 8.5: arreglos de la cuarta prueba de Miguel** (20/11/2026; mismas semillas, las partidas siguen valiendo; solucionario idéntico al de la 8.4):
    - **Reinicio al capturar al guardián de la ISLA NEVADA:** no era el guardián. NIEVES usaba un gráfico de Rojo Fuego (`OBJ_EVENT_GFX_COOLTRAINER_F`), que en Esmeralda no existe: su sprite salía con datos basura y, al animarse, el juego saltaba a una dirección mala y se reiniciaba. Igual DARÍO (ISLA ARENOSA) y el bañista de la PLAYA VOLCÁNICA (seguramente el "personaje roto"). Cambiados por los de Esmeralda, y `tools/dualocke/graficos.py` lo comprueba en el CI.
    - **Mapas con más de un dibujo** (`tools/dualocke/variantes.py`, en el CI): la RUTA 131 usa siempre `LAYOUT_ROUTE131_SKY_PILLAR` y el paso a la ISLA DE RUINAS se había abierto en el otro dibujo (en el juego estaba cerrado); la RUTA 111 usa `LAYOUT_ROUTE111_NO_MIRAGE_TOWER` cuando no se ve la TORRE ESPEJISMO (al azar, y siempre después del fósil) y ahí no estaba la puerta del DESIERTO PROFUNDO. Ahora están en los dos. `alcance.py` mira el dibujo del juego.
    - **ISLA NEVADA:** una fila de rocas abajo, salvo por donde se llega: bajando por el resto se salía a ARRECÍPOLIS y a la RUTA 125.
    - **ISLA VOLCÁNICA:** 10 casillas a la derecha bajo la RUTA 134, para que no quede al lado del puerto de PORTUAL (al cruzar, el puerto aparecía y desaparecía).
    - **Combate con MÁXIMO PEÑAS en el CENTRO ESPACIAL:** su equipo se quedó a nivel 42-44 contra MAXI (84) y TATIANA (75-81). `tools/dualocke/companeros.py` lo pone al nivel del tramo (84): Metagross, Skarmory y Aggron, sin ataques que te den a ti. Lo revisa Miguel.
    - Pendiente: lo de Ferrocuello y el Campo de Niebla en la RUTA 124 (hace falta el `.sav` de Miguel para ver su equipo) y mejorar el dibujo de la ISLA VOLCÁNICA.
  - **Versión 9: la partida que cuenta** (22/11/2026): commit `e38ad8986f`, con **semillas nuevas**: Jorge y Miguel empiezan el locke de cero (el #115 cambia la partida guardada). Antes de fusionar, Claude lo probó todo junto con el bot y la ROM release (`registro/2026-11-22-jorge-prueba-todo-junto.md`). Añade:
    - todo lo de Miguel desde la 8.5: respuestas a Jorge, PLAYA VOLCÁNICA con ceniza, los arreglos de la quinta prueba, los biomas CANTERA, PRADO DE HADAS e ISLA DEL DRAGÓN, y los arreglos de lo que vio el bot en las zonas nuevas (#112, #113, #116 y #117);
    - la regla de la Liga dentro del juego (#122, Miguel) y su mensaje (#123);
    - nombre del jugador de hasta 10 letras y mochila más grande (#115);
    - el bot que se pasa el juego (#118);
    - Toxtricity Grave ya no pasa a Aguda, y 12 Poké Balls que tapaban el paso movidas (#119);
    - textos que seguían en inglés (opciones, menú del equipo, POKéNAV, PC, ficha, dinero, pantalla de datos, tipos, mote) y 108 descripciones de movimientos, objetos y habilidades que se saltaban (#120 y #121).
- **Semillas actuales (versión 9):** Miguel `3483218843` (`Esmeralda Dualocke - Mikemine.gba`), Jorge `2635893558` (`Esmeralda Dualocke - Jorgemori.gba`).
- Semillas de las versiones anteriores (partidas abandonadas):
  - versión 8: Miguel `3632113266`, Jorge `2425682645`;
  - versiones 5-7: Miguel `2918696854`, Jorge `2780853751`;
  - versión 4: Miguel `1820821844`, Jorge `5966102869`;
  - versiones 1-3: Miguel `7044754226`, Jorge `6629063067`.
- **Para regenerar la misma ROM:** `git checkout <commit de la versión>` y `make release SEED=<semilla>`. Con un commit más nuevo, la misma semilla puede barajar distinto si ha cambiado el randomizer o los datos, y la partida guardada puede dejar de servir si cambia lo que se guarda (como pasó con los bolsillos). Si hay que arreglar algo a mitad del locke, se hace la ROM nueva con la misma semilla y se comprueba antes que la partida carga.
- **No actualizar con el instalador a mitad del locke:** usa su propia semilla (`dualocke_semilla.txt`) y compila `master`. Si hace falta, se pone la semilla de cada uno en ese archivo antes.
- Las ideas de `IDEAS.md` se dejan para después de pasárnoslo.

### Hecho

- Fork montado y compilando (en Windows/WSL y en el entorno de Claude).
- Level caps duros con la curva de la sección 5.
- Caramelos Raros limitados por el cap.
- Evoluciones por intercambio convertidas (sección 6).
- Paso 1 del orden de trabajo (detalles en la sección 12).
- Equilibrio (Miguel): reescalado de niveles por tramos, equipos de los jefes con megas, evoluciones de los entrenadores normales y parámetros del randomizer (secciones 5, 6 y 7).
- Vidas y caja de muertos (Jorge). Cómo funciona:
  - Se empieza con 20 vidas (`VAR_DUALOCKE_LIVES`). Cada Pokémon que acaba un combate debilitado muere: va a la última caja del PC ("DEAD", la 14) y se resta una vida.
  - Con 0 vidas se sigue jugando; la siguiente muerte pierde el locke (`FLAG_DUALOCKE_LOCKE_LOST`). Perder un combate también lo pierde, sin mover a nadie (el equipo no puede quedarse vacío). El juego no se bloquea: se marca y se ve en el menú.
  - El menú de pausa muestra "Lives: N" o "LOCKE LOST".
  - La caja de muertos solo deja ver el resumen: no se puede sacar, mover, soltar ni meter nada, y los Pokémon nuevos nunca van ahí.
  - **Objetos de los muertos (Jorge, 07/11/2026, encontrado jugando):** como en la caja no se puede tocar nada, los objetos que lleven vuelven solos a la mochila (al PC de objetos si ese bolsillo está lleno). Pasa al acabar cada combate y al encender el PC, así que también recupera los de los que murieron antes. Lo hace `Dualocke_RecoverDeadMonsItems` (`src/dualocke.c`).
  - Los objetos de revivir no se pueden usar en combate.
  - **Muerto cambiado por la captura (Jorge, 13/11/2026, encontrado jugando):** al capturar con el equipo lleno se puede mandar a la caja a uno del equipo. Si se elegía a uno que había caído en ese combate, iba vivo a una caja normal. Ahora va a la caja de muertos y resta su vida (`Dualocke_TryBuryChosenPartyMon`, llamada desde `Cmd_givecaughtmon` en `src/battle_script_commands.c`). Para las partidas en las que ya pasó, la primera vez que se enciende el PC se entierran los de las cajas normales con 0 PS y se resta su vida (`Dualocke_BuryFaintedBoxMonsOnce`, una sola vez con `FLAG_DUALOCKE_CAJAS_REVISADAS`, porque la Torre Entrenador no cura y no hay que tocar a los que se debiliten ahí). Si el muerto ya se había curado en un Centro Pokémon, no se puede detectar: hay que liberarlo a mano.
  - No cuentan: Frontera, Pirámide, Pike, Cima Entrenador, combates por cable, Safari, el primer combate y las bases secretas.
  - Tests en `test/dualocke.c` (`make check TESTS="Dualocke"`).
  - **Aviso al morir (hecho, Miguel, 24/10/2026):** cuando se debilita un Pokémon tuyo en un combate en el que cuentan las vidas, en vez de "X fainted!" sale "X has died! Lives left: N." (las vidas que quedarán al acabar el combate). Si ya no quedan vidas, o se han debilitado todos, sale "X has died! The locke is lost!". Los Pokémon del compañero (combates dobles con compañero) no cuentan. En los tests de la expansion se deja el texto original. Código: `src/dualocke_aviso.c`, enganchado en `BufferStringBattle` (`src/battle_message.c`).
- Combate con Máximo en la Ruta 120 que da el Mega-Aro (Jorge, sección 6).
- Primera captura por zona para los salvajes (Jorge, sección 4). Las zonas gastadas se guardan en `VAR_DUALOCKE_ZONES_0` a `_7` (8 variables libres, un bit por zona; no gasta flags; la `_7` se añadió el 17/11/2026 con la MARISMA AZULIZA). Tests en `test/dualocke.c`.
- Caja de prohibidos (Jorge, sección 4): regalos, eventos, fósiles, estáticos, huevos e intercambios repetidos o legendarios van a la caja 13 ("VETADOS"), bloqueada hasta que dejan de ser repetidos.
- Randomizer completo (Jorge, sección 7) y traducción al español de la historia (Miguel y Jorge, sección 8).
- Bolsillos Medicinas y Megapiedras en la mochila (Jorge, sección 6).
- Recuerdamovimientos en los Centros Pokémon y Ticket-Recuerdo por las rutas (Miguel, sección 6).
- **Guía para jugar** en `GUIA.html` (se abre con el navegador): cómo avanzar, caps y niveles de los jefes, objetos nuevos, pistas de megapiedras y Ticket-Recuerdo, y novedades. Tiene también una **Pokédex** (estadísticas base, tipos, debilidades, evoluciones y megas, con sprites). Las pistas salen de los mapas con `python3 tools/dualocke/guia.py` y la Pokédex del código con `python3 tools/dualocke/guia_pokedex.py`; el resto se edita a mano.
  - **Fotos de las pistas** (pedidas por Miguel, 19/11/2026): cada megapiedra y cada Ticket-Recuerdo tiene, después de "Más pistas", una **foto del juego** con el sitio marcado con un círculo rojo. Desde el 22/11/2026 la "Solución" (la casilla exacta) solo sale si el objeto no tiene foto (Jorge: con la foto no hace falta). Las saca `python3 tools/dualocke/emulador/fotos_guia.py` con el emulador sin pantalla (ver la sección 3), poniendo al jugador al lado; van dentro de `GUIA.html` (WebP, unos 2,7 MB las 161). Si se mueve un objeto: `guia.py` y después `fotos_guia.py`. Las evoluciones raras salen explicadas: Tandemaus (nivel 25 subiendo en combate, no con Caramelo Raro fuera de combate), Shedinja, Sirfetch'd y las que no se pueden hacer en Hoenn (Runerigus, Urshifu).
- **Mapa interactivo** en `MAPA.html` (Jorge, 22/11/2026; idea sacada de los mapas web de Project Zomboid). Se abre con el navegador, en la misma carpeta que la guía (se enlazan entre sí). Lo genera entero `python3 tools/dualocke/mapa_interactivo.py` desde los mapas del juego (plantilla en `tools/dualocke/mapa/plantilla.html`, con Leaflet 1.9.4 dentro; un solo archivo de unos 6 MB, como la guía). Hay que volver a lanzarlo cuando se toque un mapa o un objeto.
  - **Mundo:** todos los mapas exteriores dibujados con sus tilesets (como Porymap) y unidos por sus conexiones, con zoom y arrastre. Nivel **Bajo el agua** con los mapas de buceo encima de su ruta. Lo que no se alcanza andando (ARRECÍPOLIS, las islas del ferry, ISLA VOLCÁNICA, FRENTE BATALLA…) sale como un botón en su sitio del mapa de la región; las islas del ferry que no salen en él, en fila debajo de Hoenn.
  - **Cuevas y edificios:** se abren pinchando su puerta (o su nombre) y tienen **selector de plantas** (como los pisos del mapa de Zomboid). Las puertas llevan de un mapa a otro; "Atrás" vuelve.
  - **Capas:** nombres de zonas, sitios (Centro POKéMON, tienda, gimnasio, puerto…), cuevas y lugares, puertas y zonas nuevas (con el texto de su tarjeta de Novedades de la guía). Apagadas de inicio por ser destripes: entrenadores (clase, nombre y nivel máximo), objetos del suelo (salen al azar con la semilla; las MT, MT al azar), megapiedras, Ticket-Recuerdo y POKéMON fuertes (guardianes y estáticos: nivel; la especie sale al azar con la semilla).
  - **Buscador** de zonas, megapiedras, entrenadores y POKéMON fuertes. **Enlace** a cualquier sitio (`#v=<mapa>&x=&y=&z=`) para mandárselo al otro.
  - **Zonas de captura:** las zonas con salvajes (una por nombre de zona, como en el juego: 85). Cada uno marca las suyas (Capturado / Fallado) desde la lista del menú o pinchando en la zona; se guarda en el navegador, aparte para Jorge y para Miguel.
- **Arreglos de lo que encontró el bot jugando (Jorge, 22/11/2026):** Toxtricity Grave ya no pasa a Aguda al acabar cada combate (usaba la tabla de cambios de forma de la Aguda; fallo heredado de la expansion, con test en `test/battle/form_change/end_battle.c`), y 12 Poké Balls nuevas que tapaban el paso se han movido (sección 6, "Que ninguna Poké Ball tape el paso").
- **Siguiente: jugar y probarlo todo junto.** Lista de qué mirar en `PRUEBAS.md`.

### Pendiente para el próximo locke

- **Fallos de la partida completa de Claude (22/11/2026)**, ver `registro/2026-11-22-jorge-bot-partida-completa.md`: Toxtricity Grave se vuelve Aguda al acabar cada combate (tabla de cambio de forma equivocada en `gen_8_families.h`), Balls delante de puertas (Museo Oceánico 2F, Ruta 122) y junto a entrenadores en la Calle Victoria, y textos en inglés (VEL. TEXTO pegado, TRAINER CARD/BADGES/MONEY, POKéNAV, SUMMARY/SWITCH/ITEM, PKMN DATA/PARTY POKéMON/CLOSE BOX). Recomendación para el randomizer: asegurar ataques de su tipo en los movimientos por nivel.
- **Estadísticas mal leídas en el randomizer: ARREGLADO (Jorge, 11/11/2026).** `aleatorio/especies.py` cogía el primer número de las estadísticas que dependen de la generación (ya preprocesadas son, por ejemplo, `8 >= 1 ? 60 : 50`). Salían mal 189 estadísticas de unas 90 especies: Machoke con 8 de Def. Esp., a Charizard le faltaba el At. Esp… Ahora se evalúa la expresión con `evaluar`, que se ha movido de `guia_pokedex.py` a `aleatorio/especies.py` para que la usen los dos. Solo afecta a los jefes (tope y estrategia de los líderes, objetos): con la semilla de Jorge cambian 52 (líderes, rivales y BLASCO, sobre todo especies y movimientos); los salvajes, las habilidades, los iniciales y el resto de entrenadores salen igual. Se metió con las partidas ya empezadas: los jefes que aún no has visto simplemente salen distintos.

### Pendiente de decidir

- ~~**Regla de la Liga**: ¿se mete dentro del juego?~~ **Decidido (Miguel, 22/11/2026): sí, entera.** Ver "Regla de la Liga dentro del juego" (sección 6).
- **Recomendaciones del bot (#118), contestadas por Miguel el 22/11/2026:** los movimientos del randomizer se quedan totalmente al azar; los salvajes de la CALLE VICTORIA, a nivel 87; y los jefes de mitad de juego no se tocan hasta que los pruebe una persona.
- ¿Se consigue la **ROM de Esmeralda española** para los diálogos oficiales?

### Orden de trabajo propuesto

1. ~~Lo fácil: mote obligatorio, quitar curativos y Objetos X de las tiendas, Caramelos Raros a 1 ₽, bloquear Objetos X en combate, correr sin Deportivas, Pokédex Nacional desde el inicio, MTs reutilizables, MOs olvidables.~~ **Hecho.**
2. ~~Combate con Máximo y el aro~~ (hecho). ~~Segundo dependiente y contenido de las tiendas~~ (hecho).
3. Reglas del locke: ~~vidas + caja de muertos~~, ~~límite de una compra por objeto~~ y ~~aviso al morir~~ (hechos); ~~primera captura por zona y caja de prohibidos~~ (hechas).
4. Randomizer con semilla (~~reescalado de niveles~~, ~~equipos de jefes~~ y ~~parámetros~~ hechos; ~~salvajes, entrenadores, iniciales, estáticos, regalos, objetos, intercambios, movimientos, habilidades y MT~~ hechos por Jorge; ~~tutores~~ hechos; falta probarlo jugando).
5. Revanchas y postgame (niveles).
6. ~~Traducción~~ (historia hecha; falta probarla jugando, `PRUEBAS.md`).
7. **Siguiente tarea (pedida por Miguel, 24/10/2026): mejorar la pantalla de datos del Pokémon.** Que se vea todo sin herramientas externas:
   - Características, **IVs** y **EVs** (número exacto, no la letra).
   - **Naturaleza** con lo que sube y lo que baja ("Firme: +Ataque, −At. Esp.").
   - **Habilidad** con su descripción y **cuál sería su otra habilidad** (y la oculta).
   - **Movimientos** con su información: tipo, categoría (físico/especial/estado), potencia, precisión, PP y descripción.
   - Parte ya la trae la expansion y solo hay que activarla en `include/config/summary_screen.h` (`P_SUMMARY_SCREEN_IV_EV_INFO`, `P_SUMMARY_SCREEN_IV_EV_VALUES`; los colores de la naturaleza ya están activos). Lo de la otra habilidad y la naturaleza en texto hay que programarlo.

**Tipo Hada:** ya está en el juego. La configuración usa los datos de la última generación (`P_UPDATED_TYPES`, `B_UPDATED_MOVE_TYPES` y `B_UPDATED_TYPE_MATCHUPS` en `GEN_LATEST`), así que Gardevoir, Mawile, Azumarill, Altaria mega, etc. son Hada, Encanto/Beso Drenaje/Carantoña son Hada y la tabla de tipos es la moderna. El randomizer tiene que contar con él.

Quién hace cada cosa y cómo se sube: sección 13.

## 10. Mapa del código (lo que ya se ha tocado y dónde está cada cosa)

| Qué | Dónde |
| --- | --- |
| Configuración de caps (tipo de cap, caramelos) | `include/config/caps.h` |
| Niveles del cap por medalla | `src/caps.c` (`sLevelCapFlagMap`) |
| Usar objetos evolutivos desde la mochila | `include/config/item.h` (`I_USE_EVO_HELD_ITEMS_FROM_BAG`) |
| Evoluciones de cada especie | `src/data/pokemon/species_info/gen_N_families.h` (`.evolutions = EVOLUTION(...)`) |
| Datos de objetos | `src/data/items.h` |
| Configuración de combate (gimmicks, mecánicas por generación) | `include/config/battle.h` |
| Especies activadas (megas, gens) | `include/config/species_enabled.h` |
| Configuración del mundo (seguidores, etc.) | `include/config/overworld.h` |
| Encuentros salvajes | `src/data/wild_encounters.json` |
| Randomizer (semilla, salvajes, entrenadores, datos de las especies) | `tools/dualocke/randomizer.py`, `tools/dualocke/aleatorio/`; integración en el `Makefile` (bloque "Dualocke: randomizer con semilla") |
| Randomizer en el juego (tablas generadas: estáticos, regalos, objetos, intercambios, habilidades, MT, tutores) | `src/dualocke_aleatorio.c`, `include/dualocke_aleatorio.h`, `src/data/dualocke_aleatorio.h` (generado); qué enseña cada MT en `include/item.h` |
| Reescalado de niveles por tramos (tabla de mapas y reglas) | `tools/dualocke/reescalar_niveles.py` |
| Desde qué tramo se llega a cada entrenador (y si va por encima) | `tools/dualocke/alcance.py` (en el CI) |
| Ningún POKéMON de entrenador por encima del cap | `src/dualocke.c` (`Dualocke_CapTrainerMon`), llamado desde `src/battle_setup.c` (`CreateNPCTrainerPartyFromTrainer`) |
| Equipos de los jefes (+1/+2, megas) | `tools/dualocke/equipos_jefes.py` |
| Textos dibujados en los gráficos (POKéNAV, PC, ficha, dinero) | `tools/dualocke/textos_graficos.py` |
| Megapiedras, objetos competitivos y Ticket-Recuerdo por el mapa | `tools/dualocke/colocar_objetos.py` (`--mover` para las que tapan el paso; `--repartir` para las amontonadas) |
| Que nadie se quede encerrado y que ninguna persona ni Ball tape el paso | `tools/dualocke/sin_salida.py` (en el CI; las Balls, `bolas_que_tapan`) |
| Recuerdamovimientos de los Centros Pokémon | `data/scripts/dualocke_recuerda_movimientos.inc` |
| Guía para jugar (walkthrough, caps, pistas de objetos, Pokédex, novedades) | `GUIA.html` (pistas: `tools/dualocke/guia.py`; fotos de las pistas: `tools/dualocke/emulador/fotos_guia.py`; Pokédex: `tools/dualocke/guia_pokedex.py`) |
| Mapa interactivo (mundo, plantas, capas, buscador, zonas de captura) | `MAPA.html` (`tools/dualocke/mapa_interactivo.py` y `tools/dualocke/mapa/plantilla.html`) |
| Emulador sin pantalla y ROM de pruebas (`make DUALOCKE_PRUEBA=1`) | `tools/dualocke/emulador/`, `src/dualocke_prueba.c`, `include/dualocke_prueba.h`; ganchos con `#ifdef DUALOCKE_PRUEBA` en `main_menu.c`, `new_game.c`, `overworld.c`, `field_weather_effect.c` y `trainer_see.c` |
| Bot que se pasa el juego con la ROM normal | `tools/dualocke/bot/` (`piloto.py`; ver su `README.md`) |
| Evolución por nivel de los entrenadores normales | `tools/dualocke/evolucionar_entrenadores.py` |
| Entrenadores | `src/data/trainers.party` |
| Tiendas | scripts de cada mapa en `data/maps/*/scripts.inc` (`pokemart`) |
| Comprobación del Mega-Aro | `src/battle_util.c` (busca `ITEM_MEGA_RING`) |
| Evento de Máximo y entrega del Mega-Aro | `data/maps/Route120/scripts.inc` (`Route120_EventScript_Steven`) |
| Datos al empezar partida nueva (correr, Pokédex Nacional) | `src/new_game.c` (`NewGameInitData`) |
| Mote obligatorio al capturar | `src/battle_script_commands.c` (`Cmd_trygivecaughtmonnick`) |
| Mote obligatorio en regalos | `src/tv.c` (`ChangeBoxPokemonNickname_CB`) y scripts con `gText_NicknameThisPokemon` |
| Mote obligatorio al eclosionar | `src/egg_hatch.c` (`EggHatchSetMonNickname`, estado 9 de `CB2_EggHatch`) |
| Objetos que no se pueden usar en combate | `src/item_use.c` (`CannotUseItemsInBattle`) |
| MTs reutilizables | `include/config/item.h` (`I_REUSABLE_TMS`) |
| MOs olvidables | `include/config/pokemon.h` (`P_CAN_FORGET_HIDDEN_MOVE`) |
| MOs para todas las especies | `src/pokemon.c` (`CanLearnTeachableMove`) |
| Filtrar tiendas por medallas/flags (útil para las megapiedras) | `src/shop_criteria.c` |
| Vidas y caja de muertos | `src/dualocke.c`, `include/dualocke.h`; se llama desde `src/battle_setup.c` (final de combate) |
| Bloqueo de las cajas de muertos y prohibidos | `src/pokemon_storage_system.c` (busca `Dualocke_IsLockedBox` y `Dualocke_IsBoxMonLocked`) y `src/pokemon.c` (`CopyMonToPC`) |
| Caja de prohibidos (qué va, cuándo se desbloquea) | `src/dualocke.c` (`Dualocke_ShouldBanMon`, `Dualocke_SendMonToBannedBox`); se llama desde `GiveScriptedMonToPlayer` y `GiveCapturedMonToPlayer` (`src/pokemon.c`), `EggHatchSetMonNickname` (`src/egg_hatch.c`) y `TradeMons` (`src/trade.c`) |
| Ventana de vidas en el menú de pausa | `src/start_menu.c` (`ShowDualockeLivesWindow`) |
| Primera captura por zona (estado del encuentro, líneas evolutivas, zonas gastadas) | `src/dualocke.c` (`Dualocke_GetWildEncounterStatus`, `Dualocke_OnBattleStart`) |
| Qué combates son encuentros aleatorios | `src/battle_setup.c` (busca `Dualocke_SetRandomEncounter`) |
| Bloqueo de las Balls y la Safari Ball | `src/item_use.c` (`GetBallThrowableState`) y `src/battle_main.c` (`B_ACTION_SAFARI_BALL`) |
| Aviso al empezar el combate | `src/battle_main.c` (`FIRST_TURN_EVENTS_DUALOCKE_ZONE`) y `data/battle_scripts_1.s` (`BattleScript_DualockeZoneMsg`) |
| Bolsillos de la mochila (Medicinas, Megapiedras) | `include/constants/item.h` (`enum Pocket`), `include/global.h` (`SaveBlock3`), `src/item.c` (`SetBagItemsPointers`), `src/item_menu.c` (busca "Dualocke"), `.pocket` en `src/data/items.h` |
| Documentación oficial de la expansion | `docs/` y https://rh-hideout.github.io/pokeemerald-expansion/ |

Para editar mapas y NPCs de forma visual existe **Porymap**; para scripts y diálogos, **poryscript**.

## 11. Cómo trabajar con Claude en este proyecto

### Para Jorge y Miguel

- Los dos tenéis Claude Pro. El límite de uso se reinicia cada 5 horas y hay otro semanal. Lo que más gasta: conversaciones largas, compilar y tareas de muchos pasos, y la traducción.
- **Repartíos el trabajo** para aprovechar los límites de los dos (por ejemplo, uno la traducción y otro las reglas o el randomizer).
- **Conversaciones nuevas por tarea**, empezando con: *"Lee DUALOCKE.md del repo Jorgemori06/pokeemerald-expansion y luego ayúdame con X"*. Hay que tener la cuenta de GitHub conectada a Claude (Ajustes → Conectores → GitHub).
- Para tareas repetitivas (traducir textos en masa) puede bastar un modelo más ligero.
- **Skills y agentes de Claude recomendados** (y cómo instalarlos): `HERRAMIENTAS_CLAUDE.md`.
- **Ideas para personalizar el juego** cuando esté terminado (no se implementan todavía): `IDEAS.md`.
- Antes de que dos personas toquen lo mismo, hablarlo para no pisarse los cambios. El reparto y el flujo de trabajo están en la sección 13.

### Para Claude

- Idioma: español, tono directo e informal. Jorge y Miguel son estudiantes de ingeniería del software; no hace falta explicar lo básico de programación, pero sí lo específico de GBA o de la decomp.
- **Compila antes de subir** (`make -j$(nproc)`). No subas cambios que no compilen. Si el entorno no tiene el compilador: `sudo apt-get install -y gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi libpng-dev`.
- Commits pequeños, uno por tema, con el mensaje en español explicando qué cambia para el jugador.
- **No trabajes directamente en `master`**: rama por tarea y PR, como dice la sección 13. Antes de empezar, actualiza `master` (`git pull`) por si el otro ha subido algo, y crea la rama desde ahí.
- **Al terminar una sesión**, escribe su registro en `registro/AAAA-MM-DD-nombre-tarea.md` (un archivo nuevo por sesión, ver la sección 13) y súbelo en la misma rama.
- Si no puedes compilar en local, di claramente que no está compilado y deja que lo compruebe el CI del PR antes de fusionar.
- **Actualiza este archivo** cuando se tome una decisión o se termine algo, en el mismo commit.
- No inventes nombres oficiales en español (Pokémon, movimientos, objetos…): búscalos.
- Cuando algo no esté decidido en este archivo, **pregunta** antes de implementarlo, sobre todo si cambia el equilibrio del juego.
- No subas ROMs ni saves, ni datos personales: el repo es público.
- Para actualizar la expansion original: `git remote add rhh https://github.com/rh-hideout/pokeemerald-expansion` y `git pull rhh master` (puede haber conflictos con nuestros cambios). Mejor hacerlo pocas veces y en un commit aparte.

## 12. Paso 1: qué se ha hecho exactamente

- **Mote obligatorio:** ya no hay Sí/No en ningún sitio: al capturar, al recibir un regalo (inicial, iniciales de Johto, Castform, fósiles, Beldum) y al eclosionar un huevo sale un aviso, se abre la pantalla de mote y, si se deja el nombre de la especie (o se borra todo), se vuelve a abrir hasta poner un mote. Los textos cambian de pregunta a orden ("Give X a nickname!"). El Calificanombres también exige un nombre distinto al de la especie, lo que da igual porque todos llevan mote.
- **Tiendas:** se han quitado de todas las tiendas de Hoenn (incluidas Liga, Frontera y Cima Entrenador) los curativos de PS, los de estado (Antídoto, Antiparalizador, Despertar, Antiquemar, Antihielo, Cura Total), los Revivir, las hierbas de la Herboristería de Lavacalda y todos los Objetos X (incluidos Directo y Protección X). **Interpretación:** "curativos" incluye los de estado; si no se quería así, se vuelven a poner.
- **Caramelos Raros a 1 ₽:** se venden en todas las tiendas que vendían curativos u Objetos X (incluida la Herboristería y el mostrador de Objetos X de Grandes Almacenes Calagua, que si no se quedarían vacíos).
- **Objetos X en combate:** el jugador no puede usar Objetos X, Directo, Protección X ni Maxisetas (`EFFECT_ITEM_INCREASE_STAT`, `INCREASE_ALL_STATS`, `SET_FOCUS_ENERGY`, `SET_MIST`). Los entrenadores rivales sí pueden.
- **Correr sin Deportivas** y **Pokédex Nacional** desde el principio de la partida (`NewGameInitData`).
- **MTs reutilizables** y **MOs olvidables** activados por config.

## 13. Cómo trabajamos los dos en paralelo

**Propuesta de Miguel (23/10/2026), confirmada por Jorge.** Desde el 23/10/2026 Miguel es colaborador, así que **los dos trabajan con ramas en este repo** (`jorge/...`, `miguel/...`) y ya no hace falta el fork de Miguel. Regla en `master`: PR obligatorio con una aprobación del otro.

### Preparación (una vez, la hace Jorge)

1. ~~**Añadir a Miguel como colaborador**~~ (hecho): Settings → Collaborators → `Mike360mine`. Así los dos trabajáis con ramas en este mismo repo y no hacen falta forks. Mientras no esté hecho, Miguel trabaja desde su fork `Mike360mine/pokeemerald-expansion` con PRs.
2. ~~**Activar Actions**~~ (hecho): pestaña Actions → *I understand my workflows, go ahead and enable them*. Sin esto, el CI no se ejecuta (GitHub lo desactiva en los forks).
3. **Opcional, recomendado:** Settings → Branches → regla para `master` que exija PR y que el check **CI** esté en verde antes de fusionar. Así nadie sube a `master` algo que no compila.

### Flujo para cada tarea

1. **Reservar la tarea**: poner tu nombre en la tabla del reparto (abajo) o abrir un *issue* en GitHub, y avisar al otro.
2. **Rama nueva desde `master` actualizado:**
   ```bash
   git checkout master && git pull
   git checkout -b jorge/maximo-aro      # o miguel/vidas, etc.
   ```
3. Trabajar con **commits pequeños**, uno por tema, en español.
4. **Compilar** (`make -j$(nproc)`) y, para cambios de juego, **probar en mGBA** lo que has tocado.
5. Actualizar **`DUALOCKE.md`**, tocando solo las líneas de tu tarea (estado, decisiones, mapa del código), y escribir el **registro de la sesión** en `registro/`.
6. `git push -u origin <rama>` y abrir un **PR a `master`**.
7. **El CI tiene que salir en verde.** Los dos tests `CRASH` del log son intencionados y no cuentan.
   - El CI (`.github/workflows/build.yml`) compila Esmeralda (~5 min), la versión release (~6 min) y pasa los tests (~25 min), en paralelo. El check de Esmeralda sale antes que los tests, así que el "compila / no compila" se ve en unos minutos. Se quitaron los trabajos de FireRed y LeafGreen porque no los usamos y tardaban hasta 50 min; si se actualiza desde la expansion original, hay que volver a quitarlos al resolver conflictos en ese archivo.
8. **El otro lo mira por encima** (cinco minutos, sobre todo si cambia el equilibrio del juego) y se fusiona. Después se borra la rama.
9. Si el PR tarda y `master` avanza, actualizar la rama con `git pull origin master` y resolver los conflictos en tu rama, nunca en `master`.

### Registros de sesión (`registro/`)

- **Un archivo nuevo por sesión**: `registro/AAAA-MM-DD-nombre-tarea.md`. Al ser archivos distintos, nunca hay conflictos entre los dos.
- Contenido: qué se pidió, qué se cambió (archivos), decisiones tomadas por el camino, cómo quedó el CI y qué queda pendiente. Ejemplo: `registro/2026-10-23-miguel-paso1.md`.
- `DUALOCKE.md` sigue siendo el resumen del estado actual; el registro es el historial.

### Reparto

Decidido el 23/10/2026 y en marcha: **Miguel se encarga del equilibrio** (dificultad, combates, niveles, equipos) y **Jorge, de las funcionalidades** (sistemas nuevos en el juego y herramientas).

| Tarea | Quién | Zona principal | Choca con |
| --- | --- | --- | --- |
| ~~Paso 1: reglas fáciles y mote obligatorio~~ (hecho, PR #1) | Miguel | — | — |
| **Equilibrio** | | | |
| ~~Reescalado de niveles de entrenadores y salvajes según la curva de la sección 5~~ (hecho, salvo revanchas y postgame) | Miguel | `src/data/trainers.party`, `src/data/wild_encounters.json` | Randomizer, combate con Máximo |
| ~~Equipos de jefes: +1/+2 Pokémon, objetos y qué mega lleva cada jefe~~ (hecho) | Miguel | `src/data/trainers.party` | Randomizer |
| ~~Equipo de Máximo en la Ruta 120~~ (hecho: `TRAINER_STEVEN_ROUTE_120`) | Miguel | `src/data/trainers.party` | Combate con Máximo |
| ~~Parámetros del randomizer~~ (hecho: `tools/dualocke/randomizer_config.json`) | Miguel | archivo de configuración del randomizer | Randomizer |
| ~~Contenido de las tiendas~~ (hecho: principal por ciudad, segundo dependiente, megapiedras por el mapa) | Miguel | listas de las tiendas | Segundo dependiente |
| **Funcionalidades** | | | |
| ~~Vidas + caja de muertos~~ (hecho, PR #4; el aviso al morir lo hizo Miguel) | Jorge | combate (desmayos), PC (`src/pokemon_storage_system.c`), HUD | — |
| ~~Primera captura por zona (+ dupes, sin legendarios, shiny libre)~~ (hecho para los salvajes) | Jorge | `src/dualocke.c`, `src/item_use.c`, `src/battle_main.c` | — |
| ~~Caja de prohibidos (regalos, eventos, fósiles, estáticos, huevos e intercambios)~~ (hecho) | Jorge | `src/dualocke.c`, PC | — |
| ~~Una compra por objeto~~ (hecho por Miguel) | Jorge | `src/shop.c` (compra) | — |
| ~~Evento del combate con Máximo y entrega del Mega-Aro~~ (hecho) | Jorge | `data/maps/Route120/` | Equipo de Máximo |
| ~~Segundo dependiente en las tiendas (mecánica)~~ (hecho por Miguel) | Jorge | `data/maps/*_Mart/`, `src/shop_criteria.c`, `src/shop.c` | Contenido de las tiendas |
| Randomizer con semilla (la herramienta; hechos la semilla, los salvajes y los entrenadores) | Jorge | script nuevo en `tools/` + `Makefile` | Todo lo de equilibrio en `trainers.party` y `wild_encounters.json` |
| Traducción (empezada por Miguel: nombres oficiales, sección 8) | Por decidir, cuando lo demás esté estable | casi todo `data/` y `src/` | Todo |

Cómo encajan las dos partes:

- **Los niveles y el tamaño de los equipos los pone Miguel a mano** en `trainers.party` y `wild_encounters.json`. **El randomizer de Jorge los respeta**: solo cambia especies, movimientos, habilidades y objetos, y lee sus parámetros de un archivo de configuración cuyos valores decide Miguel.
- **Máximo:** Jorge hace el evento (script, mapa, entrega del aro) y Miguel decide su equipo. Hay que acordar el nombre del entrenador (`TRAINER_...`) antes de empezar.
- **Segundo dependiente:** Jorge hace la mecánica y Miguel decide qué vende. Hay que acordar el formato de las listas antes de empezar.
- **Choques en archivos:** `trainers.party` lo tocan los dos (Miguel los niveles y equipos, Jorge solo la entrada nueva de Máximo si hace falta). `src/shop.c` ya solo lo toca Jorge.
- **Traducción:** toca casi todos los archivos de texto. Mejor empezarla cuando las reglas estén cerradas, o en una rama larga que se actualice a menudo desde `master`.
- **Decisiones:** las de equilibrio las toma Miguel y las demás quien implemente esa parte, hablándolo antes con el otro. Ya decididas por Jorge (23/10/2026): el aro lo da Máximo en la Ruta 120 y la lista de jefes con mega (sección 6). Pendiente: la ROM española (sección 9).
