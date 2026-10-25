"""
Dualocke: randomizer de los equipos de los entrenadores (src/data/trainers.party).

Reglas (randomizer_config.json, "entrenadores" y "jefes"; decididas por Miguel):
- Se respetan los niveles y el tamaño de los equipos (los pone Miguel): solo cambian las especies.
- Especies al azar, sin repetir dentro de un equipo, evolucionadas según el nivel (mismas
  reglas que los salvajes) y con formas regionales.
- Sin legendarios, salvo en los jefes de la Liga (Alto Mando y Plubio).
- Jefes: el equipo es al azar, pero el as (el último) es de su tipo o temática. Los marcados
  "con_mega_desde_el_aro" llevan como as una especie con mega de ese tipo y su megapiedra.
- Las revanchas del mismo entrenador (_2, _3...) usan las mismas líneas que el primer combate,
  evolucionadas a su nivel, como en el juego original.
- Máximo en la Ruta 120 (TRAINER_STEVEN_ROUTE_120) tiene equipo fijo: no se toca.
- El rival se queda como está hasta que se randomicen los iniciales (va con su inicial).

Al cambiar la especie se quitan los movimientos, la habilidad y el sexo que tenía escritos (no
valdrían para la nueva): sale con los movimientos de su nivel y una habilidad normal. Se
mantienen el nivel, el objeto, los IVs/EVs y la naturaleza.
"""

import random
import re

FIJOS = {"TRAINER_STEVEN_ROUTE_120", "TRAINER_NONE"}
JEFES_LIGA = {"TRAINER_SIDNEY", "TRAINER_PHOEBE", "TRAINER_GLACIA", "TRAINER_DRAKE", "TRAINER_WALLACE"}
RIVAL = re.compile(r"TRAINER_(MAY|BRENDAN)_")
CAMPOS_QUE_SE_QUITAN = ("Ability:", "- ")


def _familia(trainer):
    """TRAINER_ROXANNE_1 y TRAINER_ROXANNE_3 son la misma familia (revanchas)."""
    return re.sub(r"_\d+$", "", trainer)


def _a_constante(nombre, alias=None):
    alias = alias or {}
    if nombre.startswith("SPECIES_"):
        return alias.get(nombre, nombre)
    n = nombre.upper().replace("♀", "_F").replace("♂", "_M").replace("É", "E")
    n = re.sub(r"[ \-]", "_", n)
    n = re.sub(r"[^A-Z0-9_]", "", n)
    return alias.get("SPECIES_" + n, "SPECIES_" + n)


def _leer(texto):
    """Divide el archivo en [cabecera, (TRAINER, bloque), (TRAINER, bloque), ...]."""
    partes = re.split(r"^(=== TRAINER_\w+ ===)[ \t]*$", texto, flags=re.M)
    resultado = [partes[0]]
    for i in range(1, len(partes), 2):
        resultado.append((partes[i], partes[i + 1]))
    return resultado


def _pokemons(bloque):
    """Separa el bloque de un entrenador en cabecera y Pokémon (por líneas en blanco)."""
    trozos = re.split(r"\n[ \t]*\n", bloque)
    return trozos


def _linea_especie(trozo):
    lineas = trozo.strip("\n").split("\n")
    return lineas, lineas[0] if lineas else ""


def _especie_y_objeto(primera):
    m = re.match(r"^\s*([^@(]+?)\s*(?:\((M|F)\))?\s*(?:@\s*(.+?))?\s*$", primera)
    if not m:
        return None, None
    return m.group(1).strip(), (m.group(3) or "").strip()


def _nivel(lineas):
    for l in lineas:
        m = re.match(r"^\s*Level:\s*(\d+)", l)
        if m:
            return int(m.group(1))
    return 100


def _reescribir(lineas, nueva, objeto):
    primera = nueva + (f" @ {objeto}" if objeto else "")
    resto = [l for l in lineas[1:] if not l.strip().startswith(CAMPOS_QUE_SE_QUITAN)]
    return "\n".join([primera] + resto)


