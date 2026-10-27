"""
Dualocke: objetos aleatorios (randomizer_config.json, "objetos" y "salvajes"; decidido por Miguel
en el PR #27, 25/10/2026).

- Objetos del suelo (Poké Balls del suelo y objetos ocultos de Hoenn):
  - Las megapiedras (flag FLAG_ITEM_MEGA_*) se quedan donde están, y ningún otro objeto del suelo
    puede ser una megapiedra.
  - Los objetos competitivos (FLAG_ITEM_COMP_*) son totalmente aleatorios, como el resto.
  - Los Ticket-Recuerdo (FLAG_ITEM_TICKET_*) se quedan donde están, para que haya al menos uno
    por ruta.
  - Las MT se barajan entre ellas: donde había una MT sale otra MT.
  - El resto, cualquier objeto menos los de "excluir", los objetos clave, las MO, las cartas, las
    megapiedras, los cristales Z y las teralitas. Las bayas sí pueden salir.
  - Los objetos clave y las MO del suelo no se tocan (hacen falta para avanzar).
- Recogida: los objetos de la tabla cambian por objetos de consumo (curas, bayas, caramelos), con
  las mismas probabilidades por nivel.
- Salvajes: cualquier salvaje puede llevar un objeto (del mismo grupo que el suelo) con poca
  probabilidad ("salvajes" -> "probabilidad_objeto", en %).

No se toca ningún mapa: el juego cambia el objeto al vuelo con las tablas que se generan aquí
(src/data/dualocke_aleatorio.h, las usa src/dualocke_aleatorio.c).
"""

import glob
import json
import random
import re

from . import especies as esp

# Objetos del suelo que no se randomizan: megapiedras y Ticket-Recuerdo (colocar_objetos.py)
FIJOS = ("FLAG_ITEM_MEGA_", "FLAG_ITEM_TICKET_")

# Nombres de "excluir" (randomizer_config.json) que no son el nombre exacto de un objeto
EXCLUIR_POR_NOMBRE = {
    "Pulsera Z": ["ITEM_Z_POWER_RING"],
    "Maxisetas": ["ITEM_MAX_MUSHROOMS"],
    "Mochi Reinicio": ["ITEM_FRESH_START_MOCHI"],
    "Remedio": ["ITEM_REMEDY"],
    "Remedio Fino": ["ITEM_FINE_REMEDY"],
    "Remedio Excelso": ["ITEM_SUPERB_REMEDY"],
    "Rábano Picante": ["ITEM_TWICE_SPICED_RADISH"],
}
# Grupos de "excluir" que son una categoría entera
EXCLUIR_POR_CATEGORIA = {
    "cristales Z": "ITEM_TYPE_Z_CRYSTAL",
    "teralitas": "ITEM_TYPE_TERA_SHARD",
}
# Además de lo que pide Miguel: objetos del Dinamax que no están en su lista
EXCLUIR_SIEMPRE = {"ITEM_NONE", "ITEM_DYNAMAX_CANDY", "ITEM_MAX_HONEY"}

# Recogida: "solo objetos de consumo (curas, bayas, Caramelos Raros…)"
CONSUMO = {"ITEM_TYPE_HEALTH_RECOVERY", "ITEM_TYPE_STATUS_RECOVERY", "ITEM_TYPE_PP_RECOVERY",
           "ITEM_TYPE_LEVEL_UP_ITEM"}

PROBABILIDAD_SALVAJES = 5  # % si el config no dice otra cosa


class Objeto:
    def __init__(self, constante, campos, nombre):
        self.constante = constante
        self.nombre = nombre
        self.bolsillo = campos.get("pocket", "POCKET_ITEMS")
        self.tipo = campos.get("sortType", "ITEM_TYPE_UNCATEGORIZED")
        self.efecto = campos.get("holdEffect")

    @property
    def es_mt(self):
        return self.constante.startswith("ITEM_TM")

    @property
    def es_mo(self):
        return self.constante.startswith("ITEM_HM")

    @property
    def es_clave(self):
        return self.bolsillo == "POCKET_KEY_ITEMS"

    @property
    def es_megapiedra(self):
        return self.tipo == "ITEM_TYPE_MEGA_STONE" or self.efecto == "HOLD_EFFECT_MEGA_STONE"


