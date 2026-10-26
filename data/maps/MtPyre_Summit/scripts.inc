MtPyre_Summit_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtPyre_Summit_OnTransition
	.byte 0

MtPyre_Summit_OnTransition:
	call_if_eq VAR_MT_PYRE_STATE, 2, MtPyre_Summit_EventScript_SetArchieMaxiePositions
	end

MtPyre_Summit_EventScript_SetArchieMaxiePositions::
	setobjectxyperm LOCALID_MT_PYRE_SUMMIT_MAXIE, 23, 6
	setobjectxyperm LOCALID_MT_PYRE_SUMMIT_ARCHIE, 22, 6
	end

MtPyre_Summit_EventScript_TeamAquaTrigger0::
	lockall
	setvar VAR_0x8008, 0
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaTrigger1::
	lockall
	setvar VAR_0x8008, 1
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto MtPyre_Summit_EventScript_TeamAquaExits
	end

MtPyre_Summit_EventScript_TeamAquaExits::
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_ArchieFacePlayer0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_ArchieFacePlayer1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_ArchieFacePlayer2
	msgbox MtPyre_Summit_Text_ArchieWeGotTheOrbLetsGo, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MT_PYRE_SUMMIT_ARCHIE
	removeobject LOCALID_MT_PYRE_SUMMIT_GRUNT_1
	removeobject LOCALID_MT_PYRE_SUMMIT_GRUNT_2
	removeobject LOCALID_MT_PYRE_SUMMIT_GRUNT_3
	removeobject LOCALID_MT_PYRE_SUMMIT_GRUNT_4
	setflag FLAG_HIDE_MT_PYRE_SUMMIT_ARCHIE
	setflag FLAG_HIDE_MT_PYRE_SUMMIT_TEAM_AQUA
	fadedefaultbgm
	fadescreenswapbuffers FADE_FROM_BLACK
	delay 20
	setvar VAR_MT_PYRE_STATE, 1
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_OldLadyApproachPlayer0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_OldLadyApproachPlayer1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_OldLadyApproachPlayer2
	msgbox MtPyre_Summit_Text_BothOrbsTakenMagmaLeftThis, MSGBOX_DEFAULT
	giveitem ITEM_MAGMA_EMBLEM
	setflag FLAG_RECEIVED_RED_OR_BLUE_ORB
	setflag FLAG_HIDE_JAGGED_PASS_MAGMA_GUARD
	releaseall
	end

MtPyre_Summit_EventScript_ArchieFacePlayer0::
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieFacePlayer0
	waitmovement 0
	return

@ Archie is already facing player
MtPyre_Summit_EventScript_ArchieFacePlayer1::
	return

MtPyre_Summit_EventScript_ArchieFacePlayer2::
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieFacePlayer2
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer0::
	applymovement LOCALID_MT_PYRE_SUMMIT_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer0
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer1::
	applymovement LOCALID_MT_PYRE_SUMMIT_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer1
	waitmovement 0
	return

MtPyre_Summit_EventScript_OldLadyApproachPlayer2::
	applymovement LOCALID_MT_PYRE_SUMMIT_OLD_LADY, MtPyre_Summit_Movement_OldLadyApproachPlayer2
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

MtPyre_Summit_Movement_OldLadyApproachPlayer0:
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_OldLadyApproachPlayer1:
	walk_down
	step_end

MtPyre_Summit_Movement_OldLadyApproachPlayer2:
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_ArchieFacePlayer0:
	walk_left
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_ArchieFacePlayer2:
	walk_right
	walk_in_place_faster_down
	step_end

MtPyre_Summit_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE, MtPyre_Summit_EventScript_OldManAfterRayquaza
	msgbox MtPyre_Summit_Text_WillYouHearOutMyTale, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, MtPyre_Summit_EventScript_OldManTale
	call_if_eq VAR_RESULT, NO, MtPyre_Summit_EventScript_DeclineOldManTale
	release
	end

MtPyre_Summit_EventScript_OldManAfterRayquaza::
	msgbox MtPyre_Summit_Text_HearTheNewLegendOfHoenn, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, MtPyre_Summit_EventScript_OldManNewTale
	call_if_eq VAR_RESULT, NO, MtPyre_Summit_EventScript_DeclineOldManTale
	release
	end

MtPyre_Summit_EventScript_OldManTale::
	msgbox MtPyre_Summit_Text_GroudonKyogreTale, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_DeclineOldManTale::
	msgbox MtPyre_Summit_Text_WellThatTooIsFine, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_OldManNewTale::
	msgbox MtPyre_Summit_Text_HoennTrioTale, MSGBOX_DEFAULT
	return

