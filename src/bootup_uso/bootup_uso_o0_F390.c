#include "common.h"

/* -O0 cluster at offsets 0xF390..0xF6C3. -O0 wrappers split out of
 * bootup_uso.c so they build at -O0 (matching the originals' frame +
 * spill+reload + b-+1 patterns). See feedback_ido_o0_register_and_inline.md,
 * project_1080_bootup_uso_o0_runs.md, and
 * feedback_o0_cluster_split_with_layout_shim.md. */

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

/* Two-block bit set/clear — set=1, masks 4 then 8. */
void func_0000F434(int *a0) {
    register int *p1, *p2;
    register int set;
    register int *t;
    p1 = (int*)((char*)a0 + 0x18);
    p2 = p1;
    set = 1;
    if (set) { t = p2; *t = *t | 4; }
    else     { t = p2; *t = *t & ~4; }

    p1 = (int*)((char*)a0 + 0x18);
    p2 = p1;
    set = 1;
    if (set) { t = p2; *t = *t | 8; }
    else     { t = p2; *t = *t & ~8; }
}

/* Two-block bit set/clear — set=0, masks 4 then 8. */
void func_0000F4CC(int *a0) {
    register int *p1, *p2;
    register int set;
    register int *t;
    p1 = (int*)((char*)a0 + 0x18);
    p2 = p1;
    set = 0;
    if (set) { t = p2; *t = *t | 4; }
    else     { t = p2; *t = *t & ~4; }

    p1 = (int*)((char*)a0 + 0x18);
    p2 = p1;
    set = 0;
    if (set) { t = p2; *t = *t | 8; }
    else     { t = p2; *t = *t & ~8; }
}

/* Single-block bit set/clear — set=0, mask=8. */
void func_0000F564(int *a0) {
    register int *p1, *p2;
    register int set;
    register int *t;
    p1 = (int*)((char*)a0 + 0x18);
    p2 = p1;
    set = 0;
    if (set) { t = p2; *t = *t | 8; }
    else     { t = p2; *t = *t & ~8; }
}

/* Single-block bit set/clear — set=1, mask=8. */
void func_0000F5BC(int *a0) {
    register int *p1, *p2;
    register int set;
    register int *t;
    p1 = (int*)((char*)a0 + 0x18);
    p2 = p1;
    set = 1;
    if (set) { t = p2; *t = *t | 8; }
    else     { t = p2; *t = *t & ~8; }
}

/* Single-block bit set/clear — set=0, mask=4. */
void func_0000F614(int *a0) {
    register int *p1, *p2;
    register int set;
    register int *t;
    p1 = (int*)((char*)a0 + 0x18);
    p2 = p1;
    set = 0;
    if (set) { t = p2; *t = *t | 4; }
    else     { t = p2; *t = *t & ~4; }
}

/* Single-block bit set/clear — set=1, mask=4. */
void func_0000F66C(int *a0) {
    register int *p1, *p2;
    register int set;
    register int *t;
    p1 = (int*)((char*)a0 + 0x18);
    p2 = p1;
    set = 1;
    if (set) { t = p2; *t = *t | 4; }
    else     { t = p2; *t = *t & ~4; }
}
