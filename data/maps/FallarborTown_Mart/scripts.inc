FallarborTown_Mart_MapScripts::
	.byte 0

FallarborTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FallarborTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FallarborTown_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_RARE_CANDY
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_MOON_STONE
	.2byte ITEM_DUSK_STONE
	pokemartlistend

FallarborTown_Mart_EventScript_Woman::
	msgbox FallarborTown_Mart_Text_DecidingSkittyEvolve, MSGBOX_NPC
	end

FallarborTown_Mart_EventScript_PokefanM::
	msgbox FallarborTown_Mart_Text_SellNuggetIFound, MSGBOX_NPC
	end

FallarborTown_Mart_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox FallarborTown_Mart_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_Mart_Text_DecidingSkittyEvolve:
	.string "No sé si hacer evolucionar a mi\n"
	.string "SKITTY o no.\p"
	.string "Solo tengo que usar esta PIEDRA\n"
	.string "LUNAR, pero me cuesta decidirme…\p"
	.string "Si evoluciona, será mucho más\n"
	.string "fuerte.\p"
	.string "Pero también cambiará mucho.$"

FallarborTown_Mart_Text_Skitty:
	.string "SKITTY: ¿Miau?$"

FallarborTown_Mart_Text_SellNuggetIFound:
	.string "Esta PEPITA que he encontrado…\n"
	.string "Supongo que tendré que venderla,\l"
	.string "porque no sirve para nada más.$"

