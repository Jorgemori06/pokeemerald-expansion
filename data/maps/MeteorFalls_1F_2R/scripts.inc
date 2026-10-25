MeteorFalls_1F_2R_MapScripts::
	.byte 0

MeteorFalls_1F_2R_EventScript_Nicolas::
	trainerbattle_single TRAINER_NICOLAS_1, MeteorFalls_1F_2R_Text_NicolasIntro, MeteorFalls_1F_2R_Text_NicolasDefeat, MeteorFalls_1F_2R_EventScript_RegisterNicolas
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchNicolas
	msgbox MeteorFalls_1F_2R_Text_NicolasPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterNicolas::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MeteorFalls_1F_2R_Text_NicolasRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_NICOLAS_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchNicolas::
	trainerbattle_rematch TRAINER_NICOLAS_1, MeteorFalls_1F_2R_Text_NicolasRematchIntro, MeteorFalls_1F_2R_Text_NicolasRematchDefeat
	msgbox MeteorFalls_1F_2R_Text_NicolasPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_EventScript_John::
	trainerbattle_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JohnIntro, MeteorFalls_1F_2R_Text_JohnDefeat, MeteorFalls_1F_2R_Text_JohnNotEnoughMons, MeteorFalls_1F_2R_EventScript_RegisterJohn
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchJohn
	msgbox MeteorFalls_1F_2R_Text_JohnPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterJohn::
	msgbox MeteorFalls_1F_2R_Text_JohnRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHN_AND_JAY_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchJohn::
	trainerbattle_rematch_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JohnRematchIntro, MeteorFalls_1F_2R_Text_JohnRematchDefeat, MeteorFalls_1F_2R_Text_JohnRematchNotEnoughMons
	msgbox MeteorFalls_1F_2R_Text_JohnPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_EventScript_Jay::
	trainerbattle_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JayIntro, MeteorFalls_1F_2R_Text_JayDefeat, MeteorFalls_1F_2R_Text_JayNotEnoughMons, MeteorFalls_1F_2R_EventScript_RegisterJay
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchJay
	msgbox MeteorFalls_1F_2R_Text_JayPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterJay::
	msgbox MeteorFalls_1F_2R_Text_JohnRegister, MSGBOX_DEFAULT  @ John speaks for both during register
	register_matchcall TRAINER_JOHN_AND_JAY_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchJay::
	trainerbattle_rematch_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JayRematchIntro, MeteorFalls_1F_2R_Text_JayRematchDefeat, MeteorFalls_1F_2R_Text_JayRematchNotEnoughMons
	msgbox MeteorFalls_1F_2R_Text_JayPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_Text_NicolasIntro:
	.string "Aquí entrenamos los que usamos\n"
	.string "POKéMON DRAGÓN.\p"
	.string "Hasta el CAMPEÓN viene por aquí.\n"
	.string "¿Ves ahora lo especial que es?$"

MeteorFalls_1F_2R_Text_NicolasDefeat:
	.string "¡Urgh!\n"
	.string "¡No esperaba que fueras tan fuerte!$"

MeteorFalls_1F_2R_Text_NicolasPostBattle:
	.string "El camino que queda es largo y duro.\p"
	.string "¿Cuándo seremos los mejores mis\n"
	.string "POKéMON y yo?$"

MeteorFalls_1F_2R_Text_NicolasRegister:
	.string "Quiero saber más de tu poder.\n"
	.string "Deja que te registre en mi POKéNAV.$"

MeteorFalls_1F_2R_Text_NicolasRematchIntro:
	.string "Desde que nos vimos, hemos entrenado\n"
	.string "duro para ser los número uno.\p"
	.string "¡Ayúdanos a ver cuánto más fuertes\n"
	.string "somos!$"

MeteorFalls_1F_2R_Text_NicolasRematchDefeat:
	.string "¡Urgh!\n"
	.string "¡No esperaba que fueras tan fuerte!$"

