# 17/11/2026 — Miguel: CUMBRE METEORO

## Qué se pidió

Miguel: "Yes, the summit". Es la propuesta 11 de ZONAS.md, la última que faltaba: una montaña escarpada junto a la CATARATA METEORO, con pisos a distintas alturas y la cima nevada.

## Qué se ha hecho

- **`tools/dualocke/crear_cumbre_meteoro.py`** (se puede volver a lanzar). Tramo 4.
- **Entrada:** una cueva nueva en la RUTA 115, junto a la de la CATARATA METEORO.
  - El borde norte de la ruta está cerrado, así que se entra por cueva.
  - Se puso en una pared lisa, sin quitar ninguna base secreta.
- **LADERA:** terrazas de roca de la RUTA 114 con hierba alta de montaña y una cueva arriba que sube a la cumbre.
- **CUMBRE:** las cimas de la RUTA 115 (en el juego no se llega a ellas), con nieve y hierba escarchada. Guardián: Salamence a nivel 40.
- **Zona de captura propia** (116 de 128), salvajes, 3 objetos y un Ticket-Recuerdo.
- **Documentación:** `DUALOCKE.md`, `PRUEBAS.md` y `GUIA.html`.

## Problemas encontrados y arreglados al hacerlo

- **Alcance con bordillos:** para saber a qué terrazas se llega hacía falta un cálculo de alcance que entienda los saltos de un solo sentido. Con él se eligieron la pared de la entrada y las dos cuevas.
- **Un trozo de bosque en la cumbre:** el recorte de la RUTA 115 se llevaba una franja del bosque de la izquierda. Se recortó dos columnas más.
- **Flags:**
  - En la zona del sistema solo quedaban dos libres que no sean diarios: el 0x91F lo usa `DAILY_FLAGS_START` y desde el 0x920 son diarios (se borran cada día).
  - El guardián usa el 0x91D, y los objetos, flags normales libres (0x1DE-0x1E1).
- **Objetos de la ladera:** `colocar_objetos.py` no les encontró sitio, así que se pusieron a mano. La Escama Dragón se apartó del guardián.

## Cómo se comprobó

- **`comprobar_zonas.py`:** 0 fallos en 956 mapas (zonas 116 de 128).
- **Alcance con bordillos:**
  - En la RUTA 115 se llega andando a la cueva nueva.
  - En la LADERA, desde la llegada se llega a la cueva de arriba.
  - En la CUMBRE, desde la llegada se llega al guardián.
- **Mapas:** dibujados y revisados.
- **Cadena de niveles:**
  - En `trainers.party` no cambia nada.
  - En `wild_encounters.json` solo se añaden las tablas nuevas al final.
  - El script conserva el nivel del guardián si se vuelve a lanzar.
- **No se ha compilado** (sin WSL).

## Pendiente

- Probarlo en el juego (`PRUEBAS.md`).
- **Con esto están hechas todas las zonas de ZONAS.md.**
- **Recursos que se acaban:**
  - Entrenadores libres: ninguno.
  - Zonas de captura: quedan 12.
  - Flags del sistema: ya no quedan libres que no sean diarios; los normales sí.
