DewfordTown_House1_MapScripts::
	.byte 0

DewfordTown_House1_EventScript_Man::
	msgbox DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Woman::
	msgbox DewfordTown_House1_Text_LifeGoesSlowlyOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox DewfordTown_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland:
	.string "Vivir en una islita así, en armonía\n"
	.string "con los POKéMON y la familia,\l"
	.string "tiene muchas ventajas.$"

DewfordTown_House1_Text_LifeGoesSlowlyOnIsland:
	.string "Dejé el gran puerto de CIUDAD PORTUAL\n"
	.string "cuando me casé con mi marido.\p"
	.string "En esta islita la vida va despacio.\n"
	.string "Pero estar rodeada de un mar tan\l"
	.string "bonito también es felicidad.$"

DewfordTown_House1_Text_Zigzagoon:
	.string "ZIGZAGOON: ¡Guguuh!$"

