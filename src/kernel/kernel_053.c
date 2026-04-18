#include "common.h"

extern s32 D_8000A410;

typedef struct {
    void* field_0;
    void* field_4;
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s32 field_14;
} Foo;

/* Initialize a 6-field struct: two pointers to D_8000A410, two zeros,
 * then a2 and a1 at fields 0x10 and 0x14. Absorbs the original
 * func_80004FE0 fragment. */
void func_80004FD0(Foo* a0, s32 a1, s32 a2) {
    a0->field_0 = &D_8000A410;
    a0->field_4 = &D_8000A410;
    a0->field_8 = 0;
    a0->field_C = 0;
    a0->field_10 = a2;
    a0->field_14 = a1;
}
