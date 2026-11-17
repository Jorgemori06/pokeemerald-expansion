CienagaToxica_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CienagaToxica_OnTransition
	.byte 0

@ Dualocke: la CIÉNAGA TÓXICA, al sur de la RUTA 117 (tools/dualocke/crear_cienaga_toxica.py).
@ El guardián es un Pokémon fuerte que se puede capturar, como en las islas del ferry
@ (data/scripts/dualocke_islas.inc). Con semilla sale otro fuerte (estaticos.py, islas()).
CienagaToxica_OnTransition:
	setvar VAR_0x8004, SPECIES_DRAGALGE
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

CienagaToxica_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, SPECIES_DRAGALGE
	setvar VAR_TEMP_9, ITEM_BLACK_SLUDGE
	call Dualocke_EventScript_AvisoIsla
	setwildbattle SPECIES_DRAGALGE, 29
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, CienagaToxica_EventScript_PokemonSigue
	setflag FLAG_DUALOCKE_GUARDIAN_CIENAGA
	call Dualocke_EventScript_PremioIsla
	release
	end

CienagaToxica_EventScript_PokemonSigue::
	release
	end

CienagaToxica_EventScript_Cientifica::
	msgbox CienagaToxica_Text_Cientifica, MSGBOX_NPC
	end

CienagaToxica_Text_Cientifica:
	.string "Estudio el agua de esta ciénaga.\n"
	.string "Está llena de veneno… ¡y de vida!\p"
	.string "En el islote de la charca grande\n"
	.string "vive un POKéMON enorme.\p"
	.string "Lleva antídotos si vas a verlo.$"
