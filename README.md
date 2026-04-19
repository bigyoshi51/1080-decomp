# 1080 Snowboarding n64 decompilation

In progress 1080 Snowboarding decompilation, mostly driven by Claude. Uses https://github.com/bigyoshi51/decomp for n64 common tooling, Claude skills, etc.

## Status

Fourteen segments are being decompiled. USO overlays ship as a custom relocatable format; we match pre-relocation bytes by splatting at `VRAM=0` with per-segment symbol prefixes (`gl_func_`, `gui_func_`, etc.).

| Segment        | Functions   | Code matched       | Notes                                          |
|----------------|-------------|--------------------|------------------------------------------------|
| `kernel`       | 96 / 237    | 10.0 KB / 40.0 KB  | libultra + USO loader + audio (`0x80000000`)   |
| `bootup_uso`   | 124 / 359   | 5.7 KB / 81.6 KB   | Giles Goddard's libgdl engine                  |
| `game_libs`    | 196 / 1,371 | 9.6 KB / 468.7 KB  | Support libraries — wrapper mass-match         |
| `gui_uso`      | 1 / 22      | 0.0 KB / 18.1 KB   | GUI/menu helpers                               |
| `titproc_uso`  | 0 / 43      | 0.0 KB / 10.5 KB   | Title-screen process                           |
| `arcproc_uso`  | 0 / 50      | 0.0 KB / 10.4 KB   | Arcade-mode process                            |
| `h2hproc_uso`  | 0 / 36      | 0.0 KB / 6.8 KB    | Head-to-head process                           |
| `eddproc_uso`  | 0 / 12      | 0.0 KB / 1.1 KB    | Edit-mode process                              |
| `n64proc_uso`  | 0 / 6       | 0.0 KB / 1.0 KB    | N64-specific process                           |
| `boarder1..5_uso` | 0 / 30   | 0.0 KB / 2.1 KB    | Per-character snowboarder USOs (6 funcs each)  |
| **Total**      | **417 / 2,166** | **25.3 KB / 640.2 KB (3.95%)** |                                  |

Remaining un-splatted USOs (`mgrproc`, `timproc`, `game_uso`, `map4_data`) have non-standard headers — each contains only 1–5 detectable function prologues despite being 22 KB to 1.2 MB in size, suggesting either compression, encrypted code, or mostly-data USOs. These need hand-investigation. Pure data USOs (audio banks, character meshes, textures) stay as `bin` segments.

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
