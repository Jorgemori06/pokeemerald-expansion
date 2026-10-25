SlateportCity_Harbor_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SlateportCity_Harbor_OnTransition
	.byte 0

SlateportCity_Harbor_OnTransition:
	setescapewarp MAP_SLATEPORT_CITY, 28, 13
	setvar VAR_TEMP_1, 0
	call_if_eq VAR_SLATEPORT_HARBOR_STATE, 1, SlateportCity_Harbor_EventScript_ReadyAquaEscapeScene
	call_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_Harbor_EventScript_ShowSSTidal
	end

SlateportCity_Harbor_EventScript_ShowSSTidal::
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_SS_TIDAL
	return

SlateportCity_Harbor_EventScript_ReadyAquaEscapeScene::
	savebgm MUS_ENCOUNTER_AQUA
	setobjectxyperm LOCALID_SLATEPORT_HARBOR_CAPT_STERN, 12, 13
	setobjectmovementtype LOCALID_SLATEPORT_HARBOR_CAPT_STERN, MOVEMENT_TYPE_FACE_LEFT
	setflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_PATRONS
	return

SlateportCity_Harbor_EventScript_AquaEscapeTrigger0::
	lockall
	setvar VAR_0x8008, 0
	goto SlateportCity_Harbor_EventScript_AquaEscapeScene
	end

SlateportCity_Harbor_EventScript_AquaEscapeTrigger1::
	lockall
	setvar VAR_0x8008, 1
	goto SlateportCity_Harbor_EventScript_AquaEscapeScene
	end

SlateportCity_Harbor_EventScript_AquaEscapeTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto SlateportCity_Harbor_EventScript_AquaEscapeScene
	end

SlateportCity_Harbor_EventScript_AquaEscapeTrigger3::
	lockall
	setvar VAR_0x8008, 3
	applymovement LOCALID_PLAYER, SlateportCity_Harbor_Movement_PlayerWalkUp
	waitmovement 0
	goto SlateportCity_Harbor_EventScript_AquaEscapeScene
	end

SlateportCity_Harbor_EventScript_AquaEscapeScene::
	applymovement LOCALID_SLATEPORT_HARBOR_ARCHIE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_SLATEPORT_HARBOR_GRUNT, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_Harbor_Text_ArchieYouAgainHideoutInLilycove, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_HARBOR_GRUNT, SlateportCity_Harbor_Movement_AquaBoardSub
	applymovement LOCALID_SLATEPORT_HARBOR_ARCHIE, SlateportCity_Harbor_Movement_AquaBoardSub
	applymovement LOCALID_SLATEPORT_HARBOR_SUBMARINE, SlateportCity_Harbor_Movement_SubmarineExit
	waitmovement 0
	removeobject LOCALID_SLATEPORT_HARBOR_GRUNT
	removeobject LOCALID_SLATEPORT_HARBOR_ARCHIE
	removeobject LOCALID_SLATEPORT_HARBOR_SUBMARINE
	setvar VAR_SLATEPORT_HARBOR_STATE, 2
	setflag FLAG_MET_TEAM_AQUA_HARBOR
	setflag FLAG_HIDE_LILYCOVE_MOTEL_SCOTT
	call_if_eq VAR_0x8008, 0, SlateportCity_Harbor_EventScript_SternApproachPlayer0
	call_if_eq VAR_0x8008, 1, SlateportCity_Harbor_EventScript_SternApproachPlayer1
	call_if_eq VAR_0x8008, 2, SlateportCity_Harbor_EventScript_SternApproachPlayer
	call_if_eq VAR_0x8008, 3, SlateportCity_Harbor_EventScript_SternApproachPlayer
	msgbox SlateportCity_Harbor_Text_CaptSternWhyStealMySubmarine, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HIDE_AQUA_HIDEOUT_1F_GRUNT_1_BLOCKING_ENTRANCE
	setflag FLAG_HIDE_AQUA_HIDEOUT_1F_GRUNT_2_BLOCKING_ENTRANCE
	copyobjectxytoperm LOCALID_SLATEPORT_HARBOR_CAPT_STERN
	setobjectmovementtype LOCALID_SLATEPORT_HARBOR_CAPT_STERN, MOVEMENT_TYPE_FACE_RIGHT
	releaseall
	end

