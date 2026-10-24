const struct AbilityInfo gAbilitiesInfo[ABILITIES_COUNT] =
{
    [ABILITY_NONE] =
    {
        .name = _("-------"),
        .description = ES(COMPOUND_STRING("No Ability."), COMPOUND_STRING("Sin habilidad.")),
        .aiRating = 0,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_STENCH] =
    {
        .name = ES(_("Stench"), _("Hedor")),
        .description = ES(COMPOUND_STRING("Moves may cause flinching."), COMPOUND_STRING("Puede amedrentar al atacar.")),
        .aiRating = 1,
    },

    [ABILITY_DRIZZLE] =
    {
        .name = ES(_("Drizzle"), _("Llovizna")),
        .description = ES(COMPOUND_STRING("Summons rain in battle."), COMPOUND_STRING("Hace que llueva.")),
        .aiRating = 9,
    },

    [ABILITY_SPEED_BOOST] =
    {
        .name = ES(_("Speed Boost"), _("Impulso")),
        .description = ES(COMPOUND_STRING("Speed raises every turn."), COMPOUND_STRING("Sube la Velocidad cada turno.")),
        .aiRating = 9,
    },

    [ABILITY_BATTLE_ARMOR] =
    {
        .name = ES(_("Battle Armor"), _("Armadura Batalla")),
        .description = ES(COMPOUND_STRING("Blocks critical hits."), COMPOUND_STRING("Bloquea los golpes críticos.")),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_STURDY] =
    {
        .name = ES(_("Sturdy"), _("Robustez")),
        .description = ES(COMPOUND_STRING("Negates 1-hit KO attacks."), COMPOUND_STRING("Anula los KO de un golpe.")),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DAMP] =
    {
        .name = ES(_("Damp"), _("Humedad")),
        .description = ES(COMPOUND_STRING("Prevents self-destruction."), COMPOUND_STRING("Impide autodestruirse.")),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_LIMBER] =
    {
        .name = ES(_("Limber"), _("Flexibilidad")),
        .description = ES(COMPOUND_STRING("Prevents paralysis."), COMPOUND_STRING("Evita ser paralizado.")),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SAND_VEIL] =
    {
        .name = ES(_("Sand Veil"), _("Velo Arena")),
        .description = ES(COMPOUND_STRING("Ups evasion in a sandstorm."), COMPOUND_STRING("Más evasión con arena.")),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_STATIC] =
    {
        .name = ES(_("Static"), _("Elec. Estática")),
        .description = ES(COMPOUND_STRING("May paralyze on contact."), COMPOUND_STRING("Puede paralizar al tocarlo.")),
        .aiRating = 4,
    },

    [ABILITY_VOLT_ABSORB] =
    {
        .name = ES(_("Volt Absorb"), _("Absorbe Elec.")),
        .description = ES(COMPOUND_STRING("Restores if hit by Electric."), COMPOUND_STRING("Lo Eléctrico le cura PS.")),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_WATER_ABSORB] =
    {
        .name = ES(_("Water Absorb"), _("Absorbe Agua")),
        .description = ES(COMPOUND_STRING("Restores HP if hit by Water."), COMPOUND_STRING("Cura si le da un mov. Agua.")),
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
        .description = ES(COMPOUND_STRING("Negates weather effects."), COMPOUND_STRING("Anula los efectos del tiempo.")),
        .aiRating = 5,
    },

    [ABILITY_COMPOUND_EYES] =
    {
        .name = ES(_("Compound Eyes"), _("Ojo Compuesto")),
        .description = ES(COMPOUND_STRING("Boosts accuracy."), COMPOUND_STRING("Sube la precisión.")),
        .aiRating = 7,
    },

    [ABILITY_INSOMNIA] =
    {
        .name = ES(_("Insomnia"), _("Insomnio")),
        .description = ES(COMPOUND_STRING("Prevents sleep."), COMPOUND_STRING("Evita el quedarse dormido.")),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_COLOR_CHANGE] =
    {
        .name = ES(_("Color Change"), _("Cambio Color")),
        .description = ES(COMPOUND_STRING("Changes type to foe's move."), COMPOUND_STRING("Toma el tipo del ataque rival.")),
        .aiRating = 2,
    },

    [ABILITY_IMMUNITY] =
    {
        .name = ES(_("Immunity"), _("Inmunidad")),
        .description = ES(COMPOUND_STRING("Prevents poisoning."), COMPOUND_STRING("Evita el envenenamiento.")),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_FLASH_FIRE] =
    {
        .name = ES(_("Flash Fire"), _("Absorbe Fuego")),
        .description = ES(COMPOUND_STRING("Powers up Fire if hit by it."), COMPOUND_STRING("El fuego potencia su Fuego.")),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SHIELD_DUST] =
    {
        .name = ES(_("Shield Dust"), _("Polvo Escudo")),
        .description = ES(COMPOUND_STRING("Blocks foes' added effects."), COMPOUND_STRING("Bloquea efectos secundarios.")),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_OWN_TEMPO] =
    {
        .name = ES(_("Own Tempo"), _("Ritmo Propio")),
        .description = ES(COMPOUND_STRING("Prevents confusion."), COMPOUND_STRING("Evita ser confundido.")),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SUCTION_CUPS] =
    {
        .name = ES(_("Suction Cups"), _("Ventosas")),
        .description = ES(COMPOUND_STRING("Can't be forced to switch."), COMPOUND_STRING("No pueden obligarle a cambiar.")),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_INTIMIDATE] =
    {
        .name = ES(_("Intimidate"), _("Intimidación")),
        .description = ES(COMPOUND_STRING("Lowers foes' Atk on entry."), COMPOUND_STRING("Baja el Ataque del rival.")),
        .aiRating = 7,
    },

    [ABILITY_SHADOW_TAG] =
    {
        .name = ES(_("Shadow Tag"), _("Sombra Trampa")),
        .description = ES(COMPOUND_STRING("Prevents the foes' escape."), COMPOUND_STRING("Evita que el enemigo huya.")),
        .aiRating = 10,
    },

    [ABILITY_ROUGH_SKIN] =
    {
        .name = ES(_("Rough Skin"), _("Piel Tosca")),
        .description = ES(COMPOUND_STRING("Damages foe on contact."), COMPOUND_STRING("Hiere al hacer contacto.")),
        .aiRating = 6,
    },

    [ABILITY_WONDER_GUARD] =
    {
        .name = ES(_("Wonder Guard"), _("Superguarda")),
        .description = ES(COMPOUND_STRING("Only “supereffective” hits."), COMPOUND_STRING("Solo le dañan supereficaces.")),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_LEVITATE] =
    {
        .name = ES(_("Levitate"), _("Levitación")),
        .description = ES(COMPOUND_STRING("Not hit by Ground attacks."), COMPOUND_STRING("Inmune a mov. Tierra.")),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_EFFECT_SPORE] =
    {
        .name = ES(_("Effect Spore"), _("Efecto Espora")),
        .description = ES(COMPOUND_STRING("Contact may psn/slp/par."), COMPOUND_STRING("Al tocarlo: ven./sueño/par.")),
        .aiRating = 4,
    },

    [ABILITY_SYNCHRONIZE] =
    {
        .name = ES(_("Synchronize"), _("Sincronía")),
        .description = ES(COMPOUND_STRING("Passes on brn/par/psn."), COMPOUND_STRING("Contagia quem./par./ven.")),
        .aiRating = 4,
    },

    [ABILITY_CLEAR_BODY] =
    {
        .name = ES(_("Clear Body"), _("Cuerpo Puro")),
        .description = ES(COMPOUND_STRING("Stats can't be lowered."), COMPOUND_STRING("No le bajan características.")),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_NATURAL_CURE] =
    {
        .name = ES(_("Natural Cure"), _("Cura Natural")),
        .description = ES(COMPOUND_STRING("Heals status upon switch."), COMPOUND_STRING("Se cura el estado al cambiar.")),
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
        .description = ES(COMPOUND_STRING("Promotes added effects."), COMPOUND_STRING("Más efectos secundarios.")),
        .aiRating = 8,
    },

    [ABILITY_SWIFT_SWIM] =
    {
        .name = ES(_("Swift Swim"), _("Nado Rápido")),
        .description = ES(COMPOUND_STRING("Boosts Speed in rain."), COMPOUND_STRING("Más Velocidad con lluvia.")),
        .aiRating = 6,
    },

    [ABILITY_CHLOROPHYLL] =
    {
        .name = ES(_("Chlorophyll"), _("Clorofila")),
        .description = ES(COMPOUND_STRING("Boosts Speed in sunlight."), COMPOUND_STRING("Más Velocidad con sol.")),
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
        .description = ES(COMPOUND_STRING("Copies a foe's Ability."), COMPOUND_STRING("Copia la habilidad rival.")),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE, //B_UPDATED_ABILITY_DATA >= GEN_4
    },

    [ABILITY_HUGE_POWER] =
    {
        .name = ES(_("Huge Power"), _("Potencia")),
        .description = ES(COMPOUND_STRING("Doubles Attack."), COMPOUND_STRING("Aumenta el Ataque.")),
        .aiRating = 10,
    },

    [ABILITY_POISON_POINT] =
    {
        .name = ES(_("Poison Point"), _("Punto Tóxico")),
        .description = ES(COMPOUND_STRING("May poison foe on contact."), COMPOUND_STRING("Puede envenenar al tocarlo.")),
        .aiRating = 4,
    },

    [ABILITY_INNER_FOCUS] =
    {
        .name = ES(_("Inner Focus"), _("Fuerza Mental")),
        .description = ES(COMPOUND_STRING("Prevents flinching."), COMPOUND_STRING("Evita el retroceso.")),
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
        .description = ES(COMPOUND_STRING("Prevents burns."), COMPOUND_STRING("Evita las quemaduras.")),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_MAGNET_PULL] =
    {
        .name = ES(_("Magnet Pull"), _("Imán")),
        .description = ES(COMPOUND_STRING("Traps Steel-type foes."), COMPOUND_STRING("Atrapa a rivales Acero.")),
        .aiRating = 9,
    },

    [ABILITY_SOUNDPROOF] =
    {
        .name = ES(_("Soundproof"), _("Insonorizar")),
        .description = ES(COMPOUND_STRING("Avoids sound-based moves."), COMPOUND_STRING("Evita ataques de sonido.")),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_RAIN_DISH] =
    {
        .name = ES(_("Rain Dish"), _("Cura Lluvia")),
        .description = ES(COMPOUND_STRING("Slight HP recovery in rain."), COMPOUND_STRING("Recupera PS con lluvia.")),
        .aiRating = 3,
    },

    [ABILITY_SAND_STREAM] =
    {
        .name = ES(_("Sand Stream"), _("Chorro Arena")),
        .description = ES(COMPOUND_STRING("Summons a sandstorm."), COMPOUND_STRING("Crea una tormenta de arena.")),
        .aiRating = 9,
    },

    [ABILITY_PRESSURE] =
    {
        .name = ES(_("Pressure"), _("Presión")),
        .description = ES(COMPOUND_STRING("Raises foe's PP usage."), COMPOUND_STRING("El rival gasta más PP.")),
        .aiRating = 5,
    },

    [ABILITY_THICK_FAT] =
    {
        .name = ES(_("Thick Fat"), _("Sebo")),
        .description = ES(COMPOUND_STRING("Halves Fire and Ice damage."), COMPOUND_STRING("Mitad de daño Fuego y Hielo.")),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_EARLY_BIRD] =
    {
        .name = ES(_("Early Bird"), _("Madrugar")),
        .description = ES(COMPOUND_STRING("Awakens twice as fast."), COMPOUND_STRING("Se despierta antes.")),
        .aiRating = 4,
    },

    [ABILITY_FLAME_BODY] =
    {
        .name = ES(_("Flame Body"), _("Cuerpo Llama")),
        .description = ES(COMPOUND_STRING("May burn foe on contact."), COMPOUND_STRING("Puede quemar al tocarlo.")),
        .aiRating = 4,
    },

    [ABILITY_RUN_AWAY] =
    {
        .name = ES(_("Run Away"), _("Fuga")),
        .description = ES(COMPOUND_STRING("Enables a sure getaway."), COMPOUND_STRING("Siempre puede huir.")),
        .aiRating = 0,
    },

    [ABILITY_KEEN_EYE] =
    {
        .name = ES(_("Keen Eye"), _("Vista Lince")),
        .description = ES(COMPOUND_STRING("Accuracy can't be lowered."), COMPOUND_STRING("No le baja la precisión.")),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_HYPER_CUTTER] =
    {
        .name = ES(_("Hyper Cutter"), _("Corte Fuerte")),
        .description = ES(COMPOUND_STRING("Attack can't be lowered."), COMPOUND_STRING("No le baja el Ataque.")),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_PICKUP] =
    {
        .name = ES(_("Pickup"), _("Recogida")),
        .description = ES(COMPOUND_STRING("May pick up items."), COMPOUND_STRING("Puede recoger objetos.")),
        .aiRating = 1,
    },

    [ABILITY_TRUANT] =
    {
        .name = ES(_("Truant"), _("Ausente")),
        .description = ES(COMPOUND_STRING("Moves only every two turns."), COMPOUND_STRING("Ataca solo un turno de cada 2.")),
        .aiRating = -2,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_HUSTLE] =
    {
        .name = ES(_("Hustle"), _("Entusiasmo")),
        .description = ES(COMPOUND_STRING("Trades accuracy for power."), COMPOUND_STRING("Más Ataque, menos precisión.")),
        .aiRating = 7,
    },

    [ABILITY_CUTE_CHARM] =
    {
        .name = ES(_("Cute Charm"), _("Gran Encanto")),
        .description = ES(COMPOUND_STRING("May infatuate on contact."), COMPOUND_STRING("Puede enamorar al tocarlo.")),
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
        .description = ES(COMPOUND_STRING("Changes with the weather."), COMPOUND_STRING("Cambia con el tiempo.")),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = B_UPDATED_ABILITY_DATA >= GEN_4,
        .failsOnImposter = B_UPDATED_ABILITY_DATA >= GEN_5,
    },

    [ABILITY_STICKY_HOLD] =
    {
        .name = ES(_("Sticky Hold"), _("Viscosidad")),
        .description = ES(COMPOUND_STRING("Held item can't be removed."), COMPOUND_STRING("No le quitan el objeto.")),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SHED_SKIN] =
    {
        .name = ES(_("Shed Skin"), _("Mudar")),
        .description = ES(COMPOUND_STRING("May heal status problems."), COMPOUND_STRING("Puede curarse el estado.")),
        .aiRating = 7,
    },

    [ABILITY_GUTS] =
    {
        .name = ES(_("Guts"), _("Agallas")),
        .description = ES(COMPOUND_STRING("Boosts Attack if statused."), COMPOUND_STRING("Más Ataque si tiene estado.")),
        .aiRating = 6,
    },

    [ABILITY_MARVEL_SCALE] =
    {
        .name = ES(_("Marvel Scale"), _("Escama Especial")),
        .description = ES(COMPOUND_STRING("Ups Defense if statused."), COMPOUND_STRING("Más Defensa si tiene estado.")),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_LIQUID_OOZE] =
    {
        .name = ES(_("Liquid Ooze"), _("Lodo Líquido")),
        .description = ES(COMPOUND_STRING("Damages HP-draining foes."), COMPOUND_STRING("Daña a quien le absorbe PS.")),
        .aiRating = 3,
    },

    [ABILITY_OVERGROW] =
    {
        .name = ES(_("Overgrow"), _("Espesura")),
        .description = ES(COMPOUND_STRING("Ups Grass moves at low HP."), COMPOUND_STRING("Potencia Planta con pocos PS.")),
        .aiRating = 5,
    },

    [ABILITY_BLAZE] =
    {
        .name = ES(_("Blaze"), _("Mar Llamas")),
        .description = ES(COMPOUND_STRING("Ups Fire moves at low HP."), COMPOUND_STRING("Potencia Fuego con pocos PS.")),
        .aiRating = 5,
    },

    [ABILITY_TORRENT] =
    {
        .name = ES(_("Torrent"), _("Torrente")),
        .description = ES(COMPOUND_STRING("Ups Water moves at low HP."), COMPOUND_STRING("Potencia Agua con pocos PS.")),
        .aiRating = 5,
    },

    [ABILITY_SWARM] =
    {
        .name = ES(_("Swarm"), _("Enjambre")),
        .description = ES(COMPOUND_STRING("Ups Bug moves at low HP."), COMPOUND_STRING("Potencia Bicho con pocos PS.")),
        .aiRating = 5,
    },

    [ABILITY_ROCK_HEAD] =
    {
        .name = ES(_("Rock Head"), _("Cabeza Roca")),
        .description = ES(COMPOUND_STRING("Prevents recoil damage."), COMPOUND_STRING("No recibe daño de retroceso.")),
        .aiRating = 5,
    },

    [ABILITY_DROUGHT] =
    {
        .name = ES(_("Drought"), _("Sequía")),
        .description = ES(COMPOUND_STRING("Summons sunlight in battle."), COMPOUND_STRING("Hace que salga el sol.")),
        .aiRating = 9,
    },

    [ABILITY_ARENA_TRAP] =
    {
        .name = ES(_("Arena Trap"), _("Trampa Arena")),
        .description = ES(COMPOUND_STRING("Prevents foes from fleeing."), COMPOUND_STRING("Evita que el rival huya.")),
        .aiRating = 9,
    },

    [ABILITY_VITAL_SPIRIT] =
    {
        .name = ES(_("Vital Spirit"), _("Espíritu Vital")),
        .description = ES(COMPOUND_STRING("Prevents sleep."), COMPOUND_STRING("Evita el quedarse dormido.")),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_WHITE_SMOKE] =
    {
        .name = ES(_("White Smoke"), _("Humo Blanco")),
        .description = ES(COMPOUND_STRING("Stats can't be lowered."), COMPOUND_STRING("No le bajan características.")),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_PURE_POWER] =
    {
        .name = ES(_("Pure Power"), _("Energía Pura")),
        .description = ES(COMPOUND_STRING("Doubles Attack."), COMPOUND_STRING("Aumenta el Ataque.")),
        .aiRating = 10,
    },

    [ABILITY_SHELL_ARMOR] =
    {
        .name = ES(_("Shell Armor"), _("Caparazón")),
        .description = ES(COMPOUND_STRING("Blocks critical hits."), COMPOUND_STRING("Bloquea los golpes críticos.")),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_AIR_LOCK] =
    {
        .name = ES(_("Air Lock"), _("Bucle Aire")),
        .description = ES(COMPOUND_STRING("Negates weather effects."), COMPOUND_STRING("Anula los efectos del tiempo.")),
        .aiRating = 5,
    },

    [ABILITY_TANGLED_FEET] =
    {
        .name = ES(_("Tangled Feet"), _("Tumbos")),
        .description = ES(COMPOUND_STRING("Boosts evasion if confused."), COMPOUND_STRING("Más evasión si está confuso.")),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MOTOR_DRIVE] =
    {
        .name = ES(_("Motor Drive"), _("Electromotor")),
        .description = ES(COMPOUND_STRING("Ups Speed if hit by Electr."), COMPOUND_STRING("Lo eléctrico le da Velocidad.")),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_RIVALRY] =
    {
        .name = ES(_("Rivalry"), _("Rivalidad")),
        .description = ES(COMPOUND_STRING("Strong vs. opposite gender."), COMPOUND_STRING("Fuerte contra su mismo sexo.")),
        .aiRating = 1,
    },

    [ABILITY_STEADFAST] =
    {
        .name = ES(_("Steadfast"), _("Impasible")),
        .description = ES(COMPOUND_STRING("Flinching raises Speed."), COMPOUND_STRING("Amedrentarlo sube Velocidad.")),
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
        .description = ES(COMPOUND_STRING("Eats Berries at half HP."), COMPOUND_STRING("Come bayas a mitad de PS.")),
        .aiRating = 3,
    },

    [ABILITY_ANGER_POINT] =
    {
        .name = ES(_("Anger Point"), _("Irascible")),
        .description = ES(COMPOUND_STRING("Maxes Attack when crit."), COMPOUND_STRING("Crítico: Ataque al máximo.")),
        .aiRating = 4,
    },

    [ABILITY_UNBURDEN] =
    {
        .name = ES(_("Unburden"), _("Liviano")),
        .description = ES(COMPOUND_STRING("Item loss boosts Speed."), COMPOUND_STRING("Perder objeto da Velocidad.")),
        .aiRating = 7,
    },

    [ABILITY_HEATPROOF] =
    {
        .name = ES(_("Heatproof"), _("Ignífugo")),
        .description = ES(COMPOUND_STRING("Halves Fire-type damage."), COMPOUND_STRING("Mitad de daño de Fuego.")),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SIMPLE] =
    {
        .name = _("Simple"),
        .description = ES(COMPOUND_STRING("Doubles stat changes."), COMPOUND_STRING("Duplica cambios de caract.")),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_DRY_SKIN] =
    {
        .name = ES(_("Dry Skin"), _("Piel Seca")),
        .description = ES(COMPOUND_STRING("Heat hurts, Water restores."), COMPOUND_STRING("El Fuego daña, el Agua cura.")),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DOWNLOAD] =
    {
        .name = ES(_("Download"), _("Descarga")),
        .description = ES(COMPOUND_STRING("Ups offense based on foe."), COMPOUND_STRING("Sube ataque según el rival.")),
        .aiRating = 7,
    },

    [ABILITY_IRON_FIST] =
    {
        .name = ES(_("Iron Fist"), _("Puño Férreo")),
        .description = ES(COMPOUND_STRING("Powers up punching moves."), COMPOUND_STRING("Potencia los puñetazos.")),
        .aiRating = 6,
    },

    [ABILITY_POISON_HEAL] =
    {
        .name = ES(_("Poison Heal"), _("Antídoto")),
        .description = ES(COMPOUND_STRING("Restores HP if poisoned."), COMPOUND_STRING("El veneno le cura PS.")),
        .aiRating = 8,
    },

    [ABILITY_ADAPTABILITY] =
    {
        .name = ES(_("Adaptability"), _("Adaptable")),
        .description = ES(COMPOUND_STRING("Powers up same-type moves."), COMPOUND_STRING("Potencia mov. de su tipo.")),
        .aiRating = 8,
    },

    [ABILITY_SKILL_LINK] =
    {
        .name = ES(_("Skill Link"), _("Encadenado")),
        .description = ES(COMPOUND_STRING("Maxes multistrike hits."), COMPOUND_STRING("Máx. golpes en mov. múltiples.")),
        .aiRating = 7,
    },

    [ABILITY_HYDRATION] =
    {
        .name = ES(_("Hydration"), _("Hidratación")),
        .description = ES(COMPOUND_STRING("Cures status in rain."), COMPOUND_STRING("Se cura el estado con lluvia.")),
        .aiRating = 4,
    },

    [ABILITY_SOLAR_POWER] =
    {
        .name = ES(_("Solar Power"), _("Poder Solar")),
        .description = ES(COMPOUND_STRING("Sunlight boosts, but hurts."), COMPOUND_STRING("El sol potencia pero daña.")),
        .aiRating = 3,
    },

    [ABILITY_QUICK_FEET] =
    {
        .name = ES(_("Quick Feet"), _("Pies Rápidos")),
        .description = ES(COMPOUND_STRING("Boosts Speed if statused."), COMPOUND_STRING("Más Velocidad si tiene estado.")),
        .aiRating = 5,
    },

    [ABILITY_NORMALIZE] =
    {
        .name = ES(_("Normalize"), _("Normalidad")),
        .description = ES(COMPOUND_STRING("Moves become Normal-type."), COMPOUND_STRING("Sus mov. pasan a ser Normal.")),
        .aiRating = -1,
    },

    [ABILITY_SNIPER] =
    {
        .name = ES(_("Sniper"), _("Francotirador")),
        .description = ES(COMPOUND_STRING("Powers up critical hits."), COMPOUND_STRING("Potencia los golpes críticos.")),
        .aiRating = 3,
    },

    [ABILITY_MAGIC_GUARD] =
    {
        .name = ES(_("Magic Guard"), _("Muro Mágico")),
        .description = ES(COMPOUND_STRING("Only damaged by attacks."), COMPOUND_STRING("Solo recibe daño de ataques.")),
        .aiRating = 9,
    },

    [ABILITY_NO_GUARD] =
    {
        .name = ES(_("No Guard"), _("Indefenso")),
        .description = ES(COMPOUND_STRING("Ensures all attacks land."), COMPOUND_STRING("Todos los ataques aciertan.")),
        .aiRating = 8,
    },

    [ABILITY_STALL] =
    {
        .name = ES(_("Stall"), _("Rezagado")),
        .description = ES(COMPOUND_STRING("Always last to use moves."), COMPOUND_STRING("Siempre ataca el último.")),
        .aiRating = -1,
    },

    [ABILITY_TECHNICIAN] =
    {
        .name = ES(_("Technician"), _("Experto")),
        .description = ES(COMPOUND_STRING("Powers up weak moves."), COMPOUND_STRING("Potencia mov. débiles.")),
        .aiRating = 8,
    },

    [ABILITY_LEAF_GUARD] =
    {
        .name = ES(_("Leaf Guard"), _("Defensa Hoja")),
        .description = ES(COMPOUND_STRING("Blocks status in sunlight."), COMPOUND_STRING("Al sol, sin problemas estado.")),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_KLUTZ] =
    {
        .name = ES(_("Klutz"), _("Zoquete")),
        .description = ES(COMPOUND_STRING("Can't use held items."), COMPOUND_STRING("No puede usar su objeto.")),
        .aiRating = -1,
    },

    [ABILITY_MOLD_BREAKER] =
    {
        .name = ES(_("Mold Breaker"), _("Rompemoldes")),
        .description = ES(COMPOUND_STRING("Moves ignore Abilities."), COMPOUND_STRING("Ignora las habilidades.")),
        .aiRating = 7,
    },

    [ABILITY_SUPER_LUCK] =
    {
        .name = ES(_("Super Luck"), _("Afortunado")),
        .description = ES(COMPOUND_STRING("Raises critical-hit ratio."), COMPOUND_STRING("Más golpes críticos.")),
        .aiRating = 3,
    },

    [ABILITY_AFTERMATH] =
    {
        .name = ES(_("Aftermath"), _("Detonación")),
        .description = ES(COMPOUND_STRING("Fainting damages the foe."), COMPOUND_STRING("Daña al rival si se debilita.")),
        .aiRating = 5,
    },

    [ABILITY_ANTICIPATION] =
    {
        .name = ES(_("Anticipation"), _("Anticipación")),
        .description = ES(COMPOUND_STRING("Senses dangerous moves."), COMPOUND_STRING("Detecta mov. peligrosos.")),
        .aiRating = 2,
    },

    [ABILITY_FOREWARN] =
    {
        .name = ES(_("Forewarn"), _("Alerta")),
        .description = ES(COMPOUND_STRING("Determines a foe's move."), COMPOUND_STRING("Revela un mov. del rival.")),
        .aiRating = 2,
    },

    [ABILITY_UNAWARE] =
    {
        .name = ES(_("Unaware"), _("Ignorante")),
        .description = ES(COMPOUND_STRING("Ignores foes' stat changes."), COMPOUND_STRING("Ignora cambios del rival.")),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_TINTED_LENS] =
    {
        .name = ES(_("Tinted Lens"), _("Cromolente")),
        .description = ES(COMPOUND_STRING("Ups “not very effective”."), COMPOUND_STRING("Potencia los poco eficaces.")),
        .aiRating = 7,
    },

    [ABILITY_FILTER] =
    {
        .name = ES(_("Filter"), _("Filtro")),
        .description = ES(COMPOUND_STRING("Weakens “supereffective”."), COMPOUND_STRING("Reduce los supereficaces.")),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SLOW_START] =
    {
        .name = ES(_("Slow Start"), _("Inicio Lento")),
        .description = ES(COMPOUND_STRING("Takes 5 turns to get going."), COMPOUND_STRING("Tarda 5 turnos en arrancar.")),
        .aiRating = -2,
    },

    [ABILITY_SCRAPPY] =
    {
        .name = ES(_("Scrappy"), _("Intrépido")),
        .description = ES(COMPOUND_STRING("Normal & Fight. hit Ghosts."), COMPOUND_STRING("Normal y Lucha dan a Fantasma.")),
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
        .description = ES(COMPOUND_STRING("Weakens “supereffective”."), COMPOUND_STRING("Reduce los supereficaces.")),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SNOW_WARNING] =
    {
        .name = ES(_("Snow Warning"), _("Nevada")),
    #if B_SNOW_WARNING >= GEN_9
        .description = ES(COMPOUND_STRING("Summons snow in battle."), COMPOUND_STRING("Hace que nieve.")),
    #else
        .description = COMPOUND_STRING("Summons hail in battle."),
    #endif
        .aiRating = 8,
    },

    [ABILITY_HONEY_GATHER] =
    {
        .name = ES(_("Honey Gather"), _("Recogemiel")),
        .description = ES(COMPOUND_STRING("May gather Honey."), COMPOUND_STRING("Puede recoger Miel.")),
        .aiRating = 0,
    },

    [ABILITY_FRISK] =
    {
        .name = ES(_("Frisk"), _("Cacheo")),
        .description = ES(COMPOUND_STRING("Checks a foe's held item."), COMPOUND_STRING("Ve el objeto del rival.")),
        .aiRating = 3,
    },

    [ABILITY_RECKLESS] =
    {
        .name = ES(_("Reckless"), _("Audaz")),
        .description = ES(COMPOUND_STRING("Powers up recoil moves."), COMPOUND_STRING("Potencia mov. con retroceso.")),
        .aiRating = 6,
    },

    [ABILITY_MULTITYPE] =
    {
        .name = ES(_("Multitype"), _("Multitipo")),
        .description = ES(COMPOUND_STRING("Matches Plate or Z-Crystal."), COMPOUND_STRING("Tipo según tabla o cristal Z.")),
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
        .description = ES(COMPOUND_STRING("Sun ups allies' Atk & Sp.Def."), COMPOUND_STRING("Al sol, más Atq y Def. Esp.")),
        .aiRating = 4,
        .cantBeCopied = TRUE,
        .cantBeTraced = B_UPDATED_ABILITY_DATA >= GEN_5,
        .breakable = TRUE,
    },

    [ABILITY_BAD_DREAMS] =
    {
        .name = ES(_("Bad Dreams"), _("Mal Sueño")),
        .description = ES(COMPOUND_STRING("Damages sleeping foes."), COMPOUND_STRING("Daña a rivales dormidos.")),
        .aiRating = 4,
    },

    [ABILITY_PICKPOCKET] =
    {
        .name = ES(_("Pickpocket"), _("Hurto")),
        .description = ES(COMPOUND_STRING("Steals foe's item if hit."), COMPOUND_STRING("Roba el objeto si le golpean.")),
        .aiRating = 3,
    },

    [ABILITY_SHEER_FORCE] =
    {
        .name = ES(_("Sheer Force"), _("Potencia Bruta")),
        .description = ES(COMPOUND_STRING("Trades effects for power."), COMPOUND_STRING("Sin efectos, más potencia.")),
        .aiRating = 8,
    },

    [ABILITY_CONTRARY] =
    {
        .name = ES(_("Contrary"), _("Respondón")),
        .description = ES(COMPOUND_STRING("Reverses stat changes."), COMPOUND_STRING("Invierte cambios de caract.")),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_UNNERVE] =
    {
        .name = ES(_("Unnerve"), _("Nerviosismo")),
        .description = ES(COMPOUND_STRING("Foes can't eat Berries."), COMPOUND_STRING("El rival no puede comer bayas.")),
        .aiRating = 3,
    },

    [ABILITY_DEFIANT] =
    {
        .name = ES(_("Defiant"), _("Competitivo")),
        .description = ES(COMPOUND_STRING("Stat-lowering ups Attack."), COMPOUND_STRING("Si le bajan algo, sube Ataque.")),
        .aiRating = 5,
    },

    [ABILITY_DEFEATIST] =
    {
        .name = ES(_("Defeatist"), _("Flaqueza")),
        .description = ES(COMPOUND_STRING("Halves offenses at half HP."), COMPOUND_STRING("Mitad de ataque a mitad de PS.")),
        .aiRating = -1,
    },

    [ABILITY_CURSED_BODY] =
    {
        .name = ES(_("Cursed Body"), _("Cuerpo Maldito")),
        .description = ES(COMPOUND_STRING("Contact may disable move."), COMPOUND_STRING("Puede anular mov. al tocarlo.")),
        .aiRating = 4,
    },

    [ABILITY_HEALER] =
    {
        .name = ES(_("Healer"), _("Alma Cura")),
        .description = ES(COMPOUND_STRING("May cure ally's status."), COMPOUND_STRING("Puede curar a un aliado.")),
        .aiRating = 0,
    },

    [ABILITY_FRIEND_GUARD] =
    {
        .name = ES(_("Friend Guard"), _("Compiescolta")),
        .description = ES(COMPOUND_STRING("Reduces damage to allies."), COMPOUND_STRING("Reduce el daño a aliados.")),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_WEAK_ARMOR] =
    {
        .name = ES(_("Weak Armor"), _("Armadura Frágil")),
        .description = ES(COMPOUND_STRING("Hits change Def and Speed."), COMPOUND_STRING("Golpes: -Def. y +Velocidad.")),
        .aiRating = 2,
    },

    [ABILITY_HEAVY_METAL] =
    {
        .name = ES(_("Heavy Metal"), _("Metal Pesado")),
        .description = ES(COMPOUND_STRING("Doubles weight."), COMPOUND_STRING("Duplica su peso.")),
        .aiRating = -1,
        .breakable = TRUE,
    },

    [ABILITY_LIGHT_METAL] =
    {
        .name = ES(_("Light Metal"), _("Metal Liviano")),
        .description = ES(COMPOUND_STRING("Halves weight."), COMPOUND_STRING("Reduce a la mitad su peso.")),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MULTISCALE] =
    {
        .name = ES(_("Multiscale"), _("Multiescamas")),
        .description = ES(COMPOUND_STRING("Reduces damage at full HP."), COMPOUND_STRING("Menos daño con PS al máximo.")),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_TOXIC_BOOST] =
    {
        .name = ES(_("Toxic Boost"), _("Ímpetu Tóxico")),
        .description = ES(COMPOUND_STRING("Boosts Attack if poisoned."), COMPOUND_STRING("Más Ataque si está envenenado.")),
        .aiRating = 6,
    },

    [ABILITY_FLARE_BOOST] =
    {
        .name = ES(_("Flare Boost"), _("Ímpetu Ardiente")),
        .description = ES(COMPOUND_STRING("Boosts Sp. Atk if burned."), COMPOUND_STRING("Más At. Esp. si está quemado.")),
        .aiRating = 5,
    },

    [ABILITY_HARVEST] =
    {
        .name = ES(_("Harvest"), _("Cosecha")),
        .description = ES(COMPOUND_STRING("May create another Berry."), COMPOUND_STRING("Puede regenerar una baya.")),
        .aiRating = 5,
    },

    [ABILITY_TELEPATHY] =
    {
        .name = ES(_("Telepathy"), _("Telepatía")),
        .description = ES(COMPOUND_STRING("Dodges ally's attacks."), COMPOUND_STRING("Esquiva ataques de aliados.")),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_MOODY] =
    {
        .name = ES(_("Moody"), _("Veleta")),
        .description = ES(COMPOUND_STRING("Stats change every turn."), COMPOUND_STRING("Cambia caract. cada turno.")),
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
        .description = ES(COMPOUND_STRING("Contact moves may poison."), COMPOUND_STRING("Puede envenenar al tocar.")),
        .aiRating = 4,
    },

    [ABILITY_REGENERATOR] =
    {
        .name = ES(_("Regenerator"), _("Regeneración")),
        .description = ES(COMPOUND_STRING("Restores HP upon switch."), COMPOUND_STRING("Recupera PS al cambiarse.")),
        .aiRating = 8,
    },

    [ABILITY_BIG_PECKS] =
    {
        .name = ES(_("Big Pecks"), _("Sacapecho")),
        .description = ES(COMPOUND_STRING("Defense can't be lowered."), COMPOUND_STRING("No le baja la Defensa.")),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_SAND_RUSH] =
    {
        .name = ES(_("Sand Rush"), _("Ímpetu Arena")),
        .description = ES(COMPOUND_STRING("Ups Speed in a sandstorm."), COMPOUND_STRING("Más Velocidad con arena.")),
        .aiRating = 6,
    },

    [ABILITY_WONDER_SKIN] =
    {
        .name = ES(_("Wonder Skin"), _("Piel Milagro")),
        .description = ES(COMPOUND_STRING("May avoid status moves."), COMPOUND_STRING("Puede evitar mov. de estado.")),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANALYTIC] =
    {
        .name = ES(_("Analytic"), _("Cálculo Final")),
        .description = ES(COMPOUND_STRING("Boosts power if last to act."), COMPOUND_STRING("Más potencia si va el último.")),
        .aiRating = 5,
    },

    [ABILITY_ILLUSION] =
    {
        .name = ES(_("Illusion"), _("Ilusión")),
        .description = ES(COMPOUND_STRING("Disguises as a partner."), COMPOUND_STRING("Se disfraza de un compañero.")),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_IMPOSTER] =
    {
        .name = ES(_("Imposter"), _("Impostor")),
        .description = ES(COMPOUND_STRING("Transforms into the foe."), COMPOUND_STRING("Se transforma en el rival.")),
        .aiRating = 9,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_INFILTRATOR] =
    {
        .name = ES(_("Infiltrator"), _("Allanamiento")),
        .description = ES(COMPOUND_STRING("Passes through barriers."), COMPOUND_STRING("Atraviesa las barreras.")),
        .aiRating = 6,
    },

    [ABILITY_MUMMY] =
    {
        .name = ES(_("Mummy"), _("Momia")),
        .description = ES(COMPOUND_STRING("Ability spreads on contact."), COMPOUND_STRING("Contagia su habilidad.")),
        .aiRating = 5,
    },

    [ABILITY_MOXIE] =
    {
        .name = ES(_("Moxie"), _("Autoestima")),
        .description = ES(COMPOUND_STRING("Raises Attack after KOs."), COMPOUND_STRING("Sube Ataque al debilitar.")),
        .aiRating = 7,
    },

    [ABILITY_JUSTIFIED] =
    {
        .name = ES(_("Justified"), _("Justiciero")),
        .description = ES(COMPOUND_STRING("Ups Attack if hit by Dark."), COMPOUND_STRING("Siniestro le sube el Ataque.")),
        .aiRating = 4,
    },

    [ABILITY_RATTLED] =
    {
        .name = ES(_("Rattled"), _("Cobardía")),
        .description = ES(COMPOUND_STRING("Raises Speed when scared."), COMPOUND_STRING("El miedo le da Velocidad.")),
        .aiRating = 3,
    },

    [ABILITY_MAGIC_BOUNCE] =
    {
        .name = ES(_("Magic Bounce"), _("Espejo Mágico")),
        .description = ES(COMPOUND_STRING("Reflects status moves."), COMPOUND_STRING("Devuelve mov. de estado.")),
        .aiRating = 9,
        .breakable = TRUE,
    },

    [ABILITY_SAP_SIPPER] =
    {
        .name = ES(_("Sap Sipper"), _("Herbívoro")),
        .description = ES(COMPOUND_STRING("Ups Attack if hit by Grass."), COMPOUND_STRING("Planta le sube el Ataque.")),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_PRANKSTER] =
    {
        .name = ES(_("Prankster"), _("Bromista")),
        .description = ES(COMPOUND_STRING("Status moves have priority."), COMPOUND_STRING("Mov. de estado con prioridad.")),
        .aiRating = 8,
    },

    [ABILITY_SAND_FORCE] =
    {
        .name = ES(_("Sand Force"), _("Poder Arena")),
        .description = ES(COMPOUND_STRING("Powers up in a sandstorm."), COMPOUND_STRING("Más fuerza con arena.")),
        .aiRating = 4,
    },

    [ABILITY_IRON_BARBS] =
    {
        .name = ES(_("Iron Barbs"), _("Punta Acero")),
        .description = ES(COMPOUND_STRING("Damages foe on contact."), COMPOUND_STRING("Hiere al hacer contacto.")),
        .aiRating = 6,
    },

    [ABILITY_ZEN_MODE] =
    {
        .name = ES(_("Zen Mode"), _("Modo Daruma")),
        .description = ES(COMPOUND_STRING("Changes shape at half HP."), COMPOUND_STRING("Cambia de forma en un apuro.")),
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
        .description = ES(COMPOUND_STRING("Boosts allies' accuracy."), COMPOUND_STRING("Más precisión al equipo.")),
        .aiRating = 6,
    },

    [ABILITY_TURBOBLAZE] =
    {
        .name = ES(_("Turboblaze"), _("Turbollama")),
        .description = ES(COMPOUND_STRING("Moves ignore Abilities."), COMPOUND_STRING("Ignora las habilidades.")),
        .aiRating = 7,
    },

    [ABILITY_TERAVOLT] =
    {
        .name = ES(_("Teravolt"), _("Terravoltaje")),
        .description = ES(COMPOUND_STRING("Moves ignore Abilities."), COMPOUND_STRING("Ignora las habilidades.")),
        .aiRating = 7,
    },

    [ABILITY_AROMA_VEIL] =
    {
        .name = ES(_("Aroma Veil"), _("Velo Aroma")),
        .description = ES(COMPOUND_STRING("Allies can't be move-bound."), COMPOUND_STRING("Protege de bloqueos a aliados.")),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_FLOWER_VEIL] =
    {
        .name = ES(_("Flower Veil"), _("Velo Flor")),
        .description = ES(COMPOUND_STRING("Mist for Grass-type allies."), COMPOUND_STRING("Protege a aliados Planta.")),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_CHEEK_POUCH] =
    {
        .name = ES(_("Cheek Pouch"), _("Carrillo")),
        .description = ES(COMPOUND_STRING("Eating a Berry restores HP."), COMPOUND_STRING("Recupera PS al comer bayas.")),
        .aiRating = 4,
    },

    [ABILITY_PROTEAN] =
    {
        .name = ES(_("Protean"), _("Mutatipo")),
        .description = ES(COMPOUND_STRING("Changes type to used move."), COMPOUND_STRING("Toma el tipo del mov. usado.")),
        .aiRating = 8,
    },

    [ABILITY_FUR_COAT] =
    {
        .name = ES(_("Fur Coat"), _("Pelaje Recio")),
        .description = ES(COMPOUND_STRING("Halves physical damage."), COMPOUND_STRING("Mitad de daño físico.")),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MAGICIAN] =
    {
        .name = ES(_("Magician"), _("Prestidigitador")),
        .description = ES(COMPOUND_STRING("Steals the foe's held item."), COMPOUND_STRING("Roba el objeto del rival.")),
        .aiRating = 3,
    },

    [ABILITY_BULLETPROOF] =
    {
        .name = ES(_("Bulletproof"), _("Antibalas")),
        .description = ES(COMPOUND_STRING("Blocks ball and bomb moves."), COMPOUND_STRING("Inmune a bolas y bombas.")),
        .breakable = TRUE,
        .aiRating = 7,
    },

    [ABILITY_COMPETITIVE] =
    {
        .name = ES(_("Competitive"), _("Tenacidad")),
        .description = ES(COMPOUND_STRING("Stat-lowering ups Sp. Atk."), COMPOUND_STRING("Si le bajan algo: +At. Esp.")),
        .aiRating = 5,
    },

    [ABILITY_STRONG_JAW] =
    {
        .name = ES(_("Strong Jaw"), _("Mandíbula Fuerte")),
        .description = ES(COMPOUND_STRING("Boosts biting moves."), COMPOUND_STRING("Potencia los mordiscos.")),
        .aiRating = 6,
    },

    [ABILITY_REFRIGERATE] =
    {
        .name = ES(_("Refrigerate"), _("Piel Helada")),
        .description = ES(COMPOUND_STRING("Normal moves become Ice."), COMPOUND_STRING("Mov. Normal pasan a Hielo.")),
        .aiRating = 8,
    },

    [ABILITY_SWEET_VEIL] =
    {
        .name = ES(_("Sweet Veil"), _("Velo Dulce")),
        .description = ES(COMPOUND_STRING("Protects allies from sleep."), COMPOUND_STRING("Evita que el equipo duerma.")),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_STANCE_CHANGE] =
    {
        .name = ES(_("Stance Change"), _("Cambio Táctico")),
        .description = ES(COMPOUND_STRING("Swaps Forme as it battles."), COMPOUND_STRING("Cambia de forma al luchar.")),
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
        .description = ES(COMPOUND_STRING("Flying moves have priority."), COMPOUND_STRING("Mov. Volador con prioridad.")),
        .aiRating = 6,
    },

    [ABILITY_MEGA_LAUNCHER] =
    {
        .name = ES(_("Mega Launcher"), _("Megadisparador")),
        .description = ES(COMPOUND_STRING("Powers up pulse moves."), COMPOUND_STRING("Potencia mov. de pulso.")),
        .aiRating = 7,
    },

    [ABILITY_GRASS_PELT] =
    {
        .name = ES(_("Grass Pelt"), _("Manto Frondoso")),
        .description = ES(COMPOUND_STRING("Grassy Terrain ups Defense."), COMPOUND_STRING("Campo de Hierba: +Defensa.")),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_SYMBIOSIS] =
    {
        .name = ES(_("Symbiosis"), _("Simbiosis")),
        .description = ES(COMPOUND_STRING("Passes held item to ally."), COMPOUND_STRING("Pasa su objeto a un aliado.")),
        .aiRating = 0,
    },

    [ABILITY_TOUGH_CLAWS] =
    {
        .name = ES(_("Tough Claws"), _("Garra Dura")),
        .description = ES(COMPOUND_STRING("Powers up contact moves."), COMPOUND_STRING("Potencia mov. de contacto.")),
        .aiRating = 7,
    },

    [ABILITY_PIXILATE] =
    {
        .name = ES(_("Pixilate"), _("Piel Feérica")),
        .description = ES(COMPOUND_STRING("Normal moves become Fairy."), COMPOUND_STRING("Mov. Normal pasan a Hada.")),
        .aiRating = 8,
    },

    [ABILITY_GOOEY] =
    {
        .name = ES(_("Gooey"), _("Baba")),
        .description = ES(COMPOUND_STRING("Contact lowers foe's Speed."), COMPOUND_STRING("Contacto: baja Velocidad.")),
        .aiRating = 5,
    },

    [ABILITY_AERILATE] =
    {
        .name = ES(_("Aerilate"), _("Piel Celeste")),
        .description = ES(COMPOUND_STRING("Normal moves become Flying."), COMPOUND_STRING("Mov. Normal pasan a Volador.")),
        .aiRating = 8,
    },

    [ABILITY_PARENTAL_BOND] =
    {
        .name = ES(_("Parental Bond"), _("Amor Filial")),
        .description = ES(COMPOUND_STRING("Parent & child each attack."), COMPOUND_STRING("Ataque doble en familia.")),
        .aiRating = 10,
    },

    [ABILITY_DARK_AURA] =
    {
        .name = ES(_("Dark Aura"), _("Aura Oscura")),
        .description = ES(COMPOUND_STRING("Ups all Dark-type moves."), COMPOUND_STRING("Potencia todo mov. Siniestro.")),
        .aiRating = 6,
        .breakable = B_UPDATED_ABILITY_DATA < GEN_8,
    },

    [ABILITY_FAIRY_AURA] =
    {
        .name = ES(_("Fairy Aura"), _("Aura Feérica")),
        .description = ES(COMPOUND_STRING("Ups all Fairy-type moves."), COMPOUND_STRING("Potencia todo mov. Hada.")),
        .aiRating = 6,
        .breakable = B_UPDATED_ABILITY_DATA < GEN_8,
    },

    [ABILITY_AURA_BREAK] =
    {
        .name = ES(_("Aura Break"), _("Rompeaura")),
        .description = ES(COMPOUND_STRING("Reverses Aura Abilities."), COMPOUND_STRING("Invierte las auras.")),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_PRIMORDIAL_SEA] =
    {
        .name = ES(_("Primordial Sea"), _("Mar del Albor")),
        .description = ES(COMPOUND_STRING("Summons heavy rain."), COMPOUND_STRING("Crea un diluvio.")),
        .aiRating = 10,
    },

    [ABILITY_DESOLATE_LAND] =
    {
        .name = ES(_("Desolate Land"), _("Tierra del Ocaso")),
        .description = ES(COMPOUND_STRING("Summons extreme sunlight."), COMPOUND_STRING("Crea un sol abrasador.")),
        .aiRating = 10,
    },

    [ABILITY_DELTA_STREAM] =
    {
        .name = ES(_("Delta Stream"), _("Ráfaga Delta")),
        .description = ES(COMPOUND_STRING("Summons strong winds."), COMPOUND_STRING("Crea turbulencias.")),
        .aiRating = 10,
    },

    [ABILITY_STAMINA] =
    {
        .name = ES(_("Stamina"), _("Firmeza")),
        .description = ES(COMPOUND_STRING("Raises Defense when hit."), COMPOUND_STRING("Sube Defensa al recibir daño.")),
        .aiRating = 6,
    },

    [ABILITY_WIMP_OUT] =
    {
        .name = ES(_("Wimp Out"), _("Huida")),
        .description = ES(COMPOUND_STRING("Switches out at half HP."), COMPOUND_STRING("Se retira a mitad de PS.")),
        .aiRating = 3,
    },

    [ABILITY_EMERGENCY_EXIT] =
    {
        .name = ES(_("Emergency Exit"), _("Retirada")),
        .description = ES(COMPOUND_STRING("Switches out at half HP."), COMPOUND_STRING("Se retira a mitad de PS.")),
        .aiRating = 3,
    },

    [ABILITY_WATER_COMPACTION] =
    {
        .name = ES(_("Water Compaction"), _("Hidrorrefuerzo")),
        .description = ES(COMPOUND_STRING("Ups Defense if hit by Water."), COMPOUND_STRING("El Agua le sube la Defensa.")),
        .aiRating = 4,
    },

    [ABILITY_MERCILESS] =
    {
        .name = ES(_("Merciless"), _("Ensañamiento")),
        .description = ES(COMPOUND_STRING("Critical hits poisoned foes."), COMPOUND_STRING("Crítico seguro si hay veneno.")),
        .aiRating = 4,
    },

    [ABILITY_SHIELDS_DOWN] =
    {
        .name = ES(_("Shields Down"), _("Escudo Limitado")),
        .description = ES(COMPOUND_STRING("Shell breaks at half HP."), COMPOUND_STRING("Rompe su coraza a mitad PS.")),
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
        .description = ES(COMPOUND_STRING("Stronger on foe's switch in."), COMPOUND_STRING("Más fuerte si el rival entra.")),
        .aiRating = 6,
    },

    [ABILITY_WATER_BUBBLE] =
    {
        .name = ES(_("Water Bubble"), _("Pompa")),
        .description = ES(COMPOUND_STRING("Guards from Fire and burns."), COMPOUND_STRING("Protege del Fuego y quemar.")),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_STEELWORKER] =
    {
        .name = ES(_("Steelworker"), _("Acero Templado")),
        .description = ES(COMPOUND_STRING("Ups Steel-type moves."), COMPOUND_STRING("Potencia mov. Acero.")),
        .aiRating = 6,
    },

    [ABILITY_BERSERK] =
    {
        .name = ES(_("Berserk"), _("Cólera")),
        .description = ES(COMPOUND_STRING("Boosts Sp. Atk at half HP."), COMPOUND_STRING("Sube At. Esp. a mitad de PS.")),
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
        .description = ES(COMPOUND_STRING("Moves don't make contact."), COMPOUND_STRING("Sus mov. no hacen contacto.")),
        .aiRating = 3,
    },

    [ABILITY_LIQUID_VOICE] =
    {
        .name = ES(_("Liquid Voice"), _("Voz Fluida")),
        .description = ES(COMPOUND_STRING("Sound moves become Water."), COMPOUND_STRING("Mov. de sonido pasan a Agua.")),
        .aiRating = 5,
    },

    [ABILITY_TRIAGE] =
    {
        .name = ES(_("Triage"), _("Primer Auxilio")),
        .description = ES(COMPOUND_STRING("Healing moves have priority."), COMPOUND_STRING("Mov. curativos con prioridad.")),
        .aiRating = 7,
    },

    [ABILITY_GALVANIZE] =
    {
        .name = ES(_("Galvanize"), _("Piel Eléctrica")),
        .description = ES(COMPOUND_STRING("Normal moves turn Electric."), COMPOUND_STRING("Mov. Normal pasan a Eléctrico.")),
        .aiRating = 8,
    },

    [ABILITY_SURGE_SURFER] =
    {
        .name = ES(_("Surge Surfer"), _("Cola Surf")),
        .description = ES(COMPOUND_STRING("Electric Terrain ups Speed."), COMPOUND_STRING("Campo Eléctrico: +Velocidad.")),
        .aiRating = 4,
    },

    [ABILITY_SCHOOLING] =
    {
        .name = ES(_("Schooling"), _("Banco")),
        .description = ES(COMPOUND_STRING("Forms a school at high HP."), COMPOUND_STRING("Forma un banco con muchos PS.")),
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
        .description = ES(COMPOUND_STRING("Shroud protects once."), COMPOUND_STRING("El disfraz le protege 1 vez.")),
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
        .description = ES(COMPOUND_STRING("Changes form after a KO."), COMPOUND_STRING("Cambia de forma al debilitar.")),
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
        .description = ES(COMPOUND_STRING("Changes Forme at half HP."), COMPOUND_STRING("Cambia de forma a mitad PS.")),
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
        .description = ES(COMPOUND_STRING("Can poison Steel & Poison."), COMPOUND_STRING("Envenena a Acero y Veneno.")),
        .aiRating = 5,
    },

    [ABILITY_COMATOSE] =
    {
        .name = ES(_("Comatose"), _("Letargo Perenne")),
        .description = ES(COMPOUND_STRING("Always drowsing."), COMPOUND_STRING("Siempre está medio dormido.")),
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
        .description = ES(COMPOUND_STRING("Allies block priority moves."), COMPOUND_STRING("Bloquea mov. con prioridad.")),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_INNARDS_OUT] =
    {
        .name = ES(_("Innards Out"), _("Revés")),
        .description = ES(COMPOUND_STRING("Damages the foe if KO'd."), COMPOUND_STRING("Daña al rival al debilitarse.")),
        .aiRating = 5,
    },

    [ABILITY_DANCER] =
    {
        .name = ES(_("Dancer"), _("Pareja de Baile")),
        .description = ES(COMPOUND_STRING("Dances along with others."), COMPOUND_STRING("Baila cuando otros bailan.")),
        .aiRating = 5,
    },

    [ABILITY_BATTERY] =
    {
        .name = ES(_("Battery"), _("Batería")),
        .description = ES(COMPOUND_STRING("Boosts ally's Sp. Atk."), COMPOUND_STRING("Sube At. Esp. de aliados.")),
        .aiRating = 0,
    },

    [ABILITY_FLUFFY] =
    {
        .name = ES(_("Fluffy"), _("Peluche")),
        .description = ES(COMPOUND_STRING("Halves contact, heat hurts."), COMPOUND_STRING("Mitad daño contacto; Fuego x2.")),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_DAZZLING] =
    {
        .name = ES(_("Dazzling"), _("Cuerpo Vívido")),
        .description = ES(COMPOUND_STRING("Allies block priority moves."), COMPOUND_STRING("Bloquea mov. con prioridad.")),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SOUL_HEART] =
    {
        .name = ES(_("Soul-Heart"), _("Coránima")),
        .description = ES(COMPOUND_STRING("Others fainting ups Sp. Atk."), COMPOUND_STRING("Si alguien cae, sube At. Esp.")),
        .aiRating = 7,
    },

    [ABILITY_TANGLING_HAIR] =
    {
        .name = ES(_("Tangling Hair"), _("Rizos Rebeldes")),
        .description = ES(COMPOUND_STRING("Contact lowers foe's Speed."), COMPOUND_STRING("Contacto: baja Velocidad.")),
        .aiRating = 5,
    },

    [ABILITY_RECEIVER] =
    {
        .name = ES(_("Receiver"), _("Receptor")),
        .description = ES(COMPOUND_STRING("Copies fainted ally Ability."), COMPOUND_STRING("Copia hab. del aliado caído.")),
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POWER_OF_ALCHEMY] =
    {
        .name = ES(_("Power Of Alchemy"), _("Reacción Química")),
        .description = ES(COMPOUND_STRING("Copies fainted ally Ability."), COMPOUND_STRING("Copia hab. del aliado caído.")),
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_BEAST_BOOST] =
    {
        .name = ES(_("Beast Boost"), _("Ultraimpulso")),
        .description = ES(COMPOUND_STRING("Raises best stat after KOs."), COMPOUND_STRING("Sube su mejor caract. al KO.")),
        .aiRating = 7,
    },

    [ABILITY_RKS_SYSTEM] =
    {
        .name = ES(_("RKS System"), _("Sistema Alfa")),
        .description = ES(COMPOUND_STRING("Matches held memory's type."), COMPOUND_STRING("Tipo según su disco.")),
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
        .description = ES(COMPOUND_STRING("Makes the field electrified."), COMPOUND_STRING("Crea un campo eléctrico.")),
        .aiRating = 8,
    },

    [ABILITY_PSYCHIC_SURGE] =
    {
        .name = ES(_("Psychic Surge"), _("Psicogénesis")),
        .description = ES(COMPOUND_STRING("Makes the field weird."), COMPOUND_STRING("Crea un campo psíquico.")),
        .aiRating = 8,
    },

    [ABILITY_MISTY_SURGE] =
    {
        .name = ES(_("Misty Surge"), _("Nebulogénesis")),
        .description = ES(COMPOUND_STRING("Makes the field misty."), COMPOUND_STRING("Crea un campo de niebla.")),
        .aiRating = 8,
    },

    [ABILITY_GRASSY_SURGE] =
    {
        .name = ES(_("Grassy Surge"), _("Herbogénesis")),
        .description = ES(COMPOUND_STRING("Makes the field grassy."), COMPOUND_STRING("Crea un campo de hierba.")),
        .aiRating = 8,
    },

    [ABILITY_FULL_METAL_BODY] =
    {
        .name = ES(_("Full Metal Body"), _("Guardia Metálica")),
        .description = ES(COMPOUND_STRING("Stats can't be lowered."), COMPOUND_STRING("No le bajan características.")),
        .aiRating = 4,
    },

    [ABILITY_SHADOW_SHIELD] =
    {
        .name = ES(_("Shadow Shield"), _("Guardia Espectro")),
        .description = ES(COMPOUND_STRING("Reduces damage at full HP."), COMPOUND_STRING("Menos daño con PS al máximo.")),
        .aiRating = 8,
    },

    [ABILITY_PRISM_ARMOR] =
    {
        .name = ES(_("Prism Armor"), _("Armadura Prisma")),
        .description = ES(COMPOUND_STRING("Weakens “supereffective”."), COMPOUND_STRING("Reduce los supereficaces.")),
        .aiRating = 6,
    },

    [ABILITY_NEUROFORCE] =
    {
        .name = ES(_("Neuroforce"), _("Fuerza Cerebral")),
        .description = ES(COMPOUND_STRING("Ups “supereffective” hits."), COMPOUND_STRING("Potencia los supereficaces.")),
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
        .description = ES(COMPOUND_STRING("Changes type to used move."), COMPOUND_STRING("Toma el tipo del mov. usado.")),
    },

    [ABILITY_BALL_FETCH] =
    {
        .name = ES(_("Ball Fetch"), _("Recogebolas")),
        .description = ES(COMPOUND_STRING("Fetches first failed Ball."), COMPOUND_STRING("Recoge la 1.ª Ball fallida.")),
        .aiRating = 0,
    },

    [ABILITY_COTTON_DOWN] =
    {
        .name = ES(_("Cotton Down"), _("Pelusa")),
        .description = ES(COMPOUND_STRING("Lowers others' Speed if hit."), COMPOUND_STRING("Si le golpean, baja Velocidad.")),
        .aiRating = 3,
    },

    [ABILITY_PROPELLER_TAIL] =
    {
        .name = ES(_("Propeller Tail"), _("Hélice Caudal")),
        .description = ES(COMPOUND_STRING("Ignores foes' move-drawing."), COMPOUND_STRING("Ignora redirecciones.")),
        .aiRating = 2,
    },

    [ABILITY_MIRROR_ARMOR] =
    {
        .name = ES(_("Mirror Armor"), _("Coraza Reflejo")),
        .description = ES(COMPOUND_STRING("Bounces stat-lowering."), COMPOUND_STRING("Devuelve bajadas de caract.")),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_GULP_MISSILE] =
    {
        .name = ES(_("Gulp Missile"), _("Tragamisil")),
        .description = ES(COMPOUND_STRING("Spits when hit after Dive."), COMPOUND_STRING("Escupe al ser golpeado.")),
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
        .description = ES(COMPOUND_STRING("Ignores foes' move-drawing."), COMPOUND_STRING("Ignora redirecciones.")),
        .aiRating = 2,
    },

    [ABILITY_STEAM_ENGINE] =
    {
        .name = ES(_("Steam Engine"), _("Combustible")),
        .description = ES(COMPOUND_STRING("Fire & Water hits up Speed."), COMPOUND_STRING("Fuego o Agua: +Velocidad.")),
        .aiRating = 3,
    },

    [ABILITY_PUNK_ROCK] =
    {
        .name = _("Punk Rock"),
        .description = ES(COMPOUND_STRING("Boosts and resists sound."), COMPOUND_STRING("Potencia y resiste el sonido.")),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_SAND_SPIT] =
    {
        .name = ES(_("Sand Spit"), _("Expulsarena")),
        .description = ES(COMPOUND_STRING("Summons a sandstorm if hit."), COMPOUND_STRING("Crea arena si le golpean.")),
        .aiRating = 5,
    },

    [ABILITY_ICE_SCALES] =
    {
        .name = ES(_("Ice Scales"), _("Escama de Hielo")),
        .description = ES(COMPOUND_STRING("Halves special damage."), COMPOUND_STRING("Mitad de daño especial.")),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_RIPEN] =
    {
        .name = ES(_("Ripen"), _("Maduración")),
        .description = ES(COMPOUND_STRING("Doubles Berry effects."), COMPOUND_STRING("Duplica el efecto de bayas.")),
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
        .description = ES(COMPOUND_STRING("Powers up ally's moves."), COMPOUND_STRING("Potencia mov. de aliados.")),
        .aiRating = 2,
    },

    [ABILITY_MIMICRY] =
    {
        .name = ES(_("Mimicry"), _("Mimetismo")),
        .description = ES(COMPOUND_STRING("Changes type on terrain."), COMPOUND_STRING("Cambia de tipo según el campo.")),
        .aiRating = 2,
    },

    [ABILITY_SCREEN_CLEANER] =
    {
        .name = ES(_("Screen Cleaner"), _("Antibarrera")),
        .description = ES(COMPOUND_STRING("Nullifies barriers on entry."), COMPOUND_STRING("Anula barreras al entrar.")),
        .aiRating = 3,
    },

    [ABILITY_STEELY_SPIRIT] =
    {
        .name = ES(_("Steely Spirit"), _("Alma Acerada")),
        .description = ES(COMPOUND_STRING("Ups allies' Steel moves."), COMPOUND_STRING("Potencia mov. Acero aliados.")),
        .aiRating = 2,
    },

    [ABILITY_PERISH_BODY] =
    {
        .name = ES(_("Perish Body"), _("Cuerpo Mortal")),
        .description = ES(COMPOUND_STRING("Foe faints in 3 turns if hit."), COMPOUND_STRING("Contacto: KO en 3 turnos.")),
        .aiRating = -1,
    },

    [ABILITY_WANDERING_SPIRIT] =
    {
        .name = ES(_("Wandering Spirit"), _("Alma Errante")),
        .description = ES(COMPOUND_STRING("Swaps Abilities on contact."), COMPOUND_STRING("Cambia habilidad al tocar.")),
        .aiRating = 2,
    },

    [ABILITY_GORILLA_TACTICS] =
    {
        .name = ES(_("Gorilla Tactics"), _("Monotema")),
        .description = ES(COMPOUND_STRING("Ups Attack and locks move."), COMPOUND_STRING("Más Ataque, un solo mov.")),
        .aiRating = 4,
    },

    [ABILITY_NEUTRALIZING_GAS] =
    {
        .name = ES(_("Neutralizing Gas"), _("Gas Reactivo")),
        .description = ES(COMPOUND_STRING("Nullifies others' Abilities."), COMPOUND_STRING("Anula las otras habilidades.")),
        .aiRating = 5,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_PASTEL_VEIL] =
    {
        .name = ES(_("Pastel Veil"), _("Velo Pastel")),
        .description = ES(COMPOUND_STRING("Allies can't be poisoned."), COMPOUND_STRING("Evita el veneno al equipo.")),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_HUNGER_SWITCH] =
    {
        .name = ES(_("Hunger Switch"), _("Mutapetito")),
        .description = ES(COMPOUND_STRING("Changes form every turn."), COMPOUND_STRING("Cambia de forma cada turno.")),
        .aiRating = 2,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_QUICK_DRAW] =
    {
        .name = ES(_("Quick Draw"), _("Mano Rápida")),
        .description = ES(COMPOUND_STRING("Occasionally moves first."), COMPOUND_STRING("A veces ataca primero.")),
        .aiRating = 4,
    },

    [ABILITY_UNSEEN_FIST] =
    {
        .name = ES(_("Unseen Fist"), _("Puño Invisible")),
        .description = ES(COMPOUND_STRING("Contact evades protection."), COMPOUND_STRING("Contacto atraviesa protección.")),
        .aiRating = 6,
    },

    [ABILITY_CURIOUS_MEDICINE] =
    {
        .name = ES(_("Curious Medicine"), _("Medicina Extraña")),
        .description = ES(COMPOUND_STRING("Removes ally stat changes."), COMPOUND_STRING("Anula cambios de aliados.")),
        .aiRating = 3,
    },

    [ABILITY_TRANSISTOR] =
    {
        .name = _("Transistor"),
        .description = ES(COMPOUND_STRING("Ups Electric-type moves."), COMPOUND_STRING("Potencia mov. Eléctrico.")),
        .aiRating = 6,
    },

    [ABILITY_DRAGONS_MAW] =
    {
        .name = ES(_("Dragon's Maw"), _("Mandíbula Dragón")),
        .description = ES(COMPOUND_STRING("Ups Dragon-type moves."), COMPOUND_STRING("Potencia mov. Dragón.")),
        .aiRating = 6,
    },

    [ABILITY_CHILLING_NEIGH] =
    {
        .name = ES(_("Chilling Neigh"), _("Relincho Blanco")),
        .description = ES(COMPOUND_STRING("Raises Attack after KOs."), COMPOUND_STRING("Sube Ataque al debilitar.")),
        .aiRating = 7,
    },

    [ABILITY_GRIM_NEIGH] =
    {
        .name = ES(_("Grim Neigh"), _("Relincho Negro")),
        .description = ES(COMPOUND_STRING("Raises Sp. Atk after KOs."), COMPOUND_STRING("Sube At. Esp. al debilitar.")),
        .aiRating = 7,
    },

    [ABILITY_AS_ONE_ICE_RIDER] =
    {
        .name = ES(_("As One"), _("Unidad Ecuestre")),
        .description = ES(COMPOUND_STRING("Unnerve and Chilling Neigh."), COMPOUND_STRING("Nerviosismo y Relincho Blanco.")),
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
        .description = ES(COMPOUND_STRING("Unnerve and Grim Neigh."), COMPOUND_STRING("Nerviosismo y Relincho Negro.")),
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
        .description = ES(COMPOUND_STRING("Ability spreads on contact."), COMPOUND_STRING("Contagia su habilidad.")),
        .aiRating = 5,
    },

    [ABILITY_SEED_SOWER] =
    {
        .name = ES(_("Seed Sower"), _("Disemillar")),
        .description = ES(COMPOUND_STRING("Makes field grassy if hit."), COMPOUND_STRING("Crea hierba si le golpean.")),
        .aiRating = 5,
    },

    [ABILITY_THERMAL_EXCHANGE] =
    {
        .name = ES(_("Thermal Exchange"), _("Termoconversión")),
        .description = ES(COMPOUND_STRING("Ups Attack if hit by Fire."), COMPOUND_STRING("El Fuego le sube el Ataque.")),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANGER_SHELL] =
    {
        .name = ES(_("Anger Shell"), _("Coraza Ira")),
        .description = ES(COMPOUND_STRING("Changes stats at half HP."), COMPOUND_STRING("Cambia caract. a mitad PS.")),
        .aiRating = 3,
    },

    [ABILITY_PURIFYING_SALT] =
    {
        .name = ES(_("Purifying Salt"), _("Sal Purificadora")),
        .description = ES(COMPOUND_STRING("Guards from status & Ghost."), COMPOUND_STRING("Sin estado; resiste Fantasma.")),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_WELL_BAKED_BODY] =
    {
        .name = ES(_("Well-Baked Body"), _("Cuerpo Horneado")),
        .description = ES(COMPOUND_STRING("Ups Defense if hit by Fire."), COMPOUND_STRING("El Fuego le sube la Defensa.")),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_WIND_RIDER] =
    {
        .name = ES(_("Wind Rider"), _("Surcavientos")),
        .description = ES(COMPOUND_STRING("Wind moves raise Attack."), COMPOUND_STRING("El viento le sube el Ataque.")),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_GUARD_DOG] =
    {
        .name = ES(_("Guard Dog"), _("Perro Guardián")),
        .description = ES(COMPOUND_STRING("Raises Atk if intimidated."), COMPOUND_STRING("Intimidarle sube su Ataque.")),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ROCKY_PAYLOAD] =
    {
        .name = ES(_("Rocky Payload"), _("Transportarrocas")),
        .description = ES(COMPOUND_STRING("Powers up Rock-type moves."), COMPOUND_STRING("Potencia mov. Roca.")),
        .aiRating = 6,
    },

    [ABILITY_WIND_POWER] =
    {
        .name = ES(_("Wind Power"), _("Energía Eólica")),
        .description = ES(COMPOUND_STRING("Gets charged if hit by wind."), COMPOUND_STRING("Se carga si recibe viento.")),
        .aiRating = 4,
    },

    [ABILITY_ZERO_TO_HERO] =
    {
        .name = ES(_("Zero to Hero"), _("Cambio Heroico")),
        .description = ES(COMPOUND_STRING("Changes form upon switch."), COMPOUND_STRING("Cambia de forma al cambiarse.")),
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
        .description = ES(COMPOUND_STRING("Commands from ally Dondozo."), COMPOUND_STRING("Dirige desde un Dondozo.")),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_ELECTROMORPHOSIS] =
    {
        .name = ES(_("Electromorphosis"), _("Dinamo")),
        .description = ES(COMPOUND_STRING("Becomes charged when hit."), COMPOUND_STRING("Se carga al recibir golpes.")),
        .aiRating = 5,
    },

    [ABILITY_PROTOSYNTHESIS] =
    {
        .name = ES(_("Protosynthesis"), _("Paleosíntesis")),
        .description = ES(COMPOUND_STRING("Sunlight boosts best stat."), COMPOUND_STRING("Sol: sube su mejor caract.")),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_QUARK_DRIVE] =
    {
        .name = ES(_("Quark Drive"), _("Carga Cuark")),
        .description = ES(COMPOUND_STRING("Electr. field ups best stat."), COMPOUND_STRING("C. Eléctrico: sube su mejor.")),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_GOOD_AS_GOLD] =
    {
        .name = ES(_("Good as Gold"), _("Cuerpo Áureo")),
        .description = ES(COMPOUND_STRING("Immunity to status moves."), COMPOUND_STRING("Inmune a mov. de estado.")),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_VESSEL_OF_RUIN] =
    {
        .name = ES(_("Vessel of Ruin"), _("Caldero Debacle")),
        .description = ES(COMPOUND_STRING("Reduces others' Sp. Atk."), COMPOUND_STRING("Baja At. Esp. a los demás.")),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SWORD_OF_RUIN] =
    {
        .name = ES(_("Sword of Ruin"), _("Espada Debacle")),
        .description = ES(COMPOUND_STRING("Reduces others' Defense."), COMPOUND_STRING("Baja Defensa a los demás.")),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_TABLETS_OF_RUIN] =
    {
        .name = ES(_("Tablets of Ruin"), _("Tablilla Debacle")),
        .description = ES(COMPOUND_STRING("Reduces others' Attack."), COMPOUND_STRING("Baja Ataque a los demás.")),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_BEADS_OF_RUIN] =
    {
        .name = ES(_("Beads of Ruin"), _("Abalorio Debacle")),
        .description = ES(COMPOUND_STRING("Reduces others' Sp. Def."), COMPOUND_STRING("Baja Def. Esp. a los demás.")),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ORICHALCUM_PULSE] =
    {
        .name = ES(_("Orichalcum Pulse"), _("Latido Oricalco")),
        .description = ES(COMPOUND_STRING("Summons sun and ups Atk."), COMPOUND_STRING("Saca el sol y sube Ataque.")),
        .aiRating = 8,
    },

    [ABILITY_HADRON_ENGINE] =
    {
        .name = ES(_("Hadron Engine"), _("Motor Hadrónico")),
        .description = ES(COMPOUND_STRING("Electr. Surge & ups Sp. Atk."), COMPOUND_STRING("Campo Eléctrico y +At. Esp.")),
        .aiRating = 8,
    },

    [ABILITY_OPPORTUNIST] =
    {
        .name = ES(_("Opportunist"), _("Oportunista")),
        .description = ES(COMPOUND_STRING("Copies a foe's stat boost."), COMPOUND_STRING("Copia subidas del rival.")),
        .aiRating = 5,
    },

    [ABILITY_CUD_CHEW] =
    {
        .name = ES(_("Cud Chew"), _("Rumia")),
        .description = ES(COMPOUND_STRING("Eats Berry again next turn."), COMPOUND_STRING("Repite la baya al turno sig.")),
        .aiRating = 4,
    },

    [ABILITY_SHARPNESS] =
    {
        .name = ES(_("Sharpness"), _("Cortante")),
        .description = ES(COMPOUND_STRING("Powers up slicing moves."), COMPOUND_STRING("Potencia mov. cortantes.")),
        .aiRating = 7,
    },

    [ABILITY_SUPREME_OVERLORD] =
    {
        .name = ES(_("Supreme Overlord"), _("General Supremo")),
        .description = ES(COMPOUND_STRING("Fainted partners up power."), COMPOUND_STRING("Aliados caídos dan potencia.")),
        .aiRating = 6,
    },

    [ABILITY_COSTAR] =
    {
        .name = ES(_("Costar"), _("Unísono")),
        .description = ES(COMPOUND_STRING("Copies ally's stat changes."), COMPOUND_STRING("Copia cambios del aliado.")),
        .aiRating = 5,
    },

    [ABILITY_TOXIC_DEBRIS] =
    {
        .name = ES(_("Toxic Debris"), _("Capa Tóxica")),
        .description = ES(COMPOUND_STRING("Lays poison spikes if hit."), COMPOUND_STRING("Pone púas tóxicas al recibir.")),
        .aiRating = 4,
    },

    [ABILITY_ARMOR_TAIL] =
    {
        .name = ES(_("Armor Tail"), _("Cola Armadura")),
        .description = ES(COMPOUND_STRING("Allies block priority moves."), COMPOUND_STRING("Bloquea mov. con prioridad.")),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_EARTH_EATER] =
    {
        .name = ES(_("Earth Eater"), _("Geofagia")),
        .description = ES(COMPOUND_STRING("Restores if hit by Ground."), COMPOUND_STRING("Cura si le da un mov. Tierra.")),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MYCELIUM_MIGHT] =
    {
        .name = ES(_("Mycelium Might"), _("Poder Fúngico")),
        .description = ES(COMPOUND_STRING("Status moves can't fail."), COMPOUND_STRING("Mov. de estado no fallan.")),
        .aiRating = 2,
    },

    [ABILITY_HOSPITALITY] =
    {
        .name = ES(_("Hospitality"), _("Hospitalidad")),
        .description = ES(COMPOUND_STRING("Restores ally's HP on entry."), COMPOUND_STRING("Cura a un aliado al entrar.")),
        .aiRating = 5,
    },

    [ABILITY_MINDS_EYE] =
    {
        .name = ES(_("Mind's Eye"), _("Ojo Mental")),
        .description = ES(COMPOUND_STRING("Grants Foresight."), COMPOUND_STRING("Da a Fantasma; precisión fija.")),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_TEAL_MASK] =
    {
        .name = ES(_("Embody Aspect"), _("Evocarrecuerdos")),
        .description = ES(COMPOUND_STRING("Terastal raises Speed."), COMPOUND_STRING("Teracristal: +Velocidad.")),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_HEARTHFLAME_MASK] =
    {
        .name = ES(_("Embody Aspect"), _("Evocarrecuerdos")),
        .description = ES(COMPOUND_STRING("Terastal raises Attack."), COMPOUND_STRING("Teracristal: +Ataque.")),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_WELLSPRING_MASK] =
    {
        .name = ES(_("Embody Aspect"), _("Evocarrecuerdos")),
        .description = ES(COMPOUND_STRING("Terastal raises Sp. Def."), COMPOUND_STRING("Teracristal: +Def. Esp.")),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_CORNERSTONE_MASK] =
    {
        .name = ES(_("Embody Aspect"), _("Evocarrecuerdos")),
        .description = ES(COMPOUND_STRING("Terastal raises Defense."), COMPOUND_STRING("Teracristal: +Defensa.")),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_TOXIC_CHAIN] =
    {
        .name = ES(_("Toxic Chain"), _("Cadena Tóxica")),
        .description = ES(COMPOUND_STRING("Attacks may badly poison."), COMPOUND_STRING("Puede envenenar gravemente.")),
        .aiRating = 8,
    },

    [ABILITY_SUPERSWEET_SYRUP] =
    {
        .name = ES(_("Supersweet Syrup"), _("Néctar Dulce")),
        .description = ES(COMPOUND_STRING("Lowers foes' evasion once."), COMPOUND_STRING("Baja la evasión rival 1 vez.")),
        .aiRating = 5,
    },

    [ABILITY_TERA_SHIFT] =
    {
        .name = ES(_("Tera Shift"), _("Teracambio")),
        .description = ES(COMPOUND_STRING("Changes form on entry."), COMPOUND_STRING("Cambia de forma al entrar.")),
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
        .description = ES(COMPOUND_STRING("Resists all types at full HP."), COMPOUND_STRING("Resiste todo con PS al máx.")),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_TERAFORM_ZERO] =
    {
        .name = ES(_("Teraform Zero"), _("Teraformación 0")),
        .description = ES(COMPOUND_STRING("Zeroes weather and terrain."), COMPOUND_STRING("Anula tiempo y campos.")),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POISON_PUPPETEER] =
    {
        .name = ES(_("Poison Puppeteer"), _("Títere Tóxico")),
        .description = ES(COMPOUND_STRING("Poisoning also confuses."), COMPOUND_STRING("Su veneno también confunde.")),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_PIERCING_DRILL] =
    {
        .name = ES(_("Piercing Drill"), _("Turbotaladro")),
        .description = ES(COMPOUND_STRING("Contact evades protection."), COMPOUND_STRING("Contacto atraviesa protección.")),
    },

    [ABILITY_DRAGONIZE] =
    {
        .name = ES(_("Dragonize"), _("Piel Dragontina")),
        .description = ES(COMPOUND_STRING("Normal moves turn Dragon."), COMPOUND_STRING("Mov. Normal pasan a Dragón.")),
    },

    [ABILITY_EELEVATE] =
    {
        .name = ES(_("Eelevate"), _("Anguilevitación")),
        .description = ES(COMPOUND_STRING("Levitate and Beast Boost."), COMPOUND_STRING("Levitación y Ultraimpulso.")),
    },

    [ABILITY_314] =
    {
        .name = _("-------"),
        .description = ES(COMPOUND_STRING("No special ability."), COMPOUND_STRING("Sin habilidad especial.")),
    },

    [ABILITY_MEGA_SOL] =
    {
        .name = ES(_("Mega Sol"), _("Megasolar")),
        .description = ES(COMPOUND_STRING("Acts like under sun."), COMPOUND_STRING("Actúa como si hiciera sol.")),
    },

    [ABILITY_FIRE_MANE] =
    {
        .name = ES(_("Fire Mane"), _("Melena Ígnea")),
        .description = ES(COMPOUND_STRING("Ups Fire-type moves."), COMPOUND_STRING("Potencia mov. Fuego.")),
    },

    [ABILITY_317] =
    {
        .name = _("-------"),
        .description = ES(COMPOUND_STRING("No special ability."), COMPOUND_STRING("Sin habilidad especial.")),
    },

    [ABILITY_SPICY_SPRAY] =
    {
        .name = ES(_("Spicy Spray"), _("Salpicante")),
        .description = ES(COMPOUND_STRING("Burns the foe when damaged."), COMPOUND_STRING("Quema al rival si le dañan.")),
    },

    [ABILITY_AURA_GUARD] =
    {
        .name = ES(_("Aura Guard"), _("Guardia Aura")),
        .description = ES(COMPOUND_STRING("Unimplemented."), COMPOUND_STRING("Sin implementar.")),
    },
};
