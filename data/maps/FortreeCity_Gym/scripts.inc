FortreeCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, FortreeCity_Gym_OnWarp
	.byte 0

FortreeCity_Gym_OnTransition:
	special RotatingGate_InitPuzzle
	setflag FLAG_TEMP_HIDE_FOLLOWER @ Hide follower bc of rotating gates
	end

FortreeCity_Gym_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, FortreeCity_Gym_EventScript_InitRotatingGates
	.2byte 0

@ NOTE: This rotating gate puzzle makes use of VAR_TEMP_0 - VAR_TEMP_3
FortreeCity_Gym_EventScript_InitRotatingGates::
	special RotatingGate_InitPuzzleAndGraphics
	end

FortreeCity_Gym_EventScript_Winona::
	trainerbattle_single TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaIntro, FortreeCity_Gym_Text_WinonaDefeat, FortreeCity_Gym_EventScript_WinonaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_Gym_EventScript_WinonaRematch
	goto_if_unset FLAG_RECEIVED_TM_AERIAL_ACE, FortreeCity_Gym_EventScript_GiveAerialAce2
	msgbox FortreeCity_Gym_Text_WinonaPostBattle, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_WinonaDefeated::
	message FortreeCity_Gym_Text_ReceivedFeatherBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_FORTREE_GYM
	setflag FLAG_BADGE06_GET
	setvar VAR_0x8008, 6
	call Common_EventScript_SetGymTrainers
	call FortreeCity_Gym_EventScript_GiveAerialAce
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox FortreeCity_Gym_Text_RegisteredWinona, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WINONA_MATCH_CALL
	setvar VAR_SCOTT_FORTREE_CALL_STEP_COUNTER, 0
	setflag FLAG_SCOTT_CALL_FORTREE_GYM
	release
	end

FortreeCity_Gym_EventScript_GiveAerialAce2::
	giveitem ITEM_TM_AERIAL_ACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
	release
	end

FortreeCity_Gym_EventScript_GiveAerialAce::
	giveitem ITEM_TM_AERIAL_ACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
	return

FortreeCity_Gym_EventScript_WinonaRematch::
	trainerbattle_rematch_double TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaPreRematch, FortreeCity_Gym_Text_WinonaRematchDefeat, FortreeCity_Gym_Text_WinonaRematchNeedTwoMons
	msgbox FortreeCity_Gym_Text_WinonaPostRematch, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Jared::
	trainerbattle_single TRAINER_JARED, FortreeCity_Gym_Text_JaredIntro, FortreeCity_Gym_Text_JaredDefeat
	msgbox FortreeCity_Gym_Text_JaredPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Edwardo::
	trainerbattle_single TRAINER_EDWARDO, FortreeCity_Gym_Text_EdwardoIntro, FortreeCity_Gym_Text_EdwardoDefeat
	msgbox FortreeCity_Gym_Text_EdwardoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Flint::
	trainerbattle_single TRAINER_FLINT, FortreeCity_Gym_Text_FlintIntro, FortreeCity_Gym_Text_FlintDefeat
	msgbox FortreeCity_Gym_Text_FlintPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Ashley::
	trainerbattle_single TRAINER_ASHLEY, FortreeCity_Gym_Text_AshleyIntro, FortreeCity_Gym_Text_AshleyDefeat
	msgbox FortreeCity_Gym_Text_AshleyPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Humberto::
	trainerbattle_single TRAINER_HUMBERTO, FortreeCity_Gym_Text_HumbertoIntro, FortreeCity_Gym_Text_HumbertoDefeat
	msgbox FortreeCity_Gym_Text_HumbertoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Darius::
	trainerbattle_single TRAINER_DARIUS, FortreeCity_Gym_Text_DariusIntro, FortreeCity_Gym_Text_DariusDefeat
	msgbox FortreeCity_Gym_Text_DariusPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_FORTREE_GYM, FortreeCity_Gym_EventScript_GymGuidePostVictory
	msgbox FortreeCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_GymGuidePostVictory::
	msgbox FortreeCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_GymStatueCertified::
	msgbox FortreeCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_EventScript_GymStatue::
	msgbox FortreeCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_Text_GymGuideAdvice:
	.string "¡Eh! ¿Qué tal, futura estrella de\n"
	.string "la LIGA, {PLAYER}?\p"
	.string "ALANA, la LÍDER de ARBORADA, es una\n"
	.string "maestra de los POKéMON de tipo VOLADOR.\p"
	.string "Te espera al fondo del GIMNASIO,\n"
	.string "detrás de las puertas giratorias.\p"
	.string "¡Espera a nuevos aspirantes que\n"
	.string "quieran alzar el vuelo!\p"
	.string "¡Venga, a por ella!$"

