MauvilleCity_BikeShop_MapScripts::
	.byte 0

MauvilleCity_BikeShop_EventScript_Rydel::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BIKE, MauvilleCity_BikeShop_EventScript_AskSwitchBikes
	goto_if_set FLAG_DECLINED_BIKE, MauvilleCity_BikeShop_EventScript_SkipGreeting
	msgbox MauvilleCity_BikeShop_Text_RydelGreeting, MSGBOX_DEFAULT
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_SkipGreeting::
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_ChooseBike::
	message MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne
	waitmessage
	multichoice 21, 8, MULTI_BIKE, TRUE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_GetMachBike
	case 1, MauvilleCity_BikeShop_EventScript_GetAcroBike
	end

MauvilleCity_BikeShop_EventScript_NotFar::
	setflag FLAG_DECLINED_BIKE
	msgbox MauvilleCity_BikeShop_Text_GuessYouDontNeedBike, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_YesFar::
	setflag FLAG_RECEIVED_BIKE
	goto MauvilleCity_BikeShop_EventScript_ChooseBike
	end

MauvilleCity_BikeShop_EventScript_GetMachBike::
	msgbox MauvilleCity_BikeShop_Text_ChoseMachBike, MSGBOX_DEFAULT
	giveitem ITEM_MACH_BIKE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_GetAcroBike::
	msgbox MauvilleCity_BikeShop_Text_ChoseAcroBike, MSGBOX_DEFAULT
	giveitem ITEM_ACRO_BIKE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes, MSGBOX_DEFAULT
	special SwapRegisteredBike
	release
	end

MauvilleCity_BikeShop_EventScript_AskSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_WantToSwitchBikes, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_SwitchBikes
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_KeepBike
	end

@ If the player does not have a bike on them Rydel assumes its stored in the PC
MauvilleCity_BikeShop_EventScript_SwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_IllSwitchBikes, MSGBOX_DEFAULT
	checkitem ITEM_ACRO_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchAcroForMach
	checkitem ITEM_MACH_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchMachForAcro
	msgbox MauvilleCity_BikeShop_Text_OhYourBikeIsInPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_KeepBike::
	msgbox MauvilleCity_BikeShop_Text_HappyYouLikeIt, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_SwitchAcroForMach::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedAcroForMach, MSGBOX_DEFAULT
	removeitem ITEM_ACRO_BIKE
	giveitem ITEM_MACH_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_SwitchMachForAcro::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedMachForAcro, MSGBOX_DEFAULT
	removeitem ITEM_MACH_BIKE
	giveitem ITEM_ACRO_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_Assistant::
	msgbox MauvilleCity_BikeShop_Text_HandbooksAreInBack, MSGBOX_NPC
	end

MauvilleCity_BikeShop_EventScript_MachBikeHandbook::
	message MauvilleCity_BikeShop_Text_MachHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage::
	multichoice 0, 0, MULTI_MACH_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_HowToRide
	case 1, MauvilleCity_BikeShop_EventScript_HowToTurn
	case 2, MauvilleCity_BikeShop_EventScript_SandySlopes
	case 3, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	end

MauvilleCity_BikeShop_EventScript_HowToRide::
	message MauvilleCity_BikeShop_Text_HowToRideMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_HowToTurn::
	message MauvilleCity_BikeShop_Text_HowToTurnMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_SandySlopes::
	message MauvilleCity_BikeShop_Text_SandySlopes
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitMachHandbook::
	release
	end

MauvilleCity_BikeShop_EventScript_AcroBikeHandbook::
	message MauvilleCity_BikeShop_Text_AcroHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage::
	multichoice 0, 0, MULTI_ACRO_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_Wheelies
	case 1, MauvilleCity_BikeShop_EventScript_BunnyHops
	case 2, MauvilleCity_BikeShop_EventScript_Jumps
	case 3, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	end

MauvilleCity_BikeShop_EventScript_Wheelies::
	message MauvilleCity_BikeShop_Text_Wheelies
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_BunnyHops::
	message MauvilleCity_BikeShop_Text_BunnyHops
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_Jumps::
	message MauvilleCity_BikeShop_Text_Jumps
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitAcroHandbook::
	release
	end

MauvilleCity_BikeShop_Text_RydelGreeting:
	.string "Vaya, vaya, ¿qué tenemos aquí?\n"
	.string "¡Un cliente de lo más enérgico!\p"
	.string "¿Yo? Puedes llamarme RYDEL.\n"
	.string "Soy el dueño de esta tienda de bicis.$"

MauvilleCity_BikeShop_Text_DidYouComeFromFarAway:
	.string "RYDEL: Tus DEPORTIVAS…\n"
	.string "Están hechas un asco.\p"
	.string "¿Vienes de muy lejos?$"

MauvilleCity_BikeShop_Text_GuessYouDontNeedBike:
	.string "RYDEL: ¿Ah, sí?\p"
	.string "Entonces supongo que no necesitas\n"
	.string "ninguna de mis BICIS.$"

MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne:
	.string "RYDEL: Mmm, mmm… … … … …\p"
	.string "¿Dices que has venido hasta aquí\n"
	.string "desde VILLA RAÍZ?\p"
	.string "¡Madre mía!\n"
	.string "¡Eso está lejísimos!\p"
	.string "Con una de mis BICIS podrías ir a\n"
	.string "cualquier parte fácilmente, sintiendo\l"
	.string "la suave caricia del viento.\p"
	.string "¡Ya sé!\n"
	.string "¡Te voy a regalar una BICI!\p"
	.string "¡Ah, espera un momento!\p"
	.string "¡Se me olvidaba decirte que hay\n"
	.string "dos tipos de BICIS!\p"
	.string "¡La BICI DE CARRERAS y la\n"
	.string "BICI ACROBÁTICA!\p"
	.string "¡La BICI DE CARRERAS es para quien\n"
	.string "quiere sentir el viento en la cara!\p"
	.string "¡Y la BICI ACROBÁTICA es para quien\n"
	.string "prefiere la técnica!\p"
	.string "¡Como soy un cielo, puedes quedarte\n"
	.string "la que más te guste!\p"
	.string "¿Cuál eliges?$"

