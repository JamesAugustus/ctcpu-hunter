/* =============================================================================
   KESİR KATMANI EMULATORU v1.4 — K-1 karantina + ÖZEL/değer-işareti ayrışımı
   HER SATIRIN yanında // ile TÜRKÇE açıklama.
   v1.4 DEĞİŞİKLİKLERİ (12 Tem, Cem K-1 onayı + 1. tur ÖZEL ayrışım kilidi):
     - FLAG_DIVZERO KALKTI. Sıfıra bölme artık RED DEĞİL, KARANTİNA ÇİFTİ:
       a÷0 → [pay=a | payda=0 = "1/0" KİLİTLİ]. MUL/DIV yalnız PAYA işler
       (iz birikir: 6÷0 sonra ×1365613 → "8193678×(1/0)"), ADD kısa devre,
       AÇMA BLOK (kilitli hücre sayı üretmez), üzerine yazma temizler.
     - ÖZEL artık YALNIZ yaklaşıklık damgası; kök/Σ/! değer-işareti AYRI
       "disaret" bitine taşındı (−√x ile "yaklaşık √x" artık karışamaz).
     - KAZA SAYACI (Cem, 12 Tem): karantinada BOŞTA duran Ppayda alanı (1 xbit)
       = "kaç tanımsız girdi" sayacı → çıktı iz×(1/0)^k. Her yeni ÷0 kaza +1;
       karantina×karantina sayaçları TOPLAR; 7'de DOYGUN ("7+" = çok — tam
       sayım DUR/debug modunun işi). Yeni bit YOK — boş alan kullanıldı.
   -----------------------------------------------------------------------------
   GERÇEKLENEN KARARLAR:
     - Kesir = REGISTER ÇİFTİ: pay(TÜR=+/−) + payda(TÜR=1/x). Üsler HEP POZİTİF.
     - TÜR=1/x tek başına var olmaz (1/7 bile çift: pay=1, payda=7).
     - POW EMİLİMİ (TABAN 8 — Cem: oktal 10=8): payda YALNIZ 2'lerden VE sığıyorsa → SAYI+POW.\n       (5'ler EMİLMEZ: 1/5, 1/10 çift olarak KESİN yaşar — dürüst sınır.)
     - PAYDA POW'u = YUKARI ölçek (değer = (Sa/Sb)×8^(Pb−Pa)), işaretli aralık ±7.
     - NEGATE TABLOSU: 0↔1, 4↔5; kök/Σ/! tiplerinde ÖZEL bayrağı (−√x ≠ i√x !).
     - AÇMA MODU (S⇔D): 00 KESİN-TUT / 01 AÇ-KESİN / 10 AÇ-YAKLAŞIK(+ÖZEL) / 11 OTOMATİK.
     - Sadeleşme LAZY (okuma anında); payda gölgesiz taşınır (gerekince "resolver" = gcd).
   DOĞRULAMA: her sonuç __int128 kesin-kesir referansıyla birebir. Yaklaşık modda hata ölçülür.
   Derle:  cc -O2 kesir_emulator.c -o ke -lm && ./ke > kesir_TEST_CIKTI.txt
   ============================================================================= */
#include <stdio.h>
#include <stdint.h>
typedef __int128 i128;                                       // kesin referans icin genis tamsayi
typedef long long ll;

static const ll MMAX = 16777215;                             // mantissa siniri (24-bit)
static ll gcdll(ll a, ll b){ while(b){ ll t=a%b; a=b; b=t; } return a; } // "resolver" modeli: ortak carpan bulucu
static ll p8(int k){ ll r=1; while(k-->0) r*=8; return r; }  // 8^k (k<=7) — TABAN 8 (Cem: oktal 10 = 8)
static int FLAG_OVF=0;                                        // kenar korumasi (DIVZERO v1.4'te KALKTI → karantina)

/* ---- SAYI: makinedeki hali — pay/payda mantissa + iki POW + isaret + bayraklar ---- */
typedef struct{
    ll pay, payda;                                           // iki mantissa (payda=1 ise TEK register demek)
    int Ppay, Ppayda;                                        // iki POW alani (0..7); payda POW'u = yukari olcek
    int sign;                                                // isaret (TUR'un icinde: 0=+, 1=−)
    int ozel;                                                // OZEL: YALNIZ yaklasiklik damgasi (v1.4 ayrisimi)
    int disaret;                                             // DEGER-ISARETI: kok/Σ/! deger isareti — OZEL'den AYRI bit
} Num;

