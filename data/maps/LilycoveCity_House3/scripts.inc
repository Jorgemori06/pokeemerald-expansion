LilycoveCity_House3_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_House3_OnTransition
	.byte 0

LilycoveCity_House3_OnTransition:
	random 4
	copyvar VAR_TEMP_1, VAR_RESULT
	end

LilycoveCity_House3_EventScript_PokefanF::
	lock
	faceplayer
	msgbox LilycoveCity_House3_Text_LearnFromMasterOfPokeblocks, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LilycoveCity_House3_EventScript_DeclinePokeblockLearn
	msgbox LilycoveCity_House3_Text_ExplainPokeblocks, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_DeclinePokeblockLearn::
	msgbox LilycoveCity_House3_Text_OhAreYouSure, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_Man::
	lock
	faceplayer
	msgbox LilycoveCity_House3_Text_HappyToHaveQuadruplets, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_GameBoyKid1::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid2::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid3::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid4::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_WereDoingMultiBattle::
	msgbox LilycoveCity_House3_Text_GoingToWinMultiBattles, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereMixingRecords::
	msgbox LilycoveCity_House3_Text_LikeMixingAtRecordCorner, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereBlendingBerries::
	msgbox LilycoveCity_House3_Text_MakePokeblocksWithBerryBlender, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereDoingContest::
	msgbox LilycoveCity_House3_Text_GoingToEnterContest, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_Text_LearnFromMasterOfPokeblocks:
	.string "¡Ay, madre! ¿Viajas sin compañía?\n"
	.string "¡Con lo joven que eres! ¡Bien hecho!\p"
	.string "¡Seguro que mis hijos podrían\n"
	.string "aprender algo de ti!\p"
	.string "¿Yo? Soy maestra de los {POKEBLOCK}S.\p"
	.string "Si me pongo un poquito en serio,\n"
	.string "preparo unos {POKEBLOCK}S geniales.\p"
	.string "¿Quieres que te enseñe una maestra\n"
	.string "de los {POKEBLOCK}S?$"

LilycoveCity_House3_Text_OhAreYouSure:
	.string "¿Oh? ¿Seguro?\p"
	.string "¡No siempre hay que intentar hacerlo\n"
	.string "todo sin ayuda, cielo!$"

LilycoveCity_House3_Text_ExplainPokeblocks:
	.string "¡Oh, bien! ¡Qué cabeza tienes!\n"
	.string "Es un poco largo, así que atención.\p"
	.string "¿Lista la cabeza?\p"
	.string "Si miras los {POKEBLOCK}S, verás que\n"
	.string "tienen una nota de textura.\p"
	.string "¡Cuanto más baja la textura, mejor!\n"
	.string "¡Que no se te olvide!\p"
	.string "Un buen {POKEBLOCK} tiene la textura\n"
	.string "baja y el nivel alto.\p"
	.string "Además, un POKéMON puede comer más\n"
	.string "{POKEBLOCK}S buenos que normales.\p"
	.string "Y esto es importante.\p"
	.string "Para hacer {POKEBLOCK}S suaves, usa\n"
	.string "BAYAS de tipos distintos.\p"
	.string "¡No seas tacaño! El tipo de BAYAS\n"
	.string "influye en la suavidad.\p"
	.string "Y otra cosa.\p"
	.string "Cuanta más gente licúe BAYAS, más\n"
	.string "suaves salen los {POKEBLOCK}S.\p"
	.string "Por eso deberías hablar con más gente\n"
	.string "y hacer {POKEBLOCK}S en compañía.\p"
	.string "Eso es lo que necesitas saber para\n"
	.string "hacer buenos {POKEBLOCK}S.\p"
	.string "Si todo el mundo tuviera POKéMON\n"
	.string "queridos, {POKEBLOCK}S suaves y una\l"
	.string "familia que lo quiere, el mundo\l"
	.string "sería más feliz.\p"
	.string "¡No te rindas, cielo!$"

LilycoveCity_House3_Text_HappyToHaveQuadruplets:
	.string "Cuando mi mujer tuvo cuatrillizos,\n"
	.string "me llevé un susto de muerte.\p"
	.string "Pero ahora, al verlos jugar juntos,\n"
	.string "soy feliz.$"

LilycoveCity_House3_Text_GoingToWinMultiBattles:
	.string "Estamos jugando a COMBATES MÚLTIPLES,\n"
	.string "pero sé que voy a ganar yo.$"

LilycoveCity_House3_Text_LikeMixingAtRecordCorner:
	.string "Nos gusta mezclar cosas en el\n"
	.string "RINCÓN RÉCORDS.\p"
	.string "¿Pero qué se mezcla?$"

LilycoveCity_House3_Text_MakePokeblocksWithBerryBlender:
	.string "¡Vamos a hacer {POKEBLOCK}S geniales\n"
	.string "con una LICUADORA DE BAYAS!$"

LilycoveCity_House3_Text_GoingToEnterContest:
	.string "Quiero presumir de lo fuerte que es\n"
	.string "mi POKéMON, así que nos vamos a\l"
	.string "presentar juntos a un CONCURSO.$"

