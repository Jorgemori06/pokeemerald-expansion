PacifidlogTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PacifidlogTown_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, PacifidlogTown_OnResume
	.byte 0

PacifidlogTown_OnTransition:
	setflag FLAG_VISITED_PACIFIDLOG_TOWN
	end

PacifidlogTown_OnResume:
	setstepcallback STEP_CB_PACIFIDLOG_BRIDGE
	end

PacifidlogTown_EventScript_NinjaBoy::
	msgbox PacifidlogTown_Text_NeatHousesOnWater, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Girl::
	msgbox PacifidlogTown_Text_FastRunningCurrent, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Fisherman::
	msgbox PacifidlogTown_Text_SkyPillarTooScary, MSGBOX_NPC
	end

PacifidlogTown_EventScript_TownSign::
	msgbox PacifidlogTown_Text_TownSign, MSGBOX_SIGN
	end

PacifidlogTown_Text_FastRunningCurrent:
	.string "En el mar entre PACIFIDLOG y PORTUAL\n"
	.string "la corriente es muy rápida.\p"
	.string "Si decides hacer SURF, puede que te\n"
	.string "arrastre a otra parte.$"

PacifidlogTown_Text_NeatHousesOnWater:
	.string "¿A que mola?\n"
	.string "¡Estas casas están sobre el agua!\p"
	.string "¡Yo nací aquí!$"

PacifidlogTown_Text_SkyPillarTooScary:
	.string "¿El PILAR CELESTE?\p"
	.string "… Ah, te referirás a esa torre tan\n"
	.string "alta que hay un poco más allá.\p"
	.string "Yo no subiría.\n"
	.string "Da demasiado miedo estar tan alto.\p"
	.string "La vida a ras del mar en PACIFIDLOG\n"
	.string "ya me va bien.$"

PacifidlogTown_Text_TownSign:
	.string "PUEBLO PACIFIDLOG\p"
	.string "“Donde el sol de la mañana sonríe\n"
	.string "sobre las aguas”.$"

