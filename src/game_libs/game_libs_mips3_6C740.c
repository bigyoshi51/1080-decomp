#include "common.h"

/* 64-bit libgcc-style helpers, statically linked into the game_libs USO.
 * Byte-identical masked-twins (0 relocs, self-contained) of the matched kernel
 * kernel_056.c family. Compile -O2 -mips3 so IDO inlines the d-arithmetic
 * (ddivu/dmultu/dsrav/...) instead of emitting jal back to themselves. The
 * "should not be used for ucode 32-bit compiles" warning is expected. Spliced
 * into game_libs_post1b2c.c.o (default -O2 -mips2) via REPLACE_FUNC_BODY, same
 * recipe as the landed game_libs_func_0006C8AC divmod. */

unsigned long long game_libs_func_0006C740(unsigned long long a, unsigned long long b) { return a % b; }  /* __ull_rem  <- func_80002A3C */
unsigned long long game_libs_func_0006C7E4(unsigned long long a, unsigned long long b) { return a % b; }  /* __ull_rem (dup) <- func_80002AE0 */
unsigned long long game_libs_func_0006C77C(unsigned long long a, unsigned long long b) { return a / b; }  /* __ull_div  <- func_80002A78 */
unsigned long long game_libs_func_0006C7B8(unsigned long long a, unsigned long long b) { return a << b; } /* __ll_lshift <- func_80002AB4 */
long long game_libs_func_0006C820(long long a, long long b) { return a / b; }  /* __ll_div <- func_80002B1C */
long long game_libs_func_0006C87C(long long a, long long b) { return a * b; }  /* __ll_mul <- func_80002B78 */
long long game_libs_func_0006C9A8(long long a, long long b) { return a >> b; } /* __ll_rshift <- func_80002CA4 */

/* gl_func_0006C90C (Euclidean mod <- func_80002C08) NOT ported here: standalone
 * -O2 -mips3 leaf-optimizes (33 insns) vs the in-context kernel form (39 insns
 * w/ arg homing). TU-context divergence; left INCLUDE_ASM. */
