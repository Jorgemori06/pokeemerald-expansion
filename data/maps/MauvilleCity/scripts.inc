MauvilleCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_OnTransition
	.byte 0

MauvilleCity_OnTransition:
	setflag FLAG_VISITED_MAUVILLE_CITY
	clearflag FLAG_FORCE_MIRAGE_TOWER_VISIBLE
	clearflag FLAG_HIDE_SLATEPORT_MUSEUM_POPULATION
	setflag FLAG_SYS_TV_START
	clearflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	setvar VAR_MAUVILLE_GYM_STATE, 0
	call_if_set FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON, MauvilleCity_EventScript_MoveWattsonBackToGym
	end

MauvilleCity_EventScript_MoveWattsonBackToGym::
	clearflag FLAG_HIDE_MAUVILLE_GYM_WATTSON
	setflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	setflag FLAG_WATTSON_REMATCH_AVAILABLE
	return

MauvilleCity_EventScript_Boy::
	msgbox MauvilleCity_Text_NurseHurtMonBackToHealth, MSGBOX_NPC
	end

MauvilleCity_EventScript_Maniac::
	msgbox MauvilleCity_Text_AllSortsOfPeopleComeThrough, MSGBOX_NPC
	end

MauvilleCity_EventScript_Woman::
	msgbox MauvilleCity_Text_RydelVeryGenerous, MSGBOX_NPC
	end

MauvilleCity_EventScript_RichBoy::
	msgbox MauvilleCity_Text_PokemonCanJumpYouOnBike, MSGBOX_NPC
	end

MauvilleCity_EventScript_CitySign::
	msgbox MauvilleCity_Text_CitySign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GymSign::
	msgbox MauvilleCity_Text_GymSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_BikeShopSign::
	msgbox MauvilleCity_Text_BikeShopSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GameCornerSign::
	msgbox MauvilleCity_Text_GameCornerSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_SchoolKidM::
	lock
	faceplayer
	goto_if_set FLAG_TV_EXPLAINED, MauvilleCity_EventScript_TVExplained
	msgbox MauvilleCity_Text_ExplainTV, MSGBOX_DEFAULT
	setflag FLAG_TV_EXPLAINED
	release
	end

MauvilleCity_EventScript_TVExplained::
	msgbox MauvilleCity_Text_BeenCheckingOutTV, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_UncleAskPlayerToBattleWally
	msgbox MauvilleCity_Text_UncleHesTooPeppy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_UncleAskPlayerToBattleWally::
	msgbox MauvilleCity_Text_UncleCanYouBattleWally, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_Wally::
	lockall
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_WallyRequestBattleAgain
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWantToChallengeGym, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_UncleYourePushingIt, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_WallyWeCanBeatAnyone, MSGBOX_DEFAULT
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWillYouBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_EventScript_BattleWallyPrompt::
	call_if_eq VAR_RESULT, YES, MauvilleCity_EventScript_BattleWally
	goto_if_eq VAR_RESULT, NO, MauvilleCity_EventScript_DeclineWallyBattle
	closemessage
	switch VAR_FACING
	case DIR_NORTH, MauvilleCity_EventScript_WallyAndUncleExitNorth
	case DIR_EAST, MauvilleCity_EventScript_WallyAndUncleExitEast
	end

MauvilleCity_EventScript_WallyAndUncleExitNorth::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth1
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitNorth1
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth1
	waitmovement 0
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerFaceUncleNorth
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerNorth
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth2
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth2
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitNorth2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_WallyAndUncleExitEast::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast1
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitEast1
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast1
	waitmovement 0
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerEast
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast2
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast2
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitEast2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_DefeatedWally::
	removeobject LOCALID_MAUVILLE_WALLY
	removeobject LOCALID_MAUVILLE_WALLYS_UNCLE
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLYS_UNCLE
	setflag FLAG_DEFEATED_WALLY_MAUVILLE
	setvar VAR_WALLY_CALL_STEP_COUNTER, 0
	setflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottApproachPlayerNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottApproachPlayerEast
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox MauvilleCity_Text_ScottYouDidntHoldBack, MSGBOX_DEFAULT
	closemessage
	addvar VAR_SCOTT_STATE, 1
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottExitEast
	removeobject LOCALID_MAUVILLE_SCOTT
	releaseall
	end

