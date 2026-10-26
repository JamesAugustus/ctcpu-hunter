# Fraction layer v1.4

## What it checks

Compares octal scale, fraction reduction and root operations in a numerator/denominator pair with expected values. Checks division-by-zero quarantine, the special approximation flag and mantissa overflow.

## How it works

Fixed rational and root examples pass through four opening modes. For 3/7, exact mode must preserve the numerator and denominator, while approximate mode must produce a nearby value at scale 8^-7 with the OZEL flag. Random product and division examples are checked against independent numerator and denominator products. A difference in the division-by-zero lock, trace or cross product counts as an error.

## Why it matters

Connects multiplication and division using prime exponents and rough components to reference arithmetic.

## How to run

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/kesir_emulator
gcc -std=c11 -O2 kesir_emulator.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [kesir_emulator.c](kesir_emulator.c)

Archived line count: 322.
