"""python3 eventos.py MAP_X [MAP_Y...] [--dibujo]

Lista los eventos de un mapa (personajes, carteles, puertas, casillas con script). Con --dibujo
pinta además la rejilla como la ve el planificador del bot: # pared, ~ agua, número = altura,
W puerta, B roca de FUERZA, R roca rompible, O otro personaje/objeto."""
import json
import os
import sys

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..", "data", "maps")
idx = {}
for c in os.listdir(R):
    p = os.path.join(R, c, "map.json")
    if os.path.exists(p):
        idx[json.load(open(p))["id"]] = c
dibujo = "--dibujo" in sys.argv
for mid in [a for a in sys.argv[1:] if not a.startswith("--")]:
    m = json.load(open(os.path.join(R, idx[mid], "map.json")))
    print(mid, m.get("region_map_section"))
    for o in m.get("object_events", []):
        print("  obj", o.get("local_id", ""), o["x"], o["y"], o["graphics_id"], o.get("script"), o.get("flag"), o.get("trainer_type"))
    for b in m.get("bg_events", []):
        print("  bg", b["x"], b["y"], b.get("script", b.get("item")))
    for w in m.get("warp_events", []):
        print("  warp", w["x"], w["y"], w["dest_map"])
    for c in m.get("coord_events", []):
        print("  coord", c["x"], c["y"], c.get("var"), c.get("var_value"), c.get("script"))
    if dibujo:
        sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
        import piloto as P
        w, h, c, warps, _ = P.info_mapa(mid)
        objs = {(o["x"], o["y"]): ("B" if "BOULDER" in o["graphics_id"] else "R" if "BREAK" in o["graphics_id"] else "O")
                for o in m["object_events"] if isinstance(o.get("x"), int)}
        print("     " + "".join(str(x % 10) for x in range(w)))
        for y in range(h):
            fila = ""
            for x in range(w):
                col, alt, mb = c[y * w + x]
                ch = "#" if col else ("~" if mb in P.mundo().surf else str(alt % 10))
                ch = "W" if (x, y) in warps else objs.get((x, y), ch)
                fila += ch
            print(f"{y:3}  {fila}")
