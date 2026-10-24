#include "global.h"
#include "battle.h"
#include "battle_message.h"
#include "dualocke.h"
#include "dualocke_aviso.h"
#include "dualocke_es.h"
#include "pokemon.h"

// Dualocke: aviso al morir.
// Cuando se debilita un Pokémon del jugador en un combate en el que cuentan las vidas, en
// vez de "X fainted!" sale "X has died!" con las vidas que quedarán al acabar el combate
// (los muertos se entierran y se restan las vidas en Dualocke_OnBattleEnd). Si ya no
// quedan vidas, o se han debilitado todos, avisa de que el locke está perdido.

static const u8 sText_DualockeDied[] = _(ES("{B_SCR_NAME_WITH_PREFIX} has died!\nLives left: {B_BUFF1}.\p",
                                             "¡{B_SCR_NAME_WITH_PREFIX} ha muerto!\nVidas restantes: {B_BUFF1}.\p"));
static const u8 sText_DualockeDiedLockeLost[] = _(ES("{B_SCR_NAME_WITH_PREFIX} has died!\nThe locke is lost!\p",
                                                     "¡{B_SCR_NAME_WITH_PREFIX} ha muerto!\n¡Has perdido el locke!\p"));

const u8 *Dualocke_GetFaintString(enum BattlerId battler)
{
    u32 i, dead = 0, alive = 0, lives;
    s32 left;

    // En los tests de la expansion se deja el texto original ("X fainted!"), que comprueban muchos
    if (TESTING || !IsDualockeBattle() || GetBattlerSide(battler) != B_SIDE_PLAYER)
        return NULL;
    // En los combates con compañero, sus Pokémon no son del jugador
    if ((gBattleTypeFlags & (BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER))
     && GetBattlerPosition(battler) == B_POSITION_PLAYER_RIGHT)
        return NULL;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];

        if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE || GetMonData(mon, MON_DATA_IS_EGG))
            continue;
        if (GetMonData(mon, MON_DATA_HP) == 0)
            dead++;
        else
            alive++;
    }

    // Perder el combate (todos debilitados) es perder el locke, y con 0 vidas, morir también
    lives = Dualocke_GetLives();
    left = (s32)lives - (s32)dead;
    if (alive == 0 || left < 0)
        return sText_DualockeDiedLockeLost;

    PREPARE_BYTE_NUMBER_BUFFER(gBattleTextBuff1, 2, left);
    return sText_DualockeDied;
}
