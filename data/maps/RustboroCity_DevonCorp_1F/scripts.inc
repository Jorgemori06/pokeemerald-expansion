RustboroCity_DevonCorp_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_1F_OnTransition
	.byte 0

RustboroCity_DevonCorp_1F_OnTransition:
	call_if_unset FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_BlockStairs
	end

RustboroCity_DevonCorp_1F_EventScript_BlockStairs::
	setobjectxyperm LOCALID_DEVON_CORP_STAIR_GUARD, 14, 2
	setobjectmovementtype LOCALID_DEVON_CORP_STAIR_GUARD, MOVEMENT_TYPE_FACE_DOWN
	return

RustboroCity_DevonCorp_1F_EventScript_Employee::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright
	msgbox RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright::
	msgbox RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered::
	msgbox RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StairGuard::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome::
	msgbox RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GotRobbed::
	msgbox RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_Greeter::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp::
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed::
	msgbox RustboroCity_DevonCorp_1F_Text_StaffGotRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RocksMetalDisplay::
	msgbox RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_EventScript_ProductsDisplay::
	msgbox RustboroCity_DevonCorp_1F_Text_ProductDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp:
	.string "Hola, te damos la bienvenida a la\n"
	.string "CORPORACIÓN DEVON.\p"
	.string "Fabricamos con orgullo objetos y\n"
	.string "medicinas que mejoran tu vida.$"

RustboroCity_DevonCorp_1F_Text_StaffGotRobbed:
	.string "A uno de nuestros investigadores le han\n"
	.string "robado un paquete. ¡Qué torpe!$"

RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct:
	.string "¡Eh, esas DEPORTIVAS!\n"
	.string "¡Son un producto nuestro!\p"
	.string "Me alegra ver a alguien usando\n"
	.string "algo que hemos fabricado.$"

RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright:
	.string "Ese paquete robado…\p"
	.string "Bueno, es importante, pero nadie\n"
	.string "más puede usarlo.\p"
	.string "Yo diría que ese ladrón no era\n"
	.string "muy listo.$"

RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered:
	.string "Parece que han recuperado las\n"
	.string "PIEZAS DEVON robadas.$"

RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter:
	.string "Lo siento, aquí solo puede entrar\n"
	.string "el personal autorizado.$"

RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed:
	.string "Es el colmo.\n"
	.string "¿Cómo han podido robarnos?$"

RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere:
	.string "¡Hola!\n"
	.string "¡Aquí siempre se te recibe con gusto!$"

RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay:
	.string "En la vitrina hay muestras de rocas\n"
	.string "y metales.\p"
	.string "Hay un panel con algo escrito…\p"
	.string "“La CORPORACIÓN DEVON empezó\n"
	.string "sacando piedra de canteras.\p"
	.string "”También sacaba hierro de las\n"
	.string "limaduras de la arena.\p"
	.string "”Desde ese humilde comienzo como\n"
	.string "productora de materias primas, DEVON\l"
	.string "creció.\p"
	.string "”Hoy DEVON fabrica una gran variedad\n"
	.string "de productos industriales”.$"

RustboroCity_DevonCorp_1F_Text_ProductDisplay:
	.string "La vitrina está llena de prototipos\n"
	.string "y productos de prueba.\p"
	.string "Hay un panel con una descripción…\p"
	.string "“Además de productos industriales,\n"
	.string "DEVON vende artículos y medicinas\l"
	.string "para vivir mejor.\p"
	.string "”Hace poco, DEVON ha empezado a vender\n"
	.string "herramientas para ENTRENADORES, como\l"
	.string "las POKé BALLS y el POKéNAV”.$"

