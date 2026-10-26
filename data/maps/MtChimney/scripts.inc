MtChimney_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MtChimney_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, MtChimney_OnTransition
	.byte 0

MtChimney_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 1
	end

MtChimney_OnResume:
	setstepcallback STEP_CB_ASH
	end

MtChimney_EventScript_Archie::
	lock
	faceplayer
	call_if_unset FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieGoStopTeamMagma
	call_if_set FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieBusyFighting
	closemessage
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_EVIL_LEADER_PLEASE_STOP
	release
	end

MtChimney_EventScript_ArchieGoStopTeamMagma::
	msgbox MtChimney_Text_ArchieGoStopTeamMagma, MSGBOX_DEFAULT
	return

MtChimney_EventScript_ArchieBusyFighting::
	msgbox MtChimney_Text_ArchieIHaveMyHandsFull, MSGBOX_DEFAULT
	return

MtChimney_EventScript_Maxie::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox MtChimney_Text_MeteoriteWillActivateVolcano, MSGBOX_DEFAULT
	applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_Delay48
	waitmovement 0
	msgbox MtChimney_Text_MaxieIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MAXIE_MT_CHIMNEY, MtChimney_Text_MaxieDefeat
	msgbox MtChimney_Text_MaxieYouHaventSeenLastOfMagma, MSGBOX_DEFAULT
	closemessage
	delay 30
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MT_CHIMNEY_MAXIE
	removeobject LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1
	removeobject LOCALID_MT_CHIMNEY_TABITHA
	removeobject LOCALID_MT_CHIMNEY_MAGMA_GRUNT_2
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_MAGMA
	fadescreenswapbuffers FADE_FROM_BLACK
	setobjectxyperm LOCALID_MT_CHIMNEY_ARCHIE, 10, 12
	addobject LOCALID_MT_CHIMNEY_ARCHIE
	call_if_eq VAR_FACING, DIR_EAST, MtChimney_EventScript_ArchieApproachPlayerEast
	call_if_eq VAR_FACING, DIR_NORTH, MtChimney_EventScript_ArchieApproachPlayerNorth
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MtChimney_Text_ArchieThankYou, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_EAST, MtChimney_EventScript_ArchieExitEast
	call_if_eq VAR_FACING, DIR_NORTH, MtChimney_EventScript_ArchieExitNorth
	removeobject LOCALID_MT_CHIMNEY_ARCHIE
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_AQUA
	setflag FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY
	clearflag FLAG_HIDE_FALLARBOR_HOUSE_PROF_COZMO
	setflag FLAG_HIDE_METEOR_FALLS_1F_1R_COZMO
	clearflag FLAG_HIDE_MT_CHIMNEY_LAVA_COOKIE_LADY
	releaseall
	end

MtChimney_EventScript_ArchieApproachPlayerEast::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieApproachPlayerEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieApproachPlayerNorth::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieApproachPlayerNorth
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitEast::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieExitEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitNorth::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieExitNorth
	waitmovement 0
	return

MtChimney_EventScript_LavaCookieLady::
	lock
	faceplayer
	showmoneybox 0, 0
	msgbox MtChimney_Text_LavaCookiesJust200, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_DeclineLavaCookie
	checkmoney 200
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_NotEnoughMoney
	msgbox MtChimney_Text_ThankYouDear, MSGBOX_DEFAULT
	checkitemspace ITEM_LAVA_COOKIE
	call_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RemoveMoney
.if OW_SHOW_ITEM_DESCRIPTIONS == OW_ITEM_DESCRIPTIONS_OFF
	giveitem ITEM_LAVA_COOKIE
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_BagIsFull
	hidemoneybox
	release
	end

MtChimney_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end
.else
	hidemoneybox
	giveitem ITEM_LAVA_COOKIE
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_BagIsFull
	release
	end

MtChimney_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end
.endif @ OW_SHOW_ITEM_DESCRIPTIONS


MtChimney_EventScript_RemoveMoney::
	removemoney 200
	updatemoneybox
	return

MtChimney_EventScript_DeclineLavaCookie::
	msgbox MtChimney_Text_OhFineThen, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_EventScript_NotEnoughMoney::
	msgbox MtChimney_Text_YouveNotGotTheMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_Movement_ArchieApproachPlayerEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	step_end

MtChimney_Movement_ArchieExitEast:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_ArchieApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

MtChimney_Movement_ArchieExitNorth:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused2:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused3:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused4:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused5:
	delay_16
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused6:
	delay_16
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused7:
	delay_16
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused8:
	delay_16
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

