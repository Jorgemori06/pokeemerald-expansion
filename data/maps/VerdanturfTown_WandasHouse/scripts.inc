VerdanturfTown_WandasHouse_MapScripts::
	.byte 0

VerdanturfTown_WandasHouse_EventScript_Wally::
	lock
	faceplayer
	goto_if_set FLAG_WALLY_SPEECH, VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeech, MSGBOX_DEFAULT
	setflag FLAG_WALLY_SPEECH
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech::
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeechShort, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff
	msgbox VerdanturfTown_WandasHouse_Text_WallysNextDoor, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff::
	msgbox VerdanturfTown_WandasHouse_Text_WallySlippedOff, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyGoneThatFar, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandasBoyfriend::
	msgbox VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay, MSGBOX_NPC
	end

VerdanturfTown_WandasHouse_EventScript_Wanda::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WandaDontWorry
	goto_if_set FLAG_DEFEATED_WALLY_MAUVILLE, VerdanturfTown_WandasHouse_EventScript_MeetWanda
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_MeetWanda::
	msgbox VerdanturfTown_WandasHouse_Text_MeetWanda, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandaDontWorry::
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAunt::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen::
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened::
	msgbox VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_Text_StrongerSpeech:
	.string "BLASCO: He perdido contra ti,\n"
	.string "{PLAYER}, pero ya no estoy triste.\p"
	.string "Porque tengo un nuevo objetivo.\n"
	.string "Con mi RALTS, voy a desafiar a los\l"
	.string "GIMNASIOS POKéMON y ser un gran\l"
	.string "ENTRENADOR.\p"
	.string "Obsérvame, {PLAYER}.\n"
	.string "Voy a ser más fuerte que tú.\p"
	.string "Y cuando lo sea, te desafiaré\n"
	.string "a otro combate.$"

VerdanturfTown_WandasHouse_Text_StrongerSpeechShort:
	.string "BLASCO: Obsérvame, {PLAYER}.\n"
	.string "Voy a ser más fuerte que tú.\p"
	.string "Y cuando lo sea, te desafiaré\n"
	.string "a otro combate.$"

VerdanturfTown_WandasHouse_Text_WallysNextDoor:
	.string "TÍO: ¡Oh! ¡{PLAYER}{KUN}!\n"
	.string "BLASCO está en la habitación de al lado.\p"
	.string "Pero tengo que contarte una cosa.\p"
	.string "Este entorno natural le está\n"
	.string "sentando de maravilla a BLASCO.\p"
	.string "Aunque quizá no sea solo eso.\n"
	.string "Puede que sean los POKéMON los que\l"
	.string "le dan esperanza al chico.$"

VerdanturfTown_WandasHouse_Text_WallySlippedOff:
	.string "WALLY's gone away…\n"
	.string "He slipped off on his own…$"

VerdanturfTown_WandasHouse_Text_WallyGoneThatFar:
	.string "UNCLE: Is that right?\n"
	.string "WALLY's gone away that far all by\l"
	.string "himself…\p"
	.string "Well, I have to give him credit--he is\n"
	.string "my little brother's son.$"

VerdanturfTown_WandasHouse_Text_MeetWanda:
	.string "WANDA: ¿Quién eres?\n"
	.string "¡Ah, claro, ya caigo!\p"
	.string "Eres {PLAYER}, de quien me ha\n"
	.string "hablado BLASCO.\p"
	.string "Soy la prima de BLASCO.\n"
	.string "¡Encantada!\p"
	.string "Creo que BLASCO está mucho más vivo\n"
	.string "y sano desde que vino aquí.$"

VerdanturfTown_WandasHouse_Text_DontWorryAboutWally:
	.string "WANDA: No te preocupes por BLASCO.\n"
	.string "Estará bien.\p"
	.string "Conozco a mi primo, y además\n"
	.string "lleva POKéMON con él.$"

VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay:
	.string "Gracias a ti, puedo ver a mi novia\n"
	.string "todos los días.\l"
	.string "¿Que si estoy feliz? ¡Ya te digo!$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven:
	.string "El novio de mi hija es muy decidido\n"
	.string "y apasionado.\p"
	.string "Ha estado cavando un túnel sin parar\n"
	.string "solo para poder ver a mi hija.\p"
	.string "Mi hija está un poco preocupada, así\n"
	.string "que va mucho al túnel.$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging:
	.string "Es increíble. ¡El novio de mi hija\n"
	.string "estaba cavando el túnel a mano!\p"
	.string "¡Qué barbaridad!$"

VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally:
	.string "If anything were to happen to WALLY,\n"
	.string "I would never be able to look his\l"
	.string "parents in PETALBURG in the eye…$"

VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande:
	.string "WALLY was in EVER GRANDE?\p"
	.string "His parents in PETALBURG would be\n"
	.string "astonished to hear that!$"

