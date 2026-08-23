#!/usr/bin/env python3
"""Build tests_battery.txt and run_battery.sh from verified puzzles."""
import os

os.chdir(os.path.dirname(os.path.abspath(__file__)))

# (name, clues, expected output lines) — all verified with rush01 on test2
CASES = [
    # INVALID
    ("inv_17", "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1", None),
    ("inv_16", "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1", None),
    ("inv_n", "4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4", None),
    ("inv_rng", "5 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2", None),
    # 4x4
    ("4x4_facil", "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2",
     "1 2 3 4\n2 3 4 1\n3 4 1 2\n4 1 2 3"),
    ("4x4_media1", "1 2 2 3 2 2 3 1 1 2 2 2 4 2 3 1",
     "4 3 2 1\n2 1 4 3\n1 4 3 2\n3 2 1 4"),
    ("4x4_media2", "1 2 3 2 3 2 1 2 1 2 2 2 4 1 3 2",
     "4 3 2 1\n3 2 1 4\n1 4 3 2\n2 1 4 3"),
    ("4x4_dificil1", "2 1 3 2 1 3 2 2 2 3 3 1 3 1 2 2",
     "3 4 2 1\n2 1 3 4\n1 3 4 2\n4 2 1 3"),
    ("4x4_dificil2", "1 2 2 3 2 2 3 1 1 3 2 2 3 2 3 1",
     "4 3 1 2\n1 2 4 3\n2 4 3 1\n3 1 2 4"),
    # 5x5
    ("5x5_facil", "5 4 3 2 1 1 2 2 2 2 5 4 3 2 1 1 2 2 2 2",
     "1 2 3 4 5\n2 3 4 5 1\n3 4 5 1 2\n4 5 1 2 3\n5 1 2 3 4"),
    ("5x5_media1", "1 3 2 2 4 3 1 3 2 2 1 3 4 2 2 4 2 2 1 3",
     "5 1 4 3 2\n2 4 5 1 3\n1 2 3 5 4\n4 3 1 2 5\n3 5 2 4 1"),
    ("5x5_media2", "2 2 2 3 1 3 2 3 1 3 2 2 1 2 3 1 3 3 2 2",
     "4 3 2 1 5\n3 2 5 4 1\n5 1 4 2 3\n2 5 1 3 4\n1 4 3 5 2"),
    ("5x5_dificil1", "2 3 2 2 1 3 1 2 2 4 4 1 3 2 2 1 4 2 2 3",
     "1 2 4 3 5\n5 4 3 1 2\n2 3 1 5 4\n4 1 5 2 3\n3 5 2 4 1"),
    ("5x5_dificil2", "2 1 2 3 4 4 3 2 2 1 2 1 2 3 4 4 3 2 2 1",
     "4 5 3 2 1\n5 3 1 4 2\n3 1 2 5 4\n2 4 5 1 3\n1 2 4 3 5"),
    # 6x6
    ("6x6_facil", "6 5 4 3 2 1 1 2 2 2 2 2 6 5 4 3 2 1 1 2 2 2 2 2",
     "1 2 3 4 5 6\n2 3 4 5 6 1\n3 4 5 6 1 2\n4 5 6 1 2 3\n5 6 1 2 3 4\n6 1 2 3 4 5"),
    ("6x6_media1", "3 3 1 3 2 2 3 2 2 1 4 2 3 3 1 5 2 3 2 2 3 1 3 2",
     "1 2 6 4 3 5\n3 5 1 2 6 4\n6 4 2 3 5 1\n2 3 4 5 1 6\n5 6 3 1 4 2\n4 1 5 6 2 3"),
    ("6x6_media2", "2 2 1 3 3 2 3 3 5 2 1 2 3 2 1 2 3 3 2 3 3 3 1 2",
     "2 3 6 1 4 5\n1 6 4 3 5 2\n6 1 5 2 3 4\n5 4 3 6 2 1\n3 5 2 4 1 6\n4 2 1 5 6 3"),
    ("6x6_dificil1", "3 3 3 1 2 2 3 2 1 2 4 3 4 3 4 1 2 2 2 2 1 3 2 3",
     "1 2 3 6 4 5\n3 5 1 4 6 2\n2 4 5 3 1 6\n6 3 4 2 5 1\n5 6 2 1 3 4\n4 1 6 5 2 3"),
    ("6x6_dificil2", "3 1 2 4 2 2 3 4 2 1 3 4 2 3 3 1 2 3 2 2 1 3 3 3",
     "2 6 4 1 3 5\n1 5 2 4 6 3\n3 2 1 5 4 6\n6 1 3 2 5 4\n5 4 6 3 1 2\n4 3 5 6 2 1"),
    # 7x7
    ("7x7_facil", "7 6 5 4 3 2 1 1 2 2 2 2 2 2 7 6 5 4 3 2 1 1 2 2 2 2 2 2",
     "1 2 3 4 5 6 7\n2 3 4 5 6 7 1\n3 4 5 6 7 1 2\n4 5 6 7 1 2 3\n5 6 7 1 2 3 4\n6 7 1 2 3 4 5\n7 1 2 3 4 5 6"),
    ("7x7_media1", "3 2 2 3 1 3 3 1 2 2 3 4 4 2 3 2 3 5 2 3 1 2 3 2 2 1 5 5",
     "5 1 6 2 7 3 4\n1 7 4 5 2 6 3\n3 4 2 7 1 5 6\n2 3 1 4 6 7 5\n6 2 3 1 5 4 7\n4 5 7 6 3 2 1\n7 6 5 3 4 1 2"),
    ("7x7_media2", "1 3 2 3 2 4 2 4 3 1 2 3 3 2 1 4 2 3 2 2 3 5 1 3 3 2 4 2",
     "7 1 6 2 5 4 3\n1 3 2 6 4 5 7\n2 7 1 5 3 6 4\n4 6 5 1 7 3 2\n6 2 4 3 1 7 5\n5 4 3 7 6 2 1\n3 5 7 4 2 1 6"),
    ("7x7_dificil1", "1 2 3 2 3 2 4 4 1 4 3 2 5 2 1 4 5 2 2 3 2 4 2 2 3 3 1 2",
     "7 6 1 2 4 5 3\n1 5 6 7 2 3 4\n2 3 4 1 6 7 5\n3 1 7 4 5 6 2\n6 2 5 3 7 4 1\n5 4 3 6 1 2 7\n4 7 2 5 3 1 6"),
    ("7x7_dificil2", "2 3 3 3 3 1 2 1 3 2 3 2 3 4 2 4 2 3 2 3 1 2 1 3 2 2 3 4",
     "6 1 2 3 4 7 5\n1 2 6 4 3 5 7\n2 7 4 1 5 6 3\n3 6 5 7 1 2 4\n4 3 7 5 2 1 6\n5 4 1 6 7 3 2\n7 5 3 2 6 4 1"),
    # 8x8
    ("8x8_facil", "8 7 6 5 4 3 2 1 1 2 2 2 2 2 2 2 8 7 6 5 4 3 2 1 1 2 2 2 2 2 2 2",
     "1 2 3 4 5 6 7 8\n2 3 4 5 6 7 8 1\n3 4 5 6 7 8 1 2\n4 5 6 7 8 1 2 3\n5 6 7 8 1 2 3 4\n6 7 8 1 2 3 4 5\n7 8 1 2 3 4 5 6\n8 1 2 3 4 5 6 7"),
    ("8x8_media1", "2 2 4 3 1 3 6 2 3 4 2 4 3 2 1 4 3 1 3 4 2 2 5 3 3 4 1 2 4 4 3 2",
     "1 7 2 4 8 6 3 5\n8 1 3 6 5 7 4 2\n6 4 1 2 7 3 5 8\n4 5 6 8 3 2 1 7\n3 8 5 7 2 1 6 4\n7 6 8 3 4 5 2 1\n2 3 4 5 1 8 7 6\n5 2 7 1 6 4 8 3"),
    # 9x9
    ("9x9_facil", "9 8 7 6 5 4 3 2 1 1 2 2 2 2 2 2 2 2 9 8 7 6 5 4 3 2 1 1 2 2 2 2 2 2 2 2",
     "1 2 3 4 5 6 7 8 9\n2 3 4 5 6 7 8 9 1\n3 4 5 6 7 8 9 1 2\n4 5 6 7 8 9 1 2 3\n5 6 7 8 9 1 2 3 4\n6 7 8 9 1 2 3 4 5\n7 8 9 1 2 3 4 5 6\n8 9 1 2 3 4 5 6 7\n9 1 2 3 4 5 6 7 8"),
]

