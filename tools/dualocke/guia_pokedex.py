#!/usr/bin/env python3
"""
Dualocke: genera los datos de la Pokédex de GUIA.html (estadísticas base, tipos, evoluciones,
megaevoluciones y el sprite de cada Pokémon) a partir del código del juego.

Uso (desde la raíz del repo, con el compilador instalado: hace falta arm-none-eabi-cpp):
    python3 tools/dualocke/guia_pokedex.py

Escribe el resultado dentro de GUIA.html, en el bloque <script id="datos-pokedex">. Los sprites
van dentro del propio HTML (PNG en base64), así la guía sigue siendo un solo archivo que no
carga nada de fuera.

Qué sale y qué no:
- Las estadísticas base, los tipos y las evoluciones son los del juego (el randomizer no los
  cambia). Las evoluciones son las de nuestra versión: las de intercambio ya salen por nivel o
  por objeto.
- Las habilidades y los movimientos no salen: el randomizer los cambia en cada partida.
- Una entrada por especie y por forma que cambie tipos o estadísticas (megas, formas regionales,
  Rotom...). Las formas que solo cambian de aspecto se juntan con la normal.
"""

import base64
import io
import json
import re
import sys

from PIL import Image

sys.path.insert(0, "tools/dualocke")
from aleatorio import especies as esp  # noqa: E402
from aleatorio import movimientos as mov  # noqa: E402
from aleatorio import objetos as obj  # noqa: E402

GUIA = "GUIA.html"
CPPFLAGS = ["-iquote", "include", "-Wno-trigraphs", "-DMODERN=1", "-DTESTING=0", "-DEMERALD", "-std=gnu17"]

STATS = ["HP", "Attack", "Defense", "SpAttack", "SpDefense", "Speed"]
# Formas que no se ven en una partida normal
FUERA = {"isGigantamax", "isTotem", "isTeraForm"}
SUFIJOS = [
    (r"_MEGA_X$", "Mega-{} X"), (r"_MEGA_Y$", "Mega-{} Y"), (r"_MEGA_Z$", "Mega-{} Z"), (r"_MEGA$", "Mega-{}"),
    (r"_PRIMAL$", "{} Primigenio"),
    (r"_ALOLA\w*$", "{} de Alola"), (r"_GALAR\w*$", "{} de Galar"), (r"_HISUI\w*$", "{} de Hisui"),
    (r"_PALDEA_COMBAT$", "{} de Paldea (Combatiente)"), (r"_PALDEA_BLAZE$", "{} de Paldea (Ardiente)"),
    (r"_PALDEA_AQUA$", "{} de Paldea (Acuático)"), (r"_PALDEA\w*$", "{} de Paldea"),
]
MOMENTOS = {"TIME_MORNING": "por la mañana", "TIME_DAY": "de día", "TIME_EVENING": "al atardecer", "TIME_NIGHT": "de noche"}


def evaluar(expr):
    """Valor de una expresión de C ya preprocesada: "8 >= 5 || 8 == 0 ? 50 : 40", "(8 >= 1 ? 109 : 85)"."""
    expr = expr.strip()
    while expr.startswith("(") and expr.endswith(")"):
        profundidad = 0
        for i, ch in enumerate(expr):
            profundidad += ch == "("
            profundidad -= ch == ")"
            if profundidad == 0 and i < len(expr) - 1:
                break
        else:
            expr = expr[1:-1].strip()
            continue
        break
    profundidad = 0
    for i, ch in enumerate(expr):
        profundidad += ch == "("
        profundidad -= ch == ")"
        if ch == "?" and profundidad == 0:
            resto, nivel = expr[i + 1:], 0
            for j, c2 in enumerate(resto):
                nivel += c2 == "?"
                if c2 == ":":
                    if nivel == 0:
                        cond = evaluar(expr[:i])
                        return evaluar(resto[:j]) if cond else evaluar(resto[j + 1:])
                    nivel -= 1
    python = expr.replace("||", " or ").replace("&&", " and ").replace("!=", " != ")
    python = re.sub(r"!(?!=)", " not ", python)
    return eval(python, {"__builtins__": {}})


def leer_stats(cuerpo):
    """Las 6 estadísticas base, evaluando las que dependen de la generación (P_UPDATED_STATS)."""
    res = {}
    for nombre, expr in re.findall(r"\.base(HP|Attack|Defense|Speed|SpAttack|SpDefense)\s*=\s*([^,]+),", cuerpo):
        res[nombre] = int(evaluar(expr))
    return res


