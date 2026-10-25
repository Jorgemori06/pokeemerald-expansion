#include "global.h"
#include "battle.h"
#include "dualocke.h"
#include "dualocke_aleatorio.h"
#include "event_data.h"
#include "item.h"
#include "global.fieldmap.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "test/test.h"
#include "constants/region_map_sections.h"
#include "constants/trade.h"

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

// Dualocke: tests de la primera captura por zona.

static void SetupCapture(void)
{
    u32 box, pos;

    ZeroPlayerPartyMons();
    for (box = 0; box < TOTAL_BOXES_COUNT; box++)
    {
        for (pos = 0; pos < IN_BOX_COUNT; pos++)
            ZeroBoxMonAt(box, pos);
    }
    for (pos = VAR_DUALOCKE_ZONES_0; pos <= VAR_DUALOCKE_ZONES_6; pos++)
        VarSet(pos, 0);
    FlagSet(FLAG_ADVENTURE_STARTED);
    gBattleTypeFlags = 0;
}

static void GiveMon(u32 partyIndex, enum Species species)
{
    CreateMon(&gParties[B_TRAINER_PLAYER][partyIndex], species, 20, 0, OTID_STRUCT_PLAYER_ID);
    CalculateMonStats(&gParties[B_TRAINER_PLAYER][partyIndex]);
    CalculatePlayerPartyCount();
}

static struct Pokemon *Wild(enum Species species, bool32 shiny)
{
    struct Pokemon *mon = &gParties[B_TRAINER_OPPONENT_A][0];

    CreateMon(mon, species, 5, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(mon, MON_DATA_IS_SHINY, &shiny);
    return mon;
}

TEST("Dualocke: el primer salvaje válido de una zona se puede capturar y la gasta")
{
    SetupCapture();
    GiveMon(0, SPECIES_TREECKO);

    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_ZIGZAGOON, FALSE), MAPSEC_ROUTE_101), DUALOCKE_ENCOUNTER_FIRST);

    Dualocke_UseZoneCapture(MAPSEC_ROUTE_101);
    EXPECT(Dualocke_IsZoneCaptureUsed(MAPSEC_ROUTE_101));
    EXPECT(!Dualocke_IsZoneCaptureUsed(MAPSEC_ROUTE_102));
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_WURMPLE, FALSE), MAPSEC_ROUTE_101), DUALOCKE_ENCOUNTER_ZONE_USED);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_WURMPLE, FALSE), MAPSEC_ROUTE_102), DUALOCKE_ENCOUNTER_FIRST);
}

TEST("Dualocke: las zonas propias de Esmeralda también se guardan")
{
    SetupCapture();
    Dualocke_UseZoneCapture(MAPSEC_ALTERING_CAVE);
    Dualocke_UseZoneCapture(MAPSEC_TRAINER_HILL);
    EXPECT(Dualocke_IsZoneCaptureUsed(MAPSEC_ALTERING_CAVE));
    EXPECT(Dualocke_IsZoneCaptureUsed(MAPSEC_TRAINER_HILL));
    EXPECT(!Dualocke_IsZoneCaptureUsed(MAPSEC_DESERT_UNDERPASS));
    EXPECT(!Dualocke_IsZoneCaptureUsed(MAPSEC_ROUTE_134));
}

TEST("Dualocke: un salvaje de una línea que ya tienes no cuenta")
{
    SetupCapture();
    GiveMon(0, SPECIES_PIKACHU);

    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_PICHU, FALSE), MAPSEC_ROUTE_110), DUALOCKE_ENCOUNTER_DUPE);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_RAICHU, FALSE), MAPSEC_ROUTE_110), DUALOCKE_ENCOUNTER_DUPE);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_RAICHU_ALOLA, FALSE), MAPSEC_ROUTE_110), DUALOCKE_ENCOUNTER_DUPE);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_PLUSLE, FALSE), MAPSEC_ROUTE_110), DUALOCKE_ENCOUNTER_FIRST);
}

