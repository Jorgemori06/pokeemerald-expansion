RustboroCity_Gym_MapScripts::
	.byte 0

RustboroCity_Gym_EventScript_Roxanne::
	trainerbattle_single TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxanneIntro, RustboroCity_Gym_Text_RoxanneDefeat, RustboroCity_Gym_EventScript_RoxanneDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Gym_EventScript_RoxanneRematch
	goto_if_unset FLAG_RECEIVED_TM_ROCK_TOMB, RustboroCity_Gym_EventScript_GiveRockTomb
	msgbox RustboroCity_Gym_Text_RoxannePostBattle, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneDefeated::
	message RustboroCity_Gym_Text_ReceivedStoneBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox RustboroCity_Gym_Text_StoneBadgeInfoTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_RUSTBORO_GYM
	setflag FLAG_BADGE01_GET
	setvar VAR_RUSTBORO_CITY_STATE, 1
	addvar VAR_PETALBURG_GYM_STATE, 1
	setvar VAR_0x8008, 1
	call Common_EventScript_SetGymTrainers
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	goto RustboroCity_Gym_EventScript_GiveRockTomb
	end

RustboroCity_Gym_EventScript_GiveRockTomb::
	giveitem ITEM_TM_ROCK_TOMB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_ROCK_TOMB
	msgbox RustboroCity_Gym_Text_ExplainRockTomb, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneRematch::
	trainerbattle_rematch_double TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxannePreRematch, RustboroCity_Gym_Text_RoxanneRematchDefeat, RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons
	msgbox RustboroCity_Gym_Text_RoxannePostRematch, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Josh::
	trainerbattle_single TRAINER_JOSH, RustboroCity_Gym_Text_JoshIntro, RustboroCity_Gym_Text_JoshDefeat
	msgbox RustboroCity_Gym_Text_JoshPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Tommy::
	trainerbattle_single TRAINER_TOMMY, RustboroCity_Gym_Text_TommyIntro, RustboroCity_Gym_Text_TommyDefeat
	msgbox RustboroCity_Gym_Text_TommyPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Marc::
	trainerbattle_single TRAINER_MARC, RustboroCity_Gym_Text_MarcIntro, RustboroCity_Gym_Text_MarcDefeat
	msgbox RustboroCity_Gym_Text_MarcPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_RUSTBORO_GYM, RustboroCity_Gym_EventScript_GymGuidePostVictory
	msgbox RustboroCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_GymGuidePostVictory::
	msgbox RustboroCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_GymStatueCertified::
	msgbox RustboroCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_GymStatue::
	msgbox RustboroCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_RegisterRoxanne::
	lockall
	pokenavcall RustboroCity_Gym_Text_RoxanneRegisterCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox RustboroCity_Gym_Text_RegisteredRoxanne, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_ROXANNE_MATCH_CALL
	clearflag FLAG_ENABLE_ROXANNE_FIRST_CALL
	releaseall
	end

RustboroCity_Gym_Text_GymGuideAdvice:
	.string "¡Eh! ¿Qué tal?\p"
	.string "¡Escúchame!\n"
	.string "¿Te gustaría ganar el CAMPEONATO?\p"
	.string "Yo no soy ENTRENADOR, pero sé\n"
	.string "darte consejos para ganar.\p"
	.string "¡Pues decidido! ¡Iremos a por el\n"
	.string "CAMPEONATO POKéMON juntos!\p"
	.string "Tu trabajo como ENTRENADOR es\n"
	.string "conseguir MEDALLAS, ¿verdad?\p"
	.string "¡Pero los LÍDERES no son blandos!\p"
	.string "¡Y ahí entro yo!\n"
	.string "¡Estoy aquí para darte consejos!\p"
	.string "PETRA, la LÍDER del GIMNASIO, usa\n"
	.string "POKéMON de tipo ROCA.\p"
	.string "El tipo ROCA es muy resistente, pero\n"
	.string "no aguanta los movimientos de\l"
	.string "tipo AGUA y PLANTA.\p"
	.string "Ven a verme después si vences\n"
	.string "a la LÍDER.\p"
	.string "¡Venga, a por ella!$"

RustboroCity_Gym_Text_GymGuidePostVictory:
	.string "¡Hala! ¡Qué victoria tan increíble!\n"
	.string "¡Mis ánimos han funcionado!\p"
	.string "¡Genial!\n"
	.string "Mira tu FICHA DE ENTRENADOR.\p"
	.string "La MEDALLA PIEDRA que has ganado\n"
	.string "debería estar registrada.\p"
	.string "O sea…\p"
	.string "¡Has subido el primer escalón\n"
	.string "hacia el CAMPEONATO!\p"
	.string "¡Eso tiene que sentar de maravilla!$"

RustboroCity_Gym_Text_JoshIntro:
	.string "¡No subestimes a los ENTRENADORES del\n"
	.string "GIMNASIO! ¡Te enseñaré por qué!$"

RustboroCity_Gym_Text_JoshDefeat:
	.string "Tienes demasiado nivel para mí…$"

RustboroCity_Gym_Text_JoshPostBattle:
	.string "¡Aún no has visto el terrible poder\n"
	.string "del tipo ROCA!$"

RustboroCity_Gym_Text_TommyIntro:
	.string "¡Si no me ganas a mí, no tendrás nada\n"
	.string "que hacer contra PETRA!$"

RustboroCity_Gym_Text_TommyDefeat:
	.string "¡Hala! ¡Tienes potencial!$"

RustboroCity_Gym_Text_TommyPostBattle:
	.string "PETRA es mucho más fuerte\n"
	.string "que yo.\p"
	.string "¡Ve con cuidado!$"

