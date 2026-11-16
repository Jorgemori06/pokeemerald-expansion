# 16/11/2026 — Miguel: las islas del ferry

## Qué se pidió

Miguel, después del análisis de zonas (`ZONAS.md`, #80): "Empieza por las islas de los ferrys". Lo que decidió:

- **Desbloqueo:** una por medalla (ISLA SUR con la 6.ª, ISLA LEJANA con la 7.ª, ISLA ORIGEN y ROCA OMBLIGO con la 8.ª).
- **Legendarios:** "sustituirlos por Pokémon fuertes (pseudos, Pokémon con mega o Gigamax) capturables y que den recompensa".

## Qué se ha hecho

- **Ferry:** el encargado del puerto de CALAGUA da el billete de cada isla según las medallas y el ferry ya no pide la Liga (`data/scripts/dualocke_islas.inc`). El billete cuenta como ya enseñado, para que la isla salga en la lista de destinos en vez de zarpar directamente.
- **Pokémon fuerte en cada isla** (Salamence, Tyranitar, Metagross, Charizard y Gyarados sin semilla), con la sprite de la especie que sale de verdad (`Dualocke_GraficoPokemonIsla`) y premio al vencerlo o capturarlo: un objeto fijo y su megapiedra si tiene (`Dualocke_MegapiedraPokemonIsla`).
  - Los legendarios siguen en los mapas, pero siempre ocultos: el código del juego usa sus objetos (el Mew que se esconde en la hierba, el puzle de Deoxys).
- **Randomizer:** `islas()` en `estaticos.py` sortea esos cinco aparte, entre líneas de 600 o más de estadísticas base o con mega. Los mapas de las islas no entran en el sorteo general, así que los demás estáticos de las semillas en curso salen igual.
- **Niveles:** regla nueva `"tope"` en `reescalar_niveles.py` (cap − 3: 70, 81 y 97). Las islas tienen tramo (7, 8 y 9).
- **Entrenadores:** 6 que no salían en ningún mapa (TERRY, CINDY_2, MIKE_1, AMY_AND_LIV_3, GINA_AND_MIA_2, LUCAS_2).
  - No cuentan para la banda de su tramo (`ENTRENADORES_ISLAS`): la primera prueba los metía y cambiaba el nivel de cientos de entrenadores y salvajes.
  - Comprobado: con la cadena de scripts solo cambian esos 6.
- **Salvajes:** `tools/dualocke/zonas_nuevas.py`, que va después de `reescalar_niveles.py` (este reescribe `wild_encounters.json` desde la base). Las tablas van al final del archivo.
- **Objetos:** 11, con `colocar_objetos.py` (`OBJETOS_ISLAS`). El script ya acepta flags libres del sistema (formato `(SYSTEM_FLAGS + 0x..)`).
- **Textos:** los del ferry y los marineros de las islas estaban en inglés (eran de postgame). Traducidos en `traduccion/dialogos/41_islas_ferry.tsv`. Los nuevos, escritos directamente en español y medidos (caben en 208 px).

## Cómo se comprobó

- **No se ha compilado** (sin WSL). Lo tiene que compilar Jorge.
- La cadena de niveles (`reescalar_niveles.py` → `zonas_nuevas.py` → `equipos_jefes.py` → `evolucionar_entrenadores.py` → `ia_entrenadores.py`) se ha lanzado entera: sin las islas daba exactamente lo que hay en el repo, y con ellas solo cambian los 6 entrenadores y se añaden las tablas al final.
- `dialogos.py comprobar`: 0 errores.
- El sorteo de las islas, probado con una Pokédex de prueba: solo elige especies fuertes, no repite y da lo mismo con la misma semilla.
- Las casillas de los entrenadores y los Pokémon se han elegido mirando por dónde se puede andar (mapas dibujados con `ver_mapa.py`). Falta verlo en el juego.
