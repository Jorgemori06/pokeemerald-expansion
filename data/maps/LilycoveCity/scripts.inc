LilycoveCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, LilycoveCity_OnLoad
	.byte 0

LilycoveCity_OnTransition:
	setflag FLAG_VISITED_LILYCOVE_CITY
	setvar VAR_CONTEST_HALL_STATE, 0
	setflag FLAG_HIDE_LILYCOVE_CONTEST_HALL_REPORTER
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	call Common_EventScript_SetupRivalGfxId
	end

LilycoveCity_OnLoad:
	call_if_unset FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_SetWailmerMetatiles
	end

LilycoveCity_EventScript_SetWailmerMetatiles::
	setmetatile 76, 12, METATILE_Lilycove_Wailmer0, TRUE
	setmetatile 77, 12, METATILE_Lilycove_Wailmer1, TRUE
	setmetatile 76, 13, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 77, 13, METATILE_Lilycove_Wailmer3, TRUE
	setmetatile 76, 14, METATILE_Lilycove_Wailmer0_Alt, TRUE
	setmetatile 77, 14, METATILE_Lilycove_Wailmer1_Alt, TRUE
	setmetatile 76, 15, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 77, 15, METATILE_Lilycove_Wailmer3, TRUE
	setmetatile 77, 16, METATILE_Lilycove_Wailmer0_Alt, TRUE
	setmetatile 78, 16, METATILE_Lilycove_Wailmer1_Alt, TRUE
	setmetatile 77, 17, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 78, 17, METATILE_Lilycove_Wailmer3, TRUE
	return

LilycoveCity_EventScript_BerryGentleman::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_LILYCOVE_RECEIVED_BERRY, LilycoveCity_EventScript_ReceivedBerry
	msgbox LilycoveCity_Text_BerrySuitsYou, MSGBOX_DEFAULT
	giverandomberry BERRY_ID_CHERI, BERRY_ID_SITRUS
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_LILYCOVE_RECEIVED_BERRY
	msgbox LilycoveCity_Text_BecauseYoureTrainer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ReceivedBerry::
	msgbox LilycoveCity_Text_PokeblocksSuitPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man3::
	msgbox LilycoveCity_Text_ContestHallInTown, MSGBOX_NPC
	end

LilycoveCity_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_GirlAquaGone
	msgbox LilycoveCity_Text_StrangeCaveInCove, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_GirlAquaGone::
	msgbox LilycoveCity_Text_GoingToMoveDeleterForHMs, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_RichBoy::
	msgbox LilycoveCity_Text_ImFromKanto, MSGBOX_NPC
	end

LilycoveCity_EventScript_Sailor2::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Sailor2AquaGone
	msgbox LilycoveCity_Text_TeamAquaBeenTrainingWailmer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor2AquaGone::
	msgbox LilycoveCity_Text_SomeonePuntedTeamAquaOut, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Woman2AquaGone
	msgbox LilycoveCity_Text_SomeoneStoleMyPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2AquaGone::
	msgbox LilycoveCity_Text_MissingPokemonCameBack, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man2::
	msgbox LilycoveCity_Text_ImArtDealer, MSGBOX_NPC
	end

LilycoveCity_EventScript_ExpertM1::
	msgbox LilycoveCity_Text_SeaRemainsForeverYoung, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertF::
	msgbox LilycoveCity_Text_SixtyYearsAgoHusbandProposed, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertM2::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_ExpertM2AquaGone
	msgbox LilycoveCity_Text_TeamAquaRenovatedCavern, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ExpertM2AquaGone::
	msgbox LilycoveCity_Text_TeamAquaLotGoneForGood, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor1::
	msgbox LilycoveCity_Text_HeardTowerCalledSkyPillar, MSGBOX_NPC
	end

LilycoveCity_EventScript_FatMan::
	msgbox LilycoveCity_Text_SawTallTowerOnRoute131, MSGBOX_NPC
	end

