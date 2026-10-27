# Günlük iddiaları T01-T22

## Ne sınar

Yayındaki T01..T22 matematik iddialarını sonlu örnekler ve karşı örneklerle inceler. Mersenne çarpan koşulları, Pascal taban eşiği, Lucas Lehmer izleri ve gösterim bağıntılarının durumunu HOLDS, FAILS veya UNTESTED olarak ayırır.

## Nasıl çalışır

Mersenne çarpan yasasını 3..31 asal üslerinde ve sekizlik gösterimi 3..300 üslerinde denetler. Pascal satırlarını n=1..30 için en büyük katsayıdan bir ve iki büyük tabanlarda geri okur, 1..64 sayı çiftlerinde asal üs vektörünün çarpım altında toplandığını karşılaştırır. Üçlü zincirde b=2..10, n=1..18 doğrudan toplamı kapalı formülle eşler ve q≤2000000 asallarında 3^(q-1)≡1 mod q² koşulunu tarar. Bir eşitliğin bozulması fail_card çağrısıdır. Bazı kartlar bilinen karşı örneği doğrulamayı amaçlar, bu yüzden karttaki FAILS etiketi tek başına uygulama hatası sayılmaz ve UNTESTED kartı doğruluk hükmü vermez.

## Neden önemli

Hunter yayınındaki numaralı iddiaların sonlu denetim kapsamını görünür kılar.

## Çalıştırma

```sh
cd TESTLER/HUNTER/07_GUNLUK_IDDIALARI/journal_tests
gcc -std=c11 -O2 journal_tests.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [journal_tests.c](../../../../../journal_tests.c)

Arşivdeki satır sayısı: 811.
