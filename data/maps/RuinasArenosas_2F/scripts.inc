RuinasArenosas_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_TRANSITION, CaveHole_FixCrackedGround
	map_script MAP_SCRIPT_ON_RESUME, RuinasArenosas_2F_SetHoleWarp
	.byte 0

@ Dualocke: RUINAS ARENOSAS (tools/dualocke/crear_desierto_profundo.py). Si el suelo se rompe, caes abajo
RuinasArenosas_2F_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_RUINAS_ARENOSAS
	end