TEST("Dualocke: con una rama elegida, las demás ramas de la línea sí cuentan")
{
    SetupCapture();
    GiveMon(0, SPECIES_GARDEVOIR);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_RALTS, FALSE), MAPSEC_ROUTE_102), DUALOCKE_ENCOUNTER_FIRST);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_KIRLIA, FALSE), MAPSEC_ROUTE_102), DUALOCKE_ENCOUNTER_FIRST);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_GALLADE, FALSE), MAPSEC_ROUTE_102), DUALOCKE_ENCOUNTER_FIRST);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_GARDEVOIR, FALSE), MAPSEC_ROUTE_102), DUALOCKE_ENCOUNTER_DUPE);

    // Con las dos ramas ocupadas, ya nada de la línea cuenta
    GiveMon(1, SPECIES_GALLADE);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_RALTS, FALSE), MAPSEC_ROUTE_102), DUALOCKE_ENCOUNTER_DUPE);

    SetupCapture();
    GiveMon(0, SPECIES_VAPOREON);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_EEVEE, FALSE), MAPSEC_ROUTE_102), DUALOCKE_ENCOUNTER_FIRST);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_SYLVEON, FALSE), MAPSEC_ROUTE_102), DUALOCKE_ENCOUNTER_FIRST);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_VAPOREON, FALSE), MAPSEC_ROUTE_102), DUALOCKE_ENCOUNTER_DUPE);
}

TEST("Dualocke: uno sin rama elegida ocupa toda la línea")
{
    SetupCapture();
    GiveMon(0, SPECIES_KIRLIA);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_RALTS, FALSE), MAPSEC_ROUTE_102), DUALOCKE_ENCOUNTER_DUPE);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_GALLADE, FALSE), MAPSEC_ROUTE_102), DUALOCKE_ENCOUNTER_DUPE);

    SetupCapture();
    GiveMon(0, SPECIES_VAPOREON);
    GiveMon(1, SPECIES_EEVEE);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_SYLVEON, FALSE), MAPSEC_ROUTE_102), DUALOCKE_ENCOUNTER_DUPE);

    // Las líneas sin ramas, como siempre
    SetupCapture();
    GiveMon(0, SPECIES_ZIGZAGOON);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_OBSTAGOON, FALSE), MAPSEC_ROUTE_101), DUALOCKE_ENCOUNTER_DUPE);
}

TEST("Dualocke: no se puede evolucionar a una rama que ya tienes viva")
{
    struct Pokemon *kirlia = &gParties[B_TRAINER_PLAYER][1];
    u32 hp = 0;

    SetupCapture();
    GiveMon(0, SPECIES_GARDEVOIR);
    CreateMaleMon(kirlia, SPECIES_KIRLIA, 40);
    CalculateMonStats(kirlia);
    CalculatePlayerPartyCount();

    // A Gardevoir no; a Gallade (Piedra Alba) sí
    EXPECT_EQ(GetEvolutionTargetSpecies(kirlia, EVO_MODE_NORMAL, ITEM_NONE, NULL, NULL, CHECK_EVO), SPECIES_NONE);
    EXPECT_EQ(GetEvolutionTargetSpecies(kirlia, EVO_MODE_ITEM_CHECK, ITEM_DAWN_STONE, NULL, NULL, CHECK_EVO), SPECIES_GALLADE);

    // Si el Gardevoir muere, la rama se libera
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HP, &hp);
    EXPECT_EQ(GetEvolutionTargetSpecies(kirlia, EVO_MODE_NORMAL, ITEM_NONE, NULL, NULL, CHECK_EVO), SPECIES_GARDEVOIR);
}

TEST("Dualocke: Eevee no evoluciona a la eeveelución que ya tienes")
{
    struct Pokemon *eevee = &gParties[B_TRAINER_PLAYER][1];

    SetupCapture();
    GiveMon(0, SPECIES_VAPOREON);
    GiveMon(1, SPECIES_EEVEE);
    EXPECT_EQ(GetEvolutionTargetSpecies(eevee, EVO_MODE_ITEM_CHECK, ITEM_WATER_STONE, NULL, NULL, CHECK_EVO), SPECIES_NONE);
    EXPECT_EQ(GetEvolutionTargetSpecies(eevee, EVO_MODE_ITEM_CHECK, ITEM_FIRE_STONE, NULL, NULL, CHECK_EVO), SPECIES_FLAREON);
}

TEST("Dualocke: los de la caja de muertos no cuentan como línea que ya tienes")
{
    struct Pokemon mon;

    SetupCapture();
    GiveMon(0, SPECIES_TREECKO);
    CreateMon(&mon, SPECIES_PIKACHU, 20, 0, OTID_STRUCT_PLAYER_ID);
    SetBoxMonAt(DUALOCKE_DEAD_BOX, 0, &mon.box);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_PIKACHU, FALSE), MAPSEC_ROUTE_110), DUALOCKE_ENCOUNTER_FIRST);

    // En cualquier otra caja sí
    SetBoxMonAt(0, 0, &mon.box);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_PIKACHU, FALSE), MAPSEC_ROUTE_110), DUALOCKE_ENCOUNTER_DUPE);
}

