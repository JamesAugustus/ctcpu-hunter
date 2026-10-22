# CTCPU parts

CTCPU is a processor design built around octal digits and two representations of a number. The positional representation supports ordinary addition and subtraction. The shadow representation stores selected prime exponents and a residual factor, so suitable multiplicative operations can work on exponents.

CTCPU is the earlier name in the work that continues as Hunter. These pages describe the parts and their roles. They do not establish that every archived component belongs to one integrated, tested machine.

## Number and representation

One xbit is three binary bits, read as one octal digit. Eight xbits hold a 24-bit unsigned value. A colour can label that digit, but does not add information beyond the three bits.

For example, 360 = 2³ × 3² × 5. Its first shadow decomposition contains exponents [3, 2, 1, 0, 0, 0, 0] for the primes [2, 3, 5, 7, 11, 13, 17], and residual 1. The [resolver](Resolver.md) produces this decomposition. Further shadow layers are outside this introductory example.

## Parts and roles

| Part | Role | Included here |
|---|---|---|
| Control and registers | Hold values, select instructions and direct data movement | Overview only |
| ISA | Defines instruction formats and behaviour | Summarised in the research journal |
| ALU | Performs arithmetic and comparisons | Overview only |
| Shadow | Holds the alternative number representation | First-layer example |
| Resolver | Converts a positive positional integer into selected prime exponents and a residual | [Explanation and worked example](Resolver.md) |
| Flags | Record conditions used by control logic | Overview only |

The arithmetic is not free. Exponent operations, residual factors, representation conversion and overflow all have costs. Addition is defined for the represented numbers, but generally cannot be performed by adding their prime exponents.

## Execution logic

Initially, a register holds a positional value. When an operation needs a shadow that is not already valid, the control logic requests conversion. The resolver reads the value, extracts the selected prime powers and returns the exponents and residual. The operation then consumes the representation it needs. Updating the positional value requires maintaining or invalidating the corresponding shadow.

This is the lazy-conversion rule: loading a number does not by itself require building its shadow. The exact scheduling, register interface and cost must be checked against the implementation when it is added.

## Publication scope

This folder currently contains explanations, not emulator source or a complete ISA specification. The assembly language, assembler, compiler and emulator can be added to this same repository later. No measured hardware speed or energy saving is claimed here.

The description draws on the archived CTCPU system definition and part cards. The 22 tests in the repository check mathematical claims from the journal, not the complete resolver or CPU interface.

[Research journal](../THE_ROAD_SO_FAR.md) · [Türkçe](../tr/CTCPU_PARCALAR/README.md) · [Repository overview](../README.md)
