#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"

// Dualocke: la IA de los jefes con estrategia usa de verdad los movimientos de su estilo
// (tools/dualocke/aleatorio/estrategia.py). Los equipos son como los que saca el randomizer.
// - IA_JEFES tiene que ser la misma que "lideres.ia" en tools/dualocke/randomizer_config.json.
// - El jugador lleva Pokémon que aguantan, para que la IA no tenga un KO a mano.
// - La IA no conoce los movimientos del jugador hasta que los ve (no lleva Omniscient).
#define IA_JEFES (AI_FLAG_BASIC_TRAINER | AI_FLAG_SMART_SWITCHING | AI_FLAG_SMART_MON_CHOICES \
                | AI_FLAG_PP_STALL_PREVENTION | AI_FLAG_RANDOMIZE_SWITCHIN | AI_FLAG_KNOW_OPPONENT_PARTY \
                | AI_FLAG_HP_AWARE | AI_FLAG_ACE_POKEMON)

#define EQUIPO_JUGADOR(nivel)                                                                     \
    PLAYER(SPECIES_SWAMPERT) { Level(nivel); Moves(MOVE_MUD_SHOT, MOVE_WATER_GUN, MOVE_PROTECT, MOVE_GROWL); } \
    PLAYER(SPECIES_GARDEVOIR) { Level(nivel); Moves(MOVE_CONFUSION, MOVE_CALM_MIND); }              \
    PLAYER(SPECIES_MANECTRIC) { Level(nivel); Moves(MOVE_SPARK, MOVE_BITE); }

// Solo pone el clima si le sirve al que está en el campo: por eso el primero lleva Meteorobola
AI_SINGLE_BATTLE_TEST("Dualocke IA: clima, el primero pone el clima")
{
    GIVEN {
        AI_FLAGS(IA_JEFES);
        EQUIPO_JUGADOR(43)
        OPPONENT(SPECIES_CYCLIZAR) { Level(43); Moves(MOVE_STOMP, MOVE_SUNNY_DAY, MOVE_WEATHER_BALL, MOVE_OCTOLOCK); }
        OPPONENT(SPECIES_CAMERUPT) { Level(43); Moves(MOVE_HEAD_SMASH, MOVE_WEATHER_BALL, MOVE_SUNNY_DAY, MOVE_CORROSIVE_GAS); }
        OPPONENT(SPECIES_ROSERADE) { Level(43); Moves(MOVE_PETAL_DANCE, MOVE_WEATHER_BALL, MOVE_SUNNY_DAY, MOVE_POISON_JAB); }
    } WHEN {
        TURN { MOVE(player, MOVE_GROWL); EXPECT_MOVE(opponent, MOVE_SUNNY_DAY); }
    }
}

AI_SINGLE_BATTLE_TEST("Dualocke IA: clima, con nieve el primero la pone por Velo Aurora")
{
    GIVEN {
        AI_FLAGS(IA_JEFES);
        EQUIPO_JUGADOR(43)
        OPPONENT(SPECIES_CYCLIZAR) { Level(43); Moves(MOVE_STOMP, MOVE_SNOWSCAPE, MOVE_AURORA_VEIL, MOVE_OCTOLOCK); }
        OPPONENT(SPECIES_CAMERUPT) { Level(43); Moves(MOVE_HEAD_SMASH, MOVE_WEATHER_BALL, MOVE_SNOWSCAPE, MOVE_CORROSIVE_GAS); }
    } WHEN {
        TURN { MOVE(player, MOVE_GROWL); EXPECT_MOVE(opponent, MOVE_SNOWSCAPE); }
    }
}

AI_SINGLE_BATTLE_TEST("Dualocke IA: clima, los demás ponen el clima si no está")
{
    GIVEN {
        AI_FLAGS(IA_JEFES);
        EQUIPO_JUGADOR(43)
        OPPONENT(SPECIES_CAMERUPT) { Level(43); Moves(MOVE_HEAD_SMASH, MOVE_WEATHER_BALL, MOVE_SUNNY_DAY, MOVE_CORROSIVE_GAS); }
        OPPONENT(SPECIES_ROSERADE) { Level(43); Moves(MOVE_PETAL_DANCE, MOVE_WEATHER_BALL, MOVE_SUNNY_DAY, MOVE_POISON_JAB); }
    } WHEN {
        TURN { MOVE(player, MOVE_GROWL); EXPECT_MOVE(opponent, MOVE_SUNNY_DAY); }
    }
}

AI_SINGLE_BATTLE_TEST("Dualocke IA: espacio raro, el lento lo pone")
{
    GIVEN {
        AI_FLAGS(IA_JEFES);
        EQUIPO_JUGADOR(60)
        OPPONENT(SPECIES_MUK_ALOLA) { Level(62); Moves(MOVE_CRUNCH, MOVE_TRICK_ROOM, MOVE_CURSE, MOVE_THUNDERCLAP); }
        OPPONENT(SPECIES_FERROTHORN) { Level(62); Moves(MOVE_LEAF_STORM, MOVE_TRICK_ROOM, MOVE_CURSE, MOVE_SCORCHING_SANDS); }
    } WHEN {
        TURN { MOVE(player, MOVE_GROWL); EXPECT_MOVE(opponent, MOVE_TRICK_ROOM); }
    }
}

