# Type and POW exhaustive scan

## What it checks

Builds the canonical representation of 2^30 states consisting of a 24-bit number, eight POW values and eight types. Checks value preservation, the second canonicalisation having no effect and the structural rules of the type.

## How it works

With eight types, 2^24 mantissas and eight POW values, 2^30 states are formed. Separate exact cross products are used for plain types, inverse types and root types. A second normalisation must not change the record, and the type's divisibility rule for 8 or 64 must be preserved. A value, idempotence or form violation counts as an error.

## Why it matters

Examines preservation of the arithmetic meaning of Hunter type and scale codes.

## How to run

```sh
cd TESTLER/HUNTER/06_TIPLER/tur_pow_tam_tarama
gcc -std=c11 -O2 tur_pow_tam_tarama.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [tur_pow_tam_tarama.c](tur_pow_tam_tarama.c)

Archived line count: 82.
