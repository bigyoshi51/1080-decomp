# Land WIP: func_00010540 -O0 exact-match grind

NOT built (`.txt` / outside src). The typed-struct -O0 body for
func_00010540, validated standalone at 364 vs 343 insns (structure exact).
Remaining: ~250 -O0 temp-register-numbering diffs cascading from the first
divergence `if (i != arg0->unk7C)` (operand eval order). See the -O0 LAND
SPEC comment in src/bootup_uso/bootup_uso_tail3a.c and the
project_1080_big_swing_strategy memo.

Grind workflow:
  cc -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O0 -mips2 -32 \
     -I include -I src -o /tmp/t.o landwip/func_00010540_o0_wip.c.txt
  python3 scripts/disasm-func.py func_00010540 --obj /tmp/t.o > /tmp/mine.s
  # diff vs target (normalize .L<hex> labels), fix first divergence, repeat top-down.
When exact: 3-way tail3a split + bootup_uso_o0_10540.c (OPT_FLAGS -O0) +
empirical TRUNCATE_TEXT, then scripts/land-successful-decomp.sh.
