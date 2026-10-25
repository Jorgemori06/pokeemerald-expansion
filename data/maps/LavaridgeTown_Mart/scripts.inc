LavaridgeTown_Mart_MapScripts::
	.byte 0

LavaridgeTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LavaridgeTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LavaridgeTown_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_RARE_CANDY
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_FIRE_STONE
	.2byte ITEM_MAGMARIZER
	pokemartlistend

LavaridgeTown_Mart_EventScript_ExpertM::
	msgbox LavaridgeTown_Mart_Text_XSpeedFirstStrike, MSGBOX_NPC
	end

LavaridgeTown_Mart_EventScript_OldWoman::
	msgbox LavaridgeTown_Mart_Text_LocalSpecialtyOnMtChimney, MSGBOX_NPC
	end

LavaridgeTown_Mart_Text_XSpeedFirstStrike:
	.string "Usa VELOCIDAD X para subir la\n"
	.string "VELOCIDAD de un POKéMON en combate.\p"
	.string "Así atacará primero, ¡y eso es una\n"
	.string "gran ventaja!$"

LavaridgeTown_Mart_Text_LocalSpecialtyOnMtChimney:
	.string "En la cima del MONTE CENIZO hay una\n"
	.string "especialidad que solo se vende allí.\p"
	.string "Dásela a un POKéMON y se pondrá\n"
	.string "contentísimo.$"