/* ---- KARANTINA (v1.4, K-1 kilidi): payda==0 = kilitli "1/0" hucresi ---- */
static int tanimsiz(Num x){ return x.payda==0; }             // TANIMSIZ mi? ((TUR=1/x, S=0) deseninin kesir modeli)

/* ---- kesin referans: (num/den) sadelesmis kesir olarak degeri verir ---- */
static void ref_of(Num x, i128*num, i128*den){               // degeri kesin kesire cevirir (kontrol icin)
    if(x.payda==0){ *num=0; *den=0; return; }                // karantina: kesin degeri YOKTUR (testler tanimsiz() kullanir)
    i128 n = x.pay, d = x.payda;                             // temel oran: pay/payda
    int s = x.Ppayda - x.Ppay;                               // net olcek = Pb − Pa (payda POW'u buyutur)
    if(s>0) n *= (i128)p8(s); else d *= (i128)p8(-s);      // olcegi paya/paydaya isle (8^s)
    i128 a=n<0?-n:n, b=d;                                    // gcd ile sadelestirilir (karsilastirma kanonik olur)
    while(b){ i128 t=a%b; a=b; b=t; }
    if(a){ n/=a; d/=a; }
    if(x.sign) n=-n;                                          // isaret uygulanir
    *num=n; *den=d; }
static int eq_frac(Num x, i128 n2, i128 d2){                 // x == n2/d2 mi (kesin)?
    i128 n,d; ref_of(x,&n,&d); return n*d2 == n2*d; }

/* LAZY temizlik: kanonik() okuma aninda cagrilir (payda golgesiz; 'resolver'=gcd modeli) */
static int SADELESME_ADIM=0;                                  // istatistik: kac kez temizlik yapildi
static void kanonik(Num*x){                                   // TEMSIL FAZLALIGI kurali: tek kanonik form
    if(x->payda==0) return;                                   // KARANTINA: kilitli hucreye DOKUNULMAZ (v1.4)
    ll g = gcdll(x->pay, x->payda);                           // 1) sadelestirilir
    if(g>1){ x->pay/=g; x->payda/=g; SADELESME_ADIM++; }
    while(x->Ppay>0 && x->Ppayda>0){ x->Ppay--; x->Ppayda--; } // 2) iki POW ayni anda kirpilabilir (8/8=1, deger degismez)
    while(x->pay && x->pay%8==0 && x->Ppay>0){ x->pay/=8; x->Ppay--; }       // 3) payin 8'li carpanlari POW'la sadelesir (TABAN 8!)
    while(x->payda && x->payda%8==0 && x->Ppayda>0){ x->payda/=8; x->Ppayda--; } // 4) ayni sey payda icin (TABAN 8)
    if(x->payda==1 && x->Ppayda>0){                           // 5) payda 1 ise kalan yukari olcek mantissaya
        while(x->Ppayda>0 && x->pay*8<=MMAX){ x->pay*=8; x->Ppayda--; }
    }                                                          // sigmazsa Ppayda kalir (dogru: kaynak olarak durur)
}

/* ---- POW EMİLİMİ (TABAN 8): payda YALNIZ 2'lerden mi? 8^k'ya tamamla, POW'a em ---- */
static int pow_emilim(Num*x){                                 // 1=emildi (tek register), 0=olmadi
    if(x->payda==0) return 0;                                 // karantina EMILEMEZ (kilit; sonsuz dongu korumasi)
    ll d = x->payda; int a2=0;                                // paydanin 2 sayisi
    while(d%2==0){ d/=2; a2++; }                              // 2'ler sayilir
    if(d!=1) return 0;                                        // 3,5,7,rough varsa → EMILEMEZ (taban 8'de 5 de emilmez!)
    int k = (a2+2)/3;                                         // 8^k'ya tamamlama: k = tavan(a2/3)
    ll tam = 1; for(int i=0;i<3*k-a2;i++) tam*=2;             // eksik 2'ler (2^(3k−a2))
    if(x->pay > MMAX/(tam?tam:1)) return 0;                   // pay×tamamlayici 24-bit'e SIGMALI ("yerimiz varsa")
    if(x->Ppay + k > 7 + x->Ppayda) return 0;                 // net asagi olcek POW alanina (0..7) sigmali
    x->pay *= tam;                                            // tamamlayici PAY MANTISSASINA carpildi
    x->payda = 1;                                             // payda 8^k oldu → silindi
    x->Ppay += k;                                             // olcek POW'a yazildi (taban 8)
    kanonik(x);                                               // kanonik forma cek
    return 1; }

