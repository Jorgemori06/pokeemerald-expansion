Route110_TrickHousePuzzle1_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Route110_TrickHousePuzzle1_OnLoad
	.byte 0

Route110_TrickHousePuzzle1_OnLoad:
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_1_STATE, 2, Route110_TrickHousePuzzle1_EventScript_OpenDoor
	end

Route110_TrickHousePuzzle1_EventScript_OpenDoor::
	setmetatile 13, 1, METATILE_TrickHousePuzzle_Stairs_Down, FALSE
	end

Route110_TrickHousePuzzle1_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_1_STATE, 0, Route110_TrickHousePuzzle1_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle1_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_1_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle1_EventScript_Sally::
	trainerbattle_single TRAINER_SALLY, Route110_TrickHousePuzzle1_Text_SallyIntro, Route110_TrickHousePuzzle1_Text_SallyDefeat
	msgbox Route110_TrickHousePuzzle1_Text_SallyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_EventScript_Eddie::
	trainerbattle_single TRAINER_EDDIE, Route110_TrickHousePuzzle1_Text_EddieIntro, Route110_TrickHousePuzzle1_Text_EddieDefeat
	msgbox Route110_TrickHousePuzzle1_Text_EddiePostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_EventScript_Robin::
	trainerbattle_single TRAINER_ROBIN, Route110_TrickHousePuzzle1_Text_RobinIntro, Route110_TrickHousePuzzle1_Text_RobinDefeat
	msgbox Route110_TrickHousePuzzle1_Text_RobinPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_Text_WroteSecretCodeLockOpened::
	.string "{PLAYER} ha escrito el código\n"
	.string "secreto en la puerta.\p"
	.string "“El MAESTRO TRAMPA es fabuloso”.\n"
	.string "… … … … … … … …\p"
	.string "¡La cerradura se ha abierto!$"

Route110_TrickHousePuzzle1_Text_SallyIntro:
	.string "¡Me abriré paso a tajos con el CORTE\n"
	.string "que acabamos de aprender!$"

Route110_TrickHousePuzzle1_Text_SallyDefeat:
	.string "¿Por qué te lo tomas tan en serio?$"

Route110_TrickHousePuzzle1_Text_SallyPostBattle:
	.string "¡Nunca me canso de dar tajos!$"

Route110_TrickHousePuzzle1_Text_EddieIntro:
	.string "He entrado en esta casa tan rara\n"
	.string "por casualidad…$"

Route110_TrickHousePuzzle1_Text_EddieDefeat:
	.string "Y ahora he perdido…$"

Route110_TrickHousePuzzle1_Text_EddiePostBattle:
	.string "Me he perdido, he perdido un combate\n"
	.string "y ahora estoy más perdido… No salgo…$"

Route110_TrickHousePuzzle1_Text_RobinIntro:
	.string "¿Quién será el MAESTRO TRAMPA?$"

Route110_TrickHousePuzzle1_Text_RobinDefeat:
	.string "¡He perdido por estar pensando\n"
	.string "en las musarañas!$"

Route110_TrickHousePuzzle1_Text_RobinPostBattle:
	.string "¡Qué fuerte eres!\n"
	.string "¿Quién eres tú?$"

