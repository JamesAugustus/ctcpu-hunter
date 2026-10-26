"""Gate modelini bağımsız Python tamsayı sonuçlarıyla sınar; dosya yazmaz."""

import itertools
import unittest

import gate_model as gate


class GateModelTests(unittest.TestCase):
    def assert_normalization(self, coefficients, base):
        # Modelin Horner okuyucusundan bağımsız ağırlıklı toplam.
        expected = sum(c * base ** i for i, c in enumerate(coefficients))
        original = list(coefficients)
        result = gate.normalize(coefficients, base)
        self.assertEqual(list(coefficients), original, "girdi bandı değişmemeli")
        self.assertEqual(gate.evaluate(coefficients, base), expected)
        self.assertEqual(result["value"], expected)
        digits = result["digits_lsb"]
        self.assertIsInstance(digits, list)
        self.assertTrue(digits)
        self.assertTrue(all(type(d) is int and 0 <= d < base for d in digits))
        self.assertEqual(sum(d * base ** i for i, d in enumerate(digits)), expected)
        if expected == 0:
            self.assertEqual(digits, [0])
        elif len(digits) > 1:
            self.assertNotEqual(digits[-1], 0)

        carry, written = 0, 0
        self.assertGreaterEqual(len(result["steps"]), len(coefficients))
        for index, step in enumerate(result["steps"]):
            coefficient = coefficients[index] if index < len(coefficients) else 0
            self.assertEqual(step["index"], index)
            self.assertEqual(step["coefficient"], coefficient)
            self.assertEqual(step["carry_in"], carry)
            self.assertEqual(step["total"], coefficient + carry)
            self.assertTrue(0 <= step["digit"] < base)
            self.assertGreaterEqual(step["carry_out"], 0)
            self.assertEqual(step["total"], step["digit"] + base * step["carry_out"])
            written += step["digit"] * base ** index
            carry = step["carry_out"]
            remaining = sum(c * base ** j for j, c in enumerate(coefficients) if j > index)
            # Her STEP: yazılmış düşük haneler + carry + okunmamış sütunlar.
            self.assertEqual(written + carry * base ** (index + 1) + remaining, expected)
        self.assertEqual(carry, 0)
        self.assertEqual(written, expected)
        return result

    def test_all_256_byte_squares_and_raw_coefficients(self):
        for value in range(256):
            with self.subTest(value=value):
                word = format(value, "08b")
                result = gate.square_bits(word)
                self.assertEqual(result["value"], value * value)
                self.assertEqual(result["bit_pair_products"], 64)
                self.assertEqual(len(result["coefficients_lsb"]), 15)

                # Her ikilik bit bir onaltılık haneye yayılır. Karede sütun başına
                # en çok sekiz katkı olduğundan taban 16 içinde carry oluşmaz.
                # Böylece yerel iç içe bit döngüsünden bağımsız ham katsayı oracle'ı çıkar.
                packed = sum(int(bit) * 16 ** i for i, bit in enumerate(reversed(word)))
                packed_square = packed * packed
                coefficients = [(packed_square // 16 ** i) % 16 for i in range(15)]
                self.assertEqual(result["coefficients_lsb"], coefficients)
                normalized = self.assert_normalization(coefficients, 2)
                self.assertEqual(result["digits_lsb"], normalized["digits_lsb"])
                self.assertEqual(result["steps"], normalized["steps"])

    def test_all_short_words_payloads_and_right_side_cuts(self):
        visited = 0
        for width in range(1, 5):
            for source in range(2 ** width):
                word = format(source, f"0{width}b")
                for payload_width in range(5):
                    for inserted in range(2 ** payload_width):
                        payload = format(inserted, f"0{payload_width}b") if payload_width else ""
                        for cut in range(width + 1):
                            split = width - cut
                            # Bağımsız oracle, bit aritmetiği yerine metinde araya ekler.
                            expected_word = word[:split] + payload + word[split:]
                            result = gate.insert_bits(word, payload, cut)
                            self.assertEqual(result["word"], expected_word)
                            self.assertEqual(result["value"], int(expected_word, 2))
                            self.assertEqual(result["left"], int(word[:split] or "0", 2))
                            self.assertEqual(result["right"], int(word[split:] or "0", 2))
                            self.assertEqual(result["cut"], cut)
                            self.assertEqual(result["payload_width"], payload_width)
                            self.assertEqual(len(result["word"]), width + payload_width)
                            visited += 1
        self.assertEqual(visited, 3968)

    def test_two_square_traces_and_multioperand_carry(self):
        first = gate.square_bits("101")
        self.assertEqual(first["coefficients_lsb"], [1, 0, 2, 0, 1])
        self.assertEqual(first["digits_lsb"], [1, 0, 0, 1, 1])
        self.assertEqual(first["value"], 25)
        self.assertEqual(first["bit_pair_products"], 9)
        self.assertEqual([s["carry_out"] for s in first["steps"]], [0, 0, 1, 0, 0])

        second = gate.square_bits("111")
        self.assertEqual(second["coefficients_lsb"], [1, 2, 3, 2, 1])
        self.assertEqual(second["digits_lsb"], [1, 0, 0, 0, 1, 1])
        self.assertEqual(second["value"], 49)
        self.assertEqual(second["bit_pair_products"], 9)
        self.assertEqual([s["total"] for s in second["steps"]], [1, 2, 4, 4, 3, 1])
        self.assertEqual([s["carry_out"] for s in second["steps"]], [0, 1, 2, 2, 1, 0])
        self.assertEqual(len(second["steps"]), 6)

    def test_raw_coefficients_keep_value_at_every_normalization_step(self):
        visited = 0
        for base in range(2, 8):
            for width in range(1, 5):
                for coefficients in itertools.product(range(5), repeat=width):
                    self.assert_normalization(coefficients, base)
                    visited += 1
        self.assertEqual(visited, 4680)
        # Katsayılar rakam değildir: tabandan büyük değer ve geniş carry geçerlidir.
        for coefficients, base in [([0, 37, 0], 2), ([99, 0, 65], 10), ([2 ** 100, 0, 3], 257)]:
            self.assert_normalization(coefficients, base)

    def test_base_walk_fixed_numeric_prefix_and_same_weight_distinction(self):
        self.assertEqual([gate.evaluate([1, 2, 1], base) for base in [2, 3, 4]], [9, 16, 25])
        self.assertEqual(gate.normalize([1, 2, 1], 2)["digits_lsb"], [1, 0, 0, 1])
        self.assertEqual(gate.normalize([1, 2, 1], 3)["digits_lsb"], [1, 2, 1])
        self.assertEqual(gate.append_prefix(24, 0, 2), 48)
        self.assertEqual(gate.append_prefix(24, 1, 2), 49)
        self.assertEqual([gate.append_prefix(24, 1, base) for base in [2, 3, 4]], [49, 73, 97])
        self.assertEqual(gate.evaluate([2], 2), 2, "aynı ağırlıkta iki katkı")
        self.assertEqual(gate.evaluate([1, 1], 2), 3, "iki farklı konumsal ağırlık")
        self.assertEqual(gate.append_prefix(2 ** 100, 256, 257), 2 ** 100 * 257 + 256)
        # Ham 121 bandında orta 2 katsayısı kabul edilir; tek ikilik rakam olarak 2 reddedilir.
        with self.assertRaises(ValueError):
            gate.append_prefix(1, 2, 2)

    def test_leading_zero_width_empty_payload_and_maximum_insertion(self):
        self.assertEqual(gate.insert_bits("11", "00", 1)["word"], "1001")
        self.assertEqual(gate.insert_bits("11", "00", 1)["value"], 9)
        self.assertEqual(gate.insert_bits("11", "00", 0)["word"], "1100")
        self.assertEqual(gate.insert_bits("11", "00", 2)["word"], "0011")
        for word in ["0", "00", "00000000", "00000101", "11111111"]:
            for cut in range(len(word) + 1):
                self.assertEqual(gate.insert_bits(word, "", cut)["word"], word)
        widest = gate.insert_bits("11111111", "11111111", 4)
        self.assertEqual(widest["word"], "1" * 16)
        self.assertEqual(widest["value"], 65535)
        zero = gate.normalize([0, 0, 0], 2)
        self.assertEqual(zero["digits_lsb"], [0])
        self.assertEqual(len(zero["steps"]), 3, "kaynak sütunları izde korunur")
        self.assertEqual(gate.normalize([1, 0, 0], 2)["digits_lsb"], [1])
        narrow, padded = gate.square_bits("1"), gate.square_bits("00000001")
        self.assertEqual(narrow["value"], padded["value"])
        self.assertEqual(narrow["bit_pair_products"], 1)
        self.assertEqual(padded["bit_pair_products"], 64)

    def test_invalid_bit_words_payloads_and_cuts_raise_value_error(self):
        bad_words = [None, True, False, 1, [], b"01", "", "2", "10x", "101010101", "-1", " 01", "01 "]
        for word in bad_words:
            with self.subTest(word=word):
                with self.assertRaises(ValueError):
                    gate.insert_bits(word, "0", 0)
                with self.assertRaises(ValueError):
                    gate.square_bits(word)
        for payload in [None, True, False, 0, [], b"0", "2", "0 1", "111111111"]:
            with self.subTest(payload=payload):
                with self.assertRaises(ValueError):
                    gate.insert_bits("11", payload, 1)
        for cut in [True, False, -1, 3, 1.5, "1", None]:
            with self.subTest(cut=cut):
                with self.assertRaises(ValueError):
                    gate.insert_bits("11", "0", cut)

    def test_invalid_arithmetic_types_bases_and_digits_raise_value_error(self):
        for coefficients in [None, [], (), "101", {0: 1}, [True], [False], [-1], [0.5], [1, "2"], [None]]:
            with self.subTest(coefficients=coefficients):
                with self.assertRaises(ValueError):
                    gate.evaluate(coefficients, 2)
                with self.assertRaises(ValueError):
                    gate.normalize(coefficients, 2)
        for base in [True, False, -1, 0, 1, 2.5, "2", None]:
            with self.subTest(base=base):
                with self.assertRaises(ValueError):
                    gate.evaluate([1], base)
                with self.assertRaises(ValueError):
                    gate.normalize([1], base)
                with self.assertRaises(ValueError):
                    gate.append_prefix(1, 0, base)
        for prefix in [True, False, -1, 0.5, "1", None]:
            with self.subTest(prefix=prefix):
                with self.assertRaises(ValueError):
                    gate.append_prefix(prefix, 0, 2)
        for digit in [True, False, -1, 2, 0.5, "1", None]:
            with self.subTest(digit=digit):
                with self.assertRaises(ValueError):
                    gate.append_prefix(1, digit, 2)


if __name__ == "__main__":
    unittest.main(verbosity=2)
