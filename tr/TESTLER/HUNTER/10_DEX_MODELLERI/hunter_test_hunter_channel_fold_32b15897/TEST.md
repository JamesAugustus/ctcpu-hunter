# Kanal katlaması

## Ne sınar

Kanal kalanını her adımda doğrudan mod hesabıyla karşılaştırır. İşaretli katlama izinin büyüklük sınırını, eşlik değişmezini ve düzeltme sayımlarını kontrol eder.

## Nasıl çalışır

q=3,7 kanallarında yüksek ve düşük bloklar toplanır, q=5,17,11,13 kanallarında uygun 2,4,5,6 bit genişlikleriyle fark alınır. Her kanal için n=0..65535 tam taranır ve sonuç n mod q ile karşılaştırılır. Sınır girdilerinin izinde işaret korunmalı, katlama mutlak büyüklüğü artırmamalı ve adım öncesi ile sonrası mod q eşdeğer kalmalıdır. Yanlış fakat 0..q-1 içinde kalan bir sonuç bilerek yerleştirilir ve gate_y'nin bunu reference_mismatch olarak yakalaması beklenir. Tam kapının 393216 deneme ve beş geçersiz girdi sayacı kontrol edilir. Yanlış kalan, iz değişmezi, hata yakalama davranışı veya beklenen ret uyuşmazlığı unittest başarısızlığıdır.

## Neden önemli

DEX model katmanının bağımsız referanslarla doğrulanmasına aittir.

## Çalıştırma

```sh
cd TESTLER/HUNTER/10_DEX_MODELLERI/hunter_test_hunter_channel_fold_32b15897/kod/MERSENNE/DEX/DEX_PIPELINE_001/tests
python3 test_hunter_channel_fold.py
```

Gerekenler: Python 3.

kod/ dizini kaynakta kullanılan göreli hiyerarşiyi korur.

## Kaynak

Kaynak: [test_hunter_channel_fold.py](../../../../../TESTLER/HUNTER/10_DEX_MODELLERI/hunter_test_hunter_channel_fold_32b15897/kod/MERSENNE/DEX/DEX_PIPELINE_001/tests/test_hunter_channel_fold.py)

Arşivdeki satır sayısı: 88.