MtPyre_Summit_EventScript_OldLady::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_RED_OR_BLUE_ORB, MtPyre_Summit_EventScript_OldLadyAfterOrbsReturned
	call_if_ge VAR_MT_PYRE_STATE, 3, MtPyre_Summit_EventScript_OldLadyOrbsReturned
	goto_if_set FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, MtPyre_Summit_EventScript_OldLadyLegendariesAwake
	msgbox MtPyre_Summit_Text_OrbsHaveBeenTaken, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_OldLadyOrbsReturned::
	msgbox MtPyre_Summit_Text_ThoseTwoMenReturnedOrbs, MSGBOX_DEFAULT
	setflag FLAG_RETURNED_RED_OR_BLUE_ORB
	release
	end

MtPyre_Summit_EventScript_OldLadyLegendariesAwake::
	msgbox MtPyre_Summit_Text_GroudonKyogreAwakened, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_OldLadyAfterOrbsReturned::
	msgbox MtPyre_Summit_Text_SuperAncientPokemonTaughtUs, MSGBOX_DEFAULT
	release
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger0::
	lockall
	setvar VAR_0x8008, 0
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger1::
	lockall
	setvar VAR_0x8008, 1
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs
	end

MtPyre_Summit_EventScript_ArchieMaxieReturnOrbs::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 60
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_ArchieMaxieBeginExit0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_ArchieMaxieBeginExit1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_ArchieMaxieBeginExit2
	playse SE_PIN
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, Common_Movement_Delay48
	waitmovement 0
	delay 30
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_MaxieApproachPlayer0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_MaxieApproachPlayer1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_MaxieApproachPlayer2
	msgbox MtPyre_Summit_Text_MaxieSilence, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 0, MtPyre_Summit_EventScript_MaxieApproachArchie0
	call_if_eq VAR_0x8008, 1, MtPyre_Summit_EventScript_MaxieApproachArchie1
	call_if_eq VAR_0x8008, 2, MtPyre_Summit_EventScript_MaxieApproachArchie2
	delay 30
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	removeobject LOCALID_MT_PYRE_SUMMIT_ARCHIE
	removeobject LOCALID_MT_PYRE_SUMMIT_MAXIE
	setvar VAR_MT_PYRE_STATE, 3
	releaseall
	end

MtPyre_Summit_EventScript_ArchieMaxieBeginExit0::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit0
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_ArchieMaxieBeginExit1::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit1
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_ArchieMaxieBeginExit2::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit2
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieExit
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieExit
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer0::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie0
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer0
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer1::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer1
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachPlayer2::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerFaceMaxie
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, MtPyre_Summit_Movement_ArchieWatchMaxie
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieApproachPlayer2
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie0::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie0
	waitmovement 0
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie1::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie1
	waitmovement 0
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_EventScript_MaxieApproachArchie2::
	applymovement LOCALID_PLAYER, MtPyre_Summit_Movement_PlayerWatchMaxie
	applymovement LOCALID_MT_PYRE_SUMMIT_MAXIE, MtPyre_Summit_Movement_MaxieApproachArchie2
	waitmovement 0
	applymovement LOCALID_MT_PYRE_SUMMIT_ARCHIE, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

MtPyre_Summit_Movement_PlayerFaceMaxie0:
	delay_16
	delay_16
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_PlayerFaceMaxie:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_ArchieExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtPyre_Summit_Movement_MaxieExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit0:
	delay_16
	delay_8
	walk_left
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit1:
	delay_16
	delay_8
	walk_right
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_PlayerWatchArchieMaxieExit2:
	delay_16
	delay_8
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer0:
	walk_up
	walk_up
	walk_up
	walk_left
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer1:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_MaxieApproachPlayer2:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_right
	step_end

MtPyre_Summit_Movement_ArchieWatchMaxie:
	delay_16
	walk_in_place_faster_up
	step_end

MtPyre_Summit_Movement_PlayerWatchMaxie:
	delay_16
	walk_in_place_faster_down
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie0:
	walk_down
	walk_right
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie1:
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_Movement_MaxieApproachArchie2:
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

MtPyre_Summit_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_1, MtPyre_Summit_Text_Grunt1Intro, MtPyre_Summit_Text_Grunt1Defeat
	msgbox MtPyre_Summit_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_2, MtPyre_Summit_Text_Grunt2Intro, MtPyre_Summit_Text_Grunt2Defeat
	msgbox MtPyre_Summit_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_3, MtPyre_Summit_Text_Grunt3Intro, MtPyre_Summit_Text_Grunt3Defeat
	msgbox MtPyre_Summit_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_MT_PYRE_4, MtPyre_Summit_Text_Grunt4Intro, MtPyre_Summit_Text_Grunt4Defeat
	msgbox MtPyre_Summit_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_Summit_Text_Grunt1Intro:
	.string "¡No! ¡Esos matones del EQUIPO MAGMA\n"
	.string "han llegado antes que nosotros!\p"
	.string "¡No podemos quedarnos atrás!$"

