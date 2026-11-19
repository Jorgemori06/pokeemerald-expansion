#!/usr/bin/env python3
"""Dualocke: fotos del juego para las pistas de GUIA.html (megapiedras y Ticket-Recuerdo).

Uso (desde la raíz del repo; hace falta la ROM de pruebas y libmgba, ver emulador.py):
    make DUALOCKE_PRUEBA=1
    python3 tools/dualocke/guia.py                    # primero las pistas (cada una dice su mapa)
    python3 tools/dualocke/emulador/fotos_guia.py     # luego las fotos
    python3 tools/dualocke/emulador/fotos_guia.py --hoja /tmp/hoja.png   # además, todas en una imagen

Para cada objeto de las pistas empieza una partida en el emulador con el jugador al lado (abajo,
a la izquierda, a la derecha o arriba, donde se pueda estar; debajo no, porque la cabeza del jugador lo tapa), con luz en las cuevas y sin lluvia ni
tormenta de arena, y hace una foto de la pantalla con el sitio marcado con un círculo rojo. Las guarda
en GUIA.html, en el bloque <script id="datos-fotos">, como imágenes WebP (unos 5 KB cada una).

Pidió fotos Miguel (19/11/2026) para encontrar las megapiedras.
"""
import argparse
import base64
import io
import json
import os
import re
import sys

from PIL import Image, ImageDraw

AQUI = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, AQUI)
sys.path.insert(0, os.path.dirname(AQUI))
from emulador import RAIZ, Emulador  # noqa: E402
import alcance as a  # noqa: E402

GUIA = os.path.join(RAIZ, "GUIA.html")
# En pantalla, la casilla del jugador (la de sus pies) es la de x 112-127 e y 72-87 (240 × 160)
JUGADOR_X, JUGADOR_Y = 112, 72
LADOS = [(-1, 0), (1, 0), (0, -1), (0, 1)]   # a los lados; debajo, lo último: la cabeza del jugador lo tapa


def clave(p):
    return f"{p['mapa']}:{p['x']}:{p['y']}"


def donde_ponerse(mundo, mid, x, y):
    """Casilla de al lado del objeto donde se puede estar (sin colisión, ni agua ni objetos ni puertas)."""
    m = mundo.mapas[mid]
    ocupadas = {(o["x"], o["y"]) for o in m.get("object_events", [])}
    ocupadas |= {(w["x"], w["y"]) for w in m.get("warp_events", [])}
    objeto = mundo.casilla(mid, x, y)
    en_agua = objeto and objeto[2] in mundo.surf
    for agua in (False, True):
        for dx, dy in LADOS:
            c = mundo.casilla(mid, x + dx, y + dy)
            if not c or c[0] or (x + dx, y + dy) in ocupadas:
                continue
            if (c[2] in mundo.surf) != (agua or en_agua):
                continue
            return x + dx, y + dy
    return x, y + 1


def foto(mid, x, y, px, py):
    with Emulador() as emu:
        emu.empezar(mid, px, py, foto=True)
        emu.avanzar(40)
        ruta = "/tmp/dualocke_foto.png"
        emu.foto(ruta, 1)
    img = Image.open(ruta).convert("RGB")
    d = ImageDraw.Draw(img)
    x0, y0 = JUGADOR_X + (x - px) * 16, JUGADOR_Y + (y - py) * 16
    d.ellipse([x0 - 4, y0 - 4, x0 + 19, y0 + 19], outline=(255, 40, 40), width=2)
    return img


def main():
    p = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    p.add_argument("--hoja", help="guarda también todas las fotos juntas en esta imagen, para revisarlas")
    args = p.parse_args()
    html = open(GUIA, encoding="utf-8").read()
    datos = json.loads(re.search(r'<script id="datos-pistas" type="application/json">(.*?)</script>', html, re.S).group(1))
    mundo = a.Mundo()
    por_carpeta = {os.path.basename(m["carpeta"]): mid for mid, m in mundo.mapas.items()}
    fotos, imagenes = {}, []
    pistas = [p for lista in ("megapiedras", "tickets") for p in datos.get(lista, [])]
    for i, pista in enumerate(pistas):
        if "mapa" not in pista:
            sys.exit("Dualocke: las pistas no dicen su mapa: lanza antes python3 tools/dualocke/guia.py")
        mid = por_carpeta[pista["mapa"]]
        px, py = donde_ponerse(mundo, mid, pista["x"], pista["y"])
        try:
            img = foto(mid, pista["x"], pista["y"], px, py)
        except RuntimeError as e:
            print(f"Dualocke: sin foto de {pista['nombre']} ({pista['mapa']}): {e}")
            continue
        buf = io.BytesIO()
        img.save(buf, "WEBP", quality=80, method=6)
        fotos[clave(pista)] = "data:image/webp;base64," + base64.b64encode(buf.getvalue()).decode()
        imagenes.append((pista, img))
        print(f"{i + 1}/{len(pistas)} {pista['nombre']} ({pista['mapa']} {pista['x']},{pista['y']})")
    bloque = json.dumps(fotos, separators=(",", ":"))
    etiqueta = '<script id="datos-fotos" type="application/json">'
    if etiqueta in html:
        html = re.sub(re.escape(etiqueta) + r".*?</script>", lambda m: etiqueta + bloque + "</script>", html, flags=re.S)
    else:
        html = html.replace('<script id="datos-pistas"', etiqueta + bloque + '</script>\n<script id="datos-pistas"', 1)
    with open(GUIA, "w", encoding="utf-8", newline="") as f:
        f.write(html)
    print(f"Fotos en la guía: {len(fotos)} de {len(pistas)} ({len(bloque) // 1024} KB)")
    if args.hoja and imagenes:
        columnas = 8
        hoja = Image.new("RGB", (columnas * 240, ((len(imagenes) + columnas - 1) // columnas) * 172), (20, 20, 20))
        d = ImageDraw.Draw(hoja)
        for i, (pista, img) in enumerate(imagenes):
            x, y = (i % columnas) * 240, (i // columnas) * 172
            hoja.paste(img, (x, y + 12))
            d.text((x + 2, y), f"{pista['nombre']} - {pista['mapa']}", fill=(255, 255, 255))
        hoja.save(args.hoja)


if __name__ == "__main__":
    main()
