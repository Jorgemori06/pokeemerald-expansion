# 23/10/2026 · Miguel · Instalación para jugar en Windows

Rama `miguel/instalacion`.

## Por qué

En el PC de Miguel no hay WSL ni compilador, así que hasta ahora nada se había compilado en local, solo en el CI. Para poder jugar hace falta compilar la ROM.

## Lo que se hizo

- **`tools/dualocke/instalar_windows.ps1`:** un único script de PowerShell.
  1. Si no hay WSL con Ubuntu, lo instala (pide administrador) y pide reiniciar.
  2. Instala el compilador dentro de Ubuntu si falta.
  3. Clona o actualiza el repo en `~/romhack/pokeemerald-expansion` (dentro de Linux, que es mucho más rápido que en `C:`) y compila.
  4. Copia la ROM al escritorio como `Dualocke.gba`.
- **Sección 3 de `DUALOCKE.md`:** cómo usarlo, actualizar y compilar otra rama (`-Rama`).
- **Probado en el PC de Miguel solo el primer paso:** sin WSL, avisa de que hay que abrir PowerShell como administrador y sale sin tocar nada.
  - Se corrigió un fallo: en Windows PowerShell 5.1, el error de `wsl.exe` cortaba el script.

## No lo hace Claude

- Instalar WSL activa una característica de Windows y necesita administrador y reiniciar, así que lo lanza Miguel.

## Queda

- Que Miguel lo ejecute, compruebe que compila y juegue en mGBA.
