ProfileMan_EventScript_Man::
	lock
	faceplayer
	goto_if_set FLAG_SYS_CHAT_USED, ProfileMan_EventScript_GivenProfileBefore
	msgbox ProfileMan_Text_CollectTrainerProfiles, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeProfile
	end

ProfileMan_EventScript_AskToSeeProfile::
	msgbox ProfileMan_Text_MayISeeYourProfile, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_YESNOINFO_2, FALSE
	switch VAR_RESULT
	case 0, ProfileMan_EventScript_CreateProfile
	case 1, ProfileMan_EventScript_DeclineShowProfile
	case 2, ProfileMan_EventScript_Info
	case MULTI_B_PRESSED, ProfileMan_EventScript_DeclineShowProfile
	end

ProfileMan_EventScript_Info::
	msgbox ProfileMan_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeProfile
	end

ProfileMan_EventScript_CreateProfile::
	msgbox ProfileMan_Text_LetsSeeItThen, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, ProfileMan_EventScript_CancelShowProfile
	goto_if_eq VAR_RESULT, 1, ProfileMan_EventScript_ShowProfile
	end

ProfileMan_EventScript_CancelShowProfile::
	msgbox ProfileMan_Text_NotIntoItRightNow, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_ShowProfile::
	setvar VAR_0x8004, 0
	special ShowEasyChatProfile
	waitmessage
	delay 80
	msgbox ProfileMan_Text_FantasticProfile, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_DeclineShowProfile::
	msgbox ProfileMan_Text_ImagineYouWouldHaveWonderfulProfile, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_GivenProfileBefore::
	msgbox ProfileMan_Text_YouHaveWonderfulSmile, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeNewProfile
	end

ProfileMan_EventScript_AskToSeeNewProfile::
	msgbox ProfileMan_Text_MayISeeYourNewProfile, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_YESNOINFO_2, FALSE
	switch VAR_RESULT
	case 0, ProfileMan_EventScript_CreateNewProfile
	case 1, ProfileMan_EventScript_DeclineNewProfile
	case 2, ProfileMan_EventScript_InfoNewProfile
	case MULTI_B_PRESSED, ProfileMan_EventScript_DeclineNewProfile
	end

ProfileMan_EventScript_InfoNewProfile::
	msgbox ProfileMan_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeNewProfile
	end

ProfileMan_EventScript_CreateNewProfile::
	msgbox ProfileMan_Text_EvenBetterThanLastProfile, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, ProfileMan_EventScript_CancelShowProfile
	goto_if_eq VAR_RESULT, 1, ProfileMan_EventScript_ShowProfile
	end

ProfileMan_EventScript_DeclineNewProfile::
	msgbox ProfileMan_Text_LikeProfileWayItIs, MSGBOX_DEFAULT
	release
	end

@ Unused
ProfileMan_EventScript_Ret::
	return

ProfileMan_Text_CollectTrainerProfiles:
	.string "¡Hola, ENTRENADOR!\n"
	.string "Qué sonrisa más maravillosa tienes.\p"
	.string "Mi afición es coleccionar los perfiles\n"
	.string "de los ENTRENADORES POKéMON.$"

ProfileMan_Text_MayISeeYourProfile:
	.string "¿Qué me dices?\n"
	.string "¿Me enseñas tu perfil?$"

ProfileMan_Text_EasyChatExplanation:
	.string "Tu perfil se hace juntando cuatro\n"
	.string "palabras o frases.\p"
	.string "Mira, te enseño un ejemplo de\n"
	.string "perfil hecho con cuatro piezas.\p"
	.string "Puedes cambiar esas cuatro piezas por\n"
	.string "otras como quieras para hacer\l"
	.string "tu propio perfil.\p"
	.string "Hay un montón de piezas que\n"
	.string "puedes usar.\p"
	.string "Están ordenadas por grupos, como\n"
	.string "POKéMON, estilo de vida o aficiones,\l"
	.string "para que sea más fácil buscarlas.\p"
	.string "Primero, elige un grupo para ver\n"
	.string "la lista de piezas.\p"
	.string "Luego, escoge la que quieras.\p"
	.string "Haz lo mismo con las demás y\n"
	.string "tendrás tu propio perfil.$"

ProfileMan_Text_LetsSeeItThen:
	.string "¡Sí! ¡Gracias!\n"
	.string "A ver, enséñamelo.$"

ProfileMan_Text_ImagineYouWouldHaveWonderfulProfile:
	.string "Vaya, ¿en serio?\p"
	.string "Seguro que alguien como tú tiene\n"
	.string "un perfil maravilloso…$"

ProfileMan_Text_NotIntoItRightNow:
	.string "¿Oh? ¿Ahora no te apetece?\p"
	.string "¡Pues cuando quieras!$"

ProfileMan_Text_YouHaveWonderfulSmile:
	.string "¡Hola, ENTRENADOR!\n"
	.string "Qué sonrisa más maravillosa tienes.$"

ProfileMan_Text_MayISeeYourNewProfile:
	.string "¿Me enseñas tu nuevo perfil?$"

ProfileMan_Text_EvenBetterThanLastProfile:
	.string "¡Sí! ¡Gracias!\p"
	.string "Ojalá sea aún mejor que el perfil\n"
	.string "que me enseñaste la otra vez.$"

ProfileMan_Text_LikeProfileWayItIs:
	.string "Ah, te gusta tu perfil tal como está.\p"
	.string "Normal: es un perfil maravilloso\n"
	.string "tal y como está ahora.$"

ProfileMan_Text_FantasticProfile:
	.string "¡F-fantástico!\p"
	.string "¡Tu perfil es maravilloso!\n"
	.string "Dice mucho de ti.\p"
	.string "¡Cualquiera que lo oiga caerá\n"
	.string "rendido a tus pies!\p"
	.string "¡Gracias!$"

@ Unused
ProfileMan_Text_YouKnowSecretSaying:
	.string "¿Oh?\n"
	.string "¡Conoces la frase secreta!\p"
	.string "¡Eso quiere decir que ya eres\n"
	.string "miembro del CLUB EVENTO MISTERIOSO!$"
