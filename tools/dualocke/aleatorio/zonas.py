"""
Dualocke: mapas de las zonas nuevas (ZONAS.md; Miguel, 16/11/2026).

Ninguno tenía salvajes ni objetos del suelo en las partidas ya empezadas. Lo suyo se sortea con
su propio generador, después de todo lo demás, para que con la misma semilla lo de siempre salga
igual (Jorge, 16/11/2026). Sin esto, como los mapas se recorren por orden alfabético, un objeto
nuevo en la ISLA LEJANA cambiaba todos los objetos de los mapas que van detrás (y la Recogida, y
lo que piden los intercambios).

Al añadir una zona nueva, se ponen aquí el prefijo de sus mapas (salvajes) y el de los flags de
sus objetos (los de su grupo en colocar_objetos.py). Los objetos van por flag y no por mapa
porque algún mapa de estas zonas ya tenía uno (la Ceniza Sagrada oculta de ROCA OMBLIGO).
"""

PREFIJOS = (
    "SouthernIsland_", "FarawayIsland_", "BirthIsland_", "NavelRock_",   # islas del ferry (#81)
    "GrutaIgnea",                                                         # GRUTA ÍGNEA (#82)
    "IslaNevada",                                                         # ISLA NEVADA (#83)
    "DesiertoProfundo", "RuinasArenosas",                                 # DESIERTO PROFUNDO y RUINAS (#84)
    "MarismaAzuliza",                                                     # MARISMA AZULIZA (#87)
    "BosqueFrondoso", "MansionOlvidada",                                  # BOSQUE FRONDOSO y MANSIÓN (#88)
    "IslaDeRuinas", "IslaVolcanica", "IslaArenosa",                       # islas de las rutas del sur (#89)
    "PlayaVolcanica",                                                     # PLAYA VOLCÁNICA (#90)
    "CumbreMeteoro",                                                      # CUMBRE METEORO (#91)
    "BosqueSiniestro",                                                    # BOSQUE SINIESTRO (#96)
    "CienagaToxica",                                                      # CIÉNAGA TÓXICA (#98)
    "Cantera",                                                            # CANTERA (21/11/2026)
    "PradoHadas",                                                         # PRADO DE HADAS (21/11/2026)
)

# Flags de los objetos de las zonas nuevas (GRUPOS de colocar_objetos.py)
FLAGS_OBJETOS = ("FLAG_ITEM_ISLA_", "FLAG_ITEM_GRUTA_", "FLAG_ITEM_NEVADA_", "FLAG_ITEM_DESIERTO_",
                 "FLAG_ITEM_MARISMA_", "FLAG_ITEM_BOSQUE_", "FLAG_ITEM_SUR_", "FLAG_ITEM_PLAYA_",
                 "FLAG_ITEM_CUMBRE_", "FLAG_ITEM_SINIESTRO_", "FLAG_ITEM_CIENAGA_",
                 "FLAG_ITEM_CANTERA_", "FLAG_ITEM_PRADO_")


def es_nueva(nombre_mapa):
    """nombre_mapa: el "name" del map.json (SouthernIsland_Exterior) o la etiqueta de los
    salvajes sin la g (gSouthernIsland_Exterior también vale)."""
    if nombre_mapa.startswith("g") and nombre_mapa[1:2].isupper():
        nombre_mapa = nombre_mapa[1:]
    return nombre_mapa.startswith(PREFIJOS)
