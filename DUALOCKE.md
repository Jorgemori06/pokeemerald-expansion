# Proyecto Dualocke: contexto completo

Este archivo resume **todo lo decidido y hecho** en el proyecto, para que cualquiera de los dos (o el Claude de cualquiera de los dos) pueda retomarlo sin haber visto las conversaciones anteriores.

> **Si eres Claude y te acaban de pedir que leas este archivo:** léelo entero antes de tocar nada. Al final hay una sección con instrucciones de trabajo para ti. Cuando cambies algo importante del proyecto, actualiza también este archivo en el mismo commit.

Última actualización: 23/10/2026.

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

### Entorno (Windows)

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
- **Nick Clause:** todos los Pokémon llevan mote.
- **Items Clause:**
  - No se pueden comprar objetos curativos ni Objetos X en las tiendas.
  - Se pueden usar curativos en combate si se han encontrado durante la aventura.
  - No se pueden usar Objetos X en combate.
  - Solo se puede comprar una unidad de cada objeto por tienda, salvo Balls, Repelentes y Bayas (y los Caramelos Raros, ver sección 6).
  - No se pueden farmear objetos.
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
| Una compra por objeto (salvo Balls, Repelentes, Bayas, Caramelos) | Limitar compras en tiendas | Medio | Pendiente |
| 20 vidas + caja de muertos | Contador de vidas en el menú de pausa y caja bloqueada | Medio | **Hecho** (aviso al morir pendiente) |
| Primera captura por ruta + dupes + sin legendarios + shiny libre | El juego bloquea lanzar Balls cuando no se puede capturar | Medio | Pendiente |
| Victoria, combates en Showdown, capturas extra | Fuera del juego, por honor | — | — |
| No farmear | Por honor | — | — |

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
  - **Líderes de gimnasio:** el equipo entero al cap.
  - **Alto Mando:** Sidney 92, Fátima 94, Nívea 95 y Dracón 97, el equipo entero a ese nivel. **Plubio** 100 y **Blasco** en Calle Victoria 90.
  - **Jefes a mitad de tramo** (rival, Magno, Aquiles, Blasco en Malvalona): el equipo entero 3 niveles por encima de los entrenadores de ese punto, sin pasar del cap.
  - **Salvajes:** los entrenadores de su zona − 3, con un margen de ±2. Las tres cañas dan el mismo nivel.
- **Sin reescalar todavía:** revanchas (Match Call), postgame (Cueva de Máximo, Frente Batalla, S.S. Marea, Cueva Ancestral, Cueva Alterada, Túnel del Desierto) y la Casa Trampa.
- **Evoluciones de los entrenadores normales (hecho):** `tools/dualocke/evolucionar_entrenadores.py` evoluciona sus Pokémon según el nivel. Las evoluciones por nivel van a su nivel normal; las que no son por nivel (piedra, amistad…) van a 30 la primera y a 40 la segunda. Los tres scripts se lanzan en orden: `reescalar_niveles.py`, `equipos_jefes.py` y `evolucionar_entrenadores.py`.
- El randomizer **no debe tocar los niveles ni el tamaño de los equipos**: solo especies, movimientos, habilidades y objetos. Al cambiar especies, debe mantener la regla de evolucionar según el nivel.

## 6. Megas, tiendas y evoluciones

### Megaevoluciones

- Las megas están activadas en el motor, incluidas las de Z-A (`P_MEGA_EVOLUTIONS`, `P_GEN_9_MEGA_EVOLUTIONS`).
- Para megaevolucionar, el jugador necesita el objeto **Aro Mega** (`ITEM_MEGA_RING`) en la mochila (lo comprueba `src/battle_util.c`).
- **Cómo se consigue el aro (decidido el 23/10/2026):** combate con **Máximo en la Ruta 120**, justo antes del gym 6 (Alana). Al ganar, te da el aro. Encaja con la historia (en ROZA Máximo está metido en lo de las megas) y llega en un punto equilibrado: equipo ya formado, cap 62, toda la segunda mitad del juego para usarlas.
- **Desde que el jugador tiene el aro, todos los jefes llevan un Pokémon con mega** (y la usan). Lista de "jefes" (decidida el 23/10/2026): líderes de gimnasio, Alto Mando, Plubio, rival (Bruno/Aura), Blasco y los líderes Magma/Aqua (Magno, Aquiles).
- **Equipos de los jefes (hecho, Miguel, 23/10/2026)** con `tools/dualocke/equipos_jefes.py` (se lanza después de `reescalar_niveles.py`):
  - **+2 Pokémon** a líderes, Alto Mando y Plubio; **+1** al rival, Blasco, Magno, Aquiles y los admins (Tatiano, Silvina, Matías). Máximo 6.
  - Los huecos nuevos son Pokémon **del tipo del jefe**; los originales **evolucionan** según su nivel. El randomizer los cambiará igualmente.
  - **Megas canónicas** desde el aro (el as, último del equipo, lleva su megapiedra): Alana Altaria, Vito y Leti Metagross, Galano Starmie, Sidney Absol, Fátima Banette, Nívea Glalie, Dracón Salamence, Plubio Gyarados, Blasco Gardevoir, Magno Camerupt, Aquiles Sharpedo y el rival su inicial (desde Ciudad Calagua).
  - **Objetos:** solo se añade la megapiedra; los que ya llevaban (Baya Zidra…) se quedan, y el resto lo pondrá el randomizer.
  - Los rivales y la IA megaevolucionan sin aro, con solo llevar la piedra.
