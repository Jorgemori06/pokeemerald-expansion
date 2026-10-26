MossdeepCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, MossdeepCity_Gym_OnLoad
	.byte 0

@ NOTE: Mossdeep Gym was redesigned between R/S and E. Leftover (and now functionally unused) scripts are commented below

MossdeepCity_Gym_OnTransition:
	setflag FLAG_TEMP_HIDE_FOLLOWER @ Hide follower since it can collide with moving statues
	end

@ All the below checks are leftover from RS. FLAG_MOSSDEEP_GYM_SWITCH_X is never set
MossdeepCity_Gym_OnLoad:
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepCity_Gym_EventScript_SetSwitch1Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch2
	end

MossdeepCity_Gym_EventScript_CheckSwitch2::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepCity_Gym_EventScript_SetSwitch2Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch3
	end

MossdeepCity_Gym_EventScript_CheckSwitch3::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepCity_Gym_EventScript_SetSwitch3Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch4
	end

MossdeepCity_Gym_EventScript_CheckSwitch4::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepCity_Gym_EventScript_SetSwitch4Metatiles
	end

@ All the below set metatile scripts are leftover from RS and are functionally unused
MossdeepCity_Gym_EventScript_SetSwitch1Metatiles::
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch2
	end

MossdeepCity_Gym_EventScript_SetSwitch2Metatiles::
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch3
	end

MossdeepCity_Gym_EventScript_SetSwitch3Metatiles::
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch4
	end

MossdeepCity_Gym_EventScript_SetSwitch4Metatiles::
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	end

MossdeepCity_Gym_EventScript_TateAndLiza::
	trainerbattle_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaIntro, MossdeepCity_Gym_Text_TateAndLizaDefeat, MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons, MossdeepCity_Gym_EventScript_TateAndLizaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MossdeepCity_Gym_EventScript_TateAndLizaRematch
	goto_if_unset FLAG_RECEIVED_TM_CALM_MIND, MossdeepCity_Gym_EventScript_GiveCalmMind2
	msgbox MossdeepCity_Gym_Text_TateAndLizaPostBattle, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_TateAndLizaDefeated::
	message MossdeepCity_Gym_Text_ReceivedMindBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_MOSSDEEP_GYM
	setflag FLAG_BADGE07_GET
	setflag FLAG_HIDE_AQUA_HIDEOUT_GRUNTS
	clearflag FLAG_HIDE_SLATEPORT_CITY_STERNS_SHIPYARD_MR_BRINEY
	clearflag FLAG_UNKNOWN_0x393
	setvar VAR_0x8008, 7
	call Common_EventScript_SetGymTrainers
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_PATRONS
	clearflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_STEVEN
	setvar VAR_MOSSDEEP_CITY_STATE, 1
	setflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_STEVEN
	setvar VAR_MOSSDEEP_SPACE_CENTER_STATE, 1
	call MossdeepCity_Gym_EventScript_GiveCalmMind
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MossdeepCity_Gym_Text_RegisteredTateAndLiza, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_TATE_AND_LIZA_MATCH_CALL
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind2::
	giveitem ITEM_TM_CALM_MIND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_CALM_MIND
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind::
	giveitem ITEM_TM_CALM_MIND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_CALM_MIND
	return

MossdeepCity_Gym_EventScript_TateAndLizaRematch::
	trainerbattle_rematch_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaPreRematch, MossdeepCity_Gym_Text_TateAndLizaRematchDefeat, MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons
	msgbox MossdeepCity_Gym_Text_TateAndLizaPostRematch, MSGBOX_AUTOCLOSE
	end

@ All the below switch scripts are leftover from RS and are functionally unused
MossdeepCity_Gym_EventScript_Switch1::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepCity_Gym_EventScript_ClearSwitch1
	setflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed::
	special DrawWholeMapView
	playse SE_CLICK
	releaseall
	end