MauvilleCity_EventScript_ScottApproachPlayerNorth::
	addobject LOCALID_MAUVILLE_SCOTT
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottApproachPlayerNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottApproachPlayerEast::
	setobjectxyperm LOCALID_MAUVILLE_SCOTT, 12, 13
	addobject LOCALID_MAUVILLE_SCOTT
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottApproachPlayerEast
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitNorth::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitNorth
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottExitNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitEast::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitEast
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottExitEast
	waitmovement 0
	return

MauvilleCity_EventScript_BattleWally::
	msgbox MauvilleCity_Text_WallyHereICome, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_MAUVILLE, MauvilleCity_Text_WallyDefeat
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyIllGoBackToVerdanturf, MSGBOX_DEFAULT
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_ThankYouNotEnoughToBattle, MSGBOX_DEFAULT
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_UncleNoNeedToBeDown, MSGBOX_DEFAULT
	return

MauvilleCity_EventScript_DeclineWallyBattle::
	setflag FLAG_DECLINED_WALLY_BATTLE_MAUVILLE
	msgbox MauvilleCity_Text_WallyMyUncleWontKnowImStrong, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallyRequestBattleAgain::
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_WallyPleaseBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_Movement_WallyExitNorth1:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	step_end

MauvilleCity_Movement_WallyExitEast1:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallyExitNorth2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_WallyExitEast2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast2:
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitNorth:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitEast:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast1:
	delay_16
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth1:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_WallysUncleExitNorth1:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

MauvilleCity_Movement_WallysUncleExitEast1:
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_PlayerFaceUncleNorth:
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerNorth:
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerEast:
	walk_right
	walk_up
	step_end

MauvilleCity_Movement_WallysUncleExitNorth2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallysUncleExitEast2:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_ScottApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_ScottApproachPlayerEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

MauvilleCity_Movement_ScottExitNorth:
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

MauvilleCity_Movement_ScottExitEast:
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

MauvilleCity_EventScript_Wattson::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON, MauvilleCity_EventScript_ReceivedThunderbolt
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 2, MauvilleCity_EventScript_CompletedNewMauville
	goto_if_set FLAG_GOT_BASEMENT_KEY_FROM_WATTSON, MauvilleCity_EventScript_BegunNewMauville
	msgbox MauvilleCity_Text_WattsonNeedFavorTakeKey, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_BASEMENT_KEY_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_BegunNewMauville::
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CompletedNewMauville::
	msgbox MauvilleCity_Text_WattsonThanksTakeTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_THUNDERBOLT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_ReceivedThunderbolt::
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_RegisterWallyCall::
	lockall
	pokenavcall MauvilleCity_Text_WallyPokenavCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MauvilleCity_Text_RegisteredWally, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WALLY_MATCH_CALL
	clearflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	releaseall
	end

MauvilleCity_Text_UncleHesTooPeppy:
	.string "TÍO: Supongo que es gracias a los\n"
	.string "POKéMON que este chico tiene más\l"
	.string "energía… Pero se ha pasado un poco…$"

MauvilleCity_Text_WallyWantToChallengeGym:
	.string "BLASCO: Venga, TÍO, ¿por favor?\p"
	.string "Quiero desafiar a este GIMNASIO y\n"
	.string "ver cuánto he mejorado.\p"
	.string "¿Porfa? ¿Me dejas, porfa?$"

MauvilleCity_Text_UncleYourePushingIt:
	.string "TÍO: Espera un momento, BLASCO.\p"
	.string "Desde que vives con POKéMON, te has\n"
	.string "vuelto mucho más fuerte.\p"
	.string "Pero ¿no crees que es pasarse\n"
	.string "desafiar de golpe a un GIMNASIO?$"

MauvilleCity_Text_WallyWeCanBeatAnyone:
	.string "BLASCO: No me estoy pasando.\p"
	.string "¡Si uno fuerzas con RALTS,\n"
	.string "podemos ganar a cualquiera!$"

