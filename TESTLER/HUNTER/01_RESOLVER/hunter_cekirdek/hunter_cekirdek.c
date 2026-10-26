/* Hunter çekirdeği: sayıyı parçalama (teorik işlemci). Yazar: James Augustus.
Ekim 2026. Lisans: MIT. Bu bir emülasyondur; devre değil. */
/* Derle: cc -std=c99 -Wall -Wextra -Wpedantic -O2 -o /tmp/hunter_cekirdek hunter_cekirdek.c
   Kullanım: ./hunter_cekirdek 744 | --iz 4782969 | --carp A B | --topla A B | --cikar A B | --bol A B | --test
   Sayı yazımı: ondalık (744), sekizlik (1350_8), kuvvet (3^14, 2^500).

   Bir Hunter sayısı üç parçadır:
     rm        mantissa: sayının kendisi, sekizlik haneler (uzunluk serbest)
     rs1..rs4  gölge: 7 kanalın (2,3,5,7,11,13,17) üs sayaçları, sekizlik kilometre sayacı
               e = rs1 + 8·rs2 + 64·rs3 + 512·rs4, en çok 4095
     rc        rough: hiçbir kanala bölünmeyen artık, sekizlik haneler
   Toplama ve çıkarma rm'de, çarpma ve bölme gölgede yapılır. Hangisi bayatsa
   gerektiğinde ötekinden kurulur: rm'den gölgeye RESOLVER, gölgeden rm'ye GERİ KURMA.
   Normal / ve % yalnız tek hanelik akış adımlarında (8·kalan + hane gibi) kullanılır. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define HMAX 1536                   /* bir sayının en çok sekizlik hanesi (4608 bit) */
#define KANAL 7
#define SATIR 4                     /* rs1..rs4 */

static const unsigned KQ[KANAL] = {2, 3, 5, 7, 11, 13, 17};
static const char *const KALT[KANAL] = {"₂", "₃", "₅", "₇", "₁₁", "₁₃", "₁₇"};

typedef struct { int n; unsigned char h[HMAX + 1]; } sayi;   /* h[0] en düşük hane; n = 0 ise sıfır */

typedef struct {
    sayi rm;                        /* mantissa */
    unsigned char rs[SATIR][KANAL]; /* gölge: rs[0] = rs1 ... rs[3] = rs4, her hücre 0..7 */
    sayi rc;                        /* rough */
    int rm_taze, golge_taze;        /* tembel gölge: hangi taraf güncel */
} hunter;

/* =====================  SEKİZLİK HANE DİZİSİ  ===================== */

/* Baştaki sıfırları atar; n gerçek hane sayısı olur. */
static void kisalt(sayi *s) { while (s->n > 0 && s->h[s->n - 1] == 0) s->n--; }

/* d = s; yalnız dolu haneler kopyalanır. */
static void kopya(sayi *d, const sayi *s) { d->n = s->n; memcpy(d->h, s->h, (size_t)s->n); }

/* Kıyas: -1, 0, 1. Önce hane sayısı, eşitse en yüksek haneden aşağı. */
static int kiyas(const sayi *a, const sayi *b)
{
    int i;
    if (a->n != b->n) return a->n < b->n ? -1 : 1;
    for (i = a->n - 1; i >= 0; i--)
        if (a->h[i] != b->h[i]) return a->h[i] < b->h[i] ? -1 : 1;
    return 0;
}

/* s = s·k + ek (k küçük). Akış adımı: t = hane·k + elde; hane = t mod 8, elde = t div 8. Taşarsa 0. */
static int kucuk_carp(sayi *s, unsigned k, unsigned ek)
{
    unsigned c = ek;
    int i;
    for (i = 0; i < s->n; i++) {
        unsigned t = s->h[i] * k + c;
        s->h[i] = (unsigned char)(t % 8);
        c = t / 8;
    }
    while (c) {
        if (s->n >= HMAX) return 0;
        s->h[s->n++] = (unsigned char)(c % 8);
        c = c / 8;
    }
    return 1;
}

/* Bölüm akışı: haneler soldan akar, t = 8·kalan + hane; bölüm hanesi = t div q, kalan = t mod q.
   b, s ile aynı olabilir (her hane okunduktan sonra yazılır). Kalanı döndürür. */
static unsigned akis_bol(sayi *b, const sayi *s, unsigned q)
{
    unsigned k = 0;
    int i;
    for (i = s->n - 1; i >= 0; i--) {
        unsigned t = 8 * k + s->h[i];
        b->h[i] = (unsigned char)(t / q);
        k = t % q;
    }
    b->n = s->n;
    kisalt(b);
    return k;
}

/* r = a + b, hane hane, elde ile. r, a ya da b ile aynı olabilir. Taşarsa 0. */
static int topla(sayi *r, const sayi *a, const sayi *b)
{
    int m = a->n > b->n ? a->n : b->n, i;
    unsigned elde = 0;
    for (i = 0; i < m; i++) {
        unsigned t = (i < a->n ? a->h[i] : 0u) + (i < b->n ? b->h[i] : 0u) + elde;
        if (t > 7) { t -= 8; elde = 1; } else elde = 0;
        r->h[i] = (unsigned char)t;
    }
    r->n = m;
    if (elde) {
        if (m >= HMAX) return 0;
        r->h[r->n++] = 1;
    }
    return 1;
}

