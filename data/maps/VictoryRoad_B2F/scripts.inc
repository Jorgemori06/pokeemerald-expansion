VictoryRoad_B2F_MapScripts::
	.byte 0

VictoryRoad_B2F_EventScript_Vito::
	trainerbattle_single TRAINER_VITO, VictoryRoad_B2F_Text_VitoIntro, VictoryRoad_B2F_Text_VitoDefeat
	msgbox VictoryRoad_B2F_Text_VitoPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Owen::
	trainerbattle_single TRAINER_OWEN, VictoryRoad_B2F_Text_OwenIntro, VictoryRoad_B2F_Text_OwenDefeat
	msgbox VictoryRoad_B2F_Text_OwenPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Caroline::
	trainerbattle_single TRAINER_CAROLINE, VictoryRoad_B2F_Text_CarolineIntro, VictoryRoad_B2F_Text_CarolineDefeat
	msgbox VictoryRoad_B2F_Text_CarolinePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Julie::
	trainerbattle_single TRAINER_JULIE, VictoryRoad_B2F_Text_JulieIntro, VictoryRoad_B2F_Text_JulieDefeat
	msgbox VictoryRoad_B2F_Text_JuliePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Felix::
	trainerbattle_single TRAINER_FELIX, VictoryRoad_B2F_Text_FelixIntro, VictoryRoad_B2F_Text_FelixDefeat
	msgbox VictoryRoad_B2F_Text_FelixPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Dianne::
	trainerbattle_single TRAINER_DIANNE, VictoryRoad_B2F_Text_DianneIntro, VictoryRoad_B2F_Text_DianneDefeat
	msgbox VictoryRoad_B2F_Text_DiannePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_Text_VitoIntro:
	.string "¡He entrenado con toda mi familia,\n"
	.string "con todos y cada uno!\l"
	.string "¡No pienso perder contra nadie!$"

VictoryRoad_B2F_Text_VitoDefeat:
	.string "¡¿Mejor que mi familia?!\n"
	.string "¡¿Es posible?!$"

VictoryRoad_B2F_Text_VitoPostBattle:
	.string "Era el mejor de mi familia. Nunca\n"
	.string "había perdido…\p"
	.string "He perdido la confianza…\n"
	.string "A lo mejor me vuelvo a casa…$"

VictoryRoad_B2F_Text_OwenIntro:
	.string "Había oído que por aquí andaba un\n"
	.string "renacuajo muy duro. ¿Eres tú?$"

VictoryRoad_B2F_Text_OwenDefeat:
	.string "¡El renacuajo es duro de verdad!$"

VictoryRoad_B2F_Text_OwenPostBattle:
	.string "Según los rumores, ese renacuajo tan\n"
	.string "duro es de CIUDAD PETALIA.$"

VictoryRoad_B2F_Text_CarolineIntro:
	.string "Ya te debe de pesar el cansancio.$"

VictoryRoad_B2F_Text_CarolineDefeat:
	.string "¡No hay ni rastro de cansancio!$"

VictoryRoad_B2F_Text_CarolinePostBattle:
	.string "La CALLE VICTORIA y la LIGA son\n"
	.string "retos largos y agotadores.\l"
	.string "¡Cuidado con el cansancio!$"

VictoryRoad_B2F_Text_JulieIntro:
	.string "No te confíes solo porque tengas\n"
	.string "muchas MEDALLAS de GIMNASIO.\p"
	.string "¡Siempre habrá alguien mejor que tú!$"

VictoryRoad_B2F_Text_JulieDefeat:
	.string "¡Eres mejor que yo!$"

VictoryRoad_B2F_Text_JuliePostBattle:
	.string "Mira tus MEDALLAS y recuerda a\n"
	.string "quienes te has enfrentado.$"

VictoryRoad_B2F_Text_FelixIntro:
	.string "He llegado hasta aquí, pero los nervios\n"
	.string "me están dando dolor de estómago…$"

VictoryRoad_B2F_Text_FelixDefeat:
	.string "Uf…\n"
	.string "Qué dolor…$"

VictoryRoad_B2F_Text_FelixPostBattle:
	.string "No puedo evitar ponerme tenso al saber\n"
	.string "que estoy cerca de la LIGA POKéMON.\p"
	.string "Bastante hago con fingir que estoy\n"
	.string "tranquilo.$"

VictoryRoad_B2F_Text_DianneIntro:
	.string "En esta cueva se reúne la élite de\n"
	.string "la élite.\p"
	.string "¿Qué te parece?$"

VictoryRoad_B2F_Text_DianneDefeat:
	.string "¡No te inmutas en absoluto!$"

VictoryRoad_B2F_Text_DiannePostBattle:
	.string "¡Tienes agallas! ¡Me gusta!\n"
	.string "¡Sigue así!$"

