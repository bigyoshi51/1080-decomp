# emu-symdump — recover real USO symbol names by running the loader

The Kyoto-USO format (1080's overlays) stores a custom reloc table: each relocated
instruction is a placeholder (`lui 0` / `addiu …,0` / `jal 0`) plus a `(symIdx, kind,
offset)` entry. splat disassembles the placeholders, so every relocated `jal`
collapses to `jal 0` — the call graph is invisible ("reloc-blind"). To match a USO
function you need the **real** target of each reloc.

The on-disk **Sym** section holds the names, but the loader resolves names→values
**in place at load** and there is no standalone parser in the kernel cluster to
decode it statically. So instead we **run the real loader inside an emulator**, dump
RDRAM once `bootup.uso` is loaded + relocated, and read the resolved targets back
out — then correlate them with the decoded reloc table to name every symIdx.

Result for bootup.uso: **1672 symbols** — 1219 `func_<off>` (the call graph),
248 `D_<off>`, 3 `RO_<off>`, 202 cross-module `import_<addr>`. Validated: every
resolved `jal` target lands on a real function prologue (`27bdffe0`/`27bdff…`).

## Status — USOs dumped (2026-05-30)

| USO | how | symname map |
|-----|-----|-------------|
| bootup_uso (+ game_libs inside it) | boot dummy-plugin dump | `bootup_uso.symnames.json` (1672) |
| game_uso | `--real-render` (title), block-diff | `game_uso.symnames.json` (1508 sites) |
| titproc_uso | resident in the game_uso dump, uso-correlate | `titproc_uso.symnames.json` (102) |
| mgrproc_uso | scripted-input (menu-manager), block-diff | `mgrproc_uso.symnames.json` (436 sites) |
| timproc_uso **b5** | scripted-input SI_EXPLORE, block-diff | `timproc_uso_b5.symnames.json` (1772 sites) |

**bootup/game_libs**: their `.s` are ALREADY symbolized (real `%hi/%lo/jal func_<off>`
names from prior work — bootup 0 placeholders, game_libs 1). What remains is the
`.c`-SIDE: the hand-written C bodies still call the collapsed `func_00000000`
placeholder (bootup.c: 731×) — renaming each call site to its real target needs a
C-source↔object-reloc mapping (the deferred build-wiring), a focused engineering
effort, not a bulk `.s` rollout. Don't re-attempt as a loop rollout.

Remaining: timproc **b1/b3** and **h2hproc** (2P). b1/b3 are NOT boot-resident
(b5 is) and the menu-sweep doesn't sustain a full race, so they need an in-progress
Time-Attack race (a save-state or longer sustained input) to load; h2hproc needs 2P VS.

**ROI note:** most USO functions already report **100%** (their `.text` byte-matches
WITH the `jal 0`/`lui 0` placeholders — e.g. 203 timproc functions are already 100%).
So the symname dumps' main payoff is **real names for episode/call-graph quality**,
NOT match-% — only the handful of byte-equal residuals stuck just under 100% (the
`-O0` symbol-value cases) actually flip to 100% via symbolize. Weigh the cost of
driving the emulator to a specific mode against that incremental value.

## Coverage: `game_libs` is inside bootup.uso's text (one dump covers both)

The project's `game_libs` segment is **not a separate USO** — its functions live
inside bootup.uso's `.text` section (verified: `game_libs_func_00003298` @ ROM
0xDE8370 is within bootup text 0xdd0a68–0xE5A378). So game_libs's relocs are in
the **same** bootup.uso TextReloc table, and its real names are already in
`bootup_uso.symnames.json` — **no separate dump is needed for game_libs**, which
holds the largest reloc-collapse-cap class.

Offset mapping (verified): a `game_libs`-segment offset `O` (i.e. the
`game_libs_func_<O>` name offset) corresponds to bootup project offset
`O + 0x1466C`. Look up the reloc at `O + 0x1466C` in the bootup TextReloc table to
get its symIdx → name. Example: `gl_func_000032B0`'s placeholder jal (game_libs
off 0x333C → bootup proj 0x179A8) resolves to the real callee **`func_0144B4`**;
game_libs `D_` refs resolve to real `import_<addr>` / `D_<off>` names. This means
the game_libs symbolize rollout reuses the existing dump + an `+0x1466C` shim.

