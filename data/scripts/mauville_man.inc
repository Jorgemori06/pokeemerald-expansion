MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan::
	special Script_GetCurrentMauvilleMan
	switch VAR_RESULT
	case MAUVILLE_MAN_BARD, MauvilleCity_PokemonCenter_1F_EventScript_Bard
	case MAUVILLE_MAN_HIPSTER, MauvilleCity_PokemonCenter_1F_EventScript_Hipster
	case MAUVILLE_MAN_TRADER, MauvilleCity_PokemonCenter_1F_EventScript_Trader
	case MAUVILLE_MAN_STORYTELLER, MauvilleCity_PokemonCenter_1F_EventScript_Storyteller
	case MAUVILLE_MAN_GIDDY, MauvilleCity_PokemonCenter_1F_EventScript_Giddy
	end

@ Bard
MauvilleCity_PokemonCenter_1F_EventScript_Bard::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_PlaySong
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong
	end

MauvilleCity_PokemonCenter_1F_EventScript_PlaySong::
	setvar VAR_0x8004, FALSE  @ Play his current song
	special PlayBardSong
	delay 60
	special HasBardSongBeenChanged
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong::
	msgbox MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	end

MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics::
	setvar VAR_0x8004, EASY_CHAT_TYPE_BARD_SONG
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, TRUE  @ Play the new song
	special PlayBardSong
	delay 60
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	special SaveBardSongLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics::
	msgbox MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2, MSGBOX_DEFAULT
	release
	end

@ Hipster
MauvilleCity_PokemonCenter_1F_EventScript_Hipster::
	lock
	faceplayer
	setflag FLAG_UNLOCKED_TRENDY_SAYINGS
	msgbox MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening, MSGBOX_DEFAULT
	special HasHipsterTaughtWord
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord
	msgbox MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord::
	special HipsterTryTeachWord
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_TeachWord
	msgbox MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TeachWord::
	msgbox MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfWord, MSGBOX_DEFAULT
	special SetHipsterTaughtWord
	release
	end

@ Trader
MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor:
	.string "Hola, soy el COMERCIANTE.\n"
	.string "¿Quieres cambiar adornos conmigo?$"

MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues:
	.string "Oh…\n"
	.string "Me has dejado muy triste…$"

MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded:
	.string "Pero tú y yo ya hemos cambiado\n"
	.string "adornos.$"

MauvilleCity_PokemonCenter_1F_Text_PickADecorItem:
	.string "Si ves algún adorno mío que\n"
	.string "quieras, dímelo.$"

MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything:
	.string "¿No quieres nada?\n"
	.string "Me siento despreciado…$"

MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt:
	.string "Ese adorno era de\n"
	.string "{STR_VAR_1}.\p"
	.string "¿Lo quieres?$"

MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor:
	.string "Eh… Un momento. ¡No tienes ni un\n"
	.string "solo adorno!$"

MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade:
	.string "Vale, elige el adorno que me vas\n"
	.string "a dar a cambio.$"

MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade:
	.string "¿No quieres cambiar conmigo?\n"
	.string "Me siento despreciado…$"

MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis:
	.string "Ya tienes todos los adornos de tipo\n"
	.string "{STR_VAR_2} que caben. No hay sitio.$"

MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor:
	.string "Vale, ¿entonces cambiamos mi\n"
	.string "{STR_VAR_3} por tu {STR_VAR_2}?$"

MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse:
	.string "Ese adorno lo estás usando.\n"
	.string "No lo puedes cambiar.$"

MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC:
	.string "¡Pues trato hecho!\n"
	.string "Te mando mi adorno a tu PC.$"

MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne:
	.string "¡Huy! ¡Lo siento! Ese adorno es muy\n"
	.string "raro.\l"
	.string "¡Ese no lo puedo cambiar!\p"
	.string "¿Te interesa otra cosa?$"

