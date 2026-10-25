#include "global.h"
#include "dualocke_aleatorio.h"
#include "random.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/species.h"
#include "constants/trade.h"

// Dualocke: lo que el randomizer cambia al vuelo, sin tocar los mapas ni los scripts:
// estáticos, regalos, objetos del suelo, Recogida, objetos de los salvajes e intercambios.
// Las tablas las genera tools/dualocke/randomizer.py según la semilla (sin semilla, están vacías
// y todo sale como en el original).

struct DualockeIntercambio
{
    u16 intercambio;
    u16 especie;
    u16 pide;
    u16 objeto;
    u8 ivs[NUM_STATS];
};

#include "data/dualocke_aleatorio.h"

static u32 Buscar(const u16 (*tabla)[2], u32 count, u32 original)
{
    u32 i;

    for (i = 0; i < count; i++)
    {
        if (tabla[i][0] == original && tabla[i][1] != 0)
            return tabla[i][1];
    }
    return original;
}

enum Species Dualocke_EstaticoAleatorio(enum Species species)
{
    return Buscar(sDualockeEstaticos, ARRAY_COUNT(sDualockeEstaticos), species);
}

enum Species Dualocke_RegaloAleatorio(enum Species species)
{
    return Buscar(sDualockeRegalos, ARRAY_COUNT(sDualockeRegalos), species);
}

enum Item Dualocke_ObjetoSuelo(u32 flag, enum Item item)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sDualockeSuelo); i++)
    {
        if (sDualockeSuelo[i][0] == flag && sDualockeSuelo[i][1] != ITEM_NONE)
            return sDualockeSuelo[i][1];
    }
    return item;
}

enum Item Dualocke_ObjetoRecogida(enum Item item)
{
    return Buscar(sDualockeRecogida, ARRAY_COUNT(sDualockeRecogida), item);
}

bool32 Dualocke_ObjetosSalvajesAleatorios(void)
{
    return DUALOCKE_PROBABILIDAD_OBJETO_SALVAJE > 0;
}

// Objeto al azar para un salvaje (o ninguno), con la probabilidad que decide Miguel. Con Ojo
// Compuesto y similares, el doble.
enum Item Dualocke_ObjetoSalvaje(bool32 masProbable)
{
    u32 probabilidad = DUALOCKE_PROBABILIDAD_OBJETO_SALVAJE * (masProbable ? 2 : 1);

    if (!Dualocke_ObjetosSalvajesAleatorios() || Random() % 100 >= probabilidad)
        return ITEM_NONE;
    return sDualockeObjetosSalvajes[Random() % ARRAY_COUNT(sDualockeObjetosSalvajes)];
}

bool32 Dualocke_IntercambioAleatorio(u32 intercambio, enum Species *especie, enum Species *pide, enum Item *objeto, u8 *ivs)
{
    u32 i, j;

    for (i = 0; i < ARRAY_COUNT(sDualockeIntercambios); i++)
    {
        if (sDualockeIntercambios[i].intercambio != intercambio)
            continue;
        *especie = sDualockeIntercambios[i].especie;
        *pide = sDualockeIntercambios[i].pide;
        *objeto = sDualockeIntercambios[i].objeto;
        for (j = 0; j < NUM_STATS; j++)
            ivs[j] = sDualockeIntercambios[i].ivs[j];
        return TRUE;
    }
    return FALSE;
}
