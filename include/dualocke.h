#ifndef GUARD_DUALOCKE_H
#define GUARD_DUALOCKE_H

#include "pokemon_storage_system.h"

// Vidas del locke: se empieza con 20 y existe además la "vida 0".
// Con 0 vidas se sigue jugando; la siguiente muerte hace perder el locke.
#define DUALOCKE_START_LIVES 20

// La última caja del PC guarda a los Pokémon muertos y está bloqueada.
#define DUALOCKE_DEAD_BOX (TOTAL_BOXES_COUNT - 1)

void Dualocke_InitNewGame(void);
void Dualocke_OnBattleEnd(bool32 playerDefeated);
u32 Dualocke_GetLives(void);
bool32 Dualocke_IsLockeLost(void);
bool32 Dualocke_IsDeadBox(u32 boxId);

#endif // GUARD_DUALOCKE_H
