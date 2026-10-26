# Flowing counter core, full test

## What it checks

Checks reconstruction accuracy of the flowing counter resolver for the numbers 1..2^24. Compares addition, subtraction, multiplication with lazy shadow and exact division against a wide integer reference on one hundred thousand random pairs.

## How it works

The --test entry applies the resolver to the numbers from 1 to 2^24 and opens each record again. It then compares addition, subtraction, multiplication and exact division results against a wide integer reference on 100000 pairs. Reverse subtraction and rejection of non-exact division are also tried. A nonzero total error count is the failure condition.

## Why it matters

This concerns the Hunter resolver's conversion between a positional number and a prime exponent record.

## How to run

```sh
cd TESTLER/HUNTER/01_RESOLVER/hunter_cekirdek
gcc -std=c11 -O2 hunter_cekirdek.c -o ./test_programi -lm && ./test_programi --test
```

Requirements: gcc, libm.

## Source

Source: [hunter_cekirdek.c](hunter_cekirdek.c)

Archived line count: 800.
