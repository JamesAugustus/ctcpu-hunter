/* ============================================================================
   GOLGE — 20 Temmuz 2026 MERDIVEN MODELI
   ============================================================================
   Bu dosya 20 Tem 2026'da ADDITIF modelden MERDIVEN modeline cevrildi (E1).

   ESKI (additif, TERK EDILDI):  us 7'yi asinca alt katmana us yazilir ve toplanir.
                                 Cem 19 Tem'de reddetti: "ustel devam korkunc
                                 sayilara izin veriyor."
   YENI (merdiven):              rough KESILEREK alt satira iner (2^3*n + a),
                                 tasan us ise a=0 DUZ CARPAN olarak yayilir.
                                 "Golgede 256 diye bir sey yok: 256 = 128x2."

   CARPMA — MERDIVEN BIR SAKLAMA FORMATIDIR, ARITMETIK FORMATI DEGIL:
       1. AC     : (us vektoru, rough) ikilisi cikarilir
       2. CARP   : usler toplanir + rough'lar BINOM'la carpilir (dev carpici YOK)
       3. ENCODE : sonuc yeniden merdivene konur
   Naif yol (satirlarin e[] hucrelerini dogrudan toplamak) YANLIS sonuc verir:
   merdivenin 2^3 carpanlari ve a haneleri toplamayi bozar.

   Dogrulama: 02_PARCALAR/B_GOLGE/EMULATOR/CEM_MODELI/golge_carpma.c
              ~15,4M carpma, 0 hata, en buyuk temel operand = 7.
   ============================================================================ */
#include <stdio.h>
#include <string.h>
#include "shadow.h"

#define SHADOW_LIM 2097151u   /* TUR=2 (ROUGH) satirinin pozisyonel tavani */

/* ---------------------------------------------------------------- yardimci */
static uint64_t row_smooth(const ShadowRow *w) {      /* hucrelerin carpimi */
    uint64_t v = 1;
    for (int i = 0; i < NUM_PRIMES; i++)
        for (int k = 0; k < w->e[i]; k++) v *= SHADOW_PRIMES[i];
    return v;
}
static uint64_t row_pos(const ShadowRow *w) {         /* TUR=2: pozisyonel okunur */
    uint64_t v = 0;
    for (int i = 0; i < NUM_PRIMES; i++) v |= (uint64_t)w->e[i] << (3 * i);
    return v;
}
static void row_setpos(ShadowRow *w, uint64_t x) {    /* TUR=2 yazilir */
    for (int i = 0; i < NUM_PRIMES; i++) w->e[i] = (x >> (3 * i)) & 7;
    w->a = 2;
}
/* hucrelere sigan usleri yazar, SIGMAYANI dondurur (duz carpan olarak yayilacak) */
static uint64_t row_fill(ShadowRow *w, uint64_t x) {
    uint64_t fazla = 1;
    for (int i = 0; i < NUM_PRIMES; i++) {
        int c = 0;
        while (x % SHADOW_PRIMES[i] == 0) { x /= SHADOW_PRIMES[i]; c++; }
        w->e[i] = (c > 7) ? 7 : (uint8_t)c;
        for (int t = 7; t < c; t++) fazla *= SHADOW_PRIMES[i];
    }
    return fazla * x;
}

void shadow_clear(Shadow *s) {
    memset(s, 0, sizeof(Shadow));
    s->rough = 1;
    s->value = 1;
    s->is_smooth = 1;
    s->fits = 1;
}

/* ------------------------------------------------------------ ENCODE (inis)
   golge_nihai.c'nin dene()/encode() mantigi. derin = izin verilen inis sayisi. */
