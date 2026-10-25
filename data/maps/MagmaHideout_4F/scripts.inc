MagmaHideout_4F_MapScripts::
	.byte 0

MagmaHideout_4F_EventScript_Maxie::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox MagmaHideout_4F_Text_MaxieAwakenGroudon, MSGBOX_DEFAULT
	closemessage
	delay 20
	setvar VAR_RESULT, 1
	playse SE_M_DETECT
	dofieldeffectsparkle 18, 42, 0
	waitfieldeffect FLDEFF_SPARKLE
	setvar VAR_RESULT, 1
	playfanfare MUS_AWAKEN_LEGEND
	playse SE_ORB
	special DoOrbEffect
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 150
	removeobject LOCALID_MAGMA_HIDEOUT_4F_GROUDON_SLEEPING
	addobject LOCALID_MAGMA_HIDEOUT_4F_GROUDON
	waitstate
	delay 60
	applymovement LOCALID_MAGMA_HIDEOUT_4F_GROUDON, MagmaHideout_4F_Movement_GroudonApproach
	waitmovement 0
	special FadeOutOrbEffect
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	applymovement LOCALID_MAGMA_HIDEOUT_4F_GROUDON, MagmaHideout_4F_Movement_GroudonExit
	waitmovement 0
	removeobject LOCALID_MAGMA_HIDEOUT_4F_GROUDON
	delay 4
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	delay 30
	applymovement LOCALID_MAGMA_HIDEOUT_4F_MAXIE, MagmaHideout_4F_Movement_MaxieLookAround
	waitmovement 0
	msgbox MagmaHideout_4F_Text_MaxieGroudonWhatsWrong, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_MAGMA_HIDEOUT_4F_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MagmaHideout_4F_Text_MaxieOhItWasYou, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_MAXIE_MAGMA_HIDEOUT, MagmaHideout_4F_Text_MaxieDefeat
	msgbox MagmaHideout_4F_Text_MaxieImGoingAfterGroudon, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_SLATEPORT_CITY_CAPTAIN_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_GABBY_AND_TY
	setvar VAR_SLATEPORT_CITY_STATE, 1
	setflag FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT
	setvar VAR_SLATEPORT_HARBOR_STATE, 1
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MAGMA_HIDEOUT_4F_MAXIE
	removeobject LOCALID_MAGMA_HIDEOUT_4F_GRUNT_1
	removeobject LOCALID_MAGMA_HIDEOUT_4F_GRUNT_2
	removeobject LOCALID_MAGMA_HIDEOUT_4F_GRUNT_3
	removeobject LOCALID_MAGMA_HIDEOUT_4F_TABITHA
	setflag FLAG_HIDE_MAGMA_HIDEOUT_GRUNTS
	fadescreen FADE_FROM_BLACK
	releaseall
	end

MagmaHideout_4F_Movement_GroudonApproach:
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	step_end

MagmaHideout_4F_Movement_GroudonExit:
	slide_up
	slide_up
	step_end

MagmaHideout_4F_Movement_MaxieLookAround:
	face_left
	delay_16
	face_right
	delay_16
	face_left
	delay_16
	face_right
	delay_16
	face_up
	delay_16
	delay_16
	step_end

MagmaHideout_4F_EventScript_Grunt11::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_11, MagmaHideout_4F_Text_Grunt11Intro, MagmaHideout_4F_Text_Grunt11Defeat
	msgbox MagmaHideout_4F_Text_Grunt11PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Grunt12::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_12, MagmaHideout_4F_Text_Grunt12Intro, MagmaHideout_4F_Text_Grunt12Defeat
	msgbox MagmaHideout_4F_Text_Grunt12PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Grunt13::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_13, MagmaHideout_4F_Text_Grunt13Intro, MagmaHideout_4F_Text_Grunt13Defeat
	msgbox MagmaHideout_4F_Text_Grunt13PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Tabitha::
	trainerbattle_single TRAINER_TABITHA_MAGMA_HIDEOUT, MagmaHideout_4F_Text_TabithaIntro, MagmaHideout_4F_Text_TabithaDefeat
	msgbox MagmaHideout_4F_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_Text_Grunt11Intro:
	.string "Yo también quiero ver a GROUDON, pero\n"
	.string "no me dejan verle ni la cola…\p"
	.string "Me frustra muchísimo.\p"
	.string "¡Ay, no!\n"
	.string "¡Se me ha escapado lo de GROUDON!$"