/* r = a - b (a >= b), hane hane, ödünç ile. r, a ya da b ile aynı olabilir. */
static void cikar(sayi *r, const sayi *a, const sayi *b)
{
    int i, odunc = 0;
    for (i = 0; i < a->n; i++) {
        int t = (int)a->h[i] - (i < b->n ? (int)b->h[i] : 0) - odunc;
        if (t < 0) { t += 8; odunc = 1; } else odunc = 0;
        r->h[i] = (unsigned char)t;
    }
    r->n = a->n;
    kisalt(r);
}

/* r = a · b, okul usulü: b'nin her hanesi için a akar; t = a hanesi·b hanesi + r hanesi + elde <= 63,
   yani her adım tek hanedir. r, a ve b'den ayrı olmalı. Taşarsa 0. */
static int carp(sayi *r, const sayi *a, const sayi *b)
{
    int i, j;
    if (a->n == 0 || b->n == 0) { r->n = 0; return 1; }
    if (a->n + b->n > HMAX) return 0;
    memset(r->h, 0, (size_t)(a->n + b->n));
    for (j = 0; j < b->n; j++) {
        unsigned c = 0, bj = b->h[j];
        if (bj == 0) continue;
        for (i = 0; i < a->n; i++) {
            unsigned t = a->h[i] * bj + r->h[i + j] + c;
            r->h[i + j] = (unsigned char)(t % 8);
            c = t / 8;
        }
        r->h[a->n + j] = (unsigned char)c;
    }
    r->n = a->n + b->n;
    kisalt(r);
    return 1;
}

/* Uzun bölme a / b (b sıfır değil): kalan bir hane sola kayar, a'nın sıradaki hanesi girer;
   bölüm hanesi, kalan b'den küçük olana dek yapılan çıkarma sayısıdır. Hane 3 bittir: 8. çıkarma
   gerekirse aritmetik bozuktur, 0 döner (sonsuz döngü yerine). */
static int bol(sayi *bolum, sayi *kalan, const sayi *a, const sayi *b)
{
    int i;
    kalan->n = 0;
    for (i = a->n - 1; i >= 0; i--) {
        unsigned d = 0;
        if (kalan->n > 0 || a->h[i]) {
            memmove(kalan->h + 1, kalan->h, (size_t)kalan->n);
            kalan->h[0] = a->h[i];
            kalan->n++;
        }
        while (kiyas(kalan, b) >= 0) {
            if (d == 7) return 0;
            cikar(kalan, kalan, b);
            d++;
        }
        bolum->h[i] = (unsigned char)d;
    }
    bolum->n = a->n;
    kisalt(bolum);
    return 1;
}

/* Metni sayıya çevirir: ondalık "744", sekizlik "1350_8", kuvvet "3^14". Ondalık haneler
   Horner ile akar (s = 10·s + hane). Hata ya da taşmada 0. */
static int oku(sayi *s, const char *m)
{
    const char *u = strchr(m, '^');
    size_t L = strlen(m), i;
    s->n = 0;
    if (u) {
        static sayi taban, g;
        char tb[64];
        unsigned long e = 0;
        size_t tl = (size_t)(u - m);
        if (tl == 0 || tl >= sizeof tb || u[1] == 0) return 0;
        memcpy(tb, m, tl);
        tb[tl] = 0;
        if (strchr(tb, '^') || !oku(&taban, tb)) return 0;
        for (i = 1; u[i]; i++) {
            if (u[i] < '0' || u[i] > '9' || e > 100000) return 0;
            e = e * 10 + (unsigned long)(u[i] - '0');
        }
        s->n = 1; s->h[0] = 1;
        while (e--) {
            if (!carp(&g, s, &taban)) return 0;
            kopya(s, &g);
        }
        return 1;
    }
    if (L > 2 && m[L - 2] == '_' && m[L - 1] == '8') {
        for (i = 0; i + 2 < L; i++) {
            if (m[i] < '0' || m[i] > '7' || !kucuk_carp(s, 8, (unsigned)(m[i] - '0'))) return 0;
            kisalt(s);
        }
        return L > 2;
    }
    for (i = 0; i < L; i++) {
        if (m[i] < '0' || m[i] > '9' || !kucuk_carp(s, 10, (unsigned)(m[i] - '0'))) return 0;
        kisalt(s);
    }
    return L > 0;
}

static char tamp[3][HMAX + 8];

/* Sekizlik metin, yüksek haneden; t = tampon numarası (aynı satırda üç sayıya kadar). */
static const char *m8(const sayi *s, int t)
{
    char *b = tamp[t];
    int i, j = 0;
    if (s->n == 0) b[j++] = '0';
    for (i = s->n - 1; i >= 0; i--) b[j++] = (char)('0' + s->h[i]);
    b[j] = 0;
    return b;
}

/* Ondalık metin: sayı akışla 10'a bölünür (t = 8·kalan + hane), her geçiş bir ondalık hane verir. */
static const char *m10(const sayi *s, int t)
{
    static sayi g;
    static char ters[HMAX + 8];
    char *b = tamp[t];
    int j = 0, i;
    kopya(&g, s);
    if (g.n == 0) ters[j++] = '0';
    while (g.n > 0) ters[j++] = (char)('0' + akis_bol(&g, &g, 10));
    for (i = 0; i < j; i++) b[i] = ters[j - 1 - i];
    b[j] = 0;
    return b;
}

