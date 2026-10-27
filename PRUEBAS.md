# Pruebas antes de jugar el locke

Todo lo grande ya está en `master`: reglas del locke, randomizer, equilibrio y la historia en español. Ya compila y pasa los tests (`make check`, 5450 en verde), pero **nadie lo ha jugado todavía**. Esta lista es para la primera partida de prueba. Lo que falle se apunta como un issue o en un PR, con el mapa y lo que pasó.

## Cómo preparar la ROM de prueba

- **Para probar:** `make SIN_RANDOM=1` (o el instalador con `-SinRandom`). Así se reconocen los Pokémon y los entrenadores originales, y es más fácil ver si algo está mal.
- **Para ver el randomizer:** `make` normal (o el instalador sin opciones) con una semilla cualquiera.
- **Atajos de prueba:** en el mapa, **R + START** abre el menú de depuración: volar a cualquier mapa, darse Pokémon y objetos, cambiar flags. En combate, **SELECT** abre el de combate.
- **Partida de verdad:** esos dos menús están activos en el `make` normal (`DEBUG_OVERWORLD_MENU` y `DEBUG_BATTLE_MENU` valen `DISABLED_ON_RELEASE`). Con **`make release`** se quitan y la ROM sale como `pokeemerald-release.gba`. El instalador ya usa `make release` para la partida de verdad (sin opciones y con `-NuevaPartida`) y la copia como `Dualocke.gba`. Con `-SinRandom` sigue siendo el `make` normal, con los menús.

## Qué mirar

### Textos en español

- [ ] **Cajas de texto:** que ninguna línea se salga ni se corte. `dialogos.py comprobar` mide el ancho con la fuente del juego, pero no ve los nombres largos que se meten en `{STR_VAR_1}` (Pokémon, objetos, movimientos).
- [ ] **Sitios con más riesgo:**
  - el tablón del BUSCATESOROS (RUTA 124), con columnas en píxeles;
  - VITO y LETI hablando a la vez (GIMNASIO de ALGARIA);
  - los tutores, que ahora dicen el movimiento al azar;
  - las llamadas de la AGENDA con nombres largos;
  - las estatuas de los gimnasios ("RECONOCIDOS POR").
- [ ] **Frases que salen en inglés** en la historia: apuntar el mapa. Lo que se dejó en inglés a propósito está en `traduccion/dialogos/PLAN.md` (postgame, la tele, el hombre de MALVALONA…).
- [ ] **Nombres sin confirmar:** RYDEL, CAMINO DE BICIS, familia VENCEDOR, ROBOMUÑECO, WANDA, SENDERO ÍGNEO, CAMINO ESCABROSO, PROF. COSMO, GUARDAS POKéMON, OLVIDAMOVIMIENTOS, MOTEL CALAGUA; y los de Jorge en el #33 (BOLETO LOTO, SALA UNIÓN, MACHACABAYAS…). Si alguien sabe el oficial, se cambia en el `.tsv` y en `LEEME.md`.
- [ ] **Género:** jugar al menos un rato con chica. Los textos se escribieron para que valgan para los dos, pero puede quedar alguno en masculino.
- [ ] **Combate y menús:** mensajes de combate (artículos, "salvaje", "enemigo"), pantalla de datos, PC, MOCHILA, tiendas.

### Reglas del locke

- [ ] **Vidas:** el menú de pausa muestra "Vidas: N". Un Pokémon debilitado sale con el aviso de muerte, va a la caja 14 y resta una vida. Con 0 vidas, la siguiente muerte pone "LOCKE PERDIDO".
- [ ] **Primera captura por zona:** solo se puede capturar el primer salvaje válido de cada zona. Los repetidos y legendarios no gastan la zona. Los shiny se capturan siempre.
- [ ] **Caja de prohibidos (13):** regalos, huevos, fósiles, estáticos e intercambios repetidos o legendarios van ahí, bloqueados.
- [ ] **Tiendas:** una compra por objeto (salvo Balls, Repelentes, Bayas y Caramelos), y el segundo dependiente en las ciudades.
- [ ] **Caps de nivel:** al llegar al cap no se gana experiencia y los Caramelos Raros no funcionan por encima.

### Recuerdamovimientos y Ticket-Recuerdo

