/* Tests for the research journal "CTCPU and Hunter: The Road So Far" (THE_ROAD_SO_FAR.md; Turkish: tr/YOL.md). Author: James Augustus. October 2026. License: MIT. */
/* Build: cc -std=c99 -O2 -o journal_tests journal_tests.c -lm && ./journal_tests */
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

static int failures = 0;
static unsigned counts[4];
static void print_result(const char *name, const char *status,
                         const char *result, const char *range);

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t m) {
    return a >= m - b ? a - (m - b) : a + b;
}

static uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t result = 0;
    if (m == 0) return 0;
    a %= m;
    while (b != 0) {
        if (b & 1U) result = add_mod(result, a, m);
        b >>= 1;
        if (b != 0) a = add_mod(a, a, m);
    }
    return result;
}

static void fail_card(const char *name, const char *reason, const char *range) {
    ++failures;
    print_result(name, "ERROR", reason, range);
}

static int is_prime(uint64_t n) {
    uint64_t d;
    if (n < 2) return 0;
    if (n % 2 == 0) return n == 2;
    for (d = 3; d <= n / d; d += 2) {
        if (n % d == 0) return 0;
    }
    return 1;
}

static uint64_t mod_pow(uint64_t a, uint64_t e, uint64_t m) {
    uint64_t result = 1;
    if (m == 0) return 0;
    a %= m;
    while (e != 0) {
        if (e & 1U) result = mul_mod(result, a, m);
        a = mul_mod(a, a, m);
        e >>= 1;
    }
    return result;
}

static uint64_t choose_u64(unsigned n, unsigned k) {
    uint64_t x = 1;
    unsigned i;
    if (k > n - k) k = n - k;
    for (i = 1; i <= k; ++i) x = x * (n - k + i) / i;
    return x;
}

#define BIGL 40
typedef struct { unsigned n; uint32_t d[BIGL]; } big_num;

static void big_num_set(big_num *x, uint64_t value) {
    x->n = 0;
    while (value != 0 && x->n < BIGL) {
        x->d[x->n++] = (uint32_t)(value % UINT32_C(1000000000));
        value /= UINT32_C(1000000000);
    }
    if (x->n == 0) x->d[x->n++] = 0;
}

static int big_num_mul(big_num *x, uint64_t factor) {
    uint64_t carry = 0;
    unsigned i;
    for (i = 0; i < x->n; ++i) {
        uint64_t value = (uint64_t)x->d[i] * factor + carry;
        x->d[i] = (uint32_t)(value % UINT32_C(1000000000));
        carry = value / UINT32_C(1000000000);
    }
    while (carry != 0) {
        if (x->n == BIGL) return 0;
        x->d[x->n++] = (uint32_t)(carry % UINT32_C(1000000000));
        carry /= UINT32_C(1000000000);
    }
    return 1;
}

static int big_num_div(big_num *x, uint64_t divisor, uint64_t *remainder) {
    uint64_t r = 0;
    unsigned i = x->n;
    if (divisor == 0 || divisor > UINT64_MAX / UINT32_C(1000000000)) return 0;
    while (i > 0) {
        uint64_t value;
        --i;
        value = r * UINT32_C(1000000000) + x->d[i];
        x->d[i] = (uint32_t)(value / divisor);
        r = value % divisor;
    }
    while (x->n > 1 && x->d[x->n - 1] == 0) --x->n;
    *remainder = r;
    return 1;
}

static int digits_u64(uint64_t value, unsigned base, uint64_t *digits, unsigned *length) {
    *length = 0;
    do {
        if (*length == 64 || base < 2) return 0;
        digits[(*length)++] = value % base;
        value /= base;
    } while (value != 0);
    return 1;
}

static int digits_big(big_num value, uint64_t base, uint64_t *digits, unsigned *length) {
    *length = 0;
    do {
        uint64_t rem;
        if (*length == 64 || !big_num_div(&value, base, &rem)) return 0;
        digits[(*length)++] = rem;
    } while (!(value.n == 1 && value.d[0] == 0));
    return 1;
}

static void print_result(const char *name, const char *status,
                         const char *result, const char *range) {
    if (status[0] == 'H') ++counts[0];
    else if (status[0] == 'F') ++counts[1];
    else if (status[0] == 'U') ++counts[2];
    else if (status[0] == 'E') ++counts[3];
    printf("%s | %s | %s | %s\n", name, status, result, range);
}

