# 11/11/2026 — Jorge: textos de la pesca, la tienda, el veneno y el casino

## Qué se pidió

Jugando, Jorge vio que los mensajes de la pesca salían en inglés.

## Qué se ha hecho

Estos textos no son diálogos de mapas, están en el código. Se han traducido con `ES()`, así que los tests siguen viendo el inglés:

- **Pesca** (`src/fishing.c`):
  - "¡Oh! ¡Ha picado algo!";
  - "¡Has pescado un POKéMON!";
  - "No pica nada…";
  - "Se ha escapado…".
- **Tienda** (`src/shop.c`): el aviso del Items Clause, "Ya has comprado uno de estos aquí."
- **Veneno fuera de combate** (`src/strings.c`): "se ha debilitado…" y "ha aguantado el veneno".
- **RULETA** (`src/roulette.c`) y **tragaperras** (`src/slot_machine.c`) del casino de MALVALONA: todos sus mensajes.

## Lo que sigue en inglés en el código

- Las frases del POKéMON que te sigue (`follower_helper.c`): los seguidores están desactivados, así que no salen.
- La LICUADORA DE BAYAS, los {POKEBLOCK}, el chat fácil, el cable y el FRENTE BATALLA.

## Cómo se comprobó

- `make` compila sin avisos.
- Ninguna línea pasa de 208 px. Las tragaperras tienen una ventana propia, así que su ayuda no pasa del ancho del inglés.
- No se ha visto en el emulador.