- [ ] En un Centro Pokémon, la señora a la derecha del PC: sin ticket te lo dice; con ticket enseña un movimiento de nivel y gasta el ticket solo si lo aprende.
- [ ] Que no tape el PC ni el mapa de la región, y que esté en todos los Centros (también en LAVACALDA).
- [ ] Que los tickets de las rutas se vean y se puedan coger. Mirar sobre todo los de las rutas de mar (en el agua, con Surf) y los ocultos de las rutas largas.
- [ ] Que la pantalla de datos ya no deje recordar movimientos gratis.

### Randomizer (con semilla)

- [ ] Salvajes, entrenadores, iniciales y rival cambian, sin legendarios donde no toca.
- [ ] Los jefes llevan su as con megapiedra desde el Mega-Aro, y objetos que les sirven.
- [ ] Habilidades, MT, tutores, intercambios y objetos del suelo cambian, y las MO no.
- [ ] Los movimientos que se aprenden al subir de nivel son al azar: los de tu inicial, los de los salvajes y los de los entrenadores. Que al principio siempre haya algún ataque y que no salgan ataques muy fuertes a nivel bajo.
- [ ] `make nueva-partida` da otra semilla y `make` repite la misma.

### Equilibrio

- [ ] Niveles de entrenadores y salvajes de cada tramo frente al cap (sección 5 de `DUALOCKE.md`).
- [ ] Combate con MÁXIMO en la RUTA 120 (nivel 62) y entrega del Mega-Aro.

## Cómo apuntar un fallo

Mapa, qué se hizo, qué pasó y, si se puede, una captura. Si es un texto, la etiqueta del `.tsv` (la sacas con `python tools/dualocke/dialogos.py exportar data/maps/MAPA/scripts.inc`) y cómo debería quedar.

## Partidas de prueba

### 1. Jorge, 26/10/2026 (randomizada, hasta la RUTA 103 y perder el locke a propósito)

**Bien:** opciones, menú con las vidas, diálogos de la intro y de VILLA RAÍZ, inicial al azar con habilidad y movimientos en español, combate, aviso de muerte con las vidas que quedan y LOCKE PERDIDO.

**Fallos encontrados (arreglados en `jorge/arreglos-prueba`):**

| Qué pasó | Arreglo |
|---|---|
| Con Poké Balls compradas en PUEBLO ESCASO antes de que te las den, se podían capturar dos salvajes en la misma ruta | Las reglas empiezan también con la primera Poké Ball en la mochila (`FLAG_DUALOCKE_TIENE_BALLS`). Test nuevo. |
| Datos del Pokémon: "lo conociste en ROUTE 101" | Nombres de los lugares de Hoenn en español |
| En combate, "TYPE/" junto a los PP | "TIPO/" |
| Al perder: "Prueba scurried back home…" | Traducidos los cuatro textos de volver a casa o al CENTRO POKéMON |
| "LOCKE PERDIDO" se cortaba en la ventana del menú | Ventana más ancha |

**No era fallo:** no poder huir de un Dreepy después de tirarle una Ball. Usó Acoso, que atrapa (en los juegos oficiales pasa igual).

**Pendiente (son imágenes):** PROFILE, ABILITY y TRAINER MEMO en los datos; MOVE INFO en combate; los iconos de tipo (ICE, GROUND…); PRESS START y "New Game" en el título; PARTY POKéMON, CLOSE BOX y PKMN DATA en el PC.

### 2. Jorge, 26/10/2026 (tarde, con el menú de depuración)

**Bien:**
- Con Poké Balls compradas, el segundo salvaje de la ruta ya no se puede capturar (arreglo de la partida 1). El mensaje cabe.
- Mewtwo (legendario) va directo a VETADOS.
- Un Bulbasaur repetido va a VETADOS; al morir el primero (aviso con 19 vidas, caja MUERTOS) se puede sacar el segundo.
- Los Caramelos Raros paran en el cap (16 con 0 medallas).

**Fallo:** al volar, "¿A dónde quieres VOLAR?" se cortaba (la ventana es estrecha). Ahora "¿Adónde VOLAR?".

**No era fallo:** no poder volar a ningún sitio. Solo se vuela a las ciudades ya visitadas.
