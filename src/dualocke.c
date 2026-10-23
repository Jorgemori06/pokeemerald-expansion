#include "global.h"
#include "battle.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "dualocke.h"
#include "event_data.h"
#include "global.fieldmap.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "string_util.h"
#include "trainer_hill.h"
#include "constants/battle.h"
#include "constants/region_map_sections.h"

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

static bool32 IsDualockeBattle(void)
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

// ---------------------------------------------------------------------------
// Dualocke: primera captura por zona (Capture Clause).
// - Cada zona con nombre propio (sección del mapa regional) da una captura: la del
//   primer Pokémon salvaje válido. Al empezar ese combate la zona queda gastada,
//   pase lo que pase (capturarlo, huir, debilitarlo o perder).
// - Si el primero es de una línea evolutiva que ya tienes viva, o es legendario o
//   singular, no cuenta: no se puede capturar y la zona sigue libre.
// - Los shiny se pueden capturar siempre y no gastan la zona.
// - Solo cuenta en los encuentros aleatorios (hierba, cuevas, surf, pesca, Golpe
//   Roca, Dulce Aroma, Safari, errantes). Los combates de evento y los estáticos
//   no gastan la zona.
// - Hasta que te dan las primeras Poké Balls (FLAG_ADVENTURE_STARTED) no cuenta nada.
// ---------------------------------------------------------------------------

static EWRAM_DATA bool8 sRandomEncounterPending = FALSE;
static EWRAM_DATA u8 sCurrentEncounter = DUALOCKE_ENCOUNTER_NO_RULE;

static const u16 sZoneVars[] =
{
    VAR_DUALOCKE_ZONES_0,
    VAR_DUALOCKE_ZONES_1,
    VAR_DUALOCKE_ZONES_2,
    VAR_DUALOCKE_ZONES_3,
    VAR_DUALOCKE_ZONES_4,
    VAR_DUALOCKE_ZONES_5,
    VAR_DUALOCKE_ZONES_6,
};

// Zonas de Hoenn: las secciones anteriores a Kanto y las propias de Esmeralda
// (de la Guarida Aqua a la Cima Entrenador), que van después de las de Kanto.
#define HOENN_EXTRA_MAPSEC_FIRST MAPSEC_AQUA_HIDEOUT
#define HOENN_EXTRA_MAPSEC_LAST  MAPSEC_TRAINER_HILL
#define NUM_DUALOCKE_ZONES (KANTO_MAPSEC_START + HOENN_EXTRA_MAPSEC_LAST - HOENN_EXTRA_MAPSEC_FIRST + 1)

STATIC_ASSERT(NUM_DUALOCKE_ZONES <= ARRAY_COUNT(sZoneVars) * 16, DualockeZoneVarsTooSmall);

static s32 GetZoneIndex(u32 mapsec)
{
    if (mapsec < KANTO_MAPSEC_START)
        return mapsec;
    if (mapsec >= HOENN_EXTRA_MAPSEC_FIRST && mapsec <= HOENN_EXTRA_MAPSEC_LAST)
        return KANTO_MAPSEC_START + (mapsec - HOENN_EXTRA_MAPSEC_FIRST);
    return -1;
}

bool32 Dualocke_IsZoneCaptureUsed(u32 mapsec)
{
    s32 zone = GetZoneIndex(mapsec);

    if (zone < 0)
        return FALSE;
    return (VarGet(sZoneVars[zone / 16]) >> (zone % 16)) & 1;
}

void Dualocke_UseZoneCapture(u32 mapsec)
{
    s32 zone = GetZoneIndex(mapsec);

    if (zone < 0)
        return;
    VarSet(sZoneVars[zone / 16], VarGet(sZoneVars[zone / 16]) | (1 << (zone % 16)));
}

bool32 Dualocke_IsSpeciesLegendary(enum Species species)
{
    const struct SpeciesInfo *info = &gSpeciesInfo[GET_BASE_SPECIES_ID(SanitizeSpeciesId(species))];
    return info->isRestrictedLegendary || info->isSubLegendary || info->isMythical;
}

