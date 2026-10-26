# Comparison of rejection and quarantine

## What it checks

Checks that random clean operation chains match an exact reference in two fraction models. Tests that in division by zero, the quarantine lock lets no number leak out and preserves the source trace.

## How it works

A chain of five operations is built in each of one million examples. The v1.3 and v1.4 results are compared with an independent fraction reference through the equality r.n×ref.d=ref.n×r.d. In a chain with injected division by zero, the lock must be preserved and the trace value must equal the independent product of the remaining factors. A difference or incorrect quarantine behaviour increases the corresponding counter.

## Why it matters

Connects multiplication and division using prime exponents and rough components to reference arithmetic.

## How to run

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/kesir_v13_v14_kiyas
gcc -std=c11 -O2 kesir_v13_v14_kiyas.c -o ./test_programi -lm && ./test_programi
```

Requirements: gcc, libm.

## Source

Source: [kesir_v13_v14_kiyas.c](kesir_v13_v14_kiyas.c)

Archived line count: 125.
