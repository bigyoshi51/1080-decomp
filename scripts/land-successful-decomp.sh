#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -eq 0 ]; then
    cat >&2 <<'EOF'
land-successful-decomp: expected at least one function name
usage: ./scripts/land-successful-decomp.sh <function_name> [<function_name> ...]

This script only lands verified exact decompiles. For each named function it
requires:
- byte-correctness against expected/.o (via fuzzy=100.0, OR byte-verify of
  build/<unit>.c.o vs expected/<unit>.c.o when fuzzy is None or < 100 — this
  covers post-cc-recipe-driven matches like PREFIX_BYTES / INSN_PATCH /
  SUFFIX_BYTES / PROLOGUE_STEALS, where the byte-correct ROM is exact even
  though the non_matching fuzzy score is < 100 by dual-build design)
- no INCLUDE_ASM fallback still present in src/
- episodes/<function_name>.json exists and passes the canonical schema validator
EOF
    exit 1
fi

repo_root="$(git rev-parse --show-toplevel 2>/dev/null)"
if [ -z "${repo_root:-}" ]; then
    echo "land-successful-decomp: not inside a git worktree" >&2
    exit 1
fi

current_branch="$(git -C "$repo_root" branch --show-current)"
if [ -z "${current_branch:-}" ]; then
    echo "land-successful-decomp: detached HEAD is not supported" >&2
    exit 1
fi

ensure_tracked_clean() {
    local path="$1"
    local label="$2"

    if ! git -C "$path" diff --quiet || ! git -C "$path" diff --cached --quiet; then
        echo "land-successful-decomp: $label has tracked changes; commit or stash them first" >&2
        exit 1
    fi
}

ensure_exact_functions() {
    local report_path="$1"
    shift

    python3 - "$report_path" "$@" <<'PY'
import json
import subprocess
import sys
import os
import glob
import re

report_path = sys.argv[1]
want = sys.argv[2:]

with open(report_path, "r", encoding="utf-8") as f:
    data = json.load(f)

found = {}
for unit in data.get("units", []):
    for fn in unit.get("functions", []):
        name = fn.get("name")
        if name in want:
            found[name] = fn

def byte_verify(name):
    """Return True if build/<seg>/<seg>.c.o and expected/<seg>/<seg>.c.o
    have byte-identical .text for this function — using the symbol-table
    address+size to extract the function's bytes directly (address-
    agnostic; tolerates different upstream offsets in build vs expected
    when adjacent functions have different sizes)."""
    def func_bytes(o):
        # symbol table to find addr + size
        try:
            tab = subprocess.run(
                ["mips-linux-gnu-objdump", "-t", o],
                capture_output=True, text=True, check=True,
            ).stdout
        except subprocess.CalledProcessError:
            return None
        for line in tab.split("\n"):
            if name not in line:
                continue
            parts = line.split()
            # symbol-table line format: ADDR FLAGS SECTION SIZE NAME
            # The trailing field is the symbol name. Match exactly to skip
            # `.NON_MATCHING` (and other suffixed) aliases, which would
            # otherwise get picked first and confuse downstream extraction.
            if not parts or parts[-1] != name:
                continue
            try:
                addr = int(parts[0], 16)
            except (ValueError, IndexError):
                continue
            # find the size field — objdump emits sizes as zero-padded
            # 8-hex-digit words. Restrict to that exact shape so the
            # single-letter type column ('F'/'O' = 15/24) doesn't get
            # picked first and truncate the byte slice.
            size = None
            for p in parts[2:]:
                if len(p) != 8 or not all(c in "0123456789abcdef" for c in p):
                    continue
                s = int(p, 16)
                if 0 < s < 0x100000:
                    size = s
                    break
            if size is None:
                continue
            try:
                text = subprocess.check_output(
                    ["mips-linux-gnu-objcopy", "-O", "binary",
                     "--only-section=.text", o, "/dev/stdout"]
                )
            except subprocess.CalledProcessError:
                return None
            return text[addr:addr + size]
        return None

    # Route to build/non_matching/.o when src has INCLUDE_ASM(name) for this
    # function. Default build/.o uses the #else INCLUDE_ASM path which is
    # trivially byte-equal to expected/.o (both come from the same .s file) —
    # the circular tautology documented at
    # docs/MATCHING_WORKFLOW.md#feedback-include-asm-tautology-trap.
    # build/non_matching/.o defines -DNON_MATCHING=1 and actually compiles
    # the C body, making the comparison meaningful. For post-cc-recipe paths
    # (INSN_PATCH/SUFFIX_BYTES/PROLOGUE_STEALS) where no NM wrap exists, the
    # default build/.o still holds.
    pat = re.compile(rf'INCLUDE_ASM\([^)]*\b{re.escape(name)}\b')
    has_include_asm = False
    for src in glob.glob("src/**/*.c", recursive=True):
        try:
            if pat.search(open(src).read()):
                has_include_asm = True
                break
        except (OSError, UnicodeDecodeError):
            continue
    build_root = "build/non_matching" if has_include_asm else "build"
    # Search for the .o pair by symbol name.
    for base_o in glob.glob(f"{build_root}/src/**/*.c.o", recursive=True):
        rel = os.path.relpath(base_o, build_root)
        exp_o = os.path.join("expected", rel)
        if not os.path.exists(exp_o):
            continue
        ba = func_bytes(base_o)
        if ba is None:
            continue
        ea = func_bytes(exp_o)
        if ea is None:
            continue
        return ba == ea
    return False

errors = []
for name in want:
    fn = found.get(name)
    if fn is None:
        # Not in report — could be a freshly-split symbol whose baseline
        # hasn't been refreshed yet. Fall back to byte-verify.
        if byte_verify(name):
            continue
        errors.append(f"{name}: not present in report.json and byte-verify failed (refresh expected/ baseline?)")
        continue
    fuzzy = fn.get("fuzzy_match_percent")
    if fuzzy == 100.0:
        continue
    # fuzzy != 100 (None, or any number < 100). The function may still be
    # byte-exact in the actual ROM build via post-cc recipes (PREFIX_BYTES,
    # INSN_PATCH, SUFFIX_BYTES, PROLOGUE_STEALS) that build/non_matching/
    # deliberately excludes — the dual-build design keeps fuzzy as a "C-only"
    # metric. Byte-correctness against expected/ is the actual landing
    # criterion; fuzzy is just an advisory partial-progress score.
    # See feedback_uso_entry0_trampoline_95pct_cap_class.md.
    if byte_verify(name):
        continue
    if fuzzy is None:
        errors.append(f"{name}: null fuzzy_match_percent and byte-verify failed")
    else:
        errors.append(f"{name}: not byte-exact (fuzzy_match_percent={fuzzy}, build/.o vs expected/.o disasm also differs)")

if errors:
    for err in errors:
        print(f"land-successful-decomp: {err}", file=sys.stderr)
    sys.exit(1)
PY
}

