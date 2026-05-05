#!/usr/bin/env python3
"""Set up a persistent Ghidra project for 1080 Snowboarding decomp work.

Imports baserom.z64 as raw MIPS BE, runs auto-analysis, then walks
asm/nonmatchings/ to import every known function name at its file offset.

Persistent project: build/ghidra-project/tenshoe.gpr
- pyghidra-mcp can open it via --project-path build/ghidra-project/tenshoe.gpr
- Ghidra GUI can open it normally

Usage:
  python3 scripts/setup-ghidra.py            # incremental (skip if .gpr exists)
  python3 scripts/setup-ghidra.py --rebuild  # nuke + redo from scratch (~7 min)
"""
import argparse
import os
import re
import shutil
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
BASEROM = ROOT / "baserom.z64"
ASM_ROOT = ROOT / "asm" / "nonmatchings"
PROJECT_DIR = ROOT / "build" / "ghidra-project"
PROJECT_NAME = "tenshoe"
PROGRAM_PATH = "/baserom.z64"

# Segments we want Ghidra to know about. Yay0-compressed segments are skipped
# because the bytes at their ROM offset are compressed — Ghidra would see
# garbage. (See feedback_uso_yay0_compressed.md.)
# Format: (asm_subdir, rom_offset, vram_base, name_prefix_filter)
SEGMENTS = [
    ("kernel",          0x001000, 0x80000000, "func_"),
    ("bootup_uso",      0xDD0A6C, 0x00000000, "func_"),
    ("game_libs",       0xDE50D8, 0x00000000, "gl_func_"),
    ("game_libs",       0xDE50D8, 0x00000000, "game_libs_func_"),
    ("gui_uso",         0x58D530, 0x00000000, "gui_func_"),
    ("n64proc_uso",     0x594A54, 0x00000000, "n64proc_uso_func_"),
    ("titproc_uso",     0x599CCC, 0x00000000, "titproc_uso_func_"),
    ("eddproc_uso",     0x59F480, 0x00000000, "eddproc_uso_func_"),
    ("arcproc_uso",     0x5A6148, 0x00000000, "arcproc_uso_func_"),
    ("h2hproc_uso",     0x5AB6B0, 0x00000000, "h2hproc_uso_func_"),
    ("boarder1_uso",    0x56A750, 0x00000000, "boarder1_uso_func_"),
    ("boarder2_uso",    0x571FBC, 0x00000000, "boarder2_uso_func_"),
    ("boarder3_uso",    0x57A790, 0x00000000, "boarder3_uso_func_"),
    ("boarder4_uso",    0x5839D8, 0x00000000, "boarder4_uso_func_"),
    ("boarder5_uso",    0x58CC50, 0x00000000, "boarder5_uso_func_"),
]

SYMBOL_ADDRS = ROOT / "symbol_addrs.txt"


def collect_functions():
    by_offset = {}
    for asm_subdir, rom_offset, vram_base, prefix in SEGMENTS:
        seg_dir = ASM_ROOT / asm_subdir
        if not seg_dir.exists():
            continue
        for s_file in seg_dir.rglob("*.s"):
            stem = s_file.stem
            if stem.endswith("_pad") or not stem.startswith(prefix):
                continue
            m = re.match(rf"^{re.escape(prefix)}([0-9A-Fa-f]+)$", stem)
            if not m:
                continue
            vram = int(m.group(1), 16)
            if not (vram_base <= vram <= vram_base + 0x100000):
                continue
            file_offset = rom_offset + (vram - vram_base)
            existing = by_offset.get(file_offset)
            if existing is None or len(stem) > len(existing):
                by_offset[file_offset] = stem
    return by_offset