// Ramas: las evoluciones finales a las que puede llegar una especie. Las formas
// regionales y las megas cuentan como su especie base (Raichu de Alola es la rama
// Raichu de la línea de Pikachu).
// - Un Pokémon con una sola rama posible (Gardevoir, Silcoon, Pikachu…) ocupa esa rama.
// - Uno con varias (Ralts, Kirlia, Eevee…) todavía no ha elegido y ocupa toda la línea.
// Dos especies son de la misma línea si comparten alguna rama.
#define MAX_EVO_NODES 32
#define MAX_BRANCHES  16

static bool32 IsInList(const u16 *list, u32 count, u32 species)
{
    u32 i;

    for (i = 0; i < count; i++)
    {
        if (list[i] == species)
            return TRUE;
    }
    return FALSE;
}

static bool32 ListsIntersect(const u16 *a, u32 countA, const u16 *b, u32 countB)
{
    u32 i;

    for (i = 0; i < countA; i++)
    {
        if (IsInList(b, countB, a[i]))
            return TRUE;
    }
    return FALSE;
}

static u32 GetSpeciesBranches(enum Species species, u16 *branches)
{
    u16 nodes[MAX_EVO_NODES];
    u32 head = 0, nodeCount = 0, branchCount = 0;
    u32 j, k;

    species = GET_BASE_SPECIES_ID(SanitizeSpeciesId(species));
    if (species == SPECIES_NONE)
        return 0;
    nodes[nodeCount++] = species;

    while (head < nodeCount)
    {
        u32 current = nodes[head++];
        const u16 *forms = GetSpeciesFormTable(current);
        u16 single[2] = {current, FORM_SPECIES_END};
        bool32 evolves = FALSE;

        if (forms == NULL || forms[0] == FORM_SPECIES_END)
            forms = single;

        for (j = 0; forms[j] != FORM_SPECIES_END; j++)
        {
            const struct Evolution *evolutions = GetSpeciesEvolutions(forms[j]);

            if (evolutions == NULL)
                continue;
            for (k = 0; evolutions[k].method != EVOLUTIONS_END; k++)
            {
                u32 target = GET_BASE_SPECIES_ID(SanitizeSpeciesId(evolutions[k].targetSpecies));

                if (target == SPECIES_NONE || target == current)
                    continue;
                evolves = TRUE;
                if (!IsInList(nodes, nodeCount, target) && nodeCount < MAX_EVO_NODES)
                    nodes[nodeCount++] = target;
            }
        }

        if (!evolves && branchCount < MAX_BRANCHES)
            branches[branchCount++] = current;
    }
    return branchCount;
}

// Recorre los Pokémon vivos del jugador (equipo con PS y PC sin la caja de muertos),
// sin contar `exclude`, que comparten alguna rama con `branches`. Marca en `occupied`
// las ramas que ya tienen dueño. Devuelve TRUE si alguno no ha elegido rama todavía.
static bool32 GetOccupiedBranches(const u16 *branches, u32 branchCount, struct BoxPokemon *exclude, bool8 *occupied)
{
    u16 monBranches[MAX_BRANCHES];
    bool32 anyUndecided = FALSE;
    u32 i, j, box, monBranchCount;

    for (i = 0; i < PARTY_SIZE + TOTAL_BOXES_COUNT * IN_BOX_COUNT; i++)
    {
        struct BoxPokemon *boxMon;
        enum Species species;

        if (i < PARTY_SIZE)
        {
            if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_HP) == 0)
                continue;
            boxMon = &gParties[B_TRAINER_PLAYER][i].box;
        }
        else
        {
            box = (i - PARTY_SIZE) / IN_BOX_COUNT;
            if (Dualocke_IsDeadBox(box))
                continue;
            boxMon = GetBoxedMonPtr(box, (i - PARTY_SIZE) % IN_BOX_COUNT);
        }
        if (boxMon == exclude)
            continue;

        species = GetBoxMonData(boxMon, MON_DATA_SPECIES_OR_EGG);
        if (species == SPECIES_NONE || species == SPECIES_EGG)
            continue;

        monBranchCount = GetSpeciesBranches(species, monBranches);
        if (!ListsIntersect(monBranches, monBranchCount, branches, branchCount))
            continue;
        if (monBranchCount > 1)
        {
            anyUndecided = TRUE;
            continue;
        }
        for (j = 0; j < branchCount; j++)
        {
            if (branches[j] == monBranches[0])
                occupied[j] = TRUE;
        }
    }
    return anyUndecided;
}

