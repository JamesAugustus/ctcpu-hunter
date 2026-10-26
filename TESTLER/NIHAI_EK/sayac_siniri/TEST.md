# The limit of the octal exponent counter

## What it checks

Tests that the four-row octal exponent counter in the flowing counter core counts correctly from 0 to 4095 in each of the seven channels. $2^{4095}$ is reconstructed, and the next exponent and a product exceeding the limit are rejected.

## How it works

The core is included without changing the code. In each channel, the counter is incremented one by one and read. Reconstruction at the boundary, rejection, rough exact division and division by zero are checked separately.

## Why it matters

Shows that the carry pins in the gear model and the 4095 limit actually work.

## How to run

```sh
cd TESTLER/NIHAI_EK/sayac_siniri
gcc -O2 -I. sayac_siniri.c -o sayac_siniri -lm && ./sayac_siniri
```

Requirements: GCC and libm.
