DewfordTown_Hall_MapScripts::
	.byte 0

DewfordTown_Hall_EventScript_Girl::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	special IsTrendyPhraseBoring
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_Hall_EventScript_GirlBoredOfTrend
	msgbox DewfordTown_Hall_Text_CantImagineLifeWithoutTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_GirlBoredOfTrend::
	msgbox DewfordTown_Hall_Text_GettingBoredOfTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Woman::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_TeachingMonAboutTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Man::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	special BufferDeepLinkPhrase
	msgbox DewfordTown_Hall_Text_DeepLinkBetweenXAndY, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, DewfordTown_Hall_EventScript_ConfirmTrendLink
	goto_if_eq VAR_RESULT, NO, DewfordTown_Hall_EventScript_RejectTrendLink
	end

DewfordTown_Hall_EventScript_ConfirmTrendLink::
	msgbox DewfordTown_Hall_Text_MyHunchWasRight, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_RejectTrendLink::
	msgbox DewfordTown_Hall_Text_NotEasyToKeepUp, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_ExpertM::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_TVShowAboutTrend, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEWFORD_HALL_EXPERT_M, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordTown_Hall_EventScript_Twin::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_IsTrendMorePopularAcrossSea, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEWFORD_HALL_TWIN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordTown_Hall_EventScript_LittleBoy::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_CollectTrendMerchandise, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Bookshelf::
	lockall
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_BooksAboutTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_Painting::
	lockall
	call Common_EventScript_BufferTrendyPhrase
	special GetDewfordHallPaintingNameIndex
	switch VAR_RESULT
	case 0, DewfordTown_Hall_EventScript_ScreamTitle
	case 4, DewfordTown_Hall_EventScript_ScreamTitle
	case 1, DewfordTown_Hall_EventScript_SmileTitle
	case 5, DewfordTown_Hall_EventScript_ScreamTitle
	case 2, DewfordTown_Hall_EventScript_LastTitle
	case 6, DewfordTown_Hall_EventScript_LastTitle
	case 3, DewfordTown_Hall_EventScript_BirthTitle
	case 7, DewfordTown_Hall_EventScript_LastTitle
	end

DewfordTown_Hall_EventScript_ScreamTitle::
	msgbox DewfordTown_Hall_Text_TrendsScream, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_SmileTitle::
	msgbox DewfordTown_Hall_Text_TrendsSmile, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_LastTitle::
	msgbox DewfordTown_Hall_Text_LastTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_BirthTitle::
	msgbox DewfordTown_Hall_Text_BirthOfTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_SchoolKidM::
	lockall
	setvar VAR_0x8008, 0
	goto DewfordTown_Hall_EventScript_DoTrendDebate
	end

DewfordTown_Hall_EventScript_PsychicM::
	lockall
	setvar VAR_0x8008, 1
	goto DewfordTown_Hall_EventScript_DoTrendDebate
	end

DewfordTown_Hall_EventScript_DoTrendDebate::
	call Common_EventScript_BufferTrendyPhrase
	special GetDewfordHallPaintingNameIndex
	switch VAR_RESULT
	case 0, DewfordTown_Hall_EventScript_TrendDebate1
	case 1, DewfordTown_Hall_EventScript_TrendDebate1
	case 2, DewfordTown_Hall_EventScript_TrendDebate2
	case 3, DewfordTown_Hall_EventScript_TrendDebate2
	case 4, DewfordTown_Hall_EventScript_TrendDebate3
	case 5, DewfordTown_Hall_EventScript_TrendDebate3
	case 6, DewfordTown_Hall_EventScript_TrendDebate4
	case 7, DewfordTown_Hall_EventScript_TrendDebate5
	end

DewfordTown_Hall_EventScript_TrendDebate1::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_SawTrendCoolestThing, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_AllegedTrendNotAuthentic, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate2::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_ComposedTrendThemeSong, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_WorkOnYourSinging, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate3::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_OrganizeTrendParty, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_BrilliantIndeed, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate4::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_TrendHasBecomePartOfLife, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_TrendWeighsHeavilyOnMind, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate5::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_IfWeTeamUpWellBeInvincible, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_WellBeTrendDuo, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_DontMovePlayer1::
	return

DewfordTown_Hall_EventScript_DebateReact1::
	applymovement LOCALID_DEWFORD_HALL_PSYCHIC_M, DewfordTown_Hall_Movement_PsychicWalkInPlaceLeft
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordTown_Hall_EventScript_PlayerReactWest
	goto_if_eq VAR_0x8008, 1, DewfordTown_Hall_EventScript_DontMovePlayer2
	end

DewfordTown_Hall_EventScript_PlayerReactWest::
	goto_if_eq VAR_FACING, DIR_EAST, DewfordTown_Hall_EventScript_DontMovePlayer1
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

DewfordTown_Hall_EventScript_DontMovePlayer2::
	return

