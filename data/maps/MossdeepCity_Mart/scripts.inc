MossdeepCity_Mart_MapScripts::
	.byte 0

MossdeepCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MossdeepCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MossdeepCity_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_RARE_CANDY
	.2byte ITEM_NET_BALL
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_DAWN_STONE
	.2byte ITEM_SHINY_STONE
	.2byte ITEM_ICE_STONE
	.2byte ITEM_PROTECTOR
	pokemartlistend

MossdeepCity_Mart_EventScript_Woman::
	msgbox MossdeepCity_Mart_Text_ReviveIsFantastic, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Boy::
	msgbox MossdeepCity_Mart_Text_MaxRepelLastsLongest, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Sailor::
	msgbox MossdeepCity_Mart_Text_NetAndDiveBallsRare, MSGBOX_NPC
	end

MossdeepCity_Mart_Text_ReviveIsFantastic:
	.string "¡El REVIVIR es fantástico!\p"
	.string "Dáselo a un POKéMON debilitado y\n"
	.string "se levantará.\p"
	.string "Pero ojo: el REVIVIR no recupera los\n"
	.string "PP gastados de los movimientos.$"

MossdeepCity_Mart_Text_MaxRepelLastsLongest:
	.string "El REPELENTE MÁXIMO aleja a todos los\n"
	.string "POKéMON débiles.\p"
	.string "De todos los REPELENTES, es el que\n"
	.string "más dura.$"

MossdeepCity_Mart_Text_NetAndDiveBallsRare:
	.string "La MALLA BALL y la BUCEO BALL son\n"
	.string "POKé BALLS raras que solo se hacen\l"
	.string "en ALGARIA.\p"
	.string "La MALLA BALL funciona bien con\n"
	.string "POKéMON de tipo BICHO y AGUA.\p"
	.string "La BUCEO BALL va mejor con POKéMON\n"
	.string "del fondo del mar.$"

