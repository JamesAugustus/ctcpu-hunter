/* =============================================================================
   TÜR×POW TAM TARAMASI — tek-değer uzayının GERÇEK tamamı: 2³⁰ ≈ 1.07 MİLYAR
   HER SATIRIN yanında // ile TÜRKÇE açıklama.
   -----------------------------------------------------------------------------
   Cem'in itirazı: 134 milyon SAYI × POW durumuna 8 TÜR de katılır, eksiler,
   karekökler ve imajinerler de kapsanır. Bu test SAYI(2²⁴) × POW(8) × TÜR(8)
   uzayının TAMAMINI tarar. Ve birleşik tarama bir TASARIM GERÇEĞİNİ zorlar:
   kanonik kural TÜR'e göre DEĞİŞMEK zorundadır —
     TÜR 0,1 (±x)   : S/=8,  P--  (bilinen kural: değer = S·8^(−P))
     TÜR 4,5 (±1/x) : S/=8,  P++  (TERS YÖN! değer = 8^(−P)/S; payda POW'unun
                                   "yukarı ölçek" olması ilkesinin doğrulaması)
     TÜR 2,3 (√,i√) : S/=64, P--  (İKİ oktal basamak birden — çünkü √64 = 8;
                                   8'e bölmek YASAK: √8 irrasyonel, P telafisi yok)
     TÜR 6,7 (Σ,!)  : kaydırma YASAK (S sembol argümanıdır; f(S) doğrusal değil;
                                   ancak AÇILDIKTAN sonra düz kurala girer)
   Her durumda 3 kontrol: (1) değer KESİN korunuyor mu (çapraz çarpım; kökte
   kareler üzerinden), (2) idempotens, (3) yapısal kural. İşaret (TÜR 1,5) ve
   imajinerlik (TÜR 3) kanonikte dokunulmaz — büyüklük kontrolü yeterli.
   Derle:  cc -O2 tur_pow_tam_tarama.c -o tpt && ./tpt > tur_pow_tam_tarama_SONUC.txt
   ============================================================================= */
#include <stdio.h>
typedef long long ll;                                          // 64-bit tam sayı
typedef __int128 i128;                                         // kök kontrolü için geniş çarpım

static ll p8(int k){ ll r=1; while(k--) r*=8; return r; }      // 8^k (k<=14: 8^14=2^42, sığar)

static void kan(int T, ll*S, int*P){                           // TÜR'e göre kanonik kural
    if(*S==0){ *P=0; return; }                                 // sıfır: her TÜR'de tek biçim
    switch(T){
        case 0: case 1:                                        // düz ±x
            while(*P>0 && (*S%8)==0){ *S/=8; (*P)--; } break;  // 8'e bölünür, POW azalır
        case 4: case 5:                                        // ters ±1/x
            while(*P<7 && (*S%8)==0){ *S/=8; (*P)++; } break;  // 8'e bölünür, POW artar (ters yön!)
        case 2: case 3:                                        // kök √S, i√S
            while(*P>0 && (*S%64)==0){ *S/=64; (*P)--; } break;// 64'e bölünür (√64=8), POW azalır
        default: break;                                        // Σ,!: sembol argümanı — DOKUNMA
    }
}

int main(){
    printf("=================================================================\n");
    printf("  TUR x POW TAM TARAMASI — 2^24 SAYI x 8 POW x 8 TUR = 2^30 durum\n");
    printf("=================================================================\n\n");
    long long toplam=0, TH=0;                                  // genel sayaçlar

    for(int T=0; T<8; T++){                                    // TÜM türler: + − √ i√ 1/ −1/ Σ !
        long long durum=0, h_deger=0, h_idem=0, h_yapi=0;      // bu TÜR'ün sayaçları
        for(ll S=0; S<(1LL<<24); S++){                         // SAYI'nın TÜM 24-bit değerleri
            for(int P=0; P<8; P++){                            // POW'un TÜM 8 değeri
                ll s=S; int p=P; kan(T,&s,&p); durum++;        // kanonikleştirilir, durum sayılır
                /* (1) DEĞER KORUNUMU — TÜR grubuna göre kesin çapraz çarpım:   */
                int ok;
                if(T==2||T==3)                                 // kök: v²=S·8^(−2P) üzerinden
                    ok = ( (i128)S*p8(2*p) == (i128)s*p8(2*P) );
                else if(T==4||T==5)                            // ters: v=8^(−P)/S
                    ok = ( s*p8(p) == S*p8(P) );               //   ⇔ s'·8^p' = S·8^P
                else                                           // düz (Σ,!'de kural no-op, geçer)
                    ok = ( S*p8(p) == s*p8(P) );               //   ⇔ S·8^p' = s'·8^P
                if(!ok) h_deger++;                             // korunmadıysa hata
                /* (2) İDEMPOTENS — ikinci uygulama değiştirmemeli              */
                ll s2=s; int q=p; kan(T,&s2,&q);               // bir daha kanonikleştirilir
                if(s2!=s || q!=p) h_idem++;                    // değiştiyse kural kararsız
                /* (3) YAPISAL KURAL — kanonik biçimin tanımı tutuyor mu        */
                int yapi_ok;
                if(s==0)              yapi_ok = (p==0);        // sıfırda POW sıfırlanmış olmalı
                else if(T==0||T==1)   yapi_ok = (s%8 !=0 || p==0); // düz: ya bölünmez ya P bitti
                else if(T==4||T==5)   yapi_ok = (s%8 !=0 || p==7); // ters: ya bölünmez ya P doldu
                else if(T==2||T==3)   yapi_ok = (s%64!=0 || p==0); // kök: 64 kuralı
                else                  yapi_ok = (s==S && p==P);    // Σ,!: hiç dokunulmamış olmalı
                if(!yapi_ok) h_yapi++;                         // yapı bozuksa hata
            }
        }
        printf("TUR %d : %lld durum — deger:%lld idem:%lld yapi:%lld hata\n",
               T, durum, h_deger, h_idem, h_yapi);             // TÜR başına rapor
        toplam+=durum; TH+=h_deger+h_idem+h_yapi;              // genel toplama eklenir
    }
    printf("\nTOPLAM: %lld durum (2^30 = 1.073.741.824), %lld HATA\n", toplam, TH);
    printf("SONUC : %s\n", TH==0 ?
        "1.07 MILYAR durumda 0 hata — tek-deger uzayi eksigiyle koklusuyle TAM tarandi."
        : "HATALAR VAR");
    return TH?1:0;
}
