# USO reloc-blind cap flip — execution plan (user-authorized 2026-05-31)

Goal: flip the ~150 reloc-blind near-miss caps to byte-match by making `expected/*.o`
reloc-aware (reloc-form) instead of raw-`.word` baked, so it compares equal to the
build's reloc-form `.o`. Validated mechanism; the existing symbolize tool covers only
part of it — see the extension below.

## Why the existing tool is insufficient

`scripts/emu-symdump/game-uso-symbolize-s.py` rewrites ONLY `imm==0` placeholder words
(`jal 0`, `lui rt,0`, `<memop> rt,rs,0`) → named reloc-form. Those words ALREADY
byte-match (imm 0 == imm 0); symbolizing them only adds real call-graph NAMES (episode
quality), it does NOT flip a cap. The reloc-blind CAPS are the opposite shape: the
`expected/.s` has the offset/target **baked** (imm != 0), e.g.

| function (real-C body)            | expected (baked)        | build (reloc-form) | class        |
|-----------------------------------|-------------------------|--------------------|--------------|
| eddproc_uso_func_0000015C         | `sw zero, 4(at)`        | `sw zero, 0(at)`+LO16 | scalar %lo |
| timproc_uso_b1_func_0000065C      | `sw s0, 0x14C(at)`      | `sw s0, 0(at)`+LO16   | scalar %lo |
| game_uso_func_00003968 (×many)    | `jal 0x280` (baked)     | `jal 0`+R_MIPS_26     | intra jal  |
| game_uso_func_0000EDD4            | `lw t6, 0x224(at)`      | `lw t6, 0x14(at)` (local jtbl) | jumptable |

For these the build's reloc-form `.o` (imm 0 + reloc) is byte-correct post-link; only
the raw-`.word` `expected/.o` differs. Fix = rewrite the BAKED expected word to
reloc-form so both carry imm 0 + a reloc to the same symbol.

## Extension needed (the actual work)

Extend the symbolize emitter to also handle `imm != 0` words at a reloc site, using the
symnames table (offset -> name) to recover the target symbol and emitting:
- `lui rt, %hi(NAME)` for the paired HI16 (already imm 0 in these cases),
- `<memop> rt, %lo(NAME)(rs)` for the LO16 (currently baked imm != 0),
- `jal NAME` for a baked intra `jal` (NAME = the intra target at that module offset),
  defined to its module offset so it re-bakes identically post-link.
Define each NAME's VALUE in `undefined_syms_auto.txt` (data sym -> its module offset,
intra func -> its module offset) so the link resolves %hi/%lo/jal back to the SAME ROM
bytes. NAME=0 is WRONG here (that's only for true cross-module imports that resolve 0).

## Per-function validation gate (REQUIRED before committing any flip)

1. Symbolize the function's `expected/.s` reloc words -> reloc-form; define NAME values.
2. `make expected` for that one `.c.o`; byte_verify build/src/<f>.c.o .text ==
   expected/src/<f>.c.o .text (the cap flips to 0 diffs).
3. **Link check: the LINKED ROM bytes for that function MUST be unchanged** (the reloc
   resolves to the same baked value). Build tenshoe.elf, objdump the function's linked
   `.text`, compare to the pre-flip linked bytes. If the ROM changed, the NAME value is
   wrong — revert.
4. report.json for that function -> 100% (objdiff resolves both relocs to the same value).

## First target (next tick)

`eddproc_uso_func_0000015C` — single scalar `sw zero, 4(at)` -> reloc-form to a data
symbol at module offset 0x4. Smallest, isolated, non-colliding (eddproc, -O2). Prove
the extension + gate end-to-end on it, THEN generalize per-class.

## Episode-eligibility — DEFERRED TO USER (do NOT log USO episodes unsupervised)

Per the migration notes: whether a flipped USO match (reloc-form bytes + ROM-correct
relocs) is EPISODE-ELIGIBLE, and wiring `uso-reloc-encode.validate_func` into the land
script, is a USER decision. Flip + byte-match + report.json gain are safe to land; the
EPISODE log is NOT — bring the policy to the user after the mechanism is proven.
