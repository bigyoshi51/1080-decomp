#!/usr/bin/env bash
# Per-worktree setup for 1080 Snowboarding agents.
# Invoked by scripts/spin-up-agent.sh from inside the new worktree.
set -euo pipefail

ln -s "../../1080 Snowboarding (USA)/tools/ido-static-recomp" tools/ido-static-recomp
ln -s "../1080 Snowboarding (USA)/baserom.z64" baserom.z64

# assets/ is .gitignored AND the Makefile uses `find assets -name '*.bin'`,
# which skips symlinks — must be copied. ~17 MB.
cp -r "../1080 Snowboarding (USA)/assets" ./

# Don't pollute git status with the symlinked toolchain dir.
GIT_EXCLUDE="$(git rev-parse --git-path info/exclude)"
echo "/tools/ido-static-recomp" >> "$GIT_EXCLUDE"
