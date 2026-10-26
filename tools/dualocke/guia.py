#!/usr/bin/env python3
"""
Dualocke: actualiza las pistas de GUIA.html (megapiedras, objetos competitivos y Ticket-Recuerdo)
a partir de los mapas, para que la guía no se quede atrás si se mueve algo.

Uso (desde la raíz del repo):
    python3 tools/dualocke/guia.py

Lee las tablas de colocar_objetos.py, busca cada objeto por su flag en el map.json y describe
el sitio sin decir la casilla exacta: zona, parte del mapa, terreno (hierba, arena, agua…) y lo que
hay cerca. La casilla va aparte, como "solución". Escribe el resultado dentro de GUIA.html, en el
bloque <script id="datos-pistas">. El resto de la guía se edita a mano.
"""

import json
import re
import struct
import sys

sys.path.insert(0, "tools/dualocke")
import colocar_objetos as c  # noqa: E402

GUIA = "GUIA.html"

# Tramo de la historia (el de la medalla que se busca) en el que se puede llegar a cada mapa
TRAMOS = [
    (1, r"^Route10[1-4]$|^PetalburgWoods"),
    (2, r"^Route116$|^RusturfTunnel|^DewfordTown|^GraniteCave|^Route106$"),
    (3, r"^Route109$|^SlateportCity|^Route110$|^MauvilleCity"),
    (4, r"^Route11[1-57]$|^Route110_TrickHouse|^VerdanturfTown|^FieryPath|^MeteorFalls_1F|^MtChimney|^JaggedPass"),
    (5, r"^MirageTower"),
    (6, r"^Route10[578]$|^AbandonedShip|^NewMauville|^Route11[89]|^Route120$|^MeteorFalls_B1F_1R"),
    (7, r"^Route12[1-5]$|^SafariZone|^LilycoveCity|^MtPyre|^MagmaHideout|^AquaHideout|^MossdeepCity$|^ShoalCave"),
    (8, r"^MossdeepCity_SpaceCenter|^Route12[6-9]$|^Route13[0-4]$|^Underwater_|^SootopolisCity|^SkyPillar"),
    (9, r"^VictoryRoad|^MeteorFalls_B1F_2R"),
]
PARTES = [
    (r"_WeatherInstitute_(\d)F", lambda m: f"INSTITUTO METEOROLÓGICO, planta {m.group(1)}"),
    (r"_OceanicMuseum_(\d)F", lambda m: f"MUSEO OCEÁNICO, planta {m.group(1)}"),
    (r"_SpaceCenter_(\d)F", lambda m: f"CENTRO ESPACIAL, planta {m.group(1)}"),
    (r"_GameCorner", lambda m: "CASINO"),
    (r"_TrickHouseEnd", lambda m: "final de la CASA TRAMPA"),
    (r"_Rooms_B1F", lambda m: "camarotes del sótano"),
    (r"_Corridors_B1F", lambda m: "pasillos del sótano"),
    (r"_HiddenFloorCorridors", lambda m: "pasillos de la planta oculta"),
    (r"_LowTide(\w+?)Room", lambda m: {"Ice": "sala de hielo", "Lower": "sala de abajo", "Inner": "sala del fondo",
                                        "Stairs": "sala de las escaleras"}.get(m.group(1), "") + " (con la marea baja)"),
    (r"_B(\d)F_(\d)R", lambda m: f"sótano {m.group(1)}, sala {m.group(2)}"),
    (r"_(\d)F_(\d)R", lambda m: f"planta {m.group(1)}, sala {m.group(2)}"),
    (r"_B(\d)F", lambda m: f"sótano {m.group(1)}"),
    (r"_(\d)F", lambda m: f"planta {m.group(1)}"),
    (r"_Summit", lambda m: "cima"),
    (r"_Exterior", lambda m: "exterior"),
    (r"_Inside", lambda m: "interior"),
    (r"_(Southwest|Northwest|Southeast|South)$", lambda m: {"Southwest": "zona suroeste", "Northwest": "zona noroeste",
                                                            "Southeast": "zona sureste", "South": "zona sur"}[m.group(1)]),
]
TERRENO = {
    "MB_TALL_GRASS": "entre la hierba alta", "MB_LONG_GRASS": "entre la hierba muy alta",
    "MB_ASHGRASS": "en la hierba con ceniza", "MB_SAND": "en la arena", "MB_DEEP_SAND": "en la arena del desierto",
    "MB_OCEAN_WATER": "en el agua (con SURF)", "MB_POND_WATER": "en el agua (con SURF)", "MB_SHORT_GRASS": "en la hierba",
    "MB_FOOTPRINTS": "en la arena", "MB_MOUNTAIN_TOP": "en lo alto de la montaña",
}
SECTORES = {"norte": "norte", "sur": "sur", "oeste": "oeste", "este": "este", "": "centro",
            "norteoeste": "noroeste", "norteeste": "noreste", "suroeste": "suroeste", "sureste": "sureste"}


def tramo(carpeta, detalles):
    if carpeta == "Route111" and any("desierto" in d for d in detalles):
        return 5  # el desierto necesita las GAFAS AISLANTES (después de LAVACALDA)
    for n, patron in TRAMOS:
        if re.search(patron, carpeta):
            return n
    return 9