RustboroCity_Gym_Text_MarcIntro:
	.string "Estaremos en mitad de la ciudad,\n"
	.string "pero ¿y qué?\p"
	.string "¡Mis POKéMON ROCA necesitan sitio\n"
	.string "para arrasar!$"

RustboroCity_Gym_Text_MarcDefeat:
	.string "¡Madre mía!\n"
	.string "¡Qué rival tan peleón!$"

RustboroCity_Gym_Text_MarcPostBattle:
	.string "Hay que reconocérselo a nuestra LÍDER.\p"
	.string "Tuvo cabeza para elegir el tipo ROCA\n"
	.string "tan joven.$"

RustboroCity_Gym_Text_RoxanneIntro:
	.string "Hola, soy PETRA, la LÍDER del\n"
	.string "GIMNASIO POKéMON de FÉRRICA.\p"
	.string "Me hice LÍDER para poner en práctica\n"
	.string "en combate lo que aprendí en la\l"
	.string "ESCUELA de ENTRENADORES POKéMON.\p"
	.string "¿Serías tan amable de enseñarme cómo\n"
	.string "combates y con qué POKéMON?$"

RustboroCity_Gym_Text_RoxanneDefeat:
	.string "Así que…\n"
	.string "He perdido…\p"
	.string "Parece que todavía me queda mucho\n"
	.string "por aprender…\p"
	.string "Lo entiendo.\p"
	.string "Las normas de la LIGA POKéMON dicen\n"
	.string "que hay que dar esto a quien venza\l"
	.string "a un LÍDER de GIMNASIO.\p"
	.string "Acepta la MEDALLA PIEDRA oficial de\n"
	.string "la LIGA POKéMON.$"

RustboroCity_Gym_Text_ReceivedStoneBadge:
	.string "¡{PLAYER} ha recibido la MEDALLA\n"
	.string "PIEDRA de PETRA!$"

RustboroCity_Gym_Text_StoneBadgeInfoTakeThis:
	.string "La MEDALLA PIEDRA sube el ATAQUE\n"
	.string "de tus POKéMON.\p"
	.string "También les permite usar el movimiento\n"
	.string "de MO CORTE fuera de los combates.\p"
	.string "Toma también esto, por favor.$"

RustboroCity_Gym_Text_ExplainRockTomb:
	.string "Esa MÁQUINA TÉCNICA, la MT39,\n"
	.string "contiene TUMBA ROCAS.\p"
	.string "No solo hace daño tirando rocas,\n"
	.string "sino que también baja la VELOCIDAD.\p"
	.string "Una MT enseña al instante el\n"
	.string "movimiento a un POKéMON.\p"
	.string "Recuerda que una MT solo se usa\n"
	.string "una vez, así que piénsalo bien.$"

RustboroCity_Gym_Text_RoxannePostBattle:
	.string "Como eres tan fuerte, deberías\n"
	.string "desafiar a otros LÍDERES.\p"
	.string "Luchando contra muchos ENTRENADORES\n"
	.string "aprenderás muchas cosas.$"

RustboroCity_Gym_Text_GymStatue:
	.string "GIMNASIO POKéMON DE FÉRRICA$"

RustboroCity_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON DE FÉRRICA\p"
	.string "RECONOCIDOS POR PETRA:\n"
	.string "{PLAYER}$"

RustboroCity_Gym_Text_RoxanneRegisterCall:
	.string "… … … … … …\n"
	.string "… … … … … ¡Bip!\p"
	.string "PETRA: Oh, hola, ¿{PLAYER}?\n"
	.string "Soy PETRA, de CIUDAD FÉRRICA.\p"
	.string "MARCIAL me ha contado que subes\n"
	.string "entre los ENTRENADORES a una\l"
	.string "velocidad increíble.\p"
	.string "Bueno, prefiero no pensar que no\n"
	.string "puedo ganarte.\p"
	.string "Te prometo que mejoraré mi GIMNASIO\n"
	.string "para que nos desafíes otra vez.\p"
	.string "¡Espero que tengas tantas ganas\n"
	.string "como yo de que llegue ese día!\p"
	.string "… … … … … …\n"
	.string "… … … … … ¡Clic!$"

RustboroCity_Gym_Text_RegisteredRoxanne:
	.string "Has registrado a la LÍDER de GIMNASIO\n"
	.string "PETRA en el POKéNAV.$"

RustboroCity_Gym_Text_RoxannePreRematch:
	.string "ROXANNE: I'm so glad to see you again.\n"
	.string "I'm ROXANNE, the GYM LEADER here.\p"
	.string "I'm sure we've both experienced many\n"
	.string "battles since we last met.\p"
	.string "I would like to see how much better\n"
	.string "we've become. Let us battle!$"

RustboroCity_Gym_Text_RoxanneRematchDefeat:
	.string "Grr…\n"
	.string "Again, I have lost…$"

RustboroCity_Gym_Text_RoxannePostRematch:
	.string "ROXANNE: I still have much to learn\n"
	.string "when it comes to battling POKéMON.\p"
	.string "That awareness makes me love battling\n"
	.string "all that much more!$"

RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons:
	.string "ROXANNE: I'm so glad to see you again.\n"
	.string "I'm ROXANNE, the GYM LEADER here.\p"
	.string "I'm sure we've both experienced many\n"
	.string "battles since we last met.\p"
	.string "I would like to see how much better\n"
	.string "we've become…\p"
	.string "Oh, no…\n"
	.string "You only have one POKéMON with you?\p"
	.string "Please return with at least one more\n"
	.string "POKéMON.$"
