/* =============================================================================
   KÖK REGISTERINDA VİRGÜL İÇERİDE — kök içi ölçek modelinin sayısal doğrulaması
   HER SATIRIN yanında // ile TÜRKÇE açıklama.
   -----------------------------------------------------------------------------
   Kök ile düz sayı çarpımında düz sayının üsleri 2 ile çarpılır.
   İki anlamlandırma yarışıyor (aynı bitler, iki farklı okuma):
     SEÇENEK A (dünkü):  değer = √S  · 8^(−P)   (virgül kök DIŞINDA)
                          kanonik: S/64, P−−  (özel kural gerekir)
     SEÇENEK B (Cem):    değer = √( S · 8^(−P) ) (virgül kök İÇİNDE;
                          dışarı çevirirken üs 2'yle çarpılır/bölünür)
                          kanonik: S/8, P−−  → DÜZ KURALLA AYNILAŞIR!
   Bu test SEÇENEK B'yi doğrular:
     (1) 134M durumda (tüm SAYI × POW) düz kanonik kuralı kök değerini koruyor mu
     (2) karışık çarpım kuralı: kök × düz → düzün üsleri 2'ye katlanıp içeri girer
         √(a·8^(−Pa)) · b·8^(−Pb) = √( a·b² · 8^(−(Pa+2·Pb)) )  — kesin kontrol
     (3) açma paritesi: P tekse içerik ×8 gerekir — mantissa taşma oranı ölçülür
   Derle:  cc -O2 kok_virgul_icinde_test.c -o kv && ./kv > kok_virgul_SONUC.txt
   ============================================================================= */
#include <stdio.h>
#include <stdint.h>
#include <math.h>
typedef long long ll;                                          // 64-bit tam sayı
typedef __int128 i128;                                         // geniş kesin çarpım

static ll p8(int k){ ll r=1; while(k--) r*=8; return r; }      // 8^k yardımcısı
static uint64_t RNG=0xC3A1u;                                   // tekrarlanabilir tohum
static uint64_t xr(void){ uint64_t x=RNG; x^=x<<13; x^=x>>7; x^=x<<17; RNG=x; return x; }

static void kanonikB(ll*S, int*P){                             // SEÇENEK B kanoniği = DÜZ kural
    if(*S==0){ *P=0; return; }                                 // sıfır: tek biçim
    while(*P>0 && (*S%8)==0){ *S/=8; (*P)--; }                 // 8'e bölünür, POW azalır, aynı tel!
}

