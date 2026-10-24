PetalburgCity_WallysHouse_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_WallysHouse_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PetalburgCity_WallysHouse_OnWarp
	.byte 0

PetalburgCity_WallysHouse_OnWarp:
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther
	.2byte 0

PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther::
	turnobject LOCALID_PLAYER, DIR_EAST
	turnobject LOCALID_WALLYS_HOUSE_WALLYS_DAD, DIR_WEST
	end

PetalburgCity_WallysHouse_OnFrame:
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_WallysHouse_EventScript_GiveHMSurf
	.2byte 0

PetalburgCity_WallysHouse_EventScript_GiveHMSurf::
	lockall
	msgbox PetalburgCity_WallysHouse_Text_PleaseExcuseUs, MSGBOX_DEFAULT
	giveitem ITEM_HM_SURF
	setflag FLAG_RECEIVED_HM_SURF
	msgbox PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces, MSGBOX_DEFAULT
	setvar VAR_PETALBURG_CITY_STATE, 5
	releaseall
	end

PetalburgCity_WallysHouse_EventScript_WallysDad::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad
	goto_if_set FLAG_RECEIVED_HM_SURF, PetalburgCity_WallysHouse_EventScript_ReceievedHMSurf
	goto_if_set FLAG_THANKED_FOR_PLAYING_WITH_WALLY, PetalburgCity_WallysHouse_EventScript_PlayedWithWally
	msgbox PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally, MSGBOX_DEFAULT
	setflag FLAG_THANKED_FOR_PLAYING_WITH_WALLY
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceievedHMSurf::
	msgbox PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad::
	msgbox PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_PlayedWithWally::
	msgbox PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_WallysMom::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_SURF, PetalburgCity_WallysHouse_EventScript_ReceivedHMSurf
	msgbox PetalburgCity_WallysHouse_Text_WallyWasReallyHappy, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceivedHMSurf::
	msgbox PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally:
	.string "Tú eres…\n"
	.string "Ah, debes de ser {PLAYER}{KUN}, ¿no?\p"
	.string "Gracias por estar con BLASCO\n"
	.string "hace un rato.\p"
	.string "Ha sido débil y enfermizo desde\n"
	.string "que era un bebé.\p"
	.string "Lo hemos mandado una temporada con\n"
	.string "mis parientes de PUEBLO VERDEGAL.\p"
	.string "Allí el aire es mucho más limpio\n"
	.string "que aquí.\p"
	.string "¿Cómo? ¿Dónde está BLASCO?\n"
	.string "Ya se ha ido.\p"
	.string "¿Por dónde andará ahora?$"

PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing:
	.string "¿Qué tal estará nuestro BLASCO?$"

PetalburgCity_WallysHouse_Text_PleaseExcuseUs:
	.string "¡{PLAYER}{KUN}! Perdona por\n"
	.string "traerte así.\p"
	.string "Pero nuestro BLASCO está mucho mejor\n"
	.string "desde que se fue a PUEBLO VERDEGAL.\p"
	.string "¡Y te lo debemos a ti!\p"
	.string "Cuando BLASCO se fue, le ayudaste\n"
	.string "a atrapar un POKéMON, ¿verdad?\p"
	.string "Creo que eso le hizo muy feliz.\p"
	.string "Y no solo a él.\n"
	.string "A mí, su padre, también.\p"
	.string "Feliz de que tenga un amigo tan\n"
	.string "bueno como tú.\p"
	.string "No es un soborno ni nada, pero\n"
	.string "me gustaría que te quedaras esto.$"

PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces:
	.string "Si tu POKéMON sabe hacer SURF,\n"
	.string "podrás ir a muchísimos sitios.$"

PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon:
	.string "BLASCO vuelve pronto a casa.\n"
	.string "Tengo muchas ganas de verlo.$"

PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity:
	.string "Oh? You met WALLY in\n"
	.string "EVER GRANDE CITY?\p"
	.string "Oh, {PLAYER}{KUN}, don't be silly.\p"
	.string "He may have gotten healthy, but he\n"
	.string "can't go somewhere far away like\l"
	.string "that all by himself.$"

PetalburgCity_WallysHouse_Text_WallyWasReallyHappy:
	.string "BLASCO estaba feliz cuando nos dijo\n"
	.string "que había atrapado un POKéMON.\p"
	.string "Hacía siglos que no lo veía\n"
	.string "sonreír así.$"

PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling:
	.string "Que no se entere mi marido…\p"
	.string "Pero nuestro BLASCO se ha ido de\n"
	.string "PUEBLO VERDEGAL sin decir nada.\p"
	.string "BLASCO es débil, pero tiene una\n"
	.string "fuerza de voluntad increíble.\p"
	.string "¡Seguro que un día vuelve sano\n"
	.string "y salvo!$"

