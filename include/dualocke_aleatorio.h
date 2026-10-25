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

#endif // GUARD_DUALOCKE_ALEATORIO_H
