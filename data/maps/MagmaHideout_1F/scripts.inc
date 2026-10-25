MagmaHideout_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MagmaHideout_1F_OnTransition
	.byte 0

MagmaHideout_1F_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 0
	end

MagmaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_1, MagmaHideout_1F_Text_Grunt1Intro, MagmaHideout_1F_Text_Grunt1Defeat
	msgbox MagmaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_2, MagmaHideout_1F_Text_Grunt2Intro, MagmaHideout_1F_Text_Grunt2Defeat
	msgbox MagmaHideout_1F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_Text_Grunt1Intro:
	.string "Cuando el EQUIPO MAGMA pasa lista, nos\n"
	.string "dan las guardias importantes según el\l"
	.string "orden en que formamos.\p"
	.string "Por eso me toca esta esquina.\n"
	.string "¡Siempre llego tarde a pasar lista!$"

MagmaHideout_1F_Text_Grunt1Defeat:
	.string "¡También llego siempre tarde a los\n"
	.string "entrenamientos!\p"
	.string "Me duele decirlo, pero soy un blando…$"

MagmaHideout_1F_Text_Grunt1PostBattle:
	.string "Vale, a partir de ahora intentaré\n"
	.string "esforzarme un poco más…$"

MagmaHideout_1F_Text_Grunt2Intro:
	.string "Nuestro líder nos dijo que caváramos\n"
	.string "en el MONTE CENIZO, y cavamos sin parar.\p"
	.string "Y cavando, ¡encontramos algo que nos\n"
	.string "dejó alucinados!\p"
	.string "¿Qué encontramos?\p"
	.string "¡Fujajaja!\n"
	.string "¡Te lo diré si me ganas!$"

MagmaHideout_1F_Text_Grunt2Defeat:
	.string "¡Arrgh!\n"
	.string "¡Derribado!$"

MagmaHideout_1F_Text_Grunt2PostBattle:
	.string "Al final no te lo digo.\n"
	.string "¡Ya lo verás cuando llegues!\p"
	.string "Las sorpresas mejor para el final,\n"
	.string "¿no crees?$"

