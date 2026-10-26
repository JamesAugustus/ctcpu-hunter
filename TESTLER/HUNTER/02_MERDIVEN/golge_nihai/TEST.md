# Octal descent, N6 ladder

## What it checks

Stores a 24-bit number in a limited number of rows in the N6 ladder representation and converts it back to an integer. Scans coverage by four rows and cases where different numbers collide in the same record summary.

## How it works

The numbers 1..2^24-1 are converted to four-row N6 records. The value read back with val is compared with N. Each record summary is placed in a hash table to count different inputs giving the same summary. A round-trip error or record collision violates the corresponding correctness condition. Numbers that do not fit are reported separately.

## Why it matters

Examines value preservation and record capacity of ladder rows in the shadow representation.

## How to run

```sh
cd TESTLER/HUNTER/02_MERDIVEN/golge_nihai
gcc -std=c11 -O2 golge_nihai.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [CEM_MODELI/golge_nihai.c](golge_nihai.c)

Archived line count: 84.
