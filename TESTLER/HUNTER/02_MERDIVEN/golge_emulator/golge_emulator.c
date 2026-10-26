/* ===========================================================================
   GOLGE EMULATOR  (CT-CPU shadow ko-prosesor)  -  MERDIVEN surumu (E1 2/2)
   Kaynak: a2 duzeltilmis surum uzerine 26 Tem 2026 donusumu:
   SAKLAMA katmani additif duz-vektorden MERDIVEN modeline (N6) cevrildi.
   Referans cekirdek: CEM_MODELI/golge_nihai.c + golge_carpma.c (birebir).
   Derle:  gcc -O2 -o golge golge_emulator.c   Calistir: ./golge
   ===========================================================================

   ====================  MIMARI: GOLGEYI NASIL KURUYORUZ?  ====================
   ILKE (20 Tem kapanisi): MERDIVEN BIR SAKLAMA FORMATIDIR, ARITMETIK
   FORMATI DEGIL. Iki katman vardir:

     SAKLAMA  = MERDIVEN: Row[4] (7 hucre x 3 bit + a) + RR.
                rough zorunlu TEK -> a yalniz 1/3/5/7; a=0 = "duz carpanim";
                bos satir 1 verir (terminal isareti GEREKMEZ);
                tasma = temsilin kendisi ("golgede 256 yok, 128x2").
                Tam 2^24: 0 hata, 0 carpisma, %100 kapsama (golge_nihai.c).

     ARITMETIK = ACILMIS calisma formu: (us vektoru, rough) ikilisi.
                Islem uc adimdir: AC -> ISLE (us topla / cikar / yarila /
                binom) -> YENIDEN ENCODE (merdivene konur).

   ADIM 1 - SAYI IKI FORMDA TUTULUR.
     (a) Pozisyonel (R0, normal sayi)      - toplama burada kolay.
     (b) Golge (merdiven saklama)          - carpma AC'ilmis formda kolay.
   ADIM 2 - ENCODE: sayi -> merdiven (golge_nihai dene/encode).
   ADIM 3 - CARPMA = AC -> US TOPLA + ROUGH BINOM -> ENCODE.
   ADIM 4 - ROUGH x ROUGH binom acilimi: dev carpici YOK (operand <= 7).
   ADIM 5 - FLOOR INIS: r = N & 7, n' = N >> 3. TOPLAMA YOK -> TASMA YOK.
   ADIM 6 - GOLGE-DOGAL ISLEMLER: faktoriyel Legendre, karekok us/2.
   ADIM 7 - OVERFLOW = MUFETTIS: sonuc 24-bit'i asarsa FLAG_OVF; deger
            "golge-only" calisma formunda tutulur (pozisyonel R0 gecersiz).
   ADIM 8 - DURUSTLUK: golge GENEL CPU degil, OZEL hizlandirici.
   =========================================================================== */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define XBIT_MAX 0xFFFFFFu          /* 2^24 - 1 = 16.777.215 (CT-CPU pozisyonel sinir) */
#define LIM      2097151u

static const uint32_t P[7] = {2,3,5,7,11,13,17};

/* ======================= SAKLAMA KATMANI: MERDIVEN =========================
   golge_nihai.c'den birebir (N6 modeli). */
typedef struct { uint8_t e[7]; uint8_t a; } Row;
typedef struct { Row r[4]; uint32_t RR; int d; } Merdiven;

static uint64_t sv(const Row*w){uint64_t v=1;for(int i=0;i<7;i++)for(int k=0;k<w->e[i];k++)v*=P[i];return v;}
static uint64_t pv(const Row*w){uint64_t v=0;for(int i=0;i<7;i++)v|=(uint64_t)w->e[i]<<(3*i);return v;}
static void setpos(Row*w,uint64_t x){for(int i=0;i<7;i++)w->e[i]=(x>>(3*i))&7;w->a=2;}
static uint64_t fill(Row*w,uint64_t x){uint64_t f=1;
    for(int i=0;i<7;i++){int c=0;while(x%P[i]==0){x/=P[i];c++;}
        w->e[i]=(c>7)?7:(uint8_t)c; for(int t=7;t<c;t++)f*=P[i];} return f*x;}
