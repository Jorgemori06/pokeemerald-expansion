VictoryRoad_B1F_MapScripts::
	.byte 0

VictoryRoad_B1F_EventScript_Samuel::
	trainerbattle_single TRAINER_SAMUEL, VictoryRoad_B1F_Text_SamuelIntro, VictoryRoad_B1F_Text_SamuelDefeat
	msgbox VictoryRoad_B1F_Text_SamuelPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Shannon::
	trainerbattle_single TRAINER_SHANNON, VictoryRoad_B1F_Text_ShannonIntro, VictoryRoad_B1F_Text_ShannonDefeat
	msgbox VictoryRoad_B1F_Text_ShannonPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Michelle::
	trainerbattle_single TRAINER_MICHELLE, VictoryRoad_B1F_Text_MichelleIntro, VictoryRoad_B1F_Text_MichelleDefeat
	msgbox VictoryRoad_B1F_Text_MichellePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Mitchell::
	trainerbattle_single TRAINER_MITCHELL, VictoryRoad_B1F_Text_MitchellIntro, VictoryRoad_B1F_Text_MitchellDefeat
	msgbox VictoryRoad_B1F_Text_MitchellPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Halle::
	trainerbattle_single TRAINER_HALLE, VictoryRoad_B1F_Text_HalleIntro, VictoryRoad_B1F_Text_HalleDefeat
	msgbox VictoryRoad_B1F_Text_HallePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_Text_SamuelIntro:
	.string "Pensar que me acerco a la LIGA\n"
	.string "POKéMON…\p"
	.string "Me está entrando pánico escénico…$"

VictoryRoad_B1F_Text_SamuelDefeat:
	.string "No he podido hacer nada…$"

VictoryRoad_B1F_Text_SamuelPostBattle:
	.string "La LIGA POKéMON vuelve a quedar\n"
	.string "lejos… Qué decepción…$"

VictoryRoad_B1F_Text_ShannonIntro:
	.string "Para abrirte paso en la LIGA POKéMON,\n"
	.string "necesitas la confianza de tus\l"
	.string "POKéMON.$"

VictoryRoad_B1F_Text_ShannonDefeat:
	.string "Vuestra relación se basa en una\n"
	.string "confianza sólida.$"

VictoryRoad_B1F_Text_ShannonPostBattle:
	.string "Estando siempre juntos, crece la\n"
	.string "confianza entre POKéMON y quien\n"
	.string "los entrena.$"

VictoryRoad_B1F_Text_MichelleIntro:
	.string "Esto no es la meta. Solo es un punto\n"
	.string "del camino hacia la LIGA POKéMON.$"

VictoryRoad_B1F_Text_MichelleDefeat:
	.string "¡Así se hace!$"

VictoryRoad_B1F_Text_MichellePostBattle:
	.string "¡Te irá bien, seguro!\n"
	.string "¡Tus POKéMON están deseando seguir!$"

VictoryRoad_B1F_Text_MitchellIntro:
	.string "¡Mis POKéMON son de una grandeza\n"
	.string "cósmica!$"

VictoryRoad_B1F_Text_MitchellDefeat:
	.string "Nunca había conocido a nadie como tú.$"

VictoryRoad_B1F_Text_MitchellPostBattle:
	.string "Incluso fuera del combate, noto un\n"
	.string "poder increíble que sale de ti y de\l"
	.string "tus POKéMON.$"

VictoryRoad_B1F_Text_HalleIntro:
	.string "¡Vale, no hace falta ponerse tenso!\n"
	.string "¡Relájate, con calma!$"

VictoryRoad_B1F_Text_HalleDefeat:
	.string "¡Uau!\n"
	.string "¡Maravilloso!$"

VictoryRoad_B1F_Text_HallePostBattle:
	.string "Sí, esto es la CALLE VICTORIA.\p"
	.string "Pero no es tan distinto del camino\n"
	.string "que has recorrido hasta ahora.\p"
	.string "¡Intenta disfrutar el resto del\n"
	.string "camino!$"

