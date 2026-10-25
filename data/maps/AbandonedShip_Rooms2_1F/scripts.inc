AbandonedShip_Rooms2_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms2_1F_EventScript_Dan::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanIntro, AbandonedShip_Rooms2_1F_Text_DanDefeat, AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterDan
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms2_1F_EventScript_DanRematch
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterDan::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT  @ Kira speaks for both when registering KiraAndDan
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_DanRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanRematchIntro, AbandonedShip_Rooms2_1F_Text_DanRematchDefeat, AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Kira::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraIntro, AbandonedShip_Rooms2_1F_Text_KiraDefeat, AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterKira
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms2_1F_EventScript_KiraRematch
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterKira::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_KiraRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraRematchIntro, AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat, AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Jani::
	trainerbattle_single TRAINER_JANI, AbandonedShip_Rooms2_1F_Text_JaniIntro, AbandonedShip_Rooms2_1F_Text_JaniDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_JaniPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Garrison::
	trainerbattle_single TRAINER_GARRISON, AbandonedShip_Rooms2_1F_Text_GarrisonIntro, AbandonedShip_Rooms2_1F_Text_GarrisonDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_Text_DanIntro:
	.string "DAN: ¡Buscando tesoros, hemos\n"
	.string "encontrado a un ENTRENADOR!$"

AbandonedShip_Rooms2_1F_Text_DanDefeat:
	.string "DAN: No hemos podido ganar ni\n"
	.string "yendo juntos…$"

AbandonedShip_Rooms2_1F_Text_DanPostBattle:
	.string "DAN: No encontramos ningún tesoro…\n"
	.string "¿Se los habrá llevado alguien?$"

AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons:
	.string "DAN: Ni siquiera tienes dos POKéMON.\n"
	.string "Así no esperarás ganarnos.$"

AbandonedShip_Rooms2_1F_Text_KiraIntro:
	.string "KIRA: ¿Oh?\n"
	.string "Estábamos buscando tesoros.\l"
	.string "¡Pero hemos encontrado a alguien!$"

AbandonedShip_Rooms2_1F_Text_KiraDefeat:
	.string "KIRA: ¡Uh, qué fuerte!$"

AbandonedShip_Rooms2_1F_Text_KiraPostBattle:
	.string "KIRA: ¿Dónde estarán los tesoros?\p"
	.string "¡Ya he decidido qué me compraré\n"
	.string "cuando los encontremos!$"

AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons:
	.string "KIRA: ¿Oh, no tienes dos POKéMON?\n"
	.string "¡Tendremos que combatir otro día!$"

AbandonedShip_Rooms2_1F_Text_KiraRegister:
	.string "KIRA: ¡Oh, qué rabia me das!\n"
	.string "¡Por eso te voy a registrar!$"

AbandonedShip_Rooms2_1F_Text_DanRematchIntro:
	.string "DAN: Llevamos todo este tiempo\n"
	.string "buscando tesoros.\p"
	.string "Nuestros POKéMON también se han hecho\n"
	.string "más fuertes. Te lo enseñamos, ¿vale?$"

AbandonedShip_Rooms2_1F_Text_DanRematchDefeat:
	.string "DAN: ¡Tan fuerte como siempre!$"

AbandonedShip_Rooms2_1F_Text_DanPostRematch:
	.string "DAN: No encontramos tesoros, perdemos\n"
	.string "con los POKéMON…\p"
	.string "Quiero irme a casa… Pero si lo digo,\n"
	.string "ella se enfada conmigo…$"

AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons:
	.string "DAN: Ni siquiera tienes dos POKéMON.\n"
	.string "Así no esperarás ganarnos.$"

AbandonedShip_Rooms2_1F_Text_KiraRematchIntro:
	.string "KIRA: ¿Oh? ¡Otra vez nos vemos!\p"
	.string "Como nosotros, sigues sin dejar de\n"
	.string "buscar tesoros, ¿verdad?\p"
	.string "¿Y si quien pierda deja de buscar?$"

AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat:
	.string "KIRA: Oh, hemos vuelto a perder…$"

AbandonedShip_Rooms2_1F_Text_KiraPostRematch:
	.string "KIRA: ¡No nos vamos hasta que\n"
	.string "entrenemos más a nuestros POKéMON\l"
	.string "y encontremos los tesoros!$"

AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons:
	.string "KIRA: ¿Oh, no tienes dos POKéMON?\n"
	.string "¡Tendremos que combatir otro día!$"

AbandonedShip_Rooms2_1F_Text_JaniIntro:
	.string "No se me da bien nadar,\n"
	.string "¡pero combatir sí!$"

AbandonedShip_Rooms2_1F_Text_JaniDefeat:
	.string "Huy.\n"
	.string "No ha salido muy bien.$"

AbandonedShip_Rooms2_1F_Text_JaniPostBattle:
	.string "Ir descalza por este barco da un\n"
	.string "poco de asco.$"

AbandonedShip_Rooms2_1F_Text_GarrisonIntro:
	.string "Fuerza y compasión…\n"
	.string "¡Esos son los tesoros de quien entrena!$"

AbandonedShip_Rooms2_1F_Text_GarrisonDefeat:
	.string "Ah, hay algo en ti que brilla.$"

AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle:
	.string "En algún camarote del barco he visto\n"
	.string "algo que brillaba.$"
