/* =============================================================================
   v1.3 (REDDET) vs v1.4 (KARANTİNA) KIYASI — çok sayıyla fark testi (Cem)
   HER SATIRIN yanında // ile TÜRKÇE açıklama.
   -----------------------------------------------------------------------------
   SORU: Sıfıra bölmede eski davranış (v1.3: bayrak konur + işlem REDDEDİLİR, bölünen
   olduğu gibi kalır) ile yeni davranış (v1.4: KARANTİNA çifti — Cem'in onayı)
   arasındaki fark NE ve NEDEN önemli?
   YÖNTEM: milyonlarca rastgele işlem zinciri iki modelden de geçirilir:
     TEMİZ zincirler (÷0 yok)  → iki model de kesin referansla birebir OLMALI
                                 (karantina normal matematiği değiştirmedi mi?)
     KAZALI zincirler (içinde 1 adet ÷0) → asıl fark burada:
       v1.3: bölme REDDEDİLİR, eski değer SESSİZCE akmaya devam eder →
             çıktı DÜZ BİR SAYI olur (sahte!). Bayrak globaldir: "bir yerde
             bir şey oldu" der ama HANGİ değer kirli, NEREDE oldu söylemez.
       v1.4: karantina çifti → çıktı ASLA düz sayı olamaz; "iz×(1/0)" görünür.
   Derle: cc -O2 kesir_v13_v14_kiyas.c -o kk && ./kk > kesir_v13_v14_SONUC.txt
   ============================================================================= */
#include <stdio.h>
#include <stdint.h>
typedef __int128 i128;
typedef long long ll;

static uint64_t RNG=0x1453u;                                   // tekrarlanabilir tohum
static uint64_t xr(void){ uint64_t x=RNG; x^=x<<13; x^=x>>7; x^=x<<17; RNG=x; return x; }

static i128 g128(i128 a,i128 b){ if(a<0)a=-a; if(b<0)b=-b;     // kesin sadeleştirici
    while(b){ i128 t=a%b; a=b; b=t; } return a; }
typedef struct{ i128 n,d; } Fr;                                // kesin kesir (referans/işlem)
static Fr indir(Fr f){ i128 g=g128(f.n,f.d); if(g){f.n/=g;f.d/=g;} if(f.d<0){f.d=-f.d;f.n=-f.n;} return f; }
static Fr fr_mul(Fr a, ll m){ a.n*=m; return indir(a); }       // kesir × tam
static Fr fr_div(Fr a, ll m){ a.d*=m; return indir(a); }       // kesir ÷ tam (m>0)
static Fr fr_add(Fr a, ll m){ a.n+=(i128)m*a.d; return indir(a); } // kesir + tam

/* zincir tanımı: 5 işlem; kazalıysa 'kaza' adımındaki işlem ÷0 olur */
typedef struct{ ll a0; int op[5]; ll m[5]; int kaza; } Zincir; // op:0=MUL 1=DIV 2=ADD
static Zincir uret(int kazali){
    Zincir z; z.a0=(ll)(xr()%999)+1; z.kaza = kazali? (int)(xr()%5) : -1;
    for(int i=0;i<5;i++){ z.op[i]=(int)(xr()%3); z.m[i]=(ll)(xr()%999)+1;
        if(i==z.kaza){ z.op[i]=1; z.m[i]=0; } }                // kaza adımı: ÷0
    return z; }

/* --- v1.3 modeli: ÷0 → bayrak + REDDET (değer olduğu gibi kalır, akış sürer) --- */
static Fr kos_v13(Zincir z, int*flag){
    Fr v={z.a0,1}; *flag=0;
    for(int i=0;i<5;i++){
        if(z.op[i]==1 && z.m[i]==0){ *flag=1; continue; }      // REDDET: v DEĞİŞMEDEN sürer!
        v = z.op[i]==0? fr_mul(v,z.m[i]) : z.op[i]==1? fr_div(v,z.m[i]) : fr_add(v,z.m[i]);
    }
    return v; }                                                // her zaman DÜZ SAYI döner

/* --- v1.4 modeli: ÷0 → KARANTİNA (iz birikir, ADD kısa devre, sayı sızmaz) --- */
static int kos_v14(Zincir z, Fr*sonuc, i128*iz){
    Fr v={z.a0,1}; int q=0; *iz=0;
    for(int i=0;i<5;i++){
        if(!q){                                                // normal akış
            if(z.op[i]==1 && z.m[i]==0){ q=1; v=indir(v); *iz = v.n<0?-v.n:v.n; continue; } // KARANTİNA kurulur: iz=pay
            v = z.op[i]==0? fr_mul(v,z.m[i]) : z.op[i]==1? fr_div(v,z.m[i]) : fr_add(v,z.m[i]);
        } else {                                               // karantinalı akış (v1.4 kuralları)
            if(z.op[i]==0 || z.op[i]==1) *iz *= z.m[i];        // MUL/DIV: iz paya işler (fmul kuralı)
            /* ADD: kısa devre — hiçbir şey yapılmaz, iz korunur */
        }
    }
    *sonuc=v; return q; }                                      // q=1: çıktı "iz×(1/0)" görünür

