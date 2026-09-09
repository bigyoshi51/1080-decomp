# 1080 Snowboarding n64 decompilation

In progress 1080 Snowboarding decompilation, mostly driven by Claude. Uses https://github.com/bigyoshi51/decomp for n64 common tooling, Claude skills, etc.

## Status

**The build is ROM-exact (2026-06-10): `make` produces a `tenshoe.z64` byte-identical to the original ROM** (md5 `fa27089c425dbab99f19245c5c997613`), and `make verify` (part of the default target) hard-fails on any regression.

Twenty segments are being decompiled. USO overlays ship as a custom relocatable format (some Yay0-compressed); we match pre-relocation bytes by splatting at `VRAM=0` with per-segment symbol prefixes (`gl_func_`, `gui_func_`, etc.).

`Matched` is the share of code bytes whose C body compiles to baserom byte-for-byte. `Fuzzy` is bytes-weighted partial credit: NM-wrapped C bodies that aren't byte-perfect contribute their per-instruction similarity (e.g., a 1 KB function at 80 % match adds ~800 bytes of fuzzy credit). Both metrics use a separate `build/non_matching/` tree compiled with `-DNON_MATCHING` so partial decomp work shows up in the report.

| Segment | Functions | Code matched | Matched | Fuzzy | Notes |
|------------------------|-------------------|------------------------|------------|------------|------------------------------------------------|
| `kernel` | 135 / 201 | 21.8 KiB / 38.9 KiB | 56.06 % | 69.26 % | libultra + USO loader + audio (`0x80000000`) |
| `bootup_uso` | 272 / 349 | 28.5 KiB / 81.6 KiB | 34.99 % | 83.75 % | Giles Goddard's libgdl engine |
| `game_libs` | 1,296 / 1,916 | 138.0 KiB / 408.8 KiB | 33.77 % | 81.50 % | Support libraries (incl. statically-linked libultra) |
| `gui_uso` | 16 / 39 | 1.7 KiB / 18.1 KiB | 9.16 % | 87.46 % | GUI/menu helpers |
| `titproc_uso` | 41 / 46 | 5.9 KiB / 10.5 KiB | 55.83 % | 97.84 % | Title-screen process |
| `arcproc_uso` | 45 / 59 | 5.2 KiB / 10.4 KiB | 50.51 % | 94.96 % | Arcade-mode process |
| `h2hproc_uso` | 33 / 40 | 3.3 KiB / 6.8 KiB | 49.02 % | 96.67 % | Head-to-head process |
| `eddproc_uso` | 15 / 15 | 1.1 KiB / 1.1 KiB | 100.00 % | 100.00 % | Edit-mode process |
| `n64proc_uso` | 7 / 7 | 1.0 KiB / 1.0 KiB | 100.00 % | 100.00 % | N64-specific process |
| `boarder1_uso` | 6 / 6 | 0.4 KiB / 0.4 KiB | 100.00 % | 100.00 % | Per-character snowboarder USO |
| `boarder2_uso` | 6 / 6 | 0.4 KiB / 0.4 KiB | 100.00 % | 100.00 % | Per-character snowboarder USO |
| `boarder3_uso` | 6 / 6 | 0.4 KiB / 0.4 KiB | 100.00 % | 100.00 % | Per-character snowboarder USO |
| `boarder4_uso` | 6 / 6 | 0.4 KiB / 0.4 KiB | 100.00 % | 100.00 % | Per-character snowboarder USO |
| `boarder5_uso` | 6 / 6 | 0.4 KiB / 0.4 KiB | 100.00 % | 100.00 % | Per-character snowboarder USO |
| `mgrproc_uso` | 45 / 57 | 7.2 KiB / 13.0 KiB | 55.09 % | 96.67 % | Manager process (Yay0-decompressed) |
| `game_uso` | 192 / 240 | 25.9 KiB / 70.8 KiB | 36.63 % | 87.12 % | Main game loop (Yay0-decompressed) |
| `timproc_uso` | 266 / 315 | 32.0 KiB / 81.4 KiB | 39.28 % | 93.50 % | Timer process (Yay0; variants b1/b3/b5) |
| `map4_data_uso_b2` | 3 / 3 | 0.2 KiB / 0.2 KiB | 100.00 % | 100.00 % | Map overlay code (remaining map assets are data) |
| **Total** | **2,396 / 3,317** | **273.8 KiB / 744.5 KiB** | **36.78 %** | **84.03 %** |  |

Snapshot from `report.json` on 2026-09-09. Remaining Yay0-compressed USOs are
splatted; code in `map4_data_uso_b2` is tracked above, while pure data assets
(audio banks, character meshes, textures) stay as `bin` segments.

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

1080 Snowboarding uses a **USO (Universal Shared Objects)** overlay system loaded at runtime. The ROM has the kernel + two large always-resident USOs (`bootup_uso`, `game_libs`), then a bag of process-specific USOs (`game_uso`, `gui_uso`, `*proc_uso`, `boarder*_uso`, `timproc_uso_b*`) that are loaded/unloaded as gameplay state changes. Yay0-compressed USOs are decompressed at splat time.

- **Kernel** (39 KB, 213 functions, VRAM `0x80000000`) — libultra, USO loader, audio
- **bootup_uso** (79 KB, 335 functions, VRAM `0`) — libgdl game engine (C++, debug strings preserved)
- **game_libs** (411 KB, 1,483 functions, VRAM `0`) — support libraries (stripped); biggest segment, the main grinding target
- **game_uso** (71 KB, 234 functions, VRAM `0`) — main game loop (Yay0-decompressed)
- **timproc_uso_b{1,3,5}** (12+12+58 KB, 263 functions total) — timer-process variants (Yay0)
- **Other process USOs** (1–18 KB each) — `gui_uso`, `titproc_uso`, `arcproc_uso`, `h2hproc_uso`, `eddproc_uso`, `n64proc_uso`, `mgrproc_uso`, `boarder{1..5}_uso`, `map4_data_uso_b2`

All USOs splat at synthetic `VRAM=0` to match unrelocated ROM bytes; distinct symbol prefixes (`func_` vs `gl_func_` vs `gui_func_` vs `game_uso_func_` vs `<usoname>_func_`) avoid linker collisions across USOs while letting each share its own internal label scope.
