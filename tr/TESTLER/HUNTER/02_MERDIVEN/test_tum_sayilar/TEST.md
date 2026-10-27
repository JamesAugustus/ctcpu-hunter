# Bütün 24 bit sayılar

## Ne sınar

Tüm 24 bit sayıları N6 merdiven saklamasına dönüştürüp geri okur. Sayısal eşitliği, dört satıra sığmayı ve sabit kabul örneklerini denetler.

## Nasıl çalışır

1..16777215 için N6 encode kaydı üretilir. Dört satır ve rough kuyruğu yeniden açılarak başlangıç N ile karşılaştırılır. Kullanılan satır sayısı, en büyük üsler ve sığmayan örnekler biriktirilir. İlk değer uyuşmazlığı kaydedilir ve hata sayacı artırılır.

## Neden önemli

Gölge temsilindeki merdiven satırlarının değer korunumunu ve kayıt kapasitesini inceler.

## Çalıştırma

```sh
cd TESTLER/HUNTER/02_MERDIVEN/test_tum_sayilar
gcc -std=c11 -O2 test_tum_sayilar.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [test_tum_sayilar.c](../../../../../TESTLER/HUNTER/02_MERDIVEN/test_tum_sayilar/test_tum_sayilar.c)

Arşivdeki satır sayısı: 122.
