"""
Dualocke: datos de las especies para el randomizer.

En vez de leer src/data/pokemon/species_info/*.h a mano (tienen #if, macros y formas), se pasa
src/pokemon.c por el preprocesador de C con la misma configuración que al compilar. Así salen
exactamente las especies, evoluciones y formas que lleva la ROM.
"""

import os
import re
import subprocess
import tempfile

# Evoluciones que no son por nivel (piedra, amistad, lugar...): la primera a partir de este
# nivel y la segunda a partir del otro. Son las mismas reglas que usa Miguel para los
# entrenadores (tools/dualocke/evolucionar_entrenadores.py y randomizer_config.json).
NIVEL_SIN_NIVEL_PRIMERA = 30
NIVEL_SIN_NIVEL_SEGUNDA = 40

REGION_DEL_JUEGO = "REGION_HOENN"


class Especie:
    def __init__(self, nombre):
        self.nombre = nombre            # SPECIES_X
        self.tipos = []                 # [TYPE_X, TYPE_Y]
        self.flags = set()              # isMythical, isMegaEvolution...
        self.evoluciones = []           # [(nivel o None, SPECIES_Y)]: las que se usan al evolucionar
        self.destinos = []              # todas las evoluciones, sea cual sea el método
        self.tabla_formas = None        # nombre de la tabla de formas, si tiene
        self.megas = []                 # [(SPECIES_X_MEGA, ITEM_XITE)] si megaevoluciona con objeto
        self.nombre_es = ""

    @property
    def es_legendaria(self):
        return bool(self.flags & {"isRestrictedLegendary", "isSubLegendary", "isMythical"})


def _cuerpo_entre_llaves(texto, inicio):
    """Devuelve el texto entre la llave que abre en `inicio` y su llave de cierre."""
    profundidad = 0
    for i in range(inicio, len(texto)):
        if texto[i] == "{":
            profundidad += 1
        elif texto[i] == "}":
            profundidad -= 1
            if profundidad == 0:
                return texto[inicio + 1:i]
    raise ValueError("llaves sin cerrar")


def _preprocesar(cpp, cppflags):
    """Pasa src/pokemon.c por el preprocesador. Si falta alguna cabecera que se genera más tarde
    en la compilación (los movimientos que se enseñan, por ejemplo), se pone una vacía en una
    carpeta temporal: no hace falta para leer las especies."""
    with tempfile.TemporaryDirectory() as vacias:
        for _ in range(20):
            orden = [cpp] + cppflags + ["-iquote", vacias, "-P", "src/pokemon.c"]
            r = subprocess.run(orden, capture_output=True, text=True)
            if r.returncode == 0:
                return r.stdout
            falta = re.search(r"fatal error: ([^:]+\.h): No such file or directory", r.stderr)
            if not falta:
                break
            ruta = os.path.join(vacias, falta.group(1))
            os.makedirs(os.path.dirname(ruta), exist_ok=True)
            open(ruta, "w").close()
        raise RuntimeError("Dualocke: no se pudo preprocesar src/pokemon.c:\n" + r.stderr[-2000:])


def _evolucion_valida_en_hoenn(condiciones):
    for cond, valor in re.findall(r"\{(IF_\w+),\s*([^}]*)\}", condiciones):
        valor = valor.strip()
        if cond == "IF_REGION" and valor != REGION_DEL_JUEGO:
            return False
        if cond == "IF_NOT_REGION" and valor == REGION_DEL_JUEGO:
            return False
    return True


