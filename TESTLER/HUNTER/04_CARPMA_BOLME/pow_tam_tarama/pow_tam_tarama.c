/* =============================================================================
   POW TAM TARAMASI — virgüllü (SAYI, POW) uzayının TAMAMI, istisnasız
   HER SATIRIN yanında // ile TÜRKÇE açıklama.
   -----------------------------------------------------------------------------
   Cem'in düzeltmesi: "24 bitin içinde virgüllüler de var, POW mevzularımız
   vardı." Doğru — tam tarama iddiası SAYI katmanıyla sınırlı kalamaz.
   BU TEST: SAYI'nın 16.777.216 değeri × POW'un 8 değeri = 134.217.728 durumun
   TAMAMINI tarar (değer = SAYI × 8^(−POW), kesir katmanındaki kanonik kural):
     (1) kanonikleştirme DEĞERİ KORUYOR mu (çapraz çarpım ile kesin kontrol)
     (2) kanonikleştirme İDEMPOTENT mi (ikinci uygulama hiçbir şey değiştirmemeli)
     (3) kanonik biçim YAPISAL olarak doğru mu (S%8!=0 ya da P==0; sıfırda P=0)
   TÜR katmanı ayrıca 8×8 tablo testiyle TAM kapsanmıştı (64 hücrenin hepsi).
   Derle:  cc -O2 pow_tam_tarama.c -o pt && ./pt > pow_tam_tarama_SONUC.txt
   ============================================================================= */
#include <stdio.h>
typedef long long ll;                                          // 64-bit tam sayı kısaltması

static ll p8(int k){ ll r=1; while(k--) r*=8; return r; }      // 8^k (k<=7, taşma yok: 8^7≈2.1M)

/* kanonik kural (kesir_emulator ile birebir): SAYI 8'e bölünüyorken ve POW>0
   iken sadeleşir (S/=8, P--); SAYI sıfırsa POW'un anlamı yok, P=0'a çekilir.   */
static void kanonik(ll*S, int*P){
    if(*S==0){ *P=0; return; }                                 // sıfır: tek kanonik biçim (0, P=0)
    while(*P>0 && (*S%8)==0){ *S/=8; (*P)--; }                 // sondaki oktal sıfırlar atılır
}

int main(){
    printf("=================================================================\n");
    printf("  POW TAM TARAMASI — (SAYI x POW) uzayinin TAMAMI: 16.777.216 x 8\n");
    printf("=================================================================\n\n");
    long long durum=0, h_deger=0, h_idem=0, h_yapi=0;          // sayaçlar: durum + üç hata türü

    for(ll S=0; S<(1LL<<24); S++){                             // SAYI'nin TÜM 24-bit değerleri
        for(int P=0; P<8; P++){                                // POW'un TÜM 8 değeri (1 xbit)
            ll s=S; int p=P;                                   // çalışma kopyası (orijinal saklı)
            kanonik(&s,&p);                                    // kanonikleştirilir
            durum++;                                           // bir durum daha tarandı
            /* (1) DEĞER KORUNUMU: S/8^P == s/8^p  ⇔  S·8^p == s·8^P (kesin) */
            if( S*p8(p) != s*p8(P) ) h_deger++;                // çapraz çarpım tutmadı → hata
            /* (2) İDEMPOTENS: ikinci kanonikleştirme hiçbir şey değiştirmemeli */
            ll s2=s; int q=p; kanonik(&s2,&q);                 // bir daha uygulanır
            if( s2!=s || q!=p ) h_idem++;                      // değiştiyse kural kararsız → hata
            /* (3) YAPI: kanonikte ya S%8!=0 ya P==0; sıfırda mutlaka P==0 */
            if( s==0 ? (p!=0) : (p>0 && s%8==0) ) h_yapi++;    // yapısal ihlal → hata
        }
    }
    printf("TARANAN DURUM : %lld (SAYI x POW uzayinin TAMAMI, istisnasiz)\n", durum);
    printf("DEGER KORUNUMU: %lld hata\n", h_deger);
    printf("IDEMPOTENS    : %lld hata\n", h_idem);
    printf("YAPISAL KURAL : %lld hata\n", h_yapi);
    printf("\nSONUC: %s\n", (h_deger+h_idem+h_yapi)==0 ?
        "134M durumda 0 hata — virgullu katman TAM tarandi." : "HATALAR VAR");
    printf("NOT: TUR katmani 8x8 tablo testiyle ayrica TAM kapsandi (64 hucre);\n");
    printf("     SAYI katmani RESOLVER'da TAM taranmisti (24-bit x 7 asal).\n");
    printf("     Tek-deger uzayi SAYIxPOWxTUR = 2^30 boylece uc katmanda kapsandi.\n");
    return (h_deger+h_idem+h_yapi)?1:0;
}