MtChimney_Movement_Unused9:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused10:
	walk_down
	step_end

MtChimney_Movement_Unused11:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused12:
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused13:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused14:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	face_right
	step_end

MtChimney_Movement_Unused15:
	walk_left
	walk_in_place_faster_right
	delay_16
	step_end

MtChimney_EventScript_BusyAquaGrunt1::
	msgbox MtChimney_Text_MagmaOutnumbersUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt2::
	msgbox MtChimney_Text_LessHabitatForWaterPokemon, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt3::
	msgbox MtChimney_Text_MagmasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_Tabitha::
	trainerbattle_single TRAINER_TABITHA_MT_CHIMNEY, MtChimney_Text_TabithaIntro, MtChimney_Text_TabithaDefeat
	msgbox MtChimney_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_2, MtChimney_Text_Grunt2Intro, MtChimney_Text_Grunt2Defeat
	msgbox MtChimney_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_BusyMagmaGrunt1::
	msgbox MtChimney_Text_TeamAquaAlwaysMessingWithPlans, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt2::
	msgbox MtChimney_Text_MeteoritesPackAmazingPower, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt3::
	msgbox MtChimney_Text_YouBetterNotMessWithUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt4::
	msgbox MtChimney_Text_AquasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt5::
	msgbox MtChimney_Text_DouseThemInFire, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt6::
	msgbox MtChimney_Text_KeepMakingMoreLand, MSGBOX_SIGN
	end

MtChimney_EventScript_MagmaPoochyena::
	msgbox MtChimney_Text_Bufoh, MSGBOX_SIGN
	end

MtChimney_EventScript_AquaPoochyena::
	msgbox MtChimney_Text_Bushaa, MSGBOX_SIGN
	end

MtChimney_EventScript_MeteoriteMachine::
	lockall
	goto_if_unset FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, MtChimney_EventScript_MachineOn
	goto_if_set FLAG_RECEIVED_METEORITE, MtChimney_EventScript_MachineOff
	msgbox MtChimney_Text_RemoveTheMeteorite, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_LeaveMeteoriteAlone
	msgbox MtChimney_Text_PlayerRemovedMeteorite, MSGBOX_DEFAULT
	giveitem ITEM_METEORITE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_METEORITE
	releaseall
	end

MtChimney_EventScript_LeaveMeteoriteAlone::
	msgbox MtChimney_Text_PlayerLeftMeteorite, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOff::
	msgbox MtChimney_Text_MachineMakesNoResponse, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOn::
	msgbox MtChimney_Text_MeteoriteFittedOnMachine, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_RouteSign::
	msgbox MtChimney_Text_RouteSign, MSGBOX_SIGN
	end

MtChimney_EventScript_Shelby::
	trainerbattle_single TRAINER_SHELBY_1, MtChimney_Text_ShelbyIntro, MtChimney_Text_ShelbyDefeat, MtChimney_EventScript_DefeatedShelby
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RematchShelby
	msgbox MtChimney_Text_ShelbyPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_DefeatedShelby::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_ShelbyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SHELBY_1
	release
	end

MtChimney_EventScript_RematchShelby::
	trainerbattle_rematch TRAINER_SHELBY_1, MtChimney_Text_ShelbyRematchIntro, MtChimney_Text_ShelbyRematchDefeat
	msgbox MtChimney_Text_ShelbyPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Melissa::
	trainerbattle_single TRAINER_MELISSA, MtChimney_Text_MelissaIntro, MtChimney_Text_MelissaDefeat
	msgbox MtChimney_Text_MelissaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sheila::
	trainerbattle_single TRAINER_SHEILA, MtChimney_Text_SheilaIntro, MtChimney_Text_SheilaDefeat
	msgbox MtChimney_Text_SheilaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Shirley::
	trainerbattle_single TRAINER_SHIRLEY, MtChimney_Text_ShirleyIntro, MtChimney_Text_ShirleyDefeat
	msgbox MtChimney_Text_ShirleyPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_1, MtChimney_Text_Grunt1Intro, MtChimney_Text_Grunt1Defeat
	msgbox MtChimney_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sawyer::
	trainerbattle_single TRAINER_SAWYER_1, MtChimney_Text_SawyerIntro, MtChimney_Text_SawyerDefeat, MtChimney_EventScript_SawyerDefeated
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_SawyerRematch
	msgbox MtChimney_Text_SawyerPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_SawyerDefeated::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_SawyerRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SAWYER_1
	release
	end

