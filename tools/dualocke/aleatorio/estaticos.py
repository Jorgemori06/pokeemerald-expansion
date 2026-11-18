"""
Dualocke: estáticos y regalos aleatorios.

Decidido por Jorge (25/10/2026):
- Estáticos (los combates con setwildbattle: Kecleon, Voltorb, Electrode, Regis, Groudon,
  Kyogre, Rayquaza, Sudowoodo; y los errantes Latios/Latias): **todo al azar**, cualquier
  especie, legendarios incluidos. Cada especie original cambia por la misma en todos sus
  sitios: todos los Kecleon del Detector son la misma especie nueva.
- Regalos (Beldum, fósiles, Castform, iniciales de Johto, huevos de Wynaut y Pichu): al azar,
  sin legendarios, ajustados a su nivel. Los huevos, siempre la forma base.
- El sprite del mapa sigue siendo el del original (da igual: se descubre al empezar el combate).

Islas del ferry (Miguel, 16/11/2026; data/scripts/dualocke_islas.inc): en vez de los legendarios, cada
isla tiene un Pokémon fuerte que se puede capturar. Con semilla sale otro fuerte: de una línea que
acaba en 600 o más de estadísticas base (las pseudolegendarias) o con mega (también las formas
Gigamax). Se sortean aparte, con su propio RNG, para no cambiar los demás estáticos ni los regalos de
las semillas en curso, y sin repetir con ellos. En esas islas el sprite sí coincide
(Dualocke_GraficoPokemonIsla).

No se tocan los scripts: el juego cambia la especie al vuelo con la tabla que se genera aquí
(src/data/dualocke_aleatorio.h, la escribe cabecera.py y la usa src/dualocke_aleatorio.c).
"""

import glob
import random
import re

ERRANTES = ("SPECIES_LATIAS", "SPECIES_LATIOS")  # src/roamer.c (InitRoamer)
# Mapas con el Pokémon fuerte de las islas del ferry: van aparte (islas())
MAPAS_ISLAS = ("SouthernIsland_Interior", "FarawayIsland_Interior", "BirthIsland_Exterior",
               "NavelRock_Top", "NavelRock_Bottom",
               # Los guardianes de las zonas nuevas, igual
               "RuinasArenosas_Camara", "GrutaIgnea_Camara", "IslaNevada_Cueva", "MansionOlvidada_Desvan",
               "IslaDeRuinas_Torre", "IslaVolcanica_Crater", "IslaArenosa",
               "PlayaVolcanica", "CumbreMeteoro", "MarismaAzuliza", "BosqueSiniestro",
               "CienagaToxica")


def _nivel_errantes():
    """Nivel de los errantes en src/roamer.c: DUALOCKE_NIVEL_ERRANTE (Miguel, #31) o el número
    que se pase a TryAddRoamer."""
    with open("src/roamer.c", encoding="utf-8") as f:
        texto = f.read()
    m = re.search(r"#define\s+DUALOCKE_NIVEL_ERRANTE\s+(\d+)", texto) \
        or re.search(r"TryAddRoamer\(SPECIES_LATI[AO]S,\s*(\d+)\)", texto)
    return int(m.group(1)) if m else 40


def _scripts_de_hoenn():
    archivos = sorted(glob.glob("data/maps/*/scripts.inc")) + sorted(glob.glob("data/scripts/*.inc"))
    return [a for a in archivos if "_Frlg" not in a and not a.endswith("debug.inc")
            and not any(f"/{m}/" in a.replace("\\", "/") for m in MAPAS_ISLAS)]


def buscar(alias):
    """Devuelve ({especie estática: nivel máximo}, {especie regalo: nivel}, {especie huevo})."""
    estaticos, regalos, huevos = dict.fromkeys(ERRANTES, _nivel_errantes()), {}, set()
    for archivo in _scripts_de_hoenn():
        with open(archivo, encoding="utf-8") as f:
            texto = f.read()
        for especie, nivel in re.findall(r"^\s*setwildbattle\s+(SPECIES_\w+)\s*,\s*(\d+)", texto, re.M):
            especie = alias.get(especie, especie)
            estaticos[especie] = max(estaticos.get(especie, 0), int(nivel))
        for especie, nivel in re.findall(r"^\s*givemon\s+(SPECIES_\w+)\s*,\s*(\d+)", texto, re.M):
            especie = alias.get(especie, especie)
            regalos[especie] = max(regalos.get(especie, 0), int(nivel))
        for especie in re.findall(r"^\s*giveegg\s+(SPECIES_\w+)", texto, re.M):
            huevos.add(alias.get(especie, especie))
    return estaticos, regalos, huevos


