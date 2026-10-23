# 23/10/2026 · Miguel · Contenido de las tiendas

Tarea de equilibrio de la sesión de Miguel. Rama `miguel/tiendas`.

## Decisiones de Miguel

- **Dependiente principal:** lo básico (Balls, Repelentes y poco más) en todas las tiendas, y además **objetos propios de cada ciudad**.
- **Objetos evolutivos:** en las tiendas, **según las medallas**.
- **Megapiedras:** **no se venden**, se encuentran **explorando el mapa**. Es una tarea aparte; la tabla se revisa antes de colocarlas.

## Cómo se hizo

- **Inventarios** reescritos en las 22 listas de tiendas de Hoenn. La tabla completa está en `DUALOCKE.md` (sección 6, "Tiendas").
- **Medallas:** el motor ya trae un filtro de tiendas (`src/shop_criteria.c`, solo en tiendas normales). Se añade una tabla `sDualockeShopBadges` (objeto → medallas) que se consulta junto al filtro original:
  - Super Ball: 1 medalla.
  - Superrepelente: 2.
  - Ultra Ball y Máximo Repelente: 5.
  - Piedras evolutivas: 2.
  - Objetos de las antiguas evoluciones por intercambio, Garra Afilada y Colmillo Agudo: 4.
- **3.ª planta de los Grandes Almacenes de Calagua:** el mostrador de Objetos X (que tras el paso 1 solo vendía Caramelos Raros) pasa a vender **todos** los objetos evolutivos.
- **Herboristería de Lavacalda:** como ya no vende curativos, vende hierbas equipables (Blanca, Mental y Única).

## Decisiones de Claude por el camino (revisables)

- **Qué objetos van en cada ciudad**, según su temática (Devon en Férrica, el puerto en Portual, el volcán en Lavacalda…).
- **Medallas** de cada objeto.
- **Amigo Ball:** no se vende, porque en esta versión tiene precio 0 y saldría gratis.
- **Cartas:** se quitan de las tiendas de ciudad, salvo en Calagua.

## Para Jorge

- `src/shop_criteria.c` está en tu zona (segundo dependiente). El cambio se reduce a una tabla y una función. Si tu segundo dependiente usa otro tipo de tienda, recuerda que el filtro solo se aplica en las normales (`MART_TYPE_NORMAL`).

## Queda

- **Megapiedras por el mapa** (siguiente tarea).
- **Probar jugando.**