- Las **megapiedras** se consiguen:
  - Aleatorias entre los objetos del suelo.
  - En el **segundo dependiente** de cada tienda (ver abajo).

### Tiendas

Cada tienda tendrá **dos dependientes**:

1. **Principal:** lo de siempre (Balls, Repelentes, etc.), **sin curativos ni Objetos X**, y con **Caramelos Raros a 1 ₽**.
2. **Secundario:** objetos **aleatorios** (distintos en cada partida/semilla), garantizando algún objeto evolutivo. **Desde que el jugador consiga el aro**, este dependiente vende además **2-3 megapiedras aleatorias**, en todas las ciudades, incluidas las ya visitadas.

Regla de compra: una unidad de cada objeto por tienda, salvo Balls, Repelentes, Bayas y Caramelos Raros.

### Evoluciones por intercambio (hecho)

Como no hay intercambios entre partidas, se han cambiado todas:

- **Las que solo pedían intercambio ahora son por nivel:**
  - Alakazam: 36
  - Machamp, Golem, Golem de Alola, Gengar, Gigalith, Conkeldurr: 38
  - Trevenant, Gourgeist (todos los tamaños), Escavalier, Accelgor: 32
- **Las que pedían intercambio con objeto equipado ahora evolucionan usando el objeto desde la mochila, como una piedra:** Steelix y Scizor (Revestimiento Metálico), Politoed y Slowking (Roca del Rey), Kingdra (Escama Dragón), Porygon2 (Mejora), Porygon-Z (Disco Extraño), Rhyperior (Protector), Electivire (Electrizador), Magmortar (Magmatizador), Dusknoir (Tela Terrible), Huntail (Diente Marino), Gorebyss (Escama Marina), Milotic (Escama Bella), Aromatisse (Saquito Fragante), Slurpuff (Dulce de Nata).

### Gimmicks desactivados

**Z, Dinamax y Tera no se usan.** No hace falta tocar el código: solo se activan con objetos (Pulsera Z, Maximuñequera, Orbe Teracristal) que no se pueden conseguir. El randomizer debe **excluir** del reparto esos objetos, los cristales Z, las teralitas y los Maxisetas.

## 7. Randomizer (pendiente, el trabajo grande)

### Diseño

- **Script propio** (Python) que baraja los datos del juego **antes de compilar**, usando una **semilla**.
- **Cada jugador tiene una partida completamente distinta**: cada uno compila con su semilla, por ejemplo `make SEED=jorge123` y `make SEED=miguel456`. La semilla también sirve para regenerar exactamente la misma partida si hace falta.
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
- Iniciales aleatorios (forma base de 3 fases y en triángulo de tipos, ver arriba).
- Habilidades aleatorias, permitiendo Superguarda.
- Pokémon estáticos completamente aleatorios.
- Estadísticas base de Gen 9 (ya vienen así en el motor) sin aleatorizar sus valores.
- Totales de estadísticas base barajados siguiendo las líneas evolutivas.
- Pokémon de los entrenadores aleatorios, sin duplicados dentro de un mismo equipo.
- El inicial del rival se mantiene durante toda la aventura.
- Los equipos de los entrenadores evolucionan según el nivel y pueden usar formas alternativas.
- +1 Pokémon a los entrenadores importantes y +2 a los jefes.
- Los Pokémon de entrenadores importantes y jefes pueden llevar objetos aleatorios, priorizando objetos coherentes.
- **Nuevo:** el as de cada jefe es de su tipo y, desde el aro, una especie con mega de ese tipo con su megapiedra (ver arriba).

