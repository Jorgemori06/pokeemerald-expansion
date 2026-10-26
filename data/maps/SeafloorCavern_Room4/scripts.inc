SeafloorCavern_Room4_MapScripts::
	.byte 0

SeafloorCavern_Room4_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_3, SeafloorCavern_Room4_Text_Grunt3Intro, SeafloorCavern_Room4_Text_Grunt3Defeat
	msgbox SeafloorCavern_Room4_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room4_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_4, SeafloorCavern_Room4_Text_Grunt4Intro, SeafloorCavern_Room4_Text_Grunt4Defeat
	msgbox SeafloorCavern_Room4_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room4_Text_Grunt3Intro:
	.string "¿Quién eres?\n"
	.string "¿Por dónde has entrado?$"

SeafloorCavern_Room4_Text_Grunt3Defeat:
	.string "He perdido…$"

SeafloorCavern_Room4_Text_Grunt3PostBattle:
	.string "¡No encuentro la salida!\p"
	.string "¡No tengo miedo, que conste!$"

SeafloorCavern_Room4_Text_Grunt4Intro:
	.string "¿Quién eres?\n"
	.string "¿Adónde te crees que vas?$"

SeafloorCavern_Room4_Text_Grunt4Defeat:
	.string "¡No he podido ganar!$"

SeafloorCavern_Room4_Text_Grunt4PostBattle:
	.string "¡Mi compañero se dejó el mapa en el\n"
	.string "submarino!\p"
	.string "¿Se puede ser más inútil?$"