def randomizar(pokedex, semilla):
    """Devuelve ({original: nueva} de estáticos, {original: nueva} de regalos y huevos)."""
    estaticos, regalos, huevos = buscar(pokedex.alias)
    rng = random.Random(f"{semilla}|estaticos")
    todas = pokedex.raices_validas(con_legendarios=True)
    sin_legendarios = pokedex.raices_validas()

    mapa_estaticos, usadas = {}, set()
    for original in sorted(estaticos):
        raiz = rng.choice([r for r in todas if r not in usadas] or todas)
        usadas.add(raiz)
        mapa_estaticos[original] = pokedex.evolucionar(raiz, estaticos[original], rng)

    mapa_regalos = {}
    for original in sorted(regalos):
        raiz = rng.choice([r for r in sin_legendarios if r not in usadas] or sin_legendarios)
        usadas.add(raiz)
        mapa_regalos[original] = pokedex.evolucionar(raiz, regalos[original], rng)
    for original in sorted(huevos):
        raiz = rng.choice([r for r in sin_legendarios if r not in usadas] or sin_legendarios)
        usadas.add(raiz)
        mapa_regalos[original] = raiz
    mapa_estaticos.update(islas(pokedex, semilla, usadas))
    mapa_regalos.update(fosiles(pokedex, semilla, usadas))
    return mapa_estaticos, mapa_regalos


def _es_fuerte(pokedex, raiz):
    """Línea que acaba en 600 o más de estadísticas base, o con mega."""
    final = pokedex.evolucionar(raiz, 100, random.Random(0))
    datos = pokedex.especies[final]
    return sum(datos.stats.values()) >= 600 or bool(datos.megas)


def islas(pokedex, semilla, usadas):
    """{original: nueva} de los Pokémon fuertes de las islas del ferry."""
    estaticos = {}
    for carpeta in MAPAS_ISLAS:
        with open(f"data/maps/{carpeta}/scripts.inc", encoding="utf-8") as f:
            texto = f.read()
        for especie, nivel in re.findall(r"^\s*setwildbattle\s+(SPECIES_\w+)\s*,\s*(\d+)", texto, re.M):
            especie = pokedex.alias.get(especie, especie)
            estaticos[especie] = max(estaticos.get(especie, 0), int(nivel))
    fuertes = [r for r in pokedex.raices_validas() if _es_fuerte(pokedex, r)]
    rng = random.Random(f"{semilla}|estaticos|islas")
    resultado = {}
    for original in sorted(estaticos):
        raiz = rng.choice([r for r in fuertes if r not in usadas] or fuertes)
        usadas.add(raiz)
        resultado[original] = pokedex.evolucionar(raiz, estaticos[original], rng)
    return resultado


NIVEL_FOSIL = 20  # como el Fósil Raíz y el Fósil Garra


def fosiles(pokedex, semilla, usadas):
    """{original: nueva} de los fósiles de otras generaciones que revive DEVON (src/data/dualocke_fosiles.h).
    Se sortean aparte, con su propio RNG y después de todo lo demás, para no cambiar los regalos ni los
    estáticos de las semillas en curso (se añadieron el 18/11/2026, con la versión 8 ya empezada)."""
    with open("src/data/dualocke_fosiles.h", encoding="utf-8") as f:
        originales = re.findall(r"\{\s*ITEM_\w+\s*,\s*(SPECIES_\w+)\s*\}", f.read())
    sin_legendarios = pokedex.raices_validas()
    rng = random.Random(f"{semilla}|estaticos|fosiles")
    resultado = {}
    for original in originales:
        original = pokedex.alias.get(original, original)
        raiz = rng.choice([r for r in sin_legendarios if r not in usadas] or sin_legendarios)
        usadas.add(raiz)
        resultado[original] = pokedex.evolucionar(raiz, NIVEL_FOSIL, rng)
    return resultado
