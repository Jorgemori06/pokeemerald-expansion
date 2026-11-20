PlayaVolcanica_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, PlayaVolcanica_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, PlayaVolcanica_OnTransition
	.byte 0

@ Dualocke: la PLAYA VOLCÁNICA, al oeste del MONTE PÍRICO (tools/dualocke/crear_playa_volcanica.py).
@ El guardián es un Pokémon fuerte que se puede capturar, como en las islas del ferry
@ (data/scripts/dualocke_islas.inc). Con semilla sale otro de su tipo (estaticos.py, islas()).
@ Al pisar la hierba con ceniza se le cae la ceniza, como en la RUTA 113.
PlayaVolcanica_OnResume:
	setstepcallback STEP_CB_ASH
	end

PlayaVolcanica_OnTransition:
	setvar VAR_0x8004, SPECIES_SLITHER_WING
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

PlayaVolcanica_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, SPECIES_SLITHER_WING
	setvar VAR_TEMP_9, ITEM_BOOSTER_ENERGY
	call Dualocke_EventScript_AvisoIsla
	setwildbattle SPECIES_SLITHER_WING, 70
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, PlayaVolcanica_EventScript_PokemonSigue
	setflag FLAG_DUALOCKE_GUARDIAN_PLAYA
	call Dualocke_EventScript_PremioIsla
	release
	end

PlayaVolcanica_EventScript_PokemonSigue::
	release
	end

PlayaVolcanica_EventScript_Vecino::
	msgbox PlayaVolcanica_Text_Vecino, MSGBOX_NPC
	end

PlayaVolcanica_Text_Vecino:
	.string "Cuando el MONTE PÍRICO echa humo,\n"
	.string "la ceniza llega hasta esta playa.\p"
	.string "Dicen que un POKéMON enorme sale\n"
	.string "del mar a tomar el sol en la arena.$"
