/* ============================================================================
   KAREKOK EMULATORU — CT-CPU karekok biriminin tum yontemleri + testleri
   Derle:  cc -O2 karekok_emulator.c -o kk -lm && ./kk
   Tum yontemler CARPICISIZ cekirdek mantigiyla (binom/Taylor/CF dogrulama icin
   kayan nokta kullanir; asil donanim yollari tamsayi kaydir+cikar'dir).
   ============================================================================ */
#include <stdio.h>
#include <stdint.h>
#include <math.h>

/* ---- 7 asal (golge) ---- */
static const int P[7]={2,3,5,7,11,13,17};

/* ============================================================================
   YOL 1 — SMOOTH (us yarila).  N'i asal uslerine ayir; ciftse disari, tekse mask.
   Donus: smooth ise tam_kisim doner, mask=kok icinde kalan asallar (7-bit), rough=kalan.
   ============================================================================ */
long smooth_sqrt(long N, int *mask, long *rough_out){
    int e[7]; long n=N;
    for(int i=0;i<7;i++){e[i]=0; while(n%P[i]==0){n/=P[i];e[i]++;}}
    *rough_out=n;                       /* 1 ise tam smooth; degilse rough kalan */
    long coef=1; *mask=0;
    for(int i=0;i<7;i++){ for(int k=0;k<e[i]/2;k++) coef*=P[i]; if(e[i]&1) *mask|=(1<<i); }
    return coef;                        /* sonuc = coef * sqrt( mask asallari ) * sqrt(rough) */
}

/* ============================================================================
   YOL 2 — √ASAL LUT (mask -> radikand degeri).  Sembolik; sayisal icin sqrt().
   ============================================================================ */
double lut_radikand(int mask){ long prod=1; for(int i=0;i<7;i++) if(mask&(1<<i)) prod*=P[i]; return sqrt((double)prod); }

/* ============================================================================
   YOL 3a — BINARY digit-by-digit (1 bit/cycle).  KESIN tam kisim + kalan.
   ============================================================================ */
uint64_t isqrt_bin(uint64_t N, uint64_t *rem_out){
    uint64_t root=0, rem=0; int sh=0; while(sh<64 && (N>>sh)) sh+=2;   /* FIX: tam 64-bit (eski sh<62 typo, >=2^62 bozuyordu) */
    for(int p=sh-2;p>=0;p-=2){ uint64_t pr=(N>>p)&3; rem=(rem<<2)|pr; uint64_t t=(root<<2)|1;
        if(rem>=t){rem-=t;root=(root<<1)|1;}else root<<=1; }
    if(rem_out)*rem_out=rem; return root;
}

/* ============================================================================
   YOL 3b — OCTAL RADIX-8 digit-by-digit (3 bit/cycle = 1 oktal hane/cycle).
   Ayni sonuc, cycle basina 3 binary hucre zincirlenir.  Cycle sayaci doner.
   ============================================================================ */
uint64_t isqrt_octal(uint64_t N, int *cycles){
    uint64_t root=0, rem=0; int sh=0; while(sh<64 && (N>>sh)) sh+=2;   /* FIX: tam 64-bit (eski sh<62 typo, >=2^62 bozuyordu) */
    int total=sh/2, done=0, cyc=0;
    int p=sh-2;
    while(done<total){
        for(int cell=0; cell<3 && p>=0; cell++){          /* 1 cycle = 3 hucre */
            uint64_t pr=(N>>p)&3; rem=(rem<<2)|pr; uint64_t t=(root<<2)|1;
            if(rem>=t){rem-=t;root=(root<<1)|1;}else root<<=1;
            p-=2; done++;
        }
        cyc++;
    }
    if(cycles)*cycles=cyc; return root;
}

/* ============================================================================
   YOL 4 — BINOM / CIPA (en yakin tam kareye yaslan, 1 terim).  Yaklasik.
   ============================================================================ */
double binom1(double N){
    if(N<=0) return 0;
    int k=0; double M=N;                  /* FIX: kucuk deger (v<0.25 -> a=0 -> INF) icin olceklenir */
    while(M<1.0){ M*=4.0; k++; }           /* M>=1 olana kadar x4 (=us 2) -> kok x2 */
    double a=floor(sqrt(M)+0.5); double r=a + (M-a*a)/(2*a);
    while(k--) r*=0.5;                     /* her x4 icin koku /2 geri */
    return r;
}

/* ============================================================================
   YOL 5 — TAYLOR (faktoriyel katsayili).  √N = a*sqrt(1+u), u=(N-a^2)/a^2.
   Katsayi C(1/2,k) merkezi binom (2k)!/(k!)^2 ile.
   ============================================================================ */
double taylor_sqrt(double N, int terms){
    /* FIX: faktoriyel YOK (fact(2k) k>=11 tasiyordu). Katsayi recurrence ile:
       (1+u)^0.5 = SUM c_k u^k ,  c_0=1 ,  c_k = c_{k-1}*(0.5-(k-1))/k . Tasma olmaz. */
    double a=floor(sqrt(N)+0.5); double u=(N-a*a)/(a*a);
    double sum=1, c=1, upow=1;
    for(int k=1;k<terms;k++){
        c *= (0.5-(k-1))/k;
        upow *= u;
        sum += c*upow;
    }
    return a*sum;
}

/* ============================================================================
   YOL 6 — log2 LNS (yaklasik):  √N = 2^(log2(N)/2).  Tek taban, evrensel.
   ============================================================================ */