LilycoveCity_EventScript_Man1::
	lockall
	msgbox LilycoveCity_Text_JustArrivedAndSawRarePokemon, MSGBOX_NPC
	applymovement LOCALID_LILYCOVE_MAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_Woman1::
	lockall
	msgbox LilycoveCity_Text_HoneymoonVowToSeeRarePokemon, MSGBOX_NPC
	applymovement LOCALID_LILYCOVE_WOMAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_CitySign::
	msgbox LilycoveCity_Text_CitySign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ContestHallSign::
	msgbox LilycoveCity_Text_ContestHallSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MotelSign::
	msgbox LilycoveCity_Text_MotelSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MuseumSign::
	lockall
	specialvar VAR_0x8004, CountPlayerMuseumPaintings
	switch VAR_0x8004
	case 0, LilycoveCity_EventScript_MuseumSignNoPaintings
	msgbox LilycoveCity_Text_MuseumSignPlayersExhibit, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_MuseumSignNoPaintings::
	msgbox LilycoveCity_Text_MuseumSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_HarborSignFerryReady
	msgbox LilycoveCity_Text_HarborSignUnderConstruction, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSignFerryReady::
	msgbox LilycoveCity_Text_HarborSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_TrainerFanClubSign::
	msgbox LilycoveCity_Text_TrainerFanClubSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_DepartmentStoreSign::
	msgbox LilycoveCity_Text_DepartmentStoreSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MoveDeletersHouseSign::
	msgbox LilycoveCity_Text_MoveDeletersHouseSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_WailmerTrainerGrunt::
	lockall
	goto_if_set FLAG_MET_WAILMER_TRAINER, LilycoveCity_EventScript_MetWailmerTrainer
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_Text_GetLostMessingUpTraining, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_MET_WAILMER_TRAINER
	releaseall
	end

LilycoveCity_EventScript_MetWailmerTrainer::
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_AquaGrunt1::
	msgbox LilycoveCity_Text_MovedLootIntoHideoutToday, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt2::
	msgbox LilycoveCity_Text_ChanceToDoBigThings, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt3::
	msgbox LilycoveCity_Text_DontGoNearCaveInCove, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt4::
	msgbox LilycoveCity_Text_IfWorldBecomesOurs, MSGBOX_NPC
	end

LilycoveCity_EventScript_Rival::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LilycoveCity_EventScript_May
	goto_if_eq VAR_RESULT, FEMALE, LilycoveCity_EventScript_Brendan
	end

LilycoveCity_EventScript_May::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattle
	goto_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DeclineMayBattle
	msgbox LilycoveCity_Text_MayWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleMayTreecko
	case 1, LilycoveCity_EventScript_BattleMayTorchic
	case 2, LilycoveCity_EventScript_BattleMayMudkip
	end

LilycoveCity_EventScript_MayAskToBattleAgain::
	msgbox LilycoveCity_Text_MayBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_MayAskToBattle::
	msgbox LilycoveCity_Text_MayShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineMayBattle::
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_MayNotRaisingPokemon, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_Brendan::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattle
	goto_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DeclineBrendanBattle
	msgbox LilycoveCity_Text_BrendanWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleBrendanTreecko
	case 1, LilycoveCity_EventScript_BattleBrendanTorchic
	case 2, LilycoveCity_EventScript_BattleBrendanMudkip
	end

LilycoveCity_EventScript_BrendanAskToBattleAgain::
	msgbox LilycoveCity_Text_BrendanBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_BrendanAskToBattle::
	msgbox LilycoveCity_Text_BrendanShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineBrendanBattle::
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_BattleMayTreecko::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TREECKO, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayTorchic::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TORCHIC, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayMudkip::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_MUDKIP, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleBrendanTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TREECKO, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TORCHIC, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_MUDKIP, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_DefeatedMay::
	msgbox LilycoveCity_Text_MayGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_EventScript_MayCollectBadges
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_MayPokemonLeague
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_PICHU_DOLL
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_CheckFinalBadge::
	goto_if_set FLAG_BADGE08_GET, LilycoveCity_EventScript_HasFinalBadge
	return

LilycoveCity_EventScript_HasFinalBadge::
	setvar VAR_RESULT, TRUE
	return

LilycoveCity_EventScript_MayCollectBadges::
	msgbox LilycoveCity_Text_MayYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayPokemonLeague::
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_MayBattleFrontier
	msgbox LilycoveCity_Text_MayYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayBattleFrontier::
	msgbox LilycoveCity_Text_MayYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DefeatedBrendan::
	msgbox LilycoveCity_Text_BrendanGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_EventScript_BrendanCollectBadges
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_BrendanPokemonLeague
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_SWABLU_DOLL
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_BrendanCollectBadges::
	msgbox LilycoveCity_Text_BrendanYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanPokemonLeague::
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_BrendanBattleFrontier
	msgbox LilycoveCity_Text_BrendanYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanBattleFrontier::
	msgbox LilycoveCity_Text_BrendanYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_RivalFlyAway::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject VAR_LAST_TALKED
	waitfieldeffect FLDEFF_NPCFLY_OUT
	savebgm MUS_DUMMY
	fadedefaultbgm
	setflag FLAG_MET_RIVAL_LILYCOVE
	release
	end