static void T01_d101_family(void) {
    unsigned p, k, count = 0;
    for (p = 3; p <= 31; p += 2) {
        uint64_t m;
        if (!is_prime(p)) continue;
        m = (UINT64_C(1) << p) - 1;
        for (k = 0; k < 4; ++k) {
            uint64_t d = UINT64_C(3) * (UINT64_C(1) << (p - 3)) - 1 + (uint64_t)k * m;
            if (8 * d + 5 != (uint64_t)(3 + 8 * k) * m) {
                fail_card("T01_d101_family", "equality broken", "prime p=3..31, k=0..3");
                return;
            }
            ++count;
        }
    }
    { char result[80]; snprintf(result, sizeof result, "%u equalities correct", count); print_result("T01_d101_family", "HOLDS", result, "prime p=3..31, k=0..3"); }
}

static void T02_mersenne_mod8(void) {
    unsigned p, count = 0;
    for (p = 3; p < 80; ++p) {
        unsigned i;
        uint64_t power = 1;
        for (i = 0; i < p; ++i) power = (power * 2U) % 8U;
        if ((power + 7U) % 8U != 7U) {
            fail_card("T02_mersenne_mod8", "mod 8 condition broken", "p=3..79");
            return;
        }
        ++count;
    }
    { char result[80]; snprintf(result, sizeof result, "correct for %u exponents", count); print_result("T02_mersenne_mod8", "HOLDS", result, "p=3..79"); }
}

static void T03_factor_law(void) {
    unsigned p, count = 0;
    for (p = 3; p <= 31; p += 2) {
        uint64_t m, n, d;
        if (!is_prime(p)) continue;
        m = (UINT64_C(1) << p) - 1;
        n = m;
        for (d = 2; d <= n / d; ++d) {
            if (n % d == 0) {
                uint64_t q = d;
                if (is_prime(q)) {
                    if ((q - 1) % (2U * p) != 0 || (q % 8 != 1 && q % 8 != 7)) {
                        fail_card("T03_factor_law", "counterexample found", "prime p=3..31");
                        return;
                    }
                    ++count;
                }
                while (n % d == 0) n /= d;
            }
        }
        if (n > 1 && is_prime(n)) {
            if ((n - 1) % (2U * p) != 0 || (n % 8 != 1 && n % 8 != 7)) {
                fail_card("T03_factor_law", "counterexample found", "prime p=3..31");
                return;
            }
            ++count;
        }
    }
    { char result[100]; snprintf(result, sizeof result, "%u prime factors satisfy the condition", count); print_result("T03_factor_law", "HOLDS", result, "prime p=3..31"); }
}

static void T04_euler_2p_plus1(void) {
    unsigned p, count = 0;
    for (p = 3; p < 100; ++p) {
        uint64_t q, m_mod_q;
        if (!is_prime(p) || p % 4 != 3) continue;
        q = 2U * p + 1;
        if (!is_prime(q)) continue;
        if (p == 3) continue; /* q = M_3 is not a proper divisor. */
        m_mod_q = (mod_pow(2, p, q) + q - 1) % q;
        if (m_mod_q != 0) {
            fail_card("T04_euler_2p_plus1", "counterexample found", "prime p<100, p=3 mod 4");
            return;
        }
        ++count;
    }
    { char result[100]; snprintf(result, sizeof result, "%u suitable q divide M_p; for p=3, q=M_3", count); print_result("T04_euler_2p_plus1", "HOLDS", result, "prime p<100, p=3 mod 4, q<M_p"); }
}

