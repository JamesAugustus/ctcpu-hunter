# CTCPU and Hunter

> **No silicon exists.** MHz and watt figures, and hardware cycle estimates, are model values. Selected archived emulator sources were rerun for this package. Earlier emulator measurements remain historical records. The runnable code includes 30 archived tests and two verification programs under `TESTLER/NIHAI_EK/`.

CTCPU is a processor idea I have been working on, which later became Hunter. I started from colour. Its smallest unit is three bits, shown as one of eight colours, and a number can also be kept in a second "shadow" form made of prime exponents. The machine tries to calculate the way a person does: it factors, keeps the symbol, and opens it only at the end. There is no chip and no measured speed or energy result. This is a record of work in progress, not a finished processor.

## Where to start

| Document | What it covers |
|---|---|
| [In simple words](pdf/IN_SIMPLE_WORDS.pdf) ([Markdown](IN_SIMPLE_WORDS.md)) | The whole idea on one page, in plain words |
| [Final Form](pdf/FINAL_FORM/CTCPU_FINAL_FORM.pdf) ([Markdown](md/FINAL_FORM/CTCPU_FINAL_FORM.md)) | The whole machine in one document: cell, colour gates, register, Resolver, multiplication, division, square root, types, core and verification |
| [CTCPU](md/CTCPU.md) | Short overview of the machine |
| [CTCPU parts](md/CTCPU_PARTS/README.md) | A separate document for each part |
| [Resolver](md/CTCPU_PARTS/Resolver/Resolver.md) | The part that turns a number into its shadow form, the working forms |
| [Resolver experiments](md/CTCPU_PARTS/Resolver/Experiments/Experiments.md) | The other forms I tried |
| [Gear model](md/CTCPU_PARTS/Resolver/Gear.md) | Resolver explained with gears |
| [ISA](md/ISA.md) | The instruction set |
| [PCCPU](pdf/CTCPU_PARTS/PCCPU/PCCPU.pdf) ([Markdown](md/CTCPU_PARTS/PCCPU/PCCPU.md)) | The separate controller I am still designing |
| [The Road So Far](pdf/THE_ROAD_SO_FAR.pdf) ([Markdown](md/THE_ROAD_SO_FAR.md)) | My research journal: what I tried, what worked, what failed |
| [Tests](TESTLER/README.md) | Tests behind the claims in the Final Form. Each folder has `TEST.md` in English, `TEST_TR.md` in Turkish and a one line command |
| [A Little Message](md/A_LITTLE_MESSAGE.md) | Why I am doing this |
| [A Note](md/NOTE.md) | On knowledge, ego and order |
| [Türkçe](tr/README.md) | The whole repository in Turkish |

I keep the main texts as Markdown in `md/` and as PDFs in the corresponding folders in `pdf/`. I use the same layout for Turkish under `tr/`. The separate Pascigon figure is PDF only. The SVG figure files are only in the Markdown trees, and `TESTLER/` is shared by both languages. In simple words sits in the root of the repository, and its PDF is in pdf/.

The separate [Pascal Mersenne Rows](https://github.com/JamesAugustus/pascal-mersenne-rows) repository contains the Mersenne row study. The journal's Pascigon figure is also available separately: [English](pdf/Pascigon.pdf) and [Turkish](tr/pdf/Pascigon.pdf).

## Run the journal tests

The 22 claims in the journal are tested by one C program. With a C99 compiler, run these commands from the repository's main folder:

```sh
cc -std=c99 -O2 -Wall -Wextra -o journal_tests journal_tests.c -lm
./journal_tests
```

No third-party library is needed. The [source code](journal_tests.c) and [expected output](TEST_OUTPUT.txt) are included. The expected summary is:

```text
HOLDS=15 | FAILS=4 | UNTESTED=3 | ERROR=0 | tests=22
```

`HOLDS` means the claim held in the tested cases. `FAILS` records a counterexample to a claim, not a broken test program. `UNTESTED` means this package cannot test the claim. `ERROR` means an implemented check did not produce its expected result. Exit code 0 means no such error occurred. It does not prove every claim in the journal.

## License and citation

The C and Python code is under the [MIT License](LICENSE). The English and Turkish text, PDFs, figures, test output and citation metadata are under [CC BY 4.0](LICENSE-CC-BY-4.0.txt), with attribution to James Augustus. These licenses do not relicense the third-party works cited. Citation details are in [CITATION.cff](CITATION.cff).

## About this work

This project started as an obsessive hobby project, turned into a curiosity, and I am still continuing it. I do it to improve myself and to share my point of view instead of keeping it to myself. My intention is to develop my skills in practice, move beyond theory and continue my research.

I am still not very comfortable with Python. I am not good at C either, and sometimes even that feels high-level to me. My coding lessons are continuing. I keep reading new books and new techniques about computers. Of course AI tools were used in this process, both for putting the documents together, fonts and page layout, and as a mentor while learning. Ten years ago, I would most likely have used Microsoft Word's ready-made templates and WordArt, and would not have spent so much time on fonts and page layout. From Times New Roman to choosing a comfortable keyboard, it is true that I have received help in this life. I could not have turned the things I wrote out by hand, in their funny and messy state, into something I could share like this. The ideas, calculations and experiments are mine. My goal is to reach the point where I can carry out these methods with just a notebook, without needing any program.

I did most of the work by hand first. The twenty pages where I looked for a square root method from a single Pythagorean triangle, the binomial expansions I worked out crosswise by hand and the notes I took on any blank paper I found are at home. Anyone who wants to see them can come and look, but they are all in rather poor condition.

I thank in advance the people I cited and everyone I could not name who contributed to this work in some way.

