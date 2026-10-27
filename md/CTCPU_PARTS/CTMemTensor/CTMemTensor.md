# CTMemTensor

James Augustus

Memory and addressing systems under consideration

## Abstract

CTMemTensor is a working name for representing numerical values, mathematical positions and symmetry relationships in a common memory record. A record may hold a value, two symmetric positions, a mathematical description or associated computed values. This document defines possible addressing and storage schemes. None is fixed as a final instruction set or physical RAM layout.

The principal example starts at the centre. In [1,4,6,4,1], the value 6 has address 0, the left 4 has address -1 and the right 4 has address +1. Rows with two central entries require an additional distinction between a shared central coefficient and two separate positions. Signed centre coordinates, distance with a side field, edge-based columns and geometric coordinates are retained as alternatives.

PCCPU concerns task dispatch and completion. CTMemTensor concerns representation of data, positions and symmetry. Pascal coefficients provide the mathematical example family. N(p) bounds the rows whose coefficients are directly readable as digits in a selected Mersenne base. Physical memory, multicore execution and a performance advantage have not been implemented.

## 1. Definitions and scope

Here n is a Pascal row number, starting with the single 1 at n = 0. A row has n + 1 entries. The representation 1331 contains four entries but corresponds to row n = 3. Entry count and row number are different parameters.

| Notation | Meaning |
|---|---|
| C(n,j) | Classical binomial coefficient at zero-based column j from the left |
| N(n,z) | Centre-based coefficient reading considered in this document |
| d | Nonnegative distance from the centre or central pair |
| a | Selected side, with example encoding 0 = left and 1 = right |
| j_L, j_R | Classical columns of the left and right positions |
| x | Computational base or power variable |
| N(p) | One-argument function giving the last carry-free row |

N(n,z) reads a coefficient in a row, whereas N(p) bounds a valid row range for a base. A final interface may give these operations different names. Different argument counts do not remove the need for explicit types and semantics.

The classical statement C(9,4) = 126 is mathematically correct. In centre-based notation the central coefficient is N(9,0) = 126. The coordinates 4 and 0 belong to different systems. Using C(n,j) internally does not require external addresses to follow column order.

The name CTMemTensor refers to a record with multiple axes. It does not denote an implemented tensor-product engine or general tensor algebra hardware. Row, centre distance, side, base and operation type may be separate axes or record fields.

## 2. Signed centre-based addressing

For row n = 4, which has one central entry:

| Coefficient | 1 | 4 | 6 | 4 | 1 |
|---|---|---|---|---|---|
| Signed address z | -2 | -1 | 0 | +1 | +2 |
| Distance d = abs(z) | 2 | 1 | 0 | 1 | 2 |
| Side | Left | Left | Centre | Right | Right |

Thus N(4,0) = 6, N(4,-1) = N(4,+1) = 4 and N(4,-2) = N(4,+2) = 1. The sign indicates direction and the absolute value indicates distance. -1 and +1 are distinct positions with distance 1 and equal coefficients in this row.

Reading distinct coefficients outwards gives 6,4,1. Reading every position from left to right gives 1,4,6,4,1. Traversal order and the mathematical row are separate concepts.

For a single-centre row n = 2m, the classical column is j = m + z, with -m ≤ z ≤ m. Its coefficient can be computed as C(n,m+z). This conversion allows the new addressing scheme to use an existing binomial routine.

## 3. Distance and a side bit

The sign may instead be stored separately. A record can use (n,d,a), with example encoding a = 0 for left and a = 1 for right. This bit assignment is not a final architectural decision.

Let m = floor(n/2). For 0 ≤ d ≤ m, the two columns are

`j_L = m - d`

`j_R = n - m + d`.

Their shared coefficient satisfies C(n,j_L) = C(n,j_R), because j_R = n - j_L.

N(n,d)[a] is a possible notation for this scheme. Its second argument is a nonnegative distance rather than a signed coordinate. An interface must declare the chosen mode. These alternatives do not silently assign two meanings to one expression.

### Rows with two central entries

Row n = 9 is [1,9,36,84,126,126,84,36,9,1], with m = 4. At d = 0, j_L = 4 and j_R = 5. Both coefficients are 126. Therefore N(9,0) = 126 identifies the central value but does not by itself select one central position.

| Distance d | Left column | Right column | Shared coefficient |
|---|---|---|---|
| 0 | 4 | 5 | 126 |
| 1 | 3 | 6 | 84 |
| 2 | 2 | 7 | 36 |
| 3 | 1 | 8 | 9 |
| 4 | 0 | 9 | 1 |

When position matters, N(9,0)[0] may select the left centre and N(9,0)[1] the right centre. Integer -0 and +0 are not distinct addresses, so a sign alone cannot distinguish those two positions.

For n = 4 and d = 0, j_L = j_R = 2. Both selectors refer to one position, counted once in a sum. For n = 9 and d = 0, two distinct positions contribute separately despite equal coefficients.

## 4. Other addressing systems under consideration

### 4.1. Edge-based columns

Classical column j runs from 0 to n from the left. For n = 4 the addresses are 0,1,2,3,4 and coefficients are 1,4,6,4,1. This scheme writes C(9,4) = 126 and pairs j with n-j.

The earlier PCCPU example assigning both endpoints to thread_no_1 illustrates an edge-based option. It remains an alternative and must not be read as the same coordinate system as centre-based N(n,z).

### 4.2. Geometric centre

The coordinate u = j - n/2 gives -2,-1,0,+1,+2 for n = 4. For n = 9, the central coordinates are -1/2 and +1/2. Every position has a distinct coordinate, but there is no entry at 0 in a two-centre row.