/* =====================  GÖLGE  ===================== */

/* Gölgeyi sıfırlar: bütün sayaç hücreleri 0, rc boş. */
static void golge_sil(hunter *H) { memset(H->rs, 0, sizeof H->rs); H->rc.n = 0; }

/* Kanal k'nın sayacı (Horner ile): e = rs1 + 8·(rs2 + 8·(rs3 + 8·rs4)). */
static unsigned us(const hunter *H, int k)
{
    unsigned e = 0;
    int j;
    for (j = SATIR - 1; j >= 0; j--) e = 8 * e + H->rs[j][k];
    return e;
}

/* Kanal k'nın sayacına bir tık: rs1 hücresi artar, 8 olunca 0'a döner ve elde üst satıra geçer.
   Döndürür: tıkın durduğu satır (0 = rs1, elde yok), -1 = rs4 de taştı (e > 4095). */
static int sayac_tik(hunter *H, int k)
{
    int j;
    for (j = 0; j < SATIR; j++) {
        if (++H->rs[j][k] < 8) return j;
        H->rs[j][k] = 0;
    }
    return -1;
}

/* RESOLVER (ileri): rm'den gölgeyi kurar.
   Parça 1: haneler soldan akar, 7 kanalın kalanı aynı anda güncellenir: kalan = (8·kalan + hane) mod q.
   Parça 2: kalanı 0 olan kanallar sırayla konveyöre girer; her aşama bölümü akıtır, bölündükçe sayaç
   bir tık. Konveyörün sonundan çıkan rc'dir. iz = 1 ise her adım yazılır.
   Döndürür 1; sayı sıfırsa 0 (0'ın gölgesi kurulmaz); sayaç taşarsa -1. */
static int resolver(hunter *H, int iz)
{
    static sayi A, B;
    static unsigned char izk[KANAL][HMAX];
    unsigned kalan[KANAL] = {0};
    sayi *cur = &A, *nxt = &B, *tk;
    int i, k, w = H->rm.n;
    if (H->rm.n == 0) return 0;
    golge_sil(H);
    for (i = H->rm.n - 1; i >= 0; i--)                          /* Parça 1: kalan akışı */
        for (k = 0; k < KANAL; k++) {
            kalan[k] = (8 * kalan[k] + H->rm.h[i]) % KQ[k];
            if (iz) izk[k][i] = (unsigned char)kalan[k];
        }
    if (iz) {
        printf("  KALAN AKIŞI\n    hane      :");
        for (i = H->rm.n - 1; i >= 0; i--) printf("%3u", H->rm.h[i]);
        printf("\n");
        for (k = 0; k < KANAL; k++) {
            printf("    kanal %2u  :", KQ[k]);
            for (i = H->rm.n - 1; i >= 0; i--) printf("%3u", izk[k][i]);
            printf("   → %s\n", kalan[k] ? "bölünmez" : "bölünür");
        }
        printf("  BÖLÜM AKIŞI (sekizlik)\n");
    }
    kopya(cur, &H->rm);
    for (k = 0; k < KANAL; k++) {                               /* Parça 2: bölüm akışı, konveyör */
        if (kalan[k]) continue;
        for (;;) {
            int j;
            if (akis_bol(nxt, cur, KQ[k])) break;
            j = sayac_tik(H, k);
            if (j < 0) return -1;
            if (iz) {
                printf("    / %-2u : %*s → %*s    sayaç%s = %u", KQ[k], w, m8(cur, 0), w, m8(nxt, 1),
                       KALT[k], H->rs[0][k]);
                if (j > 0) printf(", elde → rs%d = %u", j + 1, H->rs[j][k]);
                printf("\n");
            }
            tk = cur; cur = nxt; nxt = tk;
        }
    }
    kopya(&H->rc, cur);
    if (iz) printf("    %s_8 = %s: hiçbir kanala bölünmez\n", m8(&H->rc, 0), m10(&H->rc, 1));
    H->golge_taze = 1;
    return 1;
}

/* GERİ KURMA: rm = rc · ∏ q^e. Her kanalda e kez küçük çarpma (hane akışı). "Çözülmesi basit" budur:
   bölme yok, arama yok, yalnız çarpma. ayrinti: 0 sessiz, 1 kanal başına satır, 2 her çarpma. Taşarsa 0. */
static int geri_kur(hunter *H, int ayrinti)
{
    int k;
    kopya(&H->rm, &H->rc);
    if (ayrinti) printf("    rc           → %s_8\n", m8(&H->rm, 0));
    for (k = 0; k < KANAL; k++) {
        unsigned e = us(H, k), c;
        char qe[24];
        for (c = 0; c < e; c++) {
            if (!kucuk_carp(&H->rm, KQ[k], 0)) return 0;
            if (ayrinti == 2) printf("    × %-10u → %s_8\n", KQ[k], m8(&H->rm, 0));
        }
        if (ayrinti == 1 && e) {
            snprintf(qe, sizeof qe, "%u^%u", KQ[k], e);
            printf("    × %-10s → %s_8\n", qe, m8(&H->rm, 0));
        }
    }
    H->rm_taze = 1;
    return 1;
}

