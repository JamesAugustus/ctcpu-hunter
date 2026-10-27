# Kök içinde kesir ve parite

## Ne sınar

Kök dışı ve kök içi POW yorumlarının kanonik dönüşümlerini karşılaştırır. Kök içinde S/8 ve P azaltma işleminin değeri korumasını ve tek POW açılışını kesin el örnekleriyle sınar.

## Nasıl çalışır

S için 0..2^24-1 ve P için 0..7 birleşimleri taranır. Dönüşüm öncesi ve sonrası değerler S×8^p=s×8^P çapraz çarpımıyla denetlenir. On milyon rastgele örnekte kök içi üslerin iki kat ölçeklenmesi karşılaştırılır. Değer veya kanonik biçim sayacının sıfır olmaması başarısızlıktır.

## Neden önemli

Hunter kök birimindeki kesin ve yaklaşık hesapların hata sınırlarını inceler.

## Çalıştırma

```sh
cd TESTLER/HUNTER/05_KAREKOK/kok_virgul_icinde_test
gcc -std=c11 -O2 kok_virgul_icinde_test.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [kok_virgul_icinde_test.c](../../../../../TESTLER/HUNTER/05_KAREKOK/kok_virgul_icinde_test/kok_virgul_icinde_test.c)

Arşivdeki satır sayısı: 107.