static void T05_137_octal_head(void) {
    unsigned p, count = 0;
    for (p = 3; p <= 300; ++p) {
        uint32_t words[10] = {0};
        uint8_t octal[101];
        unsigned bit, i, length = 0, expected;
        unsigned r = p % 3;
        /* Shifting left p times and adding 1 builds 2^p - 1 in 32-bit words. */
        for (bit = 0; bit < p; ++bit) {
            uint64_t carry = 1;
            for (i = 0; i < 10; ++i) {
                uint64_t value = (uint64_t)words[i] * 2U + carry;
                words[i] = (uint32_t)value;
                carry = value >> 32;
            }
            if (carry != 0) {
                fail_card("T05_137_octal_head", "M_p word capacity exceeded", "p=3..300");
                return;
            }
        }
        /* Octal digits come from repeated division of the big integer by 8. */
        for (;;) {
            uint64_t rem = 0;
            int nonzero = 0;
            for (i = 10; i > 0; --i) {
                uint64_t current = (rem << 32) | words[i - 1];
                words[i - 1] = (uint32_t)(current / 8U);
                rem = current % 8U;
                if (words[i - 1] != 0) nonzero = 1;
            }
            if (length == sizeof octal) {
                fail_card("T05_137_octal_head", "octal digit capacity exceeded", "p=3..300");
                return;
            }
            octal[length++] = (uint8_t)rem;
            if (!nonzero) break;
        }
        expected = r == 0 ? 7U : ((1U << r) - 1U);
        if (length != (p + 2U) / 3U || octal[length - 1] != expected) {
            fail_card("T05_137_octal_head", "octal head digit or length broken", "p=3..300");
            return;
        }
        for (i = 0; i + 1 < length; ++i) {
            if (octal[i] != 7U) {
                fail_card("T05_137_octal_head", "octal tail digits broken", "p=3..300");
                return;
            }
        }
        if (length == 0) {
            fail_card("T05_137_octal_head", "empty octal representation", "p=3..300");
            return;
        }
        ++count;
    }
    { char result[80]; snprintf(result, sizeof result, "%u/%u forms correct", count, count); print_result("T05_137_octal_head", "HOLDS", result, "p=3..300"); }
}

static void T06_head_digit_primality_degil(void) {
    const uint64_t m11 = (UINT64_C(1) << 11) - 1;
    const uint64_t m5 = (UINT64_C(1) << 5) - 1;
    uint64_t d11[64], d5[64];
    unsigned n11, n5;
    if (!digits_u64(m11, 8, d11, &n11) || !digits_u64(m5, 8, d5, &n5) ||
        m11 != 23U * 89U || n11 != 4 || d11[3] != 3 ||
        m5 != 31 || !is_prime(m5) || n5 != 2 || d5[1] != 3) {
        fail_card("T06_head_digit_primality", "prime and composite examples not as expected", "p=5,11");
        return;
    }
    print_result("T06_head_digit_primality", "FAILS",
                 "M_11=2047=23x89, octal 3777; M_5=31=37_8 prime, head 3", "p=5,11");
}

static void T07_pascal_11(void) {
    unsigned n, checked = 0;
    for (n = 0; n <= 4; ++n) {
        uint64_t value = 1, digits[64];
        unsigned length, k;
        for (k = 0; k < n; ++k) value *= 11U;
        if (!digits_u64(value, 10, digits, &length) || length != n + 1) {
            fail_card("T07_pascal_11", "digit count of 11^n does not match", "n=0..4");
            return;
        }
        for (k = 0; k <= n; ++k) {
            if (digits[k] != choose_u64(n, k)) {
                fail_card("T07_pascal_11", "decimal digits of 11^n are not a Pascal row", "n=0..4");
                return;
            }
        }
        ++checked;
    }
    for (n = 1; n <= 30; ++n) {
        uint64_t row[31], max = 0, base;
        unsigned k, j;
        for (k = 0; k <= n; ++k) {
            row[k] = choose_u64(n, k);
            if (row[k] > max) max = row[k];
        }
        base = max + 1;
        for (j = 0; j < 2; ++j) {
            big_num value;
            uint64_t digits[64];
            unsigned length;
            big_num_set(&value, 1);
            for (k = 0; k < n; ++k) {
                if (!big_num_mul(&value, base + j + 1)) {
                    fail_card("T07_pascal_11", "big integer capacity exceeded", "n=1..30, b=max(Pascal)+1,+2");
                    return;
                }
            }
            if (!digits_big(value, base + j, digits, &length) || length != n + 1) {
                fail_card("T07_pascal_11", "base-b digit count does not match", "n=1..30, b=max(Pascal)+1,+2");
                return;
            }
            for (k = 0; k <= n; ++k) {
                if (digits[k] != row[k]) {
                    fail_card("T07_pascal_11", "base-b digits are not a Pascal row", "n=1..30, b=max(Pascal)+1,+2");
                    return;
                }
            }
            ++checked;
        }
    }
    { char result[80]; snprintf(result, sizeof result, "%u digit checks correct", checked); print_result("T07_pascal_11", "HOLDS", result, "n=0..4; n=1..30, b=max(Pascal)+1,+2"); }
}

