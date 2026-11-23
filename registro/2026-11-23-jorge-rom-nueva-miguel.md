# 23/11/2026 — Jorge: ROM nueva para Miguel

## Qué pasó

Miguel perdió a todo el equipo en el segundo gimnasio (MARCIAL, en PUEBLO AZULIZA) con la semilla `3483218843`. Jorge le da otra oportunidad y sigue con su partida.

El equipo de MARCIAL con esa semilla:

| Pokémon | Nivel | Objeto | Movimientos |
|---|---|---|---|
| Greavard | 21 | Baya Lichi | Terremoto, Brillo Mágico, Viento Afín, Bomba Lodo |
| Dwebble | 22 | Cinta Fuerte | Zumbido, Simún de Arena, Onda Trueno, Pulso Cura |
| **Pawmo** | 22 | Baya Zidra | **Fuerza Bruta** (120, STAB), **Rayo Fusión** (100, STAB), Esquirla Helada (prioridad), Onda Trueno |
| Crabrawler | 23 | Pañuelo de Seda | Patada Giro, Fuerza, Cara Susto, Amnesia |

- El Pawmo tiene 24 IVs. Su habilidad con esa semilla es Llovizna, Defensa Hoja o Capa Tóxica.
- Fuerza Bruta y Rayo Fusión llevan STAB, con 85 de Velocidad base. Además tiene Esquirla Helada con prioridad y Onda Trueno para paralizar.
- Contra un equipo de nivel 20, cada golpe hace un roto.

## ROM nueva

- Semilla `1649870500`, versión 9.1 (master `a198bc1aa2`). md5 `06b1691653dca9fc75357ef77e91d6ac`.
- Probada: con el bot se llega en una partida nueva hasta el camión (nombre MIKEMINE).

## Para Miguel (equilibrio)

No es mala suerte de una semilla: el randomizer da a los jefes movimientos muy fuertes desde el principio en todas las semillas. Potencia máxima de los movimientos de los jefes de los tres primeros gimnasios:

| Semilla | PETRA | MARCIAL | ERICO |
|---|---|---|---|
| Miguel, vieja | 130 (Martillo Hielo, Llama Azul, Infierno…) | 120 (Fuerza Bruta, Rayo Fusión, Terremoto) | 150 (Estallido, Danza Pétalo…) |
| Miguel, nueva | 120 (Asalto Espadón, Llama Fusión) | 100 (Llama Fusión, Terremoto…) | 130 (Patada Salto Alta, Placaje Eléctrico…) |
| Jorge | 130 (Patada Salto Alta, Ariete) | 120 (Megacuerno) | 125 (Onda Mental, Onda Certera…) |

El tope por tramo de los jefes solo limita la suma de estadísticas base, no la potencia de los movimientos. Una idea sería poner también un tope de potencia por tramo, sobre todo para los movimientos con STAB, o quitar los movimientos exclusivos de legendarios (Rayo Fusión, Llama Azul, Onda Mental…) en los primeros gimnasios.
