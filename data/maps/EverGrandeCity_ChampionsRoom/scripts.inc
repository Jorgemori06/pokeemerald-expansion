EverGrandeCity_ChampionsRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_ChampionsRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_ChampionsRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_ChampionsRoom_OnFrame
	.byte 0

EverGrandeCity_ChampionsRoom_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	end

EverGrandeCity_ChampionsRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

EverGrandeCity_ChampionsRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_EnterRoom
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_EnterRoom::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp4
	waitmovement 0
	delay 40
	applymovement LOCALID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace
	waitmovement 0
	setvar VAR_TEMP_1, 1
	goto EverGrandeCity_ChampionsRoom_EventScript_Wallace
	releaseall
	end

EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_EventScript_Wallace::
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox EverGrandeCity_ChampionsRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLACE, EverGrandeCity_ChampionsRoom_Text_Defeat
	goto EverGrandeCity_ChampionsRoom_EventScript_Defeated
	end

EverGrandeCity_ChampionsRoom_EventScript_Defeated::
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, FALSE
	special DrawWholeMapView
	msgbox EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic
	addobject LOCALID_CHAMPIONS_ROOM_RIVAL
	call EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayAdvice
	goto_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice
	end

EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_MayAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF::
	closemessage
	addobject LOCALID_CHAMPIONS_ROOM_BIRCH
	applymovement LOCALID_CHAMPIONS_ROOM_BIRCH, EverGrandeCity_ChampionsRoom_Movement_BirchArrives
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex, MSGBOX_DEFAULT
	call ProfBirch_EventScript_RatePokedex
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchCongratulations, MSGBOX_DEFAULT
	applymovement LOCALID_CHAMPIONS_ROOM_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	applymovement LOCALID_CHAMPIONS_ROOM_WALLACE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_CHAMPIONS_ROOM_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart
	applymovement LOCALID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart
	applymovement LOCALID_CHAMPIONS_ROOM_BIRCH, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalFollows
	waitmovement 0
	delay 20
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside, MSGBOX_DEFAULT
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations
	closemessage
	applymovement LOCALID_CHAMPIONS_ROOM_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExit
	applymovement LOCALID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExit
	waitmovement 0
	setflag FLAG_HIDE_PETALBURG_GYM_GREETER
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 7, 16
	waitstate
	releaseall
	end

EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer::
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth::
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_PlayerExit:
	walk_up
	delay_16
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_in_place_faster_right
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth:
	walk_in_place_faster_up
	delay_16
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_up
	delay_8
	walk_in_place_faster_right
	delay_16
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalFollows:
	walk_right
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart:
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExit:
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_BirchArrives:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_in_place_faster_left
	step_end

EverGrandeCity_ChampionsRoom_Text_IntroSpeech:
	.string "PLUBIO: Te doy la bienvenida,\n"
	.string "{PLAYER}{KUN}.\p"
	.string "Lo de CIUDAD ARRECÍPOLIS…\n"
	.string "Fue un trabajo magnífico, acabar con\l"
	.string "esa crisis tú solo.\p"
	.string "¡Huy!\p"
	.string "No sería justo decir que acabaste con\n"
	.string "la crisis tú solo.\p"
	.string "Superaste esa situación tan difícil\n"
	.string "formando un equipo con tus POKéMON.\p"
	.string "Los ENTRENADORES criamos a los POKéMON\n"
	.string "dándoles objetos y enseñándoles\l"
	.string "técnicas nuevas para combatir.\p"
	.string "Pero nosotros también aprendemos\n"
	.string "muchas cosas de los POKéMON.\p"
	.string "Y aquí es donde tus logros se ponen a\n"
	.string "prueba frente a los de otros como tú.\p"
	.string "¡Vamos!\p"
	.string "¿Quién baila con más elegancia junto a\n"
	.string "sus POKéMON en HOENN?\p"
	.string "¡Demuéstramelo aquí y ahora!$"

