PradoHadas_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PradoHadas_OnTransition
	.byte 0

@ Dualocke: el PRADO DE HADAS, al oeste del INSTITUTO METEOROLÓGICO (tools/dualocke/crear_prado_hadas.py).
@ El guardián es un Pokémon fuerte que se puede capturar, como en las islas del ferry
@ (data/scripts/dualocke_islas.inc). Con semilla sale otro fuerte (estaticos.py, islas()).
PradoHadas_OnTransition:
	setvar VAR_0x8004, SPECIES_GARDEVOIR
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

PradoHadas_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, SPECIES_GARDEVOIR
	setvar VAR_TEMP_9, ITEM_PIXIE_PLATE
	call Dualocke_EventScript_AvisoIsla
	setwildbattle SPECIES_GARDEVOIR, 59
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, PradoHadas_EventScript_PokemonSigue
	setflag FLAG_DUALOCKE_GUARDIAN_PRADO
	call Dualocke_EventScript_PremioIsla
	release
	end

PradoHadas_EventScript_PokemonSigue::
	release
	end

PradoHadas_EventScript_Florista::
	msgbox PradoHadas_Text_Florista, MSGBOX_NPC
	end

PradoHadas_Text_Florista:
	.string "Vengo a por flores para la tienda,\n"
	.string "pero aquí hay que andar con cuidado.\p"
	.string "Los POKéMON hada juegan a esconderte\n"
	.string "el camino entre la hierba.\p"
	.string "Junto a la charca grande del norte\n"
	.string "vive una que protege el prado.$"