LilycoveCity_EventScript_SchoolKidM::
	lock
	faceplayer
	msgbox LilycoveCity_Text_DoYouKnowAboutBerryBlender, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, LilycoveCity_EventScript_KnowAboutBerryBlender
	call_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DontKnowAboutBerryBlender
	release
	end

LilycoveCity_EventScript_KnowAboutBerryBlender::
	msgbox LilycoveCity_Text_FasterSpinBetterPokeblocks, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DontKnowAboutBerryBlender::
	msgbox LilycoveCity_Text_ExplainBerryBlender, MSGBOX_DEFAULT
	return

LilycoveCity_Text_MayShoppingLetsBattle:
	.string "AURA: ¿Oh, eh? ¡{PLAYER}{KUN}!\n"
	.string "¿Tú también de compras?\p"
	.string "Yo me he comprado un montón de\n"
	.string "MUÑECOS y PÓSTERES.\p"
	.string "Claro que también he atrapado muchos\n"
	.string "POKéMON y los estoy criando\l"
	.string "como es debido.\p"
	.string "La verdad, me preocupa más si tú\n"
	.string "los crías bien, {PLAYER}{KUN}.\p"
	.string "Combatiré contigo para que me\n"
	.string "enseñes tus POKéMON, {PLAYER}{KUN}.$"

LilycoveCity_Text_MayNotRaisingPokemon:
	.string "AURA: ¿Oh, por qué? {PLAYER}{KUN},\n"
	.string "¿no has criado a tus POKéMON?\p"
	.string "Eso no dice mucho de ti como\n"
	.string "ENTRENADOR…$"

LilycoveCity_Text_MayBattleMe:
	.string "AURA: ¡Venga, combate conmigo para\n"
	.string "que vea tus POKéMON!$"

LilycoveCity_Text_MayWontBeBeaten:
	.string "AURA: ¡{PLAYER}{KUN}, mis POKéMON no\n"
	.string "perderán contra los tuyos!$"

LilycoveCity_Text_MayDefeat:
	.string "… … … … … … … …\p"
	.string "Me acuerdo del combate que tuvimos\n"
	.string "en la RUTA 103, {PLAYER}{KUN}.\p"
	.string "Aquel combate te ayudó a ser tan\n"
	.string "fuerte, ¿verdad, {PLAYER}{KUN}?$"

LilycoveCity_Text_MayGoingBackToLittleroot:
	.string "AURA: Estoy pensando en volver pronto\n"
	.string "a VILLA RAÍZ.\p"
	.string "He atrapado un buen grupo de POKéMON\n"
	.string "y mi POKéDEX va avanzando, así\l"
	.string "que voy a enseñársela a mi padre.$"

LilycoveCity_Text_MayYouGoingToCollectBadges:
	.string "{PLAYER}{KUN}, ¿qué vas a hacer?\p"
	.string "¿Conseguir todas las MEDALLAS y\n"
	.string "desafiar a la LIGA POKéMON?\p"
	.string "Bueno, mientras tú consigues\n"
	.string "MEDALLAS, yo trabajaré en mi\l"
	.string "POKéDEX. ¡La completaré antes que tú!\p"
	.string "¡Hasta luego!$"

LilycoveCity_Text_MayYouGoingToPokemonLeague:
	.string "{PLAYER}{KUN}, ¿qué vas a hacer?\p"
	.string "¿Vas a desafiar a la LIGA POKéMON?\p"
	.string "¿O vas a completar tu POKéDEX?\p"
	.string "Puede que haya perdido contra ti,\n"
	.string "¡pero acabaré mi POKéDEX antes!\p"
	.string "¡Hasta luego!$"

LilycoveCity_Text_MayYouGoingToBattleFrontier:
	.string "{PLAYER}{KUN}, what are you going to do?\p"
	.string "Are you taking the BATTLE FRONTIER\n"
	.string "challenge?\p"
	.string "Or, are you going to complete your\n"
	.string "POKéDEX?\p"
	.string "I might've lost to you in battling,\n"
	.string "but I'll finish my POKéDEX before you!\p"
	.string "See you!$"

