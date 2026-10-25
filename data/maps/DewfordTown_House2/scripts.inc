DewfordTown_House2_MapScripts::
	.byte 0

DewfordTown_House2_EventScript_Man::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SILK_SCARF, DewfordTown_House2_EventScript_ExplainSilkScarf
	msgbox DewfordTown_House2_Text_WantYouToHaveSilkScarf, MSGBOX_DEFAULT
	giveitem ITEM_SILK_SCARF
	goto_if_eq VAR_RESULT, FALSE, DewfordTown_House2_EventScript_NoRoomForScarf
	setflag FLAG_RECEIVED_SILK_SCARF
	release
	end

DewfordTown_House2_EventScript_NoRoomForScarf::
	msgbox DewfordTown_House2_Text_NoRoom, MSGBOX_DEFAULT
	release
	end

DewfordTown_House2_EventScript_ExplainSilkScarf::
	msgbox DewfordTown_House2_Text_ExplainSilkScarf, MSGBOX_DEFAULT
	release
	end

DewfordTown_House2_EventScript_Boy::
	msgbox DewfordTown_House2_Text_BrawlySoCool, MSGBOX_NPC
	end

DewfordTown_House2_Text_WantYouToHaveSilkScarf:
	.string "¡Recréate la vista con esto!\p"
	.string "¡Es un PAÑUELO SEDA! ¡Lo último en\n"
	.string "moda, ya lo creo!\p"
	.string "¡Oh, te brillan los ojos!\n"
	.string "¡Sabes apreciar mi estilo!\p"
	.string "¡Qué encanto!\n"
	.string "Toma. ¡Quiero que lo tengas tú!$"

DewfordTown_House2_Text_NoRoom:
	.string "Ah, ¿no te cabe?\p"
	.string "Pues escúchame bien: ¡este PAÑUELO es\n"
	.string "imprescindible! ¡Yo vendería todos mis\l"
	.string "objetos para tenerlo!$"

DewfordTown_House2_Text_ExplainSilkScarf:
	.string "El PAÑUELO SEDA sube la potencia de\n"
	.string "los movimientos de tipo NORMAL.\p"
	.string "¡Es un PAÑUELO maravilloso que queda\n"
	.string "bien con casi cualquier POKéMON!$"

DewfordTown_House2_Text_BrawlySoCool:
	.string "¿Has cruzado el mar para venir\n"
	.string "a AZULIZA?\p"
	.string "¿Has venido porque te han hablado\n"
	.string "de MARCIAL?\p"
	.string "Es tan guay…\n"
	.string "Todo el mundo lo adora.$"

