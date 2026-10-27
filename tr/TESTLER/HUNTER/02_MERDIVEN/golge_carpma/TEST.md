# Merdiven temsilinde çarpma

## Ne sınar

Merdivende saklanan iki sayıyı asal üs ve rough bileşenlerine açıp çarpar ve yeniden saklar. Küçük çiftlerde, büyük rough çiftlerinde ve kapasite taşmasında sayısal değer korunmasını kontrol eder.

## Nasıl çalışır

1≤a≤b<4096 koşulunu sağlayan 8.386.560 operand çifti ve beş milyon rough çifti merdiven kaydından açılır. Üsler toplanır, rough bileşenler binom yoluyla çarpılır ve sonuç yeniden saklanır. Açılan sonuç uint64_t(a)×b ile aynı olmalıdır. Kapasiteyi aşan örneklerde de geniş sonuç korunmalı ve kullanılan küçük çarpım operandı yediyi aşmamalıdır.

## Neden önemli

Gölge temsilindeki merdiven satırlarının değer korunumunu ve kayıt kapasitesini inceler.

## Çalıştırma

```sh
cd TESTLER/HUNTER/02_MERDIVEN/golge_carpma
gcc -std=c11 -O2 golge_carpma.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [CEM_MODELI/golge_carpma.c](../../../../../TESTLER/HUNTER/02_MERDIVEN/golge_carpma/golge_carpma.c)

Arşivdeki satır sayısı: 223.
