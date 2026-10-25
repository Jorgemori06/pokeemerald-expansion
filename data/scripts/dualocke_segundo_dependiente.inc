@ Dualocke: segundo dependiente de las tiendas de ciudad (src/dualocke_segundo_dependiente.c).
@ Vende 1 objeto evolutivo y 3 equipables al azar, distintos en cada partida.
Dualocke_EventScript_SegundoDependiente::
	lock
	faceplayer
	msgbox Dualocke_Text_SegundoDependiente, MSGBOX_DEFAULT
	special Dualocke_AbrirSegundoDependiente
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

Dualocke_Text_SegundoDependiente:
	.string "¡Hola! Vendo objetos raros traídos\n"
	.string "de todo HOENN.\p"
	.string "¿Qué quieres?$"
