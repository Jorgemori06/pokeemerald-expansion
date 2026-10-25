Route110_TrickHousePuzzle6_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_TrickHousePuzzle6_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route110_TrickHousePuzzle6_OnWarp
	.byte 0

Route110_TrickHousePuzzle6_OnTransition:
	special RotatingGate_InitPuzzle
	end

Route110_TrickHousePuzzle6_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, Route110_TrickHousePuzzle6_EventScript_InitPuzzle
	.2byte 0

@ NOTE: This rotating gate puzzle makes use of VAR_TEMP_0 - VAR_TEMP_5
Route110_TrickHousePuzzle6_EventScript_InitPuzzle::
	special RotatingGate_InitPuzzleAndGraphics
	end

Route110_TrickHousePuzzle6_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_6_STATE, 0, Route110_TrickHousePuzzle6_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle6_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_6_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle6_EventScript_Sophia::
	trainerbattle_single TRAINER_SOPHIA, Route110_TrickHousePuzzle6_Text_SophiaIntro, Route110_TrickHousePuzzle6_Text_SophiaDefeat
	msgbox Route110_TrickHousePuzzle6_Text_SophiaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_EventScript_Benny::
	trainerbattle_single TRAINER_BENNY, Route110_TrickHousePuzzle6_Text_BennyIntro, Route110_TrickHousePuzzle6_Text_BennyDefeat
	msgbox Route110_TrickHousePuzzle6_Text_BennyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_EventScript_Sebastian::
	trainerbattle_single TRAINER_SEBASTIAN, Route110_TrickHousePuzzle6_Text_SebastianIntro, Route110_TrickHousePuzzle6_Text_SebastianDefeat
	msgbox Route110_TrickHousePuzzle6_Text_SebastianPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_Text_WroteSecretCodeLockOpened:
	.string "{PLAYER} ha escrito el código\n"
	.string "secreto en la puerta.\p"
	.string "“El MAESTRO TRAMPA es mi vida”.\n"
	.string "… … … … … … … …\p"
	.string "¡La cerradura se ha abierto!$"

Route110_TrickHousePuzzle6_Text_SophiaIntro:
	.string "Cuando me dijeron que había una casa\n"
	.string "rara, tuve que venir a verla.$"

Route110_TrickHousePuzzle6_Text_SophiaDefeat:
	.string "¡He descubierto a alguien muy duro!$"

Route110_TrickHousePuzzle6_Text_SophiaPostBattle:
	.string "Me lo estoy pasando genial\n"
	.string "explorando este sitio.\p"
	.string "¡Es un desafío que merece la pena\n"
	.string "repetir!$"

Route110_TrickHousePuzzle6_Text_BennyIntro:
	.string "A lo mejor mi POKéMON PÁJARO puede\n"
	.string "volar por encima de la pared…$"

Route110_TrickHousePuzzle6_Text_BennyDefeat:
	.string "¡Uaaah! ¡La he fastidiado!$"

Route110_TrickHousePuzzle6_Text_BennyPostBattle:
	.string "Jejeje… Supongo que he perdido por\n"
	.string "intentar hacer trampa.$"

Route110_TrickHousePuzzle6_Text_SebastianIntro:
	.string "Me estoy mareando con estas\n"
	.string "puertas giratorias…$"

Route110_TrickHousePuzzle6_Text_SebastianDefeat:
	.string "Todo me da vueltas y más vueltas.\n"
	.string "No puedo más…$"

Route110_TrickHousePuzzle6_Text_SebastianPostBattle:
	.string "Parece que a ti no te afecta nada.\n"
	.string "¿O es que pones cara de póquer?$"