SlateportCity_Harbor_EventScript_SternApproachPlayer0::
	applymovement LOCALID_SLATEPORT_HARBOR_CAPT_STERN, SlateportCity_Harbor_Movement_SternApproachPlayer0
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

SlateportCity_Harbor_EventScript_SternApproachPlayer1::
	applymovement LOCALID_SLATEPORT_HARBOR_CAPT_STERN, SlateportCity_Harbor_Movement_SternApproachPlayer1
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

SlateportCity_Harbor_EventScript_SternApproachPlayer::
	applymovement LOCALID_SLATEPORT_HARBOR_CAPT_STERN, SlateportCity_Harbor_Movement_SternApproachPlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

SlateportCity_Harbor_Movement_AquaBoardSub:
	delay_16
	delay_16
	jump_up
	set_invisible
	step_end

@ Unused, Archie instead shares above identical movement script with Grunt
SlateportCity_Harbor_Movement_ArchieBoardSub:
	delay_16
	delay_16
	jump_up
	set_invisible
	step_end

SlateportCity_Harbor_Movement_SubmarineExit:
	delay_16
	delay_16
	delay_16
	delay_16
	walk_right
	walk_right
	walk_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

SlateportCity_Harbor_Movement_SternApproachPlayer0:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

SlateportCity_Harbor_Movement_SternApproachPlayer1:
	walk_left
	walk_left
	walk_up
	walk_left
	step_end

SlateportCity_Harbor_Movement_SternApproachPlayer:
	walk_left
	walk_left
	walk_left
	step_end

SlateportCity_Harbor_Movement_PlayerWalkUp:
	walk_up
	step_end

SlateportCity_Harbor_EventScript_FerryAttendant::
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_Harbor_EventScript_AskForTicket
	msgbox SlateportCity_Harbor_Text_FerryServiceUnavailable, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_AskForTicket::
	msgbox SlateportCity_Harbor_Text_MayISeeYourTicket, MSGBOX_DEFAULT
	message SlateportCity_Harbor_Text_FlashedTicketWhereTo
	waitmessage
	goto SlateportCity_Harbor_EventScript_ChooseDestination
	end

SlateportCity_Harbor_EventScript_ChooseDestination::
	goto_if_set FLAG_MET_SCOTT_ON_SS_TIDAL, SlateportCity_Harbor_EventScript_ChooseDestinationWithBattleFrontier
	multichoicedefault 18, 8, MULTI_SSTIDAL_SLATEPORT_NO_BF, 2, FALSE
	switch VAR_RESULT
	case 0, SlateportCity_Harbor_EventScript_Lilycove
	case 1, SlateportCity_Harbor_EventScript_CancelDestinationSelect
	case MULTI_B_PRESSED, SlateportCity_Harbor_EventScript_CancelDestinationSelect
	end

SlateportCity_Harbor_EventScript_ChooseDestinationWithBattleFrontier::
	multichoicedefault 17, 6, MULTI_SSTIDAL_SLATEPORT_WITH_BF, 2, FALSE
	switch VAR_RESULT
	case 0, SlateportCity_Harbor_EventScript_Lilycove
	case 1, SlateportCity_Harbor_EventScript_BattleFrontier
	case 2, SlateportCity_Harbor_EventScript_CancelDestinationSelect
	case MULTI_B_PRESSED, SlateportCity_Harbor_EventScript_CancelDestinationSelect
	end

