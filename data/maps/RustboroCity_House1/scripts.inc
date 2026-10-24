RustboroCity_House1_MapScripts::
	.byte 0

RustboroCity_House1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_RUSTBORO_NPC_TRADE_COMPLETED, RustboroCity_House1_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_SEEDOT, RustboroCity_House1_Text_IllTradeIfYouWant, RustboroCity_House1_EventScript_DeclineTrade, RustboroCity_House1_EventScript_NotRequestedMon, RustboroCity_House1_Text_PleaseBeGoodToMyPokemon
	setflag FLAG_RUSTBORO_NPC_TRADE_COMPLETED
	release
	end

RustboroCity_House1_EventScript_DeclineTrade::
	msgbox RustboroCity_House1_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox RustboroCity_House1_Text_DoesntLookLikeMonToMe, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_TradeCompleted::
	msgbox RustboroCity_House1_Text_AnyPokemonCanBeCute, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_Hiker::
	msgbox RustboroCity_House1_Text_AllSortsOfPlaces, MSGBOX_NPC
	end

RustboroCity_House1_Text_IllTradeIfYouWant:
	.string "¿Eh? ¿Que mi POKéMON es mono?\n"
	.string "Claro, ya lo sé.\p"
	.string "Pero si de verdad lo quieres,\n"
	.string "te lo cambio.\p"
	.string "Te cambio mi {STR_VAR_2} por\n"
	.string "un {STR_VAR_1}, si quieres.$"

RustboroCity_House1_Text_PleaseBeGoodToMyPokemon:
	.string "Jejeje…\n"
	.string "Cuida bien de mi POKéMON, por favor.$"

RustboroCity_House1_Text_DoesntLookLikeMonToMe:
	.string "¿Eh? Eso no se parece en nada\n"
	.string "a un {STR_VAR_1}.$"

RustboroCity_House1_Text_YouDontWantToThatsOkay:
	.string "Ah, si no quieres, no pasa nada.\n"
	.string "Pero mi POKéMON es muy mono, ¿eh?…$"

RustboroCity_House1_Text_AnyPokemonCanBeCute:
	.string "Cualquier POKéMON puede ser mono\n"
	.string "si lo crías con cariño.$"

RustboroCity_House1_Text_AllSortsOfPlaces:
	.string "En todos los sitios hay todo tipo\n"
	.string "de POKéMON y de personas.\p"
	.string "Me parece fascinante, así que voy\n"
	.string "a todo tipo de sitios.$"

