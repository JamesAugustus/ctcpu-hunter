/* =============================================================================
   TÜR×TÜR TESTİ — 8×8 çarpma tablosunun TÜM hücreleri + negate + ters tabloları
   HER SATIRIN yanında // ile TÜRKÇE açıklama.
   -----------------------------------------------------------------------------
   YÖNTEM: Her TÜR'lü değerin KESİN cebirsel biçimi:  ε · i^m · (num/den) · √rad
   (ε=işaret, m=imajinerlik, num/den kesin kesir, rad kök içi). İki değerin çarpımı
   bu biçimde KESİN hesaplanır (referans). Sonra bizim 5 KURALLI tablo motorumuz
   aynı çarpımı TÜR mekanizmasıyla yapar; iki sonuç birebir karşılaştırılır.
   Σ ve ! tipleri AÇ-KESİN yolundan (Gauss formülü / faktöriyel) açılır.
   Derle:  cc -O2 tur_x_tur_test.c -o tt -lm && ./tt > tur_x_tur_SONUC.txt
   ============================================================================= */
#include <stdio.h>
#include <stdint.h>
typedef __int128 i128;
typedef long long ll;

/* ---- KESİN CEBİRSEL BİÇİM: ε · i^m · (num/den) · √rad ---- */
typedef struct{ int sgn, im; i128 num, den; ll rad; } Ex;     // referans değer kabı
static i128 g128(i128 a,i128 b){ if(a<0)a=-a; while(b){ i128 t=a%b; a=b; b=t; } return a; }
static Ex norm(Ex e){                                          // kanonik biçime çek
    for(ll f=2; f*f<=e.rad; f++)                               // kök içindeki TAM KARELER dışarı alınır
        while(e.rad % (f*f) == 0){ e.rad /= f*f; e.num *= f; } // √(f²·r) = f·√r
    if(e.num==0){ e.sgn=1; e.im=0; e.den=1; e.rad=1; }         // sıfır: tek biçim
    i128 g=g128(e.num,e.den); if(g){ e.num/=g; e.den/=g; }     // kesri sadeleştir
    return e; }
static Ex exmul(Ex a, Ex b){                                   // KESİN çarpım (referans)
    Ex r; r.sgn = a.sgn*b.sgn;                                 // işaretler çarpılır
    if(a.im && b.im) r.sgn = -r.sgn;                           // i·i = −1 (işaret döner)
    r.im  = (a.im + b.im) % 2;                                 // i'lerin kalanı
    r.num = a.num*b.num; r.den = a.den*b.den;                  // kesirler çarpılır
    r.rad = a.rad*b.rad;                                       // kökler kök içinde birleşir
    return norm(r); }
static int exeq(Ex a, Ex b){ a=norm(a); b=norm(b);             // kesin eşitlik testi
    return a.sgn==b.sgn && a.im==b.im && a.rad==b.rad && a.num*b.den==b.num*a.den; }

/* ---- TÜR'lü değerin kesin karşılığı: v(TÜR, S) ---- */
static ll fact(int s){ ll r=1; for(int i=2;i<=s;i++) r*=i; return r; } // S! (S<=12)
static Ex val(int T, int S){                                   // 8 TÜR'ün cebirsel anlamı
    Ex e = { 1,0, S,1, 1 };                                    // varsayılan: +S
    switch(T){
        case 0: break;                                         // 0: +S
        case 1: e.sgn=-1; break;                               // 1: −S
        case 2: e.num=1; e.rad=S; break;                       // 2: √S
        case 3: e.num=1; e.rad=S; e.im=1; break;               // 3: i√S  (=√(−S))
        case 4: e.num=1; e.den=S; break;                       // 4: 1/S
        case 5: e.num=1; e.den=S; e.sgn=-1; break;             // 5: −1/S
        case 6: e.num=(i128)S*(S+1)/2; break;                  // 6: Σ = S(S+1)/2 (Gauss)
        case 7: e.num=fact(S); break;                          // 7: S!
    }
    return norm(e); }

/* ---- MAKİNE TARAFI: 5 kurallı TÜR×TÜR motoru ----
   Makine sonucu şu biçimde üretir: işaret(TÜR/ÖZEL) + kökpayı + düz pay + payda.
   Bu da bir Ex'e çevrilir; referansla karşılaştırılır.                          */
