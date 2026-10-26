SootopolisCity_House4_MapScripts::
	.byte 0

SootopolisCity_House4_EventScript_Man::
	msgbox SootopolisCity_House4_Text_AncientTreasuresWaitingInSea, MSGBOX_NPC
	end

SootopolisCity_House4_EventScript_Woman::
	msgbox SootopolisCity_House4_Text_StrollUnderwaterWithPokemon, MSGBOX_NPC
	end

SootopolisCity_House4_EventScript_Azumarill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZUMARILL, CRY_MODE_NORMAL
	msgbox SootopolisCity_House4_Text_Azumarill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SootopolisCity_House4_Text_AncientTreasuresWaitingInSea:
	.string "Escucha, que te cuento algo bueno.\p"
	.string "Se supone que por el mar de aquí hay\n"
	.string "unas ruinas antiguas.\p"
	.string "Podría haber tesoros esperando a que\n"
	.string "los descubran ahí abajo.$"

SootopolisCity_House4_Text_StrollUnderwaterWithPokemon:
	.string "Tesoros antiguos…\p"
	.string "Estaría bien que existieran, pero\n"
	.string "aunque no, sería precioso dar un\l"
	.string "paseo bajo el agua con mis POKéMON.$"

SootopolisCity_House4_Text_Azumarill:
	.string "AZUMARILL: Maruriii.$"