/* ---- İŞLEMLER: MUL, DIV (takas+MUL), kesirli ADD ---- */
static Num fmul(Num A, Num B){                                // (a/b)×(c/d): paylar ve paydalar kendi kanalinda
    Num R; R.sign = A.sign ^ B.sign; R.ozel = A.ozel|B.ozel;  // isaret XOR; yaklasiklik bulasir
    R.disaret = A.disaret ^ B.disaret;                        // deger-isareti carpimda XOR (v1.4 ayrisimi)
    if(tanimsiz(A) || tanimsiz(B)){                           // KARANTINA (v1.4): kontrollu bulasma —
        i128 wq=(i128)A.pay*B.pay;                            //   iz YALNIZ PAYDA birikir (Cem: 6×1365613)
        if(wq>MMAX) FLAG_OVF=1;                               //   iz de tasabilir; durust bayrak
        int k=(tanimsiz(A)?A.Ppayda:0)+(tanimsiz(B)?B.Ppayda:0); // KAZA SAYACI: (1/0)^k1 × (1/0)^k2
        R.pay=(ll)wq; R.payda=0; R.Ppay=0;                    //   payda "1/0" KILITLI kalir
        R.Ppayda = k>7?7:k;                                   //   sayac toplanir; 1 xbit → 7'de DOYGUN
        return R; }                                           //   payda kanali HIC calismadi (kisa devre)
    i128 wp = (i128)A.pay   * B.pay;                          // genis ara deger (model)
    i128 wd = (i128)A.payda * B.payda;
    if(wp>MMAX || wd>MMAX) FLAG_OVF=1;                        // KENAR KORUMASI: mantissa 24-bit'i asti → bayrak
    R.pay=(ll)wp; R.payda=(ll)wd;                             // (modelde deger korunur, donanimda bayrak/tuzak)
    R.Ppay   = A.Ppay + B.Ppay;                               // asagi olcekler toplanir
    R.Ppayda = A.Ppayda + B.Ppayda;                           // yukari olcekler toplanir
    if(R.Ppay>7 || R.Ppayda>7) FLAG_OVF=1;                    // POW alani da tasabilir (kanonik kirpar; asarsa bayrak)
    return R; }
static Num fdiv(Num A, Num B){                                // (a/b)÷(c/d) = TAKAS + MUL
    if(B.pay==0 && !tanimsiz(B)){                             // SIFIRA BOLME (v1.4): YENI KAZA — red YOK
        Num R=A; R.payda=0;                                   //   KARANTINA kurulur/surdurulur: [iz | "1/0"]
        int k=(tanimsiz(A)?A.Ppayda:0)+1;                     //   KAZA SAYACI +1 (Cem: kac 1/0 girdi)
        R.Ppayda = k>7?7:k;                                   //   1 xbit → 7'de DOYGUN ("7+")
        return R; }
    if(tanimsiz(A) || tanimsiz(B)) return fmul(A,B);          // karantinali operand: iz+sayac tasinir
    Num T = B; ll t = T.pay; T.pay = T.payda; T.payda = t;    // bolenin pay/paydasini takas et
    int tp = T.Ppay; T.Ppay = T.Ppayda; T.Ppayda = tp;        // POW'lari da takas (olcek tersine doner)
    return fmul(A, T); }
