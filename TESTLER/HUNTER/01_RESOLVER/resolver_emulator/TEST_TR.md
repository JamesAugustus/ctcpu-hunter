# Resolver tam tarama

## Ne sınar

Sekizlik basamak akıtma ile kalan hesabını tüm 24 bit sayılarda yedi asalın doğrudan mod işlemiyle karşılaştırır. Encode decode dönüşünü, asal üslerini ve rough içinde küçük asal kalmaması koşulunu ayrıca denetler.

## Nasıl çalışır

N=0..16777215 ve p=2,3,5,7,11,13,17 için sekizlik akıştan kalan çıkarılır. Akış kalanı N%p ile karşılaştırılır. Sonra 1..16777215 sayıları asal üs ve rough bileşenlerine ayrılıp tekrar çarpılır. Geri dönüşün N olmaması, yanlış üs veya rough içinde küçük asal kalması hata sayacını artırır.

## Neden önemli

Hunter resolverının konumsal sayı ile asal üs kaydı arasındaki dönüşümüne aittir.

## Çalıştırma

```sh
cd TESTLER/HUNTER/01_RESOLVER/resolver_emulator
gcc -std=c11 -O2 resolver_emulator.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [resolver_emulator.c](resolver_emulator.c)

Arşivdeki satır sayısı: 155.
