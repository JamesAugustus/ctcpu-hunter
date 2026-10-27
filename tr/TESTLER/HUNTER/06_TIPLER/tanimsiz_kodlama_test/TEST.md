# Tanımsız değer kodlaması

## Ne sınar

Yaklaşık sıfır ile tanımsız değer için eski ve yeni bit kodlarının çakışmasını sayar. TÜR=1/x ve SAYI=0 düzeninin meşru sıfırdan ayrıldığını kontrol eder.

## Nasıl çalışır

8^-12 dahil, 8^-6 hariç aralıktaki küçük değerleri yaklaşık sayı koduna çeviriyorum. Sıfıra yuvarlanan meşru değerlerde eski ve yeni tanımsızlık işaretlerinin çakışma sayıları karşılaştırılır. Bütün 24 bit bölenlerde sıfır paydalı olay ayrı izlenir. Yeni kodun meşru sıfırı tanımsız sayması veya sıfır dışı böleni sıfır kodlaması ihlaldir.

## Neden önemli

Hunter tür ve ölçek kodlarının aritmetik anlamının korunmasını inceler.

## Çalıştırma

```sh
cd TESTLER/HUNTER/06_TIPLER/tanimsiz_kodlama_test
gcc -std=c11 -O2 tanimsiz_kodlama_test.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [tanimsiz_kodlama_test.c](../../../../../TESTLER/HUNTER/06_TIPLER/tanimsiz_kodlama_test/tanimsiz_kodlama_test.c)

Arşivdeki satır sayısı: 85.
