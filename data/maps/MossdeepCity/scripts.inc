MossdeepCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_OnTransition
	.byte 0

MossdeepCity_OnTransition:
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	end

MossdeepCity_EventScript_PokefanF::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_PokefanFMagmaGone
	msgbox MossdeepCity_Text_SpaceCenterReceivedLetter, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_PokefanFMagmaGone::
	msgbox MossdeepCity_Text_SpaceCenterLaunchingRockets, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_Sailor::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_SailorMagmaGone
	msgbox MossdeepCity_Text_MossdeepTargetedByMagma, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_SailorMagmaGone::
	msgbox MossdeepCity_Text_FeelReliefOnLand, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_NinjaBoy::
	msgbox MossdeepCity_Text_WailmerWatching, MSGBOX_NPC
	end

MossdeepCity_EventScript_ExpertM::
	msgbox MossdeepCity_Text_LifeNeedsSeaToLive, MSGBOX_NPC
	end

MossdeepCity_EventScript_Girl::
	msgbox MossdeepCity_Text_NiceIfWorldCoveredByFlowers, MSGBOX_NPC
	end

MossdeepCity_EventScript_Woman::
	msgbox MossdeepCity_Text_SpecialSpaceCenterRock, MSGBOX_NPC
	end

MossdeepCity_EventScript_WhiteRock::
	msgbox MossdeepCity_Text_ItsAWhiteRock, MSGBOX_SIGN
	end

MossdeepCity_EventScript_GymSign::
	msgbox MossdeepCity_Text_GymSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_CitySign::
	msgbox MossdeepCity_Text_CitySign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_SpaceCenterSign::
	msgbox MossdeepCity_Text_SpaceCenterSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_VisitedMossdeep::
	setflag FLAG_VISITED_MOSSDEEP_CITY
	setvar VAR_TEMP_1, 1
	end

MossdeepCity_EventScript_TeamMagmaEnterSpaceCenter::
	lockall
	applymovement LOCALID_MOSSDEEP_MAXIE, MossdeepCity_Movement_MaxieGestureToSpaceCenter
	waitmovement 0
	applymovement LOCALID_MOSSDEEP_GRUNT_1, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_2, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_3, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_4, MossdeepCity_Movement_GruntFaceSpaceCenter
	waitmovement 0
	applymovement LOCALID_MOSSDEEP_MAXIE, MossdeepCity_Movement_MaxieEnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_1, MossdeepCity_Movement_Grunt1EnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_2, MossdeepCity_Movement_Grunt2EnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_3, MossdeepCity_Movement_Grunt3EnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_4, MossdeepCity_Movement_Grunt4EnterSpaceCenter
	waitmovement 0
	removeobject LOCALID_MOSSDEEP_MAXIE
	removeobject LOCALID_MOSSDEEP_GRUNT_1
	removeobject LOCALID_MOSSDEEP_GRUNT_2
	removeobject LOCALID_MOSSDEEP_GRUNT_3
	removeobject LOCALID_MOSSDEEP_GRUNT_4
	delay 30
	setvar VAR_MOSSDEEP_CITY_STATE, 2
	setflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	releaseall
	end

MossdeepCity_Movement_MaxieGestureToSpaceCenter:
	delay_16
	face_right
	delay_16
	delay_16
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_GruntFaceSpaceCenter:
	face_right
	delay_16
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_MaxieEnterSpaceCenter:
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt1EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt2EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt3EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt4EnterSpaceCenter:
	delay_16
	delay_8
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_EventScript_Man::
	lock
	faceplayer
	msgbox MossdeepCity_Text_SurfExhilarating, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_EventScript_KingsRockBoy::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_KINGS_ROCK, MossdeepCity_EventScript_ReceivedKingsRock
	msgbox MossdeepCity_Text_WantKingsRockStevenGaveMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_EventScript_DeclineKingsRock
	msgbox MossdeepCity_Text_YouCanKeepIt, MSGBOX_DEFAULT
	giveitem ITEM_KINGS_ROCK
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_KINGS_ROCK
	release
	end

MossdeepCity_EventScript_ReceivedKingsRock::
	msgbox MossdeepCity_Text_StevensHouseOverThere, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_DeclineKingsRock::
	msgbox MossdeepCity_Text_WhatToDoWithWeirdRock, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_BlackBelt::
	msgbox MossdeepCity_Text_SootopolisNewGymLeader, MSGBOX_NPC
	end

MossdeepCity_EventScript_Scott::
	lock
	faceplayer
	msgbox MossdeepCity_Text_ScottSomethingWrongWithTown, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, MossdeepCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MossdeepCity_EventScript_ScottExitEast
	addvar VAR_SCOTT_STATE, 1
	removeobject LOCALID_MOSSDEEP_SCOTT
	release
	end

MossdeepCity_EventScript_ScottExitNorth::
	applymovement LOCALID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_MOSSDEEP_SCOTT, MossdeepCity_Movement_ScottExitNorth
	waitmovement 0
	return

MossdeepCity_EventScript_ScottExitEast::
	applymovement LOCALID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_MOSSDEEP_SCOTT, MossdeepCity_Movement_ScottExitEast
	waitmovement 0
	return

MossdeepCity_Movement_PlayerWatchScottExit:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MossdeepCity_Movement_ScottExitNorth:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Movement_ScottExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Text_WantKingsRockStevenGaveMe:
	.string "Me lo dio MÁXIMO, pero no sé para\n"
	.string "qué sirve.\p"
	.string "Creo que se llama ROCA DEL REY.\n"
	.string "¿La quieres?$"