Other project segments (gui_uso, timproc_uso, mgrproc_uso, …) appear to be their
own USO modules and would each need their own dump (and the compressed ones need
decompressed text first).

## Pipeline

```
ROM ──run loader──► RDRAM dump ──correlate w/ reloc table──► symnames.json ──► emitter
   uso-emu-dump.py                 uso-correlate.py                 ../uso-reloc-symbolize.py --symnames
```

### 1. One-time setup

```bash
# a) a prebuilt mupen64plus bundle (core + headers). Any recent linux64 bundle works.
#    e.g. mupen64plus-bundle-linux64-*.tar.gz from the mupen64plus releases.
BUNDLE=/path/to/mupen64plus-bundle-...    # dir containing libmupen64plus.so.2*

# b) build the three no-op plugins + the task-completing RSP plugin.
#    Headers (m64p_types.h, m64p_plugin.h) ship in the mupen64plus-core source api/.
API=/path/to/mupen64plus-core/src/api     # or wherever the m64p_*.h headers are
mkdir -p /tmp/dummyplugins && cd /tmp/dummyplugins
gcc -shared -fPIC -I"$API" -DPLUGIN_TYPE=2 -DPLUGIN_API=0x020200 -o dummy-GFX.so   dummy-plugin.c
gcc -shared -fPIC -I"$API" -DPLUGIN_TYPE=3 -DPLUGIN_API=0x020000 -o dummy-AUDIO.so dummy-plugin.c
gcc -shared -fPIC -I"$API" -DPLUGIN_TYPE=4 -DPLUGIN_API=0x020100 -o dummy-INPUT.so dummy-plugin.c
gcc -shared -fPIC -I"$API" -o dummy-RSP.so dummy-rsp.c
```

### 2. Dump RDRAM with the module loaded

```bash
python3 scripts/emu-symdump/uso-emu-dump.py \
    --bundle "$BUNDLE" --plugins /tmp/dummyplugins \
    --rom baserom.z64 --module 0xD9FE28 \
    --out /tmp/rdram.bin --found /tmp/found.json
# -> "FOUND: textbase phys 0x95e4c; wrote /tmp/rdram.bin + /tmp/found.json"
```

`--module` is the ROM offset of the USO header (magic `0x12345678`). bootup.uso is
`0xD9FE28`.

### 3. Correlate → real names

```bash
python3 scripts/emu-symdump/uso-correlate.py \
    --module 0xD9FE28 --dump /tmp/rdram.bin --found /tmp/found.json \
    --out scripts/emu-symdump/bootup_uso.symnames.json
# -> "resolved 1672 symIdx; classes: {'import':202,'func':1219,'D':248,'RO':3}"
```

### 4. Emit the symbolized .s with real names

```bash
python3 scripts/uso-reloc-symbolize.py bootup_uso 0xD9FE28 \
    --symnames scripts/emu-symdump/bootup_uso.symnames.json --apply
# bytes are IDENTICAL to the usosym_<N> form (undefined/=0 -> placeholder bytes);
# only the reloc symbol NAME changes (jal 0 + R_MIPS_26 -> func_00049AAC).
```

`bootup_uso.symnames.json` is committed so step 4 works without re-running the
emulator. Re-run steps 2–3 for other USO modules (different `--module`).

## Gotchas (each cost real time — do not re-discover)

- **RDRAM byte-order**: `DebugMemGetPointer(M64P_DBG_PTR_RDRAM)` returns memory
  **byte-swapped per 32-bit word** (host little-endian storage). Byteswap every
  4 bytes (`array.array('I').byteswap()`) to get big-endian N64 memory — otherwise
  NOTHING matches. This was the single breakthrough; before it, every signature
  scan found nothing.
- **Plugin attach order**: `CoreAttachPlugin` must be called **after**
  `M64CMD_ROM_OPEN` (else `M64ERR_INVALID_STATE` = 10).