FORMAS_ES = {"WASH": "Lavado", "HEAT": "Calor", "FROST": "Frío", "FAN": "Ventilador", "MOW": "Corte",
             "ATTACK": "Ataque", "DEFENSE": "Defensa", "SPEED": "Velocidad", "ORIGIN": "Origen",
             "SKY": "Cielo", "THERIAN": "Tótem", "BLACK": "Negro", "WHITE": "Blanco", "FEMALE": "hembra",
             "MALE": "macho", "SUNNY": "Sol", "RAINY": "Lluvia", "SNOWY": "Nieve"}


def tipos_es():
    """{TYPE_X: nombre en español} de src/data/types_info.h."""
    texto = open("src/data/types_info.h", encoding="utf-8").read()
    res = {}
    for m in re.finditer(r"\[(TYPE_\w+)\]\s*=\s*\{(.*?)\n    \},", texto, re.S):
        nombres = re.findall(r'_\("([^"]*)"\)', re.search(r"\.name\s*=([^\n]*)", m.group(2)).group(1))
        res[m.group(1)] = nombres[-1]
    return res


def numeros_pokedex():
    texto = open("include/constants/pokedex.h", encoding="utf-8").read()
    texto = texto[texto.index("enum NationalDexOrder"):]
    texto = texto[:texto.index("};")]
    nombres = re.findall(r"^\s*(NATIONAL_DEX_\w+)\s*,", texto, re.M)
    return {n: i for i, n in enumerate(nombres)}


def archivos_graficos():
    """{gMonFrontPic_X / gMonPalette_X: ruta}, sin las variantes de estilo GBA."""
    res = {}
    for simbolo, ruta in re.findall(r"const u\d+ (gMon(?:FrontPic|Palette)_\w+)\[\]\s*=\s*INCGFX_U\d+\(\"([^\"]+)\"",
                                    open("src/data/graphics/pokemon.h", encoding="utf-8").read()):
        if "_gba." in ruta:
            continue
        res.setdefault(simbolo, ruta)
    return res


def leer_paleta(ruta):
    lineas = open(ruta, encoding="utf-8").read().split()
    numeros = [int(x) for x in lineas[3:]]
    return numeros[:48]


def sprite(ruta_png, ruta_pal):
    """PNG del primer fotograma (64x64), con el color 0 transparente, en base64."""
    im = Image.open(ruta_png)
    im = im.crop((0, 0, 64, 64))
    if im.mode != "P":
        im = im.convert("P")
    pal = leer_paleta(ruta_pal)
    im.putpalette(pal + [0] * (768 - len(pal)))
    salida = io.BytesIO()
    im.save(salida, format="PNG", optimize=True, transparency=0, bits=4)
    return base64.b64encode(salida.getvalue()).decode()


def nombre_forma(constante, nombre, base):
    for patron, plantilla in SUFIJOS:
        if re.search(patron, constante):
            return plantilla.format(nombre)
    if constante != base and constante.startswith(base + "_"):
        sufijo = constante[len(base) + 1:]
        return f"{nombre} ({' '.join(FORMAS_ES.get(p, p.capitalize()) for p in sufijo.split('_'))})"
    return nombre


