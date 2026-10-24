RustboroCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

RustboroCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_RUSTBORO_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

RustboroCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_RUSTBORO_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

RustboroCity_PokemonCenter_1F_EventScript_Man::
	msgbox RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Boy::
	msgbox RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_EventScript_Girl::
	msgbox RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor, MSGBOX_NPC
	end

RustboroCity_PokemonCenter_1F_Text_PokemonHavePersonalities:
	.string "Mi POKéMON tiene naturaleza ALOCADA\n"
	.string "y el de mi amigo, ALEGRE.\p"
	.string "¡Es fascinante que los POKéMON\n"
	.string "tengan personalidad!$"

RustboroCity_PokemonCenter_1F_Text_MaleAndFemalePokemon:
	.string "Igual que las personas, hay POKéMON\n"
	.string "machos y hembras.\p"
	.string "Pero nadie parece saber en qué\n"
	.string "se diferencian.$"

RustboroCity_PokemonCenter_1F_Text_HMCutNextDoor:
	.string "¡El hombre de al lado me ha dado\n"
	.string "una MO!\p"
	.string "La he usado para enseñar a mi\n"
	.string "POKéMON a CORTAR árboles finos.$"

