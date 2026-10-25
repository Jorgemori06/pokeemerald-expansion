# 24/10/2026 · Miguel · Nombres oficiales en español (traducción, paso 1)

Rama `miguel/nombres-oficiales`. **No cambia el juego:** prepara las tablas para que la traducción no invente nombres.

## Lo que se hizo

- **Fuente:** los CSV de PokéAPI (`github.com/PokeAPI/pokeapi`, carpeta `data/v2/csv`), con permiso de Miguel para descargarlos.
  - Se usa el idioma 7 (español de España). Son unos 1,6 MB.
  - Están en la carpeta temporal de la sesión, no en el repo.
- **`tools/dualocke/nombres_oficiales.py`:**
  1. Para cada constante del juego, saca su nombre inglés del código (`moves_info.h`, `items.h`, `abilities.h`, `types_info.h`, `pokemon.c` y `species_info`).
  2. Lo empareja con el nombre inglés de PokéAPI; si no lo encuentra, prueba con el identificador.
  3. Saca el nombre oficial en español.
  - Las especies van por número de la Pokédex Nacional, porque las formas comparten nombre.
- **Resultado en `traduccion/nombres/`:** un CSV por categoría (`constante, ingles, espanol, caracteres, cabe_en_N`) y `PENDIENTES.md`.

| Categoría | Total | Sin nombre oficial | No caben |
| --- | --- | --- | --- |
| Especies | 1013 | 0 | 0 |
| Movimientos | 934 | 33 (Gigamax) | 28 (casi todos movimientos Z) |
| Objetos | 873 | 15 (de Leyendas Arceus y Escarlata/Púrpura, no salen en el juego) | 0 |
| Habilidades | 319 | 5 (3 nuevas de Z-A y 2 huecos) | 2 |
| Tipos | 20 | 0 | 2 (Eléctrico, Siniestro) |
| Naturalezas | 25 | 0 | 0 |

- **Comprobado a mano:** Caramelo Raro, Restos, Vidasfera, Periscopio, Rayo, Terremoto, Teraexplosión, Melenaleteo… PokéAPI da los nombres tal como salen en los juegos, con sus abreviaturas oficiales (Mineral Evol).

## Hallazgos

- En la documentación había nombres escritos de memoria que no son los oficiales: **Mega-Aro** (no "Aro Mega") y **Repelente Máximo** (no "Máximo Repelente"). A partir de ahora, consultar estas tablas.

## Queda (traducción)

- **Abreviar o subir el límite** de los que no caben y sí se usan: 4 movimientos, 2 habilidades y 2 tipos.
- **Nombres de las 3 habilidades nuevas de Z-A:** buscarlos en otra fuente oficial.
- **Paso 2:** reaprovechar la traducción de Heart & Soul para menús y mensajes de combate.
- **Paso 3:** diálogos de Hoenn, desde la Esmeralda española si se consigue.
- **Aplicar los nombres** en el código: es otro paso, cuando lo demás esté estable.
