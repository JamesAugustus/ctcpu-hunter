# 24 bit karekök hata taraması

## Ne sınar

2..16777215 sayılarında binom yaklaşımı, Newton düzeltmeleri ve LNS karekök yollarının hatasını ölçer. Her yöntemin en büyük ve ortalama bağıl hatasını standart sqrt referansıyla karşılaştırır.

## Nasıl çalışır

N=2..16777215 için standart sqrt ve beş yaklaşım hesaplanır. Her yöntemde abs(yaklaşım-sqrt(N))/sqrt(N) bağıl hatası biriktirilir. En büyük hata, bunu üreten girdi ve ortalama hata yazdırılır. Kaynak bir geçti veya kaldı eşiği tanımlamaz.

## Neden önemli

Hunter kök birimindeki kesin ve yaklaşık hesapların hata sınırlarını inceler.

## Çalıştırma

```sh
cd TESTLER/HUNTER/05_KAREKOK/test_dogruluk
gcc -std=c11 -O2 test_dogruluk.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [test_dogruluk.c](test_dogruluk.c)

Arşivdeki satır sayısı: 24.
