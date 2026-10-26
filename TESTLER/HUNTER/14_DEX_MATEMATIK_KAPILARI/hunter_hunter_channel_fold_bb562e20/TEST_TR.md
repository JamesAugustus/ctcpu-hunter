# Kanal katlama referansı

## Ne sınar

Her küçük asal kanalında sınırlı tamsayı aralığını katlayarak kalan üretir. Sonucu doğrudan mod işlemiyle ve her katlamanın eşkalıntı değişmeziyle denetler.

## Nasıl çalışır

sinama.py gate_y kapısını çağırır. n=0..65535 sayıları q=3,7,5,17,11,13 kanallarının her birinde, toplam 393216 kez katlanır. 3 ve 7 için yüksek ve düşük bit blokları toplanır, 5,17,11,13 için ilgili 2,4,5,6 bit blokları çıkarılır. İşaret korunarak katlanan değer son aşamada q ekleme veya çıkarma ile 0..q-1 aralığına alınır. Sonuç n mod q ile aynı olmalı, her iz adımında mod q eşdeğerliği korunmalı ve mutlak değer kesin küçülmelidir. Negatif,65536,desteklenmeyen31 kanalı ve bool girdiler reddedilir. İlk kalan, iz veya doğrulama hatası FAIL verir ve başlatıcı assert ile durur. Ana dosyanın yazdıran girişi FAIL dönüşünü çıkış koduna bağlamaz.

## Neden önemli

DEX matematik kapılarının sonlu girdi alanındaki kabul sözleşmesine aittir.

## Çalıştırma

```sh
cd TESTLER/HUNTER/14_DEX_MATEMATIK_KAPILARI/hunter_hunter_channel_fold_bb562e20/kod/MERSENNE/DEX/DEX_PIPELINE_001/runs/20260908T051824.547563Z/code
python3 sinama.py
```

Gerekenler: Python 3.

## Kaynak

Kaynak: [hunter_channel_fold.py](kod/MERSENNE/DEX/DEX_PIPELINE_001/runs/20260908T051824.547563Z/code/models/hunter_channel_fold.py)

Arşivdeki satır sayısı: 150.

Katalogdaki python -c giriş kodu sinama.py dosyasına alındı. Matematik kapıları aynı sırayla çağrılır.
