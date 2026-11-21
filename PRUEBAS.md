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

### CUMBRE METEORO (desde el 17/11/2026)

- [ ] **Entrada:** en la RUTA 115, a la derecha de la entrada de la CATARATA METEORO y una terraza más abajo, hay una cueva nueva en la pared. Lleva a la LADERA, y se vuelve igual.
- [ ] **LADERA:** se puede subir por las escaleras hasta la cueva de arriba (a la derecha). Hay salvajes en la hierba alta.
- [ ] **Arreglo del 18/11/2026:** las dos cuevas de la LADERA (la de bajada a la RUTA 115 y la de subida a la CUMBRE) ya funcionan, y se pueden coger la Piedra Dura y el Ticket-Recuerdo. Fuera del mapa se ve montaña, no agua.
- [ ] **CUMBRE:** nieve fuera y en combate, salvajes en la hierba escarchada y el guardián arriba, que da premio y no vuelve a salir.
- [ ] **Bases secretas:** la de la RUTA 115 que está junto a la cueva nueva sigue funcionando.

### PLAYA VOLCÁNICA (desde el 17/11/2026)

- [ ] **Entrada:** en la RUTA 122, por el hueco nuevo del anillo de rocas de arriba a la izquierda, se surfea hacia el oeste hasta la playa (sin pantalla de carga), y se vuelve igual.
- [ ] **La unión:** que no se vea nada raro en el borde, ni desde la playa ni desde la RUTA 122. Es lo más delicado: los dos mapas tienen gráficos distintos.
- [ ] **Sol normal** fuera, **sin sol en combate** (Miguel, 20/11/2026). Cartel "PLAYA VOLCÁNICA". Salvajes en la hierba alta; pesca y surf en el mar.
- [ ] **La ceniza (20/11/2026):** la hierba alta y el césped de la meseta se ven de color ceniza, como en la RUTA 113, y los árboles y las hojas de las flores siguen verdes.
  - Que no quede ningún trozo verde suelto (bordes del camino, del risco, de las termas y de la peña).
  - Que la unión con la RUTA 122 se siga viendo bien (ahí solo hay mar y rocas, que no cambian de color).
  - Al pasar por la hierba alta salen las hojitas verdes de siempre (son un efecto aparte, con sus propios colores, no del mapa): mirar si quedan raras.
- [ ] **El personaje al capturar surfeando:** a Miguel se le rompió **al volver de capturar** un Pokémon en el agua (20/11/2026). Probarlo varias veces y hacer foto si pasa.
- [ ] **Termas:** se ven bien (sin trozos de acantilado ni de hierba raros).
- [ ] **Guardián** en la arena (Slither Wing sin semilla): da premio y no vuelve a salir.
- [ ] **Mapa rehecho (17/11/2026):** se baja de la meseta a la playa saltando el risco o por la escalera, y se sube solo por la escalera. Que no se vea ninguna pieza rara (orillas, risco, árboles, la charca de marea).

### CIÉNAGA TÓXICA (desde el 17/11/2026)

- [ ] **Entrada:** bajando por el borde sur de la RUTA 117 (x 32-36, junto a la hierba alta) se pasa a la ciénaga sin cortes. Que no se vean copas de árbol sueltas en la unión. Al cruzar empieza a llover.
- [ ] **El mapa:** que las orillas de las charcas y el camino de barro se vean bien, y que la lengua de tierra lleve al islote.
- [ ] **Cartel** "CIÉNAGA TÓXICA", y que cuente como zona de captura propia.
- [ ] **Salvajes** en la hierba alta (Veneno, nivel 27-31) y con caña en las charcas. La científica habla.
- [ ] **Guardián** del islote (Dragalge sin semilla): da el Lodo Negro y no vuelve a salir.

### BOSQUE SINIESTRO (desde el 17/11/2026)

- [ ] **Entrada:** bajando por el borde sur de la RUTA 123 (x 103-106) se pasa al bosque sin cortes. Que no se vean copas de árbol sueltas ni troncos cortados en la unión. Al cruzar se oscurece (sombra) y cambia la música.
- [ ] **El bosque:** que los árboles se vean bien (copas, troncos), que el risco del centro se salte hacia abajo y no se suba, y que se pueda volver a la entrada rodeándolo por el este.
- [ ] **Cartel** "BOSQUE SINIESTRO", y que cuente como zona de captura propia.
- [ ] **Salvajes** en la hierba alta (Siniestro, Fantasma y Bicho, nivel 54-58). La bruja del primer claro habla.
- [ ] **Guardián** del claro del fondo (Hydreigon sin semilla): da la Tabla Pavor y no vuelve a salir. Con semilla, que salga otro.