static void T08_threshold_law(void) {
    unsigned n, checked = 0;
    for (n = 1; n <= 15; ++n) {
        unsigned k;
        uint64_t max = 0, threshold;
        for (k = 0; k <= n; ++k) {
            uint64_t c = choose_u64(n, k);
            if (c > max) max = c;
        }
        threshold = max + 1;
        /* Every binomial coefficient fits in one digit of the base. */
        for (k = 0; k < 2; ++k) {
            uint64_t b = threshold + k;
            unsigned j;
            for (j = 0; j <= n; ++j) {
                if (choose_u64(n, j) >= b) {
                    fail_card("T08_threshold_law", "coefficient carries at the threshold", "n=1..15");
                    return;
                }
            }
            ++checked;
        }
        if (n > 1) {
            uint64_t b = threshold - 1;
            if (max < b) {
                fail_card("T08_threshold_law", "no carry one base below the threshold", "n=2..15");
                return;
            }
            ++checked;
        }
    }
    { char result[80]; snprintf(result, sizeof result, "%u base checks correct", checked); print_result("T08_threshold_law", "HOLDS", result, "n=1..15, threshold and above; n=2..15 one below threshold"); }
}

static void T09_11_base_value(void) {
    unsigned b;
    for (b = 2; b <= 100; ++b) {
        const unsigned numeral[2] = {1, 1};
        unsigned value = 0, i;
        uint64_t square = (uint64_t)(b + 1) * (b + 1), digits[64];
        unsigned length;
        for (i = 0; i < 2; ++i) value = value * b + numeral[i];
        if (value != b + 1) {
            fail_card("T09_11_base_value", "11 in base b is not b + 1", "b=2..100");
            return;
        }
        if (b >= 3 && (!digits_u64(square, b, digits, &length) || length != 3 ||
                       digits[0] != 1 || digits[1] != 2 || digits[2] != 1)) {
            fail_card("T09_11_base_value", "digits of (b+1)^2 are not 121 in base b", "b=3..100");
            return;
        }
    }
    print_result("T09_11_base_value", "HOLDS", "99 bases and 98 squares correct", "b=2..100; squares b=3..100");
}

static void T10_square_seal(void) {
    const unsigned exponents[] = {3, 5, 7, 11, 13};
    uint64_t pre_square_11 = 0, final_11 = 0;
    unsigned i;
    for (i = 0; i < sizeof exponents / sizeof exponents[0]; ++i) {
        unsigned p = exponents[i], step;
        uint64_t m = (UINT64_C(1) << p) - 1, state = 4, square = 0;
        for (step = 0; step < p - 2; ++step) {
            square = mul_mod(state, state, m);
            state = (square + m - 2) % m;
        }
        if (p == 11) { pre_square_11 = square; final_11 = state; }
        if (p != 11 && (!is_prime(m) || state != 0 || square != 2)) {
            fail_card("T10_square_seal", "small LL trace for prime M_p not as expected", "p=3,5,7,11,13");
            return;
        }
        if (p == 11 && (is_prime(m) || state == 0 || square == 2)) {
            fail_card("T10_square_seal", "LL trace for composite M_11 not as expected", "p=3,5,7,11,13");
            return;
        }
    }
    if (pre_square_11 != 1738 || final_11 != 1736 ||
        mul_mod(64, 64, (UINT64_C(1) << 11) - 1) != 2) {
        fail_card("T10_square_seal", "M_11 comparison does not match", "p=11");
        return;
    }
    print_result("T10_square_seal", "UNTESTED",
                 "LL p=3,5,7,13 final residue 0; M_11: s8^2=1738, final residue 1736; 64^2 mod M_11=2; seal criterion undefined",
                 "small p=3,5,7,11,13");
}

