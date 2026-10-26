# POW exhaustive scan

## What it checks

Canonicalises the 134217728 states combining a 24-bit number and eight POW values. Checks value preservation through exact cross multiplication, idempotence and the representation rule.

## How it works

For S=0..2^24-1 and P=0..7, 134217728 states are canonicalised. Value preservation is checked through the cross product S×8^p=s×8^P. A second canonicalisation must give the same s and p values. At zero, p=0, and away from zero, s must not be divisible by 8 until p is exhausted. Each violation of the three conditions is counted separately.

## Why it matters

Connects multiplication and division using prime exponents and rough components to reference arithmetic.

## How to run

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/pow_tam_tarama
gcc -std=c11 -O2 pow_tam_tarama.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [pow_tam_tarama.c](pow_tam_tarama.c)

Archived line count: 57.