MtChimney_EventScript_SawyerRematch::
	trainerbattle_rematch TRAINER_SAWYER_1, MtChimney_Text_SawyerRematchIntro, MtChimney_Text_SawyerRematchDefeat
	msgbox MtChimney_Text_SawyerPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_Text_MeteoriteWillActivateVolcano:
	.string "El poder del METEORITO…\p"
	.string "Si lo amplificamos con esta máquina,\n"
	.string "la actividad volcánica del MONTE\l"
	.string "CENIZO aumentará al instante…\p"
	.string "Su energía crecerá en lo más hondo\n"
	.string "del cráter y…\l"
	.string "Fufufu…$"

MtChimney_Text_MaxieIntro:
	.string "MAGNO: ¿Mm?\n"
	.string "¿Quién eres?\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "He oído a AQUILES quejarse de una\n"
	.string "criatura que se mete en los asuntos\l"
	.string "del EQUIPO AQUA.\p"
	.string "Debía de referirse a ti.\p"
	.string "¡Hmpf! ¿Así que piensas meterte con\n"
	.string "nosotros, el EQUIPO MAGMA?\p"
	.string "Escúchame bien.\n"
	.string "Hace mucho, los seres vivos usaban\l"
	.string "la tierra para vivir y crecer.\p"
	.string "¡Por eso la tierra es lo más\n"
	.string "importante! ¡Es la cuna de todo!\p"
	.string "Por eso el EQUIPO MAGMA se dedica\n"
	.string "a expandir la tierra firme.\p"
	.string "¡Por el progreso de la humanidad\n"
	.string "y de los POKéMON!\p"
	.string "Y para eso necesitamos el poder de\n"
	.string "lo que duerme en esta montaña…\p"
	.string "¡Oh! No hacía falta que supieras\n"
	.string "tanto.\p"
	.string "¡Pero da igual!\n"
	.string "Te enseñaré lo que pasa por meterse\l"
	.string "en nuestro gran plan.$"

MtChimney_Text_MaxieDefeat:
	.string "¡¿Qué?!\p"
	.string "¡¿A mí, a MAGNO, me han pillado\n"
	.string "desprevenido?!$"

MtChimney_Text_MaxieYouHaventSeenLastOfMagma:
	.string "MAGNO: Pero basta.\n"
	.string "Esta vez me retiro.\p"
	.string "Pero no creas que es lo último que\n"
	.string "verás del EQUIPO MAGMA.\p"
	.string "Fufufu…\p"
	.string "Aun sin el METEORITO, si conseguimos\n"
	.string "ese PRISMA… Fufufu…$"

MtChimney_Text_TabithaIntro:
	.string "¡Jejeje!\p"
	.string "¡Así que has llegado hasta aquí!\p"
	.string "¡Pero llegas tarde!\n"
	.string "¡Ya le he entregado al JEFE el\l"
	.string "METEORITO de las CATARATAS METEORO!$"

MtChimney_Text_TabithaDefeat:
	.string "Jejeje…\p"
	.string "Aunque haya perdido, si nuestro líder\n"
	.string "despierta a esa cosa…$"

MtChimney_Text_TabithaPostBattle:
	.string "¡JEFE, deprisa!\n"
	.string "¡Dale la energía del METEORITO!\p"
	.string "Jejeje…$"

MtChimney_Text_Grunt2Intro:
	.string "Los del EQUIPO MAGMA trabajamos duro\n"
	.string "por el bien de todos.\p"
	.string "O sea, si el poder de esa cosa crea\n"
	.string "más tierra, habrá más sitio para vivir.\p"
	.string "¡Todos serían felices!$"

MtChimney_Text_Grunt2Defeat:
	.string "¿Eh?\n"
	.string "¿Cómo que he perdido?$"

MtChimney_Text_Grunt2PostBattle:
	.string "Nuestro JEFE dice: “Hará feliz a todo\n"
	.string "el mundo”.\p"
	.string "Pero ¿por qué todos se empeñan en\n"
	.string "ponernos trabas?$"

MtChimney_Text_Grunt1Intro:
	.string "¡Si hubiera más tierra, podría tener\n"
	.string "una casa enorme para mí solo!\p"
	.string "¡La construiré sobre lava solidificada!$"

MtChimney_Text_Grunt1Defeat:
	.string "Mi sueño de una casa enorme…$"

MtChimney_Text_Grunt1PostBattle:
	.string "¡Alguien de tu edad debería estar\n"
	.string "chapoteando en las olas!$"