/* Gölgeyi şablondaki gibi yazar: rs1..rs4 satırları (kanal sırası 2 3 5 7 11 13 17), e ve rc. */
static void golge_yaz(const hunter *H)
{
    int j, k, ilk = 1;
    for (j = 0; j < SATIR; j++) {
        printf("    rs%d = [", j + 1);
        for (k = 0; k < KANAL; k++) printf("%u%s", H->rs[j][k], k < KANAL - 1 ? ", " : "]");
        printf(j == 0 ? "      kanal sırası 2 3 5 7 11 13 17\n" : "\n");
    }
    printf("    e   = ");
    for (k = 0; k < KANAL; k++)
        if (us(H, k)) { printf("%s%u^%u", ilk ? "" : " · ", KQ[k], us(H, k)); ilk = 0; }
    printf("%s\n    rc  = %s_8 = %s\n", ilk ? "(hiçbir kanal bölmüyor)" : "", m8(&H->rc, 0), m10(&H->rc, 1));
}

/* =====================  HUNTER İŞLEMLERİ  ===================== */

/* Mantissayı yükler; gölge henüz kurulmadı (bayat). */
static void h_yukle(hunter *H, const sayi *s) { kopya(&H->rm, s); H->rm_taze = 1; H->golge_taze = 0; }

/* Sayı sıfır mı? Gölgesi taze olan sayı sıfır olamaz. */
static int h_sifir(const hunter *H) { return H->rm_taze && H->rm.n == 0; }

/* rm bayatsa gölgeden geri kurar. */
static int rm_hazir(hunter *H) { return H->rm_taze ? 1 : geri_kur(H, 0); }

/* Gölge bayatsa resolver yeniden kurar (tembel gölge). */
static int golge_hazir(hunter *H) { return H->golge_taze ? 1 : resolver(H, 0); }

/* TOPLAMA mantissada; sonucun gölgesi bayat kalır. Taşarsa 0. */
static int h_topla(hunter *R, hunter *A, hunter *B)
{
    if (!rm_hazir(A) || !rm_hazir(B) || !topla(&R->rm, &A->rm, &B->rm)) return 0;
    R->rm_taze = 1; R->golge_taze = 0;
    return 1;
}

/* ÇIKARMA mantissada (A >= B); sonucun gölgesi bayat kalır. A < B ise -1, hata 0. */
static int h_cikar(hunter *R, hunter *A, hunter *B)
{
    if (!rm_hazir(A) || !rm_hazir(B)) return 0;
    if (kiyas(&A->rm, &B->rm) < 0) return -1;
    cikar(&R->rm, &A->rm, &B->rm);
    R->rm_taze = 1; R->golge_taze = 0;
    return 1;
}

/* ÇARPMA gölgede: resolver çarpmanın kendisinde çalışmaz. e(A·B) = e(A) + e(B) kanal kanal, hücre hücre
   elde ile; rc(A·B) = rc(A)·rc(B). Sonucun rm'si bayat kalır. R, A ve B'den ayrı olmalı.
   Döndürür 1; sayaç ya da hane taşması -1. */
static int h_carp(hunter *R, hunter *A, hunter *B)
{
    int j, k;
    if (h_sifir(A) || h_sifir(B)) { R->rm.n = 0; R->rm_taze = 1; R->golge_taze = 0; return 1; }
    if (golge_hazir(A) != 1 || golge_hazir(B) != 1) return -1;
    for (k = 0; k < KANAL; k++) {
        unsigned c = 0;
        for (j = 0; j < SATIR; j++) {
            unsigned t = A->rs[j][k] + B->rs[j][k] + c;
            if (t >= 8) { t -= 8; c = 1; } else c = 0;
            R->rs[j][k] = (unsigned char)t;
        }
        if (c) return -1;
    }
    if (!carp(&R->rc, &A->rc, &B->rc)) return -1;
    R->golge_taze = 1; R->rm_taze = 0;
    return 1;
}

/* BÖLME gölgede: e(A/B) = e(A) - e(B) hücre hücre ödünç ile; rc(A)/rc(B) uzun bölme.
   Bir kanalda ödünç tükenirse ya da rc kalanı varsa bölünemez. Döndürür 1 bölündü, 0 bölünemez
   (*neden = kanal sırası, rc ise KANAL), -1 hata (B sıfır ya da taşma). R, A ve B'den ayrı olmalı. */
static int h_bol(hunter *R, hunter *A, hunter *B, int *neden)
{
    static sayi kalan;
    int j, k;
    if (h_sifir(B)) return -1;
    if (h_sifir(A)) { R->rm.n = 0; R->rm_taze = 1; R->golge_taze = 0; return 1; }
    if (golge_hazir(A) != 1 || golge_hazir(B) != 1) return -1;
    for (k = 0; k < KANAL; k++) {
        int odunc = 0;
        for (j = 0; j < SATIR; j++) {
            int t = (int)A->rs[j][k] - (int)B->rs[j][k] - odunc;
            if (t < 0) { t += 8; odunc = 1; } else odunc = 0;
            R->rs[j][k] = (unsigned char)t;
        }
        if (odunc) { *neden = k; return 0; }
    }
    if (!bol(&R->rc, &kalan, &A->rc, &B->rc)) return -1;
    if (kalan.n) { *neden = KANAL; return 0; }
    R->golge_taze = 1; R->rm_taze = 0;
    return 1;
}

