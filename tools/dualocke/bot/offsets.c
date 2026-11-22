/* Desplazamientos de structs que necesita el bot (preparar.py lo compila y los lee). */
#include "global.h"
#include "battle.h"
#include "pokemon.h"
#include "party_menu.h"
#include "field_player_avatar.h"
#define O(n, s, f) const unsigned int n = offsetof(s, f);
#define S(n, s) const unsigned int n = sizeof(s);
O(bm_hp, struct BattlePokemon, hp)
O(bm_maxHP, struct BattlePokemon, maxHP)
O(bm_level, struct BattlePokemon, level)
O(bm_moves, struct BattlePokemon, moves)
O(bm_pp, struct BattlePokemon, pp)
O(bm_types, struct BattlePokemon, types)
O(bm_ability, struct BattlePokemon, ability)
O(bm_status1, struct BattlePokemon, status1)
S(sz_bm, struct BattlePokemon)
O(pk_level, struct Pokemon, level)
O(pk_hp, struct Pokemon, hp)
O(pk_maxHP, struct Pokemon, maxHP)
O(pk_status, struct Pokemon, status)
S(sz_pk, struct Pokemon)
S(sz_box, struct BoxPokemon)
O(pa_objId, struct PlayerAvatar, objectEventId)
O(pm_slot, struct PartyMenu, slotId)
O(pm_action, struct PartyMenu, action)
