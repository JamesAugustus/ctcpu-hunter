# PCCPU documents

James Augustus

This section brings together the PCCPU design, the working C cell model and a proposed symmetric thread/RAM record. The mathematical connection is Pascal coefficient symmetry and the carry-free row bound N(p) in a Mersenne base.


| Document | Markdown | PDF |
|---|---|---|
| PCCPU design, N(p) and symmetric threads | [Text](PCCPU.md) | [PDF](../../../pdf/CTCPU_PARTS/PCCPU/PCCPU.pdf) |
| Step-by-step C test explanation (Turkish) | [Text](../../../tr/md/CTCPU_PARCALAR/PCCPU/PCCPU_C_TESTI_ACIKLAMA.md) | [PDF](../../../tr/pdf/CTCPU_PARCALAR/PCCPU/PCCPU_C_TESTI_ACIKLAMA.pdf) |
| Results from a fresh test run | [Results](TEST_RESULTS.md) | Raw output is linked below |

The [C source](../../../kod/PCCPU/pccpu_address_model.c), [runner](../../../kod/PCCPU/calistir.sh) and [raw test output](../../../kod/PCCPU/TEST_OUTPUT.txt) share one code directory.

From the repository root:

```sh
bash kod/PCCPU/calistir.sh
```

The working model implements two producers, an adder and controller state. A RAM record holding two symmetric positions per thread remains a design proposal. The current tests do not validate an implementation of that proposal.

[CTCPU parts](../README.md) | [Türkçe](../../../tr/md/CTCPU_PARCALAR/PCCPU/README.md)

## CTMemTensor and addressing alternatives

[CTMemTensor](../CTMemTensor/CTMemTensor.md) is a separate CTCPU part concerned with values and positions. Centre-based reading gives N(9,0) = 126 and addresses -2,-1,0,+1,+2 for [1,4,6,4,1]. C(9,4) in the PCCPU example uses a classical binomial column. The earlier edge-based thread example remains one of the alternatives.
