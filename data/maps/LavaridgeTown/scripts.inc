LavaridgeTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LavaridgeTown_OnFrame
	.byte 0

LavaridgeTown_OnTransition:
	setflag FLAG_VISITED_LAVARIDGE_TOWN
	call_if_set FLAG_WHITEOUT_TO_LAVARIDGE, LavaridgeTown_EventScript_ClearLavaridgeWhiteOut
	call_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, LavaridgeTown_EventScript_ShowMtChimneyTrainers
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_CheckSetRivalPos
	call_if_eq VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_HideMapNamePopup
	end

LavaridgeTown_EventScript_ClearLavaridgeWhiteOut::
	clearflag FLAG_WHITEOUT_TO_LAVARIDGE
	return

LavaridgeTown_EventScript_CheckSetRivalPos::
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 9, LavaridgeTown_EventScript_SetRivalPos
	return

LavaridgeTown_EventScript_SetRivalPos::
	setobjectxyperm LOCALID_LAVARIDGE_RIVAL, 11, 9
	setobjectxyperm LOCALID_LAVARIDGE_RIVAL_ON_BIKE, 9, 8
	setobjectmovementtype LOCALID_LAVARIDGE_RIVAL_ON_BIKE, MOVEMENT_TYPE_FACE_UP
	clearflag FLAG_HIDE_LAVARIDGE_TOWN_RIVAL
	return

LavaridgeTown_EventScript_ShowMtChimneyTrainers::
	clearflag FLAG_HIDE_MT_CHIMNEY_TRAINERS
	return

LavaridgeTown_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

LavaridgeTown_OnFrame:
	map_script_2 VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_RivalGiveGoGoggles
	.2byte 0

LavaridgeTown_EventScript_RivalGiveGoGoggles::
	lockall
	getplayerxy VAR_0x8008, VAR_0x8009
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalNoticePlayer
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExitHerbShop
	delay 20
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_PlayBrendanMusic
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalApproachPlayer1
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalApproachPlayer2
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LavaridgeTown_EventScript_MayGiveGoGoggles
	goto_if_eq VAR_RESULT, FEMALE, LavaridgeTown_EventScript_BrendanGiveGoGoggles
	end

LavaridgeTown_EventScript_MayGiveGoGoggles::
	msgbox LavaridgeTown_Text_MayNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_MayExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_BrendanGiveGoGoggles::
	msgbox LavaridgeTown_Text_BrendanNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_RivalExit::
	closemessage
	removeobject LOCALID_LAVARIDGE_RIVAL
	addobject LOCALID_LAVARIDGE_RIVAL_ON_BIKE
	delay 30
	call_if_eq VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExit1
	call_if_ne VAR_0x8008, 9, LavaridgeTown_EventScript_RivalExit2
	removeobject LOCALID_LAVARIDGE_RIVAL_ON_BIKE
	setvar VAR_LAVARIDGE_TOWN_STATE, 2
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LavaridgeTown_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

LavaridgeTown_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

LavaridgeTown_EventScript_RivalNoticePlayer::
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_Delay48
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExitHerbShop::
	opendoor 12, 15
	waitdooranim
	addobject LOCALID_LAVARIDGE_RIVAL
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalExitHerbShop
	waitmovement 0
	closedoor 12, 15
	waitdooranim
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LAVARIDGE_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer1::
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer2::
	applymovement LOCALID_LAVARIDGE_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer2
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit1::
	applymovement LOCALID_PLAYER, LavaridgeTown_Movement_PlayerWatchRivalExit
	applymovement LOCALID_LAVARIDGE_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit2::
	applymovement LOCALID_LAVARIDGE_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit2
	waitmovement 0
	return

LavaridgeTown_Movement_RivalExit2:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

LavaridgeTown_Movement_PlayerWatchRivalExit:
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

LavaridgeTown_Movement_RivalExit1:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

LavaridgeTown_Movement_RivalApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LavaridgeTown_Movement_RivalApproachPlayer1:
	walk_left
	walk_left
	walk_up
	step_end

LavaridgeTown_Movement_RivalExitHerbShop:
	walk_down
	step_end

