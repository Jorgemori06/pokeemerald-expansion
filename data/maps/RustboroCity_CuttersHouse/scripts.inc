RustboroCity_CuttersHouse_MapScripts::
	.byte 0

RustboroCity_CuttersHouse_EventScript_Cutter::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_CUT, RustboroCity_CuttersHouse_EventScript_ExplainCut
	msgbox RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse, MSGBOX_DEFAULT
	giveitem ITEM_HM_CUT
	setflag FLAG_RECEIVED_HM_CUT
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_ExplainCut::
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_Lass::
	msgbox RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees, MSGBOX_NPC
	end

RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse:
	.string "Esa expresión decidida…\n"
	.string "Esa forma ágil de moverte…\l"
	.string "Y tus POKéMON bien entrenados…\p"
	.string "¡Está claro que tienes talento!\p"
	.string "No, espera, no digas nada.\n"
	.string "Se nota con solo mirarte.\p"
	.string "Seguro que sabrás sacarle partido\n"
	.string "a esta MÁQUINA OCULTA.\p"
	.string "Nada de modestia ni timidez.\n"
	.string "¡Venga, tómala!$"

RustboroCity_CuttersHouse_Text_ExplainCut:
	.string "Esa MÁQUINA OCULTA, o MO,\n"
	.string "contiene CORTE.\p"
	.string "Un movimiento de MO lo pueden usar\n"
	.string "los POKéMON fuera de los combates.\p"
	.string "Un POKéMON que sepa CORTE puede talar\n"
	.string "árboles finos si su ENTRENADOR\l"
	.string "tiene la MEDALLA PIEDRA.\p"
	.string "Y, al contrario que una MT, una MO\n"
	.string "se puede usar más de una vez.$"

RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees:
	.string "Cuando ampliaron CIUDAD FÉRRICA,\n"
	.string "mi padre echó una mano.\p"
	.string "Hizo que sus POKéMON usaran CORTE\n"
	.string "para despejar el terreno de árboles.$"