MauvilleCity_PokemonCenter_1F_EventScript_Trader::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade
	special GetTraderTradedFlag
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded
	message MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade::
	msgbox MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive::
	special TraderMenuGetDecoration
	goto_if_eq VAR_0x8004, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor
	goto_if_eq VAR_0x8004, 0xFFFF, MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor
	msgbox MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor
	special DoesPlayerHaveNoDecorations
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor::
	message MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor::
	message MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive::
	msgbox MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade, MSGBOX_DEFAULT
	special TraderShowDecorationMenu
	goto_if_eq VAR_0x8006, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor
	goto_if_eq VAR_0x8006, 0xFFFF, MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse
	special IsDecorationCategoryFull
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor
	msgbox MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	special TraderDoDecorationTrade
	msgbox MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse::
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse, MSGBOX_DEFAULT
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis, MSGBOX_DEFAULT
	release
	end

@ Storyteller
MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale:
	.string "Soy el CUENTACUENTOS.\n"
	.string "Te contaré historias de ENTRENADORES\l"
	.string "legendarios.\p"
	.string "¿Quieres oír mi historia?$"

MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues:
	.string "Oh…\n"
	.string "Me has dejado muy triste…$"

MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell:
	.string "Conozco estas leyendas.\n"
	.string "¿Cuál quieres que te cuente?$"

MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales:
	.string "Pero no conozco a ningún ENTRENADOR\n"
	.string "legendario, así que no sé historias.\p"
	.string "¿Dónde se encuentra un ENTRENADOR\n"
	.string "digno de una leyenda?$"

MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes:
	.string "¡¿Qué?!\n"
	.string "Tú… ¿Tú…?\p"
	.string "¡¿Has {STR_VAR_2}\n"
	.string "{STR_VAR_1} veces?!\p"
	.string "¡Es verdaderamente magnífico!\n"
	.string "¡Nace una nueva leyenda!$"

MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends:
	.string "Me hace pensar… ¿Habrá otros\n"
	.string "ENTRENADORES con leyendas aún más\l"
	.string "impresionantes por descubrir?$"

MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales:
	.string "¿Eres ENTRENADOR?\p"
	.string "Entonces dime, ¿tienes alguna\n"
	.string "historia que sea mínimamente\l"
	.string "legendaria?$"

@ Unused
MauvilleCity_PokemonCenter_1F_Text_HearAnotherLegendaryTale:
	.string "Por cierto… ¿Te gustaría oír otra\n"
	.string "historia legendaria?$"

MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend:
	.string "Mmm…\n"
	.string "No me convence…\p"
	.string "Ojalá me trajeras algo digno de\n"
	.string "llamarse leyenda.$"

MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested:
	.string "Ojalá a más gente le interesaran mis\n"
	.string "historias épicas de ENTRENADORES\l"
	.string "legendarios.$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameTitle::
	.string "El ENTRENADOR guardador$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameAction::
	.string "guardado la partida$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR guardó la partida\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡Nunca encontrarás un ENTRENADOR\n"
	.string "más precavido que {STR_VAR_3}!$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedTitle::
	.string "El ENTRENADOR a la moda$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedAction::
	.string "creado modas$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR creó modas nuevas\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} marca tendencia en toda\n"
	.string "la región de HOENN!$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedTitle::
	.string "El ENTRENADOR sembrador$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedAction::
	.string "plantado BAYAS$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR plantó BAYAS\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} es un amante legendario\n"
	.string "de las BAYAS!$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesTitle::
	.string "El ENTRENADOR ciclista$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesAction::
	.string "cambiado de BICI$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR cambió de BICI\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡A {STR_VAR_3} le deben de encantar\n"
	.string "las BICIS con locura!$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsTitle::
	.string "El ENTRENADOR entrevistado$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsAction::
	.string "dado entrevistas$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR dio entrevistas\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} debe de ser un ENTRENADOR\n"
	.string "que llama mucho la atención!$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesTitle::
	.string "El ENTRENADOR peleón$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesAction::
	.string "combatido$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR combatió\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} debe de ser un ENTRENADOR\n"
	.string "que nunca rechaza un combate!$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtTitle::
	.string "El ENTRENADOR cazador$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtAction::
	.string "capturado POKéMON$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR capturó\n"
	.string "{STR_VAR_1} POKéMON!\p"
	.string "¡{STR_VAR_3} es un cazador legendario\n"
	.string "de POKéMON salvajes!$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtTitle::
	.string "El ENTRENADOR pescador$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtAction::
	.string "pescado POKéMON$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR pescó\n"
	.string "{STR_VAR_1} POKéMON!\p"
	.string "¡{STR_VAR_3} es un pescador\n"
	.string "legendario!$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedTitle::
	.string "El ENTRENADOR incubador$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedAction::
	.string "hecho eclosionar HUEVOS$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡De los HUEVOS de este ENTRENADOR\n"
	.string "nacieron {STR_VAR_1} POKéMON!\p"
	.string "¡{STR_VAR_3} es un incubador\n"
	.string "legendario de HUEVOS!$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedTitle::
	.string "El ENTRENADOR evolucionador$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedAction::
	.string "hecho evolucionar POKéMON$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR hizo evolucionar a\n"
	.string "{STR_VAR_1} POKéMON!\p"
	.string "¡{STR_VAR_3} es el evolucionador\n"
	.string "de POKéMON definitivo!$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterTitle::
	.string "El ENTRENADOR del CENTRO$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterAction::
	.string "ido al CENTRO POKéMON$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR curó a sus POKéMON\n"
	.string "{STR_VAR_1} veces en CENTROS POKéMON!\p"
	.string "¡Nadie quiere tanto a los CENTROS\n"
	.string "POKéMON como {STR_VAR_3}!$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeTitle::
	.string "El ENTRENADOR casero$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeAction::
	.string "descansado en casa$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR curó a sus POKéMON\n"
	.string "en casa {STR_VAR_1} veces!\p"
	.string "¡No hay nadie más casero que\n"
	.string "{STR_VAR_3}!$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesTitle::
	.string "El ENTRENADOR del SAFARI$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesAction::
	.string "entrado en la ZONA SAFARI$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR entró en la ZONA\n"
	.string "SAFARI {STR_VAR_1} veces!\p"
	.string "¡A {STR_VAR_3} le sale el lado salvaje\n"
	.string "en la ZONA SAFARI!$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutTitle::
	.string "El ENTRENADOR podador$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutAction::
	.string "usado CORTE$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR usó CORTE\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡A {STR_VAR_3} le debe de encantar\n"
	.string "CORTAR!$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashTitle::
	.string "El ENTRENADOR rompepiedras$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashAction::
	.string "roto rocas$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR usó GOLPE ROCA\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} no puede dejar una piedra\n"
	.string "sin romper!$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesTitle::
	.string "El ENTRENADOR nómada$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesAction::
	.string "mudado su BASE SECRETA$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR mudó su BASE\n"
	.string "SECRETA {STR_VAR_1} veces!\p"
	.string "¡A {STR_VAR_3} le encanta mudarse\n"
	.string "a menudo!$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashTitle::
	.string "El ENTRENADOR salpicón$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashAction::
	.string "usado SALPICADURA$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR usó SALPICADURA\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡A {STR_VAR_3} le debe de encantar\n"
	.string "SALPICAR!$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleTitle::
	.string "El ENTRENADOR tenaz$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleAction::
	.string "tenido que usar FORCEJEO$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR tuvo que usar\n"
	.string "FORCEJEO {STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} es un ENTRENADOR tenaz\n"
	.string "que nunca se rinde!$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsTitle::
	.string "El rey de las TRAGAPERRAS$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsAction::
	.string "ganado el premio gordo$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR ganó el premio gordo\n"
	.string "de las TRAGAPERRAS {STR_VAR_1} veces.\p"
	.string "¡{STR_VAR_3} tuvo mucha suerte en las\n"
	.string "TRAGAPERRAS!$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsTitle::
	.string "El rey de la RULETA$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsAction::
	.string "ganado seguidas en la RULETA$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR ganó en la RULETA\n"
	.string "{STR_VAR_1} veces seguidas.\p"
	.string "¡{STR_VAR_3} tuvo suerte con la bola\n"
	.string "de la RULETA!$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesTitle::
	.string "El aspirante de la TORRE BATALLA$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesAction::
	.string "ido a la TORRE BATALLA$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR aceptó el desafío de\n"
	.string "la TORRE BATALLA {STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} aspira a la excelencia\n"
	.string "en la TORRE BATALLA!$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksTitle::
	.string "El ENTRENADOR licuador$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksAction::
	.string "hecho {POKEBLOCK}S$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR hizo {POKEBLOCK}S\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡Nadie usa la LICUADORA de BAYAS\n"
	.string "mejor que {STR_VAR_3}!$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsTitle::
	.string "El ENTRENADOR concursante$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsAction::
	.string "ido a CONCURSOS$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR participó en\n"
	.string "CONCURSOS {STR_VAR_1} veces!\p"
	.string "¡A {STR_VAR_3} le debe de encantar\n"
	.string "lucir a sus POKéMON!$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsTitle::
	.string "El maestro de los CONCURSOS$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsAction::
	.string "ganado CONCURSOS$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR ganó CONCURSOS\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} debe de ser un maestro\n"
	.string "increíble de los CONCURSOS!$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedTitle::
	.string "El comprador feliz$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedAction::
	.string "ido de compras$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR compró en tiendas\n"
	.string "{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe de ser de esas\n"
	.string "personas que nacen para comprar.$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderTitle::
	.string "El ENTRENADOR buscatesoros$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderAction::
	.string "usado un BUSCAOBJETOS$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR usó un BUSCAOBJETOS\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡A {STR_VAR_3} le debe de encantar\n"
	.string "buscar objetos ocultos!$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedTitle::
	.string "El ENTRENADOR empapado$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedAction::
	.string "acabado empapado$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡A este ENTRENADOR le cayó la lluvia\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡El carisma de {STR_VAR_3} hasta\n"
	.string "atrae la lluvia!$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexTitle::
	.string "El lector de la POKéDEX$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexAction::
	.string "mirado la POKéDEX$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR miró la POKéDEX\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡A {STR_VAR_3} le debe de encantar\n"
	.string "estudiar POKéMON en la POKéDEX!$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsTitle::
	.string "El coleccionista de CINTAS$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsAction::
	.string "recibido CINTAS$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR recibió CINTAS\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡A {STR_VAR_3} le debe de encantar\n"
	.string "coleccionar CINTAS!$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedTitle::
	.string "El ENTRENADOR saltarín$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedAction::
	.string "saltado bordillos$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR saltó bordillos\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡Si hay un bordillo, {STR_VAR_3}\n"
	.string "no puede evitar saltarlo!$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedTitle::
	.string "El telespectador legendario$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedAction::
	.string "visto la tele$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR vio la tele\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡A {STR_VAR_3} le debe de encantar\n"
	.string "ver la tele!$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockTitle::
	.string "El ENTRENADOR puntual$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockAction::
	.string "mirado la hora$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR miró la hora\n"
	.string "{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe de ser un ENTRENADOR\n"
	.string "puntual que no pierde la hora.$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryTitle::
	.string "El mago de la LOTERÍA POKéMON$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryAction::
	.string "ganado la LOTERÍA POKéMON$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR ganó la LOTERÍA\n"
	.string "POKéMON {STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} debe de tener muchos\n"
	.string "amigos con quien cambiar POKéMON!$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareTitle::
	.string "El ENTRENADOR de la GUARDERÍA$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareAction::
	.string "dejado POKéMON en la GUARDERÍA$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR dejó POKéMON en la\n"
	.string "GUARDERÍA {STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} debe de ser alguien muy\n"
	.string "ambicioso criando POKéMON!$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarTitle::
	.string "El ENTRENADOR del TELEFÉRICO$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarAction::
	.string "subido al TELEFÉRICO$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR subió al TELEFÉRICO\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} debe de ser un ENTRENADOR\n"
	.string "que no para de subir y bajar!$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsTitle::
	.string "El ENTRENADOR de las termas$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsAction::
	.string "ido a las aguas termales$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR se bañó en aguas\n"
	.string "termales {STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} debe de tener la piel\n"
	.string "suave como la de un bebé!$"


