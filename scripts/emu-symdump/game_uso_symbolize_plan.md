# game_uso symbolize-only rollout — blueprint (no episodes)

Goal (user-directed 2026-05-30): give game_uso's reloc placeholders their REAL
names (from `game_uso.symnames.json`, 1508 sites) so the call graph / disassembly
is readable, WITHOUT logging episodes. Byte output must stay identical (placeholder
bytes unchanged) — this only renames symbols.

## Inputs (ready)
- `game_uso.symnames.json` — offset→name: 408 internal `func_<projoff>`, 457 `D_`,
  488 imports→real bootup names, plus kernel/mid-object `import_<addr>`.
- game_uso module: ROM 0x7CC900-ish, text tbase (RAM) 0x7ecaa0; build via
  `src/game_uso/game_uso.c` (300 INCLUDE_ASM + hand C bodies) pulling
  `asm/nonmatchings/game_uso/game_uso/*.s` (raw baked `.word`).

## Naming reconciliation (critical — avoid global-namespace collisions)
- INTERNAL calls/data: name `game_uso_func_<projoff>` / `game_uso_D_<off>` — NOT
  bare `func_<off>` (that collides with bootup's `func_<off>` for a different fn).
- IMPORTS: use the real cross-module name from the join (`func_<bootupoff>` IS a
  bootup symbol; `import_<addr>` for kernel/unresolved).
- DEFINES (preserve bytes): the `.s` bakes INTRA-module jals to their target
  (e.g. `.word 0x0C0000A0` = jal proj 0x280), so `game_uso_func_<0x280>` must be
  defined = 0x280 to re-assemble to the same word. Import placeholders are `=0`
  (jal 0 / lui 0), exactly like the existing `gl_func_00000000`/`D_00000000`.

## Why this is a FOCUSED PASS, not a loop tick
- Build-approach refactor: rewrite each `.s`'s baked `.word` reloc sites to named
  instructions + add the per-name defines, keeping `expected/.o` == build bytes.
  (bootup's `uso-reloc-symbolize.py` rewrites MNEMONIC `.s`; game_uso `.s` are raw
  `.word`, so that tool doesn't transfer — needs an offset→named-`.word` emitter.)
- HIGH COLLISION: `game_uso.c` (598 KB, one file) is under heavy concurrent edit
  (multiple agents landing matches this session). A bulk rename of its placeholder
  refs WILL conflict with in-flight work.
- LOW headline value: most game_uso fns already report 100% (placeholder-match);
  episodes are excluded → the payoff is readable names only.

## Recommended execution (when ready)
1. Do it on a DEDICATED branch in a quiet window (no other agent mid-edit on
   game_uso), or coordinate a freeze.
2. Operate on the `.s` side first (generated, less hand-edited): emit named `.word`
   relocs from `game_uso.symnames.json` + the per-name defines; verify each `.o`
   is byte-identical before/after.
3. Only then reconcile `game_uso.c`'s collapsed `gl_func_00000000`/`D_00000000`
   refs to the same names, function-by-function, rebasing onto origin frequently.
4. Gate every step on byte-identical `.text` (land `byte_verify`); abort on any diff.

Status: blueprint only. Bulk application deferred to a coordinated focused pass —
not run mid-session against actively-edited `game_uso.c`.