def describir_evolucion(metodo, param, condiciones, objetos, movimientos, tipos):
    def nombre_objeto(c):
        return objetos[c].nombre if c in objetos else c
    partes = []
    if metodo == "EVO_LEVEL":
        if param.isdigit() and int(param) > 0:
            partes.append(f"Nivel {param}")
        else:
            partes.append("Subir de nivel")
    elif metodo == "EVO_ITEM":
        partes.append(f"Con {nombre_objeto(param)}")
    elif metodo == "EVO_SPIN":
        partes.append("Girando con un dulce equipado")
        return " ".join(partes)
    else:
        return "Método especial"
    for cond, valor in re.findall(r"\{(IF_\w+),\s*([^}]*)\}", condiciones):
        valor = valor.strip()
        if cond == "IF_TIME":
            partes.append(MOMENTOS.get(valor, ""))
        elif cond == "IF_NOT_TIME":
            partes.append("no " + MOMENTOS.get(valor, ""))
        elif cond == "IF_HOLD_ITEM":
            partes.append(f"llevando {nombre_objeto(valor)}")
        elif cond == "IF_MIN_FRIENDSHIP":
            partes.append("con mucha amistad")
        elif cond == "IF_KNOWS_MOVE":
            partes.append(f"sabiendo {movimientos[valor].nombre}" if valor in movimientos else "sabiendo un movimiento")
        elif cond == "IF_KNOWS_MOVE_TYPE":
            partes.append(f"sabiendo un movimiento de tipo {tipos.get(valor, valor)}")
        elif cond == "IF_GENDER":
            partes.append("si es hembra" if "FEMALE" in valor else "si es macho")
        elif cond == "IF_WEATHER":
            partes.append("con lluvia o niebla")
        elif cond in ("IF_IN_MAPSEC", "IF_IN_MAP"):
            partes.append("en un lugar concreto")
        elif cond == "IF_MIN_BEAUTY":
            partes.append("con mucha belleza")
        elif cond in ("IF_SPECIES_IN_PARTY", "IF_TYPE_IN_PARTY"):
            partes.append("con otro Pokémon concreto en el equipo")
        elif cond.startswith("IF_PID"):
            partes.append("(según el Pokémon)")
        elif cond in ("IF_REGION", "IF_NOT_REGION"):
            continue
        else:
            partes.append("(condición especial)")
    return " ".join(p for p in partes if p)


def leer_evoluciones(cuerpo):
    m = re.search(r"\.evolutions\s*=\s*\(const struct Evolution\[\]\)\s*\{", cuerpo)
    if not m:
        return []
    lista = esp._cuerpo_entre_llaves(cuerpo, m.end() - 1)
    res, i = [], 0
    while True:
        i = lista.find("{", i)
        if i == -1:
            break
        entrada = esp._cuerpo_entre_llaves(lista, i)
        i += len(entrada) + 2
        partes = entrada.split(",", 3)
        if len(partes) < 3 or not partes[0].strip().startswith("EVO_"):
            continue
        metodo, param, destino = (p.strip() for p in partes[:3])
        condiciones = partes[3] if len(partes) > 3 else ""
        if destino.startswith("SPECIES_") and esp._evolucion_valida_en_hoenn(condiciones):
            res.append((metodo, param, destino, condiciones))
    return res


