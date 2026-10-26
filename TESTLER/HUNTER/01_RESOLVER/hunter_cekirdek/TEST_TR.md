# Akan sayaç çekirdeği, tam test

## Ne sınar

Akan sayaç resolverının 1..2^24 sayılarında geri kurma doğruluğunu denetler. Yüz bin rastgele çiftte toplama, çıkarma, tembel gölgeli çarpma ve tam bölmeyi geniş tamsayı referansıyla karşılaştırır.

## Nasıl çalışır

--test girişi resolverı 1 ile 2^24 arasındaki sayılara uygular ve her kaydı tekrar açar. Ardından 100000 çiftte toplama, çıkarma, çarpma ve tam bölme sonuçlarını geniş tamsayı referansıyla karşılaştırır. Ters çıkarma ve tam bölünmeyen bölüm reddi ayrıca denenir. Toplam hata sayısının sıfır olmaması başarısızlık koşuludur.

## Neden önemli

Hunter resolverının konumsal sayı ile asal üs kaydı arasındaki dönüşümüne aittir.

## Çalıştırma

```sh
cd TESTLER/HUNTER/01_RESOLVER/hunter_cekirdek
gcc -std=c11 -O2 hunter_cekirdek.c -o ./test_programi -lm && ./test_programi --test
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [hunter_cekirdek.c](hunter_cekirdek.c)

Arşivdeki satır sayısı: 800.