@ Unused. Should be impossible for player to reach Ferry without having received SS Tidal ticket
SlateportCity_Harbor_EventScript_NoTicket::
	msgbox SlateportCity_Harbor_Text_YouMustHaveTicket, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_Lilycove::
	msgbox SlateportCity_Harbor_Text_LilycoveItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SlateportCity_Harbor_EventScript_ChooseNewDestination
	setvar VAR_SS_TIDAL_STATE, SS_TIDAL_BOARD_SLATEPORT
	call SlateportCity_Harbor_EventScript_BoardFerry
	warp MAP_SS_TIDAL_CORRIDOR, 1, 10
	waitstate
	release
	end

SlateportCity_Harbor_EventScript_BattleFrontier::
	msgbox SlateportCity_Harbor_Text_BattleFrontierItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SlateportCity_Harbor_EventScript_ChooseNewDestination
	call SlateportCity_Harbor_EventScript_BoardFerry
	warp MAP_BATTLE_FRONTIER_OUTSIDE_WEST, 19, 67
	waitstate
	release
	end

SlateportCity_Harbor_EventScript_ChooseNewDestination::
	message SlateportCity_Harbor_Text_WhereWouldYouLikeToGo
	waitmessage
	goto SlateportCity_Harbor_EventScript_ChooseDestination
	end

SlateportCity_Harbor_EventScript_BoardFerry::
	msgbox SlateportCity_Harbor_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 30
	hideobjectat VAR_LAST_TALKED, MAP_SLATEPORT_CITY_HARBOR
	call_if_eq VAR_FACING, DIR_NORTH, SlateportCity_Harbor_EventScript_BoardFerryNorth
	call_if_eq VAR_FACING, DIR_EAST, SlateportCity_Harbor_EventScript_BoardFerryEast
	delay 30
	hideplayer
	setvar VAR_0x8004, LOCALID_SLATEPORT_HARBOR_SS_TIDAL
	call Common_EventScript_FerryDepart
	return

SlateportCity_Harbor_EventScript_CancelDestinationSelect::
	msgbox SlateportCity_Harbor_Text_SailAnotherTime, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_BoardFerryEast::
	applymovement LOCALID_PLAYER, SlateportCity_Harbor_Movement_BoardFerryEast
	waitmovement 0
	return

SlateportCity_Harbor_EventScript_BoardFerryNorth::
	applymovement LOCALID_PLAYER, SlateportCity_Harbor_Movement_BoardFerryNorth
	waitmovement 0
	return

SlateportCity_Harbor_Movement_BoardFerryEast:
	walk_right
	walk_in_place_faster_up
	step_end

SlateportCity_Harbor_Movement_BoardFerryNorth:
	walk_up
	step_end

SlateportCity_Harbor_EventScript_Sailor::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, SlateportCity_Harbor_EventScript_SailorNoAbnormalWeather
	setvar VAR_0x8004, 0
	call_if_set FLAG_DEFEATED_KYOGRE, SlateportCity_Harbor_EventScript_CountDefeatedLegendary
	call_if_set FLAG_DEFEATED_GROUDON, SlateportCity_Harbor_EventScript_CountDefeatedLegendary
	goto_if_eq VAR_0x8004, 2, SlateportCity_Harbor_EventScript_SailorNoAbnormalWeather  @ Defeated both
	msgbox SlateportCity_Harbor_Text_AbnormalWeather, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_SailorNoAbnormalWeather::
	msgbox SlateportCity_Harbor_Text_LoveToGoDeepUnderwaterSomeday, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_CountDefeatedLegendary::
	addvar VAR_0x8004, 1
	return

SlateportCity_Harbor_EventScript_FatMan::
	msgbox SlateportCity_Harbor_Text_SubTooSmallForMe, MSGBOX_NPC
	end

