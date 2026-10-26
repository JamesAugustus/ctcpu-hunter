# Resolver experiments

James Augustus

Here I explain forms of Resolver that have not been implemented in code or have remained only as examples and scripts. The working and tested forms are in [Resolver](../Resolver.md). The forms are ordered from newest to oldest. Numbers are decimal unless marked with $_8$.

| Order | Form | Date | Status |
|:---:|---|---|---|
| 1 | Resolving through the exponent, the $2^p - 1$ form | 4 September 2026 | demonstrated with a script, not coded as a Resolver unit |
| 2 | Layered ladder | 3 September 2026 | not implemented in code |
| 3 | The $a$ cell's dual role and plain factor | July-August 2026 | exponent spreading tested |

## Contents

| Section | Title |
|---|---|
| 1 | Resolving through the exponent, the $2^p - 1$ form |
| 1.1 | Date and source |
| 1.2 | Idea |
| 1.3 | Mechanism |
| 1.3.1 | Reading from the form |
| 1.3.2 | The $2p + 1$ gate |
| 1.3.3 | The $k$ walk |
| 1.3.4 | Folding if the body is needed |
| 1.4 | Example |
| 1.5 | Code and testing |
| 1.6 | Difference |
| 2 | Layered ladder |
| 2.1 | Date and source |
| 2.2 | Idea |
| 2.3 | Mechanism |
| 2.4 | Example |
| 2.5 | Code and testing |
| 2.6 | Difference |
| 3 | The $a$ cell's dual role and plain factor |
| 3.1 | Date and source |
| 3.2 | Idea |
| 3.3 | Mechanism |
| 3.4 | Example |
| 3.5 | Code and testing |
| 3.6 | Difference |
| 4 | Open questions |

## 1. Resolving through the exponent, the $2^p - 1$ form

### 1.1 Date and source

4 September 2026. An account of the process for a twenty-five-digit number from start to finish.

### 1.2 Idea

Some numbers do not fit in a register, but their forms are known. When working with a number of the form $2^p - 1$, compositeness is established when a divisor greater than 1 and smaller than the number is found using only the exponent $p$ and small remainders, without ever building the number itself. Failure to find a divisor in a limited search does not establish primality.

### 1.3 Mechanism

There are four steps.

#### 1.3.1 Reading from the form

The octal notation of $2^p - 1$ depends on $p \bmod 3$: if the remainder is 1, the leading digit is 1. If the remainder is 2, the leading digit is 3. If the remainder is 0, there is no leading digit. Only 7s follow.

#### 1.3.2 The $2p + 1$ gate

If $p \equiv 3 \pmod 4$ and $2p + 1$ is prime, $2p + 1$ divides the number.

#### 1.3.3 The $k$ walk

For an odd prime exponent $p$, if the gate does not open, divisors are sought only in the forms $q = 2kp + 1$ and $q \equiv \pm 1 \pmod 8$. For $p \equiv 3 \pmod 4$, only the classes $k \equiv 0, 1 \pmod 4$ are tried. The other classes are eliminated without calculation.

#### 1.3.4 Folding if the body is needed

If the body itself is needed, the flow folding in [Resolver](../Resolver.md) is used instead of division.

### 1.4 Example

$p = 83$, $N = 2^{83} - 1$, 25 decimal digits, 28 octal digits. It does not fit in a register.

Since $83 = 3 \cdot 27 + 2$, the remainder is 2, and the octal notation starts with a 3 followed by 27 copies of 7. Also, $83 \equiv 3 \pmod 4$ and $2 \cdot 83 + 1 = 167$ is prime. So 167 divides $N$, and $N$ is composite.

This information comes from two operations on two-digit numbers. For verification, $N \bmod 167 = 0$ was also calculated.

### 1.5 Code and testing

Python. Every number in the account of the process was produced by a script. The Lucas-Lehmer steps were followed one by one for $p = 13$, and the final value was 0. $8191$ is prime.

