@ Dualocke: el que recuerda movimientos, en todos los Centros Pokémon de Hoenn.
@ Enseña un movimiento que el Pokémon ya pudo aprender subiendo de nivel, a cambio de un
@ Ticket-Recuerdo (ITEM_HEART_SCALE). Los tickets están repartidos por las rutas (colocar_objetos.py).
Dualocke_EventScript_RecuerdaMovimientos::
	lock
	faceplayer
	msgbox Dualocke_Text_RecuerdaHola, MSGBOX_DEFAULT
	checkitem ITEM_HEART_SCALE
	goto_if_eq VAR_RESULT, FALSE, Dualocke_EventScript_RecuerdaSinTicket
	msgbox Dualocke_Text_RecuerdaTienesTicket, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Dualocke_EventScript_RecuerdaAdios
	goto Dualocke_EventScript_RecuerdaElegir
	end

Dualocke_EventScript_RecuerdaElegir::
	msgbox Dualocke_Text_RecuerdaQuePokemon, MSGBOX_DEFAULT
	setmoverelearnerstate MOVE_RELEARNER_LEVEL_UP_MOVES
	chooseboxmon SELECT_PC_MON_MOVE_RELEARNER
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Dualocke_EventScript_RecuerdaAdios
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, Dualocke_EventScript_RecuerdaHuevo
	special Special_HasMoveToRelearn
	goto_if_eq VAR_RESULT, FALSE, Dualocke_EventScript_RecuerdaNada
	msgbox Dualocke_Text_RecuerdaQueMovimiento, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	goto_if_eq VAR_RESULT, FALSE, Dualocke_EventScript_RecuerdaElegir
	removeitem ITEM_HEART_SCALE
	msgbox Dualocke_Text_RecuerdaEntregado, MSGBOX_DEFAULT
	goto Dualocke_EventScript_RecuerdaAdios
	end

Dualocke_EventScript_RecuerdaHuevo::
	msgbox Dualocke_Text_RecuerdaHuevo, MSGBOX_DEFAULT
	goto Dualocke_EventScript_RecuerdaElegir
	end

Dualocke_EventScript_RecuerdaNada::
	msgbox Dualocke_Text_RecuerdaNada, MSGBOX_DEFAULT
	goto Dualocke_EventScript_RecuerdaElegir
	end

Dualocke_EventScript_RecuerdaSinTicket::
	msgbox Dualocke_Text_RecuerdaSinTicket, MSGBOX_DEFAULT
	release
	end

Dualocke_EventScript_RecuerdaAdios::
	msgbox Dualocke_Text_RecuerdaAdios, MSGBOX_DEFAULT
	release
	end

Dualocke_Text_RecuerdaHola:
	.string "¡Hola! Ayudo a los POKéMON a\n"
	.string "recordar movimientos.\p"
	.string "Cualquier movimiento que hayan\n"
	.string "podido aprender subiendo de nivel.\p"
	.string "Por cada uno, cobro un\n"
	.string "TICKET-RECUERDO.$"

Dualocke_Text_RecuerdaSinTicket:
	.string "No llevas ningún TICKET-RECUERDO.\p"
	.string "Hay por todas las rutas de HOENN.\n"
	.string "¡Vuelve cuando encuentres uno!$"

Dualocke_Text_RecuerdaTienesTicket:
	.string "¡Llevas un TICKET-RECUERDO!\p"
	.string "¿Quieres que un POKéMON recuerde\n"
	.string "un movimiento?$"

Dualocke_Text_RecuerdaQuePokemon:
	.string "¿Qué POKéMON tiene que recordar\n"
	.string "un movimiento?$"

Dualocke_Text_RecuerdaQueMovimiento:
	.string "¿Qué movimiento quieres que\n"
	.string "recuerde?$"

Dualocke_Text_RecuerdaHuevo:
	.string "Un HUEVO no tiene nada que\n"
	.string "recordar…$"

Dualocke_Text_RecuerdaNada:
	.string "Ese POKéMON no tiene ningún\n"
	.string "movimiento que recordar.$"

Dualocke_Text_RecuerdaEntregado:
	.string "{PLAYER} ha entregado un\n"
	.string "TICKET-RECUERDO a cambio.$"

Dualocke_Text_RecuerdaAdios:
	.string "¡Vuelve cuando quieras!$"
