# All 24-bit numbers

## What it checks

Converts all 24-bit numbers to N6 ladder storage and reads them back. Checks numerical equality, fitting into four rows and fixed acceptance examples.

## How it works

An N6 encode record is produced for 1..16777215. The four rows and rough tail are opened again and compared with the initial N. The number of rows used, the largest exponents and examples that do not fit are accumulated. The first value mismatch is recorded and the error counter is increased.

## Why it matters

Examines value preservation and record capacity of ladder rows in the shadow representation.

## How to run

```sh
cd TESTLER/HUNTER/02_MERDIVEN/test_tum_sayilar
gcc -std=c11 -O2 test_tum_sayilar.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [test_tum_sayilar.c](test_tum_sayilar.c)

Archived line count: 122.