MeteorFalls_1F_2R_Text_NicolasPostRematch:
	.string "Se nota que sigues entrenando a\n"
	.string "tus POKéMON.\p"
	.string "¡Mientras tú sigas siendo fuerte,\n"
	.string "yo también podré serlo!$"

MeteorFalls_1F_2R_Text_JohnIntro:
	.string "JOHN: Siempre hemos combatido en\n"
	.string "pareja.\l"
	.string "Confiamos en nosotros.$"

MeteorFalls_1F_2R_Text_JohnDefeat:
	.string "JOHN: Vaya, vaya.\n"
	.string "Hemos perdido, querida.$"

MeteorFalls_1F_2R_Text_JohnPostBattle:
	.string "JOHN: Llevamos cincuenta años\n"
	.string "casados.\p"
	.string "Ahora que lo pienso, todavía no le\n"
	.string "he ganado nunca a mi mujer.$"

MeteorFalls_1F_2R_Text_JohnNotEnoughMons:
	.string "JOHN: ¡Vaya, vaya, qué joven!\p"
	.string "¿Combatirás con nosotros? Si es así,\n"
	.string "tendrás que volver con más POKéMON.$"

MeteorFalls_1F_2R_Text_JohnRegister:
	.string "JOHN: Si se presenta la ocasión,\n"
	.string "¿volverás a combatir con nosotros?$"

MeteorFalls_1F_2R_Text_JayIntro:
	.string "JAY: Llevamos cincuenta años\n"
	.string "casados.\p"
	.string "El lazo que nos une como pareja\n"
	.string "no se puede romper.$"

MeteorFalls_1F_2R_Text_JayDefeat:
	.string "JAY: Ay, ay.\n"
	.string "Hemos perdido, querido.$"

MeteorFalls_1F_2R_Text_JayPostBattle:
	.string "JAY: Cincuenta años de casados…\p"
	.string "Si alguna vez discutíamos, siempre\n"
	.string "lo arreglábamos con un combate…$"

MeteorFalls_1F_2R_Text_JayNotEnoughMons:
	.string "JAY: ¡Vaya, vaya, qué joven!\p"
	.string "Si quieres combatir con nosotros,\n"
	.string "tendrás que volver con más POKéMON.$"

MeteorFalls_1F_2R_Text_JohnRematchIntro:
	.string "JOHN: Siempre hemos combatido en\n"
	.string "pareja.\l"
	.string "Confiamos en nosotros.$"

MeteorFalls_1F_2R_Text_JohnRematchDefeat:
	.string "JOHN: Vaya, vaya.\n"
	.string "Hemos perdido, querida.$"

MeteorFalls_1F_2R_Text_JohnPostRematch:
	.string "JOHN: Cincuenta años casados…\p"
	.string "Pensándolo bien, mi mujer y yo\n"
	.string "combatíamos todos los días…$"

MeteorFalls_1F_2R_Text_JohnRematchNotEnoughMons:
	.string "JOHN: ¡Vaya, vaya, qué joven!\p"
	.string "¿Combatirás con nosotros? Si es así,\n"
	.string "tendrás que volver con más POKéMON.$"

MeteorFalls_1F_2R_Text_JayRematchIntro:
	.string "JAY: Llevamos cincuenta años\n"
	.string "casados.\p"
	.string "Nos hemos apoyado todo este tiempo.\n"
	.string "Así nos hemos hecho fuertes.$"

MeteorFalls_1F_2R_Text_JayRematchDefeat:
	.string "JAY: Ay, ay.\n"
	.string "Hemos perdido, querido.$"

MeteorFalls_1F_2R_Text_JayPostRematch:
	.string "JAY: Cincuenta años de casados…\n"
	.string "Han pasado muchas cosas.\p"
	.string "Espero que sigamos teniendo\n"
	.string "recuerdos felices juntos.$"

MeteorFalls_1F_2R_Text_JayRematchNotEnoughMons:
	.string "JAY: ¡Vaya, vaya, qué joven!\p"
	.string "Si quieres combatir con nosotros,\n"
	.string "tendrás que volver con más POKéMON.$"

