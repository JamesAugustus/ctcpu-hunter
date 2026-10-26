# Producing a Mersenne remainder through cell flow

## What it checks

Calculates the Mersenne remainder as a stream by reducing digit shift positions through exponent mod p. Compares the result with direct modulo calculation of the full integer body and records accumulator width and folding count.

## How it works

Artificial tables of 2,3,4,8 rows are built for p=13,31,61,127,521 and cell widths 3,8,16. A Horner step and Mersenne folding are applied as digits are read in snake order. The value%(2^p-1) calculated from the full body must give the same remainder. Inequality is an assert error. The accumulator's largest bit length and folding count are also measured.

## Why it matters

This concerns claims based on representation, remainders and finite examples in DEX research.

## How to run

```sh
cd TESTLER/HUNTER/11_DEX_ARASTIRMALARI/hunter_stream026_9dd5af2c
python3 stream026.py
```

Requirements: Python 3.

## Source

Source: [stream026.py](stream026.py)

Archived line count: 38.
