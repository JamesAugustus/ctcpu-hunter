# Shadow core acceptance examples

## What it checks

Checks zero, multiplication, division, factorial and root behaviour in 23 acceptance examples for the ladder shadow core. Checks that after an operation, the result is stored in the ladder again and read with the same value.

## How it works

The examples 0,1,17,360,738,41,720720,1000003 are stored and read back. Then 12×10=120, 41×43=1763, exact and symbolic roots, factorial and modulo examples are passed to the CHK routine. The final product is written into the ladder again and opened. If any expected value or flag differs, the FAIL counter increases.

## Why it matters

Examines value preservation and record capacity of ladder rows in the shadow representation.

## How to run

```sh
cd TESTLER/HUNTER/02_MERDIVEN/golge_emulator
gcc -std=c11 -O2 golge_emulator.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [golge_emulator.c](golge_emulator.c)

Archived line count: 359.
