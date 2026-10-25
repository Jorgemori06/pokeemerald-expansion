FortreeCity_House5_MapScripts::
	.byte 0

FortreeCity_House5_EventScript_PokefanF::
	msgbox FortreeCity_House5_Text_TreeHousesAreGreat, MSGBOX_NPC
	end

FortreeCity_House5_EventScript_Man::
	msgbox FortreeCity_House5_Text_AdaptedToNature, MSGBOX_NPC
	end

FortreeCity_House5_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox FortreeCity_House5_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House5_Text_TreeHousesAreGreat:
	.string "¡Las casas en los árboles de\n"
	.string "ARBORADA son geniales!\p"
	.string "Creo que es el mejor sitio para vivir\n"
	.string "junto a los POKéMON.$"

FortreeCity_House5_Text_AdaptedToNature:
	.string "Los POKéMON y las personas se han\n"
	.string "adaptado a la naturaleza para vivir.\p"
	.string "No hace falta cambiar la naturaleza\n"
	.string "a nuestro gusto.$"

FortreeCity_House5_Text_Zigzagoon:
	.string "ZIGZAGOON: ¡Bufuu!$"