static void T11_packed_sieve(void) {
    const uint64_t m = (UINT64_C(1) << 41) - 1;
    const uint64_t q = 13367;
    unsigned k;
    int represented = 0;
    for (k = 1; k <= 64; ++k) if (q == 2U * k * 41U + 1U) represented = 1;
    if (m % q == 0 && is_prime(q) && !represented) {
        print_result("T11_packed_sieve", "FAILS", "M_41 composite: 13367 | M_41 with k=163; a k<=64 filter misses it", "p=41, q=13367, k<=64");
    } else {
        fail_card("T11_packed_sieve", "known miss not confirmed", "p=41, k=1..64");
    }
}

static void T12_digit_flow(void) {
    uint32_t n;
    unsigned p, checks = 0;
    for (n = 0; n < (UINT32_C(1) << 15); ++n) {
        unsigned digits[16], len = 0;
        uint32_t x = n;
        if (x == 0) digits[len++] = 0;
        while (x != 0) {
            digits[len++] = x % 8U;
            x /= 8U;
        }
        for (p = 3; p <= 17; ++p) {
            uint32_t rem = 0;
            unsigned i = len;
            while (i > 0) {
                --i;
                rem = (8U * rem + digits[i]) % p;
            }
            if (rem != n % p) {
                fail_card("T12_digit_flow", "remainder equality broken", "n=0..32767, p=3..17");
                return;
            }
            ++checks;
        }
    }
    { char result[100]; snprintf(result, sizeof result, "%u remainder equalities correct", checks); print_result("T12_digit_flow", "HOLDS", result, "n=0..32767, p=3..17"); }
}

static void factor_vector(unsigned n, unsigned primes[32], unsigned exps[32], unsigned *len) {
    unsigned d;
    *len = 0;
    for (d = 2; d * d <= n; ++d) {
        if (n % d == 0) {
            unsigned e = 0;
            while (n % d == 0) { n /= d; ++e; }
            primes[*len] = d;
            exps[*len] = e;
            ++*len;
        }
    }
    if (n > 1) { primes[*len] = n; exps[*len] = 1; ++*len; }
}

static void T13_shadow_vector(void) {
    unsigned a, b, checks = 0;
    for (a = 1; a <= 64; ++a) {
        for (b = 1; b <= 64; ++b) {
            unsigned ap[32], ae[32], bp[32], be[32], cp[32], ce[32], al, bl, cl, i, j;
            factor_vector(a, ap, ae, &al);
            factor_vector(b, bp, be, &bl);
            factor_vector(a * b, cp, ce, &cl);
            for (i = 0; i < al; ++i) {
                unsigned e = ae[i];
                for (j = 0; j < bl; ++j) if (bp[j] == ap[i]) e += be[j];
                for (j = 0; j < cl && cp[j] != ap[i]; ++j) { }
                if (j == cl || ce[j] != e) {
                    fail_card("T13_shadow_vector", "vector(a*b) != vector(a)+vector(b)", "a,b=1..64");
                    return;
                }
            }
            for (j = 0; j < bl; ++j) {
                int in_a = 0;
                for (i = 0; i < al; ++i) if (ap[i] == bp[j]) in_a = 1;
                if (!in_a) {
                    unsigned k;
                    for (k = 0; k < cl && cp[k] != bp[j]; ++k) { }
                    if (k == cl || ce[k] != be[j]) {
                        fail_card("T13_shadow_vector", "vector(a*b) != vector(a)+vector(b)", "a,b=1..64");
                        return;
                    }
                }
            }
            ++checks;
        }
    }
    { char result[80]; snprintf(result, sizeof result, "%u vector comparisons correct", checks); print_result("T13_shadow_vector", "HOLDS", result, "a,b=1..64"); }
}

static void T14_quadratic_generator(void) {
    const unsigned m = 3, k = 3;
    const unsigned value = m * m + 10U * m + k;
    if (value != 42 || value % 2 != 0 || value / 2 != 21) {
        fail_card("T14_quadratic_generator", "factor check for 42 failed", "M=3, k=3");
        return;
    }
    print_result("T14_quadratic_generator", "FAILS", "M=3, k=3: computed 42=2x21", "M=3, k=3");
}

static void T15_reverse_p_general(void) {
    const unsigned p = 19, reverse = 91, a = 7, b = 13;
    if (reverse != 10U * (p % 10U) + p / 10U || a * b != reverse) {
        fail_card("T15_reverse_p_general", "counterexample 19 -> 91 could not be computed", "p=19");
        return;
    }
    print_result("T15_reverse_p_general", "FAILS", "counterexample 19 -> 91 = 7 x 13", "p=19");
}

