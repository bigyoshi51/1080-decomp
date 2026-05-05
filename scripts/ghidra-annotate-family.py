"""Batch-apply a struct prototype to a family of related functions.

Common workflow:
  1. Find family via xref to a shared callee (e.g. __rmonSendHeader → 27 rmon
     callers in 1080). Either MCP `list_xrefs` or via Ghidra GUI.
  2. Decide which functions take the same struct as their first arg.
  3. Run this script to define the struct and apply `<Struct> *<argname>`
     across the whole family in one transaction.

Inputs:
  - Struct definition (built-in templates, e.g. "RmonMsg", or pass --field-spec)
  - Comma-separated function-name list

Output: re-decompiles each function so you can eyeball the typed result.

Example:
  python3 scripts/ghidra-annotate-family.py \\
    --struct-template RmonMsg \\
    --param-name msg \\
    --funcs func_80006D0C,func_80006C64,func_80006BD8

  python3 scripts/ghidra-annotate-family.py \\
    --struct-spec 'MyStruct{4:int pad0;4:byte type;9:byte domain;C:int id}' \\
    --struct-size 0x10 \\
    --funcs func_A,func_B
"""
import argparse
import re
import sys
from pathlib import Path

import pyghidra
pyghidra.start()
from pyghidra import open_project, program_context
from ghidra.app.decompiler import DecompInterface
from ghidra.program.model.data import (
    StructureDataType, ByteDataType, IntegerDataType, ShortDataType,
    CharDataType, CategoryPath, PointerDataType, DataTypeConflictHandler,
)
from ghidra.program.model.symbol import SourceType
from ghidra.program.model.listing import ParameterImpl, ReturnParameterImpl
from ghidra.program.model.listing.Function import FunctionUpdateType
from ghidra.util.task import ConsoleTaskMonitor

ROOT = Path(__file__).resolve().parent.parent
PROJECT_DIR = ROOT / "build" / "ghidra-project"

# Built-in struct templates for common 1080 types.
TEMPLATES = {
    "RmonMsg": [
        (0x0, IntegerDataType, 4, "pad0"),
        (0x4, ByteDataType, 1, "type"),
        (0x9, ByteDataType, 1, "domain"),
        (0xC, IntegerDataType, 4, "id"),
    ],
    "RmonMsgSmall": [
        (0x0, IntegerDataType, 4, "pad0"),
        (0x4, ByteDataType, 1, "type"),
    ],
    "Vec3": [
        (0x0, IntegerDataType, 4, "x"),
        (0x4, IntegerDataType, 4, "y"),
        (0x8, IntegerDataType, 4, "z"),
    ],
    "Quad4": [
        (0x0, IntegerDataType, 4, "a"),
        (0x4, IntegerDataType, 4, "b"),
        (0x8, IntegerDataType, 4, "c"),
        (0xC, IntegerDataType, 4, "d"),
    ],
}

DT_MAP = {
    "int": IntegerDataType, "byte": ByteDataType, "char": CharDataType,
    "short": ShortDataType, "u8": ByteDataType, "s32": IntegerDataType,
}


def parse_struct_spec(spec):
    """Parse 'Name{0:int pad0;4:byte type;9:byte domain;C:int id}' →
    (name, [(offset, dt_class, size, fname), ...])."""
    m = re.match(r"^(\w+)\{(.+)\}$", spec)
    if not m:
        raise SystemExit(f"bad --struct-spec: {spec!r}")
    name, body = m.group(1), m.group(2)
    fields = []
    for entry in body.split(";"):
        entry = entry.strip()
        if not entry: continue
        m2 = re.match(r"^([0-9A-Fa-fxX]+):\s*(\w+)\s+(\w+)$", entry)
        if not m2:
            raise SystemExit(f"bad field: {entry!r}")
        off = int(m2.group(1), 16)
        dt_name = m2.group(2)
        fname = m2.group(3)
        if dt_name not in DT_MAP:
            raise SystemExit(f"unknown type {dt_name}; allowed: {sorted(DT_MAP)}")
        dt_cls = DT_MAP[dt_name]
        # Default size by type
        sz = {ByteDataType: 1, ShortDataType: 2, IntegerDataType: 4,
              CharDataType: 1}[dt_cls]
        fields.append((off, dt_cls, sz, fname))
    return name, fields


def lookup_fn(program, name):
    syms = list(program.getSymbolTable().getSymbols(name))
    if not syms: return None
    return program.getFunctionManager().getFunctionAt(syms[0].getAddress())


