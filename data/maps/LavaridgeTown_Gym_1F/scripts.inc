LavaridgeTown_Gym_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_Gym_1F_OnTransition
	.byte 0

LavaridgeTown_Gym_1F_OnTransition:
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	call LavaridgeTown_Gym_1F_EventScript_CheckBuryTrainers
	end

@ Unclear where/if these temp vars are getting checked
LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars::
	setvar VAR_TEMP_B, 0
	setvar VAR_TEMP_C, 0
	setvar VAR_TEMP_D, 0
	setvar VAR_TEMP_E, 0
	setvar VAR_TEMP_F, 0
	goto_if_defeated TRAINER_COLE, LavaridgeTown_Gym_1F_EventScript_SetGeraldTempVar
	setvar VAR_TEMP_B, 1
LavaridgeTown_Gym_1F_EventScript_SetGeraldTempVar::
	goto_if_defeated TRAINER_GERALD, LavaridgeTown_Gym_1F_EventScript_SetAxleTempVar
	setvar VAR_TEMP_C, 1
LavaridgeTown_Gym_1F_EventScript_SetAxleTempVar::
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar
	setvar VAR_TEMP_D, 1
LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar::
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars
	setvar VAR_TEMP_E, 1
LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars::
	return

LavaridgeTown_Gym_1F_EventScript_CheckBuryTrainers::
	goto_if_defeated TRAINER_COLE, LavaridgeTown_Gym_1F_EventScript_CheckBuryGerald
	setobjectmovementtype LOCALID_COLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryGerald::
	goto_if_defeated TRAINER_GERALD, LavaridgeTown_Gym_1F_EventScript_CheckBuryAxle
	setobjectmovementtype LOCALID_GERALD, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryAxle::
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_CheckBuryDanielle
	setobjectmovementtype LOCALID_AXLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryDanielle::
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndCheckBuryTrainers
	setobjectmovementtype LOCALID_DANIELLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_EndCheckBuryTrainers::
	return

LavaridgeTown_Gym_1F_EventScript_Flannery::
	trainerbattle_single TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryIntro, LavaridgeTown_Gym_1F_Text_FlanneryDefeat, LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, LavaridgeTown_Gym_1F_EventScript_FlanneryRematch
	goto_if_unset FLAG_RECEIVED_TM_OVERHEAT, LavaridgeTown_Gym_1F_EventScript_GiveOverheat2
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostBattle, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated::
	message LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_WHITEOUT_TO_LAVARIDGE
	setflag FLAG_DEFEATED_LAVARIDGE_GYM
	setflag FLAG_BADGE04_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 4
	call Common_EventScript_SetGymTrainers
	setflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	setvar VAR_LAVARIDGE_TOWN_STATE, 1
	call LavaridgeTown_Gym_1F_EventScript_GiveOverheat
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox LavaridgeTown_Gym_1F_Text_RegisteredFlannery, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_FLANNERY_MATCH_CALL
	release
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat2::
	giveitem ITEM_TM_OVERHEAT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_OVERHEAT
	release
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat::
	giveitem ITEM_TM_OVERHEAT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_OVERHEAT
	return

LavaridgeTown_Gym_1F_EventScript_FlanneryRematch::
	trainerbattle_rematch_double TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryPreRematch, LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat, LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostRematch, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Cole::
	trainerbattle_lavaridge LOCALID_COLE, TRAINER_COLE, LavaridgeTown_Gym_1F_Text_ColeIntro, LavaridgeTown_Gym_1F_Text_ColeDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	end

LavaridgeTown_Gym_EventScript_CheckTrainerScript::
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	release
	special ShouldTryGetTrainerScript
	goto_if_eq VAR_RESULT, 1, EventScript_GotoTrainerScript
	end

