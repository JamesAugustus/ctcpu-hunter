# Ladder and conventional multiplication cost

## What it checks

Compares the actual ladder encode, open and multiply chain with conventional positional multiplication. Measures addition, small multiplication and shift counts on the same inputs.

## How it works

First, the smooth and rough distribution in the 24-bit domain is counted. Then 200000 pairs pass through encode, open and multiply steps. Addition, small multiplication and shift counts are compared between the path combining exponents and rough components and conventional positional multiplication. Exact division examples require divisibility of the exponents and rough component. The program reports cost tables.

## Why it matters

This concerns the numerical contract of Hunter CPU and arithmetic models.

## How to run

```sh
cd TESTLER/HUNTER/09_CPU_ARITMETIGI/hunter_golge_vs_klasik_ad96e0c4
gcc -std=gnu11 -O2 golge_vs_klasik.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [golge_vs_klasik.c](golge_vs_klasik.c)

Archived line count: 240.
