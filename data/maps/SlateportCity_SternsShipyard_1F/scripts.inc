SlateportCity_SternsShipyard_1F_MapScripts::
	.byte 0

SlateportCity_SternsShipyard_1F_EventScript_Dock::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_SternsShipyard_1F_EventScript_FerryReady
	goto_if_set FLAG_BADGE07_GET, SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined
	goto_if_set FLAG_DELIVERED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran
	goto_if_set FLAG_DOCK_REJECTED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_GoFindStern
	msgbox SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails, MSGBOX_DEFAULT
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_DOCK_REJECTED_DEVON_GOODS
	setflag FLAG_HIDE_SLATEPORT_CITY_TEAM_AQUA
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_FerryReady::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_FerryIsReady, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_GoFindStern::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist1::
	msgbox SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist2::
	msgbox SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Briney::
	msgbox SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails:
	.string "Mmm… Si esto va aquí y eso va\n"
	.string "allí…\p"
	.string "¿Dónde va esto otro?\n"
	.string "¿Y ese chisme?\p"
	.string "¡Aaarg! ¡No me aclaro con esto!$"

SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern:
	.string "¿Mm?\n"
	.string "Hola, soy DOCK.\p"
	.string "El CAPITÁN BABOR me encargó diseñar\n"
	.string "un ferry.\p"
	.string "¡Oh! Eso de ahí…\n"
	.string "¿Son las PIEZAS DEVON?\p"
	.string "Pero, mmm…\n"
	.string "Así no puede ser…\p"
	.string "El CAPITÁN BABOR se ha ido a algún\n"
	.string "sitio. Dijo que tenía trabajo.\p"
	.string "¿Podrías ir a buscar al CAPITÁN\n"
	.string "BABOR y entregárselas?$"

SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern:
	.string "DOCK: ¿Dónde se habrá metido el\n"
	.string "CAPITÁN BABOR?\p"
	.string "¿Podrías buscarlo y entregarle\n"
	.string "ese paquete?$"

SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran:
	.string "DOCK: Construir barcos es un arte.\p"
	.string "Hay muchas cosas que no se resuelven\n"
	.string "solo con cálculos.\p"
	.string "Me vendrían muy bien los consejos de\n"
	.string "un veterano que conozca el mar…$"

SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs:
	.string "DOCK: ¡Hola! El SR. ARENQUE se ha unido\n"
	.string "a nosotros para echarnos una mano.\p"
	.string "Gracias al viejo marinero, el ferry\n"
	.string "va cogiendo forma.$"

SlateportCity_SternsShipyard_1F_Text_FerryIsReady:
	.string "DOCK: ¡Por fin está listo el ferry!\p"
	.string "¡El nuevo M.S. MAREA es una maravilla\n"
	.string "de la tecnología!\p"
	.string "Pero me da la sensación de que\n"
	.string "podemos hacer algo aún mejor.\p"
	.string "Ya sabes, la tecnología nunca\n"
	.string "deja de avanzar.$"

SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock:
	.string "SR. ARENQUE: ¡Ah, {PLAYER}{KUN}!\n"
	.string "¡Cuánto tiempo!\p"
	.string "Desde que te conocí, este viejo lobo\n"
	.string "de mar está lleno de energía.\p"
	.string "Así que he decidido ayudar a DOCK\n"
	.string "a construir un ferry.\p"
	.string "Al fin y al cabo, un ferry podría\n"
	.string "llevar a muchísima gente.\p"
	.string "Pero, ¿sabes?, ese DOCK es alguien\n"
	.string "muy especial.\p"
	.string "Con su talento para la tecnología\n"
	.string "y mi experiencia, seguro que hacemos\l"
	.string "un barco estupendo.$"

SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing:
	.string "Las estaciones, el tiempo, dónde\n"
	.string "está la luna en el cielo…\p"
	.string "Estas y otras cosas hacen que el mar\n"
	.string "cambie de cara.\p"
	.string "¡Así es!\n"
	.string "¡El mar es como un ser vivo!$"

SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily:
	.string "Me mareo enseguida en el mar.\n"
	.string "Así que ayudo aquí.$"

