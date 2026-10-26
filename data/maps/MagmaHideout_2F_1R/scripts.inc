MagmaHideout_2F_1R_MapScripts::
	.byte 0

MagmaHideout_2F_1R_EventScript_Grunt14::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_14, MagmaHideout_2F_1R_Text_Grunt14Intro, MagmaHideout_2F_1R_Text_Grunt14Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt14PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_3, MagmaHideout_2F_1R_Text_Grunt3Intro, MagmaHideout_2F_1R_Text_Grunt3Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_4, MagmaHideout_2F_1R_Text_Grunt4Intro, MagmaHideout_2F_1R_Text_Grunt4Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_5, MagmaHideout_2F_1R_Text_Grunt5Intro, MagmaHideout_2F_1R_Text_Grunt5Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_Text_Grunt14Intro:
	.string "¿Qué, qué, qué?\p"
	.string "¡Aquí solo pueden estar los miembros\n"
	.string "del EQUIPO MAGMA!\p"
	.string "Pero no llevas el uniforme del\n"
	.string "EQUIPO MAGMA…\p"
	.string "¡Qué sospechoso!\n"
	.string "¡Combate conmigo!$"

MagmaHideout_2F_1R_Text_Grunt14Defeat:
	.string "Ayayay…\n"
	.string "Mi orgullo de miembro del MAGMA…$"

MagmaHideout_2F_1R_Text_Grunt14PostBattle:
	.string "Si sufres de frío, deberías unirte al\n"
	.string "EQUIPO MAGMA.$"

MagmaHideout_2F_1R_Text_Grunt3Intro:
	.string "¡Alto ahí!\p"
	.string "¿De verdad crees que voy a cerrar el\n"
	.string "pico y dejarte pasar sin más?$"

MagmaHideout_2F_1R_Text_Grunt3Defeat:
	.string "¡Uau!\n"
	.string "¡Me rindo!$"

MagmaHideout_2F_1R_Text_Grunt3PostBattle:
	.string "A lo mejor habría sido mejor dejarte\n"
	.string "pasar sin más…$"

MagmaHideout_2F_1R_Text_Grunt4Intro:
	.string "¡Ajá!\n"
	.string "¡Un intruso!$"

MagmaHideout_2F_1R_Text_Grunt4Defeat:
	.string "¡Grrraaah!$"

MagmaHideout_2F_1R_Text_Grunt4PostBattle:
	.string "Ya he perdido.\p"
	.string "¿De verdad tengo que seguir dando\n"
	.string "vueltas en círculo?$"

MagmaHideout_2F_1R_Text_Grunt5Intro:
	.string "¡Oh, oh!\n"
	.string "¡Un intruso!$"

MagmaHideout_2F_1R_Text_Grunt5Defeat:
	.string "Grrr…$"

MagmaHideout_2F_1R_Text_Grunt5PostBattle:
	.string "La verdad es que combatir no se me\n"
	.string "da nada bien…$"

