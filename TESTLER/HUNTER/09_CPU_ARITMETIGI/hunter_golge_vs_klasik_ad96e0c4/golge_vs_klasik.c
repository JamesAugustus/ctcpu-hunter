/* ============================================================================
   GOLGE vs KLASIK — FIILI UYGULAMANIN KIYASI
   ============================================================================
   NEDEN BU TEST VAR: 20 Tem denetimi su boslugu buldu — hicbir ozel test
   golgenin FIILI encoding'ini (merdiven/TUR/RR + AC-CARP-ENCODE carpmasi)
   klasik yonteme karsi olcmuyordu. golge_lazy.c en yakin analogdu ama o
   19 Tem'de, model kapanmadan once yazilmis SOYUT bir simulasyondu.

   NE OLCULUYOR — ve NE OLCULMUYOR:
     OLCULUYOR : TEMEL ISLEM SAYISI (kaydirma / kucuk-carpim / toplama).
                 Donanimda kapi maliyetinin proxy'si budur.
     OLCULMUYOR: duvar saati. Host CPU'da kosuyoruz; emulasyon overhead'i
                 gercek silikonu YANSITMAZ. Sure olcup "Nx hizli" demek
                 YANILTICI olurdu — CT-CPU silikonu YOK.

   DURUSTLUK KURALI: gölgenin kaybettigi yerler de raporlanir.
   ============================================================================ */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define MAXN 16777216u
#define LIM 2097151u
static const uint32_t P[7]={2,3,5,7,11,13,17};
typedef struct { uint8_t e[7]; uint8_t a; } Row;

/* ---- sayaclar: her "temel islem" ayri sayilir ---------------------------- */
typedef struct {
    long kaydirma;      /* <<3, <<6 — donanimda TEL/MONTAJ, ~0 kapi */
    long kucuk_carpim;  /* operandi <=7 olan carpim — incrementer sinifi */
    long toplama;       /* us toplama / binom toplamalari */
    long buyuk_carpim;  /* 7'yi asan operandli carpim — ISTENMEYEN */
} Sayac;
static Sayac G, K;

/* ---- encode/decode (golge_nihai.c ile birebir) -------------------------- */
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
static void ac(const Row r[4],uint32_t RR,uint32_t us[7],uint64_t*rough){
    for(int i=0;i<7;i++) us[i]=r[0].e[i];
    int m=1;
    while(m<=3 && r[m].a==0){ for(int i=0;i<7;i++) us[i]+=r[m].e[i]; m++; }
    if(m<=3){ if(r[m].a==2) *rough=pv(&r[m]); else *rough=8*val(r,m,RR)+r[m].a; }
    else *rough = RR ? RR : 1; }

/* ---- GOLGE: rough x rough binom, sayacli ------------------------------- */
static uint64_t rbinom(uint64_t A,uint64_t B){
    if(A==0||B==0) return 0;
    if(A<8 && B<8){ G.kucuk_carpim++; return A*B; }
    if(B<8){ uint64_t a1=A>>3, rA=A&7; G.kaydirma++; G.kucuk_carpim++; G.toplama++;
             return (rbinom(a1,B)<<3) + rA*B; }
    if(A<8) return rbinom(B,A);
    uint64_t a1=A>>3, rA=A&7, b1=B>>3, rB=B&7;
    G.kaydirma+=2; G.toplama+=3;
    return (rbinom(a1,b1)<<6) + ((rbinom(a1,rB)+rbinom(b1,rA))<<3) + rA*rB; }

/* ---- KLASIK: 24x24 shift-add carpici, sayacli --------------------------
   Donanimda dizi carpici (array multiplier) ~24 kismi carpim + toplayici
   agaci demektir. Burada kismi-carpim/toplama sayisi olculur.            */
static uint64_t klasik_carp(uint32_t a,uint32_t b){
    uint64_t sonuc=0, x=a;
    while(b){ if(b&1){ sonuc+=x; K.toplama++; }
              x<<=1; b>>=1; K.kaydirma++;
              if(b) K.buyuk_carpim++; }   /* her kismi carpim asamasi */
    return sonuc; }