MossdeepCity_Text_YouCanKeepIt:
	.string "¿Para qué la quieres?\n"
	.string "Qué gustos más raros.\p"
	.string "Te la puedes quedar, pero no se lo\n"
	.string "digas a MÁXIMO.$"

MossdeepCity_Text_StevensHouseOverThere:
	.string "¡La casa de MÁXIMO está ahí mismo!$"

MossdeepCity_Text_WhatToDoWithWeirdRock:
	.string "¡Sí, tú también lo piensas! ¿Qué se\n"
	.string "supone que haces con una roca rara?$"

MossdeepCity_Text_WailmerWatching:
	.string "Por ALGARIA se ven WAILMER salvajes.\p"
	.string "Se llama, eh…\n"
	.string "¿Cómo era…?\p"
	.string "WAI, WAI, WAI…\p"
	.string "¡Avistamiento de WAILMER!$"

MossdeepCity_Text_SpaceCenterReceivedLetter:
	.string "El CENTRO ESPACIAL de la isla lanza\n"
	.string "cohetes enormes.\p"
	.string "Últimamente hay mucho revuelo por\n"
	.string "una carta que han recibido.$"

MossdeepCity_Text_SpaceCenterLaunchingRockets:
	.string "El CENTRO ESPACIAL de la isla lanza\n"
	.string "cohetes enormes.$"

MossdeepCity_Text_MossdeepTargetedByMagma:
	.string "Un amigo MARINERO me ha dicho que el\n"
	.string "EQUIPO AQUA se instaló en CALAGUA.\p"
	.string "¡Y también que alguien llegó y los\n"
	.string "dejó por los suelos!\p"
	.string "Pero ALGARIA está en el punto de mira\n"
	.string "del EQUIPO MAGMA.\p"
	.string "Si quieres saber qué traman, ve al\n"
	.string "CENTRO ESPACIAL.$"

MossdeepCity_Text_FeelReliefOnLand:
	.string "Soy MARINERO, así que el mar es lo más\n"
	.string "importante para mí, claro.\p"
	.string "¿Pero sabes qué? ¡Cuando vuelvo a\n"
	.string "tierra tras un viaje largo, me alivia!$"

MossdeepCity_Text_NiceIfWorldCoveredByFlowers:
	.string "¿No sería bonito?\p"
	.string "¿Que el mundo entero estuviera\n"
	.string "cubierto de plantas y flores como\l"
	.string "esta isla?$"

MossdeepCity_Text_LifeNeedsSeaToLive:
	.string "Toda la vida necesita el mar, aunque\n"
	.string "viva en tierra.\p"
	.string "La vida, cuando termina, se hace\n"
	.string "tierra y vuelve a la tierra.\p"
	.string "Y el mar siempre está unido a la\n"
	.string "tierra.\p"
	.string "Sí, como esta misma orilla.$"

MossdeepCity_Text_SurfExhilarating:
	.string "Un viaje en barco está bien.\p"
	.string "Pero cruzar el mar con POKéMON\n"
	.string "usando SURF…\p"
	.string "¡Eso sí que es un viaje emocionante!\n"
	.string "¿No te parece, joven?$"

MossdeepCity_Text_SpecialSpaceCenterRock:
	.string "Esta roca es muy especial para la\n"
	.string "gente del CENTRO ESPACIAL.\p"
	.string "La pusieron aquí para pedir que sus\n"
	.string "cohetes vuelen sin problemas.\p"
	.string "Cuando pides un deseo, ¿qué usas?\n"
	.string "¿Se lo pides a una estrella?\p"
	.string "Yo uso un amuleto de los deseos.\n"
	.string "Eso es lo que hago.$"

MossdeepCity_Text_ItsAWhiteRock:
	.string "Es una roca blanca.$"

MossdeepCity_Text_GymSign:
	.string "GIMNASIO POKéMON DE ALGARIA\n"
	.string "LÍDERES: VITO y LETI\l"
	.string "“¡La combinación mística!”$"

MossdeepCity_Text_CitySign:
	.string "CIUDAD ALGARIA\n"
	.string "“Nuestro lema: ¡Quiere a los POKéMON!”$"

MossdeepCity_Text_SpaceCenterSign:
	.string "CENTRO ESPACIAL DE ALGARIA\n"
	.string "“El lugar más cercano al espacio”.$"

MossdeepCity_Text_ScottSomethingWrongWithTown:
	.string "SCOTT: {PLAYER}{KUN}, ¿qué tal?\n"
	.string "¡Yo genial!\p"
	.string "Había oído que el LÍDER de ALGARIA\n"
	.string "es bastante fuerte, así que he\l"
	.string "venido a verlo con mis ojos.\p"
	.string "Pero en este pueblo pasa algo raro.\p"
	.string "La gente no para de hablar de una\n"
	.string "carta de amenaza y del CENTRO…\p"
	.string "Aunque no creo que tenga nada que\n"
	.string "ver conmigo.$"

MossdeepCity_Text_SootopolisNewGymLeader:
	.string "Aaah… Qué gusto que las olas te\n"
	.string "mojen los pies…\p"
	.string "Hablando de olas, ¿conoces la ciudad\n"
	.string "de la isla, ARRECÍPOLIS?\p"
	.string "Creo que su GIMNASIO tiene un\n"
	.string "LÍDER nuevo.\p"
	.string "Dicen que el nuevo LÍDER fue el\n"
	.string "maestro de PLUBIO.$"

