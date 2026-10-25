SlateportCity_Mart_MapScripts::
	.byte 0

SlateportCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart SlateportCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_RARE_CANDY
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_WATER_STONE
	.2byte ITEM_PRISM_SCALE
	.2byte ITEM_DEEP_SEA_TOOTH
	.2byte ITEM_DEEP_SEA_SCALE
	pokemartlistend

SlateportCity_Mart_EventScript_BlackBelt::
	msgbox SlateportCity_Mart_Text_SomeItemsOnlyAtMart, MSGBOX_NPC
	end

SlateportCity_Mart_EventScript_Man::
	msgbox SlateportCity_Mart_Text_GreatBallIsBetter, MSGBOX_NPC
	end

SlateportCity_Mart_Text_SomeItemsOnlyAtMart:
	.string "El MERCADO tiene cosas muy\n"
	.string "interesantes.\p"
	.string "Pero hay objetos que solo se\n"
	.string "consiguen en una TIENDA POKéMON.$"

SlateportCity_Mart_Text_GreatBallIsBetter:
	.string "Una SUPER BALL atrapa mejor que una\n"
	.string "POKé BALL.\p"
	.string "Con esto, debería poder atrapar a ese\n"
	.string "POKéMON tan escurridizo…$"

