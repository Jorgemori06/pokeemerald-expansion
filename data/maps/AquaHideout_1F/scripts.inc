AquaHideout_1F_MapScripts::
	.byte 0

@ The below two entrance guards give hints about what to do to progress the story
AquaHideout_1F_EventScript_HideoutEntranceGrunt1::
	lock
	faceplayer
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, AquaHideout_1F_EventScript_SlateportHint1
	goto_if_set FLAG_RECEIVED_RED_OR_BLUE_ORB, AquaHideout_1F_EventScript_MagmaHideoutHint1
	msgbox AquaHideout_1F_Text_OurBossIsSnatchingSomething, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_MagmaHideoutHint1::
	msgbox AquaHideout_1F_Text_WhereMightMagmaHideoutBe, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_SlateportHint1::
	msgbox AquaHideout_1F_Text_BossWentToJackASubmarine, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_HideoutEntranceGrunt2::
	lock
	faceplayer
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, AquaHideout_1F_EventScript_SlateportHint2
	goto_if_set FLAG_RECEIVED_RED_OR_BLUE_ORB, AquaHideout_1F_EventScript_MagmaHideoutHint2
	msgbox AquaHideout_1F_Text_BossIsOnRoute122, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_MagmaHideoutHint2::
	msgbox AquaHideout_1F_Text_TeamMagmaAtMtChimney, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_SlateportHint2::
	msgbox AquaHideout_1F_Text_BossIsInSlateportCity, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_1, AquaHideout_1F_Text_Grunt1Intro, AquaHideout_1F_Text_Grunt1Defeat, AquaHideout_1F_EventScript_Grunt1Defeated
	msgbox AquaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_1F_EventScript_Grunt1Defeated::
	msgbox AquaHideout_1F_Text_Grunt1PostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_Text_OurBossIsSnatchingSomething:
	.string "¿Qué? ¿Qué? ¿Qué quieres del\n"
	.string "EQUIPO AQUA?\p"
	.string "¡Nuestro JEFE no está! ¡Ha ido a\n"
	.string "hacerse con algo importante!\p"
	.string "… …\n"
	.string "¿Que adónde ha ido?\p"
	.string "¡Juajuajua! ¿De verdad crees que te\n"
	.string "diría algo tan importante?$"

AquaHideout_1F_Text_WhereMightMagmaHideoutBe:
	.string "¿Qué? ¿Qué?\n"
	.string "¿Eres un soldado del EQUIPO MAGMA?\p"
	.string "He oído que el EQUIPO MAGMA intenta\n"
	.string "despertar a un POKéMON tremendo en\l"
	.string "su GUARIDA.\p"
	.string "¿Pero dónde estará su GUARIDA?$"

AquaHideout_1F_Text_BossWentToJackASubmarine:
	.string "¿Qué? ¿Qué? ¿Qué quieres del\n"
	.string "EQUIPO AQUA?\p"
	.string "¡Nuestro JEFE no está!\n"
	.string "¡Ha ido a robar un submarino!\p"
	.string "… …\n"
	.string "¿Que adónde ha ido?\p"
	.string "¡Juajuajua! ¿De verdad crees que te\n"
	.string "diría algo tan importante?$"

AquaHideout_1F_Text_BossIsOnRoute122:
	.string "¿Qué? ¿Qué? ¿Qué quieres del\n"
	.string "EQUIPO AQUA?\p"
	.string "¡Nuestro JEFE no está! ¡Va camino del\n"
	.string "MONTE PÍRICO, en la RUTA 122!\p"
	.string "… …\n"
	.string "¿Que por qué ha ido?\p"
	.string "¡Juajuajua! ¿De verdad crees que te\n"
	.string "diría algo tan importante?$"

AquaHideout_1F_Text_TeamMagmaAtMtChimney:
	.string "¿Qué? ¿Qué?\n"
	.string "¿Eres un soldado del EQUIPO MAGMA?\p"
	.string "He oído que el EQUIPO MAGMA va a por\n"
	.string "un POKéMON enorme en el MONTE CENIZO.\p"
	.string "¿Pero cómo será ese POKéMON?$"

AquaHideout_1F_Text_BossIsInSlateportCity:
	.string "¿Qué? ¿Qué? ¿Qué quieres del\n"
	.string "EQUIPO AQUA?\p"
	.string "¡Nuestro JEFE no está!\n"
	.string "¡Va camino de CIUDAD PORTUAL!\p"
	.string "… …\n"
	.string "¿Que por qué ha ido?\p"
	.string "¡Juajuajua! ¿De verdad crees que te\n"
	.string "diría algo tan importante?$"

AquaHideout_1F_Text_Grunt1Intro:
	.string "¡Ayayay!\n"
	.string "¡Intruso a la vista!$"

AquaHideout_1F_Text_Grunt1Defeat:
	.string "Grrrrr…\n"
	.string "¡He perdido!$"

AquaHideout_1F_Text_Grunt1PostBattle:
	.string "He perdido por el EQUIPO, pero he\n"
	.string "cumplido con mi deber…$"