DewfordTown_Hall_EventScript_DebateReact2::
	applymovement LOCALID_DEWFORD_HALL_SCHOOL_KID_M, DewfordTown_Hall_Movement_SchoolKidWalkInPlaceRight
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordTown_Hall_EventScript_PlayerReactNorthSouth
	goto_if_eq VAR_0x8008, 1, DewfordTown_Hall_EventScript_PlayerReactEast
	end

DewfordTown_Hall_EventScript_PlayerReactNorthSouth::
	call_if_eq VAR_FACING, DIR_NORTH, DewfordTown_Hall_EventScript_PlayerWalkInPlaceUp
	call_if_eq VAR_FACING, DIR_SOUTH, DewfordTown_Hall_EventScript_PlayerWalkInPlaceDown
	return

DewfordTown_Hall_EventScript_PlayerWalkInPlaceUp::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

DewfordTown_Hall_EventScript_PlayerWalkInPlaceDown::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

DewfordTown_Hall_EventScript_PlayerReactEast::
	goto_if_eq VAR_FACING, DIR_WEST, DewfordTown_Hall_EventScript_DontMovePlayer1
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

DewfordTown_Hall_Movement_PsychicWalkInPlaceLeft:
	walk_in_place_left
	step_end

DewfordTown_Hall_Movement_SchoolKidWalkInPlaceRight:
	walk_in_place_right
	step_end

DewfordTown_Hall_EventScript_SludgeBombMan::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	goto_if_set FLAG_RECEIVED_TM_SLUDGE_BOMB, DewfordTown_Hall_EventScript_ReceivedSludgeBomb
	msgbox DewfordTown_Hall_Text_GiveYouSludgeBomb, MSGBOX_DEFAULT
	giveitem ITEM_TM_SLUDGE_BOMB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_SLUDGE_BOMB
	release
	end

DewfordTown_Hall_EventScript_ReceivedSludgeBomb::
	msgbox DewfordTown_Hall_Text_LoveSludgeBombButTrendInToo, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_Text_CantImagineLifeWithoutTrend:
	.string "¿Lo que está de moda? ¡Pues claro,\n"
	.string "“{STR_VAR_1}”!\p"
	.string "¡No me imagino la vida sin\n"
	.string "“{STR_VAR_1}”!$"

DewfordTown_Hall_Text_GettingBoredOfTrend:
	.string "¿Lo que está de moda? ¡Pues claro,\n"
	.string "“{STR_VAR_1}”!\p"
	.string "Pero ya me está aburriendo un poco.\p"
	.string "Tendré que buscar lo próximo.$"

DewfordTown_Hall_Text_TeachingMonAboutTrend:
	.string "I'm teaching my POKéMON about\n"
	.string "“{STR_VAR_1},”\l"
	.string "but it's not going well.\p"
	.string "It's a bit too much, I think.$"

DewfordTown_Hall_Text_DeepLinkBetweenXAndY:
	.string "Ahora estoy estudiando lo último:\n"
	.string "“{STR_VAR_1}”.\p"
	.string "¿Es verdad que hay una relación\n"
	.string "profunda entre “{STR_VAR_1}”\l"
	.string "y “{STR_VAR_2}”?$"

DewfordTown_Hall_Text_MyHunchWasRight:
	.string "¡Oh!\n"
	.string "¡Así que tenía razón!\p"
	.string "¡Estoy un paso más cerca de ir\n"
	.string "a la última! ¡Toma ya!$"

DewfordTown_Hall_Text_NotEasyToKeepUp:
	.string "¡¿Qué?!\n"
	.string "¡¿En serio?!\p"
	.string "¡No es fácil para alguien de mi\n"
	.string "edad estar al día de las modas!$"

DewfordTown_Hall_Text_TVShowAboutTrend:
	.string "Todo esto de\n"
	.string "“{STR_VAR_1}”…\l"
	.string "¿No hay un programa de tele?$"

DewfordTown_Hall_Text_IsTrendMorePopularAcrossSea:
	.string "Al otro lado del mar…\p"
	.string "¿“{STR_VAR_1}”\n"
	.string "estará aún más de moda?$"

DewfordTown_Hall_Text_CollectTrendMerchandise:
	.string "Colecciono artículos oficiales\n"
	.string "de “{STR_VAR_1}”.\p"
	.string "Tengo MUÑECOS oficiales de\n"
	.string "“{STR_VAR_1}”…\p"
	.string "Ropa de la marca\n"
	.string "“{STR_VAR_1}”…\p"
	.string "Y libros ilustrados oficiales de\n"
	.string "“{STR_VAR_1}”.\p"
	.string "¡Jejeje, son míos!\n"
	.string "¡No te pienso dejar nada!$"

DewfordTown_Hall_Text_BooksAboutTrend:
	.string "IDENTIFYING GOOD\n"
	.string "“{STR_VAR_1}” &\l"
	.string "BAD “{STR_VAR_1}”…\p"
	.string "THE LINK BETWEEN\n"
	.string "“{STR_VAR_1}” AND\l"
	.string "POKéMON…\p"
	.string "USEFUL\n"
	.string "“{STR_VAR_1}”…\p"
	.string "It's neatly jammed with books about\n"
	.string "“{STR_VAR_1}.”$"