LavaridgeTown_Gym_1F_EventScript_Axle::
	trainerbattle_lavaridge LOCALID_AXLE, TRAINER_AXLE, LavaridgeTown_Gym_1F_Text_AxleIntro, LavaridgeTown_Gym_1F_Text_AxleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_AxlePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Keegan::
	trainerbattle_lavaridge LOCALID_KEEGAN, TRAINER_KEEGAN, LavaridgeTown_Gym_B1F_Text_KeeganIntro, LavaridgeTown_Gym_B1F_Text_KeeganDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_KeeganPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Danielle::
	trainerbattle_lavaridge LOCALID_DANIELLE, TRAINER_DANIELLE, LavaridgeTown_Gym_1F_Text_DanielleIntro, LavaridgeTown_Gym_1F_Text_DanielleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_DaniellePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Gerald::
	trainerbattle_lavaridge LOCALID_GERALD, TRAINER_GERALD, LavaridgeTown_Gym_1F_Text_GeraldIntro, LavaridgeTown_Gym_1F_Text_GeraldDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_GeraldPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Jace::
	trainerbattle_lavaridge LOCALID_JACE, TRAINER_JACE, LavaridgeTown_Gym_B1F_Text_JaceIntro, LavaridgeTown_Gym_B1F_Text_JaceDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_JacePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Jeff::
	trainerbattle_lavaridge LOCALID_JEFF, TRAINER_JEFF, LavaridgeTown_Gym_B1F_Text_JeffIntro, LavaridgeTown_Gym_B1F_Text_JeffDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_JeffPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Eli::
	trainerbattle_lavaridge LOCALID_ELI, TRAINER_ELI, LavaridgeTown_Gym_B1F_Text_EliIntro, LavaridgeTown_Gym_B1F_Text_EliDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_EliPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory
	msgbox LavaridgeTown_Gym_1F_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory::
	msgbox LavaridgeTown_Gym_1F_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_GymStatueCertified::
	msgbox LavaridgeTown_Gym_1F_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_EventScript_GymStatue::
	msgbox LavaridgeTown_Gym_1F_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_Text_GymGuideAdvice:
	.string "¡Eh! ¿Qué tal, futura estrella de\n"
	.string "la LIGA, {PLAYER}?\p"
	.string "CANDELA, la LÍDER de LAVACALDA,\n"
	.string "usa POKéMON de tipo FUEGO.\p"
	.string "Su pasión por los POKéMON arde con\n"
	.string "más fuerza que un volcán.\p"
	.string "¡No te acerques mucho o te quemarás!\n"
	.string "¡Échale agua y a por ella!$"

LavaridgeTown_Gym_1F_Text_GymGuidePostVictory:
	.string "¡Uf! ¡Ha sido un combate abrasador!$"

LavaridgeTown_Gym_1F_Text_ColeIntro:
	.string "¡Ayayayayay!\n"
	.string "¡Qué calor!$"

LavaridgeTown_Gym_1F_Text_ColeDefeat:
	.string "El sudor no me deja ver…$"

LavaridgeTown_Gym_1F_Text_ColePostBattle:
	.string "Enterrarse en arena caliente mejora\n"
	.string "la circulación.\p"
	.string "Va muy bien para el dolor de\n"
	.string "articulaciones.$"

LavaridgeTown_Gym_1F_Text_AxleIntro:
	.string "Estoy intentando relajarme.\n"
	.string "¡No vengas a estresarme!$"

LavaridgeTown_Gym_1F_Text_AxleDefeat:
	.string "¡Espero que CANDELA te achicharre!$"

LavaridgeTown_Gym_1F_Text_AxlePostBattle:
	.string "Aaah… Uf…\p"
	.string "Si pasas mucho tiempo enterrado en\n"
	.string "arena caliente, acabas agotado…$"

LavaridgeTown_Gym_B1F_Text_KeeganIntro:
	.string "Ya debes de estar cansado.\n"
	.string "Te gustaría descansar en la arena\l"
	.string "caliente, ¿a que sí?\p"
	.string "Pero que sepas que no perder la\n"
	.string "voluntad es una capacidad importante\l"
	.string "para cualquier ENTRENADOR.$"

