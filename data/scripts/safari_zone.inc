SafariZone_EventScript_OutOfBallsMidBattle::
#if IS_FRLG
	setvar VAR_MAP_SCENE_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 3
#else
	setvar VAR_SAFARI_ZONE_STATE, 1
#endif
	special ExitSafariMode
#if IS_FRLG
	setwarp MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 4, 1
#else
	setwarp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
#endif
	end

SafariZone_EventScript_Exit::
#if IS_FRLG
	setvar VAR_MAP_SCENE_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 1
#else
	setvar VAR_SAFARI_ZONE_STATE, 1
#endif
	special ExitSafariMode
#if IS_FRLG
	warp MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 4, 1
#else
	warp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
#endif
	waitstate
	end

SafariZone_EventScript_RetirePrompt::
	lockall
	msgbox SafariZone_Text_WouldYouLikeToExit, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_Retire
	releaseall
	end

SafariZone_EventScript_Retire::
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_TimesUp::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_TimesUp
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_OutOfBalls::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_OutOfBalls
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

EventScript_PokeBlockFeeder::
	lockall
	special GetPokeblockFeederInFront
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPresent
	msgbox SafariZone_Text_PlacePokeblockOnFeeder, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_ChoosePokeblock
	releaseall
	end

SafariZone_EventScript_ChoosePokeblock::
	fadescreen FADE_TO_BLACK
	special OpenPokeblockCaseOnFeeder
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPlaced
#ifdef BUGFIX
	releaseall  @ Only gets called from EventScript_PokeBlockFeeder which uses lockall.
#endif
	end

SafariZone_EventScript_PokeblockPlaced::
	message SafariZone_Text_PokeblockWasPlaced
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_EventScript_PokeblockPresent::
	message SafariZone_Text_PokeblockStillHere
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_Text_WouldYouLikeToExit:
	.string "¿Quieres salir de la ZONA SAFARI\n"
	.string "ahora mismo?$"

SafariZone_Text_TimesUp:
	.string "¡Din-don! ¡Se acabó el tiempo!\n"
	.string "Tu juego del SAFARI ha terminado.$"

SafariZone_Text_OutOfBalls:
	.string "Te has quedado sin SAFARI BALLS.\n"
	.string "Tu juego del SAFARI ha terminado.$"

SafariZone_Text_PlacePokeblockOnFeeder:
	.string "¿Quieres poner un {POKEBLOCK}\n"
	.string "en el COMEDERO?$"

SafariZone_Text_PokeblockStillHere:
	.string "El {STR_VAR_1} que dejaste\n"
	.string "antes sigue aquí.$"

SafariZone_Text_PokeblockWasPlaced:
	.string "Has puesto el {STR_VAR_1}\n"
	.string "en el COMEDERO de {POKEBLOCK}S.$"

Route121_SafariZoneEntrance_Text_WelcomeToSafariZone:
	.string "¡Te damos la bienvenida a la ZONA\n"
	.string "SAFARI!\p"
	.string "Aquí podrás ver muchos tipos de\n"
	.string "POKéMON que casi no se ven en HOENN.\p"
	.string "Y los verás en estado salvaje, en\n"
	.string "su hábitat natural.\p"
	.string "Además, ¡hemos abierto las puertas\n"
	.string "a los ENTRENADORES POKéMON!\p"
	.string "¡Puedes atrapar POKéMON y quedártelos!\p"
	.string "¡Entra y disfruta de la ZONA SAFARI!$"

Route121_SafariZoneEntrance_Text_WelcomeFirstTime:
	.string "¡Te damos la bienvenida a la ZONA\n"
	.string "SAFARI! ¿Es tu primera vez?$"

Route121_SafariZoneEntrance_Text_ComeInAndEnjoy:
	.string "¡Entra y disfruta de la ZONA SAFARI!$"

