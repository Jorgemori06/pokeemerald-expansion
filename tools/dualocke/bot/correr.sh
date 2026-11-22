#!/bin/bash
# correr.sh ENTRADA SALIDA 'código' -> lo mismo que paso.py, en segundo plano (máximo 50 min),
# con la salida en ultimo.log dentro de la carpeta de la partida.
AQUI="$(cd "$(dirname "$0")" && pwd)"
PARTIDA="${DUALOCKE_PARTIDA:-$AQUI/../../../partida_bot}"
nohup timeout 3000 python3 "$AQUI/paso.py" "$1" "$2" "$3" > "$PARTIDA/ultimo.log" 2>&1 &
echo $!
