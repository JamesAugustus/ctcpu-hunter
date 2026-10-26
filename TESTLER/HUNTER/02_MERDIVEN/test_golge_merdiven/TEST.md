# Main emulator ladder acceptance

## What it checks

Runs shadow storage in the main shadow.c implementation using the actual project functions. Checks that the number read back equals the input in fixed examples and scans.

## How it works

Inputs 1..16777215 are stored with the actual shadow_resolve and read back with shadow_value. In the exhaustive scan of pairs 1<=a<=b<4096, the product record is compared with a×b. In a separate scan of 1,000,000 random pairs with 1<=a,b<4096, division of the product record by b must give a. Fixed overflow and rough examples are also run. An increase in the round-trip, product or division error counter is the failure condition.

## Why it matters

Examines value preservation and record capacity of ladder rows in the shadow representation.

## How to run

```sh
cd TESTLER/HUNTER/02_MERDIVEN/test_golge_merdiven/kod/SISTEM/ctcpu/05_KOD/TESTLER
gcc -std=c11 -O2 test_golge_merdiven.c ../EMULATOR/shadow.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

The kod/ directory preserves the relative hierarchy used in the source.

## Source

Source: [test_golge_merdiven.c](kod/SISTEM/ctcpu/05_KOD/TESTLER/test_golge_merdiven.c)

Archived line count: 132.