LavaridgeTown_Gym_B1F_Text_KeeganDefeat:
	.string "Quien juega con fuego, se quema…$"

LavaridgeTown_Gym_B1F_Text_KeeganPostBattle:
	.string "Tu habilidad es real…\n"
	.string "Pero nuestra LÍDER, CANDELA, es fuerte.\p"
	.string "Si no tienes cuidado, saldrás\n"
	.string "muy quemado.$"

LavaridgeTown_Gym_1F_Text_GeraldIntro:
	.string "¿Aguantarán tus POKéMON un calor\n"
	.string "de 200 grados?$"

LavaridgeTown_Gym_1F_Text_GeraldDefeat:
	.string "No ardía lo suficiente…$"

LavaridgeTown_Gym_1F_Text_GeraldPostBattle:
	.string "El magma está a unos 200 grados\n"
	.string "o más.\p"
	.string "Tus POKéMON me han ganado, así que\n"
	.string "sobrevivirían en el magma sin problema.$"

LavaridgeTown_Gym_1F_Text_DanielleIntro:
	.string "Esto…\n"
	.string "Vale, combatiré contigo.$"

LavaridgeTown_Gym_1F_Text_DanielleDefeat:
	.string "Oh, pero qué fuerza tienes.$"

LavaridgeTown_Gym_1F_Text_DaniellePostBattle:
	.string "Voy a ser una ENTRENADORA guapa y\n"
	.string "fuerte como CANDELA.$"

LavaridgeTown_Gym_B1F_Text_JaceIntro:
	.string "¡Venga, espabila!\n"
	.string "¡Vamos antes de que se me enfríe\l"
	.string "el ánimo!$"

LavaridgeTown_Gym_B1F_Text_JaceDefeat:
	.string "Hace tanto calor y, aun así, tengo\n"
	.string "el corazón helado…$"

LavaridgeTown_Gym_B1F_Text_JacePostBattle:
	.string "Con lo que te arde el espíritu de\n"
	.string "combate, puede que tengas una\l"
	.string "oportunidad contra nuestra LÍDER.$"

LavaridgeTown_Gym_B1F_Text_JeffIntro:
	.string "¿Ves cómo arden las llamas?\n"
	.string "¡Arden esperando mi victoria!$"

LavaridgeTown_Gym_B1F_Text_JeffDefeat:
	.string "Algo ha salido mal.$"

LavaridgeTown_Gym_B1F_Text_JeffPostBattle:
	.string "Bueno, ¿y qué? ¿Y qué, eh?\n"
	.string "¡Puedo andar descalzo sobre brasas!\p"
	.string "… ¡Ni se te ocurra intentarlo!$"

LavaridgeTown_Gym_B1F_Text_EliIntro:
	.string "Me encantan las montañas, pero sobre\n"
	.string "todo los volcanes.$"

LavaridgeTown_Gym_B1F_Text_EliDefeat:
	.string "Bueno, me parece que he perdido sin\n"
	.string "controlar nada en ningún momento.$"

LavaridgeTown_Gym_B1F_Text_EliPostBattle:
	.string "Estoy aquí porque me hice fan del\n"
	.string "poder de CANDELA.\p"
	.string "Jejejeje.$"

LavaridgeTown_Gym_1F_Text_FlanneryIntro:
	.string "Bienven… No, espera.\p"
	.string "¡ENTRENADOR insignificante, qué bien\n"
	.string "que hayas llegado hasta aquí!\p"
	.string "Me han confiado el… No, espera.\p"
	.string "¡Soy CANDELA, y soy la LÍDER de este\n"
	.string "GIMNASIO!\p"
	.string "Eh…\n"
	.string "¡No me subestimes, aunque lleve poco\l"
	.string "tiempo de LÍDER!\p"
	.string "Con las técnicas que heredé de mi\n"
	.string "abuelo, te, eh… ¡demostraré los\l"
	.string "movimientos ardientes de esta tierra!$"

