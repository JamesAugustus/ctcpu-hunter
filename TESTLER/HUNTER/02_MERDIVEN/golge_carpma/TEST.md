# Multiplication in the ladder representation

## What it checks

Opens two numbers stored in the ladder into prime exponents and rough components, multiplies them and stores them again. Checks preservation of the numerical value for small pairs, large rough pairs and capacity overflow.

## How it works

The 8,386,560 operand pairs satisfying 1≤a≤b<4096 and five million rough pairs are opened from the ladder record. Exponents are added, rough components are multiplied through the binomial path and the result is stored again. The opened result must equal uint64_t(a)×b. In examples exceeding capacity, the wide result must also be preserved and the small multiplication operand used must not exceed seven.

## Why it matters

Examines value preservation and record capacity of ladder rows in the shadow representation.

## How to run

```sh
cd TESTLER/HUNTER/02_MERDIVEN/golge_carpma
gcc -std=c11 -O2 golge_carpma.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [CEM_MODELI/golge_carpma.c](golge_carpma.c)

Archived line count: 223.
