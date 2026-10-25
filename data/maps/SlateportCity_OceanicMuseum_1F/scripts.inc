SlateportCity_OceanicMuseum_1F_MapScripts::
	.byte 0

SlateportCity_OceanicMuseum_1F_EventScript_EntranceAttendant::
	msgbox SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeLeft::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeRight::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee::
	showmoneybox 0, 0
	msgbox SlateportCity_OceanicMuseum_1F_Text_WouldYouLikeToEnter, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_OceanicMuseum_1F_EventScript_CheckMoneyForFee
	closemessage
	hidemoneybox
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_CheckMoneyForFee::
	checkmoney 50
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_OceanicMuseum_1F_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 50
	updatemoneybox
	msgbox SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 1
	hidemoneybox
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_NotEnoughMoney::
	goto_if_unset FLAG_DELIVERED_DEVON_GOODS, SlateportCity_OceanicMuseum_1F_EventScript_AllowEntranceAnyway
	msgbox SlateportCity_OceanicMuseum_1F_Text_NotEnoughMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_AllowEntranceAnyway::
	msgbox SlateportCity_OceanicMuseum_1F_Text_CatchUpWithYourGroup, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 1
	hidemoneybox
	releaseall
	end

SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter:
	walk_down
	step_end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_AquaExistForGoodOfAll, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OurBossIsntHere, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WouldStuffHereMakeMeRich, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt4::
	msgbox SlateportCity_OceanicMuseum_1F_Text_CanLearnForNefariousDeeds, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt5::
	msgbox SlateportCity_OceanicMuseum_1F_Text_RustboroBungled, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt6::
	msgbox SlateportCity_OceanicMuseum_1F_Text_DidntHaveMoney, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_WhirlpoolExperiment::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WhirlpoolExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_WaterfallExperiment::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WaterfallExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanSoilDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanSoilDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_BeachSandDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_BeachSandDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact3, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_FossilDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_FossilDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_DepthMeasuringMachine::
	msgbox SlateportCity_OceanicMuseum_1F_Text_DepthMeasuringMachine, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_LearnAboutSeaForBattling, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_SternIsRoleModel, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_MustBePokemonWeDontKnow, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron4::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WantSeaPokemon, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGrunt::
	lock
	faceplayer
	delay 8
	playse SE_PIN
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_1F_Text_RememberMeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_THIEF
	goto_if_eq VAR_RESULT, 0, SlateportCity_OceanicMuseum_1F_EventScript_NoRoomForThief
	setflag FLAG_RECEIVED_TM_THIEF
	msgbox SlateportCity_OceanicMuseum_1F_Text_HopeINeverSeeYouAgain, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_NORTH, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitNorth
	goto_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitSouth
	goto_if_eq VAR_FACING, DIR_WEST, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast
	goto_if_eq VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitNorth::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitNorth
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExitNorth
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitSouth::
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitWestEast
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited::
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_FAMILIAR_AQUA_GRUNT
	playse SE_EXIT
	removeobject LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT
	release
	end

SlateportCity_OceanicMuseum_1F_EventScript_NoRoomForThief::
	msgbox SlateportCity_OceanicMuseum_1F_Text_YouHaveToTakeThis, MSGBOX_DEFAULT
	release
	end

SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitNorth:
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitWestEast:
	delay_16
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit:
	face_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	delay_8
	step_end

SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExitNorth:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	delay_8
	step_end

SlateportCity_OceanicMuseum_1F_Text_WouldYouLikeToEnter:
	.string "Te damos la bienvenida al MUSEO\n"
	.string "OCEÁNICO.\p"
	.string "La entrada cuesta 50 ¥.\n"
	.string "¿Quieres entrar?$"

SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself:
	.string "Disfruta de la visita.$"

SlateportCity_OceanicMuseum_1F_Text_NotEnoughMoney:
	.string "¿Oh? Lo siento, pero parece que no\n"
	.string "tienes bastante dinero.$"

SlateportCity_OceanicMuseum_1F_Text_CatchUpWithYourGroup:
	.string "¿Oh? ¿Vienes con el grupo que\n"
	.string "ha entrado antes?\p"
	.string "Solo faltabas tú.\n"
	.string "¡Date prisa y alcánzalos!$"

SlateportCity_OceanicMuseum_1F_Text_AquaExistForGoodOfAll:
	.string "¡Nosotros, el EQUIPO AQUA, existimos\n"
	.string "por el bien de todos!$"

SlateportCity_OceanicMuseum_1F_Text_OurBossIsntHere:
	.string "Nos dijeron que nos reuniéramos aquí,\n"
	.string "y aquí estamos, pero…\p"
	.string "¡Nuestro JEFE, el que lo organiza\n"
	.string "todo, no está!$"

SlateportCity_OceanicMuseum_1F_Text_WouldStuffHereMakeMeRich:
	.string "Si me llevo las cosas de aquí,\n"
	.string "¿me haré rico?$"

SlateportCity_OceanicMuseum_1F_Text_CanLearnForNefariousDeeds:
	.string "Lo que aprenda aquí lo usaré para\n"
	.string "hacer maldades…$"

SlateportCity_OceanicMuseum_1F_Text_RustboroBungled:
	.string "Si los nuestros no la hubieran\n"
	.string "fastidiado en FÉRRICA, ¡no estaríamos\l"
	.string "aquí!$"

