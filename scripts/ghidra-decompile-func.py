"""Decompile a function by name from the cached Ghidra project. For debug/dev.

Uses the same project that pyghidra-mcp serves, so output should match.
"""
import sys
from pathlib import Path

import pyghidra
pyghidra.start()
from pyghidra import open_project, program_context
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor

ROOT = Path(__file__).resolve().parent.parent
PROJECT_DIR = ROOT / "build" / "ghidra-project"
PROGRAM_PATH = "/baserom.z64"

if len(sys.argv) < 2:
    print("usage: ghidra-decompile-func.py <function_name>", file=sys.stderr)
    sys.exit(1)
target = sys.argv[1]

project = open_project(PROJECT_DIR, "tenshoe", create=False)
try:
    with program_context(project, PROGRAM_PATH) as program:
        n_fns = program.getFunctionManager().getFunctionCount()
        print(f"# {n_fns} fns in project; looking for {target!r}", file=sys.stderr)
        syms = list(program.getSymbolTable().getSymbols(target))
        if not syms:
            print(f"NOT FOUND: {target}", file=sys.stderr)
            sys.exit(2)
        sym = syms[0]
        addr = sym.getAddress()
        print(f"# found {target} @ {addr}", file=sys.stderr)
        func = program.getFunctionManager().getFunctionAt(addr)
        if func is None:
            print(f"# symbol exists but no function at {addr}", file=sys.stderr)
            sys.exit(3)
        decomp = DecompInterface()
        decomp.openProgram(program)
        result = decomp.decompileFunction(func, 30, ConsoleTaskMonitor())
        if result.decompileCompleted():
            print(result.getDecompiledFunction().getC())
        else:
            print(f"DECOMP FAILED: {result.getErrorMessage()}", file=sys.stderr)
            sys.exit(4)
finally:
    project.close()
