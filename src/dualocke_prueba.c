#include "global.h"
#include "dualocke_prueba.h"

#ifdef DUALOCKE_PRUEBA
#include "dualocke.h"
#include "event_data.h"
#include "constants/characters.h"
#include "item.h"
#include "overworld.h"
#include "pokemon.h"
#include "script_pokemon_util.h"
#include "string_util.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/species.h"

// El emulador la rellena en la pantalla de título (después de que el arranque borre la RAM); la busca en el .map
struct DualockePrueba gDualockePrueba = {0};

bool32 Dualocke_PruebaActiva(void)
{
    return gDualockePrueba.magia == DUALOCKE_PRUEBA_MAGIA;
}

bool32 Dualocke_PruebaFoto(void)
{
    return Dualocke_PruebaActiva() && gDualockePrueba.foto;
}

void Dualocke_PruebaNombre(void)
{
    // Un nombre de más de 7 letras, para probar el nombre largo (como si se escribiera en la pantalla de nombres)
    static const u8 sNombre[] = _("JORGEMORI");
    memset(gSaveBlock2Ptr->playerNameLong, EOS, sizeof(gSaveBlock2Ptr->playerNameLong));
    StringCopy(gSaveBlock2Ptr->playerNameLong, sNombre);
    Dualocke_GuardarNombreJugador();
    gSaveBlock2Ptr->playerGender = MALE;
}

bool32 Dualocke_PruebaDestino(void)
{
    if (!Dualocke_PruebaActiva())
        return FALSE;
    SetWarpDestination(gDualockePrueba.mapa >> 8, gDualockePrueba.mapa & 0xFF, WARP_ID_NONE,
                       gDualockePrueba.x, gDualockePrueba.y);
    WarpIntoMap();
    return TRUE;
}

void Dualocke_PruebaPreparar(void)
{
    static const u16 sClave[] = {ITEM_GO_GOGGLES, ITEM_MACH_BIKE, ITEM_ACRO_BIKE, ITEM_SUPER_ROD, ITEM_DEVON_SCOPE};
    static const u16 sMovimientos[] = {MOVE_SURF, MOVE_WATERFALL, MOVE_DIVE, MOVE_STRENGTH};
    u32 i;

    if (!Dualocke_PruebaActiva())
        return;
    for (i = FLAG_BADGE01_GET; i <= FLAG_BADGE08_GET; i++)
        FlagSet(i);
    FlagSet(FLAG_SYS_POKEMON_GET);
    FlagSet(FLAG_SYS_POKEDEX_GET);
    FlagSet(FLAG_SYS_B_DASH);
    for (i = 0; i < ARRAY_COUNT(sClave); i++)
        AddBagItem(sClave[i], 1);
    AddBagItem(ITEM_MASTER_BALL, 20);
    AddBagItem(ITEM_REPEL, 20);
    if (!gDualockePrueba.sinEquipo)
    {
        ScriptGiveMon(gDualockePrueba.especie ? gDualockePrueba.especie : SPECIES_LAPRAS,
                      gDualockePrueba.nivel ? gDualockePrueba.nivel : 70, ITEM_NONE);
        for (i = 0; i < ARRAY_COUNT(sMovimientos); i++)
            SetMonMoveSlot(&gPlayerParty[0], sMovimientos[i], i);
    }
}
#endif // DUALOCKE_PRUEBA
