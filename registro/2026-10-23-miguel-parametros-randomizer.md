# 23/10/2026 · Miguel · Parámetros del randomizer

Quinta tarea de equilibrio de la sesión de Miguel. Rama `miguel/parametros-randomizer`, encima de `miguel/evoluciones-entrenadores` (PR #6). Solo documentación y configuración: no cambia nada del juego.

## Para qué

Jorge va a empezar el randomizer. Este archivo le dice qué debe barajar y con qué reglas, para que no tenga que decidir cosas de equilibrio.

## Decisiones de Miguel

| Pregunta | Decisión |
| --- | --- |
| Salvajes | **Según el nivel:** especie libre, ajustada a la fase que le toca por el nivel de la zona |
| Jefes | **Equipos totalmente aleatorios**, pero el **as de su tipo o temática**; desde el aro, la mega también de ese tipo |
| Iniciales | **Forma base de línea de 3 fases**, sin legendarios, y los tres en **triángulo de tipos** |
| Legendarios | **Solo legendarios y singulares** (Ultraentes y paradójicos cuentan como normales) |

## Lo que se hizo

- `tools/dualocke/randomizer_config.json` recoge todos los parámetros: los nuevos y los del preset de Platino que ya estaban en la sección 7.
- La sección 7 de `DUALOCKE.md` resume las decisiones nuevas.
- **Comprobado en los datos del motor:** cada tipo tiene al menos 4 megas que no son legendarias (Roca es el que menos), así que la regla del as con mega de su tipo siempre tiene opciones.
- **Detalle para Jorge:** algunas formas mega de legendarios (Mewtwo, Latios, Rayquaza, Heatran, Zygarde…) no están marcadas como legendarias, así que hay que mirar la marca en la especie base.

## Decisiones de Claude por el camino (revisables)

- **Temáticas de los importantes:** Magno y Tatiano Fuego/Tierra, Aquiles, Silvina y Matías Agua/Siniestro, Blasco Psíquico/Hada.
- **Rival:** su as es su inicial. Si esa línea no tiene mega, desde el aro lleva además una mega del tipo de su inicial como as.
- **Legendarios** permitidos solo como estáticos y en los jefes de la Liga.
- **Salvajes:** evitar repetir especies entre zonas mientras queden.

## Queda

- Que Jorge lo revise. Si su herramienta necesita otro formato, se cambia.
