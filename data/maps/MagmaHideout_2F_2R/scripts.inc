MagmaHideout_2F_2R_MapScripts::
	.byte 0

MagmaHideout_2F_2R_EventScript_Grunt15::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_15, MagmaHideout_2F_2R_Text_Grunt15Intro, MagmaHideout_2F_2R_Text_Grunt15Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt15PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_6, MagmaHideout_2F_2R_Text_Grunt6Intro, MagmaHideout_2F_2R_Text_Grunt6Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt6PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt7::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_7, MagmaHideout_2F_2R_Text_Grunt7Intro, MagmaHideout_2F_2R_Text_Grunt7Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt7PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_8, MagmaHideout_2F_2R_Text_Grunt8Intro, MagmaHideout_2F_2R_Text_Grunt8Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt8PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_Text_Grunt15Intro:
	.string "No tengo nada contra ti.\n"
	.string "¡Solo cumplo órdenes!$"

MagmaHideout_2F_2R_Text_Grunt15Defeat:
	.string "Habré perdido, pero…$"

MagmaHideout_2F_2R_Text_Grunt15PostBattle:
	.string "¡Hemos desenterrado algo increíble!\n"
	.string "¡Y tenemos el PRISMA AZUL!\p"
	.string "Solo falta que nuestro líder…\n"
	.string "Fufufu… ¡Fuajajaja!$"

MagmaHideout_2F_2R_Text_Grunt6Intro:
	.string "No aguanto el calor. Quizá tendría que\n"
	.string "haberme unido al EQUIPO AQUA…$"

MagmaHideout_2F_2R_Text_Grunt6Defeat:
	.string "Sí, puede que el EQUIPO MAGMA no sea\n"
	.string "lo mío…$"

MagmaHideout_2F_2R_Text_Grunt6PostBattle:
	.string "¿No echas de menos el mar en un\n"
	.string "sitio así?$"

MagmaHideout_2F_2R_Text_Grunt7Intro:
	.string "A veces se oyen temblores.\p"
	.string "¿Será el volcán?\n"
	.string "¿O será GROU…?\p"
	.string "¡Huy!\n"
	.string "¡No, no, olvídalo!$"

MagmaHideout_2F_2R_Text_Grunt7Defeat:
	.string "Combates con fuego.\n"
	.string "¡Como un volcán!$"

MagmaHideout_2F_2R_Text_Grunt7PostBattle:
	.string "Esta vez has ganado de casualidad,\n"
	.string "pero da igual.\p"
	.string "¡El EQUIPO MAGMA está a punto de\n"
	.string "cumplir su objetivo!$"

MagmaHideout_2F_2R_Text_Grunt8Intro:
	.string "Uno de los nuestros estaba de los\n"
	.string "nervios porque perdió su SIGNO MAGMA…\p"
	.string "¡Espera un momento!\n"
	.string "¿Lo encontraste tú?$"

MagmaHideout_2F_2R_Text_Grunt8Defeat:
	.string "Me cuesta creerlo…$"

MagmaHideout_2F_2R_Text_Grunt8PostBattle:
	.string "Tengo la sensación de que nuestro\n"
	.string "plan va a fracasar…$"