double lns_sqrt(double N, int mant_bits){
    double L=log2(N); double q=round(L*(1<<mant_bits))/(1<<mant_bits); return exp2(q/2);
}

/* ============================================================================
   YOL 7 — SUREKLI KESIR (Cem):  √p = taban + artik/(2*taban + tekrar).
   ============================================================================ */
double cf_sqrt(double N, int iters){
    int t=(int)sqrt(N); int ex=(int)N - t*t; double f=0;
    for(int k=0;k<iters;k++) f=(double)ex/(2*t+f); return t+f;
}

/* ============================================================================
   TESTLER
   ============================================================================ */
int main(){
    printf("==================================================================\n");
    printf("  KAREKOK EMULATORU — testler\n");
    printf("==================================================================\n\n");

    /* TEST 1: octal d-by-d TUM tam kareler (n=0..3000) -> isqrt(n^2)==n */
    int bad=0,cyc;
    for(long n=0;n<=3000;n++) if(isqrt_octal((uint64_t)n*n,&cyc)!=(uint64_t)n) bad++;
    printf("TEST 1  octal d-by-d, tum tam kareler n=0..3000 : %d hata / 3001\n", bad);

    /* TEST 2: octal == binary (ayni sonuc) N=0..200000 */
    bad=0; for(uint64_t N=0;N<=200000;N++){ uint64_t r; if(isqrt_octal(N,&cyc)!=isqrt_bin(N,&r)) bad++; }
    printf("TEST 2  octal == binary, N=0..200000           : %d uyusmazlik\n", bad);

    /* TEST 3: floor dogrulugu N=0..1000000  (r^2<=N<(r+1)^2) */
    bad=0; for(uint64_t N=0;N<=1000000;N++){ uint64_t r=isqrt_octal(N,&cyc); if(!(r*r<=N && (r+1)*(r+1)>N)) bad++; }
    printf("TEST 3  floor dogru, N=0..1000000              : %d hata\n", bad);

    /* TEST 4: smooth yol — ornekler */
    printf("\nTEST 4  smooth (us yarila):\n");
    int mask; long rough;
    struct{long N;}sm[]={{144},{720},{129600},{49},{2124},{744}};
    for(int i=0;i<6;i++){ long c=smooth_sqrt(sm[i].N,&mask,&rough);
        const char* tag = (mask==0&&rough==1) ? "(TAM exact)"
                        : (rough!=1)          ? "(rough kalan -> kok icinde, sembolik)"
                        :                       "(kok-ici asal -> sembolik)";
        printf("   √%-7ld -> coef=%ld, mask=0x%02x, rough=%ld %s\n", sm[i].N,c,mask,rough, tag); }

    /* TEST 5: octal cycle sayisi */
    printf("\nTEST 5  octal cycle sayisi:\n");
    long ns[]={3969,65025,16777000};
    for(int i=0;i<3;i++){ isqrt_octal(ns[i],&cyc); printf("   √%-9ld : %d octal cycle\n",ns[i],cyc); }

    /* TEST 6: yaklasik yontemlerin hatasi (orneklerle) */
    printf("\nTEST 6  yaklasik yontemler (√59 = %.8f):\n", sqrt(59.0));
    printf("   binom1        = %.8f  (hata %.1e)\n", binom1(59), fabs(binom1(59)-sqrt(59))/sqrt(59));
    printf("   taylor 5 terim= %.8f  (hata %.1e)\n", taylor_sqrt(59,5), fabs(taylor_sqrt(59,5)-sqrt(59))/sqrt(59));
    printf("   log2-LNS 12bit= %.8f  (hata %.1e)\n", lns_sqrt(59,12), fabs(lns_sqrt(59,12)-sqrt(59))/sqrt(59));
    printf("   surekli kesir = %.8f  (hata %.1e, 5 iter)\n", cf_sqrt(59,5), fabs(cf_sqrt(59,5)-sqrt(59))/sqrt(59));

    /* TEST 7: yaklasik max hata (tum 24-bit, ornekleme) */
    double maxb=0; for(uint64_t N=2;N<=16777215;N+=7){ double e=fabs(binom1((double)N)-sqrt((double)N))/sqrt((double)N); if(e>maxb)maxb=e; }
    printf("\nTEST 7  binom1 MAX bagil hata (24-bit ornekleme): %.2e\n", maxb);

    /* TEST 8: 64-bit sinir (eski sh<62 bug duzeltildi mi?) */
    printf("\nTEST 8  64-bit sinir (eski sh<62 bug):\n");
    struct{uint64_t N,beklenen;}b64[]={
        {18446744065119617025ull,4294967295ull}, /* (2^32-1)^2 */
        {4611686018427387904ull, 2147483648ull},  /* 2^62 */
        {18446744073709551615ull,4294967295ull}}; /* 2^64-1 -> floor=2^32-1 */
    int b64bad=0;
    for(int i=0;i<3;i++){ int cc; uint64_t r=isqrt_octal(b64[i].N,&cc);
        int ok=(r==b64[i].beklenen);
        printf("   isqrt_octal(%llu)=%llu beklenen %llu %s\n",
            (unsigned long long)b64[i].N,(unsigned long long)r,(unsigned long long)b64[i].beklenen, ok?"OK":"YANLIS");
        if(!ok)b64bad++; }
    printf("   -> 64-bit: %d hata / 3 (0 ise sh fix calisti)\n", b64bad);

    printf("\n==================================================================\n");
    printf("  Tum cekirdek testler tamam. (Yontemler dosyada fonksiyon olarak.)\n");
    printf("==================================================================\n");
    return 0;
}