static Num fadd(Num A, Num B, int*adim){                      // kesirli TOPLAMA (E akisi): payda esitlenir → poz. toplama
    if(tanimsiz(A) || tanimsiz(B)){ *adim=0;                  // KARANTINA (v1.4): toplama KISA DEVRE —
        Num Q = tanimsiz(A)? A : B;                           //   hesap HIC calismaz, iz korunur
        if(tanimsiz(A) && tanimsiz(B)){                       //   iki karantina toplanirsa:
            int k=A.Ppayda+B.Ppayda; Q.Ppayda=k>7?7:k; }      //   KAZA SAYACLARI toplanir (bilgi kaybolmaz)
        return Q; }
    Num R; R.sign=0; R.ozel=A.ozel|B.ozel; *adim=0;
    R.disaret = A.disaret | B.disaret;                        // deger-isareti bilgisi korunur (v1.4)
    /* once olcekler mantissalara indirilir (toplama pozisyonel ister) */
    i128 na = (i128)A.pay * p8(A.Ppayda), da = (i128)A.payda * p8(A.Ppay); // A = na/da (genis ara)
    i128 nb = (i128)B.pay * p8(B.Ppayda), db = (i128)B.payda * p8(B.Ppay); // B = nb/db
    i128 ia = A.sign? -na : na, ib = B.sign? -nb : nb;        // isaretli paylar
    i128 pay = ia*db + ib*da; (*adim)+=3;                      // capraz MUL ×2 + POZISYONEL TOPLAMA = 3 adim
    i128 payda = da*db; (*adim)+=1;                            // payda esitleme carpimi = 1 adim
    if((pay<0?-pay:pay)>MMAX || payda>MMAX) FLAG_OVF=1;        // KENAR KORUMASI: sonuc 24-bit'i asti → bayrak
    R.sign = pay<0; R.pay = (ll)(pay<0? -pay: pay); R.payda = (ll)payda;
    R.Ppay = 0; R.Ppayda = 0;
    kanonik(&R); (*adim)+=2;                                   // okuma-ani temizlik = 2 adim (lazy politika)
    return R; }

/* ---- NEGATE TABLOSU: 8 TÜR × isaret-cevir → (hedef TÜR, DEGER-ISARETI) ---- */
/* TÜR: 0:+ 1:− 2:√+ 3:√− 4:1/+ 5:1/− 6:Σ 7:!  — v1.4: kok/seri deger-isareti
   ARTIK AYRI "disaret" bitinde (ÖZEL DEGIL — ÖZEL yalniz yaklasiklik damgasi;
   böylece −√x ile "yaklasik √x" hicbir zaman karisamaz — 1. tur kilidi)        */
static void negate(int*tur, int*disaret){
    switch(*tur){
        case 0: *tur=1; break;                                // +  → −
        case 1: *tur=0; break;                                // −  → +
        case 4: *tur=5; break;                                // 1/+ → 1/−
        case 5: *tur=4; break;                                // 1/− → 1/+
        case 2: case 3: case 6: case 7:                       // √±, Σ, ! : TÜR DEGISMEZ
            *disaret ^= 1; break;                             // DEGER-ISARETI cevrilir (−√x ≠ i√x !)
    } }

/* ---- AÇMA MODU: 00 KESİN-TUT / 01 AÇ-KESİN / 10 AÇ-YAKLAŞIK / 11 OTOMATİK ---- */
static const char* acma(Num*x, int mod){                      // sonucu moda gore bicimlendir; bicim adini dondur
    if(tanimsiz(*x)) return "KARANTINA (kilitli 1/0 — ACILAMAZ)"; // v1.4 BLOK: sayi uretmez, sizinti yok
    kanonik(x);                                               // once kanonik (lazy temizlik burada olur)
    if(x->payda==1 && x->Ppayda==0) return "TEK-REGISTER";    // zaten acik (tam sayi ya da kesin virgullu)
    if(mod==0) return "CIFT (kesin tut)";                     // 00: paydali kalir
    if(mod==1){ if(pow_emilim(x)) return "ACILDI-KESIN (POW)"; // 01: yalniz kayipsiz acilirsa
                else return "CIFT (kayipsiz acilamadi)"; }
    if(mod==2){                                               // 10: her durumda ac — gerekirse YAKLASIK
        if(pow_emilim(x)) return "ACILDI-KESIN (POW)";        // once kayipsiz acma denenir
        /* yaklasik ac: pay/payda pozisyonel bolme, 7 anlamli hane */
        i128 n = (i128)x->pay * p8(7);                       // 7 OKTAL hane hassasiyetle bolunur (8^7)
        ll q = (ll)( n / x->payda );                          // bolum (yaklasik mantissa)
        int P = 7 + x->Ppay - x->Ppayda;                      // olcek (taban 8)
        while(q>MMAX){ q/=8; P--; }                           // 24-bit'e sigdir
        while(P>7){ q/=8; P--; }                              // POW alanina sigdir (hassasiyet kirpilir, DURUST)
        if(P<0){ while(P<0 && q<=MMAX/8){ q*=8; P++; } }      // negatif olcek mantissaya
        x->pay=q; x->payda=1; x->Ppay=P<0?0:P; x->Ppayda=0;
        x->ozel=1;                                            // ÖZEL: "bu deger YAKLASIK" — kesin zincire karisamaz
        return "ACILDI-YAKLASIK (+OZEL)"; }
    /* mod==3 OTOMATIK: kayipsiz acilabiliyorsa acilir, degilse tutulur */
    if(pow_emilim(x)) return "ACILDI-KESIN (POW/oto)";
    return "CIFT (oto: kesin kalsin)"; }

