#include "global.h"
#include "item.h"
#include "script.h"
#include "event_data.h"
#include "malloc.h"
#include "shop_criteria.h"

static EWRAM_DATA const u16 *sDynamicShopItemListRef = NULL;

// Remove the UNUSED if you'll use the functions!
static bool32 ShopCriteriaByBadgeCount(u32 count);
static bool32 DualockeShopCriteria(enum Item item);
static UNUSED bool32 ShopCriteriaByFlag(u32 flagId);
static UNUSED bool32 ShopCriteriaByVar(u32 varId, u32 varValue);

void TryBuildDynamicShopItemList(const u16 **ogItemList, u16 *resultingTotal)
{
    sDynamicShopItemListRef = *ogItemList;

    u16 *list = AllocZeroed((*resultingTotal + 1) * sizeof(u16));
    u32 overallIdx = 0, idx = 0;

    while (idx < *resultingTotal)
    {
        enum Item item = sDynamicShopItemListRef[idx];

        if (IsItemShopCriteriaFulfilled(item) && DualockeShopCriteria(item))
        {
            list[overallIdx] = item;
            overallIdx++;
        }

        idx++;
    }

    list[overallIdx] = ITEM_NONE;

    *ogItemList = list;
    *resultingTotal = overallIdx;
}

void TryFreeDynamicShopItemList(const u16 **ogItemList)
{
    Free((u16 *)*ogItemList);
    *ogItemList = sDynamicShopItemListRef;
}

// Add new Criterias below!

// Dualocke: medallas necesarias para que un objeto aparezca en las tiendas.
// Vale para todas las tiendas normales; los objetos que no están en la tabla salen siempre.
static const struct
{
    u16 item;
    u8 badges;
} sDualockeShopBadges[] =
{
    {ITEM_GREAT_BALL,     1},
    {ITEM_SUPER_REPEL,    2},
    {ITEM_ULTRA_BALL,     5},
    {ITEM_MAX_REPEL,      5},
    // Piedras evolutivas: desde la 2.ª medalla
    {ITEM_FIRE_STONE,     2},
    {ITEM_WATER_STONE,    2},
    {ITEM_THUNDER_STONE,  2},
    {ITEM_LEAF_STONE,     2},
    {ITEM_MOON_STONE,     2},
    {ITEM_SUN_STONE,      2},
    {ITEM_SHINY_STONE,    2},
    {ITEM_DUSK_STONE,     2},
    {ITEM_DAWN_STONE,     2},
    {ITEM_ICE_STONE,      2},
    {ITEM_OVAL_STONE,     2},
    // Objetos de las antiguas evoluciones por intercambio y similares: desde la 4.ª medalla
    {ITEM_METAL_COAT,     4},
    {ITEM_KINGS_ROCK,     4},
    {ITEM_DRAGON_SCALE,   4},
    {ITEM_UPGRADE,        4},
    {ITEM_DUBIOUS_DISC,   4},
    {ITEM_PROTECTOR,      4},
    {ITEM_ELECTIRIZER,    4},
    {ITEM_MAGMARIZER,     4},
    {ITEM_REAPER_CLOTH,   4},
    {ITEM_DEEP_SEA_TOOTH, 4},
    {ITEM_DEEP_SEA_SCALE, 4},
    {ITEM_PRISM_SCALE,    4},
    {ITEM_SACHET,         4},
    {ITEM_WHIPPED_DREAM,  4},
    {ITEM_RAZOR_CLAW,     4},
    {ITEM_RAZOR_FANG,     4},
};

static bool32 DualockeShopCriteria(enum Item item)
{
    for (u32 i = 0; i < ARRAY_COUNT(sDualockeShopBadges); i++)
    {
        if (sDualockeShopBadges[i].item == item)
            return ShopCriteriaByBadgeCount(sDualockeShopBadges[i].badges);
    }
    return TRUE;
}

static bool32 ShopCriteriaByBadgeCount(u32 count)
{
    u32 badgeCount = 0;

    for (u32 badgeFlag = FLAG_BADGE01_GET; badgeFlag < FLAG_BADGE01_GET + NUM_BADGES; badgeFlag++)
    {
        if (FlagGet(badgeFlag))
            badgeCount++;
    }

    if (badgeCount >= count)
        return TRUE;

    return FALSE;
}

// These two below are somewhat identical to ShopCriteriaByBadgeCount
// but uses only one specific event var/flag check. Useful if you need
// a specific badge flag instead of just the badge total.

static UNUSED bool32 ShopCriteriaByFlag(u32 flagId)
{
    if (FlagGet(flagId))
        return TRUE;

    return FALSE;
}

static UNUSED bool32 ShopCriteriaByVar(u32 varId, u32 varValue)
{
    if (VarGet(varId) >= varValue)
        return TRUE;

    return FALSE;
}
