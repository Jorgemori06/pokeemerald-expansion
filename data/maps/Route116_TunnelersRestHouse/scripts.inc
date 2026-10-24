Route116_TunnelersRestHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route116_TunnelersRestHouse_OnTransition
	.byte 0

Route116_TunnelersRestHouse_OnTransition:
	setflag FLAG_LANDMARK_TUNNELERS_REST_HOUSE
	end

Route116_TunnelersRestHouse_EventScript_Tunneler1::
	msgbox Route116_TunnelersRestHouse_Text_WeHadToStopBoring, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler2::
	msgbox Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler3::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, Route116_TunnelersRestHouse_EventScript_TunnelOpened
	msgbox Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_EventScript_TunnelOpened::
	msgbox Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_Text_WeHadToStopBoring:
	.string "Ese TÚNEL FERVERGAL de ahí…\p"
	.string "Al principio, un montón de obreros\n"
	.string "perforaban la roca con máquinas\l"
	.string "modernas. Pero tuvimos que parar.\p"
	.string "Resulta que habríamos perjudicado\n"
	.string "a los POKéMON salvajes de la zona.\p"
	.string "Así que no tenemos nada que hacer\n"
	.string "más que holgazanear aquí.$"

Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf:
	.string "Hay un hombre cavando él solo hasta\n"
	.string "VERDEGAL.\l"
	.string "Está desesperado por llegar.\p"
	.string "Dice que si cava poco a poco sin\n"
	.string "máquinas, no molestará a los\l"
	.string "POKéMON ni dañará la naturaleza.\p"
	.string "¿Habrá llegado ya al otro lado?$"

Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel:
	.string "Para ir a VERDEGAL sin usar este\n"
	.string "TÚNEL, tendrías que cruzar el mar\l"
	.string "hasta AZULIZA, navegar hasta PORTUAL\l"
	.string "y luego pasar por MALVALONA.$"

Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough:
	.string "¿Te has enterado? ¡El TÚNEL a VERDEGAL\n"
	.string "ya está abierto!\p"
	.string "A veces, si lo deseas con muchas\n"
	.string "ganas, los sueños se cumplen.$"

