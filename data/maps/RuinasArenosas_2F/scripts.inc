RuinasArenosas_2F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, RuinasArenosas_2F_OnLoad
	.byte 0

@ Dualocke: RUINAS ARENOSAS (tools/dualocke/crear_desierto_profundo.py). El interruptor abre las puertas
@ de piedra de esta planta, que se quedan abiertas.
RuinasArenosas_2F_OnLoad:
	goto_if_unset FLAG_DUALOCKE_RUINAS_2F_ABIERTA, RuinasArenosas_2F_OnLoadFin
	call RuinasArenosas_2F_Abrir
RuinasArenosas_2F_OnLoadFin:
	end

RuinasArenosas_2F_Abrir:
	setmetatile 16, 8, 0x211, FALSE
	setmetatile 10, 13, 0x211, FALSE
	setmetatile 10, 14, 0x211, FALSE
	setmetatile 3, 11, 0x232, FALSE
	return

RuinasArenosas_2F_EventScript_Interruptor::
	lockall
	goto_if_set FLAG_DUALOCKE_RUINAS_2F_ABIERTA, RuinasArenosas_2F_EventScript_InterruptorFin
	setflag FLAG_DUALOCKE_RUINAS_2F_ABIERTA
	playse SE_SWITCH
	call RuinasArenosas_2F_Abrir
	special DrawWholeMapView
	playse SE_M_STRENGTH
	msgbox RuinasArenosas_Text_Interruptor, MSGBOX_DEFAULT
RuinasArenosas_2F_EventScript_InterruptorFin:
	releaseall
	end
