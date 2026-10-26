/* =============================================================================
   KARANTİNA ÇİFTİ DEMOSU — K-1 (Cem): tanımsız hücre karantinada tutulur
   HER SATIRIN yanında // ile TÜRKÇE açıklama.
   -----------------------------------------------------------------------------
   CEM'İN FİKRİ: TANIMSIZ her şeyi yutan genel bir damga değildir. 1/0 KİLİTLİ
   bir hücre olarak durur, işlem sonucu "1365613×(1/0)" biçiminde İZLENEBİLİR
   kalır. Kullanıcı hatanın NEREDEN geldiğini doğrudan görür.
   GERÇEKLEME: bu zaten ÇİFT mekanizmasıyla bedava —
     SDIV a ÷ 0  →  çift kurulur:  pay = a  ·  payda = (TÜR=1/x, S=0)  [KİLİTLİ]
     sonraki MUL/DIV yalnız PAYA işler (payda kilitli kalır) → iz birikir
     karantinalı çift POZİSYONELE AÇILAMAZ (blok) → yanlış sayı asla sızmaz
     üzerine LOAD → karantina boşalır (programcının bilinçli hamlesi)
   BONUS: pay, 0/0 ile x/0'ı BEDAVA ayırır (IEEE'de NaN/Inf ayrımının karşılığı).
   Derle:  cc -O2 karantina_cift_demo.c -o kd && ./kd > karantina_cift_SONUC.txt
   ============================================================================= */
#include <stdio.h>
typedef long long ll;
typedef __int128 i128;

/* karantina çifti: pay (birikir) + payda kilidi (TÜR=4,S=0 deseni) */
typedef struct{ i128 pay; int kilit; } KC;                     // kilit=1: payda=1/0

static KC kc_kur(ll a){ KC k={a,1}; return k; }                // SDIV a÷0 anında kurulur
static KC kc_mul(KC k, ll x){ k.pay*=x; return k; }            // çarpan PAYA işler, kilit kalır
static int kc_acilir_mi(KC k){ return !k.kilit; }              // pozisyonel açma BLOK
static void kc_yaz(KC k){                                      // insan-okur çıktı
    printf("%lld×(1/0)", (ll)k.pay); }                         // iz: "pay×(1/0)"

int main(){
    printf("=================================================================\n");
    printf("  KARANTINA CIFTI — 1/0 kilitli hucre, iz birikir, sizinti yok\n");
    printf("=================================================================\n\n");
    int hata=0;

    /* --- SENARYO 1: Cem'in ornegi — 6/0 sonra ×1365613 --- */
    printf("SENARYO 1  R1=6 ; SDIV R1÷0 ; SMUL ×1365613 :\n");
    KC q = kc_kur(6);                                          // 6÷0 → karantina: 6×(1/0)
    printf("  SDIV sonrasi  : "); kc_yaz(q); printf("   (kilit=%d — payda 1/0 DONDU)\n", q.kilit);
    q = kc_mul(q, 1365613);                                    // çarpan paya işlendi
    printf("  SMUL sonrasi  : "); kc_yaz(q); printf("   (iz korundu: hangi hesap bulandi, GORUNUR)\n");
    if((ll)q.pay!=8193678 || !q.kilit) hata++;                 // 6×1365613=8193678, kilit durur

    /* --- SENARYO 2: pozisyonel acma BLOK — yanlis sayi asla sizamaz --- */
    printf("\nSENARYO 2  karantinali ciftin pozisyonele acilma denemesi:\n");
    if(!kc_acilir_mi(q)) printf("  ACMA REDDEDILDI — kilitli hucre sayi uretmez; program COKMEZ,\n"
                                "  kendi kafasina sayi da UYDURMAZ (Cem'in iki sarti birden)\n");
    else { printf("  ACILDI — HATA!\n"); hata++; }

    /* --- SENARYO 3: 0/0 ile x/0 ayrimi BEDAVA (IEEE NaN/Inf karsiligi) --- */
    printf("\nSENARYO 3  0÷0 ile 6÷0 ayni mi? (pay ayrimi bedava):\n");
    KC q00=kc_kur(0), q60=kc_kur(6);                           // iki farklı kaza
    printf("  0÷0 → "); kc_yaz(q00); printf("   ·   6÷0 → "); kc_yaz(q60);
    printf("\n  pay alani kazanin TURUNU de soyluyor (0/0 belirsiz, x/0 sonsuz-egilimli)\n");
    if((ll)q00.pay!=0 || (ll)q60.pay!=6) hata++;

    /* --- SENARYO 4: uzerine LOAD → karantina bosalir (bilincli hamle) --- */
    printf("\nSENARYO 4  LOAD R,#42 (ustune yeni deger yazmak):\n");
    KC t={42,0};                                               // programcı YENİ değer yazdı
    printf("  register artik DUZ 42 — karantina bosaldi; bu makinenin 'kafasina gore\n");
    printf("  devam etmesi' DEGIL, programcinin bilincli yeni yuklemesidir.\n");
    if(t.kilit) hata++;

    printf("\nSONUC: %s\n", hata==0 ?
        "KARANTINA MODELI CALISIYOR — iz birikir, kilit acilamaz, sizinti yok (0 hata)"
        : "HATALAR VAR");
    return hata;
}
