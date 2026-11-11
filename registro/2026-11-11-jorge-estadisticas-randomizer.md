# 11/11/2026 — Jorge: estadísticas del randomizer

## Qué se pidió

Estaba apuntado para el próximo locke (#59). Jorge perdió 4 POKéMON en el primer gimnasio, con el equilibrio de antes del #63, y se plantea empezar de cero con semilla nueva. Así que se deja listo para meterlo con la partida nueva.

## Qué se ha hecho

- `aleatorio/especies.py` evalúa las estadísticas con `evaluar` en vez de coger el primer número que aparece. Antes, con `8 >= 1 ? 60 : 50`, salía un 8.
- `evaluar` se ha movido de `guia_pokedex.py` a `aleatorio/especies.py`: la guía la importaba del randomizer y al revés no se podía, por la importación circular y por PIL.
- Comprobado:
  - Machoke: 80/100/70/50/60/45 (405).
  - Charizard: 534.
  - Pikachu: Def. Esp. 50.
  - Solo SPECIES_NONE y SPECIES_EGG no tienen estadísticas.
- La guía regenerada sale idéntica.
- `DUALOCKE.md`: marcado como arreglado en "Pendiente para el próximo locke".

## Ojo

Con la misma semilla cambian muchos entrenadores: el tope de los líderes, la estrategia y los objetos. Solo debe fusionarse cuando se empiece partida nueva.