// Sin Omniscient no sabe si el jugador pega físico o especial hasta que lo ve (ShouldSetScreen)
AI_SINGLE_BATTLE_TEST("Dualocke IA: pantallas, el primero pone una cuando ha visto un ataque")
{
    GIVEN {
        AI_FLAGS(IA_JEFES);
        EQUIPO_JUGADOR(50)
        OPPONENT(SPECIES_CLAYDOL) { Level(50); Moves(MOVE_REFLECT, MOVE_LIGHT_SCREEN, MOVE_EARTH_POWER, MOVE_SWIFT); }
        OPPONENT(SPECIES_ABSOL) { Level(50); Moves(MOVE_SWORDS_DANCE, MOVE_REFLECT, MOVE_NIGHT_SLASH, MOVE_SWIFT); }
    } WHEN {
        TURN { MOVE(player, MOVE_MUD_SHOT); NOT_EXPECT_MOVES(opponent, MOVE_REFLECT, MOVE_LIGHT_SCREEN); }
        TURN { MOVE(player, MOVE_MUD_SHOT); EXPECT_MOVE(opponent, MOVE_LIGHT_SCREEN); }
    }
}

AI_SINGLE_BATTLE_TEST("Dualocke IA: velocidad, el primero pone Viento Afín")
{
    GIVEN {
        AI_FLAGS(IA_JEFES);
        EQUIPO_JUGADOR(50)
        OPPONENT(SPECIES_CLAYDOL) { Level(50); Moves(MOVE_TAILWIND, MOVE_ICY_WIND, MOVE_EARTH_POWER, MOVE_SWIFT); }
        OPPONENT(SPECIES_ABSOL) { Level(50); Moves(MOVE_ICY_WIND, MOVE_AGILITY, MOVE_NIGHT_SLASH, MOVE_SWIFT); }
    } WHEN {
        TURN { MOVE(player, MOVE_GROWL); EXPECT_MOVE(opponent, MOVE_TAILWIND); }
    }
}

AI_SINGLE_BATTLE_TEST("Dualocke IA: trampas, el primero las pone")
{
    GIVEN {
        AI_FLAGS(IA_JEFES);
        EQUIPO_JUGADOR(50)
        OPPONENT(SPECIES_CLAYDOL) { Level(50); Moves(MOVE_STEALTH_ROCK, MOVE_ROAR, MOVE_EARTH_POWER, MOVE_SWIFT); }
        OPPONENT(SPECIES_ABSOL) { Level(50); Moves(MOVE_ROAR, MOVE_TAUNT, MOVE_NIGHT_SLASH, MOVE_SWIFT); }
    } WHEN {
        TURN { MOVE(player, MOVE_GROWL); EXPECT_MOVE(opponent, MOVE_STEALTH_ROCK); }
    }
}

AI_SINGLE_BATTLE_TEST("Dualocke IA: estados, usa uno al empezar")
{
    GIVEN {
        AI_FLAGS(IA_JEFES);
        EQUIPO_JUGADOR(50)
        OPPONENT(SPECIES_CLAYDOL) { Level(50); Moves(MOVE_TOXIC, MOVE_CONFUSE_RAY, MOVE_EARTH_POWER, MOVE_SWIFT); }
        OPPONENT(SPECIES_ABSOL) { Level(50); Moves(MOVE_WILL_O_WISP, MOVE_YAWN, MOVE_NIGHT_SLASH, MOVE_SWIFT); }
    } WHEN {
        TURN { MOVE(player, MOVE_GROWL); EXPECT_MOVES(opponent, MOVE_TOXIC, MOVE_CONFUSE_RAY); }
    }
}

AI_SINGLE_BATTLE_TEST("Dualocke IA: aguante, envenena y se cura cuando le queda poca vida")
{
    GIVEN {
        AI_FLAGS(IA_JEFES);
        EQUIPO_JUGADOR(50)
        OPPONENT(SPECIES_CLAYDOL) { Level(50); HP(40); Moves(MOVE_TOXIC, MOVE_RECOVER, MOVE_EARTH_POWER, MOVE_SWIFT); }
        OPPONENT(SPECIES_ABSOL) { Level(50); Moves(MOVE_LEECH_SEED, MOVE_PROTECT, MOVE_NIGHT_SLASH, MOVE_SWIFT); }
    } WHEN {
        TURN { MOVE(player, MOVE_GROWL); EXPECT_MOVES(opponent, MOVE_RECOVER, MOVE_TOXIC); }
    }
}

AI_SINGLE_BATTLE_TEST("Dualocke IA: chetarse, se sube el ataque al empezar")
{
    GIVEN {
        AI_FLAGS(IA_JEFES);
        EQUIPO_JUGADOR(50)
        OPPONENT(SPECIES_ABSOL) { Level(50); Moves(MOVE_SWORDS_DANCE, MOVE_SUBSTITUTE, MOVE_NIGHT_SLASH, MOVE_SWIFT); }
        OPPONENT(SPECIES_CLAYDOL) { Level(50); Moves(MOVE_CALM_MIND, MOVE_PROTECT, MOVE_EARTH_POWER, MOVE_SWIFT); }
    } WHEN {
        TURN { MOVE(player, MOVE_GROWL); EXPECT_MOVES(opponent, MOVE_SWORDS_DANCE, MOVE_SUBSTITUTE); }
    }
}
