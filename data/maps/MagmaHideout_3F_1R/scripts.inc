MagmaHideout_3F_1R_MapScripts::
	.byte 0

MagmaHideout_3F_1R_EventScript_Grunt9::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_9, MagmaHideout_3F_1R_Text_Grunt9Intro, MagmaHideout_3F_1R_Text_Grunt9Defeat
	msgbox MagmaHideout_3F_1R_Text_Grunt9PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_1R_EventScript_Grunt16::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_16, MagmaHideout_3F_1R_Text_Grunt16Intro, MagmaHideout_3F_1R_Text_Grunt16Defeat
	msgbox MagmaHideout_3F_1R_Text_Grunt16PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_1R_Text_Grunt9Intro:
	.string "¿Qué he hecho yo para merecer este\n"
	.string "puesto de guardia?\p"
	.string "¡Se me está quemando la oreja\n"
	.string "izquierda!$"

MagmaHideout_3F_1R_Text_Grunt9Defeat:
	.string "Me va a dar un golpe de calor…$"

MagmaHideout_3F_1R_Text_Grunt9PostBattle:
	.string "¿No te parece raro que llevemos\n"
	.string "capucha en un volcán lleno de magma?$"

MagmaHideout_3F_1R_Text_Grunt16Intro:
	.string "Nos unimos para ayudar a nuestro\n"
	.string "líder a cumplir su gran visión.\p"
	.string "Me da igual si eres del EQUIPO AQUA\n"
	.string "o si solo pasabas por aquí.\p"
	.string "¡Nadie se mete con nosotros y se\n"
	.string "sale con la suya!$"

MagmaHideout_3F_1R_Text_Grunt16Defeat:
	.string "¡Ay, no!\n"
	.string "¡No hay quien se fíe de ti!$"

MagmaHideout_3F_1R_Text_Grunt16PostBattle:
	.string "Escúchame.\n"
	.string "¡El EQUIPO MAGMA tiene razón!\p"
	.string "No le hagas caso al EQUIPO AQUA.\n"
	.string "¡No te creas sus mentiras!$"

