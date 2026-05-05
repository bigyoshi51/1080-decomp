# 1080 Snowboarding n64 decompilation

In progress 1080 Snowboarding decompilation, mostly driven by Claude. Uses https://github.com/bigyoshi51/decomp for n64 common tooling, Claude skills, etc.

## Status

Nineteen segments are being decompiled. USO overlays ship as a custom relocatable format (some Yay0-compressed); we match pre-relocation bytes by splatting at `VRAM=0` with per-segment symbol prefixes (`gl_func_`, `gui_func_`, etc.).

`Matched` is the share of code bytes whose C body compiles to baserom byte-for-byte. `Fuzzy` is bytes-weighted partial credit: NM-wrapped C bodies that aren't byte-perfect contribute their per-instruction similarity (e.g., a 1 KB function at 80 % match adds ~800 bytes of fuzzy credit). Both metrics use a separate `build/non_matching/` tree compiled with `-DNON_MATCHING` so partial decomp work shows up in the report.

| Segment        | Functions       | Code matched           | Matched   | Fuzzy     | Notes                                          |
|----------------|-----------------|------------------------|-----------|-----------|------------------------------------------------|
| `kernel`       | 95 / 224        | 9.1 KB / 39.4 KB       | 23.20 %   | 28.21 %   | libultra + USO loader + audio (`0x80000000`)   |
| `bootup_uso`   | 197 / 359       | 11.2 KB / 81.6 KB      | 13.73 %   | 15.06 %   | Giles Goddard's libgdl engine                  |
| `game_libs`    | 243 / 1,373     | 12.4 KB / 412.5 KB     | 3.02 %    | 3.81 %    | Support libraries — wrapper mass-match         |
| `gui_uso`      | 10 / 24         | 0.8 KB / 18.1 KB       | 4.61 %    | 5.44 %    | GUI/menu helpers                               |
| `titproc_uso`  | 21 / 43         | 1.8 KB / 10.5 KB       | 16.92 %   | 22.93 %   | Title-screen process (templates + composites)  |
| `arcproc_uso`  | 20 / 50         | 1.4 KB / 10.4 KB       | 13.11 %   | 24.42 %   | Arcade-mode process                            |
| `h2hproc_uso`  | 23 / 40         | 1.5 KB / 6.8 KB        | 22.67 %   | 43.55 %   | Head-to-head process                           |
| `eddproc_uso`  | 12 / 15         | 0.7 KB / 1.1 KB        | 64.46 %   | 91.53 %   | Edit-mode process                              |
| `n64proc_uso`  | 2 / 7           | 0.1 KB / 1.0 KB        | 6.02 %    | 63.18 %   | N64-specific process                           |
| `boarder1..5_uso` | 29 / 30      | 1.9 KB / 1.9 KB        | 96.74 %   | 99.80 %   | Per-character snowboarder USOs                 |
| `mgrproc_uso`  | 12 / 50         | 0.7 KB / 13.0 KB       | 5.67 %    | 7.37 %    | Manager process (Yay0-decompressed)            |
| `game_uso`     | 80 / 226        | 4.5 KB / 70.8 KB       | 6.41 %    | 13.44 %   | Main game loop (Yay0-decompressed)             |
| `timproc_uso_b1,b3,b5` | 77 / 224 | 4.3 KB / 81.3 KB       | 5.29 %    | 8.27 %    | Timer process variants (Yay0-decompressed)     |
| `map4_data_uso_b2` | 3 / 3       | 0.2 KB / 0.2 KB        | 100.00 %  | 100.00 %  | Map-4 data block                               |
| **Total**      | **824 / 2,668** | **50.7 KB / 748.6 KB** | **6.77 %**| **9.21 %**|                                                |

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

### Optional: Ghidra integration

A persistent Ghidra project at `build/ghidra-project/tenshoe.gpr` complements `m2c` for struct-recovery, xref discovery, and type-decorated decomp output. Setup (one-time, ~7 min):

```bash
# Tools (downloaded into ../tools/, gitignored):
#   - JDK 21 (Adoptium portable)
#   - Ghidra 12.x (NSA release)
#   - pyghidra-mcp (uv tool install pyghidra-mcp)
# See ~/.claude/projects/.../memory/feedback_pyghidra_mcp_setup_for_n64_decomp.md

bash scripts/setup-ghidra.sh           # build project + import 2,000+ symbols
bash scripts/ghidra-decompile-func.sh func_80008430   # one-shot decomp
```

Use Ghidra by trigger only (struct shape unknown, function family >3, stuck <50% fuzzy with structural unknowns) — m2c remains the default. See the `/decompile` skill for the trigger list.

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
