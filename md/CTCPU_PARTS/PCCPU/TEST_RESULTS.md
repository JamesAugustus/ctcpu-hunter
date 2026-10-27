# PCCPU C model: test results

James Augustus

Run date: 27 October 2026.

## Result

The C source was rebuilt and the tests were run again. **60,353 checks passed, 0 errors.** The runner exited with code 0. The small example returned 210. The large example returned this 59-digit integer:

```text
90548514656103281165404177077484163874504589675413336841320
```

The [raw output](../../../kod/PCCPU/TEST_OUTPUT.txt) includes the build message, test summary and both demonstrations. It contains no username, hostname or absolute local file path. In its Turkish labels, `gecti` means passed, `hata` means error, `tur` means round and `sonuc` means result.

## Reproduction

From the repository root:

```sh
bash kod/PCCPU/calistir.sh
```

Bash, a C11 compiler and GMP development files are required. Compilation uses `-std=c11 -O2 -Wall -Wextra -Werror -pedantic` and `-lgmp`. The binary runs with `--test` followed by `--demo`. Temporary build output is removed at the end. No network connection is required.

## Checked behavior

| Check | Observed result |
|---|---|
| Six cells and coordinate bounds | Distinct addresses, invalid coordinates rejected |
| Invalid row and duplicate worker order | Request rejected without advancing counters |
| Unready result and invalid address reads | Reads rejected |
| Consumer waiting for producers | Only A and B complete in round 1, C in round 2 |
| All six worker inspection orders | Same result, 3 completions, 2 logical rounds |
| Running a completed model again | No new work or counter increments |
| 20,100 adjacent Pascal sums | Match an independent addition-only row construction |
| Values beyond a fixed 64-bit integer | Exact GMP integer result |
| Carry-free row-product decision | Boundary examples in bases 10, 3 and 127 pass |
| Coefficient equal to the base | Rejected as a carry-free digit |
| Invalid base and row-sum overflow | Request rejected |

The Pascal comparison covers all adjacent pairs in rows n = 1..200. There are 1 + 2 + ... + 200 = 20,100 pairs. Each checks initialization, execution and result equality. Other checks bring the total to 60,353 evaluated conditions, not 60,353 separate algorithms or hardware experiments.

The comparison does not call the binomial-coefficient routine; it constructs rows by addition. Both paths still use GMP for integer arithmetic, so this is not verification by an independent arithmetic library.

## Demonstrations

| Demonstration | Value | Controller |
|---|---|---|
| C(9,3) + C(9,4) | 84 + 126 = 210 | 3 completions, 2 rounds |
| C(199,99) + C(199,100) | C(200,100), 59 digits | 3 completions, 2 rounds |

The printed 121 × 121 and 1331 × 121 statements are explanatory text. Automated checks test the carry-free decision for those rows. They do not separately reconstruct and compare those complete integer products.

## Not covered

Symmetric thread records, paired RAM fields, side selection and invalidation after writes are not implemented in this C program. These test results do not validate them. The model does not compute N(p). Physical PCCPU hardware, actual concurrent execution, clock cycles, speed, energy and total memory savings were not measured.

See the [PCCPU design](PCCPU.md) and the [step-by-step Turkish explanation](../../../tr/md/CTCPU_PARCALAR/PCCPU/PCCPU_C_TESTI_ACIKLAMA.md).

Addressing note: C(n,j) here is the test program’s classical binomial notation. CTMemTensor centre-based reading denotes the same central coefficient as N(9,0) = 126. Its addressing alternatives are defined [separately](../CTMemTensor/CTMemTensor.md).


## CTMemTensor numerical illustration

The CTMemTensor HTML illustration was checked for n = 0..16 and x = 2..255 in three addressing modes: centre pair, left-edge column and doubled geometric coordinate. For all 12,954 row, base and mode combinations, the weighted sum matched (x+1)^n. Coefficients were compared with independently constructed Pascal rows using addition only. Every column was covered exactly once, including a single central position.

The examples N(9,0) = 126 and N(4,-2..+2) = [1,4,6,4,1] were verified. Thirteen invalid inputs were rejected. These results concern the browser's mathematical illustration. They do not validate a C address decoder, concurrent thread execution or a physical RAM protocol.
