BirthIsland_Exterior_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BirthIsland_Exterior_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, BirthIsland_Exterior_OnResume
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, BirthIsland_Exterior_OnReturnToField
	.byte 0

BirthIsland_Exterior_OnReturnToField:
	special SetDeoxysRockPalette
	end

BirthIsland_Exterior_OnTransition:
	setflag FLAG_MAP_SCRIPT_CHECKED_DEOXYS
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL
	setvar VAR_DEOXYS_ROCK_STEP_COUNT, 0
	setvar VAR_DEOXYS_ROCK_LEVEL, 0
	@ Dualocke: sin Deoxys ni el puzle del triángulo
	call BirthIsland_Exterior_EventScript_HideDeoxysAndPuzzle
	@ Dualocke: el Pokémon fuerte de la isla, con el sprite de la especie que sale con la semilla
	setvar VAR_0x8004, SPECIES_METAGROSS
	special Dualocke_GraficoPokemonIsla
	copyvar VAR_OBJ_GFX_ID_1, VAR_RESULT
	end

BirthIsland_Exterior_EventScript_HideDeoxysAndPuzzle::
	setflag FLAG_HIDE_DEOXYS
	setflag FLAG_HIDE_BIRTH_ISLAND_DEOXYS_TRIANGLE
	return

BirthIsland_Exterior_EventScript_TryShowDeoxysPuzzle::
	goto_if_set FLAG_DEFEATED_DEOXYS, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_BIRTH_ISLAND_DEOXYS_TRIANGLE
	clearflag FLAG_DEOXYS_ROCK_COMPLETE
	return

BirthIsland_Exterior_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, BirthIsland_Exterior_EventScript_TryRemoveDeoxys
	end

BirthIsland_Exterior_EventScript_TryRemoveDeoxys::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject LOCALID_BIRTH_ISLAND_DEOXYS
	return

BirthIsland_Exterior_EventScript_Triangle::
	lock
	faceplayer
	special DoDeoxysRockInteraction
	switch VAR_RESULT
	case DEOXYS_ROCK_FAILED,     BirthIsland_Exterior_EventScript_Failed
	case DEOXYS_ROCK_PROGRESSED, BirthIsland_Exterior_EventScript_Progressed
	case DEOXYS_ROCK_SOLVED,     BirthIsland_Exterior_EventScript_Deoxys
	case DEOXYS_ROCK_COMPLETE,   BirthIsland_Exterior_EventScript_Complete
	end

@ The actual rock triangle movement is handled by DoDeoxysRockInteraction.
@ Unless the player has solved the puzzle and needs to encounter Deoxys,
@ there's nothing else the script needs to do.
BirthIsland_Exterior_EventScript_Failed::
	release
	end

BirthIsland_Exterior_EventScript_Progressed::
	release
	end

BirthIsland_Exterior_EventScript_Complete::
	release
	end

BirthIsland_Exterior_EventScript_Deoxys::
	waitse
	setfieldeffectargument 0, LOCALID_BIRTH_ISLAND_EXTERIOR_ROCK
	setfieldeffectargument 1, MAP_NUM(MAP_BIRTH_ISLAND_EXTERIOR)
	setfieldeffectargument 2, MAP_GROUP(MAP_BIRTH_ISLAND_EXTERIOR)
	dofieldeffect FLDEFF_DESTROY_DEOXYS_ROCK
	playbgm MUS_RG_ENCOUNTER_DEOXYS, FALSE
	waitfieldeffect FLDEFF_DESTROY_DEOXYS_ROCK
	addobject LOCALID_BIRTH_ISLAND_DEOXYS
	applymovement LOCALID_BIRTH_ISLAND_DEOXYS, BirthIsland_Exterior_Movement_DeoxysApproach
	waitmovement 0
	waitse
	playmoncry SPECIES_DEOXYS_NORMAL, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_BIRTH_ISLAND_DEOXYS
	seteventmon SPECIES_DEOXYS_NORMAL, 30
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, BirthIsland_Exterior_EventScript_DefeatedDeoxys
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BirthIsland_Exterior_EventScript_RanFromDeoxys
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BirthIsland_Exterior_EventScript_RanFromDeoxys
	setflag FLAG_BATTLED_DEOXYS
	release
	end

BirthIsland_Exterior_EventScript_DefeatedDeoxys::
	setflag FLAG_DEFEATED_DEOXYS
	setvar VAR_0x8004, SPECIES_DEOXYS_NORMAL
	goto Common_EventScript_LegendaryFlewAway
	end

BirthIsland_Exterior_EventScript_RanFromDeoxys::
	setvar VAR_0x8004, SPECIES_DEOXYS_NORMAL
	goto Common_EventScript_LegendaryFlewAway
	end

BirthIsland_Exterior_Movement_DeoxysApproach:
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	step_end

@ Dualocke: el Pokémon fuerte de la isla (data/scripts/dualocke_islas.inc)
BirthIsland_Exterior_EventScript_Pokemon::
	lock
	setvar VAR_TEMP_8, SPECIES_METAGROSS
	setvar VAR_TEMP_9, ITEM_ABILITY_PATCH
	call Dualocke_EventScript_AvisoIsla
	setwildbattle SPECIES_METAGROSS, 97
	dowildbattle
	call Dualocke_EventScript_ResultadoIsla
	goto_if_eq VAR_RESULT, FALSE, BirthIsland_Exterior_EventScript_PokemonSigue
	setflag FLAG_DUALOCKE_ISLA_ORIGEN
	call Dualocke_EventScript_PremioIsla
	release
	end

BirthIsland_Exterior_EventScript_PokemonSigue::
	release
	end

BirthIsland_Exterior_EventScript_GinaMia::
	trainerbattle_double TRAINER_GINA_AND_MIA_2, BirthIsland_Exterior_Text_GinaMiaIntro, BirthIsland_Exterior_Text_GinaMiaDefeat, BirthIsland_Exterior_Text_GinaMiaNotEnoughMons
	msgbox BirthIsland_Exterior_Text_GinaMiaPostBattle, MSGBOX_AUTOCLOSE
	end

BirthIsland_Exterior_Text_GinaMiaIntro:
	.string "¡Esta isla tiene forma de\n"
	.string "triángulo! ¡Y nosotras, de pareja!$"

BirthIsland_Exterior_Text_GinaMiaDefeat:
	.string "¡No nos ha salido la figura!$"

BirthIsland_Exterior_Text_GinaMiaNotEnoughMons:
	.string "¡Hacen falta dos POKéMON para\n"
	.string "jugar con nosotras!$"

BirthIsland_Exterior_Text_GinaMiaPostBattle:
	.string "Dicen que aquí cayó algo del cielo\n"
	.string "hace mucho tiempo.$"
