#include "global.h"
#include "dualocke_aleatorio.h"
#include "constants/species.h"

// Dualocke: estáticos y regalos del randomizer.
// No se tocan los scripts: setwildbattle, givemon, giveegg y los errantes piden aquí la especie
// que les toca. La tabla la genera tools/dualocke/randomizer.py según la semilla (sin semilla,
// está vacía y todo sale como en el original).

#include "data/dualocke_aleatorio.h"

static enum Species Buscar(const u16 (*tabla)[2], u32 count, enum Species species)
{
    u32 i;

    for (i = 0; i < count; i++)
    {
        if (tabla[i][0] == species && tabla[i][1] != SPECIES_NONE)
            return tabla[i][1];
    }
    return species;
}

enum Species Dualocke_EstaticoAleatorio(enum Species species)
{
    return Buscar(sDualockeEstaticos, ARRAY_COUNT(sDualockeEstaticos), species);
}

enum Species Dualocke_RegaloAleatorio(enum Species species)
{
    return Buscar(sDualockeRegalos, ARRAY_COUNT(sDualockeRegalos), species);
}
