#!/usr/bin/env bash
# regalloc-dump.sh <function_name> — dump IDO's register-allocation coloring for one
# function, the systematic diagnostic for register-renumber / spill caps.
#
# Recompiles the (NON_MATCHING) preprocessed TU that defines <function_name> with
# `cc -Wo,-zdbug:6` (writes a file `uoptlist` in CWD), then extracts that function's
# section: the UCODE flow-graph vreg lines + the `N: N assigned (un)constrained R`
# candidate->register coloring. Reorder the C so the value you want in the lower
# reg is referenced first (see docs/IDO_CODEGEN.md#feedback-ido-regalloc-renumber-
# matching-techniques and the project_1080_regalloc_dump memo).
#
# Requires the ecvt/fcvt patch in tools/ido-static-recomp/libc_impl.c (per-machine,
# gitignored — see the regalloc_dump memo). If the dump is empty, the patch is not
# applied to THIS worktree's ido copy.
#
# Usage: scripts/regalloc-dump.sh game_uso_func_00007538
set -euo pipefail

fn="${1:?usage: regalloc-dump.sh <function_name>}"
cc="tools/ido-static-recomp/build/7.1/out/cc"
[ -x "$cc" ] || { echo "regalloc-dump: $cc not found (build ido first)" >&2; exit 1; }

# Locate the build/non_matching/.o that defines the symbol, then its preprocessed .c.
obj=""
for o in build/non_matching/src/*/*.c.o; do
    # capture first (avoid SIGPIPE under pipefail when grep -q exits early)
    syms="$(mips-linux-gnu-nm "$o" 2>/dev/null || true)"
    if printf '%s\n' "$syms" | grep -qE " [Tt] ${fn}$"; then obj="$o"; break; fi
done
[ -n "$obj" ] || { echo "regalloc-dump: no build/non_matching object defines $fn (run 'make non_matching_objects' first)" >&2; exit 1; }
src="${obj%.o}"          # build/non_matching/src/<seg>/<file>.c
[ -f "$src" ] || { echo "regalloc-dump: preprocessed TU $src missing" >&2; exit 1; }

# Per-file OPT_FLAGS: most are -O2; a few -O0/-O1 splits. Honor a 2nd arg override.
opt="${2:--O2}"
rm -f uoptlist
"$cc" -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul "$opt" -mips2 -32 \
      -DNON_MATCHING=1 -I include -I src -Wo,-zdbug:6 -o /dev/null "$src" 2>/dev/null || true
[ -s uoptlist ] || { echo "regalloc-dump: uoptlist empty — ecvt patch not applied to this worktree's ido (see regalloc_dump memo)" >&2; exit 1; }

# Extract this function's section (between its first "OF <fn>" phase line and the
# next function's "OF <other>"), print the coloring + a register legend.
awk -v fn="$fn" '
  /[A-Z] OF [a-zA-Z0-9_]+$/ { cur=$NF; inf=(cur==fn) }
  inf { print }
' uoptlist > "/tmp/uopt_${fn}.txt"

echo "=== regalloc coloring for $fn (opt=$opt, full section: /tmp/uopt_${fn}.txt) ==="
echo "--- candidate -> register ( N: N assigned R ) ---"
grep -E "assigned \((un)?constrained\)" "/tmp/uopt_${fn}.txt" || echo "(no coloring lines — check /tmp/uopt_${fn}.txt)"
cat <<'LEGEND'
--- IDO internal R -> MIPS (color order): ---
  1=$v0 2=$v1 3=$a0 4=$a1 5=$a2 6=$a3 7..14=$t0..$t7 24=$t8 25=$t9
  (callee-saved) the dump's 14..21 form = $s0..$s7 for promoted loop-invariants.
  Earlier-encountered candidate wins the lower reg -> reference-first to steer it.
LEGEND
