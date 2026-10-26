# Cascade from end to end

## What it checks

Writes prime exponents into four cells of 0..7 and performs multiplication and division through the cells. Measures the exponent limit of 28 and equality of two million exact division pairs with direct division.

## How it works

Exponents 0..56 are encoded into four cells of 0..7. Up to 28, decode(encode(e))=e is required, and overflow is expected for larger exponents. In three million product and two million exact division examples, the result opened from the cells is compared with the direct arithmetic value. A cell limit, overflow flag or numerical result mismatch is an error. I return a nonzero exit code when a calculation error is detected.

## Why it matters

Connects multiplication and division using prime exponents and rough components to reference arithmetic.

## How to run

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/kaskad_uctan_uca_test
gcc -std=c11 -O2 kaskad_uctan_uca_test.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [kaskad_uctan_uca_test.c](kaskad_uctan_uca_test.c)

Archived line count: 150.
