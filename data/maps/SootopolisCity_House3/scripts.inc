SootopolisCity_House3_MapScripts::
	.byte 0

SootopolisCity_House3_EventScript_Woman::
	lock
	faceplayer
	msgbox SootopolisCity_House3_Text_JuanHasManyFansDoYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SootopolisCity_House3_EventScript_HaveFans
	msgbox SootopolisCity_House3_Text_LonesomeTryWorkingHarder, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_HaveFans::
	msgbox SootopolisCity_House3_Text_YouMustBePrettyStrong, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_Girl::
	msgbox SootopolisCity_House3_Text_TrainerFanClubWasWild, MSGBOX_NPC
	end

SootopolisCity_House3_Text_JuanHasManyFansDoYou:
	.string "Entrenas POKéMON, ¿verdad?\p"
	.string "GALANO, de ARRECÍPOLIS, tiene muchos\n"
	.string "fans. ¡Más que su alumno PLUBIO!\p"
	.string "¿Tú tienes fans?$"

SootopolisCity_House3_Text_YouMustBePrettyStrong:
	.string "Oh, entonces debes de ser bastante\n"
	.string "fuerte.$"

SootopolisCity_House3_Text_LonesomeTryWorkingHarder:
	.string "Ay, vaya…\n"
	.string "Qué solitario.\p"
	.string "Esfuérzate un poco más para tener\n"
	.string "fans.$"

SootopolisCity_House3_Text_TrainerFanClubWasWild:
	.string "Vienen fans entregados incluso de\n"
	.string "fuera de HOENN.\p"
	.string "Fue una locura cuando fui al CLUB DE\n"
	.string "FANS DE ENTRENADORES de CALAGUA.$"

