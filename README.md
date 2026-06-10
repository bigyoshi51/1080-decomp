# 1080 Snowboarding n64 decompilation

In progress 1080 Snowboarding decompilation, mostly driven by Claude. Uses https://github.com/bigyoshi51/decomp for n64 common tooling, Claude skills, etc.

## Status

**The build is ROM-exact (2026-06-10): `make` produces a `tenshoe.z64` byte-identical to the original ROM** (md5 `fa27089c425dbab99f19245c5c997613`), and `make verify` (part of the default target) hard-fails on any regression.

Twenty segments are being decompiled. USO overlays ship as a custom relocatable format (some Yay0-compressed); we match pre-relocation bytes by splatting at `VRAM=0` with per-segment symbol prefixes (`gl_func_`, `gui_func_`, etc.).

`Matched` is the share of code bytes whose C body compiles to baserom byte-for-byte. `Fuzzy` is bytes-weighted partial credit: NM-wrapped C bodies that aren't byte-perfect contribute their per-instruction similarity (e.g., a 1 KB function at 80 % match adds ~800 bytes of fuzzy credit). Both metrics use a separate `build/non_matching/` tree compiled with `-DNON_MATCHING` so partial decomp work shows up in the report.

| Segment | Functions | Code matched | Matched | Fuzzy | Notes |
|------------------------|-------------------|------------------------|------------|------------|------------------------------------------------|
| `kernel` | 101 / 214 | 9.8 KB / 39.4 KB | 24.94 % | 55.44 % | libultra + USO loader + audio (`0x80000000`) |
| `bootup_uso` | 227 / 359 | 14.7 KB / 81.6 KB | 18.02 % | 49.70 % | Giles Goddard's libgdl engine |
| `game_libs` | 919 / 2081 | 52.3 KB / 412.4 KB | 12.68 % | 52.61 % | Support libraries (incl. statically-linked libultra) |
| `gui_uso` | 15 / 40 | 1.3 KB / 18.1 KB | 7.37 % | 68.17 % | GUI/menu helpers |
| `titproc_uso` | 30 / 46 | 2.7 KB / 10.5 KB | 26.02 % | 77.82 % | Title-screen process |
| `arcproc_uso` | 39 / 60 | 2.8 KB / 10.4 KB | 27.01 % | 78.69 % | Arcade-mode process |
| `h2hproc_uso` | 28 / 41 | 1.9 KB / 6.8 KB | 27.56 % | 89.67 % | Head-to-head process |
| `eddproc_uso` | 14 / 15 | 0.9 KB / 1.1 KB | 82.58 % | 99.30 % | Edit-mode process |
| `n64proc_uso` | 5 / 7 | 0.5 KB / 1.0 KB | 49.25 % | 93.03 % | N64-specific process |
| `boarder1_uso` | 6 / 6 | 0.4 KB / 0.4 KB | 100.00 % | 100.00 % | Per-character snowboarder USO |
| `boarder2_uso` | 6 / 6 | 0.4 KB / 0.4 KB | 100.00 % | 100.00 % | Per-character snowboarder USO |
| `boarder3_uso` | 6 / 6 | 0.4 KB / 0.4 KB | 100.00 % | 100.00 % | Per-character snowboarder USO |
| `boarder4_uso` | 6 / 6 | 0.4 KB / 0.4 KB | 100.00 % | 100.00 % | Per-character snowboarder USO |
| `boarder5_uso` | 6 / 6 | 0.4 KB / 0.4 KB | 100.00 % | 100.00 % | Last snowboarder USO -- 1 function left |
| `mgrproc_uso` | 32 / 62 | 2.3 KB / 13.0 KB | 17.35 % | 86.01 % | Manager process (Yay0-decompressed) |
| `game_uso` | 148 / 241 | 12.1 KB / 70.9 KB | 17.05 % | 61.16 % | Main game loop (Yay0-decompressed) |
| `timproc_uso` | 213 / 344 | 13.5 KB / 81.4 KB | 16.58 % | 64.86 % | Timer process (Yay0; variants b1/b3/b5) |
| **Total** | **1,801 / 3,540** | **116.8 KB / 748.5 KB** | **15.60 %** | **56.84 %** |  |

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

1080 Snowboarding uses a **USO (Universal Shared Objects)** overlay system loaded at runtime. The ROM has the kernel + two large always-resident USOs (`bootup_uso`, `game_libs`), then a bag of process-specific USOs (`game_uso`, `gui_uso`, `*proc_uso`, `boarder*_uso`, `timproc_uso_b*`) that are loaded/unloaded as gameplay state changes. Yay0-compressed USOs are decompressed at splat time.

- **Kernel** (39 KB, 213 functions, VRAM `0x80000000`) — libultra, USO loader, audio
- **bootup_uso** (79 KB, 335 functions, VRAM `0`) — libgdl game engine (C++, debug strings preserved)
- **game_libs** (411 KB, 1,483 functions, VRAM `0`) — support libraries (stripped); biggest segment, the main grinding target
- **game_uso** (71 KB, 234 functions, VRAM `0`) — main game loop (Yay0-decompressed)
- **timproc_uso_b{1,3,5}** (12+12+58 KB, 263 functions total) — timer-process variants (Yay0)
- **Other process USOs** (1–18 KB each) — `gui_uso`, `titproc_uso`, `arcproc_uso`, `h2hproc_uso`, `eddproc_uso`, `n64proc_uso`, `mgrproc_uso`, `boarder{1..5}_uso`, `map4_data_uso_b2`

All USOs splat at synthetic `VRAM=0` to match unrelocated ROM bytes; distinct symbol prefixes (`func_` vs `gl_func_` vs `gui_func_` vs `game_uso_func_` vs `<usoname>_func_`) avoid linker collisions across USOs while letting each share its own internal label scope.
