MansionOlvidada_MapScripts::
	.byte 0

@ Dualocke: la MANSIÓN OLVIDADA, en el BOSQUE FRONDOSO (tools/dualocke/crear_bosque_frondoso.py)
MansionOlvidada_EventScript_PuertaAtascada::
	msgbox MansionOlvidada_Text_PuertaAtascada, MSGBOX_SIGN
	end

@ ELVIRA es TRAINER_MAY_PLACEHOLDER y ALFONSO es TRAINER_LEAF: existían sin usar
MansionOlvidada_EventScript_Elvira::
	trainerbattle_single TRAINER_MAY_PLACEHOLDER, MansionOlvidada_Text_ElviraIntro, MansionOlvidada_Text_ElviraDefeat
	msgbox MansionOlvidada_Text_ElviraPostBattle, MSGBOX_AUTOCLOSE
	end

MansionOlvidada_EventScript_Alfonso::
	trainerbattle_single TRAINER_LEAF, MansionOlvidada_Text_AlfonsoIntro, MansionOlvidada_Text_AlfonsoDefeat
	msgbox MansionOlvidada_Text_AlfonsoPostBattle, MSGBOX_AUTOCLOSE
	end

MansionOlvidada_Text_PuertaAtascada:
	.string "La puerta está atascada.\n"
	.string "No se abre.$"

MansionOlvidada_Text_ElviraIntro:
	.string "Los espíritus de esta casa\n"
	.string "quieren conocerte…$"

MansionOlvidada_Text_ElviraDefeat:
	.string "Los espíritus están contentos…$"

MansionOlvidada_Text_ElviraPostBattle:
	.string "Arriba hay algo muy fuerte.\n"
	.string "Lo noto desde aquí…$"

MansionOlvidada_Text_AlfonsoIntro:
	.string "Antes esta casa era mía.\n"
	.string "Ahora es de los fantasmas.$"

MansionOlvidada_Text_AlfonsoDefeat:
	.string "Qué combate tan elegante.$"

MansionOlvidada_Text_AlfonsoPostBattle:
	.string "La puerta de esta sala lleva\n"
	.string "años atascada.$"
