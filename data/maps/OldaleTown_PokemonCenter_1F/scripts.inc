OldaleTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

OldaleTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_OLDALE_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

OldaleTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_OLDALE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

OldaleTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox OldaleTown_PokemonCenter_1F_Text_TrainersCanUsePC, MSGBOX_NPC
	end

OldaleTown_PokemonCenter_1F_EventScript_Boy::
	msgbox OldaleTown_PokemonCenter_1F_Text_PokemonCentersAreGreat, MSGBOX_NPC
	end

OldaleTown_PokemonCenter_1F_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_SYS_POKEDEX_GET, OldaleTown_PokemonCenter_1F_EventScript_WirelessClubAvailable
	msgbox OldaleTown_PokemonCenter_1F_Text_WirelessClubNotAvailable, MSGBOX_DEFAULT
	release
	end

OldaleTown_PokemonCenter_1F_EventScript_WirelessClubAvailable::
	msgbox OldaleTown_PokemonCenter_1F_Text_TradedInWirelessClub, MSGBOX_DEFAULT
	release
	end

OldaleTown_PokemonCenter_1F_Text_TrainersCanUsePC:
	.string "El PC de ese rincón lo puede usar\n"
	.string "cualquier ENTRENADOR POKéMON.\p"
	.string "Claro, eso quiere decir que tú\n"
	.string "también puedes usarlo.$"

OldaleTown_PokemonCenter_1F_Text_PokemonCentersAreGreat:
	.string "¡Los CENTROS POKéMON son geniales!\p"
	.string "Puedes usarlos todo lo que quieras\n"
	.string "y además son gratis.\l"
	.string "¡No hay de qué preocuparse!$"

OldaleTown_PokemonCenter_1F_Text_WirelessClubNotAvailable:
	.string "El CLUB INALÁMBRICO POKéMON del\n"
	.string "segundo piso es nuevo.\p"
	.string "Pero dicen que todavía lo están\n"
	.string "ajustando.$"

OldaleTown_PokemonCenter_1F_Text_TradedInWirelessClub:
	.string "El CLUB INALÁMBRICO POKéMON del\n"
	.string "segundo piso es nuevo.\p"
	.string "Yo ya he cambiado POKéMON.$"

