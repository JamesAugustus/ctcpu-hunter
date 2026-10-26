# Sabit noktalı karekök ölçümü

## Ne sınar

Sabit noktalı kesirlerin karekökünü kesin basamak, binom yaklaşımı ve logaritmik sayı sistemi yollarında hesaplar. Aynı girdilerde referans köke göre hatayı ve model adım sayısını karşılaştırır.

## Nasıl çalışır

F=16 kesir bitli girdiler isqrt_octal, binom1 ve lns yollarına verilir. Her sonuç aynı ölçekle gerçek sayıya çevrilip sqrt referansından farkı hesaplanır. Çarpım ve sadeleşme örnekleri ayrıca yazdırılır. Kod bir sayısal kabul eşiği belirlemez.

## Neden önemli

Hunter kök birimindeki kesin ve yaklaşık hesapların hata sınırlarını inceler.

## Çalıştırma

```sh
cd TESTLER/HUNTER/05_KAREKOK/frac_test
gcc -std=c11 -O2 frac_test.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [frac_test.c](frac_test.c)

Arşivdeki satır sayısı: 68.
