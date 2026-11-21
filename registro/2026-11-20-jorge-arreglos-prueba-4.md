# 20/11/2026 — Jorge: arreglos de la cuarta prueba de Miguel

**Qué se pidió:** salirse del mapa yendo a la ISLA HELADA (NEVADA); reinicio al capturar a su guardián; ataques sin daño contra Ferrocuello con Campo de Niebla en la RUTA 124; combate imposible con MÁXIMO PEÑAS en el CENTRO ESPACIAL (Miguel perdió el locke ahí); camino a la ISLA DE RUINAS bloqueado; mapa que se buguea yendo a la ISLA VOLCÁNICA desde PORTUAL.

**Qué se hizo** (todo comprobado en el emulador sin pantalla, salvo el combate con MÁXIMO PEÑAS):
- Reinicio: gráficos de Rojo Fuego en tres personajes (NIEVES, DARÍO y el bañista de la PLAYA VOLCÁNICA). Encontrado siguiendo instrucción a instrucción en el emulador (`gbarun.c` tiene ahora órdenes para eso). Nuevo `graficos.py` en el CI.
- ISLA DE RUINAS y DESIERTO PROFUNDO: los cambios estaban en un dibujo del mapa que el juego no usa (o no siempre). Nuevo `variantes.py` en el CI; `crear_desierto_profundo.py` y `crear_islas_sur.py` dibujan en todos.
- ISLA NEVADA: fila de rocas abajo (`crear_isla_nevada.py`).
- ISLA VOLCÁNICA: desplazada 10 casillas (`VOLCAN_DESPLAZAMIENTO`).
- MÁXIMO PEÑAS: `companeros.py`, nivel 84.

**Comprobado:** `make`, `make check TESTS="Dualocke"` (62/62), `alcance.py`, `sin_salida.py`, `graficos.py` y `variantes.py` sin problemas; solucionario idéntico al de la 8.4 con las dos semillas.

**Pendiente:** Ferrocuello (falta el `.sav` de Miguel), mejorar el dibujo de la ISLA VOLCÁNICA, y lo nuevo que diga Jorge.
