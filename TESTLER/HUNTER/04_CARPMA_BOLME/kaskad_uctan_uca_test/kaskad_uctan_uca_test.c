/* =============================================================================
   KASKAD UCTAN UCA + US>28 DEMO  —  MUL/DIV kalanlari (madde 1 ve 2)
   -----------------------------------------------------------------------------
   AMAC (mul_div_emulator.c §8.1 acik maddeleri):
     (1) "CASCADE UCTAN UCA BAGLI DEGIL: us tek int; RS1-4 hucrelerine yazilip
          geri okunmuyor." -> BURADA us GERCEKTEN 4 hucreye (0-7) yazilir,
          gmul/gdiv hucre temsili uzerinden calisir, geri okunur.
     (2) "US>28 ICIN CALISAN DEMO YOK." -> BURADA us>28 sinir davranisi KOSAN
          ornekle gosterilir (golge registera sigmaz -> OVF, pozisyonele duser).
   TEMSIL: her asalin ussu = golge katmanlari RS1..RS4, her hucre 3-bit (0-7).
     kapasite = 4×7 = 28. FLOOR yayilim (mevcut cascade() ile ayni: greedy).
     Negatif us SAKLANMAZ (kesir karari: payda mantissaya gider); bu dosya
     MUL ve TAM DIV (us>=0) icin cascade dogrular.
   Dogrulama: hucre round-trip + native __int128 karsilastirmasi.
   Derle:  cc -O2 kaskad_uctan_uca_test.c -o k && ./k
   ============================================================================= */
#include <stdio.h>
#include <stdint.h>
typedef __int128 i128;

static const int P[7]={2,3,5,7,11,13,17};       // 7 asal
#define KAT 4                                    // RS1..RS4
#define HUC 7                                    // hucre max (3-bit: 0-7)
#define KAP (KAT*HUC)                            // kapasite = 28

/* golge sayi: us'ler HUCRE biciminde saklanir (asil donanim temsili) */
typedef struct { int cell[7][KAT]; long long rough; int sign; int ovf; } G;

/* us -> 4 hucre (0-7), FLOOR greedy. donus: tasma (us>28) mi? */
static int enc(int e,int c[KAT]){
    int r=e;                                     // e>=0 varsayilir
    for(int i=0;i<KAT;i++){ c[i]= r>HUC?HUC:r; r-=c[i]; } // her hucre en cok 7
    return r>0;                                  // hala kaldi -> 28'i asti
}
/* 4 hucre -> us (topla) */
static int dec(const int c[KAT]){ int s=0; for(int i=0;i<KAT;i++) s+=c[i]; return s; }

/* tam sayi golgeye cevrilir + USLER HUCRELERE yazilir (encode yolu) */
static G factor_cells(long long N,int sign){
    G g; g.sign=sign; g.rough=1; g.ovf=0;
    long long n=N;
    if(n==0){ for(int k=0;k<7;k++) for(int i=0;i<KAT;i++) g.cell[k][i]=0; g.rough=0; return g; }
    for(int k=0;k<7;k++){ int e=0; while(n%P[k]==0){ n/=P[k]; e++; }
        if(enc(e,g.cell[k])) g.ovf=1; }          // us hucreye yazilirken 28'i asarsa OVF
    g.rough=n;
    return g;
}
/* golgeyi (hucrelerden OKUYARAK) tam sayiya cozer */
static i128 decode_cells(G g){
    i128 v=g.rough;
    for(int k=0;k<7;k++){ int e=dec(g.cell[k]); for(int j=0;j<e;j++) v*=P[k]; }
    return v;
}
/* MUL: her asalda us'ler HUCREDEN okunur, toplanir, HUCREYE geri yazilir (uctan uca) */
static G gmul_cells(G a,G b){
    G r; r.sign=a.sign^b.sign; r.rough=a.rough*b.rough; r.ovf=a.ovf|b.ovf;
    for(int k=0;k<7;k++){ int e=dec(a.cell[k])+dec(b.cell[k]);  // hucreden okunur + toplanir
        if(enc(e,r.cell[k])) r.ovf=1; }                          // hucreye geri yazilir, >28 -> OVF
    return r;
}
/* TAM DIV: us'ler hucreden okunur, cikarilir (us>=0 varsayimi), hucreye yazilir */
static G gdiv_cells(G a,G b){
    G r; r.sign=a.sign^b.sign; r.ovf=a.ovf|b.ovf;
    r.rough=(b.rough!=0 && a.rough%b.rough==0)? a.rough/b.rough : a.rough;
    for(int k=0;k<7;k++){ int e=dec(a.cell[k])-dec(b.cell[k]);
        if(e<0){ r.cell[k][0]=-1; }              // negatif -> bu dosyanin disi (kesir/payda)
        else enc(e,r.cell[k]); }
    return r;
}

uint64_t rng=0xC0FFEEu; uint64_t xr(){ uint64_t x=rng;x^=x<<13;x^=x>>7;x^=x<<17;rng=x;return x; }
static i128 ipow(int b,int k){ i128 r=1; for(int i=0;i<k;i++) r*=b; return r; }

