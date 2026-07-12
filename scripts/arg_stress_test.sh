#!/usr/bin/env bash
set -u

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT" || exit 1
BIN="./cub3D"

pass=0
fail=0
crash=0

run_case() {
	local name="$1"
	shift
	local out
	local rc
	local sig

	out=$(timeout 3 "$BIN" "$@" 2>&1)
	rc=$?

	if [ $rc -eq 124 ]; then
		printf 'TIMEOUT  %-50s (opened window? kill with timeout)\n' "$name"
		((fail++)) || true
		return
	fi
	if [ $rc -gt 128 ]; then
		sig=$((rc - 128))
		printf 'CRASH    %-50s signal %s\n' "$name" "$sig"
		((crash++)) || true
		return
	fi
	if [ $rc -eq 0 ] || [ $rc -eq 1 ]; then
		printf 'OK       %-50s exit=%s\n' "$name" "$rc"
		((pass++)) || true
	else
		printf 'WEIRD    %-50s exit=%s\n' "$name" "$rc"
		((fail++)) || true
	fi
}

echo "cub3D argument stress test — $(date)"
echo "Binary: $BIN"
echo ""

# --- argc only (no window) ---
run_case "no arguments"
run_case "one extra arg" maps/valid/simple.cub extra
run_case "two extra args" maps/valid/simple.cub a b
run_case "many extra args" maps/valid/simple.cub $(seq 1 20)
run_case "only garbage" notamap notamap2
run_case "empty string arg" ""
run_case "two empty strings" "" ""
run_case "flag -h" -h
run_case "flag --help" --help
run_case "flag -v" -v
run_case "numeric args" 1 2 3 4 5
run_case "special chars" '$@#!%^&*()'
run_case "spaces in arg" "maps/valid/simple.cub extra"
run_case "null byte path" $'maps/valid/simple.cub\0hack'
run_case "very long arg" "$(printf 'A%.0s' {1..5000})"
run_case "path traversal" ../../../etc/passwd
run_case "absolute missing" /tmp/does_not_exist_42.cub
run_case "relative missing" maps/nope.cub
run_case "wrong extension" README.md
run_case "wrong extension .txt" maps/valid/simple.txt
run_case "directory as arg" maps/
run_case "directory valid" maps/valid/
run_case "binary itself" ./cub3D
run_case "cub3D twice" ./cub3D ./cub3D
run_case "valid + invalid" maps/valid/simple.cub maps/invalid/not_closed.cub
run_case "invalid only" maps/invalid/not_closed.cub
run_case "invalid + garbage" maps/invalid/not_closed.cub foo bar baz
run_case "tab char" $'maps/valid/simple.cub\textra'
run_case "newline in arg" $'maps/valid/simple.cub\n'
run_case "unicode arg" maps/valid/simple.cub café
run_case "semicolon injection" 'maps/valid/simple.cub;rm -rf /'
run_case "pipe char" 'maps/valid|simple.cub'
run_case "wildcard" maps/valid/*
run_case "tilde" ~/nonexistent.cub
run_case "dot" .
run_case "dotdot" ..
run_case "single dot cub" .cub
run_case "hidden file" .gitignore
run_case "zero width join" maps/valid/simple.cub""
run_case "50 args" $(for i in $(seq 1 50); do echo "arg$i"; done)

# --- single valid arg (may open window — timeout 3s) ---
run_case "valid simple.cub" maps/valid/simple.cub
run_case "valid box.cub" maps/valid/box.cub
run_case "valid with ./" ./maps/valid/simple.cub

echo ""
echo "============================================"
printf 'PASS (exit 0 or 1): %s\n' "$pass"
printf 'FAIL (timeout/weird): %s\n' "$fail"
printf 'CRASH (signal):     %s\n' "$crash"
echo "============================================"
[ "$crash" -eq 0 ] && exit 0 || exit 1
