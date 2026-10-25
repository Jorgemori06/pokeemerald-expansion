FortreeCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FortreeCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_FORTREE_CITY
	end

FortreeCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_FORTREE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FortreeCity_PokemonCenter_1F_EventScript_Gentleman::
	msgbox FortreeCity_PokemonCenter_1F_Text_GoToSafariZone, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Man::
	msgbox FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Boy::
	msgbox FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_Text_GoToSafariZone:
	.string "Oye, ¿estás completando la\n"
	.string "POKéDEX?\p"
	.string "Mmm… Ve a la ZONA SAFARI.\n"
	.string "Eso te recomiendo.$"

FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat:
	.string "¿Has probado el RINCÓN RÉCORDS?\p"
	.string "Está muy bien. Mezcla y combina los\n"
	.string "récords de los ENTRENADORES.\p"
	.string "No sé muy bien cómo funciona, pero\n"
	.string "mola. ¡Hasta emociona!$"

FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav:
	.string "¡Hala, tienes un POKéNAV!\n"
	.string "¡Y es igual que el mío!\p"
	.string "¿Conoces la AGENDA del POKéNAV?\p"
	.string "Con ella puedes hablar con los\n"
	.string "ENTRENADORES registrados.\p"
	.string "También te dice qué ENTRENADORES\n"
	.string "quieren la revancha.\p"
	.string "¡Es una pasada! ¡Los de DEVON saben\n"
	.string "lo que hacen!$"

