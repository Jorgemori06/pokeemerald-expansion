# Skills y agentes de Claude útiles para el proyecto

Análisis hecho el 23/10/2026 a partir de lo que Miguel tiene instalado en Claude Code. El objetivo es que los dos trabajéis con las mismas herramientas.

> **Ojo:** en la sesión del paso 1 no se usó ninguna de estas skills: todo se hizo con las herramientas base de Claude Code (git, `gh`, editar archivos). Esto es una **recomendación** de cuáles encajan con el trabajo que viene, no un resumen de lo que ya ha funcionado.

## Qué es cada cosa

- **Skill:** instrucciones empaquetadas que Claude carga cuando la tarea encaja (por ejemplo, cómo hacer TDD). Se activan solas o pidiéndolas por su nombre.
- **Agente:** un "rol" que Claude puede lanzar como subagente con un enfoque concreto (por ejemplo, diseñador de juegos).
- **Plugin:** un paquete que puede traer skills, comandos y otras cosas.

## Recomendadas

### Para todos

| Skill | Para qué nos sirve aquí |
| --- | --- |
| `git-workflow-and-versioning` | El flujo de ramas, commits pequeños y PR de la sección 13 de `DUALOCKE.md`. |
| `debugging-and-error-recovery` | Cuando el CI falla, no compila o un test se rompe: buscar la causa en vez de parchear. |
| `code-review-and-quality` | Revisar el PR del otro antes de fusionar. También existe el comando integrado `/code-review`. |
| `documentation-and-adrs` | Dejar las decisiones en `DUALOCKE.md` y en `registro/` con su porqué. |
| `ci-cd-and-automation` | Si hay que volver a tocar el CI (como cuando quitamos FireRed y LeafGreen). |

### Para Jorge (funcionalidades)

| Skill | Para qué |
| --- | --- |
| `test-driven-development` | La expansion tiene un sistema de tests de combate (`test/battle/`, `make check`). Las reglas del locke (vidas, primera captura, bloqueos) se pueden probar con tests antes de jugar. |
| `incremental-implementation` | Funcionalidades que tocan muchos archivos (vidas + caja de muertos, segundo dependiente), en pasos pequeños que compilen. |
| `spec-driven-development` | Antes de programar el randomizer: escribir qué hace, qué entra y qué sale, y cómo encaja con los niveles que pone Miguel. |
| `planning-and-task-breakdown` | Partir el randomizer en tareas. |

### Para Miguel (equilibrio)

| Skill / agente | Para qué |
| --- | --- |
| `interview-me` (skill) | Que Claude te pregunte una cosa cada vez hasta tener claras las decisiones de equilibrio (curva, jefes, megas). |
| **Game Designer** (agente) | Revisar la curva de dificultad, los equipos de los jefes y el ritmo del juego. |
| **Economy Designer** (agente) | Precios de las tiendas, qué vende el segundo dependiente y cuántas megapiedras. |
| **Level Designer** (agente) | Qué hay en cada tramo entre medallas y cómo se reparten los combates. |

Para usar un agente basta con pedirlo: *"usa el agente Game Designer para revisar la curva de niveles"*.

### Opcionales

- **`claude-mem`** (plugin): memoria entre sesiones en tu propio PC. No sustituye a `DUALOCKE.md` y `registro/`, que son la memoria **compartida** entre los dos. Útil, pero no imprescindible.
- `doubt-driven-development`: que Claude revise a fondo una decisión arriesgada (por ejemplo, tocar el guardado para las vidas).
- `shipping-and-launch`: cuando toque repartir el juego como parche `.bps`.

## No aportan nada a este proyecto

Las skills de web y diseño (`frontend-ui-engineering`, `design-taste-frontend`, `web-design-guidelines`, `image-to-code`, `browser-testing-with-devtools`), APIs (`api-and-interface-design`), vídeo (`remotion-best-practices`), Instagram (`instagram-skills`), seguridad web y observabilidad. Se pueden tener instaladas, pero no hace falta copiarlas.

## Cómo instalarlas

Desde una terminal con Node.js. Son los mismos repos de los que las instaló Miguel:

```bash
# Casi todas las skills recomendadas (git, debugging, TDD, specs, interview-me…)
npx skills add addyosmani/agent-skills

# Para buscar e instalar más skills desde Claude
npx skills add vercel-labs/skills
```

Si pregunta dónde instalarlas, elige **Claude Code** y la instalación **global** (en tu usuario), que es como las tiene Miguel.

Plugin de memoria (opcional), desde una sesión de `claude` en la terminal:

```
/plugin marketplace add thedotmack/claude-mem
/plugin install claude-mem
```

Los **agentes** (Game Designer, Economy Designer, Level Designer…) son archivos `.md` en `~/.claude/agents/` del PC de Miguel. No se ha podido comprobar de qué repositorio vienen, así que lo más fácil es que Miguel te pase esos archivos y los copies en la misma carpeta de tu PC.
