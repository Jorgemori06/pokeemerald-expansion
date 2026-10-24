"""
Dualocke: randomizer de los Pokémon salvajes.

Reglas (randomizer_config.json, "salvajes"; decididas por Miguel):
- Mapeo 1 a 1 por zona: en cada mapa, cada especie original se cambia por una línea al azar,
  la misma en hierba, agua, pesca y Golpe Roca.
- Sin legendarios ni singulares.
- La especie se ajusta a la fase que le toca por el nivel (mismas reglas que los entrenadores).
  Así no hay un Garchomp a nivel 5 ni un Gible a nivel 60.
- Se evita repetir líneas entre zonas mientras queden sin usar.
- Se respetan los niveles: solo cambian las especies.

Solo se tocan los mapas de Hoenn (gWildMonHeaders). Los de Kanto (_FRLG), la Pirámide y el
Pike del Frente Batalla se quedan como están.
"""

import random

TIPOS_DE_ENCUENTRO = ("land_mons", "water_mons", "rock_smash_mons", "fishing_mons")


class Mazo:
    """Saca raíces sin repetir; cuando se acaban, vuelve a barajar todas."""

    def __init__(self, raices, rng):
        self.raices = list(raices)
        self.rng = rng
        self.pila = []

    def sacar(self, evitar=()):
        for _ in range(2):
            if not self.pila:
                self.pila = self.raices[:]
                self.rng.shuffle(self.pila)
            for i in range(len(self.pila) - 1, -1, -1):
                if self.pila[i] not in evitar:
                    return self.pila.pop(i)
            self.pila = []
        return self.rng.choice(self.raices)


def randomizar(datos, pokedex, semilla, config):
    """Cambia las especies de `datos` (el JSON de wild_encounters ya cargado).
    Devuelve el solucionario: {mapa: {especie original: raíz nueva}}."""
    rng = random.Random(f"{semilla}|salvajes")
    mazo = Mazo(pokedex.raices_validas(), rng)
    solucionario = {}

    for grupo in datos["wild_encounter_groups"]:
        if grupo.get("label") != "gWildMonHeaders":
            continue
        for encuentro in grupo["encounters"]:
            mapa = encuentro["map"]
            if mapa.endswith("_FRLG"):
                continue
            originales = []
            for tipo in TIPOS_DE_ENCUENTRO:
                for mon in encuentro.get(tipo, {}).get("mons", []):
                    if mon["species"] not in originales:
                        originales.append(mon["species"])
            if not originales:
                continue

            mapeo = {}
            for original in originales:
                mapeo[original] = mazo.sacar(evitar=set(mapeo.values()))
            solucionario[mapa] = mapeo

            for tipo in TIPOS_DE_ENCUENTRO:
                for mon in encuentro.get(tipo, {}).get("mons", []):
                    raiz = mapeo[mon["species"]]
                    # Misma rama para todas las apariciones de esa especie en el mapa
                    rng_rama = random.Random(f"{semilla}|salvajes|{mapa}|{raiz}")
                    if config.get("evolucion_segun_nivel", True):
                        mon["species"] = pokedex.evolucionar(raiz, mon["min_level"], rng_rama)
                    else:
                        mon["species"] = raiz
    return solucionario


def comprobar(original, randomizado, pokedex):
    """Comprueba que solo han cambiado las especies, que existen y que no hay legendarios.
    Devuelve una lista de errores (vacía si todo está bien)."""
    errores = []
    for g_o, g_r in zip(original["wild_encounter_groups"], randomizado["wild_encounter_groups"]):
        for e_o, e_r in zip(g_o["encounters"], g_r["encounters"]):
            for tipo in TIPOS_DE_ENCUENTRO:
                mons_o = e_o.get(tipo, {}).get("mons", [])
                mons_r = e_r.get(tipo, {}).get("mons", [])
                if len(mons_o) != len(mons_r):
                    errores.append(f"{e_o['map']} {tipo}: cambia el número de huecos")
                    continue
                for m_o, m_r in zip(mons_o, mons_r):
                    if (m_o["min_level"], m_o["max_level"]) != (m_r["min_level"], m_r["max_level"]):
                        errores.append(f"{e_o['map']} {tipo}: cambia el nivel")
                    especie = pokedex.especies.get(m_r["species"])
                    if especie is None:
                        errores.append(f"{e_o['map']} {tipo}: especie desconocida {m_r['species']}")
                    elif g_o.get("label") == "gWildMonHeaders" and not e_o["map"].endswith("_FRLG") \
                            and especie.es_legendaria:
                        errores.append(f"{e_o['map']} {tipo}: legendario {m_r['species']}")
    return errores
