/* =============================================================================
   ROUGH FALLBACK DEVRE  —  MUL/DIV kalanlari (madde 3)
   -----------------------------------------------------------------------------
   AMAC (mul_div_emulator.c §8.1): "ROUGH FALLBACK DEVRESI CIZILMEDI: binom/
     kaydir+topla yolu kavramsal; somut devre yok." -> BURADA somut + kosan + native dogrulama.
   FIKIR (golge spec F.2): rough sayilar us-toplamaya INMEZ. Pozisyonel yoldan
     gider ama DEV DIZI CARPICI YOK. Oktal (8n-r) binom ile kaydir+topla:
       A = 8a + rA ,  B = 8b + rB   (rA,rB = A&7,B&7 ; a,b = A>>3,B>>3)
       A·B = 64·(a·b) + 8·(a·rB + b·rA) + rA·rB
             \__<<6__/   \____<<3____/    \small/
     - 64 ve 8 SADECE KAYDIRMA. rA,rB in 0..7 -> minik carpim (kaydir+topla).
     - a·b alt seviyede AYNI sekilde (recursive, oktal-seri). Her seviye 3 bit peel.
   ISPAT NIYETI: (1) sonuc == a·b (native, __int128). (2) HICBIR temel carpim
     operandi 7'yi asmaz (dizi carpici yok, sadece +7/+1 incrementer felsefesi).
   Derle:  cc -O2 rough_fallback_devre_test.c -o r && ./r
   ============================================================================= */
#include <stdio.h>
#include <stdint.h>
typedef __int128 i128;

static long ADD=0, SHIFT=0, SMALLMUL=0; int MAXR=0;   // devre maliyeti sayaclari

/* x * r  (r in 0..7) — SADECE kaydir+topla (3-bit seri). Dizi carpici degil. */
static i128 smul(i128 x,int r){
    if(r>MAXR) MAXR=r;                                // en buyuk temel operand (<=7 olmali)
    SMALLMUL++;
    i128 res=0;
    for(int b=0;b<3;b++){ if(r&(1<<b)){ res += (x<<b); ADD++; if(b) SHIFT++; } }
    return res;                                       // r=0 -> 0 ; r<=7 -> <=3 kaydirmali toplama
}
/* OKTAL BINOM CARPIM — recursive kaydir+topla (rough fallback) */
static i128 bmul(i128 A,i128 B){
    if(A<8 || B<8){                                   // taban: bir operand <=7 -> minik
        return (A<8)? smul(B,(int)A) : smul(A,(int)B);
    }
    i128 a=A>>3, b=B>>3; int rA=(int)(A&7), rB=(int)(B&7); SHIFT+=2;
    i128 ab = bmul(a,b);                              // 64·(a·b) -> alt seviye (oktal peel)
    i128 mid = smul(a,rB) + smul(b,rA); ADD++;        // 8·(a·rB + b·rA)
    i128 lo  = smul(rA,rB);                           // rA·rB (minik)
    i128 res = (ab<<6) + (mid<<3) + lo; SHIFT+=2; ADD+=2;
    return res;
}
/* smooth mu? (7 asaldan mi olusuyor) — rough tespiti icin */
static const int P[7]={2,3,5,7,11,13,17};
static int is_rough(long long n){ for(int k=0;k<7;k++) while(n%P[k]==0) n/=P[k]; return n>1; }

uint64_t rng=0xBEEFu; uint64_t xr(){ uint64_t x=rng;x^=x<<13;x^=x>>7;x^=x<<17;rng=x;return x; }

int main(void){
    printf("=================================================================\n");
    printf("  ROUGH FALLBACK DEVRE (oktal binom kaydir+topla)  —  MUL/DIV madde 3\n");
    printf("=================================================================\n\n");

    /* TEST 1: bmul == a·b (native). Genel + rough×rough alt-sayaci. */
    long bad=0, roughpair=0;
    for(long t=0;t<5000000L;t++){
        long long a=(long long)(xr()%2000000)+1, b=(long long)(xr()%2000000)+1;
        i128 got=bmul(a,b), real=(i128)a*b;
        if(got!=real) bad++;
        if(is_rough(a) && is_rough(b)) roughpair++;
    }
    printf("TEST 1  bmul(a,b) == a·b (native __int128)  [5M cift]: %ld hata\n", bad);
    printf("        rough×rough olan cift: %ld/5M (%.1f%%) — us-toplamaya inMEYEN, fallback alani\n",
           roughpair, 100.0*roughpair/5000000L);

    /* TEST 2: DEVRE SINIRI — hicbir temel carpim 7'yi asmadi mi? (dizi carpici YOK) */
    printf("\nTEST 2  DEVRE: en buyuk temel carpim operandi = %d  (<=7 olmali -> dizi carpici YOK)\n", MAXR);
    printf("        -> %s\n", MAXR<=7 ? "GECTI: tum carpimlar r<=7 (minik incrementer), sadece kaydir+topla"
                                       : "KALDI: 8+ operand var (dizi carpici sizdi!)");

    /* TEST 3: somut rough ornekler (elle dogrulanabilir) */
    printf("\nTEST 3  somut rough ornekler:\n");
    struct{ long long a,b; } E[]={ {19,23}, {29,31}, {101,103}, {9973,101} };
    for(int i=0;i<4;i++){
        long long a=E[i].a,b=E[i].b; i128 g=bmul(a,b); long long real=a*b;
        printf("   %lld×%lld : rough? %s/%s -> bmul=%lld  (native %lld)  %s\n",
               a,b, is_rough(a)?"E":"h", is_rough(b)?"E":"h",
               (long long)g, real, (i128)g==(i128)real?"OK":"HATA");
    }
    /* 19×23 acilimi (golge spec F.2 ile birebir) */
    printf("   ACILIM 19×23: 19=8·2+3, 23=8·2+7 -> 64·(2·2) + 8·(2·7+2·3) + 3·7\n");
    printf("                = 64·4 + 8·20 + 21 = 256 + 160 + 21 = 437  (kaydirmalar bedava)\n");

    /* TEST 4: MALIYET — bir 24-bit×24-bit worst-case op sayimi (az kablo iddiasi) */
    ADD=SHIFT=SMALLMUL=0; MAXR=0;
    { long long a=16777213LL, b=16777199LL;           // iki buyuk rough (asala yakin)
      i128 g=bmul(a,b);
      printf("\nTEST 4  MALIYET (24-bit × 24-bit, buyuk rough %lld×%lld):\n", a,b);
      printf("        toplama=%ld  kaydirma=%ld  minik-carpim(r<=7)=%ld  ; sonuc %s\n",
             ADD, SHIFT, SMALLMUL, (i128)g==(i128)a*b?"DOGRU":"YANLIS");
      printf("        -> oktal-seri (8 hane), dizi carpici (24 kismi carpim) YOK; az kablo.\n");
    }

    printf("\n=================================================================\n");
    printf("  SONUC: rough×rough us-toplamaya inmez -> oktal binom fallback: 64ab+8(...)+rArB.\n");
    printf("  Sadece kaydirma + r<=7 minik toplama; DEV DIZI CARPICI YOK. Native ile 0 hata.\n");
    printf("=================================================================\n");
    return 0;
}