ensure_not_include_asm() {
    local func_name="$1"

    if rg -n "INCLUDE_ASM\\([^\\n]*\\b${func_name}\\b" "$repo_root/src" >/dev/null; then
        echo "land-successful-decomp: $func_name still has an INCLUDE_ASM fallback in src/" >&2
        exit 1
    fi
}

ensure_episode_exists() {
    local func_name="$1"

    if [ ! -f "$repo_root/episodes/${func_name}.json" ]; then
        echo "land-successful-decomp: missing episodes/${func_name}.json" >&2
        exit 1
    fi
}

ensure_episode_schema() {
    local func_name="$1"

    if ! python3 "$repo_root/../../scripts/validate_episode_schema.py" \
        "$repo_root/episodes/${func_name}.json" --require-match; then
        echo "land-successful-decomp: episodes/${func_name}.json does not match the canonical schema" >&2
        exit 1
    fi
}

main_worktree=""
pending_path=""
while IFS= read -r line; do
    case "$line" in
        worktree\ *)
            pending_path="${line#worktree }"
            ;;
        branch\ refs/heads/main)
            main_worktree="$pending_path"
            ;;
    esac
done < <(git -C "$repo_root" worktree list --porcelain)

if [ -z "$main_worktree" ]; then
    echo "land-successful-decomp: could not find a main worktree" >&2
    exit 1
fi

ensure_tracked_clean "$repo_root" "current worktree"
ensure_tracked_clean "$main_worktree" "main worktree"

git -C "$repo_root" fetch origin
if [ "$current_branch" != "main" ]; then
    git -C "$repo_root" rebase origin/main
fi

"$repo_root/scripts/refresh-report.sh"
ensure_exact_functions "$repo_root/report.json" "$@"
for func_name in "$@"; do
    ensure_not_include_asm "$func_name"
    ensure_episode_exists "$func_name"
    ensure_episode_schema "$func_name"
done

# Refresh expected/ baseline so CI scores fresh build/.o against an
# up-to-date pure-INCLUDE_ASM snapshot. Use refresh-expected-baseline.py
# (NOT the Makefile's `expected` target directly): the Makefile target
# is a blanket cp of build/*.o → expected/*.o, which when run against a
# decomp-bodies build snapshots the decomp build INTO expected/, making
# expected/.o byte-identical to build/.o by definition and reporting
# 100% match for every function in the file (including NM-wrapped ones).
# refresh-expected-baseline.py swaps every C body to INCLUDE_ASM before
# building, so expected/ is a truthful pure-asm baseline.
# See feedback_report_json_vs_decomp_dev_diverge.md.
(cd "$repo_root" && python3 scripts/refresh-expected-baseline.py)
if ! git -C "$repo_root" diff --quiet -- expected/ \
   || [ -n "$(git -C "$repo_root" ls-files --others --exclude-standard -- expected/)" ]; then
    git -C "$repo_root" add expected/
    git -C "$repo_root" commit -m "Refresh expected/ baseline for $* land

Auto-generated by land-successful-decomp.sh: pure-INCLUDE_ASM rebuild
via refresh-expected-baseline.py after verifying $* matches exact, so
CI scores against a truthful baseline.

Co-Authored-By: Claude Opus 4.7 (1M context) <noreply@anthropic.com>"
fi

git -C "$main_worktree" fetch origin
git -C "$main_worktree" merge --ff-only origin/main

if [ "$current_branch" != "main" ]; then
    if ! git -C "$repo_root" merge-base --is-ancestor origin/main "$current_branch"; then
        echo "land-successful-decomp: $current_branch is behind origin/main after fetch; rerun after rebasing" >&2
        exit 1
    fi
    git -C "$main_worktree" merge --ff-only "$current_branch"
fi

git -C "$main_worktree" push origin main

"$main_worktree/scripts/refresh-report.sh"
if [ "$repo_root" != "$main_worktree" ]; then
    "$repo_root/scripts/refresh-report.sh"
fi

printf 'land-successful-decomp: landed %s to main and pushed origin/main for %s\n' "$current_branch" "$*"
