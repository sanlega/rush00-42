#!/usr/bin/env python3
"""Generate a verified rush01 test battery (4x4..9x9, easy/medium/hard/invalid)."""
import random
import subprocess
import os
import sys

os.chdir(os.path.dirname(os.path.abspath(__file__)))


def vis(line):
    m, c = 0, 0
    for v in line:
        if v > m:
            m, c = v, c + 1
    return c


def clues_from(g):
    n = len(g)
    top = [vis([g[r][c] for r in range(n)]) for c in range(n)]
    bot = [vis([g[r][c] for r in range(n - 1, -1, -1)]) for c in range(n)]
    left = [vis(g[r]) for r in range(n)]
    right = [vis(g[r][::-1]) for r in range(n)]
    return top + bot + left + right


def latin(n, seed):
    rng = random.Random(seed)
    base = [[((i + j) % n) + 1 for j in range(n)] for i in range(n)]
    rp = list(range(n))
    cp = list(range(n))
    sy = list(range(1, n + 1))
    rng.shuffle(rp)
    rng.shuffle(cp)
    rng.shuffle(sy)
    return [[sy[base[rp[r]][cp[c]] - 1] for c in range(n)] for r in range(n)]


def easy_grid(n):
    return [[((i + j) % n) + 1 for j in range(n)] for i in range(n)]


def fmt(c):
    return " ".join(map(str, c))


def grid_str(g):
    return "\n".join(" ".join(map(str, row)) for row in g)


def extreme_count(c, n):
    return sum(1 for x in c if x in (1, n))


def run_solver(p, timeout=5):
    try:
        r = subprocess.run(
            ["./rush01", p], capture_output=True, text=True, timeout=timeout
        )
        out = r.stdout.strip()
        err = "Error" in out or r.returncode != 0
        return (not err and bool(out)), out
    except subprocess.TimeoutExpired:
        return False, "TIMEOUT"


def pick_medium(n, need=2):
    found = []
    for s in range(5000):
        g = latin(n, 1000 * n + s)
        c = clues_from(g)
        ex = extreme_count(c, n)
        if 4 <= ex <= max(6, n + 2):
            found.append((ex, s, g, c))
            if len(found) >= need:
                break
    return found


def pick_hard(n, need=2):
    found = []
    for s in range(8000):
        g = latin(n, 2000 * n + s)
        c = clues_from(g)
        ex = extreme_count(c, n)
        if ex <= 4:
            found.append((ex, s, g, c))
            if len(found) >= need:
                break
    return found


lines = []
lines.append("RUSH01 - Bateria de tests")
lines.append("Dificultad: FACIL (muchas pistas 1/n) | MEDIA | DIFICIL (pocas 1/n)")
lines.append("Formato pistas: top bottom left right")
lines.append("Uso: ./rush01 \"pistas...\"")
lines.append("")

# --- INVALID ---
lines.append("=" * 80)
lines.append("INVALIDOS (deben imprimir Error)")
lines.append("=" * 80)
invalids = [
    ("argc != 2", None),
    ("17 unos (count % 4 != 0)", "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"),
    ("16 unos (opuestos 1+1)", "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"),
    ("4x4 opuestos > n+1", "4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4"),
    ("valor fuera de rango", "5 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"),
    ("caracter invalido", "4 a 2 1 1 2 2 2 4 3 2 1 1 2 2 2"),
]
for name, p in invalids:
    lines.append("")
    lines.append(f"# {name}")
    if p is None:
        lines.append("./rush01")
        lines.append("./rush01 a b")
    else:
        lines.append(f'./rush01 "{p}"')
    lines.append("Esperado: Error")

verified = []
skipped_hard = []

