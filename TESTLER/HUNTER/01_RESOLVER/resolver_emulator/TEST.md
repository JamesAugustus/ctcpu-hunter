# Resolver exhaustive scan

## What it checks

Compares remainder calculation by streaming octal digits with direct modulo operations for seven primes across all 24-bit numbers. Also checks the encode/decode round trip, prime exponents and the condition that no small prime remains in rough.

## How it works

For N=0..16777215 and p=2,3,5,7,11,13,17, the remainder is obtained from the octal stream. The stream remainder is compared with N%p. Then the numbers 1..16777215 are separated into prime exponents and rough components and multiplied back together. A round trip that does not return N, a wrong exponent or a small prime remaining in rough increases the error counter.

## Why it matters

This concerns the Hunter resolver's conversion between a positional number and a prime exponent record.

## How to run

```sh
cd TESTLER/HUNTER/01_RESOLVER/resolver_emulator
gcc -std=c11 -O2 resolver_emulator.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [resolver_emulator.c](resolver_emulator.c)

Archived line count: 155.
