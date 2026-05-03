#include "common.h"

/* -O0 cluster at offsets 0xF390..0xF430. Three -O0 wrappers split out of
 * bootup_uso.c so they can build at -O0 (matching the originals' frame +
 * spill+reload + b-+1 patterns). See feedback_ido_o0_register_and_inline.md
 * and project_1080_bootup_uso_o0_runs.md. */

extern int func_00000000();
extern char D_00000000;
extern char D_0000C574;

void func_0000F390(void) {
    register char *p = &D_00000000;
    func_00000000(p, &D_0000C574);
}

void func_0000F3D4(int a0) {
    func_00000000(a0);
}

void func_0000F404(int a0) {
    func_00000000(a0);
}