LilycoveCity_Text_BrendanShoppingLetsBattle:
	.string "BRUNO: Oh, eh, es {PLAYER}.\p"
	.string "Estoy haciendo un recado para mi padre.\n"
	.string "No, no estoy comprando MUÑECOS.\p"
	.string "Bueno, cuánto tiempo.\p"
	.string "¿Combatimos para ver quién ha criado\n"
	.string "mejor a sus POKéMON?$"

LilycoveCity_Text_BrendanNoConfidence:
	.string "BRUNO: Oh, ¿qué pasa?\n"
	.string "¿No te ves capaz?$"

LilycoveCity_Text_BrendanBattleMe:
	.string "BRUNO: ¿Combatimos para ver quién ha\n"
	.string "criado mejor a sus POKéMON?$"

LilycoveCity_Text_BrendanWontBeBeaten:
	.string "BRUNO: Ya sabes que contra ti no\n"
	.string "pienso perder, {PLAYER}.$"

LilycoveCity_Text_BrendanDefeat:
	.string "Hmpf…\n"
	.string "Los has criado mucho.\p"
	.string "Eso escuece un poco, que yo empecé\n"
	.string "a entrenar antes que tú…$"

LilycoveCity_Text_BrendanGoingBackToLittleroot:
	.string "BRUNO: Yo…\n"
	.string "Pienso volver a VILLA RAÍZ.\p"
	.string "Ya sabes que ayudo a mi padre con\n"
	.string "su POKéDEX. Va bastante bien,\l"
	.string "así que debería enseñársela.$"

LilycoveCity_Text_BrendanYouGoingToCollectBadges:
	.string "{PLAYER}, ¿qué vas a hacer?\p"
	.string "¿Conseguir todas las MEDALLAS y\n"
	.string "desafiar a la LIGA POKéMON?\p"
	.string "A lo mejor yo también lo hago…\p"
	.string "¡Bueno, ánimo!$"

LilycoveCity_Text_BrendanYouGoingToPokemonLeague:
	.string "{PLAYER}, ¿qué vas a hacer?\p"
	.string "Con lo fuerte que eres, ¿vas a\n"
	.string "desafiar a la LIGA POKéMON?\p"
	.string "Je, si yo entrenara un poco más a\n"
	.string "mis POKéMON, sería más fuerte que\l"
	.string "tú, {PLAYER}.\p"
	.string "¡Bueno, ánimo!$"

LilycoveCity_Text_BrendanYouGoingToBattleFrontier:
	.string "{PLAYER}, what are you going to do?\p"
	.string "Are you taking the BATTLE FRONTIER\n"
	.string "challenge?\p"
	.string "Or, are you going to complete your\n"
	.string "POKéDEX?\p"
	.string "Since you're that strong, you should\n"
	.string "consider the BATTLE FRONTIER.\p"
	.string "Heh, if I train my POKéMON a bit more,\n"
	.string "I'll get stronger than you, {PLAYER}.\p"
	.string "Maybe I should go to the BATTLE\n"
	.string "FRONTIER.\p"
	.string "Well, anyway, hang in there!$"

LilycoveCity_Text_MovedLootIntoHideoutToday:
	.string "Fufufu…\p"
	.string "Hoy hemos metido más botín en la\n"
	.string "GUARIDA secreta…\p"
	.string "¡¿Q-quién eres?!\n"
	.string "¡Solo hablaba solo!$"

LilycoveCity_Text_ChanceToDoBigThings:
	.string "Solo soy un SOLDADO, así que no sé\n"
	.string "qué piensa el JEFE…\p"
	.string "¡Pero en el EQUIPO AQUA sé que tendré\n"
	.string "la ocasión de hacer cosas grandes!\p"
	.string "¡¿Q-quién eres?!\n"
	.string "¡Solo hablaba solo!$"

LilycoveCity_Text_DontGoNearCaveInCove:
	.string "¡Eh, tú!\p"
	.string "¡No te acerques a la cueva de la cala!\p"
	.string "¿Por qué? ¡No te hace falta saberlo!\n"
	.string "¡Soy mayor, así que hazme caso!$"

LilycoveCity_Text_IfWorldBecomesOurs:
	.string "Si el mundo entero es nuestro, del\n"
	.string "EQUIPO AQUA, también será un sitio\l"
	.string "más feliz para los POKéMON.$"

