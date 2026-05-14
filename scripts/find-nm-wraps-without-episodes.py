#!/usr/bin/env python3
"""
Find NM-wrap functions (#ifdef NON_MATCHING ... #else INCLUDE_ASM ... #endif)
that don't yet have an episode logged.

Use this BEFORE attempting episode-logging via the byte-verify-first sweep
recipe. Caveats:

- The land script's `byte_verify` must route to `build/non_matching/.o` for
  NM-wrapped functions (post 2026-05-14 fix in agent-i). Otherwise it's the
  documented circular tautology — see
  docs/MATCHING_WORKFLOW.md#feedback-include-asm-tautology-trap.
- Just because a function shows up here does NOT mean it's byte-exact. The
  C body may have real diffs vs expected/.o. Always byte-verify against
  build/non_matching/.o (not default build/.o) BEFORE logging an episode.
- Functions with `fuzzy_match_percent: 100.0` in report.json are already
  counted as matched — re-logging is redundant.

Run from a project worktree (where src/, asm/, episodes/, report.json
all exist).
"""
import os
import re
import sys
import json
import subprocess
from pathlib import Path


def find_nm_wraps_without_episodes() -> list[tuple[str, str]]:
    """Return [(function_name, source_file_path), ...] for NM-wrapped
    functions that have no episodes/<name>.json file yet."""
    results = []
    nm_re = re.compile(
        r'#ifdef NON_MATCHING.*?#else\s*INCLUDE_ASM\("[^"]+",\s*(\w+)\);\s*#endif',
        re.DOTALL,
    )
    for root, _, files in os.walk("src"):
        for f in files:
            if not f.endswith(".c"):
                continue
            path = os.path.join(root, f)
            try:
                text = open(path).read()
            except (OSError, UnicodeDecodeError):
                continue
            for m in nm_re.finditer(text):
                fn = m.group(1)
                if not os.path.exists(f"episodes/{fn}.json"):
                    results.append((fn, path))
    return results


def report_match_percents(names: set[str]) -> dict[str, float | None]:
    """Read fuzzy_match_percent from report.json for the given function names."""
    if not os.path.exists("report.json"):
        return {}
    try:
        d = json.load(open("report.json"))
    except json.JSONDecodeError:
        return {}
    out: dict[str, float | None] = {}
    for unit in d.get("units", []):
        for fn in unit.get("functions", []):
            n = fn.get("name")
            if n in names:
                out[n] = fn.get("fuzzy_match_percent")
    return out


def main() -> int:
    if not Path("src").is_dir():
        print("error: run from a project worktree (no src/ directory)", file=sys.stderr)
        return 1
    wraps = find_nm_wraps_without_episodes()
    print(f"NM-wraps without episodes: {len(wraps)}")
    pcts = report_match_percents({fn for fn, _ in wraps})
    # Sort by percent desc (high first)
    annotated = [(fn, path, pcts.get(fn)) for fn, path in wraps]
    annotated.sort(key=lambda x: (-(x[2] or 0), x[0]))
    for fn, path, mp in annotated[:50]:
        mp_str = f"{mp:.1f}%" if mp is not None else "None"
        rel_path = os.path.relpath(path)
        print(f"  {mp_str:>6}  {fn}  ({rel_path})")
    if len(annotated) > 50:
        print(f"  ... {len(annotated) - 50} more")
    return 0


if __name__ == "__main__":
    sys.exit(main())
