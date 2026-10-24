#include "global.h"
#include "dualocke_compras.h"
#include "event_data.h"
#include "constants/items.h"
#include "constants/maps.h"

// Dualocke (Items Clause): una unidad de cada objeto por tienda.
// - La tabla de parejas (tienda, objeto) limitadas la genera
//   tools/dualocke/compras_limitadas.py a partir de las listas de las tiendas.
// - Cada pareja es un bit de las variables VAR_DUALOCKE_COMPRAS_*, así que lo comprado
//   se guarda con la partida.
// - Lo que no está en la tabla (Balls, Repelentes, Bayas, Caramelos Raros, Cuerda Huida
//   y cualquier tienda que no sea de Hoenn) se puede comprar sin límite.

#include "data/dualocke_compras.h"

static const u16 sComprasVars[] =
{
    VAR_DUALOCKE_COMPRAS_0,
    VAR_DUALOCKE_COMPRAS_1,
    VAR_DUALOCKE_COMPRAS_2,
    VAR_DUALOCKE_COMPRAS_3,
    VAR_DUALOCKE_COMPRAS_4,
    VAR_DUALOCKE_COMPRAS_5,
};

STATIC_ASSERT(ARRAY_COUNT(sComprasLimitadas) <= ARRAY_COUNT(sComprasVars) * 16, DualockeComprasVarsTooSmall);

static s32 GetCompraIndex(enum Item item)
{
    u32 mapId = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sComprasLimitadas); i++)
    {
        if (sComprasLimitadas[i].mapId == mapId && sComprasLimitadas[i].item == item)
            return i;
    }
    return -1;
}

bool32 Dualocke_IsCompraLimitada(enum Item item)
{
    return GetCompraIndex(item) >= 0;
}

bool32 Dualocke_YaComprado(enum Item item)
{
    s32 index = GetCompraIndex(item);

    if (index < 0)
        return FALSE;
    return (VarGet(sComprasVars[index / 16]) >> (index % 16)) & 1;
}

void Dualocke_MarcarComprado(enum Item item)
{
    s32 index = GetCompraIndex(item);

    if (index < 0)
        return;
    VarSet(sComprasVars[index / 16], VarGet(sComprasVars[index / 16]) | (1 << (index % 16)));
}
