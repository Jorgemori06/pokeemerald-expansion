GraniteCave_1F_MapScripts::
	.byte 0

GraniteCave_1F_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_1F_EventScript_ReceivedFlash
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	setflag FLAG_RECEIVED_HM_FLASH
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_EventScript_ReceivedFlash::
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_Text_GetsDarkAheadHereYouGo:
	.string "Oye.\n"
	.string "Más adelante está muy oscuro.\l"
	.string "Será difícil explorar.\p"
	.string "Ese chico que ha pasado antes…\n"
	.string "MÁXIMO, creo que se llamaba.\p"
	.string "Sabía usar DESTELLO, así que no le\n"
	.string "pasará nada, pero…\p"
	.string "Bueno, nuestro lema como MONTAÑEROS\n"
	.string "es ayudar a quien nos encontremos.\p"
	.string "Toma, te lo doy.$"

GraniteCave_1F_Text_ExplainFlash:
	.string "Enséñale el movimiento oculto\n"
	.string "DESTELLO a un POKéMON y úsalo.\p"
	.string "Ilumina hasta la oscuridad más\n"
	.string "negra de las cuevas.\p"
	.string "Pero, para usarlo, necesitas la\n"
	.string "MEDALLA del GIMNASIO de AZULIZA.$"