### Islas de las rutas del sur (desde el 17/11/2026)

- [ ] **Se llega a las tres islas surfeando (17/11/2026):** por el hueco nuevo en las rocas de la RUTA 129 (46, 24), de la RUTA 131 (7, 12) y de la RUTA 134 (9, 21). Que el hueco se vea como un paso normal entre rocas.
- [ ] **ISLA DE RUINAS:** desde el norte de la RUTA 131, surfeando hacia arriba.
  - La cueva de la orilla de abajo sale por la del montículo, y se vuelve igual.
  - La puerta de la torre lleva a la TORRE; la escalera de arriba ya no está.
  - Niebla fuera y Campo de Niebla en combate.
- [ ] **ISLA VOLCÁNICA:** desde el sur de la RUTA 134 (la parte sin corriente, cerca de PORTUAL).
  - La cueva del montículo baja al CRÁTER y la cueva nueva del escalón sube.
  - En la ceniza salen salvajes. Sol fuera y en combate.
- [ ] **ISLA ARENOSA:** desde el este de la RUTA 129. Tormenta de arena. Salvajes en la hierba alta del islote de hierba (al oeste). DARÍO lucha.
- [ ] **Islas rehechas (17/11/2026):** que las orillas, el bajío y las peñas se vean bien. Que en las peñas no se pueda hacer una base secreta. En la ISLA DE RUINAS, que la playa de abajo una bien con la franja de arena. En la ISLA VOLCÁNICA, que la cima del montículo se vea bien.
- [ ] **Uniones:** que las tres se vean bien desde la ruta y desde la isla, sin trozos raros en el borde.
- [ ] **Guardianes** (TORRE, CRÁTER e ISLA ARENOSA): dan premio y no vuelven a salir. Cada isla es una zona de captura.
- [ ] **Guardianes nuevos (17/11/2026), sin semilla:** ISLA SUR Dragonite, ISLA LEJANA Flutter Mane, ISLA ORIGEN Roaring Moon, ROCA OMBLIGO Volcarona (cima) y Kingdra (fondo), ISLA ARENOSA Sandy Shocks. Que salga su sprite en el mapa y que capturar un Pokémon Paradoja no cuente como legendario.

### BOSQUE FRONDOSO y MANSIÓN OLVIDADA (desde el 17/11/2026)

- [ ] **Entrada:** en el claro del noreste del BOSQUE PETALIA hay dos árboles de CORTE; detrás, el pasillo lleva al BOSQUE FRONDOSO sin pantalla de carga, y se vuelve igual.
- [ ] **La unión:** que los árboles del borde de abajo del BOSQUE FRONDOSO sigan bien con los del BOSQUE PETALIA, y que no se vea nada raro al ir por el pasillo.
- [ ] **El bosque:** que ningún árbol salga cortado. Carteles "BOSQUE FRONDOSO" y "MANSIÓN OLVIDADA": cada uno es una zona de captura.
- [ ] **Bosque rehecho (17/11/2026):** el risco del medio se salta hacia abajo y no se sube; para ir a la mansión se rodea por el este. El cartel de la mansión se lee desde abajo.
- [ ] **Pesca** en la charca.
- [ ] **La mansión:** la puerta del edificio entra y sale. Dentro hay salvajes en el suelo de madera.
  - La puerta de arriba a la izquierda dice que está atascada.
  - La de la derecha sube al DESVÁN.
- [ ] **Guardián del DESVÁN**, delante de la puerta rota: da premio al vencerlo o capturarlo y no vuelve a salir.
- [ ] **Entrenadores:** SEBAS y OLIVIA en el bosque, ELVIRA y ALFONSO en la mansión. Que salgan con su nombre, su foto y su equipo, no con los de BRENDAN, MAY o HOJA.

### MARISMA AZULIZA (desde el 17/11/2026)

