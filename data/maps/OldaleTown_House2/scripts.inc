OldaleTown_House2_MapScripts::
	.byte 0

OldaleTown_House2_EventScript_Woman::
	msgbox OldaleTown_House2_Text_PokemonLevelUp, MSGBOX_NPC
	end

OldaleTown_House2_EventScript_Man::
	msgbox OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon, MSGBOX_NPC
	end

OldaleTown_House2_Text_PokemonLevelUp:
	.string "Al combatir, los POKéMON acaban\n"
	.string "subiendo de nivel y haciéndose fuertes.$"

OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon:
	.string "Si tus POKéMON se hacen más fuertes,\n"
	.string "podrás ir más lejos.$"

