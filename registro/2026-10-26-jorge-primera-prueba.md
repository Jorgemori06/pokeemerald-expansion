# 26/10/2026 · Jorge · Primera partida de prueba y arreglos

Sesión de Jorge con Claude (mañana). Rama `jorge/arreglos-prueba`.

## Qué se hizo

- **#32 de Miguel** (la historia traducida): compila con y sin randomizar y `make check` da 5450 en verde, ya unido con master. Aprobado y fusionado. Miguel aprobó y fusionó el #33 y el #34 de Jorge. El #35 de Miguel (documentación y `PRUEBAS.md`) aprobado y fusionado.
- **ROM de prueba para Jorge:** master + #32 + #33, randomizada con una semilla nueva.
- **Jorge la jugó** unos 20 minutos (intro, inicial, RUTA 101-103, perder el locke a propósito). Fallos y arreglos en `PRUEBAS.md` ("Partidas de prueba").

## Arreglos

- **Reglas desde la primera Poké Ball:** Miguel pone las Poké Balls a la venta en PUEBLO ESCASO desde el principio, y la regla de captura por zona solo empezaba con `FLAG_ADVENTURE_STARTED`.
  - Ahora `Dualocke_ReglasEmpezadas` también mira si hay Poké Balls en la mochila y lo guarda en `FLAG_DUALOCKE_TIENE_BALLS` (0x2B5, de los libres).
  - Vale para la captura por zona y para la caja de prohibidos.
  - Test nuevo en `test/dualocke.c`.
- **Nombres de los lugares de Hoenn** en `src/data/region_map/region_map_sections.json`, con 16 letras como mucho.
- **"TIPO/"** en la ventana de movimientos (`battle_message.c`, con `ES()`).
- **Textos al perder un combate** (`field_screen_effect.c`, con `ES()`).
- **Ventana de vidas más ancha** (`start_menu.c`) para que quepa LOCKE PERDIDO.

## Pendiente

- Las imágenes en inglés (lista en `PRUEBAS.md`).
- Seguir probando con la ROM nueva.
