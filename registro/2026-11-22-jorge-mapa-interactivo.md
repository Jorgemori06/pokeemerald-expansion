# 22/11/2026 — Jorge: mapa interactivo

## Qué se pidió

Jorge: un mapa interactivo como el de Project Zomboid (projectzomboidmap.com), pero de Hoenn, para ver las zonas nuevas y lo demás, solo con lo útil para este juego.

## Qué se ha hecho

- **`MAPA.html`**: un solo archivo, de unos 6 MB, que se abre con el navegador como la guía. Se enlazan entre sí: en la guía, "🗺 Mapa interactivo" debajo del índice; en el mapa, "abrir la guía".
- **`tools/dualocke/mapa_interactivo.py`**: lo genera entero desde los mapas, en unos 10 segundos. Dibuja los mapas con numpy y salen igual que con `ver_mapa.py` (comprobado píxel a píxel en la RUTA 119).
- **`tools/dualocke/mapa/`**: la plantilla y Leaflet 1.9.4, con su licencia.
- **De la web de Zomboid se ha cogido:**
  - zoom y arrastre;
  - nombres que salen según el zoom (de lejos, ciudades y zonas nuevas; al acercarte, rutas, cuevas y sitios);
  - buscador;
  - capas;
  - selector de plantas para cuevas y edificios;
  - enlace a un sitio exacto.
- **No se ha cogido:** cuenta, GPS, comentarios, idiomas, tamaño y color de etiquetas, ni dibujar a mano.
- **Lo propio del dualocke:**
  - zonas de captura que se marcan como Capturado o Fallado, por jugador;
  - zonas nuevas resaltadas, con el texto de la guía;
  - las capas que destripan (entrenadores, objetos, megapiedras, tickets y POKéMON fuertes) empiezan apagadas.
- **Lo que sale al azar con la semilla se dice así:** objetos del suelo, MT y especie de los guardianes y estáticos. Las megapiedras y los Ticket-Recuerdo sí van con nombre, porque son fijos.

## Números

- 501 mapas:
  - 58 en el mundo;
  - 8 bajo el agua;
  - el resto se abre desde su puerta.
- 9 sitios a los que no se llega andando.
- 85 zonas de captura.
- 21 zonas nuevas, con las islas del ferry.
- 1270 puertas.
- 519 entrenadores.
- 444 objetos al azar.
- 107 megapiedras.
- 57 Ticket-Recuerdo.
- 25 POKéMON fuertes.

## Comprobado

En Chrome sin pantalla, sin errores de JavaScript:

- mundo entero y de cerca;
- buscador: "monte pirico" y "gardevoirita";
- entrar en el MONTE PÍRICO y cambiar de planta;
- ventanas de zona y de guardián;
- marcar la RUTA 101;
- bajo el agua;
- pantalla de móvil.

## Pendiente o ideas

- Los mapas de bajo el agua se ven morados, con su paleta tal cual, como en Porymap. En el juego se oscurecen.
- La CUEVA ABISAL y la CÁMARA SELLADA salen sueltas: se entra buceando por script, no por una puerta.
- Se podría cargar la semilla para ver los salvajes de cada zona, como la Pokédex de la guía.
- Hay que volver a lanzar `mapa_interactivo.py` cuando se toque un mapa.
