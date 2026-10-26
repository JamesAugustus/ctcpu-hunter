# Tür ve POW tam tarama

## Ne sınar

24 bit sayı, sekiz POW ve sekiz türden oluşan 2^30 durumun kanonik gösterimini kurar. Değer korunumu, ikinci kanonikleştirmenin etkisizliği ve türün yapısal kurallarını denetler.

## Nasıl çalışır

Sekiz tür, 2^24 mantissa ve sekiz POW değeriyle 2^30 durum oluşturulur. Düz türler, ters türler ve kök türleri için ayrı kesin çapraz çarpımlar kullanılır. İkinci normalleştirme kaydı değiştirmemeli ve türün 8 ya da 64 bölünebilirlik kuralı korunmalıdır. Değer, idempotens veya biçim ihlali hata sayılır.

## Neden önemli

Hunter tür ve ölçek kodlarının aritmetik anlamının korunmasını inceler.

## Çalıştırma

```sh
cd TESTLER/HUNTER/06_TIPLER/tur_pow_tam_tarama
gcc -std=c11 -O2 tur_pow_tam_tarama.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [tur_pow_tam_tarama.c](tur_pow_tam_tarama.c)

Arşivdeki satır sayısı: 82.
