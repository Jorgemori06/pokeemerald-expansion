Route119_WeatherInstitute_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route119_WeatherInstitute_1F_OnTransition
	.byte 0

Route119_WeatherInstitute_1F_OnTransition:
	call_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Route119_WeatherInstitute_1F_EventScript_SetLittleBoyPos
	end

Route119_WeatherInstitute_1F_EventScript_SetLittleBoyPos::
	setobjectxyperm LOCALID_WEATHER_INSTITUTE_LITTLE_BOY, 0, 5
	setobjectmovementtype LOCALID_WEATHER_INSTITUTE_LITTLE_BOY, MOVEMENT_TYPE_FACE_RIGHT
	return

Route119_WeatherInstitute_1F_EventScript_LittleBoy::
	lock
	faceplayer
	special GetPlayerBigGuyGirlString
	goto_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Route119_WeatherInstitute_1F_EventScript_LittleBoyTeamAquaHere
	msgbox Route119_WeatherInstitute_1F_Text_WowYoureStrong, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_LittleBoyTeamAquaHere::
	msgbox Route119_WeatherInstitute_1F_Text_EveryoneWentUpstairs, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_InstituteWorker1::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, Route119_WeatherInstitute_1F_EventScript_StudyingRain
	setvar VAR_0x8004, 0
	call_if_set FLAG_DEFEATED_KYOGRE, Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated
	call_if_set FLAG_DEFEATED_GROUDON, Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated
	goto_if_eq VAR_0x8004, 2, Route119_WeatherInstitute_1F_EventScript_StudyingRain  @ Both defeated
	msgbox Route119_WeatherInstitute_1F_Text_NoticingAbnormalWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated::
	addvar VAR_0x8004, 1
	return

Route119_WeatherInstitute_1F_EventScript_StudyingRain::
	msgbox Route119_WeatherInstitute_1F_Text_ProfStudyingRain, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_InstituteWorker2::
	msgbox Route119_WeatherInstitute_1F_Text_WhatWereAquasUpTo, MSGBOX_NPC
	end

Route119_WeatherInstitute_1F_EventScript_Bed::
	lockall
	msgbox Route119_WeatherInstitute_1F_Text_TakeRestInBed, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	releaseall
	end

Route119_WeatherInstitute_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_1, Route119_WeatherInstitute_1F_Text_Grunt1Intro, Route119_WeatherInstitute_1F_Text_Grunt1Defeat
	msgbox Route119_WeatherInstitute_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_1F_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_4, Route119_WeatherInstitute_1F_Text_Grunt4Intro, Route119_WeatherInstitute_1F_Text_Grunt4Defeat
	msgbox Route119_WeatherInstitute_1F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_1F_Text_Grunt1Intro:
	.string "Al JEFE le interesa lo que investigan\n"
	.string "aquí, así que nos ha mandado.\p"
	.string "¡Deja de meter las narices!$"

Route119_WeatherInstitute_1F_Text_Grunt1Defeat:
	.string "Maldita sea…\n"
	.string "Me ha machacado un renacuajo…$"

Route119_WeatherInstitute_1F_Text_Grunt1PostBattle:
	.string "Nuestro JEFE lo sabe todo.\p"
	.string "Pero yo solo soy un SOLDADO.\n"
	.string "¿Qué voy a saber de lo que piensa?$"

Route119_WeatherInstitute_1F_Text_Grunt4Intro:
	.string "¿Eh?\n"
	.string "¿Qué hace aquí una criatura?$"

Route119_WeatherInstitute_1F_Text_Grunt4Defeat:
	.string "¿Eh?\n"
	.string "¡¿He perdido?!$"

Route119_WeatherInstitute_1F_Text_Grunt4PostBattle:
	.string "Ay, no…\n"
	.string "Me va a caer una buena por perder\l"
	.string "contra una criatura…\p"
	.string "Mejor me echo una siesta en la cama…$"

Route119_WeatherInstitute_1F_Text_EveryoneWentUpstairs:
	.string "¡Mientras dormía, todos se han\n"
	.string "ido arriba!$"

Route119_WeatherInstitute_1F_Text_WowYoureStrong:
	.string "¡Hala, qué fuerte eres!\p"
	.string "¡Ojalá pudiera entrenar POKéMON\n"
	.string "como tú!$"

Route119_WeatherInstitute_1F_Text_ProfStudyingRain:
	.string "Al PROFESOR le encanta la lluvia.\n"
	.string "Es un hecho.\p"
	.string "Pero si no para de llover, la gente lo\n"
	.string "pasará mal. Es otro hecho.\p"
	.string "Por eso, el PROFESOR estudia si la\n"
	.string "lluvia se puede aprovechar.$"

Route119_WeatherInstitute_1F_Text_NoticingAbnormalWeather:
	.string "En la segunda planta del INSTITUTO\n"
	.string "estudiamos el tiempo en la región\l"
	.string "de HOENN.\p"
	.string "Últimamente hemos visto sequías y\n"
	.string "lluvias torrenciales en sitios\l"
	.string "concretos y durante poco tiempo…$"

Route119_WeatherInstitute_1F_Text_WhatWereAquasUpTo:
	.string "¡Hola!\n"
	.string "¡Gracias a ti nos hemos salvado!\p"
	.string "Lo que no entiendo es qué demonios\n"
	.string "querían los del AQUA.$"

Route119_WeatherInstitute_1F_Text_TakeRestInBed:
	.string "Hay una cama…\n"
	.string "Vamos a descansar.$"

