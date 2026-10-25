#include "global.h"
#include "battle.h"
#include "dualocke_es.h"
#include "string_util.h"
#include "constants/battle_string_ids.h"
#include "constants/characters.h"

// Dualocke: traducción al español de los mensajes de combate.
// - La tabla sTextosCombateES (src/data/dualocke_textos_combate_es.h) tiene los mensajes de
//   gBattleStringsTable ya traducidos. Los que faltan salen en inglés, así que se puede
//   traducir poco a poco.
// - En los tests de la expansion (TESTING) siempre sale el inglés.
// - El nombre de un Pokémon rival lleva artículo delante y "salvaje"/"enemigo" detrás:
//   "¡El Pikachu salvaje usó Placaje!", "La Defensa del Pikachu enemigo bajó".

#include "data/dualocke_textos_combate_es.h"

const u8 *Dualocke_GetBattleStringES(u32 stringId)
{
    if (TESTING || stringId >= ARRAY_COUNT(sTextosCombateES))
        return NULL;
    return sTextosCombateES[stringId];
}

// Escribe "El "/"el " delante del nombre de un Pokémon rival y devuelve el nuevo dstID.
u32 Dualocke_CopiarArticuloES(u8 *dst, u32 dstID, bool32 mayuscula)
{
    dst[dstID++] = mayuscula ? CHAR_E : CHAR_e;
    dst[dstID++] = CHAR_l;
    dst[dstID++] = CHAR_SPACE;
    return dstID;
}

static const u8 sText_SufijoSalvaje[] = _(" salvaje");
static const u8 sText_SufijoEnemigo[] = _(" enemigo");

void Dualocke_AnadirSufijoES(u8 *nombre, bool32 entrenador)
{
    StringAppend(nombre, entrenador ? sText_SufijoEnemigo : sText_SufijoSalvaje);
}

static bool32 EsInicioDePalabra(const u8 *str, u32 pos)
{
    if (pos == 0)
        return TRUE;
    pos--;
    return str[pos] == CHAR_SPACE || str[pos] == CHAR_INV_EXCL_MARK
        || str[pos] == CHAR_INV_QUESTION_MARK || str[pos] >= CHAR_PROMPT_SCROLL;
}

// Junta "de el " en "del " y "a el " en "al " (también "A el " -> "Al ") sobre el mensaje
// ya montado, porque el artículo y la preposición pueden venir de trozos distintos.
// Devuelve la nueva longitud.
u32 Dualocke_ContraccionesES(u8 *str)
{
    u32 i = 0, j = 0;

    while (str[i] != EOS)
    {
        if (EsInicioDePalabra(str, j) && str[i] == CHAR_d && str[i + 1] == CHAR_e
         && str[i + 2] == CHAR_SPACE && str[i + 3] == CHAR_e && str[i + 4] == CHAR_l
         && str[i + 5] == CHAR_SPACE)
        {
            str[j++] = CHAR_d;
            str[j++] = CHAR_e;
            str[j++] = CHAR_l;
            str[j++] = CHAR_SPACE;
            i += 6;
        }
        else if (EsInicioDePalabra(str, j) && (str[i] == CHAR_a || str[i] == CHAR_A)
              && str[i + 1] == CHAR_SPACE && str[i + 2] == CHAR_e && str[i + 3] == CHAR_l
              && str[i + 4] == CHAR_SPACE)
        {
            str[j++] = str[i];
            str[j++] = CHAR_l;
            str[j++] = CHAR_SPACE;
            i += 5;
        }
        else
        {
            str[j++] = str[i++];
        }
    }
    str[j] = EOS;
    return j;
}