SlateportCity_Harbor_EventScript_CaptStern::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, SlateportCity_Harbor_EventScript_CaptSternFerryOrScannerComment
	goto_if_set FLAG_EVIL_TEAM_ESCAPED_STERN_SPOKE, SlateportCity_Harbor_EventScript_NeedDive
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, SlateportCity_Harbor_EventScript_TeamAquaLeftNeedDive
	goto_if_eq VAR_SLATEPORT_HARBOR_STATE, 2, SlateportCity_Harbor_EventScript_WhyStealSubmarine
	msgbox SlateportCity_Harbor_Text_SameThugsTriedToRobAtMuseum, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_Harbor_EventScript_WhyStealSubmarine::
	msgbox SlateportCity_Harbor_Text_CaptSternWhyStealMySubmarine, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_TeamAquaLeftNeedDive::
	setflag FLAG_EVIL_TEAM_ESCAPED_STERN_SPOKE
	msgbox SlateportCity_Harbor_Text_TeamAquaLeftNeedDive, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_NeedDive::
	msgbox SlateportCity_Harbor_Text_NeedDiveToCatchSub, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_CaptSternFerryOrScannerComment::
	goto_if_eq VAR_TEMP_1, 1, SlateportCity_Harbor_EventScript_TradedScanner
	checkitem ITEM_SCANNER
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_Harbor_EventScript_AskToTradeScanner
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_Harbor_EventScript_FerryFinished
	msgbox SlateportCity_Harbor_Text_WontBeLongBeforeWeFinishFerry, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_FerryFinished::
	msgbox SlateportCity_Harbor_Text_FinishedMakingFerry, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_AskToTradeScanner::
	message SlateportCity_Harbor_Text_WouldYouTradeScanner
	waitmessage
	goto SlateportCity_Harbor_EventScript_ChooseScannerTrade
	end

SlateportCity_Harbor_EventScript_ChooseScannerTrade::
	multichoice 0, 0, MULTI_STERN_DEEPSEA, FALSE
	switch VAR_RESULT
	case 0, SlateportCity_Harbor_EventScript_DeepSeaTooth
	case 1, SlateportCity_Harbor_EventScript_DeepSeaScale
	case 2, SlateportCity_Harbor_EventScript_DeclineTrade
	case MULTI_B_PRESSED, SlateportCity_Harbor_EventScript_DeclineTrade
	end

SlateportCity_Harbor_EventScript_DeepSeaTooth::
	msgbox SlateportCity_Harbor_Text_TradeForDeepSeaTooth, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SlateportCity_Harbor_EventScript_ChooseDifferentTrade
	giveitem ITEM_DEEP_SEA_TOOTH
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	removeitem ITEM_SCANNER
	msgbox SlateportCity_Harbor_Text_HandedScannerToStern, MSGBOX_DEFAULT
	setflag FLAG_EXCHANGED_SCANNER
	goto SlateportCity_Harbor_EventScript_TradedScanner
	end

SlateportCity_Harbor_EventScript_DeepSeaScale::
	msgbox SlateportCity_Harbor_Text_TradeForDeepSeaScale, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SlateportCity_Harbor_EventScript_ChooseDifferentTrade
	giveitem ITEM_DEEP_SEA_SCALE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	removeitem ITEM_SCANNER
	msgbox SlateportCity_Harbor_Text_HandedScannerToStern, MSGBOX_DEFAULT
	setflag FLAG_EXCHANGED_SCANNER
	goto SlateportCity_Harbor_EventScript_TradedScanner
	end

SlateportCity_Harbor_EventScript_DeclineTrade::
	msgbox SlateportCity_Harbor_Text_IfYouWantToTradeLetMeKnow, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_EventScript_ChooseDifferentTrade::
	message SlateportCity_Harbor_Text_WhichOneDoYouWant
	waitmessage
	goto SlateportCity_Harbor_EventScript_ChooseScannerTrade
	end

SlateportCity_Harbor_EventScript_TradedScanner::
	setvar VAR_TEMP_1, 1
	msgbox SlateportCity_Harbor_Text_ThisWillHelpResearch, MSGBOX_DEFAULT
	release
	end

SlateportCity_Harbor_Text_FerryServiceUnavailable:
	.string "¿Perdona?\n"
	.string "¿Buscas un barco?\p"
	.string "Lo siento, ahora mismo no hay\n"
	.string "servicio de ferry…$"

