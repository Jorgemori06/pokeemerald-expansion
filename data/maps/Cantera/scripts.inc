Cantera_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Cantera_OnTransition
	.byte 0

@ Dualocke: la CANTERA, por una cueva de la RUTA 116 (tools/dualocke/crear_cantera.py).
@ El guardián es un Pokémon fuerte que se puede capturar, como en las islas del ferry
@ (data/scripts/dualocke_islas.inc). Con semilla sale otro fuerte (estaticos.py, islas()).
Cantera_OnTransition:
	setvar VAR_0x8004, SPECIES_AGGRON
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

Cantera_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, SPECIES_AGGRON
	setvar VAR_TEMP_9, ITEM_IRON_PLATE
	call Dualocke_EventScript_AvisoIsla
	setwildbattle SPECIES_AGGRON, 29
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, Cantera_EventScript_PokemonSigue
	setflag FLAG_DUALOCKE_GUARDIAN_CANTERA
	call Dualocke_EventScript_PremioIsla
	release
	end

Cantera_EventScript_PokemonSigue::
	release
	end

Cantera_EventScript_Obrera::
	msgbox Cantera_Text_Obrera, MSGBOX_NPC
	end

Cantera_Text_Obrera:
	.string "De esta cantera sale el hierro\n"
	.string "con el que DEVON hace sus inventos.\p"
	.string "Los POKéMON de acero vienen a comer\n"
	.string "las piedras… ¡y a veces el material!\p"
	.string "Abajo del todo vive uno enorme.\n"
	.string "Desde que llegó, no bajamos.$"
