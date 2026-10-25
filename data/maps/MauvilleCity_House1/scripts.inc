MauvilleCity_House1_MapScripts::
	.byte 0

MauvilleCity_House1_EventScript_RockSmashDude::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_ROCK_SMASH, MauvilleCity_House1_EventScript_ReceivedRockSmash
	msgbox MauvilleCity_House1_Text_ImRockSmashDudeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_HM_ROCK_SMASH
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
	setflag FLAG_HIDE_ROUTE_111_ROCK_SMASH_TIP_GUY
	msgbox MauvilleCity_House1_Text_ExplainRockSmash, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_EventScript_ReceivedRockSmash::
	msgbox MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_Text_ImRockSmashDudeTakeThis:
	.string "¡Yuju!\p"
	.string "La gente me llama el TÍO DE GOLPE\n"
	.string "ROCA, pero eso me parece poco.\p"
	.string "Creo que merezco más respeto, algo\n"
	.string "como el MAESTRO DE GOLPE ROCA.\p"
	.string "¡Yuju!\p"
	.string "En fin, tus POKéMON parecen\n"
	.string "bastante fuertes.\p"
	.string "¡Eso me gusta!\n"
	.string "¡Toma, esta MÁQUINA OCULTA!$"

MauvilleCity_House1_Text_ExplainRockSmash:
	.string "Esa MO contiene GOLPE ROCA.\p"
	.string "Si te encuentras rocas grandes que\n"
	.string "te cortan el paso…\p"
	.string "¡Usa ese movimiento de MO y quítalas\n"
	.string "de en medio a golpes!\p"
	.string "¡Eso es! ¡Rompe las rocas, digo yo!\n"
	.string "¡Yuju!$"

MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock:
	.string "Ah, sí: si rompes una roca, puede\n"
	.string "salir un POKéMON de su escondite.\p"
	.string "¡Yuju!$"