Route121_SafariZoneEntrance_Text_FirstTimeInfo:
	.string "Al entrar en la ZONA SAFARI, empiezas\n"
	.string "con 30 SAFARI BALLS para atrapar\l"
	.string "POKéMON.\p"
	.string "El juego del SAFARI se acaba cuando\n"
	.string "te quedas sin SAFARI BALLS o cuando\l"
	.string "has dado 500 pasos.\p"
	.string "¡Entra y disfruta de la ZONA SAFARI!$"

Route121_SafariZoneEntrance_Text_WouldYouLikeToPlay:
	.string "¡Te damos la bienvenida a la ZONA\n"
	.string "SAFARI!\p"
	.string "¡Atrapa todo lo que puedas por 500 ¥!\n"
	.string "¿Quieres jugar al SAFARI?$"

Route121_SafariZoneEntrance_Text_PlayAnotherTime:
	.string "Vale.\n"
	.string "¡Vuelve a jugar otro día!$"

Route121_SafariZoneEntrance_Text_NotEnoughMoney:
	.string "No tienes bastante dinero.\n"
	.string "Lo siento.$"

Route121_SafariZoneEntrance_Text_ThatWillBe500Please:
	.string "Son 500 ¥, por favor.$"

Route121_SafariZoneEntrance_Text_HereAreYourSafariBalls:
	.string "Aquí tienes tus SAFARI BALLS.$"

Route121_SafariZoneEntrance_Text_Received30SafariBalls:
	.string "{PLAYER} ha recibido 30 SAFARI BALLS.$"

Route121_SafariZoneEntrance_Text_PleaseEnjoyYourself:
	.string "Te avisaremos cuando se acabe\n"
	.string "el juego.\p"
	.string "Hasta entonces, ¡disfruta!\n"
	.string "¡A por tu excursión salvaje!$"

Route121_SafariZoneEntrance_Text_PCIsFull:
	.string "¡Perdona!\n"
	.string "La CAJA de tu PC está llena.$"

Route121_SafariZoneEntrance_Text_YouNeedPokeblockCase:
	.string "¡Perdona!\n"
	.string "Parece que no llevas TUBO {POKEBLOCK}.\p"
	.string "El SAFARI te irá mucho mejor si\n"
	.string "usas {POKEBLOCK}S.\p"
	.string "Vuelve con un TUBO {POKEBLOCK}, por favor.\p"
	.string "Te darán un TUBO {POKEBLOCK} en la\n"
	.string "SALA DE CONCURSOS de CALAGUA.$"

SafariZone_South_Text_StillHaveTimeExit:
	.string "Aún te queda tiempo. ¿Quieres salir\n"
	.string "de la ZONA SAFARI ya?$"

SafariZone_South_Text_EnjoyTheRestOfYourAdventure:
	.string "¡Disfruta del resto de tu aventura\n"
	.string "salvaje!$"

SafariZone_South_Text_ExitEarlyThankYouForPlaying:
	.string "Vale.\p"
	.string "Me quedo con las SAFARI BALLS que\n"
	.string "te sobran.\p"
	.string "Gracias por jugar.\n"
	.string "Esperamos volver a verte.$"

SafariZone_South_Text_GoodLuck:
	.string "¡Buena suerte!\p"
	.string "Si necesitas algo, ¡no dudes en\n"
	.string "decírmelo!$"

SafariZone_South_Text_Boy:
	.string "¿Sabías que…?\p"
	.string "Si pones un {POKEBLOCK} en esa caja\n"
	.string "cuadrada, se acercan POKéMON.$"

SafariZone_South_Text_Man:
	.string "Quiero seguir adentrándome, pero me\n"
	.string "he olvidado la BICI.\p"
	.string "Algo me dice que en las zonas de\n"
	.string "las afueras viven POKéMON raros.$"

SafariZone_Southwest_Text_Woman:
	.string "A veces, cuando le lanzo un {POKEBLOCK}\n"
	.string "a un POKéMON, ni lo mira.\p"
	.string "¿Tendrán los POKéMON gustos con\n"
	.string "la comida?$"

