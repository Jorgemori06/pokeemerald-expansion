"""python3 paso.py ENTRADA SALIDA 'código'

Carga el estado ENTRADA (ruta dentro de la carpeta de la partida), ejecuta el código con todo lo de
piloto.py a mano (variable `e` = el emulador) y guarda en SALIDA. Si algo falla, guarda en
SALIDA_fallo.ss para poder seguir desde ahí."""
import os
import signal
import sys
import time


def _parar(*a):
    signal.signal(signal.SIGTERM, signal.SIG_IGN)
    raise KeyboardInterrupt()


signal.signal(signal.SIGTERM, _parar)
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import piloto as P  # noqa: E402
from piloto import *  # noqa: E402,F401,F403

e = P.Piloto()
A = P.AQUI
ENT, SAL = os.path.join(A, sys.argv[1]), os.path.join(A, sys.argv[2])
e.cargar_estado(ENT)
e.avanzar(2)
t0 = time.time()
bien = False
try:
    exec(sys.argv[3])
    bien = True
finally:
    destino = SAL if bien else SAL.replace(".ss", "_fallo.ss")
    try:
        e.guardar_estado(destino)
        e.foto(destino.replace(".ss", ".png"))
        print("FIN", "" if bien else "(CON FALLO, guardado aparte)", P.estado(e), f"{time.time()-t0:.0f}s")
    except Exception as err:
        print("FIN sin guardar:", err)
