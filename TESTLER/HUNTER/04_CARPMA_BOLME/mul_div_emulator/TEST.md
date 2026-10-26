# Multiplication and division with exponents

## What it checks

Performs multiplication by adding prime exponents and division by subtracting them. Compares exactly divisible, fractional, rough and capacity limit examples with direct arithmetic.

## How it works

Twenty million signed operand pairs are separated into prime exponent and rough parts. The product obtained by adding exponents is compared with __int128(a)×b. Exact division, fractional division and the rough path are also tried. For exponents 0..40, the sum of four cells must preserve the initial exponent, and overflow must be reported above 28. Comparison differences are recorded in the error counter.

## Why it matters

Connects multiplication and division using prime exponents and rough components to reference arithmetic.

## How to run

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/mul_div_emulator
gcc -std=c11 -O2 mul_div_emulator.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [mul_div_emulator.c](mul_div_emulator.c)

Archived line count: 156.
