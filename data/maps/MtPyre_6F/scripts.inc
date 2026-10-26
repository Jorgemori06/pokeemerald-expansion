MtPyre_6F_MapScripts::
	.byte 0

MtPyre_6F_EventScript_Valerie::
	trainerbattle_single TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieIntro, MtPyre_6F_Text_ValerieDefeat, MtPyre_6F_EventScript_RegisterValerie
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtPyre_6F_EventScript_RematchValerie
	msgbox MtPyre_6F_Text_ValeriePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_6F_EventScript_RegisterValerie::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_6F_Text_ValerieRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_VALERIE_1
	release
	end

MtPyre_6F_EventScript_RematchValerie::
	trainerbattle_rematch TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieRematchIntro, MtPyre_6F_Text_ValerieRematchDefeat
	msgbox MtPyre_6F_Text_ValeriePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_EventScript_Cedric::
	trainerbattle_single TRAINER_CEDRIC, MtPyre_6F_Text_CedricIntro, MtPyre_6F_Text_CedricDefeat
	msgbox MtPyre_6F_Text_CedricPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_Text_ValerieIntro:
	.string "Cuando estoy aquí…\n"
	.string "Me entra un poder curioso…$"

MtPyre_6F_Text_ValerieDefeat:
	.string "El poder se está apagando…$"

MtPyre_6F_Text_ValeriePostBattle:
	.string "Quizá el poder venga de los espíritus\n"
	.string "de los POKéMON que duermen inquietos…$"

MtPyre_6F_Text_ValerieRegister:
	.string "Fufufu… He perdido, pero…\n"
	.string "Tengo una pequeña habilidad…\p"
	.string "Sin tocar siquiera tu POKéNAV…\n"
	.string "¡Hiyah!$"

MtPyre_6F_Text_ValerieRematchIntro:
	.string "Detrás de ti…\n"
	.string "¿Qué es eso…?$"

MtPyre_6F_Text_ValerieRematchDefeat:
	.string "Algo se ha desvanecido…$"

MtPyre_6F_Text_ValeriePostRematch:
	.string "Los POKéMON que descansan aquí…\n"
	.string "A veces, juegan…$"

MtPyre_6F_Text_CedricIntro:
	.string "¿Te has perdido?\n"
	.string "¡No temas, que aquí estoy yo!$"

MtPyre_6F_Text_CedricDefeat:
	.string "¿No te habías perdido?$"

MtPyre_6F_Text_CedricPostBattle:
	.string "Pensé que alguien que se ha perdido\n"
	.string "se pondría nervioso y sería fácil.\p"
	.string "Es un truco sucio y no lo repetiré…$"

