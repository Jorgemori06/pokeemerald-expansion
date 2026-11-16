#ifndef GUARD_DUALOCKE_ALEATORIO_H
#define GUARD_DUALOCKE_ALEATORIO_H

// Dualocke: lo que el randomizer cambia al vuelo (tools/dualocke/aleatorio/).
// Sin semilla todo devuelve lo original.

// Estáticos y regalos (estaticos.py)
enum Species Dualocke_EstaticoAleatorio(enum Species species);
enum Species Dualocke_RegaloAleatorio(enum Species species);

// Objetos (objetos.py): los del suelo y ocultos van por su flag
enum Item Dualocke_ObjetoSuelo(u32 flag, enum Item item);
enum Item Dualocke_ObjetoRecogida(enum Item item);
bool32 Dualocke_ObjetosSalvajesAleatorios(void);
enum Item Dualocke_ObjetoSalvaje(bool32 masProbable);

// Intercambios con NPCs (intercambios.py). FALSE si ese intercambio se queda como el original.
bool32 Dualocke_IntercambioAleatorio(u32 intercambio, enum Species *especie, enum Species *pide, enum Item *objeto, u8 *ivs);

// Habilidades (habilidades.py): ABILITY_NONE si la especie se queda con las suyas
enum Ability Dualocke_HabilidadAleatoria(enum Species species);

// MT (mts.py). Dualocke_MovimientoMT y Dualocke_ObjetoMT están declaradas en include/item.h.
s32 Dualocke_PuedeAprenderMT(enum Species species, enum Move move);

// Pokédex HGSS: los movimientos de MT, MO y tutor que puede aprender la especie con la semilla,
// sin repetir (primero las MT y MO, luego los tutores nuevos y luego el resto de su lista original).
// Devuelve cuántos ha escrito en moves, como mucho max (DUALOCKE_MAX_ENSENABLES, en pokedex_common.h).
u32 Dualocke_MovimientosEnsenables(enum Species species, u16 *moves, u32 max);

// Movimientos por nivel (aprendizajes.py): NULL si la especie se queda con su tabla
const struct LevelUpMove *Dualocke_AprendizajeAleatorio(enum Species species);

// Tutores (mts.py): callnative en la macro move_tutor (asm/macros/event.inc)
void Dualocke_TutorAleatorio(void);

#endif // GUARD_DUALOCKE_ALEATORIO_H
