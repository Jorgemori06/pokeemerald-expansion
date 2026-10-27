# 26/10/2026 — Miguel: guía del juego en HTML

## Qué se pidió

Una guía en HTML, bonita, con índice y categorías, para tenerla en el repo y consultarla mientras jugamos. Tenía que llevar:

- un walkthrough breve con los level caps y los niveles de los jefes;
- los objetos añadidos importantes;
- pistas para encontrar las megapiedras y los Ticket-Recuerdo;
- un apartado con todas las novedades.

## Qué se ha hecho

- **`GUIA.html`:** un solo archivo, sin nada externo, que se abre con el navegador. Tiene índice lateral (desplegable en el móvil), tema claro y oscuro, y nueve secciones:
  1. Cómo empezar.
  2. Reglas del locke.
  3. Level caps.
  4. Cómo avanzar, tramo a tramo. Cada tramo lleva su cap y los jefes con el nivel de su as, sacado de `trainers.party`.
  5. Objetos importantes, con la tabla de las tiendas.
  6. Pistas de las 81 megapiedras.
  7. Pistas de los 45 Ticket-Recuerdo.
  8. Los 55 sitios de los objetos competitivos.
  9. Novedades.
- **Pistas en tres niveles:** la zona; "Más pistas", con la parte del mapa, el terreno y lo que hay cerca; y "Solución", con la casilla.
  - Se pueden marcar las que ya tienes (se guarda en el navegador) y filtrar por "Voy por la medalla N", para no ver las de más adelante.
  - También hay buscador y barra de progreso.
- **`tools/dualocke/guia.py`:** genera las pistas desde los mapas (tablas de `colocar_objetos.py`, `map.json`, comportamiento de las casillas, nombres de `region_map_sections.json`) y las escribe dentro de `GUIA.html`. Así no se quedan atrás si se mueve algo.
- **Ticket-Recuerdo:** las pistas se generaron desde la rama del #40, que todavía no está fusionado. La guía lo avisa ("próximamente"), igual que el #38 y el #42.
- **`DUALOCKE.md`:** la guía está en "Hecho" y en el mapa del código.

## Cómo se comprobó

- Abierta en el navegador, en escritorio y en móvil (375 px): sin errores en la consola y sin barra horizontal. Salen 81 megapiedras, 45 tickets y 55 objetos competitivos.
- Los niveles de los jefes salen de `src/data/trainers.party` (el máximo de cada equipo) y los caps de la sección 5 de `DUALOCKE.md`.

## Pendiente

- Cuando se fusione el #40, volver a lanzar `python3 tools/dualocke/guia.py` en `master` para que las pistas salgan de allí. Deberían salir iguales.
- Si cambia algo del walkthrough o de las novedades, se edita a mano en `GUIA.html`.