DewfordTown_Hall_Text_TrendsScream:
	.string "El título es “EL GRITO DE\n"
	.string "{STR_VAR_1}”.$"

DewfordTown_Hall_Text_TrendsSmile:
	.string "El título es “LA SONRISA DE\n"
	.string "{STR_VAR_1}”.$"

DewfordTown_Hall_Text_LastTrend:
	.string "El título es “EL ÚLTIMO\n"
	.string "{STR_VAR_1}”.$"

DewfordTown_Hall_Text_BirthOfTrend:
	.string "El título es “EL NACIMIENTO DE\n"
	.string "{STR_VAR_1}”.$"

DewfordTown_Hall_Text_SawTrendCoolestThing:
	.string "¡He visto “{STR_VAR_1}”!\n"
	.string "¿Mola, eh?\p"
	.string "¡Es lo más guay que hay ahora mismo!\p"
	.string "¡Fue alucinante!\n"
	.string "¡Era de verdad, sí, señor!$"

DewfordTown_Hall_Text_AllegedTrendNotAuthentic:
	.string "No, no, no.\p"
	.string "Ese supuesto\n"
	.string "“{STR_VAR_1}”\l"
	.string "que dices haber visto… no lo era.\p"
	.string "El auténtico es mucho más…\n"
	.string "¿Cómo decirlo?\l"
	.string "¡Más afilado y a la vez más suave!\p"
	.string "Bah, da igual. ¡Es asombroso!$"

DewfordTown_Hall_Text_ComposedTrendThemeSong:
	.string "Oye, escucha, he compuesto una\n"
	.string "canción para “{STR_VAR_1}”.\p"
	.string "“{STR_VAR_1}”\n"
	.string "está muy de moda ahora mismo.\p"
	.string "¡Venga, escucha!\n"
	.string "… …\p"
	.string "¡Oh!\n"
	.string "¡{STR_VAR_1}!\p"
	.string "¡Maravilloso\n"
	.string "{STR_VAR_1}!$"

DewfordTown_Hall_Text_WorkOnYourSinging:
	.string "… …\p"
	.string "Me atrevo a decir, amigo, que te\n"
	.string "vendría bien practicar el canto antes\l"
	.string "de meterte con\l"
	.string "“{STR_VAR_1}”.$"

DewfordTown_Hall_Text_OrganizeTrendParty:
	.string "En fin, como decía antes, deberíamos\n"
	.string "juntarnos y organizar una fiesta de\l"
	.string "“{STR_VAR_1}”\l"
	.string "en la isla.$"

DewfordTown_Hall_Text_BrilliantIndeed:
	.string "¡Oh, qué idea tan estupenda!\p"
	.string "¡Así se sabrá de una vez por todas\n"
	.string "quién es el mejor en\l"
	.string "“{STR_VAR_1}”!\l"
	.string "¡Brillante, sin duda!\p"
	.string "¡Desde hoy, nuestras vidas girarán\n"
	.string "en torno a “{STR_VAR_1}”!$"

DewfordTown_Hall_Text_TrendHasBecomePartOfLife:
	.string "Aunque, estaba pensando…\p"
	.string "¿No te parece que\n"
	.string "“{STR_VAR_1}” ha\l"
	.string "pasado de ser una moda a ser\l"
	.string "parte de nuestra vida diaria?$"

DewfordTown_Hall_Text_TrendWeighsHeavilyOnMind:
	.string "¿Perdón?\n"
	.string "¿Tanto así?\p"
	.string "Aunque es verdad que\n"
	.string "“{STR_VAR_1}”\l"
	.string "te ronda la cabeza, estés\l"
	.string "despierto o dormido.\p"
	.string "¡Desde luego, eres el PROFESOR de\n"
	.string "“{STR_VAR_1}”,\l"
	.string "colega!$"

DewfordTown_Hall_Text_IfWeTeamUpWellBeInvincible:
	.string "¡Si tú y yo hacemos equipo, seremos\n"
	.string "invencibles en todo lo que tenga\l"
	.string "que ver con “{STR_VAR_1}”!$"

DewfordTown_Hall_Text_WellBeTrendDuo:
	.string "¡Exacto, amigo mío!\p"
	.string "¡Seremos el DÚO\n"
	.string "“{STR_VAR_1}”!\p"
	.string "¿A que suena genial?\n"
	.string "¡Jajajá!$"

DewfordTown_Hall_Text_GiveYouSludgeBomb:
	.string "Para mí, BOMBA LODO está en lo más\n"
	.string "alto. Es lo mejor que hay.\p"
	.string "¿Qué? ¿Me estás diciendo que no\n"
	.string "conoces BOMBA LODO?\p"
	.string "Eso es lamentable.\n"
	.string "Te daré una.$"

DewfordTown_Hall_Text_LoveSludgeBombButTrendInToo:
	.string "I love SLUDGE BOMB.\p"
	.string "But POKéMON with the move\n"
	.string "“{STR_VAR_1}”\l"
	.string "are in, too.$"

