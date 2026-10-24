SlateportCity_House_MapScripts::
	.byte 0

SlateportCity_House_EventScript_PokefanM::
	msgbox SlateportCity_House_Text_NatureToDoWithStatGains, MSGBOX_NPC
	end

SlateportCity_House_EventScript_Girl::
	msgbox SlateportCity_House_Text_MustBeGoingToBattleTent, MSGBOX_NPC
	end

SlateportCity_House_Text_NatureToDoWithStatGains:
	.string "Mi POKéMON tiene naturaleza ACTIVA.\p"
	.string "Tiene más VELOCIDAD que mis otros\n"
	.string "POKéMON.\p"
	.string "A lo mejor la naturaleza tiene que\n"
	.string "ver con cómo suben las caract.$"

SlateportCity_House_Text_MustBeGoingToBattleTent:
	.string "Entrenas POKéMON, ¿verdad?\p"
	.string "Si has venido a CIUDAD PORTUAL, irás\n"
	.string "a la CARPA DE COMBATE.$"

