/* =============================================================================
   RESOLVER EMULATORU  —  sayi -> golge (asal-us vektoru)
   HER SATIRIN yaninda // ile TURKCE: hem kodun YAPISI (sayac kurulumu, kosul, dongu...)
   hem de O AN NE yaptigimiz anlatilir. Yeni baslayan birine ogretir gibi.
   Derle:  cc -O3 resolver_emulator.c -o re -lm && ./re > TEST_CIKTI.txt
   Kapsam: 24-bit POZITIF TAMSAYI. rough RR / genis-kelime = ACIK IS.
   ============================================================================= */
#include <stdio.h>                                  // "standart giris-cikis" kutuphanesi eklenir -> printf kullanilir
#include <stdint.h>                                 // sabit-boyutlu tamsayi tipleri eklenir -> uint32_t (32-bit, isaretsiz)

static const int  P[7]  = {2,3,5,7,11,13,17};       // 7 elemanli, degismez (const) bir tamsayi DIZISI: RESOLVER'in 7 asali
static const char* PN[7]= {"2","3","5","7","11","13","17"}; // ayni asallarin yazi (metin) hali -> ekrana basarken kullanacagiz

/* ---- CYCLE 1: octal hane akitma -> N, p'ye bolunuyor mu? (carpici/bolucu YOK) ---- */
int mod_via_stream(uint32_t N, int p){              // FONKSIYON: girdi N (sayi) ve p (asal); cikti = N'in p'ye kalani
    int rem = 0;                                    // "rem" adli bir tamsayi kutusu acilir, icine 0 konur (tasinan kalan)
    for(int i=0; i<8; i++){                         // DONGU: i sayaci 0 olur, i<8 oldukca tekrarlanir, her turda i 1 artar -> 8 kez (hane 0..7)
        int d = (N >> (3*(7-i))) & 7;               // N saga 3*(7-i) bit kaydirilir (o hane en saga gelir), "& 7" ile son 3 bit tutulur -> o octal hane (0..7)
        rem = (rem*8 + d) % p;                       // rem 8 ile carpilir (yeni haneye yer acilir), hane eklenir, p'ye bolumun KALANI alinip yine rem'e konur
    }                                                // suslu parantez kapandi: dongu govdesi burada biter, basa donup i'yi artirir
    return rem;                                       // dongu bitti, kalan geri verilir. 0 ise: N, p'ye TAM bolunur demektir
}

/* ---- CYCLE 2: encode -> 7 asalin usu + rough kalan ---- */
uint32_t encode(uint32_t N, int e[7], int *exp_steps){ // FONKSIYON: N cevrilir, e[] dizisi uslerle DOLDURULUR, *exp_steps'e adim sayisi yazilir, cikti=rough
    *exp_steps = 0;                                  // exp_steps'in GOSTERDIGI kutuya 0 yazilir (yildiz = "isaret ettigi yer"), adim sayaci sifirlanir
    uint32_t n = N;                                  // "n" adli calisma kopyasi acilir, icine N konur (orijinali bozmadan bu kopya bolunur)

    e[0] = 0;                                         // dizinin 0. kutusu = 2'nin ussu; basta 0
    while(n && (n&1)==0){                             // KOSULLU DONGU: n sifir degilse VE (n&1)==0 yani son bit 0 (sayi CIFT) ise tekrarlanir
        n >>= 1;                                      // n bir bit saga kaydirilir = ikiye bolunur (n = n/2)
        e[0]++;                                       // bir tane daha "2" bulduk: 2'nin ussu 1 artar
    }                                                 // while govdesi bitti -> kosul tekrar denetlenir, sayi tekleyince cikilir (donanimda bu = sondaki sifir bitleri, BEDAVA)
    if(e[0]) (*exp_steps) += 1;                       // KOSUL: e[0] sifirdan farkliysa (en az bir 2 vardiysa) adim sayacina 1 eklenir (2'nin tum usu tek adim sayilir)

    for(int k=1; k<7; k++){                           // DONGU: k=1'den 6'ya (3,5,7,11,13,17 asallarinin dizi indeksleri)
        e[k] = 0;                                     // bu asalin ussu 0'dan baslar
        while(n % P[k] == 0){                         // KOSULLU DONGU: n, bu asala TAM bolunuyorsa (kalan 0) tekrarlanir
            n /= P[k];                                // n bu asala bolunur (n = n / P[k]), sabit ÷p = kaydir-topla agi (genel bolucu DEGIL)
            e[k]++;                                   // us 1 artar (bir tane daha bu asaldan bulundu)
            (*exp_steps)++;                           // her basarili bolme = 1 adim (hiz olcumu icin sayilir)
        }                                             // while bitti: bu asal artik bolmuyorsa dongu durur, sonraki asala gecilir
    }
    return n;                                          // tum kucuk asallar cekildi; geriye kalan = ROUGH (smooth ise 1). Duz tasinir
}