class Mapas:
    def __init__(self):
        self.mb = {v: k for k, v in c.comportamientos().items()}
        self.ts = c.atributos_tilesets()
        self.layouts = c.cargar_layouts()
        with open("src/data/region_map/region_map_sections.json", encoding="utf-8") as f:
            self.secciones = {s["id"]: s.get("name", s["id"]) for s in json.load(f)["map_sections"]}

    def describir(self, carpeta, flag, tipo):
        with open(f"data/maps/{carpeta}/map.json", encoding="utf-8") as f:
            mapa = json.load(f)
        pos = [(o["x"], o["y"]) for o in mapa["object_events"] if o.get("flag") == flag]
        pos += [(b["x"], b["y"]) for b in mapa.get("bg_events", []) if b.get("flag") == flag]
        if not pos:
            return None
        x, y = pos[0]
        l = self.layouts[mapa["layout"]]
        w, h = l["width"], l["height"]
        with open(l["blockdata_filepath"], "rb") as f:
            d = struct.unpack(f"<{w * h}H", f.read())
        p, s = self.ts.get(l["primary_tileset"], []), self.ts.get(l["secondary_tileset"], [])

        def comp(cx, cy):
            if not (0 <= cx < w and 0 <= cy < h):
                return ""
            mt = d[cy * w + cx] & 0x3FF
            b = p[mt] if mt < 512 and mt < len(p) else (s[mt - 512] if 0 <= mt - 512 < len(s) else -1)
            return self.mb.get(b, "")

        aqui = comp(x, y)
        cerca = {comp(x + dx, y + dy) for dx in range(-3, 4) for dy in range(-3, 4)}
        detalles = []
        if aqui in TERRENO:
            detalles.append(TERRENO[aqui])
        if "WATER" not in aqui and any("WATER" in cc for cc in cerca):
            detalles.append("cerca del agua")
        if "GRASS" not in aqui and cerca & {"MB_TALL_GRASS", "MB_LONG_GRASS"}:
            detalles.append("junto a hierba alta")
        if any(abs(wp["x"] - x) + abs(wp["y"] - y) <= 5 for wp in mapa.get("warp_events", [])):
            detalles.append("cerca de una entrada o escalera")
        if any(o.get("trainer_type", "TRAINER_TYPE_NONE") != "TRAINER_TYPE_NONE" and abs(o["x"] - x) + abs(o["y"] - y) <= 5
               for o in mapa["object_events"]):
            detalles.append("cerca de un entrenador")
        if any(o["graphics_id"] == "OBJ_EVENT_GFX_ITEM_BALL" and (o["x"], o["y"]) != (x, y)
               and abs(o["x"] - x) + abs(o["y"] - y) <= 4 for o in mapa["object_events"]):
            detalles.append("al lado de otra bola de objeto")
        parte = ""
        if carpeta.startswith("Underwater_"):
            parte = "bajo el agua (con BUCEO)"
        else:
            for patron, f in PARTES:
                m = re.search(patron, carpeta)
                if m:
                    parte = f(m)
                    break
        v = "norte" if y < h / 3 else "sur" if y >= 2 * h / 3 else ""
        hz = "oeste" if x < w / 3 else "este" if x >= 2 * w / 3 else ""
        return {
            "zona": self.secciones.get(mapa.get("region_map_section"), carpeta), "parte": parte,
            "tipo": "oculto" if tipo == "oculta" else "bola", "sector": SECTORES[v + hz],
            "detalles": detalles, "x": x, "y": y, "tramo": tramo(carpeta, detalles),
        }


def nombres_es():
    with open("src/data/items.h", encoding="utf-8") as f:
        texto = f.read()
    return dict(re.findall(r'\[(ITEM_\w+)\]\s*=\s*\{\s*(?://[^\n]*\n\s*)?\.name = ES\(ITEM_NAME\("[^"]*"\), ITEM_NAME\("([^"]*)"\)\)', texto))


def main():
    mapas = Mapas()
    nombres = nombres_es()
    datos = {"megapiedras": [], "competitivos": [], "tickets": []}
    grupos = [("megapiedras", c.MEGAPIEDRAS, "FLAG_ITEM_MEGA_", None),
              ("competitivos", c.COMPETITIVOS, "FLAG_ITEM_COMP_", None),
              ("tickets", getattr(c, "TICKETS", []) + getattr(c, "TICKETS_OCULTOS", []), "FLAG_ITEM_TICKET_", "Ticket-Recuerdo")]
    for clave, lista, prefijo, nombre_fijo in grupos:
        for objeto, carpeta, tipo, _ in lista:
            sitio = mapas.describir(carpeta, f"{prefijo}{objeto}", tipo)
            if not sitio:
                print(f"Dualocke: {objeto} no está en {carpeta} (¿falta lanzar colocar_objetos.py?)")
                continue
            sitio["nombre"] = nombre_fijo or nombres.get(f"ITEM_{objeto}", objeto)
            datos[clave].append(sitio)
    for lista in datos.values():
        lista.sort(key=lambda s: (s["tramo"], s["zona"], s["parte"], s["nombre"]))

    with open(GUIA, encoding="utf-8", newline="") as f:
        html = f.read()
    bloque = json.dumps(datos, ensure_ascii=False, separators=(",", ":"))
    nuevo, n = re.subn(r'(<script id="datos-pistas" type="application/json">).*?(</script>)',
                       lambda m: m.group(1) + bloque + m.group(2), html, flags=re.S)
    if n != 1:
        sys.exit(f"Dualocke: no encuentro el bloque de datos en {GUIA}")
    with open(GUIA, "w", encoding="utf-8", newline="") as f:
        f.write(nuevo)
    print("Pistas actualizadas:", {k: len(v) for k, v in datos.items()})


if __name__ == "__main__":
    main()
