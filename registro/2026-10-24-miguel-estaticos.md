# 24/10/2026 · Miguel · Niveles de estáticos y regalos

Rama `miguel/estaticos`.

## Por qué

Al revisar el PR #16 de Jorge se vio que los Kecleon de la Ruta 120 seguían a nivel 30, con entrenadores de 52-59 alrededor. Ningún script de equilibrio tocaba los estáticos ni los regalos.

## Decisiones de Miguel

| Pregunta | Decisión |
| --- | --- |
| Nivel de los estáticos normales | **Como jefes de zona** (entrenadores del mapa + 3, sin pasar del cap) |
| ¿Se pueden capturar? | **Solo el primero de cada tipo**, sin gastar zona |
| Regalos | **Nivel bajo, a entrenar** (se quedan como en el original) |
| Legendarios estáticos | **Al cap de su tramo** |

## Lo que se hizo

- `tools/dualocke/reescalar_niveles.py` tiene ahora una tabla `ESTATICOS` y reescribe el nivel de los `setwildbattle` de cada script. Se puede volver a lanzar sin que cambie nada.

| Estático | Antes | Ahora |
| --- | --- | --- |
| Kecleon (rutas 119-120, `data/scripts/kecleon.inc` y el del puente) | 30 | 58 |
| Voltorb ×3 (Nuevo Malvalona) | 25 | 56 (no tiene entrenadores: mitad del tramo 6 + 3) |
| Electrode ×2 (Guarida Aqua) | 30 | 65 |
| Regirock, Regice, Registeel | 40 | 84 |
| Rayquaza, Groudon, Kyogre | 70 | 100 |
| Sudowoodo (Frente Batalla) | 40 | 100 |

- **Regalos sin cambios:** Castform 25, fósiles 20, Beldum e iniciales de Johto 5, huevo de Wynaut.

## Queda

- **"Solo el primero de cada tipo":** es código de captura, y vive en el `src/dualocke.c` del PR #17 de Jorge. Se hará cuando ese PR esté en `master`, para no pisarle.
- **Probar jugando.**