class Generador:
    def __init__(self, pokedex, semilla, config):
        self.pokedex = pokedex
        self.semilla = semilla
        self.config = config
        self.raices = pokedex.raices_validas()
        self.raices_liga = pokedex.raices_validas(con_legendarios=True)
        self.lineas_familia = {}   # (familia, especie original) -> raíz nueva

    def _tipos(self, especie):
        return set(self.pokedex.especies[especie].tipos)

    def _raiz_para(self, familia, original, raices, usadas, rng):
        clave = (familia, original)
        raiz = self.lineas_familia.get(clave)
        if raiz is None or raiz in usadas:
            opciones = [r for r in raices if r not in usadas]
            raiz = rng.choice(opciones)
            self.lineas_familia.setdefault(clave, raiz)
        return raiz

    def _as_de_jefe(self, trainer, familia, original, nivel, tipos, con_mega, raices, usadas, rng):
        """Raíz y especie del as: de uno de `tipos` y, si toca, con mega (y su megapiedra)."""
        clave = (familia, "AS")
        candidatos = []
        for raiz in raices:
            if raiz in usadas:
                continue
            especie = self.pokedex.evolucionar(raiz, nivel, random.Random(f"{self.semilla}|{familia}|{raiz}"))
            if not (self._tipos(especie) & set(tipos)):
                continue
            if con_mega and not self.pokedex.especies[especie].megas:
                continue
            candidatos.append((raiz, especie))
        if not candidatos:
            return None
        previa = self.lineas_familia.get(clave)
        elegido = next((c for c in candidatos if c[0] == previa), None) or rng.choice(candidatos)
        self.lineas_familia.setdefault(clave, elegido[0])
        return elegido

    def randomizar(self, texto):
        cfg_jefes = self.config.get("jefes", {})
        as_por_tipo = {k: ["TYPE_" + t for t in v] for k, v in cfg_jefes.get("as_por_tipo", {}).items()
                       if k.startswith("TRAINER_")}
        con_mega = set(cfg_jefes.get("con_mega_desde_el_aro", []))
        solucionario = {}
        partes = _leer(texto)
        salida = [partes[0]]
        for cabecera, bloque in partes[1:]:
            trainer = cabecera[4:-4]
            familia = _familia(trainer)
            if trainer in FIJOS or "PLACEHOLDER" in trainer or RIVAL.match(trainer):
                salida.append(cabecera + bloque)
                continue
            # El tipo del as y la mega valen también para las revanchas del mismo jefe
            tipos_as = as_por_tipo.get(trainer) or as_por_tipo.get(familia + "_1")
            mega_as = trainer in con_mega or (familia + "_1") in con_mega
            raices = self.raices_liga if familia in JEFES_LIGA else self.raices
            rng = random.Random(f"{self.semilla}|entrenadores|{trainer}")

            trozos = _pokemons(bloque)
            # trozos[0] es lo que hay entre la cabecera y el primer Pokémon (los datos del
            # entrenador); el resto, un Pokémon por trozo
            indices = [i for i in range(1, len(trozos)) if trozos[i].strip()]
            usadas = set()
            cambios = []
            for n, i in enumerate(indices):
                lineas, primera = _linea_especie(trozos[i])
                nombre, objeto = _especie_y_objeto(primera)
                if not nombre:
                    continue
                original = _a_constante(nombre, self.pokedex.alias)
                if original not in self.pokedex.especies:
                    continue
                nivel = _nivel(lineas)
                es_as = (n == len(indices) - 1) and tipos_as
                elegido = None
                if es_as:
                    elegido = self._as_de_jefe(trainer, familia, original, nivel, tipos_as,
                                               mega_as, raices, usadas, rng)
                if elegido:
                    raiz, nueva = elegido
                    if mega_as:
                        objeto = self.pokedex.especies[nueva].megas[0][1]
                else:
                    raiz = self._raiz_para(familia, original, raices, usadas, rng)
                    nueva = self.pokedex.evolucionar(raiz, nivel, random.Random(f"{self.semilla}|{familia}|{raiz}"))
                usadas.add(raiz)
                trozos[i] = _reescribir(lineas, nueva, objeto)
                cambios.append(nueva)
            solucionario[trainer] = cambios
            salida.append(cabecera + "\n\n".join(trozos))
        return "".join(salida), solucionario


def comprobar(original, randomizado, pokedex):
    """Mismos entrenadores, mismo tamaño de equipo y mismos niveles; especies que existen."""
    errores = []
    a, b = _leer(original), _leer(randomizado)
    if len(a) != len(b):
        return ["cambia el número de entrenadores"]
    for (cab_a, blo_a), (cab_b, blo_b) in zip(a[1:], b[1:]):
        if cab_a != cab_b:
            errores.append(f"{cab_a}: cambia el orden")
            continue
        mons_a = [t for t in _pokemons(blo_a)[1:] if t.strip()]
        mons_b = [t for t in _pokemons(blo_b)[1:] if t.strip()]
        if len(mons_a) != len(mons_b):
            errores.append(f"{cab_a}: cambia el tamaño del equipo")
            continue
        vistas = []
        for ta, tb in zip(mons_a, mons_b):
            la, lb = ta.strip("\n").split("\n"), tb.strip("\n").split("\n")
            if _nivel(la) != _nivel(lb):
                errores.append(f"{cab_a}: cambia un nivel")
            nombre, _ = _especie_y_objeto(lb[0])
            especie = pokedex.especies.get(_a_constante(nombre or "", pokedex.alias))
            if especie is None:
                errores.append(f"{cab_a}: especie desconocida {nombre}")
            elif ta != tb and especie.es_legendaria and _familia(cab_a[4:-4]) not in JEFES_LIGA:
                errores.append(f"{cab_a}: legendario {nombre}")
    return errores