MtPyre_Summit_Text_Grunt1Defeat:
	.string "Creía que eras de los MAGMA y que\n"
	.string "habías vuelto…$"

MtPyre_Summit_Text_Grunt1PostBattle:
	.string "Sí, vale, eres fuerte…\n"
	.string "¡Pero nosotros somos muchos!$"

MtPyre_Summit_Text_Grunt2Intro:
	.string "¡Ja!\n"
	.string "¡Qué mala suerte la tuya!\p"
	.string "Si hubieras llegado antes, solo\n"
	.string "habrías tenido que combatir con el\l"
	.string "EQUIPO MAGMA, que son unos blandos.\p"
	.string "¡Pero como llegas ahora, te toca\n"
	.string "enfrentarte a nosotros, los duros!$"

MtPyre_Summit_Text_Grunt2Defeat:
	.string "Urgh… Tendría que haberte dejado al\n"
	.string "EQUIPO MAGMA primero…$"

MtPyre_Summit_Text_Grunt2PostBattle:
	.string "¡No sabes nada!\n"
	.string "¿Por qué te metes con nosotros?$"

MtPyre_Summit_Text_Grunt3Intro:
	.string "Tú…\n"
	.string "Te vimos en el MONTE CENIZO.\p"
	.string "No eres de ningún EQUIPO, así que\n"
	.string "¿qué haces aquí?$"

MtPyre_Summit_Text_Grunt3Defeat:
	.string "Si te vas a meter con alguien, que\n"
	.string "sea con el EQUIPO MAGMA…$"

MtPyre_Summit_Text_Grunt3PostBattle:
	.string "Je, ¡da igual!\n"
	.string "¡Hemos ganado tiempo!\p"
	.string "¡El JEFE ya habrá conseguido lo que\n"
	.string "buscaba!$"

MtPyre_Summit_Text_Grunt4Intro:
	.string "¡Ah, ya sé!\n"
	.string "Quisiste entrar en el EQUIPO MAGMA,\l"
	.string "¡pero no te quisieron!\p"
	.string "¡Pues no creas que te vamos a dejar\n"
	.string "entrar en el EQUIPO AQUA!$"

MtPyre_Summit_Text_Grunt4Defeat:
	.string "Si tantas ganas tienes de entrar en\n"
	.string "el EQUIPO AQUA, lo podemos pensar…$"

MtPyre_Summit_Text_Grunt4PostBattle:
	.string "Los miembros y nuestro líder hacemos\n"
	.string "un equipo genial.$"

MtPyre_Summit_Text_ArchieWeGotTheOrbLetsGo:
	.string "AQUILES: MAGNO, del EQUIPO MAGMA, se\n"
	.string "nos ha adelantado, pero ya tenemos\l"
	.string "lo que queríamos.\p"
	.string "¡El PRISMA ROJO que se guardaba en el\n"
	.string "MONTE PÍRICO ya es mío, de AQUILES!\p"
	.string "Fufufu… ¡Ahora podremos cumplir\n"
	.string "nuestro objetivo final!\p"
	.string "¡Vamos, EQUIPO!\n"
	.string "¡Nos retiramos!$"

MtPyre_Summit_Text_BothOrbsTakenMagmaLeftThis:
	.string "Ay, no…\n"
	.string "Esto no puede estar pasando…\p"
	.string "No solo el PRISMA AZUL, sino también\n"
	.string "el PRISMA ROJO se lo han llevado…\p"
	.string "El PRISMA AZUL y el PRISMA ROJO no\n"
	.string "deben separarse nunca. Van juntos.\p"
	.string "¿Qué pretenden hacer esos hombres\n"
	.string "con los dos PRISMAS?\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Ah, sí. ¿Fue el EQUIPO MAGMA el que\n"
	.string "vino primero y se llevó el PRISMA AZUL?\p"
	.string "Con las prisas, se dejaron esto.\p"
	.string "No sé qué será exactamente.\p"
	.string "Me gustaría que te lo quedaras.\n"
	.string "Quizá te sirva de algo.$"

MtPyre_Summit_Text_OrbsHaveBeenTaken:
	.string "El PRISMA AZUL y el PRISMA ROJO, en\n"
	.string "manos de esos hombres siniestros…\p"
	.string "No deben separarse nunca…\n"
	.string "Me temo que pasará algo terrible…$"

