RuinasArenosas_3F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, RuinasArenosas_3F_OnLoad
	.byte 0

@ Dualocke: RUINAS ARENOSAS (tools/dualocke/crear_desierto_profundo.py). El interruptor abre las puertas
@ de piedra de esta planta, que se quedan abiertas.
RuinasArenosas_3F_OnLoad:
	goto_if_unset FLAG_DUALOCKE_RUINAS_3F_ABIERTA, RuinasArenosas_3F_OnLoadFin
	call RuinasArenosas_3F_Abrir
RuinasArenosas_3F_OnLoadFin:
	end

RuinasArenosas_3F_Abrir:
	setmetatile 10, 2, 0x29A, FALSE
	setmetatile 10, 3, 0x2AA, FALSE
	setmetatile 3, 8, 0x2A1, FALSE
	setmetatile 4, 8, 0x2A2, FALSE
	setmetatile 3, 12, 0x232, FALSE
	return

RuinasArenosas_3F_EventScript_Interruptor::
	lockall
	goto_if_set FLAG_DUALOCKE_RUINAS_3F_ABIERTA, RuinasArenosas_3F_EventScript_InterruptorFin
	setflag FLAG_DUALOCKE_RUINAS_3F_ABIERTA
	playse SE_SWITCH
	call RuinasArenosas_3F_Abrir
	special DrawWholeMapView
	playse SE_M_STRENGTH
	msgbox RuinasArenosas_Text_Interruptor, MSGBOX_DEFAULT
RuinasArenosas_3F_EventScript_InterruptorFin:
	releaseall
	end
