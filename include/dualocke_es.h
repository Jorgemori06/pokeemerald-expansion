#ifndef GUARD_DUALOCKE_ES_H
#define GUARD_DUALOCKE_ES_H

// Dualocke: traducción al español.
// ES("inglés", "español") elige el texto al compilar: en los tests de la expansion
// (TESTING) se queda el inglés, porque cientos de tests comprueban los mensajes exactos;
// en el juego sale el español. Funciona porque el preprocesador de C se ejecuta antes que
// la herramienta que convierte los _("...") (ver la regla de los .c en el Makefile).
#if TESTING
#define ES(en, es) en
#else
#define ES(en, es) es
#endif

// Mensajes de combate de gBattleStringsTable traducidos (src/dualocke_traduccion.c).
// Devuelve NULL si el mensaje aún no está traducido o en los tests: entonces sale el inglés.
const u8 *Dualocke_GetBattleStringES(u32 stringId);

// Nombre de un Pokémon rival en los mensajes de combate, en español:
// "El Pikachu salvaje", "el Pikachu enemigo".
u32 Dualocke_CopiarArticuloES(u8 *dst, u32 dstID, bool32 mayuscula);
void Dualocke_AnadirSufijoES(u8 *nombre, bool32 entrenador);

// "de el " -> "del " y "a el " -> "al " en un mensaje ya montado. Devuelve la nueva longitud.
u32 Dualocke_ContraccionesES(u8 *str);

#endif // GUARD_DUALOCKE_ES_H
