MarismaAzuliza_MapScripts::
	.byte 0

@ Dualocke: la MARISMA AZULIZA, al oeste de PUEBLO AZULIZA (tools/dualocke/crear_marisma_azuliza.py)
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
	.string "Con la CAÑA VIEJA se pesca en las\n"
	.string "charcas. Te la dan en AZULIZA.$"

MarismaAzuliza_Text_MargaritaIntro:
	.string "Con la lluvia, las flores huelen\n"
	.string "mejor. ¿Lo notas?$"

MarismaAzuliza_Text_MargaritaDefeat:
	.string "Qué combate tan fresco.$"

MarismaAzuliza_Text_MargaritaPostBattle:
	.string "En la hierba alta se esconden\n"
	.string "muchos POKéMON de pantano.$"
