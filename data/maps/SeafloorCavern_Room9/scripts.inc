SeafloorCavern_Room9_MapScripts::
	.byte 0

SeafloorCavern_Room9_EventScript_ArchieAwakenKyogre::
	lockall
	setvar VAR_0x8004, LOCALID_SEAFLOOR_CAVERN_ARCHIE
	setvar VAR_0x8005, LOCALID_SEAFLOOR_CAVERN_MAXIE
	setvar VAR_0x8006, LOCALID_SEAFLOOR_CAVERN_GRUNT_1
	setvar VAR_0x8007, LOCALID_SEAFLOOR_CAVERN_GRUNT_2
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	applymovement LOCALID_PLAYER, SeafloorCavern_Room9_Movement_Delay32
	waitmovement 0
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	msgbox SeafloorCavern_Room9_Text_ArchieHoldItRightThere, MSGBOX_DEFAULT
	closemessage
	addobject VAR_0x8004
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement VAR_0x8004, SeafloorCavern_Room9_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieSoItWasYou, MSGBOX_DEFAULT
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieBeholdKyogre, MSGBOX_DEFAULT
	applymovement VAR_0x8004, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieYouMustDisappear, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ARCHIE, SeafloorCavern_Room9_Text_ArchieDefeat
	msgbox SeafloorCavern_Room9_Text_ArchieWithThisRedOrb, MSGBOX_DEFAULT
	setweather WEATHER_NONE
	doweather
	special Script_FadeOutMapMusic
	msgbox SeafloorCavern_Room9_Text_RedOrbShinesByItself, MSGBOX_DEFAULT
	special WaitWeather
	setvar VAR_RESULT, 1
	playse SE_M_DETECT
	dofieldeffectsparkle 16, 42, 0
	waitfieldeffect FLDEFF_SPARKLE
	closemessage
	setvar VAR_RESULT, 0
	playfanfare MUS_AWAKEN_LEGEND
	playse SE_ORB
	special DoOrbEffect
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 150
	removeobject LOCALID_SEAFLOOR_CAVERN_KYOGRE_SLEEPING
	addobject LOCALID_SEAFLOOR_CAVERN_KYOGRE
	waitstate
	delay 60
	applymovement LOCALID_SEAFLOOR_CAVERN_KYOGRE, SeafloorCavern_Room9_Movement_KyogreApproach
	waitmovement 0
	special FadeOutOrbEffect
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	applymovement LOCALID_SEAFLOOR_CAVERN_KYOGRE, SeafloorCavern_Room9_Movement_KyogreExit
	waitmovement 0
	removeobject LOCALID_SEAFLOOR_CAVERN_KYOGRE
	delay 4
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	delay 30
	setvar VAR_0x8004, LOCALID_SEAFLOOR_CAVERN_ARCHIE
	setvar VAR_0x8005, LOCALID_SEAFLOOR_CAVERN_MAXIE
	setvar VAR_0x8006, LOCALID_SEAFLOOR_CAVERN_GRUNT_1
	setvar VAR_0x8007, LOCALID_SEAFLOOR_CAVERN_GRUNT_2
	msgbox SeafloorCavern_Room9_Text_ArchieWhereDidKyogreGo, MSGBOX_DEFAULT
	playse SE_PC_LOGIN
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieAMessageFromOutside, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_0x8004, SeafloorCavern_Room9_Movement_ArchieListenMessage
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieWhatRainingTooHard, MSGBOX_DEFAULT
	closemessage
	playse SE_PC_OFF
	delay 20
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieWhyDidKyogreDisappear, MSGBOX_DEFAULT
	closemessage
	addobject VAR_0x8005
	addobject VAR_0x8006
	addobject VAR_0x8007
	applymovement VAR_0x8007, SeafloorCavern_Room9_Movement_MagmaGruntArrive
	applymovement VAR_0x8006, SeafloorCavern_Room9_Movement_MagmaGruntArrive
	applymovement VAR_0x8005, SeafloorCavern_Room9_Movement_MaxieArrive
	waitmovement 0
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_MaxieWhatHaveYouWrought, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement VAR_0x8004, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x8004, Common_Movement_Delay48
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieDontGetAllHighAndMighty, MSGBOX_DEFAULT
	msgbox SeafloorCavern_Room9_Text_MaxieWeDontHaveTimeToArgue, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_0x8005, SeafloorCavern_Room9_Movement_MaxieExit
	applymovement VAR_0x8004, SeafloorCavern_Room9_Movement_ArchieExit
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_MaxieComeOnPlayer, MSGBOX_DEFAULT
	setvar VAR_ROUTE128_STATE, 1
	setvar VAR_SOOTOPOLIS_CITY_STATE, 1
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_STEVEN
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_ARCHIE
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_MAXIE
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_RESIDENTS
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_GROUDON
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_KYOGRE
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_MAN_1
	setflag FLAG_LEGENDARIES_IN_SOOTOPOLIS
	clearflag FLAG_HIDE_ROUTE_128_ARCHIE
	clearflag FLAG_HIDE_ROUTE_128_MAXIE
	setflag FLAG_SYS_WEATHER_CTRL
	setflag FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN
	setflag FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_STEVEN
	setvar VAR_STEVENS_HOUSE_STATE, 2
	setvar VAR_SEAFLOOR_CAVERN_STATE, 1
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_ARCHIE
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_MAXIE
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_MAGMA_GRUNTS
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_KYOGRE
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_AQUA_GRUNTS
	setflag FLAG_HIDE_MAP_NAME_POPUP
	warp MAP_ROUTE128, 38, 22
	waitstate
	releaseall
	end

