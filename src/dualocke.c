#include "global.h"
#include "battle.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "dualocke.h"
#include "event_data.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "string_util.h"
#include "trainer_hill.h"
#include "constants/battle.h"

// Dualocke: sistema de vidas y caja de muertos.
// - Cada Pokémon del jugador que acaba un combate debilitado muere: se mueve a la
//   última caja del PC (bloqueada) y se resta una vida.
// - Con 0 vidas se sigue jugando; la siguiente muerte, o perder un combate, hace
//   perder el locke (FLAG_DUALOCKE_LOCKE_LOST). El juego no se bloquea: solo se marca.

static const u8 sText_DeadBoxName[] = _("DEAD");

void Dualocke_InitNewGame(void)
{
    VarSet(VAR_DUALOCKE_LIVES, DUALOCKE_START_LIVES);
    FlagClear(FLAG_DUALOCKE_LOCKE_LOST);
    StringCopy(GetBoxNamePtr(DUALOCKE_DEAD_BOX), sText_DeadBoxName);
}

u32 Dualocke_GetLives(void)
{
    return VarGet(VAR_DUALOCKE_LIVES);
}

bool32 Dualocke_IsLockeLost(void)
{
    return FlagGet(FLAG_DUALOCKE_LOCKE_LOST);
}

bool32 Dualocke_IsDeadBox(u32 boxId)
{
    return boxId == DUALOCKE_DEAD_BOX;
}

static void LoseLife(void)
{
    u32 lives = Dualocke_GetLives();

    if (lives == 0)
        FlagSet(FLAG_DUALOCKE_LOCKE_LOST);
    else
        VarSet(VAR_DUALOCKE_LIVES, lives - 1);
}

static void BuryMon(struct Pokemon *mon)
{
    u32 boxPos;

    for (boxPos = 0; boxPos < IN_BOX_COUNT; boxPos++)
    {
        struct BoxPokemon *slot = GetBoxedMonPtr(DUALOCKE_DEAD_BOX, boxPos);
        if (GetBoxMonData(slot, MON_DATA_SPECIES) == SPECIES_NONE)
        {
            CopyMon(slot, &mon->box, sizeof(mon->box));
            break;
        }
    }
    // Si la caja estuviera llena (más de 30 muertes), el Pokémon simplemente desaparece.
    ZeroMonData(mon);
}

// No es static: la usa también el aviso al morir (src/dualocke_aviso.c)
bool32 IsDualockeBattle(void)
{
    if (gBattleTypeFlags & (BATTLE_TYPE_LINK
                          | BATTLE_TYPE_RECORDED
                          | BATTLE_TYPE_RECORDED_LINK
                          | BATTLE_TYPE_FRONTIER
                          | BATTLE_TYPE_SAFARI
                          | BATTLE_TYPE_FIRST_BATTLE
                          | BATTLE_TYPE_EREADER_TRAINER))
        return FALSE;
    if (CurrentBattlePyramidLocation() != PYRAMID_LOCATION_NONE)
        return FALSE;
    if (InBattlePike() || InTrainerHillChallenge())
        return FALSE;
    return TRUE;
}

// Se llama al terminar un combate, con el equipo del jugador ya restaurado.
void Dualocke_OnBattleEnd(bool32 playerDefeated)
{
    u32 i;
    bool32 anyDead = FALSE;

    if (!IsDualockeBattle())
        return;

    // Perder un combate (todo el equipo debilitado) es perder el locke.
    // No se mueven los Pokémon: el equipo no puede quedarse vacío.
    if (playerDefeated)
    {
        FlagSet(FLAG_DUALOCKE_LOCKE_LOST);
        return;
    }

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];

        if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE
         || GetMonData(mon, MON_DATA_IS_EGG)
         || GetMonData(mon, MON_DATA_HP) != 0)
            continue;

        BuryMon(mon);
        LoseLife();
        anyDead = TRUE;
    }

    if (anyDead)
    {
        CompactPartySlots();
        CalculatePlayerPartyCount();
    }
}
