#!/usr/bin/env python3
"""Extract Yay0-compressed blocks from 1080's compressed USOs.

For each USO that contains Yay0 blocks (game.uso, mgrproc.uso, timproc.uso,
map4_data.uso), this:
  1. Finds every `Yay0` magic.
  2. Decompresses each block.
  3. Verifies a re-compression round-trips byte-exact (sanity check).
  4. Writes each decompressed block to `assets/<usoname>_block_<N>.bin`.
  5. Prints the inter-block 16-byte descriptor for each block (for format RE).

Crunch64 is the byte-exact Yay0 encoder used by papermario in production —
verified to match all 23 Yay0 blocks in 1080's baserom.

Usage:
    python3 scripts/extract-uso-yay0.py [--write]

Without --write, only prints. With --write, dumps decompressed blocks to assets/.
"""
import argparse
import struct
import sys
from pathlib import Path

import crunch64

# (name, fs_rom_start, end_rom)
USOS = [
    ("game_uso",      0x7CC8D8, 0x84F6F8),
    ("mgrproc_uso",   0x5A015C, 0x5A5BE0),
    ("timproc_uso",   0x5AF0EC, 0x6E466C),
    ("map4_data_uso", 0x6E466C, 0x7CC8D8),
]


def find_inner_data_magic(data: bytes, fs: int, end: int) -> int | None:
    for i in range(fs + 4, end, 4):
        if struct.unpack(">I", data[i:i+4])[0] == 0x12345678:
            return i
    return None


def find_yay0_blocks(data: bytes, fs: int, end: int) -> list[int]:
    return sorted(i for i in range(fs, end) if data[i:i+4] == b'Yay0')


def main():
    p = argparse.ArgumentParser()
    p.add_argument("--write", action="store_true",
                   help="Write decompressed blocks to assets/<name>_block_<N>.bin")
    p.add_argument("--rom", default="baserom.z64")
    args = p.parse_args()

    data = open(args.rom, "rb").read()
    out_dir = Path("assets")

    total_blocks = 0
    total_match = 0
    for name, fs, end in USOS:
        data_off = find_inner_data_magic(data, fs, end)
        starts = find_yay0_blocks(data, fs, end) + [end]
        nblocks = len(starts) - 1
        print(f"\n=== {name} ({(end-fs)/1024:.1f} KB, inner@0x{data_off:X}, {nblocks} Yay0 blocks) ===")
        for i in range(nblocks):
            start = starts[i]
            slice_ = data[start:starts[i+1]]
            try:
                dec = crunch64.yay0.decompress(slice_)
                recomp = crunch64.yay0.compress(dec)
                csize = len(recomp)
                actual = data[start:start+csize]
                ok = (recomp == actual)
            except Exception as e:
                print(f"  block {i}: ERROR decompress/compress: {e}")
                continue

            # 8-byte inter-block descriptor immediately before the Yay0 magic
            desc_before = data[max(start - 8, data_off):start]
            print(f"  block {i}: ROM 0x{start:X} (off 0x{start-data_off:X})  "
                  f"csize=0x{csize:X}  usize=0x{len(dec):X}  match={ok}  "
                  f"hdr={desc_before.hex()}")

            total_blocks += 1
            if ok: total_match += 1

            if args.write:
                out = out_dir / f"{name}_block_{i}.bin"
                out.write_bytes(dec)

    print(f"\nTotal: {total_match}/{total_blocks} blocks round-trip byte-exact via crunch64")
    return 0 if total_match == total_blocks else 1


if __name__ == "__main__":
    sys.exit(main())
