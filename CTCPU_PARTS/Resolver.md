# Resolver

The resolver builds the first shadow decomposition of a positive integer. It extracts powers of the fixed primes 2, 3, 5, 7, 11, 13 and 17, and retains the remaining factor. That remaining factor need not be prime.

The input range described here is 1 ≤ N ≤ 2²⁴ − 1. Numbers in the examples are decimal unless marked with a base. The output obeys:

```text
N = 2^e2 × 3^e3 × 5^e5 × 7^e7 × 11^e11 × 13^e13 × 17^e17 × R
```

## Execution logic

The following is a simple sequential explanation of the arithmetic. Its steps are not measured hardware cycles or a final register allocation.

- `N` holds the unchanged input.
- `V` holds the part still being processed, initially N.
- `E[0..6]` holds the seven exponents, initially zero.
- `i` selects a prime in `P = [2, 3, 5, 7, 11, 13, 17]`, initially 0.
- `R` receives V when processing finishes.

```text
shadow requested → validate N → V=N, E=0, i=0
                              ↓
                   V=1 or i=7? ──yes──→ R=V, return E and R
                              │ no
                              ↓
                   V divisible by P[i]?
                      │ yes             │ no
                      ↓                 ↓
                V=V/P[i], E[i]++       i++
                      └────── back to stop check ──────┘
```

For N = 360:

| Step | Before | Action | After |
|---|---|---|---|
| Start | — | Initialise | V=360, E=0, i=0 |
| 1 | V=360, prime=2 | Divide and increment e2 | V=180, e2=1 |
| 2 | V=180, prime=2 | Divide and increment e2 | V=90, e2=2 |
| 3 | V=90, prime=2 | Divide and increment e2 | V=45, e2=3 |
| 4 | V=45, prime=2 | Not divisible, advance | i=1, prime=3 |
| 5 | V=45, prime=3 | Divide and increment e3 | V=15, e3=1 |
| 6 | V=15, prime=3 | Divide and increment e3 | V=5, e3=2 |
| 7 | V=5, prime=3 | Not divisible, advance | i=2, prime=5 |
| 8 | V=5, prime=5 | Divide and increment e5 | V=1, e5=1 |
| Finish | V=1 | Stop and write residual | E=[3,2,1,0,0,0,0], R=1 |

For this loop, there are 8 divisibility checks, 6 exact divisions, 6 exponent increments and 2 prime-index increments. The stop condition is evaluated 9 times. A physical implementation can use a different schedule.

The invariant is `N = V × product(P[j]^E[j])`. A successful division removes one prime factor from V and adds it to E, preserving N. V decreases on a successful division, and i increases otherwise. Processing therefore finishes after a finite number of steps. On completion, R contains none of the seven selected prime factors.

## Octal digit flow

The divisibility filter can scan octal digits from left to right. Each prime channel starts with remainder 0 and updates:

```text
remainder = (8 × remainder + digit) mod prime
```

A digit counter tracks the remaining input digits. In the 24-bit format there are eight octal digits, including leading zeros. Each digit consumes one scan step, and the filter stops after eight steps. Its remainder equals the value of the prefix already read, modulo that prime. The seven channels can be evaluated in parallel.

A zero final remainder detects divisibility. It does not produce the quotient or count every repeated factor by itself. Quotient extraction and exponent counting are separate work. A fully unrolled filter and a serial scan have different area and timing costs.

## Boundaries and cost

- N=1 returns all-zero exponents and R=1.
- N=59 returns all-zero exponents and R=59.
- N=437 returns R=437=19×23. A residual is not a primality certificate.
- N=2124 returns e2=2, e3=2 and R=59.
- Zero is rejected by this model. Repeated division of zero would not terminate.
- Negative, fractional and wider inputs require a separate interface. Silent truncation is not allowed.
- Exponent fields must hold the supported range. For example, N=2²³ requires e2=23. This page does not specify the packed shadow encoding.

The archived design uses shared resolver units and lazy conversion when a multiplicative operation needs a valid shadow. Placement, throughput and gate cost require implementation-specific checks. This page supplies no new hardware measurements, and the journal tests are not a complete resolver test suite.

[Parts](README.md) · [Türkçe](../tr/CTCPU_PARCALAR/Resolver.md) · [Repository overview](../README.md)