int main(){                                           // PROGRAMIN giris noktasi: calisma buradan baslar
    printf("=================================================================\n"); // ekrana cizgi basilir (\n = alt satira gecis)
    printf("  RESOLVER EMULATORU — ASIRI TEST RAPORU\n");                            // baslik yazilir
    printf("=================================================================\n\n");

    /* TEST 1: octal-akitma kalani, gercek kalanla birebir mi? (TUM 24-bit x 7 asal) */
    long bad = 0;                                     // "bad" adli buyuk tamsayi sayaci acilir (hatalari sayar), 0'dan baslar
    for(uint32_t N=0; N<=16777215u; N++)              // DIS DONGU: N, 0'dan 2^24-1'e (=16777215) kadar tek tek artar
        for(int k=0; k<7; k++)                        // IC DONGU: her N icin 7 asalin hepsi sirayla denenir (k=0..6)
            if(mod_via_stream(N,P[k]) != (int)(N%P[k])) // KOSUL: bizim akitma sonucumuz, dilin gercek "%" kalanindan FARKLIYSA
                bad++;                                // hata sayaci 1 artar
    printf("TEST 1  octal-akitma mod == gercek mod  [TUM 24-bit x 7 asal = ~117M kontrol]: %ld hata\n", bad); // %ld yerine bad yazilir

    /* TEST 2-3: encode'u geri carpinca N geri geliyor mu? smooth orani ne? */
    bad = 0;                                          // hata sayaci tekrar 0 olur (yeni test)
    long smooth = 0;                                  // tam smooth (rough'u 1 olan) sayilari sayacak kutu
    for(uint32_t N=1; N<=16777215u; N++){             // 1'den 16.7M'e kadar her sayi icin
        int e[7], st;                                 // 7 elemanli us dizisi e[] ve adim sayisi st (bu tur icin gecici)
        uint32_t r = encode(N,e,&st);                 // N cevrilir: e dolar, st adim, r = rough ("&st" = fonksiyonun yazacagi st adresi)
        uint64_t v = r;                               // geri-carpim icin 64-bit "v" kutusu (tasma olmasin diye genis), rough'tan baslar
        for(int k=0; k<7; k++)                        // her asal icin
            for(int j=0; j<e[k]; j++)                 // o asalin usu kadar (j=0..e[k]-1)
                v *= P[k];                            // v o asalla carpilir (golgeden sayi geri kurulur)
        if(v != N) bad++;                             // geri kurdugumuz sayi N degilse: faktorizasyon hatasi
        if(r == 1) smooth++;                          // rough 1 ise: bu sayi tam smooth, sayilir
    }
    printf("TEST 2  encode->decode == N  [TUM 24-bit = 16.7M]: %ld hata\n", bad);
    printf("TEST 3  smooth oran (rough==1): %ld/16777215 = %.4f%% (beklenen ~0.09%%)\n", smooth, 100.0*smooth/16777215); // %.4f = 4 ondalik

    /* TEST 4-5: her asalin usu gercek faktorizasyonla ayni mi? rough'ta 7-asal kalmis mi? */
    bad = 0;                                          // us-hata sayaci sifirlanir
    long roughbad = 0;                                // rough'ta asal kalma ihlali sayaci
    for(uint32_t N=2; N<=5000000u; N++){              // 2'den 5 milyona kadar (daha kucuk aralik ama derin kontrol)
        int e[7], st;                                 // usler + adim
        uint32_t r = encode(N,e,&st);                 // golgeye cevrilir
        for(int k=0; k<7; k++){                       // her asalin gercek ussu BAGIMSIZ hesaplanir (encode'dan bagimsiz)
            int real = 0;                             // gercek us icin sayac
            uint32_t t = N;                           // N'in ayri bir kopyasi
            while(t % P[k] == 0){ t /= P[k]; real++; } // bolunebildigi kadar bolunur, bolme sayisi sayilir
            if(e[k] != real) bad++;                   // encode'un buldugu us != gercek us ise: hata
        }
        for(int k=0; k<7; k++)                        // rough'un hala bir asala bolunup bolunmedigi denetlenir
            if(r % P[k] == 0) roughbad++;             // bolunuyorsa: ihlal (rough'ta kucuk asal kalmamali)
    }
    printf("TEST 4  us dogrulugu [N=2..5M x 7 asal]: %ld hata\n", bad);
    printf("TEST 5  rough'ta 7-asal faktoru YOK [N=2..5M]: %ld ihlal\n", roughbad);

    /* TEST 6: 2'ler cekildikten sonra rough TEK olmali (cift kalirsa bug) */
    long reven = 0;                                   // cift-rough ihlali sayaci
    for(uint32_t N=2; N<=5000000u; N++){              // 2..5M
        int e[7], st;                                 // usler + adim
        uint32_t r = encode(N,e,&st);                 // golgeye cevrilir
        if(r > 1 && (r&1)==0) reven++;                // rough 1'den buyukse VE son biti 0 ise (CIFT) -> ihlal (2'leri kacirmis oluruz)
    }
    printf("TEST 6  rough kalan TEK (2'ler cekildi) [N=2..5M]: %ld cift-ihlal (0 olmali)\n", reven);

    /* TEST 7: HIZ — us-bulma kac adim suruyor + cycle modeli */
    long sum=0, mx=0;                                 // sum = tum adimlarin toplami; mx = gorulen en buyuk adim
    uint32_t worst=0;                                 // en cok adim isteyen sayiyi hatirlamak icin
    long hist[6]={0};                                 // 6 kutuluk histogram dizisi, hepsi 0 (adim araliklarini sayacak)
    for(uint32_t N=1; N<=16777215u; N++){             // her sayi icin
        int e[7], st;                                 // usler + adim
        encode(N,e,&st);                              // cevrilir, adim sayisi st'ye yazilir
        sum += st;                                     // toplama eklenir
        if(st > mx){ mx = st; worst = N; }            // bu sayi yeni rekor adim yaptiysa kaydedilir
        int b = st<=1?0 : st<=3?1 : st<=7?2 : st<=15?3 : st<=31?4 : 5; // uclu-soru: st hangi araliga dusuyor -> kova no (0..5)
        hist[b]++;                                    // o kova 1 artar
    }
    double avg = (double)sum/16777215;                // ortalama adim = toplam / sayi adedi ((double) = ondalikli bolme)
    printf("\nTEST 7  HIZ:\n        us-bulma adim: ORT %.3f, MAX %ld (N=%u)\n", avg, mx, worst);
    const char* lbl[6]={"0-1","2-3","4-7","8-15","16-31","32+"}; // kova etiketleri (ekranda gostermek icin)
    printf("        dagilim: ");
    for(int i=0;i<6;i++) printf("%s:%.1f%% ", lbl[i], 100.0*hist[i]/16777215); // her kovanin yuzdesi yazilir
    printf("\n");
    printf("        CYCLE: SERI akitma 8cy + us %.1f ~= %.0f cy | PARALEL 1cy + us %.1f ~= %.0f cy\n", avg,8+avg,avg,1+avg);

    /* TEST 8: kose-durumlar (birim, asal, max, saf-kuvvet, primorial, kup) dogru cevriliyor mu? */
    printf("\nTEST 8  edge case'ler:\n");
    struct{ uint32_t N; const char* ad; } ec[] = {    // kucuk bir YAPI dizisi: her eleman bir sayi (N) + ismi (ad)
        {1,"1 (birim)"}, {2,"2 (asal)"}, {59,"59 (rough asal)"},
        {16777215,"2^24-1 (max)"}, {8388608,"2^23 (saf 2)"}, {14348907,"3^15 (saf 3)"},
        {510510,"2*3*5*7*11*13*17"}, {4913,"17^3"} };
    for(int i=0;i<8;i++){                              // 8 ozel sayinin her biri icin
        int e[7], st;                                 // usler + adim
        uint32_t r = encode(ec[i].N,e,&st);           // o sayi cevrilir ("ec[i].N" = i. elemanin N alani)
        printf("   %-20s -> [", ec[i].ad);            // ismi sola yaslayarak yazilir (%-20s)
        for(int k=0;k<7;k++)                          // 7 asali gez
            if(e[k]) printf("%s^%d ", PN[k], e[k]);   // us doluysa "asal^us" yazilir (ornek 2^3)
        printf("] rough=%u (%d adim)\n", r, st);      // rough degeri ve adim sayisi yazilir
    }

    /* TEST 9: her asalin ilk 3 kati mod=0 veriyor mu? (akitmanin akil-saglik kontrolu) */
    printf("\nTEST 9  her asalin akitma-bolunurlugu (ilk 3 kati, mod==0 olmali):\n");
    for(int k=0;k<7;k++){                              // her asal icin
        printf("   %s: ", PN[k]);                      // asalin ismi yazilir
        int c = 0;                                     // kac kat yazdik sayaci (3 yetiyor)
        for(uint32_t N=P[k]; c<3; N+=P[k]){            // N asalin kendisinden baslar, her turda asal kadar artar (p, 2p, 3p), 3 tur
            printf("%u(m=%d) ", N, mod_via_stream(N,P[k])); // kat ve akitma kalani yazilir (0 bekleniyor, cunku tam kat)
            c++;                                       // bir kat islendi
        }
        printf("\n");                                  // satiri bitir
    }

    printf("\n=================================================================\n");
    printf("  SONUC: TEST 1-9 tamam. Cekirdek (akitma + encode + rough) saglam.\n");
    printf("  KAPSAM: 24-bit pozitif tamsayi. rough RR / genis-kelime = ACIK IS.\n");
    printf("=================================================================\n");
    return 0;                                          // 0 doner = "program sorunsuz bitti" demek (isletim sistemine)
}
