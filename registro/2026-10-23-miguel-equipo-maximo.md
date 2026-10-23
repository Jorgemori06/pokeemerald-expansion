# 23/10/2026 · Miguel · Equipo de Máximo

Tarea de equilibrio de la sesión de Miguel. Rama `miguel/equipo-maximo`.

## Decisiones de Miguel

- **Equipo fijo:** el randomizer no lo toca.
- **As:** Metagross, que megaevoluciona.
- **Resto del equipo:** Aggron, Aegislash, Excadrill, Mawile y Empoleon.

## Lo que se hizo

- **Entrenador nuevo `TRAINER_STEVEN_ROUTE_120`** (id 855) en `include/constants/opponents.h`. `TRAINERS_COUNT_EMERALD` pasa a 856 (el máximo es 864, así que caben 8 más).
- **Equipo** en `src/data/trainers.party`: los 6 a **nivel 62**, el cap del tramo 6, porque es un jefe justo antes de Alana y los entrenadores de la Ruta 120 van de 52 a 59. Metagross lleva la **Metagrossita**. IVs perfectos, como el Máximo original.
- **Cabecera** igual que el Máximo que ya existe (clase Rival, sprite de Máximo) y IA básica.

## Decisiones de Claude por el camino (revisables)

- **Nivel 62** (la regla de los jefes a mitad de tramo: los entrenadores de la zona + 3, sin pasar del cap).
- **Objetos:** 2 Hiperpociones, como Alana.
- **Movimientos:** los de serie de cada especie a su nivel.

## Para Jorge

- **Evento:** monta el combate en `data/maps/Route120/` con `trainerbattle_single TRAINER_STEVEN_ROUTE_120, <texto de intro>, <texto de derrota>` y da el `ITEM_MEGA_RING` al ganar.
- **Randomizer:** sáltate este entrenador; su equipo es fijo.
- **Mis scripts de equilibrio** no lo tocan: no está en el original de la expansion.
