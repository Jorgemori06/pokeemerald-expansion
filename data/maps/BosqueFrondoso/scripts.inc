BosqueFrondoso_MapScripts::
	.byte 0

@ Dualocke: el BOSQUE FRONDOSO, al norte del BOSQUE PETALIA (tools/dualocke/crear_bosque_frondoso.py)
BosqueFrondoso_EventScript_CartelMansion::
	msgbox BosqueFrondoso_Text_CartelMansion, MSGBOX_SIGN
	end

BosqueFrondoso_EventScript_Sebas::
	trainerbattle_single TRAINER_SEBAS, BosqueFrondoso_Text_SebasIntro, BosqueFrondoso_Text_SebasDefeat
	msgbox BosqueFrondoso_Text_SebasPostBattle, MSGBOX_AUTOCLOSE
	end

@ OLIVIA es TRAINER_BRENDAN_PLACEHOLDER, que existía sin usar (zonas_nuevas.py le pone nombre y equipo)
BosqueFrondoso_EventScript_Olivia::
	trainerbattle_single TRAINER_BRENDAN_PLACEHOLDER, BosqueFrondoso_Text_OliviaIntro, BosqueFrondoso_Text_OliviaDefeat
	msgbox BosqueFrondoso_Text_OliviaPostBattle, MSGBOX_AUTOCLOSE
	end

BosqueFrondoso_Text_CartelMansion:
	.string "MANSIÓN OLVIDADA\n"
	.string "Nadie vive aquí desde hace años.$"

BosqueFrondoso_Text_SebasIntro:
	.string "¡En este bosque hay bichos que\n"
	.string "no salen en el BOSQUE PETALIA!$"

BosqueFrondoso_Text_SebasDefeat:
	.string "¡Mis bichos se han escondido!$"

BosqueFrondoso_Text_SebasPostBattle:
	.string "Dicen que en la mansión hay\n"
	.string "fantasmas. Yo no entro…$"

BosqueFrondoso_Text_OliviaIntro:
	.string "¡Qué sitio tan bonito para\n"
	.string "un combate!$"

BosqueFrondoso_Text_OliviaDefeat:
	.string "Me lo he pasado bien igual.$"

BosqueFrondoso_Text_OliviaPostBattle:
	.string "Con una caña se puede pescar\n"
	.string "en la charca. ¡Pruébalo!$"
