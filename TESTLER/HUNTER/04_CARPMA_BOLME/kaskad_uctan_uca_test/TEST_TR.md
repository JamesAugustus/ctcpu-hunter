# Kaskad uçtan uca

## Ne sınar

Asal üsleri dört adet 0..7 hücresine yazıp çarpma ve bölmeyi hücreler üzerinden yürütür. Üs 28 sınırını ve iki milyon tam bölme çiftinin doğrudan bölümle eşitliğini ölçer.

## Nasıl çalışır

0..56 üsleri dört adet 0..7 hücresine kodlanır. 28'e kadar decode(encode(e))=e aranır, daha büyük üslerde taşma beklenir. Üç milyon çarpım ve iki milyon tam bölüm örneğinde hücrelerden açılan sonuç doğrudan aritmetik değerle karşılaştırılır. Hücre sınırı, taşma bayrağı veya sayısal sonuç uyuşmazlığı hatadır. Hesap hatası saptandığında sıfırdan farklı çıkış kodu döndürüyorum.

## Neden önemli

Asal üs ve rough bileşenleriyle yapılan çarpma ve bölmenin referans aritmetiğe bağlanmasını sağlar.

## Çalıştırma

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/kaskad_uctan_uca_test
gcc -std=c11 -O2 kaskad_uctan_uca_test.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [kaskad_uctan_uca_test.c](kaskad_uctan_uca_test.c)

Arşivdeki satır sayısı: 150.
