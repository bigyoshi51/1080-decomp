#!/usr/bin/env bash
set -euo pipefail

repo_root="$(git rev-parse --show-toplevel 2>/dev/null)"
if [ -z "${repo_root:-}" ]; then
    echo "refresh-report: not inside a git worktree" >&2
    exit 1
fi

cd "$repo_root"

if ! command -v objdiff-cli >/dev/null 2>&1; then
    echo "refresh-report: objdiff-cli not found in PATH" >&2
    exit 1
fi

if [ ! -f objdiff.json ]; then
    echo "refresh-report: objdiff.json not found in $repo_root" >&2
    exit 1
fi

objdiff-cli report generate > report.json

python3 - <<'PY'
import json

with open("report.json", "r", encoding="utf-8") as f:
    data = json.load(f)

m = data["measures"]
print(
    "refresh-report:",
    f"{m['matched_functions']}/{m['total_functions']} functions,",
    f"{m['matched_code']}/{m['total_code']} code bytes",
)
PY
