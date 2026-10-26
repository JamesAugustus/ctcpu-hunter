# Büyük kalan için çarpma yolu

## Ne sınar

Rough çarpımı sekizlik binom açılımı, kaydırma ve en çok yedi değerli küçük çarpımlarla hesaplar. Sonucu __int128 doğrudan çarpımla karşılaştırıp aritmetik işlem sayılarını yazdırır.

## Nasıl çalışır

Beş milyon operand çiftinde rough bileşenlerin sekizlik açılımları alınır. Küçük basamak çarpımları ve kaydırmalarla oluşturulan got değeri __int128 doğrudan çarpımıyla karşılaştırılır. Dört sabit örnek ayrıca yazdırılır. got!=real olması hatadır, toplama ve kaydırma adetleri ayrı maliyet ölçümüdür.

## Neden önemli

Asal üs ve rough bileşenleriyle yapılan çarpma ve bölmenin referans aritmetiğe bağlanmasını sağlar.

## Çalıştırma

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/rough_fallback_devre_test
gcc -std=c11 -O2 rough_fallback_devre_test.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [rough_fallback_devre_test.c](rough_fallback_devre_test.c)

Arşivdeki satır sayısı: 99.
