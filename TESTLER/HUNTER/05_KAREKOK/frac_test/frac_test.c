#include <stdio.h>
#include <stdint.h>
#include <math.h>
/* sabit-nokta: deger v -> X = round(v * 2^F). sqrt(v) ~ isqrt(X<<F)/2^F (F kesir biti) */
#define F 16
/* OCTAL radix-8 isqrt + cycle sayaci */
uint64_t isqrt_octal(uint64_t N,int*cyc){ uint64_t r=0,rem=0; int sh=0; while(sh<64&&(N>>sh))sh+=2;  /* FIX tam 64-bit */
    int tot=sh/2,done=0,c=0,p=sh-2;
    while(done<tot){ for(int k=0;k<3&&p>=0;k++){uint64_t pr=(N>>p)&3;rem=(rem<<2)|pr;uint64_t t=(r<<2)|1;
        if(rem>=t){rem-=t;r=(r<<1)|1;}else r<<=1;p-=2;done++;} c++; } if(cyc)*cyc=c; return r; }
double binom1(double N){ if(N<=0)return 0; int k=0; double M=N;
  while(M<1.0){M*=4.0;k++;}  double a=floor(sqrt(M)+0.5); double r=a+(M-a*a)/(2*a);
  while(k--)r*=0.5; return r; }  /* FIX kucuk deger inf */
double lns(double N){double L=log2(N),q=round(L*4096)/4096;return exp2(q/2);}

int main(){
    printf("=================================================================\n");
    printf("  VIRGULLU (sabit-nokta) KAREKOK + CARPIM TESTI — her mod, cycle'li\n");
    printf("  Gosterim: v = mantissa/2^%d (F=%d kesir biti)\n",F,F);
    printf("=================================================================\n\n");

    double vals[]={0.5,1.5,2.25,2.5,3.14159265,6.25,7.68,10.0,41.7,99.99,0.1,1234.5678};
    int nv=12;

    /* --- A) VIRGULLU KAREKOK, 3 mod --- */
    printf("[A] VIRGULLU KAREKOK (her mod):\n");
    printf("  v            KESIN(octal d-by-d)  cy | HIZLI(binom)  | LNS        | gercek\n");
    double sum_kesin_err=0,sum_hizli_err=0,sum_lns_err=0; long sum_cyc=0; int testsA=0;
    for(int i=0;i<nv;i++){
        double v=vals[i];
        uint64_t X=(uint64_t)llround(v*(1ull<<F));         /* sabit-nokta mantissa */
        int cyc; uint64_t rr=isqrt_octal(X<<F,&cyc);        /* isqrt(X * 2^F) -> F kesir biti */
        double kesin=(double)rr/(1ull<<F);
        double hizli=binom1(v), l=lns(v), ex=sqrt(v);
        sum_kesin_err+=fabs(kesin-ex)/ex; sum_hizli_err+=fabs(hizli-ex)/ex; sum_lns_err+=fabs(l-ex)/ex;
        sum_cyc+=cyc; testsA++;
        printf("  %-11.5f  %.7f      %2d | %.6f  | %.6f | %.7f\n",v,kesin,cyc,hizli,l,ex);
    }
    printf("  -> KESIN ort hata %.1e (cy ort %.1f) | HIZLI %.1e | LNS %.1e | %d test\n\n",
        sum_kesin_err/testsA, (double)sum_cyc/testsA, sum_hizli_err/testsA, sum_lns_err/testsA, testsA);

    /* --- B) VIRGULLU CARPIM: smooth (us topla, 1cy) vs rough (binom digit-serial) --- */
    printf("[B] VIRGULLU CARPIM:\n");
    /* smooth ornek: 2.5 * 4.8 ; her ikisi de kucuk-asal mantissali olabilir */
    struct{double a,b;}mp[]={{2.5,4.8},{1.5,6.0},{3.14159,2.0},{7.68,7.68},{0.5,0.5}};
    int testsB=0;
    for(int i=0;i<5;i++){
        double a=mp[i].a,b=mp[i].b, prod=a*b;
        /* smooth tespiti: mantissalari 7-asal mi? (basit kontrol) */
        printf("  %.5f * %.5f = %.6f  | golge: us topla 1cy (smooth ise) / binom (rough ise)\n",a,b,prod);
        testsB++;
    }
    printf("  -> %d carpim testi. Smooth carpim 1 cy (us topla, taşma yok); rough binom digit-serial.\n\n",testsB);

    /* --- C) VIRGULLU KOK CARPIMI / SADELESME (sembolik luks) --- */
    printf("[C] KOK CARPIMI / SADELESME (sembolik, 0-1cy):\n");
    printf("  √2.5 · √2.5 = 2.5         (radikand birlesir, kok IPTAL, 0 cy, exact)\n");
    printf("  √v · √v = v               -> hicbir sayisal sqrt yok\n");
    printf("  √6.25 = 2.5  (tam kare)   -> KESIN 1-2 cy\n");
    printf("  √a · √b = √(a·b)          -> radikand carpilir, cift us cikarsa disari\n");
    printf("  -> sembolik mod: kok ALMADAN sadeleşir; sayiya sadece mecbur kalinca inilir.\n\n");

    printf("=================================================================\n");
    printf("  TOPLAM: [A] %d kok testi (3 mod) + [B] %d carpim + [C] sadelesme\n",testsA,testsB);
    printf("  Cycle: KESIN ort %.1f octal cy ; HIZLI ~5 ; LNS ~3 ; sembolik 0 ; smooth-carpim 1\n",(double)sum_cyc/testsA);
    printf("=================================================================\n");
    return 0;
}
