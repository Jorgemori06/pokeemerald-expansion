VerdanturfTown_BattleTentCorridor_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VerdanturfTown_BattleTentCorridor_OnFrame
	.byte 0

VerdanturfTown_BattleTentCorridor_OnFrame:
	map_script_2 VAR_TEMP_0, 0, VerdanturfTown_BattleTentCorridor_EventScript_EnterCorridor
	.2byte 0

VerdanturfTown_BattleTentCorridor_EventScript_EnterCorridor::
	lockall
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_VERDANTURF_TENT_CORRIDOR_ATTENDANT, VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor
	applymovement LOCALID_PLAYER, VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor
	waitmovement 0
	opendoor 2, 1
	waitdooranim
	applymovement LOCALID_VERDANTURF_TENT_CORRIDOR_ATTENDANT, VerdanturfTown_BattleTentCorridor_Movement_AttendantEnterDoor
	applymovement LOCALID_PLAYER, VerdanturfTown_BattleTentCorridor_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 1
	waitdooranim
	setvar VAR_0x8006, 0
	warp MAP_VERDANTURF_TOWN_BATTLE_TENT_BATTLE_ROOM, 6, 5
	waitstate
	releaseall
	end

VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

VerdanturfTown_BattleTentCorridor_Movement_PlayerEnterDoor:
	walk_up
VerdanturfTown_BattleTentCorridor_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end


@ Leftover text from when this was a Contest Hall in R/S
@ Unused
VerdanturfTown_ContestHall_Text_WhichContestYouEntering:
	.string "¿A qué CONCURSO te vas a presentar?\n"
	.string "¿Quieres un consejo?\p"
	.string "En cualquier CONCURSO, por ejemplo en\n"
	.string "uno de DULZURA, no creo que en la\l"
	.string "primera ronda solo cuente la dulzura.\p"
	.string "Tienes que buscar formas de criar\n"
	.string "mejor a tus POKéMON.$"

@ Unused
VerdanturfTown_ContestHall_Text_RaisedMonToBeCute:
	.string "He criado a mi POKéMON para que\n"
	.string "sea dulce.\p"
	.string "¡Y he descubierto que se puede\n"
	.string "presentar a un CONCURSO de dulzura!\p"
	.string "¡Qué bien que lo criara con tanto\n"
	.string "cariño!$"

@ Unused
VerdanturfTown_ContestHall_Text_MyMonRules:
	.string "¡Mi POKéMON es lo más!\p"
	.string "Es carismático, duro, bello, dulce\n"
	.string "y listo. ¡Lo tiene todo!\p"
	.string "Ya puestos, iré a por la victoria en\n"
	.string "todos los CONCURSOS.$"

@ Unused
VerdanturfTown_ContestHall_Text_NormalRankStage:
	.string "CONCURSOS POKéMON\n"
	.string "¡ESCENARIO DE CATEGORÍA NORMAL!$"