MtChimney_Text_TeamAquaAlwaysMessingWithPlans:
	.string "Ese EQUIPO AQUA tan pesado…\n"
	.string "¡Siempre nos fastidian los planes!$"

MtChimney_Text_MeteoritesPackAmazingPower:
	.string "¡Los METEORITOS tienen un poder\n"
	.string "increíble!$"

MtChimney_Text_YouBetterNotMessWithUs:
	.string "¡Más te vale no meterte con nosotros!\p"
	.string "¡Queremos despertar a esa cosa por\n"
	.string "el bien de todos!$"

MtChimney_Text_AquasNameSimilar:
	.string "¡Somos el EQUIPO MAGMA!\p"
	.string "¡Ellos son el EQUIPO AQUA!\p"
	.string "¡Me revienta que usen un nombre\n"
	.string "tan parecido al nuestro!$"

MtChimney_Text_DouseThemInFire:
	.string "¡Sí!\n"
	.string "¡Achicharradlos!$"

MtChimney_Text_KeepMakingMoreLand:
	.string "¡Vamos a seguir creando tierra!$"

MtChimney_Text_Bufoh:
	.string "¡Bufoh!$"

MtChimney_Text_ArchieGoStopTeamMagma:
	.string "AQUILES: ¡Grr, {PLAYER}!\n"
	.string "¡Debí suponer que aparecerías!\p"
	.string "¡Mira con tus ojos lo que traman esos\n"
	.string "fanáticos del EQUIPO MAGMA!\p"
	.string "¡Quieren meter en el volcán el poder\n"
	.string "del METEORITO que han robado!\p"
	.string "¡Si lo hacen, el volcán entrará\n"
	.string "en erupción!$"

MtChimney_Text_ArchieIHaveMyHandsFull:
	.string "AQUILES: Grrr…\p"
	.string "Quiero detener a MAGNO,\n"
	.string "¡pero no puedo!\p"
	.string "¡No mientras tenga que combatir con\n"
	.string "tres rivales a la vez!$"

MtChimney_Text_ArchieThankYou:
	.string "AQUILES: ¡{PLAYER}!\n"
	.string "¡Gracias!\p"
	.string "¡Con tu ayuda, hemos frustrado el\n"
	.string "plan destructivo del EQUIPO MAGMA!\p"
	.string "Pero… Tú…\n"
	.string "¿De qué lado estás?\p"
	.string "Bah, da igual.\p"
	.string "Seguiremos alerta y no dejaremos de\n"
	.string "perseguir al EQUIPO MAGMA.\p"
	.string "¡{PLAYER}, volveremos a vernos!$"

MtChimney_Text_MagmaOutnumbersUs:
	.string "Mecachis… ¡El EQUIPO MAGMA nos supera\n"
	.string "en número! ¡No podemos con ellos!$"

MtChimney_Text_LessHabitatForWaterPokemon:
	.string "¡Si amplían la tierra, habrá menos\n"
	.string "hábitats para los POKéMON de AGUA!$"

MtChimney_Text_MagmasNameSimilar:
	.string "¡Somos el EQUIPO AQUA!\p"
	.string "¡Ellos son el EQUIPO MAGMA!\p"
	.string "¡Me saca de quicio que usen un\n"
	.string "nombre tan confuso!$"

MtChimney_Text_Bushaa:
	.string "¡Bushaa!$"

MtChimney_Text_LavaCookiesJust200:
	.string "Las GALLETAS LAVA son típicas del\n"
	.string "MONTE CENIZO.\p"
	.string "Prueba una. Solo cuesta 200 ¥.$"

MtChimney_Text_ThankYouDear:
	.string "¡Gracias, cielo!$"

MtChimney_Text_YouveNotGotTheMoney:
	.string "Ay, cielo. No puedes comprar nada\n"
	.string "si no tienes dinero.$"

MtChimney_Text_OhFineThen:
	.string "Bueno, como quieras.$"

MtChimney_Text_MeteoriteFittedOnMachine:
	.string "Hay un METEORITO colocado en una\n"
	.string "máquina misteriosa…\p"
	.string "Parece que la máquina está cargando\n"
	.string "energía en el METEORITO.$"

MtChimney_Text_RemoveTheMeteorite:
	.string "Hay un METEORITO colocado en una\n"
	.string "máquina misteriosa…\p"
	.string "¿Quieres quitar el METEORITO?$"

MtChimney_Text_PlayerRemovedMeteorite:
	.string "{PLAYER} ha quitado el METEORITO de\n"
	.string "la máquina misteriosa.$"

