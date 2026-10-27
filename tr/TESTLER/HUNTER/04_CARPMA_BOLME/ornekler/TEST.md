# 41 çarpma ve bölme örneği

## Ne sınar

Asal üs vektöründe çarpma, tam bölme ve rasyonel bölme örneklerini geniş tamsayı referansıyla karşılaştırır. Rough çarpımı, işaret ve büyük ara çarpımı sadeleştiren zincir örneklerini de gösterir.

## Nasıl çalışır

Sabit smooth ve rough örnekler asal üslerine ayrılır. Çarpmada üsler toplanır, bölmede çıkarılır ve sonuç tekrar sayıya açılır. Tam sayılarda __int128 çarpımı, kesirlerde çapraz çarpım referans alınır. HATA sayacı sıfır değilse sınama başarısızdır.

## Neden önemli

Asal üs ve rough bileşenleriyle yapılan çarpma ve bölmenin referans aritmetiğe bağlanmasını sağlar.

## Çalıştırma

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/ornekler
gcc -std=c11 -O2 ornekler.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [ornekler.c](../../../../../TESTLER/HUNTER/04_CARPMA_BOLME/ornekler/ornekler.c)

Arşivdeki satır sayısı: 139.
