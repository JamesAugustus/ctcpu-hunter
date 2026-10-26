# Type product and inverse tables

## What it checks

Compares the 64 product cells of eight types with independent algebra in the form of sign, imaginary unit, exact fraction and radicand. Also checks the inverse and sign change tables.

## How it works

The 64 product pairs of eight types are tried with Svals inputs. Examples above 10 in the factorial type are skipped to prevent overflow. The value from the machine's type table is converted to independent exact fraction and root algebra and compared. Inversion and sign change are checked against the same reference. If exeq equality does not hold, it counts as an error.

## Why it matters

Examines preservation of the arithmetic meaning of Hunter type and scale codes.

## How to run

```sh
cd TESTLER/HUNTER/06_TIPLER/tur_x_tur_test
gcc -std=c11 -O2 tur_x_tur_test.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [tur_x_tur_test.c](tur_x_tur_test.c)

Archived line count: 154.
