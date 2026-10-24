RustboroCity_PokemonSchool_MapScripts::
	.byte 0

RustboroCity_PokemonSchool_EventScript_Blackboard::
	lockall
	msgbox RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic::
	message RustboroCity_PokemonSchool_Text_ReadWhichTopic
	waitmessage
	multichoicegrid 8, 1, MULTI_STATUS_INFO, 3, FALSE
	switch VAR_RESULT
	case 0, RustboroCity_PokemonSchool_EventScript_Poison
	case 1, RustboroCity_PokemonSchool_EventScript_Paralysis
	case 2, RustboroCity_PokemonSchool_EventScript_Sleep
	case 3, RustboroCity_PokemonSchool_EventScript_Burn
	case 4, RustboroCity_PokemonSchool_EventScript_Freeze
	case 5, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
	case MULTI_B_PRESSED, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
	end

RustboroCity_PokemonSchool_EventScript_Poison::
	msgbox RustboroCity_PokemonSchool_Text_ExplainPoison, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Paralysis::
	msgbox RustboroCity_PokemonSchool_Text_ExplainParalysis, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Sleep::
	msgbox RustboroCity_PokemonSchool_Text_ExplainSleep, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Burn::
	msgbox RustboroCity_PokemonSchool_Text_ExplainBurn, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Freeze::
	msgbox RustboroCity_PokemonSchool_Text_ExplainFreeze, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_ExitTopicSelect::
	releaseall
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid1::
	msgbox RustboroCity_PokemonSchool_Text_TradingRightNow, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid2::
	msgbox RustboroCity_PokemonSchool_Text_AlwaysWantedSeedot, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_RichBoy::
	msgbox RustboroCity_PokemonSchool_Text_PokemontCantUseManMadeItems, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_Lass::
	msgbox RustboroCity_PokemonSchool_Text_ConfusedPokemonAttacksItself, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_SchoolKidM::
	msgbox RustboroCity_PokemonSchool_Text_PokemonHealItselfWithBerry, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_StudentNotebook::
	msgbox RustboroCity_PokemonSchool_Text_StudentsNotes, MSGBOX_SIGN
	end

RustboroCity_PokemonSchool_EventScript_Teacher::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_QUICK_CLAW, RustboroCity_PokemonSchool_EventScript_GaveQuickClaw
	call_if_eq VAR_FACING, DIR_EAST, RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast
	call_if_eq VAR_FACING, DIR_WEST, RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest
	msgbox RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw, MSGBOX_DEFAULT
	giveitem ITEM_QUICK_CLAW
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	setflag FLAG_RECEIVED_QUICK_CLAW
	release
	end

RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast::
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast
	waitmovement 0
	return

RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest::
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest
	waitmovement 0
	return

RustboroCity_PokemonSchool_EventScript_GaveQuickClaw::
	msgbox RustboroCity_PokemonSchool_Text_ExplainQuickClaw, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	release
	end

RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest:
	walk_left
	walk_down
	walk_down
	walk_right
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_faster_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	walk_right
	step_end

RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast:
	walk_right
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_faster_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_right
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

RustboroCity_PokemonSchool_EventScript_Scott::
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE, RustboroCity_PokemonSchool_EventScript_ScottWatchStudents
	goto_if_set FLAG_MET_SCOTT_RUSTBORO, RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_RUSTBORO
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready::
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge::
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge::
	msgbox RustboroCity_PokemonSchool_Text_ScottStoneBadge, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge::
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottWatchStudents::
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges:
	.string "En la pizarra están los problemas\n"
	.string "de estado que hay en combate.$"

RustboroCity_PokemonSchool_Text_ReadWhichTopic:
	.string "¿Qué tema quieres leer?$"

RustboroCity_PokemonSchool_Text_ExplainPoison:
	.string "Un POKéMON envenenado pierde PS\n"
	.string "poco a poco.\p"
	.string "El veneno sigue después del\n"
	.string "combate.\p"
	.string "Un POKéMON envenenado pierde PS\n"
	.string "mientras viajas.\p"
	.string "Cura el envenenamiento con un\n"
	.string "ANTÍDOTO.$"

RustboroCity_PokemonSchool_Text_ExplainParalysis:
	.string "Si un POKéMON se paraliza,\n"
	.string "baja su VELOCIDAD.\p"
	.string "Además, a veces no podrá moverse\n"
	.string "en el combate.\p"
	.string "La parálisis sigue tras el combate.\n"
	.string "Cúrala con un ANTIPARALIZADOR.$"

RustboroCity_PokemonSchool_Text_ExplainSleep:
	.string "Un POKéMON dormido no puede\n"
	.string "atacar.\p"
	.string "Puede despertarse solo, pero si el\n"
	.string "combate acaba mientras duerme,\l"
	.string "seguirá dormido.\p"
	.string "Despiértalo con un DESPERTAR.$"

RustboroCity_PokemonSchool_Text_ExplainBurn:
	.string "Una quemadura baja el ATAQUE y\n"
	.string "resta PS poco a poco.\p"
	.string "Sigue después del combate.\n"
	.string "Cúrala con un ANTIQUEMAR.$"