def leer_objetos(cpp="arm-none-eabi-cpp", cppflags=None):
    """Lee gItemsInfo de src/item.c (con la misma configuración que al compilar).
    Devuelve {ITEM_X: Objeto}, con el nombre en español."""
    if cppflags is None:
        cppflags = ["-iquote", "include", "-Wno-trigraphs", "-DMODERN=1", "-DTESTING=0",
                    "-DEMERALD", "-std=gnu17"]
    texto = esp._preprocesar(cpp, cppflags, "src/item.c")
    texto = texto[texto.index("gItemsInfo[] ="):]
    objetos = {}
    for m in re.finditer(r"\[(ITEM_\w+)\]\s*=\s*\{", texto):
        cuerpo = esp._cuerpo_entre_llaves(texto, m.end() - 1)
        campos = dict(re.findall(r"\.(\w+)\s*=\s*([A-Za-z0-9_]+)", cuerpo))
        cabeza = re.search(r"\.name\s*=(.*?)\n\s*\.\w+\s*=", cuerpo, re.S)
        cabeza = cabeza.group(1) if cabeza else ""
        nombres = re.findall(r'_\("([^"]*)"\)', cabeza) or re.findall(r'COMPOUND_STRING\("([^"]*)"\)', cabeza)
        objetos[m.group(1)] = Objeto(m.group(1), campos, nombres[-1] if nombres else "?")
    if len(objetos) < 500:
        raise RuntimeError(f"Dualocke: solo se han leído {len(objetos)} objetos de src/item.c")
    return objetos


def excluidos(objetos, config):
    """Constantes de los objetos que no pueden salir al azar (lista de Miguel y los fijos)."""
    por_nombre = {}
    for o in objetos.values():
        por_nombre.setdefault(o.nombre, []).append(o.constante)
    fuera = set(EXCLUIR_SIEMPRE)
    for nombre in config.get("objetos", {}).get("excluir", []):
        if nombre in EXCLUIR_POR_CATEGORIA:
            fuera |= {o.constante for o in objetos.values() if o.tipo == EXCLUIR_POR_CATEGORIA[nombre]}
        elif nombre in por_nombre:
            fuera |= set(por_nombre[nombre])
        elif nombre in EXCLUIR_POR_NOMBRE:
            fuera |= set(EXCLUIR_POR_NOMBRE[nombre])
        else:
            raise RuntimeError(f"Dualocke: no encuentro el objeto '{nombre}' de objetos.excluir (randomizer_config.json)")
    for o in objetos.values():
        if (o.es_clave or o.es_mo or o.es_mt or o.es_megapiedra or o.tipo == "ITEM_TYPE_MAIL"
                or o.tipo in EXCLUIR_POR_CATEGORIA.values() or o.nombre.startswith("?")):
            fuera.add(o.constante)
    return fuera


def grupo_suelo(objetos, config):
    """Objetos que pueden salir en el suelo y en los salvajes."""
    fuera = excluidos(objetos, config)
    return sorted(c for c in objetos if c not in fuera)


def grupo_consumo(objetos, config):
    fuera = excluidos(objetos, config)
    return sorted(c for c, o in objetos.items()
                  if c not in fuera and (o.tipo in CONSUMO or o.bolsillo == "POCKET_BERRIES"))


def _mapas_de_hoenn():
    return [m for m in sorted(glob.glob("data/maps/*/map.json")) if "_Frlg" not in m]


def buscar_suelo():
    """Devuelve [(flag, objeto, mapa)] de las Poké Balls del suelo y los objetos ocultos de Hoenn."""
    resultado = []
    for ruta in _mapas_de_hoenn():
        with open(ruta, encoding="utf-8") as f:
            mapa = json.load(f)
        for o in mapa.get("object_events", []):
            if o.get("script") == "Common_EventScript_FindItem":
                resultado.append((o["flag"], o["trainer_sight_or_berry_tree_id"], mapa["name"]))
        for b in mapa.get("bg_events", []):
            if b.get("type") == "hidden_item":
                resultado.append((b["flag"], b["item"], mapa["name"]))
    return resultado


