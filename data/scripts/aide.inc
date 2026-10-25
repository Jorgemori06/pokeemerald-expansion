Aide_EventScript_HaventCaughtEnough::
	msgbox Aide_Text_HaventCaughtEnoughMonsForItem
	release
	end

Aide_EventScript_NoRoomForItem::
	msgbox Aide_Text_DontHaveAnyRoomForItem
	release
	end

Aide_EventScript_DeclineCheckMons::
	msgbox Aide_Text_GetEnoughMonsComeBackForItem
	release
	end

Aide_Text_HaventCaughtEnoughMonsForItem::
	.string "A ver…\n"
	.string "¡Vaya! Solo has atrapado\l"
	.string "{STR_VAR_3} tipos de POKéMON.\p"
	.string "Necesitas {STR_VAR_1} tipos\n"
	.string "si quieres {STR_VAR_2}.$"

Aide_Text_GetEnoughMonsComeBackForItem::
	.string "… Oh. Ya veo.\p"
	.string "Cuando tengas {STR_VAR_1} tipos de\n"
	.string "POKéMON, vuelve a por {STR_VAR_2}.$"

Aide_Text_DontHaveAnyRoomForItem::
	.string "¡Oh! Veo que no tienes sitio\n"
	.string "para {STR_VAR_2}.$"
