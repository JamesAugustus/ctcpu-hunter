# Kesir katmanı v1.4

## Ne sınar

Pay payda çiftinde sekizlik ölçek, kesir sadeleşmesi ve kök işlemlerini beklenen değerlerle karşılaştırır. Sıfıra bölme karantinasını, özel yaklaşık bayrağını ve mantissa taşmasını kontrol eder.

## Nasıl çalışır

Sabit rasyonel ve kök örnekleri dört açma modundan geçirilir. 3/7 örneğinde kesin mod pay ve paydayı korumalı, yaklaşık mod 8^-7 ölçeğinde yakın değer ile OZEL bayrağı üretmelidir. Rastgele çarpım ve bölüm örnekleri bağımsız pay ve payda çarpımlarıyla denetlenir. Sıfıra bölme kilidi, iz veya çapraz çarpım farklıysa hata sayılır.

## Neden önemli

Asal üs ve rough bileşenleriyle yapılan çarpma ve bölmenin referans aritmetiğe bağlanmasını sağlar.

## Çalıştırma

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/kesir_emulator
gcc -std=c11 -O2 kesir_emulator.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [kesir_emulator.c](kesir_emulator.c)

Arşivdeki satır sayısı: 322.
