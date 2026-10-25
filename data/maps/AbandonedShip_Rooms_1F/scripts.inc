AbandonedShip_Rooms_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms_1F_EventScript_Gentleman::
	msgbox AbandonedShip_Rooms_1F_Text_TakingALookAround, MSGBOX_NPC
	end

AbandonedShip_Rooms_1F_EventScript_Demetrius::
	trainerbattle_single TRAINER_DEMETRIUS, AbandonedShip_Rooms_1F_Text_DemetriusIntro, AbandonedShip_Rooms_1F_Text_DemetriusDefeat
	msgbox AbandonedShip_Rooms_1F_Text_DemetriusPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_EventScript_Thalia::
	trainerbattle_single TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaIntro, AbandonedShip_Rooms_1F_Text_ThaliaDefeat, AbandonedShip_Rooms_1F_EventScript_RegisterThalia
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms_1F_EventScript_ThaliaRematch
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms_1F_EventScript_RegisterThalia::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_THALIA_1
	release
	end

AbandonedShip_Rooms_1F_EventScript_ThaliaRematch::
	trainerbattle_rematch TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro, AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_Text_TakingALookAround:
	.string "Los barcos así son raros, así que\n"
	.string "estoy echando un vistazo.\p"
	.string "Mmm…\n"
	.string "Parece que hay más camarotes…$"

AbandonedShip_Rooms_1F_Text_ThaliaIntro:
	.string "¿Qué te ha traído hasta aquí?\n"
	.string "¡Debes de tener mucha curiosidad!$"

AbandonedShip_Rooms_1F_Text_ThaliaDefeat:
	.string "No solo curiosidad, también fuerza…$"

AbandonedShip_Rooms_1F_Text_ThaliaPostBattle:
	.string "El hombre del camarote de al lado…\p"
	.string "Dice que solo está de turismo, pero\n"
	.string "no me lo creo.$"

AbandonedShip_Rooms_1F_Text_ThaliaRegister:
	.string "¡Qué fuerte eres!\n"
	.string "¡Deja que te registre de recuerdo!$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro:
	.string "¿Qué te ha hecho volver?\n"
	.string "¡Sí que tienes curiosidad!$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat:
	.string "¿No eres demasiado fuerte?$"

AbandonedShip_Rooms_1F_Text_ThaliaPostRematch:
	.string "¡Seguro que ese hombre trama algo!\n"
	.string "¡Es que es muy sospechoso!$"

AbandonedShip_Rooms_1F_Text_DemetriusIntro:
	.string "¡Buaaah!\n"
	.string "¡Me han encontrado! … ¿Eh?$"

AbandonedShip_Rooms_1F_Text_DemetriusDefeat:
	.string "Oh, no eres mi madre.$"

AbandonedShip_Rooms_1F_Text_DemetriusPostBattle:
	.string "Mi madre me ha regañado y me he\n"
	.string "escapado. ¡No digas dónde estoy!$"

