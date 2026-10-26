# Akan sayaç, 744 yürütme izi

## Ne sınar

744 sayısının resolverdan geçirilerek asal üs ve sekizlik sayaç durumlarına ayrılışını gösterir. Geri kurulan rm değerinin 1350_8 yani 744 ile birebir eşleştiğini denetler.

## Nasıl çalışır

--iz 744 girişi her resolver geçişinde asal üslerini ve sayaç değişimini yazdırır. Çıktıdaki rm değeri tekrar okunur ve 1350_8=744 eşitliği aranır. Geri kurulan değer farklıysa veya birebir doğrulama oluşmazsa sınama başarısızdır.

## Neden önemli

Hunter resolverının konumsal sayı ile asal üs kaydı arasındaki dönüşümüne aittir.

## Çalıştırma

```sh
cd TESTLER/HUNTER/01_RESOLVER/hunter_iz
gcc -std=c11 -O2 hunter_cekirdek.c -o ./test_programi -lm && ./test_programi --iz 744
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [hunter_cekirdek.c](hunter_cekirdek.c)

Arşivdeki satır sayısı: 800.
