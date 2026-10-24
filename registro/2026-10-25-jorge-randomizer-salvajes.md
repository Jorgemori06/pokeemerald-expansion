# 25/10/2026 · Jorge · Randomizer (1): semilla y salvajes

Sesión de Jorge con Claude. Rama `jorge/randomizer`. Primera parte del randomizer (sección 7 de `DUALOCKE.md`): la herramienta con la semilla y los Pokémon salvajes.

## Decisiones de Jorge

- **Opción A** de las que se valoraron: el randomizer va al compilar, con semilla. Las otras eran un randomizer dentro del juego (como Heart & Soul) y un programa aparte que modificase la ROM.
- **La semilla no se elige: es aleatoria.** `make` se inventa una la primera vez y la guarda, para que actualizar el juego no cambie la partida en curso. `make nueva-partida` da otra.

## Cómo funciona

- **Uso:**
  - `make`: partida randomizada.
  - `make nueva-partida`: partida nueva.
  - `make SEED=x`: una semilla concreta.
  - `make SIN_RANDOM=1`: el juego sin randomizar.
  - `make check` nunca randomiza.
- **La semilla** se guarda en `dualocke_semilla.txt`, en la raíz del repo. Está en `.gitignore`, así que no se sube. Las semillas son números de hasta 10 cifras.
- **No se toca ningún archivo del repo.** `tools/dualocke/randomizer.py` lee los originales (los de Miguel) y escribe en `build/dualocke/`:
  - `wild_encounters.json`, el barajado, que es el que se compila;
  - `solucionario.json`, lo que ha salido (no abrir si no quieres destriparte la partida).
- **Makefile** (bloque "Dualocke: randomizer con semilla"):
  - decide la semilla y se la pasa al `make generated` interno;
  - `build/dualocke/semilla.txt` cambia cuando cambia la semilla, así que se regenera lo que dependa de ella, también al pasar de randomizado a sin randomizar y al revés;
  - `wild_encounters_to_header.py` acepta otro JSON de entrada (cambio mínimo en el script de la expansion).
- **Datos de las especies** (`tools/dualocke/aleatorio/especies.py`): se pasa `src/pokemon.c` por el preprocesador de C con la misma configuración que al compilar, y se leen `gSpeciesInfo`, las tablas de formas, las de cambios de forma y los alias del enum (`SPECIES_ALCREMIE`…). Así las evoluciones, formas y legendarios son exactamente los de la ROM, sin leer los `#if` a mano.
- **Salvajes** (`tools/dualocke/aleatorio/salvajes.py`), con las reglas de `randomizer_config.json`:
  - En cada mapa, cada especie original se cambia por una **línea** al azar. Es la misma en hierba, agua, pesca y Golpe Roca, y con la misma rama en todos los huecos.
  - **Sin legendarios ni singulares** en ninguna fase de la línea. Los Ultraentes y los paradójicos sí pueden salir.
  - La especie se ajusta a la **fase que le toca por el nivel mínimo** del hueco, con las mismas reglas que los entrenadores: por nivel, a su nivel; piedra, amistad…, a 30 la primera y a 40 la segunda. Si hay varias ramas, una al azar.
  - **No se repiten líneas** entre zonas hasta usarlas todas (hay unas 470).
  - Pueden salir formas regionales. No salen megas, Gigamax, totémicos, formas de combate (Darmanitan Zen…) ni formas cosméticas (las de Vivillon, Alcremie…, salvo la primera).
  - Solo los mapas de Hoenn: la Pirámide y el Pike se quedan como están.
  - **Antes de escribir nada, comprueba el resultado:** que solo cambian las especies, que existen y que no hay legendarios. Si algo falla, para la compilación.

## Pruebas

- Misma semilla, mismo resultado; otra semilla, otro resultado (comprobado con el script y con el md5 de la ROM).
- `make` en limpio con semilla al azar: compila.
- Segundo `make` (misma semilla): misma ROM.
- `make SIN_RANDOM=1`: vuelven los salvajes originales.
- `make nueva-partida`: semilla nueva.
- `make check` (sin randomizar): ver el PR.
- **No probado jugando.**

## Decisiones de Claude por el camino (revisables)

- La fase por el **nivel mínimo** del hueco, para que nunca salga una evolución antes de su nivel.
- **Mapeo por mapa**, no por zona del mapa regional: Cueva Granito 1F y B1F pueden tener especies distintas. La regla de captura sigue siendo una por zona.
- Evoluciones que no son por nivel ni por objeto (girar con Milcery, golpes críticos de Farfetch'd de Galar…): no se aplican, igual que en el script de entrenadores de Miguel.

## Pendiente

- Fases 3-5: entrenadores (con el as de los jefes y las megas), iniciales y estáticos (Kecleon, regalos…), movimientos, habilidades y objetos.
- **Para Miguel:** su `instalar_windows.ps1` compila con `make`, así que ya saldrá randomizado. Le falta una opción para pedir una partida nueva (`make nueva-partida`).