MagmaHideout_4F_Text_Grunt11Defeat:
	.string "Supongo que es imposible ganar sin\n"
	.string "la mente tranquila…$"

MagmaHideout_4F_Text_Grunt11PostBattle:
	.string "¿GROUDON tendrá cola siquiera?$"

MagmaHideout_4F_Text_Grunt12Intro:
	.string "¡Fujajaja!\n"
	.string "¡Pronto! ¡Muy pronto!\l"
	.string "¡Cumpliremos nuestro gran objetivo!$"

MagmaHideout_4F_Text_Grunt12Defeat:
	.string "Grrr…\n"
	.string "¿Llego hasta aquí y ahora esto?$"

MagmaHideout_4F_Text_Grunt12PostBattle:
	.string "¡Señor MAGNO!\n"
	.string "¡Un intruso va hacia usted!$"

MagmaHideout_4F_Text_Grunt13Intro:
	.string "¡Aún no has terminado!\n"
	.string "¡No vas a pasar tan fácilmente!$"

MagmaHideout_4F_Text_Grunt13Defeat:
	.string "¿Tan fácil era tumbarme?$"

MagmaHideout_4F_Text_Grunt13PostBattle:
	.string "V-venga, otro combate…$"

MagmaHideout_4F_Text_TabithaIntro:
	.string "¡Jejeje!\n"
	.string "¡Has llegado hasta aquí, te lo diré!\p"
	.string "¡Así es!\n"
	.string "¡Ahí delante duerme GROUDON!\p"
	.string "¡MAGNO acaba de ir a ver a GROUDON\n"
	.string "hace unos segundos!\p"
	.string "¡Va a despertar muy pronto!\n"
	.string "¡Jeje! ¡Jejeje!$"

MagmaHideout_4F_Text_TabithaDefeat:
	.string "Otra vez derribado…\n"
	.string "Jeje…$"

MagmaHideout_4F_Text_TabithaPostBattle:
	.string "… Y mientras perdías el tiempo conmigo,\n"
	.string "MAGNO ya habrá despertado a GROUDON…$"

MagmaHideout_4F_Text_MaxieAwakenGroudon:
	.string "MAGNO: GROUDON…\p"
	.string "Nada podía despertarte de tu sueño\n"
	.string "bañado en magma…\p"
	.string "Este PRISMA AZUL es lo que buscabas.\n"
	.string "¿Verdad?\p"
	.string "Te he traído el PRISMA AZUL.\n"
	.string "¡Que su brillo te despierte!\p"
	.string "Y muéstrame…\n"
	.string "¡Muéstrame todo tu poder!$"

MagmaHideout_4F_Text_MaxieGroudonWhatsWrong:
	.string "MAGNO: ¡GROUDON!\n"
	.string "¿Qué te pasa?\p"
	.string "¿No era el PRISMA AZUL la clave?\p"
	.string "¡GROUDON!\n"
	.string "¿Adónde te has ido…?$"

MagmaHideout_4F_Text_MaxieOhItWasYou:
	.string "MAGNO: ¿Oh, así que eras tú?\p"
	.string "Te he visto husmear por aquí y por\n"
	.string "allá sin invitación…\p"
	.string "¡Ahora lo entiendo!\n"
	.string "¡Seguro que has hecho alguna trampa!$"

MagmaHideout_4F_Text_MaxieDefeat:
	.string "¿Cómo es que se te dan tan bien\n"
	.string "los POKéMON?$"

MagmaHideout_4F_Text_MaxieImGoingAfterGroudon:
	.string "MAGNO: Debe de haber algún motivo por\n"
	.string "el que GROUDON ha huido…\p"
	.string "Eso es lo que quieres decir,\n"
	.string "¿verdad?\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Hmpf…\n"
	.string "¿Crees que no lo sabía?\p"
	.string "Sin GROUDON, este maldito volcán ya\n"
	.string "no nos sirve.\p"
	.string "Voy a ir tras GROUDON, así que aquí\n"
	.string "se separan nuestros caminos.$"
