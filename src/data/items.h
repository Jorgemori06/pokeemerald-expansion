#if I_USE_EVO_HELD_ITEMS_FROM_BAG == TRUE
    #define EVO_HELD_ITEM_TYPE ITEM_USE_PARTY_MENU
    #define EVO_HELD_ITEM_FIELD_FUNC ItemUseOutOfBattle_EvolutionStone
#else
    #define EVO_HELD_ITEM_TYPE ITEM_USE_BAG_MENU
    #define EVO_HELD_ITEM_FIELD_FUNC ItemUseOutOfBattle_CannotUse
#endif

#define GEM_BOOST_PARAM ((I_GEM_BOOST_POWER >= GEN_6) ? 30 : 50)
#define TYPE_BOOST_PARAM ((I_TYPE_BOOST_POWER >= GEN_4) ? 20 : 10) // For non Pokémon-specific type-boosting held items.
#define POWER_ITEM_BOOST ((I_POWER_ITEM_BOOST >= GEN_7) ? 8 : 4)

#define X_ITEM_STAGES ((B_X_ITEMS_BUFF >= GEN_7) ? 2 : 1)

#define TREASURE_FACTOR ((I_SELL_VALUE_FRACTION >= GEN_9) ? 2 : 1)

#define ITEM_NAME(str) COMPOUND_STRING_SIZE_LIMIT(str, ITEM_NAME_LENGTH)
#define ITEM_PLURAL_NAME(str) COMPOUND_STRING_SIZE_LIMIT(str, ITEM_NAME_PLURAL_LENGTH)

const u8 gQuestionMarksItemName[] = _("????????");

const struct ItemInfo gItemsInfo[] =
{
    [ITEM_NONE] =
    {
        .name = gQuestionMarksItemName,
        .price = 0,
        .description = COMPOUND_STRING("?????"),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_UNCATEGORIZED,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_QuestionMark,
        .iconPalette = gItemIconPalette_QuestionMark,
    },

// Poké Balls

    [ITEM_STRANGE_BALL] =
    {
        .name = ES(ITEM_NAME("Strange Ball"), ITEM_NAME("Extraña Ball")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A Ball that has\n"
            "traveled across\n"
            "space and time."), COMPOUND_STRING("Una Ball que ha\n" "viajado por el\n" "espacio y el tiempo.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_STRANGE,
        .iconPic = gItemIcon_StrangeBall,
        .iconPalette = gItemIconPalette_StrangeBall,
    },

    [ITEM_POKE_BALL] =
    {
        .name = ITEM_NAME("Poké Ball"),
        .price = 200,
        .description = ES(COMPOUND_STRING("A tool used for\n"
            "catching wild\n"
            "Pokémon."), COMPOUND_STRING("Sirve para atrapar\n" "Pokémon salvajes.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_POKE,
        .iconPic = gItemIcon_PokeBall,
        .iconPalette = gItemIconPalette_PokeBall,
    },

    [ITEM_GREAT_BALL] =
    {
        .name = ES(ITEM_NAME("Great Ball"), ITEM_NAME("Super Ball")),
        .price = 600,
        .description = ES(COMPOUND_STRING("A good Ball with a\n"
            "higher catch rate\n"
            "than a Poké Ball."), COMPOUND_STRING("Atrapa mejor que una\n" "Poké Ball.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_GREAT,
        .iconPic = gItemIcon_GreatBall,
        .iconPalette = gItemIconPalette_GreatBall,
    },

    [ITEM_ULTRA_BALL] =
    {
        .name = ITEM_NAME("Ultra Ball"),
        .price = (I_PRICE >= GEN_7) ? 800 : 1200,
        .description = ES(COMPOUND_STRING("A better Ball with\n"
            "a higher catch rate\n"
            "than a Great Ball."), COMPOUND_STRING("Atrapa mejor que una\n" "Super Ball.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_ULTRA,
        .iconPic = gItemIcon_UltraBall,
        .iconPalette = gItemIconPalette_UltraBall,
    },

    [ITEM_MASTER_BALL] =
    {
        .name = ITEM_NAME("Master Ball"),
        .price = 0,
        .description = ES(COMPOUND_STRING("The best Ball that\n"
            "catches a Pokémon\n"
            "without fail."), COMPOUND_STRING("La mejor Ball.\n" "Atrapa a cualquier\n" "Pokémon.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_MASTER,
        .iconPic = gItemIcon_MasterBall,
        .iconPalette = gItemIconPalette_MasterBall,
    },

    [ITEM_PREMIER_BALL] =
    {
        .name = ES(ITEM_NAME("Premier Ball"), ITEM_NAME("Honor Ball")),
        .price = (I_PRICE >= GEN_7) ? 20 : 200,
        .description = ES(COMPOUND_STRING("A rare Ball made\n"
            "in commemoration\n"
            "of some event."), COMPOUND_STRING("Una Ball rara hecha\n" "para celebrar algo.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_PREMIER,
        .iconPic = gItemIcon_PremierBall,
        .iconPalette = gItemIconPalette_PremierBall,
    },

    [ITEM_HEAL_BALL] =
    {
        .name = ES(ITEM_NAME("Heal Ball"), ITEM_NAME("Sana Ball")),
        .price = 300,
        .description = ES(COMPOUND_STRING("A remedial Ball\n"
            "that restores\n"
            "caught Pokémon."), COMPOUND_STRING("Cura al Pokémon que\n" "se atrapa con ella.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_HEAL,
        .iconPic = gItemIcon_HealBall,
        .iconPalette = gItemIconPalette_HealBall,
    },

    [ITEM_NET_BALL] =
    {
        .name = ES(ITEM_NAME("Net Ball"), ITEM_NAME("Malla Ball")),
        .price = 1000,
        .description = ES(COMPOUND_STRING("A Ball that works\n"
            "well on Water- and\n"
            "Bug-type Pokémon."), COMPOUND_STRING("Va mejor con Pokémon\n" "de tipo Agua y\n" "Bicho.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_NET,
        .iconPic = gItemIcon_NetBall,
        .iconPalette = gItemIconPalette_NetBall,
    },

    [ITEM_NEST_BALL] =
    {
        .name = ES(ITEM_NAME("Nest Ball"), ITEM_NAME("Nido Ball")),
        .price = 1000,
        .description = ES(COMPOUND_STRING("A Ball that works\n"
            "better on weaker\n"
            "Pokémon."), COMPOUND_STRING("Va mejor con Pokémon\n" "de nivel bajo.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_NEST,
        .iconPic = gItemIcon_NestBall,
        .iconPalette = gItemIconPalette_NestBall,
    },

    [ITEM_DIVE_BALL] =
    {
        .name = ES(ITEM_NAME("Dive Ball"), ITEM_NAME("Buceo Ball")),
        .price = 1000,
        .description = COMPOUND_STRING(
            "A Ball that works\n"
            "better on Pokémon\n"
        #if B_DIVE_BALL_MODIFIER >= GEN_4
            "in the water."),
        #else
            "on the ocean floor."),
        #endif
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_DIVE,
        .iconPic = gItemIcon_DiveBall,
        .iconPalette = gItemIconPalette_DiveBall,
    },

    [ITEM_DUSK_BALL] =
    {
        .name = ES(ITEM_NAME("Dusk Ball"), ITEM_NAME("Ocaso Ball")),
        .price = 1000,
        .description = ES(COMPOUND_STRING("A Ball that works\n"
            "better at night\n"
            "or in dark places."), COMPOUND_STRING("Va mejor de noche o\n" "en sitios oscuros.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_DUSK,
        .iconPic = gItemIcon_DuskBall,
        .iconPalette = gItemIconPalette_DuskBall,
    },

    [ITEM_TIMER_BALL] =
    {
        .name = ES(ITEM_NAME("Timer Ball"), ITEM_NAME("Turno Ball")),
        .price = 1000,
        .description = ES(COMPOUND_STRING("A Ball that gains\n"
            "power in battles\n"
            "taking many turns."), COMPOUND_STRING("Va mejor cuantos más\n" "turnos dure el\n" "combate.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_TIMER,
        .iconPic = gItemIcon_TimerBall,
        .iconPalette = gItemIconPalette_RepeatBall,
    },

    [ITEM_QUICK_BALL] =
    {
        .name = ES(ITEM_NAME("Quick Ball"), ITEM_NAME("Veloz Ball")),
        .price = 1000,
        .description = ES(COMPOUND_STRING("A Ball that works\n"
            "better at the\n"
            "start of a battle."), COMPOUND_STRING("Va mejor al\n" "principio del\n" "combate.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_QUICK,
        .iconPic = gItemIcon_QuickBall,
        .iconPalette = gItemIconPalette_QuickBall,
    },

    [ITEM_REPEAT_BALL] =
    {
        .name = ES(ITEM_NAME("Repeat Ball"), ITEM_NAME("Acopio Ball")),
        .price = 1000,
        .description = ES(COMPOUND_STRING("A Ball that works\n"
            "better on Pokémon\n"
            "caught before."), COMPOUND_STRING("Va mejor con\n" "especies ya\n" "atrapadas.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_REPEAT,
        .iconPic = gItemIcon_RepeatBall,
        .iconPalette = gItemIconPalette_RepeatBall,
    },

    [ITEM_LUXURY_BALL] =
    {
        .name = ES(ITEM_NAME("Luxury Ball"), ITEM_NAME("Lujo Ball")),
        .price = (I_PRICE >= GEN_8) ? 3000 : 1000,
        .description = ES(COMPOUND_STRING("A cozy Ball that\n"
            "makes Pokémon\n"
            "quickly friendly."), COMPOUND_STRING("Una Ball cómoda: el\n" "Pokémon coge cariño\n" "antes.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_LUXURY,
        .iconPic = gItemIcon_LuxuryBall,
        .iconPalette = gItemIconPalette_LuxuryBall,
    },

    [ITEM_LEVEL_BALL] =
    {
        .name = ES(ITEM_NAME("Level Ball"), ITEM_NAME("Nivel Ball")),
        .price = (I_PRICE >= GEN_7) ? 0 : 300,
        .description = ES(COMPOUND_STRING("A Ball that works\n"
            "better on lower-\n"
            "level Pokémon."), COMPOUND_STRING("Va mejor con Pokémon\n" "de menos nivel.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_LEVEL,
        .iconPic = gItemIcon_LevelBall,
        .iconPalette = gItemIconPalette_LevelBall,
    },

    [ITEM_LURE_BALL] =
    {
        .name = ES(ITEM_NAME("Lure Ball"), ITEM_NAME("Cebo Ball")),
        .price = (I_PRICE >= GEN_7) ? 0 : 300,
        .description = ES(COMPOUND_STRING("A Ball that works\n"
            "better on Pokémon\n"
            "hooked by a Rod."), COMPOUND_STRING("Va mejor con Pokémon\n" "pescados con caña.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_LURE,
        .iconPic = gItemIcon_LureBall,
        .iconPalette = gItemIconPalette_LureBall,
    },

    [ITEM_MOON_BALL] =
    {
        .name = ES(ITEM_NAME("Moon Ball"), ITEM_NAME("Luna Ball")),
        .price = (I_PRICE >= GEN_7) ? 0 : 300,
        .description = ES(COMPOUND_STRING("A Ball that works\n"
            "better on Moon\n"
            "Stone evolvers."), COMPOUND_STRING("Va mejor con los que\n" "evolucionan con\n" "Piedra Lunar.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_MOON,
        .iconPic = gItemIcon_MoonBall,
        .iconPalette = gItemIconPalette_MoonBall,
    },

    [ITEM_FRIEND_BALL] =
    {
        .name = ES(ITEM_NAME("Friend Ball"), ITEM_NAME("Amigo Ball")),
        .price = (I_PRICE >= GEN_7) ? 0 : 300,
        .description = ES(COMPOUND_STRING("A Ball that makes\n"
            "caught Pokémon\n"
            "more friendly."), COMPOUND_STRING("El Pokémon atrapado\n" "le coge más cariño.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_FRIEND,
        .iconPic = gItemIcon_FriendBall,
        .iconPalette = gItemIconPalette_FriendBall,
    },

    [ITEM_LOVE_BALL] =
    {
        .name = ES(ITEM_NAME("Love Ball"), ITEM_NAME("Amor Ball")),
        .price = (I_PRICE >= GEN_7) ? 0 : 300,
        .description = ES(COMPOUND_STRING("A Ball that works\n"
            "better on the\n"
            "opposite gender."), COMPOUND_STRING("Va mejor con los del\n" "sexo opuesto.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_LOVE,
        .iconPic = gItemIcon_LoveBall,
        .iconPalette = gItemIconPalette_LoveBall,
    },

    [ITEM_FAST_BALL] =
    {
        .name = ES(ITEM_NAME("Fast Ball"), ITEM_NAME("Rapid Ball")),
        .price = (I_PRICE >= GEN_7) ? 0 : 300,
        .description = ES(COMPOUND_STRING("A Ball that works\n"
            "better on fast\n"
            "Pokémon."), COMPOUND_STRING("Va mejor con Pokémon\n" "muy rápidos.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_FAST,
        .iconPic = gItemIcon_FastBall,
        .iconPalette = gItemIconPalette_FastBall,
    },

    [ITEM_HEAVY_BALL] =
    {
        .name = ES(ITEM_NAME("Heavy Ball"), ITEM_NAME("Peso Ball")),
        .price = (I_PRICE >= GEN_7) ? 0 : 300,
        .description = ES(COMPOUND_STRING("A Ball that works\n"
            "better on very\n"
            "heavy Pokémon."), COMPOUND_STRING("Va mejor con Pokémon\n" "muy pesados.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_HEAVY,
        .iconPic = gItemIcon_HeavyBall,
        .iconPalette = gItemIconPalette_HeavyBall,
    },

    [ITEM_DREAM_BALL] =
    {
        .name = ES(ITEM_NAME("Dream Ball"), ITEM_NAME("Ensueño Ball")),
        .price = 0,
        .description = COMPOUND_STRING(
        #if B_DREAM_BALL_MODIFIER >= GEN_8
            "A Ball that works\n"
            "better on Pokémon\n"
            "that are alseep."),
        #else
            "A special Ball that\n"
            "appears in the\n"
            "Entree Forest."),
        #endif
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_DREAM,
        .iconPic = gItemIcon_DreamBall,
        .iconPalette = gItemIconPalette_DreamBall,
    },

    [ITEM_SAFARI_BALL] =
    {
        .name = ITEM_NAME("Safari Ball"),
        .price = 0,
        .description = ES(COMPOUND_STRING("A special Ball that\n"
            "is used only in the\n"
            "Safari Zone."), COMPOUND_STRING("Una Ball especial de\n" "la Zona Safari.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_SAFARI,
        .iconPic = gItemIcon_SafariBall,
        .iconPalette = gItemIconPalette_SafariBall,
    },

    [ITEM_SPORT_BALL] =
    {
        .name = ES(ITEM_NAME("Sport Ball"), ITEM_NAME("Competi Ball")),
        .price = (I_PRICE <= GEN_3 || I_PRICE >= GEN_9) ? 0 : 300,
        .description = ES(COMPOUND_STRING("A special Ball that\n"
            "is used in the Bug-\n"
            "Catching Contest."), COMPOUND_STRING("Una Ball especial\n" "del Concurso de\n" "Bichos.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_SPORT,
        .iconPic = gItemIcon_SportBall,
        .iconPalette = gItemIconPalette_SportBall,
    },

    [ITEM_PARK_BALL] =
    {
        .name = ES(ITEM_NAME("Park Ball"), ITEM_NAME("Parque Ball")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A special Poké Ball\n"
            "for the Pal Park."), COMPOUND_STRING("Poké Ball que se\n" "utiliza dentro del\n" "Parque Compi.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_PARK,
        .iconPic = gItemIcon_ParkBall,
        .iconPalette = gItemIconPalette_ParkBall,
    },

    [ITEM_BEAST_BALL] =
    {
        .name = ES(ITEM_NAME("Beast Ball"), ITEM_NAME("Ente Ball")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A special Poké Ball\n"
            "designed to catch\n"
            "Ultra Beasts."), COMPOUND_STRING("Una Ball especial\n" "para atrapar\n" "Ultraentes.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_BEAST,
        .iconPic = gItemIcon_BeastBall,
        .iconPalette = gItemIconPalette_BeastBall,
    },

    [ITEM_CHERISH_BALL] =
    {
        .name = ES(ITEM_NAME("Cherish Ball"), ITEM_NAME("Gloria Ball")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A rare Ball crafted\n"
            "to commemorate a\n"
            "special occasion."), COMPOUND_STRING("Una Ball rara hecha\n" "para una ocasión\n" "especial.")),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_CHERISH,
        .iconPic = gItemIcon_CherishBall,
        .iconPalette = gItemIconPalette_CherishBall,
    },

// Medicine

    [ITEM_POTION] =
    {
        .name = ES(ITEM_NAME("Potion"), ITEM_NAME("Poción")),
        .price = (I_PRICE >= GEN_7) ? 200 : 300,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("Restores the HP of\n"
            "a Pokémon by\n"
            "20 points."), COMPOUND_STRING("Restaura 20 PS a un\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_Potion,
        .flingPower = 30,
        .iconPic = gItemIcon_Potion,
        .iconPalette = gItemIconPalette_Potion,
    },

    [ITEM_SUPER_POTION] =
    {
        .name = ES(ITEM_NAME("Super Potion"), ITEM_NAME("Superpoción")),
        .price = 700,
        .holdEffectParam = 60,
        .description = COMPOUND_STRING(
            "Restores the HP of\n"
            "a Pokémon by\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "60 points."),
        #else
            "50 points."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_SuperPotion,
        .flingPower = 30,
        .iconPic = gItemIcon_Potion,
        .iconPalette = gItemIconPalette_SuperPotion,
    },

    [ITEM_HYPER_POTION] =
    {
        .name = ES(ITEM_NAME("Hyper Potion"), ITEM_NAME("Hiperpoción")),
        .price = (I_PRICE >= GEN_2 && I_PRICE <= GEN_6) ? 1200 : 1500,
        .holdEffectParam = 120,
        .description = COMPOUND_STRING(
            "Restores the HP of\n"
            "a Pokémon by\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "120 points."),
        #else
            "200 points."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_HyperPotion,
        .flingPower = 30,
        .iconPic = gItemIcon_Potion,
        .iconPalette = gItemIconPalette_HyperPotion,
    },

    [ITEM_MAX_POTION] =
    {
        .name = ES(ITEM_NAME("Max Potion"), ITEM_NAME("Poción Máxima")),
        .price = 2500,
        .holdEffectParam = 255,
        .description = ES(COMPOUND_STRING("Fully restores the\n"
            "HP of a Pokémon."), COMPOUND_STRING("Restaura todos los\n" "PS de un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_MaxPotion,
        .flingPower = 30,
        .iconPic = gItemIcon_LargePotion,
        .iconPalette = gItemIconPalette_MaxPotion,
    },

    [ITEM_FULL_RESTORE] =
    {
        .name = ES(ITEM_NAME("Full Restore"), ITEM_NAME("Restaurar Todo")),
        .price = 3000,
        .holdEffectParam = 255,
        .description = ES(COMPOUND_STRING("Fully restores the\n"
            "HP and status of a\n"
            "Pokémon."), COMPOUND_STRING("Restaura todos los\n" "PS y el estado de un\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_HEAL_AND_CURE_STATUS,
        .effect = gItemEffect_FullRestore,
        .flingPower = 30,
        .iconPic = gItemIcon_LargePotion,
        .iconPalette = gItemIconPalette_FullRestore,
    },

    [ITEM_REVIVE] =
    {
        .name = ES(ITEM_NAME("Revive"), ITEM_NAME("Revivir")),
        .price = (I_PRICE >= GEN_7) ? 2000 : 1500,
        .description = ES(COMPOUND_STRING("Revives a fainted\n"
            "Pokémon with half\n"
            "its HP."), COMPOUND_STRING("Revive a un Pokémon\n" "con la mitad de sus\n" "PS.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_REVIVE,
        .effect = gItemEffect_Revive,
        .flingPower = 30,
        .iconPic = gItemIcon_Revive,
        .iconPalette = gItemIconPalette_Revive,
    },

    [ITEM_MAX_REVIVE] =
    {
        .name = ES(ITEM_NAME("Max Revive"), ITEM_NAME("Revivir Máximo")),
        .price = 4000,
        .description = ES(COMPOUND_STRING("Revives a fainted\n"
            "Pokémon with all\n"
            "its HP."), COMPOUND_STRING("Revive a un Pokémon\n" "con todos sus PS.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_REVIVE,
        .effect = gItemEffect_MaxRevive,
        .flingPower = 30,
        .iconPic = gItemIcon_MaxRevive,
        .iconPalette = gItemIconPalette_Revive,
    },

    [ITEM_FRESH_WATER] =
    {
        .name = ES(ITEM_NAME("Fresh Water"), ITEM_NAME("Agua Fresca")),
        .price = 200,
        .holdEffectParam = 30,
        .description = COMPOUND_STRING(
            "A mineral water\n"
            "that restores HP\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "by 30 points."),
        #else
            "by 50 points."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_FreshWater,
        .flingPower = 30,
        .iconPic = gItemIcon_FreshWater,
        .iconPalette = gItemIconPalette_FreshWater,
    },

    [ITEM_SODA_POP] =
    {
        .name = ES(ITEM_NAME("Soda Pop"), ITEM_NAME("Refresco")),
        .price = 300,
        .holdEffectParam = 50,
        .description = COMPOUND_STRING(
            "A fizzy soda drink\n"
            "that restores HP\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "by 50 points."),
        #else
            "by 60 points."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_SodaPop,
        .flingPower = 30,
        .iconPic = gItemIcon_SodaPop,
        .iconPalette = gItemIconPalette_SodaPop,
    },

    [ITEM_LEMONADE] =
    {
        .name = ES(ITEM_NAME("Lemonade"), ITEM_NAME("Limonada")),
        .price = (I_PRICE >= GEN_7) ? 400 : 350,
        .holdEffectParam = 70,
        .description = COMPOUND_STRING(
            "A very sweet drink\n"
            "that restores HP\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "by 70 points."),
        #else
            "by 80 points."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_Lemonade,
        .flingPower = 30,
        .iconPic = gItemIcon_Lemonade,
        .iconPalette = gItemIconPalette_Lemonade,
    },

    [ITEM_MOOMOO_MILK] =
    {
        .name = ES(ITEM_NAME("Moomoo Milk"), ITEM_NAME("Leche Mu-mu")),
        .price = (I_PRICE >= GEN_7) ? 600 : 500,
        .holdEffectParam = 100,
        .description = ES(COMPOUND_STRING("A nutritious milk\n"
            "that restores HP\n"
            "by 100 points."), COMPOUND_STRING("Leche nutritiva que\n" "restaura 100 PS.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_MoomooMilk,
        .flingPower = 30,
        .iconPic = gItemIcon_MoomooMilk,
        .iconPalette = gItemIconPalette_MoomooMilk,
    },

    [ITEM_ENERGY_POWDER] =
    {
        .name = ES(ITEM_NAME("Energy Powder"), ITEM_NAME("Polvo Energía")),
        .price = 500,
        .description = COMPOUND_STRING(
            "A bitter powder\n"
            "that restores HP\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "by 60 points."),
        #else
            "by 50 points."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_EnergyPowder,
        .flingPower = 30,
        .iconPic = gItemIcon_Powder,
        .iconPalette = gItemIconPalette_EnergyPowder,
    },

    [ITEM_ENERGY_ROOT] =
    {
        .name = ES(ITEM_NAME("Energy Root"), ITEM_NAME("Raíz Energía")),
        .price = (I_PRICE >= GEN_7) ? 1200 : 800,
        .description = COMPOUND_STRING(
            "A bitter root\n"
            "that restores HP\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "by 120 points."),
        #else
            "by 200 points."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_EnergyRoot,
        .flingPower = 30,
        .iconPic = gItemIcon_EnergyRoot,
        .iconPalette = gItemIconPalette_EnergyRoot,
    },

    [ITEM_HEAL_POWDER] =
    {
        .name = ES(ITEM_NAME("Heal Powder"), ITEM_NAME("Polvo Curación")),
        .price = (I_PRICE >= GEN_7) ? 300 : 450,
        .description = ES(COMPOUND_STRING("A bitter powder\n"
            "that heals all\n"
            "status problems."), COMPOUND_STRING("Un polvo amargo que\n" "cura todos los\n" "estados.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_HealPowder,
        .flingPower = 30,
        .iconPic = gItemIcon_Powder,
        .iconPalette = gItemIconPalette_HealPowder,
    },

    [ITEM_REVIVAL_HERB] =
    {
        .name = ES(ITEM_NAME("Revival Herb"), ITEM_NAME("Hierba Revivir")),
        .price = 2800,
        .description = ES(COMPOUND_STRING("A very bitter herb\n"
            "that revives a\n"
            "fainted Pokémon."), COMPOUND_STRING("Una hierba muy\n" "amarga que revive a\n" "un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_REVIVE,
        .effect = gItemEffect_RevivalHerb,
        .flingPower = 30,
        .iconPic = gItemIcon_RevivalHerb,
        .iconPalette = gItemIconPalette_RevivalHerb,
    },

    [ITEM_ANTIDOTE] =
    {
        .name = ES(ITEM_NAME("Antidote"), ITEM_NAME("Antídoto")),
        .price = (I_PRICE >= GEN_7) ? 200 : 100,
        .description = ES(COMPOUND_STRING("Heals a poisoned\n"
            "Pokémon."), COMPOUND_STRING("Cura el\n" "envenenamiento.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_Antidote,
        .flingPower = 30,
        .iconPic = gItemIcon_StatusHeal,
        .iconPalette = gItemIconPalette_Antidote,
    },

    [ITEM_PARALYZE_HEAL] =
    {
        .name = ES(ITEM_NAME("Paralyze Heal"), ITEM_NAME("Antiparalizador")),
        .price = (I_PRICE == GEN_7) ? 300 : 200,
        .description = ES(COMPOUND_STRING("Heals a paralyzed\n"
            "Pokémon."), COMPOUND_STRING("Medicina en espray\n" "que cura a un\n" "Pokémon paralizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_ParalyzeHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_StatusHeal,
        .iconPalette = gItemIconPalette_ParalyzeHeal,
    },

    [ITEM_BURN_HEAL] =
    {
        .name = ES(ITEM_NAME("Burn Heal"), ITEM_NAME("Antiquemar")),
    #if I_PRICE >= GEN_8
        .price = 200,
    #elif I_PRICE == GEN_7
        .price = 300,
    #else
        .price = 250,
    #endif
        .description = ES(COMPOUND_STRING("Heals Pokémon\n"
            "of a burn."), COMPOUND_STRING("Cura las quemaduras.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_BurnHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_StatusHeal,
        .iconPalette = gItemIconPalette_BurnHeal,
    },

    [ITEM_ICE_HEAL] =
    {
        .name = ES(ITEM_NAME("Ice Heal"), ITEM_NAME("Antihielo")),
    #if I_PRICE >= GEN_8
        .price = 200,
    #elif I_PRICE == GEN_7
        .price = 100,
    #else
        .price = 250,
    #endif
        .description = COMPOUND_STRING(
        #if B_USE_FROSTBITE
            "Heals Pokémon\n"
            "of frostbite."),
        #else
            "Defrosts a frozen\n"
            "Pokémon."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_IceHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_StatusHeal,
        .iconPalette = gItemIconPalette_IceHeal,
    },

    [ITEM_AWAKENING] =
    {
        .name = ES(ITEM_NAME("Awakening"), ITEM_NAME("Despertar")),
    #if (I_PRICE >= GEN_8 || I_PRICE == GEN_1)
        .price = 200,
    #elif I_PRICE == GEN_7
        .price = 100,
    #else
        .price = 250,
    #endif
        .description = ES(COMPOUND_STRING("Awakens a sleeping\n"
            "Pokémon."), COMPOUND_STRING("Despierta a un\n" "Pokémon dormido.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_Awakening,
        .flingPower = 30,
        .iconPic = gItemIcon_StatusHeal,
        .iconPalette = gItemIconPalette_Awakening,
    },

    [ITEM_FULL_HEAL] =
    {
        .name = ES(ITEM_NAME("Full Heal"), ITEM_NAME("Cura Total")),
        .price = (I_PRICE >= GEN_7) ? 400 : 600,
        .description = ES(COMPOUND_STRING("Heals all the\n"
            "status problems of\n"
            "one Pokémon."), COMPOUND_STRING("Cura todos los\n" "problemas de estado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_FullHeal,
        .iconPalette = gItemIconPalette_FullHeal,
    },

    [ITEM_ETHER] =
    {
        .name = ES(ITEM_NAME("Ether"), ITEM_NAME("Éter")),
        .price = (I_PRICE >= GEN_2) ? 1200 : 1,
        .holdEffectParam = 10,
        .description = ES(COMPOUND_STRING("Restores the PP\n"
            "of a selected move\n"
            "by 10."), COMPOUND_STRING("Restaura 10 PP del\n" "movimiento elegido\n" "de un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PP_RECOVERY,
        .type = ITEM_USE_PARTY_MENU_MOVES,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = EFFECT_ITEM_RESTORE_PP,
        .effect = gItemEffect_Ether,
        .flingPower = 30,
        .iconPic = gItemIcon_Ether,
        .iconPalette = gItemIconPalette_Ether,
    },

    [ITEM_MAX_ETHER] =
    {
        .name = ES(ITEM_NAME("Max Ether"), ITEM_NAME("Éter Máximo")),
        .price = (I_PRICE >= GEN_2) ? 2000 : 1,
        .holdEffectParam = 255,
        .description = ES(COMPOUND_STRING("Fully restores the\n"
            "PP of a selected\n"
            "move."), COMPOUND_STRING("Restaura todos los\n" "PP de un movimiento.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PP_RECOVERY,
        .type = ITEM_USE_PARTY_MENU_MOVES,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = EFFECT_ITEM_RESTORE_PP,
        .effect = gItemEffect_MaxEther,
        .flingPower = 30,
        .iconPic = gItemIcon_Ether,
        .iconPalette = gItemIconPalette_MaxEther,
    },

    [ITEM_ELIXIR] =
    {
        .name = ITEM_NAME("Elixir"),
        .price = (I_PRICE >= GEN_2) ? 3000 : 1,
        .holdEffectParam = 10,
        .description = ES(COMPOUND_STRING("Restores the PP\n"
            "of all moves by 10."), COMPOUND_STRING("Restaura 10 PP a\n" "todos los\n" "movimientos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PP_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = EFFECT_ITEM_RESTORE_PP,
        .effect = gItemEffect_Elixir,
        .flingPower = 30,
        .iconPic = gItemIcon_Ether,
        .iconPalette = gItemIconPalette_Elixir,
    },

    [ITEM_MAX_ELIXIR] =
    {
        .name = ES(ITEM_NAME("Max Elixir"), ITEM_NAME("Elixir Máximo")),
        .price = (I_PRICE >= GEN_2) ? 4500 : 1,
        .holdEffectParam = 255,
        .description = ES(COMPOUND_STRING("Fully restores the\n"
            "PP of a Pokémon's\n"
            "moves."), COMPOUND_STRING("Restaura todos los\n" "PP de todos los\n" "movimientos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PP_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = EFFECT_ITEM_RESTORE_PP,
        .effect = gItemEffect_MaxElixir,
        .flingPower = 30,
        .iconPic = gItemIcon_Ether,
        .iconPalette = gItemIconPalette_MaxElixir,
    },

    [ITEM_BERRY_JUICE] =
    {
        .name = ES(ITEM_NAME("Berry Juice"), ITEM_NAME("Zumo de Baya")),
        .price = 100,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A 100% pure juice\n"
            "that restores HP\n"
            "by 20 points."), COMPOUND_STRING("Zumo de bayas 100%\n" "natural que restaura\n" "20 PS de un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_Potion,
        .flingPower = 30,
        .iconPic = gItemIcon_BerryJuice,
        .iconPalette = gItemIconPalette_BerryJuice,
    },

    [ITEM_SACRED_ASH] =
    {
        .name = ES(ITEM_NAME("Sacred Ash"), ITEM_NAME("Ceniza Sagrada")),
        .pluralName = ITEM_PLURAL_NAME("Sacred Ashes"),
        .price = (I_PRICE >= GEN_7) ? 50000 : 200,
        .description = ES(COMPOUND_STRING("Fully revives and\n"
            "restores all\n"
            "fainted Pokémon."), COMPOUND_STRING("Revive y cura del\n" "todo a los Pokémon\n" "debilitados.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_SacredAsh,
        .effect = gItemEffect_SacredAsh,
        .flingPower = 30,
        .iconPic = gItemIcon_DittoPowder,
        .iconPalette = gItemIconPalette_SacredAsh,
    },

    [ITEM_SWEET_HEART] =
    {
        .name = ES(ITEM_NAME("Sweet Heart"), ITEM_NAME("Corazón Dulce")),
        .price = (I_PRICE >= GEN_7) ? 3000 : 100,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A sweet chocolate\n"
            "that restores HP\n"
            "by 20 points."), COMPOUND_STRING("Chocolatina de sabor\n" "dulce. Restaura 20\n" "PS de un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_Potion,
        .flingPower = 30,
        .iconPic = gItemIcon_SweetHeart,
        .iconPalette = gItemIconPalette_SweetHeart,
    },

    [ITEM_MAX_HONEY] =
    {
        .name = ES(ITEM_NAME("Max Honey"), ITEM_NAME("Maxipanal")),
        .pluralName = ITEM_PLURAL_NAME("Max Honey"),
        .price = 8000,
        .description = ES(COMPOUND_STRING("Revives a fainted\n"
            "Pokémon with all\n"
            "its HP."), COMPOUND_STRING("Revive a un Pokémon\n" "con todos sus PS.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_REVIVE,
        .effect = gItemEffect_MaxRevive,
        .flingPower = 30,
        .iconPic = gItemIcon_MaxHoney,
        .iconPalette = gItemIconPalette_MaxHoney,
    },

// Local specialties

    [ITEM_PEWTER_CRUNCHIES] =
    {
        .name = ES(ITEM_NAME("Pewter Crunchies"), ITEM_NAME("Rokikos")),
        .pluralName = ITEM_PLURAL_NAME("Pewter Crunchies"),
        .price = 250,
        .description = ES(COMPOUND_STRING("A local specialty\n"
            "that heals all\n"
            "status problems."), COMPOUND_STRING("Especialidad local\n" "que cura todos los\n" "estados.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_PewterCrunchies,
        .iconPalette = gItemIconPalette_PewterCrunchies,
    },

    [ITEM_RAGE_CANDY_BAR] =
    {
        .name = ES(ITEM_NAME("Rage Candy Bar"), ITEM_NAME("Caramelo Furia")),
        .price = (I_PRICE >= GEN_7) ? 350 : 300,
        .description = ES(COMPOUND_STRING("A local specialty\n"
            "that heals all\n"
            "status problems."), COMPOUND_STRING("Especialidad local\n" "que cura todos los\n" "estados.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_RageCandyBar,
        .iconPalette = gItemIconPalette_RageCandyBar,
    },

    [ITEM_LAVA_COOKIE] =
    {
        .name = ES(ITEM_NAME("Lava Cookie"), ITEM_NAME("Galleta Lava")),
        .price = (I_PRICE >= GEN_7) ? 350 : 200,
        .description = ES(COMPOUND_STRING("A local specialty\n"
            "that heals all\n"
            "status problems."), COMPOUND_STRING("Especialidad local\n" "que cura todos los\n" "estados.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_LavaCookie,
        .iconPalette = gItemIconPalette_LavaCookieAndLetter,
    },

    [ITEM_OLD_GATEAU] =
    {
        .name = ES(ITEM_NAME("Old Gateau"), ITEM_NAME("Barrita Plus")),
        .pluralName = ITEM_PLURAL_NAME("Old Gateaux"),
        .price = (I_PRICE >= GEN_7) ? 350 : 200,
        .description = ES(COMPOUND_STRING("A local specialty\n"
            "that heals all\n"
            "status problems."), COMPOUND_STRING("Especialidad local\n" "que cura todos los\n" "estados.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_OldGateau,
        .iconPalette = gItemIconPalette_OldGateau,
    },

    [ITEM_CASTELIACONE] =
    {
        .name = ES(ITEM_NAME("Casteliacone"), ITEM_NAME("Porcehelado")),
        .price = (I_PRICE >= GEN_7) ? 350 : 100,
        .description = ES(COMPOUND_STRING("A local specialty\n"
            "that heals all\n"
            "status problems."), COMPOUND_STRING("Especialidad local\n" "que cura todos los\n" "estados.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_Casteliacone,
        .iconPalette = gItemIconPalette_Casteliacone,
    },

    [ITEM_LUMIOSE_GALETTE] =
    {
        .name = ES(ITEM_NAME("Lumiose Galette"), ITEM_NAME("Crêpe Luminalia")),
        .price = (I_PRICE >= GEN_7) ? 350 : 200,
        .description = ES(COMPOUND_STRING("A local specialty\n"
            "that heals all\n"
            "status problems."), COMPOUND_STRING("Especialidad local\n" "que cura todos los\n" "estados.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_LumioseGalette,
        .iconPalette = gItemIconPalette_LumioseGalette,
    },

    [ITEM_SHALOUR_SABLE] =
    {
        .name = ES(ITEM_NAME("Shalour Sable"), ITEM_NAME("Galleta Yantra")),
        .price = (I_PRICE >= GEN_7) ? 350 : 200,
        .description = ES(COMPOUND_STRING("A local specialty\n"
            "that heals all\n"
            "status problems."), COMPOUND_STRING("Especialidad local\n" "que cura todos los\n" "estados.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_ShalourSable,
        .iconPalette = gItemIconPalette_ShalourSable,
    },

    [ITEM_BIG_MALASADA] =
    {
        .name = ES(ITEM_NAME("Big Malasada"), ITEM_NAME("Malasada Maxi")),
        .price = 350,
        .description = ES(COMPOUND_STRING("A local specialty\n"
            "that heals all\n"
            "status problems."), COMPOUND_STRING("Especialidad local\n" "que cura todos los\n" "estados.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_BigMalasada,
        .iconPalette = gItemIconPalette_BigMalasada,
    },

// Vitamins

    [ITEM_HP_UP] =
    {
        .name = ES(ITEM_NAME("HP Up"), ITEM_NAME("Más PS")),
        .price = (I_PRICE >= GEN_7) ? 10000 : 9800,
        .description = ES(COMPOUND_STRING("Raises the base HP\n"
            "of one Pokémon."), COMPOUND_STRING("Nutritiva bebida que\n" "potencia los PS de\n" "base de un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_DRINK,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_HPUp,
        .flingPower = 30,
        .iconPic = gItemIcon_HPUp,
        .iconPalette = gItemIconPalette_HPUp,
    },

    [ITEM_PROTEIN] =
    {
        .name = ES(ITEM_NAME("Protein"), ITEM_NAME("Proteína")),
        .price = (I_PRICE >= GEN_7) ? 10000 : 9800,
        .description = ES(COMPOUND_STRING("Raises the base\n"
            "Attack stat of one\n"
            "Pokémon."), COMPOUND_STRING("Sube la base de\n" "Ataque de un\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_DRINK,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_Protein,
        .flingPower = 30,
        .iconPic = gItemIcon_Vitamin,
        .iconPalette = gItemIconPalette_Protein,
    },

    [ITEM_IRON] =
    {
        .name = ES(ITEM_NAME("Iron"), ITEM_NAME("Hierro")),
        .price = (I_PRICE >= GEN_7) ? 10000 : 9800,
        .description = ES(COMPOUND_STRING("Raises the base\n"
            "Defense stat of\n"
            "one Pokémon."), COMPOUND_STRING("Sube la base de\n" "Defensa de un\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_DRINK,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_Iron,
        .flingPower = 30,
        .iconPic = gItemIcon_Vitamin,
        .iconPalette = gItemIconPalette_Iron,
    },

    [ITEM_CALCIUM] =
    {
        .name = ES(ITEM_NAME("Calcium"), ITEM_NAME("Calcio")),
        .price = (I_PRICE >= GEN_7) ? 10000 : 9800,
        .description = ES(COMPOUND_STRING("Raises the base\n"
            "Sp. Atk stat of one\n"
            "Pokémon."), COMPOUND_STRING("Sube la base de At.\n" "Esp. de un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_DRINK,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_Calcium,
        .flingPower = 30,
        .iconPic = gItemIcon_Vitamin,
        .iconPalette = gItemIconPalette_Calcium,
    },

    [ITEM_ZINC] =
    {
        .name = ITEM_NAME("Zinc"),
        .price = (I_PRICE >= GEN_7) ? 10000 : 9800,
        .description = ES(COMPOUND_STRING("Raises the base\n"
            "Sp. Def stat of one\n"
            "Pokémon."), COMPOUND_STRING("Sube la base de Def.\n" "Esp. de un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_DRINK,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_Zinc,
        .flingPower = 30,
        .iconPic = gItemIcon_Vitamin,
        .iconPalette = gItemIconPalette_Zinc,
    },

    [ITEM_CARBOS] =
    {
        .name = ES(ITEM_NAME("Carbos"), ITEM_NAME("Carburante")),
        .pluralName = ITEM_PLURAL_NAME("Carbos"),
        .price = (I_PRICE >= GEN_7) ? 10000 : 9800,
        .description = ES(COMPOUND_STRING("Raises the base\n"
            "Speed stat of one\n"
            "Pokémon."), COMPOUND_STRING("Sube la base de\n" "Velocidad de un\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_DRINK,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_Carbos,
        .flingPower = 30,
        .iconPic = gItemIcon_Vitamin,
        .iconPalette = gItemIconPalette_Carbos,
    },

    [ITEM_PP_UP] =
    {
        .name = ES(ITEM_NAME("PP Up"), ITEM_NAME("Más PP")),
    #if I_PRICE >= GEN_7
        .price = 10000,
    #elif I_PRICE >= GEN_2
        .price = 9800,
    #else
        .price = 1,
    #endif
        .description = ES(COMPOUND_STRING("Raises the maximum\n"
            "PP of a selected\n"
            "move."), COMPOUND_STRING("Sube los PP máximos\n" "de un movimiento.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_DRINK,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPUp,
        .effect = gItemEffect_PPUp,
        .flingPower = 30,
        .iconPic = gItemIcon_PPUp,
        .iconPalette = gItemIconPalette_PPUp,
    },

    [ITEM_PP_MAX] =
    {
        .name = ES(ITEM_NAME("PP Max"), ITEM_NAME("PP Máximos")),
        .pluralName = ITEM_PLURAL_NAME("PP Maxes"),
        .price = (I_PRICE >= GEN_7) ? 10000 : 9800,
        .description = ES(COMPOUND_STRING("Raises the PP of a\n"
            "move to its maximum\n"
            "points."), COMPOUND_STRING("Sube al máximo los\n" "PP de un movimiento.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_DRINK,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPUp,
        .effect = gItemEffect_PPMax,
        .flingPower = 30,
        .iconPic = gItemIcon_PPMax,
        .iconPalette = gItemIconPalette_PPMax,
    },

// EV Feathers

    [ITEM_HEALTH_FEATHER] =
    {
        .name = ES(ITEM_NAME("Health Feather"), ITEM_NAME("Pluma Vigor")),
        .price = (I_PRICE >= GEN_7) ? 300 : 3000,
        .description = ES(COMPOUND_STRING("Raises the base HP\n"
            "of one Pokémon."), COMPOUND_STRING("Sube un poco la base\n" "de PS de un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_FEATHER,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_HpFeather,
        .flingPower = 20,
        .iconPic = gItemIcon_EVFeather,
        .iconPalette = gItemIconPalette_HealthFeather,
    },

    [ITEM_MUSCLE_FEATHER] =
    {
        .name = ES(ITEM_NAME("Muscle Feather"), ITEM_NAME("Pluma Músculo")),
        .price = (I_PRICE >= GEN_7) ? 300 : 3000,
        .description = ES(COMPOUND_STRING("Raises the base\n"
            "Attack stat of one\n"
            "Pokémon."), COMPOUND_STRING("Sube un poco la base\n" "de Ataque.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_FEATHER,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_AtkFeather,
        .flingPower = 20,
        .iconPic = gItemIcon_EVFeather,
        .iconPalette = gItemIconPalette_MuscleFeather,
    },

    [ITEM_RESIST_FEATHER] =
    {
        .name = ES(ITEM_NAME("Resist Feather"), ITEM_NAME("Pluma Aguante")),
        .price = (I_PRICE >= GEN_7) ? 300 : 3000,
        .description = ES(COMPOUND_STRING("Raises the base\n"
            "Defense stat of\n"
            "one Pokémon."), COMPOUND_STRING("Sube un poco la base\n" "de Defensa.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_FEATHER,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_DefFeather,
        .flingPower = 20,
        .iconPic = gItemIcon_EVFeather,
        .iconPalette = gItemIconPalette_ResistFeather,
    },

    [ITEM_GENIUS_FEATHER] =
    {
        .name = ES(ITEM_NAME("Genius Feather"), ITEM_NAME("Pluma Intelecto")),
        .price = (I_PRICE >= GEN_7) ? 300 : 3000,
        .description = ES(COMPOUND_STRING("Raises the base\n"
            "Sp. Atk stat of one\n"
            "Pokémon."), COMPOUND_STRING("Sube un poco la base\n" "de At. Esp.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_FEATHER,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_SpatkFeather,
        .flingPower = 20,
        .iconPic = gItemIcon_EVFeather,
        .iconPalette = gItemIconPalette_GeniusFeather,
    },

    [ITEM_CLEVER_FEATHER] =
    {
        .name = ES(ITEM_NAME("Clever Feather"), ITEM_NAME("Pluma Mente")),
        .price = (I_PRICE >= GEN_7) ? 300 : 3000,
        .description = ES(COMPOUND_STRING("Raises the base\n"
            "Sp. Def stat of one\n"
            "Pokémon."), COMPOUND_STRING("Sube un poco la base\n" "de Def. Esp.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_FEATHER,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_SpdefFeather,
        .flingPower = 20,
        .iconPic = gItemIcon_EVFeather,
        .iconPalette = gItemIconPalette_CleverFeather,
    },

    [ITEM_SWIFT_FEATHER] =
    {
        .name = ES(ITEM_NAME("Swift Feather"), ITEM_NAME("Pluma Ímpetu")),
        .price = (I_PRICE >= GEN_7) ? 300 : 3000,
        .description = ES(COMPOUND_STRING("Raises the base\n"
            "Speed stat of one\n"
            "Pokémon."), COMPOUND_STRING("Sube un poco la base\n" "de Velocidad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_FEATHER,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_SpeedFeather,
        .flingPower = 20,
        .iconPic = gItemIcon_EVFeather,
        .iconPalette = gItemIconPalette_SwiftFeather,
    },

// Ability Modifiers

    [ITEM_ABILITY_CAPSULE] =
    {
        .name = ES(ITEM_NAME("Ability Capsule"), ITEM_NAME("Cáps. Habilidad")),
    #if I_PRICE >= GEN_9
        .price = 100000,
    #elif I_PRICE >= GEN_7
        .price = 10000,
    #else
        .price = 1000,
    #endif
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("A capsule that\n"
            "allows a Pokémon to\n"
            "switch Abilities."), COMPOUND_STRING("Cambia la habilidad\n" "de un Pokémon por la\n" "otra.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_AbilityCapsule,
        .iconPic = gItemIcon_AbilityCapsule,
        .iconPalette = gItemIconPalette_AbilityCapsule,
    },

    [ITEM_ABILITY_PATCH] =
    {
        .name = ES(ITEM_NAME("Ability Patch"), ITEM_NAME("Parche Habilidad")),
        .pluralName = ITEM_PLURAL_NAME("Ability Patches"),
        .price = (I_PRICE >= GEN_9) ? 250000 : 20,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Changes a regular\n"
            "Ability to a\n"
            "rarer Ability."), COMPOUND_STRING("Cambia la habilidad\n" "por la oculta.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_AbilityPatch,
        .iconPic = gItemIcon_AbilityPatch,
        .iconPalette = gItemIconPalette_AbilityPatch,
    },

// Mints

    [ITEM_LONELY_MINT] =
    {
        .name = ES(ITEM_NAME("Lonely Mint"), ITEM_NAME("Menta Huraña")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Attack and\n"
            "lowers Defense."), COMPOUND_STRING("Al olerla, sube\n" "Ataque y baja\n" "Defensa.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_LONELY,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_RedMint,
    },

    [ITEM_ADAMANT_MINT] =
    {
        .name = ES(ITEM_NAME("Adamant Mint"), ITEM_NAME("Menta Firme")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Attack and\n"
            "lowers Sp. Atk."), COMPOUND_STRING("Al olerla, sube\n" "Ataque y baja At.\n" "Esp.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_ADAMANT,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_RedMint,
    },

    [ITEM_NAUGHTY_MINT] =
    {
        .name = ES(ITEM_NAME("Naughty Mint"), ITEM_NAME("Menta Pícara")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Attack and\n"
            "lowers Sp. Def."), COMPOUND_STRING("Al olerla, sube\n" "Ataque y baja Def.\n" "Esp.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_NAUGHTY,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_RedMint,
    },

    [ITEM_BRAVE_MINT] =
    {
        .name = ES(ITEM_NAME("Brave Mint"), ITEM_NAME("Menta Audaz")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Attack and\n"
            "lowers Speed."), COMPOUND_STRING("Al olerla, sube\n" "Ataque y baja\n" "Velocidad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_BRAVE,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_RedMint,
    },

    [ITEM_BOLD_MINT] =
    {
        .name = ES(ITEM_NAME("Bold Mint"), ITEM_NAME("Menta Osada")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Defense and\n"
            "lowers Attack."), COMPOUND_STRING("Al olerla, sube\n" "Defensa y baja\n" "Ataque.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_BOLD,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_BlueMint,
    },

    [ITEM_IMPISH_MINT] =
    {
        .name = ES(ITEM_NAME("Impish Mint"), ITEM_NAME("Menta Agitada")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Defense and\n"
            "lowers Sp. Atk."), COMPOUND_STRING("Al olerla, sube\n" "Defensa y baja At.\n" "Esp.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_IMPISH,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_BlueMint,
    },

    [ITEM_LAX_MINT] =
    {
        .name = ES(ITEM_NAME("Lax Mint"), ITEM_NAME("Menta Floja")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Defense and\n"
            "lowers Sp. Def."), COMPOUND_STRING("Al olerla, sube\n" "Defensa y baja Def.\n" "Esp.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_LAX,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_BlueMint,
    },

    [ITEM_RELAXED_MINT] =
    {
        .name = ES(ITEM_NAME("Relaxed Mint"), ITEM_NAME("Menta Plácida")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Defense and\n"
            "lowers Speed."), COMPOUND_STRING("Al olerla, sube\n" "Defensa y baja\n" "Velocidad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_RELAXED,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_BlueMint,
    },

    [ITEM_MODEST_MINT] =
    {
        .name = ES(ITEM_NAME("Modest Mint"), ITEM_NAME("Menta Modesta")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Sp. Atk and\n"
            "lowers Attack."), COMPOUND_STRING("Al olerla, sube At.\n" "Esp. y baja Ataque.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_MODEST,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_LightBlueMint,
    },

    [ITEM_MILD_MINT] =
    {
        .name = ES(ITEM_NAME("Mild Mint"), ITEM_NAME("Menta Afable")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Sp. Atk and\n"
            "lowers Defense."), COMPOUND_STRING("Al olerla, sube At.\n" "Esp. y baja Defensa.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_MILD,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_LightBlueMint,
    },

    [ITEM_RASH_MINT] =
    {
        .name = ES(ITEM_NAME("Rash Mint"), ITEM_NAME("Menta Alocada")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Sp. Atk and\n"
            "lowers Sp. Def."), COMPOUND_STRING("Al olerla, sube At.\n" "Esp. y baja Def.\n" "Esp.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_RASH,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_LightBlueMint,
    },

    [ITEM_QUIET_MINT] =
    {
        .name = ES(ITEM_NAME("Quiet Mint"), ITEM_NAME("Menta Mansa")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Sp. Atk and\n"
            "lowers Speed."), COMPOUND_STRING("Al olerla, sube At.\n" "Esp. y baja\n" "Velocidad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_QUIET,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_LightBlueMint,
    },

    [ITEM_CALM_MINT] =
    {
        .name = ES(ITEM_NAME("Calm Mint"), ITEM_NAME("Menta Serena")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Sp. Def and\n"
            "lowers Attack."), COMPOUND_STRING("Al olerla, sube Def.\n" "Esp. y baja Ataque.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_CALM,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_PinkMint,
    },

    [ITEM_GENTLE_MINT] =
    {
        .name = ES(ITEM_NAME("Gentle Mint"), ITEM_NAME("Menta Amable")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Sp. Def and\n"
            "lowers Defense."), COMPOUND_STRING("Al olerla, sube Def.\n" "Esp. y baja Defensa.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_GENTLE,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_PinkMint,
    },

    [ITEM_CAREFUL_MINT] =
    {
        .name = ES(ITEM_NAME("Careful Mint"), ITEM_NAME("Menta Cauta")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Sp. Def and\n"
            "lowers Sp. Atk."), COMPOUND_STRING("Al olerla, sube Def.\n" "Esp. y baja At. Esp.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_CAREFUL,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_PinkMint,
    },

    [ITEM_SASSY_MINT] =
    {
        .name = ES(ITEM_NAME("Sassy Mint"), ITEM_NAME("Menta Grosera")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Sp. Def and\n"
            "lowers Speed."), COMPOUND_STRING("Al olerla, sube Def.\n" "Esp. y baja\n" "Velocidad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_SASSY,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_PinkMint,
    },

    [ITEM_TIMID_MINT] =
    {
        .name = ES(ITEM_NAME("Timid Mint"), ITEM_NAME("Menta Miedosa")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Speed and\n"
            "lowers Attack."), COMPOUND_STRING("Al olerla, sube\n" "Velocidad y baja\n" "Ataque.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_TIMID,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_GreenMint,
    },

    [ITEM_HASTY_MINT] =
    {
        .name = ES(ITEM_NAME("Hasty Mint"), ITEM_NAME("Menta Activa")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Speed and\n"
            "lowers Defense."), COMPOUND_STRING("Al olerla, sube\n" "Velocidad y baja\n" "Defensa.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_HASTY,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_GreenMint,
    },

    [ITEM_JOLLY_MINT] =
    {
        .name = ES(ITEM_NAME("Jolly Mint"), ITEM_NAME("Menta Alegre")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Speed and\n"
            "lowers Sp. Atk."), COMPOUND_STRING("Al olerla, sube\n" "Velocidad y baja At.\n" "Esp.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_JOLLY,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_GreenMint,
    },

    [ITEM_NAIVE_MINT] =
    {
        .name = ES(ITEM_NAME("Naive Mint"), ITEM_NAME("Menta Ingenua")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "raises Speed and\n"
            "lowers Sp. Def."), COMPOUND_STRING("Al olerla, sube\n" "Velocidad y baja\n" "Def. Esp.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_NAIVE,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_GreenMint,
    },

    [ITEM_SERIOUS_MINT] =
    {
        .name = ES(ITEM_NAME("Serious Mint"), ITEM_NAME("Menta Seria")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = ES(COMPOUND_STRING("When smelled, it\n"
            "makes a Pokémon's\n"
            "stats grow equally."), COMPOUND_STRING("Al olerla, las\n" "características\n" "crecen por igual.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_SERIOUS,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_YellowMint,
    },

// Candies

    [ITEM_RARE_CANDY] =
    {
        .name = ES(ITEM_NAME("Rare Candy"), ITEM_NAME("Caramelo Raro")),
        .pluralName = ITEM_PLURAL_NAME("Rare Candies"),
        .price = 1, // Dualocke: Caramelos Raros a 1 ₽ (no pasan del level cap)
        .description = ES(COMPOUND_STRING("Raises the level\n"
            "of a Pokémon by\n"
            "one."), COMPOUND_STRING("Caramelo energético\n" "que sube a un\n" "Pokémon de nivel.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_LEVEL_UP_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .effect = gItemEffect_RareCandy,
        .flingPower = 30,
        .iconPic = gItemIcon_RareCandy,
        .iconPalette = gItemIconPalette_RareCandy,
    },

    [ITEM_EXP_CANDY_XS] =
    {
        .name = ES(ITEM_NAME("Exp. Candy XS"), ITEM_NAME("Caramelo Exp. XS")),
        .pluralName = ITEM_PLURAL_NAME("Exp. Candies XS"),
        .price = 20,
        .holdEffectParam = EXP_100,
        .description = ES(COMPOUND_STRING("Grants a very small\n"
            "amount of Exp. to\n"
            "a single Pokémon."), COMPOUND_STRING("Da muy poca\n" "experiencia a un\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_LEVEL_UP_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .effect = gItemEffect_RareCandy,
        .flingPower = 30,
        .iconPic = gItemIcon_ExpCandyXS,
        .iconPalette = gItemIconPalette_ExpCandies,
    },

    [ITEM_EXP_CANDY_S] =
    {
        .name = ES(ITEM_NAME("Exp. Candy S"), ITEM_NAME("Caramelo Exp. S")),
        .pluralName = ITEM_PLURAL_NAME("Exp. Candies S"),
        .price = 240,
        .holdEffectParam = EXP_800,
        .description = ES(COMPOUND_STRING("Grants a small\n"
            "amount of Exp. to\n"
            "a single Pokémon."), COMPOUND_STRING("Da poca experiencia\n" "a un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_LEVEL_UP_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .effect = gItemEffect_RareCandy,
        .flingPower = 30,
        .iconPic = gItemIcon_ExpCandyS,
        .iconPalette = gItemIconPalette_ExpCandies,
    },

    [ITEM_EXP_CANDY_M] =
    {
        .name = ES(ITEM_NAME("Exp. Candy M"), ITEM_NAME("Caramelo Exp. M")),
        .pluralName = ITEM_PLURAL_NAME("Exp. Candies M"),
        .price = 1000,
        .holdEffectParam = EXP_3000,
        .description = ES(COMPOUND_STRING("Grants a moderate\n"
            "amount of Exp. to\n"
            "a single Pokémon."), COMPOUND_STRING("Da algo de\n" "experiencia a un\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_LEVEL_UP_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .effect = gItemEffect_RareCandy,
        .flingPower = 30,
        .iconPic = gItemIcon_ExpCandyM,
        .iconPalette = gItemIconPalette_ExpCandies,
    },

    [ITEM_EXP_CANDY_L] =
    {
        .name = ES(ITEM_NAME("Exp. Candy L"), ITEM_NAME("Caramelo Exp. L")),
        .pluralName = ITEM_PLURAL_NAME("Exp. Candies L"),
        .price = 3000,
        .holdEffectParam = EXP_10000,
        .description = ES(COMPOUND_STRING("Grants a large\n"
            "amount of Exp. to\n"
            "a single Pokémon."), COMPOUND_STRING("Da mucha experiencia\n" "a un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_LEVEL_UP_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .effect = gItemEffect_RareCandy,
        .flingPower = 30,
        .iconPic = gItemIcon_ExpCandyL,
        .iconPalette = gItemIconPalette_ExpCandies,
    },

    [ITEM_EXP_CANDY_XL] =
    {
        .name = ES(ITEM_NAME("Exp. Candy XL"), ITEM_NAME("Caramelo Exp. XL")),
        .pluralName = ITEM_PLURAL_NAME("Exp. Candies XL"),
        .price = 10000,
        .holdEffectParam = EXP_30000,
        .description = ES(COMPOUND_STRING("Grants a very large\n"
            "amount of Exp. to\n"
            "a single Pokémon."), COMPOUND_STRING("Da muchísima\n" "experiencia a un\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_LEVEL_UP_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .effect = gItemEffect_RareCandy,
        .flingPower = 30,
        .iconPic = gItemIcon_ExpCandyXL,
        .iconPalette = gItemIconPalette_ExpCandies,
    },

    [ITEM_DYNAMAX_CANDY] =
    {
        .name = ES(ITEM_NAME("Dynamax Candy"), ITEM_NAME("Caramelo Dinamax")),
        .pluralName = ITEM_PLURAL_NAME("Dynamax Candies"),
        .price = 0,
        .description = ES(COMPOUND_STRING("Raises the Dynamax\n"
            "Level of a single\n"
            "Pokémon by one."), COMPOUND_STRING("Sube 1 el nivel\n" "Dinamax de un\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_LEVEL_UP_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_DynamaxCandy,
        .flingPower = 30,
        .iconPic = gItemIcon_DynamaxCandy,
        .iconPalette = gItemIconPalette_DynamaxCandy,
    },

// Medicinal Flutes

    [ITEM_BLUE_FLUTE] =
    {
        .name = ES(ITEM_NAME("Blue Flute"), ITEM_NAME("Flauta Azul")),
        .price = (I_PRICE >= GEN_7) ? 20 : 100,
        .description = ES(COMPOUND_STRING("A glass flute that\n"
            "awakens sleeping\n"
            "Pokémon."), COMPOUND_STRING("Una flauta de\n" "juguete de cristal\n" "azul.")),
        .notConsumed = TRUE,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FLUTE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_Awakening,
        .flingPower = 30,
        .iconPic = gItemIcon_Flute,
        .iconPalette = gItemIconPalette_BlueFlute,
    },

    [ITEM_YELLOW_FLUTE] =
    {
        .name = ES(ITEM_NAME("Yellow Flute"), ITEM_NAME("Flauta Amarilla")),
        .price = (I_PRICE >= GEN_7) ? 20 : 300,
        .description = ES(COMPOUND_STRING("A glass flute that\n"
            "snaps Pokémon\n"
            "out of confusion."), COMPOUND_STRING("Una flauta de\n" "juguete de cristal\n" "amarillo.")),
        .notConsumed = TRUE,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FLUTE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_YellowFlute,
        .flingPower = 30,
        .iconPic = gItemIcon_Flute,
        .iconPalette = gItemIconPalette_YellowFlute,
    },

    [ITEM_RED_FLUTE] =
    {
        .name = ES(ITEM_NAME("Red Flute"), ITEM_NAME("Flauta Roja")),
        .price = (I_PRICE >= GEN_7) ? 20 : 200,
        .description = ES(COMPOUND_STRING("A glass flute that\n"
            "snaps Pokémon\n"
            "out of attraction."), COMPOUND_STRING("Una flauta de\n" "juguete de cristal\n" "rojo.")),
        .notConsumed = TRUE,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FLUTE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_RedFlute,
        .flingPower = 30,
        .iconPic = gItemIcon_Flute,
        .iconPalette = gItemIconPalette_RedFlute,
    },

// Encounter-modifying Flutes

    [ITEM_BLACK_FLUTE] =
    {
        .name = ES(ITEM_NAME("Black Flute"), ITEM_NAME("Flauta Negra")),
        .price = (I_PRICE >= GEN_7) ? 20 : 400,
        .holdEffectParam = 50,
        .description = ES(COMPOUND_STRING("A glass flute that\n"
            "keeps away wild\n"
            "Pokémon."), COMPOUND_STRING("Una flauta de\n" "juguete de cristal\n" "negro.")),
        .notConsumed = TRUE,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FLUTE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_BlackWhiteFlute,
        .flingPower = 30,
        .iconPic = gItemIcon_Flute,
        .iconPalette = gItemIconPalette_BlackFlute,
    },

    [ITEM_WHITE_FLUTE] =
    {
        .name = ES(ITEM_NAME("White Flute"), ITEM_NAME("Flauta Blanca")),
        .price = (I_PRICE >= GEN_7) ? 20 : 500,
        .holdEffectParam = 150,
        .description = ES(COMPOUND_STRING("A glass flute that\n"
            "lures wild Pokémon."), COMPOUND_STRING("Una flauta de\n" "juguete de cristal\n" "blanco.")),
        .notConsumed = TRUE,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FLUTE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_BlackWhiteFlute,
        .flingPower = 30,
        .iconPic = gItemIcon_Flute,
        .iconPalette = gItemIconPalette_WhiteFlute,
    },

// Encounter Modifiers

    [ITEM_REPEL] =
    {
        .name = ES(ITEM_NAME("Repel"), ITEM_NAME("Repelente")),
        .price = (I_PRICE >= GEN_7) ? 400 : 350,
        .holdEffectParam = 100,
        .description = ES(COMPOUND_STRING("Repels weak wild\n"
            "Pokémon for 100\n"
            "steps."), COMPOUND_STRING("Ahuyenta a Pokémon\n" "débiles durante 100\n" "pasos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Repel,
        .flingPower = 30,
        .iconPic = gItemIcon_Repel,
        .iconPalette = gItemIconPalette_Repel,
    },

    [ITEM_SUPER_REPEL] =
    {
        .name = ES(ITEM_NAME("Super Repel"), ITEM_NAME("Superrepelente")),
        .price = (I_PRICE >= GEN_7) ? 700 : 500,
        .holdEffectParam = 200,
        .description = ES(COMPOUND_STRING("Repels weak wild\n"
            "Pokémon for 200\n"
            "steps."), COMPOUND_STRING("Ahuyenta a Pokémon\n" "débiles durante 200\n" "pasos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Repel,
        .flingPower = 30,
        .iconPic = gItemIcon_Repel,
        .iconPalette = gItemIconPalette_SuperRepel,
    },

    [ITEM_MAX_REPEL] =
    {
        .name = ES(ITEM_NAME("Max Repel"), ITEM_NAME("Repelente Máximo")),
        .price = (I_PRICE >= GEN_7) ? 900 : 700,
        .holdEffectParam = 250,
        .description = ES(COMPOUND_STRING("Repels weak wild\n"
            "Pokémon for 250\n"
            "steps."), COMPOUND_STRING("Ahuyenta a Pokémon\n" "débiles durante 250\n" "pasos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Repel,
        .flingPower = 30,
        .iconPic = gItemIcon_Repel,
        .iconPalette = gItemIconPalette_MaxRepel,
    },

    [ITEM_LURE] =
    {
        .name = ES(ITEM_NAME("Lure"), ITEM_NAME("Colonia")),
        .price = 400,
        .holdEffectParam = 100,
        .description = ES(COMPOUND_STRING("Makes Pokémon more\n"
            "likely to appear\n"
            "for 100 steps."), COMPOUND_STRING("Atrae más Pokémon\n" "durante 100 pasos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Lure,
        .secondaryId = 0,
        .flingPower = 30,
        .iconPic = gItemIcon_Lure,
        .iconPalette = gItemIconPalette_Lure,
    },

    [ITEM_SUPER_LURE] =
    {
        .name = ES(ITEM_NAME("Super Lure"), ITEM_NAME("Supercolonia")),
        .price = 700,
        .holdEffectParam = 200,
        .description = ES(COMPOUND_STRING("Makes Pokémon more\n"
            "likely to appear\n"
            "for 200 steps."), COMPOUND_STRING("Atrae más Pokémon\n" "durante 200 pasos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Lure,
        .secondaryId = 0,
        .flingPower = 30,
        .iconPic = gItemIcon_Lure,
        .iconPalette = gItemIconPalette_SuperLure,
    },

    [ITEM_MAX_LURE] =
    {
        .name = ES(ITEM_NAME("Max Lure"), ITEM_NAME("Colonia Máxima")),
        .price = 900,
        .holdEffectParam = 250,
        .description = ES(COMPOUND_STRING("Makes Pokémon more\n"
            "likely to appear\n"
            "for 250 steps."), COMPOUND_STRING("Atrae más Pokémon\n" "durante 250 pasos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Lure,
        .secondaryId = 0,
        .flingPower = 30,
        .iconPic = gItemIcon_Lure,
        .iconPalette = gItemIconPalette_MaxLure,
    },

    [ITEM_ESCAPE_ROPE] =
    {
        .name = ES(ITEM_NAME("Escape Rope"), ITEM_NAME("Cuerda Huida")),
        .description = ES(COMPOUND_STRING("Use to escape\n"
            "instantly from a\n"
            "cave or a dungeon."), COMPOUND_STRING("Para salir al\n" "instante de una\n" "cueva o mazmorra.")),
    #if I_KEY_ESCAPE_ROPE >= GEN_8
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
    #else
        .price = (I_PRICE >= GEN_7) ? 1000 : 550,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
    #endif
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_EscapeRope,
        .flingPower = 30,
        .iconPic = gItemIcon_EscapeRope,
        .iconPalette = gItemIconPalette_EscapeRope,
    },

// X items

    [ITEM_X_ATTACK] =
    {
        .name = ES(ITEM_NAME("X Attack"), ITEM_NAME("Ataque X")),
        .price = (I_PRICE >= GEN_7) ? 1000 : 500,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises the\n"
            "Attack stat\n"
            "during one battle."),
        #else
            "Raises the stat\n"
            "Attack during one\n"
            "battle."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_X_ITEM,
        .type = B_X_ITEMS_CROSSUSE ? ITEM_USE_BATTLER : ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_INCREASE_STAT,
        .effect = gItemEffect_XAttack,
        .flingPower = 30,
        .iconPic = gItemIcon_BattleStatItem,
        .iconPalette = gItemIconPalette_XAttack,
    },

    [ITEM_X_DEFENSE] =
    {
        .name = ES(ITEM_NAME("X Defense"), ITEM_NAME("Defensa X")),
        .price = (I_PRICE >= GEN_7) ? 2000 : 550,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises the\n"
            "Defense stat\n"
            "during one battle."),
        #else
            "Raises the stat\n"
            "Defense during one\n"
            "battle."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_X_ITEM,
        .type = B_X_ITEMS_CROSSUSE ? ITEM_USE_BATTLER : ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_INCREASE_STAT,
        .effect = gItemEffect_XDefense,
        .flingPower = 30,
        .iconPic = gItemIcon_BattleStatItem,
        .iconPalette = gItemIconPalette_XDefend,
    },

    [ITEM_X_SP_ATK] =
    {
        .name = ES(ITEM_NAME("X Sp. Atk"), ITEM_NAME("At. Especial X")),
        .price = (I_PRICE >= GEN_7) ? 1000 : 350,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises the\n"
            "Sp. Atk stat\n"
            "during one battle."),
        #else
            "Raises the stat\n"
            "Sp. Atk during one\n"
            "battle."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_X_ITEM,
        .type = B_X_ITEMS_CROSSUSE ? ITEM_USE_BATTLER : ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_INCREASE_STAT,
        .effect = gItemEffect_XSpecialAttack,
        .flingPower = 30,
        .iconPic = gItemIcon_BattleStatItem,
        .iconPalette = gItemIconPalette_XSpecial,
    },

    [ITEM_X_SP_DEF] =
    {
        .name = ES(ITEM_NAME("X Sp. Def"), ITEM_NAME("Def. Especial X")),
        .price = (I_PRICE >= GEN_7) ? 2000 : 350,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises the\n"
            "Sp. Def stat\n"
            "during one battle."),
        #else
            "Raises the stat\n"
            "Sp. Def during one\n"
            "battle."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_X_ITEM,
        .type = B_X_ITEMS_CROSSUSE ? ITEM_USE_BATTLER : ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_INCREASE_STAT,
        .effect = gItemEffect_XSpecialDefense,
        .flingPower = 30,
        .iconPic = gItemIcon_BattleStatItem,
        .iconPalette = gItemIconPalette_XSpecialDefense,
    },

    [ITEM_X_SPEED] =
    {
        .name = ES(ITEM_NAME("X Speed"), ITEM_NAME("Velocidad X")),
        .price = (I_PRICE >= GEN_7) ? 1000 : 350,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises the\n"
            "Speed stat\n"
            "during one battle."),
        #else
            "Raises the stat\n"
            "Speed during one\n"
            "battle."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_X_ITEM,
        .type = B_X_ITEMS_CROSSUSE ? ITEM_USE_BATTLER : ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_INCREASE_STAT,
        .effect = gItemEffect_XSpeed,
        .flingPower = 30,
        .iconPic = gItemIcon_BattleStatItem,
        .iconPalette = gItemIconPalette_XSpeed,
    },

    [ITEM_X_ACCURACY] =
    {
        .name = ES(ITEM_NAME("X Accuracy"), ITEM_NAME("Precisión X")),
        .pluralName = ITEM_PLURAL_NAME("X Accuracies"),
        .price = (I_PRICE >= GEN_7) ? 1000 : 950,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises\n"
            "accuracy during\n"
            "one battle."),
        #else
            "Raises accuracy\n"
            "of moves\n"
            "during one battle."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_X_ITEM,
        .type = B_X_ITEMS_CROSSUSE ? ITEM_USE_BATTLER : ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_INCREASE_STAT,
        .effect = gItemEffect_XAccuracy,
        .flingPower = 30,
        .iconPic = gItemIcon_BattleStatItem,
        .iconPalette = gItemIconPalette_XAccuracy,
    },

    [ITEM_DIRE_HIT] =
    {
        .name = ES(ITEM_NAME("Dire Hit"), ITEM_NAME("Crítico X")),
        .price = (I_PRICE >= GEN_7) ? 1000 : 650,
        .description = ES(COMPOUND_STRING("Raises the\n"
            "critical-hit ratio\n"
            "during one battle."), COMPOUND_STRING("Sube el índice de\n" "golpe crítico en un\n" "combate.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_X_ITEM,
        .type = B_X_ITEMS_CROSSUSE ? ITEM_USE_BATTLER : ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_SET_FOCUS_ENERGY,
        .effect = gItemEffect_DireHit,
        .flingPower = 30,
        .iconPic = gItemIcon_BattleStatItem,
        .iconPalette = gItemIconPalette_DireHit,
    },

    [ITEM_GUARD_SPEC] =
    {
        .name = ES(ITEM_NAME("Guard Spec."), ITEM_NAME("Protección X")),
        .pluralName = ITEM_PLURAL_NAME("Guard Specs."),
        .price = (I_PRICE >= GEN_7) ? 1500 : 700,
        .description = ES(COMPOUND_STRING("Prevents stat\n"
            "lowering when\n"
            "used in battle."), COMPOUND_STRING("Evita que bajen las\n" "caract. en un\n" "combate.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_X_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_SET_MIST,
        .effect = gItemEffect_GuardSpec,
        .flingPower = 30,
        .iconPic = gItemIcon_BattleStatItem,
        .iconPalette = gItemIconPalette_GuardSpec,
    },

    [ITEM_POKE_DOLL] =
    {
        .name = ES(ITEM_NAME("Poké Doll"), ITEM_NAME("Poké Muñeco")),
    #if I_PRICE >= GEN_8
        .price = 300,
    #elif I_PRICE == GEN_7
        .price = 100,
    #else
        .price = 1000,
    #endif
        .description = ES(COMPOUND_STRING("Use to flee from\n"
            "any battle with\n"
            "a wild Pokémon."), COMPOUND_STRING("Permite huir de un\n" "combate contra un\n" "salvaje.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_BATTLE_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_ESCAPE,
        .flingPower = 30,
        .iconPic = gItemIcon_PokeDoll,
        .iconPalette = gItemIconPalette_PokeDoll,
    },

    [ITEM_FLUFFY_TAIL] =
    {
        .name = ES(ITEM_NAME("Fluffy Tail"), ITEM_NAME("Cola Skitty")),
        .price = (I_PRICE >= GEN_7) ? 100 : 1000,
        .description = ES(COMPOUND_STRING("Use to flee from\n"
            "any battle with\n"
            "a wild Pokémon."), COMPOUND_STRING("Permite huir de un\n" "combate contra un\n" "salvaje.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_BATTLE_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_ESCAPE,
        .flingPower = 30,
        .iconPic = gItemIcon_FluffyTail,
        .iconPalette = gItemIconPalette_FluffyTail,
    },

    [ITEM_POKE_TOY] =
    {
        .name = ES(ITEM_NAME("Poké Toy"), ITEM_NAME("Pokéseñuelo")),
        .price = (I_PRICE >= GEN_7) ? 100 : 1000,
        .description = ES(COMPOUND_STRING("Use to flee from\n"
            "any battle with\n"
            "a wild Pokémon."), COMPOUND_STRING("Permite huir de un\n" "combate contra un\n" "salvaje.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_BATTLE_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_ESCAPE,
        .flingPower = 30,
        .iconPic = gItemIcon_PokeToy,
        .iconPalette = gItemIconPalette_PokeToy,
    },

    [ITEM_MAX_MUSHROOMS] =
    {
        .name = ES(ITEM_NAME("Max Mushrooms"), ITEM_NAME("Maxiseta")),
        .pluralName = ITEM_PLURAL_NAME("Max Mushrooms"),
        .price = 8000,
        .description = ES(COMPOUND_STRING("Mushrooms that\n"
            "raise all stats\n"
            "during one battle."), COMPOUND_STRING("Setas que suben\n" "todas las caract. en\n" "un combate.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_BATTLE_ITEM,
        .type = B_X_ITEMS_CROSSUSE ? ITEM_USE_BATTLER : ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_INCREASE_ALL_STATS,
        .flingPower = 30,
        .iconPic = gItemIcon_MaxMushrooms,
        .iconPalette = gItemIconPalette_MaxMushrooms,
    },

// Treasures

    [ITEM_BOTTLE_CAP] =
    {
        .name = ES(ITEM_NAME("Bottle Cap"), ITEM_NAME("Chapa Plateada")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 5000,
        .description = ES(COMPOUND_STRING("A beautiful bottle\n"
            "cap that gives off\n"
            "a silver gleam."), COMPOUND_STRING("Una chapa preciosa\n" "de brillo plateado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BottleCap,
        .iconPalette = gItemIconPalette_BottleCap,
    },

    [ITEM_GOLD_BOTTLE_CAP] =
    {
        .name = ES(ITEM_NAME("Gold Bottle Cap"), ITEM_NAME("Chapa Dorada")),
        .price = (I_PRICE >= GEN_9) ? 60000 : 10000,
        .description = ES(COMPOUND_STRING("A beautiful bottle\n"
            "cap that gives off\n"
            "a golden gleam."), COMPOUND_STRING("Una chapa preciosa\n" "de brillo dorado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BottleCap,
        .iconPalette = gItemIconPalette_GoldBottleCap,
    },

    [ITEM_NUGGET] =
    {
        .name = ES(ITEM_NAME("Nugget"), ITEM_NAME("Pepita")),
        .price = 10000 * TREASURE_FACTOR,
        .description = ES(COMPOUND_STRING("A nugget of pure\n"
            "gold. Can be sold at\n"
            "a high price."), COMPOUND_STRING("Una pepita de oro\n" "puro. Se vende cara.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Nugget,
        .iconPalette = gItemIconPalette_Nugget,
    },

    [ITEM_BIG_NUGGET] =
    {
        .name = ES(ITEM_NAME("Big Nugget"), ITEM_NAME("Maxipepita")),
    #if I_PRICE >= GEN_7
        .price = 40000 * TREASURE_FACTOR,
    #elif I_PRICE == GEN_6
        .price = 20000,
    #else
        .price = 0,
    #endif
        .description = ES(COMPOUND_STRING("A big nugget of\n"
            "gold. Can be sold at\n"
            "a high price."), COMPOUND_STRING("Una pepita de oro\n" "grande. Se vende\n" "cara.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = B_UPDATED_MOVE_DATA >= GEN_8 ? 130 : 80,
        .iconPic = gItemIcon_BigNugget,
        .iconPalette = gItemIconPalette_BigNugget,
    },

    [ITEM_TINY_MUSHROOM] =
    {
        .name = ES(ITEM_NAME("Tiny Mushroom"), ITEM_NAME("Miniseta")),
        .price = 500 * TREASURE_FACTOR,
        .description = ES(COMPOUND_STRING("A plain mushroom\n"
            "that would sell\n"
            "at a cheap price."), COMPOUND_STRING("Una seta normal. Se\n" "vende barata.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_TinyMushroom,
        .iconPalette = gItemIconPalette_Mushroom,
    },

    [ITEM_BIG_MUSHROOM] =
    {
        .name = ES(ITEM_NAME("Big Mushroom"), ITEM_NAME("Seta Grande")),
        .price = 5000 * TREASURE_FACTOR,
        .description = ES(COMPOUND_STRING("A rare mushroom\n"
            "that would sell at a\n"
            "high price."), COMPOUND_STRING("Una seta rara. Se\n" "vende cara.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BigMushroom,
        .iconPalette = gItemIconPalette_Mushroom,
    },

    [ITEM_BALM_MUSHROOM] =
    {
        .name = ES(ITEM_NAME("Balm Mushroom"), ITEM_NAME("Seta Aroma")),
    #if I_PRICE >= GEN_7
        .price = 15000 * TREASURE_FACTOR,
    #elif I_PRICE == GEN_6
        .price = 12500,
    #else
        .price = 0,
    #endif
        .description = ES(COMPOUND_STRING("Gives off a nice\n"
            "fragrance. It would\n"
            "sell at a high price."), COMPOUND_STRING("Huele muy bien. Se\n" "vende cara.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BalmMushroom,
        .iconPalette = gItemIconPalette_BalmMushroom,
    },

    [ITEM_PEARL] =
    {
        .name = ES(ITEM_NAME("Pearl"), ITEM_NAME("Perla")),
        .price = (I_PRICE >= GEN_7) ? 2000 * TREASURE_FACTOR: 1400,
        .description = ES(COMPOUND_STRING("A pretty pearl\n"
            "that would sell at a\n"
            "cheap price."), COMPOUND_STRING("Una perla bonita. Se\n" "vende barata.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Pearl,
        .iconPalette = gItemIconPalette_Pearl,
    },

    [ITEM_BIG_PEARL] =
    {
        .name = ES(ITEM_NAME("Big Pearl"), ITEM_NAME("Perla Grande")),
        .price = (I_PRICE >= GEN_7) ? 8000 * TREASURE_FACTOR: 7500,
        .description = ES(COMPOUND_STRING("A lovely large pearl\n"
            "that would sell at a\n"
            "high price."), COMPOUND_STRING("Una perla grande. Se\n" "vende cara.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BigPearl,
        .iconPalette = gItemIconPalette_Pearl,
    },

    [ITEM_PEARL_STRING] =
    {
        .name = ES(ITEM_NAME("Pearl String"), ITEM_NAME("Sarta Perlas")),
    #if I_PRICE >= GEN_8
        .price = 20000 * TREASURE_FACTOR,
    #elif I_PRICE == GEN_7
        .price = 30000,
    #elif I_PRICE == GEN_6
        .price = 15000,
    #else
        .price = 0,
    #endif
        .description = ES(COMPOUND_STRING("Very large pearls\n"
            "that would sell at a\n"
            "high price."), COMPOUND_STRING("Perlas muy grandes.\n" "Se venden caras.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_PearlString,
        .iconPalette = gItemIconPalette_PearlString,
    },

    [ITEM_STARDUST] =
    {
        .name = ES(ITEM_NAME("Stardust"), ITEM_NAME("Polvo Estelar")),
        .price = (I_PRICE >= GEN_7) ? 3000 * TREASURE_FACTOR: 2000,
        .description = ES(COMPOUND_STRING("Beautiful red sand.\n"
            "Can be sold at a\n"
            "high price."), COMPOUND_STRING("Una arena roja\n" "preciosa. Se vende\n" "cara.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Sand,
        .iconPalette = gItemIconPalette_Star,
    },

    [ITEM_STAR_PIECE] =
    {
        .name = ES(ITEM_NAME("Star Piece"), ITEM_NAME("Trozo Estrella")),
        .price = (I_PRICE >= GEN_7) ? 12000 * TREASURE_FACTOR: 9800,
        .description = ES(COMPOUND_STRING("A red gem shard.\n"
            "It would sell for a\n"
            "very high price."), COMPOUND_STRING("Un trozo de gema\n" "roja. Se vende muy\n" "cara.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_StarPiece,
        .iconPalette = gItemIconPalette_Star,
    },

    [ITEM_COMET_SHARD] =
    {
        .name = ES(ITEM_NAME("Comet Shard"), ITEM_NAME("Fragmento Cometa")),
    #if I_PRICE >= GEN_8
        .price = 25000 * TREASURE_FACTOR,
    #elif I_PRICE == GEN_7
        .price = 60000,
    #elif I_PRICE == GEN_6
        .price = 30000,
    #else
        .price = 0,
    #endif
        .description = ES(COMPOUND_STRING("A fallen shard of\n"
            "a comet. It would\n"
            "sell at a high price."), COMPOUND_STRING("Un trozo de cometa.\n" "Se vende cara.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_StarPiece,
        .iconPalette = gItemIconPalette_CometShard,
    },

    [ITEM_SHOAL_SALT] =
    {
        .name = ES(ITEM_NAME("Shoal Salt"), ITEM_NAME("Sal Cardumen")),
        .price = 20,
        .description = ES(COMPOUND_STRING("Salt obtained from\n"
            "deep inside the\n"
            "Shoal Cave."), COMPOUND_STRING("Una sal muy fina que\n" "se encuentra en la\n" "Cueva Cardumen.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Powder,
        .iconPalette = gItemIconPalette_ShoalSalt,
    },

    [ITEM_SHOAL_SHELL] =
    {
        .name = ES(ITEM_NAME("Shoal Shell"), ITEM_NAME("Concha Cardumen")),
        .price = 20,
        .description = ES(COMPOUND_STRING("A seashell found\n"
            "deep inside the\n"
            "Shoal Cave."), COMPOUND_STRING("Concha que se\n" "encuentra en la\n" "Cueva Cardumen.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_ShoalShell,
        .iconPalette = gItemIconPalette_Shell,
    },

    [ITEM_RED_SHARD] =
    {
        .name = ES(ITEM_NAME("Red Shard"), ITEM_NAME("Parte Roja")),
        .price = (I_PRICE >= GEN_7) ? 1000 : 200,
        .description = ES(COMPOUND_STRING("A shard from an\n"
            "ancient item. Can\n"
            "be sold cheaply."), COMPOUND_STRING("Un trozo de un\n" "objeto antiguo. Se\n" "vende barato.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Shard,
        .iconPalette = gItemIconPalette_RedShard,
    },

    [ITEM_BLUE_SHARD] =
    {
        .name = ES(ITEM_NAME("Blue Shard"), ITEM_NAME("Parte Azul")),
        .price = (I_PRICE >= GEN_7) ? 1000 : 200,
        .description = ES(COMPOUND_STRING("A shard from an\n"
            "ancient item. Can\n"
            "be sold cheaply."), COMPOUND_STRING("Un trozo de un\n" "objeto antiguo. Se\n" "vende barato.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Shard,
        .iconPalette = gItemIconPalette_BlueShard,
    },

    [ITEM_YELLOW_SHARD] =
    {
        .name = ES(ITEM_NAME("Yellow Shard"), ITEM_NAME("Parte Amarilla")),
        .price = (I_PRICE >= GEN_7) ? 1000 : 200,
        .description = ES(COMPOUND_STRING("A shard from an\n"
            "ancient item. Can\n"
            "be sold cheaply."), COMPOUND_STRING("Un trozo de un\n" "objeto antiguo. Se\n" "vende barato.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Shard,
        .iconPalette = gItemIconPalette_YellowShard,
    },

    [ITEM_GREEN_SHARD] =
    {
        .name = ES(ITEM_NAME("Green Shard"), ITEM_NAME("Parte Verde")),
        .price = (I_PRICE >= GEN_7) ? 1000 : 200,
        .description = ES(COMPOUND_STRING("A shard from an\n"
            "ancient item. Can\n"
            "be sold cheaply."), COMPOUND_STRING("Un trozo de un\n" "objeto antiguo. Se\n" "vende barato.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Shard,
        .iconPalette = gItemIconPalette_GreenShard,
    },

    [ITEM_HEART_SCALE] =
    {
        .name = ES(ITEM_NAME("Heart Scale"), ITEM_NAME("Escama Corazón")),
        .price = 100,
        .description = ES(COMPOUND_STRING("A lovely scale.\n"
            "It is coveted by\n"
            "collectors."), COMPOUND_STRING("Una escama preciosa.\n" "Los coleccionistas\n" "la adoran.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_HeartScale,
        .iconPalette = gItemIconPalette_HeartScale,
    },

    [ITEM_HONEY] =
    {
        .name = ES(ITEM_NAME("Honey"), ITEM_NAME("Miel")),
        .pluralName = ITEM_PLURAL_NAME("Honey"),
    #if I_PRICE >= GEN_8
        .price = 900,
    #elif I_PRICE == GEN_7
        .price = 300,
    #else
        .price = 100,
    #endif
        .description = ES(COMPOUND_STRING("A sweet honey that\n"
            "attracts wild\n"
            "Pokémon when used."), COMPOUND_STRING("Miel dulce que atrae\n" "a Pokémon salvajes.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Honey,
        .flingPower = 30,
        .iconPic = gItemIcon_Honey,
        .iconPalette = gItemIconPalette_Honey,
    },

    [ITEM_RARE_BONE] =
    {
        .name = ES(ITEM_NAME("Rare Bone"), ITEM_NAME("Hueso Raro")),
        .price = (I_PRICE >= GEN_7) ? 5000 * TREASURE_FACTOR: 10000,
        .description = ES(COMPOUND_STRING("A bone for study\n"
            "that would sell at a\n"
            "high price."), COMPOUND_STRING("Un hueso para\n" "estudiar. Se vende\n" "caro.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_Bone,
        .iconPalette = gItemIconPalette_Bone,
    },

    [ITEM_ODD_KEYSTONE] =
    {
        .name = ES(ITEM_NAME("Odd Keystone"), ITEM_NAME("Piedra Espíritu")),
        .price = 2100,
        .description = ES(COMPOUND_STRING("A vital item. Voices\n"
            "can be heard from\n"
            "it occasionally."), COMPOUND_STRING("Un objeto vital. A\n" "veces se oyen voces\n" "dentro.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_OddKeystone,
        .iconPalette = gItemIconPalette_OddKeystone,
    },

    [ITEM_PRETTY_FEATHER] =
    {
        .name = ES(ITEM_NAME("Pretty Feather"), ITEM_NAME("Pluma Bella")),
        .price = (I_PRICE >= GEN_7) ? 1000 * TREASURE_FACTOR: 200,
        .description = ES(COMPOUND_STRING("A regular feather\n"
            "that has no effect\n"
            "on Pokémon."), COMPOUND_STRING("Una pluma normal. No\n" "afecta a los\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 20,
        .iconPic = gItemIcon_PrettyFeather,
        .iconPalette = gItemIconPalette_PrettyFeather,
    },

    [ITEM_RELIC_COPPER] =
    {
        .name = ES(ITEM_NAME("Relic Copper"), ITEM_NAME("Real Cobre")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A copper coin used\n"
            "by a civilization\n"
            "3,000 years ago."), COMPOUND_STRING("Moneda de cobre de\n" "más de 3000 años de\n" "antigüedad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_RELIC,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_RelicCoin,
        .iconPalette = gItemIconPalette_RelicCopper,
    },

    [ITEM_RELIC_SILVER] =
    {
        .name = ES(ITEM_NAME("Relic Silver"), ITEM_NAME("Real Plata")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A silver coin used\n"
            "by a civilization\n"
            "3,000 years ago."), COMPOUND_STRING("Moneda de plata de\n" "más de 3000 años de\n" "antigüedad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_RELIC,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_RelicCoin,
        .iconPalette = gItemIconPalette_RelicSilver,
    },

    [ITEM_RELIC_GOLD] =
    {
        .name = ES(ITEM_NAME("Relic Gold"), ITEM_NAME("Real Oro")),
        .price = (I_PRICE >= GEN_6) ? 60000 : 0,
        .description = ES(COMPOUND_STRING("A gold coin used\n"
            "by a civilization\n"
            "3,000 years ago."), COMPOUND_STRING("Moneda de oro de más\n" "de 3000 años de\n" "antigüedad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_RELIC,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_RelicCoin,
        .iconPalette = gItemIconPalette_RelicGold,
    },

    [ITEM_RELIC_VASE] =
    {
        .name = ES(ITEM_NAME("Relic Vase"), ITEM_NAME("Ánfora")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A fragile vase made\n"
            "by a civilization\n"
            "3,000 years ago."), COMPOUND_STRING("Jarrón de más de\n" "3000 años de\n" "antigüedad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_RELIC,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_RelicVase,
        .iconPalette = gItemIconPalette_Relics,
    },

    [ITEM_RELIC_BAND] =
    {
        .name = ES(ITEM_NAME("Relic Band"), ITEM_NAME("Brazal")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A bracelet made\n"
            "by a civilization\n"
            "3,000 years ago."), COMPOUND_STRING("Brazalete de más de\n" "3000 años de\n" "antigüedad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_RELIC,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_RelicBand,
        .iconPalette = gItemIconPalette_Relics,
    },

    [ITEM_RELIC_STATUE] =
    {
        .name = ES(ITEM_NAME("Relic Statue"), ITEM_NAME("Efigie Antigua")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A stone figure made\n"
            "by a civilization\n"
            "3,000 years ago."), COMPOUND_STRING("Efigie de piedra de\n" "más de 3000 años de\n" "antigüedad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_RELIC,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_RelicStatue,
        .iconPalette = gItemIconPalette_Relics,
    },

    [ITEM_RELIC_CROWN] =
    {
        .name = ES(ITEM_NAME("Relic Crown"), ITEM_NAME("Corona Antigua")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A heavy crown made\n"
            "by a civilization\n"
            "3,000 years ago."), COMPOUND_STRING("Corona de más de\n" "3000 años de\n" "antigüedad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_RELIC,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_RelicCrown,
        .iconPalette = gItemIconPalette_Relics,
    },

    [ITEM_STRANGE_SOUVENIR] =
    {
        .name = ES(ITEM_NAME("Strange Souvenir"), ITEM_NAME("Estatuilla Rara")),
        .price = (I_PRICE >= GEN_7) ? 3000 : 10,
        .description = ES(COMPOUND_STRING("An ornament that\n"
            "depicts a Pokémon\n"
            "from Alola."), COMPOUND_STRING("Un adorno con un\n" "Pokémon de Alola.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_RELIC,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_StrangeSouvenir,
        .iconPalette = gItemIconPalette_StrangeSouvenir,
    },

// Fossils

    [ITEM_HELIX_FOSSIL] =
    {
        .name = ES(ITEM_NAME("Helix Fossil"), ITEM_NAME("Fósil Hélix")),
        .description = ES(COMPOUND_STRING("A piece of an\n"
            "ancient marine\n"
            "Pokémon's seashell."), COMPOUND_STRING("Un trozo de concha\n" "de un Pokémon marino\n" "antiguo.")),
    #if I_KEY_FOSSILS >= GEN_4
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
    #else
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
    #endif
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_HelixFossil,
        .iconPalette = gItemIconPalette_KantoFossil,
    },

    [ITEM_DOME_FOSSIL] =
    {
        .name = ES(ITEM_NAME("Dome Fossil"), ITEM_NAME("Fósil Domo")),
        .description = ES(COMPOUND_STRING("A piece of an\n"
            "ancient marine\n"
            "Pokémon's shell."), COMPOUND_STRING("Un trozo de\n" "caparazón de un\n" "Pokémon antiguo.")),
    #if I_KEY_FOSSILS >= GEN_4
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
    #else
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
    #endif
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_DomeFossil,
        .iconPalette = gItemIconPalette_KantoFossil,
    },

    [ITEM_OLD_AMBER] =
    {
        .name = ES(ITEM_NAME("Old Amber"), ITEM_NAME("Ámbar Viejo")),
        .description = ES(COMPOUND_STRING("A stone containing\n"
            "the genes of an\n"
            "ancient Pokémon."), COMPOUND_STRING("Una piedra con genes\n" "de un Pokémon\n" "antiguo.")),
    #if I_KEY_FOSSILS >= GEN_4
        .price = 1000,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
    #else
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
    #endif
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_OldAmber,
        .iconPalette = gItemIconPalette_OldAmber,
    },

    [ITEM_ROOT_FOSSIL] =
    {
        .name = ES(ITEM_NAME("Root Fossil"), ITEM_NAME("Fósil Raíz")),
        .description = ES(COMPOUND_STRING("A fossil of an\n"
            "ancient, seafloor-\n"
            "dwelling Pokémon."), COMPOUND_STRING("Fósil de un Pokémon\n" "antiguo del fondo\n" "del mar.")),
    #if I_KEY_FOSSILS >= GEN_4
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
    #else
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
    #endif
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_RootFossil,
        .iconPalette = gItemIconPalette_HoennFossil,
    },

    [ITEM_CLAW_FOSSIL] =
    {
        .name = ES(ITEM_NAME("Claw Fossil"), ITEM_NAME("Fósil Garra")),
        .description = ES(COMPOUND_STRING("A fossil of an\n"
            "ancient, seafloor-\n"
            "dwelling Pokémon."), COMPOUND_STRING("Fósil de un Pokémon\n" "antiguo del fondo\n" "del mar.")),
    #if I_KEY_FOSSILS >= GEN_4
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
    #else
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
    #endif
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_ClawFossil,
        .iconPalette = gItemIconPalette_HoennFossil,
    },

    [ITEM_ARMOR_FOSSIL] =
    {
        .name = ES(ITEM_NAME("Armor Fossil"), ITEM_NAME("Fósil Coraza")),
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .description = ES(COMPOUND_STRING("A part of an\n"
            "ancient land\n"
            "Pokémon's collar."), COMPOUND_STRING("Parte del collar de\n" "un Pokémon terrestre\n" "antiguo.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_ArmorFossil,
        .iconPalette = gItemIconPalette_ArmorFossil,
    },

    [ITEM_SKULL_FOSSIL] =
    {
        .name = ES(ITEM_NAME("Skull Fossil"), ITEM_NAME("Fósil Cráneo")),
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .description = ES(COMPOUND_STRING("A part of an\n"
            "ancient land\n"
            "Pokémon's head."), COMPOUND_STRING("Parte de la cabeza\n" "de un Pokémon\n" "antiguo.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_SkullFossil,
        .iconPalette = gItemIconPalette_SkullFossil,
    },

    [ITEM_COVER_FOSSIL] =
    {
        .name = ES(ITEM_NAME("Cover Fossil"), ITEM_NAME("Fósil Tapa")),
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .description = ES(COMPOUND_STRING("A part of an\n"
            "ancient sea\n"
            "Pokémon's back."), COMPOUND_STRING("Parte del lomo de un\n" "Pokémon marino\n" "antiguo.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_CoverFossil,
        .iconPalette = gItemIconPalette_CoverFossil,
    },

    [ITEM_PLUME_FOSSIL] =
    {
        .name = ES(ITEM_NAME("Plume Fossil"), ITEM_NAME("Fósil Pluma")),
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .description = ES(COMPOUND_STRING("A part of an\n"
            "ancient sky\n"
            "Pokémon's wing."), COMPOUND_STRING("Parte del ala de un\n" "Pokémon volador\n" "antiguo.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_PlumeFossil,
        .iconPalette = gItemIconPalette_PlumeFossil,
    },

    [ITEM_JAW_FOSSIL] =
    {
        .name = ES(ITEM_NAME("Jaw Fossil"), ITEM_NAME("Fósil Mandíbula")),
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .description = ES(COMPOUND_STRING("A piece of an\n"
            "ancient land\n"
            "Pokémon's jaw."), COMPOUND_STRING("Parte de la\n" "mandíbula de un\n" "Pokémon antiguo.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_JawFossil,
        .iconPalette = gItemIconPalette_JawFossil,
    },

    [ITEM_SAIL_FOSSIL] =
    {
        .name = ES(ITEM_NAME("Sail Fossil"), ITEM_NAME("Fósil Aleta")),
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .description = ES(COMPOUND_STRING("An impression of an\n"
            "ancient land\n"
            "Pokémon's skin sail."), COMPOUND_STRING("Huella de la vela de\n" "un Pokémon antiguo.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_SailFossil,
        .iconPalette = gItemIconPalette_SailFossil,
    },

    [ITEM_FOSSILIZED_BIRD] =
    {
        .name = ES(ITEM_NAME("Fossilized Bird"), ITEM_NAME("Ornitofósil")),
        .price = 5000,
        .description = ES(COMPOUND_STRING("A fossil of an\n"
            "ancient, sky-\n"
            "soaring Pokémon."), COMPOUND_STRING("Fósil de un Pokémon\n" "antiguo que volaba.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_FossilizedBird,
        .iconPalette = gItemIconPalette_FossilizedBird,
    },

    [ITEM_FOSSILIZED_FISH] =
    {
        .name = ES(ITEM_NAME("Fossilized Fish"), ITEM_NAME("Ictiofósil")),
        .pluralName = ITEM_PLURAL_NAME("Fossilized Fish"),
        .price = 5000,
        .description = ES(COMPOUND_STRING("A fossil of an\n"
            "ancient, sea-\n"
            "dwelling Pokémon."), COMPOUND_STRING("Fósil de un Pokémon\n" "antiguo que vivía en\n" "el mar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_FossilizedFish,
        .iconPalette = gItemIconPalette_FossilizedFish,
    },

    [ITEM_FOSSILIZED_DRAKE] =
    {
        .name = ES(ITEM_NAME("Fossilized Drake"), ITEM_NAME("Dracofósil")),
        .price = 5000,
        .description = ES(COMPOUND_STRING("A fossil of an\n"
            "ancient, land-\n"
            "roaming Pokémon."), COMPOUND_STRING("Fósil de un Pokémon\n" "antiguo de tierra.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_FossilizedDrake,
        .iconPalette = gItemIconPalette_FossilizedDrake,
    },

    [ITEM_FOSSILIZED_DINO] =
    {
        .name = ES(ITEM_NAME("Fossilized Dino"), ITEM_NAME("Plesiofósil")),
        .price = 5000,
        .description = ES(COMPOUND_STRING("A fossil of an\n"
            "ancient, sea-\n"
            "dwelling Pokémon."), COMPOUND_STRING("Fósil de un Pokémon\n" "antiguo que vivía en\n" "el mar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_FossilizedDino,
        .iconPalette = gItemIconPalette_FossilizedDino,
    },

// Mulch

    [ITEM_GROWTH_MULCH] =
    {
        .name = ES(ITEM_NAME("Growth Mulch"), ITEM_NAME("Abono Rápido")),
        .pluralName = ITEM_PLURAL_NAME("Growth Mulch"),
        .price = 200,
    #if OW_BERRY_MULCH_USAGE == TRUE
        .description = ES(COMPOUND_STRING("Speeds up Berry\n"
            "growth, but dries\n"
            "the soil faster."), COMPOUND_STRING("Las bayas crecen\n" "antes, pero el suelo\n" "se seca.")),
    #else
        .description = COMPOUND_STRING(
            "It appears to be\n"
            "unsuitable for\n"
            "the soil."),
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = ITEM_TO_MULCH(ITEM_GROWTH_MULCH),
        .flingPower = 30,
        .iconPic = gItemIcon_Mulch,
        .iconPalette = gItemIconPalette_GrowthMulch,
    },

    [ITEM_DAMP_MULCH] =
    {
        .name = ES(ITEM_NAME("Damp Mulch"), ITEM_NAME("Abono Lento")),
        .pluralName = ITEM_PLURAL_NAME("Damp Mulch"),
        .price = 200,
    #if OW_BERRY_MULCH_USAGE == TRUE
        .description = ES(COMPOUND_STRING("Causes the soil to\n"
            "dry slower, but\n"
            "slows Berry growth."), COMPOUND_STRING("El suelo se seca\n" "menos, pero crecen\n" "más lento.")),
    #else
        .description = COMPOUND_STRING(
            "It appears to be\n"
            "unsuitable for\n"
            "the soil."),
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = ITEM_TO_MULCH(ITEM_DAMP_MULCH),
        .flingPower = 30,
        .iconPic = gItemIcon_Mulch,
        .iconPalette = gItemIconPalette_DampMulch,
    },

    [ITEM_STABLE_MULCH] =
    {
        .name = ES(ITEM_NAME("Stable Mulch"), ITEM_NAME("Abono Fijador")),
        .pluralName = ITEM_PLURAL_NAME("Stable Mulch"),
        .price = 200,
    #if OW_BERRY_MULCH_USAGE == TRUE
        .description = ES(COMPOUND_STRING("Extends the time\n"
            "ripened Berries\n"
            "remain on plants."), COMPOUND_STRING("Las bayas maduras\n" "duran más en la\n" "planta.")),
    #else
        .description = COMPOUND_STRING(
            "It appears to be\n"
            "unsuitable for\n"
            "the soil."),
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = ITEM_TO_MULCH(ITEM_STABLE_MULCH),
        .flingPower = 30,
        .iconPic = gItemIcon_StableMulch,
        .iconPalette = gItemIconPalette_StableMulch,
    },

    [ITEM_GOOEY_MULCH] =
    {
        .name = ES(ITEM_NAME("Gooey Mulch"), ITEM_NAME("Abono Brote")),
        .pluralName = ITEM_PLURAL_NAME("Gooey Mulch"),
        .price = 200,
    #if OW_BERRY_MULCH_USAGE == TRUE
        .description = ES(COMPOUND_STRING("Ups the times new\n"
            "plants grow where\n"
            "mature ones withered."), COMPOUND_STRING("Más plantas nuevas\n" "donde se secaron\n" "otras.")),
    #else
        .description = COMPOUND_STRING(
            "It appears to be\n"
            "unsuitable for\n"
            "the soil."),
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = ITEM_TO_MULCH(ITEM_GOOEY_MULCH),
        .flingPower = 30,
        .iconPic = gItemIcon_Mulch,
        .iconPalette = gItemIconPalette_GooeyMulch,
    },

    [ITEM_RICH_MULCH] =
    {
        .name = ES(ITEM_NAME("Rich Mulch"), ITEM_NAME("Abono Fértil")),
        .pluralName = ITEM_PLURAL_NAME("Rich Mulch"),
        .price = 200,
    #if OW_BERRY_MULCH_USAGE == TRUE
        .description = ES(COMPOUND_STRING("A fertilizer for\n"
            "growing Berries that\n"
            "increases the harvest."), COMPOUND_STRING("Un abono que da más\n" "bayas.")),
    #else
        .description = COMPOUND_STRING(
            "It appears to be\n"
            "unsuitable for\n"
            "the soil."),
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = ITEM_TO_MULCH(ITEM_RICH_MULCH),
        .flingPower = 30,
        .iconPic = gItemIcon_Mulch,
        .iconPalette = gItemIconPalette_RichMulch,
    },

    [ITEM_SURPRISE_MULCH] =
    {
        .name = ES(ITEM_NAME("Surprise Mulch"), ITEM_NAME("Abono Sorpresa")),
        .pluralName = ITEM_PLURAL_NAME("Surprise Mulch"),
        .price = 200,
    #if OW_BERRY_MULCH_USAGE == TRUE
        .description = ES(COMPOUND_STRING("A fertilizer for\n"
            "growing Berries that\n"
            "causes mutations."), COMPOUND_STRING("Un abono que causa\n" "mutaciones en las\n" "bayas.")),
    #else
        .description = COMPOUND_STRING(
            "It appears to be\n"
            "unsuitable for\n"
            "the soil."),
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = ITEM_TO_MULCH(ITEM_SURPRISE_MULCH),
        .flingPower = 30,
        .iconPic = gItemIcon_Mulch,
        .iconPalette = gItemIconPalette_SurpriseMulch,
    },

    [ITEM_BOOST_MULCH] =
    {
        .name = ES(ITEM_NAME("Boost Mulch"), ITEM_NAME("Abono Fructífero")),
        .pluralName = ITEM_PLURAL_NAME("Boost Mulch"),
        .price = 200,
    #if OW_BERRY_MULCH_USAGE == TRUE
        .description = ES(COMPOUND_STRING("Increases the Berry\n"
            "harvest that can be\n"
            "grown by watering."), COMPOUND_STRING("Da más bayas al\n" "regarlas.")),
    #else
        .description = COMPOUND_STRING(
            "It appears to be\n"
            "unsuitable for\n"
            "the soil."),
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = ITEM_TO_MULCH(ITEM_BOOST_MULCH),
        .flingPower = 30,
        .iconPic = gItemIcon_Mulch,
        .iconPalette = gItemIconPalette_BoostMulch,
    },

    [ITEM_AMAZE_MULCH] =
    {
        .name = ES(ITEM_NAME("Amaze Mulch"), ITEM_NAME("Abono Insólito")),
        .pluralName = ITEM_PLURAL_NAME("Amaze Mulch"),
        .price = 200,
    #if OW_BERRY_MULCH_USAGE == TRUE
        .description = ES(COMPOUND_STRING("A fertilizer with the\n"
            "effects of Rich, Boost,\n"
            "and Surprise Mulch."), COMPOUND_STRING("Abono con el efecto\n" "de Rico, Mejora y\n" "Sorpresa.")),
    #else
        .description = COMPOUND_STRING(
            "It appears to be\n"
            "unsuitable for\n"
            "the soil."),
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = ITEM_TO_MULCH(ITEM_AMAZE_MULCH),
        .flingPower = 30,
        .iconPic = gItemIcon_Mulch,
        .iconPalette = gItemIconPalette_AmazeMulch,
    },

// Apricorns
#if (I_PRICE >= GEN_8 || I_PRICE <= GEN_2)
    #define APRICORN_PRICE 200
#elif I_PRICE >= GEN_5
    #define APRICORN_PRICE 20
#else
    #define APRICORN_PRICE 0
#endif

    [ITEM_RED_APRICORN] =
    {
        .name = ES(ITEM_NAME("Red Apricorn"), ITEM_NAME("Bonguri Rojo")),
        .price = APRICORN_PRICE,
        .description = ES(COMPOUND_STRING("A red Apricorn.\n"
            "It assails your\n"
            "nostrils."), COMPOUND_STRING("Bonguri de color\n" "rojo y aroma muy\n" "penetrante.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Apricorn,
        .iconPalette = gItemIconPalette_RedApricorn,
    },

    [ITEM_BLUE_APRICORN] =
    {
        .name = ES(ITEM_NAME("Blue Apricorn"), ITEM_NAME("Bonguri Azul")),
        .price = APRICORN_PRICE,
        .description = ES(COMPOUND_STRING("A blue Apricorn.\n"
            "It smells a bit\n"
            "like grass."), COMPOUND_STRING("Bonguri de color\n" "azul y aroma tierno.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Apricorn,
        .iconPalette = gItemIconPalette_BlueApricorn,
    },

    [ITEM_YELLOW_APRICORN] =
    {
        .name = ES(ITEM_NAME("Yellow Apricorn"), ITEM_NAME("Bonguri Amarillo")),
        .price = APRICORN_PRICE,
        .description = ES(COMPOUND_STRING("A yellow Apricorn.\n"
            "It has a light,\n"
            "refreshing scent."), COMPOUND_STRING("Bonguri de color\n" "amarillo y aroma\n" "refrescante.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Apricorn,
        .iconPalette = gItemIconPalette_YellowApricorn,
    },

    [ITEM_GREEN_APRICORN] =
    {
        .name = ES(ITEM_NAME("Green Apricorn"), ITEM_NAME("Bonguri Verde")),
        .price = APRICORN_PRICE,
        .description = ES(COMPOUND_STRING("A green Apricorn.\n"
            "It has an aromatic,\n"
            "mysterious scent."), COMPOUND_STRING("Un bonguri verde de\n" "aroma misterioso.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Apricorn,
        .iconPalette = gItemIconPalette_GreenApricorn,
    },

    [ITEM_PINK_APRICORN] =
    {
        .name = ES(ITEM_NAME("Pink Apricorn"), ITEM_NAME("Bonguri Rosa")),
        .price = APRICORN_PRICE,
        .description = ES(COMPOUND_STRING("A pink Apricorn.\n"
            "It has a nice,\n"
            "sweet scent."), COMPOUND_STRING("Bonguri de color\n" "rosa y aroma dulce.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Apricorn,
        .iconPalette = gItemIconPalette_PinkApricorn,
    },

    [ITEM_WHITE_APRICORN] =
    {
        .name = ES(ITEM_NAME("White Apricorn"), ITEM_NAME("Bonguri Blanco")),
        .price = APRICORN_PRICE,
        .description = ES(COMPOUND_STRING("A white Apricorn.\n"
            "It doesn't smell\n"
            "like anything."), COMPOUND_STRING("Un bonguri blanco.\n" "No huele a nada.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Apricorn,
        .iconPalette = gItemIconPalette_WhiteApricorn,
    },

    [ITEM_BLACK_APRICORN] =
    {
        .name = ES(ITEM_NAME("Black Apricorn"), ITEM_NAME("Bonguri Negro")),
        .price = APRICORN_PRICE,
        .description = ES(COMPOUND_STRING("A black Apricorn.\n"
            "Its scent is\n"
            "indescribable."), COMPOUND_STRING("Bonguri de color\n" "negro y aroma\n" "indescriptible.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Apricorn,
        .iconPalette = gItemIconPalette_BlackApricorn,
    },

    [ITEM_WISHING_PIECE] =
    {
        .name = ES(ITEM_NAME("Wishing Piece"), ITEM_NAME("Trozo Deseo")),
        .price = 20,
        .description = ES(COMPOUND_STRING("Throw one into a\n"
            "den to attract a\n"
            "Dynamax Pokémon."), COMPOUND_STRING("Se echa en una\n" "guarida para atraer\n" "un Dinamax.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 50,
        .iconPic = gItemIcon_WishingPiece,
        .iconPalette = gItemIconPalette_WishingPiece,
    },

    [ITEM_GALARICA_TWIG] =
    {
        .name = ES(ITEM_NAME("Galarica Twig"), ITEM_NAME("Rama de Galanuez")),
        .price = 20 * TREASURE_FACTOR,
        .description = ES(COMPOUND_STRING("A twig from a tree\n"
            "called Galarica\n"
            "that grows in Galar."), COMPOUND_STRING("Una ramita del árbol\n" "Galanuez de Galar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_GalaricaTwig,
        .iconPalette = gItemIconPalette_GalaricaItem,
    },

    [ITEM_ARMORITE_ORE] =
    {
        .name = ES(ITEM_NAME("Armorite Ore"), ITEM_NAME("Duralium")),
        .pluralName = ITEM_PLURAL_NAME("Armorite Ore"),
        .price = 20,
        .description = ES(COMPOUND_STRING("Rare ore that\n"
            "can be obtained on\n"
            "the Isle of Armor."), COMPOUND_STRING("Un mineral raro de\n" "la Isla de la\n" "Armadura.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_ArmoriteOre,
        .iconPalette = gItemIconPalette_ArmoriteOre,
    },

    [ITEM_DYNITE_ORE] =
    {
        .name = ES(ITEM_NAME("Dynite Ore"), ITEM_NAME("Maxinium")),
        .pluralName = ITEM_PLURAL_NAME("Dynite Ore"),
        .price = 20,
        .description = ES(COMPOUND_STRING("Mysterious ore\n"
            "obtained in\n"
            "the Max Lair."), COMPOUND_STRING("Un mineral\n" "misterioso de la\n" "Guarida Dinamax.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_DyniteOre,
        .iconPalette = gItemIconPalette_DyniteOre,
    },

// Mail

    [ITEM_ORANGE_MAIL] =
    {
        .name = ES(ITEM_NAME("Orange Mail"), ITEM_NAME("Car. Naranja")),
        .pluralName = ITEM_PLURAL_NAME("Orange Mail"),
        .price = 50,
        .description = ES(COMPOUND_STRING("A Zigzagoon-print\n"
            "Mail to be held by\n"
            "a Pokémon."), COMPOUND_STRING("Carta con dibujos de\n" "Zigzagoon para\n" "llevar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_ORANGE_MAIL),
        .iconPic = gItemIcon_OrangeMail,
        .iconPalette = gItemIconPalette_OrangeMail,
    },

    [ITEM_HARBOR_MAIL] =
    {
        .name = ES(ITEM_NAME("Harbor Mail"), ITEM_NAME("Carta Puerto")),
        .pluralName = ITEM_PLURAL_NAME("Harbor Mail"),
        .price = 50,
        .description = ES(COMPOUND_STRING("A Wingull-print\n"
            "Mail to be held by\n"
            "a Pokémon."), COMPOUND_STRING("Carta con dibujos de\n" "Wingull para llevar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_HARBOR_MAIL),
        .iconPic = gItemIcon_HarborMail,
        .iconPalette = gItemIconPalette_HarborMail,
    },

    [ITEM_GLITTER_MAIL] =
    {
        .name = ES(ITEM_NAME("Glitter Mail"), ITEM_NAME("Carta Brillo")),
        .pluralName = ITEM_PLURAL_NAME("Glitter Mail"),
        .price = 50,
        .description = ES(COMPOUND_STRING("A Pikachu-print\n"
            "Mail to be held by\n"
            "a Pokémon."), COMPOUND_STRING("Carta con dibujos de\n" "Pikachu para llevar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_GLITTER_MAIL),
        .iconPic = gItemIcon_GlitterMail,
        .iconPalette = gItemIconPalette_GlitterMail,
    },

    [ITEM_MECH_MAIL] =
    {
        .name = ES(ITEM_NAME("Mech Mail"), ITEM_NAME("Carta Imán")),
        .pluralName = ITEM_PLURAL_NAME("Mech Mail"),
        .price = 50,
        .description = ES(COMPOUND_STRING("A Magnemite-print\n"
            "Mail to be held by\n"
            "a Pokémon."), COMPOUND_STRING("Carta con dibujos de\n" "Magnemite para\n" "llevar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_MECH_MAIL),
        .iconPic = gItemIcon_MechMail,
        .iconPalette = gItemIconPalette_MechMail,
    },

    [ITEM_WOOD_MAIL] =
    {
        .name = ES(ITEM_NAME("Wood Mail"), ITEM_NAME("Carta Madera")),
        .pluralName = ITEM_PLURAL_NAME("Wood Mail"),
        .price = 50,
        .description = ES(COMPOUND_STRING("A Slakoth-print\n"
            "Mail to be held by\n"
            "a Pokémon."), COMPOUND_STRING("Carta con dibujos de\n" "Slakoth para llevar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_WOOD_MAIL),
        .iconPic = gItemIcon_WoodMail,
        .iconPalette = gItemIconPalette_WoodMail,
    },

    [ITEM_WAVE_MAIL] =
    {
        .name = ES(ITEM_NAME("Wave Mail"), ITEM_NAME("Carta Ola")),
        .pluralName = ITEM_PLURAL_NAME("Wave Mail"),
        .price = 50,
        .description = ES(COMPOUND_STRING("A Wailmer-print\n"
            "Mail to be held by\n"
            "a Pokémon."), COMPOUND_STRING("Carta con dibujos de\n" "Wailmer para llevar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_WAVE_MAIL),
        .iconPic = gItemIcon_WaveMail,
        .iconPalette = gItemIconPalette_WaveMail,
    },

    [ITEM_BEAD_MAIL] =
    {
        .name = ES(ITEM_NAME("Bead Mail"), ITEM_NAME("Carta Imagen")),
        .pluralName = ITEM_PLURAL_NAME("Bead Mail"),
        .price = 50,
        .description = ES(COMPOUND_STRING("Mail featuring a\n"
            "sketch of the\n"
            "holding Pokémon."), COMPOUND_STRING("Carta con un dibujo\n" "del Pokémon que la\n" "lleva.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_BEAD_MAIL),
        .iconPic = gItemIcon_BeadMail,
        .iconPalette = gItemIconPalette_BeadMail,
    },

    [ITEM_SHADOW_MAIL] =
    {
        .name = ES(ITEM_NAME("Shadow Mail"), ITEM_NAME("Carta Sombra")),
        .pluralName = ITEM_PLURAL_NAME("Shadow Mail"),
        .price = 50,
        .description = ES(COMPOUND_STRING("A Duskull-print\n"
            "Mail to be held by\n"
            "a Pokémon."), COMPOUND_STRING("Carta con dibujos de\n" "Duskull para llevar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_SHADOW_MAIL),
        .iconPic = gItemIcon_ShadowMail,
        .iconPalette = gItemIconPalette_ShadowMail,
    },

    [ITEM_TROPIC_MAIL] =
    {
        .name = ES(ITEM_NAME("Tropic Mail"), ITEM_NAME("Car. Tropic.")),
        .pluralName = ITEM_PLURAL_NAME("Tropic Mail"),
        .price = 50,
        .description = ES(COMPOUND_STRING("A Bellossom-print\n"
            "Mail to be held by\n"
            "a Pokémon."), COMPOUND_STRING("Carta con dibujos de\n" "Bellossom para\n" "llevar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_TROPIC_MAIL),
        .iconPic = gItemIcon_TropicMail,
        .iconPalette = gItemIconPalette_TropicMail,
    },

    [ITEM_DREAM_MAIL] =
    {
        .name = ES(ITEM_NAME("Dream Mail"), ITEM_NAME("Carta Sueño")),
        .pluralName = ITEM_PLURAL_NAME("Dream Mail"),
        .price = 50,
        .description = ES(COMPOUND_STRING("Mail featuring a\n"
            "sketch of the\n"
            "holding Pokémon."), COMPOUND_STRING("Carta con un dibujo\n" "del Pokémon que la\n" "lleva.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_DREAM_MAIL),
        .iconPic = gItemIcon_DreamMail,
        .iconPalette = gItemIconPalette_DreamMail,
    },

    [ITEM_FAB_MAIL] =
    {
        .name = ES(ITEM_NAME("Fab Mail"), ITEM_NAME("Carta Fab.")),
        .pluralName = ITEM_PLURAL_NAME("Fab Mail"),
        .price = 50,
        .description = ES(COMPOUND_STRING("A gorgeous-print\n"
            "Mail to be held\n"
            "by a Pokémon."), COMPOUND_STRING("Carta con un dibujo\n" "precioso para\n" "llevar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_FAB_MAIL),
        .iconPic = gItemIcon_FabMail,
        .iconPalette = gItemIconPalette_FabMail,
    },

    [ITEM_RETRO_MAIL] =
    {
        .name = ES(ITEM_NAME("Retro Mail"), ITEM_NAME("Carta Retro.")),
        .pluralName = ITEM_PLURAL_NAME("Retro Mail"),
        .price = 50,
        .description = ES(COMPOUND_STRING("Mail featuring the\n"
            "drawings of three\n"
            "Pokémon."), COMPOUND_STRING("Carta con dibujos de\n" "tres Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_RETRO_MAIL),
        .iconPic = gItemIcon_RetroMail,
        .iconPalette = gItemIconPalette_RetroMail,
    },

// Evolution items

    [ITEM_FIRE_STONE] =
    {
        .name = ES(ITEM_NAME("Fire Stone"), ITEM_NAME("Piedra Fuego")),
        .price = (I_PRICE >= GEN_7) ? 3000 : 2100,
        .description = ES(COMPOUND_STRING("Makes certain\n"
            "species of Pokémon\n"
            "evolve."), COMPOUND_STRING("Hace evolucionar a\n" "ciertos Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_FireStone,
        .iconPalette = gItemIconPalette_FireStone,
    },

    [ITEM_WATER_STONE] =
    {
        .name = ES(ITEM_NAME("Water Stone"), ITEM_NAME("Piedra Agua")),
        .price = (I_PRICE >= GEN_7) ? 3000 : 2100,
        .description = ES(COMPOUND_STRING("Makes certain\n"
            "species of Pokémon\n"
            "evolve."), COMPOUND_STRING("Hace evolucionar a\n" "ciertos Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_WaterStone,
        .iconPalette = gItemIconPalette_WaterStone,
    },

    [ITEM_THUNDER_STONE] =
    {
        .name = ES(ITEM_NAME("Thunder Stone"), ITEM_NAME("Piedra Trueno")),
        .price = (I_PRICE >= GEN_7) ? 3000 : 2100,
        .description = ES(COMPOUND_STRING("Makes certain\n"
            "species of Pokémon\n"
            "evolve."), COMPOUND_STRING("Hace evolucionar a\n" "ciertos Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_ThunderStone,
        .iconPalette = gItemIconPalette_ThunderStone,
    },

    [ITEM_LEAF_STONE] =
    {
        .name = ES(ITEM_NAME("Leaf Stone"), ITEM_NAME("Piedra Hoja")),
        .price = (I_PRICE >= GEN_7) ? 3000 : 2100,
        .description = ES(COMPOUND_STRING("Makes certain\n"
            "species of Pokémon\n"
            "evolve."), COMPOUND_STRING("Hace evolucionar a\n" "ciertos Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_LeafStone,
        .iconPalette = gItemIconPalette_LeafStone,
    },

    [ITEM_ICE_STONE] =
    {
        .name = ES(ITEM_NAME("Ice Stone"), ITEM_NAME("Piedra Hielo")),
        .price = (I_PRICE >= GEN_7) ? 3000 : 2100,
        .description = ES(COMPOUND_STRING("Makes certain\n"
            "species of Pokémon\n"
            "evolve."), COMPOUND_STRING("Hace evolucionar a\n" "ciertos Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_IceStone,
        .iconPalette = gItemIconPalette_IceStone,
    },

    [ITEM_SUN_STONE] =
    {
        .name = ES(ITEM_NAME("Sun Stone"), ITEM_NAME("Piedra Solar")),
        .price = (I_PRICE >= GEN_7) ? 3000 : 2100,
        .description = ES(COMPOUND_STRING("Makes certain\n"
            "species of Pokémon\n"
            "evolve."), COMPOUND_STRING("Hace evolucionar a\n" "ciertos Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_SunStone,
        .iconPalette = gItemIconPalette_SunStone,
    },

    [ITEM_MOON_STONE] =
    {
        .name = ES(ITEM_NAME("Moon Stone"), ITEM_NAME("Piedra Lunar")),
    #if I_PRICE >= GEN_7
        .price = 3000,
    #elif I_PRICE >= GEN_4
        .price = 2100,
    #elif I_PRICE == GEN_3
        .price = 0,
    #else
        .price = 1,
    #endif
        .description = ES(COMPOUND_STRING("Makes certain\n"
            "species of Pokémon\n"
            "evolve."), COMPOUND_STRING("Hace evolucionar a\n" "ciertos Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_MoonStone,
        .iconPalette = gItemIconPalette_MoonStone,
    },

    [ITEM_SHINY_STONE] =
    {
        .name = ES(ITEM_NAME("Shiny Stone"), ITEM_NAME("Piedra Día")),
        .price = (I_PRICE >= GEN_7) ? 3000 : 2100,
        .description = ES(COMPOUND_STRING("Makes certain\n"
            "species of Pokémon\n"
            "evolve."), COMPOUND_STRING("Hace evolucionar a\n" "ciertos Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_ShinyStone,
        .iconPalette = gItemIconPalette_ShinyStone,
    },

    [ITEM_DUSK_STONE] =
    {
        .name = ES(ITEM_NAME("Dusk Stone"), ITEM_NAME("Piedra Noche")),
        .price = (I_PRICE >= GEN_7) ? 3000 : 2100,
        .description = ES(COMPOUND_STRING("Makes certain\n"
            "species of Pokémon\n"
            "evolve."), COMPOUND_STRING("Hace evolucionar a\n" "ciertos Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_DuskStone,
        .iconPalette = gItemIconPalette_DuskStone,
    },

    [ITEM_DAWN_STONE] =
    {
        .name = ES(ITEM_NAME("Dawn Stone"), ITEM_NAME("Piedra Alba")),
        .price = (I_PRICE >= GEN_7) ? 3000 : 2100,
        .description = ES(COMPOUND_STRING("Makes certain\n"
            "species of Pokémon\n"
            "evolve."), COMPOUND_STRING("Hace evolucionar a\n" "ciertos Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_DawnStone,
        .iconPalette = gItemIconPalette_DawnStone,
    },

    [ITEM_SWEET_APPLE] =
    {
        .name = ES(ITEM_NAME("Sweet Apple"), ITEM_NAME("Manzana Dulce")),
        .price = 2200,
        .description = ES(COMPOUND_STRING("A peculiar apple\n"
            "that makes certain\n"
            "Pokémon evolve."), COMPOUND_STRING("Una manzana rara que\n" "hace evolucionar a\n" "ciertos Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_SweetApple,
        .iconPalette = gItemIconPalette_SweetApple,
    },

    [ITEM_TART_APPLE] =
    {
        .name = ES(ITEM_NAME("Tart Apple"), ITEM_NAME("Manzana Ácida")),
        .price = 2200,
        .description = ES(COMPOUND_STRING("A peculiar apple\n"
            "that makes certain\n"
            "Pokémon evolve."), COMPOUND_STRING("Una manzana rara que\n" "hace evolucionar a\n" "ciertos Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_TartApple,
        .iconPalette = gItemIconPalette_TartApple,
    },

    [ITEM_CRACKED_POT] =
    {
        .name = ES(ITEM_NAME("Cracked Pot"), ITEM_NAME("Tetera Agrietada")),
        .price = 1600,
        .description = ES(COMPOUND_STRING("A peculiar teapot\n"
            "that makes certain\n"
            "Pokémon evolve."), COMPOUND_STRING("Una tetera rara que\n" "hace evolucionar a\n" "algunos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_CrackedPot,
        .iconPalette = gItemIconPalette_Pot,
    },

    [ITEM_CHIPPED_POT] =
    {
        .name = ES(ITEM_NAME("Chipped Pot"), ITEM_NAME("Tetera Rota")),
        .price = 38000,
        .description = ES(COMPOUND_STRING("A peculiar teapot\n"
            "that makes certain\n"
            "Pokémon evolve."), COMPOUND_STRING("Una tetera rara que\n" "hace evolucionar a\n" "algunos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_ChippedPot,
        .iconPalette = gItemIconPalette_Pot,
    },

    [ITEM_GALARICA_CUFF] =
    {
        .name = ES(ITEM_NAME("Galarica Cuff"), ITEM_NAME("Brazal Galanuez")),
        .price = (I_PRICE >= GEN_9) ? 3000 : 6000,
        .description = ES(COMPOUND_STRING("A cuff that\n"
            "makes Galarian\n"
            "Slowpoke happy."), COMPOUND_STRING("Un brazalete que\n" "alegra al Slowpoke\n" "de Galar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_GalaricaCuff,
        .iconPalette = gItemIconPalette_GalaricaItem,
    },

    [ITEM_GALARICA_WREATH] =
    {
        .name = ES(ITEM_NAME("Galarica Wreath"), ITEM_NAME("Corona Galanuez")),
        .price = (I_PRICE >= GEN_9) ? 3000 : 6000,
        .description = ES(COMPOUND_STRING("A wreath that\n"
            "makes Galarian\n"
            "Slowpoke happy."), COMPOUND_STRING("Una corona que\n" "alegra al Slowpoke\n" "de Galar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_GalaricaWreath,
        .iconPalette = gItemIconPalette_GalaricaItem,
    },

    [ITEM_DRAGON_SCALE] =
    {
        .name = ES(ITEM_NAME("Dragon Scale"), ITEM_NAME("Escama Dragón")),
        .price = (I_PRICE >= GEN_7) ? 2000 * TREASURE_FACTOR : 2100,
        .holdEffectParam = 10,
        .description = ES(COMPOUND_STRING("A strange scale\n"
            "held by Dragon-\n"
            "type Pokémon."), COMPOUND_STRING("Una escama rara de\n" "los Pokémon de tipo\n" "Dragón.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_DragonScale,
        .iconPalette = gItemIconPalette_DragonScale,
    },

    [ITEM_UPGRADE] =
    {
        .name = ES(ITEM_NAME("Upgrade"), ITEM_NAME("Mejora")),
        .price = (I_PRICE >= GEN_7) ? 2000 * TREASURE_FACTOR : 2100,
        .description = ES(COMPOUND_STRING("A peculiar box made\n"
            "by Silph Co."), COMPOUND_STRING("Una caja extraña\n" "creada por Silph\n" "S.A.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_Upgrade,
        .iconPalette = gItemIconPalette_Upgrade,
    },

    [ITEM_PROTECTOR] =
    {
        .name = ITEM_NAME("Protector"),
        .price = (I_PRICE >= GEN_7) ? 2000 * TREASURE_FACTOR : 2100,
        .description = ES(COMPOUND_STRING("A protective item.\n"
            "It is loved by\n"
            "a certain Pokémon."), COMPOUND_STRING("Un objeto protector\n" "que adora cierto\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_Protector,
        .iconPalette = gItemIconPalette_Protector,
    },

    [ITEM_ELECTIRIZER] =
    {
        .name = ES(ITEM_NAME("Electirizer"), ITEM_NAME("Electrizador")),
        .price = (I_PRICE >= GEN_7) ? 2000 * TREASURE_FACTOR : 2100,
        .description = ES(COMPOUND_STRING("A box of electric\n"
            "energy loved by\n"
            "a certain Pokémon."), COMPOUND_STRING("Caja de energía\n" "eléctrica que adora\n" "un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_Electirizer,
        .iconPalette = gItemIconPalette_Electirizer,
    },

    [ITEM_MAGMARIZER] =
    {
        .name = ES(ITEM_NAME("Magmarizer"), ITEM_NAME("Magmatizador")),
        .price = (I_PRICE >= GEN_7) ? 2000 * TREASURE_FACTOR : 2100,
        .description = ES(COMPOUND_STRING("A box of magma\n"
            "energy loved by\n"
            "a certain Pokémon."), COMPOUND_STRING("Caja de energía\n" "magmática que adora\n" "un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_Magmarizer,
        .iconPalette = gItemIconPalette_Magmarizer,
    },

    [ITEM_DUBIOUS_DISC] =
    {
        .name = ES(ITEM_NAME("Dubious Disc"), ITEM_NAME("Disco Extraño")),
        .price = (I_PRICE >= GEN_7) ? 2000 * TREASURE_FACTOR : 2100,
        .description = ES(COMPOUND_STRING("A transparent\n"
            "device overflowing\n"
            "with dubious data."), COMPOUND_STRING("Un disco\n" "transparente lleno\n" "de datos dudosos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 50,
        .iconPic = gItemIcon_DubiousDisc,
        .iconPalette = gItemIconPalette_DubiousDisc,
    },

    [ITEM_REAPER_CLOTH] =
    {
        .name = ES(ITEM_NAME("Reaper Cloth"), ITEM_NAME("Tela Terrible")),
        .price = (I_PRICE >= GEN_7) ? 2000 * TREASURE_FACTOR : 2100,
        .description = ES(COMPOUND_STRING("A cloth imbued with\n"
            "energy loved by\n"
            "a certain Pokémon."), COMPOUND_STRING("Una tela llena de\n" "energía que adora un\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 10,
        .iconPic = gItemIcon_ReaperCloth,
        .iconPalette = gItemIconPalette_ReaperCloth,
    },

    [ITEM_PRISM_SCALE] =
    {
        .name = ES(ITEM_NAME("Prism Scale"), ITEM_NAME("Escama Bella")),
    #if I_PRICE >= GEN_9
        .price = 3000,
    #elif I_PRICE >= GEN_7
        .price = 2000,
    #else
        .price = 500,
    #endif
        .description = ES(COMPOUND_STRING("A mysterious scale\n"
            "that makes certain\n"
            "Pokémon evolve."), COMPOUND_STRING("Una escama\n" "misteriosa que hace\n" "evolucionar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_PrismScale,
        .iconPalette = gItemIconPalette_PrismScale,
    },

    [ITEM_WHIPPED_DREAM] =
    {
        .name = ES(ITEM_NAME("Whipped Dream"), ITEM_NAME("Dulce de Nata")),
        .price = (I_PRICE >= GEN_7) ? 2000 * TREASURE_FACTOR : 2100,
        .description = ES(COMPOUND_STRING("A soft and sweet\n"
            "treat loved by\n"
            "a certain Pokémon."), COMPOUND_STRING("Un dulce suave que\n" "adora cierto\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_WhippedDream,
        .iconPalette = gItemIconPalette_WhippedDream,
    },

    [ITEM_SACHET] =
    {
        .name = ES(ITEM_NAME("Sachet"), ITEM_NAME("Saquito Fragante")),
        .price = (I_PRICE >= GEN_7) ? 2000 * TREASURE_FACTOR : 2100,
        .description = ES(COMPOUND_STRING("A sachet with\n"
            "perfumes loved by\n"
            "a certain Pokémon."), COMPOUND_STRING("Una bolsita de\n" "perfume que adora un\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_Sachet,
        .iconPalette = gItemIconPalette_Sachet,
    },

    [ITEM_OVAL_STONE] =
    {
        .name = ES(ITEM_NAME("Oval Stone"), ITEM_NAME("Piedra Oval")),
        .price = (I_PRICE >= GEN_7) ? 2000 : 2100,
        .description = ES(COMPOUND_STRING("Makes certain\n"
            "species of Pokémon\n"
            "evolve."), COMPOUND_STRING("Hace evolucionar a\n" "ciertos Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_OvalStone,
        .iconPalette = gItemIconPalette_OvalStone,
    },

    [ITEM_STRAWBERRY_SWEET] =
    {
        .name = ES(ITEM_NAME("Strawberry Sweet"), ITEM_NAME("Confite Fresa")),
        .price = 500 * TREASURE_FACTOR,
        .description = ES(COMPOUND_STRING("Strawberry-shaped\n"
            "sweet. When held by\n"
            "Milcery, it's happy."), COMPOUND_STRING("Dulce de fresa. Si\n" "lo lleva Milcery, se\n" "alegra.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_StrawberrySweet,
        .iconPalette = gItemIconPalette_StrawberrySweet,
    },

    [ITEM_LOVE_SWEET] =
    {
        .name = ES(ITEM_NAME("Love Sweet"), ITEM_NAME("Confite Corazón")),
        .price = 500 * TREASURE_FACTOR,
        .description = ES(COMPOUND_STRING("A heart-shaped\n"
            "sweet. When held by\n"
            "Milcery, it's happy."), COMPOUND_STRING("Dulce de corazón. Si\n" "lo lleva Milcery, se\n" "alegra.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_LoveSweet,
        .iconPalette = gItemIconPalette_LoveSweet,
    },

    [ITEM_BERRY_SWEET] =
    {
        .name = ES(ITEM_NAME("Berry Sweet"), ITEM_NAME("Confite Fruto")),
        .price = 500 * TREASURE_FACTOR,
        .description = ES(COMPOUND_STRING("A berry-shaped\n"
            "sweet. When held by\n"
            "Milcery, it's happy."), COMPOUND_STRING("Dulce de baya. Si lo\n" "lleva Milcery, se\n" "alegra.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_BerrySweet,
        .iconPalette = gItemIconPalette_BerrySweet,
    },

    [ITEM_CLOVER_SWEET] =
    {
        .name = ES(ITEM_NAME("Clover Sweet"), ITEM_NAME("Confite Trébol")),
        .price = 500 * TREASURE_FACTOR,
        .description = ES(COMPOUND_STRING("A clover-shaped\n"
            "sweet. When held by\n"
            "Milcery, it's happy."), COMPOUND_STRING("Dulce de trébol. Si\n" "lo lleva Milcery, se\n" "alegra.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_CloverSweet,
        .iconPalette = gItemIconPalette_CloverSweet,
    },

    [ITEM_FLOWER_SWEET] =
    {
        .name = ES(ITEM_NAME("Flower Sweet"), ITEM_NAME("Confite Flor")),
        .price = 500 * TREASURE_FACTOR,
        .description = ES(COMPOUND_STRING("A flower-shaped\n"
            "sweet. When held by\n"
            "Milcery, it's happy."), COMPOUND_STRING("Dulce de flor. Si lo\n" "lleva Milcery, se\n" "alegra.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_FlowerSweet,
        .iconPalette = gItemIconPalette_FlowerSweet,
    },

    [ITEM_STAR_SWEET] =
    {
        .name = ES(ITEM_NAME("Star Sweet"), ITEM_NAME("Confite Estrella")),
        .price = 500 * TREASURE_FACTOR,
        .description = ES(COMPOUND_STRING("A star-shaped\n"
            "sweet. When held by\n"
            "Milcery, it's happy."), COMPOUND_STRING("Dulce de estrella.\n" "Si lo lleva Milcery,\n" "se alegra.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_StarSweet,
        .iconPalette = gItemIconPalette_StarSweet,
    },

    [ITEM_RIBBON_SWEET] =
    {
        .name = ES(ITEM_NAME("Ribbon Sweet"), ITEM_NAME("Confite Lazo")),
        .price = 500 * TREASURE_FACTOR,
        .description = ES(COMPOUND_STRING("A ribbon-shaped\n"
            "sweet. When held by\n"
            "Milcery, it's happy."), COMPOUND_STRING("Dulce de lazo. Si lo\n" "lleva Milcery, se\n" "alegra.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_RibbonSweet,
        .iconPalette = gItemIconPalette_RibbonSweet,
    },

    [ITEM_EVERSTONE] =
    {
        .name = ES(ITEM_NAME("Everstone"), ITEM_NAME("Piedra Eterna")),
        .price = (I_PRICE >= GEN_7) ? 3000 : 200,
        .holdEffect = HOLD_EFFECT_PREVENT_EVOLVE,
        .description = ES(COMPOUND_STRING("A wondrous hold\n"
            "item that prevents\n"
            "evolution."), COMPOUND_STRING("El Pokémon que lleva\n" "esta piedra mágica\n" "no evoluciona.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Everstone,
        .iconPalette = gItemIconPalette_Everstone,
    },

// Nectars

    [ITEM_RED_NECTAR] =
    {
        .name = ES(ITEM_NAME("Red Nectar"), ITEM_NAME("Néctar Rojo")),
        .price = 300,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Flower nectar that\n"
            "changes the form\n"
            "of certain Pokémon."), COMPOUND_STRING("Néctar que cambia la\n" "forma de cierto\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NECTAR,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange_ConsumedOnUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Nectar,
        .iconPalette = gItemIconPalette_RedNectar,
    },

    [ITEM_YELLOW_NECTAR] =
    {
        .name = ES(ITEM_NAME("Yellow Nectar"), ITEM_NAME("Néctar Amarillo")),
        .price = 300,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Flower nectar that\n"
            "changes the form\n"
            "of certain Pokémon."), COMPOUND_STRING("Néctar que cambia la\n" "forma de cierto\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NECTAR,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange_ConsumedOnUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Nectar,
        .iconPalette = gItemIconPalette_YellowNectar,
    },

    [ITEM_PINK_NECTAR] =
    {
        .name = ES(ITEM_NAME("Pink Nectar"), ITEM_NAME("Néctar Rosa")),
        .price = 300,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Flower nectar that\n"
            "changes the form\n"
            "of certain Pokémon."), COMPOUND_STRING("Néctar que cambia la\n" "forma de cierto\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NECTAR,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange_ConsumedOnUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Nectar,
        .iconPalette = gItemIconPalette_PinkNectar,
    },

    [ITEM_PURPLE_NECTAR] =
    {
        .name = ES(ITEM_NAME("Purple Nectar"), ITEM_NAME("Néctar Violeta")),
        .price = 300,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Flower nectar that\n"
            "changes the form\n"
            "of certain Pokémon."), COMPOUND_STRING("Néctar que cambia la\n" "forma de cierto\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NECTAR,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange_ConsumedOnUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Nectar,
        .iconPalette = gItemIconPalette_PurpleNectar,
    },

// Plates

    [ITEM_FLAME_PLATE] =
    {
        .name = ES(ITEM_NAME("Flame Plate"), ITEM_NAME("Tabla Llama")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Fire-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Fuego.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIRE,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_FlamePlate,
    },

    [ITEM_SPLASH_PLATE] =
    {
        .name = ES(ITEM_NAME("Splash Plate"), ITEM_NAME("Tabla Linfa")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Water-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Agua.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_SplashPlate,
    },

    [ITEM_ZAP_PLATE] =
    {
        .name = ES(ITEM_NAME("Zap Plate"), ITEM_NAME("Tabla Trueno")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "boosts Electric-\n"
            "type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Eléctrico.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ELECTRIC,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_ZapPlate,
    },

    [ITEM_MEADOW_PLATE] =
    {
        .name = ES(ITEM_NAME("Meadow Plate"), ITEM_NAME("Tabla Pradal")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Grass-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Planta.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GRASS,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_MeadowPlate,
    },

    [ITEM_ICICLE_PLATE] =
    {
        .name = ES(ITEM_NAME("Icicle Plate"), ITEM_NAME("Tabla Helada")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Ice-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Hielo.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ICE,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_IciclePlate,
    },

    [ITEM_FIST_PLATE] =
    {
        .name = ES(ITEM_NAME("Fist Plate"), ITEM_NAME("Tabla Fuerte")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "boosts Fighting-\n"
            "type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Lucha.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIGHTING,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_FistPlate,
    },

    [ITEM_TOXIC_PLATE] =
    {
        .name = ES(ITEM_NAME("Toxic Plate"), ITEM_NAME("Tabla Tóxica")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Poison-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Veneno.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_POISON,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_ToxicPlate,
    },

    [ITEM_EARTH_PLATE] =
    {
        .name = ES(ITEM_NAME("Earth Plate"), ITEM_NAME("Tabla Terrax")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Ground-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Tierra.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GROUND,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_EarthPlate,
    },

    [ITEM_SKY_PLATE] =
    {
        .name = ES(ITEM_NAME("Sky Plate"), ITEM_NAME("Tabla Cielo")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Flying-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Volador.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FLYING,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_SkyPlate,
    },

    [ITEM_MIND_PLATE] =
    {
        .name = ES(ITEM_NAME("Mind Plate"), ITEM_NAME("Tabla Mental")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "boosts Psychic-\n"
            "type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Psíquico.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_PSYCHIC,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_MindPlate,
    },

    [ITEM_INSECT_PLATE] =
    {
        .name = ES(ITEM_NAME("Insect Plate"), ITEM_NAME("Tabla Bicho")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Bug-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Bicho.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_BUG,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_InsectPlate,
    },

    [ITEM_STONE_PLATE] =
    {
        .name = ES(ITEM_NAME("Stone Plate"), ITEM_NAME("Tabla Pétrea")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Rock-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Roca.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ROCK,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_StonePlate,
    },

    [ITEM_SPOOKY_PLATE] =
    {
        .name = ES(ITEM_NAME("Spooky Plate"), ITEM_NAME("Tabla Terror")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Ghost-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Fantasma.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GHOST,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_SpookyPlate,
    },

    [ITEM_DRACO_PLATE] =
    {
        .name = ES(ITEM_NAME("Draco Plate"), ITEM_NAME("Tabla Draco")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Dragon-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Dragón.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DRAGON,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_DracoPlate,
    },

    [ITEM_DREAD_PLATE] =
    {
        .name = ES(ITEM_NAME("Dread Plate"), ITEM_NAME("Tabla Oscura")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Dark-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Siniestro.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DARK,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_DreadPlate,
    },

    [ITEM_IRON_PLATE] =
    {
        .name = ES(ITEM_NAME("Iron Plate"), ITEM_NAME("Tabla Acero")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Steel-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Acero.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_STEEL,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_IronPlate,
    },

    [ITEM_PIXIE_PLATE] =
    {
        .name = ES(ITEM_NAME("Pixie Plate"), ITEM_NAME("Tabla Duende")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Fairy-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Hada.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FAIRY,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_PixiePlate,
    },

// Drives

    [ITEM_DOUSE_DRIVE] =
    {
        .name = ES(ITEM_NAME("Douse Drive"), ITEM_NAME("HidroROM")),
        .price = (I_PRICE >= GEN_7) ? 0 : 1000,
        .holdEffect = HOLD_EFFECT_DRIVE,
        .description = ES(COMPOUND_STRING("Changes Techno\n"
            "Blast to a\n"
            "Water-type move."), COMPOUND_STRING("Tecno Shock pasa a\n" "ser de tipo Agua.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_DRIVE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .flingPower = 70,
        .iconPic = gItemIcon_Drive,
        .iconPalette = gItemIconPalette_DouseDrive,
    },

    [ITEM_SHOCK_DRIVE] =
    {
        .name = ES(ITEM_NAME("Shock Drive"), ITEM_NAME("FulgoROM")),
        .price = (I_PRICE >= GEN_7) ? 0 : 1000,
        .holdEffect = HOLD_EFFECT_DRIVE,
        .description = ES(COMPOUND_STRING("Changes Techno\n"
            "Blast to an\n"
            "Electric move."), COMPOUND_STRING("Chocolatina de sabor\n" "dulce. Restaura 20\n" "PS de un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_DRIVE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ELECTRIC,
        .flingPower = 70,
        .iconPic = gItemIcon_Drive,
        .iconPalette = gItemIconPalette_ShockDrive,
    },

    [ITEM_BURN_DRIVE] =
    {
        .name = ES(ITEM_NAME("Burn Drive"), ITEM_NAME("PiroROM")),
        .price = (I_PRICE >= GEN_7) ? 0 : 1000,
        .holdEffect = HOLD_EFFECT_DRIVE,
        .description = ES(COMPOUND_STRING("Changes Techno\n"
            "Blast to a\n"
            "Fire-type move."), COMPOUND_STRING("Tecno Shock pasa a\n" "ser de tipo Fuego.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_DRIVE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIRE,
        .flingPower = 70,
        .iconPic = gItemIcon_Drive,
        .iconPalette = gItemIconPalette_BurnDrive,
    },

    [ITEM_CHILL_DRIVE] =
    {
        .name = ES(ITEM_NAME("Chill Drive"), ITEM_NAME("CrioROM")),
        .price = (I_PRICE >= GEN_7) ? 0 : 1000,
        .holdEffect = HOLD_EFFECT_DRIVE,
        .description = ES(COMPOUND_STRING("Changes Techno\n"
            "Blast to an\n"
            "Ice-type move."), COMPOUND_STRING("Tecno Shock pasa a\n" "ser de tipo Hielo.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_DRIVE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ICE,
        .flingPower = 70,
        .iconPic = gItemIcon_Drive,
        .iconPalette = gItemIconPalette_ChillDrive,
    },

// Memories

    [ITEM_FIRE_MEMORY] =
    {
        .name = ES(ITEM_NAME("Fire Memory"), ITEM_NAME("Disco Fuego")),
        .pluralName = ITEM_PLURAL_NAME("Fire Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Contains Fire-\n"
            "type data. Changes\n"
            "Silvally's type."), COMPOUND_STRING("Datos de tipo Fuego.\n" "Cambia el tipo de\n" "Silvally.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIRE,
        .flingPower = 50,
        .iconPic = gItemIcon_FireMemory,
        .iconPalette = gItemIconPalette_FireMemory,
    },

    [ITEM_WATER_MEMORY] =
    {
        .name = ES(ITEM_NAME("Water Memory"), ITEM_NAME("Disco Agua")),
        .pluralName = ITEM_PLURAL_NAME("Water Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Contains Water-\n"
            "type data. Changes\n"
            "Silvally's type."), COMPOUND_STRING("Datos de tipo Agua.\n" "Cambia el tipo de\n" "Silvally.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .flingPower = 50,
        .iconPic = gItemIcon_WaterMemory,
        .iconPalette = gItemIconPalette_WaterMemory,
    },

    [ITEM_ELECTRIC_MEMORY] =
    {
        .name = ES(ITEM_NAME("Electric Memory"), ITEM_NAME("Disco Eléctrico")),
        .pluralName = ITEM_PLURAL_NAME("Electric Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Contains Electric-\n"
            "type data. Changes\n"
            "Silvally's type."), COMPOUND_STRING("Datos de tipo\n" "Eléctrico. Cambia el\n" "tipo de Silvally.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ELECTRIC,
        .flingPower = 50,
        .iconPic = gItemIcon_ElectricMemory,
        .iconPalette = gItemIconPalette_ElectricMemory,
    },

    [ITEM_GRASS_MEMORY] =
    {
        .name = ES(ITEM_NAME("Grass Memory"), ITEM_NAME("Disco Planta")),
        .pluralName = ITEM_PLURAL_NAME("Grass Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Contains Grass-\n"
            "type data. Changes\n"
            "Silvally's type."), COMPOUND_STRING("Datos de tipo\n" "Planta. Cambia el\n" "tipo de Silvally.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GRASS,
        .flingPower = 50,
        .iconPic = gItemIcon_GrassMemory,
        .iconPalette = gItemIconPalette_GrassMemory,
    },

    [ITEM_ICE_MEMORY] =
    {
        .name = ES(ITEM_NAME("Ice Memory"), ITEM_NAME("Disco Hielo")),
        .pluralName = ITEM_PLURAL_NAME("Ice Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Contains Ice-\n"
            "type data. Changes\n"
            "Silvally's type."), COMPOUND_STRING("Datos de tipo Hielo.\n" "Cambia el tipo de\n" "Silvally.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ICE,
        .flingPower = 50,
        .iconPic = gItemIcon_IceMemory,
        .iconPalette = gItemIconPalette_IceMemory,
    },

    [ITEM_FIGHTING_MEMORY] =
    {
        .name = ES(ITEM_NAME("Fighting Memory"), ITEM_NAME("Disco Lucha")),
        .pluralName = ITEM_PLURAL_NAME("Fighting Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Contains Fighting-\n"
            "type data. Changes\n"
            "Silvally's type."), COMPOUND_STRING("Datos de tipo Lucha.\n" "Cambia el tipo de\n" "Silvally.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIGHTING,
        .flingPower = 50,
        .iconPic = gItemIcon_FightingMemory,
        .iconPalette = gItemIconPalette_FightingMemory,
    },

    [ITEM_POISON_MEMORY] =
    {
        .name = ES(ITEM_NAME("Poison Memory"), ITEM_NAME("Disco Veneno")),
        .pluralName = ITEM_PLURAL_NAME("Poison Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Contains Poison-\n"
            "type data. Changes\n"
            "Silvally's type."), COMPOUND_STRING("Datos de tipo\n" "Veneno. Cambia el\n" "tipo de Silvally.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_POISON,
        .flingPower = 50,
        .iconPic = gItemIcon_PoisonMemory,
        .iconPalette = gItemIconPalette_PoisonMemory,
    },

    [ITEM_GROUND_MEMORY] =
    {
        .name = ES(ITEM_NAME("Ground Memory"), ITEM_NAME("Disco Tierra")),
        .pluralName = ITEM_PLURAL_NAME("Ground Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Contains Ground-\n"
            "type data. Changes\n"
            "Silvally's type."), COMPOUND_STRING("Datos de tipo\n" "Tierra. Cambia el\n" "tipo de Silvally.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GROUND,
        .flingPower = 50,
        .iconPic = gItemIcon_GroundMemory,
        .iconPalette = gItemIconPalette_GroundMemory,
    },

    [ITEM_FLYING_MEMORY] =
    {
        .name = ES(ITEM_NAME("Flying Memory"), ITEM_NAME("Disco Volador")),
        .pluralName = ITEM_PLURAL_NAME("Flying Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Contains Flying-\n"
            "type data. Changes\n"
            "Silvally's type."), COMPOUND_STRING("Datos de tipo\n" "Volador. Cambia el\n" "tipo de Silvally.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FLYING,
        .flingPower = 50,
        .iconPic = gItemIcon_FlyingMemory,
        .iconPalette = gItemIconPalette_FlyingMemory,
    },

    [ITEM_PSYCHIC_MEMORY] =
    {
        .name = ES(ITEM_NAME("Psychic Memory"), ITEM_NAME("Disco Psíquico")),
        .pluralName = ITEM_PLURAL_NAME("Psychic Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Contains Psychic-\n"
            "type data. Changes\n"
            "Silvally's type."), COMPOUND_STRING("Datos de tipo\n" "Psíquico. Cambia el\n" "tipo de Silvally.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_PSYCHIC,
        .flingPower = 50,
        .iconPic = gItemIcon_PsychicMemory,
        .iconPalette = gItemIconPalette_PsychicMemory,
    },

    [ITEM_BUG_MEMORY] =
    {
        .name = ES(ITEM_NAME("Bug Memory"), ITEM_NAME("Disco Bicho")),
        .pluralName = ITEM_PLURAL_NAME("Bug Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Contains Bug-\n"
            "type data. Changes\n"
            "Silvally's type."), COMPOUND_STRING("Datos de tipo Bicho.\n" "Cambia el tipo de\n" "Silvally.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_BUG,
        .flingPower = 50,
        .iconPic = gItemIcon_BugMemory,
        .iconPalette = gItemIconPalette_BugMemory,
    },

    [ITEM_ROCK_MEMORY] =
    {
        .name = ES(ITEM_NAME("Rock Memory"), ITEM_NAME("Disco Roca")),
        .pluralName = ITEM_PLURAL_NAME("Rock Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Contains Rock-\n"
            "type data. Changes\n"
            "Silvally's type."), COMPOUND_STRING("Datos de tipo Roca.\n" "Cambia el tipo de\n" "Silvally.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ROCK,
        .flingPower = 50,
        .iconPic = gItemIcon_RockMemory,
        .iconPalette = gItemIconPalette_RockMemory,
    },

    [ITEM_GHOST_MEMORY] =
    {
        .name = ES(ITEM_NAME("Ghost Memory"), ITEM_NAME("Disco Fantasma")),
        .pluralName = ITEM_PLURAL_NAME("Ghost Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Contains Ghost-\n"
            "type data. Changes\n"
            "Silvally's type."), COMPOUND_STRING("Datos de tipo\n" "Fantasma. Cambia el\n" "tipo de Silvally.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GHOST,
        .flingPower = 50,
        .iconPic = gItemIcon_GhostMemory,
        .iconPalette = gItemIconPalette_GhostMemory,
    },

    [ITEM_DRAGON_MEMORY] =
    {
        .name = ES(ITEM_NAME("Dragon Memory"), ITEM_NAME("Disco Dragón")),
        .pluralName = ITEM_PLURAL_NAME("Dragon Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Contains Dragon-\n"
            "type data. Changes\n"
            "Silvally's type."), COMPOUND_STRING("Datos de tipo\n" "Dragón. Cambia el\n" "tipo de Silvally.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DRAGON,
        .flingPower = 50,
        .iconPic = gItemIcon_DragonMemory,
        .iconPalette = gItemIconPalette_DragonMemory,
    },

    [ITEM_DARK_MEMORY] =
    {
        .name = ES(ITEM_NAME("Dark Memory"), ITEM_NAME("Disco Siniestro")),
        .pluralName = ITEM_PLURAL_NAME("Dark Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Contains Dark-\n"
            "type data. Changes\n"
            "Silvally's type."), COMPOUND_STRING("Datos de tipo\n" "Siniestro. Cambia el\n" "tipo de Silvally.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DARK,
        .flingPower = 50,
        .iconPic = gItemIcon_DarkMemory,
        .iconPalette = gItemIconPalette_DarkMemory,
    },

    [ITEM_STEEL_MEMORY] =
    {
        .name = ES(ITEM_NAME("Steel Memory"), ITEM_NAME("Disco Acero")),
        .pluralName = ITEM_PLURAL_NAME("Steel Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Contains Steel-\n"
            "type data. Changes\n"
            "Silvally's type."), COMPOUND_STRING("Datos de tipo Acero.\n" "Cambia el tipo de\n" "Silvally.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_STEEL,
        .flingPower = 50,
        .iconPic = gItemIcon_SteelMemory,
        .iconPalette = gItemIconPalette_SteelMemory,
    },

    [ITEM_FAIRY_MEMORY] =
    {
        .name = ES(ITEM_NAME("Fairy Memory"), ITEM_NAME("Disco Hada")),
        .pluralName = ITEM_PLURAL_NAME("Fairy Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Contains Fairy-\n"
            "type data. Changes\n"
            "Silvally's type."), COMPOUND_STRING("Datos de tipo Hada.\n" "Cambia el tipo de\n" "Silvally.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FAIRY,
        .flingPower = 50,
        .iconPic = gItemIcon_FairyMemory,
        .iconPalette = gItemIconPalette_FairyMemory,
    },

    [ITEM_RUSTED_SWORD] =
    {
        .name = ES(ITEM_NAME("Rusted Sword"), ITEM_NAME("Espada Oxidada")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A hero used this\n"
            "sword to halt a\n"
            "terrible disaster."), COMPOUND_STRING("Un héroe usó esta\n" "espada para frenar\n" "un desastre.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_RustedSword,
        .iconPalette = gItemIconPalette_RustedWeapons,
    },

    [ITEM_RUSTED_SHIELD] =
    {
        .name = ES(ITEM_NAME("Rusted Shield"), ITEM_NAME("Escudo Oxidado")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A hero used this\n"
            "shield to halt a\n"
            "terrible disaster."), COMPOUND_STRING("Un héroe usó este\n" "escudo para frenar\n" "un desastre.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_RustedShield,
        .iconPalette = gItemIconPalette_RustedWeapons,
    },

// Colored orbs

    [ITEM_RED_ORB] =
    {
        .name = ES(ITEM_NAME("Red Orb"), ITEM_NAME("Prisma Rojo")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_PRIMAL_ORB,
        .description = ES(COMPOUND_STRING("A red, glowing orb\n"
            "said to contain an\n"
            "ancient power."), COMPOUND_STRING("Un orbe rojo\n" "brillante con un\n" "poder ancestral.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_RedOrb,
        .iconPalette = gItemIconPalette_RedOrb,
    },

    [ITEM_BLUE_ORB] =
    {
        .name = ES(ITEM_NAME("Blue Orb"), ITEM_NAME("Prisma Azul")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_PRIMAL_ORB,
        .description = ES(COMPOUND_STRING("A blue, glowing orb\n"
            "said to contain an\n"
            "ancient power."), COMPOUND_STRING("Un orbe azul\n" "brillante con un\n" "poder ancestral.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_BlueOrb,
        .iconPalette = gItemIconPalette_BlueOrb,
    },

// Mega Stones

    [ITEM_VENUSAURITE] =
    {
        .name = ES(ITEM_NAME("Venusaurite"), ITEM_NAME("Venusaurita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Venusaur to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Venusaur.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Venusaurite,
        .iconPalette = gItemIconPalette_Venusaurite,
    },

    [ITEM_CHARIZARDITE_X] =
    {
        .name = ES(ITEM_NAME("Charizardite X"), ITEM_NAME("Charizardita X")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Charizard to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Charizard.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_CharizarditeX,
        .iconPalette = gItemIconPalette_CharizarditeX,
    },

    [ITEM_CHARIZARDITE_Y] =
    {
        .name = ES(ITEM_NAME("Charizardite Y"), ITEM_NAME("Charizardita Y")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Charizard to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Charizard.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_CharizarditeY,
        .iconPalette = gItemIconPalette_CharizarditeY,
    },

    [ITEM_BLASTOISINITE] =
    {
        .name = ES(ITEM_NAME("Blastoisinite"), ITEM_NAME("Blastoisita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Blastoise to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Blastoise.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Blastoisinite,
        .iconPalette = gItemIconPalette_Blastoisinite,
    },

    [ITEM_BEEDRILLITE] =
    {
        .name = ES(ITEM_NAME("Beedrillite"), ITEM_NAME("Beedrillita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Beedrill to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Beedrill.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Beedrillite,
        .iconPalette = gItemIconPalette_Beedrillite,
    },

    [ITEM_PIDGEOTITE] =
    {
        .name = ES(ITEM_NAME("Pidgeotite"), ITEM_NAME("Pidgeotita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Pidgeot to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Pidgeot.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Pidgeotite,
        .iconPalette = gItemIconPalette_Pidgeotite,
    },

    [ITEM_ALAKAZITE] =
    {
        .name = ES(ITEM_NAME("Alakazite"), ITEM_NAME("Alakazamita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Alakazam to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Alakazam.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Alakazite,
        .iconPalette = gItemIconPalette_Alakazite,
    },

    [ITEM_SLOWBRONITE] =
    {
        .name = ES(ITEM_NAME("Slowbronite"), ITEM_NAME("Slowbronita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Slowbro to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Slowbro.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Slowbronite,
        .iconPalette = gItemIconPalette_Slowbronite,
    },

    [ITEM_GENGARITE] =
    {
        .name = ES(ITEM_NAME("Gengarite"), ITEM_NAME("Gengarita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Gengar to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Gengar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Gengarite,
        .iconPalette = gItemIconPalette_Gengarite,
    },

    [ITEM_KANGASKHANITE] =
    {
        .name = ES(ITEM_NAME("Kangaskhanite"), ITEM_NAME("Kangaskhanita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Kangaskhan to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Kangaskhan.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Kangaskhanite,
        .iconPalette = gItemIconPalette_Kangaskhanite,
    },

    [ITEM_PINSIRITE] =
    {
        .name = ES(ITEM_NAME("Pinsirite"), ITEM_NAME("Pinsirita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Pinsir to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Pinsir.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Pinsirite,
        .iconPalette = gItemIconPalette_Pinsirite,
    },

    [ITEM_GYARADOSITE] =
    {
        .name = ES(ITEM_NAME("Gyaradosite"), ITEM_NAME("Gyaradosita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Gyarados to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Gyarados.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Gyaradosite,
        .iconPalette = gItemIconPalette_Gyaradosite,
    },

    [ITEM_AERODACTYLITE] =
    {
        .name = ES(ITEM_NAME("Aerodactylite"), ITEM_NAME("Aerodactylita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Aerodactyl to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Aerodactyl.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Aerodactylite,
        .iconPalette = gItemIconPalette_Aerodactylite,
    },

    [ITEM_MEWTWONITE_X] =
    {
        .name = ES(ITEM_NAME("Mewtwonite X"), ITEM_NAME("Mewtwoita X")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Mewtwo to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Mewtwo.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_MewtwoniteX,
        .iconPalette = gItemIconPalette_MewtwoniteX,
    },

    [ITEM_MEWTWONITE_Y] =
    {
        .name = ES(ITEM_NAME("Mewtwonite Y"), ITEM_NAME("Mewtwoita Y")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Mewtwo to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Mewtwo.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_MewtwoniteY,
        .iconPalette = gItemIconPalette_MewtwoniteY,
    },

    [ITEM_AMPHAROSITE] =
    {
        .name = ES(ITEM_NAME("Ampharosite"), ITEM_NAME("Ampharosita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Ampharos to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Ampharos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Ampharosite,
        .iconPalette = gItemIconPalette_Ampharosite,
    },

    [ITEM_STEELIXITE] =
    {
        .name = ES(ITEM_NAME("Steelixite"), ITEM_NAME("Steelixita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Steelix to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Steelix.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Steelixite,
        .iconPalette = gItemIconPalette_Steelixite,
    },

    [ITEM_SCIZORITE] =
    {
        .name = ES(ITEM_NAME("Scizorite"), ITEM_NAME("Scizorita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Scizor to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Scizor.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Scizorite,
        .iconPalette = gItemIconPalette_Scizorite,
    },

    [ITEM_HERACRONITE] =
    {
        .name = ES(ITEM_NAME("Heracronite"), ITEM_NAME("Heracrossita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Heracross to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Heracross.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Heracronite,
        .iconPalette = gItemIconPalette_Heracronite,
    },

    [ITEM_HOUNDOOMINITE] =
    {
        .name = ES(ITEM_NAME("Houndoominite"), ITEM_NAME("Houndoomita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Houndoom to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Houndoom.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Houndoominite,
        .iconPalette = gItemIconPalette_Houndoominite,
    },

    [ITEM_TYRANITARITE] =
    {
        .name = ES(ITEM_NAME("Tyranitarite"), ITEM_NAME("Tyranitarita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Tyranitar to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Tyranitar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Tyranitarite,
        .iconPalette = gItemIconPalette_Tyranitarite,
    },

    [ITEM_SCEPTILITE] =
    {
        .name = ES(ITEM_NAME("Sceptilite"), ITEM_NAME("Sceptilita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Sceptile to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Sceptile.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Sceptilite,
        .iconPalette = gItemIconPalette_Sceptilite,
    },

    [ITEM_BLAZIKENITE] =
    {
        .name = ES(ITEM_NAME("Blazikenite"), ITEM_NAME("Blazikenita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Blaziken to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Blaziken.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Blazikenite,
        .iconPalette = gItemIconPalette_Blazikenite,
    },

    [ITEM_SWAMPERTITE] =
    {
        .name = ES(ITEM_NAME("Swampertite"), ITEM_NAME("Swampertita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Swampert to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Swampert.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Swampertite,
        .iconPalette = gItemIconPalette_Swampertite,
    },

    [ITEM_GARDEVOIRITE] =
    {
        .name = ES(ITEM_NAME("Gardevoirite"), ITEM_NAME("Gardevoirita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Gardevoir to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Gardevoir.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Gardevoirite,
        .iconPalette = gItemIconPalette_Gardevoirite,
    },

    [ITEM_SABLENITE] =
    {
        .name = ES(ITEM_NAME("Sablenite"), ITEM_NAME("Sableynita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Sableye to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Sableye.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Sablenite,
        .iconPalette = gItemIconPalette_Sablenite,
    },

    [ITEM_MAWILITE] =
    {
        .name = ES(ITEM_NAME("Mawilite"), ITEM_NAME("Mawilita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Mawile to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Mawile.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Mawilite,
        .iconPalette = gItemIconPalette_Mawilite,
    },

    [ITEM_AGGRONITE] =
    {
        .name = ES(ITEM_NAME("Aggronite"), ITEM_NAME("Aggronita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Aggron to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Aggron.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Aggronite,
        .iconPalette = gItemIconPalette_Aggronite,
    },

    [ITEM_MEDICHAMITE] =
    {
        .name = ES(ITEM_NAME("Medichamite"), ITEM_NAME("Medichamita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Medicham to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Medicham.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Medichamite,
        .iconPalette = gItemIconPalette_Medichamite,
    },

    [ITEM_MANECTITE] =
    {
        .name = ES(ITEM_NAME("Manectite"), ITEM_NAME("Manectricita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Manectric to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Manectric.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Manectite,
        .iconPalette = gItemIconPalette_Manectite,
    },

    [ITEM_SHARPEDONITE] =
    {
        .name = ES(ITEM_NAME("Sharpedonite"), ITEM_NAME("Sharpedonita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Sharpedo to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Sharpedo.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Sharpedonite,
        .iconPalette = gItemIconPalette_Sharpedonite,
    },

    [ITEM_CAMERUPTITE] =
    {
        .name = ES(ITEM_NAME("Cameruptite"), ITEM_NAME("Cameruptita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Camerupt to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Camerupt.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Cameruptite,
        .iconPalette = gItemIconPalette_Cameruptite,
    },

    [ITEM_ALTARIANITE] =
    {
        .name = ES(ITEM_NAME("Altarianite"), ITEM_NAME("Altarianita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Altaria to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Altaria.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Altarianite,
        .iconPalette = gItemIconPalette_Altarianite,
    },

    [ITEM_BANETTITE] =
    {
        .name = ES(ITEM_NAME("Banettite"), ITEM_NAME("Banettita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Banette to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Banette.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Banettite,
        .iconPalette = gItemIconPalette_Banettite,
    },

    [ITEM_ABSOLITE] =
    {
        .name = ES(ITEM_NAME("Absolite"), ITEM_NAME("Absolita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Absol to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Absol.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Absolite,
        .iconPalette = gItemIconPalette_Absolite,
    },

    [ITEM_GLALITITE] =
    {
        .name = ES(ITEM_NAME("Glalitite"), ITEM_NAME("Glalita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Glalie to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Glalie.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Glalitite,
        .iconPalette = gItemIconPalette_Glalitite,
    },

    [ITEM_SALAMENCITE] =
    {
        .name = ES(ITEM_NAME("Salamencite"), ITEM_NAME("Salamencita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Salamence to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Salamence.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Salamencite,
        .iconPalette = gItemIconPalette_Salamencite,
    },

    [ITEM_METAGROSSITE] =
    {
        .name = ES(ITEM_NAME("Metagrossite"), ITEM_NAME("Metagrossita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Metagross to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Metagross.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Metagrossite,
        .iconPalette = gItemIconPalette_Metagrossite,
    },

    [ITEM_LATIASITE] =
    {
        .name = ES(ITEM_NAME("Latiasite"), ITEM_NAME("Latiasita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Latias to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Latias.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Latiasite,
        .iconPalette = gItemIconPalette_Latiasite,
    },

    [ITEM_LATIOSITE] =
    {
        .name = ES(ITEM_NAME("Latiosite"), ITEM_NAME("Latiosita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Latios to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Latios.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Latiosite,
        .iconPalette = gItemIconPalette_Latiosite,
    },

    [ITEM_LOPUNNITE] =
    {
        .name = ES(ITEM_NAME("Lopunnite"), ITEM_NAME("Lopunnita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Lopunny to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Lopunny.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Lopunnite,
        .iconPalette = gItemIconPalette_Lopunnite,
    },

    [ITEM_GARCHOMPITE] =
    {
        .name = ES(ITEM_NAME("Garchompite"), ITEM_NAME("Garchompita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Garchomp to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Garchomp.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Garchompite,
        .iconPalette = gItemIconPalette_Garchompite,
    },

    [ITEM_LUCARIONITE] =
    {
        .name = ES(ITEM_NAME("Lucarionite"), ITEM_NAME("Lucarita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Lucario to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Lucario.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Lucarionite,
        .iconPalette = gItemIconPalette_Lucarionite,
    },

    [ITEM_ABOMASITE] =
    {
        .name = ES(ITEM_NAME("Abomasite"), ITEM_NAME("Abomasnowita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Abomasnow to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Inflige daño a los\n" "oponentes con una\n" "potente luz.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Abomasite,
        .iconPalette = gItemIconPalette_Abomasite,
    },

    [ITEM_GALLADITE] =
    {
        .name = ES(ITEM_NAME("Galladite"), ITEM_NAME("Galladita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Gallade to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Gallade.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Galladite,
        .iconPalette = gItemIconPalette_Galladite,
    },

    [ITEM_AUDINITE] =
    {
        .name = ES(ITEM_NAME("Audinite"), ITEM_NAME("Audinita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Audino to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Audino.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Audinite,
        .iconPalette = gItemIconPalette_Audinite,
    },

    [ITEM_DIANCITE] =
    {
        .name = ES(ITEM_NAME("Diancite"), ITEM_NAME("Diancita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Diancie to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Diancie.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Diancite,
        .iconPalette = gItemIconPalette_Diancite,
    },

    [ITEM_CLEFABLITE] =
    {
        .name = ES(ITEM_NAME("Clefablite"), ITEM_NAME("Clefablita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Clefable to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Clefable.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Clefablite,
        .iconPalette = gItemIconPalette_Clefablite,
    },

    [ITEM_VICTREEBELITE] =
    {
        .name = ES(ITEM_NAME("Victreebelite"), ITEM_NAME("Victreebelita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Victreebel to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Victreebel.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Victreebelite,
        .iconPalette = gItemIconPalette_Victreebelite,
    },

    [ITEM_STARMINITE] =
    {
        .name = ES(ITEM_NAME("Starminite"), ITEM_NAME("Starmita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Starmie to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Starmie.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Starminite,
        .iconPalette = gItemIconPalette_Starminite,
    },

    [ITEM_DRAGONINITE] =
    {
        .name = ES(ITEM_NAME("Dragoninite"), ITEM_NAME("Dragonitita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Dragonite to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Dragonite.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Dragoninite,
        .iconPalette = gItemIconPalette_Dragoninite,
    },

    [ITEM_MEGANIUMITE] =
    {
        .name = ES(ITEM_NAME("Meganiumite"), ITEM_NAME("Meganiumita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Meganium to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Meganium.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Meganiumite,
        .iconPalette = gItemIconPalette_Meganiumite,
    },

    [ITEM_FERALIGITE] =
    {
        .name = ES(ITEM_NAME("Feraligite"), ITEM_NAME("Feraligatrita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Feraligatr to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Feraligatr.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Feraligite,
        .iconPalette = gItemIconPalette_Feraligite,
    },

    [ITEM_SKARMORITE] =
    {
        .name = ES(ITEM_NAME("Skarmorite"), ITEM_NAME("Skarmorita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Skarmory to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Skarmory.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Skarmorite,
        .iconPalette = gItemIconPalette_Skarmorite,
    },

    [ITEM_FROSLASSITE] =
    {
        .name = ES(ITEM_NAME("Froslassite"), ITEM_NAME("Froslassita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Froslass to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Froslass.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Froslassite,
        .iconPalette = gItemIconPalette_Froslassite,
    },

    [ITEM_EMBOARITE] =
    {
        .name = ES(ITEM_NAME("Emboarite"), ITEM_NAME("Emboarita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Emboar to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Emboar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Emboarite,
        .iconPalette = gItemIconPalette_Emboarite,
    },

    [ITEM_EXCADRITE] =
    {
        .name = ES(ITEM_NAME("Excadrite"), ITEM_NAME("Excadrillita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Excadrill to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Excadrill.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Excadrite,
        .iconPalette = gItemIconPalette_Excadrite,
    },

    [ITEM_SCOLIPITE] =
    {
        .name = ES(ITEM_NAME("Scolipite"), ITEM_NAME("Scolipedita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Scolipede to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Scolipede.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Scolipite,
        .iconPalette = gItemIconPalette_Scolipite,
    },

    [ITEM_SCRAFTINITE] =
    {
        .name = ES(ITEM_NAME("Scraftinite"), ITEM_NAME("Scraftita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Scrafty to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Scrafty.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Scraftinite,
        .iconPalette = gItemIconPalette_Scraftinite,
    },

    [ITEM_EELEKTROSSITE] =
    {
        .name = ES(ITEM_NAME("Eelektrossite"), ITEM_NAME("Eelektrossita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Eelektross to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Eelektross.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Eelektrossite,
        .iconPalette = gItemIconPalette_Eelektrossite,
    },

    [ITEM_CHANDELURITE] =
    {
        .name = ES(ITEM_NAME("Chandelurite"), ITEM_NAME("Chandelurita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Chandelure to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Chandelure.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Chandelurite,
        .iconPalette = gItemIconPalette_Chandelurite,
    },

    [ITEM_CHESNAUGHTITE] =
    {
        .name = ES(ITEM_NAME("Chesnaughtite"), ITEM_NAME("Chesnaughtita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Chesnaught to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Chesnaught.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Chesnaughtite,
        .iconPalette = gItemIconPalette_Chesnaughtite,
    },

    [ITEM_DELPHOXITE] =
    {
        .name = ES(ITEM_NAME("Delphoxite"), ITEM_NAME("Delphoxita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Delphox to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Delphox.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Delphoxite,
        .iconPalette = gItemIconPalette_Delphoxite,
    },

    [ITEM_GRENINJITE] =
    {
        .name = ES(ITEM_NAME("Greninjite"), ITEM_NAME("Greninjanita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Greninja to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Greninja.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Greninjite,
        .iconPalette = gItemIconPalette_Greninjite,
    },

    [ITEM_PYROARITE] =
    {
        .name = ES(ITEM_NAME("Pyroarite"), ITEM_NAME("Pyroarita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Pyroar to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Pyroar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Pyroarite,
        .iconPalette = gItemIconPalette_Pyroarite,
    },

    [ITEM_FLOETTITE] =
    {
        .name = ES(ITEM_NAME("Floettite"), ITEM_NAME("Floettita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Floette to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Floette.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Floettite,
        .iconPalette = gItemIconPalette_Floettite,
    },

    [ITEM_MALAMARITE] =
    {
        .name = ES(ITEM_NAME("Malamarite"), ITEM_NAME("Malamarita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Malamar to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Malamar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Malamarite,
        .iconPalette = gItemIconPalette_Malamarite,
    },

    [ITEM_BARBARACITE] =
    {
        .name = ES(ITEM_NAME("Barbaracite"), ITEM_NAME("Barbaraclita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Barbaracle to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Barbaracle.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Barbaracite,
        .iconPalette = gItemIconPalette_Barbaracite,
    },

    [ITEM_DRAGALGITE] =
    {
        .name = ES(ITEM_NAME("Dragalgite"), ITEM_NAME("Dragalgita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Dragalge to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Dragalge.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Dragalgite,
        .iconPalette = gItemIconPalette_Dragalgite,
    },

    [ITEM_HAWLUCHANITE] =
    {
        .name = ES(ITEM_NAME("Hawluchanite"), ITEM_NAME("Hawluchanita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Hawlucha to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Hawlucha.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Hawluchanite,
        .iconPalette = gItemIconPalette_Hawluchanite,
    },

    [ITEM_ZYGARDITE] =
    {
        .name = ES(ITEM_NAME("Zygardite"), ITEM_NAME("Zygardita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Zygarde to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Zygarde.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Zygardite,
        .iconPalette = gItemIconPalette_Zygardite,
    },

    [ITEM_DRAMPANITE] =
    {
        .name = ES(ITEM_NAME("Drampanite"), ITEM_NAME("Drampanita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Drampa to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Drampa.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Drampanite,
        .iconPalette = gItemIconPalette_Drampanite,
    },

    [ITEM_FALINKSITE] =
    {
        .name = ES(ITEM_NAME("Falinksite"), ITEM_NAME("Falinksita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Falinks to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Falinks.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Falinksite,
        .iconPalette = gItemIconPalette_Falinksite,
    },

    [ITEM_HEATRANITE] =
    {
        .name = ES(ITEM_NAME("Heatranite"), ITEM_NAME("Heatranita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Heatran to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Heatran.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Heatranite,
        .iconPalette = gItemIconPalette_Heatranite,
    },

    [ITEM_DARKRANITE] =
    {
        .name = ES(ITEM_NAME("Darkranite"), ITEM_NAME("Darkrainita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Darkrai to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Darkrai.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Darkranite,
        .iconPalette = gItemIconPalette_Darkranite,
    },

    [ITEM_ZERAORITE] =
    {
        .name = ES(ITEM_NAME("Zeraorite"), ITEM_NAME("Zeraoranita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Zeraora to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Zeraora.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Zeraorite,
        .iconPalette = gItemIconPalette_Zeraorite,
    },

    [ITEM_RAICHUNITE_X] =
    {
        .name = ES(ITEM_NAME("Raichunite X"), ITEM_NAME("Raichunita X")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Raichu to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Raichu.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_RaichuniteX,
        .iconPalette = gItemIconPalette_RaichuniteX,
    },

    [ITEM_RAICHUNITE_Y] =
    {
        .name = ES(ITEM_NAME("Raichunite Y"), ITEM_NAME("Raichunita Y")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Raichu to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Raichu.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_RaichuniteY,
        .iconPalette = gItemIconPalette_RaichuniteY,
    },

    [ITEM_CHIMECHITE] =
    {
        .name = ES(ITEM_NAME("Chimechite"), ITEM_NAME("Chimechita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Chimecho to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Chimecho.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Chimechite,
        .iconPalette = gItemIconPalette_Chimechite,
    },

    [ITEM_ABSOLITE_Z] =
    {
        .name = ES(ITEM_NAME("Absolite Z"), ITEM_NAME("Absolita Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Absol to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Absol.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_AbsoliteZ,
        .iconPalette = gItemIconPalette_AbsoliteZ,
    },

    [ITEM_STARAPTITE] =
    {
        .name = ES(ITEM_NAME("Staraptite"), ITEM_NAME("Staraptorita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Staraptor to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Staraptor.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Staraptite,
        .iconPalette = gItemIconPalette_Staraptite,
    },

    [ITEM_GARCHOMPITE_Z] =
    {
        .name = ES(ITEM_NAME("Garchompite Z"), ITEM_NAME("Garchompita Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Garchomp to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Garchomp.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_GarchompiteZ,
        .iconPalette = gItemIconPalette_GarchompiteZ,
    },

    [ITEM_LUCARIONITE_Z] =
    {
        .name = ES(ITEM_NAME("Lucarionite Z"), ITEM_NAME("Lucarita Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Lucario to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Lucario.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_LucarioniteZ,
        .iconPalette = gItemIconPalette_LucarioniteZ,
    },

    [ITEM_GOLURKITE] =
    {
        .name = ES(ITEM_NAME("Golurkite"), ITEM_NAME("Golurkita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Golurk to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Golurk.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Golurkite,
        .iconPalette = gItemIconPalette_Golurkite,
    },

    [ITEM_MEOWSTICITE] =
    {
        .name = ES(ITEM_NAME("Meowsticite"), ITEM_NAME("Meowsticita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Meowstic to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Meowstic.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Meowsticite,
        .iconPalette = gItemIconPalette_Meowsticite,
    },

    [ITEM_CRABOMINITE] =
    {
        .name = ES(ITEM_NAME("Crabominite"), ITEM_NAME("Crabominablita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Crabominable to\n"
            "Mega in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Crabominable.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Crabominite,
        .iconPalette = gItemIconPalette_Crabominite,
    },

    [ITEM_GOLISOPITE] =
    {
        .name = ES(ITEM_NAME("Golisopite"), ITEM_NAME("Golisopodita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Golisopod to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Golisopod.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Golisopite,
        .iconPalette = gItemIconPalette_Golisopite,
    },

    [ITEM_MAGEARNITE] =
    {
        .name = ES(ITEM_NAME("Magearnite"), ITEM_NAME("Magearnita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Magearna to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Magearna.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Magearnite,
        .iconPalette = gItemIconPalette_Magearnite,
    },

    [ITEM_SCOVILLAINITE] =
    {
        .name = ES(ITEM_NAME("Scovillainite"), ITEM_NAME("Scovillainita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Scovillain to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Scovillain.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Scovillainite,
        .iconPalette = gItemIconPalette_Scovillainite,
    },

    [ITEM_BAXCALIBRITE] =
    {
        .name = ES(ITEM_NAME("Baxcalibrite"), ITEM_NAME("Baxcaliburita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Baxcalibur to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Baxcalibur.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Baxcalibrite,
        .iconPalette = gItemIconPalette_Baxcalibrite,
    },

    [ITEM_TATSUGIRINITE] =
    {
        .name = ES(ITEM_NAME("Tatsugirinite"), ITEM_NAME("Tatsugirita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Tatsugiri to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Tatsugiri.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Tatsugirinite,
        .iconPalette = gItemIconPalette_Tatsugirinite,
    },

    [ITEM_GLIMMORANITE] =
    {
        .name = ES(ITEM_NAME("Glimmoranite"), ITEM_NAME("Glimmoranita")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = ES(COMPOUND_STRING("This stone enables\n"
            "Glimmora to Mega\n"
            "Evolve in battle."), COMPOUND_STRING("Hace megaevolucionar\n" "a Glimmora.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Glimmoranite,
        .iconPalette = gItemIconPalette_Glimmoranite,
    },

// Gems
#if I_PRICE >= GEN_9
    #define GEM_PRICE 15000
#elif I_PRICE >= GEN_7
    #define GEM_PRICE 4000
#else
    #define GEM_PRICE 200
#endif

    [ITEM_NORMAL_GEM] =
    {
        .name = ES(ITEM_NAME("Normal Gem"), ITEM_NAME("Gema Normal")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of a Normal-\n"
            "type move once."), COMPOUND_STRING("Potencia una vez un\n" "movimiento de tipo\n" "Normal.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_NORMAL,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_NormalGem,
    },

    [ITEM_FIRE_GEM] =
    {
        .name = ES(ITEM_NAME("Fire Gem"), ITEM_NAME("Gema Fuego")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of a Fire-\n"
            "type move once."), COMPOUND_STRING("Pluma que aumenta un\n" "poco la Defensa de\n" "base de un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIRE,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_FireGem,
    },

    [ITEM_WATER_GEM] =
    {
        .name = ES(ITEM_NAME("Water Gem"), ITEM_NAME("Gema Agua")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of a Water-\n"
            "type move once."), COMPOUND_STRING("Potencia una vez un\n" "movimiento de tipo\n" "Agua.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_WaterGem,
    },

    [ITEM_ELECTRIC_GEM] =
    {
        .name = ES(ITEM_NAME("Electric Gem"), ITEM_NAME("Gema Eléctrica")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of an Electric-\n"
            "type move once."), COMPOUND_STRING("Potencia una vez un\n" "movimiento de tipo\n" "Eléctrico.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ELECTRIC,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_ElectricGem,
    },

    [ITEM_GRASS_GEM] =
    {
        .name = ES(ITEM_NAME("Grass Gem"), ITEM_NAME("Gema Planta")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of a Grass-\n"
            "type move once."), COMPOUND_STRING("Pluma que aumenta un\n" "poco la Velocidad de\n" "base de un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GRASS,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_GrassGem,
    },

    [ITEM_ICE_GEM] =
    {
        .name = ES(ITEM_NAME("Ice Gem"), ITEM_NAME("Gema Hielo")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of an Ice-\n"
            "type move once."), COMPOUND_STRING("Potencia una vez un\n" "movimiento de tipo\n" "Hielo.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ICE,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_IceGem,
    },

    [ITEM_FIGHTING_GEM] =
    {
        .name = ES(ITEM_NAME("Fighting Gem"), ITEM_NAME("Gema Lucha")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of a Fighting-\n"
            "type move once."), COMPOUND_STRING("Potencia una vez un\n" "movimiento de tipo\n" "Lucha.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIGHTING,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_FightingGem,
    },

    [ITEM_POISON_GEM] =
    {
        .name = ES(ITEM_NAME("Poison Gem"), ITEM_NAME("Gema Veneno")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of a Poison-\n"
            "type move once."), COMPOUND_STRING("Potencia una vez un\n" "movimiento de tipo\n" "Veneno.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_POISON,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_PoisonGem,
    },

    [ITEM_GROUND_GEM] =
    {
        .name = ES(ITEM_NAME("Ground Gem"), ITEM_NAME("Gema Tierra")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of a Ground-\n"
            "type move once."), COMPOUND_STRING("Potencia una vez un\n" "movimiento de tipo\n" "Tierra.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GROUND,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_GroundGem,
    },

    [ITEM_FLYING_GEM] =
    {
        .name = ES(ITEM_NAME("Flying Gem"), ITEM_NAME("Gema Voladora")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of a Flying-\n"
            "type move once."), COMPOUND_STRING("Potencia una vez un\n" "movimiento de tipo\n" "Volador.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FLYING,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_FlyingGem,
    },

    [ITEM_PSYCHIC_GEM] =
    {
        .name = ES(ITEM_NAME("Psychic Gem"), ITEM_NAME("Gema Psíquica")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of a Psychic-\n"
            "type move once."), COMPOUND_STRING("Potencia una vez un\n" "movimiento de tipo\n" "Psíquico.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_PSYCHIC,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_PsychicGem,
    },

    [ITEM_BUG_GEM] =
    {
        .name = ES(ITEM_NAME("Bug Gem"), ITEM_NAME("Gema Bicho")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of a Bug-\n"
            "type move once."), COMPOUND_STRING("Potencia una vez un\n" "movimiento de tipo\n" "Bicho.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_BUG,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_BugGem,
    },

    [ITEM_ROCK_GEM] =
    {
        .name = ES(ITEM_NAME("Rock Gem"), ITEM_NAME("Gema Roca")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of a Rock-\n"
            "type move once."), COMPOUND_STRING("Potencia una vez un\n" "movimiento de tipo\n" "Roca.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ROCK,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_RockGem,
    },

    [ITEM_GHOST_GEM] =
    {
        .name = ES(ITEM_NAME("Ghost Gem"), ITEM_NAME("Gema Fantasma")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of a Ghost-\n"
            "type move once."), COMPOUND_STRING("Potencia una vez un\n" "movimiento de tipo\n" "Fantasma.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GHOST,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_GhostGem,
    },

    [ITEM_DRAGON_GEM] =
    {
        .name = ES(ITEM_NAME("Dragon Gem"), ITEM_NAME("Gema Dragón")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of a Dragon-\n"
            "type move once."), COMPOUND_STRING("Potencia una vez un\n" "movimiento de tipo\n" "Dragón.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DRAGON,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_DragonGem,
    },

    [ITEM_DARK_GEM] =
    {
        .name = ES(ITEM_NAME("Dark Gem"), ITEM_NAME("Gema Siniestra")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of a Dark-\n"
            "type move once."), COMPOUND_STRING("Potencia una vez un\n" "movimiento de tipo\n" "Siniestro.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DARK,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_DarkGem,
    },

    [ITEM_STEEL_GEM] =
    {
        .name = ES(ITEM_NAME("Steel Gem"), ITEM_NAME("Gema Acero")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of a Steel-\n"
            "type move once."), COMPOUND_STRING("Potencia una vez un\n" "movimiento de tipo\n" "Acero.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_STEEL,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_SteelGem,
    },

    [ITEM_FAIRY_GEM] =
    {
        .name = ES(ITEM_NAME("Fairy Gem"), ITEM_NAME("Gema Hada")),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of a Fairy-\n"
            "type move once."), COMPOUND_STRING("Potencia una vez un\n" "movimiento de tipo\n" "Hada.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FAIRY,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_FairyGem,
    },

// Z-Crystals

    [ITEM_NORMALIUM_Z] =
    {
        .name = ES(ITEM_NAME("Normalium Z"), ITEM_NAME("Normastal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Normal-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Normal a mov.\n" "Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_NORMAL,
        .iconPic = gItemIcon_NormaliumZ,
        .iconPalette = gItemIconPalette_NormaliumZ,
    },

    [ITEM_FIRIUM_Z] =
    {
        .name = ES(ITEM_NAME("Firium Z"), ITEM_NAME("Pirostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Fire-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Fuego a mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIRE,
        .iconPic = gItemIcon_FiriumZ,
        .iconPalette = gItemIconPalette_FiriumZ,
    },

    [ITEM_WATERIUM_Z] =
    {
        .name = ES(ITEM_NAME("Waterium Z"), ITEM_NAME("Hidrostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Water-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Agua a mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .iconPic = gItemIcon_WateriumZ,
        .iconPalette = gItemIconPalette_WateriumZ,
    },

    [ITEM_ELECTRIUM_Z] =
    {
        .name = ES(ITEM_NAME("Electrium Z"), ITEM_NAME("Electrostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Electric-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Eléctrico a\n" "mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ELECTRIC,
        .iconPic = gItemIcon_ElectriumZ,
        .iconPalette = gItemIconPalette_ElectriumZ,
    },

    [ITEM_GRASSIUM_Z] =
    {
        .name = ES(ITEM_NAME("Grassium Z"), ITEM_NAME("Fitostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Grass-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Planta a mov.\n" "Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GRASS,
        .iconPic = gItemIcon_GrassiumZ,
        .iconPalette = gItemIconPalette_GrassiumZ,
    },

    [ITEM_ICIUM_Z] =
    {
        .name = ES(ITEM_NAME("Icium Z"), ITEM_NAME("Criostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Ice-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Hielo a mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ICE,
        .iconPic = gItemIcon_IciumZ,
        .iconPalette = gItemIconPalette_IciumZ,
    },

    [ITEM_FIGHTINIUM_Z] =
    {
        .name = ES(ITEM_NAME("Fightinium Z"), ITEM_NAME("Lizastal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Fighting-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Lucha a mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIGHTING,
        .iconPic = gItemIcon_FightiniumZ,
        .iconPalette = gItemIconPalette_FightiniumZ,
    },

    [ITEM_POISONIUM_Z] =
    {
        .name = ES(ITEM_NAME("Poisonium Z"), ITEM_NAME("Toxistal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Poison-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Veneno a mov.\n" "Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_POISON,
        .iconPic = gItemIcon_PoisoniumZ,
        .iconPalette = gItemIconPalette_PoisoniumZ,
    },

    [ITEM_GROUNDIUM_Z] =
    {
        .name = ES(ITEM_NAME("Groundium Z"), ITEM_NAME("Geostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Ground-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Tierra a mov.\n" "Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GROUND,
        .iconPic = gItemIcon_GroundiumZ,
        .iconPalette = gItemIconPalette_GroundiumZ,
    },

    [ITEM_FLYINIUM_Z] =
    {
        .name = ES(ITEM_NAME("Flyinium Z"), ITEM_NAME("Aerostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Flying-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Volador a mov.\n" "Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FLYING,
        .iconPic = gItemIcon_FlyiniumZ,
        .iconPalette = gItemIconPalette_FlyiniumZ,
    },

    [ITEM_PSYCHIUM_Z] =
    {
        .name = ES(ITEM_NAME("Psychium Z"), ITEM_NAME("Psicostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Psychic-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Psíquico a mov.\n" "Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_PSYCHIC,
        .iconPic = gItemIcon_PsychiumZ,
        .iconPalette = gItemIconPalette_PsychiumZ,
    },

    [ITEM_BUGINIUM_Z] =
    {
        .name = ES(ITEM_NAME("Buginium Z"), ITEM_NAME("Insectostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Bug-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Bicho a mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_BUG,
        .iconPic = gItemIcon_BuginiumZ,
        .iconPalette = gItemIconPalette_BuginiumZ,
    },

    [ITEM_ROCKIUM_Z] =
    {
        .name = ES(ITEM_NAME("Rockium Z"), ITEM_NAME("Litostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Rock-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Roca a mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ROCK,
        .iconPic = gItemIcon_RockiumZ,
        .iconPalette = gItemIconPalette_RockiumZ,
    },

    [ITEM_GHOSTIUM_Z] =
    {
        .name = ES(ITEM_NAME("Ghostium Z"), ITEM_NAME("Espectrostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Ghost-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Fantasma a mov.\n" "Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GHOST,
        .iconPic = gItemIcon_GhostiumZ,
        .iconPalette = gItemIconPalette_GhostiumZ,
    },

    [ITEM_DRAGONIUM_Z] =
    {
        .name = ES(ITEM_NAME("Dragonium Z"), ITEM_NAME("Dracostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Dragon-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Dragón a mov.\n" "Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DRAGON,
        .iconPic = gItemIcon_DragoniumZ,
        .iconPalette = gItemIconPalette_DragoniumZ,
    },

    [ITEM_DARKINIUM_Z] =
    {
        .name = ES(ITEM_NAME("Darkinium Z"), ITEM_NAME("Nictostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Dark-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Siniestro a\n" "mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DARK,
        .iconPic = gItemIcon_DarkiniumZ,
        .iconPalette = gItemIconPalette_DarkiniumZ,
    },

    [ITEM_STEELIUM_Z] =
    {
        .name = ES(ITEM_NAME("Steelium Z"), ITEM_NAME("Metalostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Steel-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Acero a mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_STEEL,
        .iconPic = gItemIcon_SteeliumZ,
        .iconPalette = gItemIconPalette_SteeliumZ,
    },

    [ITEM_FAIRIUM_Z] =
    {
        .name = ES(ITEM_NAME("Fairium Z"), ITEM_NAME("Feeristal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Fairy-\n"
            "type moves to\n"
            "Z-Moves."), COMPOUND_STRING("Mejora los mov. de\n" "tipo Hada a mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FAIRY,
        .iconPic = gItemIcon_FairiumZ,
        .iconPalette = gItemIconPalette_FairiumZ,
    },

    [ITEM_PIKANIUM_Z] =
    {
        .name = ES(ITEM_NAME("Pikanium Z"), ITEM_NAME("Pikastal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Pikachu's\n"
            "Volt Tackle\n"
            "to a Z-Move."), COMPOUND_STRING("Mejora el Placaje\n" "Eléc. de Pikachu a\n" "mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // Signature Z-Move
        .iconPic = gItemIcon_PikaniumZ,
        .iconPalette = gItemIconPalette_PikaniumZ,
    },

    [ITEM_EEVIUM_Z] =
    {
        .name = ES(ITEM_NAME("Eevium Z"), ITEM_NAME("Eeveestal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Eevee's\n"
            "Last Resort\n"
            "to a Z-Move."), COMPOUND_STRING("Mejora Última Baza\n" "de Eevee a mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // Signature Z-Move
        .iconPic = gItemIcon_EeviumZ,
        .iconPalette = gItemIconPalette_EeviumZ,
    },

    [ITEM_SNORLIUM_Z] =
    {
        .name = ES(ITEM_NAME("Snorlium Z"), ITEM_NAME("Snorlastal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Snorlax's\n"
            "Giga Impact\n"
            "to a Z-Move."), COMPOUND_STRING("Mejora Gigaimpacto\n" "de Snorlax a mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // Signature Z-Move
        .iconPic = gItemIcon_SnorliumZ,
        .iconPalette = gItemIconPalette_SnorliumZ,
    },

    [ITEM_MEWNIUM_Z] =
    {
        .name = ES(ITEM_NAME("Mewnium Z"), ITEM_NAME("Mewstal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Mew's\n"
            "Psychic\n"
            "to a Z-Move."), COMPOUND_STRING("Mejora Psíquico de\n" "Mew a mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // Signature Z-Move
        .iconPic = gItemIcon_MewniumZ,
        .iconPalette = gItemIconPalette_MewniumZ,
    },

    [ITEM_DECIDIUM_Z] =
    {
        .name = ES(ITEM_NAME("Decidium Z"), ITEM_NAME("Dueyestal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Decidueye\n"
            "Spirit Shackle\n"
            "to a Z-Move."), COMPOUND_STRING("Mejora Puntada\n" "Sombría de Decidueye\n" "a mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // Signature Z-Move
        .iconPic = gItemIcon_DecidiumZ,
        .iconPalette = gItemIconPalette_DecidiumZ,
    },

    [ITEM_INCINIUM_Z] =
    {
        .name = ES(ITEM_NAME("Incinium Z"), ITEM_NAME("Incinostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrade Incineroar\n"
            "Darkest Lariat\n"
            "to a Z-Move."), COMPOUND_STRING("Mejora Lariat Oscuro\n" "de Incineroar a mov.\n" "Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // Signature Z-Move
        .iconPic = gItemIcon_InciniumZ,
        .iconPalette = gItemIconPalette_InciniumZ,
    },

    [ITEM_PRIMARIUM_Z] =
    {
        .name = ES(ITEM_NAME("Primarium Z"), ITEM_NAME("Primastal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrade Primarina's\n"
            "Sparkling Aria\n"
            "to a Z-Move."), COMPOUND_STRING("Mejora Aria Burbuja\n" "de Primarina a mov.\n" "Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // Signature Z-Move
        .iconPic = gItemIcon_PrimariumZ,
        .iconPalette = gItemIconPalette_PrimariumZ,
    },

    [ITEM_LYCANIUM_Z] =
    {
        .name = ES(ITEM_NAME("Lycanium Z"), ITEM_NAME("Lycanrostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrade Lycanroc's\n"
            "Stone Edge\n"
            "to a Z-Move."), COMPOUND_STRING("Mejora Roca Afilada\n" "de Lycanroc a mov.\n" "Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // Signature Z-Move
        .iconPic = gItemIcon_LycaniumZ,
        .iconPalette = gItemIconPalette_LycaniumZ,
    },

    [ITEM_MIMIKIUM_Z] =
    {
        .name = ES(ITEM_NAME("Mimikium Z"), ITEM_NAME("Mimikyustal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Mimikyu's\n"
            "Play Rough\n"
            "to a Z-Move."), COMPOUND_STRING("Mejora Carantoña de\n" "Mimikyu a mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // Signature Z-Move
        .iconPic = gItemIcon_MimikiumZ,
        .iconPalette = gItemIconPalette_MimikiumZ,
    },

    [ITEM_KOMMONIUM_Z] =
    {
        .name = ES(ITEM_NAME("Kommonium Z"), ITEM_NAME("Kommostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Kommo-o's\n"
            "Clanging Scales\n"
            "to a Z-Move."), COMPOUND_STRING("Mejora Fragor\n" "Escamas de Kommo-o a\n" "mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // Signature Z-Move
        .iconPic = gItemIcon_KommoniumZ,
        .iconPalette = gItemIconPalette_KommoniumZ,
    },

    [ITEM_TAPUNIUM_Z] =
    {
        .name = ES(ITEM_NAME("Tapunium Z"), ITEM_NAME("Tapistal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrade the tapu's\n"
            "Nature's Madness\n"
            "to a Z-Move."), COMPOUND_STRING("Mejora Furia Natural\n" "de los Tapu a mov.\n" "Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  //Signature Z-Move
        .iconPic = gItemIcon_TapuniumZ,
        .iconPalette = gItemIconPalette_TapuniumZ,
    },

    [ITEM_SOLGANIUM_Z] =
    {
        .name = ES(ITEM_NAME("Solganium Z"), ITEM_NAME("Solgaleostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrade Solgaleo's\n"
            "Sunsteel Strike\n"
            "to a Z-Move."), COMPOUND_STRING("Mejora Meteoimpacto\n" "de Solgaleo a mov.\n" "Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // Signature Z-Move
        .iconPic = gItemIcon_SolganiumZ,
        .iconPalette = gItemIconPalette_SolganiumZ,
    },

    [ITEM_LUNALIUM_Z] =
    {
        .name = ES(ITEM_NAME("Lunalium Z"), ITEM_NAME("Lunalastal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Lunala's\n"
            "Moongeist Beam\n"
            "to a Z-Move."), COMPOUND_STRING("Mejora Rayo Umbrío\n" "de Lunala a mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // Signature Z-Move
        .iconPic = gItemIcon_LunaliumZ,
        .iconPalette = gItemIconPalette_LunaliumZ,
    },

    [ITEM_MARSHADIUM_Z] =
    {
        .name = ES(ITEM_NAME("Marshadium Z"), ITEM_NAME("Marshastal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrade Marshadow\n"
            "Spectral Thief\n"
            "to a Z-Move."), COMPOUND_STRING("Mejora Robasombra de\n" "Marshadow a mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // Signature Z-Move
        .iconPic = gItemIcon_MarshadiumZ,
        .iconPalette = gItemIconPalette_MarshadiumZ,
    },

    [ITEM_ALORAICHIUM_Z] =
    {
        .name = ES(ITEM_NAME("Aloraichium Z"), ITEM_NAME("Alo-Raistal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrades Alolan\n"
            "Raichu Thunderbolt\n"
            "to a Z-Move."), COMPOUND_STRING("Mejora Rayo del\n" "Raichu de Alola a\n" "mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // Signature Z-Move
        .iconPic = gItemIcon_AloraichiumZ,
        .iconPalette = gItemIconPalette_AloraichiumZ,
    },

    [ITEM_PIKASHUNIUM_Z] =
    {
        .name = ES(ITEM_NAME("Pikashunium Z"), ITEM_NAME("Ash-Pikastal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrade Pikachu in\n"
            "a cap's Thunderbolt\n"
            "to a Z-Move."), COMPOUND_STRING("Mejora Rayo del\n" "Pikachu con gorra a\n" "mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // Signature Z-Move
        .iconPic = gItemIcon_PikashuniumZ,
        .iconPalette = gItemIconPalette_PikashuniumZ,
    },

    [ITEM_ULTRANECROZIUM_Z] =
    {
        .name = ES(ITEM_NAME("Ultranecrozium Z"), ITEM_NAME("Ultranecrostal Z")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = ES(COMPOUND_STRING("Upgrade Necrozma's\n"
            "Photon Geyser\n"
            "to a Z-Move."), COMPOUND_STRING("Mejora Fotogeyser de\n" "Necrozma a mov. Z.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255, //Signature Z-Move
        .iconPic = gItemIcon_UltranecroziumZ,
        .iconPalette = gItemIconPalette_UltranecroziumZ,
    },

// Species-specific Stat-enhancing items

    [ITEM_LIGHT_BALL] =
    {
        .name = ES(ITEM_NAME("Light Ball"), ITEM_NAME("Bola Luminosa")),
        .price = (I_PRICE >= GEN_7) ? 1000 : 100,
        .holdEffect = HOLD_EFFECT_LIGHT_BALL,
        .description = COMPOUND_STRING(
            "A held item that\n"
        #if B_LIGHT_BALL_ATTACK_BOOST
            "boosts the Atk and\n"
            "Sp. Atk of Pikachu."),
        #else
            "boosts the Sp. Atk\n"
            "of Pikachu."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_LightBall,
        .iconPalette = gItemIconPalette_LightBall,
    },

    [ITEM_LEEK] =
    {
        .name = ES(ITEM_NAME("Leek"), ITEM_NAME("Puerro")),
        .price = (I_PRICE >= GEN_7) ? 1000 : 200,
        .holdEffect = HOLD_EFFECT_LEEK,
        .description = COMPOUND_STRING(
        #if P_GALARIAN_FORMS
            "Raises Farfetch'd\n"
            "or Sirfetch'd's\n"
            "critical-hit ratio."),
        #else
            "A held item that\n"
            "raises Farfetch'd's\n"
            "critical-hit ratio."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_Leek,
        .iconPalette = gItemIconPalette_Leek,
    },

    [ITEM_THICK_CLUB] =
    {
        .name = ES(ITEM_NAME("Thick Club"), ITEM_NAME("Hueso Grueso")),
        .price = (I_PRICE >= GEN_7) ? 1000 : 500,
        .holdEffect = HOLD_EFFECT_THICK_CLUB,
        .description = ES(COMPOUND_STRING("A held item that \n"
            "boosts Cubone or\n"
            "Marowak's Attack."), COMPOUND_STRING("Sube el Ataque de\n" "Cubone o Marowak.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 90,
        .iconPic = gItemIcon_Bone,
        .iconPalette = gItemIconPalette_Bone,
    },

    [ITEM_LUCKY_PUNCH] =
    {
        .name = ES(ITEM_NAME("Lucky Punch"), ITEM_NAME("Puño Suerte")),
        .pluralName = ITEM_PLURAL_NAME("Lucky Punches"),
        .price = (I_PRICE >= GEN_7) ? 1000 : 10,
        .holdEffect = HOLD_EFFECT_LUCKY_PUNCH,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises Chansey's\n"
            "critical-hit rate."), COMPOUND_STRING("Sube los golpes\n" "críticos de Chansey.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 40,
        .iconPic = gItemIcon_LuckyPunch,
        .iconPalette = gItemIconPalette_LuckyPunch,
    },

    [ITEM_METAL_POWDER] =
    {
        .name = ES(ITEM_NAME("Metal Powder"), ITEM_NAME("Polvo Metálico")),
        .price = (I_PRICE >= GEN_7) ? 1000 : 10,
        .holdEffect = HOLD_EFFECT_METAL_POWDER,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "boosts Ditto's\n"
            "Defense."), COMPOUND_STRING("Sube la Defensa de\n" "Ditto.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_DittoPowder,
        .iconPalette = gItemIconPalette_MetalPowder,
    },

    [ITEM_QUICK_POWDER] =
    {
        .name = ES(ITEM_NAME("Quick Powder"), ITEM_NAME("Polvo Veloz")),
        .price = (I_PRICE >= GEN_7) ? 1000 : 10,
        .holdEffect = HOLD_EFFECT_QUICK_POWDER,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "boosts Ditto's\n"
            "Speed."), COMPOUND_STRING("Sube la Velocidad de\n" "Ditto.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_DittoPowder,
        .iconPalette = gItemIconPalette_QuickPowder,
    },

    [ITEM_DEEP_SEA_SCALE] =
    {
        .name = ES(ITEM_NAME("Deep Sea Scale"), ITEM_NAME("Escama Marina")),
        .price = (I_PRICE >= GEN_7) ? 2000 : 200,
        .holdEffect = HOLD_EFFECT_DEEP_SEA_SCALE,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "boosts the Sp. Def\n"
            "of Clamperl."), COMPOUND_STRING("Sube la Def. Esp. de\n" "Clamperl.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_DeepSeaScale,
        .iconPalette = gItemIconPalette_DeepSeaScale,
    },

    [ITEM_DEEP_SEA_TOOTH] =
    {
        .name = ES(ITEM_NAME("Deep Sea Tooth"), ITEM_NAME("Diente Marino")),
        .pluralName = ITEM_PLURAL_NAME("Deep Sea Teeth"),
        .price = (I_PRICE >= GEN_7) ? 2000 : 200,
        .holdEffect = HOLD_EFFECT_DEEP_SEA_TOOTH,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "boosts the Sp. Atk\n"
            "of Clamperl."), COMPOUND_STRING("Sube el At. Esp. de\n" "Clamperl.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 90,
        .iconPic = gItemIcon_DeepSeaTooth,
        .iconPalette = gItemIconPalette_DeepSeaTooth,
    },

    [ITEM_SOUL_DEW] =
    {
        .name = ES(ITEM_NAME("Soul Dew"), ITEM_NAME("Rocío Bondad")),
        .price = (I_PRICE >= GEN_7) ? 0 : 200,
        .holdEffect = HOLD_EFFECT_SOUL_DEW,
        .holdEffectParam = B_SOUL_DEW_BOOST >= GEN_7 ? 20 : 50,
        .description = COMPOUND_STRING(
        #if B_SOUL_DEW_BOOST >= GEN_7
            "Boosts Latios or\n"
            "Latias' Psychic- &\n"
            "Dragon-type moves."),
        #else
            "Held item: boosts\n"
            "Sp. Atk & Sp. Def of\n"
            "Latios & Latias."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_SoulDew,
        .iconPalette = gItemIconPalette_SoulDew,
    },

    [ITEM_ADAMANT_ORB] =
    {
        .name = ES(ITEM_NAME("Adamant Orb"), ITEM_NAME("Diamansfera")),
        .price = (I_PRICE >= GEN_7) ? 0 : 10000,
        .holdEffect = HOLD_EFFECT_ADAMANT_ORB,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("Boosts Dialga's\n"
            "Dragon- and Steel-\n"
            "type moves."), COMPOUND_STRING("Potencia los mov.\n" "Dragón y Acero de\n" "Dialga.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_AdamantOrb,
        .iconPalette = gItemIconPalette_AdamantOrb,
    },

    [ITEM_LUSTROUS_ORB] =
    {
        .name = ES(ITEM_NAME("Lustrous Orb"), ITEM_NAME("Lustresfera")),
        .price = (I_PRICE >= GEN_7) ? 0 : 10000,
        .holdEffect = HOLD_EFFECT_LUSTROUS_ORB,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("Boosts Palkia's\n"
            "Dragon- and Water-\n"
            "type moves."), COMPOUND_STRING("Los Pokémon pueden\n" "llevarla o usarla\n" "para descongelarse.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_LustrousOrb,
        .iconPalette = gItemIconPalette_LustrousOrb,
    },

    [ITEM_GRISEOUS_ORB] =
    {
        .name = ES(ITEM_NAME("Griseous Orb"), ITEM_NAME("Griseosfera")),
        .price = (I_PRICE >= GEN_7) ? 0 : 10000,
        .holdEffect = HOLD_EFFECT_GRISEOUS_ORB,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("Boosts Giratina's\n"
            "Dragon- and Ghost-\n"
            "type moves."), COMPOUND_STRING("Potencia los mov.\n" "Dragón y Fantasma de\n" "Giratina.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_GriseousOrb,
        .iconPalette = gItemIconPalette_GriseousOrb,
    },

// Incenses

    [ITEM_SEA_INCENSE] =
    {
        .name = ES(ITEM_NAME("Sea Incense"), ITEM_NAME("Incienso Marino")),
        .price = (I_PRICE >= GEN_7) ? 2000 : 9600,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = I_TYPE_BOOST_POWER >= GEN_4 ? 20 : 5,
    #if I_TYPE_BOOST_POWER >= GEN_4
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Water-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Agua.")),
    #else
        .description = COMPOUND_STRING(
            "A held item that\n"
            "slightly boosts\n"
            "Water-type moves."),
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .flingPower = 10,
        .iconPic = gItemIcon_SeaIncense,
        .iconPalette = gItemIconPalette_SeaIncense,
    },

    [ITEM_LAX_INCENSE] =
    {
        .name = ES(ITEM_NAME("Lax Incense"), ITEM_NAME("Incienso Suave")),
        .price = (I_PRICE >= GEN_7) ? 5000 : 9600,
        .holdEffect = HOLD_EFFECT_EVASION_UP,
    #if I_LAX_INCENSE_BOOST >= GEN_4
        .holdEffectParam = 10,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "cuts the\n"
            "foe's accuracy."), COMPOUND_STRING("Baja la precisión de\n" "los rivales.")),
    #else
        .holdEffectParam = 5,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "slightly cuts the\n"
            "foe's accuracy."),
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_LaxIncense,
        .iconPalette = gItemIconPalette_LaxIncense,
    },

    [ITEM_ODD_INCENSE] =
    {
        .name = ES(ITEM_NAME("Odd Incense"), ITEM_NAME("Incienso Raro")),
        .price = (I_PRICE >= GEN_7) ? 2000 : 9600,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "boosts Psychic-\n"
            "type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Psíquico.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_PSYCHIC,
        .flingPower = 10,
        .iconPic = gItemIcon_OddIncense,
        .iconPalette = gItemIconPalette_OddIncense,
    },

    [ITEM_ROCK_INCENSE] =
    {
        .name = ES(ITEM_NAME("Rock Incense"), ITEM_NAME("Incienso Roca")),
        .price = (I_PRICE >= GEN_7) ? 2000 : 9600,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Rock-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Roca.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ROCK,
        .flingPower = 10,
        .iconPic = gItemIcon_RockIncense,
        .iconPalette = gItemIconPalette_RockIncense,
    },

    [ITEM_FULL_INCENSE] =
    {
        .name = ES(ITEM_NAME("Full Incense"), ITEM_NAME("Incienso Lento")),
        .price = (I_PRICE >= GEN_7) ? 5000 : 9600,
        .holdEffect = HOLD_EFFECT_LAGGING_TAIL,
        .holdEffectParam = 5,
        .description = ES(COMPOUND_STRING("An item that makes\n"
            "the holder move\n"
            "slower than usual."), COMPOUND_STRING("Hace que el portador\n" "actúe más tarde.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_FullIncense,
        .iconPalette = gItemIconPalette_FullIncense,
    },

    [ITEM_WAVE_INCENSE] =
    {
        .name = ES(ITEM_NAME("Wave Incense"), ITEM_NAME("Incienso Acua")),
        .price = (I_PRICE >= GEN_7) ? 2000 : 9600,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Water-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Agua.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .flingPower = 10,
        .iconPic = gItemIcon_WaveIncense,
        .iconPalette = gItemIconPalette_WaveIncense,
    },

    [ITEM_ROSE_INCENSE] =
    {
        .name = ES(ITEM_NAME("Rose Incense"), ITEM_NAME("Incienso Floral")),
        .price = (I_PRICE >= GEN_7) ? 2000 : 9600,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Grass-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Planta.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GRASS,
        .flingPower = 10,
        .iconPic = gItemIcon_RoseIncense,
        .iconPalette = gItemIconPalette_RoseIncense,
    },

    [ITEM_LUCK_INCENSE] =
    {
        .name = ES(ITEM_NAME("Luck Incense"), ITEM_NAME("Incienso Duplo")),
        .price = (I_PRICE >= GEN_7) ? 11000 : 9600,
        .holdEffect = HOLD_EFFECT_DOUBLE_PRIZE,
        .description = ES(COMPOUND_STRING("Doubles money in\n"
            "battle if the\n"
            "holder takes part."), COMPOUND_STRING("Dobla el dinero\n" "ganado si el\n" "portador lucha.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_LuckIncense,
        .iconPalette = gItemIconPalette_LuckIncense,
    },

    [ITEM_PURE_INCENSE] =
    {
        .name = ES(ITEM_NAME("Pure Incense"), ITEM_NAME("Incienso Puro")),
        .price = (I_PRICE >= GEN_7) ? 6000 : 9600,
        .holdEffect = HOLD_EFFECT_REPEL,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "helps repel wild\n"
            "Pokémon."), COMPOUND_STRING("Ayuda a ahuyentar a\n" "Pokémon salvajes.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_PureIncense,
        .iconPalette = gItemIconPalette_PureIncense,
    },

// Contest Scarves

    [ITEM_RED_SCARF] =
    {
        .name = ES(ITEM_NAME("Red Scarf"), ITEM_NAME("Pañuelo Rojo")),
        .pluralName = ITEM_PLURAL_NAME("Red Scarves"),
        .price = 100,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises Cool in\n"
            "Contests."), COMPOUND_STRING("Sube el Carisma en\n" "los concursos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_CONTEST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Scarf,
        .iconPalette = gItemIconPalette_RedScarf,
    },

    [ITEM_BLUE_SCARF] =
    {
        .name = ES(ITEM_NAME("Blue Scarf"), ITEM_NAME("Pañuelo Azul")),
        .pluralName = ITEM_PLURAL_NAME("Blue Scarves"),
        .price = 100,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises Beauty in\n"
            "Contests."), COMPOUND_STRING("Sube la Belleza en\n" "los concursos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_CONTEST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Scarf,
        .iconPalette = gItemIconPalette_BlueScarf,
    },

    [ITEM_PINK_SCARF] =
    {
        .name = ES(ITEM_NAME("Pink Scarf"), ITEM_NAME("Pañuelo Rosa")),
        .pluralName = ITEM_PLURAL_NAME("Pink Scarves"),
        .price = 100,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises Cute in\n"
            "Contests."), COMPOUND_STRING("Sube la Dulzura en\n" "los concursos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_CONTEST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Scarf,
        .iconPalette = gItemIconPalette_PinkScarf,
    },

    [ITEM_GREEN_SCARF] =
    {
        .name = ES(ITEM_NAME("Green Scarf"), ITEM_NAME("Pañuelo Verde")),
        .pluralName = ITEM_PLURAL_NAME("Green Scarves"),
        .price = 100,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises Smart in\n"
            "Contests."), COMPOUND_STRING("Sube el Ingenio en\n" "los concursos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_CONTEST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Scarf,
        .iconPalette = gItemIconPalette_GreenScarf,
    },

    [ITEM_YELLOW_SCARF] =
    {
        .name = ES(ITEM_NAME("Yellow Scarf"), ITEM_NAME("Pañuelo Amarillo")),
        .pluralName = ITEM_PLURAL_NAME("Yellow Scarves"),
        .price = 100,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises Tough in\n"
            "Contests."), COMPOUND_STRING("Sube la Dureza en\n" "los concursos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_CONTEST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Scarf,
        .iconPalette = gItemIconPalette_YellowScarf,
    },

// Power items

    [ITEM_MACHO_BRACE] =
    {
        .name = ES(ITEM_NAME("Macho Brace"), ITEM_NAME("Brazal Firme")),
        .price = 3000,
        .holdEffect = HOLD_EFFECT_MACHO_BRACE,
        .description = ES(COMPOUND_STRING("Promotes growth,\n"
            "but reduces\n"
            "Speed in battle."), COMPOUND_STRING("Ayuda a crecer, pero\n" "baja la Velocidad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EV_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_MachoBrace,
        .iconPalette = gItemIconPalette_MachoBrace,
    },

    [ITEM_POWER_WEIGHT] =
    {
        .name = ES(ITEM_NAME("Power Weight"), ITEM_NAME("Pesa Recia")),
        .price = (I_PRICE >= GEN_9) ? 10000 : 3000,
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = POWER_ITEM_BOOST,
        .description = ES(COMPOUND_STRING("Promotes HP\n"
            "gain, but cuts\n"
            "Speed in battle."), COMPOUND_STRING("Ayuda a subir PS,\n" "pero baja la\n" "Velocidad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EV_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_HP,
        .flingPower = 70,
        .iconPic = gItemIcon_PowerWeight,
        .iconPalette = gItemIconPalette_PowerWeight,
    },

    [ITEM_POWER_BRACER] =
    {
        .name = ES(ITEM_NAME("Power Bracer"), ITEM_NAME("Brazal Recio")),
        .price = (I_PRICE >= GEN_9) ? 10000 : 3000,
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = POWER_ITEM_BOOST,
        .description = ES(COMPOUND_STRING("Promotes Attack\n"
            "gain, but cuts\n"
            "Speed in battle."), COMPOUND_STRING("Ayuda a subir\n" "Ataque, pero baja la\n" "Velocidad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EV_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_ATK,
        .flingPower = 70,
        .iconPic = gItemIcon_PowerBracer,
        .iconPalette = gItemIconPalette_PowerBracer,
    },

    [ITEM_POWER_BELT] =
    {
        .name = ES(ITEM_NAME("Power Belt"), ITEM_NAME("Cinto Recio")),
        .price = (I_PRICE >= GEN_9) ? 10000 : 3000,
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = POWER_ITEM_BOOST,
        .description = ES(COMPOUND_STRING("Promotes Defense\n"
            "gain, but cuts\n"
            "Speed in battle."), COMPOUND_STRING("Ayuda a subir\n" "Defensa, pero baja\n" "la Velocidad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EV_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_DEF,
        .flingPower = 70,
        .iconPic = gItemIcon_PowerBelt,
        .iconPalette = gItemIconPalette_PowerBelt,
    },

    [ITEM_POWER_LENS] =
    {
        .name = ES(ITEM_NAME("Power Lens"), ITEM_NAME("Lente Recia")),
        .pluralName = ITEM_PLURAL_NAME("Power Lenses"),
        .price = (I_PRICE >= GEN_9) ? 10000 : 3000,
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = POWER_ITEM_BOOST,
        .description = ES(COMPOUND_STRING("Promotes Sp. Atk\n"
            "gain, but cuts\n"
            "Speed in battle."), COMPOUND_STRING("Ayuda a subir At.\n" "Esp., pero baja la\n" "Velocidad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EV_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_SPATK,
        .flingPower = 70,
        .iconPic = gItemIcon_PowerLens,
        .iconPalette = gItemIconPalette_PowerLens,
    },

    [ITEM_POWER_BAND] =
    {
        .name = ES(ITEM_NAME("Power Band"), ITEM_NAME("Banda Recia")),
        .price = (I_PRICE >= GEN_9) ? 10000 : 3000,
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = POWER_ITEM_BOOST,
        .description = ES(COMPOUND_STRING("Promotes Sp. Def\n"
            "gain, but cuts\n"
            "Speed in battle."), COMPOUND_STRING("Ayuda a subir Def.\n" "Esp., pero baja la\n" "Velocidad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EV_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_SPDEF,
        .flingPower = 70,
        .iconPic = gItemIcon_PowerBand,
        .iconPalette = gItemIconPalette_PowerBand,
    },

    [ITEM_POWER_ANKLET] =
    {
        .name = ES(ITEM_NAME("Power Anklet"), ITEM_NAME("Franja Recia")),
        .price = (I_PRICE >= GEN_9) ? 10000 : 3000,
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = POWER_ITEM_BOOST,
        .description = ES(COMPOUND_STRING("Promotes Speed\n"
            "gain, but cuts\n"
            "Speed in battle."), COMPOUND_STRING("Ayuda a subir\n" "Velocidad, pero la\n" "baja en combate.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EV_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_SPEED,
        .flingPower = 70,
        .iconPic = gItemIcon_PowerAnklet,
        .iconPalette = gItemIconPalette_PowerAnklet,
    },

// Type-enhancing items
#if I_PRICE >= GEN_9
    #define TYPE_BOOSTING_PRICE 3000
#elif I_PRICE >= GEN_7
    #define TYPE_BOOSTING_PRICE 1000
#else
    #define TYPE_BOOSTING_PRICE 100
#endif

    [ITEM_SILK_SCARF] =
    {
        .name = ES(ITEM_NAME("Silk Scarf"), ITEM_NAME("Pañuelo de Seda")),
        .pluralName = ITEM_PLURAL_NAME("Silk Scarves"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Normal-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Normal.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_NORMAL,
        .flingPower = 10,
        .iconPic = gItemIcon_SilkScarf,
        .iconPalette = gItemIconPalette_SilkScarf,
    },

    [ITEM_CHARCOAL] =
    {
        .name = ES(ITEM_NAME("Charcoal"), ITEM_NAME("Carbón")),
    #if I_PRICE >= GEN_9
        .price = 3000,
    #elif I_PRICE >= GEN_7
        .price = 1000,
    #else
        .price = 9800,
    #endif
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Fire-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Fuego.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIRE,
        .flingPower = 30,
        .iconPic = gItemIcon_Charcoal,
        .iconPalette = gItemIconPalette_Charcoal,
    },

    [ITEM_MYSTIC_WATER] =
    {
        .name = ES(ITEM_NAME("Mystic Water"), ITEM_NAME("Agua Mística")),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Water-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Agua.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .flingPower = 30,
        .iconPic = gItemIcon_MysticWater,
        .iconPalette = gItemIconPalette_MysticWater,
    },

    [ITEM_MAGNET] =
    {
        .name = ES(ITEM_NAME("Magnet"), ITEM_NAME("Imán")),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "boosts Electric-\n"
            "type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Eléctrico.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ELECTRIC,
        .flingPower = 30,
        .iconPic = gItemIcon_Magnet,
        .iconPalette = gItemIconPalette_Magnet,
    },

    [ITEM_MIRACLE_SEED] =
    {
        .name = ES(ITEM_NAME("Miracle Seed"), ITEM_NAME("Semilla Milagro")),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Grass-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Planta.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GRASS,
        .flingPower = 30,
        .iconPic = gItemIcon_MiracleSeed,
        .iconPalette = gItemIconPalette_MiracleSeed,
    },

    [ITEM_NEVER_MELT_ICE] =
    {
        .name = ES(ITEM_NAME("Never-Melt Ice"), ITEM_NAME("Hielo Perpetuo")),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Ice-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Hielo.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ICE,
        .flingPower = 30,
        .iconPic = gItemIcon_NeverMeltIce,
        .iconPalette = gItemIconPalette_NeverMeltIce,
    },

    [ITEM_BLACK_BELT] =
    {
        .name = ES(ITEM_NAME("Black Belt"), ITEM_NAME("Cinturón Negro")),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "boosts Fighting-\n"
            "type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Lucha.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIGHTING,
        .flingPower = 30,
        .iconPic = gItemIcon_BlackBelt,
        .iconPalette = gItemIconPalette_BlackTypeEnhancingItem,
    },

    [ITEM_POISON_BARB] =
    {
        .name = ES(ITEM_NAME("Poison Barb"), ITEM_NAME("Flecha Venenosa")),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Poison-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Veneno.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_POISON,
        .flingPower = 70,
        .iconPic = gItemIcon_PoisonBarb,
        .iconPalette = gItemIconPalette_PoisonBarb,
    },

    [ITEM_SOFT_SAND] =
    {
        .name = ES(ITEM_NAME("Soft Sand"), ITEM_NAME("Arena Fina")),
        .pluralName = ITEM_PLURAL_NAME("Soft Sand"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Ground-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Tierra.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GROUND,
        .flingPower = 10,
        .iconPic = gItemIcon_Sand,
        .iconPalette = gItemIconPalette_SoftSand,
    },

    [ITEM_SHARP_BEAK] =
    {
        .name = ES(ITEM_NAME("Sharp Beak"), ITEM_NAME("Pico Afilado")),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Flying-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Volador.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FLYING,
        .flingPower = 50,
        .iconPic = gItemIcon_SharpBeak,
        .iconPalette = gItemIconPalette_SharpBeak,
    },

    [ITEM_TWISTED_SPOON] =
    {
        .name = ES(ITEM_NAME("Twisted Spoon"), ITEM_NAME("Cuchara Torcida")),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "boosts Psychic-\n"
            "type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Psíquico.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_PSYCHIC,
        .flingPower = 30,
        .iconPic = gItemIcon_TwistedSpoon,
        .iconPalette = gItemIconPalette_TwistedSpoon,
    },

    [ITEM_SILVER_POWDER] =
    {
        .name = ES(ITEM_NAME("Silver Powder"), ITEM_NAME("Polvo Plata")),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Bug-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Bicho.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_BUG,
        .flingPower = 10,
        .iconPic = gItemIcon_SilverPowder,
        .iconPalette = gItemIconPalette_SilverPowder,
    },

    [ITEM_HARD_STONE] =
    {
        .name = ES(ITEM_NAME("Hard Stone"), ITEM_NAME("Piedra Dura")),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Rock-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Roca.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ROCK,
        .flingPower = 100,
        .iconPic = gItemIcon_HardStone,
        .iconPalette = gItemIconPalette_HardStone,
    },

    [ITEM_SPELL_TAG] =
    {
        .name = ES(ITEM_NAME("Spell Tag"), ITEM_NAME("Hechizo")),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Ghost-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Fantasma.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GHOST,
        .flingPower = 30,
        .iconPic = gItemIcon_SpellTag,
        .iconPalette = gItemIconPalette_SpellTag,
    },

    [ITEM_DRAGON_FANG] =
    {
        .name = ES(ITEM_NAME("Dragon Fang"), ITEM_NAME("Colmillo de Dragón")),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Dragon-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Dragón.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DRAGON,
        .flingPower = 70,
        .iconPic = gItemIcon_DragonFang,
        .iconPalette = gItemIconPalette_DragonFang,
    },

    [ITEM_BLACK_GLASSES] =
    {
        .name = ES(ITEM_NAME("Black Glasses"), ITEM_NAME("Gafas de Sol")),
        .pluralName = ITEM_PLURAL_NAME("Black Glasses"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Dark-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Siniestro.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DARK,
        .flingPower = 30,
        .iconPic = gItemIcon_BlackGlasses,
        .iconPalette = gItemIconPalette_BlackTypeEnhancingItem,
    },

    [ITEM_METAL_COAT] =
    {
        .name = ES(ITEM_NAME("Metal Coat"), ITEM_NAME("Revest. Metálico")),
    #if I_PRICE >= GEN_9
        .price = 3000,
    #elif I_PRICE >= GEN_7
        .price = 2000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Steel-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Acero.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .secondaryId = TYPE_STEEL,
        .flingPower = 30,
        .iconPic = gItemIcon_MetalCoat,
        .iconPalette = gItemIconPalette_MetalCoat,
    },

// Choice items

    [ITEM_CHOICE_BAND] =
    {
        .name = ES(ITEM_NAME("Choice Band"), ITEM_NAME("Cinta Elección")),
    #if I_PRICE >= GEN_9
        .price = 100000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_CHOICE_BAND,
        .description = ES(COMPOUND_STRING("Boosts Attack,\n"
            "but permits\n"
            "only one move."), COMPOUND_STRING("Sube el Ataque, pero\n" "solo deja usar un\n" "mov.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ChoiceBand,
        .iconPalette = gItemIconPalette_ChoiceBand,
    },

    [ITEM_CHOICE_SPECS] =
    {
        .name = ES(ITEM_NAME("Choice Specs"), ITEM_NAME("Gafas Elección")),
        .pluralName = ITEM_PLURAL_NAME("Choice Specs"),
    #if I_PRICE >= GEN_9
        .price = 100000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_CHOICE_SPECS,
        .description = ES(COMPOUND_STRING("Boosts Sp. Atk,\n"
            "but permits\n"
            "only one move."), COMPOUND_STRING("Sube el At. Esp.,\n" "pero solo deja usar\n" "un mov.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ChoiceSpecs,
        .iconPalette = gItemIconPalette_ChoiceSpecs,
    },

    [ITEM_CHOICE_SCARF] =
    {
        .name = ES(ITEM_NAME("Choice Scarf"), ITEM_NAME("Pañuelo Elección")),
        .pluralName = ITEM_PLURAL_NAME("Choice Scarves"),
    #if I_PRICE >= GEN_9
        .price = 100000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_CHOICE_SCARF,
        .description = ES(COMPOUND_STRING("Boosts Speed,\n"
            "but permits\n"
            "only one move."), COMPOUND_STRING("Sube la Velocidad,\n" "pero solo deja usar\n" "un mov.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ChoiceScarf,
        .iconPalette = gItemIconPalette_ChoiceScarf,
    },

// Status Orbs

    [ITEM_FLAME_ORB] =
    {
        .name = ES(ITEM_NAME("Flame Orb"), ITEM_NAME("Llamasfera")),
    #if I_PRICE >= GEN_9
        .price = 15000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_FLAME_ORB,
        .description = ES(COMPOUND_STRING("A bizarre orb that\n"
            "burns the\n"
            "holder in battle."), COMPOUND_STRING("Un orbe extraño que\n" "quema al portador.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_FlameOrb,
        .iconPalette = gItemIconPalette_FlameOrb,
    },

    [ITEM_TOXIC_ORB] =
    {
        .name = ES(ITEM_NAME("Toxic Orb"), ITEM_NAME("Toxisfera")),
    #if I_PRICE >= GEN_9
        .price = 15000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_TOXIC_ORB,
        .description = ES(COMPOUND_STRING("A bizarre orb that\n"
            "badly poisons the\n"
            "holder in battle."), COMPOUND_STRING("Un orbe extraño que\n" "envenena gravemente\n" "al portador.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_ToxicOrb,
        .iconPalette = gItemIconPalette_ToxicOrb,
    },

// Weather Rocks

    [ITEM_DAMP_ROCK] =
    {
        .name = ES(ITEM_NAME("Damp Rock"), ITEM_NAME("Roca Lluvia")),
    #if I_PRICE >= GEN_9
        .price = 8000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_DAMP_ROCK,
        .description = ES(COMPOUND_STRING("Extends rain\n"
            "when the\n"
            "holder summons it."), COMPOUND_STRING("Alarga la lluvia que\n" "crea el portador.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_DampRock,
        .iconPalette = gItemIconPalette_DampRock,
    },

    [ITEM_HEAT_ROCK] =
    {
        .name = ES(ITEM_NAME("Heat Rock"), ITEM_NAME("Roca Calor")),
    #if I_PRICE >= GEN_9
        .price = 8000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_HEAT_ROCK,
        .description = ES(COMPOUND_STRING("Extends harsh\n"
            "sunlight when the\n"
            "holder summons it."), COMPOUND_STRING("Alarga el sol que\n" "crea el portador.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_HeatRock,
        .iconPalette = gItemIconPalette_HeatRock,
    },

    [ITEM_SMOOTH_ROCK] =
    {
        .name = ES(ITEM_NAME("Smooth Rock"), ITEM_NAME("Roca Suave")),
    #if I_PRICE >= GEN_9
        .price = 8000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_SMOOTH_ROCK,
        .description = ES(COMPOUND_STRING("Extends a\n"
            "sandstorm when the\n"
            "holder summons it."), COMPOUND_STRING("Alarga la tormenta\n" "de arena del\n" "portador.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_SmoothRock,
        .iconPalette = gItemIconPalette_SmoothRock,
    },

    [ITEM_ICY_ROCK] =
    {
        .name = ES(ITEM_NAME("Icy Rock"), ITEM_NAME("Roca Helada")),
    #if I_PRICE >= GEN_9
        .price = 8000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_ICY_ROCK,
    #if B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_HAIL
        .description = ES(COMPOUND_STRING("Extends a\n"
            "hailstorm when the\n"
            "holder summons it."), COMPOUND_STRING("Alarga el granizo o\n" "la nieve del\n" "portador.")),
    #elif B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_SNOW
        .description = COMPOUND_STRING(
            "Extends a\n"
            "snowstorm when the\n"
            "holder summons it."),
    #else
        .description = COMPOUND_STRING(
            "Extends hail or\n"
            "snow when the\n"
            "holder summons it."),
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 40,
        .iconPic = gItemIcon_IcyRock,
        .iconPalette = gItemIconPalette_IcyRock,
    },

// Terrain Seeds

    [ITEM_ELECTRIC_SEED] =
    {
        .name = ES(ITEM_NAME("Electric Seed"), ITEM_NAME("Semilla Electro")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 4000,
        .holdEffect = HOLD_EFFECT_TERRAIN_SEED,
        .holdEffectParam = HOLD_EFFECT_PARAM_ELECTRIC_TERRAIN,
        .description = ES(COMPOUND_STRING("Raises Defense on\n"
            "Electric Terrain,\n"
            "but only once."), COMPOUND_STRING("Sube la Defensa en\n" "campo eléctrico. Un\n" "uso.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_TerrainSeed,
        .iconPalette = gItemIconPalette_ElectricSeed,
    },

    [ITEM_PSYCHIC_SEED] =
    {
        .name = ES(ITEM_NAME("Psychic Seed"), ITEM_NAME("Semilla Psique")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 4000,
        .holdEffect = HOLD_EFFECT_TERRAIN_SEED,
        .holdEffectParam = HOLD_EFFECT_PARAM_PSYCHIC_TERRAIN,
        .description = ES(COMPOUND_STRING("Raises Sp. Def on\n"
            "Psychic Terrain,\n"
            "but only once."), COMPOUND_STRING("Sube la Def. Esp. en\n" "campo psíquico. Un\n" "uso.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_TerrainSeed,
        .iconPalette = gItemIconPalette_PsychicSeed,
    },

    [ITEM_MISTY_SEED] =
    {
        .name = ES(ITEM_NAME("Misty Seed"), ITEM_NAME("Semilla Bruma")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 4000,
        .holdEffect = HOLD_EFFECT_TERRAIN_SEED,
        .holdEffectParam = HOLD_EFFECT_PARAM_MISTY_TERRAIN,
        .description = ES(COMPOUND_STRING("Raises Sp. Def on\n"
            "Misty Terrain,\n"
            "but only once."), COMPOUND_STRING("Sube la Def. Esp. en\n" "campo de niebla. Un\n" "uso.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_TerrainSeed,
        .iconPalette = gItemIconPalette_MistySeed,
    },

    [ITEM_GRASSY_SEED] =
    {
        .name = ES(ITEM_NAME("Grassy Seed"), ITEM_NAME("Semilla Hierba")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 4000,
        .holdEffect = HOLD_EFFECT_TERRAIN_SEED,
        .holdEffectParam = HOLD_EFFECT_PARAM_GRASSY_TERRAIN,
        .description = ES(COMPOUND_STRING("Raises Defense on\n"
            "Grassy Terrain,\n"
            "but only once."), COMPOUND_STRING("Sube la Defensa en\n" "campo de hierba. Un\n" "uso.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_TerrainSeed,
        .iconPalette = gItemIconPalette_GrassySeed,
    },

// Type-activated stat modifiers

    [ITEM_ABSORB_BULB] =
    {
        .name = ES(ITEM_NAME("Absorb Bulb"), ITEM_NAME("Tubérculo")),
    #if I_PRICE >= GEN_9
        .price = 5000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_ABSORB_BULB,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Ups Sp. Atk if the\n"
            "holder is hurt by\n"
            "a Water-type move."), COMPOUND_STRING("Sube el At. Esp. si\n" "le da un mov. de\n" "tipo Agua.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_AbsorbBulb,
        .iconPalette = gItemIconPalette_AbsorbBulb,
    },

    [ITEM_CELL_BATTERY] =
    {
        .name = ES(ITEM_NAME("Cell Battery"), ITEM_NAME("Pila")),
        .pluralName = ITEM_PLURAL_NAME("Cell Batteries"),
    #if I_PRICE >= GEN_9
        .price = 5000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_CELL_BATTERY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Ups Attack if the\n"
            "holder is hurt by\n"
            "an Electric move."), COMPOUND_STRING("Pluma que aumenta un\n" "poco los PS de base\n" "de un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_CellBattery,
        .iconPalette = gItemIconPalette_CellBattery,
    },

    [ITEM_LUMINOUS_MOSS] =
    {
        .name = ES(ITEM_NAME("Luminous Moss"), ITEM_NAME("Musgo Brillante")),
        .pluralName = ITEM_PLURAL_NAME("Luminous Moss"),
    #if I_PRICE >= GEN_9
        .price = 5000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 1000,
    #endif
        .holdEffect = HOLD_EFFECT_LUMINOUS_MOSS,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Ups Sp. Def if the\n"
            "holder is hurt by\n"
            "a Water-type move."), COMPOUND_STRING("Sube la Def. Esp. si\n" "le da un mov. de\n" "tipo Agua.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_LuminousMoss,
        .iconPalette = gItemIconPalette_LuminousMoss,
    },

    [ITEM_SNOWBALL] =
    {
        .name = ES(ITEM_NAME("Snowball"), ITEM_NAME("Bola de Nieve")),
    #if I_PRICE >= GEN_9
        .price = 5000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_SNOWBALL,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Ups Attack if the\n"
            "holder is hurt by\n"
            "an Ice-type move."), COMPOUND_STRING("Sube el Ataque si le\n" "da un mov. de tipo\n" "Hielo.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Snowball,
        .iconPalette = gItemIconPalette_Snowball,
    },

// Miscellaneous Held items

    [ITEM_BRIGHT_POWDER] =
    {
        .name = ES(ITEM_NAME("Bright Powder"), ITEM_NAME("Polvo Brillo")),
    #if I_PRICE >= GEN_9
        .price = 30000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 10,
    #endif
        .holdEffect = HOLD_EFFECT_EVASION_UP,
        .holdEffectParam = 10,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "casts a glare to\n"
            "reduce accuracy."), COMPOUND_STRING("Un destello que baja\n" "la precisión rival.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_BrightPowder,
        .iconPalette = gItemIconPalette_BrightPowder,
    },

    [ITEM_WHITE_HERB] =
    {
        .name = ES(ITEM_NAME("White Herb"), ITEM_NAME("Hierba Blanca")),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_WHITE_HERB,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "restores any\n"
            "lowered stat once."), COMPOUND_STRING("Recupera una vez las\n" "caract. que hayan\n" "bajado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_InBattleHerb,
        .iconPalette = gItemIconPalette_WhiteHerb,
    },

    [ITEM_EXP_SHARE] =
    {
        .name = ES(ITEM_NAME("Exp. Share"), ITEM_NAME("Repartir Exp")),
        .holdEffect = HOLD_EFFECT_EXP_SHARE,
    #if I_EXP_SHARE_ITEM >= GEN_6
        .description = ES(COMPOUND_STRING("This device allows\n"
            "all party members\n"
            "to share in Exp."), COMPOUND_STRING("Reparte la\n" "experiencia entre\n" "todo el equipo.")),
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
    #else
        .description = COMPOUND_STRING(
            "A held item that\n"
            "gets Exp. Points\n"
            "from battles."),
        .price = (I_PRICE == GEN_1) ? 1 : 3000,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
    #endif
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_ExpShare,
        .flingPower = 30,
        .iconPic = gItemIcon_ExpShare,
        .iconPalette = gItemIconPalette_ExpShare,
    },

    [ITEM_QUICK_CLAW] =
    {
        .name = ES(ITEM_NAME("Quick Claw"), ITEM_NAME("Garra Rápida")),
    #if I_PRICE >= GEN_9
        .price = 8000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_QUICK_CLAW,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "occasionally allows\n"
            "the first strike."), COMPOUND_STRING("A veces permite\n" "atacar primero.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_QuickClaw,
        .iconPalette = gItemIconPalette_QuickClaw,
    },

    [ITEM_SOOTHE_BELL] =
    {
        .name = ES(ITEM_NAME("Soothe Bell"), ITEM_NAME("Cascabel Alivio")),
    #if I_PRICE >= GEN_9
        .price = 5000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_FRIENDSHIP_UP,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "calms spirits and\n"
            "fosters friendship."), COMPOUND_STRING("Calma al portador y\n" "le hace coger\n" "cariño.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_SootheBell,
        .iconPalette = gItemIconPalette_SootheBell,
    },

    [ITEM_MENTAL_HERB] =
    {
        .name = ES(ITEM_NAME("Mental Herb"), ITEM_NAME("Hierba Mental")),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_MENTAL_HERB,
        .description = COMPOUND_STRING(
        #if B_MENTAL_HERB >= GEN_5
            "Snaps Pokémon out\n"
            "of move-binding\n"
            "effects once."),
        #else
            "A held item that\n"
            "snaps Pokémon out\n"
            "of attraction once."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_InBattleHerb,
        .iconPalette = gItemIconPalette_MentalHerb,
    },

    [ITEM_KINGS_ROCK] =
    {
        .name = ES(ITEM_NAME("King's Rock"), ITEM_NAME("Roca del Rey")),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 5000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_FLINCH,
        .holdEffectParam = 10,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "may cause flinching\n"
            "when the foe is hit."), COMPOUND_STRING("Al golpear, puede\n" "amedrentar al rival.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_KingsRock,
        .iconPalette = gItemIconPalette_KingsRock,
    },

    [ITEM_AMULET_COIN] =
    {
        .name = ES(ITEM_NAME("Amulet Coin"), ITEM_NAME("Moneda Amuleto")),
    #if I_PRICE >= GEN_9
        .price = 30000,
    #elif I_PRICE >= GEN_7
        .price = 10000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_DOUBLE_PRIZE,
        .description = ES(COMPOUND_STRING("Doubles money in\n"
            "battle if the\n"
            "holder takes part."), COMPOUND_STRING("Dobla el dinero\n" "ganado si el\n" "portador lucha.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_AmuletCoin,
        .iconPalette = gItemIconPalette_AmuletCoin,
    },

    [ITEM_CLEANSE_TAG] =
    {
        .name = ES(ITEM_NAME("Cleanse Tag"), ITEM_NAME("Amuleto")),
        .price = (I_PRICE >= GEN_7) ? 5000 : 200,
        .holdEffect = HOLD_EFFECT_REPEL,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "helps repel wild\n"
            "Pokémon."), COMPOUND_STRING("Ayuda a ahuyentar a\n" "Pokémon salvajes.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_CleanseTag,
        .iconPalette = gItemIconPalette_CleanseTag,
    },

    [ITEM_SMOKE_BALL] =
    {
        .name = ES(ITEM_NAME("Smoke Ball"), ITEM_NAME("Bola de Humo")),
    #if I_PRICE >= GEN_9
        .price = 15000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_CAN_ALWAYS_RUN,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "assures fleeing\n"
            "from wild Pokémon."), COMPOUND_STRING("Permite huir siempre\n" "de un Pokémon\n" "salvaje.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_SmokeBall,
        .iconPalette = gItemIconPalette_SmokeBall,
    },

    [ITEM_FOCUS_BAND] =
    {
        .name = ES(ITEM_NAME("Focus Band"), ITEM_NAME("Cinta Aguante")),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_FOCUS_BAND,
        .holdEffectParam = 10,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "occasionally\n"
            "prevents fainting."), COMPOUND_STRING("A veces evita que el\n" "portador se\n" "debilite.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_FocusBand,
        .iconPalette = gItemIconPalette_FocusBand,
    },

    [ITEM_LUCKY_EGG] =
    {
        .name = ES(ITEM_NAME("Lucky Egg"), ITEM_NAME("Huevo Suerte")),
        .price = (I_PRICE >= GEN_7) ? 10000 : 200,
        .holdEffect = HOLD_EFFECT_LUCKY_EGG,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "boosts Exp. Points\n"
            "earned in battle."), COMPOUND_STRING("Da más experiencia\n" "en los combates.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_LuckyEgg,
        .iconPalette = gItemIconPalette_LuckyEgg,
    },

    [ITEM_SCOPE_LENS] =
    {
        .name = ES(ITEM_NAME("Scope Lens"), ITEM_NAME("Periscopio")),
        .pluralName = ITEM_PLURAL_NAME("Scope Lenses"),
    #if I_PRICE >= GEN_9
        .price = 15000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_SCOPE_LENS,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "improves the\n"
            "critical-hit rate."), COMPOUND_STRING("Sube el índice de\n" "golpe crítico.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_ScopeLens,
        .iconPalette = gItemIconPalette_ScopeLens,
    },

    [ITEM_LEFTOVERS] =
    {
        .name = ES(ITEM_NAME("Leftovers"), ITEM_NAME("Restos")),
        .pluralName = ITEM_PLURAL_NAME("Leftovers"),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_LEFTOVERS,
        .holdEffectParam = 10,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "gradually restores\n"
            "HP in battle."), COMPOUND_STRING("Recupera PS poco a\n" "poco en combate.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Leftovers,
        .iconPalette = gItemIconPalette_Leftovers,
    },

    [ITEM_SHELL_BELL] =
    {
        .name = ES(ITEM_NAME("Shell Bell"), ITEM_NAME("Cascabel Concha")),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_SHELL_BELL,
        .holdEffectParam = 8,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "restores HP upon\n"
            "striking the foe."), COMPOUND_STRING("Recupera PS al\n" "golpear al rival.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_ShellBell,
        .iconPalette = gItemIconPalette_Shell,
    },

    [ITEM_WIDE_LENS] =
    {
        .name = ES(ITEM_NAME("Wide Lens"), ITEM_NAME("Lupa")),
        .pluralName = ITEM_PLURAL_NAME("Wide Lenses"),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_WIDE_LENS,
        .holdEffectParam = 10,
        .description = ES(COMPOUND_STRING("A magnifying lens\n"
            "that boosts the\n"
            "accuracy of moves."), COMPOUND_STRING("Una lupa que sube la\n" "precisión de los\n" "mov.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_WideLens,
        .iconPalette = gItemIconPalette_WideLens,
    },

    [ITEM_MUSCLE_BAND] =
    {
        .name = ES(ITEM_NAME("Muscle Band"), ITEM_NAME("Cinta Fuerte")),
    #if I_PRICE >= GEN_9
        .price = 8000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_MUSCLE_BAND,
        .holdEffectParam = 10,
        .description = ES(COMPOUND_STRING("A headband that\n"
            "slightly boosts\n"
            "physical moves."), COMPOUND_STRING("Una cinta que\n" "potencia un poco los\n" "mov. físicos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_MuscleBand,
        .iconPalette = gItemIconPalette_MuscleBand,
    },

    [ITEM_WISE_GLASSES] =
    {
        .name = ES(ITEM_NAME("Wise Glasses"), ITEM_NAME("Gafas Especiales")),
        .pluralName = ITEM_PLURAL_NAME("Wise Glasses"),
    #if I_PRICE >= GEN_9
        .price = 8000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_WISE_GLASSES,
        .holdEffectParam = 10,
        .description = ES(COMPOUND_STRING("Thick glasses that\n"
            "slightly boost\n"
            "special moves."), COMPOUND_STRING("Unas gafas que\n" "potencian un poco\n" "los mov. especiales.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_WiseGlasses,
        .iconPalette = gItemIconPalette_WiseGlasses,
    },

    [ITEM_EXPERT_BELT] =
    {
        .name = ES(ITEM_NAME("Expert Belt"), ITEM_NAME("Cinta Experto")),
    #if I_PRICE >= GEN_9
        .price = 30000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_EXPERT_BELT,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A well-worn belt\n"
            "that boosts super\n"
            "effective moves."), COMPOUND_STRING("Un cinturón que\n" "potencia los mov.\n" "supereficaces.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ExpertBelt,
        .iconPalette = gItemIconPalette_ExpertBelt,
    },

    [ITEM_LIGHT_CLAY] =
    {
        .name = ES(ITEM_NAME("Light Clay"), ITEM_NAME("Refleluz")),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_LIGHT_CLAY,
        .description = ES(COMPOUND_STRING("Barrier moves\n"
            "like Light Screen\n"
            "last longer."), COMPOUND_STRING("Las barreras como\n" "Pantalla de Luz\n" "duran más.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_LightClay,
        .iconPalette = gItemIconPalette_LightClay,
    },

    [ITEM_LIFE_ORB] =
    {
        .name = ES(ITEM_NAME("Life Orb"), ITEM_NAME("Vidasfera")),
    #if I_PRICE >= GEN_9
        .price = 50000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_LIFE_ORB,
        .description = ES(COMPOUND_STRING("Boosts moves, but\n"
            "cuts HP when the\n"
            "holder lands hits."), COMPOUND_STRING("Potencia los mov.,\n" "pero resta PS al\n" "golpear.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_LifeOrb,
        .iconPalette = gItemIconPalette_LifeOrb,
    },

    [ITEM_POWER_HERB] =
    {
        .name = ES(ITEM_NAME("Power Herb"), ITEM_NAME("Hierba Única")),
    #if I_PRICE >= GEN_9
        .price = 30000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_POWER_HERB,
        .description = ES(COMPOUND_STRING("Allows immediate\n"
            "use of a move that\n"
            "requires charging."), COMPOUND_STRING("Usa al instante un\n" "mov. que necesita\n" "cargar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_PowerHerb,
        .iconPalette = gItemIconPalette_PowerHerb,
    },

    [ITEM_FOCUS_SASH] =
    {
        .name = ES(ITEM_NAME("Focus Sash"), ITEM_NAME("Banda Aguante")),
        .pluralName = ITEM_PLURAL_NAME("Focus Sashes"),
    #if I_PRICE >= GEN_9
        .price = 50000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_FOCUS_SASH,
        .description = ES(COMPOUND_STRING("If the holder has\n"
            "full HP, it endures\n"
            "one KO with 1 HP."), COMPOUND_STRING("Con PS al máximo,\n" "aguanta un KO con 1\n" "PS.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_FocusSash,
        .iconPalette = gItemIconPalette_FocusSash,
    },

    [ITEM_ZOOM_LENS] =
    {
        .name = ES(ITEM_NAME("Zoom Lens"), ITEM_NAME("Telescopio")),
        .pluralName = ITEM_PLURAL_NAME("Zoom Lenses"),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_ZOOM_LENS,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("Boosts accuracy if\n"
            "the holder moves\n"
            "after the foe."), COMPOUND_STRING("Sube la precisión si\n" "actúa después del\n" "rival.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ZoomLens,
        .iconPalette = gItemIconPalette_ZoomLens,
    },

    [ITEM_METRONOME] =
    {
        .name = ES(ITEM_NAME("Metronome"), ITEM_NAME("Metrónomo")),
    #if I_PRICE >= GEN_9
        .price = 15000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_METRONOME,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of a move that is\n"
            "used repeatedly."), COMPOUND_STRING("Potencia un mov. que\n" "se usa varias veces\n" "seguidas.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Metronome,
        .iconPalette = gItemIconPalette_Metronome,
    },

    [ITEM_IRON_BALL] =
    {
        .name = ES(ITEM_NAME("Iron Ball"), ITEM_NAME("Bola Férrea")),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_IRON_BALL,
        .description = ES(COMPOUND_STRING("Cuts Speed and\n"
            "makes Ground moves\n"
            "hit the holder."), COMPOUND_STRING("Baja la Velocidad y\n" "le dan los mov.\n" "Tierra.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 130,
        .iconPic = gItemIcon_IronBall,
        .iconPalette = gItemIconPalette_IronBall,
    },

    [ITEM_LAGGING_TAIL] =
    {
        .name = ES(ITEM_NAME("Lagging Tail"), ITEM_NAME("Cola Plúmbea")),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_LAGGING_TAIL,
        .description = ES(COMPOUND_STRING("An item that makes\n"
            "the holder move\n"
            "slower than usual."), COMPOUND_STRING("Hace que el portador\n" "actúe más tarde.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_LaggingTail,
        .iconPalette = gItemIconPalette_LaggingTail,
    },

    [ITEM_DESTINY_KNOT] =
    {
        .name = ES(ITEM_NAME("Destiny Knot"), ITEM_NAME("Lazo Destino")),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_DESTINY_KNOT,
        .description = ES(COMPOUND_STRING("If the holder falls\n"
            "in love, the foe\n"
            "does too."), COMPOUND_STRING("Si se enamora, el\n" "rival también se\n" "enamora.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_DestinyKnot,
        .iconPalette = gItemIconPalette_DestinyKnot,
    },

    [ITEM_BLACK_SLUDGE] =
    {
        .name = ES(ITEM_NAME("Black Sludge"), ITEM_NAME("Lodo Negro")),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_BLACK_SLUDGE,
        .description = ES(COMPOUND_STRING("Gradually restores\n"
            "Poison-types' HP.\n"
            "Damages all others."), COMPOUND_STRING("Cura a los tipo\n" "Veneno; daña a los\n" "demás.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BlackSludge,
        .iconPalette = gItemIconPalette_BlackSludge,
    },

    [ITEM_GRIP_CLAW] =
    {
        .name = ES(ITEM_NAME("Grip Claw"), ITEM_NAME("Garra Garfio")),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_GRIP_CLAW,
        .description = ES(COMPOUND_STRING("Multi-turn moves\n"
            "like Bind and Wrap\n"
            "last longer."), COMPOUND_STRING("Los mov. que\n" "atrapan, como\n" "Atadura, duran más.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 90,
        .iconPic = gItemIcon_GripClaw,
        .iconPalette = gItemIconPalette_GripClaw,
    },

    [ITEM_STICKY_BARB] =
    {
        .name = ES(ITEM_NAME("Sticky Barb"), ITEM_NAME("Toxiestrella")),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_STICKY_BARB,
        .description = ES(COMPOUND_STRING("Damages the holder\n"
            "each turn. Latches\n"
            "on from contact."), COMPOUND_STRING("Daña al portador\n" "cada turno. Se pega\n" "al tocar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_StickyBarb,
        .iconPalette = gItemIconPalette_StickyBarb,
    },

    [ITEM_SHED_SHELL] =
    {
        .name = ES(ITEM_NAME("Shed Shell"), ITEM_NAME("Muda Concha")),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_SHED_SHELL,
        .description = ES(COMPOUND_STRING("Enables the holder\n"
            "to switch out\n"
            "without fail."), COMPOUND_STRING("Permite cambiarse\n" "siempre.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ShedShell,
        .iconPalette = gItemIconPalette_ShedShell,
    },

    [ITEM_BIG_ROOT] =
    {
        .name = ES(ITEM_NAME("Big Root"), ITEM_NAME("Raíz Grande")),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_BIG_ROOT,
        .holdEffectParam = 30,
        .description = ES(COMPOUND_STRING("Boosts the amount\n"
            "of HP restored from\n"
            "HP-stealing moves."), COMPOUND_STRING("Recupera más PS con\n" "los mov. que\n" "absorben.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_BigRoot,
        .iconPalette = gItemIconPalette_BigRoot,
    },

    [ITEM_RAZOR_CLAW] =
    {
        .name = ES(ITEM_NAME("Razor Claw"), ITEM_NAME("Garra Afilada")),
    #if I_PRICE >= GEN_9
        .price = 15000,
    #elif I_PRICE >= GEN_7
        .price = 5000,
    #else
        .price = 2100,
    #endif
        .holdEffect = HOLD_EFFECT_SCOPE_LENS,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "improves the\n"
            "critical-hit rate."), COMPOUND_STRING("Sube el índice de\n" "golpe crítico.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_RazorClaw,
        .iconPalette = gItemIconPalette_RazorClaw,
    },

    [ITEM_RAZOR_FANG] =
    {
        .name = ES(ITEM_NAME("Razor Fang"), ITEM_NAME("Colmillo Agudo")),
    #if I_PRICE >= GEN_9
        .price = 15000,
    #elif I_PRICE >= GEN_7
        .price = 5000,
    #else
        .price = 2100,
    #endif
        .holdEffect = HOLD_EFFECT_FLINCH,
        .holdEffectParam = 10,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "may cause flinching\n"
            "when the foe is hit."), COMPOUND_STRING("Al golpear, puede\n" "amedrentar al rival.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_RazorFang,
        .iconPalette = gItemIconPalette_RazorFang,
    },

    [ITEM_EVIOLITE] =
    {
        .name = ES(ITEM_NAME("Eviolite"), ITEM_NAME("Mineral Evol")),
    #if I_PRICE >= GEN_9
        .price = 50000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_EVIOLITE,
        .holdEffectParam = 50,
        .description = ES(COMPOUND_STRING("Ups the defensive\n"
            "stats of Pokémon\n"
            "that can evolve."), COMPOUND_STRING("Sube las defensas de\n" "quien aún puede\n" "evolucionar.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 40,
        .iconPic = gItemIcon_Eviolite,
        .iconPalette = gItemIconPalette_Eviolite,
    },

    [ITEM_FLOAT_STONE] =
    {
        .name = ES(ITEM_NAME("Float Stone"), ITEM_NAME("Piedra Pómez")),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_FLOAT_STONE,
        .description = ES(COMPOUND_STRING("A light stone that\n"
            "reduces the weight\n"
            "of the holder."), COMPOUND_STRING("Una piedra ligera\n" "que reduce el peso.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_FloatStone,
        .iconPalette = gItemIconPalette_FloatStone,
    },

    [ITEM_ROCKY_HELMET] =
    {
        .name = ES(ITEM_NAME("Rocky Helmet"), ITEM_NAME("Casco Dentado")),
    #if I_PRICE >= GEN_9
        .price = 50000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_ROCKY_HELMET,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Damages foes that\n"
            "make contact with\n"
            "the holder."), COMPOUND_STRING("Daña a quien toque\n" "al portador.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_RockyHelmet,
        .iconPalette = gItemIconPalette_RockyHelmet,
    },

    [ITEM_AIR_BALLOON] =
    {
        .name = ES(ITEM_NAME("Air Balloon"), ITEM_NAME("Globo Helio")),
    #if I_PRICE >= GEN_9
        .price = 15000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_AIR_BALLOON,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Makes the holder\n"
            "float, but bursts\n"
            "if hit by an attack."), COMPOUND_STRING("Hace flotar al\n" "portador; explota al\n" "recibir un golpe.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_AirBalloon,
        .iconPalette = gItemIconPalette_AirBalloon,
    },

    [ITEM_RED_CARD] =
    {
        .name = ES(ITEM_NAME("Red Card"), ITEM_NAME("Tarjeta Roja")),
    #if I_PRICE >= GEN_9
        .price = 3000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_RED_CARD,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Foes that hit the\n"
            "holder are removed\n"
            "from the battle."), COMPOUND_STRING("Quien golpee al\n" "portador sale del\n" "combate.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_RedCard,
        .iconPalette = gItemIconPalette_RedCard,
    },

    [ITEM_RING_TARGET] =
    {
        .name = ES(ITEM_NAME("Ring Target"), ITEM_NAME("Blanco")),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_RING_TARGET,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("Moves that have no\n"
            "effect due to type\n"
            "will hit the holder."), COMPOUND_STRING("Le alcanzan mov. a\n" "los que sería inmune\n" "por tipo.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_RingTarget,
        .iconPalette = gItemIconPalette_RingTarget,
    },

    [ITEM_BINDING_BAND] =
    {
        .name = ES(ITEM_NAME("Binding Band"), ITEM_NAME("Banda Atadura")),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_BINDING_BAND,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of the holder's\n"
            "binding moves."), COMPOUND_STRING("Banda que potencia\n" "los movimientos que\n" "estrujan al rival.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BindingBand,
        .iconPalette = gItemIconPalette_BindingBand,
    },

    [ITEM_EJECT_BUTTON] =
    {
        .name = ES(ITEM_NAME("Eject Button"), ITEM_NAME("Botón Escape")),
    #if I_PRICE >= GEN_9
        .price = 30000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_EJECT_BUTTON,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("If the holder is\n"
            "hit, it will be\n"
            "switched out."), COMPOUND_STRING("Pluma que aumenta un\n" "poco el Ataque de\n" "base de un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_EjectButton,
        .iconPalette = gItemIconPalette_EjectButton,
    },

    [ITEM_WEAKNESS_POLICY] =
    {
        .name = ES(ITEM_NAME("Weakness Policy"), ITEM_NAME("Seguro Debilidad")),
        .pluralName = ITEM_PLURAL_NAME("Weakness Policies"),
        .price = (I_PRICE >= GEN_9) ? 50000 : 1000,
        .holdEffect = HOLD_EFFECT_WEAKNESS_POLICY,
        .holdEffectParam = 0,
        .description = ES(COMPOUND_STRING("If hit super\n"
            "effectively, ups\n"
            "offenses sharply."), COMPOUND_STRING("Si recibe un\n" "supereficaz, sube\n" "mucho sus ataques.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_WeaknessPolicy,
        .iconPalette = gItemIconPalette_WeaknessPolicy,
    },

    [ITEM_ASSAULT_VEST] =
    {
        .name = ES(ITEM_NAME("Assault Vest"), ITEM_NAME("Chaleco Asalto")),
        .price = (I_PRICE >= GEN_9) ? 50000 : 1000,
        .holdEffect = HOLD_EFFECT_ASSAULT_VEST,
        .holdEffectParam = 50,
        .description = ES(COMPOUND_STRING("Boosts Sp. Def, but\n"
            "prevents the use\n"
            "of status moves."), COMPOUND_STRING("Sube la Def. Esp.,\n" "pero no deja usar\n" "mov. de estado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_AssaultVest,
        .iconPalette = gItemIconPalette_AssaultVest,
    },

    [ITEM_SAFETY_GOGGLES] =
    {
        .name = ES(ITEM_NAME("Safety Goggles"), ITEM_NAME("Gafa Protectora")),
        .pluralName = ITEM_PLURAL_NAME("Safety Goggles"),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 1000,
    #endif
        .holdEffect = HOLD_EFFECT_SAFETY_GOGGLES,
        .description = ES(COMPOUND_STRING("Protects from\n"
            "weather damage,\n"
            "powder and spores."), COMPOUND_STRING("Protege del tiempo,\n" "del polvo y de las\n" "esporas.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_SafetyGoggles,
        .iconPalette = gItemIconPalette_SafetyGoggles,
    },

    [ITEM_ADRENALINE_ORB] =
    {
        .name = ES(ITEM_NAME("Adrenaline Orb"), ITEM_NAME("Nerviosfera")),
    #if I_PRICE >= GEN_9
        .price = 5000,
    #elif I_PRICE == GEN_8
        .price = 4000,
    #else
        .price = 300,
    #endif
        .holdEffect = HOLD_EFFECT_ADRENALINE_ORB,
        .description = ES(COMPOUND_STRING("This orb raises\n"
            "Speed if the holder\n"
            "is intimidated."), COMPOUND_STRING("Aumenta la Velocidad\n" "del portador si se\n" "siente intimidado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_AdrenalineOrb,
        .iconPalette = gItemIconPalette_AdrenalineOrb,
    },

    [ITEM_TERRAIN_EXTENDER] =
    {
        .name = ES(ITEM_NAME("Terrain Extender"), ITEM_NAME("Cubresuelos")),
        .price = (I_PRICE >= GEN_9) ? 15000 : 4000,
        .holdEffect = HOLD_EFFECT_TERRAIN_EXTENDER,
        .description = ES(COMPOUND_STRING("Extends terrain\n"
            "duration when the\n"
            "holder summons it."), COMPOUND_STRING("Alarga el campo que\n" "crea el portador.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_TerrainExtender,
        .iconPalette = gItemIconPalette_TerrainExtender,
    },

    [ITEM_PROTECTIVE_PADS] =
    {
        .name = ES(ITEM_NAME("Protective Pads"), ITEM_NAME("Paracontacto")),
        .pluralName = ITEM_PLURAL_NAME("Protective Pads"),
        .price = (I_PRICE >= GEN_9) ? 15000 : 4000,
        .holdEffect = HOLD_EFFECT_PROTECTIVE_PADS,
        .description = ES(COMPOUND_STRING("Protects from\n"
            "effects triggered\n"
            "by making contact."), COMPOUND_STRING("Protege de los\n" "efectos del\n" "contacto.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_ProtectivePads,
        .iconPalette = gItemIconPalette_ProtectivePads,
    },

    [ITEM_THROAT_SPRAY] =
    {
        .name = ES(ITEM_NAME("Throat Spray"), ITEM_NAME("Espray Bucal")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 4000,
        .holdEffect = HOLD_EFFECT_THROAT_SPRAY,
        .description = ES(COMPOUND_STRING("Raises Sp. Atk if\n"
            "the holder uses a\n"
            "sound-based move."), COMPOUND_STRING("Sube el At. Esp. al\n" "usar un mov. de\n" "sonido.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_ThroatSpray,
        .iconPalette = gItemIconPalette_ThroatSpray,
    },

    [ITEM_EJECT_PACK] =
    {
        .name = ES(ITEM_NAME("Eject Pack"), ITEM_NAME("Mochila Escape")),
        .price = (I_PRICE >= GEN_9) ? 30000 : 4000,
        .holdEffect = HOLD_EFFECT_EJECT_PACK,
        .description = ES(COMPOUND_STRING("If the holder's\n"
            "stats are lowered,\n"
            "it'll be switched."), COMPOUND_STRING("Si le bajan caract.,\n" "el portador se\n" "cambia.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 50,
        .iconPic = gItemIcon_EjectPack,
        .iconPalette = gItemIconPalette_EjectPack,
    },

    [ITEM_HEAVY_DUTY_BOOTS] =
    {
        .name = ES(ITEM_NAME("Heavy-Duty Boots"), ITEM_NAME("Botas Gruesas")),
        .pluralName = ITEM_PLURAL_NAME("Heavy-Duty Boots"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 4000,
        .holdEffect = HOLD_EFFECT_HEAVY_DUTY_BOOTS,
        .description = ES(COMPOUND_STRING("Protects from the\n"
            "effects of traps\n"
            "set on the field."), COMPOUND_STRING("Protege de las\n" "trampas del campo.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_HeavyDutyBoots,
        .iconPalette = gItemIconPalette_HeavyDutyBoots,
    },

    [ITEM_BLUNDER_POLICY] =
    {
        .name = ES(ITEM_NAME("Blunder Policy"), ITEM_NAME("Seguro Fallo")),
        .pluralName = ITEM_PLURAL_NAME("Blunder Policies"),
        .price = (I_PRICE >= GEN_9) ? 30000 : 4000,
        .holdEffect = HOLD_EFFECT_BLUNDER_POLICY,
        .description = ES(COMPOUND_STRING("Sharply ups speed\n"
            "if a move misses\n"
            "due to accuracy."), COMPOUND_STRING("Si falla un mov.,\n" "sube mucho la\n" "Velocidad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_BlunderPolicy,
        .iconPalette = gItemIconPalette_BlunderPolicy,
    },

    [ITEM_ROOM_SERVICE] =
    {
        .name = ES(ITEM_NAME("Room Service"), ITEM_NAME("Servicio Raro")),
        .price = (I_PRICE >= GEN_9) ? 20000 : 4000,
        .holdEffect = HOLD_EFFECT_ROOM_SERVICE,
        .description = ES(COMPOUND_STRING("Lowers the holder's\n"
            "Speed when Trick\n"
            "Room takes effect."), COMPOUND_STRING("Baja la Velocidad\n" "cuando hay Espacio\n" "Raro.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_RoomService,
        .iconPalette = gItemIconPalette_RoomService,
    },

    [ITEM_UTILITY_UMBRELLA] =
    {
        .name = ES(ITEM_NAME("Utility Umbrella"), ITEM_NAME("Parasol Multiuso")),
        .price = (I_PRICE >= GEN_9) ? 15000 : 4000,
        .holdEffect = HOLD_EFFECT_UTILITY_UMBRELLA,
        .description = ES(COMPOUND_STRING("Protects from the\n"
            "effects of rain\n"
            "and harsh sunlight."), COMPOUND_STRING("Protege de los\n" "efectos de la lluvia\n" "y el sol.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_UtilityUmbrella,
        .iconPalette = gItemIconPalette_UtilityUmbrella,
    },

// Berries

    [ITEM_CHERI_BERRY] =
    {
        .name = ES(ITEM_NAME("Cheri Berry"), ITEM_NAME("Baya Zreza")),
        .pluralName = ITEM_PLURAL_NAME("Cheri Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CURE_PAR,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "heals paralysis\n"
            "in battle."), COMPOUND_STRING("Una baya muy rara en\n" "la región de\n" "Teselia.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_ParalyzeHeal,
        .flingPower = 10,
        .iconPic = gItemIcon_CheriBerry,
        .iconPalette = gItemIconPalette_CheriBerry,
    },

    [ITEM_CHESTO_BERRY] =
    {
        .name = ES(ITEM_NAME("Chesto Berry"), ITEM_NAME("Baya Atania")),
        .pluralName = ITEM_PLURAL_NAME("Chesto Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CURE_SLP,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "awakens Pokémon\n"
            "in battle."), COMPOUND_STRING("Una baya muy rara en\n" "la región de\n" "Teselia.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_Awakening,
        .flingPower = 10,
        .iconPic = gItemIcon_ChestoBerry,
        .iconPalette = gItemIconPalette_ChestoBerry,
    },

    [ITEM_PECHA_BERRY] =
    {
        .name = ES(ITEM_NAME("Pecha Berry"), ITEM_NAME("Baya Meloc")),
        .pluralName = ITEM_PLURAL_NAME("Pecha Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CURE_PSN,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "heals poisoning\n"
            "in battle."), COMPOUND_STRING("Una baya muy rara en\n" "la región de\n" "Teselia.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_Antidote,
        .flingPower = 10,
        .iconPic = gItemIcon_PechaBerry,
        .iconPalette = gItemIconPalette_PechaBerry,
    },

    [ITEM_RAWST_BERRY] =
    {
        .name = ES(ITEM_NAME("Rawst Berry"), ITEM_NAME("Baya Safre")),
        .pluralName = ITEM_PLURAL_NAME("Rawst Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CURE_BRN,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "heals a burn in\n"
            "battle."), COMPOUND_STRING("Cura una quemadura\n" "en combate.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_BurnHeal,
        .flingPower = 10,
        .iconPic = gItemIcon_RawstBerry,
        .iconPalette = gItemIconPalette_RawstBerry,
    },

    [ITEM_ASPEAR_BERRY] =
    {
        .name = ES(ITEM_NAME("Aspear Berry"), ITEM_NAME("Baya Perasi")),
        .pluralName = ITEM_PLURAL_NAME("Aspear Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CURE_FRZ,
        .description = COMPOUND_STRING(
            "A held item that\n"
        #if B_USE_FROSTBITE
            "heals frostbite\n"
        #else
            "defrosts Pokémon\n"
        #endif
            "in battle."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_IceHeal,
        .flingPower = 10,
        .iconPic = gItemIcon_AspearBerry,
        .iconPalette = gItemIconPalette_AspearBerry,
    },

    [ITEM_LEPPA_BERRY] =
    {
        .name = ES(ITEM_NAME("Leppa Berry"), ITEM_NAME("Baya Zanama")),
        .pluralName = ITEM_PLURAL_NAME("Leppa Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESTORE_PP,
        .holdEffectParam = 10,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "restores 10 PP in\n"
            "battle."), COMPOUND_STRING("Restaura 10 PP en\n" "combate.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU_MOVES,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = EFFECT_ITEM_RESTORE_PP,
        .effect = gItemEffect_LeppaBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_LeppaBerry,
        .iconPalette = gItemIconPalette_LeppaBerry,
    },

    [ITEM_ORAN_BERRY] =
    {
        .name = ES(ITEM_NAME("Oran Berry"), ITEM_NAME("Baya Aranja")),
        .pluralName = ITEM_PLURAL_NAME("Oran Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 10,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "restores 10 HP in\n"
            "battle."), COMPOUND_STRING("Restaura 10 PS en\n" "combate.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_OranBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_OranBerry,
        .iconPalette = gItemIconPalette_OranBerry,
    },

    [ITEM_PERSIM_BERRY] =
    {
        .name = ES(ITEM_NAME("Persim Berry"), ITEM_NAME("Baya Caquic")),
        .pluralName = ITEM_PLURAL_NAME("Persim Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CURE_CONFUSION,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "heals confusion\n"
            "in battle."), COMPOUND_STRING("Cura la confusión en\n" "combate.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_PersimBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_PersimBerry,
        .iconPalette = gItemIconPalette_PersimBerry,
    },

    [ITEM_LUM_BERRY] =
    {
        .name = ES(ITEM_NAME("Lum Berry"), ITEM_NAME("Baya Ziuela")),
        .pluralName = ITEM_PLURAL_NAME("Lum Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CURE_STATUS,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "heals any status\n"
            "problem in battle."), COMPOUND_STRING("Cura cualquier\n" "problema de estado\n" "en combate.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 10,
        .iconPic = gItemIcon_LumBerry,
        .iconPalette = gItemIconPalette_LumBerry,
    },

    [ITEM_SITRUS_BERRY] =
    {
        .name = ES(ITEM_NAME("Sitrus Berry"), ITEM_NAME("Baya Zidra")),
        .pluralName = ITEM_PLURAL_NAME("Sitrus Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
    #if I_SITRUS_BERRY_HEAL >= GEN_4
        .holdEffect = HOLD_EFFECT_RESTORE_PCT_HP,
        .holdEffectParam = 25,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "restores a little\n"
            "HP in battle."), COMPOUND_STRING("Una baya muy rara en\n" "la región de\n" "Teselia.")),
    #else
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 30,
        .description = COMPOUND_STRING(
            "A held item that\n"
            "restores 30 HP in\n"
            "battle."),
    #endif
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_SitrusBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_SitrusBerry,
        .iconPalette = gItemIconPalette_SitrusBerry,
    },

    [ITEM_FIGY_BERRY] =
    {
        .name = ES(ITEM_NAME("Figy Berry"), ITEM_NAME("Baya Higog")),
        .pluralName = ITEM_PLURAL_NAME("Figy Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CONFUSE_FLAVOR,
        .secondaryId = FLAVOR_SPICY,
        .holdEffectParam = CONFUSE_BERRY_HEAL_FRACTION,
        .description = ES(COMPOUND_STRING("Restores HP, but\n"
            "confuses if the\n"
            "flavor is hated."), COMPOUND_STRING("Una baya muy rara en\n" "la región de\n" "Teselia.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_FigyBerry,
        .iconPalette = gItemIconPalette_FigyBerry,
    },

    [ITEM_WIKI_BERRY] =
    {
        .name = ES(ITEM_NAME("Wiki Berry"), ITEM_NAME("Baya Wiki")),
        .pluralName = ITEM_PLURAL_NAME("Wiki Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CONFUSE_FLAVOR,
        .secondaryId = FLAVOR_DRY,
        .holdEffectParam = CONFUSE_BERRY_HEAL_FRACTION,
        .description = ES(COMPOUND_STRING("Restores HP, but\n"
            "confuses if the\n"
            "flavor is hated."), COMPOUND_STRING("Una baya muy rara en\n" "la región de\n" "Teselia.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_WikiBerry,
        .iconPalette = gItemIconPalette_WikiBerry,
    },

    [ITEM_MAGO_BERRY] =
    {
        .name = ES(ITEM_NAME("Mago Berry"), ITEM_NAME("Baya Ango")),
        .pluralName = ITEM_PLURAL_NAME("Mago Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CONFUSE_FLAVOR,
        .secondaryId = FLAVOR_SWEET,
        .holdEffectParam = CONFUSE_BERRY_HEAL_FRACTION,
        .description = ES(COMPOUND_STRING("Restores HP, but\n"
            "confuses if the\n"
            "flavor is hated."), COMPOUND_STRING("Una baya muy rara en\n" "la región de\n" "Teselia.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_MagoBerry,
        .iconPalette = gItemIconPalette_MagoBerry,
    },

    [ITEM_AGUAV_BERRY] =
    {
        .name = ES(ITEM_NAME("Aguav Berry"), ITEM_NAME("Baya Guaya")),
        .pluralName = ITEM_PLURAL_NAME("Aguav Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CONFUSE_FLAVOR,
        .secondaryId = FLAVOR_BITTER,
        .holdEffectParam = CONFUSE_BERRY_HEAL_FRACTION,
        .description = ES(COMPOUND_STRING("Restores HP, but\n"
            "confuses if the\n"
            "flavor is hated."), COMPOUND_STRING("Una baya muy rara en\n" "la región de\n" "Teselia.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_AguavBerry,
        .iconPalette = gItemIconPalette_AguavBerry,
    },

    [ITEM_IAPAPA_BERRY] =
    {
        .name = ES(ITEM_NAME("Iapapa Berry"), ITEM_NAME("Baya Pabaya")),
        .pluralName = ITEM_PLURAL_NAME("Iapapa Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CONFUSE_FLAVOR,
        .secondaryId = FLAVOR_SOUR,
        .holdEffectParam = CONFUSE_BERRY_HEAL_FRACTION,
        .description = ES(COMPOUND_STRING("Restores HP, but\n"
            "confuses if the\n"
            "flavor is hated."), COMPOUND_STRING("Una baya muy rara en\n" "la región de\n" "Teselia.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_IapapaBerry,
        .iconPalette = gItemIconPalette_IapapaBerry,
    },

    [ITEM_RAZZ_BERRY] =
    {
        .name = ES(ITEM_NAME("Razz Berry"), ITEM_NAME("Baya Frambu")),
        .pluralName = ITEM_PLURAL_NAME("Razz Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Razz."), COMPOUND_STRING("Una baya muy rara en\n" "la región de\n" "Teselia.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_RazzBerry,
        .iconPalette = gItemIconPalette_RazzBerry,
    },

    [ITEM_BLUK_BERRY] =
    {
        .name = ES(ITEM_NAME("Bluk Berry"), ITEM_NAME("Baya Oram")),
        .pluralName = ITEM_PLURAL_NAME("Bluk Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Bluk."), COMPOUND_STRING("Una baya muy rara en\n" "la región de\n" "Teselia.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_BlukBerry,
        .iconPalette = gItemIconPalette_BlukBerry,
    },

    [ITEM_NANAB_BERRY] =
    {
        .name = ES(ITEM_NAME("Nanab Berry"), ITEM_NAME("Baya Latano")),
        .pluralName = ITEM_PLURAL_NAME("Nanab Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Nanab."), COMPOUND_STRING("Una baya muy rara en\n" "la región de\n" "Teselia.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_NanabBerry,
        .iconPalette = gItemIconPalette_NanabBerry,
    },

    [ITEM_WEPEAR_BERRY] =
    {
        .name = ES(ITEM_NAME("Wepear Berry"), ITEM_NAME("Baya Peragu")),
        .pluralName = ITEM_PLURAL_NAME("Wepear Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Wepear."), COMPOUND_STRING("Para hacer\n" "{POKEBLOCK}. Se\n" "puede plantar.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_WepearBerry,
        .iconPalette = gItemIconPalette_WepearBerry,
    },

    [ITEM_PINAP_BERRY] =
    {
        .name = ES(ITEM_NAME("Pinap Berry"), ITEM_NAME("Baya Pinia")),
        .pluralName = ITEM_PLURAL_NAME("Pinap Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Pinap."), COMPOUND_STRING("Para hacer\n" "{POKEBLOCK}. Se\n" "puede plantar.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_PinapBerry,
        .iconPalette = gItemIconPalette_PinapBerry,
    },

    [ITEM_POMEG_BERRY] =
    {
        .name = ES(ITEM_NAME("Pomeg Berry"), ITEM_NAME("Baya Grana")),
        .pluralName = ITEM_PLURAL_NAME("Pomeg Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("Makes a Pokémon\n"
            "friendly but lowers\n"
            "base HP."), COMPOUND_STRING("Le coge cariño, pero\n" "baja la base de PS.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .effect = gItemEffect_PomegBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_PomegBerry,
        .iconPalette = gItemIconPalette_PomegBerry,
    },

    [ITEM_KELPSY_BERRY] =
    {
        .name = ES(ITEM_NAME("Kelpsy Berry"), ITEM_NAME("Baya Algama")),
        .pluralName = ITEM_PLURAL_NAME("Kelpsy Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("Makes a Pokémon\n"
            "friendly but lowers\n"
            "base Attack."), COMPOUND_STRING("Le coge cariño, pero\n" "baja la base de\n" "Ataque.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .effect = gItemEffect_KelpsyBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_KelpsyBerry,
        .iconPalette = gItemIconPalette_KelpsyBerry,
    },

    [ITEM_QUALOT_BERRY] =
    {
        .name = ES(ITEM_NAME("Qualot Berry"), ITEM_NAME("Baya Ispero")),
        .pluralName = ITEM_PLURAL_NAME("Qualot Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("Makes a Pokémon\n"
            "friendly but lowers\n"
            "base Defense."), COMPOUND_STRING("Le coge cariño, pero\n" "baja la base de\n" "Defensa.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .effect = gItemEffect_QualotBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_QualotBerry,
        .iconPalette = gItemIconPalette_QualotBerry,
    },

    [ITEM_HONDEW_BERRY] =
    {
        .name = ES(ITEM_NAME("Hondew Berry"), ITEM_NAME("Baya Meluce")),
        .pluralName = ITEM_PLURAL_NAME("Hondew Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("Makes a Pokémon\n"
            "friendly but lowers\n"
            "base Sp. Atk."), COMPOUND_STRING("Le coge cariño, pero\n" "baja la base de At.\n" "Esp.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .effect = gItemEffect_HondewBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_HondewBerry,
        .iconPalette = gItemIconPalette_HondewBerry,
    },

    [ITEM_GREPA_BERRY] =
    {
        .name = ES(ITEM_NAME("Grepa Berry"), ITEM_NAME("Baya Uvav")),
        .pluralName = ITEM_PLURAL_NAME("Grepa Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("Makes a Pokémon\n"
            "friendly but lowers\n"
            "base Sp. Def."), COMPOUND_STRING("Le coge cariño, pero\n" "baja la base de Def.\n" "Esp.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .effect = gItemEffect_GrepaBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_GrepaBerry,
        .iconPalette = gItemIconPalette_GrepaBerry,
    },

    [ITEM_TAMATO_BERRY] =
    {
        .name = ES(ITEM_NAME("Tamato Berry"), ITEM_NAME("Baya Tamate")),
        .pluralName = ITEM_PLURAL_NAME("Tamato Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("Makes a Pokémon\n"
            "friendly but lowers\n"
            "base Speed."), COMPOUND_STRING("Le coge cariño, pero\n" "baja la base de\n" "Velocidad.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .effect = gItemEffect_TamatoBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_TamatoBerry,
        .iconPalette = gItemIconPalette_TamatoBerry,
    },

    [ITEM_CORNN_BERRY] =
    {
        .name = ES(ITEM_NAME("Cornn Berry"), ITEM_NAME("Baya Mais")),
        .pluralName = ITEM_PLURAL_NAME("Cornn Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Cornn."), COMPOUND_STRING("Para hacer\n" "{POKEBLOCK}. Se\n" "puede plantar.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_CornnBerry,
        .iconPalette = gItemIconPalette_CornnBerry,
    },

    [ITEM_MAGOST_BERRY] =
    {
        .name = ES(ITEM_NAME("Magost Berry"), ITEM_NAME("Baya Aostan")),
        .pluralName = ITEM_PLURAL_NAME("Magost Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Magost."), COMPOUND_STRING("Para hacer\n" "{POKEBLOCK}. Se\n" "puede plantar.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_MagostBerry,
        .iconPalette = gItemIconPalette_MagostBerry,
    },

    [ITEM_RABUTA_BERRY] =
    {
        .name = ES(ITEM_NAME("Rabuta Berry"), ITEM_NAME("Baya Rautan")),
        .pluralName = ITEM_PLURAL_NAME("Rabuta Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Rabuta."), COMPOUND_STRING("Para hacer\n" "{POKEBLOCK}. Se\n" "puede plantar.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_RabutaBerry,
        .iconPalette = gItemIconPalette_RabutaBerry,
    },

    [ITEM_NOMEL_BERRY] =
    {
        .name = ES(ITEM_NAME("Nomel Berry"), ITEM_NAME("Baya Monli")),
        .pluralName = ITEM_PLURAL_NAME("Nomel Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Nomel."), COMPOUND_STRING("Para hacer\n" "{POKEBLOCK}. Se\n" "puede plantar.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_NomelBerry,
        .iconPalette = gItemIconPalette_NomelBerry,
    },

    [ITEM_SPELON_BERRY] =
    {
        .name = ES(ITEM_NAME("Spelon Berry"), ITEM_NAME("Baya Wikano")),
        .pluralName = ITEM_PLURAL_NAME("Spelon Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Spelon."), COMPOUND_STRING("Para hacer\n" "{POKEBLOCK}. Se\n" "puede plantar.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_SpelonBerry,
        .iconPalette = gItemIconPalette_SpelonBerry,
    },

    [ITEM_PAMTRE_BERRY] =
    {
        .name = ES(ITEM_NAME("Pamtre Berry"), ITEM_NAME("Baya Plama")),
        .pluralName = ITEM_PLURAL_NAME("Pamtre Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Pamtre."), COMPOUND_STRING("Para hacer\n" "{POKEBLOCK}. Se\n" "puede plantar.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_PamtreBerry,
        .iconPalette = gItemIconPalette_PamtreBerry,
    },

    [ITEM_WATMEL_BERRY] =
    {
        .name = ES(ITEM_NAME("Watmel Berry"), ITEM_NAME("Baya Sambia")),
        .pluralName = ITEM_PLURAL_NAME("Watmel Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Watmel."), COMPOUND_STRING("Para hacer\n" "{POKEBLOCK}. Se\n" "puede plantar.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_WatmelBerry,
        .iconPalette = gItemIconPalette_WatmelBerry,
    },

    [ITEM_DURIN_BERRY] =
    {
        .name = ES(ITEM_NAME("Durin Berry"), ITEM_NAME("Baya Rudion")),
        .pluralName = ITEM_PLURAL_NAME("Durin Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Durin."), COMPOUND_STRING("Para hacer\n" "{POKEBLOCK}. Se\n" "puede plantar.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_DurinBerry,
        .iconPalette = gItemIconPalette_DurinBerry,
    },

    [ITEM_BELUE_BERRY] =
    {
        .name = ES(ITEM_NAME("Belue Berry"), ITEM_NAME("Baya Andano")),
        .pluralName = ITEM_PLURAL_NAME("Belue Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Belue."), COMPOUND_STRING("Para hacer\n" "{POKEBLOCK}. Se\n" "puede plantar.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_BelueBerry,
        .iconPalette = gItemIconPalette_BelueBerry,
    },

    [ITEM_CHILAN_BERRY] =
    {
        .name = ES(ITEM_NAME("Chilan Berry"), ITEM_NAME("Baya Chilan")),
        .pluralName = ITEM_PLURAL_NAME("Chilan Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_NORMAL,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "weakens one\n"
            "Normal-type move."), COMPOUND_STRING("Debilita una vez un\n" "mov. de tipo Normal.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ChilanBerry,
        .iconPalette = gItemIconPalette_ChilanBerry,
    },

    [ITEM_OCCA_BERRY] =
    {
        .name = ES(ITEM_NAME("Occa Berry"), ITEM_NAME("Baya Caoca")),
        .pluralName = ITEM_PLURAL_NAME("Occa Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_FIRE,
        .description = ES(COMPOUND_STRING("Weakens one\n"
            "supereffective\n"
            "Fire-type move."), COMPOUND_STRING("Debilita un mov.\n" "Fuego supereficaz\n" "una vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_OccaBerry,
        .iconPalette = gItemIconPalette_OccaBerry,
    },

    [ITEM_PASSHO_BERRY] =
    {
        .name = ES(ITEM_NAME("Passho Berry"), ITEM_NAME("Baya Pasio")),
        .pluralName = ITEM_PLURAL_NAME("Passho Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_WATER,
        .description = ES(COMPOUND_STRING("Weakens one\n"
            "supereffective\n"
            "Water-type move."), COMPOUND_STRING("Debilita un mov.\n" "Agua supereficaz una\n" "vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_PasshoBerry,
        .iconPalette = gItemIconPalette_PasshoBerry,
    },

    [ITEM_WACAN_BERRY] =
    {
        .name = ES(ITEM_NAME("Wacan Berry"), ITEM_NAME("Baya Gualot")),
        .pluralName = ITEM_PLURAL_NAME("Wacan Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_ELECTRIC,
        .description = ES(COMPOUND_STRING("Weakens one\n"
            "supereffective\n"
            "Electric move."), COMPOUND_STRING("Debilita un mov.\n" "Eléctrico\n" "supereficaz una vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_WacanBerry,
        .iconPalette = gItemIconPalette_WacanBerry,
    },

    [ITEM_RINDO_BERRY] =
    {
        .name = ES(ITEM_NAME("Rindo Berry"), ITEM_NAME("Baya Tamar")),
        .pluralName = ITEM_PLURAL_NAME("Rindo Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_GRASS,
        .description = ES(COMPOUND_STRING("Weakens one\n"
            "supereffective\n"
            "Grass-type move."), COMPOUND_STRING("Debilita un mov.\n" "Planta supereficaz\n" "una vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_RindoBerry,
        .iconPalette = gItemIconPalette_RindoBerry,
    },

    [ITEM_YACHE_BERRY] =
    {
        .name = ES(ITEM_NAME("Yache Berry"), ITEM_NAME("Baya Rimoya")),
        .pluralName = ITEM_PLURAL_NAME("Yache Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_ICE,
        .description = ES(COMPOUND_STRING("Weakens one\n"
            "supereffective\n"
            "Ice-type move."), COMPOUND_STRING("Debilita un mov.\n" "Hielo supereficaz\n" "una vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_YacheBerry,
        .iconPalette = gItemIconPalette_YacheBerry,
    },

    [ITEM_CHOPLE_BERRY] =
    {
        .name = ES(ITEM_NAME("Chople Berry"), ITEM_NAME("Baya Pomaro")),
        .pluralName = ITEM_PLURAL_NAME("Chople Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_FIGHTING,
        .description = ES(COMPOUND_STRING("Weakens one\n"
            "supereffective\n"
            "Fighting move."), COMPOUND_STRING("Debilita un mov.\n" "Lucha supereficaz\n" "una vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ChopleBerry,
        .iconPalette = gItemIconPalette_ChopleBerry,
    },

    [ITEM_KEBIA_BERRY] =
    {
        .name = ES(ITEM_NAME("Kebia Berry"), ITEM_NAME("Baya Kebia")),
        .pluralName = ITEM_PLURAL_NAME("Kebia Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_POISON,
        .description = ES(COMPOUND_STRING("Weakens one\n"
            "supereffective\n"
            "Poison-type move."), COMPOUND_STRING("Debilita un mov.\n" "Veneno supereficaz\n" "una vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_KebiaBerry,
        .iconPalette = gItemIconPalette_KebiaBerry,
    },

    [ITEM_SHUCA_BERRY] =
    {
        .name = ES(ITEM_NAME("Shuca Berry"), ITEM_NAME("Baya Acardo")),
        .pluralName = ITEM_PLURAL_NAME("Shuca Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_GROUND,
        .description = ES(COMPOUND_STRING("Weakens one\n"
            "supereffective\n"
            "Ground-type move."), COMPOUND_STRING("Debilita un mov.\n" "Tierra supereficaz\n" "una vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ShucaBerry,
        .iconPalette = gItemIconPalette_ShucaBerry,
    },

    [ITEM_COBA_BERRY] =
    {
        .name = ES(ITEM_NAME("Coba Berry"), ITEM_NAME("Baya Kouba")),
        .pluralName = ITEM_PLURAL_NAME("Coba Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_FLYING,
        .description = ES(COMPOUND_STRING("Weakens one\n"
            "supereffective\n"
            "Flying-type move."), COMPOUND_STRING("Debilita un mov.\n" "Volador supereficaz\n" "una vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_CobaBerry,
        .iconPalette = gItemIconPalette_CobaBerry,
    },

    [ITEM_PAYAPA_BERRY] =
    {
        .name = ES(ITEM_NAME("Payapa Berry"), ITEM_NAME("Baya Payapa")),
        .pluralName = ITEM_PLURAL_NAME("Payapa Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_PSYCHIC,
        .description = ES(COMPOUND_STRING("Weakens one\n"
            "supereffective\n"
            "Psychic-type move."), COMPOUND_STRING("Debilita un mov.\n" "Psíquico supereficaz\n" "una vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_PayapaBerry,
        .iconPalette = gItemIconPalette_PayapaBerry,
    },

    [ITEM_TANGA_BERRY] =
    {
        .name = ES(ITEM_NAME("Tanga Berry"), ITEM_NAME("Baya Yecana")),
        .pluralName = ITEM_PLURAL_NAME("Tanga Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_BUG,
        .description = ES(COMPOUND_STRING("Weakens one\n"
            "supereffective\n"
            "Bug-type move."), COMPOUND_STRING("Debilita un mov.\n" "Bicho supereficaz\n" "una vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_TangaBerry,
        .iconPalette = gItemIconPalette_TangaBerry,
    },

    [ITEM_CHARTI_BERRY] =
    {
        .name = ES(ITEM_NAME("Charti Berry"), ITEM_NAME("Baya Alcho")),
        .pluralName = ITEM_PLURAL_NAME("Charti Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_ROCK,
        .description = ES(COMPOUND_STRING("Weakens one\n"
            "supereffective\n"
            "Rock-type move."), COMPOUND_STRING("Debilita un mov.\n" "Roca supereficaz una\n" "vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ChartiBerry,
        .iconPalette = gItemIconPalette_ChartiBerry,
    },

    [ITEM_KASIB_BERRY] =
    {
        .name = ES(ITEM_NAME("Kasib Berry"), ITEM_NAME("Baya Drasi")),
        .pluralName = ITEM_PLURAL_NAME("Kasib Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_GHOST,
        .description = ES(COMPOUND_STRING("Weakens one\n"
            "supereffective\n"
            "Ghost-type move."), COMPOUND_STRING("Debilita un mov.\n" "Fantasma supereficaz\n" "una vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_KasibBerry,
        .iconPalette = gItemIconPalette_KasibBerry,
    },

    [ITEM_HABAN_BERRY] =
    {
        .name = ES(ITEM_NAME("Haban Berry"), ITEM_NAME("Baya Anjiro")),
        .pluralName = ITEM_PLURAL_NAME("Haban Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_DRAGON,
        .description = ES(COMPOUND_STRING("Weakens one\n"
            "supereffective\n"
            "Dragon-type move."), COMPOUND_STRING("Debilita un mov.\n" "Dragón supereficaz\n" "una vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_HabanBerry,
        .iconPalette = gItemIconPalette_HabanBerry,
    },

    [ITEM_COLBUR_BERRY] =
    {
        .name = ES(ITEM_NAME("Colbur Berry"), ITEM_NAME("Baya Dillo")),
        .pluralName = ITEM_PLURAL_NAME("Colbur Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_DARK,
        .description = ES(COMPOUND_STRING("Weakens one\n"
            "supereffective\n"
            "Dark-type move."), COMPOUND_STRING("Debilita un mov.\n" "Siniestro\n" "supereficaz una vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ColburBerry,
        .iconPalette = gItemIconPalette_ColburBerry,
    },

    [ITEM_BABIRI_BERRY] =
    {
        .name = ES(ITEM_NAME("Babiri Berry"), ITEM_NAME("Baya Baribá")),
        .pluralName = ITEM_PLURAL_NAME("Babiri Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_STEEL,
        .description = ES(COMPOUND_STRING("Weakens one\n"
            "supereffective\n"
            "Steel-type move."), COMPOUND_STRING("Debilita un mov.\n" "Acero supereficaz\n" "una vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_BabiriBerry,
        .iconPalette = gItemIconPalette_BabiriBerry,
    },

    [ITEM_ROSELI_BERRY] =
    {
        .name = ES(ITEM_NAME("Roseli Berry"), ITEM_NAME("Baya Hibis")),
        .pluralName = ITEM_PLURAL_NAME("Roseli Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_FAIRY,
        .description = ES(COMPOUND_STRING("Weakens one\n"
            "supereffective\n"
            "Fairy-type move."), COMPOUND_STRING("Debilita un mov.\n" "Hada supereficaz una\n" "vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_RoseliBerry,
        .iconPalette = gItemIconPalette_RoseliBerry,
    },

    [ITEM_LIECHI_BERRY] =
    {
        .name = ES(ITEM_NAME("Liechi Berry"), ITEM_NAME("Baya Lichi")),
        .pluralName = ITEM_PLURAL_NAME("Liechi Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_ATTACK_UP,
        .holdEffectParam = 4,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises Attack in\n"
            "a pinch."), COMPOUND_STRING("Sube el Ataque en un\n" "apuro.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_LiechiBerry,
        .iconPalette = gItemIconPalette_LiechiBerry,
    },

    [ITEM_GANLON_BERRY] =
    {
        .name = ES(ITEM_NAME("Ganlon Berry"), ITEM_NAME("Baya Gonlan")),
        .pluralName = ITEM_PLURAL_NAME("Ganlon Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_DEFENSE_UP,
        .holdEffectParam = 4,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises Defense in\n"
            "a pinch."), COMPOUND_STRING("Sube la Defensa en\n" "un apuro.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_GanlonBerry,
        .iconPalette = gItemIconPalette_GanlonBerry,
    },

    [ITEM_SALAC_BERRY] =
    {
        .name = ES(ITEM_NAME("Salac Berry"), ITEM_NAME("Baya Aslac")),
        .pluralName = ITEM_PLURAL_NAME("Salac Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_SPEED_UP,
        .holdEffectParam = 4,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises Speed in\n"
            "a pinch."), COMPOUND_STRING("Sube la Velocidad en\n" "un apuro.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_SalacBerry,
        .iconPalette = gItemIconPalette_SalacBerry,
    },

    [ITEM_PETAYA_BERRY] =
    {
        .name = ES(ITEM_NAME("Petaya Berry"), ITEM_NAME("Baya Yapati")),
        .pluralName = ITEM_PLURAL_NAME("Petaya Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_SP_ATTACK_UP,
        .holdEffectParam = 4,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises Sp. Atk in\n"
            "a pinch."), COMPOUND_STRING("Sube el At. Esp. en\n" "un apuro.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_PetayaBerry,
        .iconPalette = gItemIconPalette_PetayaBerry,
    },

    [ITEM_APICOT_BERRY] =
    {
        .name = ES(ITEM_NAME("Apicot Berry"), ITEM_NAME("Baya Aricoc")),
        .pluralName = ITEM_PLURAL_NAME("Apicot Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_SP_DEFENSE_UP,
        .holdEffectParam = 4,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises Sp. Def in\n"
            "a pinch."), COMPOUND_STRING("Sube la Def. Esp. en\n" "un apuro.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ApicotBerry,
        .iconPalette = gItemIconPalette_ApicotBerry,
    },

    [ITEM_LANSAT_BERRY] =
    {
        .name = ES(ITEM_NAME("Lansat Berry"), ITEM_NAME("Baya Zonlan")),
        .pluralName = ITEM_PLURAL_NAME("Lansat Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CRITICAL_UP,
        .holdEffectParam = 4,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "ups the critical-\n"
            "hit rate in a pinch."), COMPOUND_STRING("Sube el índice de\n" "golpe crítico en un\n" "apuro.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_LansatBerry,
        .iconPalette = gItemIconPalette_LansatBerry,
    },

    [ITEM_STARF_BERRY] =
    {
        .name = ES(ITEM_NAME("Starf Berry"), ITEM_NAME("Baya Arabol")),
        .pluralName = ITEM_PLURAL_NAME("Starf Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RANDOM_STAT_UP,
        .holdEffectParam = 4,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "sharply raises a\n"
            "stat in a pinch."), COMPOUND_STRING("Sube mucho una\n" "característica en un\n" "apuro.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_StarfBerry,
        .iconPalette = gItemIconPalette_StarfBerry,
    },

    [ITEM_ENIGMA_BERRY] =
    {
        .name = ES(ITEM_NAME("Enigma Berry"), ITEM_NAME("Baya Enigma")),
        .pluralName = ITEM_PLURAL_NAME("Enigma Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_ENIGMA_BERRY,
        .description = ES(COMPOUND_STRING("Restores HP when\n"
            "hit by a super\n"
            "effective move."), COMPOUND_STRING("Cura PS al recibir\n" "un mov. supereficaz.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_EnigmaBerry,
        .iconPalette = gItemIconPalette_EnigmaBerry,
    },

    [ITEM_MICLE_BERRY] =
    {
        .name = ES(ITEM_NAME("Micle Berry"), ITEM_NAME("Baya Lagro")),
        .pluralName = ITEM_PLURAL_NAME("Micle Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_MICLE_BERRY,
        .holdEffectParam = 4,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "boosts accuracy in\n"
            "a pinch."), COMPOUND_STRING("Sube la precisión en\n" "un apuro.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_MicleBerry,
        .iconPalette = gItemIconPalette_MicleBerry,
    },

    [ITEM_CUSTAP_BERRY] =
    {
        .name = ES(ITEM_NAME("Custap Berry"), ITEM_NAME("Baya Chiri")),
        .pluralName = ITEM_PLURAL_NAME("Custap Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CUSTAP_BERRY,
        .holdEffectParam = 4,
        .description = ES(COMPOUND_STRING("The holder gets\n"
            "to move first just\n"
            "once in a pinch."), COMPOUND_STRING("En un apuro, actúa\n" "primero una vez.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_CustapBerry,
        .iconPalette = gItemIconPalette_CustapBerry,
    },

    [ITEM_JABOCA_BERRY] =
    {
        .name = ES(ITEM_NAME("Jaboca Berry"), ITEM_NAME("Baya Jaboca")),
        .pluralName = ITEM_PLURAL_NAME("Jaboca Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_JABOCA_BERRY,
        .description = ES(COMPOUND_STRING("If hit by a physical\n"
            "move, the foe will\n"
            "also take damage."), COMPOUND_STRING("Si recibe un ataque\n" "físico, daña al\n" "rival.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_JabocaBerry,
        .iconPalette = gItemIconPalette_JabocaBerry,
    },

    [ITEM_ROWAP_BERRY] =
    {
        .name = ES(ITEM_NAME("Rowap Berry"), ITEM_NAME("Baya Magua")),
        .pluralName = ITEM_PLURAL_NAME("Rowap Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_ROWAP_BERRY,
        .description = ES(COMPOUND_STRING("If hit by a special\n"
            "move, the foe will\n"
            "also take damage."), COMPOUND_STRING("El Pokémon que lleva\n" "esta piedra mágica\n" "no evoluciona.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_RowapBerry,
        .iconPalette = gItemIconPalette_RowapBerry,
    },

    [ITEM_KEE_BERRY] =
    {
        .name = ES(ITEM_NAME("Kee Berry"), ITEM_NAME("Baya Biglia")),
        .pluralName = ITEM_PLURAL_NAME("Kee Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_KEE_BERRY,
        .description = ES(COMPOUND_STRING("If hit by a physical\n"
            "move, it raises the\n"
            "holder's Defense."), COMPOUND_STRING("Si recibe un ataque\n" "físico, sube la\n" "Defensa.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_KeeBerry,
        .iconPalette = gItemIconPalette_KeeBerry,
    },

    [ITEM_MARANGA_BERRY] =
    {
        .name = ES(ITEM_NAME("Maranga Berry"), ITEM_NAME("Baya Maranga")),
        .pluralName = ITEM_PLURAL_NAME("Maranga Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_MARANGA_BERRY,
        .description = ES(COMPOUND_STRING("If hit by a special\n"
            "move, it raises the\n"
            "holder's Sp. Def."), COMPOUND_STRING("Si recibe un ataque\n" "especial, sube la\n" "Def. Esp.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_MarangaBerry,
        .iconPalette = gItemIconPalette_MarangaBerry,
    },

    [ITEM_ENIGMA_BERRY_E_READER] =
    {
        .name = ES(ITEM_NAME("Enigma Berry"), ITEM_NAME("Baya Enigma")),
        .pluralName = ITEM_PLURAL_NAME("Enigma Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = ES(COMPOUND_STRING("{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow a mystery."), COMPOUND_STRING("Ingrediente de\n" "{POKEBLOCK}.\n" "Plántala y verás.")),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU, // Type handled by ItemUseOutOfBattle_EnigmaBerry
        .fieldUseFunc = ItemUseOutOfBattle_EnigmaBerry,
        .battleUsage = EFFECT_ITEM_ENIGMA_BERRY_EREADER,
        .flingPower = 10,
        .iconPic = gItemIcon_EnigmaBerry,
        .iconPalette = gItemIconPalette_EnigmaBerry,
    },

// TMs/HMs. They don't have a set flingPower, as that's handled by GetFlingPowerFromItemId.

    [ITEM_TM_FOCUS_PUNCH] =
    {
        .name = ES(ITEM_NAME("TM01"), ITEM_NAME("MT01")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Powerful, but fails\n"
            "if the user is\n"
            "hit by the foe."), COMPOUND_STRING("Potente, pero falla\n" "si el rival le\n" "golpea antes.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_DRAGON_CLAW] =
    {
        .name = ES(ITEM_NAME("TM02"), ITEM_NAME("MT02")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Hooks and slashes\n"
            "the foe with long,\n"
            "sharp claws."), COMPOUND_STRING("Araña al rival con\n" "garras largas y\n" "afiladas.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_WATER_PULSE] =
    {
        .name = ES(ITEM_NAME("TM03"), ITEM_NAME("MT03")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Generates an\n"
            "ultrasonic wave\n"
            "that may confuse."), COMPOUND_STRING("Ondas ultrasónicas\n" "que pueden\n" "confundir.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_CALM_MIND] =
    {
        .name = ES(ITEM_NAME("TM04"), ITEM_NAME("MT04")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Raises Sp. Atk and\n"
            "Sp. Def by focusing\n"
            "the mind."), COMPOUND_STRING("Se concentra y sube\n" "el At. Esp. y la\n" "Def. Esp.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_ROAR] =
    {
        .name = ES(ITEM_NAME("TM05"), ITEM_NAME("MT05")),
        .price = 1000,
        .description = ES(COMPOUND_STRING("A roar that makes\n"
            "the foe switch or\n"
            "ends the battle."), COMPOUND_STRING("Un rugido que cambia\n" "al rival o acaba el\n" "combate.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_TOXIC] =
    {
        .name = ES(ITEM_NAME("TM06"), ITEM_NAME("MT06")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Poisons the foe\n"
            "with a toxin that\n"
            "gradually worsens."), COMPOUND_STRING("Envenena con una\n" "toxina que empeora\n" "poco a poco.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_HAIL] =
    {
        .name = ES(ITEM_NAME("TM07"), ITEM_NAME("MT07")),
        .price = 3000,
        .description = COMPOUND_STRING(
        #if B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_SNOW
            "Boosts the\n"
            "Defense of Ice-\n"
            "types for 5 turns."),
        #else
            "Damages all\n"
            "types except Ice\n"
            "for 5 turns."),
        #endif
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_BULK_UP] =
    {
        .name = ES(ITEM_NAME("TM08"), ITEM_NAME("MT08")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Bulks up the body\n"
            "to raise both\n"
            "Attack & Defense."), COMPOUND_STRING("Tensa el cuerpo y\n" "sube el Ataque y la\n" "Defensa.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_BULLET_SEED] =
    {
        .name = ES(ITEM_NAME("TM09"), ITEM_NAME("MT09")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Shoots 2 to 5 seeds\n"
            "in a row to strike\n"
            "the foe."), COMPOUND_STRING("Dispara de 2 a 5\n" "semillas seguidas.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_HIDDEN_POWER] =
    {
        .name = ES(ITEM_NAME("TM10"), ITEM_NAME("MT10")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("The type\n"
            "varies among\n"
            "different Pokémon."), COMPOUND_STRING("Su tipo depende del\n" "Pokémon que lo usa.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SUNNY_DAY] =
    {
        .name = ES(ITEM_NAME("TM11"), ITEM_NAME("MT11")),
        .price = 2000,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of Fire-type moves\n"
            "for 5 turns."), COMPOUND_STRING("Potencia los mov.\n" "Fuego durante 5\n" "turnos.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_TAUNT] =
    {
        .name = ES(ITEM_NAME("TM12"), ITEM_NAME("MT12")),
        .price = 3000,
        .description = COMPOUND_STRING(
            "The foe can only\n"
            "use attack moves\n"
        #if B_TAUNT_TURNS >= GEN_5
            "for 3 turns."),
        #elif B_TAUNT_TURNS == GEN_4
            "for 2 to 4 turns."),
        #else
            "for 2 turns."),
        #endif
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_ICE_BEAM] =
    {
        .name = ES(ITEM_NAME("TM13"), ITEM_NAME("MT13")),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Fires an icy cold\n"
            "beam that may\n"
        #if B_USE_FROSTBITE
            "cause frostbite."),
        #else
            "freeze the foe."),
        #endif
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_BLIZZARD] =
    {
        .name = ES(ITEM_NAME("TM14"), ITEM_NAME("MT14")),
        .price = 5500,
        .description = COMPOUND_STRING(
        #if B_USE_FROSTBITE
            "A snow-and-wind\n"
            "attack that may\n"
            "cause frostbite."),
        #else
            "A brutal snow-and-\n"
            "wind attack that\n"
            "may freeze the foe."),
        #endif
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_HYPER_BEAM] =
    {
        .name = ES(ITEM_NAME("TM15"), ITEM_NAME("MT15")),
        .price = 7500,
        .description = COMPOUND_STRING(
        #if B_SKIP_RECHARGE != GEN_1
            "Powerful, but needs\n"
            "recharging the\n"
            "next turn."),
        #else
            "Needs recharging if\n"
            "it doesn't knock\n"
            "out the target."),
        #endif
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_LIGHT_SCREEN] =
    {
        .name = ES(ITEM_NAME("TM16"), ITEM_NAME("MT16")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Creates a wall of\n"
            "light that reduces\n"
            "special damage."), COMPOUND_STRING("Una barrera de luz\n" "que reduce el daño\n" "especial.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_PROTECT] =
    {
        .name = ES(ITEM_NAME("TM17"), ITEM_NAME("MT17")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Negates all damage,\n"
            "but may fail if used\n"
            "in succession."), COMPOUND_STRING("Evita todo el daño;\n" "puede fallar si se\n" "repite.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_RAIN_DANCE] =
    {
        .name = ES(ITEM_NAME("TM18"), ITEM_NAME("MT18")),
        .price = 2000,
        .description = ES(COMPOUND_STRING("Boosts the power\n"
            "of Water-type\n"
            "moves for 5 turns."), COMPOUND_STRING("Potencia los mov.\n" "Agua durante 5\n" "turnos.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_GIGA_DRAIN] =
    {
        .name = ES(ITEM_NAME("TM19"), ITEM_NAME("MT19")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Recovers half the\n"
            "HP of the damage \n"
            "this move inflicts."), COMPOUND_STRING("Recupera la mitad\n" "del daño que causa.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SAFEGUARD] =
    {
        .name = ES(ITEM_NAME("TM20"), ITEM_NAME("MT20")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Guards allies from\n"
            "status problems\n"
            "for 5 turns."), COMPOUND_STRING("Protege del estado\n" "al equipo durante 5\n" "turnos.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_FRUSTRATION] =
    {
        .name = ES(ITEM_NAME("TM21"), ITEM_NAME("MT21")),
        .price = 1000,
        .description = ES(COMPOUND_STRING("The less the user\n"
            "likes you, the more\n"
            "powerful this move."), COMPOUND_STRING("Más fuerte cuanto\n" "menos aprecio le\n" "tenga.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SOLAR_BEAM] =
    {
        .name = ES(ITEM_NAME("TM22"), ITEM_NAME("MT22")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Absorbs sunlight in\n"
            "the 1st turn, then\n"
            "attacks next turn."), COMPOUND_STRING("Absorbe luz un turno\n" "y ataca en el\n" "siguiente.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_IRON_TAIL] =
    {
        .name = ES(ITEM_NAME("TM23"), ITEM_NAME("MT23")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Slams the foe with\n"
            "a hard tail. It may\n"
            "lower Defense."), COMPOUND_STRING("Golpea con la cola\n" "dura. Puede bajar la\n" "Defensa.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_THUNDERBOLT] =
    {
        .name = ES(ITEM_NAME("TM24"), ITEM_NAME("MT24")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("A powerful electric\n"
            "attack that may\n"
            "cause paralysis."), COMPOUND_STRING("Potente ataque\n" "eléctrico. Puede\n" "paralizar.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_THUNDER] =
    {
        .name = ES(ITEM_NAME("TM25"), ITEM_NAME("MT25")),
        .price = 5500,
        .description = ES(COMPOUND_STRING("Strikes the foe\n"
            "with a thunderbolt.\n"
            "It may paralyze."), COMPOUND_STRING("Lanza un rayo al\n" "rival. Puede\n" "paralizar.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_EARTHQUAKE] =
    {
        .name = ES(ITEM_NAME("TM26"), ITEM_NAME("MT26")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Causes a quake\n"
            "that hits all\n"
            "other Pokémon."), COMPOUND_STRING("Un terremoto que\n" "golpea a todos los\n" "demás.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_RETURN] =
    {
        .name = ES(ITEM_NAME("TM27"), ITEM_NAME("MT27")),
        .price = 1000,
        .description = ES(COMPOUND_STRING("The more the user\n"
            "likes you, the more\n"
            "powerful this move."), COMPOUND_STRING("Más fuerte cuanto\n" "más aprecio le\n" "tenga.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_DIG] =
    {
        .name = ES(ITEM_NAME("TM28"), ITEM_NAME("MT28")),
        .price = 2000,
        .description = ES(COMPOUND_STRING("Digs underground\n"
            "the 1st turn, then\n"
            "strikes next turn."), COMPOUND_STRING("Excava el 1.er turno\n" "y ataca en el\n" "siguiente.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_PSYCHIC] =
    {
        .name = ES(ITEM_NAME("TM29"), ITEM_NAME("MT29")),
        .price = 2000,
        .description = ES(COMPOUND_STRING("A powerful psychic\n"
            "attack that may\n"
            "lower Sp. Def."), COMPOUND_STRING("Potente ataque\n" "psíquico. Puede\n" "bajar la Def. Esp.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SHADOW_BALL] =
    {
        .name = ES(ITEM_NAME("TM30"), ITEM_NAME("MT30")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Hurls a dark lump\n"
            "at the foe. It may\n"
            "lower Sp. Def."), COMPOUND_STRING("Lanza una sombra.\n" "Puede bajar la Def.\n" "Esp.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_BRICK_BREAK] =
    {
        .name = ES(ITEM_NAME("TM31"), ITEM_NAME("MT31")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Destroys barriers\n"
            "like Light Screen\n"
            "and causes damage."), COMPOUND_STRING("Rompe barreras como\n" "Pantalla de Luz y\n" "daña.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_DOUBLE_TEAM] =
    {
        .name = ES(ITEM_NAME("TM32"), ITEM_NAME("MT32")),
        .price = 2000,
        .description = ES(COMPOUND_STRING("Creates illusory\n"
            "copies to raise\n"
            "evasiveness."), COMPOUND_STRING("Crea copias\n" "ilusorias y sube la\n" "evasión.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_REFLECT] =
    {
        .name = ES(ITEM_NAME("TM33"), ITEM_NAME("MT33")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Creates a wall of\n"
            "light that weakens\n"
            "physical attacks."), COMPOUND_STRING("Una barrera de luz\n" "que reduce el daño\n" "físico.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SHOCK_WAVE] =
    {
        .name = ES(ITEM_NAME("TM34"), ITEM_NAME("MT34")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Zaps the foe with a\n"
            "jolt of electricity\n"
            "that never misses."), COMPOUND_STRING("Una descarga\n" "eléctrica que nunca\n" "falla.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_FLAMETHROWER] =
    {
        .name = ES(ITEM_NAME("TM35"), ITEM_NAME("MT35")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Looses a stream of\n"
            "fire that may burn\n"
            "the foe."), COMPOUND_STRING("Lanza un chorro de\n" "fuego. Puede quemar.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SLUDGE_BOMB] =
    {
        .name = ES(ITEM_NAME("TM36"), ITEM_NAME("MT36")),
        .price = 1000,
        .description = ES(COMPOUND_STRING("Hurls sludge at the\n"
            "foe. It may poison\n"
            "the foe."), COMPOUND_STRING("Lanza lodo al rival.\n" "Puede envenenar.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SANDSTORM] =
    {
        .name = ES(ITEM_NAME("TM37"), ITEM_NAME("MT37")),
        .price = 2000,
        .description = ES(COMPOUND_STRING("Causes a sandstorm\n"
            "that hits\n"
            "over 5 turns."), COMPOUND_STRING("Crea una tormenta de\n" "arena de 5 turnos.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_FIRE_BLAST] =
    {
        .name = ES(ITEM_NAME("TM38"), ITEM_NAME("MT38")),
        .price = 5500,
        .description = ES(COMPOUND_STRING("A powerful fire\n"
            "attack that may\n"
            "burn the foe."), COMPOUND_STRING("Potente ataque de\n" "fuego. Puede quemar.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_ROCK_TOMB] =
    {
        .name = ES(ITEM_NAME("TM39"), ITEM_NAME("MT39")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Stops the foe from\n"
            "moving with rocks.\n"
            "May lower Speed."), COMPOUND_STRING("Bloquea al rival con\n" "rocas y baja su\n" "Velocidad.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_AERIAL_ACE] =
    {
        .name = ES(ITEM_NAME("TM40"), ITEM_NAME("MT40")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("An extremely fast\n"
            "attack that can't\n"
            "be avoided."), COMPOUND_STRING("Un ataque rapidísimo\n" "que no se puede\n" "esquivar.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_TORMENT] =
    {
        .name = ES(ITEM_NAME("TM41"), ITEM_NAME("MT41")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Prevents the foe\n"
            "from using the same\n"
            "move in a row."), COMPOUND_STRING("Impide que el rival\n" "repita el mismo mov.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_FACADE] =
    {
        .name = ES(ITEM_NAME("TM42"), ITEM_NAME("MT42")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Boosts power when\n"
            "poisoned, burned,\n"
            "or paralyzed."), COMPOUND_STRING("Más potencia si está\n" "envenenado, quemado\n" "o paralizado.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SECRET_POWER] =
    {
        .name = ES(ITEM_NAME("TM43"), ITEM_NAME("MT43")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Adds an effect to\n"
            "attack depending\n"
            "on the location."), COMPOUND_STRING("Su efecto depende\n" "del lugar.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_REST] =
    {
        .name = ES(ITEM_NAME("TM44"), ITEM_NAME("MT44")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("The user sleeps for\n"
            "2 turns to restore\n"
            "health and status."), COMPOUND_STRING("Duerme 2 turnos y\n" "recupera sus PS y su\n" "estado.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_ATTRACT] =
    {
        .name = ES(ITEM_NAME("TM45"), ITEM_NAME("MT45")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Makes it tough for\n"
            "the opposite\n"
            "gender to attack."), COMPOUND_STRING("El sexo opuesto\n" "atacará menos.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_THIEF] =
    {
        .name = ES(ITEM_NAME("TM46"), ITEM_NAME("MT46")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("While attacking,\n"
            "it steals the\n"
            "foe's held item."), COMPOUND_STRING("Al atacar, roba el\n" "objeto del rival.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_STEEL_WING] =
    {
        .name = ES(ITEM_NAME("TM47"), ITEM_NAME("MT47")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Slams into the\n"
            "foe. This may\n"
            "raise Defense."), COMPOUND_STRING("Golpea con alas\n" "duras. Puede subir\n" "la Defensa.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SKILL_SWAP] =
    {
        .name = ES(ITEM_NAME("TM48"), ITEM_NAME("MT48")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Switches Abilities\n"
            "with the foe on the\n"
            "turn this is used."), COMPOUND_STRING("Intercambia la\n" "habilidad con el\n" "rival.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SNATCH] =
    {
        .name = ES(ITEM_NAME("TM49"), ITEM_NAME("MT49")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Steals the next\n"
            "healing or stat-\n"
            "changing move."), COMPOUND_STRING("Roba el siguiente\n" "mov. de curación o\n" "de caract.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_OVERHEAT] =
    {
        .name = ES(ITEM_NAME("TM50"), ITEM_NAME("MT50")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("Enables full-power\n"
            "attack, but harshly\n"
            "lowers Sp. Atk."), COMPOUND_STRING("Ataca con todo, pero\n" "baja mucho su At.\n" "Esp.")),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM51] =
    {
        .name = ES(ITEM_NAME("TM51"), ITEM_NAME("MT51")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM52] =
    {
        .name = ES(ITEM_NAME("TM52"), ITEM_NAME("MT52")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM53] =
    {
        .name = ES(ITEM_NAME("TM53"), ITEM_NAME("MT53")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM54] =
    {
        .name = ES(ITEM_NAME("TM54"), ITEM_NAME("MT54")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM55] =
    {
        .name = ES(ITEM_NAME("TM55"), ITEM_NAME("MT55")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM56] =
    {
        .name = ES(ITEM_NAME("TM56"), ITEM_NAME("MT56")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM57] =
    {
        .name = ES(ITEM_NAME("TM57"), ITEM_NAME("MT57")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM58] =
    {
        .name = ES(ITEM_NAME("TM58"), ITEM_NAME("MT58")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM59] =
    {
        .name = ES(ITEM_NAME("TM59"), ITEM_NAME("MT59")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM60] =
    {
        .name = ES(ITEM_NAME("TM60"), ITEM_NAME("MT60")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM61] =
    {
        .name = ES(ITEM_NAME("TM61"), ITEM_NAME("MT61")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM62] =
    {
        .name = ES(ITEM_NAME("TM62"), ITEM_NAME("MT62")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM63] =
    {
        .name = ES(ITEM_NAME("TM63"), ITEM_NAME("MT63")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM64] =
    {
        .name = ES(ITEM_NAME("TM64"), ITEM_NAME("MT64")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM65] =
    {
        .name = ES(ITEM_NAME("TM65"), ITEM_NAME("MT65")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM66] =
    {
        .name = ES(ITEM_NAME("TM66"), ITEM_NAME("MT66")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM67] =
    {
        .name = ES(ITEM_NAME("TM67"), ITEM_NAME("MT67")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM68] =
    {
        .name = ES(ITEM_NAME("TM68"), ITEM_NAME("MT68")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM69] =
    {
        .name = ES(ITEM_NAME("TM69"), ITEM_NAME("MT69")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM70] =
    {
        .name = ES(ITEM_NAME("TM70"), ITEM_NAME("MT70")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM71] =
    {
        .name = ES(ITEM_NAME("TM71"), ITEM_NAME("MT71")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM72] =
    {
        .name = ES(ITEM_NAME("TM72"), ITEM_NAME("MT72")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM73] =
    {
        .name = ES(ITEM_NAME("TM73"), ITEM_NAME("MT73")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM74] =
    {
        .name = ES(ITEM_NAME("TM74"), ITEM_NAME("MT74")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM75] =
    {
        .name = ES(ITEM_NAME("TM75"), ITEM_NAME("MT75")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM76] =
    {
        .name = ES(ITEM_NAME("TM76"), ITEM_NAME("MT76")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM77] =
    {
        .name = ES(ITEM_NAME("TM77"), ITEM_NAME("MT77")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM78] =
    {
        .name = ES(ITEM_NAME("TM78"), ITEM_NAME("MT78")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM79] =
    {
        .name = ES(ITEM_NAME("TM79"), ITEM_NAME("MT79")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM80] =
    {
        .name = ES(ITEM_NAME("TM80"), ITEM_NAME("MT80")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM81] =
    {
        .name = ES(ITEM_NAME("TM81"), ITEM_NAME("MT81")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM82] =
    {
        .name = ES(ITEM_NAME("TM82"), ITEM_NAME("MT82")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM83] =
    {
        .name = ES(ITEM_NAME("TM83"), ITEM_NAME("MT83")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM84] =
    {
        .name = ES(ITEM_NAME("TM84"), ITEM_NAME("MT84")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM85] =
    {
        .name = ES(ITEM_NAME("TM85"), ITEM_NAME("MT85")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM86] =
    {
        .name = ES(ITEM_NAME("TM86"), ITEM_NAME("MT86")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM87] =
    {
        .name = ES(ITEM_NAME("TM87"), ITEM_NAME("MT87")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM88] =
    {
        .name = ES(ITEM_NAME("TM88"), ITEM_NAME("MT88")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM89] =
    {
        .name = ES(ITEM_NAME("TM89"), ITEM_NAME("MT89")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM90] =
    {
        .name = ES(ITEM_NAME("TM90"), ITEM_NAME("MT90")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM91] =
    {
        .name = ES(ITEM_NAME("TM91"), ITEM_NAME("MT91")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM92] =
    {
        .name = ES(ITEM_NAME("TM92"), ITEM_NAME("MT92")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM93] =
    {
        .name = ES(ITEM_NAME("TM93"), ITEM_NAME("MT93")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM94] =
    {
        .name = ES(ITEM_NAME("TM94"), ITEM_NAME("MT94")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM95] =
    {
        .name = ES(ITEM_NAME("TM95"), ITEM_NAME("MT95")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM96] =
    {
        .name = ES(ITEM_NAME("TM96"), ITEM_NAME("MT96")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM97] =
    {
        .name = ES(ITEM_NAME("TM97"), ITEM_NAME("MT97")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM98] =
    {
        .name = ES(ITEM_NAME("TM98"), ITEM_NAME("MT98")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM99] =
    {
        .name = ES(ITEM_NAME("TM99"), ITEM_NAME("MT99")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM100] =
    {
        .name = ES(ITEM_NAME("TM100"), ITEM_NAME("MT100")),
        .price = 3000,
        .description = COMPOUND_STRING("?????"), // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM_CUT] =
    {
        .name = ES(ITEM_NAME("HM01"), ITEM_NAME("MO01")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Attacks the foe\n"
            "with sharp blades\n"
            "or claws."), COMPOUND_STRING("Corta al rival con\n" "cuchillas o garras\n" "afiladas.")),
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM_FLY] =
    {
        .name = ES(ITEM_NAME("HM02"), ITEM_NAME("MO02")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Flies up on the\n"
            "first turn, then\n"
            "attacks next turn."), COMPOUND_STRING("Vuela el 1.er turno\n" "y ataca en el\n" "siguiente.")),
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM_SURF] =
    {
        .name = ES(ITEM_NAME("HM03"), ITEM_NAME("MO03")),
        .price = 0,
        .description = COMPOUND_STRING(
            "Creates a huge\n"
            "wave, then crashes\n"
        #if B_UPDATED_MOVE_DATA >= GEN_4
            "it on all others."),
        #else
            "it down on foes."),
        #endif
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM_STRENGTH] =
    {
        .name = ES(ITEM_NAME("HM04"), ITEM_NAME("MO04")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Builds enormous\n"
            "power, then slams\n"
            "the foe."), COMPOUND_STRING("Reúne una fuerza\n" "enorme y golpea al\n" "rival.")),
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM_FLASH] =
    {
        .name = ES(ITEM_NAME("HM05"), ITEM_NAME("MO05")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Looses a powerful\n"
            "blast of light that\n"
            "lowers accuracy."), COMPOUND_STRING("Un destello potente\n" "que baja la\n" "precisión.")),
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM_ROCK_SMASH] =
    {
        .name = ES(ITEM_NAME("HM06"), ITEM_NAME("MO06")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A rock-crushingly\n"
            "tough attack that\n"
            "may lower Defense."), COMPOUND_STRING("Rompe rocas. Puede\n" "bajar la Defensa.")),
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM_WATERFALL] =
    {
        .name = ES(ITEM_NAME("HM07"), ITEM_NAME("MO07")),
        .price = 0,
        .description = COMPOUND_STRING(
        #if B_UPDATED_MOVE_DATA >= GEN_4
            "Attacks with power\n"
            "to climb waterfalls.\n"
            "May flinch."),
        #else
            "Attacks the foe\n"
            "with enough power\n"
            "to climb waterfalls."),
        #endif
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM_DIVE] =
    {
        .name = ES(ITEM_NAME("HM08"), ITEM_NAME("MO08")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Dives underwater\n"
            "the 1st turn, then\n"
            "attacks next turn."), COMPOUND_STRING("Bucea el 1.er turno\n" "y ataca en el\n" "siguiente.")),
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

// Charms

    [ITEM_OVAL_CHARM] =
    {
        .name = ES(ITEM_NAME("Oval Charm"), ITEM_NAME("Amuleto Oval")),
        .price = 0,
        .importance = 1,
        .description = ES(COMPOUND_STRING("Increases the\n"
            "chance of finding\n"
            "Pokémon Eggs."), COMPOUND_STRING("Es más fácil\n" "encontrar Huevos.")),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_OvalCharm,
        .iconPalette = gItemIconPalette_OvalCharm,
    },

    [ITEM_SHINY_CHARM] =
    {
        .name = ES(ITEM_NAME("Shiny Charm"), ITEM_NAME("Amuleto Iris")),
        .price = 0,
        .importance = 1,
        .description = ES(COMPOUND_STRING("Increases the\n"
            "chance of finding\n"
            "Shiny Pokémon."), COMPOUND_STRING("Es más fácil\n" "encontrar Pokémon\n" "variocolor.")),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_ShinyCharm,
        .iconPalette = gItemIconPalette_ShinyCharm,
    },

    [ITEM_CATCHING_CHARM] =
    {
        .name = ES(ITEM_NAME("Catching Charm"), ITEM_NAME("Amuleto Captura")),
        .price = 0,
        .importance = 1,
        .description = ES(COMPOUND_STRING("Increases the\n"
            "chance of getting\n"
            "a critical catch."), COMPOUND_STRING("Más capturas\n" "críticas.")),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_CatchingCharm,
        .iconPalette = gItemIconPalette_CatchingCharm,
    },

    [ITEM_EXP_CHARM] =
    {
        .name = ES(ITEM_NAME("Exp. Charm"), ITEM_NAME("Amuleto Exp")),
        .price = 0,
        .importance = 1,
        .description = ES(COMPOUND_STRING("Increases the\n"
            "Exp. Points that\n"
            "Pokémon can get."), COMPOUND_STRING("Los Pokémon ganan\n" "más experiencia.")),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_ExpCharm,
        .iconPalette = gItemIconPalette_ExpCharm,
    },

// Form-changing Key Items

    [ITEM_ROTOM_CATALOG] =
    {
        .name = ES(ITEM_NAME("Rotom Catalog"), ITEM_NAME("Catálogo Rotom")),
        .price = 0,
        .importance = 1,
        .description = ES(COMPOUND_STRING("Use to have Rotom\n"
            "hop in and out of\n"
            "the devices listed."), COMPOUND_STRING("Para que Rotom entre\n" "y salga de los\n" "aparatos.")),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_RotomCatalog,
        .iconPic = gItemIcon_RotomCatalog,
        .iconPalette = gItemIconPalette_RotomCatalog,
    },

    [ITEM_GRACIDEA] =
    {
        .name = ES(ITEM_NAME("Gracidea"), ITEM_NAME("Gracídea")),
        .price = 0,
        .importance = 1,
        .description = ES(COMPOUND_STRING("A flower given as\n"
            "an expression of\n"
            "gratitude."), COMPOUND_STRING("Bonguri de color\n" "rojo y aroma muy\n" "penetrante.")),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange,
        .iconPic = gItemIcon_Gracidea,
        .iconPalette = gItemIconPalette_Gracidea,
    },

    [ITEM_REVEAL_GLASS] =
    {
        .name = ES(ITEM_NAME("Reveal Glass"), ITEM_NAME("Espejo Veraz")),
        .pluralName = ITEM_PLURAL_NAME("Reveal Glasses"),
        .price = 0,
        .importance = 1,
        .description = ES(COMPOUND_STRING("Returns a\n"
            "Pokémon back to\n"
            "its original shape."), COMPOUND_STRING("Devuelve a un\n" "Pokémon a su forma\n" "original.")),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange,
        .iconPic = gItemIcon_RevealGlass,
        .iconPalette = gItemIconPalette_RevealGlass,
    },

    [ITEM_DNA_SPLICERS] =
    {
        .name = ES(ITEM_NAME("DNA Splicers"), ITEM_NAME("Punta ADN")),
        .pluralName = ITEM_PLURAL_NAME("DNA Splicers"),
        .price = 0,
        .importance = 1,
        .description = ES(COMPOUND_STRING("A splicer that\n"
            "fuses Kyurem and\n"
            "a certain Pokémon."), COMPOUND_STRING("Fusiona a Kyurem con\n" "cierto Pokémon.")),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Fusion,
        .iconPic = gItemIcon_DNASplicers,
        .iconPalette = gItemIconPalette_DNASplicers,
    },

    [ITEM_ZYGARDE_CUBE] =
    {
        .name = ES(ITEM_NAME("Zygarde Cube"), ITEM_NAME("Arca de Zygarde")),
        .price = 0,
        .importance = 1,
        .description = ES(COMPOUND_STRING("An item to change\n"
            "Zygarde's forms."), COMPOUND_STRING("Sirve para cambiar\n" "las formas de\n" "Zygarde.")),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_ZygardeCube,
        .iconPic = gItemIcon_ZygardeCube,
        .iconPalette = gItemIconPalette_ZygardeCube,
    },

    [ITEM_PRISON_BOTTLE] =
    {
        .name = ES(ITEM_NAME("Prison Bottle"), ITEM_NAME("Vasija Castigo")),
        .price = 0,
        .importance = 1,
        .description = ES(COMPOUND_STRING("A bottle used to\n"
            "seal a certain\n"
            "Pokémon long ago."), COMPOUND_STRING("Una vasija con la\n" "que se selló a un\n" "Pokémon.")),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange,
        .iconPic = gItemIcon_PrisonBottle,
        .iconPalette = gItemIconPalette_PrisonBottle,
    },

    [ITEM_N_SOLARIZER] =
    {
        .name = ES(ITEM_NAME("N-Solarizer"), ITEM_NAME("Necrosol")),
        .price = 0,
        .importance = 1,
        .description = ES(COMPOUND_STRING("Fuses or separates\n"
            "Necrozma and\n"
            "Solgaleo."), COMPOUND_STRING("Fusiona o separa a\n" "Necrozma y Solgaleo.")),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Fusion,
        .iconPic = gItemIcon_NecrozmaFuser,
        .iconPalette = gItemIconPalette_NSolarizer,
    },

    [ITEM_N_LUNARIZER] =
    {
        .name = ES(ITEM_NAME("N-Lunarizer"), ITEM_NAME("Necroluna")),
        .price = 0,
        .importance = 1,
        .description = ES(COMPOUND_STRING("Fuses or separates\n"
            "Necrozma and\n"
            "Lunala."), COMPOUND_STRING("Fusiona o separa a\n" "Necrozma y Lunala.")),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Fusion,
        .iconPic = gItemIcon_NecrozmaFuser,
        .iconPalette = gItemIconPalette_NLunarizer,
    },

    [ITEM_REINS_OF_UNITY] =
    {
        .name = ES(ITEM_NAME("Reins of Unity"), ITEM_NAME("Riendas Unión")),
        .pluralName = ITEM_PLURAL_NAME("Reins of Unity"),
        .price = 0,
        .importance = 1,
        .description = ES(COMPOUND_STRING("Unites or\n"
            "separates Calyrex\n"
            "and its steed."), COMPOUND_STRING("Une o separa a\n" "Calyrex y su corcel.")),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Fusion,
        .iconPic = gItemIcon_ReinsOfUnity,
        .iconPalette = gItemIconPalette_ReinsOfUnity,
    },

// Battle Mechanic Key Items

    [ITEM_MEGA_RING] =
    {
        .name = ES(ITEM_NAME("Mega Ring"), ITEM_NAME("Mega-Aro")),
        .price = 0,
        .importance = 1,
        .description = ES(COMPOUND_STRING("Enables Pokémon\n"
            "with Mega Stones\n"
            "to Mega Evolve."), COMPOUND_STRING("Permite\n" "megaevolucionar con\n" "megapiedras.")),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_MegaRing,
        .iconPalette = gItemIconPalette_MegaRing,
    },

    [ITEM_Z_POWER_RING] =
    {
        .name = ES(ITEM_NAME("Z-Power Ring"), ITEM_NAME("Superpulsera Z")),
        .price = 0,
        .importance = 1,
        .description = ES(COMPOUND_STRING("A ring that\n"
            "enables Pokémon\n"
            "to use Z-Power."), COMPOUND_STRING("Un aro que permite\n" "usar el Poder Z.")),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_ZPowerRing,
        .iconPalette = gItemIconPalette_ZPowerRing,
    },

    [ITEM_DYNAMAX_BAND] =
    {
        .name = ES(ITEM_NAME("Dynamax Band"), ITEM_NAME("Maximuñequera")),
        .price = 0,
        .importance = 1,
        .description = ES(COMPOUND_STRING("Allows Pokémon to\n"
            "Dynamax when at\n"
            "a Power Spot."), COMPOUND_STRING("Permite el Dinamax\n" "en una zona de\n" "poder.")),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_DynamaxBand,
        .iconPalette = gItemIconPalette_DynamaxBand,
    },

// Miscellaneous Key Items

    [ITEM_BICYCLE] =
    {
        .name = ES(ITEM_NAME("Bike"), ITEM_NAME("Bici")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A folding bicycle\n"
            "that is faster than\n"
            "the Running Shoes."), COMPOUND_STRING("Una bici plegable,\n" "más rápida que\n" "correr.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Bike,
        .secondaryId = STANDARD_BIKE,
        .iconPic = gItemIcon_Bicycle,
        .iconPalette = gItemIconPalette_Bicycle,
    },

    [ITEM_MACH_BIKE] =
    {
        .name = ES(ITEM_NAME("Mach Bike"), ITEM_NAME("Bici de Carreras")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A folding bicycle\n"
            "that doubles your\n"
            "speed or better."), COMPOUND_STRING("Una bici plegable\n" "que va el doble de\n" "rápido.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Bike,
        .secondaryId = MACH_BIKE,
        .iconPic = gItemIcon_MachBike,
        .iconPalette = gItemIconPalette_MachBike,
    },

    [ITEM_ACRO_BIKE] =
    {
        .name = ES(ITEM_NAME("Acro Bike"), ITEM_NAME("Bici Acrobática")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A folding bicycle\n"
            "capable of jumps\n"
            "and wheelies."), COMPOUND_STRING("Una bici plegable\n" "para saltos y\n" "caballitos.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Bike,
        .secondaryId = ACRO_BIKE,
        .iconPic = gItemIcon_AcroBike,
        .iconPalette = gItemIconPalette_AcroBike,
    },

    [ITEM_OLD_ROD] =
    {
        .name = ES(ITEM_NAME("Old Rod"), ITEM_NAME("Caña Vieja")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Use by any body of\n"
            "water to fish for\n"
            "wild Pokémon."), COMPOUND_STRING("Sirve para pescar\n" "Pokémon en cualquier\n" "agua.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Rod,
        .secondaryId = OLD_ROD,
        .iconPic = gItemIcon_OldRod,
        .iconPalette = gItemIconPalette_OldRod,
    },

    [ITEM_GOOD_ROD] =
    {
        .name = ES(ITEM_NAME("Good Rod"), ITEM_NAME("Caña Buena")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A decent fishing\n"
            "rod for catching\n"
            "wild Pokémon."), COMPOUND_STRING("Una caña decente\n" "para pescar Pokémon.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Rod,
        .secondaryId = GOOD_ROD,
        .iconPic = gItemIcon_GoodRod,
        .iconPalette = gItemIconPalette_GoodRod,
    },

    [ITEM_SUPER_ROD] =
    {
        .name = ES(ITEM_NAME("Super Rod"), ITEM_NAME("Supercaña")),
        .price = 0,
        .description = ES(COMPOUND_STRING("The best fishing\n"
            "rod for catching\n"
            "wild Pokémon."), COMPOUND_STRING("La mejor caña para\n" "pescar Pokémon.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Rod,
        .secondaryId = SUPER_ROD,
        .iconPic = gItemIcon_SuperRod,
        .iconPalette = gItemIconPalette_SuperRod,
    },

    [ITEM_DOWSING_MACHINE] =
    {
        .name = ES(ITEM_NAME("Dowsing Machine"), ITEM_NAME("Zahorí")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A device that\n"
            "signals an invisible\n"
            "item by sound."), COMPOUND_STRING("Avisa con un sonido\n" "de objetos ocultos.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Itemfinder,
        .iconPic = gItemIcon_DowsingMachine,
        .iconPalette = gItemIconPalette_DowsingMachine,
    },

    [ITEM_TOWN_MAP] =
    {
        .name = ES(ITEM_NAME("Town Map"), ITEM_NAME("Mapa")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Can be viewed\n"
            "anytime. Shows your\n"
            "present location."), COMPOUND_STRING("Muestra dónde estás.\n" "Se puede ver\n" "siempre.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TownMap,
        .iconPic = gItemIcon_TownMap,
        .iconPalette = gItemIconPalette_TownMap,
    },

    [ITEM_VS_SEEKER] =
    {
        .name = ES(ITEM_NAME("Vs. Seeker"), ITEM_NAME("Buscapelea")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A rechargeable unit\n"
            "that flags battle-\n"
            "ready Trainers."), COMPOUND_STRING("Recargable. Avisa de\n" "Entrenadores listos.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
    #if I_VS_SEEKER_CHARGING != 0
        .fieldUseFunc = FieldUseFunc_VsSeeker,
    #else
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    #endif
        .iconPic = gItemIcon_VsSeeker,
        .iconPalette = gItemIconPalette_VsSeeker,
    },

    [ITEM_TM_CASE] =
    {
        .name = ES(ITEM_NAME("TM Case"), ITEM_NAME("Estuche de MT")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A convenient case\n"
            "that holds TMs and\n"
            "HMs."), COMPOUND_STRING("Un estuche práctico\n" "para MT y MO.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TMCase,
        .iconPalette = gItemIconPalette_TMCase,
    },

    [ITEM_BERRY_POUCH] =
    {
        .name = ES(ITEM_NAME("Berry Pouch"), ITEM_NAME("Saco Bayas")),
        .pluralName = ITEM_PLURAL_NAME("Berry Pouches"),
        .price = 0,
        .description = ES(COMPOUND_STRING("A convenient\n"
            "container that\n"
            "holds Berries."), COMPOUND_STRING("Una bolsa práctica\n" "para guardar bayas.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_BerryPouch,
        .iconPalette = gItemIconPalette_BerryPouch,
    },

    [ITEM_POKEMON_BOX_LINK] =
    {
        .name = ES(ITEM_NAME("{PKMN} Box Link"), ITEM_NAME("Caja de Pokémon")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Allows access to\n"
            "the Pokémon\n"
            "Storage System."), COMPOUND_STRING("Permite usar el\n" "sistema de cajas.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_PokemonBoxLink,
        .iconPic = gItemIcon_PokemonBoxLink,
        .iconPalette = gItemIconPalette_PokemonBoxLink,
    },

    [ITEM_COIN_CASE] =
    {
        .name = ES(ITEM_NAME("Coin Case"), ITEM_NAME("Monedero")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A case that holds\n"
            "up to 9,999 Coins."), COMPOUND_STRING("Un estuche para\n" "hasta 9.999 fichas.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CoinCase,
        .iconPic = gItemIcon_CoinCase,
        .iconPalette = gItemIconPalette_CoinCase,
    },

    [ITEM_POWDER_JAR] =
    {
        .name = ES(ITEM_NAME("Powder Jar"), ITEM_NAME("Bote Polvos")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Stores Berry\n"
            "Powder made using\n"
            "a Berry Crusher."), COMPOUND_STRING("Guarda el polvo de\n" "baya de la\n" "Trituradora.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PowderJar,
        .iconPic = gItemIcon_PowderJar,
        .iconPalette = gItemIconPalette_PowderJar,
    },

    [ITEM_WAILMER_PAIL] =
    {
        .name = ES(ITEM_NAME("Wailmer Pail"), ITEM_NAME("Wailmegadera")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A tool used for\n"
            "watering Berries\n"
            "and plants."), COMPOUND_STRING("Una regadera para\n" "regar bayas y\n" "plantas.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_WailmerPail,
        .iconPic = gItemIcon_WailmerPail,
        .iconPalette = gItemIconPalette_WailmerPail,
    },

    [ITEM_POKE_RADAR] =
    {
        .name = ES(ITEM_NAME("Poké Radar"), ITEM_NAME("Pokéradar")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A tool that can\n"
            "search out Pokémon\n"
            "hiding in grass."), COMPOUND_STRING("Busca Pokémon\n" "escondidos en la\n" "hierba.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .iconPic = gItemIcon_PokeRadar,
        .iconPalette = gItemIconPalette_PokeRadar,
    },

    [ITEM_POKEBLOCK_CASE] =
    {
        .name = ES(ITEM_NAME("{POKEBLOCK} Case"), ITEM_NAME("Tubo Pokécubos")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A case for holding\n"
            "{POKEBLOCK}s made with\n"
            "a Berry Blender."), COMPOUND_STRING("Un estuche para los\n" "{POKEBLOCK} de la\n" "Licuadora.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PBLOCK_CASE,
        .fieldUseFunc = ItemUseOutOfBattle_PokeblockCase,
        .iconPic = gItemIcon_PokeblockCase,
        .iconPalette = gItemIconPalette_PokeblockCase,
    },

    [ITEM_SOOT_SACK] =
    {
        .name = ES(ITEM_NAME("Soot Sack"), ITEM_NAME("Saco Hollín")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A sack used to\n"
            "gather and hold\n"
            "volcanic ash."), COMPOUND_STRING("Una bolsa para\n" "recoger ceniza\n" "volcánica.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_SootSack,
        .iconPalette = gItemIconPalette_SootSack,
    },

    [ITEM_POKE_FLUTE] =
    {
        .name = ES(ITEM_NAME("Poké Flute"), ITEM_NAME("Poké Flauta")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A sweet-sounding\n"
            "flute that awakens\n"
            "Pokémon."), COMPOUND_STRING("Una flauta dulce que\n" "despierta a los\n" "Pokémon.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PokeFlute,
        .battleUsage = EFFECT_ITEM_USE_POKE_FLUTE,
        .iconPic = gItemIcon_PokeFlute,
        .iconPalette = gItemIconPalette_PokeFlute,
    },

    [ITEM_FAME_CHECKER] =
    {
        .name = ES(ITEM_NAME("Fame Checker"), ITEM_NAME("Memorín")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Stores information\n"
            "on famous people\n"
            "for instant recall."), COMPOUND_STRING("Guarda información\n" "sobre gente famosa.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_FameChecker,
        .iconPalette = gItemIconPalette_FameChecker,
    },

    [ITEM_TEACHY_TV] =
    {
        .name = ES(ITEM_NAME("Teachy TV"), ITEM_NAME("Poké Tele")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A TV set tuned to\n"
            "an advice program\n"
            "for Trainers."), COMPOUND_STRING("Una tele con\n" "consejos para\n" "Entrenadores.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeachyTV,
        .iconPalette = gItemIconPalette_TeachyTV,
    },

// Story Key Items

    [ITEM_SS_TICKET] =
    {
        .name = ES(ITEM_NAME("S.S. Ticket"), ITEM_NAME("Ticket del Barco")),
        .price = 0,
        .description = ES(COMPOUND_STRING("The ticket required\n"
            "for sailing on a\n"
            "ferry."), COMPOUND_STRING("El billete necesario\n" "para viajar en\n" "ferry.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_SSTicket,
        .iconPalette = gItemIconPalette_SSTicket,
    },

    [ITEM_EON_TICKET] =
    {
        .name = ES(ITEM_NAME("Eon Ticket"), ITEM_NAME("Ticket Eón")),
        .price = 0,
        .description = ES(COMPOUND_STRING("The ticket for a\n"
            "ferry to a distant\n"
            "southern island."), COMPOUND_STRING("El billete del ferry\n" "a una isla lejana\n" "del sur.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 1,
        .iconPic = gItemIcon_EonTicket,
        .iconPalette = gItemIconPalette_EonTicket,
    },

    [ITEM_MYSTIC_TICKET] =
    {
        .name = ES(ITEM_NAME("Mystic Ticket"), ITEM_NAME("Misti-Ticket")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A ticket required\n"
            "to board the ship\n"
            "to Navel Rock."), COMPOUND_STRING("El billete para ir\n" "en barco a Roca\n" "Ombligo.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_MysticTicket,
        .iconPalette = gItemIconPalette_MysticTicket,
    },

    [ITEM_AURORA_TICKET] =
    {
        .name = ES(ITEM_NAME("Aurora Ticket"), ITEM_NAME("Ori-Ticket")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A ticket required\n"
            "to board the ship\n"
            "to Birth Island."), COMPOUND_STRING("El billete para ir\n" "en barco a Isla\n" "Origen.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_AuroraTicket,
        .iconPalette = gItemIconPalette_AuroraTicket,
    },

    [ITEM_OLD_SEA_MAP] =
    {
        .name = ES(ITEM_NAME("Old Sea Map"), ITEM_NAME("Mapa Viejo")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A faded sea chart\n"
            "that shows the way\n"
            "to a certain island."), COMPOUND_STRING("Una carta náutica\n" "vieja que lleva a\n" "una isla.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_OldSeaMap,
        .iconPalette = gItemIconPalette_OldSeaMap,
    },

    [ITEM_LETTER] =
    {
        .name = ES(ITEM_NAME("Letter"), ITEM_NAME("Carta a Máximo")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A letter to Steven\n"
            "from the President\n"
            "of the Devon Corp."), COMPOUND_STRING("Una carta del\n" "presidente de Devon\n" "para Máximo.")),
        .importance = 2,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Letter,
        .iconPalette = gItemIconPalette_LavaCookieAndLetter,
    },

    [ITEM_DEVON_PARTS] =
    {
        .name = ES(ITEM_NAME("Devon Parts"), ITEM_NAME("Piezas Devon")),
        .pluralName = ITEM_PLURAL_NAME("Devon Parts"),
        .price = 0,
        .description = ES(COMPOUND_STRING("A package that\n"
            "contains Devon's\n"
            "machine parts."), COMPOUND_STRING("Contiene piezas de\n" "algo fabricado por\n" "Devon S. A.")),
        .importance = 2,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_DevonParts,
        .iconPalette = gItemIconPalette_DevonParts,
    },

    [ITEM_GO_GOGGLES] =
    {
        .name = ES(ITEM_NAME("Go-Goggles"), ITEM_NAME("Gafas Aislantes")),
        .pluralName = ITEM_PLURAL_NAME("Go-Goggles"),
        .price = 0,
        .description = ES(COMPOUND_STRING("Nifty goggles that\n"
            "protect eyes from\n"
            "desert sandstorms."), COMPOUND_STRING("Unas gafas que\n" "protegen de la arena\n" "del desierto.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_GoGoggles,
        .iconPalette = gItemIconPalette_GoGoggles,
    },

    [ITEM_DEVON_SCOPE] =
    {
        .name = ES(ITEM_NAME("Devon Scope"), ITEM_NAME("Detector Devon")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A device by Devon\n"
            "that signals any\n"
            "unseeable Pokémon."), COMPOUND_STRING("Un aparato de Devon\n" "que revela Pokémon\n" "invisibles.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_DevonScope,
        .iconPalette = gItemIconPalette_DevonScope,
    },

    [ITEM_BASEMENT_KEY] =
    {
        .name = ES(ITEM_NAME("Basement Key"), ITEM_NAME("Llave del Sótano")),
        .price = 0,
        .description = ES(COMPOUND_STRING("The key for New\n"
            "Mauville beneath\n"
            "Mauville City."), COMPOUND_STRING("Llave que abre la\n" "puerta que hay en el\n" "Túnel Trigal.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_BasementKey,
        .iconPalette = gItemIconPalette_OldKey,
    },

    [ITEM_SCANNER] =
    {
        .name = ES(ITEM_NAME("Scanner"), ITEM_NAME("Escáner")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A device found\n"
            "inside the\n"
            "Abandoned Ship."), COMPOUND_STRING("Objeto hallado en el\n" "interior de\n" "Malvamar.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Scanner,
        .iconPalette = gItemIconPalette_Scanner,
    },

    [ITEM_STORAGE_KEY] =
    {
        .name = ES(ITEM_NAME("Storage Key"), ITEM_NAME("Llave Almacén")),
        .price = 0,
        .description = ES(COMPOUND_STRING("The key to the\n"
            "storage inside the\n"
            "Abandoned Ship."), COMPOUND_STRING("Misteriosa ala de un\n" "brillante color\n" "plateado.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_StorageKey,
        .iconPalette = gItemIconPalette_OldKey,
    },

    [ITEM_KEY_TO_ROOM_1] =
    {
        .name = ES(ITEM_NAME("Key to Room 1"), ITEM_NAME("Ll. Habitación 1")),
        .pluralName = ITEM_PLURAL_NAME("Keys to Room 1"),
        .price = 0,
        .description = ES(COMPOUND_STRING("A key that opens a\n"
            "door inside the\n"
            "Abandoned Ship."), COMPOUND_STRING("Abre una puerta del\n" "Barco Abandonado.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_KeyToRoom1,
        .iconPalette = gItemIconPalette_Key,
    },

    [ITEM_KEY_TO_ROOM_2] =
    {
        .name = ES(ITEM_NAME("Key to Room 2"), ITEM_NAME("Ll. Habitación 2")),
        .pluralName = ITEM_PLURAL_NAME("Keys to Room 2"),
        .price = 0,
        .description = ES(COMPOUND_STRING("A key that opens a\n"
            "door inside the\n"
            "Abandoned Ship."), COMPOUND_STRING("Abre una puerta del\n" "Barco Abandonado.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_KeyToRoom2,
        .iconPalette = gItemIconPalette_Key,
    },

    [ITEM_KEY_TO_ROOM_4] =
    {
        .name = ES(ITEM_NAME("Key to Room 4"), ITEM_NAME("Ll. Habitación 4")),
        .pluralName = ITEM_PLURAL_NAME("Keys to Room 4"),
        .price = 0,
        .description = ES(COMPOUND_STRING("A key that opens a\n"
            "door inside the\n"
            "Abandoned Ship."), COMPOUND_STRING("Abre una puerta del\n" "Barco Abandonado.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_KeyToRoom4,
        .iconPalette = gItemIconPalette_Key,
    },

    [ITEM_KEY_TO_ROOM_6] =
    {
        .name = ES(ITEM_NAME("Key to Room 6"), ITEM_NAME("Ll. Habitación 6")),
        .pluralName = ITEM_PLURAL_NAME("Keys to Room 6"),
        .price = 0,
        .description = ES(COMPOUND_STRING("A key that opens a\n"
            "door inside the\n"
            "Abandoned Ship."), COMPOUND_STRING("Abre una puerta del\n" "Barco Abandonado.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_KeyToRoom6,
        .iconPalette = gItemIconPalette_Key,
    },

    [ITEM_METEORITE] =
    {
        .name = ES(ITEM_NAME("Meteorite"), ITEM_NAME("Meteorito")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A rock that allows\n"
            "a certain Pokémon\n"
            "to change Formes."), COMPOUND_STRING("Una roca que cambia\n" "la forma de cierto\n" "Pokémon.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange,
        .iconPic = gItemIcon_Meteorite,
        .iconPalette = gItemIconPalette_Meteorite,
    },

    [ITEM_MAGMA_EMBLEM] =
    {
        .name = ES(ITEM_NAME("Magma Emblem"), ITEM_NAME("Signo Magma")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A medal-like item in\n"
            "the same shape as\n"
            "Team Magma's mark."), COMPOUND_STRING("Una insignia con la\n" "forma del logo del\n" "Equipo Magma.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_MagmaEmblem,
        .iconPalette = gItemIconPalette_MagmaEmblem,
    },

    [ITEM_CONTEST_PASS] =
    {
        .name = ES(ITEM_NAME("Contest Pass"), ITEM_NAME("Pase Concurso")),
        .pluralName = ITEM_PLURAL_NAME("Contest Passes"),
        .price = 0,
        .description = ES(COMPOUND_STRING("The pass required\n"
            "for entering\n"
            "Pokémon Contests."), COMPOUND_STRING("Llave que abre la\n" "puerta que hay en el\n" "Túnel Trigal.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_ContestPass,
        .iconPalette = gItemIconPalette_ContestPass,
    },

    [ITEM_PARCEL] =
    {
        .name = ES(ITEM_NAME("Parcel"), ITEM_NAME("Paquete")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A parcel for Prof.\n"
            "Oak from a Pokémon\n"
            "Mart's clerk."), COMPOUND_STRING("Un paquete para el\n" "Prof. Oak de la\n" "tienda.")),
        .importance = 2,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Parcel,
        .iconPalette = gItemIconPalette_Parcel,
    },

    [ITEM_SECRET_KEY] =
    {
        .name = ES(ITEM_NAME("Secret Key"), ITEM_NAME("Llave Secreta")),
        .price = 0,
        .description = ES(COMPOUND_STRING("The key to the\n"
            "Cinnabar Island\n"
            "Gym's entrance."), COMPOUND_STRING("Bonguri de color\n" "azul y aroma tierno.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_SecretKey,
        .iconPalette = gItemIconPalette_SecretKey,
    },

    [ITEM_BIKE_VOUCHER] =
    {
        .name = ES(ITEM_NAME("Bike Voucher"), ITEM_NAME("Bono Bici")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A voucher for\n"
            "obtaining a bicycle\n"
            "from the Bike Shop."), COMPOUND_STRING("Un vale para\n" "conseguir una bici\n" "en la tienda.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_BikeVoucher,
        .iconPalette = gItemIconPalette_BikeVoucher,
    },

    [ITEM_GOLD_TEETH] =
    {
        .name = ES(ITEM_NAME("Gold Teeth"), ITEM_NAME("Dentadura de Oro")),
        .pluralName = ITEM_PLURAL_NAME("Gold Teeth"),
        .price = 0,
        .description = ES(COMPOUND_STRING("Gold dentures lost\n"
            "by the Safari\n"
            "Zone's Warden."), COMPOUND_STRING("La dentadura de oro\n" "del guarda del\n" "Safari.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_GoldTeeth,
        .iconPalette = gItemIconPalette_GoldTeeth,
    },

    [ITEM_CARD_KEY] =
    {
        .name = ES(ITEM_NAME("Card Key"), ITEM_NAME("Llave Magnética")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A card-type door\n"
            "key used in Silph\n"
            "Co's office."), COMPOUND_STRING("Una tarjeta llave de\n" "las oficinas de\n" "Silph.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_CardKey,
        .iconPalette = gItemIconPalette_CardKey,
    },

    [ITEM_LIFT_KEY] =
    {
        .name = ES(ITEM_NAME("Lift Key"), ITEM_NAME("Llave Ascensor")),
        .price = 0,
        .description = ES(COMPOUND_STRING("An elevator key\n"
            "used in Team\n"
            "Rocket's Hideout."), COMPOUND_STRING("La llave del\n" "ascensor de la\n" "guarida Rocket.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_LiftKey,
        .iconPalette = gItemIconPalette_Key,
    },

    [ITEM_SILPH_SCOPE] =
    {
        .name = ES(ITEM_NAME("Silph Scope"), ITEM_NAME("Visor Silph")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Silph Co's scope\n"
            "makes unseeable\n"
            "Pokémon visible."), COMPOUND_STRING("Un visor de Silph\n" "que revela Pokémon\n" "invisibles.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_SilphScope,
        .iconPalette = gItemIconPalette_SilphScope,
    },

    [ITEM_TRI_PASS] =
    {
        .name = ES(ITEM_NAME("Tri-Pass"), ITEM_NAME("Tri-Ticket")),
        .pluralName = ITEM_PLURAL_NAME("Tri-Passes"),
        .price = 0,
        .description = ES(COMPOUND_STRING("A pass for ferries\n"
            "between One, Two,\n"
            "and Three Island."), COMPOUND_STRING("Un pase para el\n" "ferry de las Islas\n" "Uno, Dos y Tres.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TriPass,
        .iconPalette = gItemIconPalette_TriPass,
    },

    [ITEM_RAINBOW_PASS] =
    {
        .name = ES(ITEM_NAME("Rainbow Pass"), ITEM_NAME("Iris-Ticket")),
        .pluralName = ITEM_PLURAL_NAME("Rainbow Passes"),
        .price = 0,
        .description = ES(COMPOUND_STRING("For ferries serving\n"
            "Vermilion and the\n"
            "Sevii Islands."), COMPOUND_STRING("Un pase para el\n" "ferry de las Islas\n" "Sete.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_RainbowPass,
        .iconPalette = gItemIconPalette_RainbowPass,
    },

    [ITEM_TEA] =
    {
        .name = ES(ITEM_NAME("Tea"), ITEM_NAME("Té")),
        .pluralName = ITEM_PLURAL_NAME("Tea"),
        .price = 0,
        .description = ES(COMPOUND_STRING("A thirst-quenching\n"
            "tea prepared by an\n"
            "old lady."), COMPOUND_STRING("Un té refrescante\n" "que prepara una\n" "anciana.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Tea,
        .iconPalette = gItemIconPalette_Tea,
    },

    [ITEM_RUBY] =
    {
        .name = ES(ITEM_NAME("Ruby"), ITEM_NAME("Rubí")),
        .pluralName = ITEM_PLURAL_NAME("Rubies"),
        .price = 0,
        .description = ES(COMPOUND_STRING("An exquisite, red-\n"
            "glowing gem that\n"
            "symbolizes passion."), COMPOUND_STRING("Una gema roja\n" "preciosa que\n" "simboliza la pasión.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Gem,
        .iconPalette = gItemIconPalette_Ruby,
    },

    [ITEM_SAPPHIRE] =
    {
        .name = ES(ITEM_NAME("Sapphire"), ITEM_NAME("Zafiro")),
        .price = 0,
        .description = ES(COMPOUND_STRING("A brilliant blue gem\n"
            "that symbolizes\n"
            "honesty."), COMPOUND_STRING("Una gema azul\n" "preciosa, símbolo de\n" "honradez.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Gem,
        .iconPalette = gItemIconPalette_Sapphire,
    },

// Gen 9 Items

    [ITEM_ABILITY_SHIELD] =
    {
        .name = ES(ITEM_NAME("Ability Shield"), ITEM_NAME("Escudo Habilidad")),
        .price = 20000,
        .holdEffect = HOLD_EFFECT_ABILITY_SHIELD,
        .description = ES(COMPOUND_STRING("Guards the holder\n"
            "from having its\n"
            "Ability changed."), COMPOUND_STRING("Evita que le cambien\n" "la habilidad.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_AbilityShield,
        .iconPalette = gItemIconPalette_AbilityShield,
    },

    [ITEM_CLEAR_AMULET] =
    {
        .name = ES(ITEM_NAME("Clear Amulet"), ITEM_NAME("Amuleto Puro")),
        .price = 30000,
        .holdEffect = HOLD_EFFECT_CLEAR_AMULET,
        .description = ES(COMPOUND_STRING("Protects the\n"
            "holder from\n"
            "stat-lowering."), COMPOUND_STRING("Evita que le bajen\n" "las características.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_ClearAmulet,
        .iconPalette = gItemIconPalette_ClearAmulet,
    },

    [ITEM_PUNCHING_GLOVE] =
    {
        .name = ES(ITEM_NAME("Punching Glove"), ITEM_NAME("Guante de Boxeo")),
        .price = 15000,
        .holdEffect = HOLD_EFFECT_PUNCHING_GLOVE,
        .description = ES(COMPOUND_STRING("Boosts punching\n"
            "moves and prevents\n"
            "contact with foes."), COMPOUND_STRING("Potencia los\n" "puñetazos y evita el\n" "contacto.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_PunchingGlove,
        .iconPalette = gItemIconPalette_PunchingGlove,
    },

    [ITEM_COVERT_CLOAK] =
    {
        .name = ES(ITEM_NAME("Covert Cloak"), ITEM_NAME("Capa Furtiva")),
        .price = 20000,
        .holdEffect = HOLD_EFFECT_COVERT_CLOAK,
        .description = ES(COMPOUND_STRING("Conceals the\n"
            "holder from\n"
            "additional effects."), COMPOUND_STRING("Le protege de los\n" "efectos secundarios.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_CovertCloak,
        .iconPalette = gItemIconPalette_CovertCloak,
    },

    [ITEM_LOADED_DICE] =
    {
        .name = ES(ITEM_NAME("Loaded Dice"), ITEM_NAME("Dado Trucado")),
        .pluralName = ITEM_PLURAL_NAME("Loaded Dice"),
        .price = 20000,
        .holdEffect = HOLD_EFFECT_LOADED_DICE,
        .description = ES(COMPOUND_STRING("The holder's\n"
            "multistrike moves\n"
            "hit more times."), COMPOUND_STRING("Sus mov. de varios\n" "golpes golpean más\n" "veces.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_LoadedDice,
        .iconPalette = gItemIconPalette_LoadedDice,
    },

    [ITEM_AUSPICIOUS_ARMOR] =
    {
        .name = ES(ITEM_NAME("Auspicious Armor"), ITEM_NAME("Armadura Auspiciosa")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("A set of armor\n"
            "that makes certain\n"
            "Pokémon evolve."), COMPOUND_STRING("Una armadura que\n" "hace evolucionar a\n" "algunos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_AuspiciousArmor,
        .iconPalette = gItemIconPalette_AuspiciousArmor,
    },

    [ITEM_BOOSTER_ENERGY] =
    {
        .name = ES(ITEM_NAME("Booster Energy"), ITEM_NAME("Energía Potenciadora")),
        .pluralName = ITEM_PLURAL_NAME("Booster Energies"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_BOOSTER_ENERGY,
        .description = ES(COMPOUND_STRING("Ups the strength\n"
            "of Pokémon with\n"
            "certain Abilities."), COMPOUND_STRING("Potencia a los\n" "Pokémon con ciertas\n" "habilidades.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BoosterEnergy,
        .iconPalette = gItemIconPalette_BoosterEnergy,
    },

    [ITEM_BIG_BAMBOO_SHOOT] =
    {
        .name = ES(ITEM_NAME("Big Bamboo Shoot"), ITEM_NAME("Bambú Grande")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("A large bamboo\n"
            "shoot. It's popular\n"
            "with gourmands."), COMPOUND_STRING("Un brote de bambú\n" "grande. Gusta a los\n" "gourmets.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BigBambooShoot,
        .iconPalette = gItemIconPalette_BigBambooShoot,
    },

    [ITEM_GIMMIGHOUL_COIN] =
    {
        .name = ES(ITEM_NAME("Gimmighoul Coin"), ITEM_NAME("Moneda de Gimmighoul")),
        .price = 400,
        .description = ES(COMPOUND_STRING("A dropped material\n"
            "Gimmighoul hoard\n"
            "and treasure."), COMPOUND_STRING("Una moneda que\n" "coleccionan los\n" "Gimmighoul.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_GimmighoulCoin,
        .iconPalette = gItemIconPalette_GimmighoulCoin,
    },

    [ITEM_LEADERS_CREST] =
    {
        .name = ES(ITEM_NAME("Leader's Crest"), ITEM_NAME("Distintivo de Líder")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("A shard of a blade.\n"
            "Bisharp that head\n"
            "a group hold it."), COMPOUND_STRING("Un trozo de hoja que\n" "llevan los Bisharp\n" "líderes.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_LeadersCrest,
        .iconPalette = gItemIconPalette_LeadersCrest,
    },

    [ITEM_MALICIOUS_ARMOR] =
    {
        .name = ES(ITEM_NAME("Malicious Armor"), ITEM_NAME("Armadura Maldita")),
        .price = 3000,
        .description = ES(COMPOUND_STRING("A set of armor\n"
            "that makes certain\n"
            "Pokémon evolve."), COMPOUND_STRING("Una armadura que\n" "hace evolucionar a\n" "algunos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_MaliciousArmor,
        .iconPalette = gItemIconPalette_MaliciousArmor,
    },

    [ITEM_MIRROR_HERB] =
    {
        .name = ES(ITEM_NAME("Mirror Herb"), ITEM_NAME("Hierba Copia")),
        .price = 30000,
        .holdEffect = HOLD_EFFECT_MIRROR_HERB,
        .description = ES(COMPOUND_STRING("Mirrors a foe's\n"
            "stat increases,\n"
            "but only once."), COMPOUND_STRING("Copia una vez las\n" "subidas de caract.\n" "del rival.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_MirrorHerb,
        .iconPalette = gItemIconPalette_MirrorHerb,
    },

    [ITEM_SCROLL_OF_DARKNESS] =
    {
        .name = ES(ITEM_NAME("Scroll of Darkness"), ITEM_NAME("Manuscrito Sombras")),
        .pluralName = ITEM_PLURAL_NAME("Scrolls of Darkness"),
        .price = 0,
        .description = ES(COMPOUND_STRING("A peculiar scroll\n"
            "that makes certain\n"
            "Pokémon evolve."), COMPOUND_STRING("Un pergamino que\n" "hace evolucionar a\n" "algunos.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .iconPic = gItemIcon_ScrollOfDarkness,
        .iconPalette = gItemIconPalette_ScrollOfDarkness,
    },

    [ITEM_SCROLL_OF_WATERS] =
    {
        .name = ES(ITEM_NAME("Scroll of Waters"), ITEM_NAME("Manuscrito Aguas")),
        .pluralName = ITEM_PLURAL_NAME("Scrolls of Waters"),
        .price = 0,
        .description = ES(COMPOUND_STRING("A peculiar scroll\n"
            "that makes certain\n"
            "Pokémon evolve."), COMPOUND_STRING("Un pergamino que\n" "hace evolucionar a\n" "algunos.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .iconPic = gItemIcon_ScrollOfWaters,
        .iconPalette = gItemIconPalette_ScrollOfWaters,
    },

    [ITEM_TERA_ORB] =
    {
        .name = ES(ITEM_NAME("Tera Orb"), ITEM_NAME("Orbe Teracristal")),
        .price = 0,
        .description = ES(COMPOUND_STRING("When charged, it\n"
            "can cause Pokémon\n"
            "to Terastallize."), COMPOUND_STRING("Cargado, permite\n" "teracristalizar a un\n" "Pokémon.")),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraOrb,
        .iconPalette = gItemIconPalette_TeraOrb,
    },

    [ITEM_TINY_BAMBOO_SHOOT] =
    {
        .name = ES(ITEM_NAME("Tiny Bamboo Shoot"), ITEM_NAME("Bambú Pequeño")),
        .price = 750,
        .description = ES(COMPOUND_STRING("A small bamboo\n"
            "shoot. It's popular\n"
            "with gourmands."), COMPOUND_STRING("Un brote de bambú\n" "pequeño. Gusta a los\n" "gourmets.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_TinyBambooShoot,
        .iconPalette = gItemIconPalette_TinyBambooShoot,
    },

    [ITEM_BUG_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Bug Tera Shard"), ITEM_NAME("Teralito Bicho")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_BugTeraShard,
    },

    [ITEM_DARK_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Dark Tera Shard"), ITEM_NAME("Teralito Siniestro")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_DarkTeraShard,
    },

    [ITEM_DRAGON_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Dragon Tera Shard"), ITEM_NAME("Teralito Dragón")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_DragonTeraShard,
    },

    [ITEM_ELECTRIC_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Electric Tera Shard"), ITEM_NAME("Teralito Eléctrico")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_ElectricTeraShard,
    },

    [ITEM_FAIRY_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Fairy Tera Shard"), ITEM_NAME("Teralito Hada")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_FairyTeraShard,
    },

    [ITEM_FIGHTING_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Fighting Tera Shard"), ITEM_NAME("Teralito Lucha")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_FightingTeraShard,
    },

    [ITEM_FIRE_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Fire Tera Shard"), ITEM_NAME("Teralito Fuego")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_FireTeraShard,
    },

    [ITEM_FLYING_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Flying Tera Shard"), ITEM_NAME("Teralito Volador")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_FlyingTeraShard,
    },

    [ITEM_GHOST_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Ghost Tera Shard"), ITEM_NAME("Teralito Fantasma")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_GhostTeraShard,
    },

    [ITEM_GRASS_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Grass Tera Shard"), ITEM_NAME("Teralito Planta")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_GrassTeraShard,
    },

    [ITEM_GROUND_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Ground Tera Shard"), ITEM_NAME("Teralito Tierra")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_GroundTeraShard,
    },

    [ITEM_ICE_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Ice Tera Shard"), ITEM_NAME("Teralito Hielo")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_IceTeraShard,
    },

    [ITEM_NORMAL_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Normal Tera Shard"), ITEM_NAME("Teralito Normal")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_NormalTeraShard,
    },

    [ITEM_POISON_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Poison Tera Shard"), ITEM_NAME("Teralito Veneno")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_PoisonTeraShard,
    },

    [ITEM_PSYCHIC_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Psychic Tera Shard"), ITEM_NAME("Teralito Psíquico")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_PsychicTeraShard,
    },

    [ITEM_ROCK_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Rock Tera Shard"), ITEM_NAME("Teralito Roca")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_RockTeraShard,
    },

    [ITEM_STEEL_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Steel Tera Shard"), ITEM_NAME("Teralito Acero")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_SteelTeraShard,
    },

    [ITEM_WATER_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Water Tera Shard"), ITEM_NAME("Teralito Agua")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_WaterTeraShard,
    },

    [ITEM_ADAMANT_CRYSTAL] =
    {
        .name = ES(ITEM_NAME("Adamant Crystal"), ITEM_NAME("Gran Diamansfera")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_ADAMANT_ORB,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A glowing gem that\n"
            "allows Dialga\n"
            "to change form."), COMPOUND_STRING("Una gema que cambia\n" "la forma de Dialga.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_AdamantCrystal,
        .iconPalette = gItemIconPalette_AdamantCrystal,
    },

    [ITEM_GRISEOUS_CORE] =
    {
        .name = ES(ITEM_NAME("Griseous Core"), ITEM_NAME("Gran Griseosfera")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_GRISEOUS_ORB,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A glowing gem that\n"
            "allows Giratina\n"
            "to change form."), COMPOUND_STRING("Una gema que cambia\n" "la forma de\n" "Giratina.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_GriseousCore,
        .iconPalette = gItemIconPalette_GriseousCore,
    },

    [ITEM_LUSTROUS_GLOBE] =
    {
        .name = ES(ITEM_NAME("Lustrous Globe"), ITEM_NAME("Gran Lustresfera")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_LUSTROUS_ORB,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("A glowing gem that\n"
            "allows Palkia\n"
            "to change form."), COMPOUND_STRING("Una gema que cambia\n" "la forma de Palkia.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_LustrousGlobe,
        .iconPalette = gItemIconPalette_LustrousGlobe,
    },

    [ITEM_BLACK_AUGURITE] =
    {
        .name = ES(ITEM_NAME("Black Augurite"), ITEM_NAME("Mineral Negro")),
        .price = 8000,
        .description = ES(COMPOUND_STRING("A black stone.\n"
            "It is loved by\n"
            "a certain Pokémon."), COMPOUND_STRING("Una piedra negra que\n" "adora cierto\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_BlackAugurite,
        .iconPalette = gItemIconPalette_BlackAugurite,
    },

    [ITEM_LINKING_CORD] =
    {
        .name = ES(ITEM_NAME("Linking Cord"), ITEM_NAME("Cordón Unión")),
        .price = 8000,
        .description = ES(COMPOUND_STRING("A string exuding\n"
            "energy loved by\n"
            "certain Pokémon."), COMPOUND_STRING("Un cordón lleno de\n" "energía que adoran\n" "algunos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_LinkingCord,
        .iconPalette = gItemIconPalette_LinkingCord,
    },

    [ITEM_PEAT_BLOCK] =
    {
        .name = ES(ITEM_NAME("Peat Block"), ITEM_NAME("Bloque de Turba")),
        .price = 10000,
        .description = ES(COMPOUND_STRING("A block of material.\n"
            "It is loved by\n"
            "a certain Pokémon."), COMPOUND_STRING("Un bloque de turba\n" "que adora cierto\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_PeatBlock,
        .iconPalette = gItemIconPalette_PeatBlock,
    },

    [ITEM_BERSERK_GENE] =
    {
        .name = ES(ITEM_NAME("Berserk Gene"), ITEM_NAME("Gen Furia")),
        .price = 20,
        .holdEffect = HOLD_EFFECT_BERSERK_GENE,
        .description = ES(COMPOUND_STRING("Sharply raises\n"
            "Attack, but causes\n"
            "lasting confusion."), COMPOUND_STRING("Sube mucho el\n" "Ataque, pero\n" "confunde.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_BerserkGene,
        .iconPalette = gItemIconPalette_BerserkGene,
    },

    [ITEM_FAIRY_FEATHER] =
    {
        .name = ES(ITEM_NAME("Fairy Feather"), ITEM_NAME("Pluma Feérica")),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = ES(COMPOUND_STRING("A held item that\n"
            "raises the power of\n"
            "Fairy-type moves."), COMPOUND_STRING("Potencia los\n" "movimientos de tipo\n" "Hada.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FAIRY,
        .flingPower = 10,
        .iconPic = gItemIcon_FairyFeather,
        .iconPalette = gItemIconPalette_FairyFeather,
    },

    [ITEM_SYRUPY_APPLE] =
    {
        .name = ES(ITEM_NAME("Syrupy Apple"), ITEM_NAME("Manzana Melosa")),
        .price = 2200,
        .description = ES(COMPOUND_STRING("A peculiar apple\n"
            "that makes certain\n"
            "Pokémon evolve."), COMPOUND_STRING("Una manzana rara que\n" "hace evolucionar a\n" "algunos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_SyrupyApple,
        .iconPalette = gItemIconPalette_SyrupyApple,
    },

    [ITEM_UNREMARKABLE_TEACUP] =
    {
        .name = ES(ITEM_NAME("Unremarkable Teacup"), ITEM_NAME("Cuenco Mediocre")),
        .price = 1600,
        .description = ES(COMPOUND_STRING("A peculiar teacup\n"
            "that makes certain\n"
            "Pokémon evolve."), COMPOUND_STRING("Un cuenco raro que\n" "hace evolucionar a\n" "algunos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_UnremarkableTeacup,
        .iconPalette = gItemIconPalette_UnremarkableTeacup,
    },

    [ITEM_MASTERPIECE_TEACUP] =
    {
        .name = ES(ITEM_NAME("Masterpiece Teacup"), ITEM_NAME("Cuenco Exquisito")),
        .price = 38000,
        .description = ES(COMPOUND_STRING("A peculiar teacup\n"
            "that makes certain\n"
            "Pokémon evolve."), COMPOUND_STRING("Un cuenco raro que\n" "hace evolucionar a\n" "algunos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_MasterpieceTeacup,
        .iconPalette = gItemIconPalette_MasterpieceTeacup,
    },

    [ITEM_CORNERSTONE_MASK] =
    {
        .name = ES(ITEM_NAME("Cornerstone Mask"), ITEM_NAME("Máscara Cimiento")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_OGERPON_MASK,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("Allows Ogerpon to\n"
            "wield the Rock\n"
            "type in battle."), COMPOUND_STRING("Ogerpon puede usar\n" "el tipo Roca en\n" "combate.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_CornerstoneMask,
        .iconPalette = gItemIconPalette_CornerstoneMask,
    },

    [ITEM_WELLSPRING_MASK] =
    {
        .name = ES(ITEM_NAME("Wellspring Mask"), ITEM_NAME("Máscara Fuente")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_OGERPON_MASK,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("Allows Ogerpon to\n"
            "wield the Water\n"
            "type in battle."), COMPOUND_STRING("Ogerpon puede usar\n" "el tipo Agua en\n" "combate.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_WellspringMask,
        .iconPalette = gItemIconPalette_WellspringMask,
    },

    [ITEM_HEARTHFLAME_MASK] =
    {
        .name = ES(ITEM_NAME("Hearthflame Mask"), ITEM_NAME("Máscara Horno")),
        .price = 0,
        .holdEffect = HOLD_EFFECT_OGERPON_MASK,
        .holdEffectParam = 20,
        .description = ES(COMPOUND_STRING("Allows Ogerpon to\n"
            "wield the Fire\n"
            "type in battle."), COMPOUND_STRING("Ogerpon puede usar\n" "el tipo Fuego en\n" "combate.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_HearthflameMask,
        .iconPalette = gItemIconPalette_HearthflameMask,
    },

    [ITEM_HEALTH_MOCHI] =
    {
        .name = ES(ITEM_NAME("Health Mochi"), ITEM_NAME("Mochi Vigor")),
        .pluralName = ITEM_PLURAL_NAME("Health Mochi"),
        .price = 500,
        .description = ES(COMPOUND_STRING("Raises the base HP\n"
            "of one Pokémon."), COMPOUND_STRING("Sube la base de PS\n" "de un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_MOCHI,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_HpMochi,
        .flingPower = 30,
        .iconPic = gItemIcon_Mochi,
        .iconPalette = gItemIconPalette_HealthMochi,
    },

    [ITEM_MUSCLE_MOCHI] =
    {
        .name = ES(ITEM_NAME("Muscle Mochi"), ITEM_NAME("Mochi Músculo")),
        .pluralName = ITEM_PLURAL_NAME("Muscle Mochi"),
        .price = 500,
        .description = ES(COMPOUND_STRING("Raises the base\n"
            "Attack stat of one\n"
            "Pokémon."), COMPOUND_STRING("Sube la base de\n" "Ataque de un\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_MOCHI,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_AtkMochi,
        .flingPower = 30,
        .iconPic = gItemIcon_Mochi,
        .iconPalette = gItemIconPalette_MuscleMochi,
    },

    [ITEM_RESIST_MOCHI] =
    {
        .name = ES(ITEM_NAME("Resist Mochi"), ITEM_NAME("Mochi Aguante")),
        .pluralName = ITEM_PLURAL_NAME("Resist Mochi"),
        .price = 500,
        .description = ES(COMPOUND_STRING("Raises the base\n"
            "Defense stat of\n"
            "one Pokémon."), COMPOUND_STRING("Sube la base de\n" "Defensa de un\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_MOCHI,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_DefMochi,
        .flingPower = 30,
        .iconPic = gItemIcon_Mochi,
        .iconPalette = gItemIconPalette_ResistMochi,
    },

    [ITEM_GENIUS_MOCHI] =
    {
        .name = ES(ITEM_NAME("Genius Mochi"), ITEM_NAME("Mochi Intelecto")),
        .pluralName = ITEM_PLURAL_NAME("Genius Mochi"),
        .price = 500,
        .description = ES(COMPOUND_STRING("Raises the base\n"
            "Sp. Atk stat of one\n"
            "Pokémon."), COMPOUND_STRING("Sube la base de At.\n" "Esp. de un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_MOCHI,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_SpatkMochi,
        .flingPower = 30,
        .iconPic = gItemIcon_Mochi,
        .iconPalette = gItemIconPalette_GeniusMochi,
    },

    [ITEM_CLEVER_MOCHI] =
    {
        .name = ES(ITEM_NAME("Clever Mochi"), ITEM_NAME("Mochi Mente")),
        .pluralName = ITEM_PLURAL_NAME("Clever Mochi"),
        .price = 500,
        .description = ES(COMPOUND_STRING("Raises the base\n"
            "Sp. Def stat of one\n"
            "Pokémon."), COMPOUND_STRING("Sube la base de Def.\n" "Esp. de un Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_MOCHI,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_SpdefMochi,
        .flingPower = 30,
        .iconPic = gItemIcon_Mochi,
        .iconPalette = gItemIconPalette_CleverMochi,
    },

    [ITEM_SWIFT_MOCHI] =
    {
        .name = ES(ITEM_NAME("Swift Mochi"), ITEM_NAME("Mochi Ímpetu")),
        .pluralName = ITEM_PLURAL_NAME("Swift Mochi"),
        .price = 500,
        .description = ES(COMPOUND_STRING("Raises the base\n"
            "Speed stat of one\n"
            "Pokémon."), COMPOUND_STRING("Sube la base de\n" "Velocidad de un\n" "Pokémon.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_MOCHI,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_SpeedMochi,
        .flingPower = 30,
        .iconPic = gItemIcon_Mochi,
        .iconPalette = gItemIconPalette_SwiftMochi,
    },

    [ITEM_FRESH_START_MOCHI] =
    {
        .name = ES(ITEM_NAME("Fresh-Start Mochi"), ITEM_NAME("Mochi Reinicio")),
        .pluralName = ITEM_PLURAL_NAME("Fresh-Start Mochi"),
        .price = 300,
        .description = ES(COMPOUND_STRING("A cake that causes\n"
            "a Pokémon to lose\n"
            "all its base stats."), COMPOUND_STRING("Un pastel que deja a\n" "cero los puntos de\n" "base.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_MOCHI,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_ResetEVs,
        .effect = gItemEffect_ResetMochi,
        .flingPower = 30,
        .iconPic = gItemIcon_Mochi,
        .iconPalette = gItemIconPalette_FreshStartMochi,
    },

    [ITEM_GLIMMERING_CHARM] =
    {
        .name = ES(ITEM_NAME("Glimmering Charm"), ITEM_NAME("Amuleto Cristalino")),
        .price = 0,
        .importance = 1,
        .description = ES(COMPOUND_STRING("Increases the\n"
            "number of Tera\n"
            "Shards from raids."), COMPOUND_STRING("Más teralitas en las\n" "incursiones.")),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_GlimmeringCharm,
        .iconPalette = gItemIconPalette_GlimmeringCharm,
    },

    [ITEM_METAL_ALLOY] =
    {
        .name = ES(ITEM_NAME("Metal Alloy"), ITEM_NAME("Metal Compuesto")),
        .price = 6000,
        .description = ES(COMPOUND_STRING("A peculiar metal\n"
            "that makes certain\n"
            "Pokémon evolve."), COMPOUND_STRING("Un metal raro que\n" "hace evolucionar a\n" "algunos.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .iconPic = gItemIcon_MetalAlloy,
        .iconPalette = gItemIconPalette_MetalAlloy,
    },

    [ITEM_STELLAR_TERA_SHARD] =
    {
        .name = ES(ITEM_NAME("Stellar Tera Shard"), ITEM_NAME("Teralito Astral")),
        .price = 0,
        .description = ES(COMPOUND_STRING("Shards that may\n"
            "form when a Tera\n"
            "Pokémon falls."), COMPOUND_STRING("Fragmentos que deja\n" "un Pokémon\n" "teracristalizado.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_StellarTeraShard,
        .iconPalette = gItemIconPalette_StellarTeraShard,
    },

    [ITEM_JUBILIFE_MUFFIN] =
    {
        .name = ES(ITEM_NAME("Jubilife Muffin"), ITEM_NAME("Bollo Jubileo")),
        .price = 250,
        .description = ES(COMPOUND_STRING("A local specialty\n"
            "that heals all\n"
            "status problems."), COMPOUND_STRING("Especialidad local\n" "que cura todos los\n" "estados.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_JubilifeMuffin,
        .iconPalette = gItemIconPalette_JubilifeMuffin,
    },

    [ITEM_REMEDY] =
    {
        .name = ES(ITEM_NAME("Remedy"), ITEM_NAME("Remedio")),
        .pluralName = ITEM_PLURAL_NAME("Remedies"),
        .price = 150,
        .description = ES(COMPOUND_STRING("A bitter powder\n"
            "that restores HP\n"
            "by 20 points."), COMPOUND_STRING("Un polvo amargo que\n" "restaura 20 PS.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_Remedy,
        .flingPower = 30,
        .iconPic = gItemIcon_Remedy,
        .iconPalette = gItemIconPalette_Remedy,
    },

    [ITEM_FINE_REMEDY] =
    {
        .name = ES(ITEM_NAME("Fine Remedy"), ITEM_NAME("Remedio Fino")),
        .pluralName = ITEM_PLURAL_NAME("Fine Remedies"),
        .price = 150,
        .description = COMPOUND_STRING(
            "A bitter powder\n"
            "that restores HP\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "by 60 points."),
        #else
            "by 50 points."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_FineRemedy,
        .flingPower = 30,
        .iconPic = gItemIcon_FineRemedy,
        .iconPalette = gItemIconPalette_FineRemedy,
    },

    [ITEM_SUPERB_REMEDY] =
    {
        .name = ES(ITEM_NAME("Superb Remedy"), ITEM_NAME("Remedio Excelso")),
        .pluralName = ITEM_PLURAL_NAME("Superb Remedies"),
        .price = 750,
        .description = COMPOUND_STRING(
            "A bitter powder\n"
            "that restores HP\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "by 120 points."),
        #else
            "by 200 points."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_SuperbRemedy,
        .flingPower = 30,
        .iconPic = gItemIcon_SuperbRemedy,
        .iconPalette = gItemIconPalette_SuperbRemedy,
    },

    [ITEM_AUX_EVASION] =
    {
        .name = ES(ITEM_NAME("Aux Evasion"), ITEM_NAME("Aux. Evasión")),
        .price = 800,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises\n"
            "evasiveness\n"
            "during one battle."),
        #else
            "Raises evasiveness\n"
            "during one battle."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_AUX_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        //.effect = currently missing
        .iconPic = gItemIcon_AuxBottle,
        .iconPalette = gItemIconPalette_AuxEvasion,
    },

    [ITEM_AUX_GUARD] =
    {
        .name = ES(ITEM_NAME("Aux Guard"), ITEM_NAME("Aux. Defensa")),
        .price = 400,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises\n"
            "defensive stats\n"
            "during one battle."),
        #else
            "Raises Defense\n"
            "and Sp. Def\n"
            "during one battle."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_AUX_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        //.effect = currently missing
        .iconPic = gItemIcon_AuxBottle,
        .iconPalette = gItemIconPalette_AuxGuard,
    },

    [ITEM_AUX_POWER] =
    {
        .name = ES(ITEM_NAME("Aux Power"), ITEM_NAME("Aux. Ataque")),
        .price = 400,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises\n"
            "offensive stats\n"
            "during one battle."),
        #else
            "Raises Attack\n"
            "and Sp. Atk\n"
            "during one battle."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_AUX_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        //.effect = currently missing
        .iconPic = gItemIcon_AuxBottle,
        .iconPalette = gItemIconPalette_AuxPower,
    },

    [ITEM_AUX_POWERGUARD] =
    {
        .name = ES(ITEM_NAME("Aux Powerguard"), ITEM_NAME("Aux. Total")),
        .price = 1200,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises\n"
            "offense & defense\n"
            "during one battle."),
        #else
            "Raises offenses\n"
            "and defenses\n"
            "during one battle."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_AUX_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        //.effect = currently missing
        .iconPic = gItemIcon_AuxPowerguard,
        .iconPalette = gItemIconPalette_AuxPowerguard,
    },

    [ITEM_CHOICE_DUMPLING] =
    {
        .name = ES(ITEM_NAME("Choice Dumpling"), ITEM_NAME("Dango Elección")),
        .price = 1200,
        .description = COMPOUND_STRING("?????"),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_AUX_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        //.effect = currently missing
        .iconPic = gItemIcon_ChoiceDumpling,
        .iconPalette = gItemIconPalette_ChoiceDumpling,
    },

    [ITEM_SWAP_SNACK] =
    {
        .name = ES(ITEM_NAME("Swap Snack"), ITEM_NAME("Tentempié Cambio")),
        .price = 1200,
        .description = COMPOUND_STRING("?????"),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_AUX_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        //.effect = currently missing
        .iconPic = gItemIcon_SwapSnack,
        .iconPalette = gItemIconPalette_SwapSnack,
    },

    [ITEM_TWICE_SPICED_RADISH] =
    {
        .name = ES(ITEM_NAME("Twice-Spiced Radish"), ITEM_NAME("Rábano Picante")),
        .pluralName = ITEM_PLURAL_NAME("Twice-Spiced Radishes"),
        .price = 1600,
        .description = COMPOUND_STRING("?????"),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_AUX_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        //.effect = currently missing
        .iconPic = gItemIcon_TwiceSpicedRadish,
        .iconPalette = gItemIconPalette_TwiceSpicedRadish,
    },

    [ITEM_POKESHI_DOLL] =
    {
        .name = ES(ITEM_NAME("Pokéshi Doll"), ITEM_NAME("Muñeca Pokéshi")),
        .price = 2000,
        .description = ES(COMPOUND_STRING("A wooden toy in the\n"
            "image of a Pokémon.\n"
            "It can be sold."), COMPOUND_STRING("Un muñeco de madera\n" "de un Pokémon. Se\n" "puede vender.")),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_PokeshiDoll,
        .iconPalette = gItemIconPalette_PokeshiDoll,
    },
};

#undef ITEM_NAME
#undef ITEM_PLURAL_NAME
