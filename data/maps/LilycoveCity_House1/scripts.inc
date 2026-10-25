LilycoveCity_House1_MapScripts::
	.byte 0

LilycoveCity_House1_EventScript_ExpertM::
	msgbox LilycoveCity_House1_Text_PokemonPartnersNotTools, MSGBOX_NPC
	end

LilycoveCity_House1_EventScript_Kecleon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KECLEON, CRY_MODE_NORMAL
	msgbox LilycoveCity_House1_Text_Kecleon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LilycoveCity_House1_Text_PokemonPartnersNotTools:
	.string "Los POKéMON son compañeros de las\n"
	.string "personas. No son herramientas.\p"
	.string "Por desgracia, hay gente que no\n"
	.string "lo entiende…$"

LilycoveCity_House1_Text_Kecleon:
	.string "KECLEON: ¿Ruroro?$"

