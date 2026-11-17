GrutaIgnea_Camara_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GrutaIgnea_Camara_OnTransition
	.byte 0

@ Dualocke: el guardián de la CÁMARA DEL MAGMA, un Pokémon fuerte que se puede capturar, como en las islas del
@ ferry (data/scripts/dualocke_islas.inc). Con semilla sale otro de su tipo (estaticos.py, islas()).
GrutaIgnea_Camara_OnTransition:
	setvar VAR_0x8004, SPECIES_HOUNDOOM
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

GrutaIgnea_Camara_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, SPECIES_HOUNDOOM
	setvar VAR_TEMP_9, ITEM_SCOPE_LENS
	call Dualocke_EventScript_AvisoIsla
	setwildbattle SPECIES_HOUNDOOM, 47
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, GrutaIgnea_Camara_EventScript_PokemonSigue
	setflag FLAG_DUALOCKE_GUARDIAN_GRUTA
	call Dualocke_EventScript_PremioIsla
	release
	end

GrutaIgnea_Camara_EventScript_PokemonSigue::
	release
	end
