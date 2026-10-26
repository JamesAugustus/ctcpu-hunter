# Fraction and parity inside a root

## What it checks

Compares canonical conversions of POW interpretations outside and inside the root. Tests value preservation by S/8 and P reduction inside the root, and opening an odd POW, with exact manual examples.

## How it works

Combinations of S from 0..2^24-1 and P from 0..7 are scanned. Values before and after conversion are checked with the cross product S×8^p=s×8^P. Doubling the scale of exponents inside the root is compared in ten million random examples. A nonzero value or canonical form counter is a failure.

## Why it matters

Examines error bounds of exact and approximate calculations in the Hunter root unit.

## How to run

```sh
cd TESTLER/HUNTER/05_KAREKOK/kok_virgul_icinde_test
gcc -std=c11 -O2 kok_virgul_icinde_test.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [kok_virgul_icinde_test.c](kok_virgul_icinde_test.c)

Archived line count: 107.
