Route110_TrickHouseEnd_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Route110_TrickHouseEnd_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_TrickHouseEnd_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route110_TrickHouseEnd_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route110_TrickHouseEnd_OnWarp
	.byte 0

Route110_TrickHouseEnd_OnResume:
	call_if_eq VAR_TEMP_1, 1, Route110_TrickHouseEnd_EventScript_SetDoorClosedMetatile
	end

Route110_TrickHouseEnd_OnTransition:
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	special SetTrickHouseNuggetFlag
	end

Route110_TrickHouseEnd_OnWarp:
	map_script_2 VAR_TEMP_2, 0, Route110_TrickHouseEnd_EventScript_SetTrickMasterPos
	.2byte 0

Route110_TrickHouseEnd_EventScript_SetTrickMasterPos::
	addobject LOCALID_TRICK_MASTER_END
	showobjectat LOCALID_TRICK_MASTER_END, MAP_ROUTE110_TRICK_HOUSE_END
	turnobject LOCALID_TRICK_MASTER_END, DIR_EAST
	end

Route110_TrickHouseEnd_OnFrame:
	map_script_2 VAR_TEMP_1, 0, Route110_TrickHouseEnd_EventScript_CloseDoor
	.2byte 0

Route110_TrickHouseEnd_EventScript_CloseDoor::
	setvar VAR_TEMP_1, 1
	call Route110_TrickHouseEnd_EventScript_SetDoorClosedMetatile
	special DrawWholeMapView
	end

Route110_TrickHouseEnd_EventScript_SetDoorClosedMetatile::
	setmetatile 10, 1, METATILE_GenericBuilding_TrickHouse_Door_Closed, TRUE
	return

Route110_TrickHouseEnd_EventScript_TrickMaster::
	lock
	faceplayer
	msgbox Route110_TrickHouseEnd_Text_YouveMadeItToMe, MSGBOX_DEFAULT
	setvar VAR_TEMP_2, 1
	switch VAR_TRICK_HOUSE_LEVEL
	case 0, Route110_TrickHouseEnd_EventScript_CompletedPuzzle1
	case 1, Route110_TrickHouseEnd_EventScript_CompletedPuzzle2
	case 2, Route110_TrickHouseEnd_EventScript_CompletedPuzzle3
	case 3, Route110_TrickHouseEnd_EventScript_CompletedPuzzle4
	case 4, Route110_TrickHouseEnd_EventScript_CompletedPuzzle5
	case 5, Route110_TrickHouseEnd_EventScript_CompletedPuzzle6
	case 6, Route110_TrickHouseEnd_EventScript_CompletedPuzzle7
	case 7, Route110_TrickHouseEnd_EventScript_CompletedPuzzle8
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle1::
	msgbox Route110_TrickHouseEnd_Text_AllNightToPlantTrees, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_RARE_CANDY
	call_if_eq VAR_RESULT, FALSE, Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle2::
	msgbox Route110_TrickHouseEnd_Text_AllNightToMakeMaze, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_TIMER_BALL
	call_if_eq VAR_RESULT, FALSE, Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle3::
	msgbox Route110_TrickHouseEnd_Text_AllNightToPreparePanels, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_HARD_STONE
	call_if_eq VAR_RESULT, FALSE, Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle4::
	msgbox Route110_TrickHouseEnd_Text_AllNightToShoveBoulders, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_SMOKE_BALL
	call_if_eq VAR_RESULT, FALSE, Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle5::
	msgbox Route110_TrickHouseEnd_Text_AllNightToMakeMechadolls, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_TM_TAUNT
	call_if_eq VAR_RESULT, FALSE, Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle6::
	msgbox Route110_TrickHouseEnd_Text_AllNightToInstallDoors, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_MAGNET
	call_if_eq VAR_RESULT, FALSE, Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle7::
	msgbox Route110_TrickHouseEnd_Text_AllNightSettingUpArrows, MSGBOX_DEFAULT
	msgbox Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	giveitem ITEM_PP_MAX
	call_if_eq VAR_RESULT, FALSE, Route110_TrickHouseEnd_EventScript_BagFull
	msgbox Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou, MSGBOX_DEFAULT
	closemessage
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	release
	end

