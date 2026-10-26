AquaHideout_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AquaHideout_B2F_OnTransition
	.byte 0

AquaHideout_B2F_OnTransition:
	call_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, AquaHideout_B2F_EventScript_PreventMattNoticing
	end

AquaHideout_B2F_EventScript_PreventMattNoticing::
	setvar VAR_TEMP_1, 1
	return

AquaHideout_B2F_EventScript_MattNoticePlayer::
	lockall
	setvar VAR_0x8008, LOCALID_AQUA_HIDEOUT_MATT
	playse SE_PIN
	applymovement VAR_0x8008, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	setvar VAR_TEMP_1, 1
	releaseall
	end

AquaHideout_B2F_EventScript_Matt::
	trainerbattle_single TRAINER_MATT, AquaHideout_B2F_Text_MattIntro, AquaHideout_B2F_Text_MattDefeat, AquaHideout_B2F_EventScript_SubmarineEscape
	msgbox AquaHideout_B2F_Text_MattPostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_B2F_EventScript_SubmarineEscape::
	setvar VAR_0x8008, LOCALID_AQUA_HIDEOUT_MATT
	setvar VAR_0x8009, LOCALID_AQUA_HIDEOUT_SUBMARINE
	applymovement VAR_0x8008, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 20
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	msgbox AquaHideout_B2F_Text_OurBossGotThroughHisPreparations, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_0x8008, Common_Movement_WalkInPlaceFasterLeft
	applymovement VAR_0x8009, AquaHideout_B2F_Movement_SumbarineDepartLeft
	waitmovement 0
	removeobject VAR_0x8009
	delay 20
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	msgbox AquaHideout_B2F_Text_MattPostBattle, MSGBOX_DEFAULT
	setflag FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE
	setflag FLAG_HIDE_LILYCOVE_CITY_AQUA_GRUNTS
	release
	end

AquaHideout_B2F_Movement_SumbarineDepartLeft:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

@ Unused
AquaHideout_B2F_Movement_SumbarineDepartRight:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

AquaHideout_B2F_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_4, AquaHideout_B2F_Text_Grunt4Intro, AquaHideout_B2F_Text_Grunt4Defeat, AquaHideout_B2F_EventScript_Grunt4Defeated
	msgbox AquaHideout_B2F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_EventScript_Grunt4Defeated::
	msgbox AquaHideout_B2F_Text_Grunt4PostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_B2F_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_6, AquaHideout_B2F_Text_Grunt6Intro, AquaHideout_B2F_Text_Grunt6Defeat
	msgbox AquaHideout_B2F_Text_Grunt6PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_8, AquaHideout_B2F_Text_Grunt8Intro, AquaHideout_B2F_Text_Grunt8Defeat
	msgbox AquaHideout_B2F_Text_Grunt8PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_Text_MattIntro:
	.string "Jejeje…\p"
	.string "¿Ya has llegado?\n"
	.string "¡Te hemos subestimado!\p"
	.string "¡Pero hasta aquí has llegado!\p"
	.string "Estoy muy por encima de los\n"
	.string "SOLDADOS que has visto hasta ahora.\p"
	.string "No estoy ganando tiempo.\n"
	.string "¡Voy a hacerte polvo!$"

AquaHideout_B2F_Text_MattDefeat:
	.string "Jejeje…\n"
	.string "Así que yo también he perdido…$"

AquaHideout_B2F_Text_OurBossGotThroughHisPreparations:
	.string "¡Jejeje!\p"
	.string "¡Mientras jugaba contigo, nuestro\n"
	.string "JEFE ha terminado los preparativos!$"

AquaHideout_B2F_Text_MattPostBattle:
	.string "¡Jejeje!\p"
	.string "¡Nuestro JEFE ya va camino de una\n"
	.string "cueva bajo el mar!\p"
	.string "Si vas a perseguirlo, más te vale\n"
	.string "buscar en el ancho mar que hay más\l"
	.string "allá de CALAGUA.\p"
	.string "¿Pero lo encontrarás?\n"
	.string "¡Jejeje!$"

AquaHideout_B2F_Text_Grunt4Intro:
	.string "¡Juajuajua, me he cansado de esperar!\n"
	.string "¡Tú también me debes un combate!$"

AquaHideout_B2F_Text_Grunt4Defeat:
	.string "Cansado de esperar…\n"
	.string "Y encima pierdo…$"

AquaHideout_B2F_Text_Grunt4PostBattle:
	.string "JEFE…\n"
	.string "¿Con esto basta?$"

AquaHideout_B2F_Text_Grunt6Intro:
	.string "¡Las baldosas de teletransporte, el\n"
	.string "orgullo de la GUARIDA!\p"
	.string "No tienes ni idea de dónde estás,\n"
	.string "¿a que no?\p"
	.string "¡Confundir y cansar al enemigo, y\n"
	.string "luego darle el golpe! ¡Ese es el plan!$"

AquaHideout_B2F_Text_Grunt6Defeat:
	.string "¿Qué te pasa?\n"
	.string "¡No te cansas nada!$"

AquaHideout_B2F_Text_Grunt6PostBattle:
	.string "Eso me recuerda… No me acuerdo de\n"
	.string "dónde puse la MASTER BALL.\p"
	.string "Si no la vigilo, el JEFE me va a\n"
	.string "echar la bronca…$"

AquaHideout_B2F_Text_Grunt8Intro:
	.string "Cuando entré en el EQUIPO AQUA, lo\n"
	.string "primero que tuve que aprender fue cómo\l"
	.string "se conectan las baldosas.$"

AquaHideout_B2F_Text_Grunt8Defeat:
	.string "Estaba muy ocupado pensando en las\n"
	.string "baldosas…$"

AquaHideout_B2F_Text_Grunt8PostBattle:
	.string "Tendré que aprender a combatir mejor…$"
