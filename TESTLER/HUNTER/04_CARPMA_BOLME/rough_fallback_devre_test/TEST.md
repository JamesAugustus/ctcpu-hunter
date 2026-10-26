# Multiplication path for a large remainder

## What it checks

Calculates a rough product using octal binomial expansion, shifting and small multiplications with values at most seven. Compares the result with direct __int128 multiplication and prints arithmetic operation counts.

## How it works

The octal expansions of rough components are taken for five million operand pairs. The got value formed with small digit products and shifts is compared with direct __int128 multiplication. Four fixed examples are also printed. got!=real is an error. Addition and shift counts are separate cost measurements.

## Why it matters

Connects multiplication and division using prime exponents and rough components to reference arithmetic.

## How to run

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/rough_fallback_devre_test
gcc -std=c11 -O2 rough_fallback_devre_test.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [rough_fallback_devre_test.c](rough_fallback_devre_test.c)

Archived line count: 99.