static void T17_signature_filter(void) {
    /* Membership of an exponent in the first 50 exponents is not a signature
       test. The historical signature function and fixed set are not included. */
    print_result("T17_signature_filter", "UNTESTED",
                 "historical signature function and fixed set are not included; raw exponent membership is not a signature test",
                 "historical claim for exponents #51 and #52");
}

static uint64_t pascal_mid(unsigned n) {
    uint64_t row[62] = {1};
    unsigned i, j;
    for (i = 1; i <= n; ++i)
        for (j = i; j > 0; --j) row[j] += row[j - 1];
    return row[n / 2];
}

static uint64_t pascal_neighbor(unsigned n) {
    uint64_t row[62] = {1};
    unsigned i, j;
    unsigned d = n & 1U;
    int k = ((int)n - 2 + (int)d) / 2;
    for (i = 1; i <= n; ++i)
        for (j = i; j > 0; --j) row[j] += row[j - 1];
    return k < 0 ? 0 : row[(unsigned)k];
}

static void T18_ladder_step(void) {
    uint64_t a = 3;
    unsigned n;
    for (n = 0; n <= 60; ++n) {
        uint64_t expected = pascal_mid(n) + 2;
        if (a != expected) {
            fail_card("T18_ladder_step", "atom recurrence does not match the middle coefficient", "n=0..60");
            return;
        }
        a += pascal_neighbor(n);
    }
    if (a != pascal_mid(61) + 2) {
        fail_card("T18_ladder_step", "atom 61 does not match the expected middle coefficient", "n=0..60");
        return;
    }
    print_result("T18_ladder_step", "HOLDS", "a_(n+1)=a_n+kom_n matches the middle coefficients", "n=0..60, uint64_t");
}

static void T19_base_difference(void) {
    unsigned n;
    for (n = 1; n <= 60; ++n) {
        uint64_t lhs = pascal_mid(n) - pascal_mid(n - 1);
        uint64_t rhs = pascal_neighbor(n - 1);
        if (lhs != rhs) {
            fail_card("T19_base_difference", "base difference does not match the neighbour coefficient", "n=1..60");
            return;
        }
    }
    print_result("T19_base_difference", "HOLDS", "base difference equals the neighbour coefficient", "n=1..60, uint64_t");
}

static void T20_middle_by_addition(void) {
    /* Make the given number the bound of the middle: base B = N + 1, B + 1 is raised to n.
       Build each row from the outer 1s towards the middle by addition only, then mirror.
       If every entry is below B, the row is the base-B digit string of (B + 1)^n
       (binomial theorem); this is also checked by Horner's rule modulo three primes. */
    const uint64_t N = UINT64_C(26321361382), B = N + 1;
    const uint64_t mods[3] = { UINT64_C(1000000007), UINT64_C(998244353), UINT64_C(4294967291) };
    uint64_t row[64], next[64];
    unsigned n, k, m, last_clean = 0;
    row[0] = 1;
    for (n = 0; n <= 40; ++n) {
        int clean = 1;
        if (n > 0) {
            next[0] = 1;
            for (k = 1; k <= n / 2; ++k) next[k] = row[k - 1] + row[k];  /* addition only */
            for (k = n / 2 + 1; k <= n; ++k) next[k] = next[n - k];      /* mirror */
            for (k = 0; k <= n; ++k) row[k] = next[k];
        }
        for (k = 0; k <= n; ++k) {
            if (row[k] != choose_u64(n, k)) {
                fail_card("T20_middle_by_addition", "row built by addition does not match the binomial", "n=0..40");
                return;
            }
            if (row[k] >= B) clean = 0;
        }
        if (!clean) break;
        for (m = 0; m < 3; ++m) {
            uint64_t h = 0;
            for (k = 0; k <= n; ++k) h = add_mod(mul_mod(h, B % mods[m], mods[m]), row[k] % mods[m], mods[m]);
            if (h != mod_pow((B + 1) % mods[m], n, mods[m])) {
                fail_card("T20_middle_by_addition", "row is not the base N+1 expansion of (N+2)^n", "n=0..37");
                return;
            }
        }
        last_clean = n;
    }
    if (last_clean != 37 || n != 38) {
        fail_card("T20_middle_by_addition", "last clean row is not 37", "N=26321361382");
        return;
    }
    print_result("T20_middle_by_addition", "HOLDS", "addition from the ends + mirror, rows 0-37 clean; at 38 the middle exceeds N", "N=26321361382, B=N+1, n=0..38");
}

