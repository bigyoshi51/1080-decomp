"""Decompile a function by name from the cached project. For testing/dev."""
import os, sys, time
import pyghidra
pyghidra.start()
from pyghidra import open_program
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
BASEROM = ROOT / "baserom.z64"
PROJECT_DIR = ROOT / "build" / "ghidra-project"

if len(sys.argv) < 2:
    print("usage: ghidra-decompile-func.py <function_name>")
    sys.exit(1)
target = sys.argv[1]

t0 = time.time()
with open_program(
    str(BASEROM), project_location=str(PROJECT_DIR), project_name="tenshoe",
    analyze=False, language="MIPS:BE:32:default",
    loader="ghidra.app.util.opinion.BinaryLoader",
) as flat_api:
    program = flat_api.getCurrentProgram()
    print(f"[{time.time()-t0:.1f}s] {program.getFunctionManager().getFunctionCount()} fns; looking for {target!r}", file=sys.stderr)
    sym_table = program.getSymbolTable()
    # Find symbol by name
    syms = list(sym_table.getSymbols(target))
    if not syms:
        print(f"NOT FOUND: {target}", file=sys.stderr)
        sys.exit(2)
    sym = syms[0]
    addr = sym.getAddress()
    print(f"  found {target} @ {addr}", file=sys.stderr)
    func = program.getFunctionManager().getFunctionAt(addr)
    if func is None:
        print(f"  symbol exists but no function at {addr}", file=sys.stderr)
        sys.exit(3)
    decomp = DecompInterface()
    decomp.openProgram(program)
    result = decomp.decompileFunction(func, 30, ConsoleTaskMonitor())
    if result.decompileCompleted():
        print(result.getDecompiledFunction().getC())
    else:
        print(f"DECOMP FAILED: {result.getErrorMessage()}", file=sys.stderr)
        sys.exit(4)