def leer_recogida():
    """Objetos de la tabla de Recogida (sPickupTable en src/battle_script_commands.c), en orden."""
    with open("src/battle_script_commands.c", encoding="utf-8") as f:
        texto = f.read()
    inicio = texto.index("sPickupTable[] =")
    tabla = texto[inicio:texto.index("};", inicio)]
    return re.findall(r"\{\s*(ITEM_\w+)\s*,", tabla)


def randomizar(objetos, semilla, config):
    """Devuelve {"suelo": {flag: nuevo}, "recogida": {original: nuevo}, "salvajes": [grupo],
    "probabilidad_salvajes": %}."""
    rng = random.Random(f"{semilla}|objetos")
    suelo = grupo_suelo(objetos, config)

    mapa_suelo = {}
    huecos_mt, mts = [], []
    for flag, objeto, _ in buscar_suelo():
        if flag in mapa_suelo or objeto not in objetos:
            continue
        o = objetos[objeto]
        if flag.startswith(FIJOS) or o.es_clave or o.es_mo:
            continue  # fijos
        if o.es_mt:
            huecos_mt.append(flag)
            mts.append(objeto)
            continue
        mapa_suelo[flag] = rng.choice(suelo)
    rng.shuffle(mts)
    mapa_suelo.update(zip(huecos_mt, mts))

    consumo = grupo_consumo(objetos, config)
    originales = leer_recogida()
    nuevos = rng.sample(consumo, len(originales))
    mapa_recogida = dict(zip(originales, nuevos))

    probabilidad = 0
    if config.get("salvajes", {}).get("objetos_aleatorios"):
        probabilidad = int(config["salvajes"].get("probabilidad_objeto", PROBABILIDAD_SALVAJES))
    return {"suelo": mapa_suelo, "recogida": mapa_recogida,
            "salvajes": suelo if probabilidad else [], "probabilidad_salvajes": probabilidad}


def comprobar(objetos, config, resultado):
    """Comprueba que no salen objetos prohibidos ni se tocan los fijos. Devuelve una lista de errores."""
    errores = []
    fuera = excluidos(objetos, config)
    originales = {flag: objeto for flag, objeto, _ in buscar_suelo()}
    for flag, nuevo in resultado["suelo"].items():
        viejo = originales.get(flag)
        if viejo is None:
            errores.append(f"{flag}: no es un objeto del suelo")
        elif flag.startswith(FIJOS):
            errores.append(f"{flag}: las megapiedras y los Ticket-Recuerdo no se tocan")
        elif objetos[viejo].es_mt != objetos[nuevo].es_mt:
            errores.append(f"{flag}: {viejo} -> {nuevo} (las MT solo se cambian por MT)")
        elif not objetos[nuevo].es_mt and nuevo in fuera:
            errores.append(f"{flag}: {nuevo} está excluido")
    for viejo, nuevo in resultado["recogida"].items():
        if nuevo in fuera or nuevo not in objetos:
            errores.append(f"Recogida: {viejo} -> {nuevo} está excluido")
    if any(o in fuera for o in resultado["salvajes"]):
        errores.append("Salvajes: hay objetos excluidos en el grupo")
    return errores


def solucionario(objetos, resultado):
    """Lo que ha salido, con los nombres en español."""
    nombre = lambda c: objetos[c].nombre if c in objetos else c  # noqa: E731
    sitio = {flag: (mapa, objeto) for flag, objeto, mapa in buscar_suelo()}
    return {
        "suelo": {f"{sitio[f][0]} ({nombre(sitio[f][1])})": nombre(n) for f, n in sorted(resultado["suelo"].items())},
        "recogida": {nombre(v): nombre(n) for v, n in resultado["recogida"].items()},
        "probabilidad_objeto_salvajes": resultado["probabilidad_salvajes"],
    }
