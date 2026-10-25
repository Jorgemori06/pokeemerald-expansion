AbandonedShip_Corridors_1F_MapScripts::
	.byte 0

AbandonedShip_Corridors_1F_EventScript_Youngster::
	msgbox AbandonedShip_Corridors_1F_Text_IsntItFunHere, MSGBOX_NPC
	end

AbandonedShip_Corridors_1F_EventScript_Charlie::
	trainerbattle_single TRAINER_CHARLIE, AbandonedShip_Corridors_1F_Text_CharlieIntro, AbandonedShip_Corridors_1F_Text_CharlieDefeat
	msgbox AbandonedShip_Corridors_1F_Text_CharliePostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Corridors_1F_Text_CharlieIntro:
	.string "¿Qué tiene de gracioso traerme el\n"
	.string "flotador al barco?$"

AbandonedShip_Corridors_1F_Text_CharlieDefeat:
	.string "¡Uau, me has arrollado!$"

AbandonedShip_Corridors_1F_Text_CharliePostBattle:
	.string "¡No es fácil lanzar POKé BALLS\n"
	.string "agarrado a un flotador!$"

AbandonedShip_Corridors_1F_Text_IsntItFunHere:
	.string "¿A que esto es divertido?\n"
	.string "¡Solo de estar aquí me emociono!$"
