Route111_Text_MakingRoomUseTMToMakeYourOwn:
	.string "¿Qué pasa?\n"
	.string "¿Que qué hago?\p"
	.string "Estoy pensando en hacerme un cuarto\n"
	.string "aquí con un movimiento POKéMON.\p"
	.string "¡Ya sé! Te doy esta MT.\n"
	.string "¿La usarás para hacerte tu cuarto?$"

Route111_Text_ExplainSecretPower:
	.string "Busca un árbol grande que parezca que\n"
	.string "puede soltar lianas.\p"
	.string "Usa DAÑO SECRETO delante del árbol.\n"
	.string "Caerán unas lianas y podrás subir.\p"
	.string "Encontrarás mucho sitio para poner\n"
	.string "tus cosas favoritas.\p"
	.string "Será tu cuarto secreto…\n"
	.string "¡Una BASE SECRETA!\p"
	.string "Deberías hacerte una.\p"
	.string "Otra cosa: la BASE SECRETA no tiene\n"
	.string "por qué estar en un árbol.\p"
	.string "Prueba a usar DAÑO SECRETO en paredes\n"
	.string "de roca con pequeños huecos.\p"
	.string "Yo también buscaré otros sitios.\n"
	.string "¡Vale, adiós!$"

Route111_Text_DontWantThis:
	.string "¿Oh, no la quieres?\n"
	.string "Si cambias de idea, dímelo, ¿vale?$"

Route111_Text_DontHaveAnyRoom:
	.string "Oh, no tienes sitio para esto.\p"
	.string "Te la guardo, así que vuelve a por\n"
	.string "ella otro día, ¿vale?$"

Route111_EventScript_SecretPowerMan::
	lock
	faceplayer
	msgbox Route111_Text_MakingRoomUseTMToMakeYourOwn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route111_EventScript_GiveSecretPower
	msgbox Route111_Text_DontWantThis, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_GiveSecretPower::
	giveitem ITEM_TM_SECRET_POWER
	goto_if_eq VAR_RESULT, FALSE, Route111_EventScript_NoRoomForSecretPower
	msgbox Route111_Text_ExplainSecretPower, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_RECEIVED_SECRET_POWER
	clearflag FLAG_HIDE_SLATEPORT_CITY_TM_SALESMAN
	call_if_eq VAR_FACING, DIR_WEST, Route111_EventScript_SecretPowerManExit
	call_if_eq VAR_FACING, DIR_EAST, Route111_EventScript_SecretPowerManExit
	call_if_eq VAR_FACING, DIR_NORTH, Route111_EventScript_SecretPowerManExitNorth
	removeobject VAR_LAST_TALKED
	release
	end

Route111_EventScript_SecretPowerManExit::
	applymovement VAR_LAST_TALKED, Route111_Movement_SecretPowerManExit
	waitmovement 0
	return

Route111_EventScript_SecretPowerManExitNorth::
	applymovement VAR_LAST_TALKED, Route111_Movement_SecretPowerManExitNorth
	waitmovement 0
	return

Route111_EventScript_NoRoomForSecretPower::
	msgbox Route111_Text_DontHaveAnyRoom, MSGBOX_DEFAULT
	release
	end

Route111_Movement_SecretPowerManExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

Route111_Movement_SecretPowerManExitNorth:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end