SeafloorCavern_Room9_Movement_ArchieApproachPlayer:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SeafloorCavern_Room9_Movement_Unused1:
	walk_left
	walk_left
	step_end

SeafloorCavern_Room9_Movement_ArchieListenMessage:
	walk_left
	delay_16
	step_end

SeafloorCavern_Room9_Movement_Unused2:
	walk_right
	step_end

SeafloorCavern_Room9_Movement_ArchieExit:
	face_up
	lock_facing_direction
	walk_down
	unlock_facing_direction
	walk_in_place_faster_right
	step_end

SeafloorCavern_Room9_Movement_KyogreApproach:
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

SeafloorCavern_Room9_Movement_KyogreExit:
	slide_up
	slide_up
	step_end

SeafloorCavern_Room9_Movement_MaxieArrive:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

SeafloorCavern_Room9_Movement_MaxieExit:
	walk_right
	walk_right
	step_end

SeafloorCavern_Room9_Movement_MagmaGruntArrive:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

SeafloorCavern_Room9_Movement_Delay32:
	delay_16
	delay_16
	step_end

SeafloorCavern_Room9_Text_ArchieHoldItRightThere:
	.string "AQUILES: Alto ahí.$"

SeafloorCavern_Room9_Text_ArchieSoItWasYou:
	.string "AQUILES: Fufufu…\n"
	.string "Así que, al final, eras tú.$"

SeafloorCavern_Room9_Text_ArchieBeholdKyogre:
	.string "AQUILES: ¡Contempla!\p"
	.string "¡Mira qué bello es el POKéMON ancestral\n"
	.string "KYOGRE mientras duerme!\p"
	.string "He esperado tanto tiempo a que\n"
	.string "llegara este día…$"

SeafloorCavern_Room9_Text_ArchieYouMustDisappear:
	.string "AQUILES: Me sorprende que hayas\n"
	.string "conseguido seguirme hasta aquí.\p"
	.string "Pero se acabó.\p"
	.string "¡Para que se cumpla mi sueño, tienes\n"
	.string "que desaparecer!$"

SeafloorCavern_Room9_Text_ArchieDefeat:
	.string "¡¿Qué?!\n"
	.string "¡¿He perdido contra una simple\l"
	.string "criatura?!$"