/* =====================  BAĞIMSIZ DENETÇİ (yalnız --test)  =====================
   Aynı sayılar 2^32 tabanında 32 bitlik kollara paketlenir; toplama, çıkarma, çarpma orada
   ayrı yazılmış kodla yapılır. Yalnız +, ·, kaydırma ve maske; bölme yok. */

#define LMAX 160
typedef struct { int n; uint32_t w[LMAX]; } kol;

/* Baştaki sıfır kolları atar. */
static void kol_kisalt(kol *a) { while (a->n > 0 && a->w[a->n - 1] == 0) a->n--; }

/* Sekizlik haneleri bit bit paketler: hane i, 3i'inci bitten başlar. */
static void kol_den(kol *a, const sayi *s)
{
    int i;
    memset(a->w, 0, sizeof a->w);
    for (i = 0; i < s->n; i++) {
        unsigned bit = 3u * (unsigned)i, w = bit >> 5, o = bit & 31u;
        a->w[w] |= (uint32_t)s->h[i] << o;
        if (o > 29) a->w[w + 1] |= (uint32_t)s->h[i] >> (32 - o);
    }
    a->n = (3 * s->n + 31) >> 5;
    kol_kisalt(a);
}

/* Kıyas: -1, 0, 1. */
static int kol_kiyas(const kol *a, const kol *b)
{
    int i;
    if (a->n != b->n) return a->n < b->n ? -1 : 1;
    for (i = a->n - 1; i >= 0; i--)
        if (a->w[i] != b->w[i]) return a->w[i] < b->w[i] ? -1 : 1;
    return 0;
}

/* r = a + b, 64 bitlik ara toplamla. */
static void kol_topla(kol *r, const kol *a, const kol *b)
{
    int m = a->n > b->n ? a->n : b->n, i;
    uint64_t c = 0;
    for (i = 0; i < m; i++) {
        uint64_t t = (uint64_t)(i < a->n ? a->w[i] : 0) + (i < b->n ? b->w[i] : 0) + c;
        r->w[i] = (uint32_t)t;
        c = t >> 32;
    }
    r->w[m] = (uint32_t)c;
    r->n = m + 1;
    kol_kisalt(r);
}

/* r = a - b, a >= b. */
static void kol_cikar(kol *r, const kol *a, const kol *b)
{
    int i;
    int64_t br = 0;
    for (i = 0; i < a->n; i++) {
        int64_t t = (int64_t)a->w[i] - (i < b->n ? (int64_t)b->w[i] : 0) - br;
        if (t < 0) { t += (int64_t)1 << 32; br = 1; } else br = 0;
        r->w[i] = (uint32_t)t;
    }
    r->n = a->n;
    kol_kisalt(r);
}

/* r = a · b, okul usulü 32x32 -> 64 bit. */
static void kol_carp(kol *r, const kol *a, const kol *b)
{
    int i, j;
    memset(r->w, 0, sizeof r->w);
    for (i = 0; i < a->n; i++) {
        uint64_t c = 0;
        for (j = 0; j < b->n; j++) {
            uint64_t t = (uint64_t)a->w[i] * b->w[j] + r->w[i + j] + c;
            r->w[i + j] = (uint32_t)t;
            c = t >> 32;
        }
        r->w[i + b->n] = (uint32_t)c;
    }
    r->n = a->n + b->n;
    kol_kisalt(r);
}

static uint64_t tohum = 0x9E3779B97F4A7C15u;

/* xorshift64* rastgele sayı üreteci, sabit tohum (her koşu aynı). */
static uint64_t rast(void)
{
    tohum ^= tohum >> 12; tohum ^= tohum << 25; tohum ^= tohum >> 27;
    return tohum * 2685821657736338717u;
}

/* 0..n-1 arası düzgün dağılım: maskeyle çekip büyükleri atar (bölme yok). */
static unsigned rastn(unsigned n)
{
    unsigned m = 1;
    while (m < n) m <<= 1;
    m -= 1;
    for (;;) {
        unsigned r = (unsigned)(rast() >> 20) & m;
        if (r < n) return r;
    }
}

/* Rastgele sayı, en çok 200 sekizlik hane. Dörtte biri küçük (1..8 hane); dörtte biri 2^e2·3^e3 ile
   çarpılır (e2 512'ye kadar), böylece sayaçların rs2, rs3, rs4 eldeleri de sınanır. */
static void rastgele_sayi(sayi *s)
{
    unsigned L = rastn(4) == 0 ? 1 + rastn(8) : 1 + rastn(200), e2 = 0, e3 = 0, i;
    if (rastn(4) == 0) {
        unsigned ek;
        e2 = rastn(rastn(2) ? 64 : 512);
        e3 = rastn(48);
        ek = (e2 + 2 * e3) >> 1;
        L = L > ek ? L - ek : 1;
    }
    s->n = (int)L;
    for (i = 0; i < L; i++) s->h[i] = (unsigned char)rastn(8);
    s->h[L - 1] = (unsigned char)(1 + rastn(7));
    while (e2--) kucuk_carp(s, 2, 0);
    while (e3--) kucuk_carp(s, 3, 0);
}

