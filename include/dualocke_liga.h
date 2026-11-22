#ifndef GUARD_DUALOCKE_LIGA_H
#define GUARD_DUALOCKE_LIGA_H

// Dualocke: regla de la Liga (src/dualocke_liga.c).
void Dualocke_LigaEmpiezaCombate(void);
bool32 Dualocke_EsCombateLiga(void);
bool32 Dualocke_EsCurativo(enum Item item);
bool32 Dualocke_LigaPuedeCurar(void);
void Dualocke_LigaObjetoUsado(enum BattlerId battler, enum Item item);

#endif // GUARD_DUALOCKE_LIGA_H