LavaridgeTown_EventScript_HotSpringsTrigger::
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_SOUTH, LavaridgeTown_EventScript_EnteredHotSprings
	end

LavaridgeTown_EventScript_EnteredHotSprings::
	incrementgamestat GAME_STAT_ENTERED_HOT_SPRINGS
	end

LavaridgeTown_EventScript_ExpertM::
	msgbox LavaridgeTown_Text_HotSpringsNeverRunDry, MSGBOX_NPC
	end

LavaridgeTown_EventScript_OldMan::
	msgbox LavaridgeTown_Text_PokemonNippedBackside, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_Twin::
	msgbox LavaridgeTown_Text_BatheInHotSpringsEveryDay, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman1::
	msgbox LavaridgeTown_Text_IfPokemonInHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman2::
	msgbox LavaridgeTown_Text_HotSpringsClaims, MSGBOX_NPC
	end

LavaridgeTown_EventScript_ExpertF::
	msgbox LavaridgeTown_Text_OhYouLikeHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_EggWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_LAVARIDGE_EGG, LavaridgeTown_EventScript_ReceivedEgg
	msgbox LavaridgeTown_Text_HaveEggWillYouTakeIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LavaridgeTown_EventScript_DeclineEgg
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, LavaridgeTown_EventScript_NoRoomForEgg
	msgbox LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_LAVARIDGE_EGG
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_ReceivedTheEgg
	waitfanfare
	giveegg SPECIES_WYNAUT
	release
	end

LavaridgeTown_EventScript_ReceivedEgg::
	msgbox LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_NoRoomForEgg::
	msgbox LavaridgeTown_Text_NoRoomForThisEgg, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_DeclineEgg::
	msgbox LavaridgeTown_Text_AsYouWishThen, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_TownSign::
	msgbox LavaridgeTown_Text_TownSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_GymSign::
	msgbox LavaridgeTown_Text_GymSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_HerbShopSign::
	msgbox LavaridgeTown_Text_HerbShopSign, MSGBOX_SIGN
	end

LavaridgeTown_Text_MayNiceBadgesTakeThis:
	.string "AURA: ¡{PLAYER}{KUN}! ¡Cuánto tiempo!\p"
	.string "¿Oh? Mientras yo iba a las aguas\n"
	.string "termales, tú has ganado la MEDALLA\l"
	.string "del GIMNASIO de LAVACALDA.\p"
	.string "Debes de haber reunido buenos\n"
	.string "POKéMON…\l"
	.string "No, seguro que los has criado tú.\p"
	.string "Creo que no pasa nada si te doy\n"
	.string "esto.$"

LavaridgeTown_Text_MayExplainGoGogglesChallengeDad:
	.string "AURA: Con esas GAFAS AISLANTES podrás\n"
	.string "cruzar sin problemas el desierto\l"
	.string "de la RUTA 111.\p"
	.string "Pero, hala, {PLAYER}{KUN}…\n"
	.string "Desafiando GIMNASIOS…\p"
	.string "¡Seguro que te esfuerzas tanto porque\n"
	.string "no quieres perder contra mí!\p"
	.string "{PLAYER}{KUN}, creo que voy a\n"
	.string "desafiar a tu padre en PETALIA.\p"
	.string "¡Hasta otra!$"

LavaridgeTown_Text_BrendanNiceBadgesTakeThis:
	.string "BRUNO: {PLAYER}, eh, cuánto tiempo.\n"
	.string "¿Qué tal te va?\p"
	.string "Mmm…\n"
	.string "Llevas unas cuantas MEDALLAS.\p"
	.string "Vale, entonces.\n"
	.string "Ya puestos, quédate esto.$"

LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad:
	.string "BRUNO: Llévalas encima si piensas\n"
	.string "entrar en el desierto de la\l"
	.string "RUTA 111.\p"
	.string "Debe de haber POKéMON que solo\n"
	.string "viven en el desierto.\l"
	.string "Podrías buscarlos.\p"
	.string "En cuanto a mí…\n"
	.string "Estoy pensando en desafiar a NORMAN,\l"
	.string "el LÍDER del GIMNASIO de PETALIA.\p"
	.string "A diferencia de ti, {PLAYER}, tu padre\n"
	.string "sí que parece duro de verdad.\p"
	.string "¡Nos vemos!$"

