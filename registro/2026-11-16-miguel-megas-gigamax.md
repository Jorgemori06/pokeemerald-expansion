# 16/11/2026 — Miguel: las formas Gigamax como megas

## Qué se pidió

Miguel (estudio del #75, idea 9): "las formas Dynamax, como es una putada implementarlas, podrían implementarse como megas de ese Pokémon. Por ejemplo, Kingler no tiene mega". Después de las opciones del motor (#78), eligió seguir con esto.

## Qué se ha hecho

- **26 megas nuevas** con los gráficos de su forma Gigamax (27 formas: Toxtricity tiene dos y una piedra). Venusaur, Charizard, Blastoise y Gengar ya tenían mega; Urshifu y Melmetal son singulares y se quedan como estaban.
- **Diseño** (propuesta de Claude, para que Miguel la cambie): estadísticas que suman 100 más que la forma normal, tipo y habilidad que pegan con su movimiento Gigamax. La tabla está en `DUALOCKE.md`, sección 6.
- **`tools/dualocke/megas_gigamax.py`** lo hace todo y se puede volver a lanzar (comprobado: la segunda vez no cambia nada):
  - formas: estadísticas, tipos, habilidad, peso (las Gigamax pesaban 0, y eso cambia Patada Baja y Cuerpo Pesado) e `isMegaEvolution` en vez de `isGigantamax`;
  - tabla de cambios de forma: megaevolución con su piedra en vez del Dinamax;
  - 26 megapiedras al final de la lista de objetos (874-899);
  - iconos: el dibujo de la Gengarita con una paleta para cada una;
  - bolsillo de megapiedras de 100 a 130.
- **Los tests de la expansion no cambian:** todo lo nuevo de las formas va dentro de `#if TESTING ... #else`, porque los tests del Dinamax usan las formas Gigamax de siempre.
- **Colocadas en el mapa** con `colocar_objetos.py` (tabla nueva `MEGAPIEDRAS_GIGAMAX`, flags 0x4CA-0x4E3), cada una en un sitio que pega con su Pokémon. Las pistas de `GUIA.html` se han regenerado con `guia.py` (107 megapiedras).
- `guia_pokedex.py` las llama "Mega-Kingler", "Mega-Toxtricity Aguda"… (falta regenerar la Pokédex de la guía: necesita el compilador).

## Cómo se comprobó

- **No se ha compilado:** en el PC de Miguel no hay WSL. Lo tiene que compilar Jorge (`make` y `make check`).
- Las 26 suman exactamente 100 más que su forma normal.
- Los nombres de las piedras miden como mucho 52 píxeles con la fuente de la mochila (el test pide 73).
- Las paletas se han dibujado en una hoja de prueba: se distinguen y se parecen a su Pokémon.
- Los sitios del mapa los ha buscado `colocar_objetos.py` (casilla transitable cerca de algo que ya se alcanza). Falta verlos en el juego.

## Ojo

- **Semillas en curso:** los jefes con as con mega (de ALANA en adelante) pueden sacar una de estas, así que su as puede cambiar al volver a generar la ROM. Lo demás sale igual: las habilidades al azar no cambian, porque esas formas ya tenían habilidad.
- **Con semilla, la habilidad de la mega sale al azar**, como la de todas las especies. La de la tabla solo vale sin semilla.
- Las partidas guardadas siguen valiendo: los objetos nuevos van al final y las casillas nuevas del bolsillo se leen vacías.