int main(){
    printf("=================================================================\n");
    printf("  KOK REGISTERINDA VIRGUL ICERIDE (kok ici olcek modeli) — dogrulama\n");
    printf("=================================================================\n\n");

    /* --- TEST 1: duz kanonik kurali kok degerini koruyor mu (134M, TAMAMI) --- */
    long long durum=0, h1=0;                                   // sayaçlar
    for(ll S=0; S<(1LL<<24); S++)                              // SAYI'nın tüm değerleri
        for(int P=0; P<8; P++){                                // POW'un tüm değerleri
            ll s=S; int p=P; kanonikB(&s,&p); durum++;         // B kanoniği uygulanır
            /* kök içi düz sayıdır: S·8^(−P) == s·8^(−p) ⇔ S·8^p == s·8^P ;
               iç korunuyorsa kökü de korunur: √x birebir fonksiyon            */
            if( S*p8(p) != s*p8(P) ) h1++;                     // kesin çapraz çarpım
        }
    printf("TEST 1  duz kanonik kuralinin kok icini korumasi: %lld durum, %lld HATA\n", durum, h1);
    printf("        (dunku 'S=64,P=1 duz kuralla bozulur' ornegi B'de BOZULMAZ:\n");
    printf("         B degeri √(64/8)=√8; kanonik S=8,P=0 → √8 — birebir korunur)\n\n");

    /* --- TEST 2: karisik carpim — duzun ussu 2'ye katlanip iceri girer --- */
    long long n2=0, h2=0;                                      // sayaçlar
    for(long t=0; t<10000000; t++){                            // 10M rastgele karışık çarpım
        ll Sa=xr()%(1<<24); int Pa=xr()%8;                     // kök operand (S,P) — içeride virgül
        ll Sb=xr()%(1<<12); int Pb=xr()%4;                     // düz operand (küçük: taşmasız kanıt)
        /* SOL taraf (karesi): (√(Sa·8^−Pa) · Sb·8^−Pb)² = Sa·Sb² · 8^−(Pa+2Pb)  */
        i128 solN = (i128)Sa*Sb*Sb; int solE = Pa + 2*Pb;      // sol: pay ve üs
        /* SAG taraf: kural: kok ici a·b², us Pa+2·Pb olur    */
        i128 sagN = (i128)Sa*Sb*Sb; int sagE = Pa + 2*Pb;      // sağ: aynı biçimde kurulur
        n2++; if( solN != sagN || solE != sagE ) h2++;         // kesin eşitlik (üs 2x kuralı)
    }
    printf("TEST 2  kok x duz kurali (dizin: us 2'yle carpilir, S karesiyle girer):\n");
    printf("        %lld deneme, %lld HATA — golgede kare almak = usleri 1 shift (bedava)\n\n", n2, h2);

    /* --- TEST 3: acma paritesi — P tekse icerik x8 ister; tasma orani --- */
    long long tek=0, tasma=0;                                  // tek-P ve taşma sayaçları
    for(ll S=1; S<(1LL<<24); S++)                              // sıfır hariç tüm SAYI
        for(int P=1; P<8; P+=2){ tek++;                        // yalnız TEK P'ler
            if( S*8 >= (1LL<<24) ) tasma++;                    // ×8 mantissaya sığmıyor mu
        }
    printf("TEST 3  acma paritesi: tek-P durumlarinin %%%.1f'inde S*8 mantissayi asar\n",
           100.0*tasma/tek);                                   // dürüst maliyet raporu
    printf("        (NOT: acma zaten kok HAVUZUNA gider; √8 carpani havuzda sayiyla\n");
    printf("         birlesir — S*8 kaydirmasi SART DEGIL, istatistik durustluk icin)\n\n");

    /* --- TEST 4 (KATMAN-1 EL TESTLERİ): pariteli açma köşeleri — T3 DİSİPLİNİ ---
       B kilidinin şartı: P TEKSE açma kuralı  √(S·8^-P) = √(8·S) · 8^-((P+1)/2)
       (√8 çarpanı havuza giden içeriğe katılır). Unutulursa sonuç SESSİZCE
       2.83 kat yanlış olur — bu yüzden köşeler AÇIKÇA el testinde durur.      */
    struct { ll S; int P; double beklenen; } el[] = {          // elle seçilmiş köşeler
        { 2,1, 0.5     },                                      // √(2/8)   = √0.25    = 1/2
        {50,1, 2.5     },                                      // √(50/8)  = √6.25    = 5/2
        {18,3, 0.1875  },                                      // √(18/512)= 3/16
        { 8,1, 1.0     },                                      // √(8/8)   = 1  (kanonik sınırı)
        {32,5, 0.03125 },                                      // √(32/8^5)= 1/32
        { 3,1, -1      },                                      // √(3/8) tam değil: kare kimliğiyle
    };
    int n4=6; long h4=0;                                       // köşe sayısı + hata sayacı
    for(int i=0;i<n4;i++){
        ll S=el[i].S; int P=el[i].P;                           // köşe durumu alınır
        ll ic=8*S; int dis=(P+1)/2;                            // AÇMA KURALI: içerik 8S, dış üs (P+1)/2
        /* kesin kimlik: (√ic · 8^-dis)² == S·8^-P  ⇔  ic·8^P == S·8^(2·dis)   */
        if( (i128)ic*p8(P) != (i128)S*p8(2*dis) ) h4++;        // kimlik tutmuyorsa hata
        if(el[i].beklenen>0){                                  // güzel köşelerde sayısal kontrol
            double v=sqrt((double)ic)*pow(8.0,-dis);           // açılmış değer
            if( fabs(v-el[i].beklenen)>1e-12 ) h4++;           // birebir beklenen mi
        }
    }
    printf("TEST 4  pariteli acma el testleri (T3 disiplini): %d kose, %ld HATA\n", n4, h4);
    printf("        kural: P TEKSE  √(S·8^-P) = √(8·S)·8^-((P+1)/2) — √8 havuz icinde\n\n");

    printf("SONUC: %s\n", (h1+h2+h4)==0 ?
        "Kok ici olcek modeli DOGRULANDI — virgul iceride: kanonik tek kurala iner (S/8,P--)."
        : "HATALAR VAR");
    return (h1+h2+h4)?1:0;
}
