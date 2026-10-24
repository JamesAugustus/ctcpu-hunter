# CTCPU and Hunter: The Road So Far

> **No silicon exists.** MHz and watt figures, and hardware cycle estimates, are model values. Archived emulator measurements were not rerun for this package. The runnable code here consists of the mathematical tests below.

**At a glance.** CTCPU is a processor idea I have been working on, which later became Hunter. Its smallest unit is three bits, shown as one of eight colours, and a number can also be kept in a second "shadow" form made of prime exponents. This repository holds my research journal, short pages on the machine and its parts, and 22 tests of the mathematical claims in the journal: 15 hold, 4 are shown false by a counterexample, and 3 cannot be tested here. There is no chip and no measured speed or energy result. Start with the [CTCPU page](CTCPU.md), then read the journal.

This is my research journal about CT-CPU and the ideas that led to Hunter. It follows what I tried, what worked, what failed, and what I later learned was already known. It includes my notes on number representations, Pascal's triangle and Mersenne numbers, along with calculations, sources and personal reflections.

This repository contains the mathematical foundations of the CTCPU/HUNTER work, on number representation and Pascal structures, together with the verification experiments.

Why I am doing this: [A Little Message](A_LITTLE_MESSAGE.md).

On knowledge, ego and order: [A Note](NOTE.md).

Machine overview and components: [CTCPU](CTCPU.md) · [CTCPU parts](CTCPU_PARTS/README.md) · [Resolver](CTCPU_PARTS/Resolver.md).

## Read the journal

- **English:** [The Road So Far — PDF](THE_ROAD_SO_FAR.pdf) · [Markdown](THE_ROAD_SO_FAR.md)
- **Türkçe:** [Hunter’a Giden Yol — PDF](tr/YOL.pdf) · [Markdown](tr/YOL.md)

Both versions contain the same entries, formulas and test results. The journal tells the story in my own voice; conversational notes that I have retold are distinguished from quotations.

This is a record of work in progress, not a finished processor. Some older experiments are described from archive records and cannot be rerun from this repository. The 22 tests included here check a specific set of mathematical claims.

The separate [Pascal Mersenne Rows](https://github.com/JamesAugustus/pascal-mersenne-rows) repository contains the Mersenne row study. The journal's Pascigon figure is also available separately: [English](Pascigon.pdf) · [Turkish](tr/Pascigon.pdf).

## Run the tests

With a C99 compiler, run these commands from the repository's main folder:

```sh
cc -std=c99 -O2 -Wall -Wextra -o journal_tests journal_tests.c -lm
./journal_tests
```

No third-party library is needed. The [source code](journal_tests.c) and [expected output](TEST_OUTPUT.txt) are included. The expected summary is:

```text
HOLDS=15 | FAILS=4 | UNTESTED=3 | ERROR=0 | tests=22
```

`HOLDS` means the claim held in the tested cases. `FAILS` records a counterexample to a claim, not a broken test program. `UNTESTED` means this package cannot test the claim. `ERROR` means an implemented check did not produce its expected result. Exit code 0 means no such error occurred; it does not prove every claim in the journal.

## License and citation

The C code is under the [MIT License](LICENSE). The English and Turkish text, PDFs, figures, test output and citation metadata are under [CC BY 4.0](LICENSE-CC-BY-4.0.txt), with attribution to James Augustus. These licenses do not relicense the third-party works cited in the journal. Citation details are in [CITATION.cff](CITATION.cff).
