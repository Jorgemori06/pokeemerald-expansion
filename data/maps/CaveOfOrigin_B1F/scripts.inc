CaveOfOrigin_B1F_MapScripts::
	.byte 0

CaveOfOrigin_B1F_EventScript_Wallace::
	lock
	faceplayer
	msgbox CaveOfOrigin_B1F_Text_WallaceStory, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 60
	playse SE_PIN
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_Delay48
	waitmovement 0
	delay 30
	applymovement LOCALID_CAVE_OF_ORIGIN_WALLACE, Common_Movement_FacePlayer
	waitmovement 0
	message CaveOfOrigin_B1F_Text_WhereIsRayquaza
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_WheresRayquaza::
	multichoice 0, 0, MULTI_WHERES_RAYQUAZA, FALSE
	switch VAR_RESULT
	case 0, CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin
	case 1, CaveOfOrigin_B1F_EventScript_AtMtPyre
	case 2, CaveOfOrigin_B1F_EventScript_AtSkyPillar
	case 3, CaveOfOrigin_B1F_EventScript_DontRemember
	goto CaveOfOrigin_B1F_EventScript_DontRemember
	end

CaveOfOrigin_B1F_EventScript_AtCaveOfOrigin::
	message CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtMtPyre::
	message CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_DontRemember::
	message CaveOfOrigin_B1F_Text_CantYouRememberSomehow
	waitmessage
	goto CaveOfOrigin_B1F_EventScript_WheresRayquaza

CaveOfOrigin_B1F_EventScript_AtSkyPillar::
	msgbox CaveOfOrigin_B1F_Text_WellHeadToSkyPillar, MSGBOX_DEFAULT
	closemessage
	playse SE_EXIT
	fadescreenspeed FADE_TO_BLACK, 4
	setflag FLAG_WALLACE_GOES_TO_SKY_PILLAR
	setvar VAR_SOOTOPOLIS_CITY_STATE, 3
	removeobject LOCALID_CAVE_OF_ORIGIN_WALLACE
	clearflag FLAG_HIDE_SKY_PILLAR_WALLACE
	fadescreen FADE_FROM_BLACK
	release
	end

CaveOfOrigin_B1F_Text_WallaceStory:
	.string "¿Ah, así que eres {PLAYER}{KUN}?\n"
	.string "He oído hablar de tus hazañas.\p"
	.string "Me llamo PLUBIO.\p"
	.string "Antes era el LÍDER del GIMNASIO de\n"
	.string "ARRECÍPOLIS, pero surgió algo.\p"
	.string "Así que le he confiado el GIMNASIO\n"
	.string "a mi maestro, GALANO.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "GROUDON y KYOGRE, los dos POKéMON que\n"
	.string "están sembrando el caos, se\l"
	.string "consideran POKéMON superancestrales.\p"
	.string "Pero no hay solo dos POKéMON\n"
	.string "superancestrales.\p"
	.string "Hay uno más en alguna parte.\p"
	.string "En algún lugar hay un POKéMON\n"
	.string "superancestral llamado RAYQUAZA.\p"
	.string "Dicen que fue RAYQUAZA quien calmó a\n"
	.string "los dos rivales en un pasado remoto.\p"
	.string "Pero ni siquiera yo tengo idea de\n"
	.string "dónde está RAYQUAZA…$"

CaveOfOrigin_B1F_Text_WhereIsRayquaza:
	.string "PLUBIO: {PLAYER}{KUN}, ¿sabes\n"
	.string "dónde está RAYQUAZA ahora?\p"
	.string "Si lo sabes, dímelo, por favor.$"

CaveOfOrigin_B1F_Text_ButWereInCaveOfOrigin:
	.string "PLUBIO: ¿La CUEVA ANCESTRAL?\p"
	.string "¡Pero si es aquí mismo!\n"
	.string "¡Necesito algo mejor que eso!\p"
	.string "Por favor, piensa dónde podría estar\n"
	.string "RAYQUAZA ahora mismo.$"

CaveOfOrigin_B1F_Text_OldLadyDidntMentionThat:
	.string "PLUBIO: ¿El MONTE PÍRICO?\p"
	.string "Pero cuando vi antes a la anciana de\n"
	.string "allí, no me dijo nada de eso.\p"
	.string "Dudo mucho que la anciana intentara\n"
	.string "ocultarme algo…\p"
	.string "{PLAYER}{KUN}, ¿puedes pensarlo\n"
	.string "con más calma?$"

CaveOfOrigin_B1F_Text_CantYouRememberSomehow:
	.string "PLUBIO: ¿Eh? ¿No te acuerdas?\n"
	.string "Mmm… Eso es un problema…\p"
	.string "¿No puedes hacer memoria?$"

CaveOfOrigin_B1F_Text_WellHeadToSkyPillar:
	.string "PLUBIO: ¿El PILAR CELESTE?\p"
	.string "¡Eso es!\n"
	.string "¡Tiene que ser el PILAR CELESTE!\p"
	.string "{PLAYER}{KUN}, ¡no hay tiempo!\n"
	.string "¡Vamos ya mismo al PILAR CELESTE!$"

