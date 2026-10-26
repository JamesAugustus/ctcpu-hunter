# Square root core

## What it checks

Checks the octal digit square root on perfect squares and the floor inequality. Also compares equality with the binary digit method, approximate root errors and 64-bit boundary examples.

## How it works

For n=0..3000, the root of input n² is compared with n. In the range N=0..200000, the octal and binary root paths must agree. The condition r²<=N<(r+1)² is checked up to one million, and three 64-bit boundary inputs are checked separately. A perfect square, method or floor condition mismatch counts as an error.

## Why it matters

Examines error bounds of exact and approximate calculations in the Hunter root unit.

## How to run

```sh
cd TESTLER/HUNTER/05_KAREKOK/karekok_emulator
gcc -std=c11 -O2 karekok_emulator.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [karekok_emulator.c](karekok_emulator.c)

Archived line count: 170.
