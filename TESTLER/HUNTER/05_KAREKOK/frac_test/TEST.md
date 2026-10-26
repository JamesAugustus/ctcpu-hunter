# Fixed-point square root measurement

## What it checks

Calculates the square roots of fixed-point fractions through exact digit, binomial approximation and logarithmic number system paths. Compares error against the reference root and model step counts on the same inputs.

## How it works

Inputs with F=16 fractional bits are passed to the isqrt_octal, binom1 and lns paths. Each result is converted to a real number with the same scale and its difference from the sqrt reference is calculated. Product and reduction examples are also printed. The code sets no numerical acceptance threshold.

## Why it matters

Examines error bounds of exact and approximate calculations in the Hunter root unit.

## How to run

```sh
cd TESTLER/HUNTER/05_KAREKOK/frac_test
gcc -std=c11 -O2 frac_test.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [frac_test.c](frac_test.c)

Archived line count: 68.
