# Journal claims T01-T22

## What it checks

Examines the mathematical claims T01..T22 in the publication through finite examples and counterexamples. Separates the status of Mersenne factor conditions, the Pascal base threshold, Lucas Lehmer traces and representation relations into HOLDS, FAILS or UNTESTED.

## How it works

Checks the Mersenne factor law for prime exponents 3..31 and octal representation for exponents 3..300. Reads Pascal rows back for n=1..30 in bases one and two larger than the largest coefficient, and compares addition of the prime exponent vector under multiplication for number pairs 1..64. In the ternary chain, matches the direct sum for b=2..10, n=1..18 with the closed formula and scans the condition 3^(q-1)≡1 mod q² over primes q≤2000000. A broken equality calls fail_card. Some cards aim to verify a known counterexample, so a FAILS label on a card alone is not considered an implementation error, and an UNTESTED card gives no verdict on correctness.

## Why it matters

Makes the scope of finite checks on numbered claims in the Hunter publication visible.

## How to run

```sh
cd TESTLER/HUNTER/07_GUNLUK_IDDIALARI/journal_tests
gcc -std=c11 -O2 journal_tests.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [journal_tests.c](../../../../journal_tests.c)

Archived line count: 811.
