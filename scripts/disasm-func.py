#!/usr/bin/env python3
"""Disassemble one function from a built/expected .o into m2c-ready MIPS asm.

The 1080 USO segments are stored as raw `.word` directives (splat can't
disassemble relocatable USO code), so `m2c` — which needs mnemonic assembly —
can't read `asm/nonmatchings/.../<fn>.s` directly. This script objdumps the
assembled bytes from a real `.o` (which DO have mnemonics) and reformats them
into the `glabel <fn>` + tab-indented-instruction shape m2c expects.

Usage:
    python3 scripts/disasm-func.py <func_name> [--obj <path.o>] [--m2c]

Without --obj it reads the TARGET: expected/**/*.c.o first (build/non_matching holds
whatever the current NM body compiles to, possibly clip-shifted -- pass --nm for that).
With --m2c it pipes the result through `uv run m2c --target mips-ido-c`.
"""
import argparse
import glob
import subprocess
import sys
from elftools.elf.elffile import ELFFile


def find_symbol(obj, name):
    f = ELFFile(open(obj, "rb"))
    st = f.get_section_by_name(".symtab")
    if not st:
        return None
    for s in st.iter_symbols():
        if s.name == name and s["st_size"]:
            return s["st_value"], s["st_size"]
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("func")
    ap.add_argument("--obj")
    ap.add_argument("--m2c", action="store_true")
    ap.add_argument("--nm", action="store_true", help="disassemble the NM build instead of the target")
    args = ap.parse_args()

    nm = glob.glob("build/non_matching/**/*.c.o", recursive=True)
    exp = glob.glob("expected/**/*.c.o", recursive=True)
    objs = [args.obj] if args.obj else (nm + exp if args.nm else exp + nm)
    hit = None
    for o in objs:
        r = find_symbol(o, args.func)
        if r:
            hit = (o, *r)
            break
    if not hit:
        sys.exit(f"disasm-func: {args.func} not found in any .o")
    obj, val, size = hit

    dump = subprocess.run(
        ["mips-linux-gnu-objdump", "-d", "-M", "no-aliases",
         f"--start-address={val}", f"--stop-address={val + size}", obj],
        capture_output=True, text=True).stdout

    import re
    # Pass 1: collect (addr, insn) and BRANCH target addresses (NOT jal/j calls).
    body = []
    targets = set()
    for ln in dump.splitlines():
        parts = ln.split("\t")
        if len(parts) >= 3 and ":" in parts[0]:
            addr = int(parts[0].strip().rstrip(":"), 16)
            insn = " ".join(p.strip() for p in parts[2:]).strip()
            mnem = insn.split()[0] if insn else ""
            m = re.search(r"\b([0-9a-f]+) <([^>]+)>$", insn)
            if m:
                if mnem in ("jal", "j", "jalr", "bal"):
                    # call/jump to a function: keep the symbol name (strip +off)
                    sym = m.group(2).split("+")[0]
                    insn = insn[: m.start()].rstrip() + " " + sym
                else:
                    # conditional branch: local .L label
                    tgt = int(m.group(1), 16)
                    targets.add(tgt)
                    insn = insn[: m.start()].rstrip() + f".L{tgt:X}"
            body.append((addr, insn))

    lines = [f"glabel {args.func}"]
    for addr, insn in body:
        if addr in targets:
            lines.append(f".L{addr:X}:")
        lines.append(f"/* {addr:X} */  {insn}")
    asm = "\n".join(lines) + "\n"

    if args.m2c:
        import tempfile, os
        fd, path = tempfile.mkstemp(suffix=".s")
        os.write(fd, asm.encode()); os.close(fd)
        subprocess.run(["uv", "run", "m2c", "--target", "mips-ido-c", path])
        os.unlink(path)
    else:
        sys.stdout.write(asm)


if __name__ == "__main__":
    main()
