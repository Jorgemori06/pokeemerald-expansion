# 18/11/2026 — Jorge: tantas habilidades como en el original

**Qué se pidió:** Miguel decidió (vía Jorge) que cada Pokémon tenga tantas habilidades como en los juegos originales, distintas entre sí: si tiene dos y la oculta, pues tres. Antes (#27) era una sola en todos los huecos, y el Parche y la Cápsula Habilidad no servían.

**Qué se hizo:**
- `aleatorio/especies.py` guarda los 3 huecos originales (`huecos_habilidad`), con los vacíos.
- `aleatorio/habilidades.py`: el primer hueco sale con el mismo sorteo que antes; los demás huecos que tenga la especie, con otro RNG (`{semilla}|habilidades|huecos`), sin repetir y sin las de relleno. Los huecos que en el original eran la misma habilidad (megas) siguen siendo la misma.
- `cabecera.py` genera `sDualockeHabilidades[NUM_SPECIES][3]`; `Dualocke_HabilidadesAleatorias` y `Dualocke_HabilidadAleatoria(especie, hueco)` en `src/dualocke_aleatorio.c`; `GetSpeciesAbility` (`src/pokemon.c`) la usa por hueco.
- Test de "sin semilla" adaptado.

**Comprobado:**
- `make` y `make check TESTS="Dualocke"` (62/62).
- Solucionario con las dos semillas de la versión 8 contra la 8.2: todo igual salvo las habilidades; la primera de cada especie no cambia en ninguna de las 1571.
- Las 1571 especies tienen los mismos huecos vacíos y repetidos que en el original (1, 2 o 3 habilidades distintas).

**Efecto en las partidas:** siguen valiendo (no cambia nada guardado). Los Pokémon con el hueco 1 o el oculto pasan a tener su habilidad nueva; los del hueco 0, la misma que tenían.

**Pendiente:** nada de esto.
