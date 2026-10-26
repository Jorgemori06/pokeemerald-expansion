SootopolisCity_House7_MapScripts::
	.byte 0

SootopolisCity_House7_EventScript_OldMan::
	msgbox SootopolisCity_House7_Text_CityFromEruptedVolcano, MSGBOX_NPC
	end

SootopolisCity_House7_EventScript_PokefanF::
	msgbox SootopolisCity_House7_Text_CaveMadeToKeepSomething, MSGBOX_NPC
	end

SootopolisCity_House7_Text_CityFromEruptedVolcano:
	.string "Un volcán submarino entró en erupción\n"
	.string "y se abrió paso desde el fondo.\p"
	.string "Su cráter salió del mar y se llenó\n"
	.string "de agua de lluvia.\p"
	.string "Así nació CIUDAD ARRECÍPOLIS.$"

SootopolisCity_House7_Text_CaveMadeToKeepSomething:
	.string "La cueva que une ARRECÍPOLIS con el\n"
	.string "mundo exterior…\p"
	.string "Parece hecha para que algo no\n"
	.string "pudiera salir.\p"
	.string "¿O son imaginaciones mías?$"

