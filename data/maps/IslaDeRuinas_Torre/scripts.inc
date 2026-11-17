IslaDeRuinas_Torre_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IslaDeRuinas_Torre_OnTransition
	.byte 0

@ Dualocke: el guardián de la ISLA DE RUINAS, un Pokémon fuerte que se puede capturar, como en las islas del
@ ferry (data/scripts/dualocke_islas.inc). Con semilla sale otro de su tipo (estaticos.py, islas()).
IslaDeRuinas_Torre_OnTransition:
	setvar VAR_0x8004, SPECIES_METAGROSS
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

IslaDeRuinas_Torre_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, SPECIES_METAGROSS
	setvar VAR_TEMP_9, ITEM_EXPERT_BELT
	call Dualocke_EventScript_AvisoIsla
	setwildbattle SPECIES_METAGROSS, 70
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, IslaDeRuinas_Torre_EventScript_PokemonSigue
	setflag FLAG_DUALOCKE_GUARDIAN_ISLA_RUINAS
	call Dualocke_EventScript_PremioIsla
	release
	end

IslaDeRuinas_Torre_EventScript_PokemonSigue::
	release
	end
