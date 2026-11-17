MarismaAzuliza_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MarismaAzuliza_OnTransition
	.byte 0

@ Dualocke: la MARISMA AZULIZA, al oeste de PUEBLO AZULIZA (tools/dualocke/crear_marisma_azuliza.py).
@ Dondozo y Tatsugiri están en la cala del otro lado del lago: hace falta SURF. Son Pokémon fuertes que se
@ pueden capturar, como los de las islas del ferry (data/scripts/dualocke_islas.inc); con semilla salen otros.
MarismaAzuliza_OnTransition:
	setvar VAR_0x8004, SPECIES_DONDOZO
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_0, VAR_RESULT
	setvar VAR_0x8004, SPECIES_TATSUGIRI
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_1, VAR_RESULT
	end

MarismaAzuliza_EventScript_Dondozo::
	lock
	setvar VAR_TEMP_8, SPECIES_DONDOZO
	setvar VAR_TEMP_9, ITEM_ROCKY_HELMET
	call Dualocke_EventScript_AvisoIsla
	setwildbattle SPECIES_DONDOZO, 59
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, MarismaAzuliza_EventScript_PokemonSigue
	setflag FLAG_DUALOCKE_MARISMA_DONDOZO
	call Dualocke_EventScript_PremioIsla
	release
	end

MarismaAzuliza_EventScript_Tatsugiri::
	lock
	setvar VAR_TEMP_8, SPECIES_TATSUGIRI
	setvar VAR_TEMP_9, ITEM_MYSTIC_WATER
	call Dualocke_EventScript_AvisoIsla
	setwildbattle SPECIES_TATSUGIRI, 59
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, MarismaAzuliza_EventScript_PokemonSigue
	setflag FLAG_DUALOCKE_MARISMA_TATSUGIRI
	call Dualocke_EventScript_PremioIsla
	release
	end

MarismaAzuliza_EventScript_PokemonSigue::
	release
	end

MarismaAzuliza_EventScript_Cartel::
	msgbox MarismaAzuliza_Text_Cartel, MSGBOX_SIGN
	end

MarismaAzuliza_EventScript_Tomas::
	trainerbattle_single TRAINER_TOMAS, MarismaAzuliza_Text_TomasIntro, MarismaAzuliza_Text_TomasDefeat
	msgbox MarismaAzuliza_Text_TomasPostBattle, MSGBOX_AUTOCLOSE
	end

MarismaAzuliza_EventScript_Margarita::
	trainerbattle_single TRAINER_MARGARITA, MarismaAzuliza_Text_MargaritaIntro, MarismaAzuliza_Text_MargaritaDefeat
	msgbox MarismaAzuliza_Text_MargaritaPostBattle, MSGBOX_AUTOCLOSE
	end

MarismaAzuliza_Text_Cartel:
	.string "MARISMA AZULIZA\n"
	.string "Aquí siempre llueve. ¡No te mojes!$"

MarismaAzuliza_Text_TomasIntro:
	.string "¡Shh! Que se me espantan los peces.\n"
	.string "Bueno, ya que estás… ¡combate!$"

MarismaAzuliza_Text_TomasDefeat:
	.string "Hoy no pican ni los combates…$"

MarismaAzuliza_Text_TomasPostBattle:
	.string "Al otro lado del lago vive un\n"
	.string "POKéMON enorme. Sin SURF, ni lo veas.$"

MarismaAzuliza_Text_MargaritaIntro:
	.string "Con la lluvia, las flores huelen\n"
	.string "mejor. ¿Lo notas?$"

MarismaAzuliza_Text_MargaritaDefeat:
	.string "Qué combate tan fresco.$"

MarismaAzuliza_Text_MargaritaPostBattle:
	.string "En la hierba muy alta se esconden\n"
	.string "muchos POKéMON de pantano.$"