static int encode_dene(Shadow *s, uint32_t N, int derin) {
    memset(s->row, 0, sizeof(s->row));
    s->rr = 0;
    uint64_t cur = N;
    int k = 0, inis = 0;
    for (;;) {
        uint64_t x = cur, sm = 1;
        for (int i = 0; i < NUM_PRIMES; i++)
            while (x % SHADOW_PRIMES[i] == 0) { x /= SHADOW_PRIMES[i]; sm *= SHADOW_PRIMES[i]; }
        uint64_t rg = x;                              /* rough kalan */
        uint64_t fazla = row_fill(&s->row[k], sm);
        int nx = k + 1;
        while (fazla > 1) {                           /* TASMA: duz carpan olarak yayil */
            if (nx > 3) return 0;
            fazla = row_fill(&s->row[nx], fazla);
            s->row[nx].a = 0;
            nx++;
        }
        if (rg == 1) break;                           /* ZINCIR BITTI (rough 1'e indi) */
        if (nx > 3 || inis >= derin) {                /* merdiven icin yer/kota yok */
            if (rg > SHADOW_LIM) return 0;
            if (nx <= 3) row_setpos(&s->row[nx], rg); /* bos satir var -> TUR=2 */
            else         s->rr = (uint32_t)rg;        /* satir kalmadi -> RR */
            break;
        }
        s->row[nx].a = (uint8_t)(rg & 7);             /* KESME: alt 3 bit asagiya */
        cur = rg >> 3;                                /* ust bitler sonraki seviyeye */
        k = nx; inis++;
        if (cur == 0) return 0;
    }
    return 1;
}
static int shadow_encode(Shadow *s, uint32_t N) {
    for (int d = 3; d >= 0; d--) if (encode_dene(s, N, d)) return 1;
    return 0;
}

/* -------------------------------------------------------------- DECODE (geri)
   val(Rk) = smooth(Rk) x [pes pese a=0 satirlarin carpimi] x (2^3*val(Rm)+a_m) */
static uint64_t row_val(const Shadow *s, int k) {
    if (k > 3) return 1;
    uint64_t v = row_smooth(&s->row[k]);
    int m = k + 1;
    while (m <= 3 && s->row[m].a == 0) { v *= row_smooth(&s->row[m]); m++; }
    if (m <= 3) {
        if (s->row[m].a == 2) v *= row_pos(&s->row[m]);       /* ROUGH: dogrudan */
        else                  v *= (8 * row_val(s, m) + s->row[m].a); /* MERDIVEN */
    } else if (s->rr) v *= s->rr;
    return v;
}

/* ------------------------------------------------------------------- 1. AC
   (us vektoru, rough) ikilisi cikarilir. Merdiven acilir, gercek asal ayrisim. */
static void shadow_ac(const Shadow *s, uint32_t us[NUM_PRIMES], uint64_t *rough) {
    for (int i = 0; i < NUM_PRIMES; i++) us[i] = s->row[0].e[i];
    int m = 1;
    while (m <= 3 && s->row[m].a == 0) {              /* duz carpanlar smooth'a katilir */
        for (int i = 0; i < NUM_PRIMES; i++) us[i] += s->row[m].e[i];
        m++;
    }
    if (m <= 3) {
        if (s->row[m].a == 2) *rough = row_pos(&s->row[m]);
        else                  *rough = 8 * row_val(s, m) + s->row[m].a;
    } else *rough = s->rr ? s->rr : 1;
}

/* ---------------------------------------------------- ROUGH x ROUGH — BINOM
   A = 2^3*a1 + rA , B = 2^3*b1 + rB
   A*B = 2^6(a1*b1) + 2^3(a1*rB + b1*rA) + rA*rB
   2^6 ve 2^3 sadece KAYDIRMA (bedava). Taban durumdaki operandlar <=7.
   DEV DIZI CARPICISI HIC KURULMAZ. (5M ciftte kanitlandi, max operand = 7) */
static uint64_t rbinom(uint64_t A, uint64_t B) {
    if (A == 0 || B == 0) return 0;
    if (A < 8 && B < 8) return A * B;                 /* taban: kucuk x kucuk */
    if (B < 8) { uint64_t a1 = A >> 3, rA = A & 7; return (rbinom(a1, B) << 3) + rA * B; }
    if (A < 8) return rbinom(B, A);
    uint64_t a1 = A >> 3, rA = A & 7, b1 = B >> 3, rB = B & 7;
    return (rbinom(a1, b1) << 6) + ((rbinom(a1, rB) + rbinom(b1, rA)) << 3) + rA * rB;
}