- [ ] **Entrada:** desde la arena del oeste de PUEBLO AZULIZA se pasa a la marisma andando, sin pantalla de carga, y se vuelve igual.
- [ ] **La unión con el pueblo:** que los árboles y la arena sigan bien por el borde.
- [ ] **Arreglo del 18/11/2026:** desde AZULIZA ya no se ve un muro de árboles encima de la playa de la RUTA 106 (la marisma ya no sobresale por encima del pueblo). En la marisma no hay hierba muy alta cortada ni la charquita suelta de abajo.
- [ ] **Lluvia** y cartel "MARISMA AZULIZA". Es una zona de captura nueva: comprobar que la primera captura cuenta aquí y no en AZULIZA.
- [ ] **Partida guardada de antes:** las zonas ya gastadas siguen gastadas (la variable nueva empieza a 0).
- [ ] **TOMÁS y MARGARITA** te ven y luchan. El Ticket-Recuerdo de la hierba se puede coger.
- [ ] **Pesca** en el lago con la CAÑA VIEJA.
- [ ] **Mapa rehecho (17/11/2026):** la escalera del risco sube de la arena a la pradera. Que no se vea ninguna pieza rara (orillas del lago, risco, árboles, la charca de marea).
- [ ] **La cala (con SURF):** al otro lado del lago, Dondozo y Tatsugiri (sin semilla) a nivel 59 y la Semilla Milagro. Cada uno da premio y no vuelve a salir. Sin SURF no se llega.
- [ ] **GOLPE ROCA:** las cuatro rocas se rompen y a veces sale un salvaje.

### DESIERTO PROFUNDO y RUINAS ARENOSAS (desde el 16/11/2026)

- [ ] **Entrada:** el montículo nuevo del desierto de la RUTA 111 lleva al DESIERTO PROFUNDO, y su salida devuelve al mismo sitio.
  - **Dónde está:** unas 8 casillas más arriba y a la derecha de la puerta de las RUINAS DESIERTO (lo midió Jorge en el emulador, 19/11/2026). Hacen falta las Gafas Aisladoras.
  - Miguel no lo encontró jugando (20/11/2026): mirar si se distingue bien del resto de la arena.
- [ ] **El mapa:** que no quede nada de la TORRE ESPEJISMO, y que los bordes (sobre todo el oeste, que es arena cortada) no queden raros.
- [ ] **Tormenta de arena** fuera y en combate, y carteles "DESIERTO PROFUNDO" y "RUINAS ARENOSAS". Cada uno es una zona de captura.
- [ ] **Ruinas:** el montículo del norte lleva a la entrada; las escaleras suben por las plantas 2 y 3 hasta la CÁMARA.
  - En las plantas 2 y 3, el suelo agrietado se rompe y caes a la de abajo.
  - En la 3, GOLPE ROCA rompe las dos rocas. El guardián tiene el sprite del Pokémon que sale y da premio al vencerlo o capturarlo.
- [ ] **Entrenadores:** SOLEDAD en el desierto y RAMIRO en las ruinas, a nivel 46-47.
- [ ] **Salvajes y objetos** de las dos zonas.

### ISLA NEVADA (desde el 16/11/2026)

- [ ] **Conexión:** surfeando hacia el norte desde la RUTA 124 se pasa a la ISLA NEVADA sin cortes, y la nieve empieza al cruzar. Se llega sin bucear, por los huecos nuevos de la RUTA 124 en (18, 16) y (11, 0).
- [ ] **El mapa:** que no se vean trozos raros de roca en el borde de la RUTA 124 ni en el islote.
- [ ] **Isla rehecha (17/11/2026):** que las orillas, el bajío, la cresta y las peñas se vean bien. Que la entrada de la cueva, en el pie de la cresta, lleve a la CUEVA HELADA y que la escalera devuelva delante de ella. Que en la cresta y las peñas no se pueda hacer una base secreta.
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

### Interfaz (desde el 16/11/2026)

- [ ] **POKéDEX nueva (estilo HeartGold/SoulSilver):**
  - Que abra desde el menú y se mueva bien por todas las páginas (información, estadísticas, evoluciones, formas, área, grito, tamaño).
  - Página de estadísticas: que los textos en español quepan (CAPT., RITMO, EXP. BASE, AMISTAD, ECLOSIÓN, grupos huevo) y no se monten unos encima de otros.
  - Que los movimientos por nivel, las MT y la habilidad sean los de la semilla: comparar con la pantalla de datos de un Pokémon tuyo y con lo que dice una MT al usarla.
  - Evoluciones: que el método se lea bien en español ("Nv.↑16", "Usar Piedra Fuego", "de noche", "tipo Siniestro en el equipo").