FortreeCity_Gym_Text_GymGuidePostVictory:
	.string "¡Lo has conseguido!\n"
	.string "¡Has despegado!$"

FortreeCity_Gym_Text_JaredIntro:
	.string "¡Contempla el elegante estilo de\n"
	.string "combate de los POKéMON PÁJARO!$"

FortreeCity_Gym_Text_JaredDefeat:
	.string "Eres…\n"
	.string "Eres fuerte…$"

FortreeCity_Gym_Text_JaredPostBattle:
	.string "Hay que ser listo para adaptarse a\n"
	.string "los giros inesperados.\p"
	.string "¿Tienes la cabeza para llegar hasta\n"
	.string "nuestra LÍDER?$"

FortreeCity_Gym_Text_EdwardoIntro:
	.string "Los amantes de los POKéMON PÁJARO\n"
	.string "sueñan con entrar en este GIMNASIO.\p"
	.string "¡Como miembro del GIMNASIO de\n"
	.string "ARBORADA, no puedo perder!$"

FortreeCity_Gym_Text_EdwardoDefeat:
	.string "Era una carga demasiado pesada\n"
	.string "para mí…$"

FortreeCity_Gym_Text_EdwardoPostBattle:
	.string "El mundo es enorme y hay muchísimos\n"
	.string "ENTRENADORES duros.\p"
	.string "Voy a seguir entrenando para ser\n"
	.string "aún más fuerte.$"

FortreeCity_Gym_Text_FlintIntro:
	.string "¡No hace falta que ALANA, nuestra\n"
	.string "LÍDER, se ocupe de ti!\p"
	.string "¡Conmigo tienes de sobra!$"

FortreeCity_Gym_Text_FlintDefeat:
	.string "ALANA, yo…\n"
	.string "¡He perdido!$"

FortreeCity_Gym_Text_FlintPostBattle:
	.string "ALANA es guapa y fuerte.\n"
	.string "¡Es la LÍDER definitiva!\p"
	.string "¡Qué vergüenza…!$"

FortreeCity_Gym_Text_AshleyIntro:
	.string "¡ALANA me ha enseñado en persona!\n"
	.string "¡No me ganarás fácilmente!$"

FortreeCity_Gym_Text_AshleyDefeat:
	.string "Me han ganado…$"

FortreeCity_Gym_Text_AshleyPostBattle:
	.string "Gracias a ALANA, la gente de\n"
	.string "ARBORADA vive sin miedo.$"

FortreeCity_Gym_Text_HumbertoIntro:
	.string "Cuando ALANA combate, su cara brilla\n"
	.string "con una determinación preciosa…\p"
	.string "¡No pienso dejar que veas esa\n"
	.string "imagen tan bonita!$"

FortreeCity_Gym_Text_HumbertoDefeat:
	.string "¡Ugh!\n"
	.string "No he podido pararte.$"

FortreeCity_Gym_Text_HumbertoPostBattle:
	.string "¡Ten cuidado!\n"
	.string "¡No te despistes mirando a ALANA\l"
	.string "o te estrellarás!$"

FortreeCity_Gym_Text_DariusIntro:
	.string "Que sepas que hay POKéMON de tipo\n"
	.string "VOLADOR de todas clases.\p"
	.string "Lo sabes, ¿verdad?$"