/* -------------------------------------------------- degerden golge kurma (RESOLVE) */
void shadow_resolve(Shadow *s, uint32_t value) {
    shadow_clear(s);
    if (value == 0) {                                 /* SIFIR = golge-yoklugu */
        s->rough = 0; s->value = 0; s->is_smooth = 0; s->fits = 1;
        return;
    }
    s->value = value;
    s->fits = (uint8_t)shadow_encode(s, value);
    uint32_t us[NUM_PRIMES]; uint64_t rg = 1;
    if (s->fits) shadow_ac(s, us, &rg);
    else {                                            /* sigmadi: rough dogrudan cikarilir */
        uint64_t v = value;
        for (int i = 0; i < NUM_PRIMES; i++)
            while (v % SHADOW_PRIMES[i] == 0) v /= SHADOW_PRIMES[i];
        rg = v;
    }
    s->rough = rg;
    s->is_smooth = (rg == 1) ? 1 : 0;
    s->ovf = 0;
}

/* --------------------------------------------- degeri golgeye yazar (ortak yol)
   AC -> CARP zaten yapildi; burasi 3. ADIM: yeniden ENCODE. */
static void shadow_store(Shadow *dst, uint64_t C, uint64_t rough_kalan) {
    shadow_clear(dst);
    dst->value = C;
    dst->rough = rough_kalan;
    dst->is_smooth = (rough_kalan == 1) ? 1 : 0;
    if (C == 0) { dst->rough = 0; dst->is_smooth = 0; return; }
    if (C > XBIT_MAX) {                               /* 2^24 asti: golge TAM kalir */
        dst->ovf = 1; dst->fits = 0;
        return;
    }
    dst->fits = (uint8_t)shadow_encode(dst, (uint32_t)C);
}

/* ------------------------------------------------------------ GOLGE CARPMA
   1. AC  2. usleri TOPLA + rough BINOM  3. yeniden ENCODE            */
int shadow_mul(Shadow *dst, const Shadow *a, const Shadow *b) {
    if (a->value == 0 || b->value == 0) { shadow_store(dst, 0, 0); return 0; }

    uint32_t ua[NUM_PRIMES], ub[NUM_PRIMES];
    uint64_t rgA, rgB;
    shadow_ac(a, ua, &rgA);                           /* 1. AC */
    shadow_ac(b, ub, &rgB);
    if (!a->fits) rgA = a->rough;                     /* sigmayanlar icin yedek */
    if (!b->fits) rgB = b->rough;

    uint64_t rgC = rbinom(rgA, rgB);                  /* 2b. rough x rough, BINOM */
    uint64_t C = rgC;
    for (int i = 0; i < NUM_PRIMES; i++) {            /* 2a. usleri TOPLA */
        uint32_t e = ua[i] + ub[i];
        for (uint32_t t = 0; t < e; t++) C *= SHADOW_PRIMES[i];
    }
    shadow_store(dst, C, rgC);                        /* 3. yeniden ENCODE */
    return dst->ovf ? 1 : 0;
}

/* -------------------------------------------------------------- GOLGE BOLME
   Ayni iskelet: AC -> usleri CIKAR + rough'lari BOL -> yeniden ENCODE.   */
int shadow_div(Shadow *dst, const Shadow *a, const Shadow *b) {
    if (b->value == 0) return -1;                     /* sifira bolme: cagiran karar verir */
    if (a->value == 0) { shadow_store(dst, 0, 0); return 0; }

    uint32_t ua[NUM_PRIMES], ub[NUM_PRIMES];
    uint64_t rgA, rgB;
    shadow_ac(a, ua, &rgA);
    shadow_ac(b, ub, &rgB);
    if (!a->fits) rgA = a->rough;
    if (!b->fits) rgB = b->rough;

    for (int i = 0; i < NUM_PRIMES; i++)
        if (ua[i] < ub[i]) return -1;                 /* tam bolunmuyor */
    if (rgB != 1 && (rgB == 0 || rgA % rgB != 0)) return -1;
    uint64_t rgC = (rgB == 1) ? rgA : rgA / rgB;

    uint64_t C = rgC;
    for (int i = 0; i < NUM_PRIMES; i++) {            /* usleri CIKAR */
        uint32_t e = ua[i] - ub[i];
        for (uint32_t t = 0; t < e; t++) C *= SHADOW_PRIMES[i];
    }
    shadow_store(dst, C, rgC);
    return 0;
}