static bool32 AreAllBranchesOccupied(const bool8 *occupied, u32 branchCount)
{
    u32 i;

    for (i = 0; i < branchCount; i++)
    {
        if (!occupied[i])
            return FALSE;
    }
    return branchCount > 0;
}

// Repetido: tienes vivo uno de la línea que todavía no ha elegido rama, o todas las
// ramas a las que puede llegar esta especie ya las tienes.
bool32 Dualocke_IsDupe(enum Species species)
{
    u16 branches[MAX_BRANCHES];
    bool8 occupied[MAX_BRANCHES] = {0};
    u32 count = GetSpeciesBranches(species, branches);

    if (GetOccupiedBranches(branches, count, NULL, occupied))
        return TRUE;
    return AreAllBranchesOccupied(occupied, count);
}

// Un Pokémon del equipo no puede evolucionar a una especie cuyas ramas ya tienes
// todas, con otros Pokémon vivos que ya las eligieron (si tienes Gardevoir, tu Kirlia
// no evoluciona a Gardevoir, pero sí a Gallade). Si el que tenías muere, se libera.
bool32 Dualocke_IsEvolutionBlocked(struct Pokemon *mon, enum Species targetSpecies)
{
    u16 branches[MAX_BRANCHES];
    bool8 occupied[MAX_BRANCHES] = {0};
    u32 count;

    if (mon < &gParties[B_TRAINER_PLAYER][0] || mon >= &gParties[B_TRAINER_PLAYER][PARTY_SIZE])
        return FALSE;

    count = GetSpeciesBranches(targetSpecies, branches);
    GetOccupiedBranches(branches, count, &mon->box, occupied);
    return AreAllBranchesOccupied(occupied, count);
}

enum DualockeEncounter Dualocke_GetWildEncounterStatus(struct Pokemon *wildMon, u32 mapsec)
{
    enum Species species = GetMonData(wildMon, MON_DATA_SPECIES);

    if (!FlagGet(FLAG_ADVENTURE_STARTED) || GetZoneIndex(mapsec) < 0 || species == SPECIES_NONE)
        return DUALOCKE_ENCOUNTER_NO_RULE;
    if (IsMonShiny(wildMon))
        return DUALOCKE_ENCOUNTER_SHINY;
    if (Dualocke_IsZoneCaptureUsed(mapsec))
        return DUALOCKE_ENCOUNTER_ZONE_USED;
    if (Dualocke_IsSpeciesLegendary(species))
        return DUALOCKE_ENCOUNTER_LEGENDARY;
    if (Dualocke_IsDupe(species))
        return DUALOCKE_ENCOUNTER_DUPE;
    return DUALOCKE_ENCOUNTER_FIRST;
}

// Lo llaman los combates salvajes aleatorios justo antes de empezar.
void Dualocke_SetRandomEncounter(void)
{
    sRandomEncounterPending = TRUE;
}

// Se llama al empezar cualquier combate, con el Pokémon salvaje ya creado.
void Dualocke_OnBattleStart(void)
{
    sCurrentEncounter = DUALOCKE_ENCOUNTER_NO_RULE;
    if (sRandomEncounterPending && !(gBattleTypeFlags & (BATTLE_TYPE_TRAINER | BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED)))
    {
        sCurrentEncounter = Dualocke_GetWildEncounterStatus(&gParties[B_TRAINER_OPPONENT_A][0], gMapHeader.regionMapSectionId);
        if (sCurrentEncounter == DUALOCKE_ENCOUNTER_FIRST)
            Dualocke_UseZoneCapture(gMapHeader.regionMapSectionId);
    }
    sRandomEncounterPending = FALSE;
}

enum DualockeEncounter Dualocke_GetCurrentEncounter(void)
{
    return sCurrentEncounter;
}

bool32 Dualocke_CanCatchCurrentEncounter(void)
{
    switch (sCurrentEncounter)
    {
    case DUALOCKE_ENCOUNTER_DUPE:
    case DUALOCKE_ENCOUNTER_LEGENDARY:
    case DUALOCKE_ENCOUNTER_ZONE_USED:
        return FALSE;
    default:
        return TRUE;
    }
}
