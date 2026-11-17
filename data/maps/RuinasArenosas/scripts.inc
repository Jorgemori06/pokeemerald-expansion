RuinasArenosas_MapScripts::
	.byte 0

@ Dualocke: las RUINAS ARENOSAS (tools/dualocke/crear_desierto_profundo.py)
RuinasArenosas_EventScript_Ramiro::
	trainerbattle_single TRAINER_RAMIRO, RuinasArenosas_Text_RamiroIntro, RuinasArenosas_Text_RamiroDefeat
	msgbox RuinasArenosas_Text_RamiroPostBattle, MSGBOX_AUTOCLOSE
	end

RuinasArenosas_Text_RamiroIntro:
	.string "¡Estas ruinas son mías! ¡Llevo años\n"
	.string "buscándolas!$"

RuinasArenosas_Text_RamiroDefeat:
	.string "¡Me has dejado hecho polvo!$"

RuinasArenosas_Text_RamiroPostBattle:
	.string "Arriba hay una sala sellada. Algo muy\n"
	.string "fuerte la guarda desde hace siglos.$"
