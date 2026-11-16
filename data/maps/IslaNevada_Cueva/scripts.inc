IslaNevada_Cueva_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IslaNevada_Cueva_OnTransition
	.byte 0

@ Dualocke: la CUEVA HELADA de la ISLA NEVADA (tools/dualocke/crear_isla_nevada.py)
IslaNevada_Cueva_EventScript_Nieves::
	trainerbattle_single TRAINER_NIEVES, IslaNevada_Cueva_Text_NievesIntro, IslaNevada_Cueva_Text_NievesDefeat
	msgbox IslaNevada_Cueva_Text_NievesPostBattle, MSGBOX_AUTOCLOSE
	end

IslaNevada_Cueva_Text_NievesIntro:
	.string "Entreno aquí porque el hielo no\n"
	.string "perdona ni un paso en falso.$"

IslaNevada_Cueva_Text_NievesDefeat:
	.string "Has cruzado el hielo mejor que yo.$"

IslaNevada_Cueva_Text_NievesPostBattle:
	.string "Si resbalas, para en una roca o en\n"
	.string "el suelo de piedra.$"

@ Dualocke: el guardián de la CUEVA HELADA, un Pokémon fuerte que se puede capturar, como en las islas del
@ ferry (data/scripts/dualocke_islas.inc). Con semilla sale otro de su tipo (estaticos.py, islas()).
IslaNevada_Cueva_OnTransition:
	setvar VAR_0x8004, SPECIES_BAXCALIBUR
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	end

IslaNevada_Cueva_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, SPECIES_BAXCALIBUR
	setvar VAR_TEMP_9, ITEM_RAZOR_CLAW
	call Dualocke_EventScript_AvisoIsla
	setwildbattle SPECIES_BAXCALIBUR, 70
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, IslaNevada_Cueva_EventScript_PokemonSigue
	setflag FLAG_DUALOCKE_GUARDIAN_NEVADA
	call Dualocke_EventScript_PremioIsla
	release
	end

IslaNevada_Cueva_EventScript_PokemonSigue::
	release
	end
