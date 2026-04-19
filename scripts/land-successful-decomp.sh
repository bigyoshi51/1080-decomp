#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -eq 0 ]; then
    cat >&2 <<'EOF'
land-successful-decomp: expected at least one function name
usage: ./scripts/land-successful-decomp.sh <function_name> [<function_name> ...]

This script only lands verified exact decompiles. For each named function it
requires:
- no fuzzy_match_percent entry in report.json
- no INCLUDE_ASM fallback still present in src/
- episodes/<function_name>.json exists
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
import sys

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

errors = []
for name in want:
    fn = found.get(name)
    if fn is None:
        errors.append(f"{name}: not present in report.json")
        continue
    if "fuzzy_match_percent" in fn:
        errors.append(
            f"{name}: still fuzzy at {fn['fuzzy_match_percent']:.6f}%"
        )

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
done

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