SlateportCity_Harbor_Text_MayISeeYourTicket:
	.string "Hola, ¿vienes por el ferry?\n"
	.string "¿Me enseñas tu BILLETE?$"

SlateportCity_Harbor_Text_YouMustHaveTicket:
	.string "{PLAYER} no tiene el BILLETE…\p"
	.string "Lo siento muchísimo.\p"
	.string "Hace falta un BILLETE para subir\n"
	.string "al ferry.$"

SlateportCity_Harbor_Text_FlashedTicketWhereTo:
	.string "{PLAYER} ha enseñado el BILLETE.\p"
	.string "¡Perfecto! ¡Es todo lo que necesitas!\p"
	.string "¿Y adónde quieres ir?$"

SlateportCity_Harbor_Text_SailAnotherTime:
	.string "¡Viaja con nosotros en otra ocasión!$"

SlateportCity_Harbor_Text_LilycoveItIs:
	.string "¡Pues a CIUDAD CALAGUA!$"

SlateportCity_Harbor_Text_BattleFrontierItIs:
	.string "¡Pues al FRENTE BATALLA!$"

SlateportCity_Harbor_Text_PleaseBoardFerry:
	.string "Sube al ferry y espera a que zarpe,\n"
	.string "por favor.$"

SlateportCity_Harbor_Text_WhereWouldYouLikeToGo:
	.string "Entonces, ¿adónde quieres ir?$"

SlateportCity_Harbor_Text_LoveToGoDeepUnderwaterSomeday:
	.string "Un viaje al fondo del mar…\n"
	.string "¿Cómo será?\p"
	.string "Me encantaría bajar hasta el fondo\n"
	.string "algún día.$"

SlateportCity_Harbor_Text_AbnormalWeather:
	.string "¡Para navegar seguro, hay que saber\n"
	.string "qué tiempo hará!\p"
	.string "Hablando del tiempo, me ha dicho uno\n"
	.string "del INSTITUTO METEOROLÓGICO que…\p"
	.string "¡Hay un tiempo anormal por todas\n"
	.string "partes!\p"
	.string "¡Deberías ir al INSTITUTO\n"
	.string "METEOROLÓGICO a preguntar!$"

SlateportCity_Harbor_Text_SubTooSmallForMe:
	.string "Quería ir con el CAPITÁN BABOR a\n"
	.string "explorar el fondo del mar.\p"
	.string "Pero el submarino es muy pequeño\n"
	.string "para mí.\p"
	.string "Si me meto, no quedaría sitio para\n"
	.string "el CAPITÁN…$"

SlateportCity_Harbor_Text_SameThugsTriedToRobAtMuseum:
	.string "CAPITÁN BABOR: Esos matones…\p"
	.string "Son los mismos que intentaron robar\n"
	.string "las PIEZAS DEVON en el MUSEO.$"

SlateportCity_Harbor_Text_ArchieYouAgainHideoutInLilycove:
	.string "AQUILES: ¿Oh?\n"
	.string "Otra vez tú…\p"
	.string "Hay que reconocer que eres tenaz\n"
	.string "por seguirnos hasta aquí.\p"
	.string "Pero ahora…\n"
	.string "¡Nadie puede pararnos! ¡Nadie!\p"
	.string "¿O nos seguirás hasta nuestra\n"
	.string "GUARIDA de CIUDAD CALAGUA?\p"
	.string "Juajuajuajua…$"

SlateportCity_Harbor_Text_CaptSternWhyStealMySubmarine:
	.string "CAPITÁN BABOR: ¿Por qué…?\p"
	.string "¿Por qué el EQUIPO AQUA iba a robar\n"
	.string "mi SUBMARINO EXPLORADOR 1?\p"
	.string "No pueden ir a por el POKéMON que\n"
	.string "duerme en el fondo del mar…\p"
	.string "Pero aunque los persiguiera, no\n"
	.string "tendría nada que hacer…$"

