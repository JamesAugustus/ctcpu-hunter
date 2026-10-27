# Gölge çekirdeği kabul örnekleri

## Ne sınar

Merdiven gölge çekirdeğinin 23 kabul örneğinde sıfır, çarpma, bölme, faktöriyel ve kök davranışını denetler. İşlem sonrasında sonucun merdivene tekrar saklanıp aynı değerle okunmasını kontrol eder.

## Nasıl çalışır

0,1,17,360,738,41,720720,1000003 örnekleri saklanıp geri okunur. Ardından 12×10=120, 41×43=1763, tam ve sembolik kökler, faktöriyel ve mod örnekleri CHK yordamına verilir. Son çarpım yeniden merdivene yazılıp açılır. Beklenen değer veya bayraklardan herhangi biri farklıysa FAIL sayacı artar.

## Neden önemli

Gölge temsilindeki merdiven satırlarının değer korunumunu ve kayıt kapasitesini inceler.

## Çalıştırma

```sh
cd TESTLER/HUNTER/02_MERDIVEN/golge_emulator
gcc -std=c11 -O2 golge_emulator.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [golge_emulator.c](../../../../../TESTLER/HUNTER/02_MERDIVEN/golge_emulator/golge_emulator.c)

Arşivdeki satır sayısı: 359.
