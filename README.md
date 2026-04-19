# 1080 Snowboarding n64 decompilation

In progress 1080 Snowboarding decompilation, mostly driven by Claude. Uses https://github.com/bigyoshi51/decomp for n64 common tooling, Claude skills, etc.

## Status

Nineteen segments are being decompiled. USO overlays ship as a custom relocatable format (some Yay0-compressed); we match pre-relocation bytes by splatting at `VRAM=0` with per-segment symbol prefixes (`gl_func_`, `gui_func_`, etc.).

| Segment        | Functions   | Code matched       | Notes                                          |
|----------------|-------------|--------------------|------------------------------------------------|
| `kernel`       | 96 / 237    | 10.0 KB / 40.0 KB  | libultra + USO loader + audio (`0x80000000`)   |
| `bootup_uso`   | 125 / 359   | 5.7 KB / 81.6 KB   | Giles Goddard's libgdl engine                  |
| `game_libs`    | 217 / 1,371 | 10.7 KB / 468.7 KB | Support libraries — wrapper mass-match (15.8 %)|
| `gui_uso`      | 4 / 22      | 0.2 KB / 18.1 KB   | GUI/menu helpers                               |
| `titproc_uso`  | 8 / 43      | 0.5 KB / 10.5 KB   | Title-screen process (templates + composites)  |
| `arcproc_uso`  | 5 / 50      | 0.2 KB / 10.4 KB   | Arcade-mode process                            |
| `h2hproc_uso`  | 3 / 36      | 0.1 KB / 6.8 KB    | Head-to-head process                           |
| `eddproc_uso`  | 2 / 12      | 0.1 KB / 1.1 KB    | Edit-mode process                              |
| `n64proc_uso`  | 0 / 6       | 0.0 KB / 1.0 KB    | N64-specific process                           |
| `boarder1..5_uso` | 20 / 30  | 0.7 KB / 2.1 KB    | Per-character snowboarder USOs — 67 % matched  |
| `mgrproc_uso`  | 7 / 50      | 0.3 KB / 13.0 KB   | Manager process (Yay0-decompressed)            |
| `game_uso`     | 33 / 201    | 1.2 KB / 70.8 KB   | Main game loop (Yay0-decompressed)             |
| `timproc_uso_b1,b3,b5` | 20 / 209 | 0.7 KB / 81.9 KB | Timer process variants (Yay0-decompressed)  |
| `map4_data_uso_b2` | 2 / 3   | 0.1 KB / —         | Map-4 data block                               |
| **Total**      | **542 / 2,629** | **32.8 KB / 805.7 KB (4.07%)** |                                |

Remaining Yay0-compressed USOs are now splatted; `map4_data` and pure data USOs (audio banks, character meshes, textures) stay as `bin` segments.

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