SeafloorCavern_Room9_Text_ArchieWithThisRedOrb:
	.string "AQUILES: Fufufu…\p"
	.string "Te felicito. Tengo que reconocer\n"
	.string "que tienes un talento enorme.\p"
	.string "¡Pero!\n"
	.string "¡Tengo esto en mi poder!\p"
	.string "¡Con este PRISMA ROJO puedo hacer\n"
	.string "que KYOGRE…!$"

SeafloorCavern_Room9_Text_RedOrbShinesByItself:
	.string "¡De repente, el PRISMA ROJO ha\n"
	.string "empezado a brillar solo!$"

SeafloorCavern_Room9_Text_ArchieWhereDidKyogreGo:
	.string "AQUILES: ¡¿Qué?!\p"
	.string "No he hecho nada.\n"
	.string "¿Por qué el PRISMA ROJO…?\p"
	.string "¿Adónde ha ido KYOGRE?$"

SeafloorCavern_Room9_Text_ArchieAMessageFromOutside:
	.string "AQUILES: ¿Mm? Es un mensaje de\n"
	.string "nuestros miembros de fuera…$"

SeafloorCavern_Room9_Text_ArchieWhatRainingTooHard:
	.string "AQUILES: Sí, ¿qué pasa?\p"
	.string "Mm…\n"
	.string "¿Que llueve muchísimo?\p"
	.string "Bien… Eso es lo que tenía que pasar.\n"
	.string "Para eso despertamos a KYOGRE, para\l"
	.string "cumplir la visión del EQUIPO AQUA de\l"
	.string "expandir el mar.\p"
	.string "¡¿Qué?!\p"
	.string "¿Que llueve mucho más de lo previsto?\n"
	.string "¿Que estáis en peligro?\p"
	.string "No puede ser…\n"
	.string "Eso es imposible…\p"
	.string "¡Mantened la posición y vigilad\n"
	.string "la situación!$"

SeafloorCavern_Room9_Text_ArchieWhyDidKyogreDisappear:
	.string "AQUILES: Aquí pasa algo raro…\p"
	.string "El PRISMA ROJO tiene que despertar\n"
	.string "y controlar a KYOGRE…\p"
	.string "Pero… ¿Por qué?\n"
	.string "¿Por qué ha desaparecido KYOGRE?\p"
	.string "¡¿Por qué?!$"

SeafloorCavern_Room9_Text_MaxieWhatHaveYouWrought:
	.string "MAGNO: ¿Qué has hecho?\p"
	.string "AQUILES… Al final has despertado a\n"
	.string "KYOGRE, ¿verdad?\p"
	.string "¿Qué le pasará al mundo si este\n"
	.string "diluvio no para nunca?\p"
	.string "La tierra firme se hundirá en un mar\n"
	.string "cada vez más profundo…$"

SeafloorCavern_Room9_Text_ArchieDontGetAllHighAndMighty:
	.string "AQUILES: ¡¿Q-qué?!\n"
	.string "¡No me vengas con aires de grandeza!\p"
	.string "¿No fuisteis vosotros, el EQUIPO MAGMA,\n"
	.string "los que enfurecisteis a GROUDON?\p"
	.string "Mientras tenga este PRISMA ROJO,\n"
	.string "debería poder controlar a KYOGRE…\p"
	.string "Debería poder controlarlo…$"

SeafloorCavern_Room9_Text_MaxieWeDontHaveTimeToArgue:
	.string "MAGNO: ¡No tenemos tiempo para\n"
	.string "discutir aquí!\p"
	.string "¡Sal fuera y míralo con tus ojos!\p"
	.string "¡Mira si lo que has hecho es el mundo\n"
	.string "que queríamos!$"

SeafloorCavern_Room9_Text_MaxieComeOnPlayer:
	.string "MAGNO: {PLAYER}, vamos, ¡tú también\n"
	.string "tienes que salir de aquí!$"
