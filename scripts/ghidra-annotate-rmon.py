"""Type-annotation workflow on rmon family. Define RmonMsg struct, apply to
func_80006D0C, decompile to verify, then check sibling.
"""
import sys
from pathlib import Path

import pyghidra
pyghidra.start()
from pyghidra import open_project, program_context
from ghidra.app.decompiler import DecompInterface
from ghidra.program.model.data import (
    StructureDataType, ByteDataType, IntegerDataType, CategoryPath,
    PointerDataType, DataTypeConflictHandler,
)
from ghidra.program.model.symbol import SourceType
from ghidra.program.model.listing import ParameterImpl, ReturnParameterImpl
from ghidra.program.model.listing.Function import FunctionUpdateType
from ghidra.util.task import ConsoleTaskMonitor

ROOT = Path(__file__).resolve().parent.parent
PROJECT_DIR = ROOT / "build" / "ghidra-project"


def fn(program, name):
    syms = list(program.getSymbolTable().getSymbols(name))
    if not syms: return None
    return program.getFunctionManager().getFunctionAt(syms[0].getAddress())


def show_signature(func):
    if func is None:
        return "<no function>"
    return f"{func.getReturnType().getName()} {func.getName()}({', '.join(p.getDataType().getName() + ' ' + p.getName() for p in func.getParameters())})"


def decompile_text(decomp, func):
    res = decomp.decompileFunction(func, 30, ConsoleTaskMonitor())
    if not res.decompileCompleted():
        return f"<decompile failed: {res.getErrorMessage()}>"
    return res.getDecompiledFunction().getC()


def main():
    project = open_project(PROJECT_DIR, "tenshoe", create=False)
    try:
        with program_context(project, "/baserom.z64") as program:
            f_target = fn(program, "func_80006D0C")
            f_sibling = fn(program, "func_80006C64")
            print(f"BEFORE signatures:")
            print(f"  target:  {show_signature(f_target)}")
            print(f"  sibling: {show_signature(f_sibling)}")

            # ---- Define RmonMsg struct + apply ----
            tx_id = program.startTransaction("annotate RmonMsg")
            try:
                dtm = program.getDataTypeManager()
                cat_path = CategoryPath("/decomp/rmon")
                if dtm.getCategory(cat_path) is None:
                    dtm.createCategory(cat_path)

                rmon_msg = StructureDataType(cat_path, "RmonMsg", 0x10)
                rmon_msg.replaceAtOffset(0x0, IntegerDataType.dataType, 4, "pad0", "")
                rmon_msg.replaceAtOffset(0x4, ByteDataType.dataType, 1, "type", "msg type")
                rmon_msg.replaceAtOffset(0x9, ByteDataType.dataType, 1, "domain", "domain")
                rmon_msg.replaceAtOffset(0xC, IntegerDataType.dataType, 4, "id", "msg id")
                rmon_msg_typed = dtm.addDataType(rmon_msg, DataTypeConflictHandler.REPLACE_HANDLER)
                rmon_msg_ptr = dtm.getPointer(rmon_msg_typed)
                print(f"\n  added: {rmon_msg_typed.getPathName()}, size={rmon_msg_typed.getLength()}")
                print(f"  ptr type: {rmon_msg_ptr.getName()}")

                # ---- Replace function signature in one go ----
                # Use updateFunction to set a fully-USER_DEFINED signature.
                # Java List required — wrap via java.util.ArrayList.
                from java.util import ArrayList
                java_params = ArrayList()
                java_params.add(ParameterImpl("msg", rmon_msg_ptr, program))
                ret = ReturnParameterImpl(IntegerDataType.dataType, program)
                f_target.updateFunction(
                    None,            # callingConventionName (None = keep)
                    ret,             # return type
                    java_params,     # java.util.List of params
                    FunctionUpdateType.DYNAMIC_STORAGE_FORMAL_PARAMS,
                    True,            # force = override existing
                    SourceType.USER_DEFINED,
                )
                print(f"  func_80006D0C updated.")
            finally:
                program.endTransaction(tx_id, True)

            # ---- Verify the signature is recorded ----
            print(f"\nAFTER signatures (in DB):")
            print(f"  target:  {show_signature(f_target)}")
            print(f"  sibling: {show_signature(f_sibling)}")

            program.save("annotate RmonMsg", ConsoleTaskMonitor())

            # ---- Re-decompile (fresh interface to dodge cache) ----
            decomp = DecompInterface()
            decomp.openProgram(program)
            print()
            print("=" * 70)
            print("AFTER decompile of func_80006D0C:")
            print("=" * 70)
            print(decompile_text(decomp, f_target))
            print("=" * 70)
            print("AFTER decompile of func_80006C64 (sibling, NOT annotated):")
            print("=" * 70)
            print(decompile_text(decomp, f_sibling))
    finally:
        project.close()


if __name__ == "__main__":
    main()
