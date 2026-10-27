#include "global.h"
#include "dualocke_aleatorio.h"
#include "event_data.h"
#include "move.h"
#include "pokemon.h"
#include "random.h"
#include "string_util.h"
#include "constants/flags.h"
#include "constants/abilities.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/trade.h"

// Dualocke: lo que el randomizer cambia al vuelo, sin tocar los mapas ni los scripts:
// estáticos, regalos, objetos del suelo, Recogida, objetos de los salvajes, intercambios,
// habilidades y MT.
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

const struct LevelUpMove *Dualocke_AprendizajeAleatorio(enum Species species)
{
    if (species >= NUM_SPECIES)
        return NULL;
    return sDualockeAprendizajes[species];
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

// Habilidad de la especie con el randomizer (una por especie), o ABILITY_NONE si no cambia
enum Ability Dualocke_HabilidadAleatoria(enum Species species)
{
    if (species >= NUM_SPECIES)
        return ABILITY_NONE;
    return sDualockeHabilidades[species];
}

// Movimiento que enseña una MT (el original si no cambia)
enum Move Dualocke_MovimientoMT(enum Item item, enum Move move)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sDualockeMT); i++)
    {
        if (sDualockeMT[i][0] == item && sDualockeMT[i][1] != MOVE_NONE)
            return sDualockeMT[i][1];
    }
    return move;
}

// La MT que enseña un movimiento (ITEM_NONE si con el randomizer ya no lo enseña ninguna)
enum Item Dualocke_ObjetoMT(enum Move move, enum Item item)
{
    u32 i;

    if (DUALOCKE_COMPATIBILIDAD_MT == 0)
        return item;
    for (i = 0; i < ARRAY_COUNT(sDualockeMT); i++)
    {
        if (sDualockeMT[i][1] == move)
            return sDualockeMT[i][0];
    }
    for (i = 0; i < ARRAY_COUNT(sDualockeMT); i++)
    {
        if (sDualockeMT[i][0] == item)
            return ITEM_NONE;
    }
    return item;
}

// ¿Puede aprender `species` el movimiento de una MT nueva (o de un tutor nuevo)? Siempre la misma respuesta para la misma
// especie, movimiento y semilla. -1 si el movimiento no es de una MT nueva (se mira la lista original).
s32 Dualocke_PuedeAprenderMT(enum Species species, enum Move move)
{
    u32 i, h;

    if (DUALOCKE_COMPATIBILIDAD_MT == 0 || move == MOVE_NONE)
        return -1;
    for (i = 0; i < ARRAY_COUNT(sDualockeMT) + ARRAY_COUNT(sDualockeTutores); i++)
    {
        u32 nuevo = (i < ARRAY_COUNT(sDualockeMT)) ? sDualockeMT[i][1] : sDualockeTutores[i - ARRAY_COUNT(sDualockeMT)][1];
        if (nuevo != move)
            continue;
        h = DUALOCKE_SEMILLA_NUMERICA ^ (species * 0x9E3779B1u) ^ (move * 0x85EBCA77u);
        h ^= h >> 15;
        h *= 0x2C1B3C6Du;
        h ^= h >> 12;
        return (h % 100) < DUALOCKE_COMPATIBILIDAD_MT;
    }
    return -1;
}

// Tutores (callnative en la macro move_tutor): cambia el movimiento de VAR_0x8005 por el de la
// semilla y guarda su nombre en STR_VAR_1 para los textos del tutor.
void Dualocke_TutorAleatorio(void)
{
    gSpecialVar_0x8005 = Buscar(sDualockeTutores, ARRAY_COUNT(sDualockeTutores), gSpecialVar_0x8005);
    StringCopy(gStringVar1, GetMoveName(gSpecialVar_0x8005));
}