Route110_TrickHouseEnd_EventScript_CompletedPuzzle8::
	msgbox Route110_TrickHouseEnd_Text_AllNightPolishingFloors, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_SOUTH, Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwaySouth
	call_if_eq VAR_FACING, DIR_NORTH, Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayNorth
	call_if_eq VAR_FACING, DIR_WEST, Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayWest
	call_if_eq VAR_FACING, DIR_EAST, Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayEast
	delay 30
	msgbox Route110_TrickHouseEnd_Text_FountainOfIdeasRunDry, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TRICK_MASTER_END, Common_Movement_FacePlayer
	waitmovement 0
	delay 30
	msgbox Route110_TrickHouseEnd_Text_DefeatedMePreferWhichTent, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 0
	call Route110_TrickHouseEnd_EventScript_ChooseTent
	call_if_eq VAR_RESULT, FALSE, Route110_TrickHouseEnd_EventScript_NoRoomForTent
	msgbox Route110_TrickHouseEnd_Text_LeavingOnJourney, MSGBOX_DEFAULT
	call Route110_TrickHouseEnd_EventScript_TrickMasterExit
	special ResetTrickHouseNuggetFlag
	release
	end

Route110_TrickHouseEnd_EventScript_ChooseTent::
	multichoice 0, 0, MULTI_TENT, TRUE
	switch VAR_RESULT
	case 0, Route110_TrickHouseEnd_EventScript_GiveRedTent
	goto Route110_TrickHouseEnd_EventScript_GiveBlueTent

Route110_TrickHouseEnd_EventScript_GiveRedTent::
	givedecoration DECOR_RED_TENT
	return

Route110_TrickHouseEnd_EventScript_GiveBlueTent::
	givedecoration DECOR_BLUE_TENT
	return

Route110_TrickHouseEnd_EventScript_TrickMasterExit::
	applymovement LOCALID_TRICK_MASTER_END, Route110_TrickHouse_Movement_TrickMasterSpin
	waitmovement 0
	playse SE_M_EXPLOSION
	applymovement LOCALID_TRICK_MASTER_END, Route110_TrickHouse_Movement_TrickMasterJumpAway
	waitmovement 0
	removeobject LOCALID_TRICK_MASTER_END
	addvar VAR_TRICK_HOUSE_LEVEL, 1
	return

Route110_TrickHouseEnd_EventScript_BagFull::
	call Common_EventScript_BagIsFull
	msgbox Route110_TrickHouseEnd_Text_NoRoomForThis, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 1
	return

Route110_TrickHouseEnd_EventScript_NoRoomForTent::
	call Common_EventScript_NoRoomForDecor
	msgbox Route110_TrickHouseEnd_Text_NoRoomInPC, MSGBOX_DEFAULT
	setvar VAR_TRICK_HOUSE_PRIZE_PICKUP, 1
	return

Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwaySouth::
	applymovement LOCALID_TRICK_MASTER_END, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayNorth::
	applymovement LOCALID_TRICK_MASTER_END, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayWest::
	applymovement LOCALID_TRICK_MASTER_END, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

Route110_TrickHouseEnd_EventScript_TrickMasterFaceAwayEast::
	applymovement LOCALID_TRICK_MASTER_END, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

Route110_TrickHouseEnd_EventScript_TrickMasterExitTrigger::
	lockall
	turnobject LOCALID_TRICK_MASTER_END, DIR_WEST
	playse SE_PIN
	applymovement LOCALID_TRICK_MASTER_END, Common_Movement_ExclamationMark
	waitmovement 0
	delay 20
	applymovement LOCALID_TRICK_MASTER_END, Route110_TrickHouseEnd_Movement_TrickMasterSurprise
	waitmovement 0
	playse SE_M_EXPLOSION
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox Route110_TrickHouseEnd_Text_YoureIgnoringMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Route110_TrickHouseEnd_Movement_KeepPlayerInRoom
	waitmovement 0
	delay 4
	turnobject LOCALID_TRICK_MASTER_END, DIR_EAST
	releaseall
	end

Route110_TrickHouseEnd_Movement_KeepPlayerInRoom:
	walk_down
	step_end

Route110_TrickHouseEnd_Movement_TrickMasterSurprise:
	jump_in_place_left
	step_end

Route110_TrickHouseEnd_Text_YouveMadeItToMe:
	.string "¡Aaah!\n"
	.string "¿Has llegado hasta mí?\l"
	.string "Mmm… ¡Menuda vista!$"

Route110_TrickHouseEnd_Text_AllNightToPlantTrees:
	.string "Me pasé toda la noche plantando\n"
	.string "esos árboles…\p"
	.string "¡Casi me igualas en grandeza! ¡Te\n"
	.string "faltan uno, dos, tres, cuatro, cinco,\l"
	.string "seis puestos!$"

Route110_TrickHouseEnd_Text_AllNightToMakeMaze:
	.string "Me pasé toda la noche haciendo\n"
	.string "el laberinto…\p"
	.string "¡Casi me igualas en grandeza! ¡Te\n"
	.string "faltan uno, dos, tres, cuatro, cinco\l"
	.string "puestos!$"

