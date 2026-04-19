# 1080 Snowboarding n64 decompilation

In progress 1080 Snowboarding decompilation, mostly driven by Claude. Uses https://github.com/bigyoshi51/decomp for n64 common tooling, Claude skills, etc.

## Status

Three segments are now being decompiled. USO overlays ship as a custom relocatable format; we match pre-relocation bytes by splatting at `VRAM=0` with distinct per-segment symbol prefixes.

| Segment        | Functions  | Code matched       | Notes                                     |
|----------------|------------|--------------------|-------------------------------------------|
| `kernel`       | 87 / 253   | 8.1 KB / 41.3 KB   | libultra + USO loader + audio (`0x80000000`) |
| `bootup_uso`   | 124 / 359  | 5.7 KB / 81.6 KB   | Giles Goddard's libgdl engine             |
| `game_libs`    | 0 / 1,371  | 0 B / 469 KB       | Support libraries — setup only            |
| **Total**      | **218 / 1,967** | **14.6 KB / 590 KB (2.48%)** |                                 |

Remaining USO overlays (`game.uso`, character models, audio banks, etc.) are still opaque binary blobs — wiring them up is straightforward but currently deferred.

## Building

Requires: `mips-linux-gnu` binutils, Python 3, and IDO 7.1.

```bash
# 1. Place your 1080 Snowboarding (USA) ROM as baserom.z64
# 2. Extract IDO 7.1:
#    https://github.com/decompals/ido-static-recomp/releases/latest
#    Extract into tools/ido-static-recomp/build/7.1/out/
# 3. Extract asset bins from baserom via splat (one-time):
make setup
# 4. Build:
make
```

ROM-derived binary extracts (`assets/*.bin`) are not committed — they are regenerated from your local baserom by `make setup`.

The build uses IDO 7.1 with per-file optimization overrides: most libultra functions compile at `-O1`, game code at `-O2`.

## References

- **[libreultra](https://github.com/n64decomp/libreultra)** — libultra decomp reference; matching functions, structs, `register` keyword usage
- **[splat](https://github.com/ethteck/splat)** — ROM splitting tool
- **[asm-processor](https://github.com/simonlindholm/asm-processor)** — Mixes C decompilation with INCLUDE_ASM stubs
- **[spimdisasm](https://github.com/Decompollaborate/spimdisasm)** — MIPS disassembler (via splat)
- **[decomp.me](https://decomp.me)** / **[objdiff](https://github.com/encounter/objdiff)** — Function-level matching, progress tracking, decomp.dev integration

## Game Structure

1080 Snowboarding uses a **USO (Universal Shared Objects)** overlay system loaded at runtime:

- **Kernel** (41 KB, 253 functions, VRAM `0x80000000`) — libultra, USO loader, audio
- **bootup_uso** (82 KB, 359 functions, VRAM `0`) — libgdl game engine (C++, debug strings preserved)
- **game_libs** (469 KB, 1,371 functions, VRAM `0`) — support libraries (stripped)
- **mainuso** (13.6 MB) — compressed data modules (models, audio, textures)

Both USO segments splat at synthetic `VRAM=0` to match unrelocated ROM bytes; distinct symbol prefixes (`func_` vs `gl_func_`) avoid linker collisions between them.