/* En yüksek dolu sayaç satırı (0 = yalnız rs1 ... 3 = rs4 kullanıldı). */
static int en_ust_satir(const hunter *H)
{
    int j, k, u = 0;
    for (j = 0; j < SATIR; j++)
        for (k = 0; k < KANAL; k++)
            if (H->rs[j][k]) u = j;
    return u;
}

/* --test: 1..2^24 resolver ve geri kurma; 100.000 rastgele çiftte toplama, çıkarma, çarpma, bölme
   bağımsız denetçiyle kıyas. Hata varsa çıkış 1. */
static int test(void)
{
    static hunter H, A, B, X, D, Q;
    static sayi orj, sa, sb;
    static kol ka, kb, kx, kr, kt;
    const uint32_t N = (uint32_t)1 << 24;
    const long CIFT = 100000;
    uint32_t *p, n;
    long y_geri = 0, y_golge = 0, y_top = 0, y_cik = 0, y_car = 0, y_bol = 0, t;
    long satir_say[SATIR] = {0}, en_cok_hane = 0;
    int k;

    /* Elek: p[m] = m'nin 2,3,5,7,11,13,17 parçası. Yalnız çarpma ve toplama. */
    p = malloc(((size_t)N + 1) * sizeof *p);
    if (!p) { printf("bellek yok\n"); return 1; }
    for (n = 0; n <= N; n++) p[n] = 1;
    for (k = 0; k < KANAL; k++) {
        uint64_t g;
        for (g = KQ[k]; g <= N; g *= KQ[k]) {
            uint64_t m;
            for (m = g; m <= N; m += g) p[m] *= KQ[k];
        }
    }
    for (n = 1; n <= N; n++) {
        uint64_t duz = 1, rc = 0;
        uint32_t v;
        int i, bozuk = 0;
        orj.n = 0;
        for (v = n; v; v >>= 3) orj.h[orj.n++] = (unsigned char)(v & 7);
        h_yukle(&H, &orj);
        if (resolver(&H, 0) != 1) { y_golge++; y_geri++; continue; }
        for (i = H.rc.n - 1; i >= 0; i--) rc = (rc << 3) | H.rc.h[i];
        for (k = 0; k < KANAL && !bozuk; k++) {
            unsigned e = us(&H, k);
            while (e--) { duz *= KQ[k]; if (duz > n) { bozuk = 1; break; } }
        }
        if (bozuk || duz != p[n] || duz * rc != n) y_golge++;
        H.rm.n = 0; H.rm_taze = 0;                              /* rm silinir, yalnız gölgeden kurulur */
        if (!geri_kur(&H, 0) || kiyas(&H.rm, &orj) != 0) y_geri++;
    }
    free(p);
    printf("TEST 1  resolver → geri kurma, 1 .. 2^24 (%lu sayı)\n", (unsigned long)N);
    printf("        geri kurma birebir değil : %ld\n", y_geri);
    printf("        gölge elekle uyuşmuyor   : %ld   (elek: 2,3,5,7,11,13,17 parçası, bölmesiz)\n", y_golge);

    for (t = 0; t < CIFT; t++) {
        int ab, x_ust, neden, r;
        hunter *xs;
        kol *kxs;
        rastgele_sayi(&sa); rastgele_sayi(&sb);
        if (sa.n > en_cok_hane) en_cok_hane = sa.n;
        if (sb.n > en_cok_hane) en_cok_hane = sb.n;
        h_yukle(&A, &sa); h_yukle(&B, &sb);
        kol_den(&ka, &sa); kol_den(&kb, &sb);

        /* toplama: X = A + B, gölgesi bayat kalır */
        if (!h_topla(&X, &A, &B)) y_top++;
        else { kol_topla(&kx, &ka, &kb); kol_den(&kr, &X.rm); if (kol_kiyas(&kr, &kx)) y_top++; }

        /* çıkarma: büyükten küçüğe (sırayı denetçi seçer); ters sıra eşit değilse reddedilmeli */
        ab = kol_kiyas(&ka, &kb);
        r = h_cikar(&D, ab >= 0 ? &A : &B, ab >= 0 ? &B : &A);
        if (r != 1) y_cik++;
        else { kol_cikar(&kt, ab >= 0 ? &ka : &kb, ab >= 0 ? &kb : &ka); kol_den(&kr, &D.rm); if (kol_kiyas(&kr, &kt)) y_cik++; }
        if (ab != 0 && h_cikar(&D, ab >= 0 ? &B : &A, ab >= 0 ? &A : &B) != -1) y_cik++;

        /* çarpma: tek turda X = A + B (bayat gölgeyi resolver yeniden kurar), çift turda X = A */
        xs = (t & 1) ? &X : &A;
        kxs = (t & 1) ? &kx : &ka;
        if (h_carp(&D, xs, &B) != 1 || !rm_hazir(&D)) { y_car++; continue; }
        kol_carp(&kt, kxs, &kb); kol_den(&kr, &D.rm);
        if (kol_kiyas(&kr, &kt)) y_car++;
        satir_say[en_ust_satir(&D)]++;

        /* bölme: (X·B)/B = X; X > 1 ise B/(X·B) bölünemez demeli */
        if (h_bol(&Q, &D, &B, &neden) != 1 || !rm_hazir(&Q)) y_bol++;
        else { kol_den(&kr, &Q.rm); if (kol_kiyas(&kr, kxs)) y_bol++; }
        x_ust = !(kxs->n == 1 && kxs->w[0] == 1);
        if (x_ust && h_bol(&Q, &B, &D, &neden) != 0) y_bol++;
    }
    printf("TEST 2  toplama  %ld rastgele çift, en çok %ld sekizlik hane : hata %ld\n", CIFT, en_cok_hane, y_top);
    printf("TEST 3  çıkarma  %ld çift (ters sıra reddi dahil)            : hata %ld\n", CIFT, y_cik);
    printf("TEST 4  çarpma   %ld çift, yarısı tembel gölgeli (A+B)·B    : hata %ld\n", CIFT, y_car);
    printf("        çarpım gölgesinin en üst satırı: rs1 %ld, rs2 %ld, rs3 %ld, rs4 %ld\n",
           satir_say[0], satir_say[1], satir_say[2], satir_say[3]);
    printf("TEST 5  bölme    %ld çift, (X·B)/B = X ve B/(X·B) bölünemez : hata %ld\n", CIFT, y_bol);
    t = y_geri + y_golge + y_top + y_cik + y_car + y_bol;
    printf("SONUÇ   toplam hata %ld → çıkış %d\n", t, t ? 1 : 0);
    return t ? 1 : 0;
}

