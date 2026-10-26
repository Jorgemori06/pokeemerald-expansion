RustboroCity_DevonCorp_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_3F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, RustboroCity_DevonCorp_3F_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RustboroCity_DevonCorp_3F_OnFrame
	.byte 0

RustboroCity_DevonCorp_3F_OnTransition:
	call_if_eq VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_SetEmployeePos
	end

RustboroCity_DevonCorp_3F_EventScript_SetEmployeePos::
	setobjectxyperm LOCALID_DEVON_CORP_3F_EMPLOYEE, 3, 2
	setobjectmovementtype LOCALID_DEVON_CORP_3F_EMPLOYEE, MOVEMENT_TYPE_FACE_LEFT
	return

RustboroCity_DevonCorp_3F_OnWarp:
	map_script_2 VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_PlayerFaceEast
	.2byte 0

RustboroCity_DevonCorp_3F_EventScript_PlayerFaceEast::
	turnobject LOCALID_PLAYER, DIR_EAST
	end

RustboroCity_DevonCorp_3F_OnFrame:
	map_script_2 VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_MeetPresident
	.2byte 0

RustboroCity_DevonCorp_3F_EventScript_MeetPresident::
	lockall
	msgbox RustboroCity_DevonCorp_3F_Text_ThisIs3rdFloorWaitHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeWalkOffscreen
	waitmovement 0
	delay 80
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeReturnToPlayer
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_WordWithPresidentComeWithMe, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_FOLLOW_ME, FALSE
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_LeadPlayerToPresident
	applymovement LOCALID_PLAYER, RustboroCity_DevonCorp_3F_Movement_PlayerFollowToPresident
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_PleaseGoAhead, MSGBOX_DEFAULT
	closemessage
	fadedefaultbgm
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeFaceDesk
	applymovement LOCALID_PLAYER, RustboroCity_DevonCorp_3F_Movement_PlayerApproachDesk
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneIHaveFavor, MSGBOX_DEFAULT
	giveitem ITEM_LETTER
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneWantYouToHaveThis, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_3F_Text_ReceivedPokenav
	waitfanfare
	setflag FLAG_SYS_POKENAV_GET
	setflag FLAG_RECEIVED_POKENAV
	setflag FLAG_HIDE_RUSTBORO_CITY_POKEMON_SCHOOL_SCOTT
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneExplainPokenavRestUp, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneGoWithCautionAndCare, MSGBOX_DEFAULT
	setflag FLAG_HIDE_ROUTE_116_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_WANDA
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setvar VAR_BRINEY_LOCATION, 1
	clearflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	setvar VAR_DEVON_CORP_3F_STATE, 1
	setvar VAR_RUSTBORO_CITY_STATE, 6
	releaseall
	end

RustboroCity_DevonCorp_3F_Movement_Unused:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_left
	step_end

RustboroCity_DevonCorp_3F_Movement_LeadPlayerToPresident:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_left
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeFaceDesk:
	delay_16
	walk_in_place_faster_down
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeWalkOffscreen:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeReturnToPlayer:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

RustboroCity_DevonCorp_3F_Movement_PlayerFollowToPresident:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_PlayerApproachDesk:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

RustboroCity_DevonCorp_3F_EventScript_MrStone::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_EXP_SHARE, RustboroCity_DevonCorp_3F_EventScript_MrStoneAfterFavor
	goto_if_set FLAG_DELIVERED_STEVEN_LETTER, RustboroCity_DevonCorp_3F_EventScript_GiveExpShare
	msgbox RustboroCity_DevonCorp_3F_Text_CountingOnYou, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_GiveExpShare::
	msgbox RustboroCity_DevonCorp_3F_Text_ThankYouForDeliveringLetter, MSGBOX_DEFAULT
	giveitem ITEM_EXP_SHARE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_EXP_SHARE
	msgbox RustboroCity_DevonCorp_3F_Text_ExplainExpShare, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_MrStoneAfterFavor::
	msgbox RustboroCity_DevonCorp_3F_Text_NotFamiliarWithTrends, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_Employee::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_REPEAT_BALL, RustboroCity_DevonCorp_3F_EventScript_EmployeeBalls
	msgbox RustboroCity_DevonCorp_3F_Text_VisitCaptSternShipyard, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_3F_EventScript_EmployeeBalls::
	msgbox RustboroCity_DevonCorp_3F_Text_RepeatAndTimerHugelyPopular, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_3F_EventScript_RareRocksDisplay::
	msgbox RustboroCity_DevonCorp_3F_Text_RareRocksDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_3F_Text_MrStoneIHaveFavor:
	.string "Soy el SR. PEÑA, PRESIDENTE de la\n"
	.string "CORPORACIÓN DEVON.\p"
	.string "¡Me acaban de hablar de ti!\p"
	.string "¡Has salvado a nuestro empleado\n"
	.string "no una, sino dos veces!\p"
	.string "Tengo que pedirle un favor a alguien\n"
	.string "tan increíble como tú.\p"
	.string "Sé que vas a llevar un paquete al\n"
	.string "ASTILLERO de PORTUAL.\p"
	.string "Pues, de camino, ¿podrías pasar\n"
	.string "por PUEBLO AZULIZA?\p"
	.string "Quería que le llevaras una CARTA\n"
	.string "a MÁXIMO, que está en AZULIZA.$"

