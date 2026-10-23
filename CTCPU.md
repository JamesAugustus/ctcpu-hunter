# CTCPU

CTCPU is a processor I am designing to work with two representations of a number. It uses ordinary positional notation and a second representation I call shadow. Hunter continues this work.

## Start with colours

A normal processor works with bits: 0 or 1. CTCPU works with a larger smallest unit, the **xbit**: three bits, which means eight values. I show those eight values as eight colours, because three light channels (red, green, blue) can be mixed into eight colours. Each colour has a number and a letter.

| Number | Colour  | Letter | Three bits |
|--------|---------|--------|------------|
| 0      | Black   | K      | 000        |
| 1      | Red     | R      | 001        |
| 2      | Green   | G      | 010        |
| 3      | Yellow  | Y      | 011        |
| 4      | Blue    | B      | 100        |
| 5      | Magenta | M      | 101        |
| 6      | Cyan    | C      | 110        |
| 7      | White   | W      | 111        |

The colours mix like light: red (1) + green (2) = yellow (3), red (1) + blue (4) = magenta (5), green (2) + blue (4) = cyan (6), and red + green + blue = white (7).

A number is a row of these colours. Written in base 8, 137 is 211, so in colours it is G R R. The Mersenne number 31 is 37 in base 8, so it is Y W. The number 127 is 177 in base 8, so it is R W W. This is why the 1, 3, 7 patterns in the journal can be seen as colours.

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
