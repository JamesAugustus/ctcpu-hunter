# Quarantine pair

## What it checks

Runs the locked register pair that accumulates the numerator trace after division by zero. Checks that a plain number cannot be opened from a locked cell, that a zero numerator is distinguished and that a new LOAD clears the lock.

## How it works

After division by zero, factors are added to the locked numerator trace. The trace must be 6×1365613=8193678 and the cell must not be opened as a plain number. Numerator traces for 0/0 and 6/0 are kept separate. A new LOAD must clear the lock. Breaking any of these fixed expectations increases the error counter.

## Why it matters

Examines preservation of the arithmetic meaning of Hunter type and scale codes.

## How to run

```sh
cd TESTLER/HUNTER/06_TIPLER/karantina_cift_demo
gcc -std=c11 -O2 karantina_cift_demo.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [karantina_cift_demo.c](karantina_cift_demo.c)

Archived line count: 67.
