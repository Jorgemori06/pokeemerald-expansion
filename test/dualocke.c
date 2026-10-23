#include "global.h"
#include "battle.h"
#include "dualocke.h"
#include "event_data.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "test/test.h"

// Dualocke: tests del sistema de vidas y la caja de muertos.

static void SetupParty(u32 count)
{
    u32 i;

    ZeroPlayerPartyMons();
    for (i = 0; i < IN_BOX_COUNT; i++)
        ZeroBoxMonAt(DUALOCKE_DEAD_BOX, i);
    for (i = 0; i < count; i++)
    {
        CreateMon(&gParties[B_TRAINER_PLAYER][i], SPECIES_WOBBUFFET + i, 20, 0, OTID_STRUCT_PLAYER_ID);
        CalculateMonStats(&gParties[B_TRAINER_PLAYER][i]); // CreateMon no rellena los PS
    }
    CalculatePlayerPartyCount();
    gBattleTypeFlags = BATTLE_TYPE_TRAINER;
    VarSet(VAR_DUALOCKE_LIVES, DUALOCKE_START_LIVES);
    FlagClear(FLAG_DUALOCKE_LOCKE_LOST);
}

static void Faint(u32 partyIndex)
{
    u32 hp = 0;
    SetMonData(&gParties[B_TRAINER_PLAYER][partyIndex], MON_DATA_HP, &hp);
}

TEST("Dualocke: un Pokémon debilitado va a la caja de muertos y resta una vida")
{
    enum Species dead;

    SetupParty(3);
    dead = GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_SPECIES);
    Faint(1);

    Dualocke_OnBattleEnd(FALSE);

    EXPECT_EQ(Dualocke_GetLives(), DUALOCKE_START_LIVES - 1);
    EXPECT_EQ(CalculatePlayerPartyCount(), 2);
    EXPECT_EQ(GetBoxMonDataAt(DUALOCKE_DEAD_BOX, 0, MON_DATA_SPECIES), dead);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_SPECIES), SPECIES_WOBBUFFET + 2);
    EXPECT(!Dualocke_IsLockeLost());
}

TEST("Dualocke: varias muertes en un combate restan varias vidas")
{
    SetupParty(4);
    Faint(0);
    Faint(3);

    Dualocke_OnBattleEnd(FALSE);

    EXPECT_EQ(Dualocke_GetLives(), DUALOCKE_START_LIVES - 2);
    EXPECT_EQ(CalculatePlayerPartyCount(), 2);
    EXPECT_EQ(GetBoxMonDataAt(DUALOCKE_DEAD_BOX, 0, MON_DATA_SPECIES), SPECIES_WOBBUFFET);
    EXPECT_EQ(GetBoxMonDataAt(DUALOCKE_DEAD_BOX, 1, MON_DATA_SPECIES), SPECIES_WOBBUFFET + 3);
}

TEST("Dualocke: con 0 vidas se sigue jugando y la siguiente muerte pierde el locke")
{
    SetupParty(3);
    VarSet(VAR_DUALOCKE_LIVES, 0);
    Dualocke_OnBattleEnd(FALSE);
    EXPECT(!Dualocke_IsLockeLost());

    Faint(0);
    Dualocke_OnBattleEnd(FALSE);
    EXPECT_EQ(Dualocke_GetLives(), 0);
    EXPECT(Dualocke_IsLockeLost());
}

TEST("Dualocke: perder un combate pierde el locke sin vaciar el equipo")
{
    SetupParty(2);
    Faint(0);
    Faint(1);

    Dualocke_OnBattleEnd(TRUE);

    EXPECT(Dualocke_IsLockeLost());
    EXPECT_EQ(CalculatePlayerPartyCount(), 2);
    EXPECT_EQ(Dualocke_GetLives(), DUALOCKE_START_LIVES);
}

TEST("Dualocke: los combates de la Frontera no cuentan")
{
    SetupParty(3);
    Faint(0);
    gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_FRONTIER;

    Dualocke_OnBattleEnd(FALSE);

    EXPECT_EQ(Dualocke_GetLives(), DUALOCKE_START_LIVES);
    EXPECT_EQ(CalculatePlayerPartyCount(), 3);
}

TEST("Dualocke: los Pokémon nuevos no se envían a la caja de muertos")
{
    u32 box, pos;
    struct Pokemon mon;

    // Se llenan todas las cajas menos la de muertos
    for (box = 0; box < TOTAL_BOXES_COUNT; box++)
    {
        for (pos = 0; pos < IN_BOX_COUNT; pos++)
        {
            if (Dualocke_IsDeadBox(box))
                ZeroBoxMonAt(box, pos);
            else
            {
                CreateMon(&mon, SPECIES_WOBBUFFET, 5, 0, OTID_STRUCT_PLAYER_ID);
                SetBoxMonAt(box, pos, &mon.box);
            }
        }
    }
    CreateMon(&mon, SPECIES_WYNAUT, 5, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(CopyMonToPC(&mon), MON_CANT_GIVE);
    EXPECT_EQ(GetBoxMonDataAt(DUALOCKE_DEAD_BOX, 0, MON_DATA_SPECIES), SPECIES_NONE);
}
