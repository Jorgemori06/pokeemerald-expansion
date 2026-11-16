IslaNevada_Cueva_MapScripts::
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
