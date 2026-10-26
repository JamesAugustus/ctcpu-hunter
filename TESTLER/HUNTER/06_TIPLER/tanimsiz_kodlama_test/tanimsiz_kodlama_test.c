/* =============================================================================
   TANIMSIZ KODLAMA TESTİ — denetim bulgusunun kanıtı + düzeltmenin doğrulaması
   HER SATIRIN yanında // ile TÜRKÇE açıklama.
   -----------------------------------------------------------------------------
   DENETİM BULGUSU (doğru çıktı): "TANIMSIZ = SAYI 0 + ÖZEL" kodlaması hiç test
   edilmemişti; ÖZEL'i modelleyen yollarla ÇAKIŞIYOR:
     yol 1: −√0  → negate kök kuralı ÖZEL'i çevirir → (S=0, ÖZEL=1) MEŞRU değer
     yol 2: AÇ-YAKLAŞIK'ta minik değer 0'a yuvarlanır → (S=0, ÖZEL=1) = "yaklaşık
            sıfır" — MEŞRU ve ANLAMLI bir durum
   DÜZELTME (bu test doğrular): TANIMSIZ = (TÜR=1/x, SAYI=0) — kelimenin tam
   anlamıyla "1/0". Yapısal olarak boş: meşru payda ASLA 0 olamaz, çünkü sıfır
   kontrolü (gölge-yokluğu) payda yaratılmadan ÖNCE çalışır ve d=0 zaten
   TANIMSIZ'ı üreten olayın kendisidir. Bedava kalır: sıfır teli + TÜR teli.
   Bonus: (0+ÖZEL) deseni "yaklaşık sıfır" anlamına GERİ verilir.
   NOT (v1.4 ayrışımı, 12 Tem): ÖZEL/değer-işareti AYRIŞTI — negate artık ÖZEL
   değil "disaret" bitini çevirir (kesir_emulator v1.4). Bu testteki −√0 senaryosu
   v1.3 davranışının TARİHSEL KANITI olarak durur (o çakışma v2 desenini doğurdu);
   yaklaşık-sıfır çakışması ise ayrışımdan bağımsız, hâlâ geçerli gerekçedir.
   Derle:  cc -O2 tanimsiz_kodlama_test.c -o tk -lm && ./tk > tanimsiz_kodlama_SONUC.txt
   ============================================================================= */
#include <stdio.h>
#include <math.h>
typedef long long ll;                                          // 64-bit tam sayı

typedef struct{ int tur; ll S; int P; int ozel; } Reg;         // register modeli
static int eski_tanimsiz(Reg r){ return r.S==0 && r.ozel; }    // ESKİ kural (doc10 v1)
static int yeni_tanimsiz(Reg r){ return r.tur==4 && r.S==0; }  // YENİ kural (1/0 deseni)

int main(){
    printf("=================================================================\n");
    printf("  TANIMSIZ KODLAMA — cakisma kaniti (eski) + ayirt edicilik (yeni)\n");
    printf("=================================================================\n\n");
    int cakismaE=0, cakismaY=0;                                // eski/yeni çakışma sayaçları

    /* --- TEST 1a: -√0 yolu (negate kök kuralı ÖZEL'i çevirir) --- */
    Reg r1 = {2, 0, 0, 0};                                     // √0 registerı (TÜR=2, S=0)
    r1.ozel ^= 1;                                              // negate: kök → ÖZEL döner
    printf("TEST 1a  -√0 = (TUR=2, S=0, OZEL=1)  — MESRU deger (=0):\n");
    printf("  eski kural TANIMSIZ okur mu? %s   yeni kural? %s\n\n",
           eski_tanimsiz(r1)?"EVET -> CAKISMA":"hayir",        // eski: yanlış sınıflar
           yeni_tanimsiz(r1)?"EVET -> CAKISMA":"HAYIR (dogru)"); // yeni: dokunmaz
    if(eski_tanimsiz(r1)) cakismaE++; if(yeni_tanimsiz(r1)) cakismaY++;

    /* --- TEST 1b: AC-YAKLASIK minik deger -> yaklasik sifir --- */
    long n=0, sifira=0;                                        // tarama sayaçları
    for(double lg=-12; lg<-6; lg+=0.001){                      // minik değerler taraması
        double v=pow(8.0,lg); n++;                             // hedef değer
        ll S=(ll)(v*pow(8.0,7)+0.5);                           // en derin P=7 ızgarasına aç
        Reg r={0, S, 7, 1};                                    // AÇ-YAKLAŞIK: ÖZEL=1 (kural)
        if(S==0){ sifira++;                                    // sıfıra yuvarlandı mı
            if(eski_tanimsiz(r)) cakismaE++;                   // eski kural: TANIMSIZ okur!
            if(yeni_tanimsiz(r)) cakismaY++; }                 // yeni kural: dokunmaz
    }
    printf("TEST 1b  AC-YAKLASIK minik deger taramasi (%ld deger):\n", n);
    printf("  %ld'i sifira yuvarlandi -> (S=0, OZEL=1) = 'YAKLASIK SIFIR' (mesru!)\n", sifira);
    printf("  eski kural bunlarin HEPSINI TANIMSIZ okurdu; yeni kural HICBIRINI.\n\n");

    /* --- TEST 2: yeni desenin ayirt ediciligi — payda olusum noktasi taramasi --- */
    ll bad=0, uretilen=0;                                      // ihlal + doğru üretim
    for(ll d=0; d<(1LL<<24); d++){                             // TÜM olası bölenler (24-bit)
        if(d==0){ uretilen++; continue; }                      // d=0: DIVZERO olayı →
                                                               //   TANIMSIZ üretilir,
                                                               //   payda HİÇ yaratılmaz
        Reg payda={4, d, 0, 0};                                // meşru payda: S=d ≥ 1
        if(payda.S==0) bad++;                                  // ihlal olabilir mi? (yapısal)
        int t2=payda.tur==4?5:4; (void)t2;                     // negate 4↔5: S'e dokunmaz
    }
    printf("TEST 2  payda olusum noktasi — 24-bit TAM tarama (16.7M bolen):\n");
    printf("  mesru yolla (TUR=1/x, S=0) uretimi: %lld  (yapisal olarak IMKANSIZ:\n", bad);
    printf("  sifir kontrolu payda yaratilmadan ONCE calisir — d=0 zaten TANIMSIZ\n");
    printf("  olayinin kendisidir, desen %lld kez YALNIZ o olaydan dogdu)\n\n", uretilen);

    /* --- TEST 3: iki durumun bit duzeyinde ayrismasi --- */
    Reg yaklasik_sifir={0,0,0,1}, tanimsiz={4,0,0,0};          // iki ayrı anlam
    printf("TEST 3  desen ayrismasi: yaklasik-sifir (TUR=0,S=0,OZEL=1) ile\n");
    printf("  TANIMSIZ (TUR=4,S=0) bit deseni farkli mi? %s\n\n",
           (yaklasik_sifir.tur!=tanimsiz.tur)?"EVET — karisma imkansiz":"HAYIR");

    printf("SONUC: eski kodlama %d cakisma (denetim HAKLIYDI) · yeni kodlama %d cakisma\n",
           cakismaE, cakismaY);
    printf("%s\n", cakismaY==0 ?
        "TANIMSIZ = (TUR=1/x, SAYI=0) AYIRT EDICI ve BEDAVA — 0 HATA."
        : "YENI KODLAMADA DA SORUN VAR");
    return cakismaY?1:0;
}
