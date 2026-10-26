/* ============================================================================
   ANA EMULATORUN GOLGESI — MERDIVEN MODELI DOGRULAMA (E1 kabul testi)
   ============================================================================
   05_KOD/EMULATOR/shadow.c 20 Tem 2026'da ADDITIF modelden MERDIVEN modeline
   cevrildi. Bu test o cevrimin dogru oldugunu kanitlar.

   Referans model: 02_PARCALAR/B_GOLGE/EMULATOR/CEM_MODELI/golge_nihai.c
   Referans carpma: .../golge_carpma.c  (~15,4M carpma, 0 hata)

   Burada emulatorun KENDI shadow.c'si sinaniyor — kopya degil, gercek dosya.
   Derleme: cc -O2 test_golge_merdiven.c ../EMULATOR/shadow.c -o t && ./t
   ============================================================================ */
#include <stdio.h>
#include <stdint.h>
#include "../EMULATOR/shadow.h"

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("=====================================================================\n");
    printf("  ANA EMULATOR GOLGESI — MERDIVEN MODELI DOGRULAMA\n");
    printf("=====================================================================\n\n");
    long hata = 0;

    /* --- TEST 1: RESOLVE -> DECODE round-trip, tam 2^24 ------------------- */
    printf("--- TEST 1: round-trip (resolve -> decode), TAM 2^24 ---\n");
    long rt_hata = 0, sigmadi = 0;
    for (uint32_t n = 1; n < 16777216u; n++) {
        Shadow s;
        shadow_resolve(&s, n);
        if (!s.fits) { sigmadi++; continue; }
        if (shadow_value(&s) != n) rt_hata++;
    }
    printf("  round-trip hata: %ld   (merdivene sigmayan: %ld)\n", rt_hata, sigmadi);
    hata += rt_hata + sigmadi;   /* kapsama %100 olmali: sigmayan da hatadir */

    /* --- TEST 2: CARPMA, a,b < 4096 tam tarama ---------------------------- */
    printf("\n--- TEST 2: CARPMA tam tarama (a,b < 4096) ---\n");
    long m_hata = 0, m_say = 0, m_ovf = 0;
    for (uint32_t a = 1; a < 4096; a++) {
        Shadow sa; shadow_resolve(&sa, a);
        for (uint32_t b = a; b < 4096; b++) {
            Shadow sb, sc; shadow_resolve(&sb, b);
            shadow_mul(&sc, &sa, &sb);
            uint64_t bekle = (uint64_t)a * b;
            if (shadow_value(&sc) != bekle) m_hata++;
            else if (sc.ovf) m_ovf++;
            m_say++;
        }
    }
    printf("  sinandi: %ld   HATA: %ld   (OVF %ld — deger yine tam)\n", m_say, m_hata, m_ovf);
    hata += m_hata;

    /* --- TEST 3: CARPMA, buyuk/rough operand ------------------------------ */
    printf("\n--- TEST 3: CARPMA buyuk/rough operand (2M cift) ---\n");
    uint64_t s = 88172645463325252ULL; long b_hata = 0, b_say = 0;
    for (long i = 0; i < 2000000; i++) {
        s ^= s << 13; s ^= s >> 7; s ^= s << 17;
        uint32_t a = (uint32_t)(s % 16777215u) + 1;
        uint32_t tavan = 16777215u / a; if (tavan < 1) continue;
        s ^= s << 13; s ^= s >> 7; s ^= s << 17;
        uint32_t b = (uint32_t)(s % tavan) + 1;
        Shadow sa, sb, sc;
        shadow_resolve(&sa, a); shadow_resolve(&sb, b);
        shadow_mul(&sc, &sa, &sb);
        if (shadow_value(&sc) != (uint64_t)a * b) b_hata++;
        b_say++;
    }
    printf("  sinandi: %ld   HATA: %ld\n", b_say, b_hata);
    hata += b_hata;

    /* --- TEST 4: TASMA — 2^24 asinca golge degeri TAM kalmali ------------- */
    printf("\n--- TEST 4: TASMA (2^24 asan carpim) — golge bozuluyor mu? ---\n");
    long t_hata = 0, t_say = 0;
    for (long i = 0; i < 1000000; i++) {
        s ^= s << 13; s ^= s >> 7; s ^= s << 17;
        uint32_t a = (uint32_t)(s % 16777215u) + 1;
        s ^= s << 13; s ^= s >> 7; s ^= s << 17;
        uint32_t b = (uint32_t)(s % 16777215u) + 1;
        if ((uint64_t)a * b <= 16777215u) continue;
        Shadow sa, sb, sc;
        shadow_resolve(&sa, a); shadow_resolve(&sb, b);
        int ovf = shadow_mul(&sc, &sa, &sb);
        t_say++;
        if (!ovf) t_hata++;                                   /* OVF bildirilmeli */
        if (shadow_value(&sc) != (uint64_t)a * b) t_hata++;   /* deger TAM kalmali */
    }
    printf("  OVF sinandi: %ld   HATA: %ld   %s\n", t_say, t_hata,
           t_hata == 0 ? "(golge TASMAZ — deger tam, OVF bildirildi)" : "**BOZULDU**");
    hata += t_hata;

    /* --- TEST 5: BOLME — carpmanin tersi ---------------------------------- */
    printf("\n--- TEST 5: BOLME (a*b sonra /b == a) 1M cift ---\n");
    long d_hata = 0, d_say = 0, d_red = 0;
    for (long i = 0; i < 1000000; i++) {
        s ^= s << 13; s ^= s >> 7; s ^= s << 17;
        uint32_t a = (uint32_t)(s % 4095u) + 1;
        s ^= s << 13; s ^= s >> 7; s ^= s << 17;
        uint32_t b = (uint32_t)(s % 4095u) + 1;
        Shadow sa, sb, sc, sq;
        shadow_resolve(&sa, a); shadow_resolve(&sb, b);
        shadow_mul(&sc, &sa, &sb);
        if (sc.ovf) continue;
        if (shadow_div(&sq, &sc, &sb) != 0) { d_red++; continue; }
        d_say++;
        if (shadow_value(&sq) != a) d_hata++;
    }
    printf("  sinandi: %ld   HATA: %ld   (tam bolunmedi: %ld)\n", d_say, d_hata, d_red);
    hata += d_hata + d_red;

    /* --- TEST 6: MERDIVEN YAPISI — us 7'yi asinca yayilma ---------------- */
    printf("\n--- TEST 6: 'Golgede 256 diye bir sey yok' — us yayilmasi ---\n");
    struct { uint32_t n; const char *not_; } O[] = {
        {256,   "2^8  -> 128 x 2"}, {2048, "2^11"}, {9728, "2^9 x 19"},
        {8388608, "2^23"},          {32768, "2^15"}, {1048576, "2^20"},
    };
    for (unsigned i = 0; i < sizeof(O)/sizeof(O[0]); i++) {
        Shadow x; shadow_resolve(&x, O[i].n);
        uint8_t e2 = shadow_total_exp(&x, 0);
        uint64_t geri = shadow_value(&x);
        int ok = (geri == O[i].n);
        printf("  %-9u %-14s toplam e2=%-3u geri=%-9llu %s\n",
               O[i].n, O[i].not_, e2, (unsigned long long)geri, ok ? "OK" : "**HATA**");
        if (!ok) hata++;
    }

    printf("\n=====================================================================\n");
    printf("  SONUC: %s\n", hata == 0
        ? "ANA EMULATOR GOLGESI MERDIVEN MODELINDE — 0 hata"
        : "**HATA VAR**");
    printf("=====================================================================\n");
    return hata ? 1 : 0;
}
