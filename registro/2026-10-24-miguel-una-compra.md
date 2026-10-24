# 24/10/2026 · Miguel · Una compra por objeto

Tarea de Jorge que adelanta Miguel (reservada en el PR #18). Rama `miguel/una-compra`.

## Regla (sección 4 de `DUALOCKE.md`)

Solo se puede comprar una unidad de cada objeto por tienda, salvo Balls, Repelentes, Bayas y Caramelos Raros. La Cuerda Huida también queda exenta, porque es objeto clave y gratis.

## Cómo se hizo

- **Tabla generada:** `tools/dualocke/compras_limitadas.py` lee las listas `pokemart` de los mapas de Hoenn y escribe `src/data/dualocke_compras.h` con cada pareja (mapa de la tienda, objeto) limitada.
  - Ahora son **86 parejas en 15 tiendas**. La que más tiene es la 3.ª planta de los Grandes Almacenes de Calagua, con 33.
  - Se identifica la tienda por el **mapa**: los dos mostradores de una misma planta cuentan como la misma tienda, y como venden cosas distintas, da igual.
- **Guardado:** 6 variables libres (`VAR_DUALOCKE_COMPRAS_0`-`5`), es decir, 96 bits.
  - Se eligieron 0x4083, 0x408B, 0x4091, 0x409B, 0x409D y 0x40A1, lejos de las 0x40F7-0x40FD que usa el PR #17 de Jorge, para que no haya conflictos.
  - Un `STATIC_ASSERT` avisa si algún día la tabla no cabe.
- **`src/dualocke_compras.c`** (nuevo, con su cabecera `include/dualocke_compras.h`), y tres enganches en `src/shop.c`:
  1. **Al elegir el objeto:** si ya lo compraste en esta tienda, sale "You've already bought one of these here.".
  2. **En la cantidad:** de los limitados, como mucho 1.
  3. **Al pagar:** se marca como comprado.
- **Lo que no está en la tabla** (exentos y tiendas de fuera de Hoenn) se compra sin límite.

## Queda

- **Probar jugando:** comprar una piedra, volver a elegirla y comprobar que no deja, y que en otra ciudad sí.
- **Si se cambian las listas de las tiendas,** hay que relanzar el generador.
