#!/usr/bin/env bash
set -euo pipefail
REPO_ROOT="$(git rev-parse --show-toplevel)"
PARENT_TOOLS="$REPO_ROOT/../../tools"
export JAVA_HOME="$PARENT_TOOLS/jdk-21.0.5"
export GHIDRA_INSTALL_DIR="$PARENT_TOOLS/ghidra-12.0.4"
export PATH="$JAVA_HOME/bin:$PATH"
exec "$HOME/.local/share/uv/tools/pyghidra-mcp/bin/python" "$REPO_ROOT/scripts/ghidra-decompile-func.py" "$@"
