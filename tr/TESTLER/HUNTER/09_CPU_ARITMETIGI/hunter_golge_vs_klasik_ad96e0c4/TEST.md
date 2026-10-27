# Merdiven ve klasik çarpım maliyeti

## Ne sınar

Fiili merdiven encode, aç ve çarp zincirini klasik pozisyonel çarpımla karşılaştırır. Aynı girdilerde toplama, küçük çarpım ve kaydırma sayılarını ölçer.

## Nasıl çalışır

Önce 24 bit alanda smooth ve rough dağılımı sayılır. Sonra 200000 çift encode, aç ve çarp adımlarından geçirilir. Üsleri ve rough bileşenleri birleştiren yol ile klasik pozisyonel çarpımın toplama, küçük çarpım ve kaydırma adetleri karşılaştırılır. Tam bölme örneklerinde üslerin ve rough bileşenin bölünebilmesi aranır. Program maliyet tablolarını raporlar.

## Neden önemli

Hunter CPU ve aritmetik modellerinin sayısal sözleşmesine aittir.

## Çalıştırma

```sh
cd TESTLER/HUNTER/09_CPU_ARITMETIGI/hunter_golge_vs_klasik_ad96e0c4
gcc -std=gnu11 -O2 golge_vs_klasik.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [golge_vs_klasik.c](../../../../../TESTLER/HUNTER/09_CPU_ARITMETIGI/hunter_golge_vs_klasik_ad96e0c4/golge_vs_klasik.c)

Arşivdeki satır sayısı: 240.
