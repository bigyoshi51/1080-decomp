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

jobs="$(getconf _NPROCESSORS_ONLN 2>/dev/null || nproc 2>/dev/null || echo 8)"
make -j"$jobs" objects >/dev/null

objdiff-cli report generate > report.json

python3 - <<'PY'
import json, re, pathlib

with open("report.json", "r", encoding="utf-8") as f:
    data = json.load(f)

m = data["measures"]
tot_f = m["total_functions"]
mat_f = m.get("matched_functions", 0)
tot_c = int(m["total_code"])
mat_c = int(m.get("matched_code", 0))
pct = m.get("matched_code_percent", 0.0)

print(
    "refresh-report:",
    f"{mat_f}/{tot_f} functions,",
    f"{mat_c}/{tot_c} code bytes ({pct:.2f}%)",
)

# Staleness check: compare against README table if present
readme = pathlib.Path("README.md")
if readme.exists():
    txt = readme.read_text()
    m2 = re.search(r"\*\*([\d,]+)\s*/\s*([\d,]+)\*\*\s*\|\s*\*\*([\d.]+)\s*KB\s*/\s*([\d.]+)\s*KB\s*\(([\d.]+)%\)\*\*", txt)
    if m2:
        readme_mf = int(m2.group(1).replace(",", ""))
        readme_tf = int(m2.group(2).replace(",", ""))
        readme_pct = float(m2.group(5))
        drift_f = mat_f - readme_mf
        drift_pct = pct - readme_pct
        if abs(drift_pct) >= 2.0 or abs(drift_f) >= 25 or tot_f != readme_tf:
            print(f"refresh-report: README TOTAL row is stale — "
                  f"README says {readme_mf}/{readme_tf} ({readme_pct:.2f}%), "
                  f"actual {mat_f}/{tot_f} ({pct:.2f}%). Consider updating README.md.")
PY