LavaridgeTown_Text_HaveEggWillYouTakeIt:
	.string "Tengo aquí un HUEVO.\p"
	.string "Quería que eclosionara cubriéndolo\n"
	.string "con arena caliente de las termas.\l"
	.string "Pero parece que no basta…\p"
	.string "He oído que lo mejor es tenerlo\n"
	.string "junto a POKéMON y llevarlo de un\l"
	.string "lado a otro.\p"
	.string "Entrenas POKéMON, ¿verdad?\n"
	.string "Y tus POKéMON rebosan vitalidad.\p"
	.string "¿Qué me dices?\n"
	.string "¿Te llevas este HUEVO?$"

LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg:
	.string "¡Bien! ¡Espero que camines mucho\n"
	.string "con este HUEVO!$"

LavaridgeTown_Text_ReceivedTheEgg:
	.string "{PLAYER} ha recibido el HUEVO.$"

LavaridgeTown_Text_NoRoomForThisEgg:
	.string "¿Oh? Llevas demasiados POKéMON.\n"
	.string "No hay sitio para este HUEVO…$"

LavaridgeTown_Text_AsYouWishThen:
	.string "Como quieras…\p"
	.string "Si cambias de idea sobre este HUEVO,\n"
	.string "aquí estaré.$"

LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare:
	.string "De vez en cuando aparece un HUEVO\n"
	.string "en la GUARDERÍA POKéMON.\p"
	.string "O eso es lo que dicen, al menos.$"

LavaridgeTown_Text_HotSpringsNeverRunDry:
	.string "Sacamos toda el agua caliente que\n"
	.string "queremos y las termas nunca se secan.\p"
	.string "¿No es mágico?\p"
	.string "Estas termas salen cerca de volcanes\n"
	.string "activos. El magma calienta las vetas\l"
	.string "de agua bajo tierra y brotan\l"
	.string "aguas termales.$"

LavaridgeTown_Text_PokemonNippedBackside:
	.string "Estar enterrado en esta arena\n"
	.string "caliente es…\p"
	.string "Suspiro…\p"
	.string "Tan calentito y celestial…\p"
	.string "¿Eh? ¡Aaah! ¡Ay!\p"
	.string "¡Un POKéMON me ha mordido el trasero!$"

LavaridgeTown_Text_OhYouLikeHotSprings:
	.string "¿Oh, te gustan las aguas termales?\p"
	.string "Qué raro, con lo joven que eres.$"

LavaridgeTown_Text_BatheInHotSpringsEveryDay:
	.string "Me baño en las termas todos los días.\p"
	.string "Quiero ser una LÍDER de GIMNASIO guapa\n"
	.string "y fuerte como CANDELA.$"

LavaridgeTown_Text_IfPokemonInHotSprings:
	.string "Si metieran POKéMON en las termas,\n"
	.string "sería rarísimo.\p"
	.string "¡Podría ser un baño eléctrico, o\n"
	.string "de burbujas, o hasta de lava!$"

LavaridgeTown_Text_HotSpringsClaims:
	.string "Dicen que estas termas van bien para\n"
	.string "los nervios, los dolores musculares,\l"
	.string "los problemas amorosos y para\l"
	.string "atraer el dinero…$"

LavaridgeTown_Text_TownSign:
	.string "PUEBLO LAVACALDA\p"
	.string "“TERMAS DEL CENTRO POKéMON\n"
	.string "¡Un lugar ideal para relajarse!”$"

LavaridgeTown_Text_GymSign:
	.string "GIMNASIO POKéMON DE LAVACALDA\n"
	.string "LÍDER: CANDELA\l"
	.string "“¡Con una pasión que arde!”$"

LavaridgeTown_Text_HerbShopSign:
	.string "HERBOLARIO POKéMON\n"
	.string "“¡Cuanto más amargo, mejor cura!”$"

