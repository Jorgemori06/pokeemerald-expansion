PlayaVolcanica_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PlayaVolcanica_OnTransition
	.byte 0

@ Dualocke: la PLAYA VOLCÁNICA, al oeste del MONTE PÍRICO (tools/dualocke/crear_playa_volcanica.py).
@ El guardián es un Pokémon fuerte que se puede capturar, como en las islas del ferry
@ (data/scripts/dualocke_islas.inc). Con semilla sale otro de su tipo (estaticos.py, islas()).
PlayaVolcanica_OnTransition:
	setvar VAR_0x8004, SPECIES_GYARADOS
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

PlayaVolcanica_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, SPECIES_GYARADOS
	setvar VAR_TEMP_9, ITEM_MYSTIC_WATER
	call Dualocke_EventScript_AvisoIsla
	setwildbattle SPECIES_GYARADOS, 70
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

PlayaVolcanica_EventScript_Banista::
	msgbox PlayaVolcanica_Text_Banista, MSGBOX_NPC
	end

PlayaVolcanica_Text_Banista:
	.string "Estas aguas las calienta el volcán\n"
	.string "que hay bajo el MONTE PÍRICO.\p"
	.string "Dicen que un POKéMON enorme sale\n"
	.string "del mar a tomar el sol.$"