/* =====================  KOMUT SATIRI  ===================== */

static hunter GA, GB, GR;

/* Tek sayı: resolver gölgeyi kurar, geri kurma rm'yi geri verir. iz: her adım. */
static int tek(const char *m, int iz)
{
    static sayi orj;
    int r;
    if (!oku(&GA.rm, m)) { printf("okunamadı ya da çok büyük: %s\n", m); return 2; }
    GA.rm_taze = 1; GA.golge_taze = 0;
    printf("N   = %s\nrm  = %s_8   (%d sekizlik hane)\n\n", m10(&GA.rm, 0), m8(&GA.rm, 1), GA.rm.n);
    if (GA.rm.n == 0) { printf("0'ın gölgesi kurulmaz (0'ın çarpanı yok).\n"); return 0; }
    kopya(&orj, &GA.rm);
    printf("RESOLVER\n");
    r = resolver(&GA, iz);
    if (r < 0) { printf("sayaç taştı: bir kanalda e > 4095\n"); return 1; }
    if (iz) printf("  ÇIKTI\n");
    golge_yaz(&GA);
    printf("\nGERİ KURMA   rm = rc · ∏ q^e\n");
    if (!geri_kur(&GA, iz ? 2 : 1)) { printf("taşma\n"); return 1; }
    r = kiyas(&GA.rm, &orj) == 0;
    printf("    rm = %s_8 = %s   %s\n", m8(&GA.rm, 0), m10(&GA.rm, 1), r ? "birebir ✓" : "FARKLI ✗");
    return r ? 0 : 1;
}

/* İki sayıyı okur ve başlığı yazar. */
static int iki_oku(const char *a, const char *b)
{
    static sayi s;
    if (!oku(&s, a)) { printf("okunamadı: %s\n", a); return 0; }
    h_yukle(&GA, &s);
    if (!oku(&s, b)) { printf("okunamadı: %s\n", b); return 0; }
    h_yukle(&GB, &s);
    printf("A = %s\n  = %s_8   (%d hane)\n", m10(&GA.rm, 0), m8(&GA.rm, 1), GA.rm.n);
    printf("B = %s\n  = %s_8   (%d hane)\n\n", m10(&GB.rm, 0), m8(&GB.rm, 1), GB.rm.n);
    return 1;
}

/* Sonucu ondalık ve sekizlik yazar. */
static void sonuc_yaz(const char *ad, const hunter *R, const char *isaret)
{
    printf("%s = %s%s\n", ad, isaret, m10(&R->rm, 0));
    printf("%*s = %s%s_8   (%d hane)\n", (int)strlen(ad), "", isaret, m8(&R->rm, 1), R->rm.n);
}

/* --topla / --cikar: mantissada hane hane; sonucun gölgesi bayat (tembel), istenirse resolver kurar. */
static int toplama_cikarma(const char *a, const char *b, int cik)
{
    const char *isaret = "";
    if (!iki_oku(a, b)) return 2;
    if (!cik) {
        printf("TOPLAMA mantissada (rm), sekizlik hane hane, elde ile\n");
        if (!h_topla(&GR, &GA, &GB)) { printf("taşma\n"); return 1; }
        sonuc_yaz("A+B", &GR, "");
    } else {
        printf("ÇIKARMA mantissada (rm), sekizlik hane hane, ödünç ile\n");
        if (h_cikar(&GR, &GA, &GB) < 0) { h_cikar(&GR, &GB, &GA); isaret = "-"; }
        sonuc_yaz("A-B", &GR, isaret);
    }
    printf("\nGÖLGE bayat (tembel gölge): toplama ve çıkarma sayaçları güncellemez.\n");
    if (GR.rm.n == 0) { printf("Sonuç 0: gölge kurulmaz.\n"); return 0; }
    printf("Bir sonraki çarpmada resolver şunu kuracak%s:\n", *isaret ? " (mutlak değer)" : "");
    if (golge_hazir(&GR) != 1) { printf("sayaç taştı\n"); return 1; }
    golge_yaz(&GR);
    return 0;
}