MauvilleCity_Text_WallyWillYouBattleMe:
	.string "BLASCO: ¡Oh! ¡Hola, {PLAYER}!\p"
	.string "Me he hecho mucho más fuerte desde\n"
	.string "que nos conocimos.\p"
	.string "{PLAYER}, quiero que mi TÍO y tú\n"
	.string "lo veáis.\p"
	.string "{PLAYER}, por favor, ¿combates\n"
	.string "conmigo?$"

MauvilleCity_Text_WallyMyUncleWontKnowImStrong:
	.string "BLASCO: Oh… Si no combates conmigo,\n"
	.string "{PLAYER}, mi TÍO no sabrá lo fuerte\l"
	.string "que me he hecho.$"

MauvilleCity_Text_UncleCanYouBattleWally:
	.string "TÍO: Eres {PLAYER}{KUN}, ¿no?\n"
	.string "De parte de BLASCO, ¿podrías\l"
	.string "combatir con él solo esta vez?\p"
	.string "Tal como está ahora, no creo que\n"
	.string "atienda a razones.$"

MauvilleCity_Text_WallyPleaseBattleMe:
	.string "BLASCO: ¡{PLAYER}, por favor!\n"
	.string "Combate conmigo, por favor.$"

MauvilleCity_Text_WallyHereICome:
	.string "BLASCO: {PLAYER}, gracias.\p"
	.string "¡Vale… allá voy!$"

MauvilleCity_Text_WallyDefeat:
	.string "BLASCO: … … … … … … …\p"
	.string "… … … … … … … …\p"
	.string "He perdido…$"

MauvilleCity_Text_WallyIllGoBackToVerdanturf:
	.string "BLASCO: TÍO…\n"
	.string "Volveré a VERDEGAL…$"

MauvilleCity_Text_ThankYouNotEnoughToBattle:
	.string "{PLAYER}, gracias.\n"
	.string "Ser ENTRENADOR es duro, ¿verdad?\p"
	.string "No basta con tener POKéMON y\n"
	.string "hacerlos combatir. Ser un ENTRENADOR\l"
	.string "de verdad no consiste en eso.$"

MauvilleCity_Text_UncleNoNeedToBeDown:
	.string "TÍO: BLASCO, no hace falta que\n"
	.string "te vengas abajo.\p"
	.string "Vamos, ¿qué te impide hacerte cada\n"
	.string "vez más fuerte?\p"
	.string "Venga, vámonos a casa.\n"
	.string "Todos te están esperando.$"

MauvilleCity_Text_UncleVisitUsSometime:
	.string "TÍO: {PLAYER}{KUN}, ahora caigo:\n"
	.string "tú debes de ser quien acompañó a\l"
	.string "BLASCO cuando atrapó a su\l"
	.string "POKéMON.\p"
	.string "¿Por qué no vienes a vernos a\n"
	.string "VERDEGAL algún día?\l"
	.string "Seguro que a BLASCO le encantaría.$"


MauvilleCity_Text_WallyPokenavCall:
	.string "… … … … … …\n"
	.string "… … … … … ¡Bip!\p"
	.string "BLASCO: ¡Oh, hola, {PLAYER}!\p"
	.string "Solo quería decirte que ¡mi tío\n"
	.string "me ha comprado un POKéNAV!\p"
	.string "¡Ahora puedo hablar contigo cuando\n"
	.string "quiera, {PLAYER}!\p"
	.string "… … … … … …\n"
	.string "… … … … … ¡Clic!$"

MauvilleCity_Text_RegisteredWally:
	.string "Has registrado a BLASCO\n"
	.string "en el POKéNAV.$"

MauvilleCity_Text_ScottYouDidntHoldBack:
	.string "SCOTT: Jeje…\n"
	.string "¡He visto el combate!\p"
	.string "Eres amigo de ese chico, BLASCO,\n"
	.string "¿verdad?\p"
	.string "Pero no te has contenido y le has\n"
	.string "ganado de forma impresionante.\p"
	.string "¡Sí! ¡Así es un combate POKéMON\n"
	.string "de verdad!\p"
	.string "¡Admiro a los ENTRENADORES así!\p"
	.string "… … … … … …\n"
	.string "¡Te estaré animando!$"

