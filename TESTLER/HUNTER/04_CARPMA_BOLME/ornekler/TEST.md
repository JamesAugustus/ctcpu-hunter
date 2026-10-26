# 41 multiplication and division examples

## What it checks

Compares multiplication, exact division and rational division examples in the prime exponent vector with a wide integer reference. Also shows rough multiplication, sign and chain examples that reduce a large intermediate product.

## How it works

Fixed smooth and rough examples are factored into prime exponents. Exponents are added for multiplication and subtracted for division, and the result is opened into a number again. The reference is an __int128 product for integers and a cross product for fractions. The test fails if the HATA counter is nonzero.

## Why it matters

Connects multiplication and division using prime exponents and rough components to reference arithmetic.

## How to run

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/ornekler
gcc -std=c11 -O2 ornekler.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [ornekler.c](ornekler.c)

Archived line count: 139.