static int dene(uint32_t N,int derin,Row r[4],uint32_t*RR){
    memset(r,0,4*sizeof(Row)); *RR=0;
    uint64_t cur=N; int k=0, inis=0;
    for(;;){ uint64_t x=cur, sm=1;
        for(int i=0;i<7;i++) while(x%P[i]==0){x/=P[i];sm*=P[i];}
        uint64_t rg=x; uint64_t f=fill(&r[k],sm); int nx=k+1;
        while(f>1){ if(nx>3) return 0; f=fill(&r[nx],f); r[nx].a=0; nx++; }
        if(rg==1) break;
        if(nx>3 || inis>=derin){ if(rg>LIM) return 0;
            if(nx<=3){ setpos(&r[nx],rg); } else { *RR=(uint32_t)rg; } break; }
        r[nx].a=(uint8_t)(rg&7); cur=rg>>3; k=nx; inis++;
        if(cur==0) return 0; }
    return 1; }
static int m_encode(uint32_t N,Row r[4],uint32_t*RR){
    for(int d=3;d>=0;d--) if(dene(N,d,r,RR)) return d; return -1; }
static uint64_t val(const Row r[4],int k,uint32_t RR){
    if(k>3) return 1;
    uint64_t v=sv(&r[k]); int m=k+1;
    while(m<=3 && r[m].a==0){ v*=sv(&r[m]); m++; }
    if(m<=3){ if(r[m].a==2) v*=pv(&r[m]); else v*=(8*val(r,m,RR)+r[m].a); }
    else if(RR) v*=RR;
    return v; }

static int mstore(uint32_t n, Merdiven*m){ m->d=m_encode(n,m->r,&m->RR); return m->d>=0; }
static uint64_t mval(const Merdiven*m){ return val(m->r,0,m->RR); }

/* AC: merdiveni (us vektoru, rough) ikilisine acar (golge_carpma.c'den) */
static void ac(const Row r[4],uint32_t RR,uint32_t us[7],uint64_t*rough){
    for(int i=0;i<7;i++) us[i]=r[0].e[i];
    int m=1;
    while(m<=3 && r[m].a==0){ for(int i=0;i<7;i++) us[i]+=r[m].e[i]; m++; }
    if(m<=3){ if(r[m].a==2) *rough=pv(&r[m]);
              else          *rough=8*val(r,m,RR)+r[m].a; }
    else *rough = RR ? RR : 1;
}

/* ====================== ARITMETIK KATMANI: ACILMIS =========================
   Shadow = ACILMIS calisma formu. Usler burada SINIRSIZ tutulabilir (ALU ara
   degeri); SAKLAMAYA donerken merdiven encode hucre sinirini (<=7) yayilmayla
   (a=0 satirlari) kendisi cozer. */
typedef struct { int e[7]; uint64_t rough; int ovf; } Shadow;   /* rough==1 -> smooth */

static int is_prime(int n){
    if(n < 2) return 0;
    for(int i=2; (long)i*i<=n; i++) if(n%i==0) return 0;
    return 1;
}

/* ---- ENCODE: sayi -> MERDIVEN saklama -> AC -> calisma formu ----
   24-bit icindeki her sayi SAKLAMADAN GECEREK acilir (saklama her encode'da
   dogrulanir). 24-bit ustu (yalniz ara sonuclarda): golge-only, ovf=1. */
static Shadow encode(uint64_t n){
    Shadow s; memset(s.e,0,sizeof(s.e)); s.ovf=0;
    if(n == 0){ s.rough = 0; return s; }       /* 0: ozel durum (ZERO), rough=0 */
    if(n <= XBIT_MAX){
        Merdiven m;
        if(mstore((uint32_t)n,&m) && mval(&m)==n){
            uint32_t us[7]; uint64_t rg;
            ac(m.r,m.RR,us,&rg);               /* SAKLA -> AC */
            for(int i=0;i<7;i++) s.e[i]=(int)us[i];
            s.rough=rg;
            return s;
        }
    }
    s.rough = n;                               /* 24-bit ustu: golge-only */
    for(int i=0;i<7;i++) while(s.rough%P[i]==0){ s.rough/=P[i]; s.e[i]++; }
    if(n > XBIT_MAX) s.ovf = 1;
    return s;
}