LavaridgeTown_Gym_1F_Text_FlanneryDefeat:
	.string "Oh…\n"
	.string "Creo que me he esforzado demasiado…\p"
	.string "Yo… Hace poco que soy LÍDER\n"
	.string "de GIMNASIO.\p"
	.string "He intentado ser alguien que\n"
	.string "no soy.\p"
	.string "Tengo que hacer las cosas a mi manera.\n"
	.string "Si no, mis POKéMON se confundirán.\p"
	.string "Gracias por enseñármelo.\n"
	.string "Por eso, te mereces esto.$"

LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge:
	.string "{PLAYER} ha recibido la MEDALLA\n"
	.string "CALOR de CANDELA.$"

LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis:
	.string "Con la MEDALLA CALOR, todos los\n"
	.string "POKéMON hasta el nivel 50, incluso los\l"
	.string "que te den en intercambios, te\l"
	.string "obedecerán por completo.\p"
	.string "Y además permite usar el movimiento\n"
	.string "de MO FUERZA fuera del combate.\p"
	.string "Esto es una muestra de mi gratitud.\n"
	.string "¡No te cortes y cógelo!$"

LavaridgeTown_Gym_1F_Text_ExplainOverheat:
	.string "Esa MT50 contiene SOFOCO.\p"
	.string "Ese movimiento hace muchísimo daño\n"
	.string "al rival.\p"
	.string "Pero también baja mucho el AT. ESP.\n"
	.string "del POKéMON que lo usa. Quizá no\l"
	.string "sirva para combates largos.$"

LavaridgeTown_Gym_1F_Text_RegisteredFlannery:
	.string "Has registrado a la LÍDER de GIMNASIO\n"
	.string "CANDELA en el POKéNAV.$"

LavaridgeTown_Gym_1F_Text_FlanneryPostBattle:
	.string "Tu fuerza me recuerda a alguien…\p"
	.string "¡Oh! ¡Ya sé! Combates como NORMAN,\n"
	.string "el LÍDER del GIMNASIO de PETALIA.$"

LavaridgeTown_Gym_1F_Text_GymStatue:
	.string "GIMNASIO POKéMON DE LAVACALDA$"

LavaridgeTown_Gym_1F_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON DE LAVACALDA\p"
	.string "RECONOCIDOS POR CANDELA:\n"
	.string "{PLAYER}$"

LavaridgeTown_Gym_1F_Text_FlanneryPreRematch:
	.string "FLANNERY: Losing a battle isn't going\n"
	.string "to deflate me.\p"
	.string "I love POKéMON.\n"
	.string "I love to battle.\l"
	.string "And… I love this GYM!\p"
	.string "Let's exchange superhot moves\n"
	.string "in another battle!$"

LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat:
	.string "Whew!\n"
	.string "On the verge of eruption!$"

LavaridgeTown_Gym_1F_Text_FlanneryPostRematch:
	.string "FLANNERY: I lost the match,\n"
	.string "but I'm completely satisfied.\p"
	.string "It's not often I get to enjoy a battle\n"
	.string "this heated.\p"
	.string "Let's have another one like this\n"
	.string "again sometime!$"

LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons:
	.string "FLANNERY: Losing a battle isn't going\n"
	.string "to deflate me.\p"
	.string "I love POKéMON.\n"
	.string "I love to battle.\l"
	.string "And… I love this GYM!\p"
	.string "Let's exchange superhot moves\n"
	.string "in another battle!\p"
	.string "Oh, wait. Do you only have one POKéMON\n"
	.string "that can battle?\p"
	.string "I hate to say this, but when you come\n"
	.string "see me, bring at least two POKéMON.$"
