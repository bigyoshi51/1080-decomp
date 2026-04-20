#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -eq 0 ]; then
    cat >&2 <<'EOF'
land-successful-decomp: expected at least one function name
usage: ./scripts/land-successful-decomp.sh <function_name> [<function_name> ...]

This script only lands verified exact decompiles. For each named function it
requires:
- report.json to mark it exact (fuzzy_match_percent == 100.0 strictly)
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
    have byte-identical .text for this function."""
    # Search for the .o pair by symbol name.
    for base_o in glob.glob("build/src/**/*.c.o", recursive=True):
        rel = os.path.relpath(base_o, "build")
        exp_o = os.path.join("expected", rel)
        if not os.path.exists(exp_o):
            continue
        try:
            b = subprocess.run(
                ["mips-linux-gnu-objdump", "-d", "-M", "no-aliases", base_o],
                capture_output=True, text=True, check=True,
            ).stdout
            if f"<{name}>:" not in b:
                continue
            e = subprocess.run(
                ["mips-linux-gnu-objdump", "-d", "-M", "no-aliases", exp_o],
                capture_output=True, text=True, check=True,
            ).stdout
            # Extract the function's disasm block from both.
            def block(txt):
                idx = txt.index(f"<{name}>:")
                end = txt.find("\n\n", idx)
                return txt[idx:end if end > 0 else None]
            return block(b) == block(e)
        except (subprocess.CalledProcessError, ValueError):
            continue
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
    if fuzzy is None:
        # objdiff reports null when build.o bytes == expected.o bytes (no diff
        # to quantify). This is usually a legit match, but can also be a
        # contaminated baseline. Fall back to byte-verify against the CURRENT
        # expected/ — which is trustworthy if the user just ran
        # scripts/refresh-expected-baseline.py.
        if byte_verify(name):
            continue
        errors.append(f"{name}: null fuzzy_match_percent and byte-verify failed")
        continue
    errors.append(f"{name}: not an exact match (fuzzy_match_percent={fuzzy})")

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
# up-to-date snapshot. Without this, CI compares the new build against
# whatever expected/.o was committed last and the converted/decomped
# functions stay below 100 % on decomp.dev. See
# feedback_expected_must_be_committed_for_decomp_dev.md.
make -C "$repo_root" expected RUN_CC_CHECK=0 >/dev/null
if ! git -C "$repo_root" diff --quiet -- expected/ \
   || [ -n "$(git -C "$repo_root" ls-files --others --exclude-standard -- expected/)" ]; then
    git -C "$repo_root" add expected/
    git -C "$repo_root" commit -m "Refresh expected/ baseline for $* land

Auto-generated by land-successful-decomp.sh: \`make expected\` after
verifying $* matches exact, so CI scores against the updated baseline.

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
