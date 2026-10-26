"""Tests for the T10 channel-folding remainder sub-gate."""
from pathlib import Path
import sys
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from models import hunter_channel_fold as fold


class HunterChannelFoldTests(unittest.TestCase):
    def test_wrong_but_canonical_remainder_cannot_pass_gate(self):
        original=fold.channel_remainder
        def wrong(value,q,trace=False):
            result=original(value,q,trace)
            if value==1: result['remainder']=0
            return result
        with patch.object(fold,'channel_remainder',side_effect=wrong):
            status,counts,mismatch=fold.gate_y()
        self.assertEqual(status,'FAIL')
        self.assertEqual(mismatch['case'],'reference_mismatch')
        self.assertEqual(mismatch['value'],1)

    def test_channel_recipes_match_t10(self):
        self.assertEqual(fold.CHANNELS[3], {"width": 2, "sign": 1})
        self.assertEqual(fold.CHANNELS[7], {"width": 3, "sign": 1})
        self.assertEqual(fold.CHANNELS[5], {"width": 2, "sign": -1})
        self.assertEqual(fold.CHANNELS[17], {"width": 4, "sign": -1})
        self.assertEqual(fold.CHANNELS[11], {"width": 5, "sign": -1})
        self.assertEqual(fold.CHANNELS[13], {"width": 6, "sign": -1})

    def test_boundaries_and_examples_match_mod_oracle(self):
        for q in fold.CHANNELS:
            for value in (0, 1, q - 1, q, q + 1, 255, 4096, fold.MAX_INPUT):
                result = fold.channel_remainder(value, q, trace=True)
                self.assertEqual(result["remainder"], value % q)
                self.assertGreaterEqual(result["folds"], 0)
                self.assertGreaterEqual(result["canonical_subtractions"], 0)
                self.assertGreaterEqual(result["canonical_additions"], 0)

    def test_full_16_bit_scan_matches_mod_oracle(self):
        for q in fold.CHANNELS:
            for value in range(fold.MAX_INPUT + 1):
                self.assertEqual(fold.channel_remainder(value, q)["remainder"], value % q)

    def test_invalid_inputs(self):
        for args, error in (
            ((-1, 3), ValueError),
            ((fold.MAX_INPUT + 1, 3), ValueError),
            ((0, 31), ValueError),
            ((True, 3), TypeError),
            ((0, True), TypeError),
        ):
            with self.subTest(args=args):
                with self.assertRaises(error):
                    fold.channel_remainder(*args)

    def test_trace_shrinks_and_preserves_congruence(self):
        for q in fold.CHANNELS:
            recipe = fold.CHANNELS[q]
            width = recipe["width"]
            sign = recipe["sign"]
            mask = (1 << width) - 1
            result = fold.channel_remainder(fold.MAX_INPUT, q, trace=True)
            previous_abs = fold.MAX_INPUT
            for step in result["trace"]:
                after = step["after"]
                expected_after = step["low"] + sign * step["high"]
                if step["before"] < 0:
                    expected_after = -expected_after
                self.assertLessEqual(abs(after), previous_abs)
                self.assertEqual(expected_after, after)
                self.assertEqual(after % q, step["before"] % q)
                previous_abs = abs(after)
            self.assertLessEqual(previous_abs, mask)

    def test_gate_y_counts_are_exact(self):
        status, counts, mismatch = fold.gate_y()
        self.assertEqual((status, mismatch), ("PASS", None))
        self.assertEqual(counts["tests"], 6 * 65536)
        self.assertEqual(counts["invalid"], 5)
        self.assertGreater(counts["folds"], counts["tests"])
        self.assertGreater(counts["canonical_subtractions"], 0)
        self.assertGreater(counts["canonical_additions"], 0)


if __name__ == "__main__":
    unittest.main()
