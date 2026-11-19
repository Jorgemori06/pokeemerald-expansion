#ifndef GUARD_DUALOCKE_PRUEBA_H
#define GUARD_DUALOCKE_PRUEBA_H

// Dualocke: ROM de pruebas (make DUALOCKE_PRUEBA=1). La usa tools/dualocke/emulador/ para entrar en
// un mapa sin jugar: el emulador escribe en gDualockePrueba antes de "Nueva partida" y la partida
// empieza ahí, sin la charla de Abedul ni el camión, con medallas, objetos clave y un equipo con MO.
// En las ROMs normales no existe nada de esto.
#ifdef DUALOCKE_PRUEBA

#define DUALOCKE_PRUEBA_MAGIA 0x50525545 // "PRUE"

struct DualockePrueba
{
    u32 magia;
    u16 mapa;      // (grupo << 8) | número, como MAP_X
    s16 x;
    s16 y;
    u16 especie;   // la del equipo; 0 = Lapras
    u8 nivel;      // 0 = 70
    u8 sinEquipo;  // para probar con el equipo vacío
    u8 foto;       // para las fotos de la guía: cuevas con luz y sin lluvia, niebla ni tormenta de arena
};

extern struct DualockePrueba gDualockePrueba;

bool32 Dualocke_PruebaActiva(void);
bool32 Dualocke_PruebaFoto(void);
void Dualocke_PruebaNombre(void);
bool32 Dualocke_PruebaDestino(void);
void Dualocke_PruebaPreparar(void);

#endif // DUALOCKE_PRUEBA
#endif // GUARD_DUALOCKE_PRUEBA_H