def show_signature(func):
    if func is None: return "<not found>"
    parts = ', '.join(p.getDataType().getName() + ' ' + p.getName() for p in func.getParameters())
    return f"{func.getReturnType().getName()} {func.getName()}({parts})"


def decompile(decomp, func):
    if func is None: return "<not found>"
    res = decomp.decompileFunction(func, 30, ConsoleTaskMonitor())
    if not res.decompileCompleted():
        return f"<decomp failed: {res.getErrorMessage()}>"
    return res.getDecompiledFunction().getC()


def main():
    parser = argparse.ArgumentParser()
    g = parser.add_mutually_exclusive_group(required=True)
    g.add_argument("--struct-template", choices=sorted(TEMPLATES),
                   help="Use a built-in struct template")
    g.add_argument("--struct-spec",
                   help="Inline struct spec: 'Name{off:type field;...}'")
    parser.add_argument("--struct-size", type=lambda s: int(s, 0),
                        help="Struct size (required with --struct-spec)")
    parser.add_argument("--param-name", default="msg",
                        help="Parameter name in the typed signature [default: msg]")
    parser.add_argument("--return-type", default="int",
                        help="Return type [default: int]")
    parser.add_argument("--funcs", required=True,
                        help="Comma-separated function names to annotate")
    parser.add_argument("--show-decomp", action="store_true",
                        help="Re-decompile each function after annotation")
    args = parser.parse_args()

    if args.struct_template:
        struct_name = args.struct_template
        fields = TEMPLATES[struct_name]
        struct_size = max(off + sz for off, _, sz, _ in fields)
        struct_size = (struct_size + 3) & ~3  # round up to 4-byte boundary
    else:
        struct_name, fields = parse_struct_spec(args.struct_spec)
        if not args.struct_size:
            raise SystemExit("--struct-size required with --struct-spec")
        struct_size = args.struct_size

    func_names = [n.strip() for n in args.funcs.split(",") if n.strip()]
    if not func_names:
        raise SystemExit("--funcs is empty")

    if args.return_type not in DT_MAP:
        raise SystemExit(f"unknown --return-type {args.return_type}; allowed: {sorted(DT_MAP)}")
    return_dt = DT_MAP[args.return_type]

    project = open_project(PROJECT_DIR, "tenshoe", create=False)
    try:
        with program_context(project, "/baserom.z64") as program:
            # Define struct + apply to each function in one transaction
            tx_id = program.startTransaction(f"annotate {struct_name} family")
            try:
                dtm = program.getDataTypeManager()
                cat = CategoryPath("/decomp/family")
                if dtm.getCategory(cat) is None:
                    dtm.createCategory(cat)
                struct = StructureDataType(cat, struct_name, struct_size)
                for off, dt_cls, sz, fname in fields:
                    struct.replaceAtOffset(off, dt_cls.dataType, sz, fname, "")
                struct_typed = dtm.addDataType(struct, DataTypeConflictHandler.REPLACE_HANDLER)
                struct_ptr = dtm.getPointer(struct_typed)
                print(f"struct: {struct_typed.getPathName()} (size={struct_typed.getLength()})")

                from java.util import ArrayList
                applied, missing = 0, []
                for name in func_names:
                    f = lookup_fn(program, name)
                    if f is None:
                        missing.append(name)
                        continue
                    params = ArrayList()
                    params.add(ParameterImpl(args.param_name, struct_ptr, program))
                    f.updateFunction(
                        None,
                        ReturnParameterImpl(return_dt.dataType, program),
                        params,
                        FunctionUpdateType.DYNAMIC_STORAGE_FORMAL_PARAMS,
                        True,
                        SourceType.USER_DEFINED,
                    )
                    applied += 1
                    print(f"  {name}: {show_signature(f)}")
                if missing:
                    print(f"WARN: {len(missing)} not found: {missing[:5]}{'...' if len(missing) > 5 else ''}")
                print(f"Applied to {applied}/{len(func_names)} functions.")
            finally:
                program.endTransaction(tx_id, True)
            program.save(f"annotate {struct_name} family", ConsoleTaskMonitor())

            if args.show_decomp:
                decomp = DecompInterface()
                decomp.openProgram(program)
                for name in func_names:
                    f = lookup_fn(program, name)
                    print()
                    print("=" * 70)
                    print(f"  {name}")
                    print("=" * 70)
                    print(decompile(decomp, f))
    finally:
        project.close()


if __name__ == "__main__":
    main()