MtChimney_Text_PlayerLeftMeteorite:
	.string "{PLAYER} ha dejado el METEORITO\n"
	.string "donde estaba.$"

MtChimney_Text_MachineMakesNoResponse:
	.string "Esta máquina misteriosa…\n"
	.string "No responde a nada.$"

MtChimney_Text_RouteSign:
	.string "{DOWN_ARROW} CAMINO ESCABROSO\n"
	.string "HACIA PUEBLO LAVACALDA$"

MtChimney_Text_ShelbyIntro:
	.string "He estado en las aguas termales\n"
	.string "y he descansado los huesos.\l"
	.string "¡Ahora mismo me siento fuerte!$"

MtChimney_Text_ShelbyDefeat:
	.string "¡Madre mía!\n"
	.string "¡Pero qué maravilla!$"

MtChimney_Text_ShelbyPostBattle:
	.string "Vaya, vaya, he perdido. Ya no puedo\n"
	.string "llamarme EXPERTA, ¿verdad?$"

MtChimney_Text_ShelbyRegister:
	.string "Gracias, criatura. Ha sido divertido,\n"
	.string "como combatir con mis nietos.\p"
	.string "Vuelve a verme para la revancha,\n"
	.string "por favor.$"

MtChimney_Text_ShelbyRematchIntro:
	.string "Si unes tu corazón con el de tus\n"
	.string "POKéMON, podrás conseguir\l"
	.string "grandes cosas.$"

MtChimney_Text_ShelbyRematchDefeat:
	.string "¡Madre mía!\n"
	.string "¡Pero qué maravilla!$"

MtChimney_Text_ShelbyPostRematch:
	.string "Quizá tu corazón se haya unido\n"
	.string "con el de tus POKéMON.$"

MtChimney_Text_MelissaIntro:
	.string "Llevo el fuego dentro, cariño.\n"
	.string "¡No lo aguanto! ¡Tengo que combatir!$"

MtChimney_Text_MelissaDefeat:
	.string "¡Uh, qué combate más abrasador!$"

MtChimney_Text_MelissaPostBattle:
	.string "¡El calor del MONTE CENIZO me\n"
	.string "enciende, cariño!$"

MtChimney_Text_SheilaIntro:
	.string "Por fin he llegado al MONTE CENIZO.\n"
	.string "¡Quiero que mis POKéMON combatan!$"

MtChimney_Text_SheilaDefeat:
	.string "Tu forma de combatir…\n"
	.string "¡Es como una erupción del MONTE CENIZO!$"

MtChimney_Text_SheilaPostBattle:
	.string "Como te decía, por fin he llegado\n"
	.string "al MONTE CENIZO. Sería una pena\l"
	.string "solo hacer turismo…\p"
	.string "Quiero combatir un poco y comprar\n"
	.string "GALLETAS de recuerdo.$"

MtChimney_Text_ShirleyIntro:
	.string "¡Desde que me bañé en las aguas\n"
	.string "termales me siento genial!\l"
	.string "¡Seguro que gano!$"

MtChimney_Text_ShirleyDefeat:
	.string "¡Ay!\n"
	.string "Me está entrando frío al salir del agua.$"

MtChimney_Text_ShirleyPostBattle:
	.string "Tendré que darme otro baño en las\n"
	.string "aguas termales. ¿Te vienes?\p"
	.string "¡Es broma!$"

MtChimney_Text_SawyerIntro:
	.string "¡Qué montaña tan estupenda! ¡Llena de\n"
	.string "gente ardiente para hacer compañía!$"

MtChimney_Text_SawyerDefeat:
	.string "¡Oh, tú también echas chispas!$"

MtChimney_Text_SawyerPostBattle:
	.string "¡Creo que necesito un baño en las\n"
	.string "aguas termales de LAVACALDA!$"

MtChimney_Text_SawyerRegister:
	.string "Me gustan las bolitas de fuego como tú.\n"
	.string "Deja que te registre en mi POKéNAV.$"

MtChimney_Text_SawyerRematchIntro:
	.string "Estoy feliz rodeado de gente ardiente\n"
	.string "por aquí. ¡No pienso perder!$"

MtChimney_Text_SawyerRematchDefeat:
	.string "¡Vaya, sigues echando chispas\n"
	.string "como antes!$"

MtChimney_Text_SawyerPostRematch:
	.string "La verdad es que aquí hace calor.\n"
	.string "Voy demasiado abrigado.$"
