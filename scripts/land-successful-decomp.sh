#!/usr/bin/env bash
set -euo pipefail

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

printf 'land-successful-decomp: landed %s to main and pushed origin/main\n' "$current_branch"