FortreeCity_Gym_Text_DariusDefeat:
	.string "¡Parece que sabes de lo que hablas!$"

FortreeCity_Gym_Text_DariusPostBattle:
	.string "Vale, me has ganado.\n"
	.string "¡Pero ten cuidado! Los POKéMON de\l"
	.string "nuestra LÍDER ALANA van en serio.$"

FortreeCity_Gym_Text_WinonaIntro:
	.string "Soy ALANA. Soy la LÍDER del\n"
	.string "GIMNASIO POKéMON de ARBORADA.\p"
	.string "Me he unido a los POKéMON PÁJARO\n"
	.string "y he surcado los cielos…\p"
	.string "Por duro que sea el combate, hemos\n"
	.string "triunfado con elegancia…\p"
	.string "¡Contempla la elegante coreografía\n"
	.string "de mis POKéMON PÁJARO y yo!$"

FortreeCity_Gym_Text_WinonaDefeat:
	.string "Nunca había visto a nadie dirigir\n"
	.string "POKéMON con más elegancia que yo…\p"
	.string "En reconocimiento a tu destreza,\n"
	.string "te entrego esta MEDALLA.$"

FortreeCity_Gym_Text_ReceivedFeatherBadge:
	.string "{PLAYER} ha recibido la MEDALLA\n"
	.string "PLUMA de ALANA.$"

FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis:
	.string "Con la MEDALLA PLUMA, todos los\n"
	.string "POKéMON hasta el nivel 70, incluso los\l"
	.string "de intercambios, te obedecerán.\p"
	.string "También podrás usar el movimiento\n"
	.string "de MO VUELO fuera del combate.\p"
	.string "Y esto…\n"
	.string "Esto es un regalo mío.$"

FortreeCity_Gym_Text_ExplainAerialAce:
	.string "La MT40 contiene GOLPE AÉREO.\p"
	.string "Su velocidad…\n"
	.string "Ningún POKéMON podrá esquivarlo.\p"
	.string "… … … … … …$"

FortreeCity_Gym_Text_RegisteredWinona:
	.string "Has registrado a la LÍDER de GIMNASIO\n"
	.string "ALANA en el POKéNAV.$"

FortreeCity_Gym_Text_WinonaPostBattle:
	.string "Aunque me hayas ganado, seguiré\n"
	.string "entregada a los POKéMON PÁJARO.$"

FortreeCity_Gym_Text_GymStatue:
	.string "GIMNASIO POKéMON DE ARBORADA$"

FortreeCity_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON DE ARBORADA\p"
	.string "RECONOCIDOS POR ALANA:\n"
	.string "{PLAYER}$"

FortreeCity_Gym_Text_WinonaPreRematch:
	.string "WINONA: We humans can never escape\n"
	.string "gravity's pull on the ground.\p"
	.string "But by striving for excellence,\n"
	.string "we have the power to soar!\p"
	.string "You have scaled the pinnacle as\n"
	.string "the reigning CHAMPION.\p"
	.string "Please, allow me to see your power\n"
	.string "at full flight!$"

FortreeCity_Gym_Text_WinonaRematchDefeat:
	.string "I failed to reach your height again…$"

FortreeCity_Gym_Text_WinonaPostRematch:
	.string "WINONA: Even though I have lost,\n"
	.string "the wings of my heart remain unbroken.\p"
	.string "I can rise and soar again and\n"
	.string "yet again.\p"
	.string "I am convinced of it!$"

FortreeCity_Gym_Text_WinonaRematchNeedTwoMons:
	.string "WINONA: We humans can never escape\n"
	.string "gravity's pull on the ground.\p"
	.string "But by striving for excellence,\n"
	.string "we have the power to soar!\p"
	.string "You have scaled the pinnacle as\n"
	.string "the reigning CHAMPION.\p"
	.string "Please, allow me to see your power\n"
	.string "at full flight!\p"
	.string "Oh, no… Do you have but one\n"
	.string "POKéMON with you?\p"
	.string "Please return with two POKéMON\n"
	.string "at the very least.$"
