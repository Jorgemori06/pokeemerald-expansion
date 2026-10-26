LilycoveCity_CoveLilyMotel_2F_MapScripts::
	.byte 0

LilycoveCity_CoveLilyMotel_2F_EventScript_GameDesigner::
	lock
	faceplayer
	call_if_unset FLAG_TEMP_2, LilycoveCity_CoveLilyMotel_2F_EventScript_ShowMeCompletedDex
	call_if_set FLAG_TEMP_2, LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma
	specialvar VAR_RESULT, HasAllHoennMons
	goto_if_eq VAR_RESULT, TRUE, LilycoveCity_CoveLilyMotel_2F_EventScript_AllHoennMonsFanfare
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_ShowMeCompletedDex::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ShowMeCompletedDex, MSGBOX_DEFAULT
	return

LilycoveCity_CoveLilyMotel_2F_EventScript_AllHoennMonsFanfare::
	setflag FLAG_TEMP_2
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	goto LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma::
	message LilycoveCity_CoveLilyMotel_2F_Text_FilledPokedexGiveYouThis
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	special Special_ShowDiploma
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Programmer::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ImTheProgrammer, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_GraphicArtist::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ImTheGraphicArtist, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_FatMan::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_GirlsAreCute, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Woman::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_SeaBreezeTicklesHeart, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_GameBoyKid::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_NeverLeaveWithoutGameBoy, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Scott::
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_IN_LILYCOVE, LilycoveCity_CoveLilyMotel_2F_EventScript_MetScott
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_SnoozingPreferBattles, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_IN_LILYCOVE
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_MetScott::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ContestsDoTakeStrategy, MSGBOX_DEFAULT
	release
	end

LilycoveCity_CoveLilyMotel_2F_Text_ShowMeCompletedDex:
	.string "Soy el DISEÑADOR DEL JUEGO.\p"
	.string "¿Ah, sí?\n"
	.string "¿Estás completando una POKéDEX?\p"
	.string "Cuesta mucho completarla, pero\n"
	.string "no te rindas.\p"
	.string "Si la completas, ven a enseñármela,\n"
	.string "por favor.$"

LilycoveCity_CoveLilyMotel_2F_Text_FilledPokedexGiveYouThis:
	.string "¡Hala! ¡Qué pasada!\n"
	.string "¡Sí, es una pasada total!\p"
	.string "¡Esta POKéDEX está completa!\n"
	.string "¡Sí que te gustan los POKéMON!\p"
	.string "¡Estoy impresionado!\p"
	.string "Deja que te dé algo como\n"
	.string "reconocimiento.$"

LilycoveCity_CoveLilyMotel_2F_Text_ImTheProgrammer:
	.string "¿Yo? ¿Me hablas a mí?\n"
	.string "Soy el PROGRAMADOR.\p"
	.string "¿Cómo serán las TRAGAPERRAS de\n"
	.string "por aquí?$"

LilycoveCity_CoveLilyMotel_2F_Text_ImTheGraphicArtist:
	.string "¡Soy la GRAFISTA! ¿A que los POKéMON\n"
	.string "de HOENN son interesantes?$"

LilycoveCity_CoveLilyMotel_2F_Text_GirlsAreCute:
	.string "Las chicas del FLOTADOR son monas,\n"
	.string "¿eh? Combatir contra una de ellas…\p"
	.string "¡Uau, es lo más!\p"
	.string "¡Y las GEMELAS! ¿A que son monas?\n"
	.string "Un combate 2 contra 2 con GEMELAS…\p"
	.string "¡Uau, es divertidísimo!$"

LilycoveCity_CoveLilyMotel_2F_Text_SeaBreezeTicklesHeart:
	.string "La brisa del mar me hace cosquillas\n"
	.string "en el corazón. ¡Qué gusto!$"

LilycoveCity_CoveLilyMotel_2F_Text_NeverLeaveWithoutGameBoy:
	.string "Nunca sabes cuándo ni dónde te\n"
	.string "van a desafiar.\p"
	.string "Por eso nunca salgo de casa sin\n"
	.string "mi GAME BOY ADVANCE.$"

LilycoveCity_CoveLilyMotel_2F_Text_SnoozingPreferBattles:
	.string "SCOTT: … … … … …\n"
	.string "… … … … … Zzz…\p"
	.string "… … … … … ¿Eh?\n"
	.string "¡Ay, perdona! ¡Me había dormido!\p"
	.string "He venido a ver eso de los\n"
	.string "CONCURSOS POKéMON.\p"
	.string "Reconozco que parece bastante\n"
	.string "entretenido, pero…\p"
	.string "Soy de la vieja escuela: prefiero los\n"
	.string "combates y los ENTRENADORES duros.\p"
	.string "Pero eso es cosa mía.\p"
	.string "¡{PLAYER}{KUN}, que lo disfrutes\n"
	.string "todo: GIMNASIOS, CONCURSOS, CARPA\l"
	.string "DE COMBATE…!$"

LilycoveCity_CoveLilyMotel_2F_Text_ContestsDoTakeStrategy:
	.string "SCOTT: Creo que para ganar un\n"
	.string "CONCURSO sí que hace falta estrategia.\p"
	.string "Pensar estrategias de CONCURSO es\n"
	.string "una forma de mejorar como ENTRENADOR.$"