LilycoveCity_Text_WailmerLeapOutOfWater:
	.string "¡Venga! ¡WAILMER!\n"
	.string "¡Salta fuera del agua!$"

LilycoveCity_Text_GetLostMessingUpTraining:
	.string "¿Eh? ¿Qué quieres?\p"
	.string "Nos estás fastidiando el entreno,\n"
	.string "así que ¿te largas, o qué?$"

LilycoveCity_Text_ContestHallInTown:
	.string "En este pueblo hay una SALA DE\n"
	.string "CONCURSOS POKéMON.\p"
	.string "Eso quiere decir que vienen POKéMON\n"
	.string "bien criados de todo el país.\p"
	.string "¡Se me hincha el corazón de emoción!$"

LilycoveCity_Text_StrangeCaveInCove:
	.string "¿Has visto esa cueva tan rara de la\n"
	.string "cala de las afueras?$"

LilycoveCity_Text_GoingToMoveDeleterForHMs:
	.string "Voy a enseñarle movimientos nuevos a\n"
	.string "mi POKéMON para un CONCURSO.\p"
	.string "Así que voy a ver al\n"
	.string "OLVIDAMOVIMIENTOS para que olvide\l"
	.string "los movimientos de MO.$"

LilycoveCity_Text_ImFromKanto:
	.string "Vengo de KANTO.\p"
	.string "La región de HOENN es preciosa, con\n"
	.string "tanta agua y tanta naturaleza.\p"
	.string "¿Eh? Espera un momento…\p"
	.string "¿Habrá POKéMON raros que solo vivan\n"
	.string "por aquí?$"

LilycoveCity_Text_TeamAquaBeenTrainingWailmer:
	.string "El EQUIPO AQUA está entrenando a sus\n"
	.string "WAILMER en la cala.\p"
	.string "¡Los MARINEROS no podemos sacar los\n"
	.string "barcos con ellos en medio!$"

LilycoveCity_Text_SomeonePuntedTeamAquaOut:
	.string "¡Ah del barco! ¿Sabes qué?\p"
	.string "¡Alguien ha echado al EQUIPO AQUA\n"
	.string "por nosotros!\p"
	.string "Los WAILMER se han ido de la cala, así\n"
	.string "que ya podemos sacar los barcos.$"

LilycoveCity_Text_SomeoneStoleMyPokemon:
	.string "Estaba echando una siesta en la posada\n"
	.string "de la playa, con el ruido de las olas…\p"
	.string "¡Y alguien me ha robado el POKéMON!\p"
	.string "¿Quién habrá sido?\n"
	.string "¿Ha sido el EQUIPO AQUA?$"

LilycoveCity_Text_MissingPokemonCameBack:
	.string "Mi POKéMON desaparecido…\n"
	.string "¡Ha vuelto sin que me diera cuenta!$"

LilycoveCity_Text_ImArtDealer:
	.string "Soy MARCHANTE DE ARTE.\p"
	.string "Compro y vendo obras de arte,\n"
	.string "sobre todo cuadros.\p"
	.string "He oído que el MUSEO de aquí expone\n"
	.string "obras magníficas…$"

LilycoveCity_Text_SeaRemainsForeverYoung:
	.string "Aunque nos hagamos viejos y arrugados,\n"
	.string "el mar sigue siempre joven, con el\l"
	.string "brillo intenso de la vida…\p"
	.string "Jojojo, jojojojo…$"

LilycoveCity_Text_SixtyYearsAgoHusbandProposed:
	.string "Hace sesenta años mi marido se me\n"
	.string "declaró aquí.\l"
	.string "El mar sigue tan bonito como siempre.\p"
	.string "Jijiji, jijijiji…$"

LilycoveCity_Text_TeamAquaRenovatedCavern:
	.string "Mm, ¿conoces la caverna tan rara\n"
	.string "que hay en esta cala?\p"
	.string "Era una formación natural, pero\n"
	.string "llegaron los del EQUIPO AQUA\l"
	.string "y la reformaron.\p"
	.string "¡Dicen que son el “EQUIPO AQUA,\n"
	.string "amante de la naturaleza”!\p"
	.string "¡Pero lo que hacen y lo que dicen no\n"
	.string "tienen nada que ver!$"

