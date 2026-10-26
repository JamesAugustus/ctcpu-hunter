# Sekizlik üs sayacının sınırı

## Ne sınar

Akan sayaç çekirdeğinde dört satırlık sekizlik üs sayacının yedi kanalın her birinde 0'dan 4095'e kadar doğru saydığını sınar. $2^{4095}$ geri kurulur, bir sonraki üs ve sınırı aşan çarpım reddedilir.

## Nasıl çalışır

Çekirdek kod değiştirilmeden dahil edilir. Her kanalda sayaç birer birer artırılıp okunur. Sınırda geri kurma, ret, rough tam bölme ve sıfıra bölme durumları ayrı ayrı denetlenir.

## Neden önemli

Dişli modelindeki elde pimlerinin ve 4095 sınırının gerçekten çalıştığını gösterir.

## Çalıştırma

```sh
cd TESTLER/NIHAI_EK/sayac_siniri
gcc -O2 -I. sayac_siniri.c -o sayac_siniri -lm && ./sayac_siniri
```

Gerekenler: GCC ve libm.
