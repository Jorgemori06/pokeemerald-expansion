IslaVolcanica_Crater_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IslaVolcanica_Crater_OnTransition
	.byte 0

@ Dualocke: el guardián de la ISLA VOLCÁNICA, un Pokémon fuerte que se puede capturar, como en las islas del
@ ferry (data/scripts/dualocke_islas.inc). Con semilla sale otro de su tipo (estaticos.py, islas()).
IslaVolcanica_Crater_OnTransition:
	setvar VAR_0x8004, SPECIES_CHARIZARD
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

IslaVolcanica_Crater_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, SPECIES_CHARIZARD
	setvar VAR_TEMP_9, ITEM_HEAT_ROCK
	call Dualocke_EventScript_AvisoIsla
	setwildbattle SPECIES_CHARIZARD, 70
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, IslaVolcanica_Crater_EventScript_PokemonSigue
	setflag FLAG_DUALOCKE_GUARDIAN_VOLCAN
	call Dualocke_EventScript_PremioIsla
	release
	end

IslaVolcanica_Crater_EventScript_PokemonSigue::
	release
	end