MauvilleCity_Text_WattsonNeedFavorTakeKey:
	.string "ERICO: ¡Oh, {PLAYER}{KUN}!\n"
	.string "¡Se te ve con mucha chispa!\l"
	.string "¡Eso es bueno, juajuajuajua!\p"
	.string "¡Bien! ¡Decidido!\n"
	.string "¡Necesito un favor, {PLAYER}{KUN}!\p"
	.string "CIUDAD MALVALONA tiene una zona\n"
	.string "subterránea llamada NUEVA MALVALONA.\p"
	.string "{PLAYER}{KUN}, quiero que vayas allí\n"
	.string "y apagues el GENERADOR.\p"
	.string "El GENERADOR se ha vuelto un poco\n"
	.string "loco. Empieza a ser peligroso.\p"
	.string "Toma, esta es la LLAVE para entrar\n"
	.string "en NUEVA MALVALONA.$"

MauvilleCity_Text_WattsonWontBeChallenge:
	.string "ERICO: No te preocupes.\n"
	.string "Para ti no será ningún reto.\p"
	.string "La entrada a NUEVA MALVALONA está\n"
	.string "a un poco de SURF de la RUTA 110.\p"
	.string "¡Pues ya está, confío en ti!\n"
	.string "¡Juajuajuajua!$"

MauvilleCity_Text_WattsonThanksTakeTM:
	.string "ERICO: ¡Juajuajuajua!\p"
	.string "¡Lo sabía, {PLAYER}{KUN}! ¡Sabía que\n"
	.string "había acertado al pedírtelo!\p"
	.string "Aquí tienes mi agradecimiento:\n"
	.string "¡una MT con RAYO!\p"
	.string "¡Venga, te lo has ganado!$"

MauvilleCity_Text_WattsonYoungTakeCharge:
	.string "ERICO: ¡Juajuajuajua!\p"
	.string "¡Me encanta ver a los jóvenes dar\n"
	.string "un paso al frente!$"

MauvilleCity_Text_NurseHurtMonBackToHealth:
	.string "Los combates POKéMON y todo eso\n"
	.string "molan mucho…\p"
	.string "Pero si tu POKéMON se hace daño,\n"
	.string "tienes que cuidarlo hasta que se cure.$"

MauvilleCity_Text_AllSortsOfPeopleComeThrough:
	.string "Las calles de esta ciudad van de\n"
	.string "norte a sur y de este a oeste.\p"
	.string "Por eso pasa por aquí gente\n"
	.string "de todo tipo.$"

MauvilleCity_Text_RydelVeryGenerous:
	.string "¿Has ido ya a BICIS RYDEL?\p"
	.string "RYDEL, el dueño, es un hombre\n"
	.string "muy generoso.$"

MauvilleCity_Text_PokemonCanJumpYouOnBike:
	.string "Aunque vayas en BICI, te pueden\n"
	.string "saltar encima POKéMON salvajes.$"

MauvilleCity_Text_CitySign:
	.string "CIUDAD MALVALONA\n"
	.string "“¡La ciudad brillante de la diversión!”$"

MauvilleCity_Text_GymSign:
	.string "GIMNASIO POKéMON DE MALVALONA\n"
	.string "LÍDER: ERICO\l"
	.string "“¡El hombre alegremente electrizante!”$"

MauvilleCity_Text_BikeShopSign:
	.string "“¡Rueda por la grava y agita\n"
	.string "tu alma!”\l"
	.string "BICIS RYDEL$"

MauvilleCity_Text_GameCornerSign:
	.string "“¡El sitio de juegos para todos!”\n"
	.string "CASINO DE MALVALONA$"

MauvilleCity_Text_ExplainTV:
	.string "Hola, ¿tú ves la tele?\p"
	.string "Hace poco han puesto un montón de\n"
	.string "programas nuevos muy chulos.\p"
	.string "La tele mola. He visto a mis amigos\n"
	.string "en la tele de repente.\p"
	.string "Y a veces hasta te sacan en la tele\n"
	.string "sin avisarte.\p"
	.string "Ojalá saliera yo algún día.\p"
	.string "Por eso creo que deberías ver la\n"
	.string "tele siempre que puedas.$"

MauvilleCity_Text_BeenCheckingOutTV:
	.string "Hola, ¿has estado viendo la tele?$"
