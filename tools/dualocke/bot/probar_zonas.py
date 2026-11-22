"""Recorre zonas con el bot y apunta qué pasa en cada una (para probar las zonas nuevas).

Uso, desde un estado guardado con Surf, Buceo, Cascada, Fuerza, Golpe Roca, Corte y Vuelo:
    python3 paso.py est/a.ss est/b.ss 'exec(open("probar_zonas.py").read()); zona(e, "MAP_CANTERA", ("MAP_CANTERA", 19, 23))'

Para cada zona: vuela a la ciudad desde la que se llega antes, va hasta la zona, busca el primer
Pokémon por la hierba, pelea con el guardián (si se le da) y vuelve a un Centro POKéMON andando, para
comprobar que no te quedas encerrado. Lo apunta todo en zonas.json, en la carpeta de la partida.

Para pasar a una ROM nueva la partida de otra (por ejemplo, la de después de la Liga), saca la partida
guardada del juego con la orden del emulador `sacar_sav` o del estado `.ss`, y métela con `meter_sav`
(reinicia la consola; luego "CONTINUAR")."""
import json
import os
import time

RES = os.path.join(P.AQUI, "zonas.json")  # noqa: F821 (P viene de paso.py)
CIUDADES = ["LITTLEROOT_TOWN", "OLDALE_TOWN", "PETALBURG_CITY", "RUSTBORO_CITY", "DEWFORD_TOWN", "SLATEPORT_CITY",
            "MAUVILLE_CITY", "VERDANTURF_TOWN", "FALLARBOR_TOWN", "LAVARIDGE_TOWN", "FORTREE_CITY", "LILYCOVE_CITY",
            "MOSSDEEP_CITY", "SOOTOPOLIS_CITY", "PACIFIDLOG_TOWN", "EVER_GRANDE_CITY"]


def _apunta(z, **k):
    d = json.load(open(RES)) if os.path.exists(RES) else {}
    d.setdefault(z, {}).update(k)
    json.dump(d, open(RES, "w"), indent=1, ensure_ascii=False)


def _ciudad_cercana(z):
    P.PUEDE_SURF[0] = P.PUEDE_BUCEAR[0] = P.PUEDE_CASCADA[0] = True  # noqa: F821
    mejor = None
    for nombre in CIUDADES:
        m, cen = "MAP_" + nombre, "MAP_" + nombre + "_POKEMON_CENTER_1F"
        if cen not in P.mundo().mapas:  # noqa: F821
            continue
        puerta = [(x, y) for (x, y), l in P.info_mapa(m)[3].items() if l[0][1]["dest_map"] == cen]  # noqa: F821
        if not puerta:
            continue
        x, y = puerta[0]
        c = P.planear((m, x, y + 1, 3), lambda s: s[0] == z, max_estados=150000)  # noqa: F821
        if c and (mejor is None or len(c) < mejor[0]):
            mejor = (len(c), "MAPSEC_" + nombre, m)
    return mejor


def zona(e, z, guardian=None, buscar=True, volar_antes=True):
    t0 = time.time()
    c = _ciudad_cercana(z) if volar_antes else None
    _apunta(z, ciudad=c and c[1], pasos=c and c[0])
    if c:
        try:
            volar(e, c[1])  # noqa: F821
        except Exception as err:
            cerrar_menus(e)  # noqa: F821
            _apunta(z, vuelo=str(err))
        curar(e, c[2] + "_POKEMON_CENTER_1F")  # noqa: F821
    try:
        ir(e, z)  # noqa: F821
        seguir(e)  # noqa: F821
        _apunta(z, llega=True, entrada=list(e.pos()))
        e.foto(os.path.join(P.AQUI, z + ".png"))  # noqa: F821
    except Exception as err:
        _apunta(z, llega=False, error=str(err), donde=[e.mapa(), list(e.pos())])
        raise
    if buscar and P.hierba(z):  # noqa: F821
        try:
            buscar_captura(e, z)  # noqa: F821
        except Exception as err:
            _apunta(z, captura_error=str(err))
        _apunta(z, zona_gastada=zona_usada(e, zona_de(z)))  # noqa: F821
    if guardian:
        gm, gx, gy = guardian
        v0 = var(e, "VAR_DUALOCKE_LIVES")  # noqa: F821
        e.no_huir = True
        try:
            hablar_con(e, gm, gx, gy)  # noqa: F821
            seguir(e)  # noqa: F821
            fl = next(o for o in P._mapa_json(gm)["object_events"] if o["x"] == gx and o["y"] == gy)["flag"]  # noqa: F821
            _apunta(z, guardian_vencido=flag(e, fl), vidas=[v0, var(e, "VAR_DUALOCKE_LIVES")])  # noqa: F821
        except Exception as err:
            _apunta(z, guardian_error=str(err), donde=[e.mapa(), list(e.pos())])
        finally:
            e.no_huir = False
    try:
        cen = centro_cercano(e)  # noqa: F821
        curar(e, cen)  # noqa: F821
        _apunta(z, sale=True, vuelve_a=cen)
    except Exception as err:
        _apunta(z, sale=False, salida_error=str(err), donde=[e.mapa(), list(e.pos())])
    _apunta(z, segundos=round(time.time() - t0))
