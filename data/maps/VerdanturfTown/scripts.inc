VerdanturfTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_OnTransition
	.byte 0

VerdanturfTown_OnTransition:
	setflag FLAG_VISITED_VERDANTURF_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	end

VerdanturfTown_EventScript_Twin::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_TwinTunnelOpen
	msgbox VerdanturfTown_Text_ManTryingToDigTunnel, MSGBOX_DEFAULT
	applymovement LOCALID_VERDANTURF_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_TwinTunnelOpen::
	msgbox VerdanturfTown_Text_ManDugTunnelForLove, MSGBOX_DEFAULT
	applymovement LOCALID_VERDANTURF_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_Man::
	msgbox VerdanturfTown_Text_AirCleanHere, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Camper::
	msgbox VerdanturfTown_Text_MakeBattleTentDebut, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_BoyTunnelOpen
	msgbox VerdanturfTown_Text_GuyTryingToBustThroughCave, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_BoyTunnelOpen::
	msgbox VerdanturfTown_Text_EasyToGetToRustboroNow, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_TownSign::
	msgbox VerdanturfTown_Text_TownSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_WandasHouseSign::
	msgbox VerdanturfTown_Text_WandasHouse, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_BattleTentSign::
	msgbox VerdanturfTown_Text_BattleTentSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_RusturfTunnelSign::
	msgbox VerdanturfTown_Text_RusturfTunnelSign, MSGBOX_SIGN
	end

VerdanturfTown_Text_ManTryingToDigTunnel:
	.string "Me lo ha contado mi papá.\p"
	.string "Dice que este túnel está lleno de\n"
	.string "POKéMON muy tímidos.\p"
	.string "Se asustan con los ruidos fuertes\n"
	.string "y arman mucho jaleo.\p"
	.string "Por eso pararon el proyecto del\n"
	.string "gran túnel.\p"
	.string "¡Pero hay un hombre que intenta\n"
	.string "cavar el túnel él solo!$"

VerdanturfTown_Text_ManDugTunnelForLove:
	.string "Había un hombre que cavaba un túnel\n"
	.string "por una chica a la que quería.\p"
	.string "No lo entiendo mucho, pero ¡bueno!$"

VerdanturfTown_Text_AirCleanHere:
	.string "Por cómo sopla el viento, la ceniza\n"
	.string "del volcán nunca llega hasta aquí.\p"
	.string "El aire es limpio y delicioso.\n"
	.string "Vivir aquí le sienta de maravilla\l"
	.string "hasta a la gente más delicada.$"

VerdanturfTown_Text_MakeBattleTentDebut:
	.string "Mis POKéMON y yo llevamos una racha\n"
	.string "de victorias impresionante.\p"
	.string "Así que he decidido estrenarme en la\n"
	.string "CARPA DE COMBATE de este pueblo.$"

VerdanturfTown_Text_GuyTryingToBustThroughCave:
	.string "¿Has visto la cueva que hay al lado\n"
	.string "de la TIENDA POKéMON?\p"
	.string "Hay un chico ahí dentro que intenta\n"
	.string "romper las rocas para salir al\l"
	.string "otro lado.\p"
	.string "Sería genial poder cruzarla…\n"
	.string "Así sería fácil ir a FÉRRICA.$"

VerdanturfTown_Text_EasyToGetToRustboroNow:
	.string "La cueva de al lado de la TIENDA\n"
	.string "POKéMON ya es un túnel al otro lado.\p"
	.string "¡Genial! Ahora es fácil ir a FÉRRICA\n"
	.string "a comprar lo nuevo de DEVON.$"

VerdanturfTown_Text_TownSign:
	.string "PUEBLO VERDEGAL\p"
	.string "“Las tierras altas barridas por el\n"
	.string "viento con dulce olor a hierba”.$"

VerdanturfTown_Text_WandasHouse:
	.string "CASA DE WANDA$"

VerdanturfTown_Text_BattleTentSign:
	.string "CARPA DE COMBATE DE VERDEGAL\n"
	.string "“¡Disfruta viendo combates!”$"

VerdanturfTown_Text_RusturfTunnelSign:
	.string "TÚNEL FERVERGAL\n"
	.string "“Une FÉRRICA y VERDEGAL”.\p"
	.string "”El proyecto del túnel se ha\n"
	.string "cancelado”.$"

