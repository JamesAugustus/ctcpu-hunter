# Undefined value encoding

## What it checks

Counts collisions between old and new bit codes for approximate zero and an undefined value. Checks that the TYPE=1/x and NUMBER=0 layout is distinct from legitimate zero.

## How it works

I convert small values from 8^-12 inclusive to 8^-6 exclusive to approximate number codes. Collision counts for the old and new undefined marks are compared on legitimate values rounded to zero. The zero-denominator event is tracked separately across all 24-bit divisors. The new code treating a legitimate zero as undefined or encoding a nonzero divisor as zero is a violation.

## Why it matters

Examines preservation of the arithmetic meaning of Hunter type and scale codes.

## How to run

```sh
cd TESTLER/HUNTER/06_TIPLER/tanimsiz_kodlama_test
gcc -std=c11 -O2 tanimsiz_kodlama_test.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [tanimsiz_kodlama_test.c](tanimsiz_kodlama_test.c)

Archived line count: 85.
