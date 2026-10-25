"""
Dualocke: escribe src/data/dualocke_aleatorio.h, las tablas que usa src/dualocke_aleatorio.c para
cambiar al vuelo lo que no se puede randomizar sin tocar los mapas y los scripts: estáticos,
regalos, objetos del suelo, Recogida, objetos de los salvajes, intercambios con NPCs,
habilidades, MT y tutores.

Sin semilla (make SIN_RANDOM=1 o make check) todas las tablas están vacías y el juego sale como
el original.
"""


def _pares(nombre, mapa, tipo="u16"):
    filas = [f"    {{{a}, {b}}}," for a, b in sorted(mapa.items())] or ["    {0, 0},"]
    return [f"static const {tipo} {nombre}[][2] =", "{"] + filas + ["};"]


def generar(comentario, estaticos=None, regalos=None, suelo=None, recogida=None,
            salvajes=None, probabilidad_salvajes=0, intercambios=None, habilidades=None,
            mts=None, compatibilidad_mt=0, semilla_numerica=0, tutores=None):
    lineas = ["// Generado por el Makefile (Dualocke, tools/dualocke/randomizer.py): no editar.",
              f"// {comentario}", ""]
    lineas += ["// Estáticos (setwildbattle y errantes): especie original -> especie nueva"]
    lineas += _pares("sDualockeEstaticos", estaticos or {})
    lineas += ["// Regalos (givemon) y huevos (giveegg): especie original -> especie nueva"]
    lineas += _pares("sDualockeRegalos", regalos or {})
    lineas += ["// Objetos del suelo y ocultos: flag -> objeto nuevo"]
    lineas += _pares("sDualockeSuelo", suelo or {})
    lineas += ["// Recogida: objeto original -> objeto nuevo"]
    lineas += _pares("sDualockeRecogida", recogida or {})
    lineas += ["// Objetos que pueden llevar los salvajes, y con qué probabilidad (en %; 0 = como el original)",
               f"#define DUALOCKE_PROBABILIDAD_OBJETO_SALVAJE {probabilidad_salvajes if salvajes else 0}",
               "static const u16 sDualockeObjetosSalvajes[] =", "{"]
    lineas += [f"    {o}," for o in (salvajes or [])] or ["    0,"]
    lineas += ["};"]
    lineas += ["// Intercambios con NPCs: {intercambio, especie que te dan, especie que te piden, objeto, IVs}",
               "static const struct DualockeIntercambio sDualockeIntercambios[] =", "{"]
    filas = []
    for clave, i in sorted((intercambios or {}).items()):
        ivs = ", ".join(str(v) for v in i["ivs"])
        filas.append(f"    {{{clave}, {i['especie']}, {i['pide']}, {i['objeto']}, {{{ivs}}}}},")
    lineas += filas or ["    {0xFFFF},"]
    lineas += ["};"]
    lineas += ["// Habilidades: una por especie (0 = la original)",
               "static const u16 sDualockeHabilidades[NUM_SPECIES] =", "{"]
    lineas += [f"    [{e}] = {h}," for e, h in sorted((habilidades or {}).items())] or ["    0,"]
    lineas += ["};"]
    lineas += ["// MT: objeto -> movimiento nuevo; quién las aprende, con qué probabilidad (en %)",
               f"#define DUALOCKE_COMPATIBILIDAD_MT {compatibilidad_mt if mts else 0}",
               f"#define DUALOCKE_SEMILLA_NUMERICA {semilla_numerica}u"]
    lineas += _pares("sDualockeMT", mts or {})
    lineas += ["// Tutores: movimiento original -> movimiento nuevo (se aprende como las MT nuevas)"]
    lineas += _pares("sDualockeTutores", tutores or {})
    return "\n".join(lineas) + "\n"
