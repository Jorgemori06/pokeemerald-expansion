DesiertoProfundo_MapScripts::
	.byte 0

@ Dualocke: el DESIERTO PROFUNDO, al este del desierto de la RUTA 111 (tools/dualocke/crear_desierto_profundo.py)
DesiertoProfundo_EventScript_Soledad::
	trainerbattle_single TRAINER_SOLEDAD, DesiertoProfundo_Text_SoledadIntro, DesiertoProfundo_Text_SoledadDefeat
	msgbox DesiertoProfundo_Text_SoledadPostBattle, MSGBOX_AUTOCLOSE
	end

DesiertoProfundo_Text_SoledadIntro:
	.string "Aquí la arena no para nunca.\n"
	.string "¿Aguantarás la tormenta?$"

DesiertoProfundo_Text_SoledadDefeat:
	.string "Has aguantado mejor que yo.$"

DesiertoProfundo_Text_SoledadPostBattle:
	.string "Las ruinas del norte están detrás\n"
	.string "de las peñas. Andando no se llega.\p"
	.string "Dicen que la arena movediza se traga\n"
	.string "a quien la pisa, y que de una de ellas\l"
	.string "se sale cerca de las ruinas.$"

@ Dualocke: arenas movedizas (crear_desierto_profundo.py; Miguel, 21/11/2026)
DesiertoProfundo_EventScript_Arena0::
	lockall
	playse SE_M_SAND_ATTACK
	msgbox DesiertoProfundo_Text_Arena, MSGBOX_DEFAULT
	closemessage
	playse SE_FALL
	warp MAP_DESIERTO_PROFUNDO_CUEVA, 33, 10
	waitstate
	releaseall
	end

DesiertoProfundo_EventScript_Arena1::
	lockall
	playse SE_M_SAND_ATTACK
	msgbox DesiertoProfundo_Text_Arena, MSGBOX_DEFAULT
	closemessage
	playse SE_FALL
	warp MAP_DESIERTO_PROFUNDO_CUEVA, 5, 10
	waitstate
	releaseall
	end

DesiertoProfundo_EventScript_Arena2::
	lockall
	playse SE_M_SAND_ATTACK
	msgbox DesiertoProfundo_Text_Arena, MSGBOX_DEFAULT
	closemessage
	playse SE_FALL
	warp MAP_DESIERTO_PROFUNDO_CUEVA, 17, 10
	waitstate
	releaseall
	end

DesiertoProfundo_EventScript_Arena3::
	lockall
	playse SE_M_SAND_ATTACK
	msgbox DesiertoProfundo_Text_Arena, MSGBOX_DEFAULT
	closemessage
	playse SE_FALL
	warp MAP_DESIERTO_PROFUNDO_CUEVA, 8, 12
	waitstate
	releaseall
	end

DesiertoProfundo_Text_Arena:
	.string "¡La arena se hunde!\n"
	.string "¡Es arena movediza!$"
