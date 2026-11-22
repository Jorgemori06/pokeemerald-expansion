#include "global.h"
#include "pokemon_storage_system.h"
#include "test/test.h"

// If you would like to ensure save compatibility, update the values below with those for your hack. You can find these through the debug menu.
// Please note that this simple check is not 100% foolproof, but should be able to catch most unintended shifts.
#define T_SAVEBLOCK1_SIZE 15680 // Dualocke (#115): la mochila y el nombre largo cambian la partida guardada a
                                // propósito, para el locke nuevo con semillas nuevas
#define T_SAVEBLOCK2_SIZE 3896 // Dualocke (#115): playerNameLong, al final
#define T_SAVEBLOCK3_SIZE 1404 // Dualocke: bolsillos MEDICINAS y MEGAPIEDRAS (4 + 60*4 + 130*4; desde el #115,
                               // con OBJETOS y los bolsillos más grandes, 1404). Los 30
                              // huecos nuevos van al final: en una partida de antes salen vacíos
                              // (al guardar, el sector se llena de ceros antes de copiar).
#define T_POKEMONSTORAGE_SIZE 34144

TEST("SaveBlock1 is backwards compatible")
{
    EXPECT_EQ(sizeof(struct SaveBlock1), T_SAVEBLOCK1_SIZE);
}

TEST("SaveBlock2 is backwards compatible")
{
    EXPECT_EQ(sizeof(struct SaveBlock2), T_SAVEBLOCK2_SIZE);
}

TEST("SaveBlock3 is backwards compatible")
{
    EXPECT_EQ(sizeof(struct SaveBlock3), T_SAVEBLOCK3_SIZE);
}

TEST("PokemonStorage is backwards compatible")
{
    EXPECT_EQ(sizeof(struct PokemonStorage), T_POKEMONSTORAGE_SIZE);
}

#undef T_SAVEBLOCK1_SIZE
#undef T_SAVEBLOCK2_SIZE
#undef T_SAVEBLOCK3_SIZE
#undef T_POKEMONSTORAGE_SIZE
