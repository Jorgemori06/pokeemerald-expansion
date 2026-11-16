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

### BOSQUE FRONDOSO y MANSIÓN OLVIDADA (desde el 17/11/2026)

- [ ] **Entrada:** en el claro del noreste del BOSQUE PETALIA hay dos árboles de CORTE; detrás, el pasillo lleva al BOSQUE FRONDOSO sin pantalla de carga, y se vuelve igual.
- [ ] **La unión:** que los árboles del borde de abajo del BOSQUE FRONDOSO sigan bien con los del BOSQUE PETALIA, y que no se vea nada raro al ir por el pasillo.
- [ ] **El bosque:** que ningún árbol salga cortado. Carteles "BOSQUE FRONDOSO" y "MANSIÓN OLVIDADA": cada uno es una zona de captura.
- [ ] **Pesca** en la charca.
- [ ] **La mansión:** la puerta del edificio entra y sale. Dentro hay salvajes en el suelo de madera.
  - La puerta de arriba a la izquierda dice que está atascada.
  - La de la derecha sube al DESVÁN.
- [ ] **Guardián del DESVÁN**, delante de la puerta rota: da premio al vencerlo o capturarlo y no vuelve a salir.
- [ ] **Entrenadores:** SEBAS y OLIVIA en el bosque, ELVIRA y ALFONSO en la mansión. Que salgan con su nombre, su foto y su equipo, no con los de BRENDAN, MAY o HOJA.

### MARISMA AZULIZA (desde el 17/11/2026)

- [ ] **Entrada:** desde la arena del oeste de PUEBLO AZULIZA se pasa a la marisma andando, sin pantalla de carga, y se vuelve igual.
- [ ] **La unión con el pueblo:** que los árboles y la arena sigan bien por el borde (filas 3 a 16).
- [ ] **Lluvia** y cartel "MARISMA AZULIZA". Es una zona de captura nueva: comprobar que la primera captura cuenta aquí y no en AZULIZA.
- [ ] **Partida guardada de antes:** las zonas ya gastadas siguen gastadas (la variable nueva empieza a 0).
- [ ] **TOMÁS y MARGARITA** te ven y luchan; los dos objetos de la hierba alta se pueden coger.
- [ ] **Pesca** en las dos charcas con la CAÑA VIEJA.

### DESIERTO PROFUNDO y RUINAS ARENOSAS (desde el 16/11/2026)

- [ ] **Entrada:** el montículo nuevo del desierto de la RUTA 111 (al este, abajo) lleva al DESIERTO PROFUNDO, y su salida devuelve al mismo sitio.
- [ ] **El mapa:** que no quede nada de la TORRE ESPEJISMO, y que los bordes (sobre todo el oeste, que es arena cortada) no queden raros.
- [ ] **Tormenta de arena** fuera y en combate, y carteles "DESIERTO PROFUNDO" y "RUINAS ARENOSAS". Cada uno es una zona de captura.
- [ ] **Ruinas:** el montículo del norte lleva a la entrada; las escaleras suben por las plantas 2 y 3 hasta la CÁMARA.
  - En las plantas 2 y 3, el suelo agrietado se rompe y caes a la de abajo.
  - En la 3, GOLPE ROCA rompe las dos rocas. El guardián tiene el sprite del Pokémon que sale y da premio al vencerlo o capturarlo.
- [ ] **Entrenadores:** SOLEDAD en el desierto y RAMIRO en las ruinas, a nivel 46-47.
- [ ] **Salvajes y objetos** de las dos zonas.

### ISLA NEVADA (desde el 16/11/2026)

- [ ] **Conexión:** surfeando hacia el norte desde la RUTA 124 se pasa a la ISLA NEVADA sin cortes, y la nieve empieza al cruzar.
- [ ] **El mapa:** que no se vean trozos raros de roca en el borde de la RUTA 124 ni en el islote.
- [ ] **Cartel de zona:** "ISLA NEVADA", también en la cueva, y que cuente como zona de captura propia.
- [ ] **Nieve en combate**, también en la cueva (dentro no nieva, así que ahí no).
- [ ] **Guardián de la CUEVA HELADA**, abajo del todo: se llega resbalando y da premio.
- [ ] **CUEVA HELADA:** se entra por el islote y la escalera devuelve fuera. Se puede recorrer resbalando por el hielo y llegar a los objetos y a NIEVES.
- [ ] **Entrenadores:** DUDLEY y KAYLEE en el agua (te ven al surfear), NIEVES en la cueva.
- [ ] **Salvajes** de hielo y la Bola de Nieve oculta en el banco de arena.

