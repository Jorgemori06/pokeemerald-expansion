LittlerootTown_BrendansHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, LittlerootTown_BrendansHouse_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_BrendansHouse_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_BrendansHouse_1F_OnFrame
	.byte 0

LittlerootTown_BrendansHouse_1F_OnLoad:
	call_if_lt VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes
	call_if_set FLAG_RECEIVED_RUNNING_SHOES, LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual
	end

LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes::
	setmetatile 5, 4, METATILE_BrendansMaysHouse_MovingBox_Open, TRUE
	setmetatile 5, 2, METATILE_BrendansMaysHouse_MovingBox_Closed, TRUE
	return

LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual
	return

LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual::
	setmetatile 3, 7, METATILE_BrendansMaysHouse_BookOnTable, TRUE
	return

LittlerootTown_BrendansHouse_1F_OnTransition:
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV
	end

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs::
	setobjectxyperm LOCALID_PLAYERS_HOUSE_1F_MOM, 8, 4
	setobjectmovementtype LOCALID_PLAYERS_HOUSE_1F_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV::
	setobjectxyperm LOCALID_PLAYERS_HOUSE_1F_MOM, 4, 5
	setobjectmovementtype LOCALID_PLAYERS_HOUSE_1F_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor::
	setobjectxyperm LOCALID_PLAYERS_HOUSE_1F_MOM, 9, 8
	setobjectmovementtype LOCALID_PLAYERS_HOUSE_1F_MOM, MOVEMENT_TYPE_FACE_UP
	return

@ Many of the below scripts have no gender check because they assume youre in the correct house
@ The below SS Ticket script uses Mays house state by accident(?), but theyre both set identically after the intro
LittlerootTown_BrendansHouse_1F_OnFrame:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 1, LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 3, PlayersHouse_1F_EventScript_GetSSTicketAndSeeLatiTV
	.2byte 0

LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock::
	lockall
	msgbox PlayersHouse_1F_Text_GoSetTheClock, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	applymovement LOCALID_PLAYERS_HOUSE_1F_MOM, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	waitmovement 0
	warp MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F, 7, 1
	waitstate
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs:
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn::
	lockall
	setvar VAR_0x8004, LOCALID_PLAYERS_HOUSE_1F_MOM
	setvar VAR_0x8005, MALE
	goto PlayersHouse_1F_EventScript_EnterHouseMovingIn
	end

LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport::
	lockall
	setvar VAR_0x8004, MALE
	setvar VAR_0x8005, LOCALID_PLAYERS_HOUSE_1F_MOM
	goto PlayersHouse_1F_EventScript_PetalburgGymReportMale
	end

LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor::
	lockall
	playse SE_PIN
	applymovement LOCALID_RIVALS_HOUSE_1F_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVALS_HOUSE_1F_MOM, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_RIVALS_HOUSE_1F_MOM, LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach
	waitmovement 0
	special GetRivalSonDaughterString
	msgbox RivalsHouse_1F_Text_OhYoureTheNewNeighbor, MSGBOX_DEFAULT
	setflag FLAG_MET_RIVAL_MOM
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 2
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_GoSeeRoom::
	lockall
	setvar VAR_0x8004, LOCALID_PLAYERS_HOUSE_1F_MOM
	setvar VAR_0x8005, MALE
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto PlayersHouse_1F_EventScript_MomGoSeeRoom
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival0::
	lockall
	setvar VAR_0x8008, 0
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival1::
	lockall
	setvar VAR_0x8008, 1
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival2::
	lockall
	setvar VAR_0x8008, 2
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival::
	playse SE_EXIT
	delay 10
	addobject LOCALID_RIVALS_HOUSE_1F_RIVAL
	delay 30
	playse SE_PIN
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call_if_ne VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_eq VAR_0x8008, 0, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0
	call_if_eq VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1
	call_if_eq VAR_0x8008, 2, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2
	msgbox RivalsHouse_1F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 0, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0
	call_if_eq VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1
	call_if_eq VAR_0x8008, 2, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2
	playse SE_EXIT
	removeobject LOCALID_RIVALS_HOUSE_1F_RIVAL
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_BRENDAN
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	delay 30
	setvar VAR_LITTLEROOT_RIVAL_STATE, 3
	setvar VAR_LITTLEROOT_TOWN_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0::
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1::
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2::
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1:
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0::
	applymovement LOCALID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1::
	applymovement LOCALID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2::
	applymovement LOCALID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2
	applymovement LOCALID_RIVALS_HOUSE_1F_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0:
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1:
	delay_16
	delay_8
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end