TEST("Dualocke: los legendarios no cuentan")
{
    SetupCapture();
    GiveMon(0, SPECIES_TREECKO);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_LATIAS, FALSE), MAPSEC_ROUTE_101), DUALOCKE_ENCOUNTER_LEGENDARY);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_JIRACHI, FALSE), MAPSEC_ROUTE_101), DUALOCKE_ENCOUNTER_LEGENDARY);
    // Ultraentes y paradójicos son Pokémon normales
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_NIHILEGO, FALSE), MAPSEC_ROUTE_101), DUALOCKE_ENCOUNTER_FIRST);
}

TEST("Dualocke: los shiny se pueden capturar siempre y no gastan la zona")
{
    SetupCapture();
    GiveMon(0, SPECIES_PIKACHU);
    Dualocke_UseZoneCapture(MAPSEC_ROUTE_102);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_PIKACHU, TRUE), MAPSEC_ROUTE_102), DUALOCKE_ENCOUNTER_SHINY);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_LATIAS, TRUE), MAPSEC_ROUTE_101), DUALOCKE_ENCOUNTER_SHINY);

    Dualocke_SetRandomEncounter();
    Wild(SPECIES_ZIGZAGOON, TRUE);
    gMapHeader.regionMapSectionId = MAPSEC_ROUTE_101;
    Dualocke_OnBattleStart();
    EXPECT(Dualocke_CanCatchCurrentEncounter());
    EXPECT(!Dualocke_IsZoneCaptureUsed(MAPSEC_ROUTE_101));
}

TEST("Dualocke: antes de recibir las Poké Balls no cuenta nada")
{
    SetupCapture();
    FlagClear(FLAG_ADVENTURE_STARTED);
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_ZIGZAGOON, FALSE), MAPSEC_ROUTE_101), DUALOCKE_ENCOUNTER_NO_RULE);
}

TEST("Dualocke: el combate aleatorio gasta la zona al empezar y bloquea los siguientes")
{
    SetupCapture();
    GiveMon(0, SPECIES_TREECKO);
    gMapHeader.regionMapSectionId = MAPSEC_ROUTE_101;

    Dualocke_SetRandomEncounter();
    Wild(SPECIES_ZIGZAGOON, FALSE);
    Dualocke_OnBattleStart();
    EXPECT_EQ(Dualocke_GetCurrentEncounter(), DUALOCKE_ENCOUNTER_FIRST);
    EXPECT(Dualocke_CanCatchCurrentEncounter());
    EXPECT(Dualocke_IsZoneCaptureUsed(MAPSEC_ROUTE_101));

    Dualocke_SetRandomEncounter();
    Wild(SPECIES_WURMPLE, FALSE);
    Dualocke_OnBattleStart();
    EXPECT_EQ(Dualocke_GetCurrentEncounter(), DUALOCKE_ENCOUNTER_ZONE_USED);
    EXPECT(!Dualocke_CanCatchCurrentEncounter());
}

TEST("Dualocke: un repetido no gasta la zona")
{
    SetupCapture();
    GiveMon(0, SPECIES_ZIGZAGOON);
    gMapHeader.regionMapSectionId = MAPSEC_ROUTE_101;

    Dualocke_SetRandomEncounter();
    Wild(SPECIES_LINOONE, FALSE);
    Dualocke_OnBattleStart();
    EXPECT_EQ(Dualocke_GetCurrentEncounter(), DUALOCKE_ENCOUNTER_DUPE);
    EXPECT(!Dualocke_CanCatchCurrentEncounter());
    EXPECT(!Dualocke_IsZoneCaptureUsed(MAPSEC_ROUTE_101));
}

TEST("Dualocke: los combates de evento no gastan la zona y se pueden capturar")
{
    SetupCapture();
    GiveMon(0, SPECIES_TREECKO);
    gMapHeader.regionMapSectionId = MAPSEC_ROUTE_120;
    Dualocke_UseZoneCapture(MAPSEC_ROUTE_120);

    // Sin Dualocke_SetRandomEncounter: es un estático (el Kecleon, por ejemplo)
    Wild(SPECIES_KECLEON, FALSE);
    Dualocke_OnBattleStart();
    EXPECT_EQ(Dualocke_GetCurrentEncounter(), DUALOCKE_ENCOUNTER_NO_RULE);
    EXPECT(Dualocke_CanCatchCurrentEncounter());
}

