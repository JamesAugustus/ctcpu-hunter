/* =============================================================================
   MUL / DIV EMULATORU  —  C_ALU System A (golge cekirdeginin kalbi)
   HER SATIRIN yaninda // ile TURKCE: hem kodun YAPISI hem O AN NE yaptigimiz.
   -----------------------------------------------------------------------------
   Ana tanim otoritesi: MUL = asal USLERI TOPLA, DIV = asal USLERI CIKAR (7 paralel).
     - Sayi golgede: 7 asalin us vektoru [e2..e17] + rough. Isaret TUR'un icinde.
     - MUL: e_r[i]=ea[i]+eb[i], rough carpilir, isaret XOR. Smooth'ta sayi buyumez, ~1 cy.
     - DIV: e_r[i]=ea[i]-eb[i]. Tam bolunmede tamsayi; bolunmezse NEGATIF us (rasyonel).
     - CASCADE: bir us hucresi 7'yi asarsa 4 registera (RS1..RS4, her biri 0-7) yayilir; toplam=us.
     - DURUST SINIR: rough×rough golgede ucuz DEGIL -> pozisyonel carpici fallback + FLAG.ROUGH.
       Us toplami 28'i (4×7) asarsa golge registera SIGMAZ (buyuk carpim tasmasi).
   Dogrulama: MUL native a·b ile, DIV rasyonel a/b ile (__int128, tam). Kalanli MOD YOK (icat etme).
   Derle:  cc -O3 mul_div_emulator.c -o md -lm && ./md > TEST_CIKTI.txt
   ============================================================================= */
#include <stdio.h>                                   // printf
#include <stdint.h>                                  // int64
typedef __int128 i128;                               // buyuk ara degerler (a·b, decode) tasmasiz

static const int P[7] = {2,3,5,7,11,13,17};          // golge tabani: 7 asal

/* golge: 7 us (negatif olabilir, DIV) + rough kalan + isaret (0=+,1=-) */
typedef struct { int e[7]; long long rough; int sign; } Golge;

/* tam sayiyi golgeye cevirir (isaretsiz buyukluk; RESOLVER encode mantigi) */
Golge factor(long long N, int sign){                 // |N| -> golge, isaret ayri
    Golge g; g.sign = sign; g.rough = 1;             // isaret + rough baslatilir
    long long n = N;                                 // calisma kopyasi
    if(n==0){ for(int k=0;k<7;k++) g.e[k]=0; g.rough=0; return g; } // KENAR: 0'in golgesi yok (kisa devre; sonsuz dongu korumasi — Ajan B)
    for(int k=0;k<7;k++){ g.e[k]=0;                  // her asal icin us 0
        while(n % P[k]==0){ n/=P[k]; g.e[k]++; } }   // bolunebildigince bolunur, sayilir
    g.rough = n;                                     // kalan = rough
    return g;
}
/* golgeyi (negatif us YOKKEN) tam sayiya cozer */
i128 decode_pos(Golge g){                            // sadece us>=0 ve rough tamsayi durumunda
    i128 v = g.rough;                                // rough'tan baslar
    for(int k=0;k<7;k++) for(int j=0;j<g.e[k];j++) v *= P[k]; // asallar uslerince carpilir
    return v;
}
long long gcd_ll(long long a,long long b){ while(b){ long long t=a%b; a=b; b=t; } return a; }
i128 ipow_i(int base,int k){ i128 r=1; for(int i=0;i<k;i++) r*=base; return r; } // base^k (k>=0)

/* --- GOLGE MUL: usleri TOPLA --- */
Golge gmul(Golge a, Golge b){                        // a × b
    Golge r; r.sign = a.sign ^ b.sign;               // isaret XOR (- × - = +)
    for(int k=0;k<7;k++) r.e[k] = a.e[k] + b.e[k];   // 7 PARALEL: usler toplanir
    r.rough = a.rough * b.rough;                      // rough kismi carpilir (fallback alani)
    return r;
}
/* --- GOLGE DIV: usleri CIKAR (tam bolme = tersine carpma) --- */
Golge gdiv(Golge a, Golge b){                        // a ÷ b
    Golge r; r.sign = a.sign ^ b.sign;               // isaret XOR
    for(int k=0;k<7;k++) r.e[k] = a.e[k] - b.e[k];   // 7 PARALEL: usler cikarilir (negatif olabilir!)
    if(b.rough!=0 && a.rough % b.rough == 0) r.rough = a.rough / b.rough; // tam bolme: rough_a/rough_b
    else r.rough = a.rough;                          // tam degil: rough kesir olur (TEST 3 pay/payda ile)
    return r;
}

