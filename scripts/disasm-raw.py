#!/usr/bin/env python3
"""Reliable raw-`.word` disassembly (and optional m2c) for USO functions.

WHY THIS EXISTS (vs `disasm-func.py`): `disasm-func.py` objdumps the BUILT
`build/non_matching/**/*.c.o`. For a function that ALREADY has a
`#ifdef NON_MATCHING` body, that shows YOUR CURRENT C body's compilation, NOT
the target bytes (cost a wasted reconstruction on gl_func_000717CC 2026-06-06).
It also resolves branch targets against `.o` offsets, which fall outside the
symbol range for some functions ("label .LXXXX does not exist").

This script reads the raw `.word` list straight from
`asm/nonmatchings/**/<func>.s` and objdumps it as a 0-based binary blob, so:
  * it ALWAYS shows the TARGET (independent of wrap state), and
  * every intra-function branch resolves inside [0, size) -> valid .L labels.

Usage:
    scripts/disasm-raw.py <func>            # print target mnemonics
    scripts/disasm-raw.py <func> --m2c      # reformat to m2c-ready .s + run m2c

Caveats (genuine caps, not tool bugs — both modes surface them):
  * branch target past the function end == an inter-function tail-branch
    (PC-relative jump into a sibling function); not C-expressible.
  * a register READ before being written (e.g. `blez t7` at entry, `mflo`
    with no preceding `mult`) == caller-set register cap.
  * `k0`/`k1` operands == kernel/exception context; m2c can't parse them.
"""
import re, struct, subprocess, sys, glob, tempfile, os


def load_words(name):
    fs = glob.glob("asm/nonmatchings/**/%s.s" % name, recursive=True)
    if not fs:
        sys.exit("no .s found for %s under asm/nonmatchings/" % name)
    return [int(m, 16) for m in
            re.findall(r"\.word 0x([0-9A-Fa-f]{8})", open(fs[0]).read())]


def objdump_blob(words):
    blob = b"".join(struct.pack(">I", w) for w in words)
    fd, p = tempfile.mkstemp(suffix=".bin")
    os.write(fd, blob); os.close(fd)
    try:
        out = subprocess.run(
            ["mips-linux-gnu-objdump", "-D", "-b", "binary", "-m", "mips:4000",
             "-EB", "-M", "no-aliases", p],
            capture_output=True, text=True).stdout
    finally:
        os.unlink(p)
    body = []
    for ln in out.splitlines():
        m = re.match(r"\s+([0-9a-f]+):\s+[0-9a-f]{8}\s+(.*)", ln)
        if m:
            body.append((int(m.group(1), 16), m.group(2).strip()))
    return body


def to_m2c_asm(name, body):
    size = (body[-1][0] + 4) if body else 0
    # Only these mnemonics carry a code-ADDRESS in their trailing operand; for
    # everything else (lui/ori/addiu/...) the trailing 0xN is an IMMEDIATE and
    # must be left alone (else `lui a0,0x2` becomes a bogus `.L2` label).
    BRANCH = {"b", "beq", "bne", "beql", "bnel", "blez", "bgtz", "bltz",
              "bgez", "bltzal", "bgezal", "beqz", "bnez", "bc1t", "bc1f",
              "bc1tl", "bc1fl"}
    CALL = {"jal", "j", "jalr", "bal"}
    targets = set()
    out = []
    for addr, insn in body:
        mnem = insn.split()[0] if insn else ""
        bm = re.search(r"\b0x([0-9a-f]+)$", insn)
        if bm and mnem in BRANCH:
            tgt = int(bm.group(1), 16)
            targets.add(tgt)
            insn = insn[:bm.start()].rstrip() + " .L%X" % tgt
        elif bm and mnem in CALL:
            insn = insn[:bm.start()].rstrip() + " func_%06X" % int(bm.group(1), 16)
        out.append((addr, insn))
    lines = ["glabel %s" % name]
    for addr, insn in out:
        if addr in targets:
            lines.append(".L%X:" % addr)
        lines.append("/* %X */  %s" % (addr, insn))
    # any branch target at/after end is an inter-function tail-branch; warn.
    for t in sorted(targets):
        if t >= size:
            lines.insert(0, "/* WARN: branch to .L%X is past end (0x%X) -- "
                            "inter-function tail-branch, not C-expressible */"
                            % (t, size))
    return "\n".join(lines) + "\n"


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    name = sys.argv[1]
    m2c = "--m2c" in sys.argv[2:]
    body = objdump_blob(load_words(name))
    if not m2c:
        sys.stdout.write("glabel %s\n" % name)
        for addr, insn in body:
            sys.stdout.write("/* %X */  %s\n" % (addr, insn))
        return
    asm = to_m2c_asm(name, body)
    fd, p = tempfile.mkstemp(suffix=".s")
    os.write(fd, asm.encode()); os.close(fd)
    try:
        subprocess.run(["uv", "run", "m2c", "--target", "mips-ido-c", p])
    finally:
        os.unlink(p)


if __name__ == "__main__":
    main()
