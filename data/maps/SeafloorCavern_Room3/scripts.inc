SeafloorCavern_Room3_MapScripts::
	.byte 0

SeafloorCavern_Room3_EventScript_Shelly::
	trainerbattle_single TRAINER_SHELLY_SEAFLOOR_CAVERN, SeafloorCavern_Room3_Text_ShellyIntro, SeafloorCavern_Room3_Text_ShellyDefeat
	msgbox SeafloorCavern_Room3_Text_ShellyPostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_5, SeafloorCavern_Room3_Text_Grunt5Intro, SeafloorCavern_Room3_Text_Grunt5Defeat
	msgbox SeafloorCavern_Room3_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_Text_ShellyIntro:
	.string "¡Jajajajaja!\p"
	.string "¿Cómo has llegado hasta aquí sin\n"
	.string "submarino?\l"
	.string "¡Qué criatura más impresionante!\p"
	.string "Pero… No me conviene que andes\n"
	.string "metiendo las narices aquí.\p"
	.string "Y quiero la revancha por lo del\n"
	.string "INSTITUTO METEOROLÓGICO…\p"
	.string "¡Te voy a dar a probar un poco de\n"
	.string "dolor! ¡Resígnate!$"

SeafloorCavern_Room3_Text_ShellyDefeat:
	.string "¡Jajajajaja!\p"
	.string "¡Ay!$"

SeafloorCavern_Room3_Text_ShellyPostBattle:
	.string "¡Jajajajaja!\n"
	.string "Qué fuerte eres, de verdad.\p"
	.string "Es una pena enorme que no seas del\n"
	.string "EQUIPO AQUA.\p"
	.string "Podrías haber disfrutado con nosotros\n"
	.string "del mundo fabuloso que nos ha\l"
	.string "prometido el JEFE…$"

SeafloorCavern_Room3_Text_Grunt5Intro:
	.string "Para que nuestro sueño se cumpla,\n"
	.string "necesitamos el poder de los POKéMON.\p"
	.string "¡Pero los entrometidos como tú usan\n"
	.string "ese poder para fastidiarnos hasta\l"
	.string "en un sitio como este!\p"
	.string "¡La vida no funciona como nos\n"
	.string "hace falta!$"

SeafloorCavern_Room3_Text_Grunt5Defeat:
	.string "¡Uah!$"

SeafloorCavern_Room3_Text_Grunt5PostBattle:
	.string "¿Sabes? Nosotros no nos atrevemos a\n"
	.string "cuestionar los motivos del líder.\p"
	.string "Pero aquí estás tú, plantándole cara\n"
	.string "a nuestro JEFE.\p"
	.string "A lo mejor…\n"
	.string "A lo mejor eres alguien especial…$"