**Salvajes**
- Aleatorios por ubicación: cada especie de una zona se sustituye por otra aleatoria (mapeo 1 a 1 por zona).
- (En Platino se mantenían los encuentros por hora del día; Esmeralda no tiene encuentros por hora, así que no aplica.)
- Pueden llevar objetos aleatorios.
- Niveles según la curva de la sección 5 (sustituye al "+10%").
- Sin legendarios en salvajes.

**Entrenadores y combates**
- Niveles según la curva de la sección 5 (sustituye al "+15%").
- Movimientos aleatorios con 3 movimientos garantizados y una ligera preferencia por movimientos dañinos potentes.
- Mejores movimientos y diversidad de tipos en jefes, importantes y normales.
- Combates individuales.

**Movimientos**
- Movimientos de Gen 9 (ya vienen así).
- MTs aleatorias con compatibilidad completamente aleatoria, conservando los movimientos de campo y comprobando los aprendibles por nivel.
- Tutores aleatorios con compatibilidad aleatoria, conservando los movimientos de campo.

**Objetos**
- Objetos del suelo aleatorios (incluyendo megapiedras).
- Objetos del segundo dependiente aleatorios, con objetos evolutivos garantizados (ver sección 6).
- Objetos de Recogida aleatorios.
- Intercambios internos totalmente aleatorios (Pokémon dado y pedido, objetos, IVs, motes, entrenador original).
- Precios equilibrados y Caramelos Raros a 1 ₽.

**Ajustes adicionales**
- Pokédex Nacional desde el principio.
- Nombres de Pokémon en minúsculas (normal en la expansion).
- Niveles de los estáticos según la curva.
- Correr sin Deportivas.
- Barras de PS y experiencia rápidas (ya activado por defecto: `B_FAST_HP_DRAIN`, `B_FAST_EXP_GROW`).
- MTs reutilizables (`I_REUSABLE_TMS` en `include/config/item.h`).
- MOs olvidables.

## 8. Traducción al español (pendiente)

Decisión: empezar en inglés y traducir en paralelo o después. La traducción y los cambios de jugabilidad tocan cosas distintas, así que se puede pasar el español por encima cuando esté listo.

### Tamaño

Texto en la versión actual de la expansion (medido con un script):

- ~184.000 palabras en `data/` (diálogos y scripts de mapas).
- ~30.000 palabras en `src/` (menús, combate, nombres, descripciones).

En total, unas 210.000 palabras: más o menos dos novelas largas.

### Plan

