IslaDragon_Valle_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IslaDragon_Valle_OnTransition
	.byte 0

@ Dualocke: el VALLE DEL DRAGÓN, en la ISLA DEL DRAGÓN (tools/dualocke/crear_isla_dragon.py).
@ El guardián es un Pokémon fuerte que se puede capturar, como en las islas del ferry
@ (data/scripts/dualocke_islas.inc). Con semilla sale otro fuerte (estaticos.py, islas()).
IslaDragon_Valle_OnTransition:
	setvar VAR_0x8004, SPECIES_HAXORUS
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

IslaDragon_Valle_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, SPECIES_HAXORUS
	setvar VAR_TEMP_9, ITEM_DRACO_PLATE
	call Dualocke_EventScript_AvisoIsla
	setwildbattle SPECIES_HAXORUS, 81
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, IslaDragon_Valle_EventScript_PokemonSigue
	setflag FLAG_DUALOCKE_GUARDIAN_DRAGON
	call Dualocke_EventScript_PremioIsla
	release
	end

IslaDragon_Valle_EventScript_PokemonSigue::
	release
	end
