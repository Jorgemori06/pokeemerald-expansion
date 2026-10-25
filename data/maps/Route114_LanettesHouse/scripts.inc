Route114_LanettesHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_LanettesHouse_OnTransition
	.byte 0

Route114_LanettesHouse_OnTransition:
	setflag FLAG_LANDMARK_LANETTES_HOUSE
	end

Route114_LanettesHouse_EventScript_Lanette::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_DOLL_LANETTE, Route114_LanettesHouse_EventScript_OfferAdvice
	setflag FLAG_SYS_PC_LANETTE
	msgbox Route114_LanettesHouse_Text_EverythingClutteredKeepThis, MSGBOX_DEFAULT
	givedecoration DECOR_LOTAD_DOLL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowNoRoomForDecor
	setflag FLAG_RECEIVED_DOLL_LANETTE
	release
	end

Route114_LanettesHouse_EventScript_OfferAdvice::
	msgbox Route114_LanettesHouse_Text_OrganizeYourBoxes, MSGBOX_DEFAULT
	release
	end

Route114_LanettesHouse_EventScript_Notebook::
	lockall
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage2
	msgbox Route114_LanettesHouse_Text_ClosedTheNotebook, MSGBOX_DEFAULT
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage2::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage2, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage3
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage3::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage3, MSGBOX_DEFAULT
	return

Route114_LanettesHouse_EventScript_PC::
	msgbox Route114_LanettesHouse_Text_EmailFromBill, MSGBOX_SIGN
	end

Route114_LanettesHouse_Text_EverythingClutteredKeepThis:
	.string "AREDIA: ¡Oh! ¡{PLAYER}{KUN}!\p"
	.string "Perdona que esté todo tan revuelto…\n"
	.string "Cuando me meto en una investigación,\l"
	.string "acaba todo así…\p"
	.string "Qué vergüenza… Guárdame el secreto\n"
	.string "a cambio de esto, por favor.$"

Route114_LanettesHouse_Text_OrganizeYourBoxes:
	.string "¿Te doy un consejo sobre mi Sistema\n"
	.string "de Almacenamiento POKéMON?\p"
	.string "Organiza tus CAJAS para saber qué\n"
	.string "POKéMON hay en cada una.$"

Route114_LanettesHouse_Text_ResearchNotesPage1:
	.string "Son las notas de investigación de\n"
	.string "AREDIA. Hablan de las CAJAS.\p"
	.string "Diseñar CAJAS de 30 POKéMON cada una.\p"
	.string "Cada ENTRENADOR debería poder guardar\n"
	.string "420 POKéMON en el PC.\p"
	.string "¿Seguir leyendo?$"

Route114_LanettesHouse_Text_ResearchNotesPage2:
	.string "Añadir un sistema de marcas para\n"
	.string "ordenar mejor a los POKéMON.\p"
	.string "El nombre y el fondo de cada CAJA\n"
	.string "se podrán cambiar para que estén\l"
	.string "a gusto los POKéMON guardados.\p"
	.string "¿Seguir leyendo?$"

Route114_LanettesHouse_Text_ResearchNotesPage3:
	.string "Al guardar un POKéMON, debe ir a la\n"
	.string "última CAJA que se haya mirado.\p"
	.string "Si esa CAJA está llena, el POKéMON\n"
	.string "se guarda en la siguiente.\p"
	.string "Es decir, al mirar una CAJA, queda\n"
	.string "seleccionada automáticamente como\l"
	.string "la CAJA donde se envían los POKéMON.$"

Route114_LanettesHouse_Text_ClosedTheNotebook:
	.string "{PLAYER} ha cerrado el cuaderno.$"

Route114_LanettesHouse_Text_EmailFromBill:
	.string "Hay un correo de alguien en el PC.\p"
	.string "“… … … … … … …\p"
	.string "”Tu Sistema de Almacenamiento es\n"
	.string "más práctico que el mío.\p"
	.string "”Tiene muchas funciones fáciles de\n"
	.string "usar que lo hacen divertido y útil.\p"
	.string "”Me enorgullece haber participado\n"
	.string "en su desarrollo.\p"
	.string "”Espero que sigas investigando en\n"
	.string "Sistemas de Almacenamiento.\p"
	.string "”De BILL\n"
	.string "… … … … … … … …”$"

