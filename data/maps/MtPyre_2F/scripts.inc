MtPyre_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_TRANSITION, CaveHole_FixCrackedGround
	map_script MAP_SCRIPT_ON_RESUME, MtPyre_2F_SetHoleWarp
	.byte 0

MtPyre_2F_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_MT_PYRE_1F
	end

MtPyre_2F_EventScript_Woman::
	msgbox MtPyre_2F_Text_MemoriesOfSkitty, MSGBOX_NPC
	end

MtPyre_2F_EventScript_PokefanM::
	msgbox MtPyre_2F_Text_TumbledFromFloorAbove, MSGBOX_NPC
	end

MtPyre_2F_EventScript_Mark::
	trainerbattle_single TRAINER_MARK, MtPyre_2F_Text_MarkIntro, MtPyre_2F_Text_MarkDefeat
	msgbox MtPyre_2F_Text_MarkPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Luke::
	trainerbattle_double TRAINER_DEZ_AND_LUKE, MtPyre_2F_Text_LukeIntro, MtPyre_2F_Text_LukeDefeat, MtPyre_2F_Text_LukeNotEnoughMons
	msgbox MtPyre_2F_Text_LukePostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Dez::
	trainerbattle_double TRAINER_DEZ_AND_LUKE, MtPyre_2F_Text_DezIntro, MtPyre_2F_Text_DezDefeat, MtPyre_2F_Text_DezNotEnoughMons
	msgbox MtPyre_2F_Text_DezPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Leah::
	trainerbattle_single TRAINER_LEAH, MtPyre_2F_Text_LeahIntro, MtPyre_2F_Text_LeahDefeat
	msgbox MtPyre_2F_Text_LeahPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Zander::
	trainerbattle_single TRAINER_ZANDER, MtPyre_2F_Text_ZanderIntro, MtPyre_2F_Text_ZanderDefeat
	msgbox MtPyre_2F_Text_ZanderPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_Text_MemoriesOfSkitty:
	.string "Los recuerdos de mi querido SKITTY…\n"
	.string "Se me llenan los ojos de lágrimas.$"

MtPyre_2F_Text_TumbledFromFloorAbove:
	.string "Ay, ay… Hay agujeros en el suelo\n"
	.string "aquí y allá.\p"
	.string "No me di cuenta y me caí del piso\n"
	.string "de arriba.$"

MtPyre_2F_Text_MarkIntro:
	.string "¡Eh! ¿Buscas POKéMON?\n"
	.string "¡Me has seguido! ¡Qué descaro!$"

MtPyre_2F_Text_MarkDefeat:
	.string "¡Aaaaah!\n"
	.string "¡Lo siento, perdóname, por favor!$"

MtPyre_2F_Text_MarkPostBattle:
	.string "Aquí no viene mucha gente, así que\n"
	.string "pensé que habría POKéMON raros.$"

MtPyre_2F_Text_LukeIntro:
	.string "LUKE: Estamos aquí por una apuesta.\p"
	.string "Jeje, si le demuestro lo guay que soy,\n"
	.string "se enamorará de mí. ¡Lo sé!\p"
	.string "¡Ya sé! ¡Te machacaré y le\n"
	.string "demostraré lo guay que soy!$"

MtPyre_2F_Text_LukeDefeat:
	.string "LUKE: ¡Huy!$"

MtPyre_2F_Text_LukePostBattle:
	.string "LUKE: Bueno, hemos perdido, ¡pero\n"
	.string "no pasa nada! Estoy a tu lado.\l"
	.string "¡Superaremos esta apuesta!$"

MtPyre_2F_Text_LukeNotEnoughMons:
	.string "LUKE: Si quieres enfrentarte a mí,\n"
	.string "trae más POKéMON.\p"
	.string "¡Si no, no podré demostrarle a mi\n"
	.string "chica lo guay que soy!$"

MtPyre_2F_Text_DezIntro:
	.string "DEZ: He venido por una apuesta con\n"
	.string "mi novio.\p"
	.string "Da muchísimo miedo, pero estoy con\n"
	.string "mi novio. No pasa nada.\p"
	.string "¡Ya sé! ¡Haré que mi novio quede\n"
	.string "guay ganándote!$"

MtPyre_2F_Text_DezDefeat:
	.string "DEZ: ¡Buaaah! ¡Qué miedo!$"

MtPyre_2F_Text_DezPostBattle:
	.string "DEZ: ¡Estamos tan enamorados que\n"
	.string "nos da igual perder!$"

MtPyre_2F_Text_DezNotEnoughMons:
	.string "DEZ: Si quieres desafiarnos, trae al\n"
	.string "menos dos POKéMON.\p"
	.string "Mi novio es fuerte.\n"
	.string "Con un POKéMON no basta.$"

MtPyre_2F_Text_LeahIntro:
	.string "No te conozco de nada…\n"
	.string "¡Vete antes de que te pase algo!$"

MtPyre_2F_Text_LeahDefeat:
	.string "Mmm…\n"
	.string "Aguantas bien.$"

MtPyre_2F_Text_LeahPostBattle:
	.string "Mi familia entrena aquí desde la época\n"
	.string "de mi bisabuela…\p"
	.string "Mi deber es proteger esta\n"
	.string "montaña…$"

MtPyre_2F_Text_ZanderIntro:
	.string "¡Kiyaaaaah!\n"
	.string "¡Qué miedo!$"

MtPyre_2F_Text_ZanderDefeat:
	.string "¡Nooooooo!\n"
	.string "¡He perdido los nervios!$"

MtPyre_2F_Text_ZanderPostBattle:
	.string "Me asusto cada vez que veo algo\n"
	.string "moverse…\p"
	.string "No tendría que haber venido aquí\n"
	.string "a entrenar…$"