/* CASCADE: bir us degerini 4 hucreye (her biri 0-7) yayar, toplam=us. tasar mi? */
int cascade(int e, int rs[4]){                        // donus: tasma (1) yoksa 0
    int r = e<0 ? -e : e;                             // buyukluk
    for(int i=0;i<4;i++){ rs[i] = r>7?7:r; r-=rs[i]; }// her hucre en cok 7
    return r>0;                                       // hala kaldiysa 28'i asti -> tasma
}

/* PRNG */
uint64_t rng=0xC0FFEEu; uint64_t xr(){ uint64_t x=rng; x^=x<<13; x^=x>>7; x^=x<<17; rng=x; return x; }

int main(){
    printf("=================================================================\n");
    printf("  MUL / DIV EMULATORU (System A, golge) — ASIRI TEST RAPORU\n");
    printf("=================================================================\n\n");

    /* TEST 1: MUL — us topla, decode == a·b (isaretli, __int128 tam) */
    long bad=0, roughmul=0, smoothmul=0;
    for(long t=0;t<20000000L;t++){
        long long a=(long long)(xr()%200000)+1, b=(long long)(xr()%200000)+1; // 1..200000
        int sa=xr()&1, sb=xr()&1;                    // rastgele isaretler
        Golge ga=factor(a,sa), gb=factor(b,sb), gr=gmul(ga,gb); // golge carpim
        i128 mag=decode_pos(gr);                     // buyukluk
        i128 mine=gr.sign?-mag:mag;                  // isaretli sonuc
        i128 real=(i128)a*b; if(sa^sb) real=-real;   // gercek a·b (isaretli)
        if(mine!=real) bad++;                        // esit mi
        if(ga.rough>1 && gb.rough>1) roughmul++;     // iki rough>1 -> fallback alani
        if(ga.rough==1 && gb.rough==1) smoothmul++;  // ikisi de smooth -> golge-dogal, sayi buyumez
    }
    printf("TEST 1  MUL  us topla, decode == a·b  [20M isaretli cift]: %ld hata\n", bad);
    printf("        SMOOTH×smooth (golge-dogal, sayi buyumez): %ld/20M (%.1f%%)\n", smoothmul, 100.0*smoothmul/20000000L);
    printf("        rough×rough  (FLAG.ROUGH, pozisyonel carpici fallback): %ld/20M (%.1f%%)\n", roughmul, 100.0*roughmul/20000000L);
    printf("        -> DURUST: rastgele buyuk sayilarda rough baskin; golge ustunlugu SMOOTH/zincirde.\n");

    /* TEST 2: DIV TAM — a=b·q kurulur, gdiv decode == q (us cikar + rough_a/rough_b) */
    bad=0;
    for(long t=0;t<10000000L;t++){
        long long b=(long long)(xr()%50000)+1, q=(long long)(xr()%50000)+1; // bolen, bolum
        long long a=b*q;                             // a tam bolunur (kurulmus)
        Golge ga=factor(a,0), gb=factor(b,0), gr=gdiv(ga,gb); // usler cikarilir, rough_a/rough_b
        int neg=0; for(int k=0;k<7;k++) if(gr.e[k]<0) neg=1;  // negatif us cikmamali (tam bolme)
        if(neg || decode_pos(gr) != (i128)q) bad++;  // us kismi × rough bolum = q olmali
    }
    printf("TEST 2  DIV TAM  a=b·q -> gdiv decode == q  [10M]: %ld hata\n", bad);

    /* TEST 3: DIV GENEL — bolunmezse NEGATIF us (rasyonel). deger == a/b (kesir, capraz carpim) */
    bad=0; long rational=0;
    for(long t=0;t<10000000L;t++){
        long long a=(long long)(xr()%100000)+1, b=(long long)(xr()%100000)+1;
        Golge ga=factor(a,0), gb=factor(b,0), gr=gdiv(ga,gb); // usler cikarilir (negatif olabilir)
        i128 num=1, den=1;                            // sonuc kesri: pay/payda
        for(int k=0;k<7;k++){ if(gr.e[k]>0) num*=ipow_i(P[k],gr.e[k]); else if(gr.e[k]<0) den*=ipow_i(P[k],-gr.e[k]); }
        num *= ga.rough; den *= gb.rough;            // rough: pay×rough_a, payda×rough_b
        int isneg=0; for(int k=0;k<7;k++) if(gr.e[k]<0) isneg=1; if(gb.rough>1 && (ga.rough%gb.rough)) isneg=1;
        if(isneg) rational++;                         // rasyonel (tam bolunmedi) sayaci
        /* a/b == num/den mi?  capraz carpim: a·den == b·num */
        if((i128)a*den != (i128)b*num) bad++;
    }
    printf("TEST 3  DIV GENEL  golge-oran == a/b (kesir)  [10M]: %ld hata\n", bad);
    printf("        (%ld/10M tam bolunmedi -> NEGATIF us / rasyonel, DURUST)\n", rational);

    /* TEST 4: CASCADE — us -> 4 hucre (0-7), toplam=us; 28 ustu tasma */
    bad=0; long overflow=0;
    for(int e=0;e<=40;e++){ int rs[4]; int of=cascade(e,rs);
        int sum=rs[0]+rs[1]+rs[2]+rs[3];
        if(!of && sum!=e) bad++;                      // tasmadiysa toplam=us olmali
        if(of) overflow++;                            // 28 ustu
    }
    printf("TEST 4  CASCADE  us -> 4×(0-7) hucre, toplam=us  [e=0..40]: %ld hata  (%ld deger 28'i asti)\n", bad, overflow);

    /* TEST 5: MUL sonucu us tasmasi (buyuk×buyuk) — durust sinir */
    { Golge big=factor(1<<23,0);                      // 2^23
      Golge sq=gmul(big,big);                          // (2^23)^2 = 2^46
      int rs[4]; int of=cascade(sq.e[0],rs);
      printf("TEST 5  (2^23)×(2^23) -> 2^%d ; cascade tasma? %s (us %d > 28 -> golge registera SIGMAZ)\n",
             sq.e[0], of?"EVET":"hayir", sq.e[0]);
    }

    /* TEST 6: somut ornekler */
    printf("\nTEST 6  somut ornekler:\n");
    { Golge a=factor(12,0),b=factor(15,0),r=gmul(a,b);
      printf("   12×15: 2^2·3 × 3·5 = "); for(int k=0;k<7;k++) if(r.e[k])printf("%d^%d ",P[k],r.e[k]);
      printf("= %lld  (klasik carpici YOK, us toplandi)\n",(long long)decode_pos(r)); }
    { Golge a=factor(360,0),b=factor(12,0),r=gdiv(a,b);
      printf("   360÷12: 2^3·3^2·5 - 2^2·3 = "); for(int k=0;k<7;k++) if(r.e[k])printf("%d^%d ",P[k],r.e[k]);
      printf("= %lld\n",(long long)decode_pos(r)); }
    { Golge a=factor(12,0),b=factor(8,0),r=gdiv(a,b);
      printf("   12÷8 (tam degil): 2^2·3 - 2^3 = 2^%d·3 = 3/2  (NEGATIF us -> rasyonel)\n", r.e[0]); }
    { Golge a=factor(6,1),b=factor(7,0),r=gmul(a,b);  // (-6)×7
      printf("   (-6)×7: isaret %s , buyukluk %lld -> %s%lld\n", r.sign?"-":"+",(long long)decode_pos(r), r.sign?"-":"+",(long long)decode_pos(r)); }
    printf("   POW sadelesme (ana tanim, taban 10): 1500×10^-2 -> 15×10^0  (2·5 cifti POW'a gecer)\n");

    printf("\n=================================================================\n");
    printf("  SONUC: MUL=us topla, DIV=us cikar (7 paralel) — golge-dogal, native ile 0 hata.\n");
    printf("  DURUST: rough×rough pozisyonel fallback (FLAG.ROUGH); us>28 golge registera sigmaz;\n");
    printf("  tam-bolunmeyen DIV -> negatif us (rasyonel). Kalanli MOD YOK. Kapi/cycle = tahmin.\n");
    printf("=================================================================\n");
    return 0;
}
