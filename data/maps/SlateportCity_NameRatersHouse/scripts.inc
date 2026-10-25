SlateportCity_NameRatersHouse_MapScripts::
	.byte 0

SlateportCity_NameRatersHouse_EventScript_NameRater::
	lock
	faceplayer
	msgbox SlateportCity_NameRatersHouse_Text_PleasedToRateMonNickname, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_NameRatersHouse_EventScript_ChooseMonToRate
	goto_if_eq VAR_RESULT, NO, SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_ChooseMonToRate::
	msgbox SlateportCity_NameRatersHouse_Text_CritiqueWhichMonNickname, MSGBOX_DEFAULT
	chooseboxmon
	waitstate
	goto_if_ne VAR_0x8004, PARTY_NOTHING_CHOSEN, SlateportCity_NameRatersHouse_EventScript_RateMonNickname
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_DeclineNameRate::
	msgbox SlateportCity_NameRatersHouse_Text_DoVisitAgain, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_RateMonNickname::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, SlateportCity_NameRatersHouse_EventScript_CantRateEgg
	special BufferMonNickname
	special IsMonOTIDNotPlayers
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	specialvar VAR_RESULT, MonOTNameNotPlayer
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	msgbox SlateportCity_NameRatersHouse_Text_FineNameSuggestBetterOne, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_NameRatersHouse_EventScript_ChangeNickname
	goto_if_eq VAR_RESULT, NO, SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_CantRateEgg::
	msgbox SlateportCity_NameRatersHouse_Text_ThatIsMerelyAnEgg, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT::
	msgbox SlateportCity_NameRatersHouse_Text_MagnificentName, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_ChangeNickname::
	msgbox SlateportCity_NameRatersHouse_Text_WhatShallNewNameBe, MSGBOX_DEFAULT
	call Common_EventScript_NameReceivedPartyMon
	specialvar VAR_RESULT, TryPutNameRaterShowOnTheAir
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_NewNameDifferent
	msgbox SlateportCity_NameRatersHouse_Text_NameNoDifferentYetSuperior, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_NewNameDifferent::
	msgbox SlateportCity_NameRatersHouse_Text_MonShallBeKnownAsName, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_Text_PleasedToRateMonNickname:
	.string "¡Hola, hola! ¡Soy el EVALUADOR DE\n"
	.string "NOMBRES! ¡El adivino de los nombres!\p"
	.string "Estaré encantado de evaluar el mote\n"
	.string "de tu POKéMON.$"

SlateportCity_NameRatersHouse_Text_CritiqueWhichMonNickname:
	.string "¿El mote de qué POKéMON quieres\n"
	.string "que evalúe?$"

SlateportCity_NameRatersHouse_Text_FineNameSuggestBetterOne:
	.string "Mmm… {STR_VAR_1}, ¿eh? Es un nombre\n"
	.string "bastante bueno el que le has puesto.\p"
	.string "¡Pero! ¿Qué te parecería si te\n"
	.string "propusiera uno un poco mejor?$"

SlateportCity_NameRatersHouse_Text_WhatShallNewNameBe:
	.string "Ah, bien. Entonces, ¿cuál será el\n"
	.string "nuevo mote?$"

SlateportCity_NameRatersHouse_Text_MonShallBeKnownAsName:
	.string "¡Hecho! ¡A partir de ahora, este\n"
	.string "POKéMON se llamará {STR_VAR_1}!\p"
	.string "¡Es mejor nombre que el de antes!\n"
	.string "¡Qué suerte tienes!$"

SlateportCity_NameRatersHouse_Text_DoVisitAgain:
	.string "Ya veo.\n"
	.string "Vuelve cuando quieras.$"

SlateportCity_NameRatersHouse_Text_NameNoDifferentYetSuperior:
	.string "¡Hecho! ¡A partir de ahora, este\n"
	.string "POKéMON se llamará {STR_VAR_1}!\p"
	.string "No parece distinto al de antes,\n"
	.string "¡pero es muchísimo mejor!\p"
	.string "¡Qué suerte tienes!$"

SlateportCity_NameRatersHouse_Text_MagnificentName:
	.string "Mmm… ¡{STR_VAR_1}!\p"
	.string "¡Es un mote magnífico!\n"
	.string "¡No tiene ni un pero!\p"
	.string "Cuida bien a tu {STR_VAR_1}\n"
	.string "ahora y siempre.$"

SlateportCity_NameRatersHouse_Text_ThatIsMerelyAnEgg:
	.string "A ver, a ver.\n"
	.string "¡Eso no es más que un HUEVO!$"

