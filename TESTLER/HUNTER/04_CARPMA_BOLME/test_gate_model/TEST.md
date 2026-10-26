# Python coefficient and product check

## What it checks

The four selected methods compare the squares of 256 byte values and raw product coefficients with an independent weighted sum. Tests value preservation at every step in a multioperand carry chain and rejection of invalid arithmetic types.

## How it works

The four GateModelTests methods in the command are called in order. The squares of values 0..255 are built with 15 raw coefficients formed from 64 bit-pair products and compared with value². The weighted sum of multioperand carry steps must be preserved in bases 2..7. Accepting an invalid type, base or digit, or coefficient normalisation changing the value, causes a unittest error.

## Why it matters

Connects multiplication and division using prime exponents and rough components to reference arithmetic.

## How to run

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/test_gate_model/kod/SISTEM/Hunter8/gate
python3 test_gate_model.py GateModelTests.test_all_256_byte_squares_and_raw_coefficients GateModelTests.test_two_square_traces_and_multioperand_carry GateModelTests.test_raw_coefficients_keep_value_at_every_normalization_step GateModelTests.test_invalid_arithmetic_types_bases_and_digits_raise_value_error
```

Requirements: Python 3.

The kod/ directory preserves the relative hierarchy used in the source.

## Source

Source: [test_gate_model.py](kod/SISTEM/Hunter8/gate/test_gate_model.py)

Archived line count: 197.