Using q = 2j - n removes fractions. Row n = 4 then has addresses -4,-2,0,+2,+4, while the two central addresses in row 9 are -1 and +1. This scale is different from central-pair distance d. It is an alternative to the N(9,0) = 126 reading convention.

### 4.3. One central entry as the origin

Taking the left central entry as origin gives t = j - floor(n/2). In row 9, central addresses are 0 and 1. All addresses are integers, but reflection pairs t with 1-t, rather than t with -t. Reflection rules depend on the addressing scheme.

### 4.4. Comparison

| Scheme | Centre of row 4 | Centres of row 9 |
|---|---|---|
| Central pair with side | 0, one position | 0 with separate left/right field |
| Geometric u | 0 | -1/2 and +1/2 |
| Doubled geometric q | 0 | -1 and +1 |
| Left-centre origin t | 0 | 0 and 1 |
| Left-edge column j | 2 | 4 and 5 |

Centre-based reading is the principal example. The other schemes remain candidates. An implementation must carry its addressing mode in the record or keep it fixed across the interface.

## 5. Position selection and arithmetic

Selecting a position does not determine which quantity is requested. The operation may read a coefficient, a base power or a positional contribution. Raising the coefficient itself to a power is another possible operation.

| Operation | Definition | n = 4, left 4, x = 10 |
|---|---|---|
| Coefficient | c = C(n,j) | 4 |
| Base power | x^(n-j) | 1000 |
| Positional contribution | c × x^(n-j) | 4000 |
| Coefficient power | c^j, using left-edge column j here | 4 |

For the right 4, j = 3. Its coefficient is 4, positional contribution is 40 and coefficient power is 4³ = 64. In 1331, the left 3 has j = 1 and 3¹ = 3; the right 3 has j = 2 and 3² = 9. These illustrate the coefficient-power option. Using distance d as the exponent would define a different operation and must be stated explicitly.

Entering 14641 in decimal notation does not itself determine the computational x. Input representation base and computational base can be separate fields. When both are 10, the positional contributions are 10000,4000,600,40,1 and sum to 14641.

## 6. Memory records under consideration

Three storage approaches are considered: storing both computed symmetric values, storing a mathematical description that can generate them, or retaining a description with cached computed values.

| Field group | Contents |
|---|---|
| Addressing | Mode, row, position or distance, side |
| Mathematical data | Shared coefficient, computational base or reference |
| Operation | Coefficient, base power, contribution or coefficient power |
| Values | Separate full integers for left and right when needed |
| State | Readiness and validity for each side |
| Ownership | Logical thread or assigned core identity |

A thread identity, a mathematical coordinate and a physical memory address are distinct. thread_no_1 need not correspond to d = 0 or j = 0. It may own the endpoints of row 4, the pair at d = 2, and values x^4 and x^0. Centre-based addressing does not prevent this ownership arrangement.

One central position is counted once. Two central positions have separate weights even if their coefficients agree. Changes to the row, base, position or operation invalidate affected cached values. Independently modifying one coefficient must break the shared-coefficient relationship.

A cell record may represent a core or a task. This does not place a physical processor inside a RAM cell. A software record layout and special computing-memory hardware are separate development stages. Field widths, access paths and concurrent-write rules remain open.

## 7. Pascal symmetry and the N(p) bound

Pascal coefficients satisfy C(n,j) = C(n,n-j). For integer base b ≥ 2,

`(b+1)^n = Σ C(n,j) b^(n-j),  j = 0,...,n`.

Direct digit interpretation requires C(n,floor(n/2)) < b. At b = 2^p - 1 with integer p ≥ 2,

`N(p) = max { n ≥ 0 : C(n,floor(n/2)) < 2^p - 1 }`

is the last valid row. For n ≤ N(p), coefficient symmetry can be read directly as digit symmetry. Beyond that bound, coefficients remain symmetric but digits after carrying need not be symmetric.

For example N(3) = 4. In base 7, row 4 gives digits [1,4,6,4,1] and value 4096. Row 5 has coefficients [1,5,10,10,5,1], but normalized digits [1,6,4,3,5,1]. Symmetric coefficient storage and normalized digit storage are therefore distinct modes.

The mathematical work belongs to [pascal-mersenne-rows](https://github.com/JamesAugustus/pascal-mersenne-rows). The published [earlier note](https://github.com/JamesAugustus/pascal-mersenne-rows/blob/main/md/PASCAL_MERSENNE_ROWS.md) explains the positional representation and carry-free condition. The N(p) extension investigates the last valid row at a fixed base. CTMemTensor does not treat N(p) as proof of a memory-speed advantage.

## 8. Implementation status and open decisions

The [PCCPU C example](../../../kod/PCCPU/pccpu_address_model.c) tests producer/adder dependencies and internally uses classical C(n,j). Its 60,353 checks belong to that existing program. A CTMemTensor centre-address decoder, selectable addressing modes and RAM protocol are not implemented in it.

The [test report](../PCCPU/TEST_RESULTS.md) describes the sequential C model. The addressing schemes in this document remain design proposals.

Open decisions include addressing mode, two-centre representation, side-bit assignment, operation types, full-value versus descriptor storage, cache validity, core ownership and physical memory layout. They are recorded as systems under consideration. CTMemTensor is a working name, with no claim of a new processor standard, completed hardware or established performance superiority.

## References and related documents

[PCCPU](../PCCPU/PCCPU.md), [Turkish explanation of the C model](../../../tr/md/CTCPU_PARCALAR/PCCPU/PCCPU_C_TESTI_ACIKLAMA.md), [Türkçe](../../../tr/md/CTCPU_PARCALAR/CTMemTensor/CTMemTensor.md).

Text: CC BY 4.0. Copyright © 2026 James Augustus.
