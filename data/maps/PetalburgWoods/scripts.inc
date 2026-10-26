PetalburgWoods_MapScripts::
	.byte 0

PetalburgWoods_EventScript_DevonResearcherLeft::
	lockall
	call PetalburgWoods_EventScript_DevonResearcherIntro
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherApproachPlayerLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaEntrance
	waitmovement 0
	msgbox PetalburgWoods_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaApproachResearcherLeft
	waitmovement 0
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_HandOverThosePapers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherFleeToPlayerLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaApproachPlayer
	waitmovement 0
	msgbox PetalburgWoods_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_PETALBURG_WOODS, PetalburgWoods_Text_YoureKiddingMe
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaBackOff
	waitmovement 0
	call PetalburgWoods_EventScript_DevonResearcherPostBattle
	applymovement LOCALID_PLAYER, PetalburgWoods_Movement_WatchResearcherLeave
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherExitLeft
	waitmovement 0
	goto PetalburgWoods_EventScript_RemoveDevonResearcher
	end

PetalburgWoods_EventScript_DevonResearcherRight::
	lockall
	call PetalburgWoods_EventScript_DevonResearcherIntro
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherApproachPlayerRight
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaEntrance
	waitmovement 0
	msgbox PetalburgWoods_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaApproachResearcherRight
	waitmovement 0
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_HandOverThosePapers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherFleeToPlayerRight
	waitmovement 0
	msgbox PetalburgWoods_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_PETALBURG_WOODS, PetalburgWoods_Text_YoureKiddingMe
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaBackOff
	waitmovement 0
	call PetalburgWoods_EventScript_DevonResearcherPostBattle
	applymovement LOCALID_PLAYER, PetalburgWoods_Movement_WatchResearcherLeave
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherExitRight
	waitmovement 0
	goto PetalburgWoods_EventScript_RemoveDevonResearcher
	end

PetalburgWoods_EventScript_DevonResearcherIntro::
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherLookAround
	waitmovement 0
	msgbox PetalburgWoods_Text_NotAOneToBeFound, MSGBOX_DEFAULT
	closemessage
	return

PetalburgWoods_EventScript_DevonResearcherPostBattle::
	msgbox PetalburgWoods_Text_YouveGotSomeNerve, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaRunAway
	waitmovement 0
	removeobject LOCALID_PETALBURG_WOODS_GRUNT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox PetalburgWoods_Text_ThatWasAwfullyClose, MSGBOX_DEFAULT
	giveitem ITEM_GREAT_BALL
	goto_if_eq VAR_RESULT, FALSE, PetalburgWoods_EventScript_BagFull
	goto PetalburgWoods_EventScript_DevonResearcherFinish
	end

PetalburgWoods_EventScript_BagFull::
	msgbox PetalburgWoods_Text_YoureLoadedWithItems, MSGBOX_DEFAULT
	goto PetalburgWoods_EventScript_DevonResearcherFinish
	end

PetalburgWoods_EventScript_DevonResearcherFinish::
	msgbox PetalburgWoods_Text_TeamAquaAfterSomethingInRustboro, MSGBOX_DEFAULT
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherStartExit
	waitmovement 0
	msgbox PetalburgWoods_Text_ICantBeWastingTime, MSGBOX_DEFAULT
	closemessage
	return

PetalburgWoods_EventScript_RemoveDevonResearcher::
	removeobject LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE
	setvar VAR_PETALBURG_WOODS_STATE, 1
	releaseall
	end

PetalburgWoods_Movement_DevonResearcherLookAround:
	face_up
	delay_16
	delay_4
	face_right
	delay_16
	delay_8
	face_left
	delay_16
	delay_8
	face_down
	delay_16
	face_right
	delay_16
	delay_8
	face_up
	delay_16
	step_end

PetalburgWoods_Movement_DevonResearcherExitLeft:
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgWoods_Movement_DevonResearcherApproachPlayerLeft:
	delay_16
	face_player
	walk_down
	walk_down
	step_end

PetalburgWoods_Movement_DevonResearcherApproachPlayerRight:
	delay_16
	face_player
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

PetalburgWoods_Movement_DevonResearcherExitRight:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgWoods_Movement_WatchResearcherLeave:
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherFleeToPlayerLeft:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherFleeToPlayerRight:
	walk_fast_down
	walk_fast_right
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherStartExit:
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_up
	step_end

PetalburgWoods_Movement_AquaApproachResearcherLeft:
	walk_fast_down
	walk_fast_down
	step_end

PetalburgWoods_Movement_AquaBackOff:
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

PetalburgWoods_Movement_AquaRunAway:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	delay_16
	delay_16
	step_end

PetalburgWoods_Movement_AquaApproachResearcherRight:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

PetalburgWoods_Movement_AquaEntrance:
	walk_down
	walk_down
	delay_16
	delay_16
	step_end

PetalburgWoods_Movement_AquaApproachPlayer:
	walk_down
	step_end