MossdeepCity_Gym_EventScript_ClearSwitch1::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch2::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepCity_Gym_EventScript_ClearSwitch2
	setflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch2::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Down, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch3::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepCity_Gym_EventScript_ClearSwitch3
	setflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch3::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch4::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepCity_Gym_EventScript_ClearSwitch4
	setflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch4::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement LOCALID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_WarpToEntrance::
	lockall
	warpmossdeepgym MAP_MOSSDEEP_CITY_GYM, 7, 30
	waitstate
	releaseall
	end

MossdeepCity_Gym_EventScript_Preston::
	trainerbattle_single TRAINER_PRESTON, MossdeepCity_Gym_Text_PrestonIntro, MossdeepCity_Gym_Text_PrestonDefeat
	msgbox MossdeepCity_Gym_Text_PrestonPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Virgil::
	trainerbattle_single TRAINER_VIRGIL, MossdeepCity_Gym_Text_VirgilIntro, MossdeepCity_Gym_Text_VirgilDefeat
	msgbox MossdeepCity_Gym_Text_VirgilPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Blake::
	trainerbattle_single TRAINER_BLAKE, MossdeepCity_Gym_Text_BlakeIntro, MossdeepCity_Gym_Text_BlakeDefeat
	msgbox MossdeepCity_Gym_Text_BlakePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Hannah::
	trainerbattle_single TRAINER_HANNAH, MossdeepCity_Gym_Text_HannahIntro, MossdeepCity_Gym_Text_HannahDefeat
	msgbox MossdeepCity_Gym_Text_HannahPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Samantha::
	trainerbattle_single TRAINER_SAMANTHA, MossdeepCity_Gym_Text_SamanthaIntro, MossdeepCity_Gym_Text_SamanthaDefeat
	msgbox MossdeepCity_Gym_Text_SamanthaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Maura::
	trainerbattle_single TRAINER_MAURA, MossdeepCity_Gym_Text_MauraIntro, MossdeepCity_Gym_Text_MauraDefeat
	msgbox MossdeepCity_Gym_Text_MauraPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Sylvia::
	trainerbattle_single TRAINER_SYLVIA, MossdeepCity_Gym_Text_SylviaIntro, MossdeepCity_Gym_Text_SylviaDefeat
	msgbox MossdeepCity_Gym_Text_SylviaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nate::
	trainerbattle_single TRAINER_NATE, MossdeepCity_Gym_Text_NateIntro, MossdeepCity_Gym_Text_NateDefeat
	msgbox MossdeepCity_Gym_Text_NatePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Macey::
	trainerbattle_single TRAINER_MACEY, MossdeepCity_Gym_Text_MaceyIntro, MossdeepCity_Gym_Text_MaceyDefeat
	msgbox MossdeepCity_Gym_Text_MaceyPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Clifford::
	trainerbattle_single TRAINER_CLIFFORD, MossdeepCity_Gym_Text_CliffordIntro, MossdeepCity_Gym_Text_CliffordDefeat
	msgbox MossdeepCity_Gym_Text_CliffordPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nicholas::
	trainerbattle_single TRAINER_NICHOLAS, MossdeepCity_Gym_Text_NicholasIntro, MossdeepCity_Gym_Text_NicholasDefeat
	msgbox MossdeepCity_Gym_Text_NicholasPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Kathleen::
	trainerbattle_single TRAINER_KATHLEEN, MossdeepCity_Gym_Text_KathleenIntro, MossdeepCity_Gym_Text_KathleenDefeat
	msgbox MossdeepCity_Gym_Text_KathleenPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MOSSDEEP_GYM, MossdeepCity_Gym_EventScript_GymGuidePostVictory
	msgbox MossdeepCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_GymGuidePostVictory::
	msgbox MossdeepCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

@ Leftover from RS, functionally unused
MossdeepCity_Gym_Movement_WaitAfterSwitchUse:
	delay_16
	delay_16
	step_end

MossdeepCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_GymStatueCertified::
	msgbox MossdeepCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_GymStatue::
	msgbox MossdeepCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_YellowFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 0
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_BlueFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 1
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_GreenFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 2
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_PurpleFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 3
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_RedFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 4
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_Text_GymGuideAdvice:
	.string "¡Eh! ¿Qué tal, futura estrella de\n"
	.string "la LIGA, {PLAYER}?\p"
	.string "Los LÍDERES de aquí usan POKéMON\n"
	.string "de tipo PSÍQUICO.\p"
	.string "Si te enfrentas a ellos con POKéMON\n"
	.string "de tipo LUCHA o VENENO, ¡les harán\l"
	.string "un daño horrible!\p"
	.string "Además, atacan con unas combinaciones\n"
	.string "impresionantes.\p"
	.string "Si quieres ganar, tendrás que\n"
	.string "demostrarles el lazo que tienes con\l"
	.string "tus POKéMON. ¡A por ellos!$"

MossdeepCity_Gym_Text_GymGuidePostVictory:
	.string "¡Hala, qué pasada!\n"
	.string "¡Qué bien entrenas!$"

MossdeepCity_Gym_Text_PrestonIntro:
	.string "¡Los combates dependen de la fuerza\n"
	.string "de espíritu! ¡Los débiles nunca ganan!$"

MossdeepCity_Gym_Text_PrestonDefeat:
	.string "¡He perdido!\n"
	.string "¡Tengo que volver a templar el espíritu!$"

MossdeepCity_Gym_Text_PrestonPostBattle:
	.string "Los indecisos pierden.\n"
	.string "Que te sirva de aviso.$"

MossdeepCity_Gym_Text_VirgilIntro:
	.string "¡Enséñame tu talento!$"

MossdeepCity_Gym_Text_VirgilDefeat:
	.string "¡Tienes un talento espectacular!$"

MossdeepCity_Gym_Text_VirgilPostBattle:
	.string "Si en el mundo hay prodigios, ¡son\n"
	.string "nuestros LÍDERES!\p"
	.string "Aunque puede que tú tengas aún más\n"
	.string "talento que ellos…$"

MossdeepCity_Gym_Text_BlakeIntro:
	.string "Fufufufu… ¡Mira cómo hago levitar una\n"
	.string "POKé BALL con la mente!\p"
	.string "¡Uooooooooaaaar!\n"
	.string "… … … … … … …\p"
	.string "A veces no estoy en sintonía…$"

MossdeepCity_Gym_Text_BlakeDefeat:
	.string "¡Mi forma de combatir tampoco está en\n"
	.string "sintonía!$"

MossdeepCity_Gym_Text_BlakePostBattle:
	.string "Una POKé BALL pesaba demasiado para\n"
	.string "levantarla con la mente. Pero esta\l"
	.string "pelusa…\p"
	.string "¡Fiuuuuuuuuuuuuuuh!\n"
	.string "… … … … … …\p"
	.string "¡No, no hago trampa!\n"
	.string "¡No he soplado! ¡De verdad!$"

MossdeepCity_Gym_Text_HannahIntro:
	.string "Cuando pierdas contra mí, no te\n"
	.string "machaques.\p"
	.string "No es que seas débil, ¡es que yo soy\n"
	.string "demasiado fuerte!$"

MossdeepCity_Gym_Text_HannahDefeat:
	.string "¡Es que eres demasiado fuerte!$"

MossdeepCity_Gym_Text_HannahPostBattle:
	.string "No me voy a venir abajo por perder.\n"
	.string "Solo tengo que entrenar más.\p"
	.string "¡Pensar en positivo es mi punto\n"
	.string "fuerte!$"

MossdeepCity_Gym_Text_SamanthaIntro:
	.string "Lo veo…\n"
	.string "Veo tu futuro…\p"
	.string "¡Si me ganas, te diré tu futuro!$"

MossdeepCity_Gym_Text_SamanthaDefeat:
	.string "¡Me rindo!$"

MossdeepCity_Gym_Text_SamanthaPostBattle:
	.string "Tendrás un combate durísimo con\n"
	.string "nuestros LÍDERES…\p"
	.string "¿El resultado…?\n"
	.string "¡Eso no te lo digo!$"

MossdeepCity_Gym_Text_MauraIntro:
	.string "Los caminos que has recorrido…\n"
	.string "Lo que has vivido…\p"
	.string "¡Lánzame todo lo que has aprendido!$"

MossdeepCity_Gym_Text_MauraDefeat:
	.string "¡Has recorrido un camino de grandeza!$"

