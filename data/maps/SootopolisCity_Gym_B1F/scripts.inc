SootopolisCity_Gym_B1F_MapScripts::
	.byte 0

SootopolisCity_Gym_B1F_EventScript_Andrea::
	trainerbattle_single TRAINER_ANDREA, SootopolisCity_Gym_B1F_Text_AndreaIntro, SootopolisCity_Gym_B1F_Text_AndreaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_AndreaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Crissy::
	trainerbattle_single TRAINER_CRISSY, SootopolisCity_Gym_B1F_Text_CrissyIntro, SootopolisCity_Gym_B1F_Text_CrissyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_CrissyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Brianna::
	trainerbattle_single TRAINER_BRIANNA, SootopolisCity_Gym_B1F_Text_BriannaIntro, SootopolisCity_Gym_B1F_Text_BriannaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BriannaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Connie::
	trainerbattle_single TRAINER_CONNIE, SootopolisCity_Gym_B1F_Text_ConnieIntro, SootopolisCity_Gym_B1F_Text_ConnieDefeat
	msgbox SootopolisCity_Gym_B1F_Text_ConniePostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Bridget::
	trainerbattle_single TRAINER_BRIDGET, SootopolisCity_Gym_B1F_Text_BridgetIntro, SootopolisCity_Gym_B1F_Text_BridgetDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BridgetPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Olivia::
	trainerbattle_single TRAINER_OLIVIA, SootopolisCity_Gym_B1F_Text_OliviaIntro, SootopolisCity_Gym_B1F_Text_OliviaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_OliviaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Tiffany::
	trainerbattle_single TRAINER_TIFFANY, SootopolisCity_Gym_B1F_Text_TiffanyIntro, SootopolisCity_Gym_B1F_Text_TiffanyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_TiffanyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Bethany::
	trainerbattle_single TRAINER_BETHANY, SootopolisCity_Gym_B1F_Text_BethanyIntro, SootopolisCity_Gym_B1F_Text_BethanyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BethanyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Annika::
	trainerbattle_single TRAINER_ANNIKA, SootopolisCity_Gym_B1F_Text_AnnikaIntro, SootopolisCity_Gym_B1F_Text_AnnikaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_AnnikaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Daphne::
	trainerbattle_single TRAINER_DAPHNE, SootopolisCity_Gym_B1F_Text_DaphneIntro, SootopolisCity_Gym_B1F_Text_DaphneDefeat
	msgbox SootopolisCity_Gym_B1F_Text_DaphnePostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_Text_AndreaIntro:
	.string "¡Te enseñaré las técnicas sublimes que\n"
	.string "aprendí de nuestro LÍDER, GALANO!$"

SootopolisCity_Gym_B1F_Text_AndreaDefeat:
	.string "Perdóname, GALANO…$"

SootopolisCity_Gym_B1F_Text_AndreaPostBattle:
	.string "Mira lo que pasa si rompes todas las\n"
	.string "baldosas del suelo.$"

SootopolisCity_Gym_B1F_Text_CrissyIntro:
	.string "Has llegado hasta aquí, pero no vas\n"
	.string "a ver a GALANO.\p"
	.string "¡No si pierdes contra mí!$"

SootopolisCity_Gym_B1F_Text_CrissyDefeat:
	.string "¡Qué fuerte!\n"
	.string "¡Me ha engañado esa carita!$"

SootopolisCity_Gym_B1F_Text_CrissyPostBattle:
	.string "Quizá seas lo bastante bueno para que\n"
	.string "GALANO no te tumbe de un golpe.$"

SootopolisCity_Gym_B1F_Text_DaphneIntro:
	.string "Ver a GALANO dirigir un combate…\p"
	.string "Su belleza me hizo querer ser\n"
	.string "ENTRENADORA.$"

SootopolisCity_Gym_B1F_Text_DaphneDefeat:
	.string "Has combatido con más belleza de la\n"
	.string "que yo podría…$"

SootopolisCity_Gym_B1F_Text_DaphnePostBattle:
	.string "La elegancia con la que combates es\n"
	.string "fabulosa.\p"
	.string "Oh… Qué suerte tengo de haber\n"
	.string "conocido a los POKéMON.$"