/* ---- DECODE: calisma formu -> sayi (24-bit asarsa ovf isaretle) ---- */
static uint64_t decode_ex(Shadow s, int* ovf){
    uint64_t v = s.rough;
    for(int i=0;i<7;i++) for(int k=0;k<s.e[i];k++) v *= P[i];
    if(ovf) *ovf = (v > XBIT_MAX);
    return v;
}
static uint64_t decode(Shadow s){ return decode_ex(s, 0); }
static int is_smooth(Shadow s){ return s.rough==1; }

/* ---- YENIDEN ENCODE: islem sonucu -> merdiven saklama (24-bit icindeyse) */
static int restore(Shadow s, Merdiven* m){
    uint64_t v = decode(s);
    if(v == 0 || v > XBIT_MAX) return 0;       /* golge-only kalir */
    return mstore((uint32_t)v, m);
}

static int is_zero(Shadow s){ if(s.rough) return 0; for(int i=0;i<7;i++) if(s.e[i]) return 0; return 1; }
static int value_exceeds_24bit(Shadow s){
    unsigned __int128 v = s.rough;
    for(int i=0;i<7;i++) for(int k=0;k<s.e[i];k++){ v *= P[i]; if(v > XBIT_MAX) return 1; }
    return v > XBIT_MAX;
}

/* ---- ROUGH x ROUGH = SEVIYE-SEVIYE BINOM (FLOOR), DEV CARPICI YOK ---- */
static uint64_t rbinom(uint64_t A, uint64_t B, int* ovf){
    if(A < 8 || B < 8){
        unsigned __int128 p = (unsigned __int128)A * B;
        if(p > XBIT_MAX) *ovf = 1;
        return (uint64_t)p;
    }
    uint64_t rA = A & 7, rB = B & 7;
    uint64_t a1 = A >> 3, b1 = B >> 3;
    unsigned __int128 r =
          (unsigned __int128)64 * rbinom(a1,b1,ovf)
        + (unsigned __int128)8  * (a1*rB + b1*rA)
        + (unsigned __int128)rA * rB;
    if(r > XBIT_MAX) *ovf = 1;
    return (uint64_t)r;
}

/* ---- MUL: AC'ilmis formda us topla + rough binom (AC->CARP->ENCODE'un CARP'i) */
static Shadow mul(Shadow a, Shadow b){
    Shadow r; r.ovf = a.ovf | b.ovf;
    for(int i=0;i<7;i++) r.e[i] = a.e[i] + b.e[i];
    int rough_ovf = 0;
    r.rough = rbinom(a.rough, b.rough, &rough_ovf);
    int dovf = 0; decode_ex(r, &dovf);
    r.ovf |= rough_ovf | dovf;
    return r;
}

/* ---- DIV (tam bolme): us cikar ---- */
static int divexact(Shadow a, Shadow b, Shadow* out){
    if(is_zero(b)) return 0;
    if(is_zero(a)){ *out = a; return 1; }
    Shadow r; r.ovf = 0;
    for(int i=0;i<7;i++){ r.e[i]=a.e[i]-b.e[i]; if(r.e[i]<0) return 0; }
    if(a.rough % b.rough) return 0;
    r.rough = a.rough / b.rough; *out = r; return 1;
}

/* ---- POW: us carp ---- */
static Shadow ipow(Shadow a, int k){
    Shadow r; r.ovf = a.ovf;
    for(int i=0;i<7;i++) r.e[i] = a.e[i]*k;
    unsigned __int128 v = 1;
    for(int j=0;j<k;j++){ v *= a.rough; if(v > XBIT_MAX){ r.ovf = 1; } }
    r.rough = (uint64_t)v;
    r.ovf |= value_exceeds_24bit(r);
    return r;
}

