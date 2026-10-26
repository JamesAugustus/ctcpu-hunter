# Kaydır ve topla referansı

## Ne sınar

8,16,24 bit işaretsiz çarpımı bit seçimi, toplama ve kaydırma üzerinden üretir. Sonucu doğrudan geniş tamsayı çarpımıyla ve geçersiz giriş davranışını beklenen redle karşılaştırır.

## Nasıl çalışır

0..255 aralığındaki 65536 çiftin 8 bit çarpımı ve 16 ile 24 bit sınır örnekleri üretilir. Seçilen bit için çarpılan kaydırılır ve akümülatöre eklenir. Sonuç uint64_t(a)×b referansına eşit olmalıdır. Desteklenmeyen genişlik, sınır dışı operand ve boş çıkış adresi reddedilmeli, eski çıkış değeri korunmalıdır.

## Neden önemli

Asal üs ve rough bileşenleriyle yapılan çarpma ve bölmenin referans aritmetiğe bağlanmasını sağlar.

## Çalıştırma

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/multiply_add
gcc -std=c11 -O2 multiply_add.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [multiply_add.c](multiply_add.c)

Arşivdeki satır sayısı: 124.
