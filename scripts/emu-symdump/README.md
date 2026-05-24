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

## Files

- `uso-emu-dump.py` — boot + dump driver (self-contained signature from the ROM).
- `uso-correlate.py` — dump + reloc table → `symnames.json`.
- `dummy-plugin.c` / `dummy-rsp.c` — no-op plugin sources (build per step 1b).
- `bootup_uso.symnames.json` — the recovered bootup.uso map (1672 names).
