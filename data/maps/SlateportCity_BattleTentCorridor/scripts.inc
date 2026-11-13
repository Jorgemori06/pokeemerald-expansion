SlateportCity_BattleTentCorridor_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SlateportCity_BattleTentCorridor_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SlateportCity_BattleTentCorridor_OnWarp
	.byte 0

	@ This is Slateport Tent's version of the Battle Factory Pre-Battle Room

SlateportCity_BattleTentCorridor_OnWarp:
	map_script_2 VAR_TEMP_1, 0, SlateportCity_BattleTentCorridor_EventScript_SetUpObjects
	.2byte 0

SlateportCity_BattleTentCorridor_EventScript_SetUpObjects::
	setvar VAR_TEMP_1, 1
	goto_if_ne VAR_0x8006, 1, SlateportCity_BattleTentCorridor_EventScript_TurnPlayerNorth
	setobjectxy LOCALID_SLATEPORT_TENT_CORRIDOR_ATTENDANT, 2, 2
	turnobject LOCALID_SLATEPORT_TENT_CORRIDOR_ATTENDANT, DIR_SOUTH
SlateportCity_BattleTentCorridor_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

SlateportCity_BattleTentCorridor_OnFrame:
	map_script_2 VAR_TEMP_0, 0, SlateportCity_BattleTentCorridor_EventScript_EnterCorridor
	.2byte 0

SlateportCity_BattleTentCorridor_EventScript_EnterCorridor::
	goto_if_eq VAR_0x8006, 1, SlateportCity_BattleTentCorridor_EventScript_ReturnToRoomFromBattle
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_SLATEPORT_TENT_CORRIDOR_ATTENDANT, SlateportCity_BattleTentCorridor_Movement_AttendantEnter
	applymovement LOCALID_PLAYER, SlateportCity_BattleTentCorridor_Movement_PlayerEnter
	waitmovement 0
	goto_if_eq VAR_0x8006, 2, SlateportCity_BattleTentCorridor_EventScript_ResumeChallenge
	slateporttent_generaterentalmons
	slateporttent_generateopponentmons
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_HoldMonsChooseFromSelection, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	slateporttent_rentmons
	waitstate
SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom::
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_RightThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_TENT_CORRIDOR_ATTENDANT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor 2, 1
	waitdooranim
	applymovement LOCALID_SLATEPORT_TENT_CORRIDOR_ATTENDANT, SlateportCity_BattleTentCorridor_Movement_AttendantExit
	applymovement LOCALID_PLAYER, SlateportCity_BattleTentCorridor_Movement_PlayerExit
	waitmovement 0
	closedoor 2, 1
	waitdooranim
	warp MAP_SLATEPORT_CITY_BATTLE_TENT_BATTLE_ROOM, 4, 4
	waitstate
	end

SlateportCity_BattleTentCorridor_EventScript_ReturnToRoomFromBattle::
	factory_setopponentmons
	factory_resethelditems
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_LetUsRestoreMons, MSGBOX_DEFAULT
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent::
	frontier_get FRONTIER_DATA_BATTLE_NUM
	call_if_eq VAR_RESULT, 1, SlateportCity_BattleTentCorridor_EventScript_ReadyFor2ndOpponent
	call_if_eq VAR_RESULT, 2, SlateportCity_BattleTentCorridor_EventScript_ReadyFor3rdOpponent
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, TRUE
	switch VAR_RESULT
	case 0, SlateportCity_BattleTentCorridor_EventScript_AskSwapMon
	case 1, SlateportCity_BattleTentCorridor_EventScript_AskPauseChallenge
	case 2, SlateportCity_BattleTentCorridor_EventScript_AskRetireChallenge

SlateportCity_BattleTentCorridor_EventScript_AskPauseChallenge::
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_SaveAndQuitGame, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent
	case YES, SlateportCity_BattleTentCorridor_EventScript_PauseChallenge
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_EventScript_AskRetireChallenge::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_RetireFromChallenge
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent
	case 0, SlateportCity_BattleTent_EventScript_WarpToLobbyLost
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_EventScript_AskSwapMon::
	slateporttent_generateopponentmons
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_LikeToSwapMon, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom
	case YES, SlateportCity_BattleTentCorridor_EventScript_SwapMons
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom

SlateportCity_BattleTentCorridor_EventScript_SwapMons::
	fadescreen FADE_TO_BLACK
	slateporttent_swapmons
	waitstate
	goto_if_eq VAR_RESULT, 1, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_YourSwapIsComplete, MSGBOX_DEFAULT
	goto SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom

SlateportCity_BattleTentCorridor_EventScript_ReadyFor2ndOpponent::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor2ndOpponent
	waitmessage
	return

SlateportCity_BattleTentCorridor_EventScript_ReadyFor3rdOpponent::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor3rdOpponent
	waitmessage
	return

SlateportCity_BattleTentCorridor_EventScript_PauseChallenge::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_SavingDataPleaseWait
	waitmessage
	slateporttent_save CHALLENGE_STATUS_PAUSED
	playse SE_SAVE
	waitse
	fadescreen FADE_TO_BLACK
	frontier_reset
	end

SlateportCity_BattleTentCorridor_EventScript_ResumeChallenge::
	special SavePlayerParty
	factory_setparties 0
	goto SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_Movement_PlayerEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SlateportCity_BattleTentCorridor_Movement_PlayerExit:
	walk_up
	walk_up
	set_invisible
	step_end

SlateportCity_BattleTentCorridor_Movement_AttendantEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

SlateportCity_BattleTentCorridor_Movement_AttendantExit:
	walk_up
	set_invisible
	step_end

