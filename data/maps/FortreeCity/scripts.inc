FortreeCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, FortreeCity_OnResume
	.byte 0

FortreeCity_OnTransition:
	setflag FLAG_VISITED_FORTREE_CITY
	end

FortreeCity_OnResume:
	setstepcallback STEP_CB_FORTREE_BRIDGE
	end

FortreeCity_EventScript_Man::
	msgbox FortreeCity_Text_SawGiganticPokemonInSky, MSGBOX_NPC
	end

FortreeCity_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_KECLEON_FLED_FORTREE, FortreeCity_EventScript_WomanGymAccessible
	msgbox FortreeCity_Text_SomethingBlockingGym, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_WomanGymAccessible::
	msgbox FortreeCity_Text_ThisTimeIllBeatWinona, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_Girl::
	msgbox FortreeCity_Text_TreesGrowByDrinkingRainwater, MSGBOX_NPC
	end

FortreeCity_EventScript_OldMan::
	msgbox FortreeCity_Text_EveryoneHealthyAndLively, MSGBOX_NPC
	end

FortreeCity_EventScript_Boy::
	msgbox FortreeCity_Text_BugPokemonComeThroughWindow, MSGBOX_NPC
	end

FortreeCity_EventScript_GameboyKid::
	msgbox FortreeCity_Text_PokemonThatEvolveWhenTraded, MSGBOX_NPC
	end

FortreeCity_EventScript_CitySign::
	msgbox FortreeCity_Text_CitySign, MSGBOX_SIGN
	end

FortreeCity_EventScript_GymSign::
	msgbox FortreeCity_Text_GymSign, MSGBOX_SIGN
	end

FortreeCity_EventScript_Kecleon::
	lock
	faceplayer
	checkitem ITEM_DEVON_SCOPE
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_EventScript_AskUseDevonScope
	msgbox FortreeCity_Text_SomethingUnseeable, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_AskUseDevonScope::
	msgbox FortreeCity_Text_UnseeableUseDevonScope, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FortreeCity_EventScript_UseDevonScope
	release
	end

FortreeCity_EventScript_UseDevonScope::
	msgbox FortreeCity_Text_UsedDevonScopePokemonFled, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Movement_KecleonAppears
	waitmovement 0
	waitse
	playmoncry SPECIES_KECLEON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	applymovement VAR_LAST_TALKED, FortreeCity_Movement_KecleonFlee
	waitmovement 0
	removeobject VAR_LAST_TALKED
	setflag FLAG_KECLEON_FLED_FORTREE
	release
	end

FortreeCity_Movement_KecleonFlee:
	walk_right
	step_end

FortreeCity_Text_SawGiganticPokemonInSky:
	.string "Nadie me cree, pero he visto un\n"
	.string "POKéMON gigantesco en el cielo.\p"
	.string "Parecía retorcerse mientras volaba\n"
	.string "hacia la RUTA 131.\p"
	.string "Por cierto… Snif…\n"
	.string "Esto… Tú, eh… hueles a chamusquina.\p"
	.string "¿Has estado en un volcán o algo así?$"

FortreeCity_Text_SomethingBlockingGym:
	.string "Quiero ir al GIMNASIO POKéMON, pero\n"
	.string "hay algo que corta el paso.\p"
	.string "Con lo que me ha costado entrenar\n"
	.string "en la RUTA 120…$"

FortreeCity_Text_ThisTimeIllBeatWinona:
	.string "Llevo a mi POKéMON favorito.\n"
	.string "Esta vez le ganaré a ALANA.$"

FortreeCity_Text_TreesGrowByDrinkingRainwater:
	.string "La tierra absorbe la lluvia, y los\n"
	.string "árboles crecen bebiendo esa agua…\p"
	.string "Nuestra CIUDAD ARBORADA existe porque\n"
	.string "hay agua y tierra.$"

FortreeCity_Text_EveryoneHealthyAndLively:
	.string "La CIUDAD está hecha de casas\n"
	.string "construidas en los árboles.\p"
	.string "Quizá por eso aquí todo el mundo\n"
	.string "está sano y lleno de vida.\p"
	.string "Hasta yo me siento como si tuviera\n"
	.string "treinta años menos.$"

FortreeCity_Text_BugPokemonComeThroughWindow:
	.string "Vivir en lo alto de los árboles\n"
	.string "está bien.\p"
	.string "Pero a veces entran POKéMON BICHO\n"
	.string "por las ventanas.\l"
	.string "¡Te pegan cada susto!$"

FortreeCity_Text_PokemonThatEvolveWhenTraded:
	.string "¡Hay POKéMON que evolucionan cuando\n"
	.string "los intercambias! Eso he oído.$"

FortreeCity_Text_SomethingUnseeable:
	.string "Hay algo invisible que corta el paso.$"

FortreeCity_Text_UnseeableUseDevonScope:
	.string "Hay algo invisible que corta el paso.\p"
	.string "¿Quieres usar el DETECTOR DEVON?$"

FortreeCity_Text_UsedDevonScopePokemonFled:
	.string "{PLAYER} ha usado el DETECTOR DEVON.\p"
	.string "¡Un POKéMON invisible se ha vuelto\n"
	.string "totalmente visible!\p"
	.string "¡El POKéMON se ha asustado y ha huido!$"

FortreeCity_Text_CitySign:
	.string "CIUDAD ARBORADA\n"
	.string "“La ciudad en las copas de los árboles\l"
	.string "que juega con la naturaleza”.$"

FortreeCity_Text_GymSign:
	.string "GIMNASIO POKéMON DE ARBORADA\n"
	.string "LÍDER: ALANA\p"
	.string "“La experta en aves que alza el vuelo\n"
	.string "hacia el mundo”.$"

