# 23/10/2026 · Miguel · Equipos de los jefes

Tercera tarea de equilibrio de la sesión de Miguel. Rama `miguel/equipos-jefes`, encima de `miguel/reescalado-niveles` (PR #3).

## Decisiones de Miguel

| Pregunta | Decisión |
| --- | --- |
| ¿Quién recibe Pokémon extra? | **+2** líderes, Alto Mando y Plubio; **+1** rival, Blasco, Magno, Aquiles y admins (máximo 6) |
| ¿Qué especies en los huecos nuevos? | **Del tipo del jefe** (el randomizer las cambiará igualmente) |
| ¿Qué mega lleva cada jefe desde el aro? | **Las canónicas**; donde no hay, una del tipo del jefe |
| ¿Objetos? | **Solo la megapiedra**; el resto, el randomizer |

## Equipos (el último es el as)

| Jefe | Nivel | Equipo |
| --- | --- | --- |
| Petra | 16 | Geodude, Larvitar*, Onix*, Aron*, Nosepass |
| Marcial | 23 | Machop, Meditite, Mankey*, Timburr*, Makuhita |
| Erico | 32 | Electrode, Magneton, Luxray*, Ampharos*, Raichu*, Manectric |
| Candela | 43 | Ninetales*, Magcargo, Houndoom*, Arcanine*, Camerupt, Torkoal |
| Norman | 50 | Spinda, Vigoroth, Linoone, Ursaring*, Kangaskhan*, Slaking |
| Alana | 62 | Swellow*, Tropius, Pelipper, Skarmory, Staraptor*, **Altaria (mega)** |
| Vito y Leti | 73 | Claydol, Xatu, Lunatone, Solrock, Bronzong*, **Metagross* (mega)** |
| Galano | 84 | Whiscash, Walrein, Crawdaunt, Lanturn*, Kingdra, **Starmie* (mega)** |
| Sidney | 92 | Mightyena, Shiftry, Cacturne, Crawdaunt, Honchkrow*, **Absol (mega)** |
| Fátima | 94 | Dusknoir, Sableye, Mismagius*, Chandelure*, Gengar*, **Banette (mega)** |
| Nívea | 95 | Walrein, Froslass*, Weavile*, Mamoswine*, Abomasnow*, **Glalie (mega)** |
| Dracón | 97 | Altaria, Kingdra, Flygon, Garchomp*, Dragonite*, **Salamence (mega)** |
| Plubio | 100 | Wailord, Tentacruel, Ludicolo, Whiscash, Milotic, **Gyarados (mega)** |
| Blasco (Malvalona / Calle Victoria) | 26 / 90 | Swablu*, Kirlia / Altaria, Delcatty, Roserade, Magnezone, Gallade*, **Gardevoir (mega)** |
| Magno (Chimenea / Guarida / Centro Espacial) | 42 / 73 / 84 | Mightyena, Golbat→Crobat, Houndoom*, Camerupt (**mega** desde la Guarida) |
| Aquiles | 84 | Mightyena, Crobat, Muk*, **Sharpedo (mega)** |
| Rival | — | Evoluciona según el nivel, +1 de su grupo habitual (Wingull, Slugma, Lotad o Tropius) y, en Ciudad Calagua, su inicial con **mega** |

\* Pokémon nuevo.

- **Admins:** Tatiano, Silvina y Matías ganan un Pokémon (Houndoom, Crawdaunt o Sharpedo según el equipo), y los suyos evolucionan según el nivel.
- **Plubio:** su as pasa a ser Gyarados, el que tiene mega. Milotic se queda en el equipo.
- **Galano:** Luvdisc sale para dejar sitio. **Fátima y Nívea:** se quitan las especies repetidas.

## Cómo se hizo

- `tools/dualocke/equipos_jefes.py` construye cada equipo desde el original de la expansion más una tabla, con los niveles de `reescalar_niveles.py`. Se puede volver a lanzar: primero el reescalado y luego los equipos.
- Los Pokémon originales conservan sus movimientos (también al evolucionar). Los nuevos usan los movimientos por defecto de su nivel.
- **Comprobado en el código:**
  - Los rivales megaevolucionan con solo llevar la piedra: el Aro Mega solo se exige al jugador (`CanMegaEvolve` en `src/battle_util.c`).
  - La IA usa el gimmick en cuanto puede (`src/battle_ai_main.c`).
- **Arreglo del reescalado** (va en el PR #3): Magno y Tatiano del Centro Espacial no se reescalaban, porque ese combate usa `multi_2_vs_2`. Ahora son 477 entrenadores, no los 475 que dice el registro del reescalado.

## Decisiones de Claude por el camino (revisables)

- Las especies nuevas de cada jefe y las megas donde no había canónica: Metagross para Vito y Leti, y Starmie (mega de Leyendas Z-A) para Galano.
- El rival de la Ruta 119 **no** lleva mega: ese combate es antes de Máximo y el aro.
- Wattson: Electrike se cambia por Raichu, para no tener dos Manectric.

## Queda

- **Probar jugando**, sobre todo los primeros gimnasios con 5 Pokémon y los combates contra megas.
- ~~Evolucionar por nivel a los entrenadores normales~~: hecho en la rama siguiente (`miguel/evoluciones-entrenadores`).
