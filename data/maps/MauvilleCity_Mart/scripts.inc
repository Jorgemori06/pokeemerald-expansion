MauvilleCity_Mart_MapScripts::
	.byte 0

MauvilleCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MauvilleCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MauvilleCity_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_RARE_CANDY
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_THUNDER_STONE
	.2byte ITEM_ELECTIRIZER
	pokemartlistend

MauvilleCity_Mart_EventScript_ExpertM::
	msgbox MauvilleCity_Mart_Text_ItemsToTemporarilyElevateStats, MSGBOX_NPC
	end

MauvilleCity_Mart_EventScript_Man::
	msgbox MauvilleCity_Mart_Text_DecisionsDetermineBattle, MSGBOX_NPC
	end

MauvilleCity_Mart_Text_ItemsToTemporarilyElevateStats:
	.string "Hay objetos que suben por un rato\n"
	.string "las características de los POKéMON.\p"
	.string "Los que sé que se usan en combate\n"
	.string "son ATAQUE X y DEFENSA X…\p"
	.string "Creo que hay otros parecidos.$"

MauvilleCity_Mart_Text_DecisionsDetermineBattle:
	.string "Usar un movimiento, o usar un objeto\n"
	.string "en su lugar…\p"
	.string "Creo que las decisiones del ENTRENADOR\n"
	.string "deciden cómo acaban los combates.$"

