# Decompiled Functions Manifest

All functions below have verified byte-matching C code. If any of these
regress during the O1/O2 file split, restore from the sources listed.

## O2 Functions (25) — compiled at -O2, source in kernel.c

| VRAM | Name | Description | Source |
|------|------|-------------|--------|
| 0x80000118 | func_80000118 | Boot init | kernel.c |
| 0x80000474 | func_80000474 | uso_set_alloc | kernel.c |
| 0x8000058C | func_8000058C | uso_stub_ret0 | kernel.c |
| 0x80000688 | func_80000688 | uso_advance_position | kernel.c |
| 0x800007C4 | func_800007C4 | uso_file_check | kernel.c |
| 0x80000E58 | func_80000E58 | callback | kernel.c |
| 0x800010B4 | func_800010B4 | uso_get_vtable | kernel.c |
| 0x800010C0 | func_800010C0 | uso_set_callbacks | kernel.c |
| 0x800010CC | func_800010CC | osSyncPrintf (variadic no-op) | kernel.c |
| 0x800012AC | func_800012AC | uso_get_error | kernel.c |
| 0x80001414 | func_80001414 | uso_read | kernel.c |
| 0x80001460 | func_80001460 | uso_file_end | kernel.c |
| 0x80001470 | func_80001470 | uso_seek | kernel.c |
| 0x80001494 | func_80001494 | uso_file_close | kernel.c |
| 0x8000149C | func_8000149C | uso_ret_zero | kernel.c |
| 0x800017B4 | func_800017B4 | empty | kernel.c |
| 0x800018A8 | func_800018A8 | empty | kernel.c |
| 0x80005800 | func_80005800 | __osSiCreateAccessQueue | kernel.c |
| 0x80005894 | func_80005894 | __osPiRelAccess | kernel.c |
| 0x80006240 | func_80006240 | __osPiReadStatus | kernel.c |
| 0x80006C58 | func_80006C58 | rmon stub (-1) | kernel.c |
| 0x80008A08 | func_80008A08 | __rmonInit | kernel.c |
| 0x80008AA0 | func_80008AA0 | __rmonSetFault | kernel.c |
| 0x800092B0 | func_800092B0 | rmon execute | kernel.c |
| 0x80009830 | func_80009830 | __osGetActiveQueue | kernel.c |

## O1 Functions (15) — compiled at -O1, source in src/o1/

| VRAM | Name | Description | Source |
|------|------|-------------|--------|
| 0x80004AC0 | func_80004AC0 | osPiRawReadIo | src/o1/func_80004AC0.c |
| 0x80004DE0 | func_80004DE0 | osSetEventMesg | src/o1/func_80004DE0.c |
| 0x800052C0 | func_800052C0 | __osSiDeviceBusy | src/o1/func_800052C0.c |
| 0x80005850 | func_80005850 | __osPiGetAccess | src/o1/func_80005850.c |
| 0x800059C0 | func_800059C0 | osSendMesg | src/o1/func_800059C0.c |
| 0x800060F0 | func_800060F0 | osGetThreadPri | src/o1/func_800060F0.c |
| 0x80006110 | func_80006110 | osSetThreadPri | src/o1/func_80006110.c |
| 0x800061F0 | func_800061F0 | __osSetGlobalIntMask | src/o1/func_800061F0.c |
| 0x80006250 | func_80006250 | __osResetGlobalIntMask (bitwise) | src/o1/func_80006250.c |
| 0x80006650 | __osResetGlobalIntMask | __osResetGlobalIntMask (loop) | src/o1/__osResetGlobalIntMask.c |
| 0x800065B0 | func_800065B0 | rmon stub (-1) | src/o1/func_800065B0.c |
| 0x80007DD0 | func_80007DD0 | osStopThread | src/o1/func_80007DD0.c |
| 0x80008424 | func_80008424 | rmon stub (-1) | src/o1/func_80008424.c |
| 0x80009A50 | func_80009A50 | osYieldThread | src/o1/func_80009A50.c |
| 0x80009C90 | func_80009C90 | osPiRawWriteIo | src/o1/func_80009C90.c |

## Verification

After the O1/O2 split, run:
```
objdiff-cli report generate | python3 -c "import json,sys; d=json.load(sys.stdin); print(d['measures']['matched_functions'])"
```
Expected: >= 40 matched functions.

After landing a successful decompile from a worktree, use:
```
./scripts/land-successful-decomp.sh <function_name> [<function_name> ...]
```
This rebases the current branch onto `origin/main`, fast-forwards the main
worktree, pushes `origin/main`, and regenerates `report.json` in both the
current worktree and the main worktree.

Important: this script is for exact matches only. It now refuses to land a
named function unless:
- `report.json` has no `fuzzy_match_percent` for that function
- the function no longer has an `INCLUDE_ASM` fallback in `src/`
- `episodes/<function_name>.json` exists

If the function is still fuzzy, keep it wrapped as `NON_MATCHING` and do not
log an episode.

## Fragment Merges Performed

These asm files were merged into their parent functions. If re-running
splat, ensure these are NOT treated as separate function boundaries.

| Fragment | Merged Into | Reason |
|----------|-------------|--------|
| func_80009DF0 | func_80009D10 | osStartThread tail |
| func_80005C00 | func_80005B10 | osCreateThread tail |
| func_80003D0C | func_80003C24 | osDestroyThread tail |
| func_800005D8 | func_800005DC | 4-byte prologue fragment |
| func_80001CF0 | func_80001CF4 | 4-byte prologue fragment |
| func_800056EC | func_800056F0 | 4-byte prologue fragment |
| func_80008BB0 | func_80008BB4 | 4-byte prologue fragment |
| func_80008D48 | func_80008D4C | 4-byte prologue fragment |
| func_80009144 | func_80009148 | 4-byte prologue fragment |