@ Leftover text from when this was a Contest Hall in R/S
@ Unused
SlateportCity_ContestHall_Text_AdviceForContests:
	.string "¿Quieres un consejito jugoso para\n"
	.string "los CONCURSOS?\p"
	.string "Usar ciertos movimientos después de\n"
	.string "otros a veces llama más la atención.\p"
	.string "Si sabes lo que haces, puedes\n"
	.string "ganar muchos puntos de exhibición.\p"
	.string "Claro que tus rivales pueden intentar\n"
	.string "estropear la actuación de tu POKéMON.$"

@ Unused
SlateportCity_ContestHall_Text_MyPapaIsContestJudge:
	.string "Mi papá es JUEZ de CONCURSOS.\p"
	.string "¿Qué seré de mayor, JUEZ o LÍDER\n"
	.string "de GIMNASIO?$"

@ Unused
SlateportCity_ContestHall_Text_ImLikeMajorlyCheesed:
	.string "Tío, estoy en plan mosqueadísimo,\n"
	.string "¿sabes? En plan, solo quería saber\l"
	.string "por qué mi POKéMON nunca gana,\l"
	.string "¿sabes?, en plan, ¿eh?\p"
	.string "Así que, en plan, le di mi opinión\n"
	.string "al JUEZ, ¿sabes?, que es gratis.\p"
	.string "¡Y no me quiso escuchar, en plan, eh!\n"
	.string "¡Total, en plan, qué bajón, tío!\p"
	.string "¡Eh, en plan, tú! Calla, ¿sabes?\n"
	.string "¡Tú, en plan, toma esto!$"

@ Unused
SlateportCity_ContestHall_Text_ExplainTorment:
	.string "Eso es, en plan, la MT41, ¿sabes?\n"
	.string "¡Eh, es TORMENTO!, ¿me oyes?\p"
	.string "En plan, no deja al otro usar el mismo\n"
	.string "movimiento dos veces seguidas, ¿ves?\p"
	.string "¡Eh, oye, escucha, en plan, que no te\n"
	.string "estoy atormentando, eh!$"

@ Unused
SlateportCity_ContestHall_Text_MCStepUpTakePartInContest:
	.string "PRESENTADOR: ¡Vaya, vaya!\n"
	.string "¿A que es un POKéMON de primera?\p"
	.string "¡Por favor! ¡Acércate y participa\n"
	.string "en nuestros espléndidos CONCURSOS!\p"
	.string "¡Lo harás bien! ¡Estoy seguro!\n"
	.string "¡Mi ojo nunca me ha fallado!$"

@ Unused
SlateportCity_ContestHall_Text_JudgeWouldntDoToMissContest:
	.string "JUEZ: ¡Vaya, hola!\n"
	.string "¡Veo que eres ENTRENADOR!\p"
	.string "¡Entonces no puedes perderte\n"
	.string "un CONCURSO POKéMON!\p"
	.string "¡Consigue un PASE CONCURSO en\n"
	.string "VERDEGAL y participa cuando quieras!$"

@ Unused
SlateportCity_ContestHall_Text_ItsAppealTime:
	.string "¡Llega la exhibición!\n"
	.string "¿Con qué empiezo?$"

@ Unused
SlateportCity_ContestHall_Text_DidntPayAttentionToAppeal:
	.string "No le han hecho mucho caso a la\n"
	.string "exhibición de mi POKéMON…\p"
	.string "Bah, ese JUEZ no sabe reconocer\n"
	.string "algo bueno cuando lo ve.$"

@ Unused
SlateportCity_ContestHall_Text_RewardWithSageAdvice:
	.string "¡Oh, hola! Para acercarte tanto debes\n"
	.string "de ser muy fan.\p"
	.string "Te premiaré el entusiasmo con\n"
	.string "este sabio consejo.\p"
	.string "Si un movimiento gusta mucho,\n"
	.string "el público se emociona.\p"
	.string "El POKéMON que hace su exhibición\n"
	.string "justo cuando todos están emocionados…\p"
	.string "¡Pues algo bueno tiene que pasar,\n"
	.string "¿no crees?!$"

@ Unused
SlateportCity_ContestHall_Text_MoreFreakedOutThanMon:
	.string "¡No puedo! Estoy más nervioso\n"
	.string "que mi POKéMON.\p"
	.string "¡Estoy temblando y el corazón me va\n"
	.string "a mil!$"

@ Unused
SlateportCity_ContestHall_Text_BattleAndContestAlike:
	.string "Un combate y un CONCURSO no son lo\n"
	.string "mismo, pero también se parecen.\p"
	.string "Hay que esforzarse y creer en los\n"
	.string "POKéMON que has criado.$"

@ Unused
SlateportCity_ContestHall_Text_MonLooksOnTopOfGame:
	.string "Ese POKéMON parece estar en plena\n"
	.string "forma, ¿eh?\p"
	.string "Un POKéMON al que le va bien en la\n"
	.string "segunda ronda parece estar más\l"
	.string "relajado en las exhibiciones.$"

@ Unused
SlateportCity_ContestHall_Text_MyMonBetterThanThatLot:
	.string "¿Has visto qué pena dan?\p"
	.string "Je, ¡mi POKéMON es muchísimo mejor\n"
	.string "que todos esos!$"

@ Unused
SlateportCity_ContestHall_Text_GetUrgeToMoveWithMon:
	.string "¿No te entran ganas de moverte con\n"
	.string "los POKéMON cuando hacen una\l"
	.string "exhibición llena de energía?$"

@ Unused
SlateportCity_ContestHall_Text_HyperRankStage:
	.string "POKéMON CONTESTS\n"
	.string "HYPER RANK STAGE!$"

