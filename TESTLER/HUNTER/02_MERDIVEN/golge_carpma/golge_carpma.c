/* GOLGE CARPMA — yeni merdiven temsilinde
   ============================================================================
   ANA FIKIR (bitmis parcalarin birlestirilmesi):

     MERDIVEN BIR SAKLAMA FORMATIDIR, ARITMETIK FORMATI DEGIL.

   Sayi golgede su iki parcadan olusur:      N = (asal usler) x (rough)
   Merdiven sadece bu ikisini 4 satira SIKISTIRMA bicimidir.

   Carpma bu yuzden UC ADIMDIR:
     1. AC     : her operandin (us vektoru, rough) ikilisi cikarilir
     2. CARP   : usler toplanir + rough'lar BINOM ile carpilir
     3. TOPLA  : sonuc yeniden encode edilir (merdivene girer)

   Ucu de zaten tasarliydi:
     - us toplama       -> MUL_DIV kilitli (1_MUL_DIV_NIHAI.txt)
     - rough x rough    -> binom acilimi, en buyuk temel operand = 7 (kanitli)
     - encode           -> golge_nihai.c (tam 2^24, 0 hata, %100 kapsama)
   Yapilmamis olan sey BIRLESTIRMEKTI.

   DEV CARPICI YOK: rough x rough binom ile acilir, taban durumdaki carpimlarin
   operandlari <=7'dir. Program bunu kosarken DOGRULAR (max_operand).
   ============================================================================ */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#define MAXN 16777216u
#define LIM 2097151u
static const uint32_t P[7]={2,3,5,7,11,13,17};
typedef struct { uint8_t e[7]; uint8_t a; } Row;

/* ---- golge_nihai.c'den birebir: encode / decode ------------------------- */
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
static int encode(uint32_t N,Row r[4],uint32_t*RR){
    for(int d=3;d>=0;d--) if(dene(N,d,r,RR)) return d; return -1; }
static uint64_t val(const Row r[4],int k,uint32_t RR){
    if(k>3) return 1;
    uint64_t v=sv(&r[k]); int m=k+1;
    while(m<=3 && r[m].a==0){ v*=sv(&r[m]); m++; }
    if(m<=3){ if(r[m].a==2) v*=pv(&r[m]); else v*=(8*val(r,m,RR)+r[m].a); }
    else if(RR) v*=RR;
    return v; }

/* ---- ADIM 1: AC — (us vektoru, rough) ikilisi cikarilir -------------------
   R1 ve pesinden gelen a=0 (duz carpan) satirlari SMOOTH kismidir.
   Geri kalan zincir (2^3*val + a) ise ROUGH kismidir.
   Merdiven acilir, sayinin gercek asal ayrisimi ortaya cikar.            */
static void ac(const Row r[4],uint32_t RR,uint32_t us[7],uint64_t*rough){
    for(int i=0;i<7;i++) us[i]=0;
    int k=0;
    for(int i=0;i<7;i++) us[i]+=r[0].e[i];       /* R1'in usleri */
    int m=1;
    while(m<=3 && r[m].a==0){                    /* pesindeki duz carpanlar */
        for(int i=0;i<7;i++) us[i]+=r[m].e[i];
        m++; }
    (void)k;
    if(m<=3){                                    /* merdiven/ROUGH devam ediyor */
        if(r[m].a==2) *rough=pv(&r[m]);          /* TUR=2: dogrudan pozisyonel */
        else          *rough=8*val(r,m,RR)+r[m].a;
    } else *rough = RR ? RR : 1;                 /* satir bitti: RR ya da 1 */
}

/* ---- ADIM 2b: ROUGH x ROUGH — binom acilimi, DEV CARPICI YOK -----------
   A = 2^3*a1 + rA ,  B = 2^3*b1 + rB
   A*B = 2^6*(a1*b1) + 2^3*(a1*rB + b1*rA) + rA*rB
   2^6 ve 2^3 sadece KAYDIRMA. rA,rB kucuk (0-7). a1*b1 ayni yontemle recursive. */
static uint64_t max_operand=0;                   /* dev carpici yok, DOGRULANIR */
static uint64_t rmul(uint64_t a,uint64_t b){
    if(a==0||b==0) return 0;
    if(a<8 && b<8){ if(a>max_operand)max_operand=a; if(b>max_operand)max_operand=b;
                    return a*b; }
    if(b<8){ uint64_t a1=a>>3, rA=a&7;
             if(b>max_operand)max_operand=b;
             return (rmul(a1,b)<<3) + rA*b; }
    if(a<8){ return rmul(b,a); }
    uint64_t a1=a>>3, rA=a&7, b1=b>>3, rB=b&7;
    return (rmul(a1,b1)<<6) + ((rmul(a1,rB)+rmul(b1,rA))<<3) + rA*rB;
}