def _leer_evoluciones(cuerpo):
    m = re.search(r"\.evolutions\s*=\s*\(const struct Evolution\[\]\)\s*\{", cuerpo)
    if not m:
        return [], []
    lista_txt = _cuerpo_entre_llaves(cuerpo, m.end() - 1)
    evos, todas = [], []
    # Cada evolución es {METODO, PARAM, SPECIES_X[, CONDICIONES]}
    i = 0
    while True:
        i = lista_txt.find("{", i)
        if i == -1:
            break
        entrada = _cuerpo_entre_llaves(lista_txt, i)
        i += len(entrada) + 2
        partes = entrada.split(",", 3)
        if len(partes) < 3 or not partes[0].strip().startswith("EVO_"):
            continue
        metodo, param, destino = (p.strip() for p in partes[:3])
        condiciones = partes[3] if len(partes) > 3 else ""
        if not destino.startswith("SPECIES_"):
            continue
        todas.append(destino)
        if not _evolucion_valida_en_hoenn(condiciones):
            continue
        # Mismas reglas que los entrenadores: por nivel si es EVO_LEVEL con nivel; si no,
        # cuenta como "sin nivel" (piedra, amistad, intercambio convertido...)
        if metodo == "EVO_LEVEL" and param.isdigit() and int(param) > 0:
            evos.append((int(param), destino))
        elif metodo in ("EVO_LEVEL", "EVO_ITEM"):
            evos.append((None, destino))
    return evos, todas


def leer_especies(cpp="arm-none-eabi-cpp", cppflags=None):
    """Devuelve ({SPECIES_X: Especie}, {tabla: [SPECIES_X, ...]}, {alias: SPECIES_X})."""
    if cppflags is None:
        cppflags = ["-iquote", "include", "-Wno-trigraphs", "-DMODERN=1", "-DTESTING=0",
                    "-DEMERALD", "-std=gnu17"]
    texto = _preprocesar(cpp, cppflags)

    tablas = {}

    # Alias del enum (SPECIES_ALCREMIE = SPECIES_ALCREMIE_STRAWBERRY_VANILLA_CREAM...): las
    # evoluciones usan el alias y gSpeciesInfo el nombre largo
    alias = {}
    with open("include/constants/species.h", encoding="utf-8") as f:
        for a, b in re.findall(r"^\s*(SPECIES_\w+)\s*=\s*(SPECIES_\w+)\s*,", f.read(), re.M):
            alias[a] = b

    # Formas que solo existen en combate (Zen, Filo, megas...): no pueden salir tal cual.
    # Y las megas de cada tabla (megaevolución con objeto: la especie mega y su megapiedra).
    formas_de_combate = set()
    megas_por_tabla = {}
    for m in re.finditer(r"static const struct FormChange (s\w+FormChangeTable)\[\]\s*=\s*\{", texto):
        cuerpo = _cuerpo_entre_llaves(texto, m.end() - 1)
        for tipo, destino, resto in re.findall(r"\{\s*(FORM_CHANGE_\w+)\s*,\s*(SPECIES_\w+)\s*,?\s*([^}]*)\}", cuerpo):
            destino = alias.get(destino, destino)
            if tipo.startswith("FORM_CHANGE_BATTLE_"):
                formas_de_combate.add(destino)
            if tipo == "FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM":
                objeto = re.search(r"ITEM_\w+", resto)
                if objeto:
                    megas_por_tabla.setdefault(m.group(1), []).append((destino, objeto.group(0)))

    for m in re.finditer(r"static const u16 (s\w+FormSpeciesIdTable)\[\]\s*=\s*\{", texto):
        cuerpo = _cuerpo_entre_llaves(texto, m.end() - 1)
        tablas[m.group(1)] = [alias.get(s, s) for s in re.findall(r"SPECIES_\w+", cuerpo)]

    inicio = texto.index("const struct SpeciesInfo gSpeciesInfo[] =")
    bloque = _cuerpo_entre_llaves(texto, texto.index("{", inicio))
    especies = {}
    for m in re.finditer(r"\[(SPECIES_\w+)\]\s*=\s*\{", bloque):
        cuerpo = _cuerpo_entre_llaves(bloque, m.end() - 1)
        e = Especie(m.group(1))
        tipos = re.search(r"\.types\s*=\s*\{([^}]*)\}", cuerpo)
        if tipos:
            e.tipos = re.findall(r"TYPE_\w+", tipos.group(1))[-2:] or []
        e.flags = set(re.findall(r"\.(is\w+)\s*=\s*(?:TRUE|1)\b", cuerpo))
        evos, todas = _leer_evoluciones(cuerpo)
        # evoluciones: las que se usan para evolucionar según el nivel (por nivel, piedra o
        # amistad); destinos: todas, para saber qué especies son de la misma línea
        e.evoluciones = [(lv, alias.get(d, d)) for lv, d in evos]
        e.destinos = [alias.get(d, d) for d in todas]
        if e.nombre in formas_de_combate:
            e.flags.add("formaDeCombate")
        cambios = re.search(r"\.formChangeTable\s*=\s*(s\w+)", cuerpo)
        if cambios and "isMegaEvolution" not in e.flags:
            e.megas = megas_por_tabla.get(cambios.group(1), [])
        formas = re.search(r"\.formSpeciesIdTable\s*=\s*(s\w+)", cuerpo)
        e.tabla_formas = formas.group(1) if formas else None
        nombre = re.search(r'\.speciesName\s*=\s*_\("([^"]*)"\)', cuerpo)
        e.nombre_es = nombre.group(1) if nombre else ""
        especies[e.nombre] = e
    return especies, tablas, alias