MossdeepCity_Gym_Text_MauraPostBattle:
	.string "A quien trabaja con constancia le\n"
	.string "espera un futuro brillante.\p"
	.string "A quien holgazanea solo le espera\n"
	.string "la desesperación.\p"
	.string "Quien siembra vientos recoge\n"
	.string "tempestades…$"

MossdeepCity_Gym_Text_SylviaIntro:
	.string "¡Ganaré este combate aunque me\n"
	.string "cueste la vida!$"

MossdeepCity_Gym_Text_SylviaDefeat:
	.string "Lo que haces…\n"
	.string "Me horroriza…$"

MossdeepCity_Gym_Text_SylviaPostBattle:
	.string "Cómo te atreves a ganarme…\p"
	.string "No será culpa mía si te pasa algo\n"
	.string "horrible…$"

MossdeepCity_Gym_Text_NateIntro:
	.string "Jojojo.\p"
	.string "Deja que te enseñe lo tenaz que\n"
	.string "puede ser el tipo PSÍQUICO.$"

MossdeepCity_Gym_Text_NateDefeat:
	.string "¡Oh! ¡Vaya, vaya!\n"
	.string "¡Tu forma de combatir es fantástica!$"

MossdeepCity_Gym_Text_NatePostBattle:
	.string "N-no dejo que la derrota me af-fecte,\n"
	.string "por muy m-mal que vaya.$"

MossdeepCity_Gym_Text_KathleenIntro:
	.string "¡Te haré pasar un rato horroroso!$"

MossdeepCity_Gym_Text_KathleenDefeat:
	.string "¡N-nooooo!$"

MossdeepCity_Gym_Text_KathleenPostBattle:
	.string "¡Tu vitalidad se contagia!\n"
	.string "¡Aléjate de mí ya!$"

MossdeepCity_Gym_Text_CliffordIntro:
	.string "Puede que ya no esté en mi mejor\n"
	.string "momento, pero no me subestimes.$"

MossdeepCity_Gym_Text_CliffordDefeat:
	.string "¡Ah, rebosas el poder de la juventud!$"

MossdeepCity_Gym_Text_CliffordPostBattle:
	.string "Parece que no he podido con tu\n"
	.string "energía juvenil.$"

MossdeepCity_Gym_Text_MaceyIntro:
	.string "¡No vas a llegar al final!\n"
	.string "¡No si yo puedo evitarlo!$"

MossdeepCity_Gym_Text_MaceyDefeat:
	.string "¿Cómo puedes ser tan ridículamente\n"
	.string "fuerte?$"

MossdeepCity_Gym_Text_MaceyPostBattle:
	.string "¡Hmpf! Serás fuerte, ¡pero el tipo\n"
	.string "PSÍQUICO no va contigo!\p"
	.string "¡Combates de una forma muy bruta!$"

MossdeepCity_Gym_Text_NicholasIntro:
	.string "¡Uoooar! ¡Prueba mi superpoder de\n"
	.string "combate POKéMON!$"

MossdeepCity_Gym_Text_NicholasDefeat:
	.string "¡Oh!\n"
	.string "¡Acabado!$"

MossdeepCity_Gym_Text_NicholasPostBattle:
	.string "¡Vale! Creo que ahora desarrollaré un\n"
	.string "superpoder POKéMON invencible.$"

MossdeepCity_Gym_Text_TateAndLizaIntro:
	.string "VITO: Jejeje… ¿Te has sorprendido?\p"
	.string "LETI: Jijiji… ¿Te has sorprendido?\p"
	.string "VITO: ¿De que haya dos LÍDERES?\n"
	.string "LETI: ¿De que haya dos LÍDERES?\p"
	.string "VITO: ¡Somos gemelos!\n"
	.string "LETI: ¡Somos gemelos!\p"
	.string "VITO: No nos hace falta hablar porque…\n"
	.string "LETI: Cada uno sabe lo que…\p"
	.string "VITO: Piensa el otro…\n"
	.string "LETI: ¡Todo en la mente!\p"
	.string "VITO: Esta combinación nuestra…\n"
	.string "LETI: ¿Podrás ganarla?$"

