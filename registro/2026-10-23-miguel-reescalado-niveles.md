# 23/10/2026 · Miguel · Reescalado de niveles

Segunda tarea de la sesión de Miguel con Claude, ya con el nuevo reparto: Miguel se encarga del equilibrio y Jorge de las funcionalidades (sección 13 de `DUALOCKE.md`). Rama `miguel/reescalado-niveles`.

## Decisiones de Miguel

| Pregunta | Decisión |
| --- | --- |
| ¿A qué nivel llega el entrenador normal más fuerte al final de cada tramo? | **Cap − 3** |
| ¿Y el equipo de los jefes? | **Todo el equipo al cap** |
| ¿Salvajes? | **Entrenadores de la zona − 3** |
| ¿Revanchas y postgame? | **Más adelante** |

## Cómo se hizo

- **Escalar por el nivel original** (lo que hace el Universal Randomizer con el "+15%") **no sirve** con esta curva. Entre Norman y Alana el original sube 2 niveles (31 → 33) y la nuestra 12 (50 → 62), así que dos entrenadores que en Esmeralda se llevaban un nivel acabarían separados por seis.
- **Se asignó cada mapa a su tramo de historia** y, dentro del tramo, se reparte del cap anterior − 3 al cap − 3 según el nivel original. La banda original de cada tramo se calcula con los percentiles 10 y 95 del Pokémon más fuerte de cada entrenador, para que no la deformen casos raros.
- **Script:** `tools/dualocke/reescalar_niveles.py`. Lee los niveles originales del commit base de la expansion (`30988a58b`), así que se puede volver a lanzar tras cambiar la tabla y da siempre lo mismo. Con `--resumen` enseña la tabla sin escribir nada.

## Resultado

| Tramo | Cap | Normales | Jefes | Salvajes |
| --- | --- | --- | --- | --- |
| 1 | 16 | 3-13 | Petra 16, rival en Ruta 103 a 7, rival en Rustboro a 16 | 2-10 |
| 2 | 23 | 13-20 | Marcial 23 | 10-17 |
| 3 | 32 | 20-29 | Erico 32, rival 28, Blasco en Malvalona 26 | 19-25 |
| 4 | 43 | 29-40 | Candela 43, Magno 42 | 26-34 |
| 5 | 50 | 47 | Norman 50 | — |
| 6 | 62 | 47-59 | Alana 62, rival 62 | 44-53 |
| 7 | 73 | 59-70 | Vito y Leti 73, Magno 73, rival 70 | 56-66 |
| 8 | 84 | 70-81 | Galano 84, Aquiles 84 | 67-73 |
| 9 | 100 | 81-97 | Sidney 92, Fátima 94, Nívea 95, Dracón 97, Plubio 100, Blasco 90 | 78-85 |

477 entrenadores reescalados (475 en la primera versión; Magno y Tatiano del Centro Espacial se añadieron después), más todas las zonas salvajes de Hoenn de la historia principal.

## Decisiones de Claude por el camino (revisables)

- **Jefes a mitad de tramo** (rival, Magno, Aquiles, Blasco en Malvalona): el equipo entero 3 niveles por encima de los entrenadores de ese punto, sin pasar del cap. Ponerlos directamente al cap obligaría a subir hasta el cap a mitad de tramo.
- **Niveles exactos del Alto Mando**, dentro del margen de 92-97 que ya estaba decidido: 92, 94, 95 y 97.
- **El rival de Rustboro sale a 16**, lo mismo que Petra. Su mapa (Ruta 104) es del tramo 1, aunque el combate es justo después de la primera medalla, así que su "+3" choca con el cap 16. Si parece duro, se baja.
- **Las tres cañas dan el mismo nivel** en cada zona (antes la Caña Vieja daba nivel 5 en cualquier sitio).
- **Entrenadores de agua en rutas tempranas** (por ejemplo, la Ruta 106 o la parte con Surf de la Ruta 103): se quedan con el nivel de su tramo aunque llegues a ellos más tarde. Serán algo fáciles, pero no rompen nada.
- **Gimnasio de Norman:** todos sus entrenadores a 47 (cap − 3), porque el tramo 5 no tiene nada más.

## Queda

- **Revanchas, postgame y Casa Trampa** sin reescalar.
- **Equipos de los jefes:** +1/+2 Pokémon, objetos y megas. Es la siguiente tarea de equilibrio.
- **Probar jugando** que la curva se siente bien, sobre todo los primeros tramos y el rival de Rustboro.
