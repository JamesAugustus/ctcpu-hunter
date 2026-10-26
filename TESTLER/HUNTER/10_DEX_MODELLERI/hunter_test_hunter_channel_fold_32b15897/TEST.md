# Channel folding

## What it checks

Compares the channel remainder with direct modulo calculation at each step. Checks the magnitude bound of the signed folding trace, the congruence invariant and correction counts.

## How it works

High and low blocks are added in channels q=3,7, and differences are taken with the corresponding 2,4,5,6-bit widths in channels q=5,17,11,13. For each channel, n=0..65535 is scanned exhaustively and the result is compared with n mod q. In the trace of boundary inputs, the sign must be preserved, folding must not increase the absolute magnitude, and the values before and after a step must remain equivalent modulo q. An incorrect result that still lies within 0..q-1 is deliberately inserted, and gate_y is expected to catch it as reference_mismatch. The full gate's counts of 393216 trials and five invalid inputs are checked. A mismatch in the remainder, trace invariant, error detection behaviour or expected rejection is a unittest failure.

## Why it matters

This concerns verification of the DEX model layer against independent references.

## How to run

```sh
cd TESTLER/HUNTER/10_DEX_MODELLERI/hunter_test_hunter_channel_fold_32b15897/kod/MERSENNE/DEX/DEX_PIPELINE_001/tests
python3 test_hunter_channel_fold.py
```

Requirements: Python 3.

The kod/ directory preserves the relative hierarchy used in the source.

## Source

Source: [test_hunter_channel_fold.py](kod/MERSENNE/DEX/DEX_PIPELINE_001/tests/test_hunter_channel_fold.py)

Archived line count: 88.