PetalburgWoods_EventScript_Boy1::
	msgbox PetalburgWoods_Text_StayOutOfTallGrass, MSGBOX_NPC
	end

PetalburgWoods_EventScript_Boy2::
	msgbox PetalburgWoods_Text_HiddenItemsExplanation, MSGBOX_NPC
	end

PetalburgWoods_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_MIRACLE_SEED, PetalburgWoods_EventScript_ExplainMiracleSeed
	msgbox PetalburgWoods_Text_TryUsingThisItem, MSGBOX_DEFAULT
	giveitem ITEM_MIRACLE_SEED
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MIRACLE_SEED
	release
	end

PetalburgWoods_EventScript_ExplainMiracleSeed::
	msgbox PetalburgWoods_Text_MiracleSeedExplanation, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_Sign1::
	msgbox PetalburgWoods_Text_TrainerTipsExperience, MSGBOX_SIGN
	end

PetalburgWoods_EventScript_Sign2::
	msgbox PetalburgWoods_Text_TrainerTipsPP, MSGBOX_SIGN
	end

PetalburgWoods_EventScript_Lyle::
	trainerbattle_single TRAINER_LYLE, PetalburgWoods_Text_GoBugPokemonTeam, PetalburgWoods_Text_ICouldntWin
	msgbox PetalburgWoods_Text_ImOutOfPokeBalls, MSGBOX_AUTOCLOSE
	end

PetalburgWoods_EventScript_James::
	trainerbattle_single TRAINER_JAMES_1, PetalburgWoods_Text_InstantlyPopularWithBugPokemon, PetalburgWoods_Text_CantBePopularIfILose, PetalburgWoods_EventScript_TryRegisterJames
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, PetalburgWoods_EventScript_JamesRematch
	setvar VAR_0x8004, TRAINER_JAMES_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, PetalburgWoods_EventScript_TryRegisterJames2
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_TryRegisterJames::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_RegisterJames
	release
	end

PetalburgWoods_EventScript_RegisterJames::
	msgbox PetalburgWoods_Text_IWantRematch1, MSGBOX_DEFAULT
	register_matchcall TRAINER_JAMES_1
	release
	end

PetalburgWoods_EventScript_TryRegisterJames2::
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_RegisterJames2
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_RegisterJames2::
	msgbox PetalburgWoods_Text_IWantRematch2, MSGBOX_DEFAULT
	register_matchcall TRAINER_JAMES_1
	release
	end

PetalburgWoods_EventScript_JamesRematch::
	trainerbattle_rematch TRAINER_JAMES_1, PetalburgWoods_Text_MyPokemonHaveGrown, PetalburgWoods_Text_CantBePopularIfLose
	msgbox PetalburgWoods_Text_IveBeenTrainingHard, MSGBOX_AUTOCLOSE
	end

PetalburgWoods_Text_NotAOneToBeFound:
	.string "Mmm…\n"
	.string "No hay ni uno…$"

PetalburgWoods_Text_HaveYouSeenShroomish:
	.string "Hola, ¿has visto por aquí algún\n"
	.string "POKéMON llamado SHROOMISH?\p"
	.string "Me encanta ese POKéMON.$"

PetalburgWoods_Text_IWasGoingToAmbushYou:
	.string "Iba a tenderte una emboscada, pero\n"
	.string "has tardado una eternidad en salir\l"
	.string "del BOSQUE PETALIA, ¿eh?\p"
	.string "¡Me he hartado de esperar y aquí estoy!$"

PetalburgWoods_Text_HandOverThosePapers:
	.string "¡Tú! ¡INVESTIGADOR de DEVON!\p"
	.string "¡Dame esos documentos!$"

PetalburgWoods_Text_YouHaveToHelpMe:
	.string "¡Aaaah!\p"
	.string "¿Entrenas POKéMON, verdad?\n"
	.string "¡Tienes que ayudarme, por favor!$"

PetalburgWoods_Text_NoOneCrossesTeamAqua:
	.string "¿Eh? ¿Qué te crees que haces?\n"
	.string "¿Qué pasa, vas a protegerlo?\p"
	.string "¡Nadie que se cruce con el EQUIPO AQUA\n"
	.string "tiene piedad, aunque sea un crío!\p"
	.string "¡Venga, lucha contra mí!$"

PetalburgWoods_Text_YoureKiddingMe:
	.string "¡No me lo creo! ¡Eres duro de pelar!$"

PetalburgWoods_Text_YouveGotSomeNerve:
	.string "Grrr… ¡Qué valor tienes, meterte\n"
	.string "con el EQUIPO AQUA!\l"
	.string "¡Venga, lucha otra vez!\p"
	.string "Eso me gustaría decir, pero no me\n"
	.string "quedan POKéMON…\p"
	.string "Y, oye, el EQUIPO AQUA también busca\n"
	.string "algo en FÉRRICA.\p"
	.string "¡Por hoy te dejo ir!$"

