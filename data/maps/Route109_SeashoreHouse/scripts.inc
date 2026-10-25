Route109_SeashoreHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route109_SeashoreHouse_OnTransition
	.byte 0

Route109_SeashoreHouse_OnTransition:
	setflag FLAG_LANDMARK_SEASHORE_HOUSE
	end

Route109_SeashoreHouse_EventScript_Owner::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_6_SODA_POP, Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop
	goto_if_set FLAG_DEFEATED_SEASHORE_HOUSE, Route109_SeashoreHouse_EventScript_DefeatedTrainers
	goto_if_set FLAG_TEMP_2, Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction
	msgbox Route109_SeashoreHouse_Text_SeashoreHouseIntro, MSGBOX_DEFAULT
	setflag FLAG_TEMP_2
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction::
	msgbox Route109_SeashoreHouse_Text_ShowMeSomeHotMatches, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_DefeatedTrainers::
	msgbox Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles, MSGBOX_DEFAULT
	giveitem ITEM_SODA_POP, 6
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_BagFull
	setflag FLAG_RECEIVED_6_SODA_POP
	release
	end

Route109_SeashoreHouse_EventScript_BagFull::
	msgbox Route109_SeashoreHouse_Text_BagFull, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop::
	showmoneybox 0, 0
	msgbox Route109_SeashoreHouse_Text_WantToBuySodaPop, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route109_SeashoreHouse_EventScript_BuySodaPop
	msgbox Route109_SeashoreHouse_Text_ThatsTooBad, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_BuySodaPop::
	checkmoney 300
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughMoney
	checkitemspace ITEM_SODA_POP
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughSpace
	msgbox Route109_SeashoreHouse_Text_HereYouGo, MSGBOX_DEFAULT
	removemoney 300
	updatemoneybox
.if OW_SHOW_ITEM_DESCRIPTIONS != OW_ITEM_DESCRIPTIONS_OFF
	hidemoneybox
	giveitem ITEM_SODA_POP
.else
	giveitem ITEM_SODA_POP
	hidemoneybox
.endif
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughMoney::
	msgbox Route109_SeashoreHouse_Text_NotEnoughMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughSpace::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_Dwayne::
	trainerbattle_single TRAINER_DWAYNE, Route109_SeashoreHouse_Text_DwayneIntro, Route109_SeashoreHouse_Text_DwayneDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_DwaynePostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Johanna::
	trainerbattle_single TRAINER_JOHANNA, Route109_SeashoreHouse_Text_JohannaIntro, Route109_SeashoreHouse_Text_JohannaDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_JohannaPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Simon::
	trainerbattle_single TRAINER_SIMON, Route109_SeashoreHouse_Text_SimonIntro, Route109_SeashoreHouse_Text_SimonDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_SimonPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_CheckTrainersCompletion::
	goto_if_not_defeated TRAINER_DWAYNE, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_JOHANNA, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_SIMON, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	setflag FLAG_DEFEATED_SEASHORE_HOUSE
	release
	end

Route109_SeashoreHouse_EventScript_TrainersNotCompleted::
	release
	end

Route109_SeashoreHouse_Text_SeashoreHouseIntro:
	.string "Soy el dueño de la CASA DE LA PLAYA.\n"
	.string "¡Pero puedes llamarme SR. MAR!\p"
	.string "Lo que más me gusta es ver combates\n"
	.string "POKéMON con mucha chispa.\p"
	.string "¡Demuéstrame que tu corazón arde!\p"
	.string "Si vences a todos los ENTRENADORES\n"
	.string "de aquí, te daré un premio.$"

Route109_SeashoreHouse_Text_ShowMeSomeHotMatches:
	.string "¡Enséñame combates con chispa!\p"
	.string "¡Llevo esta CASA DE LA PLAYA solo\n"
	.string "por eso!$"

Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles:
	.string "¡Estás que ardes!\n"
	.string "¡Esos combates han sido de fuego!\l"
	.string "¡Estoy más que satisfecho!\p"
	.string "Para darte las gracias por tu racha,\n"
	.string "quiero que te quedes esto.\p"
	.string "¡Media docena de botellas de\n"
	.string "REFRESCO!$"

Route109_SeashoreHouse_Text_BagFull:
	.string "Pero, oye, tienes la MOCHILA llena.\n"
	.string "Te las guardo yo.$"

Route109_SeashoreHouse_Text_WantToBuySodaPop:
	.string "¿Quieres comprar REFRESCOS?\n"
	.string "¡A los POKéMON les encantan!\p"
	.string "¡Solo ¥300 la botella!\n"
	.string "¡Compra alguno!$"

Route109_SeashoreHouse_Text_HereYouGo:
	.string "¡Aquí tienes!$"

Route109_SeashoreHouse_Text_NotEnoughMoney:
	.string "No tienes dinero.$"

Route109_SeashoreHouse_Text_ThatsTooBad:
	.string "¿No?\n"
	.string "Qué pena.$"

Route109_SeashoreHouse_Text_DwayneIntro:
	.string "¡Si buscas combate en la CASA DE LA\n"
	.string "PLAYA, no encontrarás a nadie con\l"
	.string "más fuego que yo, colega!$"

Route109_SeashoreHouse_Text_DwayneDefeated:
	.string "¡Qué combate más ardiente!\n"
	.string "¡Acepto la derrota, colega!$"

Route109_SeashoreHouse_Text_DwaynePostBattle:
	.string "¡Cuando estoy en PORTUAL, disfruto\n"
	.string "de combates ardientes y REFRESCOS\l"
	.string "bien fríos!$"

Route109_SeashoreHouse_Text_JohannaIntro:
	.string "Los combates aburridos no valen\n"
	.string "la pena.\p"
	.string "¡Los combates ardientes son los\n"
	.string "que curten a ENTRENADORES y POKéMON!$"

Route109_SeashoreHouse_Text_JohannaDefeated:
	.string "¡Qué calor!$"

Route109_SeashoreHouse_Text_JohannaPostBattle:
	.string "Uf, qué sed.\n"
	.string "Creo que me tomaré un REFRESCO.$"

Route109_SeashoreHouse_Text_SimonIntro:
	.string "Te voy a enseñar lo geniales que son\n"
	.string "mis POKéMON, ¡pero no llores!$"

Route109_SeashoreHouse_Text_SimonDefeated:
	.string "…He perdido, pero no voy a llorar…$"

Route109_SeashoreHouse_Text_SimonPostBattle:
	.string "Si uno de mis POKéMON supiera el\n"
	.string "movimiento para llevarme por el agua,\l"
	.string "podría dejar este flotador.$"