MauvilleCity_PokemonCenter_1F_EventScript_Storyteller::
	lock
	faceplayer
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, 0
	setvar VAR_0x800A, 0
	setvar VAR_0x800B, 0
	msgbox MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar VAR_RESULT, StorytellerGetFreeStorySlot
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales
	message MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell
	waitmessage
	special StorytellerStoryListMenu
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection
	setvar VAR_0x8008, 1
	special Script_StorytellerDisplayStory
	waitmessage
	waitbuttonpress
	specialvar VAR_RESULT, StorytellerUpdateStat
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales
	goto MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale

MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection::
	goto MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	end

MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends, MSGBOX_DEFAULT
	specialvar VAR_RESULT, HasStorytellerAlreadyRecorded
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd
	goto MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales

MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales, MSGBOX_DEFAULT
MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar VAR_RESULT, Script_StorytellerInitializeRandomStat
	goto_if_eq VAR_RESULT, 1, MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale
	msgbox MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller::
	msgbox MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

@ Unused
MauvilleCity_PokemonCenter_1F_EventScript_WaitingForRecordMix::
	msgbox MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd::
	release
	end

@ Giddy
MauvilleCity_PokemonCenter_1F_Text_HearMyStory:
	.string "¡Soy el CHARLATÁN!\n"
	.string "¡Tengo una historia brillante para ti!\p"
	.string "¿Quieres oír mi historia?$"

MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues:
	.string "Oh…\n"
	.string "Me has dejado muy triste…$"

MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking:
	.string "Y además, estaba pensando…$"

MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain:
	.string "Creo que eso es todo…\p"
	.string "¡Tenemos que volver a charlar!\n"
	.string "¡Adiós!$"

MauvilleCity_PokemonCenter_1F_EventScript_Giddy::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_HearMyStory, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale::
	special GiddyShouldTellAnotherTale
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale::
	special GiddyShouldTellAnotherTale
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale::
	msgbox MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking, MSGBOX_DEFAULT
	goto MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	end

@ Giddy will continue to tell stories regardless of whether yes or no is selected below.
@ Each story there is a 10% chance it will be his last. Otherwise he will stop at 10 stories.
MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale::
	special GenerateGiddyLine
	special ShowFieldMessageStringVar4
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy::
	msgbox MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong:
	.string "Hola, soy el BARDO.\n"
	.string "¿Quieres oír mi canción?$"

MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1:
	.string "Oh…\n"
	.string "Me has dejado muy triste…$"

MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers:
	.string "Oh, qué canción tan emotiva…\n"
	.string "Ojalá pudiera tocarla para otros…$"

MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics:
	.string "¿Y bien?\n"
	.string "¿Te gusta mi canción?\p"
	.string "Pero la letra no me acaba de\n"
	.string "convencer.\p"
	.string "¿Te gustaría escribirme una\n"
	.string "letra nueva?$"

MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2:
	.string "Oh…\n"
	.string "Me has dejado muy triste…$"

MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou:
	.string "¡Muchísimas gracias!\n"
	.string "Deja que te la cante.$"

MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo:
	.string "¿Así querías que sonara tu\n"
	.string "canción?$"

MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile:
	.string "¡Vale! Pues así se queda.\n"
	.string "Cantaré esta canción una temporada.$"

MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening:
	.string "¡Eh, colega! Me llaman el MODERNO.\n"
	.string "Te enseñaré lo que está de moda.$"

MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou:
	.string "Pero, eh, ya te enseñé lo que está\n"
	.string "de moda.\p"
	.string "Quiero compartir la buena nueva\n"
	.string "con otra gente.$"

MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach:
	.string "Pero, eh, tú ya sabes un montón de\n"
	.string "lo que está de moda.\p"
	.string "¡No tengo nada nuevo que enseñarte!$"

MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfWord:
	.string "Eh, ¿has oído hablar de\n"
	.string "“{STR_VAR_1}”?\p"
	.string "¿Que qué significa? Pues…\n"
	.string "Pregúntaselo a tus padres, ¿vale?$"
