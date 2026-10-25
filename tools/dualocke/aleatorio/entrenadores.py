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
- El rival lleva el inicial que gana al del jugador, evolucionado según el nivel, y el resto
  del equipo al azar (el mismo en todos sus combates). Desde Ciudad Calagua ("RIVAL_LILYCOVE"
  en con_mega_desde_el_aro) el as lleva mega: su inicial si tiene, y si no, una especie con mega
  del tipo de su inicial (y el inicial pasa al hueco anterior).

Al cambiar la especie se quitan los movimientos, la habilidad y el sexo que tenía escritos (no
valdrían para la nueva). Los movimientos nuevos los elige movimientos.py (3 de los que aprende
por nivel y el cuarto al azar) y la habilidad es la de su especie. Se mantienen el nivel, los
IVs/EVs y la naturaleza; el objeto también, salvo en los jefes, que llevan uno "coherente" (que
le sirva a ese Pokémon) en todo el equipo, menos la megapiedra del as.
"""

import random
import re

from . import movimientos as mov

FIJOS = {"TRAINER_STEVEN_ROUTE_120", "TRAINER_NONE"}
JEFES_LIGA = {"TRAINER_SIDNEY", "TRAINER_PHOEBE", "TRAINER_GLACIA", "TRAINER_DRAKE", "TRAINER_WALLACE"}
RIVAL = re.compile(r"TRAINER_(MAY|BRENDAN)_(\w+)_(TREECKO|TORCHIC|MUDKIP)$")
INICIALES_ORIGINALES = ["SPECIES_TREECKO", "SPECIES_TORCHIC", "SPECIES_MUDKIP"]
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


def _es_megapiedra(objeto):
    # Las megapiedras del rival original (Blazikenita...) no valen para otra especie
    return bool(objeto) and objeto.upper().replace(" ", "_").endswith(("ITE", "ITE_X", "ITE_Y"))


def _reescribir(lineas, nueva, objeto, movimientos=None):
    primera = nueva + (f" @ {objeto}" if objeto else "")
    resto = [l for l in lineas[1:] if not l.strip().startswith(CAMPOS_QUE_SE_QUITAN)]
    return "\n".join([primera] + resto + [f"- {m}" for m in (movimientos or [])])


# Objetos "coherentes" de los jefes (Miguel, PR #27): un objeto que le sirva a ese Pokémon
POTENCIADOR_DE_TIPO = {
    "TYPE_FIRE": "ITEM_CHARCOAL", "TYPE_WATER": "ITEM_MYSTIC_WATER", "TYPE_GRASS": "ITEM_MIRACLE_SEED",
    "TYPE_ELECTRIC": "ITEM_MAGNET", "TYPE_ICE": "ITEM_NEVER_MELT_ICE", "TYPE_FIGHTING": "ITEM_BLACK_BELT",
    "TYPE_POISON": "ITEM_POISON_BARB", "TYPE_GROUND": "ITEM_SOFT_SAND", "TYPE_FLYING": "ITEM_SHARP_BEAK",
    "TYPE_PSYCHIC": "ITEM_TWISTED_SPOON", "TYPE_BUG": "ITEM_SILVER_POWDER", "TYPE_ROCK": "ITEM_HARD_STONE",
    "TYPE_GHOST": "ITEM_SPELL_TAG", "TYPE_DRAGON": "ITEM_DRAGON_FANG", "TYPE_DARK": "ITEM_BLACK_GLASSES",
    "TYPE_STEEL": "ITEM_METAL_COAT", "TYPE_NORMAL": "ITEM_SILK_SCARF", "TYPE_FAIRY": "ITEM_FAIRY_FEATHER",
}


def objeto_coherente(especie, movimientos, datos_mov, rng, usados=()):
    """Un objeto que le sirva a `especie` con esos movimientos: Mineral Evolutivo si puede
    evolucionar; si no, según sus estadísticas (atacante físico o especial, rápido, resistente)."""
    st = especie.stats
    if especie.destinos:
        return "ITEM_EVIOLITE"
    danos = [datos_mov[m] for m in movimientos if m in datos_mov and datos_mov[m].de_dano]
    todo_dano = len(danos) == len(movimientos) and danos
    fisico = st.get("Attack", 0) >= st.get("SpAttack", 0) + 10
    especial = st.get("SpAttack", 0) >= st.get("Attack", 0) + 10
    opciones = ["ITEM_LIFE_ORB", "ITEM_EXPERT_BELT"]
    if fisico:
        opciones += ["ITEM_MUSCLE_BAND"] + (["ITEM_CHOICE_BAND"] if todo_dano else [])
    if especial:
        opciones += ["ITEM_WISE_GLASSES"] + (["ITEM_CHOICE_SPECS"] if todo_dano else [])
    if st.get("Speed", 0) >= 95:
        opciones += ["ITEM_FOCUS_SASH"] + (["ITEM_CHOICE_SCARF"] if todo_dano else [])
    if danos:
        opciones.append(POTENCIADOR_DE_TIPO.get(max(danos, key=lambda d: d.potencia).tipo, "ITEM_LIFE_ORB"))
    if st.get("HP", 0) + st.get("Defense", 0) + st.get("SpDefense", 0) >= 260:
        restos = "ITEM_BLACK_SLUDGE" if "TYPE_POISON" in especie.tipos else "ITEM_LEFTOVERS"
        opciones += [restos, restos, "ITEM_SITRUS_BERRY"]
        if st.get("Defense", 0) >= 100:
            opciones.append("ITEM_ROCKY_HELMET")
        if st.get("SpDefense", 0) >= 100 and todo_dano:
            opciones.append("ITEM_ASSAULT_VEST")
    libres = [o for o in opciones if o not in usados]
    return rng.choice(libres or opciones)


class Generador:
    def __init__(self, pokedex, semilla, config, iniciales=None, movimientos=None):
        self.pokedex = pokedex
        # Movimientos ({MOVE_X: Movimiento}); sin ellos, sale con los de su nivel (como antes)
        self.movs = movimientos
        self.todos = mov.validos(movimientos) if movimientos else []
        self.iniciales = iniciales or INICIALES_ORIGINALES
        self.semilla = semilla
        self.config = config
        self.raices = pokedex.raices_validas()
        self.raices_liga = pokedex.raices_validas(con_legendarios=True)
        self.lineas_familia = {}   # (familia, especie original) -> raíz nueva

    def _equipar(self, trainer, i, especie, nivel, objeto, jefe, usados):
        """Movimientos (todos los entrenadores) y objeto (los jefes, menos las megapiedras)."""
        if not self.movs:
            return None, objeto
        rng = random.Random(f"{self.semilla}|movimientos|{trainer}|{i}")
        cfg = self.config.get("entrenadores", {}).get("movimientos", {})
        tope = cfg.get("potencia_maxima_del_cuarto", {"base": 40, "por_nivel": 1.5})
        tope = (tope["base"], tope["por_nivel"]) if tope else None
        movimientos = mov.elegir(especie, nivel, self.pokedex, self.movs, self.todos, rng,
                                 cfg.get("garantizados", 3), tope)
        if jefe and not _es_megapiedra(objeto):
            objeto = objeto_coherente(self.pokedex.especies[especie], movimientos, self.movs, rng, usados)
        if objeto:
            usados.add(objeto)
        return movimientos, objeto

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

    def _rival(self, trainer, m, bloque, con_mega):
        """Equipo del rival: su inicial (el que gana al del jugador) y el resto al azar."""
        jugador = INICIALES_ORIGINALES.index("SPECIES_" + m.group(3))
        inicial_original = INICIALES_ORIGINALES[(jugador + 1) % 3]
        inicial_nuevo = self.iniciales[(jugador + 1) % 3]
        tipos_inicial = set(self.pokedex.especies[inicial_nuevo].tipos[:1])
        lugar = m.group(2)
        quiere_mega = f"RIVAL_{lugar}" in con_mega
        rng = random.Random(f"{self.semilla}|rival|{lugar}|{jugador}")

        trozos = _pokemons(bloque)
        indices = [i for i in range(1, len(trozos)) if trozos[i].strip()]
        datos = []
        for i in indices:
            lineas, primera = _linea_especie(trozos[i])
            nombre, objeto = _especie_y_objeto(primera)
            datos.append([i, lineas, _a_constante(nombre or "", self.pokedex.alias), objeto, _nivel(lineas)])

        usadas = {inicial_nuevo}
        nuevas = {}
        # El inicial: el hueco que tenía la línea del inicial original
        hueco_inicial = next((d for d in datos if _es_de_linea(self.pokedex, d[2], inicial_original)), None)
        if hueco_inicial:
            rng_rama = random.Random(f"{self.semilla}|rival|inicial")
            especie_inicial = self.pokedex.evolucionar(inicial_nuevo, hueco_inicial[4], rng_rama)
            nuevas[hueco_inicial[0]] = (especie_inicial, None)
            if quiere_mega:
                megas = self.pokedex.especies[especie_inicial].megas
                if megas:
                    nuevas[hueco_inicial[0]] = (especie_inicial, megas[0][1])
                else:
                    # Una especie con mega del tipo del inicial como as (el último hueco)
                    ultimo = datos[-1]
                    elegido = self._as_de_jefe(trainer, "RIVAL_MEGA", None, ultimo[4], tipos_inicial,
                                               True, self.raices, usadas, rng)
                    if elegido and len(datos) >= 2:
                        raiz, especie = elegido
                        usadas.add(raiz)
                        # El as con mega va al último hueco; si el inicial estaba ahí, pasa al anterior
                        if ultimo[0] == hueco_inicial[0]:
                            del nuevas[hueco_inicial[0]]
                            penultimo = datos[-2]
                            nuevas[penultimo[0]] = (self.pokedex.evolucionar(
                                inicial_nuevo, penultimo[4], random.Random(f"{self.semilla}|rival|inicial")), None)
                        nuevas[ultimo[0]] = (especie, self.pokedex.especies[especie].megas[0][1])
        # El resto, al azar y el mismo en todos los combates del rival
        for i, lineas, original, objeto, nivel in datos:
            if i in nuevas or original not in self.pokedex.especies:
                continue
            raiz = self._raiz_para("RIVAL", original, self.raices, usadas, rng)
            usadas.add(raiz)
            nuevas[i] = (self.pokedex.evolucionar(raiz, nivel, random.Random(f"{self.semilla}|RIVAL|{raiz}")), None)
        cambios = []
        usados = set()
        for i, lineas, original, objeto, nivel in datos:
            if i not in nuevas:
                cambios.append(original)
                continue
            especie, objeto_nuevo = nuevas[i]
            objeto = objeto_nuevo or ("" if objeto_nuevo is None and _es_megapiedra(objeto) else objeto)
            movimientos, objeto = self._equipar(trainer, i, especie, nivel, objeto, True, usados)
            trozos[i] = _reescribir(lineas, especie, objeto, movimientos)
            cambios.append(especie)
        return "\n\n".join(trozos), cambios

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
            if trainer in FIJOS or "PLACEHOLDER" in trainer:
                salida.append(cabecera + bloque)
                continue
            rival = RIVAL.match(trainer)
            if rival:
                bloque, solucionario[trainer] = self._rival(trainer, rival, bloque, con_mega)
                salida.append(cabecera + bloque)
                continue
            # El tipo del as y la mega valen también para las revanchas del mismo jefe
            tipos_as = as_por_tipo.get(trainer) or as_por_tipo.get(familia + "_1")
            mega_as = trainer in con_mega or (familia + "_1") in con_mega
            raices = self.raices_liga if familia in JEFES_LIGA else self.raices
            jefe = bool(tipos_as) or familia in JEFES_LIGA
            rng = random.Random(f"{self.semilla}|entrenadores|{trainer}")

            trozos = _pokemons(bloque)
            # trozos[0] es lo que hay entre la cabecera y el primer Pokémon (los datos del
            # entrenador); el resto, un Pokémon por trozo
            indices = [i for i in range(1, len(trozos)) if trozos[i].strip()]
            usadas = set()
            usados = set()
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
                movimientos, objeto = self._equipar(trainer, i, nueva, nivel, objeto, jefe, usados)
                trozos[i] = _reescribir(lineas, nueva, objeto, movimientos)
                cambios.append(nueva)
            solucionario[trainer] = cambios
            salida.append(cabecera + "\n\n".join(trozos))
        return "".join(salida), solucionario


def _es_de_linea(pokedex, especie, raiz):
    return especie in pokedex.linea(raiz)


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
