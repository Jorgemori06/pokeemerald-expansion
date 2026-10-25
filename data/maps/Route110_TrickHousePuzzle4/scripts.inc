Route110_TrickHousePuzzle4_MapScripts::
	.byte 0

Route110_TrickHousePuzzle4_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_4_STATE, 0, Route110_TrickHousePuzzle4_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle4_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_4_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle4_EventScript_Cora::
	trainerbattle_single TRAINER_CORA, Route110_TrickHousePuzzle4_Text_CoraIntro, Route110_TrickHousePuzzle4_Text_CoraDefeat
	msgbox Route110_TrickHousePuzzle4_Text_CoraPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Yuji::
	trainerbattle_single TRAINER_YUJI, Route110_TrickHousePuzzle4_Text_YujiIntro, Route110_TrickHousePuzzle4_Text_YujiDefeat
	msgbox Route110_TrickHousePuzzle4_Text_YujiPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Paula::
	trainerbattle_single TRAINER_PAULA, Route110_TrickHousePuzzle4_Text_PaulaIntro, Route110_TrickHousePuzzle4_Text_PaulaDefeat
	msgbox Route110_TrickHousePuzzle4_Text_PaulaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_Text_WroteSecretCodeLockOpened:
	.string "{PLAYER} ha escrito el código\n"
	.string "secreto en la puerta.\p"
	.string "“El MAESTRO TRAMPA mola”.\n"
	.string "… … … … … … … …\p"
	.string "¡La cerradura se ha abierto!$"

Route110_TrickHousePuzzle4_Text_CoraIntro:
	.string "Pensar esto es un rollo.\n"
	.string "¡Yo solo quería combatir!$"

Route110_TrickHousePuzzle4_Text_CoraDefeat:
	.string "¡Aunque haya perdido, combatir es\n"
	.string "lo que más me gusta!$"

Route110_TrickHousePuzzle4_Text_CoraPostBattle:
	.string "¿A que sí? Irías a cualquier parte\n"
	.string "si hubiera ENTRENADORES.$"

Route110_TrickHousePuzzle4_Text_YujiIntro:
	.string "¡Je! ¡Rocas como estas las aparto\n"
	.string "con un dedo!$"

Route110_TrickHousePuzzle4_Text_YujiDefeat:
	.string "Puedo empujar rocas, pero no\n"
	.string "resolver el puzle…$"

Route110_TrickHousePuzzle4_Text_YujiPostBattle:
	.string "No basta con tener músculo…\n"
	.string "¡Hay que usar la cabeza!$"

Route110_TrickHousePuzzle4_Text_PaulaIntro:
	.string "La CASA TRAMPA cada vez tiene más\n"
	.string "trampas, ¿no?$"

Route110_TrickHousePuzzle4_Text_PaulaDefeat:
	.string "¡Aaah!$"

Route110_TrickHousePuzzle4_Text_PaulaPostBattle:
	.string "¿Alguien habrá llegado al final?$"

