Route114_FossilManiacsHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_FossilManiacsHouse_OnTransition
	.byte 0

Route114_FossilManiacsHouse_OnTransition:
	setflag FLAG_LANDMARK_FOSSIL_MANIACS_HOUSE
	end

Route114_FossilManiacsHouse_EventScript_FossilManiacsBrother::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_DIG, Route114_FossilManiacsHouse_EventScript_ReceivedDig
	msgbox Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother, MSGBOX_DEFAULT
	giveitem ITEM_TM_DIG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_DIG
	release
	end

Route114_FossilManiacsHouse_EventScript_ReceivedDig::
	msgbox Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsHouse_EventScript_RockDisplay::
	msgbox Route114_FossilManiacsHouse_Text_RocksFillDisplayCase, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_EventScript_Bookshelf::
	msgbox Route114_FossilManiacsHouse_Text_CrammedWithBooks, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother:
	.string "Mi hermano mayor es el MANÍACO DE\n"
	.string "LOS FÓSILES… Es majo y le encantan…\p"
	.string "También le encanta cavar agujeros…\n"
	.string "Este lo ha cavado él solo…\p"
	.string "Toma esto, así podrás EXCAVAR\n"
	.string "agujeros como mi hermano…$"

Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance:
	.string "Si un POKéMON usa EXCAVAR dentro de\n"
	.string "una cueva, vuelves a la entrada…$"

Route114_FossilManiacsHouse_Text_RocksFillDisplayCase:
	.string "La vitrina está llena de rocas con\n"
	.string "formas curiosas…$"

Route114_FossilManiacsHouse_Text_CrammedWithBooks:
	.string "LA COMPOSICIÓN DE LOS ESTRATOS…\n"
	.string "CÓMO LA LLUVIA DA FORMA AL TERRENO…\l"
	.string "PIEDRAS, TIERRA Y ROCA…\p"
	.string "Está abarrotada de libros.$"

