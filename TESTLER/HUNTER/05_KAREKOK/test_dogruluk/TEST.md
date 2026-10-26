# 24-bit square root error scan

## What it checks

Measures the error of binomial approximation, Newton corrections and LNS square root paths on the numbers 2..16777215. Compares each method's largest and mean relative error with the standard sqrt reference.

## How it works

For N=2..16777215, the standard sqrt and five approximations are calculated. For each method, the relative error abs(approximation-sqrt(N))/sqrt(N) is accumulated. The largest error, the input producing it and the mean error are printed. The source defines no pass or fail threshold.

## Why it matters

Examines error bounds of exact and approximate calculations in the Hunter root unit.

## How to run

```sh
cd TESTLER/HUNTER/05_KAREKOK/test_dogruluk
gcc -std=c11 -O2 test_dogruluk.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [test_dogruluk.c](test_dogruluk.c)

Archived line count: 24.