RustboroCity_PokemonSchool_Text_ExplainFreeze:
	.string "Un POKéMON congelado no puede\n"
	.string "hacer nada.\p"
	.string "Sigue congelado tras el combate.\n"
	.string "Descongélalo con un ANTIHIELO.$"

RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw:
	.string "Los alumnos que no estudian prueban\n"
	.string "mi GARRA RÁPIDA.\p"
	.string "Se verá si eres buen alumno por\n"
	.string "cómo usas este objeto.$"

RustboroCity_PokemonSchool_Text_ExplainQuickClaw:
	.string "Un POKéMON con GARRA RÁPIDA a veces\n"
	.string "se acelera y actúa antes que\l"
	.string "su rival.\p"
	.string "Hay muchos otros objetos para que\n"
	.string "los lleven los POKéMON.\p"
	.string "¡Solo con eso ya tienes muchos\n"
	.string "temas que estudiar!$"

RustboroCity_PokemonSchool_Text_TradingRightNow:
	.string "Estoy cambiando POKéMON con mi\n"
	.string "amigo ahora mismo.$"

RustboroCity_PokemonSchool_Text_AlwaysWantedSeedot:
	.string "Siempre he querido un SEEDOT,\n"
	.string "¡y por fin voy a tenerlo!$"

RustboroCity_PokemonSchool_Text_PokemontCantUseManMadeItems:
	.string "Los POKéMON pueden llevar objetos,\n"
	.string "pero no saben usar cosas fabricadas\l"
	.string "como POCIONES o ANTÍDOTOS.$"

RustboroCity_PokemonSchool_Text_ConfusedPokemonAttacksItself:
	.string "¿Sabes que algunos movimientos\n"
	.string "pueden confundir a un POKéMON?\p"
	.string "Un POKéMON confuso a veces se ataca\n"
	.string "a sí mismo sin querer.\p"
	.string "Pero al salir del combate vuelve\n"
	.string "a la normalidad.$"

RustboroCity_PokemonSchool_Text_PokemonHealItselfWithBerry:
	.string "Un POKéMON con una BAYA se\n"
	.string "cura solo…\p"
	.string "Hay muchos objetos que pueden\n"
	.string "llevar los POKéMON…\p"
	.string "¡Uf, qué difícil es tomar\n"
	.string "apuntes…!$"

RustboroCity_PokemonSchool_Text_StudentsNotes:
	.string "Es el cuaderno de un alumno…\p"
	.string "Los POKéMON se atrapan con\n"
	.string "POKé BALLS.\p"
	.string "Un ENTRENADOR puede llevar hasta\n"
	.string "seis POKéMON.\p"
	.string "Un ENTRENADOR es quien atrapa\n"
	.string "POKéMON, los cría y combate\l"
	.string "con ellos.\p"
	.string "Su misión es vencer a los ENTRENADORES\n"
	.string "fuertes que esperan rivales en los\l"
	.string "GIMNASIOS POKéMON.$"

RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut:
	.string "¿Hola? ¿No nos hemos visto antes?\n"
	.string "Creo que en CIUDAD PETALIA.\p"
	.string "Deja que me presente.\n"
	.string "Me llamo SCOTT.\p"
	.string "Viajo por todas partes buscando\n"
	.string "ENTRENADORES excepcionales.\p"
	.string "Más bien, busco expertos en\n"
	.string "combates POKéMON.\p"
	.string "Y bien, ¿qué te trae a esta ESCUELA?\n"
	.string "¿También entrenas POKéMON?\p"
	.string "Lo primero que deberías hacer es\n"
	.string "enseñarle CORTE a un POKéMON.\p"
	.string "Si no recuerdo mal, alguien de esta\n"
	.string "ciudad tiene CORTE.$"

RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown:
	.string "SCOTT: Mmm…\p"
	.string "No se sabe el talento de los alumnos\n"
	.string "de aquí. Pero potencial hay.$"

RustboroCity_PokemonSchool_Text_ScottStoneBadge:
	.string "SCOTT: Oh, ¿qué es eso?\p"
	.string "¿Es la MEDALLA PIEDRA?\n"
	.string "Yo diría que es impresionante.\p"
	.string "Pero, ¿sabes?, me habría encantado\n"
	.string "verte combatir.\p"
	.string "Con una MEDALLA no se sabe cómo\n"
	.string "combate un ENTRENADOR.$"

RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge:
	.string "¿Hola? ¿No nos hemos visto antes?\n"
	.string "Creo que en CIUDAD PETALIA.\p"
	.string "Deja que me presente.\n"
	.string "Me llamo SCOTT.\p"
	.string "Viajo por todas partes buscando\n"
	.string "ENTRENADORES excepcionales.\p"
	.string "Más bien, busco expertos en\n"
	.string "combates POKéMON.\p"
	.string "Oh, ¿qué es eso?\n"
	.string "¿Es la MEDALLA PIEDRA?\p"
	.string "Para alguien que acaba de empezar,\n"
	.string "yo diría que es impresionante.\p"
	.string "Pero, ¿sabes?, me habría encantado\n"
	.string "verte combatir.\p"
	.string "Con una MEDALLA no se sabe cómo\n"
	.string "combate un ENTRENADOR.$"

