# Karekök çekirdeği

## Ne sınar

Sekizlik basamak karekökünü tam karelerde ve floor eşitsizliğinde denetler. İkili basamak yöntemiyle eşitliği, yaklaşık kök hatalarını ve 64 bit sınır örneklerini ayrıca karşılaştırır.

## Nasıl çalışır

n=0..3000 için n² girdisinin kökü n ile karşılaştırılır. N=0..200000 aralığında sekizlik ve ikili kök yolları eşit olmalıdır. Bir milyona kadar r²<=N<(r+1)² koşulu aranır ve üç 64 bit sınır girdisi ayrıca denetlenir. Tam kare, yöntem veya floor koşulu uyuşmazlığı hata sayılır.

## Neden önemli

Hunter kök birimindeki kesin ve yaklaşık hesapların hata sınırlarını inceler.

## Çalıştırma

```sh
cd TESTLER/HUNTER/05_KAREKOK/karekok_emulator
gcc -std=c11 -O2 karekok_emulator.c -o ./test_programi -lm && ./test_programi
```

Gerekenler: gcc, libm.

## Kaynak

Kaynak: [karekok_emulator.c](karekok_emulator.c)

Arşivdeki satır sayısı: 170.
