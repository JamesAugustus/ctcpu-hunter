#ifndef XBIT_H
#define XBIT_H

#include <stdint.h>

#define XBIT_COUNT     10
#define XBIT_SAYI      8
#define XBIT_MAX       16777215  /* 8 xbit = 24 bit = 2^24 - 1 */
#define REG_BITS       30        /* 10 xbit × 3 bit */

/* TUR (type) values — stored in xbit 9, 3 bit = 8 value
 * Renk harfleri: K R G Y B M C W
 * Isaret once, islem sonra: TUR sayinin ne oldugunu soyler */
enum {
    TUR_K = 0,   /* +(SAYI)          pozitif                */
    TUR_R = 1,   /* -(SAYI)          negatif                */
    TUR_G = 2,   /* sqrt(+SAYI)      pozitif karekok        */
    TUR_Y = 3,   /* sqrt(-SAYI)      imajiner = i*sqrt(N)   */
    TUR_B = 4,   /* 1/(+SAYI)        pozitif ters           */
    TUR_M = 5,   /* 1/(-SAYI)        negatif ters           */
    TUR_C = 6,   /* sigma(SAYI)      1+2+...+N              */
    TUR_W = 7,   /* !(SAYI)          N! faktoriyel          */
};

/* FLAG bits */
#define FLAG_OVF    (1 << 0)   /* overflow */
#define FLAG_ZERO   (1 << 1)   /* result is zero */
#define FLAG_ROUGH  (1 << 2)   /* rough/approximate */
#define FLAG_PREFIX (1 << 3)   /* chain: I am continuation of previous */
#define FLAG_SUFFIX (1 << 4)   /* chain: next register continues me */
#define FLAG_OZEL   (1 << 5)   /* special condition */
#define FLAG_NOCPU  (1 << 6)   /* core sleeping */
#define FLAG_RECV   (1 << 7)   /* received data from another core */

typedef struct {
    uint32_t sayi;     /* 24 bit value (8 xbit) */
    uint8_t  pow;      /* 3 bit POW (xbit 8) */
    uint8_t  tur;      /* 3 bit TUR (xbit 9) */
    uint8_t  flag;     /* 8 bit FLAG */
} Reg;

#define NUM_PRIMES  7
#define SHADOW_LAYERS 4

static const uint32_t SHADOW_PRIMES[NUM_PRIMES] = {2, 3, 5, 7, 11, 13, 17};

/* ---------------------------------------------------------------------------
   GOLGE SATIRI — 20 Temmuz 2026 MERDIVEN MODELI (additif model TERK EDILDI)

   [ e2 e3 e5 e7 e11 e13 e17 | TUR ]   8 alan x 3 bit = 24 bit

   TUR (= a) tek hucre, cift gorev:
     1,3,5,7  MERDIVEN   : ustumun rough'u = 2^3 * V(ben) + a
     0        DUZ CARPAN : kendimden onceki merdiven satirinin degerine
                           carpilirim (+a UYGULANMADAN ONCE). Bos satir = 1.
     2        ROUGH      : ben ustumun rough'uyum DOGRUDAN (pozisyonel okunur)
     4,6      PREFIX/SUFFIX — cip siniri, 24-bit kelimede kullanilmaz
   R1'in TUR'u YOKTUR (ustunde R0'dan baska satir yok).
   a merdivende ASLA 0 olmaz: resolver butun 2'leri soyar -> rough TEKTIR
   -> oktal son hane zorunlu 1/3/5/7. Bu ISPAT, olcum degil.
   Referans: 02_PARCALAR/B_GOLGE/GOLGE_MEKANIZMA_SEMASI.txt
             02_PARCALAR/B_GOLGE/EMULATOR/CEM_MODELI/golge_nihai.c
--------------------------------------------------------------------------- */
typedef struct {
    uint8_t e[NUM_PRIMES];      /* 7 asalin usleri, her hucre 0-7 */
    uint8_t a;                  /* TUR hucresi (yukaridaki tablo) */
} ShadowRow;

typedef struct {
    ShadowRow row[SHADOW_LAYERS]; /* R1..R4 — merdiven */
    uint32_t rr;                  /* RR: yuvarlanan rough registeri (0 = yok).
                                     Satir kalmayinca dolar; tavan <=15 bit. */
    uint64_t rough;               /* ACILMIS rough (aritmetik icin tutulur).
                                     64-bit: OVF'de golge TAM kalir. */
    uint64_t value;               /* tam deger — 2^24 assa bile BOZULMAZ */
    uint8_t  is_smooth;           /* 1 if rough==1 */
    uint8_t  ovf;                 /* 1 = deger 2^24'u asti (golge yine tam) */
    uint8_t  fits;                /* 1 = merdivene sigdi (encode basarili) */
    uint8_t  dirty;               /* LAZY GOLGE (G01 KARAR): 1 = golge bayat.
                                     ADD/SUB/MUL sadece bu biti koyar; resolver
                                     SMUL/SDIV ihtiyac aninda kosar (1x). */
} Shadow;

static inline uint32_t xbit_add(uint32_t a, uint32_t b, uint8_t *ovf) {
    uint32_t result = a + b;
    *ovf = (result > XBIT_MAX) ? 1 : 0;
    return result & XBIT_MAX;
}

static inline uint32_t xbit_sub(uint32_t a, uint32_t b, uint8_t *tur_flip) {
    if (a >= b) {
        *tur_flip = 0;
        return a - b;
    }
    *tur_flip = 1;
    return b - a;
}

static inline uint32_t xbit_mul(uint32_t a, uint32_t b, uint32_t *high) {
    uint64_t result = (uint64_t)a * b;
    *high = (uint32_t)(result >> 24);
    return (uint32_t)(result & XBIT_MAX);
}

#endif
