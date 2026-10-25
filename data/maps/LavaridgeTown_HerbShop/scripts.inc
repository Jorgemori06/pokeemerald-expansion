LavaridgeTown_HerbShop_MapScripts::
	.byte 0

LavaridgeTown_HerbShop_EventScript_Clerk::
	lock
	faceplayer
	message LavaridgeTown_HerbShop_Text_WelcomeToHerbShop
	waitmessage
	pokemart LavaridgeTown_HerbShop_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LavaridgeTown_HerbShop_Pokemart:
	.2byte ITEM_WHITE_HERB
	.2byte ITEM_MENTAL_HERB
	.2byte ITEM_POWER_HERB
	pokemartlistend

LavaridgeTown_HerbShop_EventScript_ExpertM::
	msgbox LavaridgeTown_HerbShop_Text_HerbalMedicineWorksButMonWillDislike, MSGBOX_NPC
	end

LavaridgeTown_HerbShop_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CHARCOAL, LavaridgeTown_HerbShop_EventScript_ExplainCharcoal
	msgbox LavaridgeTown_HerbShop_Text_YouveComeToLookAtHerbalMedicine, MSGBOX_DEFAULT
	giveitem ITEM_CHARCOAL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CHARCOAL
	release
	end

LavaridgeTown_HerbShop_EventScript_ExplainCharcoal::
	msgbox LavaridgeTown_HerbShop_Text_ExplainCharcoal, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_HerbShop_Text_WelcomeToHerbShop:
	.string "¡Te damos la bienvenida al HERBOLARIO,\n"
	.string "medicinas eficaces y baratas!$"

LavaridgeTown_HerbShop_Text_YouveComeToLookAtHerbalMedicine:
	.string "¿Has venido a LAVACALDA a ver\n"
	.string "remedios de hierbas?\p"
	.string "Eso dice mucho de ti.\p"
	.string "¡Me caes bien! ¡Toma esto!$"

LavaridgeTown_HerbShop_Text_ExplainCharcoal:
	.string "Ese CARBÓN que te he dado se usa\n"
	.string "para hacer remedios de hierbas.\p"
	.string "Y si se lo das a un POKéMON, hace\n"
	.string "maravillas.\p"
	.string "Aumenta la potencia de los\n"
	.string "movimientos de tipo FUEGO.$"

LavaridgeTown_HerbShop_Text_HerbalMedicineWorksButMonWillDislike:
	.string "Los remedios de hierbas funcionan de\n"
	.string "maravilla. Pero tus POKéMON no te\l"
	.string "lo perdonarán. ¡Saben fatal!$"

