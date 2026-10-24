const struct AbilityInfo gAbilitiesInfo[ABILITIES_COUNT] =
{
    [ABILITY_NONE] =
    {
        .name = _("-------"),
        .description = COMPOUND_STRING("No Ability."),
        .aiRating = 0,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_STENCH] =
    {
        .name = ES(_("Stench"), _("Hedor")),
        .description = COMPOUND_STRING("Moves may cause flinching."),
        .aiRating = 1,
    },

    [ABILITY_DRIZZLE] =
    {
        .name = ES(_("Drizzle"), _("Llovizna")),
        .description = COMPOUND_STRING("Summons rain in battle."),
        .aiRating = 9,
    },

    [ABILITY_SPEED_BOOST] =
    {
        .name = ES(_("Speed Boost"), _("Impulso")),
        .description = COMPOUND_STRING("Speed raises every turn."),
        .aiRating = 9,
    },

    [ABILITY_BATTLE_ARMOR] =
    {
        .name = ES(_("Battle Armor"), _("Armadura Batalla")),
        .description = COMPOUND_STRING("Blocks critical hits."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_STURDY] =
    {
        .name = ES(_("Sturdy"), _("Robustez")),
        .description = COMPOUND_STRING("Negates 1-hit KO attacks."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DAMP] =
    {
        .name = ES(_("Damp"), _("Humedad")),
        .description = COMPOUND_STRING("Prevents self-destruction."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_LIMBER] =
    {
        .name = ES(_("Limber"), _("Flexibilidad")),
        .description = COMPOUND_STRING("Prevents paralysis."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SAND_VEIL] =
    {
        .name = ES(_("Sand Veil"), _("Velo Arena")),
        .description = COMPOUND_STRING("Ups evasion in a sandstorm."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_STATIC] =
    {
        .name = ES(_("Static"), _("Elec. Estática")),
        .description = COMPOUND_STRING("May paralyze on contact."),
        .aiRating = 4,
    },

    [ABILITY_VOLT_ABSORB] =
    {
        .name = ES(_("Volt Absorb"), _("Absorbe Elec.")),
        .description = COMPOUND_STRING("Restores if hit by Electric."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_WATER_ABSORB] =
    {
        .name = ES(_("Water Absorb"), _("Absorbe Agua")),
        .description = COMPOUND_STRING("Restores HP if hit by Water."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_OBLIVIOUS] =
    {
        .name = ES(_("Oblivious"), _("Despiste")),
        .description = COMPOUND_STRING(
        #if B_OBLIVIOUS_TAUNT >= GEN_6
            "Blocks Attract and Taunt."),
        #else
            "Prevents attraction."),
        #endif
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_CLOUD_NINE] =
    {
        .name = ES(_("Cloud Nine"), _("Aclimatación")),
        .description = COMPOUND_STRING("Negates weather effects."),
        .aiRating = 5,
    },

    [ABILITY_COMPOUND_EYES] =
    {
        .name = ES(_("Compound Eyes"), _("Ojo Compuesto")),
        .description = COMPOUND_STRING("Boosts accuracy."),
        .aiRating = 7,
    },

    [ABILITY_INSOMNIA] =
    {
        .name = ES(_("Insomnia"), _("Insomnio")),
        .description = COMPOUND_STRING("Prevents sleep."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_COLOR_CHANGE] =
    {
        .name = ES(_("Color Change"), _("Cambio Color")),
        .description = COMPOUND_STRING("Changes type to foe's move."),
        .aiRating = 2,
    },

    [ABILITY_IMMUNITY] =
    {
        .name = ES(_("Immunity"), _("Inmunidad")),
        .description = COMPOUND_STRING("Prevents poisoning."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_FLASH_FIRE] =
    {
        .name = ES(_("Flash Fire"), _("Absorbe Fuego")),
        .description = COMPOUND_STRING("Powers up Fire if hit by it."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SHIELD_DUST] =
    {
        .name = ES(_("Shield Dust"), _("Polvo Escudo")),
        .description = COMPOUND_STRING("Blocks foes' added effects."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_OWN_TEMPO] =
    {
        .name = ES(_("Own Tempo"), _("Ritmo Propio")),
        .description = COMPOUND_STRING("Prevents confusion."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SUCTION_CUPS] =
    {
        .name = ES(_("Suction Cups"), _("Ventosas")),
        .description = COMPOUND_STRING("Can't be forced to switch."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_INTIMIDATE] =
    {
        .name = ES(_("Intimidate"), _("Intimidación")),
        .description = COMPOUND_STRING("Lowers foes' Atk on entry."),
        .aiRating = 7,
    },

    [ABILITY_SHADOW_TAG] =
    {
        .name = ES(_("Shadow Tag"), _("Sombra Trampa")),
        .description = COMPOUND_STRING("Prevents the foes' escape."),
        .aiRating = 10,
    },

    [ABILITY_ROUGH_SKIN] =
    {
        .name = ES(_("Rough Skin"), _("Piel Tosca")),
        .description = COMPOUND_STRING("Damages foe on contact."),
        .aiRating = 6,
    },

    [ABILITY_WONDER_GUARD] =
    {
        .name = ES(_("Wonder Guard"), _("Superguarda")),
        .description = COMPOUND_STRING("Only “supereffective” hits."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_LEVITATE] =
    {
        .name = ES(_("Levitate"), _("Levitación")),
        .description = COMPOUND_STRING("Not hit by Ground attacks."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_EFFECT_SPORE] =
    {
        .name = ES(_("Effect Spore"), _("Efecto Espora")),
        .description = COMPOUND_STRING("Contact may psn/slp/par."),
        .aiRating = 4,
    },

    [ABILITY_SYNCHRONIZE] =
    {
        .name = ES(_("Synchronize"), _("Sincronía")),
        .description = COMPOUND_STRING("Passes on brn/par/psn."),
        .aiRating = 4,
    },

    [ABILITY_CLEAR_BODY] =
    {
        .name = ES(_("Clear Body"), _("Cuerpo Puro")),
        .description = COMPOUND_STRING("Stats can't be lowered."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_NATURAL_CURE] =
    {
        .name = ES(_("Natural Cure"), _("Cura Natural")),
        .description = COMPOUND_STRING("Heals status upon switch."),
        .aiRating = 7,
    },

    [ABILITY_LIGHTNING_ROD] =
    {
        .name = ES(_("Lightning Rod"), _("Pararrayos")),
        .description = COMPOUND_STRING(
        #if B_REDIRECT_ABILITY_IMMUNITY >= GEN_4
            "Draws Electr. to up Sp. Atk."),
        #else
            "Draws Electric moves."),
        #endif
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_SERENE_GRACE] =
    {
        .name = ES(_("Serene Grace"), _("Dicha")),
        .description = COMPOUND_STRING("Promotes added effects."),
        .aiRating = 8,
    },

    [ABILITY_SWIFT_SWIM] =
    {
        .name = ES(_("Swift Swim"), _("Nado Rápido")),
        .description = COMPOUND_STRING("Boosts Speed in rain."),
        .aiRating = 6,
    },

    [ABILITY_CHLOROPHYLL] =
    {
        .name = ES(_("Chlorophyll"), _("Clorofila")),
        .description = COMPOUND_STRING("Boosts Speed in sunlight."),
        .aiRating = 6,
    },

    [ABILITY_ILLUMINATE] =
    {
        .name = ES(_("Illuminate"), _("Iluminación")),
        .description = 
        #if B_ILLUMINATE_EFFECT >= GEN_9
            COMPOUND_STRING("Accuracy can't be lowered."),
        #else
            COMPOUND_STRING("Encounter rate increases."),
        #endif
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_TRACE] =
    {
        .name = ES(_("Trace"), _("Calco")),
        .description = COMPOUND_STRING("Copies a foe's Ability."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE, //B_UPDATED_ABILITY_DATA >= GEN_4
    },

    [ABILITY_HUGE_POWER] =
    {
        .name = ES(_("Huge Power"), _("Potencia")),
        .description = COMPOUND_STRING("Doubles Attack."),
        .aiRating = 10,
    },

    [ABILITY_POISON_POINT] =
    {
        .name = ES(_("Poison Point"), _("Punto Tóxico")),
        .description = COMPOUND_STRING("May poison foe on contact."),
        .aiRating = 4,
    },

    [ABILITY_INNER_FOCUS] =
    {
        .name = ES(_("Inner Focus"), _("Fuerza Mental")),
        .description = COMPOUND_STRING("Prevents flinching."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MAGMA_ARMOR] =
    {
        .name = ES(_("Magma Armor"), _("Escudo Magma")),
        .description = COMPOUND_STRING(
        #if B_USE_FROSTBITE
            "Prevents frostbite."),
        #else
            "Prevents freezing."),
        #endif
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_WATER_VEIL] =
    {
        .name = ES(_("Water Veil"), _("Velo Agua")),
        .description = COMPOUND_STRING("Prevents burns."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_MAGNET_PULL] =
    {
        .name = ES(_("Magnet Pull"), _("Imán")),
        .description = COMPOUND_STRING("Traps Steel-type foes."),
        .aiRating = 9,
    },

    [ABILITY_SOUNDPROOF] =
    {
        .name = ES(_("Soundproof"), _("Insonorizar")),
        .description = COMPOUND_STRING("Avoids sound-based moves."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_RAIN_DISH] =
    {
        .name = ES(_("Rain Dish"), _("Cura Lluvia")),
        .description = COMPOUND_STRING("Slight HP recovery in rain."),
        .aiRating = 3,
    },

    [ABILITY_SAND_STREAM] =
    {
        .name = ES(_("Sand Stream"), _("Chorro Arena")),
        .description = COMPOUND_STRING("Summons a sandstorm."),
        .aiRating = 9,
    },

    [ABILITY_PRESSURE] =
    {
        .name = ES(_("Pressure"), _("Presión")),
        .description = COMPOUND_STRING("Raises foe's PP usage."),
        .aiRating = 5,
    },

    [ABILITY_THICK_FAT] =
    {
        .name = ES(_("Thick Fat"), _("Sebo")),
        .description = COMPOUND_STRING("Halves Fire and Ice damage."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_EARLY_BIRD] =
    {
        .name = ES(_("Early Bird"), _("Madrugar")),
        .description = COMPOUND_STRING("Awakens twice as fast."),
        .aiRating = 4,
    },

    [ABILITY_FLAME_BODY] =
    {
        .name = ES(_("Flame Body"), _("Cuerpo Llama")),
        .description = COMPOUND_STRING("May burn foe on contact."),
        .aiRating = 4,
    },

    [ABILITY_RUN_AWAY] =
    {
        .name = ES(_("Run Away"), _("Fuga")),
        .description = COMPOUND_STRING("Enables a sure getaway."),
        .aiRating = 0,
    },

    [ABILITY_KEEN_EYE] =
    {
        .name = ES(_("Keen Eye"), _("Vista Lince")),
        .description = COMPOUND_STRING("Accuracy can't be lowered."),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_HYPER_CUTTER] =
    {
        .name = ES(_("Hyper Cutter"), _("Corte Fuerte")),
        .description = COMPOUND_STRING("Attack can't be lowered."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_PICKUP] =
    {
        .name = ES(_("Pickup"), _("Recogida")),
        .description = COMPOUND_STRING("May pick up items."),
        .aiRating = 1,
    },

    [ABILITY_TRUANT] =
    {
        .name = ES(_("Truant"), _("Ausente")),
        .description = COMPOUND_STRING("Moves only every two turns."),
        .aiRating = -2,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_HUSTLE] =
    {
        .name = ES(_("Hustle"), _("Entusiasmo")),
        .description = COMPOUND_STRING("Trades accuracy for power."),
        .aiRating = 7,
    },

    [ABILITY_CUTE_CHARM] =
    {
        .name = ES(_("Cute Charm"), _("Gran Encanto")),
        .description = COMPOUND_STRING("May infatuate on contact."),
        .aiRating = 2,
    },

    [ABILITY_PLUS] =
    {
        .name = ES(_("Plus"), _("Más")),
        .description =
        #if B_PLUS_MINUS_INTERACTION >= GEN_5
            COMPOUND_STRING("Ups Sp. Atk with Minus."),
        #else
            COMPOUND_STRING("Plus or Minus ups Sp. Atk."),
        #endif
        .aiRating = 0,
    },

    [ABILITY_MINUS] =
    {
        .name = ES(_("Minus"), _("Menos")),
        .description =
        #if B_PLUS_MINUS_INTERACTION >= GEN_5
            COMPOUND_STRING("Ups Sp. Atk with Plus."),
        #else
            COMPOUND_STRING("Plus or Minus ups Sp. Atk."),
        #endif
        .aiRating = 0,
    },

    [ABILITY_FORECAST] =
    {
        .name = ES(_("Forecast"), _("Predicción")),
        .description = COMPOUND_STRING("Changes with the weather."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = B_UPDATED_ABILITY_DATA >= GEN_4,
        .failsOnImposter = B_UPDATED_ABILITY_DATA >= GEN_5,
    },

    [ABILITY_STICKY_HOLD] =
    {
        .name = ES(_("Sticky Hold"), _("Viscosidad")),
        .description = COMPOUND_STRING("Held item can't be removed."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SHED_SKIN] =
    {
        .name = ES(_("Shed Skin"), _("Mudar")),
        .description = COMPOUND_STRING("May heal status problems."),
        .aiRating = 7,
    },

    [ABILITY_GUTS] =
    {
        .name = ES(_("Guts"), _("Agallas")),
        .description = COMPOUND_STRING("Boosts Attack if statused."),
        .aiRating = 6,
    },

    [ABILITY_MARVEL_SCALE] =
    {
        .name = ES(_("Marvel Scale"), _("Escama Especial")),
        .description = COMPOUND_STRING("Ups Defense if statused."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_LIQUID_OOZE] =
    {
        .name = ES(_("Liquid Ooze"), _("Lodo Líquido")),
        .description = COMPOUND_STRING("Damages HP-draining foes."),
        .aiRating = 3,
    },

    [ABILITY_OVERGROW] =
    {
        .name = ES(_("Overgrow"), _("Espesura")),
        .description = COMPOUND_STRING("Ups Grass moves at low HP."),
        .aiRating = 5,
    },

    [ABILITY_BLAZE] =
    {
        .name = ES(_("Blaze"), _("Mar Llamas")),
        .description = COMPOUND_STRING("Ups Fire moves at low HP."),
        .aiRating = 5,
    },

    [ABILITY_TORRENT] =
    {
        .name = ES(_("Torrent"), _("Torrente")),
        .description = COMPOUND_STRING("Ups Water moves at low HP."),
        .aiRating = 5,
    },

    [ABILITY_SWARM] =
    {
        .name = ES(_("Swarm"), _("Enjambre")),
        .description = COMPOUND_STRING("Ups Bug moves at low HP."),
        .aiRating = 5,
    },

    [ABILITY_ROCK_HEAD] =
    {
        .name = ES(_("Rock Head"), _("Cabeza Roca")),
        .description = COMPOUND_STRING("Prevents recoil damage."),
        .aiRating = 5,
    },

    [ABILITY_DROUGHT] =
    {
        .name = ES(_("Drought"), _("Sequía")),
        .description = COMPOUND_STRING("Summons sunlight in battle."),
        .aiRating = 9,
    },

    [ABILITY_ARENA_TRAP] =
    {
        .name = ES(_("Arena Trap"), _("Trampa Arena")),
        .description = COMPOUND_STRING("Prevents foes from fleeing."),
        .aiRating = 9,
    },

    [ABILITY_VITAL_SPIRIT] =
    {
        .name = ES(_("Vital Spirit"), _("Espíritu Vital")),
        .description = COMPOUND_STRING("Prevents sleep."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_WHITE_SMOKE] =
    {
        .name = ES(_("White Smoke"), _("Humo Blanco")),
        .description = COMPOUND_STRING("Stats can't be lowered."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_PURE_POWER] =
    {
        .name = ES(_("Pure Power"), _("Energía Pura")),
        .description = COMPOUND_STRING("Doubles Attack."),
        .aiRating = 10,
    },

    [ABILITY_SHELL_ARMOR] =
    {
        .name = ES(_("Shell Armor"), _("Caparazón")),
        .description = COMPOUND_STRING("Blocks critical hits."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_AIR_LOCK] =
    {
        .name = ES(_("Air Lock"), _("Bucle Aire")),
        .description = COMPOUND_STRING("Negates weather effects."),
        .aiRating = 5,
    },

    [ABILITY_TANGLED_FEET] =
    {
        .name = ES(_("Tangled Feet"), _("Tumbos")),
        .description = COMPOUND_STRING("Boosts evasion if confused."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MOTOR_DRIVE] =
    {
        .name = ES(_("Motor Drive"), _("Electromotor")),
        .description = COMPOUND_STRING("Ups Speed if hit by Electr."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_RIVALRY] =
    {
        .name = ES(_("Rivalry"), _("Rivalidad")),
        .description = COMPOUND_STRING("Strong vs. opposite gender."),
        .aiRating = 1,
    },

    [ABILITY_STEADFAST] =
    {
        .name = ES(_("Steadfast"), _("Impasible")),
        .description = COMPOUND_STRING("Flinching raises Speed."),
        .aiRating = 2,
    },

    [ABILITY_SNOW_CLOAK] =
    {
        .name = ES(_("Snow Cloak"), _("Manto Níveo")),
        .description = COMPOUND_STRING(
        #if B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_HAIL
            "Boosts evasion in hail."),
        #elif B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_SNOW
            "Boosts evasion in snow."),
        #else
            "Ups evasion in hail or snow."),
        #endif
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_GLUTTONY] =
    {
        .name = ES(_("Gluttony"), _("Gula")),
        .description = COMPOUND_STRING("Eats Berries at half HP."),
        .aiRating = 3,
    },

    [ABILITY_ANGER_POINT] =
    {
        .name = ES(_("Anger Point"), _("Irascible")),
        .description = COMPOUND_STRING("Maxes Attack when crit."),
        .aiRating = 4,
    },

    [ABILITY_UNBURDEN] =
    {
        .name = ES(_("Unburden"), _("Liviano")),
        .description = COMPOUND_STRING("Item loss boosts Speed."),
        .aiRating = 7,
    },

    [ABILITY_HEATPROOF] =
    {
        .name = ES(_("Heatproof"), _("Ignífugo")),
        .description = COMPOUND_STRING("Halves Fire-type damage."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SIMPLE] =
    {
        .name = _("Simple"),
        .description = COMPOUND_STRING("Doubles stat changes."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_DRY_SKIN] =
    {
        .name = ES(_("Dry Skin"), _("Piel Seca")),
        .description = COMPOUND_STRING("Heat hurts, Water restores."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DOWNLOAD] =
    {
        .name = ES(_("Download"), _("Descarga")),
        .description = COMPOUND_STRING("Ups offense based on foe."),
        .aiRating = 7,
    },

    [ABILITY_IRON_FIST] =
    {
        .name = ES(_("Iron Fist"), _("Puño Férreo")),
        .description = COMPOUND_STRING("Powers up punching moves."),
        .aiRating = 6,
    },

    [ABILITY_POISON_HEAL] =
    {
        .name = ES(_("Poison Heal"), _("Antídoto")),
        .description = COMPOUND_STRING("Restores HP if poisoned."),
        .aiRating = 8,
    },

    [ABILITY_ADAPTABILITY] =
    {
        .name = ES(_("Adaptability"), _("Adaptable")),
        .description = COMPOUND_STRING("Powers up same-type moves."),
        .aiRating = 8,
    },

    [ABILITY_SKILL_LINK] =
    {
        .name = ES(_("Skill Link"), _("Encadenado")),
        .description = COMPOUND_STRING("Maxes multistrike hits."),
        .aiRating = 7,
    },

    [ABILITY_HYDRATION] =
    {
        .name = ES(_("Hydration"), _("Hidratación")),
        .description = COMPOUND_STRING("Cures status in rain."),
        .aiRating = 4,
    },

    [ABILITY_SOLAR_POWER] =
    {
        .name = ES(_("Solar Power"), _("Poder Solar")),
        .description = COMPOUND_STRING("Sunlight boosts, but hurts."),
        .aiRating = 3,
    },

    [ABILITY_QUICK_FEET] =
    {
        .name = ES(_("Quick Feet"), _("Pies Rápidos")),
        .description = COMPOUND_STRING("Boosts Speed if statused."),
        .aiRating = 5,
    },

    [ABILITY_NORMALIZE] =
    {
        .name = ES(_("Normalize"), _("Normalidad")),
        .description = COMPOUND_STRING("Moves become Normal-type."),
        .aiRating = -1,
    },

    [ABILITY_SNIPER] =
    {
        .name = ES(_("Sniper"), _("Francotirador")),
        .description = COMPOUND_STRING("Powers up critical hits."),
        .aiRating = 3,
    },

    [ABILITY_MAGIC_GUARD] =
    {
        .name = ES(_("Magic Guard"), _("Muro Mágico")),
        .description = COMPOUND_STRING("Only damaged by attacks."),
        .aiRating = 9,
    },

    [ABILITY_NO_GUARD] =
    {
        .name = ES(_("No Guard"), _("Indefenso")),
        .description = COMPOUND_STRING("Ensures all attacks land."),
        .aiRating = 8,
    },

    [ABILITY_STALL] =
    {
        .name = ES(_("Stall"), _("Rezagado")),
        .description = COMPOUND_STRING("Always last to use moves."),
        .aiRating = -1,
    },

    [ABILITY_TECHNICIAN] =
    {
        .name = ES(_("Technician"), _("Experto")),
        .description = COMPOUND_STRING("Powers up weak moves."),
        .aiRating = 8,
    },

    [ABILITY_LEAF_GUARD] =
    {
        .name = ES(_("Leaf Guard"), _("Defensa Hoja")),
        .description = COMPOUND_STRING("Blocks status in sunlight."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_KLUTZ] =
    {
        .name = ES(_("Klutz"), _("Zoquete")),
        .description = COMPOUND_STRING("Can't use held items."),
        .aiRating = -1,
    },

    [ABILITY_MOLD_BREAKER] =
    {
        .name = ES(_("Mold Breaker"), _("Rompemoldes")),
        .description = COMPOUND_STRING("Moves ignore Abilities."),
        .aiRating = 7,
    },

    [ABILITY_SUPER_LUCK] =
    {
        .name = ES(_("Super Luck"), _("Afortunado")),
        .description = COMPOUND_STRING("Raises critical-hit ratio."),
        .aiRating = 3,
    },

    [ABILITY_AFTERMATH] =
    {
        .name = ES(_("Aftermath"), _("Detonación")),
        .description = COMPOUND_STRING("Fainting damages the foe."),
        .aiRating = 5,
    },

    [ABILITY_ANTICIPATION] =
    {
        .name = ES(_("Anticipation"), _("Anticipación")),
        .description = COMPOUND_STRING("Senses dangerous moves."),
        .aiRating = 2,
    },

    [ABILITY_FOREWARN] =
    {
        .name = ES(_("Forewarn"), _("Alerta")),
        .description = COMPOUND_STRING("Determines a foe's move."),
        .aiRating = 2,
    },

    [ABILITY_UNAWARE] =
    {
        .name = ES(_("Unaware"), _("Ignorante")),
        .description = COMPOUND_STRING("Ignores foes' stat changes."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_TINTED_LENS] =
    {
        .name = ES(_("Tinted Lens"), _("Cromolente")),
        .description = COMPOUND_STRING("Ups “not very effective”."),
        .aiRating = 7,
    },

    [ABILITY_FILTER] =
    {
        .name = ES(_("Filter"), _("Filtro")),
        .description = COMPOUND_STRING("Weakens “supereffective”."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SLOW_START] =
    {
        .name = ES(_("Slow Start"), _("Inicio Lento")),
        .description = COMPOUND_STRING("Takes 5 turns to get going."),
        .aiRating = -2,
    },

    [ABILITY_SCRAPPY] =
    {
        .name = ES(_("Scrappy"), _("Intrépido")),
        .description = COMPOUND_STRING("Normal & Fight. hit Ghosts."),
        .aiRating = 6,
    },

    [ABILITY_STORM_DRAIN] =
    {
        .name = ES(_("Storm Drain"), _("Colector")),
        .description = COMPOUND_STRING(
        #if B_REDIRECT_ABILITY_IMMUNITY >= GEN_4
            "Draws Water to up Sp. Atk."),
        #else
            "Draws Water-type moves."),
        #endif
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_ICE_BODY] =
    {
        .name = ES(_("Ice Body"), _("Gélido")),
        .description = COMPOUND_STRING(
        #if B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_HAIL
            "Slight HP recovery in hail."),
        #elif B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_SNOW
            "Slight HP recovery in snow."),
        #else
            "HP recovery in hail or snow."),
        #endif
        .aiRating = 3,
    },

    [ABILITY_SOLID_ROCK] =
    {
        .name = ES(_("Solid Rock"), _("Roca Sólida")),
        .description = COMPOUND_STRING("Weakens “supereffective”."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SNOW_WARNING] =
    {
        .name = ES(_("Snow Warning"), _("Nevada")),
    #if B_SNOW_WARNING >= GEN_9
        .description = COMPOUND_STRING("Summons snow in battle."),
    #else
        .description = COMPOUND_STRING("Summons hail in battle."),
    #endif
        .aiRating = 8,
    },

    [ABILITY_HONEY_GATHER] =
    {
        .name = ES(_("Honey Gather"), _("Recogemiel")),
        .description = COMPOUND_STRING("May gather Honey."),
        .aiRating = 0,
    },

    [ABILITY_FRISK] =
    {
        .name = ES(_("Frisk"), _("Cacheo")),
        .description = COMPOUND_STRING("Checks a foe's held item."),
        .aiRating = 3,
    },

    [ABILITY_RECKLESS] =
    {
        .name = ES(_("Reckless"), _("Audaz")),
        .description = COMPOUND_STRING("Powers up recoil moves."),
        .aiRating = 6,
    },

    [ABILITY_MULTITYPE] =
    {
        .name = ES(_("Multitype"), _("Multitipo")),
        .description = COMPOUND_STRING("Matches Plate or Z-Crystal."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = B_UPDATED_ABILITY_DATA >= GEN_5,
    },

    [ABILITY_FLOWER_GIFT] =
    {
        .name = ES(_("Flower Gift"), _("Don Floral")),
        .description = COMPOUND_STRING("Sun ups allies' Atk & Sp.Def."),
        .aiRating = 4,
        .cantBeCopied = TRUE,
        .cantBeTraced = B_UPDATED_ABILITY_DATA >= GEN_5,
        .breakable = TRUE,
    },

    [ABILITY_BAD_DREAMS] =
    {
        .name = ES(_("Bad Dreams"), _("Mal Sueño")),
        .description = COMPOUND_STRING("Damages sleeping foes."),
        .aiRating = 4,
    },

    [ABILITY_PICKPOCKET] =
    {
        .name = ES(_("Pickpocket"), _("Hurto")),
        .description = COMPOUND_STRING("Steals foe's item if hit."),
        .aiRating = 3,
    },

    [ABILITY_SHEER_FORCE] =
    {
        .name = ES(_("Sheer Force"), _("Potencia Bruta")),
        .description = COMPOUND_STRING("Trades effects for power."),
        .aiRating = 8,
    },

    [ABILITY_CONTRARY] =
    {
        .name = ES(_("Contrary"), _("Respondón")),
        .description = COMPOUND_STRING("Reverses stat changes."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_UNNERVE] =
    {
        .name = ES(_("Unnerve"), _("Nerviosismo")),
        .description = COMPOUND_STRING("Foes can't eat Berries."),
        .aiRating = 3,
    },

    [ABILITY_DEFIANT] =
    {
        .name = ES(_("Defiant"), _("Competitivo")),
        .description = COMPOUND_STRING("Stat-lowering ups Attack."),
        .aiRating = 5,
    },

    [ABILITY_DEFEATIST] =
    {
        .name = ES(_("Defeatist"), _("Flaqueza")),
        .description = COMPOUND_STRING("Halves offenses at half HP."),
        .aiRating = -1,
    },

    [ABILITY_CURSED_BODY] =
    {
        .name = ES(_("Cursed Body"), _("Cuerpo Maldito")),
        .description = COMPOUND_STRING("Contact may disable move."),
        .aiRating = 4,
    },

    [ABILITY_HEALER] =
    {
        .name = ES(_("Healer"), _("Alma Cura")),
        .description = COMPOUND_STRING("May cure ally's status."),
        .aiRating = 0,
    },

    [ABILITY_FRIEND_GUARD] =
    {
        .name = ES(_("Friend Guard"), _("Compiescolta")),
        .description = COMPOUND_STRING("Reduces damage to allies."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_WEAK_ARMOR] =
    {
        .name = ES(_("Weak Armor"), _("Armadura Frágil")),
        .description = COMPOUND_STRING("Hits change Def and Speed."),
        .aiRating = 2,
    },

    [ABILITY_HEAVY_METAL] =
    {
        .name = ES(_("Heavy Metal"), _("Metal Pesado")),
        .description = COMPOUND_STRING("Doubles weight."),
        .aiRating = -1,
        .breakable = TRUE,
    },

    [ABILITY_LIGHT_METAL] =
    {
        .name = ES(_("Light Metal"), _("Metal Liviano")),
        .description = COMPOUND_STRING("Halves weight."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MULTISCALE] =
    {
        .name = ES(_("Multiscale"), _("Multiescamas")),
        .description = COMPOUND_STRING("Reduces damage at full HP."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_TOXIC_BOOST] =
    {
        .name = ES(_("Toxic Boost"), _("Ímpetu Tóxico")),
        .description = COMPOUND_STRING("Boosts Attack if poisoned."),
        .aiRating = 6,
    },

    [ABILITY_FLARE_BOOST] =
    {
        .name = ES(_("Flare Boost"), _("Ímpetu Ardiente")),
        .description = COMPOUND_STRING("Boosts Sp. Atk if burned."),
        .aiRating = 5,
    },

    [ABILITY_HARVEST] =
    {
        .name = ES(_("Harvest"), _("Cosecha")),
        .description = COMPOUND_STRING("May create another Berry."),
        .aiRating = 5,
    },

    [ABILITY_TELEPATHY] =
    {
        .name = ES(_("Telepathy"), _("Telepatía")),
        .description = COMPOUND_STRING("Dodges ally's attacks."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_MOODY] =
    {
        .name = ES(_("Moody"), _("Veleta")),
        .description = COMPOUND_STRING("Stats change every turn."),
        .aiRating = 10,
    },

    [ABILITY_OVERCOAT] =
    {
        .name = ES(_("Overcoat"), _("Funda")),
        .description = COMPOUND_STRING(
        #if B_POWDER_OVERCOAT >= GEN_6
            "Blocks weather and powder."),
        #else
            "Prevents weather damage."),
        #endif
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_POISON_TOUCH] =
    {
        .name = ES(_("Poison Touch"), _("Toque Tóxico")),
        .description = COMPOUND_STRING("Contact moves may poison."),
        .aiRating = 4,
    },

    [ABILITY_REGENERATOR] =
    {
        .name = ES(_("Regenerator"), _("Regeneración")),
        .description = COMPOUND_STRING("Restores HP upon switch."),
        .aiRating = 8,
    },

    [ABILITY_BIG_PECKS] =
    {
        .name = ES(_("Big Pecks"), _("Sacapecho")),
        .description = COMPOUND_STRING("Defense can't be lowered."),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_SAND_RUSH] =
    {
        .name = ES(_("Sand Rush"), _("Ímpetu Arena")),
        .description = COMPOUND_STRING("Ups Speed in a sandstorm."),
        .aiRating = 6,
    },

    [ABILITY_WONDER_SKIN] =
    {
        .name = ES(_("Wonder Skin"), _("Piel Milagro")),
        .description = COMPOUND_STRING("May avoid status moves."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANALYTIC] =
    {
        .name = ES(_("Analytic"), _("Cálculo Final")),
        .description = COMPOUND_STRING("Boosts power if last to act."),
        .aiRating = 5,
    },

    [ABILITY_ILLUSION] =
    {
        .name = ES(_("Illusion"), _("Ilusión")),
        .description = COMPOUND_STRING("Disguises as a partner."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_IMPOSTER] =
    {
        .name = ES(_("Imposter"), _("Impostor")),
        .description = COMPOUND_STRING("Transforms into the foe."),
        .aiRating = 9,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_INFILTRATOR] =
    {
        .name = ES(_("Infiltrator"), _("Allanamiento")),
        .description = COMPOUND_STRING("Passes through barriers."),
        .aiRating = 6,
    },

    [ABILITY_MUMMY] =
    {
        .name = ES(_("Mummy"), _("Momia")),
        .description = COMPOUND_STRING("Ability spreads on contact."),
        .aiRating = 5,
    },

    [ABILITY_MOXIE] =
    {
        .name = ES(_("Moxie"), _("Autoestima")),
        .description = COMPOUND_STRING("Raises Attack after KOs."),
        .aiRating = 7,
    },

    [ABILITY_JUSTIFIED] =
    {
        .name = ES(_("Justified"), _("Justiciero")),
        .description = COMPOUND_STRING("Ups Attack if hit by Dark."),
        .aiRating = 4,
    },

    [ABILITY_RATTLED] =
    {
        .name = ES(_("Rattled"), _("Cobardía")),
        .description = COMPOUND_STRING("Raises Speed when scared."),
        .aiRating = 3,
    },

    [ABILITY_MAGIC_BOUNCE] =
    {
        .name = ES(_("Magic Bounce"), _("Espejo Mágico")),
        .description = COMPOUND_STRING("Reflects status moves."),
        .aiRating = 9,
        .breakable = TRUE,
    },

    [ABILITY_SAP_SIPPER] =
    {
        .name = ES(_("Sap Sipper"), _("Herbívoro")),
        .description = COMPOUND_STRING("Ups Attack if hit by Grass."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_PRANKSTER] =
    {
        .name = ES(_("Prankster"), _("Bromista")),
        .description = COMPOUND_STRING("Status moves have priority."),
        .aiRating = 8,
    },

    [ABILITY_SAND_FORCE] =
    {
        .name = ES(_("Sand Force"), _("Poder Arena")),
        .description = COMPOUND_STRING("Powers up in a sandstorm."),
        .aiRating = 4,
    },

    [ABILITY_IRON_BARBS] =
    {
        .name = ES(_("Iron Barbs"), _("Punta Acero")),
        .description = COMPOUND_STRING("Damages foe on contact."),
        .aiRating = 6,
    },

    [ABILITY_ZEN_MODE] =
    {
        .name = ES(_("Zen Mode"), _("Modo Daruma")),
        .description = COMPOUND_STRING("Changes shape at half HP."),
        .aiRating = -1,
        .cantBeCopied = TRUE,
        .cantBeSwapped = B_UPDATED_ABILITY_DATA >= GEN_7,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = B_UPDATED_ABILITY_DATA >= GEN_7,
        .cantBeOverwritten = B_UPDATED_ABILITY_DATA >= GEN_7,
        .failsOnImposter = TRUE,
    },

    [ABILITY_VICTORY_STAR] =
    {
        .name = ES(_("Victory Star"), _("Tinovictoria")),
        .description = COMPOUND_STRING("Boosts allies' accuracy."),
        .aiRating = 6,
    },

    [ABILITY_TURBOBLAZE] =
    {
        .name = ES(_("Turboblaze"), _("Turbollama")),
        .description = COMPOUND_STRING("Moves ignore Abilities."),
        .aiRating = 7,
    },

    [ABILITY_TERAVOLT] =
    {
        .name = ES(_("Teravolt"), _("Terravoltaje")),
        .description = COMPOUND_STRING("Moves ignore Abilities."),
        .aiRating = 7,
    },

    [ABILITY_AROMA_VEIL] =
    {
        .name = ES(_("Aroma Veil"), _("Velo Aroma")),
        .description = COMPOUND_STRING("Allies can't be move-bound."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_FLOWER_VEIL] =
    {
        .name = ES(_("Flower Veil"), _("Velo Flor")),
        .description = COMPOUND_STRING("Mist for Grass-type allies."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_CHEEK_POUCH] =
    {
        .name = ES(_("Cheek Pouch"), _("Carrillo")),
        .description = COMPOUND_STRING("Eating a Berry restores HP."),
        .aiRating = 4,
    },

    [ABILITY_PROTEAN] =
    {
        .name = ES(_("Protean"), _("Mutatipo")),
        .description = COMPOUND_STRING("Changes type to used move."),
        .aiRating = 8,
    },

    [ABILITY_FUR_COAT] =
    {
        .name = ES(_("Fur Coat"), _("Pelaje Recio")),
        .description = COMPOUND_STRING("Halves physical damage."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MAGICIAN] =
    {
        .name = ES(_("Magician"), _("Prestidigitador")),
        .description = COMPOUND_STRING("Steals the foe's held item."),
        .aiRating = 3,
    },

    [ABILITY_BULLETPROOF] =
    {
        .name = ES(_("Bulletproof"), _("Antibalas")),
        .description = COMPOUND_STRING("Blocks ball and bomb moves."),
        .breakable = TRUE,
        .aiRating = 7,
    },

    [ABILITY_COMPETITIVE] =
    {
        .name = ES(_("Competitive"), _("Tenacidad")),
        .description = COMPOUND_STRING("Stat-lowering ups Sp. Atk."),
        .aiRating = 5,
    },

    [ABILITY_STRONG_JAW] =
    {
        .name = ES(_("Strong Jaw"), _("Mandíbula Fuerte")),
        .description = COMPOUND_STRING("Boosts biting moves."),
        .aiRating = 6,
    },

    [ABILITY_REFRIGERATE] =
    {
        .name = ES(_("Refrigerate"), _("Piel Helada")),
        .description = COMPOUND_STRING("Normal moves become Ice."),
        .aiRating = 8,
    },

    [ABILITY_SWEET_VEIL] =
    {
        .name = ES(_("Sweet Veil"), _("Velo Dulce")),
        .description = COMPOUND_STRING("Protects allies from sleep."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_STANCE_CHANGE] =
    {
        .name = ES(_("Stance Change"), _("Cambio Táctico")),
        .description = COMPOUND_STRING("Swaps Forme as it battles."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_GALE_WINGS] =
    {
        .name = ES(_("Gale Wings"), _("Alas Vendaval")),
        .description = COMPOUND_STRING("Flying moves have priority."),
        .aiRating = 6,
    },

    [ABILITY_MEGA_LAUNCHER] =
    {
        .name = ES(_("Mega Launcher"), _("Megadisparador")),
        .description = COMPOUND_STRING("Powers up pulse moves."),
        .aiRating = 7,
    },

    [ABILITY_GRASS_PELT] =
    {
        .name = ES(_("Grass Pelt"), _("Manto Frondoso")),
        .description = COMPOUND_STRING("Grassy Terrain ups Defense."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_SYMBIOSIS] =
    {
        .name = ES(_("Symbiosis"), _("Simbiosis")),
        .description = COMPOUND_STRING("Passes held item to ally."),
        .aiRating = 0,
    },

    [ABILITY_TOUGH_CLAWS] =
    {
        .name = ES(_("Tough Claws"), _("Garra Dura")),
        .description = COMPOUND_STRING("Powers up contact moves."),
        .aiRating = 7,
    },

    [ABILITY_PIXILATE] =
    {
        .name = ES(_("Pixilate"), _("Piel Feérica")),
        .description = COMPOUND_STRING("Normal moves become Fairy."),
        .aiRating = 8,
    },

    [ABILITY_GOOEY] =
    {
        .name = ES(_("Gooey"), _("Baba")),
        .description = COMPOUND_STRING("Contact lowers foe's Speed."),
        .aiRating = 5,
    },

    [ABILITY_AERILATE] =
    {
        .name = ES(_("Aerilate"), _("Piel Celeste")),
        .description = COMPOUND_STRING("Normal moves become Flying."),
        .aiRating = 8,
    },

    [ABILITY_PARENTAL_BOND] =
    {
        .name = ES(_("Parental Bond"), _("Amor Filial")),
        .description = COMPOUND_STRING("Parent & child each attack."),
        .aiRating = 10,
    },

    [ABILITY_DARK_AURA] =
    {
        .name = ES(_("Dark Aura"), _("Aura Oscura")),
        .description = COMPOUND_STRING("Ups all Dark-type moves."),
        .aiRating = 6,
        .breakable = B_UPDATED_ABILITY_DATA < GEN_8,
    },

    [ABILITY_FAIRY_AURA] =
    {
        .name = ES(_("Fairy Aura"), _("Aura Feérica")),
        .description = COMPOUND_STRING("Ups all Fairy-type moves."),
        .aiRating = 6,
        .breakable = B_UPDATED_ABILITY_DATA < GEN_8,
    },

    [ABILITY_AURA_BREAK] =
    {
        .name = ES(_("Aura Break"), _("Rompeaura")),
        .description = COMPOUND_STRING("Reverses Aura Abilities."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_PRIMORDIAL_SEA] =
    {
        .name = ES(_("Primordial Sea"), _("Mar del Albor")),
        .description = COMPOUND_STRING("Summons heavy rain."),
        .aiRating = 10,
    },

    [ABILITY_DESOLATE_LAND] =
    {
        .name = ES(_("Desolate Land"), _("Tierra del Ocaso")),
        .description = COMPOUND_STRING("Summons extreme sunlight."),
        .aiRating = 10,
    },

    [ABILITY_DELTA_STREAM] =
    {
        .name = ES(_("Delta Stream"), _("Ráfaga Delta")),
        .description = COMPOUND_STRING("Summons strong winds."),
        .aiRating = 10,
    },

    [ABILITY_STAMINA] =
    {
        .name = ES(_("Stamina"), _("Firmeza")),
        .description = COMPOUND_STRING("Raises Defense when hit."),
        .aiRating = 6,
    },

    [ABILITY_WIMP_OUT] =
    {
        .name = ES(_("Wimp Out"), _("Huida")),
        .description = COMPOUND_STRING("Switches out at half HP."),
        .aiRating = 3,
    },

    [ABILITY_EMERGENCY_EXIT] =
    {
        .name = ES(_("Emergency Exit"), _("Retirada")),
        .description = COMPOUND_STRING("Switches out at half HP."),
        .aiRating = 3,
    },

    [ABILITY_WATER_COMPACTION] =
    {
        .name = ES(_("Water Compaction"), _("Hidrorrefuerzo")),
        .description = COMPOUND_STRING("Ups Defense if hit by Water."),
        .aiRating = 4,
    },

    [ABILITY_MERCILESS] =
    {
        .name = ES(_("Merciless"), _("Ensañamiento")),
        .description = COMPOUND_STRING("Critical hits poisoned foes."),
        .aiRating = 4,
    },

    [ABILITY_SHIELDS_DOWN] =
    {
        .name = ES(_("Shields Down"), _("Escudo Limitado")),
        .description = COMPOUND_STRING("Shell breaks at half HP."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_STAKEOUT] =
    {
        .name = ES(_("Stakeout"), _("Vigilante")),
        .description = COMPOUND_STRING("Stronger on foe's switch in."),
        .aiRating = 6,
    },

    [ABILITY_WATER_BUBBLE] =
    {
        .name = ES(_("Water Bubble"), _("Pompa")),
        .description = COMPOUND_STRING("Guards from Fire and burns."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_STEELWORKER] =
    {
        .name = ES(_("Steelworker"), _("Acero Templado")),
        .description = COMPOUND_STRING("Ups Steel-type moves."),
        .aiRating = 6,
    },

    [ABILITY_BERSERK] =
    {
        .name = ES(_("Berserk"), _("Cólera")),
        .description = COMPOUND_STRING("Boosts Sp. Atk at half HP."),
        .aiRating = 5,
    },

    [ABILITY_SLUSH_RUSH] =
    {
        .name = ES(_("Slush Rush"), _("Quitanieves")),
        .description = COMPOUND_STRING(
        #if B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_HAIL
            "Boosts Speed in hail."),
        #elif B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_SNOW
            "Boosts Speed in snow."),
        #else
            "Ups Speed in hail or snow."),
        #endif
        .aiRating = 5,
    },

    [ABILITY_LONG_REACH] =
    {
        .name = ES(_("Long Reach"), _("Remoto")),
        .description = COMPOUND_STRING("Moves don't make contact."),
        .aiRating = 3,
    },

    [ABILITY_LIQUID_VOICE] =
    {
        .name = ES(_("Liquid Voice"), _("Voz Fluida")),
        .description = COMPOUND_STRING("Sound moves become Water."),
        .aiRating = 5,
    },

    [ABILITY_TRIAGE] =
    {
        .name = ES(_("Triage"), _("Primer Auxilio")),
        .description = COMPOUND_STRING("Healing moves have priority."),
        .aiRating = 7,
    },

    [ABILITY_GALVANIZE] =
    {
        .name = ES(_("Galvanize"), _("Piel Eléctrica")),
        .description = COMPOUND_STRING("Normal moves turn Electric."),
        .aiRating = 8,
    },

    [ABILITY_SURGE_SURFER] =
    {
        .name = ES(_("Surge Surfer"), _("Cola Surf")),
        .description = COMPOUND_STRING("Electric Terrain ups Speed."),
        .aiRating = 4,
    },

    [ABILITY_SCHOOLING] =
    {
        .name = ES(_("Schooling"), _("Banco")),
        .description = COMPOUND_STRING("Forms a school at high HP."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_DISGUISE] =
    {
        .name = ES(_("Disguise"), _("Disfraz")),
        .description = COMPOUND_STRING("Shroud protects once."),
        .aiRating = 8,
        .breakable = TRUE,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_BATTLE_BOND] =
    {
        .name = ES(_("Battle Bond"), _("Fuerte Afecto")),
        .description = COMPOUND_STRING("Changes form after a KO."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_POWER_CONSTRUCT] =
    {
        .name = ES(_("Power Construct"), _("Agrupamiento")),
        .description = COMPOUND_STRING("Changes Forme at half HP."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_CORROSION] =
    {
        .name = ES(_("Corrosion"), _("Corrosión")),
        .description = COMPOUND_STRING("Can poison Steel & Poison."),
        .aiRating = 5,
    },

    [ABILITY_COMATOSE] =
    {
        .name = ES(_("Comatose"), _("Letargo Perenne")),
        .description = COMPOUND_STRING("Always drowsing."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_QUEENLY_MAJESTY] =
    {
        .name = ES(_("Queenly Majesty"), _("Regia Presencia")),
        .description = COMPOUND_STRING("Allies block priority moves."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_INNARDS_OUT] =
    {
        .name = ES(_("Innards Out"), _("Revés")),
        .description = COMPOUND_STRING("Damages the foe if KO'd."),
        .aiRating = 5,
    },

    [ABILITY_DANCER] =
    {
        .name = ES(_("Dancer"), _("Pareja de Baile")),
        .description = COMPOUND_STRING("Dances along with others."),
        .aiRating = 5,
    },

    [ABILITY_BATTERY] =
    {
        .name = ES(_("Battery"), _("Batería")),
        .description = COMPOUND_STRING("Boosts ally's Sp. Atk."),
        .aiRating = 0,
    },

    [ABILITY_FLUFFY] =
    {
        .name = ES(_("Fluffy"), _("Peluche")),
        .description = COMPOUND_STRING("Halves contact, heat hurts."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_DAZZLING] =
    {
        .name = ES(_("Dazzling"), _("Cuerpo Vívido")),
        .description = COMPOUND_STRING("Allies block priority moves."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SOUL_HEART] =
    {
        .name = ES(_("Soul-Heart"), _("Coránima")),
        .description = COMPOUND_STRING("Others fainting ups Sp. Atk."),
        .aiRating = 7,
    },

    [ABILITY_TANGLING_HAIR] =
    {
        .name = ES(_("Tangling Hair"), _("Rizos Rebeldes")),
        .description = COMPOUND_STRING("Contact lowers foe's Speed."),
        .aiRating = 5,
    },

    [ABILITY_RECEIVER] =
    {
        .name = ES(_("Receiver"), _("Receptor")),
        .description = COMPOUND_STRING("Copies fainted ally Ability."),
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POWER_OF_ALCHEMY] =
    {
        .name = ES(_("Power Of Alchemy"), _("Reacción Química")),
        .description = COMPOUND_STRING("Copies fainted ally Ability."),
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_BEAST_BOOST] =
    {
        .name = ES(_("Beast Boost"), _("Ultraimpulso")),
        .description = COMPOUND_STRING("Raises best stat after KOs."),
        .aiRating = 7,
    },

    [ABILITY_RKS_SYSTEM] =
    {
        .name = ES(_("RKS System"), _("Sistema Alfa")),
        .description = COMPOUND_STRING("Matches held memory's type."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_ELECTRIC_SURGE] =
    {
        .name = ES(_("Electric Surge"), _("Electrogénesis")),
        .description = COMPOUND_STRING("Makes the field electrified."),
        .aiRating = 8,
    },

    [ABILITY_PSYCHIC_SURGE] =
    {
        .name = ES(_("Psychic Surge"), _("Psicogénesis")),
        .description = COMPOUND_STRING("Makes the field weird."),
        .aiRating = 8,
    },

    [ABILITY_MISTY_SURGE] =
    {
        .name = ES(_("Misty Surge"), _("Nebulogénesis")),
        .description = COMPOUND_STRING("Makes the field misty."),
        .aiRating = 8,
    },

    [ABILITY_GRASSY_SURGE] =
    {
        .name = ES(_("Grassy Surge"), _("Herbogénesis")),
        .description = COMPOUND_STRING("Makes the field grassy."),
        .aiRating = 8,
    },

    [ABILITY_FULL_METAL_BODY] =
    {
        .name = ES(_("Full Metal Body"), _("Guardia Metálica")),
        .description = COMPOUND_STRING("Stats can't be lowered."),
        .aiRating = 4,
    },

    [ABILITY_SHADOW_SHIELD] =
    {
        .name = ES(_("Shadow Shield"), _("Guardia Espectro")),
        .description = COMPOUND_STRING("Reduces damage at full HP."),
        .aiRating = 8,
    },

    [ABILITY_PRISM_ARMOR] =
    {
        .name = ES(_("Prism Armor"), _("Armadura Prisma")),
        .description = COMPOUND_STRING("Weakens “supereffective”."),
        .aiRating = 6,
    },

    [ABILITY_NEUROFORCE] =
    {
        .name = ES(_("Neuroforce"), _("Fuerza Cerebral")),
        .description = COMPOUND_STRING("Ups “supereffective” hits."),
        .aiRating = 6,
    },

    [ABILITY_INTREPID_SWORD] =
    {
        .name = ES(_("Intrepid Sword"), _("Espada Indómita")),
        .description = COMPOUND_STRING(
        #if B_INTREPID_SWORD >= GEN_9
            "Ups Attack on entry once."),
        #else
            "Raises Attack on entry."),
        #endif
        .aiRating = 3,
    },

    [ABILITY_DAUNTLESS_SHIELD] =
    {
        .name = ES(_("Dauntless Shield"), _("Escudo Recio")),
        .description = COMPOUND_STRING(
        #if B_DAUNTLESS_SHIELD >= GEN_9
            "Ups Defense on entry once."),
        #else
            "Raises Defense on entry."),
        #endif
        .aiRating = 3,
    },

    [ABILITY_LIBERO] =
    {
        .name = ES(_("Libero"), _("Líbero")),
        .description = COMPOUND_STRING("Changes type to used move."),
    },

    [ABILITY_BALL_FETCH] =
    {
        .name = ES(_("Ball Fetch"), _("Recogebolas")),
        .description = COMPOUND_STRING("Fetches first failed Ball."),
        .aiRating = 0,
    },

    [ABILITY_COTTON_DOWN] =
    {
        .name = ES(_("Cotton Down"), _("Pelusa")),
        .description = COMPOUND_STRING("Lowers others' Speed if hit."),
        .aiRating = 3,
    },

    [ABILITY_PROPELLER_TAIL] =
    {
        .name = ES(_("Propeller Tail"), _("Hélice Caudal")),
        .description = COMPOUND_STRING("Ignores foes' move-drawing."),
        .aiRating = 2,
    },

    [ABILITY_MIRROR_ARMOR] =
    {
        .name = ES(_("Mirror Armor"), _("Coraza Reflejo")),
        .description = COMPOUND_STRING("Bounces stat-lowering."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_GULP_MISSILE] =
    {
        .name = ES(_("Gulp Missile"), _("Tragamisil")),
        .description = COMPOUND_STRING("Spits when hit after Dive."),
        .aiRating = 3,
        .cantBeSwapped = B_UPDATED_ABILITY_DATA < GEN_9,
        .cantBeCopied = B_UPDATED_ABILITY_DATA < GEN_9,
        .cantBeTraced = B_UPDATED_ABILITY_DATA < GEN_9,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_STALWART] =
    {
        .name = ES(_("Stalwart"), _("Acérrimo")),
        .description = COMPOUND_STRING("Ignores foes' move-drawing."),
        .aiRating = 2,
    },

    [ABILITY_STEAM_ENGINE] =
    {
        .name = ES(_("Steam Engine"), _("Combustible")),
        .description = COMPOUND_STRING("Fire & Water hits up Speed."),
        .aiRating = 3,
    },

    [ABILITY_PUNK_ROCK] =
    {
        .name = _("Punk Rock"),
        .description = COMPOUND_STRING("Boosts and resists sound."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_SAND_SPIT] =
    {
        .name = ES(_("Sand Spit"), _("Expulsarena")),
        .description = COMPOUND_STRING("Summons a sandstorm if hit."),
        .aiRating = 5,
    },

    [ABILITY_ICE_SCALES] =
    {
        .name = ES(_("Ice Scales"), _("Escama de Hielo")),
        .description = COMPOUND_STRING("Halves special damage."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_RIPEN] =
    {
        .name = ES(_("Ripen"), _("Maduración")),
        .description = COMPOUND_STRING("Doubles Berry effects."),
        .aiRating = 4,
    },

    [ABILITY_ICE_FACE] =
    {
        .name = ES(_("Ice Face"), _("Cara de Hielo")),
        .description = COMPOUND_STRING(
        #if B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_HAIL
            "Hail renews one free hit."),
        #elif B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_SNOW
            "Snow renews one free hit."),
        #else
            "Hail & snow renew free hit."),
        #endif
        .aiRating = 4,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .breakable = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_POWER_SPOT] =
    {
        .name = ES(_("Power Spot"), _("Fuente Energía")),
        .description = COMPOUND_STRING("Powers up ally's moves."),
        .aiRating = 2,
    },

    [ABILITY_MIMICRY] =
    {
        .name = ES(_("Mimicry"), _("Mimetismo")),
        .description = COMPOUND_STRING("Changes type on terrain."),
        .aiRating = 2,
    },

    [ABILITY_SCREEN_CLEANER] =
    {
        .name = ES(_("Screen Cleaner"), _("Antibarrera")),
        .description = COMPOUND_STRING("Nullifies barriers on entry."),
        .aiRating = 3,
    },

    [ABILITY_STEELY_SPIRIT] =
    {
        .name = ES(_("Steely Spirit"), _("Alma Acerada")),
        .description = COMPOUND_STRING("Ups allies' Steel moves."),
        .aiRating = 2,
    },

    [ABILITY_PERISH_BODY] =
    {
        .name = ES(_("Perish Body"), _("Cuerpo Mortal")),
        .description = COMPOUND_STRING("Foe faints in 3 turns if hit."),
        .aiRating = -1,
    },

    [ABILITY_WANDERING_SPIRIT] =
    {
        .name = ES(_("Wandering Spirit"), _("Alma Errante")),
        .description = COMPOUND_STRING("Swaps Abilities on contact."),
        .aiRating = 2,
    },

    [ABILITY_GORILLA_TACTICS] =
    {
        .name = ES(_("Gorilla Tactics"), _("Monotema")),
        .description = COMPOUND_STRING("Ups Attack and locks move."),
        .aiRating = 4,
    },

    [ABILITY_NEUTRALIZING_GAS] =
    {
        .name = ES(_("Neutralizing Gas"), _("Gas Reactivo")),
        .description = COMPOUND_STRING("Nullifies others' Abilities."),
        .aiRating = 5,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_PASTEL_VEIL] =
    {
        .name = ES(_("Pastel Veil"), _("Velo Pastel")),
        .description = COMPOUND_STRING("Allies can't be poisoned."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_HUNGER_SWITCH] =
    {
        .name = ES(_("Hunger Switch"), _("Mutapetito")),
        .description = COMPOUND_STRING("Changes form every turn."),
        .aiRating = 2,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_QUICK_DRAW] =
    {
        .name = ES(_("Quick Draw"), _("Mano Rápida")),
        .description = COMPOUND_STRING("Occasionally moves first."),
        .aiRating = 4,
    },

    [ABILITY_UNSEEN_FIST] =
    {
        .name = ES(_("Unseen Fist"), _("Puño Invisible")),
        .description = COMPOUND_STRING("Contact evades protection."),
        .aiRating = 6,
    },

    [ABILITY_CURIOUS_MEDICINE] =
    {
        .name = ES(_("Curious Medicine"), _("Medicina Extraña")),
        .description = COMPOUND_STRING("Removes ally stat changes."),
        .aiRating = 3,
    },

    [ABILITY_TRANSISTOR] =
    {
        .name = _("Transistor"),
        .description = COMPOUND_STRING("Ups Electric-type moves."),
        .aiRating = 6,
    },

    [ABILITY_DRAGONS_MAW] =
    {
        .name = ES(_("Dragon's Maw"), _("Mandíbula Dragón")),
        .description = COMPOUND_STRING("Ups Dragon-type moves."),
        .aiRating = 6,
    },

    [ABILITY_CHILLING_NEIGH] =
    {
        .name = ES(_("Chilling Neigh"), _("Relincho Blanco")),
        .description = COMPOUND_STRING("Raises Attack after KOs."),
        .aiRating = 7,
    },

    [ABILITY_GRIM_NEIGH] =
    {
        .name = ES(_("Grim Neigh"), _("Relincho Negro")),
        .description = COMPOUND_STRING("Raises Sp. Atk after KOs."),
        .aiRating = 7,
    },

    [ABILITY_AS_ONE_ICE_RIDER] =
    {
        .name = ES(_("As One"), _("Unidad Ecuestre")),
        .description = COMPOUND_STRING("Unnerve and Chilling Neigh."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_AS_ONE_SHADOW_RIDER] =
    {
        .name = ES(_("As One"), _("Unidad Ecuestre")),
        .description = COMPOUND_STRING("Unnerve and Grim Neigh."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_LINGERING_AROMA] =
    {
        .name = ES(_("Lingering Aroma"), _("Olor Persistente")),
        .description = COMPOUND_STRING("Ability spreads on contact."),
        .aiRating = 5,
    },

    [ABILITY_SEED_SOWER] =
    {
        .name = ES(_("Seed Sower"), _("Disemillar")),
        .description = COMPOUND_STRING("Makes field grassy if hit."),
        .aiRating = 5,
    },

    [ABILITY_THERMAL_EXCHANGE] =
    {
        .name = ES(_("Thermal Exchange"), _("Termoconversión")),
        .description = COMPOUND_STRING("Ups Attack if hit by Fire."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANGER_SHELL] =
    {
        .name = ES(_("Anger Shell"), _("Coraza Ira")),
        .description = COMPOUND_STRING("Changes stats at half HP."),
        .aiRating = 3,
    },

    [ABILITY_PURIFYING_SALT] =
    {
        .name = ES(_("Purifying Salt"), _("Sal Purificadora")),
        .description = COMPOUND_STRING("Guards from status & Ghost."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_WELL_BAKED_BODY] =
    {
        .name = ES(_("Well-Baked Body"), _("Cuerpo Horneado")),
        .description = COMPOUND_STRING("Ups Defense if hit by Fire."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_WIND_RIDER] =
    {
        .name = ES(_("Wind Rider"), _("Surcavientos")),
        .description = COMPOUND_STRING("Wind moves raise Attack."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_GUARD_DOG] =
    {
        .name = ES(_("Guard Dog"), _("Perro Guardián")),
        .description = COMPOUND_STRING("Raises Atk if intimidated."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ROCKY_PAYLOAD] =
    {
        .name = ES(_("Rocky Payload"), _("Transportarrocas")),
        .description = COMPOUND_STRING("Powers up Rock-type moves."),
        .aiRating = 6,
    },

    [ABILITY_WIND_POWER] =
    {
        .name = ES(_("Wind Power"), _("Energía Eólica")),
        .description = COMPOUND_STRING("Gets charged if hit by wind."),
        .aiRating = 4,
    },

    [ABILITY_ZERO_TO_HERO] =
    {
        .name = ES(_("Zero to Hero"), _("Cambio Heroico")),
        .description = COMPOUND_STRING("Changes form upon switch."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_COMMANDER] =
    {
        .name = ES(_("Commander"), _("Comandar")),
        .description = COMPOUND_STRING("Commands from ally Dondozo."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_ELECTROMORPHOSIS] =
    {
        .name = ES(_("Electromorphosis"), _("Dinamo")),
        .description = COMPOUND_STRING("Becomes charged when hit."),
        .aiRating = 5,
    },

    [ABILITY_PROTOSYNTHESIS] =
    {
        .name = ES(_("Protosynthesis"), _("Paleosíntesis")),
        .description = COMPOUND_STRING("Sunlight boosts best stat."),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_QUARK_DRIVE] =
    {
        .name = ES(_("Quark Drive"), _("Carga Cuark")),
        .description = COMPOUND_STRING("Electr. field ups best stat."),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_GOOD_AS_GOLD] =
    {
        .name = ES(_("Good as Gold"), _("Cuerpo Áureo")),
        .description = COMPOUND_STRING("Immunity to status moves."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_VESSEL_OF_RUIN] =
    {
        .name = ES(_("Vessel of Ruin"), _("Caldero Debacle")),
        .description = COMPOUND_STRING("Reduces others' Sp. Atk."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SWORD_OF_RUIN] =
    {
        .name = ES(_("Sword of Ruin"), _("Espada Debacle")),
        .description = COMPOUND_STRING("Reduces others' Defense."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_TABLETS_OF_RUIN] =
    {
        .name = ES(_("Tablets of Ruin"), _("Tablilla Debacle")),
        .description = COMPOUND_STRING("Reduces others' Attack."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_BEADS_OF_RUIN] =
    {
        .name = ES(_("Beads of Ruin"), _("Abalorio Debacle")),
        .description = COMPOUND_STRING("Reduces others' Sp. Def."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ORICHALCUM_PULSE] =
    {
        .name = ES(_("Orichalcum Pulse"), _("Latido Oricalco")),
        .description = COMPOUND_STRING("Summons sun and ups Atk."),
        .aiRating = 8,
    },

    [ABILITY_HADRON_ENGINE] =
    {
        .name = ES(_("Hadron Engine"), _("Motor Hadrónico")),
        .description = COMPOUND_STRING("Electr. Surge & ups Sp. Atk."),
        .aiRating = 8,
    },

    [ABILITY_OPPORTUNIST] =
    {
        .name = ES(_("Opportunist"), _("Oportunista")),
        .description = COMPOUND_STRING("Copies a foe's stat boost."),
        .aiRating = 5,
    },

    [ABILITY_CUD_CHEW] =
    {
        .name = ES(_("Cud Chew"), _("Rumia")),
        .description = COMPOUND_STRING("Eats Berry again next turn."),
        .aiRating = 4,
    },

    [ABILITY_SHARPNESS] =
    {
        .name = ES(_("Sharpness"), _("Cortante")),
        .description = COMPOUND_STRING("Powers up slicing moves."),
        .aiRating = 7,
    },

    [ABILITY_SUPREME_OVERLORD] =
    {
        .name = ES(_("Supreme Overlord"), _("General Supremo")),
        .description = COMPOUND_STRING("Fainted partners up power."),
        .aiRating = 6,
    },

    [ABILITY_COSTAR] =
    {
        .name = ES(_("Costar"), _("Unísono")),
        .description = COMPOUND_STRING("Copies ally's stat changes."),
        .aiRating = 5,
    },

    [ABILITY_TOXIC_DEBRIS] =
    {
        .name = ES(_("Toxic Debris"), _("Capa Tóxica")),
        .description = COMPOUND_STRING("Lays poison spikes if hit."),
        .aiRating = 4,
    },

    [ABILITY_ARMOR_TAIL] =
    {
        .name = ES(_("Armor Tail"), _("Cola Armadura")),
        .description = COMPOUND_STRING("Allies block priority moves."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_EARTH_EATER] =
    {
        .name = ES(_("Earth Eater"), _("Geofagia")),
        .description = COMPOUND_STRING("Restores if hit by Ground."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MYCELIUM_MIGHT] =
    {
        .name = ES(_("Mycelium Might"), _("Poder Fúngico")),
        .description = COMPOUND_STRING("Status moves can't fail."),
        .aiRating = 2,
    },

    [ABILITY_HOSPITALITY] =
    {
        .name = ES(_("Hospitality"), _("Hospitalidad")),
        .description = COMPOUND_STRING("Restores ally's HP on entry."),
        .aiRating = 5,
    },

    [ABILITY_MINDS_EYE] =
    {
        .name = ES(_("Mind's Eye"), _("Ojo Mental")),
        .description = COMPOUND_STRING("Grants Foresight."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_TEAL_MASK] =
    {
        .name = ES(_("Embody Aspect"), _("Evocarrecuerdos")),
        .description = COMPOUND_STRING("Terastal raises Speed."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_HEARTHFLAME_MASK] =
    {
        .name = ES(_("Embody Aspect"), _("Evocarrecuerdos")),
        .description = COMPOUND_STRING("Terastal raises Attack."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_WELLSPRING_MASK] =
    {
        .name = ES(_("Embody Aspect"), _("Evocarrecuerdos")),
        .description = COMPOUND_STRING("Terastal raises Sp. Def."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_CORNERSTONE_MASK] =
    {
        .name = ES(_("Embody Aspect"), _("Evocarrecuerdos")),
        .description = COMPOUND_STRING("Terastal raises Defense."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_TOXIC_CHAIN] =
    {
        .name = ES(_("Toxic Chain"), _("Cadena Tóxica")),
        .description = COMPOUND_STRING("Attacks may badly poison."),
        .aiRating = 8,
    },

    [ABILITY_SUPERSWEET_SYRUP] =
    {
        .name = ES(_("Supersweet Syrup"), _("Néctar Dulce")),
        .description = COMPOUND_STRING("Lowers foes' evasion once."),
        .aiRating = 5,
    },

    [ABILITY_TERA_SHIFT] =
    {
        .name = ES(_("Tera Shift"), _("Teracambio")),
        .description = COMPOUND_STRING("Changes form on entry."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_TERA_SHELL] =
    {
        .name = ES(_("Tera Shell"), _("Teracaparazón")),
        .description = COMPOUND_STRING("Resists all types at full HP."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_TERAFORM_ZERO] =
    {
        .name = ES(_("Teraform Zero"), _("Teraformación 0")),
        .description = COMPOUND_STRING("Zeroes weather and terrain."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POISON_PUPPETEER] =
    {
        .name = ES(_("Poison Puppeteer"), _("Títere Tóxico")),
        .description = COMPOUND_STRING("Poisoning also confuses."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_PIERCING_DRILL] =
    {
        .name = ES(_("Piercing Drill"), _("Turbotaladro")),
        .description = COMPOUND_STRING("Contact evades protection."),
    },

    [ABILITY_DRAGONIZE] =
    {
        .name = ES(_("Dragonize"), _("Piel Dragontina")),
        .description = COMPOUND_STRING("Normal moves turn Dragon."),
    },

    [ABILITY_EELEVATE] =
    {
        .name = ES(_("Eelevate"), _("Anguilevitación")),
        .description = COMPOUND_STRING("Levitate and Beast Boost."),
    },

    [ABILITY_314] =
    {
        .name = _("-------"),
        .description = COMPOUND_STRING("No special ability."),
    },

    [ABILITY_MEGA_SOL] =
    {
        .name = ES(_("Mega Sol"), _("Megasolar")),
        .description = COMPOUND_STRING("Acts like under sun."),
    },

    [ABILITY_FIRE_MANE] =
    {
        .name = ES(_("Fire Mane"), _("Melena Ígnea")),
        .description = COMPOUND_STRING("Ups Fire-type moves."),
    },

    [ABILITY_317] =
    {
        .name = _("-------"),
        .description = COMPOUND_STRING("No special ability."),
    },

    [ABILITY_SPICY_SPRAY] =
    {
        .name = ES(_("Spicy Spray"), _("Salpicante")),
        .description = COMPOUND_STRING("Burns the foe when damaged."),
    },

    [ABILITY_AURA_GUARD] =
    {
        .name = ES(_("Aura Guard"), _("Guardia Aura")),
        .description = COMPOUND_STRING("Unimplemented."),
    },
};
