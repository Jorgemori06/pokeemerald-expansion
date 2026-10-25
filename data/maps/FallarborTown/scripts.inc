FallarborTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_OnTransition
	.byte 0

FallarborTown_OnTransition:
	setflag FLAG_VISITED_FALLARBOR_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	clearflag FLAG_CONTEST_SKETCH_CREATED
	end

FallarborTown_EventScript_ExpertM::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_EventScript_ExpertMNormal
	msgbox FallarborTown_Text_ShadyCharactersCozmosHome, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_ExpertMNormal::
	msgbox FallarborTown_Text_RegionKnownForMeteors, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_Girl::
	msgbox FallarborTown_Text_MyPreciousAzurill, MSGBOX_NPC
	end

FallarborTown_EventScript_Gentleman::
	msgbox FallarborTown_Text_HaveYouChallengedFlannery, MSGBOX_NPC
	end

FallarborTown_EventScript_Azurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_NORMAL
	msgbox FallarborTown_Text_Azurill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_EventScript_BattleTentSign::
	msgbox FallarborTown_Text_BattleTentSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_TownSign::
	msgbox FallarborTown_Text_TownSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_MoveTutorSign::
	msgbox FallarborTown_Text_MoveTutorSign, MSGBOX_SIGN
	end

FallarborTown_Text_ShadyCharactersCozmosHome:
	.string "¡Aquí pasa algo, y no me gusta\n"
	.string "nada!\p"
	.string "He visto a gente sospechosa entrar y\n"
	.string "salir de la casa del PROF. COSMO…$"

FallarborTown_Text_RegionKnownForMeteors:
	.string "Esta zona es famosa por los\n"
	.string "meteoritos desde tiempos antiguos.\p"
	.string "Dicen que las CATARATAS METEORO las\n"
	.string "excavó un meteorito hace mucho.$"

FallarborTown_Text_MyPreciousAzurill:
	.string "¡Mira! ¡Fíjate!\n"
	.string "¡Es mi querido AZURILL!\p"
	.string "¡Es suavecito, liso y blandito!$"

FallarborTown_Text_Azurill:
	.string "AZURILL: Ruriluuu.$"

FallarborTown_Text_HaveYouChallengedFlannery:
	.string "¿Has desafiado ya a CANDELA, la LÍDER\n"
	.string "del GIMNASIO de LAVACALDA?\p"
	.string "El abuelo de la chica era famoso.\n"
	.string "Fue del ALTO MANDO de la LIGA\l"
	.string "POKéMON durante un tiempo.\p"
	.string "No me extrañaría que CANDELA llegara\n"
	.string "a ser una gran ENTRENADORA.$"

FallarborTown_Text_BattleTentSign:
	.string "CARPA DE COMBATE DE PARDAL\n"
	.string "“¡Que se reúnan los mejores equipos!”$"

FallarborTown_Text_TownSign:
	.string "PUEBLO PARDAL\n"
	.string "“Un pueblo de pequeños huertos”.$"

FallarborTown_Text_MoveTutorSign:
	.string "CASA DEL TUTOR DE MOVIMIENTOS\n"
	.string "“Se enseñan movimientos a POKéMON”.$"

