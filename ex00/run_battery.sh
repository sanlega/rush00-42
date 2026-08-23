#!/bin/bash
set -e
PASS=0; FAIL=0
run_ok() {
  name="$1"; shift
  echo -n "$name ... "
  out=$(./rush01 "$@" 2>&1) || true
  if echo "$out" | grep -q Error; then echo FAIL; FAIL=$((FAIL+1)); else echo OK; PASS=$((PASS+1)); fi
}
run_err() {
  name="$1"; shift
  echo -n "$name ... "
  out=$(./rush01 "$@" 2>&1) || true
  if echo "$out" | grep -q Error; then echo OK; PASS=$((PASS+1)); else echo FAIL; FAIL=$((FAIL+1)); fi
}
echo "=== INVALIDOS ==="
run_err "17 unos" "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"
run_err "16 unos" "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"
run_err "opuestos n" "4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4"
run_err "rango" "5 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
echo "=== FACILES ==="
run_ok "4x4 facil" "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
run_ok "5x5 facil" "5 4 3 2 1 1 2 2 2 2 5 4 3 2 1 1 2 2 2 2"
run_ok "6x6 facil" "6 5 4 3 2 1 1 2 2 2 2 2 6 5 4 3 2 1 1 2 2 2 2 2"
run_ok "7x7 facil" "7 6 5 4 3 2 1 1 2 2 2 2 2 2 7 6 5 4 3 2 1 1 2 2 2 2 2 2"
run_ok "8x8 facil" "8 7 6 5 4 3 2 1 1 2 2 2 2 2 2 2 8 7 6 5 4 3 2 1 1 2 2 2 2 2 2 2"
run_ok "9x9 facil" "9 8 7 6 5 4 3 2 1 1 2 2 2 2 2 2 2 2 9 8 7 6 5 4 3 2 1 1 2 2 2 2 2 2 2 2"
echo "=== SUBJECT ==="
run_ok "subject 4x4" "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
echo "PASS=$PASS FAIL=$FAIL"
test "$FAIL" -eq 0