/* ---- GCD: min us + rough gcd ---- */
static uint64_t gcd_u(uint64_t a,uint64_t b){ while(b){uint64_t t=a%b;a=b;b=t;} return a; }
static Shadow sgcd(Shadow a, Shadow b){
    if(is_zero(a)) return b;
    if(is_zero(b)) return a;
    Shadow r; r.ovf = 0;
    for(int i=0;i<7;i++) r.e[i] = a.e[i]<b.e[i]?a.e[i]:b.e[i];
    r.rough = gcd_u(a.rough,b.rough); return r;
}

/* ---- FAKTORIYEL (Legendre): us_p = sum floor(n/p^k), CARPMA YOK ---- */
static Shadow factorial(int n){
    Shadow s; memset(s.e,0,sizeof(s.e)); s.rough=1; s.ovf=0;
    for(int i=0;i<7;i++){ long pk=P[i]; while(pk<=n){ s.e[i]+=n/pk; pk*=P[i]; } }
    for(int p=19; p<=n; p++){
        if(!is_prime(p)) continue;
        long pk=p, exp=0; while(pk<=n){ exp+=n/pk; pk*=p; }
        for(long j=0;j<exp;j++){
            unsigned __int128 v = (unsigned __int128)s.rough * p;
            if(v > XBIT_MAX) s.ovf = 1;
            s.rough = (uint64_t)v;
        }
    }
    s.ovf |= value_exceeds_24bit(s);
    return s;
}

/* ---- SQRT: us yarila + tek us radikalde; rough digit-by-digit ---- */
static uint64_t isqrt(uint64_t n){
    uint64_t r=0,b=1ULL<<62; while(b>n) b>>=2;
    while(b){ uint64_t t=r+b; if(n>=t){ n-=t; r=(r>>1)+b; } else r>>=1; b>>=2; } return r;
}
static void ssqrt(Shadow a, Shadow* coef, uint64_t* radikand){
    Shadow c; memset(c.e,0,sizeof(c.e)); c.rough=1; c.ovf=0; uint64_t rad=1;
    for(int i=0;i<7;i++){ c.e[i]=a.e[i]/2; if(a.e[i]&1) rad*=P[i]; }
    rad *= a.rough;
    *coef=c; *radikand=rad;
}

/* ---- MOD (oktal 8^k periyodu kurallari) ---- */
static int mod7 (uint64_t n){ uint64_t s=0; while(n){s+=n&7;n>>=3;} return s%7; }
static int mod13(uint64_t n){ return ((n&0xFFF)+(n>>12))%13; }
static int mod11(uint64_t n){ int64_t v=((int64_t)(n&0x7FFF)-(int64_t)(n>>15))%11; return (int)((v+11)%11); }

/* ---- 8n-r katman encode (FLOOR: N = 8*n' + r, r = N&7) ---- */
static int layers8nr(uint64_t v, int* r_out, uint64_t* tail){
    int r = (int)(v & 7); *r_out = r; *tail = v >> 3; return r;
}

/* =========================================================================== */
static int pass=0, fail=0;
static void CHK(const char* ad, int ok, const char* d){
    printf("  [%s] %-36s %s\n", ok?"PASS":"FAIL", ad, d);
    if(ok) pass++; else fail++;
}

