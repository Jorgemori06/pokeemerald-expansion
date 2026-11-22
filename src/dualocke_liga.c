#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "dualocke_liga.h"
#include "item.h"
#include "constants/battle.h"
#include "constants/items.h"
#include "constants/opponents.h"

// Dualocke: regla de la Liga (contada por Jorge; Miguel la mete en el juego, 22/11/2026).
// - En la Liga se venden RESTAURAR TODO sin límite (tienda de EverGrandeCity_PokemonLeague_1F; la
//   excepción a "una compra por objeto" está en tools/dualocke/compras_limitadas.py).
// - En los combates del Alto Mando y del Campeón, el jugador solo puede usar un curativo si el rival ya
//   ha usado uno, y como mucho tantos como él (CannotUseItemsInBattle, src/item_use.c). Se cuentan al
//   usarse (HandleAction_UseItem, src/battle_util.c).
// - Al entrar en cada sala se cura el equipo entero (Dualocke_EventScript_CuraLiga,
//   data/scripts/dualocke_liga.inc).

static EWRAM_DATA u8 sCurativosRival = 0;
static EWRAM_DATA u8 sCurativosJugador = 0;

// Se llama al empezar cualquier combate (Dualocke_OnBattleStart).
void Dualocke_LigaEmpiezaCombate(void)
{
    sCurativosRival = 0;
    sCurativosJugador = 0;
}

// Combate contra el Alto Mando o el Campeón.
bool32 Dualocke_EsCombateLiga(void)
{
    if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER)
     || (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED | BATTLE_TYPE_FRONTIER
                           | BATTLE_TYPE_TRAINER_HILL | BATTLE_TYPE_EREADER_TRAINER)))
        return FALSE;

    switch (TRAINER_BATTLE_PARAM.opponentA)
    {
    case TRAINER_SIDNEY:
    case TRAINER_PHOEBE:
    case TRAINER_GLACIA:
    case TRAINER_DRAKE:
    case TRAINER_WALLACE:
        return TRUE;
    default:
        return FALSE;
    }
}

// Objetos que curan en combate: PS, estados, PP (y revivir, aunque el locke no lo deja usar).
bool32 Dualocke_EsCurativo(enum Item item)
{
    switch (GetItemBattleUsage(item))
    {
    case EFFECT_ITEM_RESTORE_HP:
    case EFFECT_ITEM_CURE_STATUS:
    case EFFECT_ITEM_HEAL_AND_CURE_STATUS:
    case EFFECT_ITEM_REVIVE:
    case EFFECT_ITEM_RESTORE_PP:
    case EFFECT_ITEM_USE_POKE_FLUTE:
        return TRUE;
    default:
        return FALSE;
    }
}

// El jugador puede curar si ha usado menos curativos que el rival en este combate.
bool32 Dualocke_LigaPuedeCurar(void)
{
    return sCurativosJugador < sCurativosRival;
}

// Se llama cada vez que alguien usa un objeto de la mochila en combate.
void Dualocke_LigaObjetoUsado(enum BattlerId battler, enum Item item)
{
    if (!Dualocke_EsCombateLiga() || !Dualocke_EsCurativo(item))
        return;

    if (IsOnPlayerSide(battler))
    {
        if (sCurativosJugador < 0xFF)
            sCurativosJugador++;
    }
    else if (sCurativosRival < 0xFF)
    {
        sCurativosRival++;
    }
}