static uint64_t gcd_u64(uint64_t a, uint64_t b) {
    while (b != 0) { uint64_t t = a % b; a = b; b = t; }
    return a;
}

/* Next digit of the row, R * (n - k) / (k + 1), without overflow. */
static uint64_t next_digit(uint64_t R, unsigned n, unsigned k) {
    uint64_t g = gcd_u64(R, (uint64_t)k + 1);
    return (R / g) * ((n - k) / ((k + 1) / g));
}

/* Is every entry of row n below the base 2^p - 1 (is the row carry-free)? */
static int row_clean(unsigned p, unsigned n) {
    uint64_t b = (UINT64_C(1) << p) - 1, R = 1;
    unsigned k;
    for (k = 0; k <= n; ++k) {
        if (R >= b) return 0;
        R = next_digit(R, n, k);
    }
    return 1;
}

static void T21_mersenne_row(void) {
    /* Base M_p = 2^p - 1. In base M_p, 2^p is written "11", so
       2^(p(p+2)) = (2^p)^(p+2) is row p + 2 of Pascal's triangle in this base.
       Digits are produced one from the next, R -> R(n-k)/(k+1); the value is
       summed back by Horner's rule and compared with 2^(p(p+2)) modulo three primes. */
    const uint64_t mods[3] = { UINT64_C(2305843009213693951),  /* 2^61 - 1 */
                               UINT64_C(1000000007), UINT64_C(4294967291) };
    unsigned p, k, m;
    if (row_clean(5, 7)) {
        fail_card("T21_mersenne_row", "for p=5 the row is clean, a carry was expected", "p=5");
        return;
    }
    for (p = 7; p <= 61; ++p) {
        unsigned n = p + 2;
        uint64_t b = (UINT64_C(1) << p) - 1;
        if (!row_clean(p, n)) {
            fail_card("T21_mersenne_row", "a digit of row p+2 exceeds the base", "p=7..61");
            return;
        }
        for (m = 0; m < 3; ++m) {
            uint64_t h = 0, R = 1;
            for (k = 0; k <= n; ++k) {
                h = add_mod(mul_mod(h, b % mods[m], mods[m]), R % mods[m], mods[m]);
                R = next_digit(R, n, k);
            }
            if (h != mod_pow(2, (uint64_t)p * n, mods[m])) {
                fail_card("T21_mersenne_row", "value is not 2^(p(p+2))", "p=7..61");
                return;
            }
        }
        /* for p = 7..37, row p + 2 is the last row whose middle stays below the base */
        if (p <= 37 && row_clean(p, n + 1)) {
            fail_card("T21_mersenne_row", "row p+3 is clean as well", "p=7..37");
            return;
        }
        if (p == 38 && !row_clean(p, n + 1)) {
            fail_card("T21_mersenne_row", "for p=38 row p+3 is not clean", "p=38");
            return;
        }
    }
    print_result("T21_mersenne_row", "HOLDS",
                 "2^(p(p+2)) is row p+2 in base 2^p-1; p=5 carries; for p=7..37 row p+2 is the last clean row",
                 "p=7..61, uint64_t, 3 prime moduli");
}