EverGrandeCity_ChampionsRoom_Text_Defeat:
	.string "Yo, el CAMPEÓN, caigo derrotado…\p"
	.string "Ha sido un trabajo maravilloso.\n"
	.string "Qué elegancia, hasta fastidia.\l"
	.string "¡Y aun así ha sido glorioso!\p"
	.string "¡Te felicito, {PLAYER}{KUN}!\p"
	.string "¡Entrenas POKéMON con auténtica\n"
	.string "nobleza!$"

EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech:
	.string "PLUBIO: Los POKéMON que sacaste\n"
	.string "al combate…\p"
	.string "A veces bailaban como una brisa de\n"
	.string "primavera, y a veces golpeaban\l"
	.string "como un rayo.\p"
	.string "Guiaste a tus POKéMON con una\n"
	.string "elegancia ligera, pero segura.\p"
	.string "¡Hasta a mí me ha deslumbrado tu\n"
	.string "actuación magistral!\p"
	.string "Ahora estás en la cima gloriosa de la\n"
	.string "LIGA POKéMON.\p"
	.string "Y ahora proclamo que, de la región\n"
	.string "de HOENN, tú eres…$"

EverGrandeCity_ChampionsRoom_Text_MayAdvice:
	.string "AURA: ¡{PLAYER}{KUN}!\p"
	.string "Aquí tienes un consejo antes de que\n"
	.string "desafíes al CAMPEÓN…$"

EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver:
	.string "AURA: ¿Eh?\n"
	.string "¿Qué, qué, qué?\p"
	.string "{PLAYER}{KUN}…\n"
	.string "¿No me digas que…\l"
	.string "¿Ya se ha acabado?$"

EverGrandeCity_ChampionsRoom_Text_BrendanAdvice:
	.string "BRUNO: ¡{PLAYER}!\p"
	.string "¿Quieres un consejo antes de desafiar\n"
	.string "al CAMPEÓN?…$"

EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon:
	.string "BRUNO: {PLAYER}…\p"
	.string "¿Me estás diciendo que…\n"
	.string "¿Que has ganado al CAMPEÓN?$"

EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex:
	.string "PROF. ABEDUL: ¿Lo ves?\n"
	.string "¿Qué te dije, {RIVAL}?\p"
	.string "¿No te dije que no tenías que\n"
	.string "preocuparte por {PLAYER}{KUN}?\p"
	.string "… … … … … … … …\n"
	.string "{PLAYER}{KUN}, por fin lo has logrado.\p"
	.string "Cuando me enteré de que habías ganado\n"
	.string "a tu padre en el GIMNASIO de PETALIA,\l"
	.string "pensé que quizá tenías opciones…\p"
	.string "¡Pero llegar a ser CAMPEÓN!\p"
	.string "¡Ah, sí!\p"
	.string "¿Cómo va tu POKéDEX?\n"
	.string "A ver, déjame verla.$"

EverGrandeCity_ChampionsRoom_Text_BirchCongratulations:
	.string "PROF. ABEDUL: En fin,\n"
	.string "¡enhorabuena!\p"
	.string "¡Ahora entra con orgullo en la última\n"
	.string "sala!$"

EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe:
	.string "PLUBIO: {PLAYER}{KUN}…\p"
	.string "No, déjame decirlo como es debido.\p"
	.string "¡CAMPEÓN de HOENN!\p"
	.string "Ven conmigo.$"

EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside:
	.string "PLUBIO: Lo siento, pero…\p"
	.string "A partir de aquí solo pueden entrar\n"
	.string "los ENTRENADORES que han llegado a\l"
	.string "CAMPEÓN.\p"
	.string "Tendrás que esperar fuera con el\n"
	.string "PROF. ABEDUL.$"

EverGrandeCity_ChampionsRoom_Text_MayCongratulations:
	.string "AURA: Jo…\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "¡Es broma! ¡No pasa nada!\n"
	.string "¡Son las normas!\p"
	.string "¡{PLAYER}{KUN}!\n"
	.string "¡De verdad, enhorabuena!$"

EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations:
	.string "BRUNO: ¡¿Quéééé?! … … … … …\n"
	.string "… … … … … … … …\p"
	.string "Si son las normas, no hay nada que\n"
	.string "hacer.\p"
	.string "¡{PLAYER}, bien hecho!\n"
	.string "¡Enhorabuena!$"

