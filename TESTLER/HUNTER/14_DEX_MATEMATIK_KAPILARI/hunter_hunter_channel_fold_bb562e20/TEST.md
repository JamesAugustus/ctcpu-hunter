# Channel folding reference

## What it checks

Produces remainders by folding a bounded integer range in each small prime channel. Checks the result against direct modulo operations and the congruence invariant of each fold.

## How it works

sinama.py calls gate_y. The numbers n=0..65535 are folded in each of the channels q=3,7,5,17,11,13, a total of 393216 times. High and low bit blocks are added for 3 and 7, and the corresponding 2,4,5,6-bit blocks are subtracted for 5,17,11,13. The value folded with its sign preserved is brought into the range 0..q-1 at the final stage by adding or subtracting q. The result must equal n mod q, equivalence modulo q must hold at every trace step, and the absolute value must strictly decrease. Negative inputs, 65536, the unsupported channel 31 and bool inputs are rejected. The first remainder, trace or verification error gives FAIL and the launcher stops with assert. The main file's printing entry does not connect the FAIL return to the exit code.

## Why it matters

This concerns the acceptance contract of DEX mathematical gates in a finite input domain.

## How to run

```sh
cd TESTLER/HUNTER/14_DEX_MATEMATIK_KAPILARI/hunter_hunter_channel_fold_bb562e20/kod/MERSENNE/DEX/DEX_PIPELINE_001/runs/20260908T051824.547563Z/code
python3 sinama.py
```

Requirements: Python 3.

## Source

Source: [hunter_channel_fold.py](kod/MERSENNE/DEX/DEX_PIPELINE_001/runs/20260908T051824.547563Z/code/models/hunter_channel_fold.py)

Archived line count: 150.

The python -c entry code in the catalogue was moved into sinama.py. The mathematical gates are called in the same order.