lines = [
    "RUSH01 - Bateria de tests",
    "FACIL | MEDIA | DIFICIL (4x4 a 9x9, verificados con rush01)",
    "Formato pistas: top bottom left right",
    "",
    "=" * 80,
    "INVALIDOS",
    "=" * 80,
]

script = [
    "#!/bin/bash",
    "set -e",
    "PASS=0; FAIL=0",
    'run_ok() { n="$1"; shift; echo -n "$n ... "; o=$(./rush01 "$@" 2>&1)||true; if echo "$o"|grep -q Error; then echo FAIL; FAIL=$((FAIL+1)); else echo OK; PASS=$((PASS+1)); fi; }',
    'run_err() { n="$1"; shift; echo -n "$n ... "; o=$(./rush01 "$@" 2>&1)||true; if echo "$o"|grep -q Error; then echo OK; PASS=$((PASS+1)); else echo FAIL; FAIL=$((FAIL+1)); fi; }',
    'echo "=== INVALIDOS ==="',
]

cur = None
for name, clues, out in CASES:
    if name.startswith("inv_"):
        lines += ["", f"# {name}", f'./rush01 "{clues}"', "Esperado: Error"]
        script.append(f'run_err "{name}" "{clues}"')
        continue
    size = name.split("_")[0]
    if size != cur:
        cur = size
        lines += ["", "=" * 80, size.upper(), "=" * 80]
        script.append(f'echo "=== {size.upper()} ==="')
    kind = name.split("_", 1)[1].replace("_", " ").upper()
    lines += ["", f"--- {kind} ---", f'./rush01 "{clues}"', "Salida esperada:", out]
    script.append(f'run_ok "{name}" "{clues}"')

lines += [
    "",
    "=" * 80,
    "NOTA 8x8 / 9x9",
    "=" * 80,
    "8x8: facil + 1 media verificada. Mas medias/dificiles en busqueda.",
    "9x9: solo facil verificado en tiempo razonable con este solver.",
    "Para backtracking duro usar 4x4-7x7 DIFICIL.",
]

script += ['echo "PASS=$PASS FAIL=$FAIL"', 'test "$FAIL" -eq 0']

open("tests_battery.txt", "w", encoding="utf-8").write("\n".join(lines) + "\n")
open("run_battery.sh", "w", encoding="utf-8", newline="\n").write("\n".join(script) + "\n")
print(f"Casos OK: {sum(1 for c in CASES if not c[0].startswith('inv_'))} validos + 4 invalidos")
