PetalburgCity_House2_MapScripts::
	.byte 0

PetalburgCity_House2_EventScript_Woman::
	msgbox PetalburgCity_House2_Text_NormanBecameGymLeader, MSGBOX_NPC
	end

PetalburgCity_House2_EventScript_SchoolKid::
	msgbox PetalburgCity_House2_Text_BattledNormanOnce, MSGBOX_NPC
	end

PetalburgCity_House2_Text_NormanBecameGymLeader:
	.string "NORMAN es el nuevo LÍDER del\n"
	.string "GIMNASIO de la ciudad.\p"
	.string "Creo que ha traído a su familia desde\n"
	.string "un sitio muy lejano.$"

PetalburgCity_House2_Text_BattledNormanOnce:
	.string "Una vez luché contra NORMAN, pero, uf,\n"
	.string "era demasiado fuerte.\p"
	.string "¿Cómo lo diría?\p"
	.string "Me dio la impresión de que vive\n"
	.string "para los POKéMON.$"