int main(void){
    printf("=================================================================\n");
    printf("  KASKAD UCTAN UCA + US>28 DEMO  (MUL/DIV kalanlari 1-2)\n");
    printf("=================================================================\n\n");

    /* TEST 1: us -> hucre -> us round-trip. e=0..28 kayipsiz + her hucre<=7;
               e=29..56 OVF isaretli. */
    long bad=0,celbad=0,totalbad=0; int firstovf=-1;
    for(int e=0;e<=56;e++){ int c[KAT]; int of=enc(e,c);
        for(int i=0;i<KAT;i++) if(c[i]<0||c[i]>7) celbad++;      // hucre 0-7 disina cikti mi
        if(e<=KAP){ if(of||dec(c)!=e) bad++; }                   // <=28 tasmamali, geri==e
        else { if(!of && firstovf<0) firstovf=e; }               // >28 tasmali
    }
    printf("TEST 1  us->hucre->us round-trip [e=0..28]: %ld hata ; hucre 0-7 disi: %ld\n", bad, celbad);
    printf("        us>28 (e=29..56) OVF isaretlendi mi: %s (ilk kacan e=%d, -1=hepsi yakalandi)\n",
           firstovf<0?"EVET tumu":"HAYIR", firstovf);
    totalbad += bad + celbad + (firstovf >= 0);

    /* TEST 2: MUL UCTAN UCA — smooth operandlar DOGRUDAN us vektorunden kurulur,
               hucreye yazilir, gmul_cells, hucreden decode == a·b (native). */
    bad=0; long dene=0;
    for(long t=0;t<3000000L;t++){
        G a,b; a.sign=0;b.sign=0;a.rough=1;b.rough=1;a.ovf=0;b.ovf=0;
        i128 na=1,nb=1; int cap_ok=1;
        for(int k=0;k<7;k++){ int ea=xr()% (k<2?8:3), eb=xr()% (k<2?8:3); // kucuk usler (kapasite/tasma disinda tutulur)
            if(ea+eb>KAP){cap_ok=0;} enc(ea,a.cell[k]); enc(eb,b.cell[k]);
            na*=ipow(P[k],ea); nb*=ipow(P[k],eb); }
        if(!cap_ok) continue;                                    // us>28 durumu TEST 3'te
        G r=gmul_cells(a,b);
        i128 got=decode_cells(r), real=na*nb;
        if(r.ovf || got!=real) bad++;
        dene++;
    }
    printf("TEST 2  MUL uctan uca (hucre yaz/oku), decode==a·b [%ld smooth cift]: %ld hata\n", dene, bad);
    totalbad += bad;

    /* TEST 3: US>28 KOSAN DEMO — sinir davranisi (golge sigmaz -> OVF -> pozisyonel) */
    printf("\nTEST 3  US>28 SINIR DAVRANISI (kosan demo):\n");
    struct{ int e1,e2; const char*ad; } D[]={
        {14,14,"2^14 × 2^14"}, {23,23,"2^23 × 2^23"}, {20,15,"3^20 × 3^15"}, {7,7,"2^7 × 2^7"} };
    for(int d=0; d<4; d++){
        int base = d==2?3:2, k = d==2?1:0;                       // 3^.. ornegi icin asal 3
        G a,b; a.sign=b.sign=0; a.rough=b.rough=1; a.ovf=b.ovf=0;
        for(int kk=0;kk<7;kk++){ for(int i=0;i<KAT;i++){a.cell[kk][i]=0;b.cell[kk][i]=0;} }
        int oa=enc(D[d].e1,a.cell[k]), ob=enc(D[d].e2,b.cell[k]);
        G r=gmul_cells(a,b);
        int esum=D[d].e1+D[d].e2;
        if(oa || ob || r.ovf != (esum > KAP)) totalbad++;
        if(!r.ovf && decode_cells(r) != ipow(base,esum)) totalbad++;
        printf("   %-14s -> %d^%d  (us=%d) : ", D[d].ad, base, esum, esum);
        if(r.ovf) printf("US TASTI (>%d) -> golge registera SIGMAZ -> FLAG_OVF, deger pozisyonele/cok-registera duser\n", KAP);
        else printf("sigar (hucreler [%d,%d,%d,%d]) -> decode=%lld, golge-dogal\n",
                    r.cell[k][0],r.cell[k][1],r.cell[k][2],r.cell[k][3],(long long)decode_cells(r));
    }
    printf("   >>> SINIR: us=28 (2^28) son sigan; us=29+ OVF. Kaskad kapasitesi 4×7=28 tam burada.\n");

    /* TEST 4: TAM DIV uctan uca — a=b·q, gdiv_cells decode==q (us>=0, hucreden) */
    bad=0;
    for(long t=0;t<2000000L;t++){
        i128 nb=1,nq=1; G b,q; b.sign=q.sign=0;b.rough=q.rough=1;b.ovf=q.ovf=0;
        int cap=1;
        for(int k=0;k<7;k++){ int eb=xr()%(k<2?5:2), eq=xr()%(k<2?5:2);
            if(eb+eq>KAP)cap=0; enc(eb,b.cell[k]); enc(eq,q.cell[k]);
            nb*=ipow(P[k],eb); nq*=ipow(P[k],eq); }
        if(!cap) continue;
        /* a = b·q  (usler toplanir) */
        G a; a.sign=0;a.rough=1;a.ovf=0;
        for(int k=0;k<7;k++){ enc(dec(b.cell[k])+dec(q.cell[k]), a.cell[k]); }
        G r=gdiv_cells(a,b);                                     // a÷b == q olmali
        int neg=0; for(int k=0;k<7;k++) if(r.cell[k][0]<0) neg=1;
        if(r.ovf || neg || decode_cells(r)!=nq) bad++;
    }
    printf("\nTEST 4  TAM DIV uctan uca  a=b·q -> gdiv decode==q [2M]: %ld hata\n", bad);
    totalbad += bad;
    if(totalbad) return 1;

    printf("\n=================================================================\n");
    printf("  SONUC: us artik GERCEKTEN 4 hucreye (RS1-4, 0-7) yazilip okunuyor;\n");
    printf("  MUL/DIV hucre temsili uzerinden calisiyor (uctan uca). US>28 sinir\n");
    printf("  davranisi kosan demoyla gosterildi: kapasite 28, ustu OVF+pozisyonel.\n");
    printf("=================================================================\n");
    return 0;
}