def collect_hand_named():
    if not SYMBOL_ADDRS.exists():
        return {}
    out = {}
    pat = re.compile(r"^(\w+)\s*=\s*0x([0-9A-Fa-f]+)\s*;\s*//\s*type:func")
    for line in SYMBOL_ADDRS.read_text().splitlines():
        m = pat.match(line)
        if not m:
            continue
        name, addr = m.group(1), int(m.group(2), 16)
        if 0x80000000 <= addr < 0x80800000:
            out[0x1000 + (addr - 0x80000000)] = name
    return out


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--rebuild", action="store_true",
                        help="Nuke project + redo from scratch (~7 min)")
    args = parser.parse_args()

    for var in ("JAVA_HOME", "GHIDRA_INSTALL_DIR"):
        if not os.environ.get(var):
            sys.exit(f"ERROR: {var} not set. Run via scripts/setup-ghidra.sh.")
    if not BASEROM.exists():
        sys.exit(f"ERROR: {BASEROM} not found")

    print("Walking asm/nonmatchings/ for function names...")
    funcs = collect_functions()
    funcs.update(collect_hand_named())
    print(f"  {len(funcs)} function symbols ready to import.")

    print("Starting pyghidra (lazy JVM boot)...")
    import pyghidra
    pyghidra.start()
    from pyghidra import open_project, program_loader, program_context
    from ghidra.app.util.opinion import BinaryLoader
    from ghidra.app.plugin.core.analysis import AutoAnalysisManager
    from ghidra.program.model.symbol import SourceType
    from ghidra.util.task import ConsoleTaskMonitor

    project_marker = PROJECT_DIR / f"{PROJECT_NAME}.gpr"
    if args.rebuild and PROJECT_DIR.exists():
        print(f"--rebuild: removing {PROJECT_DIR}")
        shutil.rmtree(PROJECT_DIR)
    PROJECT_DIR.mkdir(parents=True, exist_ok=True)
    fresh = not project_marker.exists()
    print(f"Project: {PROJECT_DIR}/{PROJECT_NAME}.gpr (fresh={fresh})")

    t0 = time.time()
    project = open_project(PROJECT_DIR, PROJECT_NAME, create=fresh)
    try:
        if fresh:
            print(f"[{time.time()-t0:.1f}s] Importing baserom...")
            loaded = (program_loader()
                      .source(str(BASEROM))
                      .project(project)
                      .language("MIPS:BE:32:default")
                      .loaders(BinaryLoader)
                      .load())
            loaded.save(ConsoleTaskMonitor())
            loaded.release(None)
            print(f"[{time.time()-t0:.1f}s] Imported & saved.")

        print(f"[{time.time()-t0:.1f}s] Opening program for analysis + symbol rename...")
        with program_context(project, PROGRAM_PATH) as program:
            fn_mgr = program.getFunctionManager()
            initial_fns = fn_mgr.getFunctionCount()
            print(f"[{time.time()-t0:.1f}s] Initial fn count: {initial_fns}")

            if fresh:
                print(f"[{time.time()-t0:.1f}s] Running auto-analysis (~7 min)...")
                mgr = AutoAnalysisManager.getAnalysisManager(program)
                tx_id = program.startTransaction("auto-analysis")
                try:
                    mgr.reAnalyzeAll(None)
                    mgr.startAnalysis(ConsoleTaskMonitor())
                finally:
                    program.endTransaction(tx_id, True)
                print(f"[{time.time()-t0:.1f}s] Auto-analysis done. fns: {fn_mgr.getFunctionCount()}")

            # Rename functions to match our project's symbol names
            print(f"[{time.time()-t0:.1f}s] Importing {len(funcs)} symbol names...")
            renamed = skipped = missing = 0
            tx_id = program.startTransaction("symbol-rename")
            try:
                for offset, name in sorted(funcs.items()):
                    addr = program.getAddressFactory().getDefaultAddressSpace().getAddress(offset)
                    f = fn_mgr.getFunctionAt(addr)
                    if f is None:
                        # Don't fall back to getFunctionContaining — that
                        # silently mis-renames neighboring functions.
                        missing += 1
                        continue
                    if f.getName() == name:
                        skipped += 1
                        continue
                    try:
                        f.setName(name, SourceType.USER_DEFINED)
                        renamed += 1
                    except Exception as e:
                        print(f"  WARN: could not rename {f.getName()} -> {name}: {e}")
            finally:
                program.endTransaction(tx_id, True)
            print(f"[{time.time()-t0:.1f}s] Renamed={renamed} already-named={skipped} not-a-known-fn={missing}")

            program.save("setup-ghidra: symbols imported", ConsoleTaskMonitor())
            print(f"[{time.time()-t0:.1f}s] Saved.")
    finally:
        project.close()

    print(f"\nTotal: {time.time()-t0:.1f}s")
    print(f"Project: {PROJECT_DIR}/{PROJECT_NAME}.gpr")
    print("MCP server can open it via .mcp.json (already configured).")


if __name__ == "__main__":
    main()