PlayersHouse_1F_Text_IsntItNiceInHere:
	.string "MAMÁ: ¿Ves, {PLAYER}?\n"
	.string "¿A que dentro también es bonito?$"

PlayersHouse_1F_Text_MoversPokemonGoSetClock:
	.string "Los POKéMON de la mudanza lo han\n"
	.string "metido y limpiado todo.\l"
	.string "¡Qué cómodo!\p"
	.string "{PLAYER}, tu habitación está arriba.\n"
	.string "¡Ve a echarle un vistazo, cielo!\p"
	.string "PAPÁ te ha comprado un reloj nuevo\n"
	.string "por la mudanza.\l"
	.string "¡No te olvides de ponerlo en hora!$"

PlayersHouse_1F_Text_ArentYouInterestedInRoom:
	.string "MAMÁ: ¿Qué pasa, {PLAYER}?\p"
	.string "¿No quieres ver tu propia\n"
	.string "habitación?$"

PlayersHouse_1F_Text_GoSetTheClock:
	.string "MAMÁ: {PLAYER}.\p"
	.string "Ve a poner en hora el reloj de tu\n"
	.string "habitación, cielo.$"

PlayersHouse_1F_Text_OhComeQuickly:
	.string "MAMÁ: ¡Oh! ¡{PLAYER}, {PLAYER}!\n"
	.string "¡Rápido! ¡Ven corriendo!$"

PlayersHouse_1F_Text_MaybeDadWillBeOn:
	.string "MAMÁ: ¡Mira! ¡Es el GIMNASIO PETALIA!\n"
	.string "¡A lo mejor sale PAPÁ!$"

PlayersHouse_1F_Text_ItsOverWeMissedHim:
	.string "MAMÁ: Oh… Ya ha terminado.\p"
	.string "Creo que ha salido PAPÁ, pero nos\n"
	.string "lo hemos perdido. ¡Qué pena!$"

PlayersHouse_1F_Text_GoIntroduceYourselfNextDoor:
	.string "Ah, sí.\n"
	.string "Un amigo de PAPÁ vive en el pueblo.\p"
	.string "Se llama PROF. ABEDUL.\p"
	.string "Vive justo al lado, así que deberías\n"
	.string "ir a presentarte.$"

PlayersHouse_1F_Text_SeeYouHoney:
	.string "MAMÁ: ¡Hasta luego, cielo!$"

PlayersHouse_1F_Text_DidYouMeetProfBirch:
	.string "MAMÁ: ¿Te has presentado al\n"
	.string "PROF. ABEDUL?$"

PlayersHouse_1F_Text_YouShouldRestABit:
	.string "MAMÁ: ¿Qué tal, {PLAYER}?\n"
	.string "Pareces un poco cansado.\p"
	.string "Creo que deberías descansar un poco.$"

PlayersHouse_1F_Text_TakeCareHoney:
	.string "MAMÁ: ¡Cuídate, cielo!$"

PlayersHouse_1F_Text_GotDadsBadgeHeresSomethingFromMom:
	.string "MAMÁ: ¿Esa MEDALLA te la ha dado PAPÁ?\p"
	.string "¡Pues aquí tienes algo de tu MAMÁ!$"

PlayersHouse_1F_Text_DontPushYourselfTooHard:
	.string "No te esfuerces demasiado, cielo.\n"
	.string "Siempre puedes volver a casa.\p"
	.string "¡A por ellos!$"