SootopolisCity_Gym_B1F_Text_ConnieIntro:
	.string "Debería enseñarte lo duros que\n"
	.string "pueden ser los combates.$"

SootopolisCity_Gym_B1F_Text_ConnieDefeat:
	.string "Oh.\n"
	.string "Eres fuerte.$"

SootopolisCity_Gym_B1F_Text_ConniePostBattle:
	.string "Te diré algo bueno.\p"
	.string "Si quieres llegar hasta GALANO, tienes\n"
	.string "que pisar cada baldosa una sola vez.$"

SootopolisCity_Gym_B1F_Text_BridgetIntro:
	.string "El GIMNASIO POKéMON de más nivel\n"
	.string "de la región de HOENN…\p"
	.string "Es el GIMNASIO de ARRECÍPOLIS.$"

SootopolisCity_Gym_B1F_Text_BridgetDefeat:
	.string "¡Qué nivel tienes!$"

SootopolisCity_Gym_B1F_Text_BridgetPostBattle:
	.string "En vez de conformarte con estar en un\n"
	.string "GIMNASIO fuerte, imagino que entrenar\l"
	.string "en otros sitios te hará más fuerte.\l"
	.string "Y, sobre todo, parece más divertido.$"

SootopolisCity_Gym_B1F_Text_OliviaIntro:
	.string "Entreno a mis POKéMON junto a\n"
	.string "GALANO.\p"
	.string "No creas que soy un blanco fácil.$"

SootopolisCity_Gym_B1F_Text_OliviaDefeat:
	.string "Me han ganado…$"

SootopolisCity_Gym_B1F_Text_OliviaPostBattle:
	.string "Creo que tienes potencial.\n"
	.string "¿Por qué no te quedas a entrenar\l"
	.string "con nosotras?$"

SootopolisCity_Gym_B1F_Text_TiffanyIntro:
	.string "Deslizarse con gracia por el hielo\n"
	.string "sin cruzar ninguna línea…\p"
	.string "¡Alguien que hiciera eso sería de una\n"
	.string "belleza elegante!$"

SootopolisCity_Gym_B1F_Text_TiffanyDefeat:
	.string "¿Perdona?$"

SootopolisCity_Gym_B1F_Text_TiffanyPostBattle:
	.string "Es evidente, pero lo fuerte que eres\n"
	.string "como ENTRENADOR no tiene nada que ver\l"
	.string "con la edad.$"

SootopolisCity_Gym_B1F_Text_BethanyIntro:
	.string "Cuando estoy con mis POKéMON, el\n"
	.string "tiempo vuela antes de decir “¡Huy!”.$"

SootopolisCity_Gym_B1F_Text_BethanyDefeat:
	.string "¡Huy!$"

SootopolisCity_Gym_B1F_Text_BethanyPostBattle:
	.string "Ojalá pudiera olvidar las causas\n"
	.string "perdidas antes de decir “¡Huy!”.$"

SootopolisCity_Gym_B1F_Text_AnnikaIntro:
	.string "Si quieres, puedo combatir con\n"
	.string "POKéMON muy raros.$"

SootopolisCity_Gym_B1F_Text_AnnikaDefeat:
	.string "¡Oh, vaya! ¿Has visto bien a mis\n"
	.string "POKéMON?$"

SootopolisCity_Gym_B1F_Text_AnnikaPostBattle:
	.string "Vine a este GIMNASIO porque GALANO\n"
	.string "elogió a mis POKéMON preciosos.\p"
	.string "Ay, si hubiera conocido a GALANO hace\n"
	.string "años, cuando era más joven…$"

SootopolisCity_Gym_B1F_Text_BriannaIntro:
	.string "Jijiji…\n"
	.string "Esa cara tan seria tiene su encanto.$"

SootopolisCity_Gym_B1F_Text_BriannaDefeat:
	.string "Ay, madre.\n"
	.string "Me he confiado demasiado.$"

SootopolisCity_Gym_B1F_Text_BriannaPostBattle:
	.string "Seguro que a GALANO no le tocas ni\n"
	.string "un pelo. Jijiji…$"