- **RSP required**: the core calls `DoRspCycles` unconditionally → null-deref with
  no RSP plugin; `rsp-hle` segfaults when attached via ctypes. The dummy RSP marks
  tasks done (`SP_STATUS |= HALT|BROKE`, `MI_INTR |= SP`, `CheckInterrupts()`).
- **Interpreter, not dynarec**: set `R4300Emulator=1` so the debugger memory API
  (`DebugMemGetPointer`) returns a live pointer.
- **Headless**: the dummy gfx/audio/input plugins are pure no-ops — no GL, no SDL,
  no Xvfb. Boot hangs in a spin loop (PC ~`0x801150ec`) after loading the USOs,
  which is fine: the module is loaded + relocated well before the hang, and the
  timer-based dump catches it.

## Gameplay USOs (`--real-render`, 2026-05-30)

The dummy-plugin path above only catches USOs loaded **during boot** (bootup,
game_libs). Mode-specific USOs (game_uso, titproc, timproc, h2hproc, …) load
later, so the game must actually run with **real** plugins:

```bash
# real video-rice (GFX) + rsp-hle (RSP) under a virtual display + software GL:
tools/mupen64plus/xvfb-extract/usr/bin/Xvfb :99 -screen 0 640x480x24 &
DISPLAY=:99 python3 scripts/emu-symdump/uso-emu-dump.py --real-render --module 0x595408 ...
```

- **The fix that makes real plugins work**: the frontend must call each plugin's
  `PluginStartup(coreHandle, …)` **before** `CoreAttachPlugin` (it resolves the
  core's VidExt fns). Dummy plugins no-op it so the old code worked; real plugins
  SIGSEGV in `InitiateGFX` on a NULL VidExt without it. Baked into `uso-emu-dump.py`.
- **One dump covers every USO resident at that game state.** The game_uso dump
  reached the title, so **titproc** (uncompressed) was also resident — dumped via
  `walk_dir`+`uso-correlate.py` against the *same* `/tmp` dump, no second run.
- **Compressed USOs** (game_uso, timproc, mgrproc) have their Sym/TextReloc *inside*
  the Yay0 blocks, so `uso-correlate` (which reads the ROM TextReloc) can't be used.
  Instead **diff** the Yay0-decompressed CODE block (`extract-uso-yay0.py --write`)
  against the resolved RAM Text: every differing word is a reloc site, the RAM word
  is the resolved target (`game-uso-reloc-diff.py` → `game-uso-name-join.py`).
- **Naming external targets**: `enrich-uso-imports.py` rewrites `import_<addr>` to
  real names via bootup's symname table + its voted RAM textbase (0x95e50).
- **BLOCKER for race procs (timproc/h2hproc/mgrproc/n64proc/eddproc)**: starting a
  race needs **menu navigation (button presses)**; the dummy INPUT plugin sends
  nothing, so passive idling stays in the title/menu (verified: a 300s real-render
  run never loaded a race proc). These need a **scripted INPUT plugin or an in-mode
  save-state** — a focused task, not a passive dump. titproc was free only because
  the title is reached without input.
- **Verify residency with a ≥64-byte probe** (or a multi-probe consistent-tbase
  test), never a single 32-byte slice: a 32-byte match can be coincidental (a
  timproc block falsely "appeared" resident in the demo dump; 64-byte probes and a
  unique-tbase vote both confirmed it absent). A genuine relocated module shows a
  *constant* tbase across many unique probes + 0 jal-0 placeholders in RAM.

## Files

- `uso-emu-dump.py` — boot + dump driver (`--real-render` for gameplay USOs).
- `uso-correlate.py` — dump + ROM reloc table → `symnames.json` (uncompressed USOs).
- `game-uso-reloc-diff.py` — on-disk-vs-RAM Text diff for COMPRESSED USOs.
- `game-uso-name-join.py` / `enrich-uso-imports.py` — `import_<addr>` → real names.
- `dummy-plugin.c` / `dummy-rsp.c` — no-op plugin sources (build per step 1b).
- `bootup_uso.symnames.json` (1672), `game_uso.symnames.json` (1508 sites),
  `titproc_uso.symnames.json` (102) — recovered maps.