SlateportCity_OceanicMuseum_1F_Text_DidntHaveMoney:
	.string "No tenía 50 ¥, así que me costó\n"
	.string "mucho pasar por la recepción.$"

SlateportCity_OceanicMuseum_1F_Text_LearnAboutSeaForBattling:
	.string "Quiero aprender sobre el mar y\n"
	.string "usarlo en mis combates.$"

SlateportCity_OceanicMuseum_1F_Text_SternIsRoleModel:
	.string "¡Me pongo como un flan cuando\n"
	.string "veo el mar!\p"
	.string "¡Para mí, el CAPITÁN BABOR es el\n"
	.string "mejor ejemplo a seguir!$"

SlateportCity_OceanicMuseum_1F_Text_MustBePokemonWeDontKnow:
	.string "El mar es inmenso y de una\n"
	.string "profundidad infinita…\p"
	.string "Seguro que hay muchos POKéMON\n"
	.string "que aún no conocemos.$"

SlateportCity_OceanicMuseum_1F_Text_WantSeaPokemon:
	.string "Quiero un POKéMON del mar.\p"
	.string "Seguro que es fresquito y da\n"
	.string "gusto abrazarlo.$"

SlateportCity_OceanicMuseum_1F_Text_RememberMeTakeThis:
	.string "¡Aaaah!\n"
	.string "¿Qué haces tú aquí?\p"
	.string "¿Yo? ¡Soy el del EQUIPO AQUA al que\n"
	.string "derrotaste! ¿No te acuerdas?\l"
	.string "¿En el TÚNEL FERVERGAL?\p"
	.string "¡Toma, quédate esto!\n"
	.string "¡Tienes que perdonarme!$"

SlateportCity_OceanicMuseum_1F_Text_HopeINeverSeeYouAgain:
	.string "Esa MT te pega más a ti que a mí.\p"
	.string "¡Espero no volver a verte!\n"
	.string "¡Juajuajua!$"

SlateportCity_OceanicMuseum_1F_Text_YouHaveToTakeThis:
	.string "¡Venga, va!\n"
	.string "¡Acepta esto y déjame en paz!$"

SlateportCity_OceanicMuseum_1F_Text_WhirlpoolExperiment:
	.string "Un líquido azul da vueltas dentro\n"
	.string "de un recipiente de cristal.\p"
	.string "“Experimento para crear un\n"
	.string "TORBELLINO artificial con viento”.$"

SlateportCity_OceanicMuseum_1F_Text_WaterfallExperiment:
	.string "Una bola roja sube y baja dentro\n"
	.string "de un recipiente de cristal.\p"
	.string "“Experimento que simula una CASCADA\n"
	.string "gracias a la flotabilidad de la bola”.$"

SlateportCity_OceanicMuseum_1F_Text_OceanSoilDisplay:
	.string "Es una muestra de tierra del fondo\n"
	.string "del océano.\p"
	.string "“Con los años, los restos de los seres\n"
	.string "vivos se depositan en el fondo del\l"
	.string "mar y forman capas de sedimentos.\p"
	.string "”Al analizar estas capas, se descubre\n"
	.string "el pasado más remoto”.$"

SlateportCity_OceanicMuseum_1F_Text_BeachSandDisplay:
	.string "Es una muestra de arena de playa.\p"
	.string "“Los ríos arrastran las piedras de\n"
	.string "las montañas, que se van rompiendo\l"
	.string "y desgastando.\p"
	.string "”Se reducen a granos y acaban\n"
	.string "siendo arena en las playas”.$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact1:
	.string "“DATO OCEÁNICO 1\n"
	.string "¿Por qué el agua del mar es azul?\p"
	.string "”La luz está formada por muchos\n"
	.string "colores.\p"
	.string "”Cuando la luz atraviesa el agua,\n"
	.string "casi todos los colores se pierden.\p"
	.string "”Pero la luz azul conserva su color,\n"
	.string "y por eso el mar se ve azul”.$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact2:
	.string "“DATO OCEÁNICO 2\n"
	.string "¿Por qué el mar es salado?\p"
	.string "”El agua del mar tiene sal disuelta\n"
	.string "en forma de iones de sodio y cloro.\p"
	.string "”Estos iones salen de las rocas\n"
	.string "y la lluvia los arrastra al mar.\p"
	.string "”La cantidad de sal disuelta hace\n"
	.string "que el mar sea salado”.$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact3:
	.string "“DATO OCEÁNICO 3\n"
	.string "¿Qué es mayor, el mar o la tierra?\p"
	.string "”El mar cubre cerca del 70% del\n"
	.string "planeta, y el resto es tierra.\p"
	.string "”Por tanto, el mar es más del doble\n"
	.string "de grande que la tierra”.$"

SlateportCity_OceanicMuseum_1F_Text_FossilDisplay:
	.string "Es un fósil con surcos ondulados.\p"
	.string "“La marea va erosionando la tierra\n"
	.string "del fondo del océano.\p"
	.string "”El agua al moverse deja en la tierra\n"
	.string "pequeñas crestas y surcos.\p"
	.string "”Si esta tierra se fosiliza, se llama\n"
	.string "marca de oleaje”.$"

SlateportCity_OceanicMuseum_1F_Text_DepthMeasuringMachine:
	.string "Una máquina extraña gira bajo una\n"
	.string "cúpula de cristal.\p"
	.string "Quizá sirva para medir la\n"
	.string "profundidad de algo…$"

