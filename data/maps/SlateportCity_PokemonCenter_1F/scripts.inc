SlateportCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SlateportCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

SlateportCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_SLATEPORT_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

SlateportCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_SLATEPORT_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

SlateportCity_PokemonCenter_1F_EventScript_Sailor::
	msgbox SlateportCity_PokemonCenter_1F_Text_RaiseDifferentTypesOfPokemon, MSGBOX_NPC
	end

SlateportCity_PokemonCenter_1F_EventScript_Woman::
	msgbox SlateportCity_PokemonCenter_1F_Text_TradedMonWithFriend, MSGBOX_NPC
	end

SlateportCity_PokemonCenter_1F_Text_RaiseDifferentTypesOfPokemon:
	.string "¿Quieres un consejo para combatir?\p"
	.string "Yo diría que criar POKéMON de\n"
	.string "distintos tipos de forma equilibrada.\p"
	.string "No sirve de nada hacer fuerte\n"
	.string "a un solo POKéMON.\p"
	.string "Si tiene desventaja de tipo, puede\n"
	.string "que no tenga nada que hacer.$"

SlateportCity_PokemonCenter_1F_Text_TradedMonWithFriend:
	.string "Cambio POKéMON con mis amigos.\p"
	.string "¡Si el POKéMON que me dan lleva un\n"
	.string "objeto, me hace el doble de ilusión!$"