/* Bir kanal satırı: e(A) op e(B) = sonuç, sekizlik hücreleriyle. */
static void kanal_satiri(int k, const char *op)
{
    printf("    kanal %2u : %4u %s %4u = %4u   [rs1..rs4: %u %u %u %u]\n", KQ[k], us(&GA, k), op, us(&GB, k),
           us(&GR, k), GR.rs[0][k], GR.rs[1][k], GR.rs[2][k], GR.rs[3][k]);
}

/* --carp: resolver iki sayıyı birer kez ölçer; çarpma yalnız sayaçları toplar ve rc'leri çarpar. */
static int carpma(const char *a, const char *b)
{
    static sayi dogrudan;
    int k, r;
    if (!iki_oku(a, b)) return 2;
    if (h_sifir(&GA) || h_sifir(&GB)) { printf("Çarpanlardan biri 0: A·B = 0\n"); return 0; }
    if (golge_hazir(&GA) != 1 || golge_hazir(&GB) != 1) { printf("sayaç taştı\n"); return 1; }
    printf("A gölgesi (resolver)\n"); golge_yaz(&GA);
    printf("B gölgesi (resolver)\n"); golge_yaz(&GB);
    if (h_carp(&GR, &GA, &GB) != 1) { printf("taşma: sayaç e > 4095 ya da hane sınırı\n"); return 1; }
    printf("\nÇARPMA gölgede: resolver çalışmaz, sayaçlar hücre hücre elde ile toplanır\n");
    for (k = 0; k < KANAL; k++) if (us(&GR, k)) kanal_satiri(k, "+");
    printf("    rc(A·B) = rc(A) · rc(B) = %s_8\n", m8(&GR.rc, 0));
    printf("A·B gölgesi\n"); golge_yaz(&GR);
    printf("\nGERİ KURMA\n");
    if (!geri_kur(&GR, 1)) { printf("taşma\n"); return 1; }
    sonuc_yaz("A·B", &GR, "");
    r = carp(&dogrudan, &GA.rm, &GB.rm) && kiyas(&dogrudan, &GR.rm) == 0;
    printf("DENETİM: rm(A)·rm(B) doğrudan hane çarpımıyla %s\n", r ? "aynı ✓" : "FARKLI ✗");
    return r ? 0 : 1;
}

/* --bol: gölgede üs çıkarma ve rc bölmesi; bölünemiyorsa nedenini söyler. */
static int bolme(const char *a, const char *b)
{
    int k, r, neden = 0;
    if (!iki_oku(a, b)) return 2;
    r = h_bol(&GR, &GA, &GB, &neden);
    if (r < 0) { printf("bölme tanımsız (B = 0) ya da taşma\n"); return 1; }
    if (h_sifir(&GA)) { printf("A = 0: A/B = 0\n"); return 0; }
    printf("A gölgesi (resolver)\n"); golge_yaz(&GA);
    printf("B gölgesi (resolver)\n"); golge_yaz(&GB);
    if (r == 0) {
        if (neden < KANAL)
            printf("\nBÖLÜNEMEZ: kanal %u'de e(A) = %u < e(B) = %u\n", KQ[neden], us(&GA, neden), us(&GB, neden));
        else
            printf("\nBÖLÜNEMEZ: rc(B) = %s, rc(A) = %s'yı bölmüyor\n", m10(&GB.rc, 0), m10(&GA.rc, 1));
        return 0;
    }
    printf("\nBÖLME gölgede: sayaçlar hücre hücre ödünç ile çıkarılır\n");
    for (k = 0; k < KANAL; k++) if (us(&GA, k)) kanal_satiri(k, "-");
    printf("    rc(A/B) = rc(A) / rc(B) = %s_8\n", m8(&GR.rc, 0));
    printf("\nGERİ KURMA\n");
    if (!geri_kur(&GR, 1)) { printf("taşma\n"); return 1; }
    sonuc_yaz("A/B", &GR, "");
    return 0;
}

/* Kullanım satırları. */
static void kullanim(void)
{
    printf("kullanım: hunter_cekirdek N | --iz N | --carp A B | --topla A B | --cikar A B | --bol A B | --test\n"
           "sayı: ondalık 744, sekizlik 1350_8, kuvvet 3^14\n");
}

int main(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "--test") == 0) return test();
    if (argc == 2 && argv[1][0] != '-') return tek(argv[1], 0);
    if (argc == 3 && strcmp(argv[1], "--iz") == 0) return tek(argv[2], 1);
    if (argc == 4 && strcmp(argv[1], "--carp") == 0) return carpma(argv[2], argv[3]);
    if (argc == 4 && strcmp(argv[1], "--topla") == 0) return toplama_cikarma(argv[2], argv[3], 0);
    if (argc == 4 && strcmp(argv[1], "--cikar") == 0) return toplama_cikarma(argv[2], argv[3], 1);
    if (argc == 4 && strcmp(argv[1], "--bol") == 0) return bolme(argv[2], argv[3]);
    kullanim();
    return 2;
}
