# Dualocke: instala lo necesario en Windows, compila el juego y deja la ROM en el escritorio.
#
# Uso, en PowerShell:
#   powershell -ExecutionPolicy Bypass -File tools\dualocke\instalar_windows.ps1
#
# - La primera vez, si no tienes WSL, lo instala (hace falta abrir PowerShell como
#   administrador) y te pide reiniciar. Despues de reiniciar, abre "Ubuntu" una vez para
#   crear tu usuario y vuelve a ejecutar este script.
# - Las siguientes veces solo actualiza el repo y vuelve a compilar (sirve para actualizar
#   el juego cuando Jorge o Miguel suban cambios).
# - La ROM se copia al escritorio como Dualocke.gba. Si mGBA guarda la partida al lado
#   (Dualocke.sav), al sustituir la ROM por una nueva la partida se conserva.
# - El juego sale randomizado y en version de juego (make release), sin los menus de
#   depuracion (R + START en el mapa, SELECT en combate). La semilla se guarda la primera
#   vez y se reutiliza, asi que actualizar no cambia tu partida. Opciones:
#     -NuevaPartida  otra semilla al azar (para empezar un locke nuevo).
#     -SinRandom     el juego sin randomizar y con los menus de depuracion, para probar.
#                    Se copia aparte, como Dualocke-sin-random.gba, para no pisar tu ROM
#                    de juego.

param(
    [string]$Rama = "master",
    [switch]$NuevaPartida,
    [switch]$SinRandom
)

$ErrorActionPreference = "Stop"

if ($NuevaPartida -and $SinRandom) {
    Write-Host "Usa -NuevaPartida o -SinRandom, pero no los dos a la vez." -ForegroundColor Red
    exit 1
}
if ($NuevaPartida) {
    Write-Host "Vas a generar una semilla nueva: la ROM sera otra partida distinta y la que" -ForegroundColor Yellow
    Write-Host "tengas guardada (Dualocke.sav) dejara de cuadrar con ella." -ForegroundColor Yellow
    $respuesta = Read-Host "Escribe SI para seguir"
    if ($respuesta -ne "SI") {
        Write-Host "Cancelado." -ForegroundColor Yellow
        exit 0
    }
}
# La partida de verdad se compila con make release (sin menus de depuracion) y sale como
# pokeemerald-release.gba; la de prueba, con make normal, como pokeemerald.gba
if ($NuevaPartida) {
    # Lo mismo que make nueva-partida, pero en version release
    $make = "rm -f dualocke_semilla.txt && make -j`$(nproc) release"
    $rom = "pokeemerald-release.gba"
} elseif ($SinRandom) {
    $make = "make -j`$(nproc) SIN_RANDOM=1"
    $rom = "pokeemerald.gba"
} else {
    $make = "make -j`$(nproc) release"
    $rom = "pokeemerald-release.gba"
}
$Distro = "Ubuntu"
$Repo = "https://github.com/Jorgemori06/pokeemerald-expansion"

function Get-Distros {
    # wsl.exe escribe en UTF-16; se quitan los caracteres nulos para poder comparar
    # Sin WSL, wsl.exe da error: se trata como "no hay distribuciones"
    try {
        $ErrorActionPreference = "Continue"
        $salida = & wsl.exe --list --quiet 2>$null
    } catch {
        return @()
    }
    if ($LASTEXITCODE -ne 0 -or -not $salida) { return @() }
    return @($salida | ForEach-Object { ($_ -replace "`0", "").Trim() } | Where-Object { $_ })
}

# 1. WSL y Ubuntu
if (-not (Get-Command wsl.exe -ErrorAction SilentlyContinue) -or -not ((Get-Distros) -contains $Distro)) {
    $admin = ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole(
        [Security.Principal.WindowsBuiltInRole]::Administrator)
    if (-not $admin) {
        Write-Host "No tienes WSL con Ubuntu. Abre PowerShell como administrador y vuelve a ejecutar este script." -ForegroundColor Yellow
        exit 1
    }
    Write-Host "Instalando WSL con Ubuntu..." -ForegroundColor Cyan
    & wsl.exe --install -d $Distro
    Write-Host ""
    Write-Host "Listo. Reinicia el PC, abre 'Ubuntu' desde el menu Inicio para crear tu usuario" -ForegroundColor Yellow
    Write-Host "y vuelve a ejecutar este script (ya sin administrador)." -ForegroundColor Yellow
    exit 0
}

# 2. Compilador, repo y compilacion (dentro de Linux, que es mucho mas rapido que en C:)
$bash = @"
set -e
if ! command -v arm-none-eabi-gcc >/dev/null; then
  echo 'Instalando el compilador (te pedira la contrasena de Ubuntu)...'
  sudo apt-get update
  sudo apt-get install -y build-essential binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi git libpng-dev python3
fi
mkdir -p ~/romhack
cd ~/romhack
if [ ! -d pokeemerald-expansion ]; then
  git clone $Repo
fi
cd pokeemerald-expansion
git fetch origin
git checkout $Rama
git pull --ff-only origin $Rama
$make
"@
Write-Host "Actualizando el repo y compilando (la primera vez tarda varios minutos)..." -ForegroundColor Cyan
& wsl.exe -d $Distro -- bash -lc ($bash -replace "`r", "")
if ($LASTEXITCODE -ne 0) {
    Write-Host "La compilacion ha fallado. Revisa el mensaje de arriba." -ForegroundColor Red
    exit 1
}

# 3. Copiar la ROM al escritorio
$escritorio = [Environment]::GetFolderPath("Desktop")
if ($SinRandom) {
    $destino = Join-Path $escritorio "Dualocke-sin-random.gba"
} else {
    $destino = Join-Path $escritorio "Dualocke.gba"
}
$origen = (& wsl.exe -d $Distro -- bash -lc "wslpath -w ~/romhack/pokeemerald-expansion/$rom").Trim()
Copy-Item -LiteralPath $origen -Destination $destino -Force
Write-Host ""
Write-Host "Hecho: $destino" -ForegroundColor Green
Write-Host "Abrela con mGBA (https://mgba.io)."
