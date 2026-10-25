FortreeCity_Mart_MapScripts::
	.byte 0

FortreeCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FortreeCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FortreeCity_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_RARE_CANDY
	.2byte ITEM_NEST_BALL
	.2byte ITEM_SUN_STONE
	.2byte ITEM_RAZOR_CLAW
	.2byte ITEM_RAZOR_FANG
	pokemartlistend

FortreeCity_Mart_EventScript_Woman::
	msgbox FortreeCity_Mart_Text_SuperRepelBetter, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Girl::
	msgbox FortreeCity_Mart_Text_StockUpOnItems, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Boy::
	msgbox FortreeCity_Mart_Text_RareCandyMakesMonGrow, MSGBOX_NPC
	end

FortreeCity_Mart_Text_SuperRepelBetter:
	.string "El SUPERREPELENTE dura mucho y\n"
	.string "cumple de sobra.\p"
	.string "Es mucho mejor que un REPELENTE\n"
	.string "normal.$"

FortreeCity_Mart_Text_StockUpOnItems:
	.string "Siempre compro más objetos de los\n"
	.string "que creo que voy a necesitar.\p"
	.string "Nunca se sabe lo que puede pasar.\n"
	.string "¡Más vale prevenir que curar!$"

FortreeCity_Mart_Text_RareCandyMakesMonGrow:
	.string "Un CARAMELO RARO hace que un POKéMON\n"
	.string "suba un nivel al instante.$"