- [ ] **Combate:** los iconos de tipo del rival junto a su barra; los textos más rápidos se pueden leer; sin la entrada deslizante.
- [ ] **No se puede huir de un entrenador:** en un combate de entrenador, HUIR da el mensaje de que no se puede.
- [ ] **Objetos:** al recoger uno sale arriba su imagen y su descripción, y se quita al cerrar el mensaje.
- [ ] **Carteles de zona:** banda negra arriba con el nombre y la hora. Mirar los nombres largos (CIUDAD ARRECÍPOLIS, CALLE VICTORIA…).

### Recuerdamovimientos y Ticket-Recuerdo

- [ ] En un Centro Pokémon, la señora a la derecha del PC: sin ticket te lo dice; con ticket enseña un movimiento de nivel y gasta el ticket solo si lo aprende.
- [ ] Que no tape el PC ni el mapa de la región, y que esté en todos los Centros (también en LAVACALDA).
- [ ] Que los tickets de las rutas se vean y se puedan coger. Mirar sobre todo los de las rutas de mar (en el agua, con Surf) y los ocultos de las rutas largas.
- [ ] Que la pantalla de datos ya no deje recordar movimientos gratis.

### Randomizer (con semilla)

- [ ] Salvajes, entrenadores, iniciales y rival cambian, sin legendarios donde no toca.
- [ ] Los jefes llevan su as con megapiedra desde el Mega-Aro, y objetos que les sirven.
- [ ] **Megas de las formas Gigamax (desde el 16/11/2026):**
  - Coger alguna de las 26 megapiedras nuevas (la Orbeetlita en la RUTA 102, la Drednawita en la RUTA 106…): que salga con su icono y su nombre, y vaya al bolsillo MEGAPIEDRAS.
  - Megaevolucionar a uno (con el Mega-Aro): animación de mega, sprite de la forma Gigamax, tipo y estadísticas nuevas en el combate, y que vuelva a la forma normal al acabar o al debilitarse.
  - Que ningún salvaje salga en forma Gigamax y que el Dinamax siga sin poder usarse.
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

### 3. Miguel, 18/11/2026 (versión 8, hasta la 3.ª medalla)

**Bien:**
- Hasta la 1.ª medalla, el BOSQUE FRONDOSO y la MANSIÓN OLVIDADA, CIUDAD PORTUAL y hasta el 3.er gimnasio.

**Fallos (arreglados en `miguel/arreglos-prueba-1`):**
- **CUMBRE METEORO:** te quedabas encerrado.
  - Las dos cuevas de la LADERA no funcionaban: estaban a altura 3 y el suelo, a 5. Una puerta solo se usa si su altura es la del jugador, o 0. Ahora van a 0, como la de la CATARATA METEORO.
  - Sus dos objetos, por lo mismo, no se podían coger.
  - El borde del mapa era mar (copiado de la RUTA 115) y se veía el mapa "cortado por agua". Ahora es montaña (el de la RUTA 114).
- **MARISMA AZULIZA:**
  - Baldosas mal puestas: la hierba muy alta no tiene borde de abajo con los gráficos de AZULIZA y quedaba cortada. Ahora es hierba alta. También se quitó una charquita de 2 × 2 suelta.
  - Árboles en AZULIZA, la ciudad del 2.º gimnasio: la marisma sobresalía 7 filas por encima del pueblo, justo donde está la RUTA 106. Ahora va a la altura del pueblo. (La #103 de Jorge lo tapaba cambiando el orden de las conexiones.)
- **Para que no vuelva a pasar:** `comprobar_zonas.py` avisa de puertas y objetos de las zonas nuevas a una altura que no es la del suelo, y `colocar_objetos.py` ajusta la altura de sus objetos al suelo en el que están.

**Idea:** una CANTERA con POKéMON de tipo Acero en la RUTA 116, por la salida del TÚNEL FERVERGAL (apuntada en `PLAN.md`).

### 2. Jorge, 26/10/2026 (tarde, con el menú de depuración)

**Bien:**
- Con Poké Balls compradas, el segundo salvaje de la ruta ya no se puede capturar (arreglo de la partida 1). El mensaje cabe.
- Mewtwo (legendario) va directo a VETADOS.
- Un Bulbasaur repetido va a VETADOS; al morir el primero (aviso con 19 vidas, caja MUERTOS) se puede sacar el segundo.
- Los Caramelos Raros paran en el cap (16 con 0 medallas).

**Fallo:** al volar, "¿A dónde quieres VOLAR?" se cortaba (la ventana es estrecha). Ahora "¿Adónde VOLAR?".

**No era fallo:** no poder volar a ningún sitio. Solo se vuela a las ciudades ya visitadas.