// Dualocke: tests de la caja de prohibidos.

static u32 Gift(enum Species species, bool32 shiny)
{
    struct Pokemon mon;

    CreateMon(&mon, species, 10, 0, OTID_STRUCT_PLAYER_ID);
    CalculateMonStats(&mon); // CreateMon no rellena los PS, y uno con 0 PS cuenta como muerto
    SetMonData(&mon, MON_DATA_IS_SHINY, &shiny);
    return GiveScriptedMonToPlayer(&mon, PARTY_SIZE);
}

TEST("Dualocke: un regalo repetido va a la caja de prohibidos")
{
    SetupCapture();
    GiveMon(0, SPECIES_TREECKO);

    EXPECT_EQ(Gift(SPECIES_BELDUM, FALSE), MON_GIVEN_TO_PARTY);
    EXPECT_EQ(CalculatePlayerPartyCount(), 2);

    EXPECT_EQ(Gift(SPECIES_METANG, FALSE), MON_GIVEN_TO_PC);
    EXPECT_EQ(CalculatePlayerPartyCount(), 2);
    EXPECT_EQ(GetBoxMonDataAt(DUALOCKE_BANNED_BOX, 0, MON_DATA_SPECIES), SPECIES_METANG);
    EXPECT_EQ(gSpecialVar_MonBoxId, DUALOCKE_BANNED_BOX);
    EXPECT(Dualocke_IsBoxMonLocked(DUALOCKE_BANNED_BOX, 0));
}

TEST("Dualocke: un regalo legendario va a la caja de prohibidos y no se desbloquea")
{
    SetupCapture();
    GiveMon(0, SPECIES_TREECKO);

    EXPECT_EQ(Gift(SPECIES_LATIOS, FALSE), MON_GIVEN_TO_PC);
    EXPECT_EQ(GetBoxMonDataAt(DUALOCKE_BANNED_BOX, 0, MON_DATA_SPECIES), SPECIES_LATIOS);
    EXPECT(Dualocke_IsBoxMonLocked(DUALOCKE_BANNED_BOX, 0));
}

TEST("Dualocke: los regalos variocolor nunca van a la caja de prohibidos")
{
    SetupCapture();
    GiveMon(0, SPECIES_BELDUM);
    EXPECT_EQ(Gift(SPECIES_BELDUM, TRUE), MON_GIVEN_TO_PARTY);
    EXPECT_EQ(Gift(SPECIES_LATIAS, TRUE), MON_GIVEN_TO_PARTY);
    EXPECT_EQ(CalculatePlayerPartyCount(), 3);
}

TEST("Dualocke: un repetido de la caja de prohibidos se desbloquea al morir el de su línea")
{
    u32 hp = 0;

    SetupCapture();
    GiveMon(0, SPECIES_TREECKO);
    GiveMon(1, SPECIES_BELDUM);
    Gift(SPECIES_BELDUM, FALSE);
    EXPECT(Dualocke_IsBoxMonLocked(DUALOCKE_BANNED_BOX, 0));

    SetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_HP, &hp);
    EXPECT(!Dualocke_IsBoxMonLocked(DUALOCKE_BANNED_BOX, 0));
}

TEST("Dualocke: los de la caja de prohibidos no cuentan como línea que ya tienes")
{
    SetupCapture();
    GiveMon(0, SPECIES_TREECKO);
    GiveMon(1, SPECIES_BELDUM);
    Gift(SPECIES_BELDUM, FALSE);
    Gift(SPECIES_BELDUM, FALSE);

    // Los dos Beldum de la caja no se bloquean entre ellos, solo por el del equipo
    EXPECT(Dualocke_IsBoxMonLocked(DUALOCKE_BANNED_BOX, 0));
    EXPECT(Dualocke_IsBoxMonLocked(DUALOCKE_BANNED_BOX, 1));
    ZeroMonData(&gParties[B_TRAINER_PLAYER][1]);
    CalculatePlayerPartyCount();
    EXPECT(!Dualocke_IsBoxMonLocked(DUALOCKE_BANNED_BOX, 0));
    EXPECT(!Dualocke_IsBoxMonLocked(DUALOCKE_BANNED_BOX, 1));

    // Y un salvaje de esa línea sí cuenta
    EXPECT_EQ(Dualocke_GetWildEncounterStatus(Wild(SPECIES_BELDUM, FALSE), MAPSEC_ROUTE_101), DUALOCKE_ENCOUNTER_FIRST);
}