/* ------------------------------------------------- toplam us (i'inci asal icin)
   Merdivende bir asalin ussu birden fazla satira yayilmis olabilir (a=0
   duz carpanlar). Bu fonksiyon onlari toplar — disariya "toplam us" verir. */
uint8_t shadow_total_exp(const Shadow *s, int i) {
    if (!s->fits) {                    /* merdivene sigmadi (OVF): degerden sayilir */
        uint64_t v = s->value; unsigned c = 0;
        if (!v) return 0;
        while (v % SHADOW_PRIMES[i] == 0) { v /= SHADOW_PRIMES[i]; c++; }
        return (c > 255) ? 255 : (uint8_t)c;
    }
    uint32_t us[NUM_PRIMES]; uint64_t rg;
    shadow_ac(s, us, &rg);
    return (us[i] > 255) ? 255 : (uint8_t)us[i];
}

uint64_t shadow_value(const Shadow *s) {
    if (s->value) return s->value;
    return s->fits ? row_val(s, 0) : 0;
}

/* ------------------------------------------------------------------- YAZDIR
   OKTAL basar — Cem kurali: "TESTLER HER ZAMAN OCTAL."
   (Eski surum decimal basiyordu, kurala aykiriydi.) */
static void okt(uint64_t v, char *b) {
    char t[32]; int n = 0;
    if (!v) { b[0] = '0'; b[1] = 0; return; }
    while (v) { t[n++] = '0' + (v & 7); v >>= 3; }
    for (int i = 0; i < n; i++) b[i] = t[n - 1 - i];
    b[n] = 0;
}

void shadow_print(const Shadow *s) {
    char bv[32], br[32];
    okt(shadow_value(s), bv);
    okt(s->rough, br);
    printf("  Golge: ");
    /* LAZY GOLGE: LOAD/ADD golge KURMAZ, sadece bayat isaretler. Resolver
       ilk carpimsal islemde (SMUL/SDIV) kosar. Bayat golgeyi "sifir" diye
       gostermek yaniltici olurdu — ayrica yazilir. */
    if (s->dirty) { printf("[BAYAT — lazy, henuz cozulmedi]\n"); return; }
    if (s->value == 0 && !s->is_smooth) { printf("SIFIR (golge-yoklugu)\n"); return; }
    if (!s->fits) {
        printf("[merdivene SIGMADI] rough=%s_8 val=%s_8 %s\n",
               br, bv, s->ovf ? "(OVF — golge degeri TAM)" : "");
        return;
    }
    for (int k = 0; k < SHADOW_LAYERS; k++) {
        printf("R%d[", k + 1);
        if (k && s->row[k].a == 2) {
            char c[32]; okt(row_pos(&s->row[k]), c);
            printf("POZ=%s_8|TUR=2", c);
        } else {
            int ilk = 1;
            for (int i = 0; i < NUM_PRIMES; i++)
                if (s->row[k].e[i]) {
                    printf("%se%u=%u", ilk ? "" : ",", SHADOW_PRIMES[i], s->row[k].e[i]);
                    ilk = 0;
                }
            if (ilk) printf("-");
            if (k) printf("|a=%u", s->row[k].a);
        }
        printf("] ");
    }
    if (s->rr) { char c[32]; okt(s->rr, c); printf("RR=%s_8 ", c); }
    printf(" val=%s_8 %s\n", bv, s->is_smooth ? "(SMOOTH)" : "(ROUGH)");
}

uint32_t xbit_mod7(uint32_t value) {
    uint32_t sum = 0;
    uint32_t v = value;
    while (v > 0) { sum += v & 7; v >>= 3; }
    while (sum >= 8) {
        uint32_t s2 = 0;
        while (sum > 0) { s2 += sum & 7; sum >>= 3; }
        sum = s2;
    }
    return (sum == 7) ? 0 : sum;
}
