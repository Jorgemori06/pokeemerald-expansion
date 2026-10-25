#ifndef GUARD_DUALOCKE_H
#define GUARD_DUALOCKE_H

#include "pokemon_storage_system.h"

// Vidas del locke: se empieza con 20 y existe además la "vida 0".
// Con 0 vidas se sigue jugando; la siguiente muerte hace perder el locke.
#define DUALOCKE_START_LIVES 20

// La última caja del PC guarda a los Pokémon muertos y está bloqueada.
#define DUALOCKE_DEAD_BOX (TOTAL_BOXES_COUNT - 1)
// La penúltima es la caja de prohibidos: regalos, eventos y fósiles repetidos o legendarios.
#define DUALOCKE_BANNED_BOX (TOTAL_BOXES_COUNT - 2)

void Dualocke_InitNewGame(void);
void Dualocke_OnBattleEnd(bool32 playerDefeated);
u32 Dualocke_GetLives(void);
bool32 Dualocke_IsLockeLost(void);
bool32 Dualocke_IsDeadBox(u32 boxId);
bool32 Dualocke_IsBannedBox(u32 boxId);
bool32 Dualocke_IsLockedBox(u32 boxId);
bool32 Dualocke_IsBoxMonLocked(u32 boxId, u32 boxPos);
bool32 Dualocke_ShouldBanMon(struct Pokemon *mon);
u32 Dualocke_SendMonToBannedBox(struct Pokemon *mon);
bool32 Dualocke_TryBanPartyMon(u32 partyIndex);

// Primera captura por zona (Capture Clause).
// Estado del encuentro salvaje del combate actual.
enum DualockeEncounter
{
    DUALOCKE_ENCOUNTER_NO_RULE,     // La regla no se aplica (evento, estático, entrenador, antes de tener Balls…): se puede capturar
    DUALOCKE_ENCOUNTER_FIRST,       // Primer Pokémon válido de la zona: se puede capturar y gasta la zona
    DUALOCKE_ENCOUNTER_SHINY,       // Shiny: se puede capturar siempre y no gasta la zona
    DUALOCKE_ENCOUNTER_DUPE,        // Repetido (línea sin rama elegida o ramas que ya tienes): no cuenta, no se puede capturar y la zona sigue libre
    DUALOCKE_ENCOUNTER_LEGENDARY,   // Legendario o singular: no cuenta, no se puede capturar y la zona sigue libre
    DUALOCKE_ENCOUNTER_ZONE_USED,   // La zona ya tuvo su encuentro: no se puede capturar
};

bool32 Dualocke_IsZoneCaptureUsed(u32 mapsec);
void Dualocke_UseZoneCapture(u32 mapsec);
bool32 Dualocke_IsDupe(enum Species species);
bool32 Dualocke_IsEvolutionBlocked(struct Pokemon *mon, enum Species targetSpecies);
bool32 Dualocke_IsSpeciesLegendary(enum Species species);
enum DualockeEncounter Dualocke_GetWildEncounterStatus(struct Pokemon *wildMon, u32 mapsec);
void Dualocke_SetRandomEncounter(void);
void Dualocke_OnBattleStart(void);
enum DualockeEncounter Dualocke_GetCurrentEncounter(void);
bool32 Dualocke_CanCatchCurrentEncounter(void);

#endif // GUARD_DUALOCKE_H
