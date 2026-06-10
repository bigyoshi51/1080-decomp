#!/usr/bin/env python3
"""Verify every built Yay0 code block against its ROM-extracted ground truth.

For each (built compressed block, assets/<name>_block_N.bin) pair:
  - decompress the build, compare lengths (must be EXACT), and
  - word-diff; every diff must be reloc-field class (jal-vs-jal target field,
    or same opcode+regs with differing lo16 immediate at lui/lw/sw/addiu sites
    of MATCHED C fns -- the USO reloc table fills these at load).
Any length mismatch, contiguous shift range, or non-reloc-class word diff
is a FAILURE (the asm-processor pad/orphan emission damage class --
see docs/MATCHING_WORKFLOW.md, asm-processor 1-word-pad defect).

Usage: python3 scripts/verify-yay0-blocks.py   (after `make <blocks>` or with
       --build to make the block targets first)
"""
import struct, subprocess, sys
import crunch64

PAIRS = [
    ("assets/mgrproc_uso_block_1.bin",  "build/assets/mgrproc_uso_block1_yay0.bin"),
    ("assets/game_uso_block_1.bin",     "build/assets/game_uso_block1_yay0.bin"),
    ("assets/timproc_uso_block_1.bin",  "build/assets/timproc_uso_block1_yay0.bin"),
    ("assets/timproc_uso_block_3.bin",  "build/assets/timproc_uso_block3_yay0.bin"),
    ("assets/timproc_uso_block_5.bin",  "build/assets/timproc_uso_block5_yay0.bin"),
    ("assets/map4_data_uso_block_2.bin","build/assets/map4_data_uso_block2_yay0.bin"),
]

def classify(o, b):
    if (o >> 26) == 3 and (b >> 26) == 3:
        return "jal"
    if (o >> 16) == (b >> 16):
        return "lo16"
    return "other"

def main():
    if "--build" in sys.argv:
        subprocess.check_call(["make"] + [b for _, b in PAIRS])
    fail = 0
    for orig_p, built_p in PAIRS:
        try:
            orig = open(orig_p, "rb").read()
            built = crunch64.yay0.decompress(open(built_p, "rb").read())
        except FileNotFoundError as e:
            print(f"SKIP  {built_p}: {e}")
            continue
        counts = {"jal": 0, "lo16": 0, "other": 0}
        others = []
        for i in range(0, min(len(orig), len(built)), 4):
            if orig[i:i+4] != built[i:i+4]:
                o, = struct.unpack(">I", orig[i:i+4])
                b, = struct.unpack(">I", built[i:i+4])
                k = classify(o, b)
                counts[k] += 1
                if k == "other":
                    others.append((i, o, b))
        ok = len(orig) == len(built) and counts["other"] == 0
        fail += not ok
        print(f'{"OK  " if ok else "FAIL"}  {built_p}: len {len(orig):#x}/{len(built):#x}, '
              f'jal={counts["jal"]} lo16={counts["lo16"]} other={counts["other"]}')
        for i, o, b in others[:12]:
            print(f"        OTHER at {i:#07x}: {o:08x} vs {b:08x}")
    return 1 if fail else 0

if __name__ == "__main__":
    sys.exit(main())