int main(void){
    char b[160];
    printf("========== GOLGE EMULATOR (MERDIVEN, E1 2/2) - TUM FONKSIYONLAR ==========\n\n");

    /* 1. ENCODE/DECODE round-trip — artik SAKLAMADAN (merdiven) gecerek */
    uint64_t tn[]={0,1,17,360,738,41,720720,1000003ull};
    int e_ok=1; for(unsigned i=0;i<sizeof(tn)/sizeof(tn[0]);i++){ Shadow s=encode(tn[i]); if(decode(s)!=tn[i]) e_ok=0; }
    CHK("encode/decode round-trip (n=0 dahil)", e_ok, "0,1,17,360,738,41,720720,1000003 (merdiven uzerinden)");
    { Shadow s=encode(738); snprintf(b,sizeof(b),"738 -> e[%d,%d,%d,%d,%d,%d,%d] rough=%llu",
        s.e[0],s.e[1],s.e[2],s.e[3],s.e[4],s.e[5],s.e[6],(unsigned long long)s.rough); printf("        %s\n",b); }

    /* 2. encode(0) kilitlenmez */
    { Shadow s=encode(0); CHK("encode(0) sonsuz dongu yok", decode(s)==0 && s.rough==0, "n=0 -> rough=0, kilitlenmez"); }

    /* 3-5. MUL: smooth / rough binom / karisik */
    { Shadow a=encode(12),bb=encode(10),r=mul(a,bb); CHK("MUL smooth (12*10)",decode(r)==120,"us topla -> 120"); }
    { Shadow a=encode(41),bb=encode(43),r=mul(a,bb); CHK("MUL rough (41*43 binom)",decode(r)==1763,"FLOOR binom -> 1763"); }
    { Shadow a=encode(41),bb=encode(720),r=mul(a,bb); CHK("MUL karisik (41*720)",decode(r)==29520,"us-topla + binom -> 29520"); }

    /* 6. DIV + 0/n=0 */
    { Shadow a=encode(120),bb=encode(8),o; int ok=divexact(a,bb,&o)&&decode(o)==15;
      Shadow z=encode(0),o2; int ok0=divexact(z,encode(15),&o2)&&decode(o2)==0;
      CHK("DIV (120/8) + 0/15=0",ok && ok0,"us cikar -> 15 ; 0/15=0 (tam)"); }

    /* 7. POW + ovf */
    { Shadow a=encode(6),r=ipow(a,4); Shadow t=encode(13),r2=ipow(t,8);
      CHK("POW (6^4) + ipow ovf (13^8)",decode(r)==1296 && r2.ovf==1,"6^4=1296 ; 13^8>2^24 -> ovf=1"); }

    /* 8-10. SQRT */
    { Shadow a=encode(576),c; uint64_t rad; ssqrt(a,&c,&rad); CHK("SQRT smooth (576)",decode(c)==24&&rad==1,"us yarila -> 24"); }
    { Shadow a=encode(720),c; uint64_t rad; ssqrt(a,&c,&rad); CHK("SQRT sembolik (720)",decode(c)==12&&rad==5,"12 * kok(5)"); }
    { uint64_t r=isqrt(6733); CHK("SQRT rough (6733 digit-by-digit)", r==82 && 6733-r*r==9, "82, kalan 9"); }

    /* 11. GCD + sifir operand */
    { Shadow a=encode(360),bb=encode(84),g=sgcd(a,bb);
      Shadow z=encode(0),n=encode(15),g0=sgcd(z,n);
      CHK("GCD (360,84) + gcd(0,15)",decode(g)==12 && decode(g0)==15,"min us -> 12 ; gcd(0,15)=15"); }

    /* 12-13. FAKTORIYEL */
    { Shadow f=factorial(10); CHK("FAKTORIYEL 10! (Legendre)",decode(f)==3628800ull,"2^8*3^4*5^2*7 = 3628800"); }
    { Shadow f=factorial(19); uint64_t v=decode(f);
      snprintf(b,sizeof(b),"19!=%llu (rough'ta 19 var), ovf=%d (deger 2^24'u asar)",(unsigned long long)v,f.ovf);
      CHK("FAKTORIYEL 19! (17-ustu + ovf)", v==121645100408832000ull && f.ovf==1, b);
      if(is_smooth(factorial(10))) printf("        (10! smooth: rough=1, 17-smooth)\n"); }

    /* 14. MOD oktal */
    { int ok=1; uint64_t xs[]={12345,98765,54321,16777215ull,7,8,63};
      for(unsigned i=0;i<sizeof(xs)/sizeof(xs[0]);i++){ uint64_t n=xs[i];
        if(mod7(n)!=n%7||mod13(n)!=n%13||mod11(n)!=n%11) ok=0; }
      CHK("MOD oktal (7,11,13) genis",ok,"hane-toplam/blok kurallari"); }

    /* 15. ADD fallback */
    { Shadow a=encode(20),bb=encode(3); uint64_t sum=decode(a)+decode(bb); Shadow r=encode(sum);
      CHK("ADD fallback (20+3=23)",decode(r)==23 && r.rough==23,"toplama pozisyonel; sonuc rough"); }

    /* 16. OVERFLOW mufettis */
    { Shadow a=encode(720720),bb=encode(30),r=mul(a,bb); int dovf; uint64_t v=decode_ex(r,&dovf);
      snprintf(b,sizeof(b),"v=%llu (>2^24) FLAG_OVF=%d, golge TAM kalir",(unsigned long long)v,r.ovf);
      CHK("OVERFLOW mufettis (720720*30)", r.ovf && dovf && v==21621600ull, b); }

    /* 17. rbinom buyuk -> ovf */
    { int ov=0; uint64_t r=rbinom(5000003ull,5000003ull,&ov);
      CHK("rbinom buyuk -> ovf isaretli", ov==1, "24-bit asti -> ovf=1 (kilitsiz)"); (void)r; }

    /* 18. 8n-r FLOOR */
    { int r; uint64_t tail; layers8nr(41,&r,&tail);
      CHK("8n-r FLOOR (41 -> r=1, n'=5)", r==1 && tail==5 && 8*tail+r==41, "8*5+1 = 41"); }

    /* 19. CASCADE -> artik YAYILMA (a=0): saklama katmani kendisi cozer */
    { Merdiven m; int ok = mstore(1u<<20,&m) && mval(&m)==(1u<<20)
        && m.r[0].e[0]==7 && m.r[1].a==0 && m.r[2].a==0;   /* 2^20 = 7+7+6, a=0 yayilma */
      CHK("YAYILMA (2^20 = R1 e2=7 x R2,R3 a=0)", ok, "hucre>7 -> duz-carpan satirlari"); }

    /* --- E1 (2/2) EK TESTLERI: MERDIVEN SAKLAMA --- */

    /* 20. Merdiven saklama round-trip (kritik ornekler) */
    { uint32_t xs[]={738,9728,256,2048,1566857u,16777213u,1};
      int ok=1; for(unsigned i=0;i<sizeof(xs)/sizeof(xs[0]);i++){
        Merdiven m; if(!mstore(xs[i],&m)||mval(&m)!=xs[i]) ok=0; }
      CHK("MERDIVEN round-trip (7 kritik)", ok, "738,9728,256,2048,1566857,16777213,1"); }

    /* 21. Eski carpismanin oldugunu kanitla: 1.566.857 vs 12.533.897 farkli saklanir */
    { Merdiven m1,m2; int ok = mstore(1566857u,&m1) && mstore(12533897u,&m2)
        && (memcmp(m1.r,m2.r,sizeof(m1.r))||m1.RR!=m2.RR)
        && mval(&m1)==1566857u && mval(&m2)==12533897u;
      CHK("CARPISMA YOK (1566857 vs 12533897)", ok, "eski 24.788'lik carpisma a-kuraliyla kapali"); }

    /* 22. AC -> CARP -> ENCODE tam zincir (saklamadan saklamaya) */
    { Merdiven ma,mb,mc; uint32_t usA[7],usB[7]; uint64_t rgA,rgB;
      int ok = mstore(41,&ma) && mstore(43,&mb);
      if(ok){ ac(ma.r,ma.RR,usA,&rgA); ac(mb.r,mb.RR,usB,&rgB);
        int ov=0; uint64_t C=rbinom(rgA,rgB,&ov);
        for(int i=0;i<7;i++) for(uint32_t t=0;t<usA[i]+usB[i];t++) C*=P[i];
        ok = !ov && C==1763 && mstore((uint32_t)C,&mc) && mval(&mc)==1763; }
      CHK("AC->CARP->ENCODE (41*43 -> saklama)", ok, "sonuc yeniden merdivende, deger 1763"); }

    /* 23. restore(): islem sonucu saklamaya doner (24-bit icindeyse) */
    { Shadow a=encode(12),bb=encode(10),r=mul(a,bb); Merdiven m;
      CHK("restore (120 saklamaya doner)", restore(r,&m) && mval(&m)==120, "MUL sonucu merdivene geri"); }

    printf("\n==========================================================================\n");
    printf("  OZET: %d PASS, %d FAIL -> %s\n", pass, fail, fail?"HATA VAR":"TUM FONKSIYONLAR CALISIYOR (MERDIVEN)");
    printf("==========================================================================\n");
    return fail?1:0;
}
