# Numerical correctness of Final Form examples

## What it checks

Recalculates the numerical examples in Final Form with independent, exact arithmetic. This includes smooth counts, reconstruction with the Chinese remainder theorem, digit weights, colour sets and continued fraction approximations of the square root.

## How it works

Each example is calculated with integers or rational numbers and compared with the given value. If an equality does not hold, the program stops and prints which check it stopped at. If all hold, it prints the total number of checks.

## Why it matters

Shows that the examples were calculated rather than written by hand.

## How to run

```sh
cd TESTLER/NIHAI_EK/ornekleri_dogrula
python3 ornekleri_dogrula.py
```

Requirements: Python 3.

The six gates AND, OR, XOR, NAND, NOR and XNOR are checked on all 64 ordered pairs each, for 384 gate checks. The complete program performs 39,110 equality checks.