SafariZone_Northwest_Text_Man:
	.string "Uf… Uf…\n"
	.string "He… llegado hasta aquí… pero…\p"
	.string "Estoy agotado… No me quedan fuerzas\n"
	.string "para atrapar POKéMON…$"

SafariZone_North_Text_Fisherman:
	.string "Estoy buscando POKéMON de tipo AGUA\n"
	.string "que no se ven en HOENN.\p"
	.string "¿Sabes dónde está el lago?$"

SafariZone_North_Text_Man:
	.string "¡Voy a atrapar un montón de POKéMON\n"
	.string "raros y cambiárselos a mis amigos!$"

SafariZone_South_Text_Youngster:
	.string "Puse un {POKEBLOCK} en el COMEDERO.\n"
	.string "Pero parece que ha desaparecido.\p"
	.string "Supongo que se lo habrán comido los\n"
	.string "POKéMON sin que me diera cuenta.$"

Route121_SafariZoneEntrance_Text_TrainerTip:
	.string "¡CONSEJO DE LA ZONA SAFARI!\p"
	.string "Lánzales {POKEBLOCK}S a los POKéMON\n"
	.string "salvajes para que no huyan tanto.$"

SafariZone_Southwest_Text_RestHouseSign:
	.string "“Descansa los pies”.\n"
	.string "CASA DE DESCANSO$"

SafariZone_RestHouse_Text_Youngster:
	.string "No tengo {POKEBLOCK}S, pero he atrapado\n"
	.string "unos cuantos POKéMON.\p"
	.string "Tendrás más posibilidades si te\n"
	.string "acercas a ellos antes de lanzar\l"
	.string "una SAFARI BALL.$"

SafariZone_RestHouse_Text_PsychicM:
	.string "Si usas {POKEBLOCK}S, los POKéMON\n"
	.string "salvajes no huirán tan rápido.\p"
	.string "No sirve de mucho dárselos a POKéMON\n"
	.string "que no huyen con facilidad.$"

SafariZone_RestHouse_Text_FatMan:
	.string "Si pones un {POKEBLOCK} en el COMEDERO,\n"
	.string "los POKéMON se acercan.\p"
	.string "Creo que los POKéMON de la misma\n"
	.string "naturaleza prefieren cierto {POKEBLOCK}.$"

SafariZone_South_Text_AreaOffLimits1:
	.string "Esta zona aún está en obras.\n"
	.string "¡Lo siento, no se puede pasar!$"

SafariZone_Southeast_Text_ExpansionIsFinished:
	.string "The SAFARI ZONE's expansion project\n"
	.string "is finished now.\p"
	.string "We hope you will enjoy the new area.$"

SafariZone_South_Text_AreaOffLimits2:
	.string "Esta zona aún está en obras.\n"
	.string "¡Lo siento, no se puede pasar!$"

SafariZone_Southeast_Text_LittleGirl:
	.string "Wow! Whee! I haven't seen any of\n"
	.string "these POKéMON before!$"

SafariZone_Southeast_Text_FatMan:
	.string "The POKéMON in this area are all\n"
	.string "new to me.\p"
	.string "And I'm allowed to catch these rare\n"
	.string "POKéMON! Too cool!$"

SafariZone_Southeast_Text_RichBoy:
	.string "The POKéMON around here seem to be\n"
	.string "from somewhere other than HOENN.$"

SafariZone_Northeast_Text_Boy:
	.string "Solo me quedan un par de SAFARI BALLS.\p"
	.string "No sé qué atrapar.$"

SafariZone_Northeast_Text_Woman:
	.string "He oído que aquí se pueden ver\n"
	.string "PIKACHU. ¿Dónde habrá alguno?$"

SafariZone_Northeast_Text_Girl:
	.string "¡Jo!\n"
	.string "¡No consigo atrapar nada!\p"
	.string "¡Si no atrapo algo, habré tirado\n"
	.string "el dinero de la entrada!$"
