# Flowing counter, execution trace of 744

## What it checks

Shows how the number 744 passes through the resolver and separates into prime exponents and octal counter states. Checks that the reconstructed rm value matches 1350_8, that is, 744, exactly.

## How it works

The --iz 744 entry prints prime exponents and counter changes at each resolver transition. The rm value in the output is read back and checked for the equality 1350_8=744. The test fails if the reconstructed value differs or exact verification is not obtained.

## Why it matters

This concerns the Hunter resolver's conversion between a positional number and a prime exponent record.

## How to run

```sh
cd TESTLER/HUNTER/01_RESOLVER/hunter_iz
gcc -std=c11 -O2 hunter_cekirdek.c -o ./test_programi -lm && ./test_programi --iz 744
```

Requirements: gcc, libm.

## Source

Source: [hunter_cekirdek.c](hunter_cekirdek.c)

Archived line count: 800.