LilycoveCity_Text_TeamAquaLotGoneForGood:
	.string "Esa cueva de la cala…\p"
	.string "No me di cuenta enseguida, pero\n"
	.string "ahora está totalmente vacía.\p"
	.string "Esos del EQUIPO AQUA se habrán ido\n"
	.string "para siempre.$"

LilycoveCity_Text_CitySign:
	.string "CIUDAD CALAGUA\p"
	.string "“Donde acaba la tierra y empieza\n"
	.string "el mar”.$"

LilycoveCity_Text_ContestHallSign:
	.string "SALA DE CONCURSOS POKéMON\n"
	.string "“¡Donde se reúnen los ENTRENADORES!”$"

LilycoveCity_Text_MotelSign:
	.string "MOTEL CALAGUA\p"
	.string "“Que nos recuerden como el motel\n"
	.string "de CALAGUA”.$"

LilycoveCity_Text_MuseumSign:
	.string "MUSEO DE CALAGUA\p"
	.string "“¡Exposición de obras maestras\n"
	.string "POKéMON!”$"

LilycoveCity_Text_MuseumSignPlayersExhibit:
	.string "MUSEO DE CALAGUA\p"
	.string "“¡Exposición de la colección\n"
	.string "POKéMON de {PLAYER}!”$"

LilycoveCity_Text_HarborSignUnderConstruction:
	.string "PUERTO DE CIUDAD CALAGUA\p"
	.string "“El ferry M.S. MAREA se está\n"
	.string "construyendo en CIUDAD PORTUAL.\p"
	.string "”Empezará a funcionar en breve”.$"

LilycoveCity_Text_HarborSign:
	.string "PUERTO DE CIUDAD CALAGUA\p"
	.string "“Disfruta de un crucero en el ferry\n"
	.string "M.S. MAREA”.$"

LilycoveCity_Text_TrainerFanClubSign:
	.string "CLUB DE FANS DE ENTRENADORES\p"
	.string "El cartel está lleno de nombres de\n"
	.string "ENTRENADORES garabateados…$"

LilycoveCity_Text_DepartmentStoreSign:
	.string "CENTRO COMERCIAL DE CALAGUA\p"
	.string "“¡Rebosante de artículos geniales\n"
	.string "y de emoción!\p"
	.string "”¡El sitio ideal para encontrar eso\n"
	.string "que necesitas!”$"

LilycoveCity_Text_MoveDeletersHouseSign:
	.string "CASA DEL OLVIDAMOVIMIENTOS\p"
	.string "“Se borran movimientos POKéMON\n"
	.string "que no se quieren”.$"

LilycoveCity_Text_DoYouKnowAboutBerryBlender:
	.string "¿Conoces la máquina llamada\n"
	.string "LICUADORA DE BAYAS?$"

LilycoveCity_Text_FasterSpinBetterPokeblocks:
	.string "Hay que coordinarse para que gire\n"
	.string "más rápido.\p"
	.string "He oído que cuanto más rápido gira,\n"
	.string "mejores {POKEBLOCK}S salen.$"

LilycoveCity_Text_ExplainBerryBlender:
	.string "Sirve para hacer unos caramelos que\n"
	.string "se llaman {POKEBLOCK}S.\p"
	.string "Si le das un buen {POKEBLOCK} a un\n"
	.string "POKéMON, su estado mejora mucho.$"

LilycoveCity_Text_HeardTowerCalledSkyPillar:
	.string "He oído que hay una torre por alguna\n"
	.string "de las rutas del mar.\p"
	.string "Dicen que se llama PILAR CELESTE.$"

LilycoveCity_Text_SawTallTowerOnRoute131:
	.string "Vi una torre muy alta por la\n"
	.string "RUTA 131.\p"
	.string "¿Será esa…?$"

LilycoveCity_Text_JustArrivedAndSawRarePokemon:
	.string "Acabamos de llegar de luna de miel.\p"
	.string "Y hemos visto un POKéMON de tipo\n"
	.string "DRAGÓN volando muy alto en el cielo.\p"
	.string "¿En HOENN viven POKéMON tan\n"
	.string "chulos como ese?$"

LilycoveCity_Text_HoneymoonVowToSeeRarePokemon:
	.string "En la luna de miel nos prometimos ver\n"
	.string "todos los POKéMON raros posibles.\p"
	.string "Y nada más llegar vimos uno raro.\n"
	.string "¡Qué alegría!\p"
	.string "¡Vamos, que estamos felicísimos!$"

