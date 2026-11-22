@ Dualocke: regla de la Liga (contada por Jorge; Miguel la mete en el juego, 22/11/2026).
@ - En la tienda de la Liga se venden RESTAURAR TODO sin límite.
@ - En combate contra el Alto Mando y el Campeón, un curativo solo si el rival ya ha usado uno, y como
@   mucho tantos como él (src/dualocke_liga.c).
@ - Al entrar en cada sala se cura el equipo entero: lo llaman PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
@   (las cuatro salas del Alto Mando) y EverGrandeCity_ChampionsRoom_EventScript_EnterRoom.

Dualocke_EventScript_CuraLiga::
	special HealPlayerParty
	playfanfare MUS_HEAL
	waitfanfare
	msgbox Dualocke_Text_CuraLiga, MSGBOX_DEFAULT
	return

Dualocke_Text_CuraLiga:
	.string "Regla de la Liga: ¡tu equipo\n"
	.string "se ha recuperado por completo!$"

@ Lo dice el dependiente de la tienda de la Liga antes de abrirla
Dualocke_Text_TiendaLiga:
	.string "Aquí se venden todos los\n"
	.string "RESTAURAR TODO que quieras.\p"
	.string "Recuerda la regla de la Liga:\n"
	.string "en combate solo puedes curar\l"
	.string "si el rival ya ha curado, y no\l"
	.string "más veces que él.$"