MauvilleCity_BikeShop_Text_ChoseMachBike:
	.string "{PLAYER} ha elegido la BICI DE CARRERAS.$"

MauvilleCity_BikeShop_Text_ChoseAcroBike:
	.string "{PLAYER} ha elegido la BICI ACROBÁTICA.$"

MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes:
	.string "RYDEL: Si te entran ganas de cambiar\n"
	.string "de BICI, ¡ven a verme!$"

MauvilleCity_BikeShop_Text_WantToSwitchBikes:
	.string "RYDEL: ¿Oh? ¿Estabas pensando en\n"
	.string "cambiar de BICI?$"

MauvilleCity_BikeShop_Text_IllSwitchBikes:
	.string "RYDEL: ¡Vale, sin problema!\n"
	.string "¡Te la cambio!$"

MauvilleCity_BikeShop_Text_ExchangedMachForAcro:
	.string "{PLAYER} ha cambiado la BICI DE\n"
	.string "CARRERAS por la BICI ACROBÁTICA.$"

MauvilleCity_BikeShop_Text_ExchangedAcroForMach:
	.string "{PLAYER} ha cambiado la BICI\n"
	.string "ACROBÁTICA por la BICI DE CARRERAS.$"

MauvilleCity_BikeShop_Text_HappyYouLikeIt:
	.string "RYDEL: ¡Bien, bien!\n"
	.string "¡Me alegra que te guste!$"

MauvilleCity_BikeShop_Text_OhYourBikeIsInPC:
	.string "¿Oh? ¿Qué ha pasado con la BICI\n"
	.string "que te di?\p"
	.string "Ah, ya lo entiendo, la has guardado\n"
	.string "en el PC.\p"
	.string "Bueno, sácala del PC y te la\n"
	.string "cambiaré encantado.\p"
	.string "¡Que el viento sople siempre a tu\n"
	.string "favor en tu aventura!$"

MauvilleCity_BikeShop_Text_HandbooksAreInBack:
	.string "Trabajo aquí mientras aprendo\n"
	.string "sobre BICIS.\p"
	.string "Si necesitas consejos para montar en\n"
	.string "BICI, hay un par de manuales\l"
	.string "al fondo.$"

MauvilleCity_BikeShop_Text_MachHandbookWhichPage:
	.string "Es un manual de la BICI DE CARRERAS.\p"
	.string "¿Qué página quieres leer?$"

MauvilleCity_BikeShop_Text_HowToRideMachBike:
	.string "La BICI va en la dirección en la que\n"
	.string "pulses la + Cruceta de Control.\p"
	.string "Acelera cuando coge carrerilla.\p"
	.string "Para parar, suelta la + Cruceta.\n"
	.string "La BICI irá frenando hasta pararse.\p"
	.string "¿Quieres leer otra página?$"

MauvilleCity_BikeShop_Text_HowToTurnMachBike:
	.string "La BICI DE CARRERAS es rápida, pero\n"
	.string "no frena muy deprisa.\p"
	.string "Tomar las curvas es un poco\n"
	.string "complicado.\p"
	.string "Suelta la + Cruceta un poco antes de\n"
	.string "la curva y reduce la velocidad.\p"
	.string "¿Quieres leer otra página?$"

MauvilleCity_BikeShop_Text_SandySlopes:
	.string "En la región de HOENN hay pequeñas\n"
	.string "cuestas de arena.\p"
	.string "La arena suelta hace imposible\n"
	.string "subirlas de forma normal.\p"
	.string "Pero con una BICI DE CARRERAS puedes\n"
	.string "subir una cuesta de arena a toda prisa.\p"
	.string "¿Quieres leer otra página?$"

MauvilleCity_BikeShop_Text_AcroHandbookWhichPage:
	.string "Es un manual de la BICI ACROBÁTICA.\p"
	.string "¿Qué página quieres leer?$"

MauvilleCity_BikeShop_Text_Wheelies:
	.string "Pulsa el Botón B mientras vas en\n"
	.string "BICI y se levantará la rueda delantera.\p"
	.string "Puedes moverte así con la\n"
	.string "+ Cruceta de Control.\p"
	.string "Esta técnica se llama caballito.\p"
	.string "¿Quieres leer otra página?$"

MauvilleCity_BikeShop_Text_BunnyHops:
	.string "Si mantienes pulsado el Botón B,\n"
	.string "la BICI saltará sin moverse.\p"
	.string "Esta técnica se llama salto de\n"
	.string "conejo.\p"
	.string "También puedes avanzar saltando.\p"
	.string "¿Quieres leer otra página?$"

MauvilleCity_BikeShop_Text_Jumps:
	.string "Pulsa a la vez el Botón B y la\n"
	.string "+ Cruceta de Control para saltar.\p"
	.string "Pulsa la + Cruceta hacia un lado\n"
	.string "para saltar de lado.\p"
	.string "Púlsala hacia atrás para que la BICI\n"
	.string "cambie de dirección al saltar.\p"
	.string "¿Quieres leer otra página?$"

