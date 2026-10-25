MagmaHideout_3F_2R_MapScripts::
	.byte 0

MagmaHideout_3F_2R_EventScript_Grunt10::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_10, MagmaHideout_3F_2R_Text_Grunt10Intro, MagmaHideout_3F_2R_Text_Grunt10Defeat
	msgbox MagmaHideout_3F_2R_Text_Grunt10PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_2R_Text_Grunt10Intro:
	.string "Entiendo todo lo que dice nuestro\n"
	.string "líder. ¿Pero sabes qué?\p"
	.string "Desenterrar un POKéMON superancestral\n"
	.string "y robarle el METEORITO a alguien…\p"
	.string "Creo que nos estamos pasando un poco.\n"
	.string "¿Tú qué crees?$"

MagmaHideout_3F_2R_Text_Grunt10Defeat:
	.string "Sí, creo que algo estamos haciendo\n"
	.string "mal.$"

MagmaHideout_3F_2R_Text_Grunt10PostBattle:
	.string "¿Sabes? Perder contra ti me ha\n"
	.string "aclarado las ideas.\p"
	.string "La próxima vez que vea a nuestro líder,\n"
	.string "le preguntaré por lo que hacemos.$"