class Pokedex:
    """Especies, líneas evolutivas y reglas de evolución por nivel."""

    def __init__(self, especies, tablas, alias=None):
        self.especies = especies
        self.tablas = tablas
        self.alias = alias or {}
        self.preevo = {}
        for e in especies.values():
            for destino in e.destinos:
                if destino in especies:
                    self.preevo.setdefault(destino, e.nombre)

    def forma_base(self, nombre):
        e = self.especies.get(nombre)
        if e and e.tabla_formas and self.tablas.get(e.tabla_formas):
            return self.tablas[e.tabla_formas][0]
        return nombre

    def es_forma_normal(self, nombre):
        """Especie que puede salir tal cual: la forma base o una forma regional."""
        e = self.especies[nombre]
        if e.flags & {"isMegaEvolution", "isGigantamax", "isTotem", "isPrimalReversion",
                      "isUltraBurst", "isTeraForm", "formaDeCombate"}:
            return False
        if self.forma_base(nombre) == nombre:
            return True
        return bool(e.flags & {"isAlolanForm", "isGalarianForm", "isHisuianForm", "isPaldeanForm"})

    def raiz(self, nombre):
        vistos = set()
        while nombre in self.preevo and nombre not in vistos:
            vistos.add(nombre)
            nombre = self.preevo[nombre]
        return nombre

    def linea(self, raiz):
        """Todas las especies de una línea, desde su raíz."""
        resultado, pendientes = [], [raiz]
        while pendientes:
            n = pendientes.pop(0)
            if n in resultado or n not in self.especies:
                continue
            resultado.append(n)
            pendientes += self.especies[n].destinos
        return resultado

    def raices_validas(self, con_legendarios=False):
        """Raíces de línea que pueden salir en salvajes y entrenadores normales:
        formas normales, sin legendarios ni singulares en la línea (salvo con_legendarios)."""
        raices = []
        for nombre in self.especies:
            if nombre in ("SPECIES_NONE", "SPECIES_EGG") or nombre in self.preevo:
                continue
            if not self.es_forma_normal(nombre) or not self.especies[nombre].nombre_es:
                continue
            linea = self.linea(nombre)
            if not con_legendarios and any(self.especies[n].es_legendaria for n in linea):
                continue
            raices.append(nombre)
        return sorted(raices)

    def evolucionar(self, nombre, nivel, rng):
        """Evoluciona la especie según el nivel. Si hay varias ramas posibles, elige una al azar."""
        while True:
            e = self.especies[nombre]
            opciones = []
            for lv, destino in e.evoluciones:
                if destino not in self.especies or not self.es_forma_normal(destino):
                    continue
                if lv is None:
                    lv = NIVEL_SIN_NIVEL_SEGUNDA if nombre in self.preevo else NIVEL_SIN_NIVEL_PRIMERA
                if nivel >= lv and destino not in opciones:
                    opciones.append(destino)
            if not opciones:
                return nombre
            nombre = rng.choice(opciones)
