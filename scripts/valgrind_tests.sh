#!/usr/bin/env bash
set -u

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT" || exit 1

BIN="./cub3D"
VG="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42 --log-file=/tmp/cub3d_vg_$$.log"

if [ ! -x "$BIN" ]; then
	echo "ERROR: $BIN not found. Run make first."
	exit 1
fi

run_test() {
	local name="$1"
	shift
	local log="/tmp/cub3d_vg_${name// /_}.log"
	local prog_exit=0
	local vg_exit=0

	$VG --log-file="$log" "$BIN" "$@" >/dev/null 2>&1 || prog_exit=$?
	vg_exit=$?

	printf '\n============================================================\n'
	printf 'TEST: %s\n' "$name"
	printf 'CMD : %s %s\n' "$BIN" "$*"
	printf 'EXIT: program=%s valgrind=%s\n' "$prog_exit" "$vg_exit"

	grep -E 'ERROR SUMMARY|definitely lost|indirectly lost|possibly lost|Invalid read|Invalid write|Use of uninitialised|Conditional jump' "$log" \
		| sed 's/^/  /' || true

	if grep -q 'definitely lost: 0 bytes in 0 blocks' "$log" \
		&& grep -q 'indirectly lost: 0 bytes in 0 blocks' "$log" \
		&& grep -q 'ERROR SUMMARY: 0 errors' "$log"; then
		printf 'RESULT: PASS (clean exit)\n'
	else
		printf 'RESULT: ISSUES FOUND\n'
	fi
}

echo "cub3D valgrind suite — $(date)"
echo "Project: $ROOT"

run_test "no arguments"
run_test "too many arguments" maps/valid/simple.cub extra
run_test "bad extension" README.md
run_test "missing file" maps/does_not_exist.cub
run_test "invalid map not closed" maps/invalid/not_closed.cub
run_test "valid map simple" maps/valid/simple.cub
run_test "valid map box" maps/valid/box.cub
run_test "valid map rooms" maps/valid/rooms.cub
run_test "valid map irregular" maps/valid/irregular.cub

printf '\nDone.\n'