static void T22_base3_chain(void) {
    /* value = b^n - (b^(n-1) + ... + b^m) - c = b^n - (b^n - b^m)/(b - 1) - c.
       b = 3, m = 0, c = 0: a(n) = (3^n + 1)/2, a(n+1) = 3a(n) - 1.
       Since 3^5 = 2*121 + 1, a(n) mod 121 has period 5 and a(n) is never divisible by 11. */
    unsigned b, n, m, c, count = 0;
    uint64_t a = 1, r = 1;
    static unsigned char composite[2000001];
    unsigned long q, i;
    unsigned wief = 0, found[4] = {0, 0, 0, 0};
    for (b = 2; b <= 10; ++b) {
        for (n = 1; n <= 18; ++n) {
            uint64_t bn = 1, chain_direct = 0, pw = 1;
            for (i = 0; i < n; ++i) bn *= b;
            for (m = 0; m < n; ++m) {
                uint64_t bm = 1;
                for (i = 0; i < m; ++i) bm *= b;
                chain_direct = 0; pw = bm;
                for (i = m; i < n; ++i) { chain_direct += pw; pw *= b; }
                for (c = 0; c <= 3; ++c) {
                    if (bn - chain_direct - c != bn - (bn - bm) / (b - 1) - c) {
                        fail_card("T22_base3_chain", "general formula does not match the direct sum", "b=2..10, n=1..18");
                        return;
                    }
                    ++count;
                }
                if (b == 2 && bn - chain_direct != bm) {
                    fail_card("T22_base3_chain", "for b=2 the value is not 2^m", "n=1..18");
                    return;
                }
                if (b == 3 && 2 * (bn - chain_direct) != bn + bm) {
                    fail_card("T22_base3_chain", "for b=3 the value is not (3^n+3^m)/2", "n=1..18");
                    return;
                }
            }
        }
    }
    for (n = 0; n < 40; ++n) {                         /* a(n) = (3^n+1)/2, a(n+1) = 3a(n) - 1 */
        uint64_t p3 = 1;
        for (i = 0; i < n; ++i) p3 *= 3;
        if (a != (p3 + 1) / 2) {
            fail_card("T22_base3_chain", "a(n) = (3^n+1)/2 does not hold", "n<40");
            return;
        }
        a = 3 * a - 1;
    }
    for (n = 0; n < 2000; ++n) {                       /* r = a(n) mod 121 */
        uint64_t p3 = mod_pow(3, n, 121);
        if (r != ((p3 + 1) * 61) % 121) {              /* 61 is the inverse of 2 modulo 121 */
            fail_card("T22_base3_chain", "residue mod 121 does not match the recurrence", "n<2000");
            return;
        }
        if (r % 11 == 0) {
            fail_card("T22_base3_chain", "a(n) divisible by 11", "n<2000");
            return;
        }
        if (n >= 5 && r != ((mod_pow(3, n - 5, 121) + 1) * 61) % 121) {
            fail_card("T22_base3_chain", "residues do not repeat with period 5", "n<2000");
            return;
        }
        r = (3 * r + 120) % 121;
    }
    for (q = 2; q <= 2000000; ++q) {                  /* base-3 Wieferich primes: 3^(q-1) = 1 mod q^2 */
        if (composite[q]) continue;
        if (q <= 2000000UL / q)
            for (i = q * q; i <= 2000000; i += q) composite[i] = 1;
        if (q != 3 && mod_pow(3, q - 1, (uint64_t)q * q) == 1 && wief < 4) found[wief++] = (unsigned)q;
    }
    if (wief != 2 || found[0] != 11 || found[1] != 1006003) {
        fail_card("T22_base3_chain", "base-3 Wieferich primes are not 11 and 1006003", "q<2000000");
        return;
    }
    {
        char result[160];
        snprintf(result, sizeof result,
                 "%u formula equalities; a(n)=(3^n+1)/2, period 5 mod 121, never divisible by 11; base-3 Wieferich: 11, 1006003", count);
        print_result("T22_base3_chain", "HOLDS", result, "b=2..10, n<2000, q<2000000");
    }
}

int main(void) {
    T01_d101_family();
    T02_mersenne_mod8();
    T03_factor_law();
    T04_euler_2p_plus1();
    T05_137_octal_head();
    T06_head_digit_primality_degil();
    T07_pascal_11();
    T08_threshold_law();
    T09_11_base_value();
    T10_square_seal();
    T11_packed_sieve();
    T12_digit_flow();
    T13_shadow_vector();
    T14_quadratic_generator();
    T15_reverse_p_general();
    print_result("T16_mersenne_infinitude", "UNTESTED", "no test written", "claim that infinitely many Mersenne primes follow from this mechanism");
    T17_signature_filter();
    T18_ladder_step();
    T19_base_difference();
    T20_middle_by_addition();
    T21_mersenne_row();
    T22_base3_chain();
    printf("TOTAL | HOLDS=%u | FAILS=%u | UNTESTED=%u | ERROR=%u | tests=22\n",
           counts[0], counts[1], counts[2], counts[3]);
    return failures == 0 ? 0 : 1;
}