/* ---- GOLGE CARPMA: AC -> CARP -> YENIDEN ENCODE ------------------------- */
static int golge_carp(uint32_t A,uint32_t B,Row rc[4],uint32_t*RRc,uint64_t*sonuc){
    Row ra[4],rb[4]; uint32_t RRa,RRb;
    if(encode(A,ra,&RRa)<0) return 0;
    if(encode(B,rb,&RRb)<0) return 0;

    uint32_t ua[7],ub[7]; uint64_t rgA,rgB;
    ac(ra,RRa,ua,&rgA);                          /* 1. AC */
    ac(rb,RRb,ub,&rgB);

    uint64_t rgC = rmul(rgA,rgB);                /* 2b. rough x rough, binom */
    uint64_t C   = rgC;
    for(int i=0;i<7;i++){                        /* 2a. usleri TOPLA */
        uint32_t e = ua[i]+ub[i];
        for(uint32_t t=0;t<e;t++) C *= P[i];
    }
    *sonuc = C;
    if(C >= MAXN) return 2;                      /* 2^24'u asti: OVF (golge dogru) */
    if(encode((uint32_t)C,rc,RRc) < 0) return 0; /* 3. YENIDEN ENCODE */
    return 1;
}

int main(void){
    setvbuf(stdout,NULL,_IONBF,0);
    printf("=====================================================================\n");
    printf("  GOLGE CARPMA — yeni merdiven temsilinde  (AC -> CARP -> ENCODE)\n");
    printf("=====================================================================\n\n");

    /* ---- ORNEKLER ---- */
    printf("--- ORNEKLER (oktal) ---\n");
    uint32_t OA[]={738, 738,  256, 15,  9728, 2048, 77,   4096, 12,  35};
    uint32_t OB[]={ 15, 738,  256, 9728,   77,   12, 121,   4,  12, 49};
    for(unsigned i=0;i<sizeof(OA)/sizeof(OA[0]);i++){
        Row rc[4]; uint32_t RRc; uint64_t C;
        int ok=golge_carp(OA[i],OB[i],rc,&RRc,&C);
        uint64_t g=(uint64_t)OA[i]*OB[i];
        char b1[32],b2[32],b3[32];
        /* oktal yazim */
        uint64_t v; int n;
        v=OA[i]; n=0; if(!v)b1[n++]='0'; { char t[32];int m=0; while(v){t[m++]='0'+(v&7);v>>=3;} for(int j=0;j<m;j++)b1[j]=t[m-1-j]; b1[m]=0; if(!m){b1[0]='0';b1[1]=0;} }
        v=OB[i];      { char t[32];int m=0; while(v){t[m++]='0'+(v&7);v>>=3;} for(int j=0;j<m;j++)b2[j]=t[m-1-j]; b2[m]=0; if(!m){b2[0]='0';b2[1]=0;} }
        v=g;          { char t[32];int m=0; while(v){t[m++]='0'+(v&7);v>>=3;} for(int j=0;j<m;j++)b3[j]=t[m-1-j]; b3[m]=0; if(!m){b3[0]='0';b3[1]=0;} }
        printf("  %8s_8 x %8s_8 = %10s_8   ",b1,b2,b3);
        if(ok==2) printf("[OVF: 2^24 asildi, golge degeri tam: %llu]\n",(unsigned long long)C);
        else if(!ok) printf("[SIGMADI]\n");
        else {
            printf("-> ");
            for(int k=0;k<4;k++){ printf("R%d[",k+1);
                if(k&&rc[k].a==2){ char c[32]; uint64_t x=pv(&rc[k]); char t[32];int m=0;
                    if(!x){c[0]='0';c[1]=0;} else {while(x){t[m++]='0'+(x&7);x>>=3;} for(int j=0;j<m;j++)c[j]=t[m-1-j]; c[m]=0;}
                    printf("POZ=%s_8|TUR=2",c); }
                else { int f=1; for(int p=0;p<7;p++) if(rc[k].e[p]){printf("%se%u=%u",f?"":",",P[p],rc[k].e[p]);f=0;}
                       if(f)printf("-"); if(k)printf("|a=%u",rc[k].a); }
                printf("] "); }
            printf(" %s\n", (C==g)?"OK":"**HATA**");
        }
    }

    /* ---- TEST 1: kucuk carpanlar tam tarama ---- */
    printf("\n--- TEST 1: TAM TARAMA  1<=a<=b<4096  (8.386.560 cift) ---\n");
    long hata=0, sinandi=0, ovf=0, sigmadi=0;
    for(uint32_t a=1;a<4096;a++) for(uint32_t b=a;b<4096;b++){
        Row rc[4]; uint32_t RRc; uint64_t C;
        int ok=golge_carp(a,b,rc,&RRc,&C);
        if(!ok){ sigmadi++; continue; }
        if(ok!=1){ if(ok==2) ovf++; else hata++; continue; }
        sinandi++;
        if(C != (uint64_t)a*b) hata++;
        else if(val(rc,0,RRc) != C) hata++;      /* yeniden encode da dogru mu */
    }
    printf("  sinandi: %ld   HATA: %ld   (OVF %ld, sigmadi %ld)\n",sinandi,hata,ovf,sigmadi);

    /* ---- TEST 2: BUYUK operand — a tum 24-bit menzilden, b sigacak kadar
           (boylece carpim 2^24 icinde kalir ve rough x rough gercekten calisir) */
    printf("\n--- TEST 2: BUYUK/ROUGH operand, 5M cift (carpim 2^24 icinde) ---\n");
    uint64_t s=88172645463325252ULL; long h2=0,n2=0,sig2=0;
    for(long i=0;i<5000000;i++){
        s^=s<<13; s^=s>>7; s^=s<<17;
        uint32_t a=(uint32_t)(s%16777215u)+1;
        uint32_t tavan=(MAXN-1)/a; if(tavan<1) continue;
        s^=s<<13; s^=s>>7; s^=s<<17;
        uint32_t b=(uint32_t)(s%tavan)+1;
        Row rc[4]; uint32_t RRc; uint64_t C;
        int ok=golge_carp(a,b,rc,&RRc,&C);
        if(!ok){ sig2++; continue; }
        if(ok!=1){ h2++; continue; }
        n2++;
        if(C != (uint64_t)a*b) h2++;
        else if(val(rc,0,RRc) != C) h2++;
    }
    printf("  sinandi: %ld   HATA: %ld   (sigmadi %ld)\n",n2,h2,sig2);

    /* ---- TEST 2b: TASMA — golge degeri 2^24 asinca da TAM kalmali mi?
           MUL_DIV belgesi: "OVF bayragi kalkar ama GOLGE DEGERI TAM KALIR" */
    printf("\n--- TEST 2b: TASMA (2^24 asan carpim) — golge degeri tam kaliyor mu? ---\n");
    long h2b=0,n2b=0;
    for(long i=0;i<2000000;i++){
        s^=s<<13; s^=s>>7; s^=s<<17;
        uint32_t a=(uint32_t)(s%16777215u)+1;
        s^=s<<13; s^=s>>7; s^=s<<17;
        uint32_t b=(uint32_t)(s%16777215u)+1;
        if((uint64_t)a*b < MAXN) continue;
        Row rc[4]; uint32_t RRc; uint64_t C;
        int ok=golge_carp(a,b,rc,&RRc,&C);
        if(ok!=2){ h2b++; continue; }
        n2b++;
        if(C != (uint64_t)a*b) h2b++;
    }
    printf("  OVF sinandi: %ld   deger BOZULAN: %ld   %s\n",n2b,h2b,
           h2b==0?"(golge tasmaz — deger tam)":"**BOZULDU**");
    h2 += h2b;

    /* ---- TEST 3: dev carpici yok ---- */
    printf("\n--- TEST 3: DEV CARPICI YOK ---\n");
    printf("  binom acilimindaki EN BUYUK temel carpim operandi = %llu",
           (unsigned long long)max_operand);
    printf("   %s\n", (max_operand<=7)?"(<=7  OK — dizi carpicisi GEREKMIYOR)":"(**7'yi ASTI**)");

    printf("\n=====================================================================\n");
    long toplam_hata = hata + h2 + ovf + sigmadi + sig2 + (max_operand > 7);
    printf("  SONUC: %s\n", toplam_hata==0
        ? "GOLGE CARPMA CALISIYOR — 0 hata, dev carpici yok."
        : "**HATA VAR**");
    printf("=====================================================================\n");
    return toplam_hata ? 1 : 0;
}