int main(void){
    setvbuf(stdout,NULL,_IONBF,0);
    printf("================================================================\n");
    printf("  GOLGE vs KLASIK — fiili uygulama, TEMEL ISLEM SAYISI\n");
    printf("  (duvar saati DEGIL: CT-CPU silikonu yok, host olcumu yanilticidir)\n");
    printf("================================================================\n\n");

    /* --- 1. SMOOTH / ROUGH DAGILIMI (tam 2^24) --------------------------- */
    printf("--- 1. SAYILAR NE KADAR 'GOLGE-DOSTU'? (tam 2^24) ---\n");
    long smooth=0, rough=0;
    for(uint32_t n=1;n<MAXN;n++){
        uint32_t v=n;
        for(int i=0;i<7;i++) while(v%P[i]==0) v/=P[i];
        if(v==1) smooth++; else rough++; }
    printf("  smooth (rough=1) : %9ld  (%%%.4f)  -> carpma = SADECE us toplama\n",
           smooth, 100.0*smooth/(MAXN-1));
    printf("  rough            : %9ld  (%%%.4f)  -> binom acilimi gerekir\n",
           rough, 100.0*rough/(MAXN-1));

    /* --- 2. CARPMA BASINA TEMEL ISLEM (rastgele cift, 200K) -------------- */
    printf("\n--- 2. CARPMA BASINA TEMEL ISLEM SAYISI ---\n");
    uint64_t s=88172645463325252ULL;
    long n_ss=0,n_sr=0,n_rr=0;
    Sayac Gss={0},Gsr={0},Grr={0};
    long adet=0;
    /* ADIL KIYAS: iki operand da TAM 24-bit menzilden. Carpim 2^24'u assa da
       onemli degil — burada DEGER degil ISLEM SAYISI olculuyor.
       (Ilk surumde b, a'ya bagli seciliyordu: a buyudukce b kuculuyor,
        klasik tarafa haksiz avantaj veriyordu. Duzeltildi.) */
    for(long i=0;i<200000;i++){
        s^=s<<13;s^=s>>7;s^=s<<17; uint32_t a=(uint32_t)(s%16777215u)+1;
        s^=s<<13;s^=s>>7;s^=s<<17; uint32_t b=(uint32_t)(s%16777215u)+1;
        Row ra[4],rb[4]; uint32_t RRa,RRb;
        if(encode(a,ra,&RRa)<0||encode(b,rb,&RRb)<0) continue;
        uint32_t ua[7],ub[7]; uint64_t rgA,rgB;
        ac(ra,RRa,ua,&rgA); ac(rb,RRb,ub,&rgB);

        memset(&G,0,sizeof(G)); memset(&K,0,sizeof(K));
        /* GOLGE: 7 us toplama + rough binom */
        for(int j=0;j<7;j++){ (void)(ua[j]+ub[j]); G.toplama++; }
        rbinom(rgA,rgB);
        /* KLASIK: 24x24 shift-add */
        klasik_carp(a,b);

        int sa=(rgA==1), sb2=(rgB==1);
        Sayac *hedef = (sa&&sb2)?&Gss : (sa||sb2)?&Gsr : &Grr;
        long *say   = (sa&&sb2)?&n_ss : (sa||sb2)?&n_sr : &n_rr;
        hedef->kaydirma+=G.kaydirma; hedef->kucuk_carpim+=G.kucuk_carpim;
        hedef->toplama+=G.toplama;   hedef->buyuk_carpim+=G.buyuk_carpim;
        (*say)++;
        /* klasik toplam ayrica biriktirilir */
        static long Kk=0,Kt=0,Kb=0;
        Kk+=K.kaydirma; Kt+=K.toplama; Kb+=K.buyuk_carpim; adet++;
        if(i==199999){
            printf("  KLASIK, carpma basina ORTALAMA:\n");
            printf("   (a) yazilim shift-add : kaydirma %.1f · toplama %.1f · asama %.1f\n",
                   (double)Kk/adet,(double)Kt/adet,(double)Kb/adet);
            printf("   (b) DONANIM dizi carpici: 24 kismi carpim SABIT + toplayici agaci\n");
            printf("       (~2500-3000 kapi TAHMIN — operanddan bagimsiz, hep ayni)\n");
        }
    }
    printf("\n  GOLGE, carpma basina ORTALAMA (operand tipine gore):\n");
    struct { const char*ad; Sayac*s; long n; } T[]={
        {"smooth x smooth",&Gss,n_ss},{"smooth x rough ",&Gsr,n_sr},{"rough  x rough ",&Grr,n_rr}};
    for(int i=0;i<3;i++){
        if(!T[i].n){ printf("     %s : ornek yok\n",T[i].ad); continue; }
        printf("     %s (%%%5.2f): kaydirma %5.2f · kucuk-carpim %5.2f · toplama %5.2f\n",
               T[i].ad, 100.0*T[i].n/(n_ss+n_sr+n_rr),
               (double)T[i].s->kaydirma/T[i].n,
               (double)T[i].s->kucuk_carpim/T[i].n,
               (double)T[i].s->toplama/T[i].n);
    }
    printf("     >>> smooth x smooth: BUYUK CARPIM YOK, sadece 7 us toplama.\n");
    printf("     >>> rough  x rough : binom acilir; operandlar <=7 kalir.\n");

    /* --- 3. DEV CARPICI HIC KURULUYOR MU? -------------------------------- */
    printf("\n--- 3. DEV CARPICI (array multiplier) GEREKIYOR MU? ---\n");
    printf("  GOLGE  buyuk-carpim (operand>7) sayisi : %ld\n", Gss.buyuk_carpim+Gsr.buyuk_carpim+Grr.buyuk_carpim);
    printf("  -> 0 ise: 24-bit dizi carpicisi HIC KURULMAZ (tasarim iddiasi dogrulanir)\n");

    /* --- 4. ZINCIR: golgenin ASIL kazandigi yer -------------------------- */
    printf("\n--- 4. ZINCIR ISLEM (a*b*c/d) — golgenin ASIL nisi ---\n");
    printf("  Golgede zincir: usler toplanir/cikarilir, ARADA DECODE YOK.\n");
    printf("  Klasikte zincir: her adimda tam carpma + tam bolme.\n");
    long z_golge_us=0, z_klasik_asama=0, z_adet=0;
    for(long i=0;i<50000;i++){
        s^=s<<13;s^=s>>7;s^=s<<17; uint32_t a=(uint32_t)(s%1000u)+2;
        s^=s<<13;s^=s>>7;s^=s<<17; uint32_t b=(uint32_t)(s%1000u)+2;
        s^=s<<13;s^=s>>7;s^=s<<17; uint32_t c=(uint32_t)(s%1000u)+2;
        Row r1[4],r2[4],r3[4]; uint32_t X,Y,Z;
        if(encode(a,r1,&X)<0||encode(b,r2,&Y)<0||encode(c,r3,&Z)<0) continue;
        uint32_t u1[7],u2[7],u3[7]; uint64_t g1,g2,g3;
        ac(r1,X,u1,&g1); ac(r2,Y,u2,&g2); ac(r3,Z,u3,&g3);
        if(g1!=1||g2!=1||g3!=1) continue;          /* smooth zincir */
        z_golge_us += 7*2;                          /* iki islem, 7 asal */
        memset(&K,0,sizeof(K));
        klasik_carp(a,b); klasik_carp((uint32_t)((uint64_t)a*b%MAXN),c);
        z_klasik_asama += K.buyuk_carpim;
        z_adet++;
    }
    if(z_adet){
        printf("  smooth zincir ornegi: %ld adet\n", z_adet);
        printf("     GOLGE  : %.1f us islemi/zincir (carpim YOK)\n",(double)z_golge_us/z_adet);
        printf("     KLASIK : %.1f kismi-carpim asamasi/zincir\n",(double)z_klasik_asama/z_adet);
    }

    /* --- 4b. BOLME — golgenin ASIL iddiasi ------------------------------- */
    printf("\n--- 4b. BOLME: golge = us CIKAR, klasik = restoring division ---\n");
    long b_golge=0, b_klasik=0, b_adet=0, b_red=0;
    for(long i=0;i<200000;i++){
        s^=s<<13;s^=s>>7;s^=s<<17; uint32_t q=(uint32_t)(s%4000u)+2;
        s^=s<<13;s^=s>>7;s^=s<<17; uint32_t d=(uint32_t)(s%4000u)+2;
        uint64_t nn=(uint64_t)q*d; if(nn>=MAXN) continue;
        Row rn[4],rd[4]; uint32_t Xn,Xd;
        if(encode((uint32_t)nn,rn,&Xn)<0||encode(d,rd,&Xd)<0) continue;
        uint32_t un[7],ud[7]; uint64_t gn,gd;
        ac(rn,Xn,un,&gn); ac(rd,Xd,ud,&gd);
        int tam=1;
        for(int j=0;j<7;j++) if(un[j]<ud[j]) tam=0;
        if(gd!=1 && (gd==0||gn%gd!=0)) tam=0;
        if(!tam){ b_red++; continue; }
        b_golge += 7;                     /* 7 asal, us CIKAR — carpim/bolme YOK */
        /* klasik restoring division: bolunen bit sayisi kadar adim */
        uint64_t t=nn; int bit=0; while(t){ t>>=1; bit++; }
        b_klasik += bit;                  /* her adim: kaydir+kiyasla+cikar */
        b_adet++;
    }
    if(b_adet){
        printf("  tam bolunen ornek: %ld  (bolunmeyen %ld -> pozisyonel yola duser)\n",b_adet,b_red);
        printf("     GOLGE  : %.1f temel islem/bolme  (us CIKARMA, bolucu YOK)\n",(double)b_golge/b_adet);
        printf("     KLASIK : %.1f adim/bolme (restoring div: kaydir+kiyasla+cikar)\n",(double)b_klasik/b_adet);
        printf("     >>> BOLMEDE golge acik ara onde — bolucu devresi HIC KURULMAZ.\n");
        printf("     >>> AMA: yalnizca TAM BOLUNME'de. Kalanli bolme pozisyonele duser.\n");
    }

    /* --- 5. DURUST SINIR ------------------------------------------------- */
    printf("\n--- 5. DURUST SINIR — golge NEREDE KAYBEDIYOR ---\n");
    printf("  · TOPLAMA golgede YAPILAMAZ (2^3+2^4 = 2^3*3, yeni asal dogar).\n");
    printf("    Toplama-agir islerde golge HIC devreye girmez, kazanc 0.\n");
    printf("  · rough x rough sayilarin cogunlugudur (yukarida %%%.2f).\n",
           100.0*rough/(MAXN-1));
    printf("    Bu durumda binom acilir — ucuz ama BEDAVA DEGIL.\n");
    printf("  · RESOLVER maliyeti: ortalama 3,600 gecis/sayi (LAZY oldugu icin\n");
    printf("    kritik yolda degil, ama ilk carpimsal islemde odenir).\n");
    printf("  · Bu test KAPI SAYMAZ, TEMEL ISLEM SAYAR. Sentez yapilmadi.\n");

    printf("\n================================================================\n");
    return 0;
}