### GRUTA ÍGNEA (desde el 16/11/2026)

- [ ] **CÁMARA DEL MAGMA:** la salida del sur de la gruta baja a ella. Se sube por las escaleras hasta el guardián, que da premio al vencerlo o capturarlo.
- [ ] **Entrada:** en la sala del suroeste del SENDERO ÍGNEO (con FUERZA) hay una boca de cueva. Bajando por ella se llega a la GRUTA ÍGNEA, y la puerta del noreste devuelve al mismo sitio.
- [ ] **El mapa:** que no quede ningún trozo de máquina de la GUARIDA MAGMA, que no se pueda pisar la lava y que se pueda dar toda la vuelta.
- [ ] **Clima:** el sol fuerte se ve bien dentro de la cueva (si queda raro, se quita) y hay sol en los combates.
- [ ] **Cartel de zona:** "GRUTA ÍGNEA". Cuenta como zona de captura propia: se puede capturar aunque ya hayas capturado en el SENDERO ÍGNEO.
- [ ] **Entrenadores:** ROQUE, ÍGOR y la soldado Magma, a nivel 46-47, y te ven al pasar.
- [ ] **Salvajes y objetos:** POKéMON de fuego y roca a nivel del tramo 5, y los 4 objetos.

### Islas del ferry (desde el 16/11/2026)

- [ ] **Billetes:** con la 6.ª medalla, el encargado del puerto de CALAGUA da el Ticket Eón; con la 7.ª, el Mapa Viejo; con la 8.ª, el Ori-Ticket y el Misti-Ticket. Cada isla sale en la lista de destinos.
- [ ] **Viaje:** se llega a cada isla y el marinero te devuelve a CALAGUA. Los textos, en español.
- [ ] **Pokémon fuerte:** el sprite del mapa es el de la especie que sale en el combate (con semilla, otra).
  - Al vencerlo o capturarlo desaparece y da el premio y su megapiedra. Si huyes, sigue ahí.
  - Que no salga ningún legendario (ni Mew escondido en la hierba de la ISLA LEJANA, ni el triángulo de la ISLA ORIGEN).
  - Capturado, va al equipo (o a VETADOS si ya tienes uno de su línea) y no gasta la zona.
- [ ] **Entrenadores:** TERRY y CINDY (ISLA SUR), MIKE y AMY Y LIV (ISLA LEJANA), GINA Y MIA (ISLA ORIGEN) y LUCAS (ROCA OMBLIGO). Que te vean y no tapen el camino.
- [ ] **Salvajes:** pesca en las cuatro, hierba en la ISLA LEJANA y cueva en ROCA OMBLIGO, a nivel de su tramo.

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
- [ ] Primeros gimnasios (desde el 11/11/2026):
  - PETRA con 4 Pokémon (14-16), MARCIAL con 4 (21-23) y ERICO con 5 (30-32), una cura cada uno.
  - Ninguno lleva Mineral Evolutivo, Vidasfera ni objetos Elección (salvo Pañuelo).
  - ¿Siguen siendo un reto sin ser un muro?
- [ ] Jefes con estilo (desde el 15/11/2026):
  - Cada jefe juega con su estilo (trampas, Espacio Raro, chetarse, clima, estados, pantallas, aguante o velocidad) y se nota la diferencia entre uno y otro.
  - Usan bien sus movimientos de estrategia: ponen el Espacio Raro cuando son lentos, el clima al salir, las pantallas al principio…
  - Cambian de Pokémon con cabeza y dejan el as para el final.
  - No adivinan lo que no han visto (tu objeto, un movimiento que no has usado).
- [ ] Entrenadores normales: después de CANDELA eligen buenos movimientos y rematan. ¿Se nota demasiado?
  - Hasta ERICO, sus Pokémon no son más fuertes que los salvajes que has visto.
- [ ] Movimientos sin tope: salvajes y tuyos con ataques fuertes a nivel bajo. Que el juego siga siendo jugable.

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
