MtPyre_1F_MapScripts::
	.byte 0

MtPyre_1F_EventScript_CleanseTagWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CLEANSE_TAG, MtPyre_1F_EventScript_ReceivedCleanseTag
	msgbox MtPyre_1F_Text_TakeThisForYourOwnGood, MSGBOX_DEFAULT
	giveitem ITEM_CLEANSE_TAG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CLEANSE_TAG
	release
	end

MtPyre_1F_EventScript_ReceivedCleanseTag::
	msgbox MtPyre_1F_Text_ExplainCleanseTag, MSGBOX_DEFAULT
	release
	end

MtPyre_1F_EventScript_PokefanF::
	msgbox MtPyre_1F_Text_ComeToPayRespects, MSGBOX_NPC
	end

MtPyre_1F_EventScript_Man::
	msgbox MtPyre_1F_Text_RestingPlaceOfZigzagoon, MSGBOX_NPC
	end

MtPyre_1F_Text_TakeThisForYourOwnGood:
	.string "Por las laderas del MONTE PÍRICO\n"
	.string "vagan seres de todo tipo…\p"
	.string "Nunca se sabe qué puede pasar.\n"
	.string "Toma esto. Es por tu bien.$"

MtPyre_1F_Text_ExplainCleanseTag:
	.string "Haz que un POKéMON lleve ese\n"
	.string "AMULETO.\p"
	.string "Ayuda a alejar a los POKéMON\n"
	.string "salvajes.$"

MtPyre_1F_Text_ComeToPayRespects:
	.string "¿Has venido a rendir homenaje a los\n"
	.string "espíritus de los POKéMON fallecidos?\p"
	.string "Se nota que quieres mucho a tus\n"
	.string "POKéMON.$"

MtPyre_1F_Text_RestingPlaceOfZigzagoon:
	.string "Aquí descansa mi ZIGZAGOON.\n"
	.string "Lo quería tanto…$"