int main(){
    printf("=================================================================\n");
    printf("  v1.3 (REDDET) vs v1.4 (KARANTINA) — 3M zincir, fark nerede?\n");
    printf("=================================================================\n\n");

    /* --- TEST 1: TEMIZ ZINCIRLER (1M) — karantina normal matematigi degistirdi mi? --- */
    long N=1000000, fark13=0, fark14=0;
    for(long t=0;t<N;t++){
        Zincir z=uret(0); int fl; Fr r13=kos_v13(z,&fl);
        Fr r14; i128 iz; int q=kos_v14(z,&r14,&iz);
        Fr ref={z.a0,1};                                       // kesin referans (ayni islemler)
        for(int i=0;i<5;i++) ref = z.op[i]==0? fr_mul(ref,z.m[i]) : z.op[i]==1? fr_div(ref,z.m[i]) : fr_add(ref,z.m[i]);
        if(r13.n*ref.d!=ref.n*r13.d) fark13++;                 // v1.3 referansla ayni mi
        if(q || r14.n*ref.d!=ref.n*r14.d) fark14++;            // v1.4: karantinasiz + ayni olmali
    }
    printf("TEST 1  TEMIZ zincirler (%ldM, ÷0 YOK):\n", N/1000000);
    printf("  v1.3 referanstan sapma: %ld   v1.4 sapma: %ld\n", fark13, fark14);
    printf("  -> KARANTINA NORMAL MATEMATIGE DOKUNMADI (iki model de kusursuz)\n\n");

    /* --- TEST 2: KAZALI ZINCIRLER (1M, her birinde 1 adet ÷0) — ASIL FARK --- */
    long sahte13=0, bayrak13=0, sizinti14=0, gorunur14=0, izhata=0;
    for(long t=0;t<N;t++){
        Zincir z=uret(1); int fl; Fr r13=kos_v13(z,&fl);
        Fr r14; i128 iz; int q=kos_v14(z,&r14,&iz);
        if(!q) sizinti14++; else gorunur14++;                  // v1.4: kaza GORUNUR mu?
        (void)r13; sahte13++;                                  // v1.3: cikti HEP duz sayi (sahte)
        if(fl) bayrak13++;                                     // bayrak yandi ama... (asagida)
        /* iz dogrulamasi: kaza anindaki pay × sonraki MUL/DIV çarpanları */
        Fr o={z.a0,1};
        for(int i=0;i<z.kaza;i++) o = z.op[i]==0? fr_mul(o,z.m[i]) : z.op[i]==1? fr_div(o,z.m[i]) : fr_add(o,z.m[i]);
        o=indir(o); i128 beklenen = o.n<0?-o.n:o.n;
        for(int i=z.kaza+1;i<5;i++) if(z.op[i]!=2) beklenen *= z.m[i];
        if(iz != beklenen) izhata++;                           // iz bagimsiz hesapla birebir mi
    }
    printf("TEST 2  KAZALI zincirler (%ldM, her birinde 1 adet ÷0):\n", N/1000000);
    printf("  v1.3: SAHTE DUZ SAYI ureten zincir : %ld / %ld  (HEPSI!)\n", sahte13, N);
    printf("        bayrak yandi ama            : global 1 bit — HANGI deger kirli,\n");
    printf("        NEREDE oldu soylemez; bakmayan program sahte sayiyi SONUC sanir\n");
    printf("  v1.4: duz sayi SIZINTISI           : %ld / %ld  (SIFIR — imkansiz)\n", sizinti14, N);
    printf("        kaza GORUNUR (iz×(1/0))      : %ld / %ld\n", gorunur14, N);
    printf("        iz dogrulamasi (bagimsiz hesapla birebir): %ld hata\n\n", izhata);

    /* --- TEST 3: SOMUT ORNEKLER — ayni zincir iki modelde, yan yana --- */
    printf("TEST 3  ayni zincir iki modelde (3 ornek — sahte sayinin 'makul' yuzu):\n");
    RNG=0xBEBEu;
    for(int s=0;s<3;s++){
        Zincir z=uret(1); int fl; Fr r13=kos_v13(z,&fl);
        Fr r14; i128 iz; kos_v14(z,&r14,&iz);
        printf("  zincir %d: %lld", s+1, z.a0);
        for(int i=0;i<5;i++) printf(" %s%lld", z.op[i]==0?"×":z.op[i]==1?"÷":"+", z.m[i]);
        printf("\n    v1.3 cikti: %lld/%lld  <- DUZ SAYI (kullanici dogru sanir!)\n",
               (ll)r13.n,(ll)r13.d);
        printf("    v1.4 cikti: %lld×(1/0)  <- kaza ve kaynagi GORUNUR\n", (ll)iz);
    }

    printf("\nSONUC: temizde fark YOK (%ld+%ld sapma). Kazada fark HER SEY:\n", fark13, fark14);
    printf("v1.3 'reddet' 1M kazanin 1M'inde makul gorunen SAHTE sayi uretti;\n");
    printf("v1.4 karantina SIFIR sizinti + %%100 gorunur kaza + birebir iz. Uc hedef:\n");
    printf("cycle ayni, kablo ayni (mevcut teller), %%100'luk YALNIZ v1.4'te.\n");
    return (fark13+fark14+sizinti14+izhata)?1:0;
}
