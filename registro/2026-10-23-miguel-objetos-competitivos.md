# 23/10/2026 · Miguel · Objetos competitivos por el mapa

Tarea de equilibrio de la sesión de Miguel. Va en la rama `miguel/megapiedras` (PR #12), junto a las megapiedras, para no apilar PR.

## Por qué

Al revisar lo que faltaba se vio que los objetos de generaciones nuevas existen en el motor, pero **no se podían conseguir**: el mapa solo tenía los objetos de Esmeralda.

## Decisiones de Miguel

- **Repartirlos por el mapa**, como las megapiedras, con la tabla revisada antes de colocarlos.

## Lo que se hizo

- **55 objetos**, colocados con el mismo script, que ahora se llama `tools/dualocke/colocar_objetos.py` y tiene dos tablas: megapiedras y competitivos.
- **Flags:** `FLAG_ITEM_COMP_...`, del **0x493 al 0x4C9**. El bloque de las megapiedras solo tenía 7 libres.
- **Mejora del script:** ahora también usa como punto de partida los PNJ, puertas y escaleras, tomando la altura del suelo de al lado. Hacía falta en pueblos como Pueblo Azuliza o Arrecípolis, que no tienen objetos ni entrenadores.
- **Corrección:** en el PR #12 se dijo que los flags 0x284-0x2BB quedaban libres, y no es así. Las megapiedras usan 0x264-0x2B4.

## Tabla

| Objeto | Mapa | Tipo |
| --- | --- | --- |
| `EVIOLITE` | Route116 | bola |
| `FOCUS_SASH` | DewfordTown | oculto |
| `PUNCHING_GLOVE` | DewfordTown | bola |
| `MUSCLE_BAND` | Route106 | bola |
| `BLUNDER_POLICY` | Route109 | oculto |
| `RED_CARD` | SlateportCity | oculto |
| `WISE_GLASSES` | SlateportCity_OceanicMuseum_2F | bola |
| `WEAKNESS_POLICY` | Route110 | bola |
| `EJECT_BUTTON` | Route110 | bola |
| `TOXIC_ORB` | Route117 | bola |
| `JOLLY_MINT` | Route117 | bola |
| `TIMID_MINT` | Route117 | oculto |
| `EJECT_PACK` | Route117 | oculto |
| `THROAT_SPRAY` | VerdanturfTown | oculto |
| `LOADED_DICE` | MauvilleCity_GameCorner | oculto |
| `FLAME_ORB` | FieryPath | bola |
| `HEAT_ROCK` | MtChimney | bola |
| `SMOOTH_ROCK` | Route111 | bola |
| `SAFETY_GOGGLES` | Route111 | bola |
| `ROCKY_HELMET` | Route111 | bola |
| `LIGHT_CLAY` | Route112 | bola |
| `PROTECTIVE_PADS` | Route112 | oculto |
| `WIDE_LENS` | Route113 | oculto |
| `HEAVY_DUTY_BOOTS` | Route114 | bola |
| `EXPERT_BELT` | Route115 | bola |
| `BLACK_SLUDGE` | AbandonedShip_Corridors_B1F | oculto |
| `ELECTRIC_SEED` | NewMauville_Inside | bola |
| `BOOSTER_ENERGY` | NewMauville_Inside | bola |
| `AIR_BALLOON` | Route119_WeatherInstitute_2F | bola |
| `UTILITY_UMBRELLA` | Route119_WeatherInstitute_1F | oculto |
| `CHOICE_SCARF` | Route118 | bola |
| `BIG_ROOT` | Route119 | bola |
| `IMPISH_MINT` | Route119 | bola |
| `CAREFUL_MINT` | Route119 | oculto |
| `DAMP_ROCK` | Route120 | bola |
| `ASSAULT_VEST` | Route120 | bola |
| `GRASSY_SEED` | Route123 | bola |
| `MIRROR_HERB` | Route123 | bola |
| `BOLD_MINT` | Route123 | bola |
| `CALM_MINT` | Route123 | oculto |
| `CHOICE_SPECS` | Route121 | bola |
| `ADAMANT_MINT` | SafariZone_South | bola |
| `MODEST_MINT` | SafariZone_Southeast | oculto |
| `LIFE_ORB` | MtPyre_Exterior | bola |
| `MISTY_SEED` | MtPyre_Summit | oculto |
| `ROOM_SERVICE` | LilycoveCity | oculto |
| `COVERT_CLOAK` | AquaHideout_B2F | bola |
| `ICY_ROCK` | ShoalCave_LowTideIceRoom | bola |
| `PSYCHIC_SEED` | MossdeepCity | oculto |
| `ZOOM_LENS` | MossdeepCity_SpaceCenter_1F | bola |
| `ABILITY_CAPSULE` | SootopolisCity | oculto |
| `CLEAR_AMULET` | MeteorFalls_B1F_1R | bola |
| `TERRAIN_EXTENDER` | SkyPillar_4F | bola |
| `ABILITY_SHIELD` | VictoryRoad_B1F | bola |
| `ABILITY_PATCH` | VictoryRoad_B2F | oculto |

## Decisiones de Claude por el camino (revisables)

- **Selección y ubicaciones**, por temática y por tramo. Los más fuertes (Pañuelo Elegido, Chaleco Asalto, Gafas Elegidas, Vidasfera) van a partir del tramo 6.
- **Fuera:** Chapas Plateadas y Doradas (necesitan un PNJ de Entrenamiento Extremo que no existe), Garra Garfio, Banda Atadura, Bola Férrea, Metrónomo y Muda Concha.
- **Nombres en español:** en `DUALOCKE.md` se han escrito de memoria y no se han comprobado con una lista oficial. En el código van con su nombre interno.

## Queda

- **Probar jugando** que se ven y se pueden coger. Sobre todo los de los pueblos, el Casino y los edificios, donde se partió de PNJ o puertas.
