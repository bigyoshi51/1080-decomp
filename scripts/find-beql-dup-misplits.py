#!/usr/bin/env python3
"""Find IDO branch-likely dup-first-insn MIS-SPLITS in asm/nonmatchings.

For `beql`/`bnel` (and other branch-likely forms) IDO copies the FIRST insn of
the target block into the branch delay slot and retargets the branch to
block+4, leaving the original insn in place as dead code. When the fall-through
arm ends in `jr ra`, the splitter (generate-uso-asm / splat jr-ra heuristic)
cuts the block off as a separate tiny "function". Fingerprint: symbol A ends
`jr ra; <delay>`; the ADJACENT next symbol B has no prologue; some branch-likely
in A targets B+4 and A's delay-slot word == B's first word. A and B are ONE
function (B is A's else/null block; a chain of several is common). Merge the .s
and decompile as a unit -- prior "leaf-branch-past-end / tail-share cap"
verdicts on such pairs have been wrong every time checked.

See docs/MATCHING_WORKFLOW.md
#feedback-beql-next-symbol-plus-4-is-mis-split-branch-likely-block
(game_uso 7A98+7ABC; game_libs 9A50+9A6C+9A80+9A9C+9AB0+9AD0).

Usage: scripts/find-beql-dup-misplits.py [--all]
  default: strict (B <= 8 words). --all: any branch in A that lands in B.
"""
import glob, os, re, sys

ROOT = "asm/nonmatchings"
RX = re.compile(r"/\*\s*([0-9A-Fa-f]+)\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]{8})\s*\*/")


def words(path):
    out = []
    for line in open(path, errors="replace"):
        m = RX.search(line)
        if m:
            out.append((int(m.group(2), 16), int(m.group(3), 16)))
    return out


def is_branch_likely(w):
    op = w >> 26
    if op in (0x14, 0x15, 0x16, 0x17):
        return True
    if op == 1 and ((w >> 16) & 0x1F) in (2, 3, 0x12, 0x13):
        return True
    if op == 0x11 and ((w >> 21) & 0x1F) == 8 and ((w >> 16) & 3) in (2, 3):
        return True
    return False


def is_branch(w):
    op = w >> 26
    return (op in (4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17)
            or (op == 1 and ((w >> 16) & 0x1F) in (0, 1, 2, 3, 0x10, 0x11, 0x12, 0x13))
            or (op == 0x11 and ((w >> 21) & 0x1F) == 8))


def boff(w):
    off = w & 0xFFFF
    return off - 0x10000 if off & 0x8000 else off


def main():
    relaxed = "--all" in sys.argv
    for seg in sorted(os.listdir(ROOT)):
        files = []
        for p in glob.glob(f"{ROOT}/{seg}/**/*.s", recursive=True):
            txt = open(p, errors="replace").read()
            if ".section .rodata" in txt or ".section .data" in txt or re.search(r"^dlabel", txt, re.M):
                continue
            w = words(p)
            if w:
                files.append((w[0][0], p, w))
        files.sort()
        for i in range(1, len(files)):
            addr_a, p_a, w_a = files[i - 1]
            addr_b, p_b, w_b = files[i]
            if w_a[-1][0] + 4 != addr_b:
                continue
            if (w_b[0][1] >> 16) == 0x27BD:  # addiu sp,sp,-N prologue
                continue
            if not relaxed and len(w_b) > 8:
                continue
            for k, (va, w) in enumerate(w_a[:-1]):
                if not is_branch(w):
                    continue
                tgt = va + 4 + boff(w) * 4
                if tgt < addr_b or tgt >= w_b[-1][0] + 4:
                    continue
                dup = is_branch_likely(w) and tgt == addr_b + 4 and w_a[k + 1][1] == w_b[0][1]
                if dup or relaxed:
                    print(f"{seg}: A={os.path.basename(p_a)} ({len(w_a)}w) -> B={os.path.basename(p_b)} "
                          f"({len(w_b)}w) br@{va:X} tgt={tgt:X} {'DUP-FIRST-INSN' if dup else ''}")


if __name__ == "__main__":
    main()