PetalburgWoods_Text_ThatWasAwfullyClose:
	.string "Uf…\n"
	.string "¡Por poco!\p"
	.string "Gracias a ti no me ha robado\n"
	.string "estos documentos tan importantes.\p"
	.string "¡Ya sé! ¡Te daré una SUPER BALL\n"
	.string "en agradecimiento!$"

PetalburgWoods_Text_TeamAquaAfterSomethingInRustboro:
	.string "¿No ha dicho ese matón del EQUIPO AQUA\n"
	.string "que también buscaban algo\l"
	.string "en FÉRRICA?$"

PetalburgWoods_Text_ICantBeWastingTime:
	.string "¡Ay, no! ¡Es una crisis!\n"
	.string "¡No puedo perder el tiempo!$"

PetalburgWoods_Text_YoureLoadedWithItems:
	.string "Vas cargado de objetos.\n"
	.string "No puedo darte esta SUPER BALL.$"

PetalburgWoods_Text_GoBugPokemonTeam:
	.string "¡He atrapado un montón de POKéMON!\p"
	.string "¡Vamos, vamos, vamos!\n"
	.string "¡Mi equipo de BICHOS!$"

PetalburgWoods_Text_ICouldntWin:
	.string "Tengo todos estos POKéMON,\n"
	.string "pero no he podido ganar…$"

PetalburgWoods_Text_ImOutOfPokeBalls:
	.string "He atrapado un montón de POKéMON.\n"
	.string "Ahora no me quedan POKé BALLS.$"

PetalburgWoods_Text_InstantlyPopularWithBugPokemon:
	.string "¡Si llevas POKéMON BICHO al cole,\n"
	.string "te haces popular al momento!$"

PetalburgWoods_Text_CantBePopularIfILose:
	.string "Si pierdo, no puedo ser popular.$"

PetalburgWoods_Text_PeopleRespectYou:
	.string "Si tienes un POKéMON BICHO grande,\n"
	.string "la gente te respeta.$"

PetalburgWoods_Text_IWantRematch1:
	.string "¡Quiero la revancha cuando crezcan\n"
	.string "mis BICHOS!\p"
	.string "¡Te registro en mi POKéNAV!$"

PetalburgWoods_Text_IWantRematch2:
	.string "¡Quiero la revancha cuando crezcan\n"
	.string "mis BICHOS!\p"
	.string "¡Te registro en mi POKéNAV!$"

PetalburgWoods_Text_MyPokemonHaveGrown:
	.string "Mis BICHOS han crecido.\n"
	.string "Volveré a ser popular.$"

PetalburgWoods_Text_CantBePopularIfLose:
	.string "Si pierdo, no puedo ser popular.$"

PetalburgWoods_Text_IveBeenTrainingHard:
	.string "Con POKéMON fuertes te haces\n"
	.string "popular, ¿verdad?\l"
	.string "Así que he entrenado mucho.$"

PetalburgWoods_Text_StayOutOfTallGrass:
	.string "¡Eh, tú!\n"
	.string "¿Tus POKéMON están bien?\p"
	.string "Si son débiles y quieres evitar\n"
	.string "combates, no te metas en\l"
	.string "la hierba alta.$"

PetalburgWoods_Text_HiddenItemsExplanation:
	.string "A veces hay cosas en el suelo\n"
	.string "aunque no se vean.\p"
	.string "Por eso siempre miro por\n"
	.string "dónde piso.$"

PetalburgWoods_Text_TryUsingThisItem:
	.string "¡Anda, qué guay!\n"
	.string "¡Es la MEDALLA del GIMNASIO de FÉRRICA!\p"
	.string "Seguro que entrenas POKéMON.\n"
	.string "Deberías probar este objeto.$"

PetalburgWoods_Text_MiracleSeedExplanation:
	.string "Es una SEMILLA MILAGRO.\n"
	.string "Si la lleva un POKéMON, sus\l"
	.string "movimientos PLANTA son más fuertes.\p"
	.string "Además de esa, creo que hay otros\n"
	.string "objetos útiles para que lleven\l"
	.string "los POKéMON.$"

PetalburgWoods_Text_TrainerTipsExperience:
	.string "CONSEJOS PARA ENTRENADORES\p"
	.string "Todo POKéMON que salga aunque sea\n"
	.string "una vez en combate gana EXPERIENCIA.\p"
	.string "Para entrenar a uno débil, ponlo\n"
	.string "el primero de la lista.\p"
	.string "En cuanto empiece el combate,\n"
	.string "cámbialo. Ganará EXPERIENCIA sin\l"
	.string "recibir ningún daño.$"

PetalburgWoods_Text_TrainerTipsPP:
	.string "CONSEJOS PARA ENTRENADORES\p"
	.string "Además de los PS, los POKéMON tienen\n"
	.string "PUNTOS DE PODER (PP) para usar\l"
	.string "sus movimientos en combate.\p"
	.string "Si un POKéMON se queda sin PP,\n"
	.string "hay que llevarlo al CENTRO POKéMON.$"

