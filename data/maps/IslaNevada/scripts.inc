IslaNevada_MapScripts::
	.byte 0

@ Dualocke: la ISLA NEVADA, al norte de la RUTA 124 (tools/dualocke/crear_isla_nevada.py; ZONAS.md)
IslaNevada_EventScript_Dudley::
	trainerbattle_single TRAINER_DUDLEY, IslaNevada_Text_DudleyIntro, IslaNevada_Text_DudleyDefeat
	msgbox IslaNevada_Text_DudleyPostBattle, MSGBOX_AUTOCLOSE
	end

IslaNevada_EventScript_Kaylee::
	trainerbattle_single TRAINER_KAYLEE, IslaNevada_Text_KayleeIntro, IslaNevada_Text_KayleeDefeat
	msgbox IslaNevada_Text_KayleePostBattle, MSGBOX_AUTOCLOSE
	end

IslaNevada_Text_DudleyIntro:
	.string "¡Brrr! Nadar con nieve endurece\n"
	.string "el cuerpo… ¡y a los POKéMON!$"

IslaNevada_Text_DudleyDefeat:
	.string "¡Me he quedado helado!$"

IslaNevada_Text_DudleyPostBattle:
	.string "En el islote hay una cueva llena\n"
	.string "de hielo. ¡Cuidado, que resbala!$"

IslaNevada_Text_KayleeIntro:
	.string "¿Sabías que en esta isla nieva\n"
	.string "todo el año?$"

IslaNevada_Text_KayleeDefeat:
	.string "¡Qué frío de derrota!$"

IslaNevada_Text_KayleePostBattle:
	.string "Con la nieve, los POKéMON de hielo\n"
	.string "aguantan mucho más.$"