TEST("Dualocke: un estático legendario capturado va a la caja de prohibidos")
{
    struct Pokemon mon;
    bool32 shiny = FALSE;

    SetupCapture();
    GiveMon(0, SPECIES_TREECKO);
    CreateMon(&mon, SPECIES_REGIROCK, 40, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_IS_SHINY, &shiny); // con personalidad 0 e ID 0 saldría variocolor
    EXPECT_EQ(GiveCapturedMonToPlayer(&mon), MON_GIVEN_TO_PC);
    EXPECT_EQ(GetBoxMonDataAt(DUALOCKE_BANNED_BOX, 0, MON_DATA_SPECIES), SPECIES_REGIROCK);
    EXPECT_EQ(CalculatePlayerPartyCount(), 1);
}

TEST("Dualocke: el PC nunca manda Pokémon nuevos a la caja de prohibidos")
{
    u32 box, pos;
    struct Pokemon mon;

    SetupCapture();
    for (box = 0; box < TOTAL_BOXES_COUNT; box++)
    {
        if (Dualocke_IsLockedBox(box))
            continue;
        for (pos = 0; pos < IN_BOX_COUNT; pos++)
        {
            CreateMon(&mon, SPECIES_WOBBUFFET, 5, 0, OTID_STRUCT_PLAYER_ID);
            SetBoxMonAt(box, pos, &mon.box);
        }
    }
    CreateMon(&mon, SPECIES_WYNAUT, 5, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(CopyMonToPC(&mon), MON_CANT_GIVE);
    EXPECT_EQ(GetBoxMonDataAt(DUALOCKE_BANNED_BOX, 0, MON_DATA_SPECIES), SPECIES_NONE);
}

TEST("Dualocke: antes de recibir las Poké Balls no se prohíbe nada")
{
    SetupCapture();
    FlagClear(FLAG_ADVENTURE_STARTED);
    GiveMon(0, SPECIES_BELDUM);
    EXPECT_EQ(Gift(SPECIES_BELDUM, FALSE), MON_GIVEN_TO_PARTY);
}

// make check nunca randomiza: las tablas del randomizer están vacías y todo sale como el original
TEST("Dualocke: sin semilla, el randomizer no cambia nada")
{
    enum Species especie = SPECIES_NONE, pide = SPECIES_NONE;
    enum Item objeto = ITEM_NONE;
    u8 ivs[NUM_STATS] = {0};

    EXPECT_EQ(Dualocke_EstaticoAleatorio(SPECIES_KECLEON), SPECIES_KECLEON);
    EXPECT_EQ(Dualocke_RegaloAleatorio(SPECIES_BELDUM), SPECIES_BELDUM);
    EXPECT_EQ(Dualocke_ObjetoSuelo(FLAG_ITEM_ROUTE_102_POTION, ITEM_POTION), ITEM_POTION);
    EXPECT_EQ(Dualocke_ObjetoSuelo(FLAG_HIDDEN_ITEM_ROUTE_104_SUPER_POTION, ITEM_SUPER_POTION), ITEM_SUPER_POTION);
    EXPECT_EQ(Dualocke_ObjetoRecogida(ITEM_POTION), ITEM_POTION);
    EXPECT(!Dualocke_ObjetosSalvajesAleatorios());
    EXPECT_EQ(Dualocke_ObjetoSalvaje(TRUE), ITEM_NONE);
    EXPECT(!Dualocke_IntercambioAleatorio(INGAME_TRADE_SEEDOT, &especie, &pide, &objeto, ivs));
    EXPECT_EQ(Dualocke_HabilidadAleatoria(SPECIES_ZIGZAGOON), ABILITY_NONE);
    EXPECT_EQ(GetSpeciesAbility(SPECIES_ZIGZAGOON, 0), ABILITY_PICKUP);
    EXPECT_EQ(GetItemTMHMMoveId(ITEM_TM_EARTHQUAKE), MOVE_EARTHQUAKE);
    EXPECT_EQ(GetTMHMItemIdFromMoveId(MOVE_EARTHQUAKE), ITEM_TM_EARTHQUAKE);
    EXPECT_EQ(Dualocke_PuedeAprenderMT(SPECIES_ZIGZAGOON, MOVE_EARTHQUAKE), -1);
    gSpecialVar_0x8005 = MOVE_SWAGGER;
    Dualocke_TutorAleatorio();
    EXPECT_EQ(gSpecialVar_0x8005, MOVE_SWAGGER);
}
