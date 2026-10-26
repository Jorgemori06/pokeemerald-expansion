EverGrandeCity_DrakesRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_DrakesRoom_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_DrakesRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_SidneysRoom_OnWarp
	.byte 0

@ Unused, Drake uses Sidneys identical OnWarp for some reason
EverGrandeCity_DrakesRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_DrakesRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_DrakesRoom_EventScript_PlayerTurnNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

EverGrandeCity_DrakesRoom_OnFrame:
	map_script_2 VAR_ELITE_4_STATE, 3, EverGrandeCity_DrakesRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_DrakesRoom_EventScript_WalkInCloseDoor::
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 4
	releaseall
	end

EverGrandeCity_DrakesRoom_OnLoad:
	call_if_set FLAG_DEFEATED_ELITE_4_DRAKE, EverGrandeCity_DrakesRoom_EventScript_ResetAdvanceToNextRoom
	call_if_eq VAR_ELITE_4_STATE, 4, EverGrandeCity_DrakesRoom_EventScript_CloseDoor
	end

EverGrandeCity_DrakesRoom_EventScript_ResetAdvanceToNextRoom::
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_DrakesRoom_EventScript_CloseDoor::
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_DrakesRoom_EventScript_Drake::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_DRAKE, EverGrandeCity_DrakesRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_DrakesRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_DRAKE, EverGrandeCity_DrakesRoom_Text_Defeat
	goto EverGrandeCity_DrakesRoom_EventScript_Defeated
	end

EverGrandeCity_DrakesRoom_EventScript_PostBattleSpeech::
	msgbox EverGrandeCity_DrakesRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_DrakesRoom_EventScript_Defeated::
	setvar VAR_0x8004, FANCOUNTER_DEFEATED_DRAKE
	special Script_TryGainNewFanFromCounter
	setflag FLAG_DEFEATED_ELITE_4_DRAKE
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_DrakesRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_DrakesRoom_Text_IntroSpeech:
	.string "¡Soy el último del ALTO MANDO de la\n"
	.string "LIGA POKéMON, DRACÓN, el maestro\l"
	.string "de los DRAGONES!\p"
	.string "En su estado natural, los POKéMON son\n"
	.string "seres salvajes. Son libres.\p"
	.string "A veces nos estorban.\n"
	.string "A veces nos ayudan.\p"
	.string "Para combatir con POKéMON como\n"
	.string "compañeros, ¿sabes qué hace falta?\p"
	.string "¿Sabes lo que se necesita?\p"
	.string "¡Si no lo sabes, nunca podrás\n"
	.string "vencerme!$"

EverGrandeCity_DrakesRoom_Text_Defeat:
	.string "Soberbio, hay que decirlo.$"

EverGrandeCity_DrakesRoom_Text_PostBattleSpeech:
	.string "Te mereces todo el reconocimiento por\n"
	.string "haber llegado hasta aquí con tus\l"
	.string "POKéMON.\p"
	.string "Parece que sabes lo que hace falta.\p"
	.string "Sí, lo que necesita un ENTRENADOR es\n"
	.string "un corazón virtuoso.\p"
	.string "Los POKéMON tocan el buen corazón de\n"
	.string "sus ENTRENADORES y aprenden el bien\l"
	.string "y el mal.\p"
	.string "Tocan el buen corazón de sus\n"
	.string "ENTRENADORES y se hacen fuertes.\p"
	.string "¡Ve! ¡Sigue adelante!\n"
	.string "¡El CAMPEÓN te espera!$"

