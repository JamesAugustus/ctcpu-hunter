"""Small T10 channel-folding remainder sub-gate.

The runtime folding path avoids %, /, // and pow.  Tests use ordinary modular
arithmetic as the independent oracle.
"""

from __future__ import annotations


PASS = "PASS"
FAIL = "FAIL"
ACIK = "ACIK"
MAX_INPUT = 65535
CHANNELS = {
    3: {"width": 2, "sign": 1},
    7: {"width": 3, "sign": 1},
    5: {"width": 2, "sign": -1},
    17: {"width": 4, "sign": -1},
    11: {"width": 5, "sign": -1},
    13: {"width": 6, "sign": -1},
}


def _is_int(value):
    return type(value) is int


def _validate_input(value, q):
    if not _is_int(value):
        raise TypeError("value must be an int")
    if not _is_int(q):
        raise TypeError("q must be an int")
    if value < 0 or value > MAX_INPUT:
        raise ValueError("value must be in 0..65535")
    if q not in CHANNELS:
        raise ValueError("unsupported channel")


def _canonicalize(value, q):
    subtractions = 0
    additions = 0
    while value >= q:
        value -= q
        subtractions += 1
    while value < 0:
        value += q
        additions += 1
    return value, subtractions, additions


def channel_remainder(value, q, trace=False):
    """Return value mod q using the T10 fold recipe for this small channel."""
    _validate_input(value, q)
    recipe = CHANNELS[q]
    width = recipe["width"]
    sign = recipe["sign"]
    mask = (1 << width) - 1
    signed = value
    negative = False
    steps = []
    folds = 0
    canonical_subtractions = 0
    canonical_additions = 0

    while signed > mask or signed < -mask:
        before = signed
        if signed < 0:
            negative = True
            word = -signed
        else:
            negative = False
            word = signed
        low = word & mask
        high = word >> width
        folded = low + sign * high
        signed = -folded if negative else folded
        folds += 1
        if trace:
            steps.append(
                {
                    "before": before,
                    "low": low,
                    "high": high,
                    "after": signed,
                }
            )

    remainder, subtractions, additions = _canonicalize(signed, q)
    canonical_subtractions += subtractions
    canonical_additions += additions
    result = {
        "remainder": remainder,
        "folds": folds,
        "canonical_subtractions": canonical_subtractions,
        "canonical_additions": canonical_additions,
    }
    if trace:
        result["trace"] = tuple(steps)
    return result


def gate_y():
    counts = {
        "tests": 0,
        "folds": 0,
        "canonical_subtractions": 0,
        "canonical_additions": 0,
        "invalid": 0,
        "reference_checks": 0,
        "fold_invariant_checks": 0,
    }
    try:
        for q in CHANNELS:
            for value in range(MAX_INPUT + 1):
                result = channel_remainder(value, q, trace=True)
                counts["tests"] += 1
                counts["folds"] += result["folds"]
                counts["canonical_subtractions"] += result["canonical_subtractions"]
                counts["canonical_additions"] += result["canonical_additions"]
                counts['reference_checks'] += 1
                if result['remainder'] != value % q:
                    return FAIL, counts, {'case':'reference_mismatch','q':q,'value':value,'result':result}
                for step in result['trace']:
                    counts['fold_invariant_checks'] += 1
                    if step['before'] % q != step['after'] % q or abs(step['after']) >= abs(step['before']):
                        return FAIL, counts, {'case':'fold_invariant','q':q,'value':value,'step':step}
                if not 0 <= result["remainder"] < q:
                    return FAIL, counts, {"case": "noncanonical", "q": q, "value": value, "result": result}
        for args in ((-1, 3), (MAX_INPUT + 1, 3), (0, 31), (True, 3), (0, True)):
            try:
                channel_remainder(*args)
            except (TypeError, ValueError):
                counts["invalid"] += 1
            else:
                return FAIL, counts, {"case": "invalid_accepted", "args": args}
        return PASS, counts, None
    except Exception as exc:
        return FAIL, counts, {"case": "exception", "error": repr(exc)}


EXPORTED_FUNCTIONS = (
    "MAX_INPUT",
    "CHANNELS",
    "channel_remainder",
    "gate_y",
)


if __name__ == "__main__":
    print("gate_y", gate_y())