MossdeepCity_Gym_Text_TateAndLizaDefeat:
	.string "VITO: ¡¿Qué?! Nuestra combinación…\n"
	.string "LETI: ¡Se ha roto!\p"
	.string "VITO: No hay más que hablar. Ganas…\n"
	.string "LETI: Así que, en reconocimiento, toma.$"

MossdeepCity_Gym_Text_ReceivedMindBadge:
	.string "{PLAYER} ha recibido la MEDALLA\n"
	.string "MENTE de VITO y LETI.$"

MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis:
	.string "VITO: La MEDALLA MENTE sube el AT. ESP.\n"
	.string "y la DEF. ESP. de los POKéMON.\p"
	.string "LETI: Y además permite usar el\n"
	.string "movimiento de MO BUCEO fuera\l"
	.string "del combate.\p"
	.string "VITO: Llévate también esto.$"

MossdeepCity_Gym_Text_ExplainCalmMind:
	.string "VITO: Esa MT04 contiene…\n"
	.string "LETI: ¡PAZ MENTAL!\p"
	.string "VITO: Sube el AT. ESP. y…\n"
	.string "LETI: ¡Sube la DEF. ESP.!\p"
	.string "VITO: Es un movimiento perfecto…\n"
	.string "LETI: ¡Para POKéMON PSÍQUICOS!\p"
	.string "… … … … … …$"

MossdeepCity_Gym_Text_RegisteredTateAndLiza:
	.string "Has registrado a los LÍDERES de\n"
	.string "GIMNASIO VITO y LETI en el POKéNAV.$"

MossdeepCity_Gym_Text_TateAndLizaPostBattle:
	.string "VITO: Parece que el lazo entre tú y\n"
	.string "tus POKéMON es mucho más fuerte\l"
	.string "que el nuestro como gemelos.\p"
	.string "LETI: ¡Te harás aún más fuerte!\n"
	.string "Hemos combatido contigo, lo sabemos.$"

MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons:
	.string "VITO: Jejeje… ¿Te has sorprendido?\p"
	.string "LETI: ¿De que haya dos LÍDERES?\p"
	.string "VITO: Vaya, solo tienes un…\n"
	.string "LETI: POKéMON que pueda combatir.\p"
	.string "VITO: ¡Así no podemos combatir!\p"
	.string "LETI: Si quieres desafiarnos, trae\n"
	.string "más POKéMON.$"

MossdeepCity_Gym_Text_GymStatue:
	.string "GIMNASIO POKéMON DE ALGARIA$"

MossdeepCity_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON DE ALGARIA\p"
	.string "RECONOCIDOS POR VITO y LETI:\n"
	.string "{PLAYER}$"

MossdeepCity_Gym_Text_TateAndLizaPreRematch:
	.string "TATE: POKéMON…\n"
	.string "LIZA: POKéMON…\p"
	.string "TATE: By changing the party's mix…\n"
	.string "LIZA: The battle style changes.\p"
	.string "TATE: But me…\n"
	.string "LIZA: But me…\p"
	.string "TATE: I'll always be with LIZA!\n"
	.string "LIZA: I'll always be with TATE!\p"
	.string "TATE: Our combination…\n"
	.string "LIZA: We'll show you again and again!$"

MossdeepCity_Gym_Text_TateAndLizaRematchDefeat:
	.string "TATE: You and your POKéMON…\n"
	.string "LIZA: It's as if you were siblings!$"

MossdeepCity_Gym_Text_TateAndLizaPostRematch:
	.string "TATE: You can knock us down,\n"
	.string "but we'll never stay down!\p"
	.string "LIZA: Because the two of us,\n"
	.string "we always support each other!$"

MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons:
	.string "TATE: You're back again…\n"
	.string "LIZA: You're back again…\p"
	.string "TATE: To give us a rematch.\n"
	.string "LIZA: To give us a rematch.\p"
	.string "TATE: But…\n"
	.string "LIZA: For our match…\p"
	.string "TATE: You brought just one POKéMON!\n"
	.string "LIZA: You brought just one POKéMON!\p"
	.string "TATE: We need you to bring at least…\n"
	.string "LIZA: Two POKéMON when you come back.$"