SlateportCity_Harbor_Text_TeamAquaLeftNeedDive:
	.string "CAPITÁN BABOR: Oh, {PLAYER}{KUN}…\p"
	.string "Vale… El EQUIPO AQUA se ha ido antes\n"
	.string "de que pudieras pararlo…\p"
	.string "No, no te culpes.\n"
	.string "No es culpa tuya.\p"
	.string "Alcanzar un submarino…\n"
	.string "Es imposible para casi todos.\p"
	.string "Haría falta un POKéMON que supiera\n"
	.string "BUCEAR…\p"
	.string "Quizá si fueras a\n"
	.string "CIUDAD ALGARIA…\p"
	.string "Allí viven muchos buceadores, así que\n"
	.string "alguien podría enseñarte…$"

SlateportCity_Harbor_Text_NeedDiveToCatchSub:
	.string "CAPITÁN BABOR: Alcanzar un\n"
	.string "submarino… Es imposible.\p"
	.string "Haría falta un POKéMON que supiera\n"
	.string "BUCEAR…\p"
	.string "Quizá si fueras a\n"
	.string "CIUDAD ALGARIA…\p"
	.string "Allí viven muchos buceadores, así que\n"
	.string "alguien podría enseñarte…$"

SlateportCity_Harbor_Text_WontBeLongBeforeWeFinishFerry:
	.string "CAPITÁN BABOR: Ah, sí.\n"
	.string "El SR. ARENQUE vino al ASTILLERO.\p"
	.string "¡No tardaremos mucho en terminar\n"
	.string "el ferry!$"

SlateportCity_Harbor_Text_FinishedMakingFerry:
	.string "CAPITÁN BABOR: ¡{PLAYER}{KUN}!\p"
	.string "¡Por fin hemos terminado el ferry\n"
	.string "M.S. MAREA!\p"
	.string "No lo habríamos conseguido sin tu\n"
	.string "amigo el SR. ARENQUE.\p"
	.string "¡Date una vuelta en él!$"

SlateportCity_Harbor_Text_WouldYouTradeScanner:
	.string "CAPITÁN BABOR: ¿Oh?\n"
	.string "{PLAYER}{KUN}, ese objeto que llevas…\p"
	.string "¡Es un ESCÁNER! Nos vendría muy bien\n"
	.string "para nuestras exploraciones.\p"
	.string "{PLAYER}{KUN}, ¿me cambiarías tu\n"
	.string "ESCÁNER por algo?\p"
	.string "¿Por ejemplo, por un DIENTE MARINO\n"
	.string "o una ESCAMA MARINA que tengo?$"

SlateportCity_Harbor_Text_IfYouWantToTradeLetMeKnow:
	.string "CAPITÁN BABOR: ¿Seguro?\n"
	.string "A ti no te sirve, {PLAYER}{KUN}…\p"
	.string "Bueno, vale. Si quieres cambiar\n"
	.string "tu ESCÁNER, avísame.$"

SlateportCity_Harbor_Text_TradeForDeepSeaTooth:
	.string "CAPITÁN BABOR: ¿Entonces lo cambias\n"
	.string "por mi DIENTE MARINO?$"

SlateportCity_Harbor_Text_TradeForDeepSeaScale:
	.string "CAPITÁN BABOR: ¿Entonces lo cambias\n"
	.string "por mi ESCAMA MARINA?$"

SlateportCity_Harbor_Text_WhichOneDoYouWant:
	.string "CAPITÁN BABOR: ¿Cuál quieres?$"

SlateportCity_Harbor_Text_HandedScannerToStern:
	.string "{PLAYER} le ha dado el ESCÁNER al\n"
	.string "CAPITÁN BABOR.$"

SlateportCity_Harbor_Text_ThisWillHelpResearch:
	.string "CAPITÁN BABOR: ¡Muchas gracias!\n"
	.string "¡Nos ayudará mucho, {PLAYER}{KUN}!$"
