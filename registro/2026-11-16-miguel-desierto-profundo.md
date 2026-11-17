# 16/11/2026 — Miguel: DESIERTO PROFUNDO, RUINAS ARENOSAS y el comprobador

## Qué se pidió

1. "Let's continue with the deep desert and some ruins".
2. Después: "mira lo que hemos hecho y mejóralo, mejores mapas, más editados y completos, que nada falle… y vas implementando lo que hemos planteado".

## Qué se ha hecho

- **`tools/dualocke/crear_desierto_profundo.py`** crea tres mapas.
  - **DESIERTO PROFUNDO:** el desierto de la RUTA 111 limpio (sin la TORRE ESPEJISMO ni los huecos de base secreta), con tormenta de arena.
  - **RUINAS ARENOSAS y su CÁMARA:** las plantas 1 y 4 de la TORRE ESPEJISMO.
  - **Entrada:** un montículo con puerta en el desierto de la RUTA 111, copia del de las RUINAS DESIERTO. El borde este del desierto es roca, así que no se podía conectar por el borde.
- **Guardián** en la CÁMARA: un Pokémon fuerte que se puede capturar. Usa los scripts de las islas del ferry, entra en `islas()` de `estaticos.py` y lleva la regla `"tope"` de niveles.
- **Dos zonas de captura** nuevas (108 de 112), dos entrenadores nuevos (861 de 864), salvajes y objetos.
- **Fallo grave encontrado y arreglado:** los `scripts.inc` de los mapas se apuntan a mano en `data/event_scripts.s`, y los seis mapas nuevos no estaban. Los PRs #82 y #83 no habrían compilado. Arreglado en cada rama.
- **`tools/dualocke/comprobar_zonas.py`:** comprueba sin compilador todo lo que puede fallar al añadir mapas. Con el repo original daba 26 avisos, que son rarezas del juego y quedan como excepciones. Ahora da 0 fallos en 941 mapas.
  - Mira: scripts apuntados, layouts, etiquetas, constantes, puertas, conexiones, objetos, entrenadores, salvajes, zonas de captura y carteles.

## Cómo se comprobó

- `comprobar_zonas.py`: 0 fallos.
- Mapas dibujados con `ver_mapa.py` y recorridos con el cálculo de alcance.
- Cadena de niveles: solo cambian SOLEDAD y RAMIRO.
- **No se ha compilado** (sin WSL).
