#!/usr/bin/env python3
"""Find uncovered byte ranges between consecutive per-function .s files in USO
segments — these are boundary bugs from generate-uso-asm.py's prologue-scan
heuristic. Three classes (see docs/MATCHING_WORKFLOW.md
#feedback-cross-function-tail-share "CAVEAT"):

  - DROPPED FUNCTIONS: a large gap (many words) of real code that no .s
    covers — whole functions splat omitted. The segment is built short and
    everything after shifts. Recover by creating .s files for each + .c
    integration. (e.g. arcproc_uso 0xEEC: two leaves dropped.)
  - TRUNCATED TAIL: a function cut short; its own body (incl. branch targets)
    past the cut is in the gap. Extend the .s. (titproc_uso 000016B8.)
  - PROLOGUE-STOLEN START: the next function's `lui rX; addiu rX` base-load
    sits before its symbol in the gap. Rename to the true entry + restore the
    prefix words. (titproc_uso 0000028C -> 00000284.)

Pad files (*_pad.s) ARE counted as coverage, so trailing-alignment gaps are
not reported. Small (1-3 word) gaps are usually legit trailing data/padding;
LARGE gaps and gaps whose bytes decode as code (prologue / jr ra) are the
real bugs.

FALSE POSITIVES — always `grep src/` for the gap's function FIRST:
  - matched-C functions have NO .s (they're unconditional C compiled
    directly), so their region shows as an uncovered "gap" though the build
    has them (e.g. game_libs_func_000683C4). NOT a bug — skip.
  - a TRUNCATED .s (e.g. game_libs_func_0004D39C: .s 0x34 but real fn 0x48)
    shows the dropped tail as a gap AFTER the function. If src already has a
    full NM/matched C body, just extend the .s to the true size + unwrap —
    often an instant match (the C was already exact, only the .s was short).
  - YAY0 segments (game_uso/timproc*/mgrproc/map4_data): the .s ROM column is
    the UNCOMPRESSED offset, so byte reads from baserom are WRONG (compressed
    data). Gap arithmetic is valid but the CODE/data classification is bogus.

Usage: python3 scripts/find-uso-coverage-gaps.py [segment_substr]
"""
import os, re, glob, struct, sys

ROMLINE = re.compile(r'/\*\s*([0-9A-Fa-f]+)\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]+)\s*\*/')
HDR = re.compile(r'nonmatching\s+(\S+),\s*0x([0-9A-Fa-f]+)')


def words_of(path):
    return [(int(m.group(1), 16), int(m.group(2), 16), m.group(3))
            for m in ROMLINE.finditer(open(path).read())]


def looks_like_code(rom_words):
    # heuristic: contains addiu $sp,-N (prologue) or 03E00008 (jr ra)
    for w in rom_words:
        v = int(w, 16)
        if (v >> 16) == 0x27BD and (v & 0x8000):
            return "prologue"
        if v == 0x03E00008:
            return "jr ra"
    return None


def main():
    filt = sys.argv[1] if len(sys.argv) > 1 else ""
    rom = open("baserom.z64", "rb").read()
    for segdir in sorted(glob.glob("asm/nonmatchings/*/*/")):
        seg = segdir.split("/")[-3]
        if filt and filt not in seg:
            continue
        covered = set()
        funcs = []
        for sf in glob.glob(segdir + "*.s"):
            ws = words_of(sf)
            for r, v, w in ws:
                covered.add(r)
            if "_pad" not in sf:
                h = HDR.search(open(sf).read())
                if h and ws:
                    funcs.append((ws[0][0], int(h.group(2), 16), os.path.basename(sf)))
        funcs.sort()
        if not funcs:
            continue
        rombase = funcs[0][0] - int(re.search(r'_([0-9A-Fa-f]+)\.s', funcs[0][2]).group(1), 16)
        for i in range(len(funcs) - 1):
            rstart, size, name = funcs[i]
            nstart = funcs[i + 1][0]
            gap = [a for a in range(rstart + size, nstart, 4) if a not in covered]
            if not gap:
                continue
            words = [f"{struct.unpack('>I', rom[a:a+4])[0]:08X}" for a in gap]
            kind = looks_like_code(words)
            tag = "CODE/" + kind if kind else "data?"
            print(f"{seg}: after {name} — {len(gap)} uncovered words @rom 0x{gap[0]:X} [{tag}]")


if __name__ == "__main__":
    main()
