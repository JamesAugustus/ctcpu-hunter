# Üslerle çarpma ve bölme

## Ne sınar

Asal üsleri toplayarak çarpma ve çıkararak bölme yapar. Tam bölünen, kesirli, rough ve kapasite sınırı örneklerini doğrudan aritmetik ile karşılaştırır.

## Nasıl çalışır

Yirmi milyon işaretli operand çifti asal üs ve rough bölümlerine ayrılır. Üs toplayan çarpım __int128(a)×b ile karşılaştırılır. Tam bölüm, kesirli bölüm ve rough yolu ayrıca denenir. 0..40 üslerinde dört hücre toplamı başlangıç üssünü korumalı, 28 üstünde taşma bildirilmelidir. Karşılaştırma farkları hata sayacına yazılır.

## Neden önemli

Asal üs ve rough bileşenleriyle yapılan çarpma ve bölmenin referans aritmetiğe bağlanmasını sağlar.

## Çalıştırma

```sh
cd TESTLER/HUNTER/04_CARPMA_BOLME/mul_div_emulator
gcc -std=c11 -O2 mul_div_emulator.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [mul_div_emulator.c](../../../../../TESTLER/HUNTER/04_CARPMA_BOLME/mul_div_emulator/mul_div_emulator.c)

Arşivdeki satır sayısı: 156.
