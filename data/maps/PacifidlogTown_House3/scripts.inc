PacifidlogTown_House3_MapScripts::
	.byte 0

PacifidlogTown_House3_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED, PacifidlogTown_House3_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_HORSEA, PacifidlogTown_House3_Text_WillingToTradeIt, PacifidlogTown_House3_EventScript_DeclineTrade, PacifidlogTown_House3_EventScript_NotRequestedMon, PacifidlogTown_House3_Text_ItsSubtlyDifferentThankYou
	setflag FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED
	release
	end

PacifidlogTown_House3_EventScript_DeclineTrade::
	msgbox PacifidlogTown_House3_Text_NotDesperateOrAnything, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox PacifidlogTown_House3_Text_WontAcceptAnyLessThanRealMon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_TradeCompleted::
	msgbox PacifidlogTown_House3_Text_ReallyWantedToGetBagon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_Girl::
	msgbox PacifidlogTown_House3_Text_IsThatAPokedex, MSGBOX_NPC
	end

PacifidlogTown_House3_Text_WillingToTradeIt:
	.string "¡Mira este {STR_VAR_2}!\p"
	.string "¡Es el {STR_VAR_2} que atrapé ayer para\n"
	.string "celebrar mi cumpleaños!\p"
	.string "¡Oh, ya veo que lo quieres!\n"
	.string "¡Al fin y al cabo, no tiene precio!\p"
	.string "Te diré qué. A lo mejor te lo cambio\n"
	.string "por un {STR_VAR_1}.$"

PacifidlogTown_House3_Text_ItsSubtlyDifferentThankYou:
	.string "¿Oh, así que esto es un {STR_VAR_1}?\p"
	.string "Se parece un poco a un {STR_VAR_2},\n"
	.string "pero tiene algo distinto.\p"
	.string "¡Gracias!$"

PacifidlogTown_House3_Text_WontAcceptAnyLessThanRealMon:
	.string "¡No, no, no! ¡Solo acepto un\n"
	.string "{STR_VAR_1} de verdad!$"

PacifidlogTown_House3_Text_NotDesperateOrAnything:
	.string "¿Oh, así que al final no?\p"
	.string "Vale. Tampoco es que me muera\n"
	.string "por cambiarlo.$"

PacifidlogTown_House3_Text_ReallyWantedToGetBagon:
	.string "Sé que podría buscar uno por mi\n"
	.string "cuenta, pero…\p"
	.string "De verdad quería un BAGON que hubiera\n"
	.string "atrapado otro ENTRENADOR…$"

PacifidlogTown_House3_Text_IsThatAPokedex:
	.string "¿Eso es una POKéDEX?\p"
	.string "¿Has conocido muchos POKéMON\n"
	.string "distintos?\p"
	.string "Ojalá yo fuera como tú.$"

