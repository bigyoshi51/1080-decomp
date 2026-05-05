#!/usr/bin/env bash
# Wrapper for setup-ghidra.py — sets JAVA_HOME, GHIDRA_INSTALL_DIR, points to the
# pyghidra-mcp venv interpreter, then runs the Python script.
set -euo pipefail

REPO_ROOT="$(git rev-parse --show-toplevel)"
# Tools live in the parent decomp repo's tools/ dir (git-ignored)
PARENT_TOOLS="$REPO_ROOT/../../tools"
export JAVA_HOME="$PARENT_TOOLS/jdk-21.0.5"
export GHIDRA_INSTALL_DIR="$PARENT_TOOLS/ghidra-12.0.4"
export PATH="$JAVA_HOME/bin:$PATH"

if [ ! -x "$JAVA_HOME/bin/java" ]; then
    echo "ERROR: JDK 21 not found at $JAVA_HOME" >&2
    echo "       Install with the snippet in feedback_pyghidra_mcp_setup_for_n64_decomp.md" >&2
    exit 1
fi
if [ ! -x "$GHIDRA_INSTALL_DIR/support/analyzeHeadless" ]; then
    echo "ERROR: Ghidra not found at $GHIDRA_INSTALL_DIR" >&2
    exit 1
fi

PYGHIDRA_PY="$HOME/.local/share/uv/tools/pyghidra-mcp/bin/python"
if [ ! -x "$PYGHIDRA_PY" ]; then
    echo "ERROR: pyghidra-mcp not installed; run 'uv tool install pyghidra-mcp' first" >&2
    exit 1
fi

exec "$PYGHIDRA_PY" "$REPO_ROOT/scripts/setup-ghidra.py" "$@"
