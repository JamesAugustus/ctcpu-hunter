# Karantina çifti

## Ne sınar

Sıfıra bölmeden sonra pay izini biriktiren kilitli register çiftini çalıştırır. Kilitli hücreden düz sayı açılamamasını, sıfır pay ayrımını ve yeni LOAD ile temizlenmesini denetler.

## Nasıl çalışır

Sıfıra bölme sonrasında çarpanlar kilitli pay izine eklenir. İz 6×1365613=8193678 olmalı ve hücre düz sayı olarak açılamamalıdır. 0/0 ile 6/0 pay izleri ayrı tutulur. Yeni LOAD kilidi temizlemelidir. Bu sabit beklentilerin herhangi birinin bozulması hata sayacını artırır.

## Neden önemli

Hunter tür ve ölçek kodlarının aritmetik anlamının korunmasını inceler.

## Çalıştırma

```sh
cd TESTLER/HUNTER/06_TIPLER/karantina_cift_demo
gcc -std=c11 -O2 karantina_cift_demo.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [karantina_cift_demo.c](../../../../../TESTLER/HUNTER/06_TIPLER/karantina_cift_demo/karantina_cift_demo.c)

Arşivdeki satır sayısı: 67.
