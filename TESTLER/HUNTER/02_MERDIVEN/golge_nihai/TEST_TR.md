# Sekizlik iniş, N6 merdiven

## Ne sınar

N6 merdiven gösteriminde 24 bit sayıyı sınırlı satırlara kaydedip tekrar tam sayıya dönüştürür. Dört satır kapsamını ve farklı sayıların aynı kayıt özetine çakışma durumunu tarar.

## Nasıl çalışır

1..2^24-1 sayıları dört satırlı N6 kaydına dönüştürülür. val ile geri okunan değer N ile karşılaştırılır. Her kaydın özeti karma tablosuna yerleştirilerek aynı özeti veren farklı girdiler sayılır. Geri dönüş hatası veya kayıt çakışması ilgili doğruluk koşulunu bozar, sığmayan sayılar ayrıca raporlanır.

## Neden önemli

Gölge temsilindeki merdiven satırlarının değer korunumunu ve kayıt kapasitesini inceler.

## Çalıştırma

```sh
cd TESTLER/HUNTER/02_MERDIVEN/golge_nihai
gcc -std=c11 -O2 golge_nihai.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [CEM_MODELI/golge_nihai.c](golge_nihai.c)

Arşivdeki satır sayısı: 84.
