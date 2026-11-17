BosqueSiniestro_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BosqueSiniestro_OnTransition
	.byte 0

@ Dualocke: el BOSQUE SINIESTRO, al sur de la RUTA 123 (tools/dualocke/crear_bosque_siniestro.py).
@ El guardián es un Pokémon fuerte que se puede capturar, como en las islas del ferry
@ (data/scripts/dualocke_islas.inc). Con semilla sale otro fuerte (estaticos.py, islas()).
BosqueSiniestro_OnTransition:
	setvar VAR_0x8004, SPECIES_HYDREIGON
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

BosqueSiniestro_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, SPECIES_HYDREIGON
	setvar VAR_TEMP_9, ITEM_DREAD_PLATE
	call Dualocke_EventScript_AvisoIsla
	setwildbattle SPECIES_HYDREIGON, 59
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, BosqueSiniestro_EventScript_PokemonSigue
	setflag FLAG_DUALOCKE_GUARDIAN_SINIESTRO
	call Dualocke_EventScript_PremioIsla
	release
	end

BosqueSiniestro_EventScript_PokemonSigue::
	release
	end

BosqueSiniestro_EventScript_Bruja::
	msgbox BosqueSiniestro_Text_Bruja, MSGBOX_NPC
	end

BosqueSiniestro_Text_Bruja:
	.string "Aquí abajo nunca llega el sol:\n"
	.string "es el bosque de la noche.\p"
	.string "Al fondo hay un claro, y algo\n"
	.string "muy grande duerme allí…\p"
	.string "No lo despiertes si no vas\n"
	.string "preparado. Je, je, je…$"
