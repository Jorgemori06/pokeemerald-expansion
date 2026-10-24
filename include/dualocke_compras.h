#ifndef GUARD_DUALOCKE_COMPRAS_H
#define GUARD_DUALOCKE_COMPRAS_H

// Dualocke (Items Clause): una unidad de cada objeto por tienda, salvo Balls, Repelentes,
// Bayas, Caramelos Raros y Cuerda Huida.
struct DualockeCompraLimitada
{
    u16 mapId;
    u16 item;
};

bool32 Dualocke_IsCompraLimitada(enum Item item);
bool32 Dualocke_YaComprado(enum Item item);
void Dualocke_MarcarComprado(enum Item item);

#endif // GUARD_DUALOCKE_COMPRAS_H
