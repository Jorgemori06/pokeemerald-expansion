GrutaIgnea_MapScripts::
	.byte 0

@ Dualocke: la GRUTA ÍGNEA, debajo del SENDERO ÍGNEO (tools/dualocke/crear_gruta_ignea.py; ZONAS.md)
GrutaIgnea_EventScript_Roque::
	trainerbattle_single TRAINER_ROQUE, GrutaIgnea_Text_RoqueIntro, GrutaIgnea_Text_RoqueDefeat
	msgbox GrutaIgnea_Text_RoquePostBattle, MSGBOX_AUTOCLOSE
	end

GrutaIgnea_EventScript_Igor::
	trainerbattle_single TRAINER_IGOR, GrutaIgnea_Text_IgorIntro, GrutaIgnea_Text_IgorDefeat
	msgbox GrutaIgnea_Text_IgorPostBattle, MSGBOX_AUTOCLOSE
	end

GrutaIgnea_EventScript_Soldado::
	trainerbattle_single TRAINER_GRUNT_UNUSED, GrutaIgnea_Text_SoldadoIntro, GrutaIgnea_Text_SoldadoDefeat
	msgbox GrutaIgnea_Text_SoldadoPostBattle, MSGBOX_AUTOCLOSE
	end

GrutaIgnea_Text_RoqueIntro:
	.string "¡Llevo días bajando por esta gruta!\n"
	.string "¡Por fin alguien con quien combatir!$"

GrutaIgnea_Text_RoqueDefeat:
	.string "¡Uf! Me vuelvo arriba a por agua.$"

GrutaIgnea_Text_RoquePostBattle:
	.string "Dicen que esta gruta se abrió cuando\n"
	.string "el volcán despertó.$"

GrutaIgnea_Text_IgorIntro:
	.string "¡Aquí abajo el calor derrite las\n"
	.string "zapatillas! ¡Y mis POKéMON, también!$"

GrutaIgnea_Text_IgorDefeat:
	.string "¡Me he quedado frío!$"

GrutaIgnea_Text_IgorPostBattle:
	.string "La lava no se puede cruzar. Hay que\n"
	.string "dar toda la vuelta al lago.$"

GrutaIgnea_Text_SoldadoIntro:
	.string "¡Eh! ¡El EQUIPO MAGMA sigue\n"
	.string "estudiando el volcán! ¡Largo!$"

GrutaIgnea_Text_SoldadoDefeat:
	.string "¡Me he quemado yo sola!$"

GrutaIgnea_Text_SoldadoPostBattle:
	.string "Los jefes se fueron hace tiempo,\n"
	.string "pero a mí nadie me avisó…$"
