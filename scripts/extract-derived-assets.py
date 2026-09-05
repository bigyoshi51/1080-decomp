#!/usr/bin/env python3
"""Produce the assets/*.bin files the build needs that `splat split --modes bin`
does NOT emit. Idempotent; run by `make setup` after splat.

Two kinds, both derived deterministically from baserom.z64:

  1. Hand-carved linker inputs referenced directly by tenshoe.ld
     (`build/assets/kernel.data.bin.o(.data)`, `build/assets/game_uso.bin.o`).
     They were carved once in March 2026 (f823d9730 / 627062f6d) and the
     splat config never described them, so a fresh checkout had no producer
     and the link died with `cannot find build/assets/kernel.data.bin.o`.
     ROM offset = segment ROM start + (VRAM - segment VRAM) from build/tenshoe.map.

  2. Decompressed Yay0 code blocks, the ground truth for
     scripts/verify-yay0-blocks.py (`make verify-blocks`). Each is the Yay0
     decompression of the compressed block splat extracts.

Every output is checked against its known md5 so a wrong offset or a changed
compressor fails loudly instead of silently producing a different ROM.
"""
import hashlib
import sys
from pathlib import Path

import crunch64

ROM = Path("baserom.z64")
ASSETS = Path("assets")

# name, rom_offset, length, md5
CARVES = [
    ("kernel.data.bin", 0x1000 + 0x9FD0, 0xABC0 - 0x9FD0, "54ee36f69c570006dc4a32bb2d80a82e"),
    ("game_uso.bin",    0x7CC8D8,        0x84F6F8 - 0x7CC8D8, "fc4a7916f834306a58147dc020388b16"),
]

# decompressed name, compressed (splat output) name, md5 of decompressed
YAY0_BLOCKS = [
    ("game_uso_block_1.bin",      "game_uso_block1_yay0.bin",      "23b30258f022d8ca64434048be7fd7c6"),
    ("map4_data_uso_block_2.bin", "map4_data_uso_block2_yay0.bin", "1b4598c9f9e04224e9ac1e043e1ee1bc"),
    ("mgrproc_uso_block_1.bin",   "mgrproc_uso_block1_yay0.bin",   "45920b67db0457c3d9214d2a7aef0037"),
    ("timproc_uso_block_1.bin",   "timproc_uso_block1_yay0.bin",   "3ae39c485b3bda7ae67a4350c20d20e1"),
    ("timproc_uso_block_3.bin",   "timproc_uso_block3_yay0.bin",   "dae258fa2777bd76c8561703ad1592fa"),
    ("timproc_uso_block_5.bin",   "timproc_uso_block5_yay0.bin",   "5d6ac34e0da9c90200a937254fe47d04"),
]


def emit(name: str, data: bytes, want_md5: str) -> None:
    got = hashlib.md5(data).hexdigest()
    if got != want_md5:
        sys.exit(f"extract-derived-assets: {name}: md5 {got}, expected {want_md5}")
    out = ASSETS / name
    if out.exists() and out.read_bytes() == data:
        print(f"  {name}: up to date")
        return
    out.write_bytes(data)
    print(f"  {name}: wrote {len(data)} bytes")


def main() -> None:
    if not ROM.exists():
        sys.exit("extract-derived-assets: baserom.z64 not found")
    rom = ROM.read_bytes()
    ASSETS.mkdir(exist_ok=True)

    print("ROM carves:")
    for name, off, length, md5 in CARVES:
        emit(name, rom[off : off + length], md5)

    print("Yay0 decompressed blocks:")
    for name, comp, md5 in YAY0_BLOCKS:
        src = ASSETS / comp
        if not src.exists():
            sys.exit(f"extract-derived-assets: missing {src} -- run splat (make setup) first")
        emit(name, crunch64.yay0.decompress(src.read_bytes()), md5)


if __name__ == "__main__":
    main()