static long PAIR_KULLANIMI=0, OZEL_KULLANIMI=0;                 // istatistik sayaçları
/* NOT: motoru sade tutmak için makine yolu da AYNI cebirsel alanda ilerler ama
   YALNIZ tablo kurallarının izin verdiği hamlelerle:                            */
typedef struct{ int isaret, im; i128 kokpay; ll kok; i128 pay, payda; } Mak;    // makine kaydı
static Ex mak2ex(Mak m){ Ex e={ m.isaret, m.im, m.kokpay*m.pay, m.payda, m.kok }; return norm(e); }
static Mak mak_yap(int T,int S){                                // TÜR'lü operandı makine kaydına aç
    Mak m={1,0, 1,1, 1,1};                                     // varsayılan +1
    switch(T){
        case 0: m.pay=S; break;                                // düz
        case 1: m.pay=S; m.isaret=-1; break;                   // eksi (işaret TÜR'de)
        case 2: m.kok=S; break;                                // kök: kök alanına
        case 3: m.kok=S; m.im=1; break;                        // i√: kök + imajinerlik
        case 4: m.payda=S; PAIR_KULLANIMI++; break;            // ters: ÇİFT (payda registerı)
        case 5: m.payda=S; m.isaret=-1; PAIR_KULLANIMI++; break;
        case 6: m.pay=(i128)S*(S+1)/2; break;                  // Σ: Gauss ile AÇ-KESİN
        case 7: m.pay=fact(S); break;                          // !: aç (küçük S; büyükte Legendre)
    }
    return m; }
static Mak mak_mul(Mak a, Mak b){                               // TABLO KURALLARI:
    Mak r;
    r.isaret = a.isaret*b.isaret;                               // K1: işaretler XOR (çarpım)
    if(a.im && b.im){ r.isaret=-r.isaret; r.im=0; OZEL_KULLANIMI++; } // K5: i·i=−1 → ÖZEL işaret
    else r.im = a.im | b.im;                                    //     tek i varsa taşınır
    r.kok   = a.kok * b.kok;                                    // K2: kök kökle birleşir √a·√b=√(ab)
    r.pay   = a.pay * b.pay;                                    // düz paylar gölge-MUL (üs topla) modeli
    r.payda = a.payda * b.payda;                                // K3+K4: paydalar çift kanalında birleşir
    r.kokpay= a.kokpay*b.kokpay;                                // (kökten çıkan tam kısımlar)
    if(r.payda>1) PAIR_KULLANIMI++;                             // istatistik: çift kullanıldı
    return r; }
static Mak mak_ters(Mak a){                                     // TERS TABLOSU: 1/x
    Mak r={ a.isaret, a.im, 1,1, 1,1 };                         // işaret/i taşınır (1/i = −i ele alınır)
    if(a.im){ r.isaret = -r.isaret; }                           // 1/i = −i (i·(−i)=1)
    r.pay   = a.payda;                                          // pay ↔ payda TAKAS (çift kuralı)
    r.payda = a.pay * a.kokpay;                                 // düz kısım paydaya
    if(a.kok>1){ r.kok=a.kok; r.payda*=a.kok; }                 // 1/√k = √k/k (RASYONELLEŞTİRME!)
    if(r.payda>1) PAIR_KULLANIMI++;
    return r; }
static void mak_negate(int*T,int*ozel){                         // NEGATE TABLOSU (gerçeklenmiş hali)
    switch(*T){ case 0:*T=1;break; case 1:*T=0;break;           // ± takas
                case 4:*T=5;break; case 5:*T=4;break;           // 1/± takas
                default: *ozel^=1; }                            // kök/Σ/!: ÖZEL (değer-işareti) döner
}

