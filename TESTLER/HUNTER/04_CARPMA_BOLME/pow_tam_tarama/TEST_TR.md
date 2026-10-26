# POW tam tarama

## Ne sınar

24 bit sayı ile sekiz POW birleşimindeki 134217728 durumu kanonikleştirir. Kesin çapraz çarpımla değer korunumu, idempotens ve gösterim kuralını denetler.

## Nasıl çalışır

S=0..2^24-1 ve P=0..7 için 134217728 durum kanonikleştirilir. S×8^p=s×8^P çapraz çarpımıyla değer korunumu aranır. İkinci kanonikleştirme aynı s ve p değerlerini vermelidir. Sıfırda p=0, sıfır dışında ise p bitmedikçe s'nin 8 ile bölünmemesi gerekir. Üç koşulun her ihlali ayrı sayılır.

## Neden önemli

Asal üs ve rough bileşenleriyle yapılan çarpma ve bölmenin referans aritmetiğe bağlanmasını sağlar.

## Çalıştırma

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/pow_tam_tarama
gcc -std=c11 -O2 pow_tam_tarama.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [pow_tam_tarama.c](pow_tam_tarama.c)

Arşivdeki satır sayısı: 57.