RustboroCity_DevonCorp_3F_Text_MrStoneWantYouToHaveThis:
	.string "SR. PEÑA: Has de saber que soy\n"
	.string "un gran PRESIDENTE.\p"
	.string "Nunca sería tan rácano como para\n"
	.string "pedir un favor a cambio de nada.\p"
	.string "¡Por eso quiero que tengas esto!$"

RustboroCity_DevonCorp_3F_Text_ReceivedPokenav:
	.string "{PLAYER} ha recibido un POKéNAV.$"

RustboroCity_DevonCorp_3F_Text_MrStoneExplainPokenavRestUp:
	.string "SR. PEÑA: Ese aparato…\p"
	.string "Es un NAVEGADOR POKéMON, o POKéNAV\n"
	.string "para abreviar.\p"
	.string "Es imprescindible para cualquier\n"
	.string "ENTRENADOR que viaje.\p"
	.string "Tiene un mapa de la región de HOENN.\p"
	.string "¡Así verás fácilmente dónde están\n"
	.string "AZULIZA y PORTUAL!\p"
	.string "Por cierto, he oído que unos\n"
	.string "criminales, MAGMA y AQUA, creo,\l"
	.string "dan problemas por todas partes.\p"
	.string "Creo que sería mejor que descansaras\n"
	.string "antes de ponerte en camino.$"

RustboroCity_DevonCorp_3F_Text_MrStoneGoWithCautionAndCare:
	.string "SR. PEÑA: Bueno, {PLAYER}{KUN},\n"
	.string "¡ve con mucho cuidado!$"

RustboroCity_DevonCorp_3F_Text_CountingOnYou:
	.string "SR. PEÑA: ¡Cuento contigo!$"

RustboroCity_DevonCorp_3F_Text_ThankYouForDeliveringLetter:
	.string "SR. PEÑA: ¿Has entregado mi CARTA?\n"
	.string "¡Muchísimas gracias!\p"
	.string "Esto es para darte las gracias.\n"
	.string "Te será útil como ENTRENADOR.$"

RustboroCity_DevonCorp_3F_Text_ExplainExpShare:
	.string "SR. PEÑA: El POKéMON que lleve el\n"
	.string "REPARTIR EXP recibirá parte de\l"
	.string "la EXPERIENCIA del combate.\p"
	.string "La recibirá aunque no haya\n"
	.string "luchado.\p"
	.string "Diría que el REPARTIR EXP es muy útil\n"
	.string "para entrenar POKéMON débiles.$"

RustboroCity_DevonCorp_3F_Text_NotFamiliarWithTrends:
	.string "SR. PEÑA: Desde joven me he volcado\n"
	.string "en el trabajo.\p"
	.string "Por eso no sé mucho de modas\n"
	.string "ni de esas cosas.\p"
	.string "¿Es verdad que todos los jóvenes\n"
	.string "quieren competir en la LIGA POKéMON?$"

RustboroCity_DevonCorp_3F_Text_ThisIs3rdFloorWaitHere:
	.string "Esta es la tercera planta de la\n"
	.string "CORPORACIÓN DEVON.\p"
	.string "En esta planta está el DESPACHO\n"
	.string "de nuestro PRESIDENTE.\p"
	.string "En fin, no sabes lo agradecido que\n"
	.string "estoy por lo que has hecho.\p"
	.string "Eh… Por cierto, ese paquete que\n"
	.string "nos has recuperado…\p"
	.string "¿Podrías llevarlo al ASTILLERO\n"
	.string "de PORTUAL?\p"
	.string "Sería horrible que esos ladrones\n"
	.string "intentaran robarlo otra vez.\p"
	.string "Eh… Jejeje, ¿puedo contar\n"
	.string "contigo para eso?\p"
	.string "Ah, es verdad.\n"
	.string "¿Puedes esperar aquí un momento?$"

RustboroCity_DevonCorp_3F_Text_WordWithPresidentComeWithMe:
	.string "Nuestro PRESIDENTE quiere hablar\n"
	.string "contigo.\p"
	.string "Ven conmigo, por favor.$"

RustboroCity_DevonCorp_3F_Text_PleaseGoAhead:
	.string "Adelante, por favor.$"

RustboroCity_DevonCorp_3F_Text_VisitCaptSternShipyard:
	.string "Si vas al ASTILLERO de PORTUAL,\n"
	.string "deberías ver al CAPITÁN BABOR.$"

RustboroCity_DevonCorp_3F_Text_RepeatAndTimerHugelyPopular:
	.string "Los nuevos productos de DEVON, la\n"
	.string "ACOPIO BALL y la TURNO BALL, son muy\l"
	.string "populares entre los ENTRENADORES.$"

RustboroCity_DevonCorp_3F_Text_RareRocksDisplay:
	.string "Es una colección de rocas y piedras\n"
	.string "raras que ha reunido el PRESIDENTE.$"

