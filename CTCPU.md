# CTCPU

CTCPU is a processor I am designing to work with two representations of a number. It uses ordinary positional notation and a second representation I call shadow. Hunter continues this work.

## How are numbers stored?

An xbit consists of three bits and represents one octal digit. Eight xbits hold a 24-bit value. Colours are used to visualise these digits.

The positional representation stores a number as digits. The shadow representation stores the exponents of selected prime factors and the remaining factor.

## Parts

| Part                   | What does it do?                                                                                                   |
|------------------------|--------------------------------------------------------------------------------------------------------------------|
| Control unit           | Selects the next instruction and directs the work of the other parts.                                              |
| Registers              | Hold the numbers being processed, intermediate results and control information.                                    |
| ALU                    | Performs addition, subtraction, comparisons and other arithmetic operations.                                       |
| Resolver               | Prepares the shadow representation by extracting selected prime exponents and the remaining factor.                |
| Shadow fields          | Store the representation produced by the resolver. Suitable multiplicative operations can use this representation. |
| Flags                  | Record conditions such as zero or overflow.                                                                        |
| Instructions and jumps | Specify the operation to perform. Jump instructions change where the program continues.                            |

The ISA is the contract that defines instruction formats and their behaviour.

## How do the parts work together?

Initially, the program and its input values are available. When execution starts, the control unit fetches the next instruction. The required values are read from registers and sent to the relevant unit.

Operations such as addition use the positional representation. If an operation needs a shadow that is not yet valid, the resolver builds it. The result is written to a register and the relevant flags are updated.

A jump instruction can return the program to an earlier step. A condition or counter in the program determines when the loop ends. Execution finishes when a stop instruction is reached.

This page describes the overall design flow. Exact connections and instruction behaviour will be detailed in the individual documents.

[Parts](CTCPU_PARTS/README.md) · [Resolver worked example](CTCPU_PARTS/Resolver.md) · [Türkçe](tr/CTCPU.md)
