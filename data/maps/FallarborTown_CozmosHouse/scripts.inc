FallarborTown_CozmosHouse_MapScripts::
	.byte 0

FallarborTown_CozmosHouse_EventScript_ProfCozmo::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_RETURN, FallarborTown_CozmosHouse_EventScript_GaveMeteorite
	checkitem ITEM_METEORITE
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite::
	call_if_unset FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_NoticeMeteorite
	call_if_set FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_AskForMeteorite
	goto_if_eq VAR_RESULT, NO, FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite
	msgbox FallarborTown_CozmosHouse_Text_PleaseUseThisTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_RETURN
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_0x8004, ITEM_METEORITE
	call Common_EventScript_PlayerHandedOverTheItem
	setflag FLAG_RECEIVED_TM_RETURN
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_NoticeMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	msgbox FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_AskForMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MayIHaveMeteorite, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite::
	setflag FLAG_TEMP_2
	msgbox FallarborTown_CozmosHouse_Text_CrushedWithDisappointment, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_GaveMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmosWife::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_RETURN, FallarborTown_CozmosHouse_EventScript_CozmoIsHappy
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_CozmosHouse_EventScript_CozmoIsSad
	msgbox FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsSad::
	msgbox FallarborTown_CozmosHouse_Text_FeelSorryForCozmo, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsHappy::
	msgbox FallarborTown_CozmosHouse_Text_CozmoIsSoHappy, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow:
	.string "PROF. COSMO: Oh…\n"
	.string "Nunca debí dejarme engañar para\l"
	.string "decirle al EQUIPO MAGMA dónde\l"
	.string "encontrar METEORITOS…\p"
	.string "Ese METEORITO de las CATARATAS\n"
	.string "METEORO… Ya nunca será mío…$"

FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt:
	.string "¡Oh!\n"
	.string "¿Eh?\p"
	.string "Ese objeto…\p"
	.string "¿Será posible?\p"
	.string "¿Es el METEORITO que el EQUIPO MAGMA\n"
	.string "se llevó de las CATARATAS METEORO?\p"
	.string "¿Me lo darías, por favor?\p"
	.string "No te lo pido gratis.\n"
	.string "¿Qué tal a cambio de esta MT?$"

FallarborTown_CozmosHouse_Text_PleaseUseThisTM:
	.string "PROF. COSMO: Esta MT es una muestra\n"
	.string "de mi agradecimiento.\l"
	.string "¡Úsala, por favor!$"

FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch:
	.string "PROF. COSMO: Oh, no me lo puedo creer.\n"
	.string "¡Esto es fantástico!\p"
	.string "¡Me va a ayudar muchísimo a\n"
	.string "investigar!$"

FallarborTown_CozmosHouse_Text_CrushedWithDisappointment:
	.string "PROF. COSMO: Oh, pero…\n"
	.string "Me has dejado hundido…$"

FallarborTown_CozmosHouse_Text_MayIHaveMeteorite:
	.string "PROF. COSMO: ¿Me darías ese\n"
	.string "METEORITO, por favor?\p"
	.string "No te lo pido gratis.\n"
	.string "¿Qué tal a cambio de esta MT?$"

FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls:
	.string "El PROF. COSMO se fue a las CATARATAS\n"
	.string "METEORO, en la RUTA 114, con unos\l"
	.string "tipos del EQUIPO MAGMA.$"

FallarborTown_CozmosHouse_Text_FeelSorryForCozmo:
	.string "Pobre PROF. COSMO…\n"
	.string "Está muy deprimido… Me da pena.$"

FallarborTown_CozmosHouse_Text_CozmoIsSoHappy:
	.string "Mira al PROF. COSMO…\n"
	.string "¡Qué contento está! Qué mono.$"