### 1.6 Difference

The number is not resolved. It is read from its form. Resolver deals with the exponent that produces the number, rather than the number itself.

## 2. Layered ladder

### 2.1 Date and source

3 September 2026. Register template and formula record.

### 2.2 Idea

The shadow's four rows are the levels of a ladder. At each level, seven primes are stripped off. If the remaining value is not divisible, its last octal digit is cut off, and the rest goes down one level. Each level descent means division by 8.

### 2.3 Mechanism

$$v_k = s_k \cdot (8\,v_{k+1} + a_{k+1})$$

Here $s_k$ is the product of prime powers stripped off at level $k$, and $a_{k+1}$ is the digit cut during descent. In $rs1$, the $a$ cell is empty, because there is no descent from the normal number to the first level. An exponent cell holds at most 7. When the cell is full, the remaining value goes down the ladder again:

$$3^{10} = 3^7 \cdot 27 = 3^7 \cdot (8 \cdot 3 + 3) = 59049$$

### 2.4 Example

$2124 = 4114_8$. At the first level, $2^2 \cdot 3^2$ is stripped off, leaving 59. $59 = 73_8$, the last digit 3 is cut off, 7 goes down to the second level, and 7 is stripped off there:

$$2124 = 2^2 \cdot 3^2 \cdot (8 \cdot 7 + 3)$$

![Figure 1a. Converting 2124, first level: loading and stripping (frames 1-7).](../figures/merdiven_2124_a.svg)

![Figure 1b. Converting 2124, level descent and second level (frames 8-11).](../figures/merdiven_2124_b.svg)

### 2.5 Code and testing

Layered descent was not implemented in code. The examples were calculated with the drawing program and checked by equality.

### 2.6 Difference

In the previous form, exponent overflow was written to a lower row as a "plain factor". Here every row is an actual descent, and no row is read without division by 8.

## 3. The $a$ cell's dual role and plain factor

### 3.1 Date and source

July and August 2026. Shadow mechanism diagram and main design description.

### 3.2 Idea

After the seven primes are stripped off, the remaining value is odd, because all factors of 2 have been stripped off (unless the exponent cell is full). The last octal digit of an odd number is always 1, 3, 5 or 7. So the $a$ digit cut during descent is never even. Even values are left free and can be used to indicate the row's type. A row either carries a remainder digit or declares a type, never both.

### 3.3 Mechanism

| $a$ | Meaning of the row |
|---|---|
| 1, 3, 5, 7 | ladder: the upper row's rough $= 8 \cdot \text{me} + a$ |
| 0 | plain factor: I am not a ladder, I join the upper row's product |
| 2 | rough: my cells are read as a normal number |
| 4, 6 | prefix and suffix: neighbouring register boundary |

If an exponent exceeds 7, the excess is written to the next empty row as a plain factor with $a = 0$. No descent is used up.

### 3.4 Example

$2^{11} = 2048 = 2^7 \cdot 2^4$: $e_2 = 7$ in the first row, $e_2 = 4$ and $a = 0$ in the second row. In this layout, the total exponent capacity is four rows times 7, that is, 28. If it is exceeded, overflow is reported. There is no silent truncation.

### 3.5 Code and testing

Exponent overflow and spreading across rows were tested in the shadow emulator. According to the recorded measurement, distributing exponents from 0 to 40 across layers is error-free.

### 3.6 Difference

In the later layered ladder, $a = 0$ also counted as an actual descent, and the value remaining at the cell limit went down. In this form, $a = 0$ is a factor without descent.

## 4. Open questions

The layered ladder was not implemented in code or tested. How the end of the chain is marked, values below 8 after reaching the exponent limit, and the end of the fourth row are open. Which of these experiments will join the working Resolver needs a separate decision.

Related pages: [Resolver](../Resolver.md), [Gear model](../Gear.md), [Register](../../Register/Register.md) and [Parts](../../README.md).