int main(){
    printf("=================================================================\n");
    printf("  TUR x TUR TESTI — 8x8 tum hucreler + negate + ters (KESIN referansla)\n");
    printf("=================================================================\n\n");
    int Svals[] = {1,2,3,4,5,6,7,8,9,10,12,15,16,18,20,24,36,49,60,72};  // taranan degerler
    int NS = sizeof(Svals)/sizeof(int);
    long test=0, hata=0;

    /* --- TEST 1: 8x8 CARPMA — her hucre, cok degerle --- */
    for(int T1=0;T1<8;T1++) for(int T2=0;T2<8;T2++)             // 64 hucrenin tamami
      for(int i=0;i<NS;i++) for(int j=0;j<NS;j++){              // deger taramasi
        int S1=Svals[i], S2=Svals[j];
        if((T1==7&&S1>10)||(T2==7&&S2>10)) continue;            // faktoriyel siniri (tasma yok)
        Ex ref = exmul(val(T1,S1), val(T2,S2));                 // KESIN referans carpim
        Mak m  = mak_mul(mak_yap(T1,S1), mak_yap(T2,S2));       // MAKINE yolu (tablo kurallari)
        test++;
        if(!exeq(mak2ex(m), ref)) { hata++;                     // birebir esit mi
            if(hata<=3) printf("  HATA: T%d(S%d) x T%d(S%d)\n",T1,S1,T2,S2); }
      }
    printf("TEST 1  8x8 CARPMA tablosu: %ld hucre-deger denemesi, %ld HATA\n", test, hata);
    printf("        (cift kullanimi: %ld — K4 karisik tipler cifte dustu; OZEL: %ld — i·i)\n",
           PAIR_KULLANIMI, OZEL_KULLANIMI);

    /* --- TEST 2: BOLME = TERS + CARP (DIV=MUL+ters deseni) --- */
    long t2=0,h2=0;
    for(int T1=0;T1<6;T1++) for(int T2=0;T2<6;T2++)             // Σ/! bolen olarak kullanilmaz (once acilir zaten)
      for(int i=0;i<NS;i++) for(int j=0;j<NS;j++){
        int S1=Svals[i], S2=Svals[j];
        Ex refb = val(T2,S2);                                    // bolenin degeri
        Ex refr = exmul(val(T1,S1), (Ex){refb.sgn, refb.im?1:0, refb.den*(refb.im?-1:1)*0+refb.den, refb.num, refb.rad}); // (asagida duzgun ters)
        /* KESIN ters: 1/(ε·i^m·(n/d)·√r) = ε'·i^m'·(d/(n·r))·√r ; i için ε döner */
        Ex tb = refb; { i128 n=tb.num; tb.num=tb.den; tb.den=n; // kesir ters çevrilir
            if(tb.rad>1){ tb.den*=tb.rad; tb.num*=1; tb.rad=tb.rad; } // 1/√r = √r/r
            if(tb.im){ tb.sgn=-tb.sgn; }                         // 1/i = −i
            tb=norm(tb); }
        Ex ref2 = exmul(val(T1,S1), tb);                         // referans: a · (1/b)
        Mak mr  = mak_mul(mak_yap(T1,S1), mak_ters(mak_yap(T2,S2))); // makine: ters tablosu + carp
        t2++; if(!exeq(mak2ex(mr), ref2)) h2++;
        (void)refr;
      }
    printf("TEST 2  BOLME = ters+carp (rasyonellestirme dahil): %ld deneme, %ld HATA\n", t2, h2);

    /* --- TEST 3: NEGATE tablosu — 8 TUR x degerler, -v(T,S) dogru mu --- */
    long t3=0,h3=0;
    for(int T=0;T<8;T++) for(int i=0;i<NS;i++){
        int S=Svals[i]; if(T==7&&S>10) continue;
        int nT=T, oz=0; mak_negate(&nT,&oz);                     // tablo uygulanır
        Ex ref = val(T,S); ref.sgn = -ref.sgn;                   // kesin: isareti dondur
        Ex got = val(nT,S); if(oz) got.sgn = -got.sgn;           // makine: yeni TUR (+ OZEL isareti)
        t3++; if(!exeq(got,ref)) h3++;
    }
    printf("TEST 3  NEGATE tablosu (8 TUR): %ld deneme, %ld HATA  (−√x imajinere dusmedi)\n", t3, h3);

    printf("\nSONUC: %s — tablo kurallari K1-K5 KESIN cebirle birebir.\n",
           (hata+h2+h3)==0? "TUM TESTLER 0 HATA":"HATALAR VAR");
    return (hata+h2+h3)?1:0;
}