Route110_TrickHouseEnd_Text_AllNightToPreparePanels:
	.string "Me pasé toda la noche preparando\n"
	.string "los paneles de las paredes…\p"
	.string "¡Casi me igualas en grandeza! ¡Te\n"
	.string "faltan uno, dos, tres, cuatro puestos!$"

Route110_TrickHouseEnd_Text_AllNightToShoveBoulders:
	.string "Me pasé toda la noche metiendo\n"
	.string "esas rocas…\p"
	.string "¡Casi me igualas en grandeza! ¡Te\n"
	.string "faltan uno, dos, tres puestos!$"

Route110_TrickHouseEnd_Text_AllNightToMakeMechadolls:
	.string "Me pasé una noche haciendo los\n"
	.string "ROBOMUÑECOS y otra pensando el test…\p"
	.string "¡Casi me igualas en grandeza! ¡Te\n"
	.string "faltan uno, dos puestos!$"

Route110_TrickHouseEnd_Text_AllNightToInstallDoors:
	.string "Me pasé toda la noche instalando\n"
	.string "las puertas…\p"
	.string "¡Casi me igualas en grandeza!$"

Route110_TrickHouseEnd_Text_AllNightSettingUpArrows:
	.string "Me pasé toda la noche poniendo\n"
	.string "flechas…\p"
	.string "¡Me igualas en grandeza!$"

Route110_TrickHouseEnd_Text_AllNightPolishingFloors:
	.string "Me pasé toda la noche puliendo\n"
	.string "los suelos…\p"
	.string "¡Me superas en grandeza!\n"
	.string "Puede…$"

Route110_TrickHouseEnd_Text_FountainOfIdeasRunDry:
	.string "¿Q-qué hago?\n"
	.string "Se me ha secado la fuente de ideas\l"
	.string "para trampas…\p"
	.string "Quizá sea hora de recorrer el país\n"
	.string "en busca de trucos nuevos…$"

Route110_TrickHouseEnd_Text_DefeatedMePreferWhichTent:
	.string "Me duele admitirlo, pero ¡me\n"
	.string "has vencido!\p"
	.string "Aun así, si vienes a verme una y otra\n"
	.string "vez, será por mi carisma.\l"
	.string "¡Seguro que sí!\p"
	.string "¡Pero eso no tiene nada que ver con\n"
	.string "que haya perdido!\p"
	.string "Para celebrar la amistad entre\n"
	.string "alguien tan tenaz como tú y un genio\l"
	.string "como yo, ¡exijo que aceptes este\l"
	.string "recuerdo!\p"
	.string "Bueno, en realidad son dos: una\n"
	.string "TIENDA ROJA y una TIENDA AZUL.\l"
	.string "¿Cuál prefieres?$"

Route110_TrickHouseEnd_Text_NoRoomInPC:
	.string "¿Qué? ¿No tienes sitio en el PC?\n"
	.string "¿Y yo qué hago con eso?\p"
	.string "Me gustaría decirlo, pero soy\n"
	.string "demasiado bueno, ¡así que vuelve luego!$"

Route110_TrickHouseEnd_Text_LeavingOnJourney:
	.string "… … … … … …\p"
	.string "Me voy de viaje a descubrir cosas.\n"
	.string "En busca de trucos nuevos.\p"
	.string "Espero que algún día vuelvas a\n"
	.string "visitarme y me entretengas.\p"
	.string "¡Y ahora, adiós!$"

Route110_TrickHouseEnd_Text_YouHaveEarnedThisReward:
	.string "¡Muy bien!\n"
	.string "¡Te has ganado este premio!$"

Route110_TrickHouseEnd_Text_NoRoomForThis:
	.string "¿Qué? ¿No tienes sitio para esto?\n"
	.string "¿Pero qué cosas llevas encima?\p"
	.string "Bueno, como has llegado hasta mí,\n"
	.string "te guardaré el premio para luego.$"

Route110_TrickHouseEnd_Text_MakeNewTricksToStumpYou:
	.string "¡Quita esa sonrisita de la cara!\n"
	.string "¡Es muy pronto para cantar victoria!\p"
	.string "Prepararé trucos nuevos para\n"
	.string "pillarte, ya verás.\p"
	.string "Solo podrás reírte de mí cuando\n"
	.string "los superes todos.\p"
	.string "¡Vuelve para la próxima entrega!$"

Route110_TrickHouseEnd_Text_YoureIgnoringMe:
	.string "¡Vaya, vaya! ¿Ahora me ignoras?\n"
	.string "¡Eso me rompe el corazón!$"