for n in range(4, 10):
    lines.append("")
    lines.append("=" * 80)
    lines.append(f"{n}x{n}")
    lines.append("=" * 80)

    # EASY
    g = easy_grid(n)
    c = clues_from(g)
    p = fmt(c)
    ok, out = run_solver(p, timeout=3)
    lines.append("")
    lines.append(f"--- FACIL (extremas={extreme_count(c, n)}/{4*n}) ---")
    lines.append(f'./rush01 "{p}"')
    if ok:
        lines.append("Salida esperada:")
        lines.append(out)
        verified.append((n, "FACIL", True))
    else:
        lines.append(f"(solver: {out})")
        lines.append("Solucion generadora:")
        lines.append(grid_str(g))
        verified.append((n, "FACIL", False))

    # MEDIUM
    meds = pick_medium(n, 2)
    for idx, (ex, seed, g, c) in enumerate(meds, 1):
        p = fmt(c)
        timeout = 5 if n <= 6 else 15
        ok, out = run_solver(p, timeout=timeout)
        lines.append("")
        lines.append(f"--- MEDIA #{idx} (seed={seed}, extremas={ex}/{4*n}) ---")
        lines.append(f'./rush01 "{p}"')
        if ok:
            lines.append("Salida esperada:")
            lines.append(out)
            verified.append((n, f"MEDIA{idx}", True))
        else:
            lines.append(f"(solver no resolvio en {timeout}s: {out})")
            lines.append("Solucion valida conocida (latin square):")
            lines.append(grid_str(g))
            verified.append((n, f"MEDIA{idx}", False))
            skipped_hard.append((n, "MEDIA", p, g))

    # HARD
    hards = pick_hard(n, 1 if n >= 8 else 2)
    for idx, (ex, seed, g, c) in enumerate(hards, 1):
        p = fmt(c)
        timeout = 8 if n <= 5 else (20 if n <= 7 else 3)
        ok, out = run_solver(p, timeout=timeout)
        lines.append("")
        lines.append(f"--- DIFICIL #{idx} (seed={seed}, extremas={ex}/{4*n}) ---")
        lines.append(f'./rush01 "{p}"')
        lines.append("# Puede tardar mucho; pistas validas generadas desde latin square")
        if ok:
            lines.append("Salida esperada:")
            lines.append(out)
            verified.append((n, f"DIFICIL{idx}", True))
        else:
            lines.append(f"(solver no resolvio en {timeout}s: {out})")
            lines.append("Solucion valida conocida (latin square):")
            lines.append(grid_str(g))
            verified.append((n, f"DIFICIL{idx}", False))
            skipped_hard.append((n, "DIFICIL", p, g))

# Classic subject
lines.append("")
lines.append("=" * 80)
lines.append("SUBJECT 4x4 (referencia)")
lines.append("=" * 80)
lines.append('./rush01 "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"')
lines.append("Salida esperada:")
lines.append("1 2 3 4\n2 3 4 1\n3 4 1 2\n4 1 2 3")

out_path = "tests_battery.txt"
with open(out_path, "w", encoding="utf-8") as f:
    f.write("\n".join(lines) + "\n")

# Also write a runnable shell script for easy/medium verified cases
sh = []
sh.append("#!/bin/bash")
sh.append("set -e")
sh.append("PASS=0; FAIL=0")
sh.append('run_ok() {')
sh.append('  name="$1"; shift')
sh.append('  echo -n "$name ... "')
sh.append('  out=$(./rush01 "$@" 2>&1) || true')
sh.append('  if echo "$out" | grep -q Error; then echo FAIL; FAIL=$((FAIL+1)); else echo OK; PASS=$((PASS+1)); fi')
sh.append('}')
sh.append('run_err() {')
sh.append('  name="$1"; shift')
sh.append('  echo -n "$name ... "')
sh.append('  out=$(./rush01 "$@" 2>&1) || true')
sh.append('  if echo "$out" | grep -q Error; then echo OK; PASS=$((PASS+1)); else echo FAIL; FAIL=$((FAIL+1)); fi')
sh.append('}')
sh.append('echo "=== INVALIDOS ==="')
sh.append('run_err "17 unos" "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"')
sh.append('run_err "16 unos" "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"')
sh.append('run_err "opuestos n" "4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4"')
sh.append('run_err "rango" "5 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"')
sh.append('echo "=== FACILES ==="')

# Re-add easy puzzles to script
for n in range(4, 10):
    g = easy_grid(n)
    p = fmt(clues_from(g))
    sh.append(f'run_ok "{n}x{n} facil" "{p}"')

sh.append('echo "=== SUBJECT ==="')
sh.append('run_ok "subject 4x4" "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"')
sh.append('echo "PASS=$PASS FAIL=$FAIL"')
sh.append('test "$FAIL" -eq 0')

with open("run_battery.sh", "w", encoding="utf-8", newline="\n") as f:
    f.write("\n".join(sh) + "\n")

print(f"Wrote {out_path}")
print(f"Verified summary: {sum(1 for _,_,ok in verified if ok)}/{len(verified)} solved by rush01")
for item in verified:
    print(f"  {item}")
