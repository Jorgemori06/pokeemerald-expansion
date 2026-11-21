// Emulador sin pantalla para probar la ROM: lee órdenes por stdin, una por línea.
//   run N            avanza N fotogramas con las teclas actuales
//   keys MASK        teclas pulsadas (bits GBA: A=1 B=2 Sel=4 Start=8 Der=16 Izq=32 Arr=64 Abj=128 R=256 L=512)
//   r8/r16/r32 ADDR  lee memoria
//   w8/w16/w32 ADDR V escribe memoria
//   shot FILE        guarda la pantalla en PPM
//   save FILE / load FILE   estado
#include <mgba/core/core.h>
#include <mgba/core/serialize.h>
#include <mgba-util/vfs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <mgba/core/log.h>
#include <mgba/internal/arm/arm.h>
static void sinlog(struct mLogger *l, int c, enum mLogLevel n, const char *f, va_list a) { (void)l; (void)c; (void)n; (void)f; (void)a; }
static struct mLogger sLogger = { .log = sinlog };

int main(int argc, char **argv) {
    if (argc < 2) return 1;
    mLogSetDefaultLogger(&sLogger);
    struct mCore *core = mCoreFind(argv[1]);
    if (!core || !core->init(core)) { fprintf(stderr, "sin core\n"); return 1; }
    mCoreInitConfig(core, NULL);
    unsigned w, h; core->desiredVideoDimensions(core, &w, &h);
    uint32_t *buf = malloc(w * h * 4);
    core->setVideoBuffer(core, (void *)buf, w);
    if (!mCoreLoadFile(core, argv[1])) { fprintf(stderr, "no carga\n"); return 1; }
    if (argc > 2) { struct VFile *vf = VFileOpen(argv[2], O_RDWR); if (vf) core->loadSave(core, vf); }
    core->reset(core);
    char line[512]; unsigned keys = 0;
    while (fgets(line, sizeof line, stdin)) {
        char cmd[32], arg[400]; unsigned long a = 0, v = 0; arg[0] = 0;
        if (sscanf(line, "%31s %399s", cmd, arg) < 1) continue;
        a = strtoul(arg, NULL, 0);
        char *rest = strchr(line, ' '); if (rest) { rest = strchr(rest + 1, ' '); if (rest) v = strtoul(rest + 1, NULL, 0); }
        if (!strcmp(cmd, "run")) { for (unsigned long i = 0; i < a; i++) { core->setKeys(core, keys); core->runFrame(core); } puts("ok"); }
        else if (!strcmp(cmd, "keys")) { keys = a; puts("ok"); }
        else if (!strcmp(cmd, "r8")) printf("%u\n", core->busRead8(core, a));
        else if (!strcmp(cmd, "r16")) printf("%u\n", core->busRead16(core, a));
        else if (!strcmp(cmd, "r32")) printf("%u\n", core->busRead32(core, a));
        else if (!strcmp(cmd, "w8")) { core->busWrite8(core, a, v); puts("ok"); }
        else if (!strcmp(cmd, "w16")) { core->busWrite16(core, a, v); puts("ok"); }
        else if (!strcmp(cmd, "w32")) { core->busWrite32(core, a, v); puts("ok"); }
        else if (!strcmp(cmd, "shot")) {
            FILE *f = fopen(arg, "wb"); fprintf(f, "P6 %u %u 255\n", w, h);
            for (unsigned i = 0; i < w * h; i++) { uint32_t c = buf[i]; fputc(c & 0xFF, f); fputc((c >> 8) & 0xFF, f); fputc((c >> 16) & 0xFF, f); }
            fclose(f); puts("ok");
        }
        else if (!strcmp(cmd, "save")) { struct VFile *vf = VFileOpen(arg, O_CREAT | O_TRUNC | O_RDWR); mCoreSaveStateNamed(core, vf, SAVESTATE_ALL); vf->close(vf); puts("ok"); }
        else if (!strcmp(cmd, "load")) { struct VFile *vf = VFileOpen(arg, O_RDONLY); mCoreLoadStateNamed(core, vf, SAVESTATE_ALL); vf->close(vf); puts("ok"); }
        else if (!strcmp(cmd, "hasta_pc")) {
            // ejecuta hasta llegar a la dirección V (o A pasos) y dice las últimas 256 instrucciones
            struct ARMCore *cpu = core->cpu; unsigned ult[8192] = {0}, n = 0; unsigned long i;
            core->setKeys(core, keys);
            for (i = 0; i < a; i++) { core->step(core); ult[n++ & 8191] = cpu->gprs[15]; if ((cpu->gprs[15] & ~1u) >= (v & ~1u) && (cpu->gprs[15] & ~1u) <= (v & ~1u) + 8) break; }
            printf("%lu", i); for (unsigned k = 0; k < 8192 && k < n; k++) printf(" %u", ult[(n - 1 - k) & 8191]); puts("");
        }
        else if (!strcmp(cmd, "vigila")) {
            // ejecuta instrucción a instrucción hasta que cambia la palabra de la dirección A (o V pasos) y dice
            // las últimas instrucciones
            struct ARMCore *cpu = core->cpu; static unsigned ult[8192]; unsigned n = 0; unsigned long i;
            uint32_t antes = core->busRead32(core, a);
            core->setKeys(core, keys);
            for (i = 0; i < v; i++) { core->step(core); ult[n++ & 8191] = cpu->gprs[15]; if (core->busRead32(core, a) != antes) break; }
            printf("%lu %u", i, (unsigned) core->busRead32(core, a)); for (unsigned k = 0; k < 8192 && k < n; k++) printf(" %u", ult[(n - 1 - k) & 8191]); puts("");
        }
        else if (!strcmp(cmd, "salto_malo")) {
            // ejecuta hasta que en la dirección A se salta por r3 a una dirección baja; dice r0-r7
            struct ARMCore *cpu = core->cpu; unsigned long i;
            core->setKeys(core, keys);
            for (i = 0; i < v; i++) {
                unsigned antes = cpu->gprs[15];
                core->step(core);
                // el salto: desde cerca de A a una dirección baja
                if (antes >= a && antes <= a + 8 && (unsigned) cpu->gprs[15] < 0x4000) break;
            }
            printf("%lu", i); for (int k = 0; k < 8; k++) printf(" %u", (unsigned) cpu->gprs[k]); printf(" %u\n", (unsigned) cpu->gprs[14]);
        }
        else if (!strcmp(cmd, "pc")) { struct ARMCore *cpu = core->cpu; printf("%u %u\n", (unsigned) cpu->gprs[15], (unsigned) cpu->gprs[14]); }
        else if (!strcmp(cmd, "hasta_cero")) {
            // ejecuta instrucción a instrucción hasta que el PC baja de 8 (reinicio) y dice las últimas
            struct ARMCore *cpu = core->cpu; static unsigned ult[65536]; unsigned n = 0; unsigned long i;
            core->setKeys(core, keys);
            for (i = 0; i < a; i++) { core->step(core); ult[n++ & 65535] = cpu->gprs[15]; if (cpu->gprs[15] < 8) break; }
            printf("%lu", i); for (unsigned k = 0; k < 65536 && k < n; k++) printf(" %u", ult[(n - 1 - k) & 65535]); puts("");
        }
        else if (!strcmp(cmd, "hasta_pc")) {
            // ejecuta hasta llegar a la dirección V (o A pasos) y dice las últimas 256 instrucciones
            struct ARMCore *cpu = core->cpu; unsigned ult[8192] = {0}, n = 0; unsigned long i;
            core->setKeys(core, keys);
            for (i = 0; i < a; i++) { core->step(core); ult[n++ & 8191] = cpu->gprs[15]; if ((cpu->gprs[15] & ~1u) >= (v & ~1u) && (cpu->gprs[15] & ~1u) <= (v & ~1u) + 8) break; }
            printf("%lu", i); for (unsigned k = 0; k < 8192 && k < n; k++) printf(" %u", ult[(n - 1 - k) & 8191]); puts("");
        }
        else if (!strcmp(cmd, "vigila")) {
            // ejecuta instrucción a instrucción hasta que cambia la palabra de la dirección A (o V pasos) y dice
            // las últimas instrucciones
            struct ARMCore *cpu = core->cpu; static unsigned ult[8192]; unsigned n = 0; unsigned long i;
            uint32_t antes = core->busRead32(core, a);
            core->setKeys(core, keys);
            for (i = 0; i < v; i++) { core->step(core); ult[n++ & 8191] = cpu->gprs[15]; if (core->busRead32(core, a) != antes) break; }
            printf("%lu %u", i, (unsigned) core->busRead32(core, a)); for (unsigned k = 0; k < 8192 && k < n; k++) printf(" %u", ult[(n - 1 - k) & 8191]); puts("");
        }
        else if (!strcmp(cmd, "salto_malo")) {
            // ejecuta hasta que en la dirección A se salta por r3 a una dirección baja; dice r0-r7
            struct ARMCore *cpu = core->cpu; unsigned long i;
            core->setKeys(core, keys);
            for (i = 0; i < v; i++) {
                unsigned antes = cpu->gprs[15];
                core->step(core);
                // el salto: desde cerca de A a una dirección baja
                if (antes >= a && antes <= a + 8 && (unsigned) cpu->gprs[15] < 0x4000) break;
            }
            printf("%lu", i); for (int k = 0; k < 8; k++) printf(" %u", (unsigned) cpu->gprs[k]); printf(" %u\n", (unsigned) cpu->gprs[14]);
        }
        else if (!strcmp(cmd, "pc")) { struct ARMCore *cpu = core->cpu; printf("%u %u\n", (unsigned) cpu->gprs[15], (unsigned) cpu->gprs[14]); }
        else if (!strcmp(cmd, "hasta_cero")) {
            // ejecuta instrucción a instrucción hasta saltar a la dirección 0 (o hasta A pasos) y dice las últimas
            struct ARMCore *cpu = core->cpu; unsigned ult[256] = {0}, n = 0; unsigned long i;
            core->setKeys(core, keys);
            for (i = 0; i < a; i++) {
                unsigned antes = cpu->gprs[15];
                core->step(core); ult[n++ & 255] = cpu->gprs[15];
                // entrada a la BIOS que no es por SWI (0x08) ni por interrupción (0x18): salto malo
                if (cpu->gprs[15] < 0x4000 && antes >= 0x4000 && cpu->gprs[15] > 0x20) break;
            }
            printf("%lu", i); for (unsigned k = 0; k < 256 && k < n; k++) printf(" %u", ult[(n - 1 - k) & 255]); puts("");
        }
        else puts("?");
        fflush(stdout);
    }
    return 0;
}
