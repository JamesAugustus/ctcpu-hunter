# Shift-and-add reference

## What it checks

Produces unsigned 8,16,24-bit products through bit selection, addition and shifting. Compares the result with direct wide integer multiplication and invalid input behaviour with the expected rejection.

## How it works

The 8-bit products of 65536 pairs in the range 0..255 and 16- and 24-bit boundary examples are produced. For the selected bit, the multiplicand is shifted and added to the accumulator. The result must equal the uint64_t(a)×b reference. Unsupported widths, out-of-range operands and a null output address must be rejected, and the old output value preserved.

## Why it matters

Connects multiplication and division using prime exponents and rough components to reference arithmetic.

## How to run

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/multiply_add
gcc -std=c11 -O2 multiply_add.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [multiply_add.c](multiply_add.c)

Archived line count: 124.
