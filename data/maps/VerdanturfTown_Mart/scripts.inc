VerdanturfTown_Mart_MapScripts::
	.byte 0

VerdanturfTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart VerdanturfTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
VerdanturfTown_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_RARE_CANDY
	.2byte ITEM_NEST_BALL
	.2byte ITEM_LEAF_STONE
	.2byte ITEM_SACHET
	.2byte ITEM_WHIPPED_DREAM
	pokemartlistend

VerdanturfTown_Mart_EventScript_Boy::
	msgbox VerdanturfTown_Mart_Text_XSpecialIsCrucial, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_ExpertF::
	msgbox VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_Lass::
	msgbox VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon, MSGBOX_NPC
	end

VerdanturfTown_Mart_Text_XSpecialIsCrucial:
	.string "En cualquier combate POKéMON, el\n"
	.string "AT. ESPECIAL X es fundamental.\p"
	.string "Sube la potencia de algunos\n"
	.string "movimientos, aunque solo dure\l"
	.string "un combate.$"

VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent:
	.string "No parece que vendan guías para\n"
	.string "ganar en la CARPA DE COMBATE…\p"
	.string "Al final, toca fiarse de la propia\n"
	.string "cabeza…$"

VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon:
	.string "La NIDO BALL funciona mejor con\n"
	.string "POKéMON debilitados.\p"
	.string "Solo se puede comprar en VERDEGAL.$"

