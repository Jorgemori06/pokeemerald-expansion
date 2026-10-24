#ifndef GUARD_DUALOCKE_AVISO_H
#define GUARD_DUALOCKE_AVISO_H

// Dualocke: aviso al morir. Sustituye el "X fainted!" de los Pokémon del jugador por
// "X has died!" con las vidas que quedan, en los combates en los que cuentan las vidas.
bool32 IsDualockeBattle(void); // src/dualocke.c
const u8 *Dualocke_GetFaintString(enum BattlerId battler);

#endif // GUARD_DUALOCKE_AVISO_H
