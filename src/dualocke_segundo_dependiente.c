#include "global.h"
#include "shop.h"
#include "tv.h"
#include "constants/items.h"
#include "constants/maps.h"

// Dualocke: segundo dependiente de las tiendas de ciudad.
// - Vende 4 objetos: 1 evolutivo y 3 equipables, elegidos al azar.
// - Son distintos en cada partida (la semilla sale del ID de entrenador) y no cambian
//   durante la partida, así que se pueden planificar.
// - Pasan por el mismo filtro que las tiendas normales (src/shop_criteria.c), así que los
//   evolutivos aparecen a partir de su medalla.
// - Lo abre el special Dualocke_AbrirSegundoDependiente desde
//   data/scripts/dualocke_segundo_dependiente.inc.

#define NUM_OBJETOS 4

static EWRAM_DATA u16 sLista[NUM_OBJETOS + 1] = {0};

// Tiendas de ciudad con segundo dependiente
static const u16 sTiendas[] =
{
    MAP_OLDALE_TOWN_MART,
    MAP_PETALBURG_CITY_MART,
    MAP_RUSTBORO_CITY_MART,
    MAP_SLATEPORT_CITY_MART,
    MAP_MAUVILLE_CITY_MART,
    MAP_VERDANTURF_TOWN_MART,
    MAP_FALLARBOR_TOWN_MART,
    MAP_LAVARIDGE_TOWN_MART,
    MAP_FORTREE_CITY_MART,
    MAP_MOSSDEEP_CITY_MART,
    MAP_SOOTOPOLIS_CITY_MART,
};

static const u16 sEvolutivos[] =
{
    ITEM_FIRE_STONE, ITEM_WATER_STONE, ITEM_THUNDER_STONE, ITEM_LEAF_STONE, ITEM_MOON_STONE,
    ITEM_SUN_STONE, ITEM_SHINY_STONE, ITEM_DUSK_STONE, ITEM_DAWN_STONE, ITEM_ICE_STONE,
    ITEM_OVAL_STONE, ITEM_METAL_COAT, ITEM_KINGS_ROCK, ITEM_DRAGON_SCALE, ITEM_UPGRADE,
    ITEM_DUBIOUS_DISC, ITEM_PROTECTOR, ITEM_ELECTIRIZER, ITEM_MAGMARIZER, ITEM_REAPER_CLOTH,
    ITEM_DEEP_SEA_TOOTH, ITEM_DEEP_SEA_SCALE, ITEM_PRISM_SCALE, ITEM_SACHET, ITEM_WHIPPED_DREAM,
    ITEM_RAZOR_CLAW, ITEM_RAZOR_FANG,
};

// Equipables clásicos que no se venden en ningún otro sitio
static const u16 sEquipables[] =
{
    ITEM_LEFTOVERS, ITEM_QUICK_CLAW, ITEM_SCOPE_LENS, ITEM_BRIGHT_POWDER, ITEM_SHELL_BELL,
    ITEM_FOCUS_BAND, ITEM_SOOTHE_BELL, ITEM_METRONOME, ITEM_SHED_SHELL,
    ITEM_CHARCOAL, ITEM_MYSTIC_WATER, ITEM_MIRACLE_SEED, ITEM_MAGNET, ITEM_NEVER_MELT_ICE,
    ITEM_BLACK_BELT, ITEM_POISON_BARB, ITEM_SOFT_SAND, ITEM_SHARP_BEAK, ITEM_TWISTED_SPOON,
    ITEM_SILVER_POWDER, ITEM_HARD_STONE, ITEM_SPELL_TAG, ITEM_DRAGON_FANG, ITEM_BLACK_GLASSES,
    ITEM_SILK_SCARF, ITEM_FAIRY_FEATHER,
};

static u32 Siguiente(u32 *estado)
{
    *estado = *estado * 1103515245 + 12345;
    return *estado >> 16;
}

static bool32 EstaEnLista(u32 count, u16 item)
{
    u32 i;

    for (i = 0; i < count; i++)
    {
        if (sLista[i] == item)
            return TRUE;
    }
    return FALSE;
}

static void GenerarLista(u32 tienda)
{
    u32 estado = GetPlayerIDAsU32() ^ ((tienda + 1) * 0x9E3779B9);
    u32 n = 0, i;

    for (i = 0; i < 4; i++)
        Siguiente(&estado);

    sLista[n++] = sEvolutivos[Siguiente(&estado) % ARRAY_COUNT(sEvolutivos)];
    while (n < NUM_OBJETOS)
    {
        u16 item = sEquipables[Siguiente(&estado) % ARRAY_COUNT(sEquipables)];
        if (!EstaEnLista(n, item))
            sLista[n++] = item;
    }
    sLista[n] = ITEM_NONE;
}

void Dualocke_AbrirSegundoDependiente(void)
{
    u32 mapId = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
    u32 tienda;

    for (tienda = 0; tienda < ARRAY_COUNT(sTiendas); tienda++)
    {
        if (sTiendas[tienda] == mapId)
            break;
    }
    GenerarLista(tienda);
    CreatePokemartMenu(sLista);
}
