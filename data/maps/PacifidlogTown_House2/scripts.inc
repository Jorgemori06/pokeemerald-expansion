PacifidlogTown_House2_MapScripts::
	.byte 0

PacifidlogTown_House2_EventScript_FanClubYoungerBrother::
	lock
	faceplayer
	dotimebasedevents
	call PacifidlogTown_House2_EventScript_UpdateFanClubTMFlag
	goto_if_set FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK, PacifidlogTown_House2_EventScript_ComeBackInXDays
	call_if_set FLAG_MET_FANCLUB_YOUNGER_BROTHER, PacifidlogTown_House2_EventScript_MonAssessment
	call_if_unset FLAG_MET_FANCLUB_YOUNGER_BROTHER, PacifidlogTown_House2_EventScript_FirstMonAssessment
	setflag FLAG_MET_FANCLUB_YOUNGER_BROTHER
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_ge VAR_RESULT, FRIENDSHIP_150_TO_199, PacifidlogTown_House2_EventScript_GiveReturn
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_ge VAR_RESULT, FRIENDSHIP_50_TO_99, PacifidlogTown_House2_EventScript_PutInEffort
	goto PacifidlogTown_House2_EventScript_GiveFrustration
	end

PacifidlogTown_House2_EventScript_UpdateFanClubTMFlag::
	goto_if_unset FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK, Common_EventScript_NopReturn
	specialvar VAR_RESULT, GetDaysUntilPacifidlogTMAvailable
	call_if_eq VAR_RESULT, 0, PacifidlogTown_House2_EventScript_ClearReceivedFanClubTM
	return

PacifidlogTown_House2_EventScript_MonAssessment::
	msgbox PacifidlogTown_House2_Text_AhYourPokemon, MSGBOX_DEFAULT
	return

PacifidlogTown_House2_EventScript_FirstMonAssessment::
	msgbox PacifidlogTown_House2_Text_ChairmansYoungerBrotherOnVacation, MSGBOX_DEFAULT
	msgbox PacifidlogTown_House2_Text_AhYourPokemon, MSGBOX_DEFAULT
	return

PacifidlogTown_House2_EventScript_ClearReceivedFanClubTM::
	clearflag FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK
	return

PacifidlogTown_House2_EventScript_GiveReturn::
	msgbox PacifidlogTown_House2_Text_AdoringPokemonTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_RETURN
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK
	special SetPacifidlogTMReceivedDay
	msgbox PacifidlogTown_House2_Text_ExplainReturnFrustration, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_PutInEffort::
	msgbox PacifidlogTown_House2_Text_PutInSomeMoreEffort, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_GiveFrustration::
	msgbox PacifidlogTown_House2_Text_ViciousPokemonTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_FRUSTRATION
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK
	special SetPacifidlogTMReceivedDay
	msgbox PacifidlogTown_House2_Text_ExplainReturnFrustration, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_ComeBackInXDays::
	specialvar VAR_RESULT, GetDaysUntilPacifidlogTMAvailable
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox PacifidlogTown_House2_Text_GetGoodTMInXDays, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_HappyAzurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_NORMAL
	msgbox PacifidlogTown_House2_Text_Rurii, MSGBOX_DEFAULT
	waitmoncry
	msgbox PacifidlogTown_House2_Text_VeryFriendlyWithTrainer, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_UnhappyAzurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_ENCOUNTER
	msgbox PacifidlogTown_House2_Text_Rururi, MSGBOX_DEFAULT
	waitmoncry
	msgbox PacifidlogTown_House2_Text_DoesntLikeTrainerVeryMuch, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_Text_ChairmansYoungerBrotherOnVacation:
	.string "¡Ejem!\p"
	.string "Soy el hermano pequeño del PRESIDENTE,\n"
	.string "la persona más importante del CLUB DE\l"
	.string "FANS DE LOS POKéMON.\p"
	.string "Estoy aquí de vacaciones con mis\n"
	.string "POKéMON, sí, sí.$"

PacifidlogTown_House2_Text_AhYourPokemon:
	.string "¡Ah!\n"
	.string "Tu POKéMON…$"

PacifidlogTown_House2_Text_AdoringPokemonTakeThis:
	.string "Se nota que te quiere muchísimo.\p"
	.string "Un POKéMON tan cariñoso y adorable se\n"
	.string "merece una MT como esta, ¿no?$"

PacifidlogTown_House2_Text_PutInSomeMoreEffort:
	.string "Mmm…\n"
	.string "No está mal, pero tampoco bien.\p"
	.string "Tú, que lo entrenas, tienes que\n"
	.string "esforzarte un poco más.$"

PacifidlogTown_House2_Text_ViciousPokemonTakeThis:
	.string "Tiene una mirada feroz.\p"
	.string "Un POKéMON que da tanto miedo se\n"
	.string "merece una MT como esta.$"

PacifidlogTown_House2_Text_ExplainReturnFrustration:
	.string "Si un POKéMON te quiere mucho, la\n"
	.string "potencia de RETRIBUCIÓN aumenta.\p"
	.string "Si no te quiere, aumenta la de\n"
	.string "FRUSTRACIÓN.$"

PacifidlogTown_House2_Text_GetGoodTMInXDays:
	.string "Ah, sí. Dentro de unos {STR_VAR_1} días\n"
	.string "tendré alguna MT buena.\p"
	.string "Ven a verme entonces.\n"
	.string "Te daré una MT que le vaya a tu\l"
	.string "POKéMON.$"

PacifidlogTown_House2_Text_Rurii:
	.string "AZURILL: Rurii.$"

PacifidlogTown_House2_Text_VeryFriendlyWithTrainer:
	.string "Parece que se lleva muy bien con su\n"
	.string "ENTRENADOR.$"

PacifidlogTown_House2_Text_Rururi:
	.string "AZURILL: ¡Rururi!$"

PacifidlogTown_House2_Text_DoesntLikeTrainerVeryMuch:
	.string "No parece que le caiga muy bien su\n"
	.string "ENTRENADOR.$"

