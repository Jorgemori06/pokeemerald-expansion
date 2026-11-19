// Dualocke: fósiles que revive el INVESTIGADOR de DEVON (FÉRRICA), además del Fósil Raíz y el Fósil Garra
// de Esmeralda, que siguen con su script original. Los reparte el randomizer de objetos del suelo.
// Con semilla, el POKéMON que sale es otro al azar (tools/dualocke/aleatorio/estaticos.py, fosiles()),
// que lee esta tabla: si se cambia, cambia lo que sale.
static const u16 sDualockeFosiles[][2] =
{
    {ITEM_HELIX_FOSSIL,     SPECIES_OMANYTE},
    {ITEM_DOME_FOSSIL,      SPECIES_KABUTO},
    {ITEM_OLD_AMBER,        SPECIES_AERODACTYL},
    {ITEM_ARMOR_FOSSIL,     SPECIES_SHIELDON},
    {ITEM_SKULL_FOSSIL,     SPECIES_CRANIDOS},
    {ITEM_COVER_FOSSIL,     SPECIES_TIRTOUGA},
    {ITEM_PLUME_FOSSIL,     SPECIES_ARCHEN},
    {ITEM_JAW_FOSSIL,       SPECIES_TYRUNT},
    {ITEM_SAIL_FOSSIL,      SPECIES_AMAURA},
    // Los de Galar van de dos en dos; aquí cada uno revive uno
    {ITEM_FOSSILIZED_BIRD,  SPECIES_DRACOZOLT},
    {ITEM_FOSSILIZED_FISH,  SPECIES_ARCTOVISH},
    {ITEM_FOSSILIZED_DRAKE, SPECIES_DRACOVISH},
    {ITEM_FOSSILIZED_DINO,  SPECIES_ARCTOZOLT},
};