static Num mk(ll pay, int Ppay, ll payda, int Ppayda, int sign){ // kisa kurucu
    Num x; x.pay=pay; x.Ppay=Ppay; x.payda=payda; x.Ppayda=Ppayda; x.sign=sign; x.ozel=0; x.disaret=0; return x; }

static int OK=0, FAIL=0;                                      // test sayaclari
static void chk(const char*ad, int kosul){                    // test raporlayici
    if(kosul){ OK++; printf("  [OK]   %s\n", ad); } else { FAIL++; printf("  [FAIL] %s\n", ad); } }

int main(){
    printf("=================================================================\n");
    printf("  KESIR KATMANI — EL TESTI (MUL/DIV kapanis turu)\n");
    printf("=================================================================\n\n");
    Num x; int adim;

    /* T1: 12/8 → 3/2 → AC-KESIN modda 15×10⁻¹ = 1.5 (kesin virgullu) */
    x = fdiv(mk(12,0,1,0,0), mk(8,0,1,0,0));                  // 12 ÷ 8 (iki tam sayi)
    const char* b1 = acma(&x, 1);                             // mod 01: kayipsizsa ac
    chk("T1  12/8 -> POW emilimi (TABAN 8) -> 12×8^-1 (=1.5=1.4oktal, kesin)",
        x.payda==1 && x.pay==12 && x.Ppay==1 && eq_frac(x,3,2));
    printf("       bicim: %s\n", b1);

    /* T2: (3/2)×(2/3) = 1 — cift kendini cozer */
    x = fmul(mk(3,0,2,0,0), mk(2,0,3,0,0)); kanonik(&x);
    chk("T2  (3/2)×(2/3) = 1 (cift cozuldu)", x.pay==1 && x.payda==1 && eq_frac(x,1,1));

    /* T3: (3/2)÷(3/4) = 2 — takas + MUL */
    x = fdiv(mk(3,0,2,0,0), mk(3,0,4,0,0)); kanonik(&x);
    chk("T3  (3/2)÷(3/4) = 2 (takas+MUL)", eq_frac(x,2,1));

    /* T4: 1/2^23 — POW emilimi REDDETMELI (8^k icin k=8 > POW alani 7) → cift kalir */
    x = fdiv(mk(1,0,1,0,0), mk(8388608,0,1,0,0));             // 1 ÷ 2^23
    const char* b4 = acma(&x, 1);                             // kayipsiz acma denenir
    chk("T4  1/2^23: emilim REDDETTI (k=8 > POW alani) -> cift kaldi, KESIN",
        x.payda==8388608 && eq_frac(x,1,8388608));
    printf("       bicim: %s (dogru davranis: POW alani siniri)\n", b4);

    /* T5: 100/19 — payda rough (19), cift, kesin */
    x = fdiv(mk(100,0,1,0,0), mk(19,0,1,0,0)); kanonik(&x);
    chk("T5  100/19: payda rough, cift, kesin", x.payda==19 && eq_frac(x,100,19));

    /* T6: 1.5 ÷ 0.25 = 6 — float÷float TABAN 8: 1.5=12×8⁻¹, 0.25=2×8⁻¹ */
    x = fdiv(mk(12,1,1,0,0), mk(2,1,1,0,0));                  // (12×8⁻¹) ÷ (2×8⁻¹)
    acma(&x, 1);                                              // mod 01: kayipsiz ac
    chk("T6  1.5 ÷ 0.25 = 6 (kesin, taban-8 virgullulerle)", eq_frac(x,6,1) && x.payda==1);

    /* T7: 1.5 ÷ 3.5 = 3/7 — taban-8 virgulluler (12×8⁻¹)÷(28×8⁻¹); kesir kalir, KESIN */
    x = fdiv(mk(12,1,1,0,0), mk(28,1,1,0,0)); kanonik(&x);
    chk("T7  1.5 ÷ 3.5 = 3/7 (kesin kesir; float yuvarlar, biz asla)", eq_frac(x,3,7));

    /* T8: (3/7)^3 = 27/343 — kuvvet iki kanalda */
    x = mk(3,0,7,0,0); x = fmul(x, fmul(mk(3,0,7,0,0), mk(3,0,7,0,0))); kanonik(&x);
    chk("T8  (3/7)^3 = 27/343", eq_frac(x,27,343));

    /* T9: 3 ÷ 0.875 — PAYDA POW'u: (3,P0)/(7,P1) = 24/7 (0.875 = 7×8⁻¹), rescale GEREKMEDEN */
    x = fdiv(mk(3,0,1,0,0), mk(7,1,1,0,0));                   // bolen 7×8⁻¹ = 0.875
    chk("T9  3 ÷ 0.875 = 24/7 (payda POW = yukari olcek, taban 8)", eq_frac(x,24,7));

    /* T10 (v1.4): NEGATE — deger-isareti AYRI bitte; OZEL'e DOKUNULMAZ */
    int tur=2, di=0, oz=0; negate(&tur,&di);                  // √+ 'yi negatifle
    chk("T10 negate(√+) = √+ + DEGER-ISARETI (OZEL degismedi; imajinere dusmedi)",
        tur==2 && di==1 && oz==0);
    tur=0; di=0; negate(&tur,&di); chk("T10b negate(+) = −", tur==1);
    tur=4; di=0; negate(&tur,&di); chk("T10c negate(1/+) = 1/−", tur==5);

    /* T11: KESIRLI TOPLAMA (E akisi): 3/2 + 1/3 = 11/6, adim sayisiyla */
    x = fadd(mk(3,0,2,0,0), mk(1,0,3,0,0), &adim);
    chk("T11 3/2 + 1/3 = 11/6 (payda esitle -> poz. topla)", eq_frac(x,11,6));
    printf("       adim: %d (2 capraz MUL + 1 payda MUL + 1 poz.topla + 2 temizlik)\n", adim);

    /* T12: ACMA MODU — ayni bolme (3/7) dort modda */
    printf("\n  T12 ACMA MODU (S⇔D): ayni sonuc 3/7, dort modda:\n");
    for(int m=0;m<4;m++){
        Num y = fdiv(mk(12,1,1,0,0), mk(28,1,1,0,0));         // 1.5/3.5 = 3/7 (taban 8)
        const char* b = acma(&y, m);
        i128 yn,yd; ref_of(y,&yn,&yd);
        double val = (double)(ll)yn / (double)(ll)yd;
        printf("     mod %d%d: %-28s deger=%.7f  OZEL=%d\n", m>>1, m&1, b, val, y.ozel);
        if(m==2){ chk("T12 mod 10: yaklasik deger 3/7'ye yakin (8^-7 hassasiyet) ve OZEL=1",
                      y.ozel==1 && val>0.428570 && val<0.428573); }
        if(m==0||m==3){ chk("T12 mod 00/11: kesin cift kaldi", eq_frac(y,3,7)); }
    }

    /* T13: RASTGELE zincir — 200K islem, kesin referansla birebir */
    { unsigned long long rng=0x77777u; long bad=0;
      for(long t=0;t<200000;t++){
          rng^=rng<<13; rng^=rng>>7; rng^=rng<<17;
          ll a=(ll)(rng%999)+1;  rng^=rng<<13; rng^=rng>>7; rng^=rng<<17;
          ll b=(ll)(rng%999)+1;  rng^=rng<<13; rng^=rng>>7; rng^=rng<<17;
          int pa=(int)(rng%3), pb=(int)((rng>>8)%3);
          Num A=mk(a,pa,1,0,0), B=mk(b,pb,1,0,0);
          Num R=(rng>>16)&1? fdiv(A,B):fmul(A,B); kanonik(&R);
          /* kesin referans */
          i128 rn,rd, an,ad2,bn,bd; ref_of(A,&an,&ad2); ref_of(B,&bn,&bd);
          if(((rng>>16)&1)){ rn=an*bd; rd=ad2*bn; } else { rn=an*bn; rd=ad2*bd; }
          if(rd<0){rd=-rd; rn=-rn;}
          if(!eq_frac(R, rn, rd)) bad++;
      }
      chk("T13 rastgele 200K MUL/DIV zinciri == kesin referans", bad==0);
      printf("       (sadelesme cagrisi toplam: %d — LAZY politika)\n", SADELESME_ADIM);
    }

    /* T14 (v1.4, K-1 KILIDI): SIFIRA BOLME = KARANTINA AKISI (bayrak/red KALKTI) */
    { Num a=mk(5,0,1,0,0), z=mk(0,0,1,0,0);
      Num r = fdiv(a,z);                                      // 5÷0 → [pay=5 | 1/0 kilitli]
      chk("T14a 5÷0 -> KARANTINA cifti (payda=1/0 kilitli, iz=5; red YOK, akis devam)",
          tanimsiz(r) && r.pay==5);
      r = fmul(r, mk(3,0,1,0,0));                             // karantina × 3 → iz birikir
      chk("T14b karantina ×3 -> 15×(1/0)  (iz birikti, kilit durdu)",
          tanimsiz(r) && r.pay==15);
      Num s = fadd(r, mk(7,0,1,0,0), &adim);                  // karantina + 7 → kisa devre
      chk("T14c karantina +7 -> hesap HIC CALISMADI (adim=0, iz korundu)",
          tanimsiz(s) && s.pay==15 && adim==0);
      chk("T14d karantina ACILAMAZ (kilitli hucre sayi uretmez — sizinti imkansiz)",
          acma(&s,2)[0]=='K');                                // "KARANTINA..." dondu
      Num y = mk(42,0,1,0,0);                                 // uzerine yazma = taze deger
      chk("T14e uzerine yazma (LOAD) temizler: register duz 42", !tanimsiz(y) && y.pay==42);

      /* T14f (Cem'in SAYAC fikri): 5 ayri 1/0 carpilirsa sayac 5 olmali */
      Num q5 = fdiv(mk(2,0,1,0,0), mk(0,0,1,0,0));            // kaza 1: 2÷0
      for(int i=0;i<4;i++)                                    // 4 kaza daha, hepsi carpima girer
          q5 = fmul(q5, fdiv(mk(3,0,1,0,0), mk(0,0,1,0,0)));
      chk("T14f 5 ayri (1/0) carpimi -> sayac=5: iz×(1/0)^5 — KAC tanimsiz girdi GORUNUR",
          tanimsiz(q5) && q5.Ppayda==5 && q5.pay==162);        // iz=2·3·3·3·3=162 birebir

      /* T14g Cem'in 1 MILYON girdi durumu: sayac 7'de DOYAR, akis surer */
      Num qM = fdiv(mk(1,0,1,0,0), mk(0,0,1,0,0));            // ilk kaza
      for(long i=0;i<1000000;i++)                             // 1 milyon kaza daha
          qM = fmul(qM, fdiv(mk(1,0,1,0,0), mk(0,0,1,0,0)));
      chk("T14g 1.000.001 kaza -> sayac DOYGUN '7+' (tam sayim DUR/debug isi), makine AKTI",
          tanimsiz(qM) && qM.Ppayda==7); }

    /* T15: MANTISSA TASMASI — MMAX asilirsa FLAG_OVF yanmali (Ajan B kenar korumasi) */
    FLAG_OVF=0;
    { Num a=mk(9999999,0,1,0,0), b=mk(9999999,0,1,0,0); fmul(a,b);
      chk("T15 mantissa tasmasi: 9999999×9999999 -> FLAG_OVF yandi", FLAG_OVF==1); }

    printf("\n=================================================================\n");
    printf("  SONUC: %d OK, %d FAIL. Kesir v1.4: TABAN 8 + K-1 KARANTINA + OZEL ayrisimi.\n", OK, FAIL);
    printf("  DURUST: yaklasik mod (10) OZEL ile isaretlenir (kesin degil). Karantina izi\n");
    printf("  TEK pay tasir: kesirli bolunende (a/b)÷0 izi a'dir — tam iz cift-ustu-cift\n");
    printf("  ister, model siniri olarak kayitli. Deger-isareti (disaret) OZEL'den ayridir.\n");
    printf("=================================================================\n");
    return FAIL? 1:0;
}
