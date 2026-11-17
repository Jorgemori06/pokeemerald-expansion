IslaArenosa_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IslaArenosa_OnTransition
	.byte 0

@ Dualocke: el guardián de la ISLA ARENOSA, un Pokémon fuerte que se puede capturar, como en las islas del
@ ferry (data/scripts/dualocke_islas.inc). Con semilla sale otro de su tipo (estaticos.py, islas()).
IslaArenosa_OnTransition:
	setvar VAR_0x8004, SPECIES_SANDY_SHOCKS
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

IslaArenosa_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, SPECIES_SANDY_SHOCKS
	setvar VAR_TEMP_9, ITEM_SMOOTH_ROCK
	call Dualocke_EventScript_AvisoIsla
	setwildbattle SPECIES_SANDY_SHOCKS, 81
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, IslaArenosa_EventScript_PokemonSigue
	setflag FLAG_DUALOCKE_GUARDIAN_ARENOSA
	call Dualocke_EventScript_PremioIsla
	release
	end

IslaArenosa_EventScript_PokemonSigue::
	release
	end

@ DARÍO es TRAINER_RED, que existía sin usar (zonas_nuevas.py le pone nombre y equipo)
IslaArenosa_EventScript_Dario::
	trainerbattle_single TRAINER_RED, IslaArenosa_Text_DarioIntro, IslaArenosa_Text_DarioDefeat
	msgbox IslaArenosa_Text_DarioPostBattle, MSGBOX_AUTOCLOSE
	end

IslaArenosa_Text_DarioIntro:
	.string "Con esta arena no se ve nada…\n"
	.string "¡Pero a ti sí te veo!$"

IslaArenosa_Text_DarioDefeat:
	.string "Se me ha metido arena en los ojos.$"

IslaArenosa_Text_DarioPostBattle:
	.string "En el islote de abajo vive un\n"
	.string "POKéMON enorme. Ten cuidado.$"