MtPyre_Summit_Text_GroudonKyogreAwakened:
	.string "Ay, madre mía…\p"
	.string "¿Dices que han despertado tanto\n"
	.string "GROUDON como KYOGRE?\p"
	.string "Dicen que el PRISMA AZUL y el PRISMA\n"
	.string "ROJO calmaron la furia de esos\l"
	.string "dos POKéMON…\p"
	.string "También dicen que el verdadero dueño\n"
	.string "de los PRISMAS aún existe.\p"
	.string "Pero nadie sabe quién, o qué, es el\n"
	.string "dueño de los PRISMAS.\p"
	.string "Podría ser una persona, o quizá un\n"
	.string "POKéMON, pero nadie lo sabe.$"

MtPyre_Summit_Text_ThoseTwoMenReturnedOrbs:
	.string "Los dos hombres que se llevaron los\n"
	.string "PRISMAS volvieron a devolverlos solos.\p"
	.string "Esos hombres…\n"
	.string "Quizá no sean tan malos…$"

MtPyre_Summit_Text_SuperAncientPokemonTaughtUs:
	.string "Las encarnaciones de la tierra, el mar\n"
	.string "y el cielo…\p"
	.string "Eso dicen que son los POKéMON\n"
	.string "superancestrales…\p"
	.string "Igual que las personas y los POKéMON\n"
	.string "tenemos vida, nuestro mundo también\l"
	.string "está vivo…\p"
	.string "Eso nos enseñaron los POKéMON\n"
	.string "superancestrales…$"

MtPyre_Summit_Text_WillYouHearOutMyTale:
	.string "En el MONTE PÍRICO calmamos los\n"
	.string "espíritus de los POKéMON que se van…\p"
	.string "Es un lugar alto desde el que se ve\n"
	.string "todo HOENN…\p"
	.string "Aquí deben encontrar consuelo los\n"
	.string "espíritus de los POKéMON…\p"
	.string "¿Será casualidad que estés aquí?…\p"
	.string "¿Escucharás mi relato? ¿Un relato que\n"
	.string "se cuenta desde siempre en HOENN?$"

MtPyre_Summit_Text_GroudonKyogreTale:
	.string "Pasó hace mucho, mucho tiempo…\p"
	.string "El mundo sufrió un choque feroz entre\n"
	.string "el POKéMON de la tierra y el POKéMON\l"
	.string "del mar…\p"
	.string "El POKéMON de la tierra alzó\n"
	.string "montañas y creó continentes…\p"
	.string "El POKéMON del mar alzó olas\n"
	.string "enormes y excavó océanos…\p"
	.string "Su duelo feroz no tenía fin.\p"
	.string "El mundo quedó envuelto en grandes\n"
	.string "incendios y tormentas terribles.\p"
	.string "El PRISMA AZUL y el PRISMA ROJO\n"
	.string "pusieron fin a la catástrofe.\p"
	.string "De los dos PRISMAS salió una luz que\n"
	.string "calmó a los furiosos rivales.\p"
	.string "Los dos, ya tranquilos, se sumergieron\n"
	.string "en lo más hondo del mar, donde al\l"
	.string "final desaparecieron…$"

MtPyre_Summit_Text_WellThatTooIsFine:
	.string "Ya veo…\n"
	.string "Bueno, también está bien…$"

MtPyre_Summit_Text_MaxieSilence:
	.string "MAGNO: {PLAYER}…\p"
	.string "… … … … … …\n"
	.string "… … … … … …$"

MtPyre_Summit_Text_HearTheNewLegendOfHoenn:
	.string "Mi papel es transmitir las leyendas\n"
	.string "de HOENN a las generaciones futuras.\p"
	.string "Y la crisis que acaba de terminar en\n"
	.string "ARRECÍPOLIS ha cambiado una leyenda…\p"
	.string "¿Tienes tiempo para escuchar la\n"
	.string "nueva leyenda de HOENN?$"

MtPyre_Summit_Text_HoennTrioTale:
	.string "Pasó hace mucho, mucho tiempo…\p"
	.string "El mundo sufrió un choque feroz entre\n"
	.string "el POKéMON de la tierra y el POKéMON\l"
	.string "del mar…\p"
	.string "El POKéMON de la tierra alzó\n"
	.string "montañas y creó continentes…\p"
	.string "El POKéMON del mar alzó olas\n"
	.string "enormes y excavó océanos…\p"
	.string "Su duelo feroz no tenía fin.\p"
	.string "El mundo quedó envuelto en grandes\n"
	.string "incendios y tormentas terribles.\p"
	.string "Fue entonces cuando el POKéMON del\n"
	.string "cielo bajó de una tormenta.\p"
	.string "El POKéMON, de un verde intenso,\n"
	.string "calmó a los dos POKéMON furiosos.\p"
	.string "Y, cumplida su misión, el POKéMON\n"
	.string "verde se perdió volando en el cielo…$"

