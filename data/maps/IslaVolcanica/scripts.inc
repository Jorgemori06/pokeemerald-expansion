IslaVolcanica_MapScripts::
	.byte 0

@ La barca a la ISLA VOLCÁNICA (Miguel, 21/11/2026): sale del muelle de PORTUAL desde la 7.ª medalla
IslaVolcanica_EventScript_BarqueroIda::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE07_GET, IslaVolcanica_EventScript_BarqueroTodavia
	msgbox IslaVolcanica_Text_BarqueroIda, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, IslaVolcanica_EventScript_BarqueroNo
	msgbox IslaVolcanica_Text_BarqueroVamos, MSGBOX_DEFAULT
	closemessage
	warp MAP_ISLA_VOLCANICA, 20, 24
	waitstate
	release
	end

IslaVolcanica_EventScript_BarqueroTodavia::
	msgbox IslaVolcanica_Text_BarqueroTodavia, MSGBOX_DEFAULT
	release
	end

IslaVolcanica_EventScript_BarqueroNo::
	msgbox IslaVolcanica_Text_BarqueroNo, MSGBOX_DEFAULT
	release
	end

IslaVolcanica_EventScript_BarqueroVuelta::
	lock
	faceplayer
	msgbox IslaVolcanica_Text_BarqueroVuelta, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, IslaVolcanica_EventScript_BarqueroNo
	msgbox IslaVolcanica_Text_BarqueroVamos, MSGBOX_DEFAULT
	closemessage
	warp MAP_SLATEPORT_CITY, 36, 40
	waitstate
	release
	end

IslaVolcanica_Text_BarqueroIda:
	.string "Llevo la barca a la ISLA VOLCÁNICA,\n"
	.string "al sur de la RUTA 134.\p"
	.string "¿Quieres ir?$"

IslaVolcanica_Text_BarqueroTodavia:
	.string "Llevo la barca a la ISLA VOLCÁNICA,\n"
	.string "pero ahora el mar está muy bravo.\p"
	.string "Vuelve cuando tengas siete\n"
	.string "medallas.$"

IslaVolcanica_Text_BarqueroNo:
	.string "Aquí estaré cuando quieras.$"

IslaVolcanica_Text_BarqueroVamos:
	.string "¡Pues allá vamos!$"

IslaVolcanica_Text_BarqueroVuelta:
	.string "¿Volvemos a CIUDAD PORTUAL?$"
