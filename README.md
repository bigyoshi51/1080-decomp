# 1080 Snowboarding (USA) Decompilation

A work-in-progress decompilation of 1080 Snowboarding for the Nintendo 64.

## Status

The kernel (libultra + USO loader + game init) is being decompiled.

```
$ ../../scripts/progress.sh
Decompilation Progress
Code:      ~2.0K / ~30K bytes (~7%)
Functions:   ~43 / ~298       (~14%)
```

## Building

```bash
# Requires: mips-linux-gnu binutils, IDO 7.1 (via ido-static-recomp)
make
```

The build uses IDO 7.1 with two optimization levels:
- `kernel_o2.c` — game code compiled with `-O2`
- `kernel_o1.c` — libultra functions compiled with `-O1`

## References

- **[libreultra](https://github.com/n64decomp/libreultra)** — Complete decompilation of Nintendo's libultra SDK. We use libreultra source as reference for matching libultra functions in the kernel. Function names, struct layouts, and `register` keyword usage are adapted from this project.
- **[splat](https://github.com/ethteck/splat)** — ROM splitting tool
- **[asm-processor](https://github.com/simonlindholm/asm-processor)** — Enables mixing C decompilation with INCLUDE_ASM stubs
- **[spimdisasm](https://github.com/Decompollaborate/spimdisasm)** — MIPS disassembler (via splat)
- **[decomp.me](https://decomp.me)** / **[objdiff](https://github.com/encounter/objdiff)** — Function-level matching and progress tracking

## Game Structure

1080 Snowboarding uses a **USO (Universal Shared Objects)** overlay system:
- **Kernel** (43K): libultra, USO loader, audio — the part being decompiled
- **bootup.uso** (277K): Giles Goddard's libgdl game engine (C++, 302 functions)
- **game_libs** (480K): Support libraries (1,371 functions)
- **mainuso** (13.6MB): Data modules (models, audio, textures)

Total: ~1,781 functions across the full ROM.