PlayersHouse_1F_Text_IsThatAPokenav:
	.string "MAMÁ: ¿Qué es eso, cielo? ¿Un POKéNAV?\n"
	.string "¿Te lo ha dado alguien de DEVON?\p"
	.string "Bueno, cielo, ¿por qué no registras\n"
	.string "a tu mamá?\p"
	.string "… … …$"

PlayersHouse_1F_Text_RegisteredMom:
	.string "Has registrado a MAMÁ\n"
	.string "en el POKéNAV.$"

PlayersHouse_1F_Text_Vigoroth1:
	.string "¡Fugiiiiih!$"

PlayersHouse_1F_Text_Vigoroth2:
	.string "Huggoh, uggo uggo…$"

PlayersHouse_1F_Text_ReportFromPetalburgGym:
	.string "REPORTERA: …Les hemos ofrecido este\n"
	.string "reportaje desde el GIMNASIO PETALIA.$"

PlayersHouse_1F_Text_TheresAMovieOnTV:
	.string "Están echando una película.\p"
	.string "Dos hombres bailan sobre el teclado\n"
	.string "de un piano gigante.\p"
	.string "¡Hay que ponerse en marcha!$"

PlayersHouse_1F_Text_RunningShoesManual:
	.string "Es el folleto de instrucciones de\n"
	.string "las DEPORTIVAS.\p"
	.string "“Pulsa el Botón B para correr con\n"
	.string "las DEPORTIVAS puestas.\p"
	.string "”¡Átate las DEPORTIVAS y sal\n"
	.string "corriendo!”$"

PlayersHouse_1F_Text_TicketFromBrineyCameForYou:
	.string "PAPÁ: ¿Mm?\p"
	.string "¡Anda, si es {PLAYER}!\p"
	.string "Hacía tiempo que no te veía, pero\n"
	.string "te veo… más fuerte, no sé.\p"
	.string "Esa es la impresión que me das.\n"
	.string "¡Pero tu viejo aún no se rinde!\p"
	.string "Ah, sí, tengo algo para ti.\n"
	.string "Te lo ha enviado un tal\l"
	.string "SR. ARENQUE.$"

PlayersHouse_1F_Text_PortsInSlateportLilycove:
	.string "PAPÁ: Mm, ¿un BILLETE de ferry?\p"
	.string "Si no recuerdo mal, hay puertos en\n"
	.string "CIUDAD PORTUAL y CIUDAD CALAGUA.$"

PlayersHouse_1F_Text_BetterGetBackToGym:
	.string "Tengo que volver al GIMNASIO PETALIA.\p"
	.string "MAMÁ, gracias por cuidar de la casa\n"
	.string "mientras estoy fuera.$"

PlayersHouse_1F_Text_DadShouldStayLonger:
	.string "MAMÁ: Tu padre…\p"
	.string "Viene a casa después de mucho\n"
	.string "tiempo y solo habla de POKéMON.\p"
	.string "Debería relajarse y quedarse más.$"

PlayersHouse_1F_Text_IsThatABreakingStory:
	.string "MAMÁ: ¿Es una noticia de última hora?$"

PlayersHouse_1F_Text_LatiEmergencyNewsFlash:
	.string "¡Interrumpimos la emisión para dar\n"
	.string "una noticia urgente!\p"
	.string "En varios lugares de HOENN se ha visto\n"
	.string "un POKéMON de color BZZT…\l"
	.string "surcando el cielo.\p"
	.string "De momento no se sabe de qué\n"
	.string "POKéMON se trata.\p"
	.string "Ahora seguimos con la película.$"

PlayersHouse_1F_Text_WhatColorDidTheySay:
	.string "MAMÁ: {PLAYER}, ¿lo has oído?\p"
	.string "¿De qué color ha dicho el locutor\n"
	.string "que era ese POKéMON?$"

PlayersHouse_1F_Text_StillUnknownPokemon:
	.string "MAMÁ: ¡Vaya, qué cosas!\n"
	.string "Todavía hay POKéMON desconocidos.$"