def main():
    texto = esp._preprocesar("arm-none-eabi-cpp", CPPFLAGS)
    especies, tablas, alias = esp.leer_especies(cppflags=CPPFLAGS)
    pokedex = esp.Pokedex(especies, tablas, alias)
    objetos = obj.leer_objetos(cppflags=CPPFLAGS)
    movimientos = mov.leer_movimientos(cppflags=CPPFLAGS)
    tipos = tipos_es()
    numeros = numeros_pokedex()
    graficos = archivos_graficos()

    # Megaevoluciones (con megapiedra o, Rayquaza, con un movimiento) y regresiones primigenias
    megas = {}
    for m in re.finditer(r"static const struct FormChange (s\w+FormChangeTable)\[\]\s*=\s*\{", texto):
        cuerpo = esp._cuerpo_entre_llaves(texto, m.end() - 1)
        for destino, como in re.findall(r"\{\s*FORM_CHANGE_BATTLE_(?:MEGA_EVOLUTION_ITEM|MEGA_EVOLUTION_MOVE|PRIMAL_REVERSION)"
                                        r"\s*,\s*(SPECIES_\w+)\s*,\s*((?:ITEM|MOVE)_\w+)", cuerpo):
            megas.setdefault(m.group(1), []).append((destino, como))

    inicio = texto.index("const struct SpeciesInfo gSpeciesInfo[] =")
    bloque = esp._cuerpo_entre_llaves(texto, texto.index("{", inicio))
    cuerpos = {m.group(1): esp._cuerpo_entre_llaves(bloque, m.end() - 1)
               for m in re.finditer(r"\[(SPECIES_\w+)\]\s*=\s*\{", bloque)}

    entradas, vistos, sprites = {}, {}, {}
    for constante, e in especies.items():
        if constante in ("SPECIES_NONE", "SPECIES_EGG") or not e.nombre_es:
            continue
        if e.flags & FUERA:
            continue
        # Solo las formas que salen en una partida: la normal, las regionales y las megas
        if not (pokedex.es_forma_normal(constante) or pokedex.forma_base(constante) == constante
                or e.flags & {"isMegaEvolution", "isPrimalReversion"}):
            continue
        cuerpo = cuerpos[constante]
        e.stats = leer_stats(cuerpo)
        if len(e.stats) < 6:
            continue
        num = re.search(r"\.natDexNum\s*=\s*(NATIONAL_DEX_\w+)", cuerpo)
        num = numeros.get(num.group(1), 0) if num else 0
        if not num:
            continue
        clave = (num, tuple(e.tipos), tuple(e.stats[s] for s in STATS))
        if clave in vistos:  # forma que solo cambia de aspecto
            alias[constante] = vistos[clave]
            continue
        vistos[clave] = constante
        pic = re.search(r"\.frontPic\s*=\s*(gMonFrontPic_\w+)", cuerpo)
        pal = re.search(r"\.palette\s*=\s*(gMonPalette_\w+)", cuerpo)
        s = None
        if pic and pal and pic.group(1) in graficos and pal.group(1) in graficos:
            s = sprite(graficos[pic.group(1)], graficos[pal.group(1)])
        tipos_unicos = list(dict.fromkeys(e.tipos))
        entradas[constante] = {
            "n": num,
            "nombre": nombre_forma(constante, e.nombre_es, pokedex.forma_base(constante)),
            "tipos": [tipos[t] for t in tipos_unicos],
            "stats": [e.stats[s_] for s_ in STATS],
            "evos": [],
            "megas": [],
            "forma": "isMegaEvolution" in e.flags or "isPrimalReversion" in e.flags,
            "leg": e.es_legendaria,
        }
        if s:
            sprites[constante] = s

    # Evoluciones (con el método) y megaevoluciones
    for constante, entrada in entradas.items():
        for metodo, param, destino, condiciones in leer_evoluciones(cuerpos[constante]):
            destino = alias.get(destino, destino)
            if destino in entradas:
                evo = [destino, describir_evolucion(metodo, param, condiciones, objetos, movimientos, tipos)]
                if evo not in entrada["evos"]:
                    entrada["evos"].append(evo)
        tabla = re.search(r"\.formChangeTable\s*=\s*(s\w+)", cuerpos[constante])
        if tabla and not entrada["forma"]:
            for mega, como in megas.get(tabla.group(1), []):
                mega = alias.get(mega, mega)
                if mega in entradas and mega != constante:
                    if como in objetos:
                        como = objetos[como].nombre
                    elif como in movimientos:
                        como = f"Sabiendo {movimientos[como].nombre}"
                    entrada["megas"].append([mega, como])

    # Preevolución de cada uno, para montar la línea entera
    for constante, entrada in entradas.items():
        for destino, _ in entrada["evos"]:
            entradas[destino].setdefault("pre", constante)

    orden = {c: i for i, c in enumerate(especies)}
    lista = sorted(entradas.items(), key=lambda kv: (kv[1]["n"], kv[1]["forma"], orden[kv[0]]))
    ids = {c: i for i, (c, _) in enumerate(lista)}
    datos = []
    for constante, entrada in lista:
        fila = {"n": entrada["n"], "nombre": entrada["nombre"], "tipos": entrada["tipos"], "stats": entrada["stats"]}
        if entrada["evos"]:
            fila["evos"] = [[ids[d], m] for d, m in entrada["evos"]]
        if entrada["megas"]:
            fila["megas"] = [[ids[d], p] for d, p in entrada["megas"]]
        if "pre" in entrada:
            fila["pre"] = ids[entrada["pre"]]
        if entrada["forma"]:
            fila["forma"] = 1
        if entrada["leg"]:
            fila["leg"] = 1
        fila["s"] = sprites.get(constante, "")
        datos.append(fila)

    guia = open(GUIA, encoding="utf-8").read()
    bloque_json = json.dumps(datos, ensure_ascii=False, separators=(",", ":"))
    nuevo, cambios = re.subn(r'(<script id="datos-pokedex" type="application/json">).*?(</script>)',
                             lambda m: m.group(1) + bloque_json + m.group(2), guia, flags=re.S)
    if not cambios:
        sys.exit('Dualocke: no encuentro <script id="datos-pokedex"> en GUIA.html')
    open(GUIA, "w", encoding="utf-8").write(nuevo)
    print(f"Pokédex actualizada: {len(datos)} entradas, {sum(1 for d in datos if d['s'])} con sprite, "
          f"{len(bloque_json) // 1024} KB")


if __name__ == "__main__":
    main()
