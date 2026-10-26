MtPyre_3F_MapScripts::
	.byte 0

MtPyre_3F_EventScript_William::
	trainerbattle_single TRAINER_WILLIAM, MtPyre_3F_Text_WilliamIntro, MtPyre_3F_Text_WilliamDefeat
	msgbox MtPyre_3F_Text_WilliamPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Kayla::
	trainerbattle_single TRAINER_KAYLA, MtPyre_3F_Text_KaylaIntro, MtPyre_3F_Text_KaylaDefeat
	msgbox MtPyre_3F_Text_KaylaPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Gabrielle::
	trainerbattle_single TRAINER_GABRIELLE_1, MtPyre_3F_Text_GabrielleIntro, MtPyre_3F_Text_GabrielleDefeat, MtPyre_3F_EventScript_RegisterGabrielle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtPyre_3F_EventScript_RematchGabrielle
	msgbox MtPyre_3F_Text_GabriellePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_3F_EventScript_RegisterGabrielle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_3F_Text_GabrielleRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_GABRIELLE_1
	release
	end

MtPyre_3F_EventScript_RematchGabrielle::
	trainerbattle_rematch TRAINER_GABRIELLE_1, MtPyre_3F_Text_GabrielleRematchIntro, MtPyre_3F_Text_GabrielleRematchDefeat
	msgbox MtPyre_3F_Text_GabriellePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_Text_WilliamIntro:
	.string "¡El ambiente de la montaña ha\n"
	.string "aumentado mi poder psíquico!\p"
	.string "¿Una simple criatura como tú…?\n"
	.string "¿Sueñas con ganar?$"

MtPyre_3F_Text_WilliamDefeat:
	.string "Me ahogo en la autocompasión…$"

MtPyre_3F_Text_WilliamPostBattle:
	.string "Mi poder psíquico se ha multiplicado,\n"
	.string "seguro, pero…$"

MtPyre_3F_Text_KaylaIntro:
	.string "¡Jajajajaja!\p"
	.string "¡Este no es sitio para críos, y\n"
	.string "menos para ti!$"

MtPyre_3F_Text_KaylaDefeat:
	.string "He perdido limpiamente…$"

MtPyre_3F_Text_KaylaPostBattle:
	.string "Esto quiere decir que aún no he\n"
	.string "entrenado bastante…\p"
	.string "Tengo que seguir hacia la cima…\p"
	.string "¡Vamos, yo!$"

MtPyre_3F_Text_GabrielleIntro:
	.string "¿Por qué has venido aquí?$"

MtPyre_3F_Text_GabrielleDefeat:
	.string "¡Ha sido increíble!\n"
	.string "Eres alguien muy especial.$"

MtPyre_3F_Text_GabriellePostBattle:
	.string "Los POKéMON que ya no están en este\n"
	.string "mundo. Los POKéMON que están contigo.\p"
	.string "Y los POKéMON que conocerás en el\n"
	.string "futuro…\p"
	.string "Todos merecen el mismo cariño.\n"
	.string "No lo olvides, por favor.$"

MtPyre_3F_Text_GabrielleRegister:
	.string "Me gustaría ver a tus POKéMON cuando\n"
	.string "crezcan un poco más…\p"
	.string "Por favor, enséñame tu POKéNAV.$"

MtPyre_3F_Text_GabrielleRematchIntro:
	.string "Oh, eres tú…\p"
	.string "¿Has venido a enseñarme a tus\n"
	.string "POKéMON ya crecidos?$"

MtPyre_3F_Text_GabrielleRematchDefeat:
	.string "¡Increíble!\n"
	.string "Eres alguien especial.$"

MtPyre_3F_Text_GabriellePostRematch:
	.string "Los POKéMON que ya no están en este\n"
	.string "mundo. Los POKéMON que están contigo.\p"
	.string "Y los POKéMON que conocerás en el\n"
	.string "futuro…\p"
	.string "Todos merecen el mismo cariño.\n"
	.string "Veo que no lo has olvidado.$"

