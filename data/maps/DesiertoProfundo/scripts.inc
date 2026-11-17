DesiertoProfundo_MapScripts::
	.byte 0

@ Dualocke: el DESIERTO PROFUNDO, al este del desierto de la RUTA 111 (tools/dualocke/crear_desierto_profundo.py)
DesiertoProfundo_EventScript_Soledad::
	trainerbattle_single TRAINER_SOLEDAD, DesiertoProfundo_Text_SoledadIntro, DesiertoProfundo_Text_SoledadDefeat
	msgbox DesiertoProfundo_Text_SoledadPostBattle, MSGBOX_AUTOCLOSE
	end

DesiertoProfundo_Text_SoledadIntro:
	.string "Aquí la arena no para nunca.\n"
	.string "¿Aguantarás la tormenta?$"

DesiertoProfundo_Text_SoledadDefeat:
	.string "Has aguantado mejor que yo.$"

DesiertoProfundo_Text_SoledadPostBattle:
	.string "En el norte hay unas ruinas medio\n"
	.string "enterradas. Dicen que algo las vigila.$"