1. **Nombres oficiales** de Pokémon, movimientos, habilidades, objetos, tipos y naturalezas. No inventarlos: sacarlos de listas oficiales.
2. **Mensajes de combate, menús y gráficos con texto:** reaprovechar la traducción de Heart & Soul ([SergioBonet/hns_es](https://github.com/SergioBonet/hns_es)), que tradujo este mismo motor (aunque una versión algo anterior). Incluye los arreglos de código para artículos y concordancias ("¡El Pikachu salvaje usó…!") y los gráficos con texto (iconos de tipo, barras de PS/Nv…).
3. **Diálogos de Hoenn:** lo ideal es sacarlos con un script de una copia de la **Esmeralda española oficial**. Es mucho más barato en uso de Claude que traducirlos y son los textos oficiales. Si no hay ROM española, se traducen.
4. **Pruebas jugando:** recuadros donde no cabe el texto, frases sin traducir, erratas.

### Dificultades técnicas

- Cada línea tiene que caber en el recuadro (ancho en píxeles de la fuente de GBA), y el español ocupa más que el inglés. Hay que recolocar saltos de línea; se puede automatizar.
- No romper los códigos dentro del texto: `{PLAYER}`, `{STR_VAR_1}`, colores, pausas, etc.
- Mensajes de combate montados por trozos que necesitan cambios de código para el género y los artículos.

Hubo una traducción antigua de la expansion al castellano (fork de Xhyzi, rama `pokeemerald-expansion-es`, compilando con `LANG=ES`), pero tiene más de tres años y no sirve tal cual.

## 9. Estado y siguientes pasos

### Hecho

- Fork montado y compilando (en Windows/WSL y en el entorno de Claude).
- Level caps duros con la curva de la sección 5.
- Caramelos Raros limitados por el cap.
- Evoluciones por intercambio convertidas (sección 6).
- Paso 1 del orden de trabajo (detalles en la sección 12).
- Vidas y caja de muertos (Jorge). Cómo funciona:
  - Se empieza con 20 vidas (`VAR_DUALOCKE_LIVES`). Cada Pokémon que acaba un combate debilitado muere: va a la última caja del PC ("DEAD", la 14) y se resta una vida.
  - Con 0 vidas se sigue jugando; la siguiente muerte pierde el locke (`FLAG_DUALOCKE_LOCKE_LOST`). Perder un combate también lo pierde, sin mover a nadie (el equipo no puede quedarse vacío). El juego no se bloquea: se marca y se ve en el menú.
  - El menú de pausa muestra "Lives: N" o "LOCKE LOST".
  - La caja de muertos solo deja ver el resumen: no se puede sacar, mover, soltar ni meter nada, y los Pokémon nuevos nunca van ahí.
  - Los objetos de revivir no se pueden usar en combate.
  - No cuentan: Frontera, Pirámide, Pike, Cima Entrenador, combates por cable, Safari, el primer combate y las bases secretas.
  - Tests en `test/dualocke.c` (`make check TESTS="Dualocke"`).
  - Pendiente: un aviso al morir ("X ha muerto, te quedan N vidas"); de momento solo se ve que desaparece del equipo y en el menú.

### Pendiente de decidir

- ¿Se consigue la **ROM de Esmeralda española** para los diálogos oficiales?

### Orden de trabajo propuesto

1. ~~Lo fácil: mote obligatorio, quitar curativos y Objetos X de las tiendas, Caramelos Raros a 1 ₽, bloquear Objetos X en combate, correr sin Deportivas, Pokédex Nacional desde el inicio, MTs reutilizables, MOs olvidables.~~ **Hecho.**
2. Combate con Máximo y el aro. Segundo dependiente en las tiendas.
3. Reglas del locke: vidas + caja de muertos, primera captura por ruta con sus excepciones, límite de una compra por objeto.
4. Randomizer con semilla + reescalado de niveles.
5. Traducción.

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
| Reescalado de niveles por tramos (tabla de mapas y reglas) | `tools/dualocke/reescalar_niveles.py` |
| Equipos de los jefes (+1/+2, megas) | `tools/dualocke/equipos_jefes.py` |
| Evolución por nivel de los entrenadores normales | `tools/dualocke/evolucionar_entrenadores.py` |
| Entrenadores | `src/data/trainers.party` |
| Tiendas | scripts de cada mapa en `data/maps/*/scripts.inc` (`pokemart`) |
| Comprobación del Aro Mega | `src/battle_util.c` (busca `ITEM_MEGA_RING`) |
| Datos al empezar partida nueva (correr, Pokédex Nacional) | `src/new_game.c` (`NewGameInitData`) |
| Mote obligatorio al capturar | `src/battle_script_commands.c` (`Cmd_trygivecaughtmonnick`) |
| Mote obligatorio en regalos | `src/tv.c` (`ChangeBoxPokemonNickname_CB`) y scripts con `gText_NicknameThisPokemon` |
| Mote obligatorio al eclosionar | `src/egg_hatch.c` (`EggHatchSetMonNickname`, estado 9 de `CB2_EggHatch`) |
| Objetos que no se pueden usar en combate | `src/item_use.c` (`CannotUseItemsInBattle`) |
| MTs reutilizables | `include/config/item.h` (`I_REUSABLE_TMS`) |
| MOs olvidables | `include/config/pokemon.h` (`P_CAN_FORGET_HIDDEN_MOVE`) |
| Filtrar tiendas por medallas/flags (útil para las megapiedras) | `src/shop_criteria.c` |
| Vidas y caja de muertos | `src/dualocke.c`, `include/dualocke.h`; se llama desde `src/battle_setup.c` (final de combate) |
| Bloqueo de la caja de muertos | `src/pokemon_storage_system.c` (busca `Dualocke_IsDeadBox`) y `src/pokemon.c` (`CopyMonToPC`) |
| Ventana de vidas en el menú de pausa | `src/start_menu.c` (`ShowDualockeLivesWindow`) |
| Documentación oficial de la expansion | `docs/` y https://rh-hideout.github.io/pokeemerald-expansion/ |

Para editar mapas y NPCs de forma visual existe **Porymap**; para scripts y diálogos, **poryscript**.

## 11. Cómo trabajar con Claude en este proyecto

### Para Jorge y Miguel

- Los dos tenéis Claude Pro. El límite de uso se reinicia cada 5 horas y hay otro semanal. Lo que más gasta: conversaciones largas, compilar y tareas de muchos pasos, y la traducción.
- **Repartíos el trabajo** para aprovechar los límites de los dos (por ejemplo, uno la traducción y otro las reglas o el randomizer).
- **Conversaciones nuevas por tarea**, empezando con: *"Lee DUALOCKE.md del repo Jorgemori06/pokeemerald-expansion y luego ayúdame con X"*. Hay que tener la cuenta de GitHub conectada a Claude (Ajustes → Conectores → GitHub).
- Para tareas repetitivas (traducir textos en masa) puede bastar un modelo más ligero.
- **Skills y agentes de Claude recomendados** (y cómo instalarlos): `HERRAMIENTAS_CLAUDE.md`.
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

Decidido por Miguel el 23/10/2026 (pendiente de que Jorge lo confirme): **Miguel se encarga del equilibrio** (dificultad, combates, niveles, equipos) y **Jorge, de las funcionalidades** (sistemas nuevos en el juego y herramientas).

| Tarea | Quién | Zona principal | Choca con |
| --- | --- | --- | --- |
| ~~Paso 1: reglas fáciles y mote obligatorio~~ (hecho, PR #1) | Miguel | — | — |
| **Equilibrio** | | | |
| ~~Reescalado de niveles de entrenadores y salvajes según la curva de la sección 5~~ (hecho, salvo revanchas y postgame) | Miguel | `src/data/trainers.party`, `src/data/wild_encounters.json` | Randomizer, combate con Máximo |
| ~~Equipos de jefes: +1/+2 Pokémon, objetos y qué mega lleva cada jefe~~ (hecho) | Miguel | `src/data/trainers.party` | Randomizer |
| Equipo de Máximo en la Ruta 120 | Miguel | `src/data/trainers.party` | Combate con Máximo |
| ~~Parámetros del randomizer~~ (hecho: `tools/dualocke/randomizer_config.json`) | Miguel | archivo de configuración del randomizer | Randomizer |
| Contenido de las tiendas: precios, objetos del segundo dependiente, qué megapiedras y cuándo | Miguel | listas de las tiendas | Segundo dependiente |
| **Funcionalidades** | | | |
| Vidas + caja de muertos | Jorge (pendiente de empezar) | combate (desmayos), PC (`src/pokemon_storage_system.c`), HUD | — |
| Primera captura por ruta (+ dupes, sin legendarios, shiny libre) | Jorge | `src/item_use.c` (Balls), `src/battle_script_commands.c`, flags por zona | — |
| Una compra por objeto | Jorge | `src/shop.c` (compra) | — |
| Evento del combate con Máximo y entrega del Aro Mega | Jorge (pendiente de empezar) | `data/maps/Route120/` | Equipo de Máximo |
| Segundo dependiente en las tiendas (mecánica) | Jorge | `data/maps/*_Mart/`, `src/shop_criteria.c`, `src/shop.c` | Contenido de las tiendas |
| Randomizer con semilla (la herramienta) | Jorge (pendiente de empezar) | script nuevo en `tools/` + `Makefile` | Todo lo de equilibrio en `trainers.party` y `wild_encounters.json` |
| Traducción | Por decidir, cuando lo demás esté estable | casi todo `data/` y `src/` | Todo |

Cómo encajan las dos partes:

- **Los niveles y el tamaño de los equipos los pone Miguel a mano** en `trainers.party` y `wild_encounters.json`. **El randomizer de Jorge los respeta**: solo cambia especies, movimientos, habilidades y objetos, y lee sus parámetros de un archivo de configuración cuyos valores decide Miguel.
- **Máximo:** Jorge hace el evento (script, mapa, entrega del aro) y Miguel decide su equipo. Hay que acordar el nombre del entrenador (`TRAINER_...`) antes de empezar.
- **Segundo dependiente:** Jorge hace la mecánica y Miguel decide qué vende. Hay que acordar el formato de las listas antes de empezar.
- **Choques en archivos:** `trainers.party` lo tocan los dos (Miguel los niveles y equipos, Jorge solo la entrada nueva de Máximo si hace falta). `src/shop.c` ya solo lo toca Jorge.
- **Traducción:** toca casi todos los archivos de texto. Mejor empezarla cuando las reglas estén cerradas, o en una rama larga que se actualice a menudo desde `master`.
- **Decisiones:** las de equilibrio las toma Miguel y las demás quien implemente esa parte, hablándolo antes con el otro. Ya decididas por Jorge (23/10/2026): el aro lo da Máximo en la Ruta 120 y la lista de jefes con mega (sección 6). Pendiente: la ROM española (sección 9).
