FarawayIsland_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FarawayIsland_Entrance_OnTransition
	.byte 0

FarawayIsland_Entrance_OnTransition:
	setflag FLAG_ARRIVED_ON_FARAWAY_ISLAND
	end

FarawayIsland_Entrance_EventScript_SetCloudsWeather::
	setweather WEATHER_SUNNY_CLOUDS
	doweather
	end

FarawayIsland_Entrance_EventScript_ClearWeather::
	setweather WEATHER_NONE
	doweather
	end

FarawayIsland_Entrance_EventScript_Sailor::
	lock
	faceplayer
	msgbox FarawayIsland_Entrance_Text_SailorReturn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FarawayIsland_Entrance_EventScript_AsYouLike
	msgbox EventTicket_Text_SailHome, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	hideobjectat LOCALID_FARAWAY_ISLAND_SAILOR, MAP_FARAWAY_ISLAND_ENTRANCE
	setvar VAR_0x8004, LOCALID_FARAWAY_ISLAND_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	warp MAP_LILYCOVE_CITY_HARBOR, 8, 11
	waitstate
	release
	end

FarawayIsland_Entrance_EventScript_AsYouLike::
	msgbox EventTicket_Text_AsYouLike, MSGBOX_DEFAULT
	release
	end

FarawayIsland_Entrance_EventScript_Sign::
	msgbox FarawayIsland_Entrance_Text_Sign, MSGBOX_SIGN
	end

@ Dualocke: entrenadores de la isla
FarawayIsland_Entrance_EventScript_Mike::
	trainerbattle_single TRAINER_MIKE_1, FarawayIsland_Entrance_Text_MikeIntro, FarawayIsland_Entrance_Text_MikeDefeat
	msgbox FarawayIsland_Entrance_Text_MikePostBattle, MSGBOX_AUTOCLOSE
	end

FarawayIsland_Entrance_EventScript_AmyLiv::
	trainerbattle_double TRAINER_AMY_AND_LIV_3, FarawayIsland_Entrance_Text_AmyLivIntro, FarawayIsland_Entrance_Text_AmyLivDefeat, FarawayIsland_Entrance_Text_AmyLivNotEnoughMons
	msgbox FarawayIsland_Entrance_Text_AmyLivPostBattle, MSGBOX_AUTOCLOSE
	end

FarawayIsland_Entrance_Text_MikeIntro:
	.string "¡Estas rocas no las ha pisado\n"
	.string "casi nadie! ¡Ni a ti te dejo!$"

FarawayIsland_Entrance_Text_MikeDefeat:
	.string "¡Me has dejado sin aliento!$"

FarawayIsland_Entrance_Text_MikePostBattle:
	.string "Arriba hay una pradera de hierba\n"
	.string "alta. Ve con cuidado.$"

FarawayIsland_Entrance_Text_AmyLivIntro:
	.string "¡Nos hemos colado en el barco!\n"
	.string "¡Ahora, combate doble!$"

FarawayIsland_Entrance_Text_AmyLivDefeat:
	.string "¡Jo! ¡Qué fuerte!$"

FarawayIsland_Entrance_Text_AmyLivNotEnoughMons:
	.string "¿Solo llevas un POKéMON?\n"
	.string "¡Así no vale!$"

FarawayIsland_Entrance_Text_AmyLivPostBattle:
	.string "¡No se lo digas al capitán, que\n"
	.string "no hemos pagado el billete!$"
